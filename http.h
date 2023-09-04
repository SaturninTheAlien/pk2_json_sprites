#pragma once

#include "3rd_party/json.hpp"
#include "3rd_party/httplib.h"

#include <string>
#include <shared_mutex>

namespace kogutozaurus{

inline void json_response(httplib::Response &res, const nlohmann::json& j, int status=200){
    res.status = status;
    res.set_content(j.dump(4), "application/json");
}

inline void json_not_found_response(httplib::Response &res, const std::string & message){
    nlohmann::json j;
    j["message"] = message;
    json_response(res, j, 404);
}

}