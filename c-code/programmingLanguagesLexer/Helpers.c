#include "Helpers.h"

// implementation of printTokens function
#include <string.h>
void printTokens(int n) {
    for (int i = 0; i < n; i++) {
        if (tokenArray[i][0] == STRING) {
            printf("String: \"%s\"\n", &tokenArray[i][1]);
        } else if (tokenArray[i][0] == CHARACTER_LITERAL) {
            printf("Character Literal: '%s'\n", &tokenArray[i][1]);
        } else if (tokenArray[i][0] == OPERATOR) {
            printf("Operator: %s\n", &tokenArray[i][1]);
        } else if (tokenArray[i][0] == KEY_WORD) {
            printf("Keyword: %s\n", &tokenArray[i][1]);
        } else if (tokenArray[i][0] == KW_IF || tokenArray[i][0] == KW_WHILE) {
            printf("Keyword: %s\n", &tokenArray[i][1]);
        } else {
            printf("Token: %s\n", &tokenArray[i][1]);
        }
    }
}

// OperatorHandler: recognizes single- and double-char operators.
// Flushes any in-progress token, stores the operator in tokenArray, returns 1.
// Returns 0 if c does not start a known operator.
int OperatorHandler(int c) {
    char op[3] = {(char)c, '\0', '\0'};
    int next;

    switch (c) {
        case '<':
            next = fgetc(filePtr);
            if (next == '<' || next == '=' || next == '>') { op[1] = (char)next; }
            else if (next != EOF) { ungetc(next, filePtr); }
            break;
        case '>':
            next = fgetc(filePtr);
            if (next == '>' || next == '=') { op[1] = (char)next; }
            else if (next != EOF) { ungetc(next, filePtr); }
            break;
        case ':':
            next = fgetc(filePtr);
            if (next == '=') { op[1] = (char)next; }
            else if (next != EOF) { ungetc(next, filePtr); }
            break;
        case '=':
            next = fgetc(filePtr);
            if (next == '=' || next == '>') { op[1] = (char)next; }
            else if (next != EOF) { ungetc(next, filePtr); }
            break;
        case '.':
            next = fgetc(filePtr);
            if (next == '.') { op[1] = (char)next; }
            else if (next != EOF) { ungetc(next, filePtr); }
            break;
        case '*':
            next = fgetc(filePtr);
            if (next == '*') { op[1] = (char)next; }
            else if (next != EOF) { ungetc(next, filePtr); }
            break;
        case '{':
            next = fgetc(filePtr);
            if (next == ':') { op[1] = (char)next; }
            else if (next != EOF) { ungetc(next, filePtr); }
            break;
        case '}':
            next = fgetc(filePtr);
            if (next == ':') { op[1] = (char)next; }
            else if (next != EOF) { ungetc(next, filePtr); }
            break;
        case '!':
            next = fgetc(filePtr);
            if (next == '=') { op[1] = (char)next; }
            else {
                if (next != EOF) { ungetc(next, filePtr); }
                return 0; // '!' alone is not a recognized operator
            }
            break;
        case '(': case ')': case '+': case '-': case '/':
        case '|': case '&': case ';': case ',': case '$':
        case '@': case '[': case ']':
            break;
        default:
            return 0;
    }

    // flush any in-progress unsorted token before storing the operator
    WhitespaceHandler();

    tokenArray[tokensIndex][0] = OPERATOR;
    int i = 1;
    for (int j = 0; op[j] != '\0'; j++, i++) {
        tokenArray[tokensIndex][i] = op[j];
    }
    tokenArray[tokensIndex][i] = '\0';
    tokensIndex++;

    return 1;
}

int CommentHandler(void) {
    int nextChar = fgetc(filePtr);
    if (nextChar == '*') {
        // it is a comment, so we will skip until sequence */ is found
        int prevChar = 0;
        int commentChar;
        while (((commentChar = fgetc(filePtr)) != EOF) && !(prevChar == '*' && commentChar == '/')) {
            prevChar = commentChar;
        }
        return 1;
    } else {
        if (nextChar != EOF) {
            ungetc(nextChar, filePtr);
        }
        return 0;
    }
}

void CharLiteralHandler(void) {
    tokenArray[tokensIndex][0] = CHARACTER_LITERAL;
    tokenArray[tokensIndex][1] = '\0'; // default if empty
    int charLiteralIndex = 1;
    int c;
    // the while condition for multi-character character literals,
    while (((c = fgetc(filePtr)) != EOF) && c != '\'') {
        tokenArray[tokensIndex][charLiteralIndex] = c;
        charLiteralIndex++;
        if (charLiteralIndex >= 255) {
            // limit, add null
            tokenArray[tokensIndex][255] = '\0';
            break; // prevent overflow, though this would be an invalid character literal
        }
    }
    tokensIndex++;
}

void WhitespaceHandler(void) {
    if (currentTokenIndex > 0) {
        // if a current token exists; add null terminator and move on
        tokenArray[tokensIndex][currentTokenIndex] = '\0';
        tokensIndex++;
        currentTokenIndex = 0;
    }
}

void AddCharToToken(int c) {
    // if at the start of a token, set the token type to unsorted
    if (currentTokenIndex == 0) {
        tokenArray[tokensIndex][0] = UN_SORTED;
        currentTokenIndex++;
    }

    // add char to current token
    if (currentTokenIndex < 255) {
        tokenArray[tokensIndex][currentTokenIndex] = c;
        currentTokenIndex++;
    }
}

void FinalizeLastToken(void) {
    // null terminator for last token since while loop wont reach it
    if (currentTokenIndex > 0 && tokensIndex < MAX_TOKENS) {
        tokenArray[tokensIndex][currentTokenIndex] = '\0';
        tokensIndex++;
    }
}

void StringCapHandler(void) {
    if (isInString) {
        // end of string
        tokenArray[tokensIndex][currentStringIndex] = '\0';
        tokensIndex++;
        currentStringIndex = 0;
        isInString = 0;
    } else {
        // start of string
        isInString = 1;
        tokenArray[tokensIndex][0] = STRING;
        currentStringIndex = 1;
    }
}

void InStringHandler(int c) {
    if (currentStringIndex < 255) {
        tokenArray[tokensIndex][currentStringIndex] = c;
        currentStringIndex++;
    }
}

void PostProcessTokens(int n) {
    for (int i = 0; i < n; i++) {
    if (tokenArray[i][0] == STRING) {
      continue;
    } else if (tokenArray[i][0] == CHARACTER_LITERAL) {
        continue;
    } else if (tokenArray[i][0] == OPERATOR) {
        continue;
    } else {
      // is token
    }
  }
}

void ClassifyKeywords() {
    const char *keywords[] = {
        "accessor", "and", "array", "bool", "case", "character", "constant",
        "else", "elsif", "end", "exit", "float", "func", "if", "ifc", "in",
        "integer", "is", "mutator", "natural", "null", "of", "or", "others",
        "out", "pkg", "positive", "proc", "ptr", "range", "subtype", "then",
        "type", "when", "while"
    };
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < tokensIndex; i++) {
        if (tokenArray[i][0] == UN_SORTED) {
            char* word = &tokenArray[i][1];
            for (int k = 0; k < num_keywords; k++) {
                if (strcmp(word, keywords[k]) == 0) {
                    if (strcmp(word, "if") == 0) {
                        tokenArray[i][0] = KW_IF;
                    }
                    else if (strcmp(word, "while") == 0) {
                        tokenArray[i][0] = KW_WHILE;
                    }
                    else {
                        tokenArray[i][0] = KEY_WORD;
                    }
                    break;
                }
            }
        }
    }
}