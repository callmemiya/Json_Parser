// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_

#include <any>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <iomanip>
using json = nlohmann::json;

struct Student {
    std::string Name;
    std::any Group;
    std::any Avg;
    std::any Debt;
};

void get_group(const json& f, std::any& a){
    if (f.is_string()){
        a = f.get<std::string>();
    }else if (f.is_number()){
        a = f.get<int>();
    }
}

void get_avg(const json& f, std::any& a){
    if (f.is_string()){
        a = f.get<std::string>();
    }else if (f.is_number_float()){
        a = f.get<double>();
    }else if (f.is_number_integer()){
        a = f.get<int>();
    }
}

void get_debt(const json& f, std::any& a){
    if (f.is_string()){
        a = f.get<std::string>();
    } else if (f.is_null()){
        a = nullptr;
    } else if (f.is_array()){
        a = f.get<std::vector<std::string>>();
    }
}

void from_json(const json& j, Student& s) {
    j.at("name").get_to(s.Name);
    get_group(j.at("group"), s.Group);
    get_avg(j.at("avg"), s.Avg);
    get_debt(j.at("debt"), s.Debt);
}

#endif // INCLUDE_PARSER_HPP_
