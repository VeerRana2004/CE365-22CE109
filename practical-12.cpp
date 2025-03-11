#include <iostream>
#include <string>
#include <regex>
#include <map>
using namespace std;
// Function to evaluate constant expressions
string evaluateExpression(const std::string& expr) {
    // Regular expression to match constant expressions
    regex pattern("(\\d+\\.\\d+|\\d+)\\s*([+*/-])\\s*(\\d+\\.\\d+|\\d+)");
    string result = expr;

    while (regex_search(result, pattern)) {
        smatch match;
        if (regex_search(result, match, pattern)) {
            double a = stod(match[1].str());
            double b = stod(match[3].str());
            char op = match[2].str()[0];

            double res;
            switch (op) {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                if (b != 0)
                    res = a / b;
                else
                    throw runtime_error("Division by zero");
                break;
            default:
                throw runtime_error("Unsupported operator");
            }

            result = regex_replace(result, pattern, to_string(res));
        }
    }

    return result;
}

// Function to apply constant folding
string constantFolding(const std::string& input) {
    // Regular expression to match expressions that can be folded
    regex pattern("\\d+\\.\\d+|\\d+");
    auto words_begin = sregex_iterator(input.begin(), input.end(), pattern);
    auto words_end = sregex_iterator();

    string result = input;

    // Check if the expression contains only constants
    bool allConstants = true;
    for (char c : input) {
        if (c == 'x' || c == 'r' || c == 'a' || c == 'c' || c == 'g') {
            allConstants = false;
            break;
        }
    }

    if (allConstants) {
        return evaluateExpression(input);
    } else {
        // Evaluate constant parts of the expression
        regex opPattern("(\\d+\\.\\d+|\\d+)\\s*([+*/-])\\s*(\\d+\\.\\d+|\\d+)");
        while (regex_search(result, opPattern)) {
            smatch match;
            if (regex_search(result, match, opPattern)) {
                double a = stod(match[1].str());
                double b = stod(match[3].str());
                char op = match[2].str()[0];

                double res;
                switch (op) {
                case '+':
                    res = a + b;
                    break;
                case '-':
                    res = a - b;
                    break;
                case '*':
                    res = a * b;
                    break;
                case '/':
                    if (b != 0)
                        res = a / b;
                    else
                        throw runtime_error("Division by zero");
                    break;
                default:
                    throw runtime_error("Unsupported operator");
                }

                result = regex_replace(result, opPattern, to_string(res));
            }
        }

        return result;
    }
}

int main() {
    string input;
    cout << "Enter an arithmetic expression: ";
    getline(cin, input);

    string output = constantFolding(input);
    cout << "Optimized expression: " << output << endl;

    return 0;
}
