#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "common.h"

namespace database{

class DatabaseManager {
public:
    DatabaseManager(const std::filesystem::path& db_file_path);

    // DatabaseManager is non-copyable
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // DatabaseManager is moveable
    DatabaseManager(DatabaseManager&& db_m) = default;
    DatabaseManager& operator=(DatabaseManager&& db_m) = default;

    // Methods
    /**
     * Adding the data to the table.
     * May throw exception.
     * Argument: 
     * @data - contains name of the table and the data to add to the table.
     */
    void ExecuteInsert(const InsertData& data);
    /**
     * Deleting some data from the table.
     * May throw exceptions.
     * Argument:
     * @data - contains name of the table and the data to add to the table.
     */
    void ExecuteDelete(const DeleteData& data);
    /**
     * Updating the data in the table.
     * May throw exception.
     * Argument:
     * @data - contains name of the table and the data to update.
     */
    void ExecuteUpdate(const UpdateData& data);
    /**
     * Selecting the output parameters.
     * May throw exception.
     * Argument:
     * @data - contains name of the table and the data to select.
     */
    void ExecuteSelect(const SelectData& data);

private:
    SQLite::Database db_;
};

}