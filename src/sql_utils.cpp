//
// Created by Joaquin Bejar Garcia on 27/11/23.
//

#include <common/sql_utils.h>


namespace common::sql_utils {
    std::string empty_to_null(const std::string &query) {
        std::string modifiedQuery = query;
        std::string toReplace = "''";
        std::string replaceWith = "NULL";


        size_t pos = 0;
        while ((pos = modifiedQuery.find(toReplace, pos)) != std::string::npos) {
            modifiedQuery.replace(pos, toReplace.length(), replaceWith);
            pos += replaceWith.length();
        }

        return modifiedQuery;
    }

    std::string remove_quotes(const std::string &input) {
        std::string result;
        for (char c: input) {
            if (c != '\'' && c != '"' && c != '`') {
                result += c;
            }
        }
        return result;
    }

    void replace_insert_type(std::string &query, const InsertType &insert_type) {
        // Use regular expressions for case-insensitive search and to handle extra spaces
        for (const auto &it: insert_type_map) {
            // Construct a regex pattern to match optional spaces at the beginning and within the string
            std::string pattern = "\\s*";  // Optionally match leading spaces
            for (char c: it.second) {
                if (c == ' ') {
                    pattern += "\\s*";  // Replace spaces with regex for optional spaces
                } else {
                    pattern += c;
                }
            }

            std::regex regex_pattern(pattern, std::regex_constants::icase);

            // Search and replace using regex
            if (std::regex_search(query, regex_pattern)) {
                const std::string &replacement = insert_type_map.at(insert_type);
                query = std::regex_replace(query, regex_pattern, replacement, std::regex_constants::format_first_only);
                break;
            }
        }
    }

    bool is_insert_or_replace_query_correct(const std::string &query) {
        return std::regex_match(query, QUERYREGEX);
    }

}
