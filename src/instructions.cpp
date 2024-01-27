//
// Created by Joaquin Bejar Garcia on 27/1/24.
//
#include <common/instructions.h>

namespace common::instructions {

    type_t get_type_name(Type type) {
        return TypeNames.at(type);
    }

    Type get_type_from_string(const type_t &type){
        return find_key_from_value(TypeNames, type, Type::NONE);
    }

    selector_t get_selector_name(Selector selector) {
        return SelectorNames.at(selector);
    }

    Selector get_selector_from_string(const selector_t &selector){
        return find_key_from_value(SelectorNames, selector, Selector::NONE);
    }

//    template<typename T>
//    json Instructions::to_json() const {
//        json result;
//        result["type"] = get_type_name(type);
//        result["selector"] = get_selector_name(selector);
//        result["tickers"] = tickers;
//        result["other"] = other.to_json();
//        return result;
//    }
//
//
//    void Instructions::from_json(const json &j) {
//        type = get_type_from_string(j["type"].get<std::string>());
//        selector = get_selector_from_string(j["selector"].get<std::string>());
//        tickers = j["tickers"].get<std::vector<std::string>>();
//        other.from_json(j["other"]);
//    }

}
