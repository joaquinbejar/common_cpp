//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#include "common/ip.h"

namespace common::ip {

    std::vector<int> split_ip_octets(const std::string& ip_address) {
        if (!is_ip(ip_address)) {
            return {};
        }
        std::vector<int> octets;
        std::stringstream ss(ip_address);
        std::string octet;

        while (std::getline(ss, octet, '.')) {
            octets.push_back(std::stoi(octet));
        }

        return octets;
    }

    std::string random_ip() {
        std::string ip;
        std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<int> distribution(1, 254);
        auto q = [&distribution, &generator] { return distribution(generator); };
        return std::to_string(q()) + "." + std::to_string(q()) + "." + std::to_string(q()) + "." + std::to_string(q());
    }

    std::string extract_ipaddress(const std::string &str) {
        std::size_t position = str.find('%');
        if (position != std::string::npos) {
            return str.substr(0, position);
        } else {
            return str;
        }
    }


    bool is_ip(const std::string &ip_address) {
        if (std::regex_match(ip_address, IPV4_PATTERN)) {
            return true;
        }
        return false;
    }

    bool is_a_valid_port(const int &port) {
        return port > 0 && port <= 65535;
    }

    bool is_a_valid_port(const std::string &port) {
        try {
            std::size_t lastChar;
            int p = std::stoi(port, &lastChar);
            if (lastChar == port.size()) {
                return is_a_valid_port(p);
            }
            return false;
        } catch (std::exception &e) {
            return false;
        }
    }


    bool ip_is_multicast(const std::string &ip_address) {
        try {
            if (is_ip(ip_address)) {
                int first_octet = std::stoi(ip_address.substr(0, ip_address.find('.')));
                return (first_octet >= 224 && first_octet <= 239);
            }
        } catch (std::exception &e) {
            return false;
        }

        return false;
    }

    bool ip_is_loopback(const std::string &ip_address) {
        if (is_ip(ip_address)) {
            int first_octet = std::stoi(ip_address.substr(0, ip_address.find('.')));
            return (first_octet == 127);
        }

        return false;
    }



    bool ip_is_private(const std::string &ip_address) {

        try {
            if (is_ip(ip_address)) {
                std::vector<int> octets = split_ip_octets(ip_address);

                if (octets[0] == 10) {
                    return true;
                }

                if (octets[0] == 172 && (octets[1] >= 16 && octets[1] <= 31)) {
                    return true;
                }

                if (octets[0] == 192 && octets[1] == 168) {
                    return true;
                }
            }

            return false;

        } catch (std::exception &e) {
            return false;
        }
    }

    std::pair<std::string, std::string> ip_and_port_from_string_to_pair(const std::string &input) {
        try {
            std::regex ip_port_regex(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}):(\d+))");
            std::smatch match;
            if (std::regex_search(input, match, ip_port_regex)) {
                std::map<std::string, std::string> ip_and_port;
                std::istringstream ss(match[0]);
                std::string ip, port;
                std::getline(ss, ip, ':');
                std::getline(ss, port);
                if (is_ip(ip) && is_a_valid_port(std::stoi(port))) {
                    std::pair<std::string, std::string> ip_pair(ip, port);
                    return ip_pair;
                }
            }
        } catch (std::exception &e) {
            std::cerr << "Error on COMMON::IP_AND_PORT_FROM_STRING_TO_PAIR: " << e.what() << std::endl;
        }
        return {"", ""};
    }

}