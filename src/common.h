#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <optional>

namespace database{

/**
 * The struct which contains name of the table and data to some operations with data base:
 * - INSERT;
 * - DELETE;
 * - UPDATE;
 * - serarch with operator WHERE.
 */

 using key = std::string;
using value = std::string;
using op = std::string;


// struct Data{
//     std::string table_name;
//     std::vector<std::pair<key, value>> columns_values;

//     void add(const std::string& column, const std::string& value) {
//         columns_values.emplace_back(column, value);
//     }
// };

struct InsertData {
    std::string table_name;
    std::vector<std::pair<key, value>> columns_values;
};

struct DeleteData {
    std::string table_name;
    std::optional<std::tuple<key, op, value>> where_op;          // for data filtrations. The conditions are combined by the "AND" operator.
};

struct UpdateData {
    std::string table_name;
    std::vector<std::pair<key, value>> set_op;                 // data for change (combined by ",")
    std::optional<std::tuple<key, op, value>> where_op;        // for data filtrations. There is only one condition (by name)
};

struct SelectData {
    std::string table_name;
    std::vector<std::tuple<key, op, value>> where_op;
};

}