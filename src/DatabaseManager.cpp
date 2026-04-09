#include "DatabaseManager.h"


namespace database{
/*-----------------------------------------------------------------------------------------------------*/
/*---------------------------------------------- PUBLIC ----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/

DatabaseManager::DatabaseManager(const std::filesystem::path& db_file_path): db_(db_file_path, SQLite::OPEN_READWRITE) {}

void DatabaseManager::ExecuteInsert(const InsertData& data) {
    std::string columns, placeholders;
    std::vector<std::string> values;
    
    for (const auto& [column, value] : data.columns_values) {
        if (!columns.empty()){
            columns += ", ";
        }
        if (!placeholders.empty()) {
            placeholders += ", ";
        }
        columns += column;
        placeholders += "?";
        values.push_back(value);
    }

    std::string sql = "INSERT INTO " + data.table_name + " (" + columns + ") VALUES (" + placeholders + ")";

    SQLite::Statement query(db_, sql);
    for(size_t index = 0; index < values.size(); ++index) {
        query.bind(index + 1, values[index]);
    }
    query.exec(); // may throw exception
}

void DatabaseManager::ExecuteDelete(const DeleteData& data) {
    std::string sql = "DELETE FROM " + data.table_name;

    if(data.where_op.has_value()) {
        std::ostringstream oss;
        const auto& [column, op, value] = data.where_op.value(); 
        oss << column << " " << op << " " << value;
        
        sql += " WHERE " + oss.str();
    }
    SQLite::Statement query(db_, sql);
    query.exec(); // may throw exception
}

void DatabaseManager::ExecuteUpdate(const UpdateData& data) {
    std::string sql = "UPDATE " + data.table_name;
    std::ostringstream oss;
    if(!data.set_op.empty()) {
        oss.clear();
        for (size_t i = 0; i < data.set_op.size(); ++i) {
            if (i > 0) {
                oss << ", ";
            }
            const auto& [column, new_value] = data.set_op[i];

            oss << column << " = " << new_value;
        }
        sql += " SET " + oss.str();
    }
    if(data.where_op.has_value()) {
        oss.clear();
        const auto& [column, op, value] = data.where_op.value();
        oss << column << " " << op << " " << value;
        sql += " WHERE " + oss.str();
    }
    SQLite::Statement query(db_, sql);
    query.exec(); // may throw exception
} 

void DatabaseManager::ExecuteSelect(const SelectData& data) {
    std::string sql = "SELECT * " + data.table_name;
    if(!data.where_op.empty()) {
        std::ostringstream oss;
        for(size_t i = 0; i < data.where_op.size(); ++i) {
            if(i > 0) {
                oss << " AND ";
            }
            const auto& [column, op, value] = data.where_op[i];
            oss << column << " " << op << " " << value;
        }
        sql += " WHERE " + oss.str();
    }
    SQLite::Statement query(db_, sql);
    query.exec(); // may throw exception
}

/*-----------------------------------------------------------------------------------------------------*/
/*------------------------------------------- PUBLIC END ----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------------------*/
/*---------------------------------------------- PRIVATE ----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------------------*/
/*------------------------------------------ PRIVATE END ----------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------*/
}