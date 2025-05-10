/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <map>
#include <vector>
#include "error_reporter.hpp"

using namespace std;

ErrorReporter errorReporter;

static const map<ErrorType, string> errorTemplates = {
    {ErrorType::REDECLARED_VARIABLE, "Variable '{0}' redeclared."},
    {ErrorType::INCOMPATIBLE_INIT, "Type '{1}' is not compatible with '{0}' on '{2}' initialization."},
    {ErrorType::UNDECLARED_VARIABLE, "Variable '{0}' undeclared."},
    {ErrorType::INVALID_ARRAY_SIZE_1, "'{0}' array declaration size must be greater than 0."},
    {ErrorType::INVALID_ARRAY_SIZE_2, "Number of elements must be equal to the declared size on '{0}' array initialization."},
    {ErrorType::INVALID_SCALAR_USAGE, "'{0}' cannot be used as a scalar variable."},
    {ErrorType::INVALID_ARRAY_USAGE, "'{0}' cannot be used as an array."},
    {ErrorType::INVALID_FUNCTION_USAGE, "'{0}' cannot be used as a function."},
    {ErrorType::INVALID_FUNCTION_CALL_1, "Function '{0}' called with wrong number of arguments."},
    {ErrorType::INVALID_FUNCTION_CALL_2, "Type '{1}' is not compatible with '{0}' on function '{2}' call."},
    {ErrorType::INVALID_ARITHMETIC_EXPR, "Invalid arithmetic expression: '{0}'."},
    {ErrorType::INVALID_RELATIONAL_EXPR, "Invalid relational expression: '{0}'."},
    {ErrorType::INVALID_LOGICAL_EXPR, "Invalid logical expression: '{0}'."},
    {ErrorType::INCOMPATIBLE_ASSIGN, "Type '{1}' is not compatible with '{0}' on '{2}' assignment."},
};

inline string formatError(ErrorType type, const vector<string>& args) {
    string msg = errorTemplates.at(type);

    for (size_t i = 0; i < args.size(); ++i) {
        string key = "{" + to_string(i) + "}";
        size_t pos = msg.find(key);

        while (pos != string::npos) {
            msg.replace(pos, key.length(), args[i]);
            pos = msg.find(key);
        }
    }

    return msg;
}

void ErrorReporter::report(ErrorType type, const vector<string>& args) {
    string msg = formatError(type, args);
    count++;

    fprintf(stderr, "\033[0;31mERROR:\033[0m %s\n", msg.c_str());
}

int ErrorReporter::getCount() const {
    return count;
}

bool ErrorReporter::hasErrors() const {
    return count > 0;
}
