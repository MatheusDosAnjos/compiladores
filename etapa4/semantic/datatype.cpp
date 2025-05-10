/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <algorithm>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include "datatype.hpp"

using namespace std;

static const unordered_map<DataType, const char*> dataTypeLabel = {
    {DataType::NONE, "none"},
    {DataType::INT, "int"},
    {DataType::BYTE, "byte"},
    {DataType::CHAR, "char"},
    {DataType::REAL, "real"},
    {DataType::STRING, "string"},
    {DataType::BOOL, "bool"}
};

const set<pair<DataType, DataType>> compatibleDataTypes = {
    {DataType::INT,  DataType::INT},
    {DataType::INT,  DataType::CHAR},
    {DataType::REAL, DataType::REAL},
    {DataType::BYTE, DataType::BYTE},
    {DataType::BYTE, DataType::INT},
    {DataType::BYTE, DataType::CHAR},
};

const vector<DataType> arithmeticDatatypes = {
    DataType::INT,
    DataType::BYTE,
    DataType::CHAR,
    DataType::REAL
};

string getDataTypeLabel(DataType type) {
    return dataTypeLabel.at(type);
}

bool isCompatible(DataType from, DataType to) {
    return compatibleDataTypes.count({from, to}) > 0;
}

bool isArithmeticOp(DataType left, DataType right) {
    bool isLeftValid  = find(arithmeticDatatypes.begin(), arithmeticDatatypes.end(), left)  != arithmeticDatatypes.end();
    bool isRightValid = find(arithmeticDatatypes.begin(), arithmeticDatatypes.end(), right) != arithmeticDatatypes.end();

    if (!isLeftValid || !isRightValid) return false;

    return isCompatible(left, right);
}
