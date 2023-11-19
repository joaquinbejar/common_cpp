//
// Created by Joaquin Bejar Garcia on 20/10/23.
//

#include <common/ip.h>
#include <catch2/catch_test_macros.hpp>

// ---------------------------------------------------------------------------------------------------
TEST_CASE("Test test", "[IP]") {
    REQUIRE(true);
}

// ---------------------------------------------------------------------------------------------------

TEST_CASE("split_ip_octets works correctly", "[split_ip_octets]") {
    using common::ip::split_ip_octets;

    SECTION("Valid IPs") {
        REQUIRE(split_ip_octets("192.168.1.1") == std::vector<int>{192, 168, 1, 1});
        REQUIRE(split_ip_octets("127.0.0.1") == std::vector<int>{127, 0, 0, 1});
        REQUIRE(split_ip_octets("0.0.0.0") == std::vector<int>{0, 0, 0, 0});
    }

    SECTION("Invalid IPs") {
        REQUIRE(split_ip_octets("192.168.300.1").empty());  // Aquí asumo que devolverías un vector vacío para IPs no válidas
        REQUIRE(split_ip_octets("192.abc.1.1").empty());
    }
}

TEST_CASE("is_ip works correctly", "[is_ip]") {
    using common::ip::is_ip;

    SECTION("Valid IPs") {
        REQUIRE(is_ip("192.168.1.1") );
        REQUIRE(is_ip("127.0.0.1") );
        REQUIRE(is_ip("0.0.0.0") );
        REQUIRE_FALSE(is_ip("192.168.1000.1") );
        REQUIRE_FALSE(is_ip("127.a.0.1") );
        REQUIRE_FALSE(is_ip("0.0.0.0.1") );
    }


}

TEST_CASE("random_ip works correctly", "[random_ip]") {
    using common::ip::random_ip;
    using common::ip::is_ip;

    SECTION("Valid IPs") {
        REQUIRE(is_ip(random_ip()));
    }
}

TEST_CASE("extract_ipaddress works correctly", "[extract_ipaddress]") {
    using common::ip::extract_ipaddress;
    using common::ip::is_ip;

    SECTION("Valid IPs") {
        REQUIRE(is_ip(extract_ipaddress("192.168.12.2%2")));
        REQUIRE_FALSE(is_ip(extract_ipaddress("2%192.168.12.2")));
        REQUIRE_FALSE(is_ip(extract_ipaddress("192.168%.12.2")));
    }
}

TEST_CASE("ip_is_multicast works correctly", "[ip_is_multicast]") {
    using common::ip::ip_is_multicast;

    SECTION("Valid IPs") {
        REQUIRE(ip_is_multicast("224.0.1.1"));
        REQUIRE(ip_is_multicast("225.0.1.1"));
        REQUIRE(ip_is_multicast("239.0.1.1"));
        REQUIRE_FALSE(ip_is_multicast("192.168.12.2"));
        REQUIRE_FALSE(ip_is_multicast("223.168.12.2"));
        REQUIRE_FALSE(ip_is_multicast("2.168.12.2"));
    }
}

TEST_CASE("ip_is_loopback works correctly", "[ip_is_loopback]") {
    using common::ip::ip_is_loopback;

    SECTION("Valid IPs") {
        REQUIRE(ip_is_loopback("127.2.1.1"));
        REQUIRE(ip_is_loopback("127.110.1.1"));
        REQUIRE(ip_is_loopback("127.0.0.1"));
        REQUIRE_FALSE(ip_is_loopback("192.168.12.2"));
        REQUIRE_FALSE(ip_is_loopback("223.168.12.2"));
        REQUIRE_FALSE(ip_is_loopback("2.168.12.2"));
    }
}

TEST_CASE("reverse_ip works correctly", "[reverse_ip]") {
    using common::ip::reverse_ip;

    SECTION("Valid IPs") {
        REQUIRE(reverse_ip(std::string("127.2.1.1")) == "1.1.2.127.in-addr.arpa");
        std::string ip = "127.110.1.1";
        REQUIRE(reverse_ip(ip) == "1.1.110.127.in-addr.arpa");
        REQUIRE(reverse_ip(std::string("127.0.0.1")) == "1.0.0.127.in-addr.arpa");
        REQUIRE_FALSE(reverse_ip(std::string("192.168.12.2")) == "1.1.110.127.in-addr.arpa");
        REQUIRE_FALSE(reverse_ip(std::string("223.168.12.2")) == "1.1.110.127.in-addr.arpa");
        REQUIRE_FALSE(reverse_ip(std::string("2.168.12.2")) == "1.1.110.127.in-addr.arpa");
    }
}

TEST_CASE("is_a_valid_port works correctly", "[is_a_valid_port]") {
    using common::ip::is_a_valid_port;

    SECTION("Valid IPs") {
        REQUIRE(is_a_valid_port("443"));
        REQUIRE(is_a_valid_port("65535"));
        REQUIRE_FALSE(is_a_valid_port("65536"));
        REQUIRE_FALSE(is_a_valid_port("223_168"));
        REQUIRE_FALSE(is_a_valid_port("223.168.12.2"));
        REQUIRE_FALSE(is_a_valid_port("-1"));
        REQUIRE_FALSE(is_a_valid_port("0"));
    }
}

TEST_CASE("ip_is_private works correctly", "[ip_is_private]") {
    using common::ip::ip_is_private;

    SECTION("Valid IPs") {
        REQUIRE(ip_is_private("10.2.1.1"));
        REQUIRE(ip_is_private("172.21.1.1"));
        REQUIRE(ip_is_private("192.168.0.1"));
        REQUIRE_FALSE(ip_is_private("192.167.12.2"));
        REQUIRE_FALSE(ip_is_private("172.168.12.2"));
        REQUIRE_FALSE(ip_is_private("2.168.12.2"));
    }
}

TEST_CASE("ip_and_port_from_string_to_pair works correctly", "[ip_and_port_from_string_to_pair]") {
    using common::ip::ip_and_port_from_string_to_pair;

    SECTION("Valid IP and port") {
        auto result = ip_and_port_from_string_to_pair("192.168.1.1:8080");
        REQUIRE(result.first == "192.168.1.1");
        REQUIRE(result.second == "8080");
    }

    SECTION("Invalid IP") {
        auto result = ip_and_port_from_string_to_pair("192.168.300.1:8080");
        REQUIRE(result.first.empty());
        REQUIRE(result.second.empty());
    }

    SECTION("Invalid port") {
        auto result = ip_and_port_from_string_to_pair("192.168.1.1:70000");
        REQUIRE(result.first.empty());
        REQUIRE(result.second.empty());
    }

    SECTION("Invalid format") {
        auto result = ip_and_port_from_string_to_pair("192.168.1.1-8080");
        REQUIRE(result.first.empty());
        REQUIRE(result.second.empty());
    }

    SECTION("Empty string") {
        auto result = ip_and_port_from_string_to_pair("");
        REQUIRE(result.first.empty());
        REQUIRE(result.second.empty());
    }
}

