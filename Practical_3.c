#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_FILE_SIZE 10000

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch) {
    return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
            ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' || ch == '{' || ch == '}');
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '>' || ch == '<' ||
            ch == '=');
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str) {
    if (!isalpha(str[0]) && str[0] != '_') // Must start with a letter or underscore
        return false;
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') // Only alphanumeric or underscore allowed
            return false;
    }
    return true;
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str) {
    const char* keywords[] = {
        "if", "else", "while", "do", "break", "continue",
        "int", "double", "float", "return", "char", "case",
        "sizeof", "long", "short", "typedef", "switch",
        "unsigned", "void", "static", "struct", "goto"
    };
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (!strcmp(str, keywords[i]))
            return true;
    }
    return false;
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char* str) {
    if (str == NULL || *str == '\0')
        return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

// Extracts the SUBSTRING.
char* subString(char* str, int left, int right) {
    int i;
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return subStr;
}

// Parsing the input STRING.
void parse(char* str) {
    int left = 0, right = 0, len = strlen(str);
    int tokenCount = 0;
    int symbolTableIndex = 0;
    char* symbolTable[100]; // Symbol table for identifiers
    char lexicalErrors[100][50]; // Array for lexical errors
    int lexicalErrorCount = 0;

    printf("TOKENS\n");
    while (right <= len && left <= right) {
        if (!isDelimiter(str[right]))
            right++;

        if (isDelimiter(str[right]) && left == right) {
            if (isOperator(str[right])) {
                printf("Operator: %c\n", str[right]);
                tokenCount++;
            } else if (str[right] == '(' || str[right] == ')' ||
                       str[right] == '{' || str[right] == '}' ||
                       str[right] == ',' || str[right] == ';') {
                printf("Punctuation: %c\n", str[right]);
                tokenCount++;
            }
            right++;
            left = right;
        } else if ((isDelimiter(str[right]) && left != right) ||
                   (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);

            if (isKeyword(subStr)) {
                printf("Keyword: %s\n", subStr);
                tokenCount++;
            } else if (isInteger(subStr)) {
                printf("Constant: %s\n", subStr);
                tokenCount++;
            } else if (validIdentifier(subStr)) {
                printf("Identifier: %s\n", subStr);
                tokenCount++;
                // Add identifier to symbol table if not already present
                int found = 0;
                for (int i = 0; i < symbolTableIndex; i++) {
                    if (strcmp(symbolTable[i], subStr) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    symbolTable[symbolTableIndex] = strdup(subStr);
                    symbolTableIndex++;
                }
            } else {
                printf("Lexical Error: %s is an invalid lexeme\n", subStr);
                strcpy(lexicalErrors[lexicalErrorCount++], subStr);
            }
            free(subStr);
            left = right;
        }
    }

    // Display token count
    printf("\nTOTAL TOKENS: %d\n", tokenCount);

    // Display lexical errors
    printf("\nLEXICAL ERRORS\n");
    for (int i = 0; i < lexicalErrorCount; i++) {
        printf("%s\n", lexicalErrors[i]);
    }

    // Display symbol table
    printf("\nSYMBOL TABLE ENTRIES\n");
    for (int i = 0; i < symbolTableIndex; i++) {
        printf("%d) %s\n", i + 1, symbolTable[i]);
        free(symbolTable[i]); // Free allocated memory
    }
}
char* fileToString(const char* filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    // Allocate memory for the file content
    char *fileContent = (char*)malloc(MAX_FILE_SIZE * sizeof(char));

    if (fileContent == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    int i = 0;
    char ch;

    // Read each character from the file until EOF or MAX_FILE_SIZE limit is reached
    while ((ch = fgetc(file)) != EOF && i < MAX_FILE_SIZE - 1) {
        fileContent[i++] = ch;
    }

    fileContent[i] = '\0';  // Null-terminate the string

    fclose(file);
    return fileContent;
}


// DRIVER FUNCTION
int main() {
    // Test input string
   char filename[150];
    FILE *sourceFile;

    printf("Enter the C source code filename: ");
    scanf("%s", filename);

    sourceFile = fopen(filename, "r");


    char *content = fileToString(filename);
    parse(content);

    if (content != NULL) {
        printf("File content:\n%s\n", content);
        free(content);  // Free the allocated memory
    }

    fclose(sourceFile);

    return 0;
}
