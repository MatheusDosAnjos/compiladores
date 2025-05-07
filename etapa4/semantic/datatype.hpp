/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <map>
#include <set>
#include <string>

enum class DataType {
    NONE, INT, BYTE, CHAR, REAL, STRING, BOOL
};

bool isCompatible(DataType from, DataType to);

#endif