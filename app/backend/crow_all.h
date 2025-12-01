#pragma once
#include <string>
#include <functional>
#include <map>
#include <unordered_map>
#include <iostream>
#include <sstream>

namespace crow {
    struct json_wvalue {
        std::unordered_map<std::string, std::string> data;
        std::string& operator[](const std::string& key) { return data[key]; }
        std::string dump() const {
            std::string s = "{";
            bool first = true;
            for (auto& kv : data) {
                if (!first) s += ",";
                s += "\"" + kv.first + "\":\"" + kv.second + "\"";
                first = false;
            }
            s += "}";
            return s;
        }
    };

    struct response {
        int code;
        std::string body;
        response(int c=200, const std::string& b="") : code(c), body(b) {}
    };

    class SimpleApp {
        using RouteHandler = std::function<response(const std::string&)>;
        std::map<std::string, RouteHandler> routes_;
    public:
        void add_route(const std::string& url, RouteHandler handler) {
            routes_[url] = handler;
        }

        // Simulate GET requests
        response handle_request(const std::string& url) {
            auto qpos = url.find('?');
            std::string path = (qpos == std::string::npos) ? url : url.substr(0, qpos);
            if (routes_.count(path))
                return routes_[path](url);
            return response(404, "{\"error\":\"Route Not Found\"}");
        }
    };
}
