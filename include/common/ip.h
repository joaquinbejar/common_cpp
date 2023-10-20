//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#ifndef COMMON_IP_H
#define COMMON_IP_H

#include "nlohmann/json.hpp"
#include <random>
#include <regex>
#include <sstream>
#include <iostream>
//#include <boost/asio/ip/network_v4.hpp>

using json = nlohmann::json;

namespace common::ip {

    const std::regex IPV4_PATTERN(
            "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
    );

    std::vector<int> split_ip_octets(const std::string& ip_address);

    std::string random_ip();

    std::string extract_ipaddress(const std::string &str);

    bool is_ip(const std::string &ip_address);

    bool is_a_valid_port(const int &port);

    bool is_a_valid_port(const std::string &port);

    bool ip_is_multicast(const std::string &sip);

    bool ip_is_loopback(const std::string &sip);

    template<typename StringType>
    std::string reverse_ip(StringType&& ip_address) {
        // Use std::forward to keep the original type  (l-value or r-value)
        auto ip_forward = std::forward<StringType>(ip_address);
        if (is_ip(ip_forward)) {
            std::vector<int> octets = split_ip_octets(ip_forward);
            return std::to_string(octets[3]) + '.' + std::to_string(octets[2]) + '.' +
                   std::to_string(octets[1]) + '.' + std::to_string(octets[0]) + ".in-addr.arpa";
        } else {
            return "";
        }
    }

    bool ip_is_private(const std::string &ip_address);

    [[maybe_unused]] std::string ip_and_port_from_string(const std::string &input);

    std::pair<std::string, std::string> ip_and_port_from_string_to_pair(const std::string &input);

}

#endif //COMMON_IP_H