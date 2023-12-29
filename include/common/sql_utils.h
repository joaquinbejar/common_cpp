//
// Created by Joaquin Bejar Garcia on 27/11/23.
//

#ifndef COMMON_SQL_UTILS_H
#define COMMON_SQL_UTILS_H
#include <string>
#include <map>
#include <regex>

namespace common::sql_utils {
    std::string empty_to_null(const std::string& query) ;

    std::string remove_quotes(const std::string &input);

    enum class InsertType {
        INSERT,
        REPLACE,
        IGNORE
    };

    // map of insert types
    static const std::map<InsertType, std::string> insert_type_map = {
            {InsertType::INSERT,  "INSERT INTO "},
            {InsertType::REPLACE, "REPLACE INTO "},
            {InsertType::IGNORE,  "INSERT IGNORE INTO "}
    };

    // funct to replace in a query the string "INSERT INTO", "REPLACE INTO" or "INSERT IGNORE INTO"
    // with the corresponding string for a given InsertType
    void replace_insert_type(std::string &query, const InsertType &insert_type);

    const std::regex QUERYREGEX(
            R"(^\s*(INSERT(\s+IGNORE)?|REPLACE)\s+INTO\s+`?[a-zA-Z_][a-zA-Z_0-9]*`?\s*\(([^)]+)\)\s*VALUES\s*\(([^)]+)\)\s*;?\s*$)",
            std::regex_constants::icase
    );

    bool is_insert_or_replace_query_correct(const std::string &query);

}
#endif //COMMON_SQL_UTILS_H
