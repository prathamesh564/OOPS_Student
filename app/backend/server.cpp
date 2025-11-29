#include "crow_all.h"
#include <unordered_map>
#include <string>

struct Student {
    std::string name;
    std::string usn;
    std::string section;
    std::string department;
    std::string contact;
};

std::unordered_map<int, Student> db = {
    {101, {"Rahul Sharma", "1RV23CS101", "A", "CSE", "9876543210"}},
    {102, {"Sneha Rao", "1RV23EC102", "B", "ECE", "8765432109"}},
    {103, {"Arjun Patil", "1RV23ME103", "C", "MECH", "9876501234"}}
};

int main()
{
    crow::SimpleApp app;

    // Route: Fetch student details using roll number
    CROW_ROUTE(app, "/student/<int>")
    ([](int roll){
        if (db.count(roll) == 0) {
            return crow::response(404, "Student Not Found");
        }

        const Student &s = db[roll];

        crow::json::wvalue res;
        res["name"] = s.name;
        res["usn"] = s.usn;
        res["section"] = s.section;
        res["department"] = s.department;
        res["contact"] = s.contact;

        return crow::response(res);
    });

    app.port(5000).multithreaded().run();
}
