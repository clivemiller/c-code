#!/bin/bash

# LaTeX to PDF Converter
# Usage: ./processor.bash <input.tex>

# Check if a file argument was provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <latex_file.tex>"
    echo "Example: $0 document.tex"
    exit 1
fi

# Get the input file
INPUT_FILE="$1"

# Check if the file exists
if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: File '$INPUT_FILE' not found!"
    exit 1
fi

# Check if the file has .tex extension
if [[ ! "$INPUT_FILE" =~ \.tex$ ]]; then
    echo "Error: File must have .tex extension"
    exit 1
fi

# Check if pdflatex is installed
if ! command -v pdflatex &> /dev/null; then
    echo "Error: pdflatex is not installed!"
    echo "Please install it using: sudo apt-get install texlive-latex-base"
    exit 1
fi

# Get the base filename without extension and directory
BASENAME="${INPUT_FILE%.tex}"
DIRNAME="$(dirname "$INPUT_FILE")"
FILENAME="$(basename "$INPUT_FILE" .tex)"

# If the input file has a directory path, we need to handle output files differently
# pdflatex creates output in the current directory by default
if [ "$DIRNAME" != "." ]; then
    OUTPUT_DIR="$DIRNAME"
else
    OUTPUT_DIR="."
fi

echo "Converting '$INPUT_FILE' to PDF..."
echo "=========================================="

# Run pdflatex (run twice to resolve references)
pdflatex -interaction=nonstopmode -output-directory="$OUTPUT_DIR" "$INPUT_FILE"

# Check if first compilation succeeded
if [ $? -eq 0 ]; then
    echo ""
    echo "Running second pass to resolve references..."
    pdflatex -interaction=nonstopmode -output-directory="$OUTPUT_DIR" "$INPUT_FILE" > /dev/null
    
    PDF_FILE="${OUTPUT_DIR}/${FILENAME}.pdf"
    if [ -f "$PDF_FILE" ]; then
        echo ""
        echo "=========================================="
        echo "Success! PDF created: $PDF_FILE"
        
        # Clean up auxiliary files
        echo "Cleaning up auxiliary files..."
        rm -f "${OUTPUT_DIR}/${FILENAME}.aux" "${OUTPUT_DIR}/${FILENAME}.log" "${OUTPUT_DIR}/${FILENAME}.out" "${OUTPUT_DIR}/${FILENAME}.toc"
        
        echo "Done!"
    else
        echo "Error: PDF file was not created"
        exit 1
    fi
else
    echo ""
    echo "=========================================="
    echo "Error: Compilation failed!"
    echo "Check ${OUTPUT_DIR}/${FILENAME}.log for details"
    exit 1
fi
