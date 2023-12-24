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
}
