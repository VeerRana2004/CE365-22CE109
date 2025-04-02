#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

// Function to check syntax and extract string with detailed error handling
bool isValidSyntax(const string& input, string& extractedString, string& errorMessage) {
    // Regular expression pattern to match 'reverse("string")'
    regex pattern(R"(reverse\(\"(.*?)\"\))");
    smatch match;

    // Check if input starts with "reverse"
    if (input.find("reverse") != 0) {
        errorMessage = "❌ Error: Missing 'reverse' keyword at the beginning.";
        return false;
    }

    // Check if input has an opening parenthesis '('
    if (input.find("(") == string::npos) {
        errorMessage = "❌ Error: Missing opening parenthesis '(' after 'reverse'.";
        return false;
    }

    // Check if input has a closing parenthesis ')'
    if (input.find(")") == string::npos) {
        errorMessage = "❌ Error: Missing closing parenthesis ')' at the end.";
        return false;
    }

    // Check if input matches the correct format
    if (regex_match(input, match, pattern)) {
        extractedString = match[1].str();  // Extract string inside quotes
        return true;  // Syntax is valid
    } else {
        errorMessage = "❌ Error: Incorrect string format. Ensure it's enclosed in double quotes (\"\").";
        return false;
    }
}

// Function to process the reverse operation if syntax is valid
void processReverse(const string& input) {
    string extractedString, errorMessage;

    // Step 1: Check Syntax with detailed error handling
    if (isValidSyntax(input, extractedString, errorMessage)) {
        cout << "✅ Syntax Valid!" << endl;
        cout << "Extracted String: " << extractedString << endl;

        // Step 2: Generate Intermediate Code
        cout << "Intermediate Code:" << endl;
        cout << "t1 = \"" << extractedString << "\"" << endl;
        cout << "t2 = reverse(t1)" << endl;

        // Step 3: Execute Reverse Operation
        reverse(extractedString.begin(), extractedString.end());
        cout << "Final Output: " << extractedString << endl;
    } else {
        cout << errorMessage << endl;  // Display specific error message
    }
}

int main() {
    string input;

    // Take input from user
    cout << "Enter your command: ";
    getline(cin, input);

    // Process input
    processReverse(input);

    return 0;
}
