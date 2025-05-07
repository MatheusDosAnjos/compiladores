/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef ERROR_REPORTER_HPP
#define ERROR_REPORTER_HPP

#include <string>

struct ErrorReporter {
    int count = 0;

    void report(const std::string& msg);
    int getCount() const;
    bool hasErrors() const;
};

extern ErrorReporter errorReporter;

#endif