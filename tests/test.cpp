// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <parser.hpp>
using nlohmann::json;

TEST(Parser, Students) {
    json N = R"(
        {
          "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
        }
    )"_json;
    Student s1;
    from_json(N, s1);
    EXPECT_EQ(std::any_cast<std::string>(s1.Group), "1");
    EXPECT_EQ(std::any_cast<std::string>(s1.Avg), "4.25");
    EXPECT_EQ(s1.Name, "Ivanov Petr");
}

TEST(Parser, Groups){
    json M = R"(
        {
          "name": "Sidorov Ivan",
          "group": 31,
          "avg": "4",
          "debt": [
            "C++",
            "Linux",
            "Network"
          ]
        }
    )"_json;
    std::vector<std::string> debt = {"C++", "Linux", "Network"};
    Student s2;
    from_json(M, s2);
    EXPECT_EQ(std::any_cast<int>(s2.Group), 31);
    EXPECT_EQ(std::any_cast<std::vector<std::string>>(s2.Debt), debt);
}

TEST(Parser, Debt){
    json B = R"(
        {
            "name": "Sidorov Ivan",
            "group": 31,
            "avg": 4,
            "debt": "C++"
        }
    )"_json;
    Student s3;
    from_json(B, s3);
    EXPECT_EQ(std::any_cast<std::string>(s3.Debt), "C++");
}

