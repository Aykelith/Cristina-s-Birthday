#ifndef XAL_JSONTOOLS_HPP
#define XAL_JSONTOOLS_HPP

#include <fstream>
#include <json.hpp>
using json = nlohmann::json;

namespace XAL {
    namespace JSONTools {
        inline json parseJSONFromFile(const std::string& filename) {
            std::ifstream file(filename);
            auto jsonObj = json::parse(file);
            file.close();

            return jsonObj;
        }
    }
}

#endif // XAL_JSONTOOLS_HPP
