#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <system_error>
#include <stdexcept>
#include <string>
#include <vector>

#include <sys/wait.h>

namespace {

constexpr char kMagic[4] = {'T', 'S', 'C', 'P'};
constexpr std::uint8_t kVersion = 1;
constexpr std::size_t kMaxRun = 130;
constexpr std::size_t kMaxLiteral = 128;

std::vector<std::uint8_t> readFile(const std::string &path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Failed to open input file: " + path);
    }
    std::vector<std::uint8_t> data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return data;
}

void writeFile(const std::string &path, const std::vector<std::uint8_t> &data) {
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Failed to open output file: " + path);
    }
    out.write(reinterpret_cast<const char *>(data.data()), static_cast<std::streamsize>(data.size()));
    if (!out) {
        throw std::runtime_error("Failed to write output file: " + path);
    }
}

std::filesystem::path makeTempPath(const std::string &suffix) {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<std::uint64_t> dist;
    const auto base = std::filesystem::temp_directory_path();
    for (;;) {
        auto candidate = base / ("twostage_" + std::to_string(dist(gen)) + suffix);
        if (!std::filesystem::exists(candidate)) {
            return candidate;
        }
    }
}

class TempFile {
  public:
    explicit TempFile(const std::string &suffix) : path_(makeTempPath(suffix)) {}
    const std::filesystem::path &path() const { return path_; }
    ~TempFile() {
        std::error_code ec;
        std::filesystem::remove(path_, ec);
    }

  private:
    std::filesystem::path path_;
};

std::string shellQuote(const std::filesystem::path &path) {
    const std::string input = path.string();
    std::string quoted = "'";
    for (char c : input) {
        if (c == '\'') {
            quoted += "'\\''";
        } else {
            quoted += c;
        }
    }
    quoted += "'";
    return quoted;
}

void runCommand(const std::string &cmd) {
    int rc = std::system(cmd.c_str());
    if (rc == -1) {
        throw std::runtime_error("Failed to launch command: " + cmd);
    }
    if (!WIFEXITED(rc) || WEXITSTATUS(rc) != 0) {
        throw std::runtime_error("Command failed: " + cmd);
    }
}

std::vector<std::uint8_t> rleEncode(const std::vector<std::uint8_t> &data) {
    std::vector<std::uint8_t> packed;
    std::size_t i = 0;
    const std::size_t n = data.size();
    while (i < n) {
        std::size_t runLength = 1;
        while (i + runLength < n && data[i + runLength] == data[i] && runLength < kMaxRun) {
            ++runLength;
        }
        if (runLength >= 3) {
            std::uint8_t header = 0x80 | static_cast<std::uint8_t>(runLength - 3);
            packed.push_back(header);
            packed.push_back(data[i]);
            i += runLength;
            continue;
        }
        std::size_t literalStart = i;
        std::size_t literalLen = 0;
        do {
            ++literalLen;
            ++i;
            if (i >= n) {
                break;
            }
            runLength = 1;
            while (i + runLength < n && data[i + runLength] == data[i] && runLength < kMaxRun) {
                ++runLength;
            }
        } while (literalLen < kMaxLiteral && runLength < 3);
        std::uint8_t header = static_cast<std::uint8_t>(literalLen - 1);
        packed.push_back(header);
        packed.insert(packed.end(), data.begin() + literalStart, data.begin() + literalStart + literalLen);
    }
    return packed;
}

std::vector<std::uint8_t> rleDecode(const std::vector<std::uint8_t> &data) {
    std::vector<std::uint8_t> unpacked;
    std::size_t i = 0;
    const std::size_t n = data.size();
    while (i < n) {
        std::uint8_t header = data[i++];
        if (header & 0x80) {
            if (i >= n) {
                throw std::runtime_error("Corrupt RLE stream (missing run byte)");
            }
            std::uint8_t value = data[i++];
            std::size_t runLength = (header & 0x7F) + 3;
            unpacked.insert(unpacked.end(), runLength, value);
        } else {
            std::size_t literalLen = static_cast<std::size_t>(header) + 1;
            if (i + literalLen > n) {
                throw std::runtime_error("Corrupt RLE stream (literal overflow)");
            }
            unpacked.insert(unpacked.end(), data.begin() + i, data.begin() + i + literalLen);
            i += literalLen;
        }
    }
    return unpacked;
}

