/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#ifndef DATATYPE_HPP
#define DATATYPE_HPP

enum class DataType {
    NONE, INT, BYTE, CHAR, REAL, STRING, BOOL
};

bool isCompatible(DataType from, DataType to);
bool isArithmeticOp(DataType left, DataType right);

std::string getDataTypeLabel(DataType type);

#endif