//
// Created by Joaquin Bejar Garcia on 27/11/23.
//

#ifndef COMMON_SQL_UTILS_H
#define COMMON_SQL_UTILS_H
#include <string>

namespace common::sql_utils {
    std::string empty_to_null(const std::string& query) ;

    std::string remove_quotes(const std::string &input);
}
#endif //COMMON_SQL_UTILS_H