std::vector<std::uint8_t> gzipCompress(const std::vector<std::uint8_t> &input, int level) {
    TempFile tempIn(".raw");
    TempFile tempOut(".gz");
    writeFile(tempIn.path().string(), input);
    std::string cmd = "gzip -c -" + std::to_string(level) + " " + shellQuote(tempIn.path()) +
                      " > " + shellQuote(tempOut.path());
    runCommand(cmd);
    return readFile(tempOut.path().string());
}

std::vector<std::uint8_t> gzipDecompress(const std::vector<std::uint8_t> &input) {
    TempFile tempIn(".gz");
    TempFile tempOut(".raw");
    writeFile(tempIn.path().string(), input);
    std::string cmd = "gzip -dc " + shellQuote(tempIn.path()) + " > " + shellQuote(tempOut.path());
    runCommand(cmd);
    return readFile(tempOut.path().string());
}

void compressFile(const std::string &inputPath, const std::string &outputPath, int level) {
    auto raw = readFile(inputPath);
    auto primary = gzipCompress(raw, level);
    auto secondary = rleEncode(primary);

    std::vector<std::uint8_t> payload;
    payload.insert(payload.end(), std::begin(kMagic), std::end(kMagic));
    payload.push_back(kVersion);
    payload.push_back(static_cast<std::uint8_t>(level));
    payload.reserve(payload.size() + 8 + secondary.size());
    std::uint64_t originalSize = static_cast<std::uint64_t>(raw.size());
    for (int i = 0; i < 8; ++i) {
        payload.push_back(static_cast<std::uint8_t>((originalSize >> (i * 8)) & 0xFF));
    }
    payload.insert(payload.end(), secondary.begin(), secondary.end());

    writeFile(outputPath, payload);
}

void decompressFile(const std::string &inputPath, const std::string &outputPath) {
    auto fileData = readFile(inputPath);
    if (fileData.size() < 4 + 1 + 1 + 8) {
        throw std::runtime_error("Input too small to be a valid archive");
    }
    if (!std::equal(std::begin(kMagic), std::end(kMagic), fileData.begin())) {
        throw std::runtime_error("Invalid file magic (not TSCP)");
    }
    std::size_t offset = 4;
    std::uint8_t version = fileData[offset++];
    if (version != kVersion) {
        throw std::runtime_error("Unsupported version");
    }
    std::uint8_t level = fileData[offset++];
    (void)level;
    std::uint64_t originalSize = 0;
    for (int i = 0; i < 8; ++i) {
        originalSize |= static_cast<std::uint64_t>(fileData[offset++]) << (i * 8);
    }
    std::vector<std::uint8_t> secondary(fileData.begin() + static_cast<long>(offset), fileData.end());
    auto primary = rleDecode(secondary);
    auto raw = gzipDecompress(primary);
    if (raw.size() != static_cast<std::size_t>(originalSize)) {
        throw std::runtime_error("Decompressed size mismatch");
    }
    writeFile(outputPath, raw);
}

void printUsage(const char *prog) {
    std::cerr << "Usage:\n"
              << "  " << prog << " compress [-l level] <input> <output>\n"
              << "  " << prog << " decompress <input> <output>\n";
}

} // namespace

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printUsage(argv[0]);
        return 1;
    }
    std::string mode = argv[1];
    try {
        if (mode == "compress") {
            int argIndex = 2;
            int level = 9;
            if (std::string(argv[argIndex]) == "-l") {
                if (argc < argIndex + 3) {
                    printUsage(argv[0]);
                    return 1;
                }
                level = std::stoi(argv[argIndex + 1]);
                if (level < 0 || level > 9) {
                    throw std::runtime_error("Compression level must be between 0 and 9");
                }
                argIndex += 2;
            }
            if (argc != argIndex + 2) {
                printUsage(argv[0]);
                return 1;
            }
            std::string inputPath = argv[argIndex];
            std::string outputPath = argv[argIndex + 1];
            compressFile(inputPath, outputPath, level);
        } else if (mode == "decompress") {
            if (argc != 4) {
                printUsage(argv[0]);
                return 1;
            }
            std::string inputPath = argv[2];
            std::string outputPath = argv[3];
            decompressFile(inputPath, outputPath);
        } else {
            printUsage(argv[0]);
            return 1;
        }
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
