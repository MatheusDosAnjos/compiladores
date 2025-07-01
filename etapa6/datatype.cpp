/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <map>
#include <set>
#include <string>
#include <vector>
#include "datatype.hpp"

using namespace std;

static const map<DataType, const char*> dataTypeLabel = {
    {DataType::NONE, "none"},
    {DataType::INT, "int"},
    {DataType::BYTE, "byte"},
    {DataType::CHAR, "char"},
    {DataType::REAL, "real"},
    {DataType::STRING, "string"},
    {DataType::BOOL, "bool"}
};

const set<pair<DataType, DataType>> compatibleDataTypes = {
    {DataType::INT, DataType::BYTE},
    {DataType::INT,  DataType::INT},
    {DataType::INT,  DataType::CHAR},
    {DataType::REAL, DataType::REAL},
    {DataType::BYTE, DataType::BYTE},
    {DataType::BYTE, DataType::INT},
    {DataType::BYTE, DataType::CHAR},
};

bool isArithmeticDataType(DataType dataType) {
    return dataType == DataType::INT || 
           dataType == DataType::BYTE ||
           dataType == DataType::CHAR ||
           dataType == DataType::REAL;
}

string getDataTypeLabel(DataType type) {
    return dataTypeLabel.at(type);
}

bool isCompatible(DataType from, DataType to) {
    return compatibleDataTypes.count({from, to}) > 0;
}

bool isArithmeticOp(DataType left, DataType right) {
    bool isLeftValid  = isArithmeticDataType(left);
    bool isRightValid = isArithmeticDataType(right);

    if (!isLeftValid || !isRightValid) return false;

    return isCompatible(left, right);
}
