#include "crow_all.h"
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>

struct Student {
    std::string name, usn, section, department, contact;
};

std::unordered_map<int, Student> db = {
    {101, {"Rahul Sharma", "1RV23CS101", "A", "CSE", "9876543210"}},
    {102, {"Sneha Rao", "1RV23EC102", "B", "ECE", "8765432109"}},
    {103, {"Arjun Patil", "1RV23ME103", "C", "MECH", "9876501234"}}
};

int main() {
    crow::SimpleApp app;

    // Register API endpoint
    app.add_route("/student", [&](const std::string& url) -> crow::response {
        auto pos = url.find("roll=");
        if (pos == std::string::npos)
            return crow::response(400, "{\"error\":\"Missing roll number\"}");

        int roll;
        std::istringstream(url.substr(pos + 5)) >> roll;

        if (db.count(roll) == 0)
            return crow::response(404, "{\"error\":\"Student Not Found\"}");

        const auto& s = db[roll];
        crow::json_wvalue res;
        res["name"] = s.name;
        res["usn"] = s.usn;
        res["section"] = s.section;
        res["department"] = s.department;
        res["contact"] = s.contact;

        return crow::response(200, res.dump());
    });

    // Simulate GET requests (like a backend API call)
    std::string test_url = "/student?roll=101";
    std::cout << app.handle_request(test_url).body << std::endl;

    test_url = "/student?roll=105";
    std::cout << app.handle_request(test_url).body << std::endl;

    test_url = "/student";
    std::cout << app.handle_request(test_url).body << std::endl;

    return 0;
}
