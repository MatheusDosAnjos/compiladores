/*
25/03/2025
UFRGS - INF01147 Compiladores - 2025/1
Matheus Adam dos Anjos
*/

#include <algorithm>
#include <string>
#include <map>

#include "datatype.hpp"

using namespace std;

const set<pair<DataType, DataType>> compatibleDataTypes = {
    {DataType::INT,  DataType::INT},
    {DataType::INT,  DataType::CHAR},
    {DataType::REAL, DataType::REAL},
    {DataType::BYTE, DataType::INT},
    {DataType::BYTE, DataType::CHAR},
};


bool isCompatible(DataType from, DataType to) {
    return compatibleDataTypes.count({from, to}) > 0;
}