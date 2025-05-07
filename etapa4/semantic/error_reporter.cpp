/*
01/05/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include "error_reporter.hpp"

using namespace std;

ErrorReporter errorReporter;

void ErrorReporter::report(const std::string& msg) {
    fprintf(stderr, "\033[0;31mERROR:\033[0m %s\n", msg.c_str());
    count++;
}

int ErrorReporter::getCount() const {
    return count;
}

bool ErrorReporter::hasErrors() const {
    return count > 0;
}
