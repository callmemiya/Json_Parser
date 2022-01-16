// Copyright 2018 Your Name <your_email>
#include <parser.hpp>
using nlohmann::json;


void print_delimeter(int n, int g, int a, int d){
    std::cout <<std::setfill('-') <<std::setw(n + 2) <<"|";
    std::cout <<std::setfill('-') <<std::setw(g + 2) <<"|";
    std::cout <<std::setfill('-') <<std::setw(a + 2) <<"|";
    std::cout <<std::setfill('-') <<std::setw(d + 2) <<"|";
}

void print(const std::vector<Student>& Stud){
    int n = 4, g = 5, a = 3, d = 4;
    std::string f, r;
    for (auto const& s : Stud){
        if (static_cast<int>(s.Name.size()) > n) n = s.Name.size();
        f = std::any_cast<std::string>(s.Group);
        if (static_cast<int>(f.size()) > g) g = f.size();
        r = std::any_cast<std::string>(s.Avg);
        if (static_cast<int>(r.size()) > a) a = r.size();
        std::vector<std::string> St;
        std::any m = std::any_cast<std::vector<std::string>>(St);
        if (s.Debt.type() == m.type()){
            if (static_cast<int>(sizeof("__ items")) > d)
                d = static_cast<int>(sizeof("__ items"));
        } else {
            r = std::any_cast<int>(s.Debt);
            if (static_cast<int>(r.size()) > d) d = r.size();
        }
    }
    std::cout <<"|" <<std::setw(n + 2) <<" name";
    std::cout <<"|" <<std::setw(g + 2) <<" group";
    std::cout <<"|" <<std::setw(a + 2) <<" avg";
    std::cout <<"|" <<std::setw(d + 2) <<" debt";
    std::cout <<"|" <<std::endl;
    print_delimeter(n, g, a, d);
    for (auto const& st : Stud){
        std::string s;
        std::cout <<"|" <<std::setw(n + 2) <<st.Name;
        s = std::any_cast<std::string>(st.Group);
        std::cout <<"|" <<std::setw(g + 2) <<s;
        s = std::any_cast<std::string>(st.Avg);
        std::cout <<"|" <<std::setw(a + 2)
        <<std::fixed <<std::setprecision(2) <<s;
        std::any v = std::vector<std::string>();
        std::any p = nullptr;
        if (st.Debt.type() == v.type()){
            auto m = std::any_cast<std::vector<std::string>>(st.Debt);
            s = std::to_string(m.size()) + " items";
        } else if (st.Debt.type() == p.type()){
            s = "null";
        } else {
            s = std::any_cast<std::string>(st.Debt);
        }
        std::cout <<"|" <<std::setw(d + 2) <<s;
        std::cout <<"|" <<std::endl;
    }
}


int main(){
    std::string jsonPath = "students.json";
    std::ifstream file{jsonPath};
    if (!file) {
        throw std::runtime_error{"unable to open json: " + jsonPath};
    }
    json data;
    file >> data;
    std::vector<Student> students;
    if (!data.at("items").is_array()){
        throw std::runtime_error{"there are no students in file"};
    }
    for (auto const& student : data.at("items")) {
        students.push_back(student);
    }
    if (students.size() != data.at("_meta").at("count").get<size_t>()){
        throw std::runtime_error
            {"actual vector size doesn't match meta value"};
    }
    print(students);
    return 0;
}
