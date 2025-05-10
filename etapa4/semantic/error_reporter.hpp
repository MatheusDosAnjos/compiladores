/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef ERROR_REPORTER_HPP
#define ERROR_REPORTER_HPP

#include <string>

enum class ErrorType {
    REDECLARED_VARIABLE,
    INCOMPATIBLE_INIT,
    UNDECLARED_VARIABLE,
    INVALID_ARRAY_SIZE_1,
    INVALID_ARRAY_SIZE_2,
    INVALID_SCALAR_USAGE,
    INVALID_ARRAY_USAGE,
    INVALID_FUNCTION_USAGE,
    INVALID_FUNCTION_CALL_1,
    INVALID_FUNCTION_CALL_2,
    INVALID_ARITHMETIC_EXPR,
    INVALID_RELATIONAL_EXPR,
    INVALID_LOGICAL_EXPR,
    INCOMPATIBLE_ASSIGN,
    INVALID_CONDITIONAL_EXPR,
    INVALID_RETURN_TYPE,
};

struct ErrorReporter {
    int count = 0;

    void report(ErrorType type, const std::vector<std::string>& args);
    int getCount() const;
    bool hasErrors() const;
};

extern ErrorReporter errorReporter;

#endif