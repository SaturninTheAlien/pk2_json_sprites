#pragma once

#include "3rd_party/json.hpp"
#include "3rd_party/httplib.h"
#include "http.h"


#include <map>
#include <shared_mutex>
#include "pk2sprite.h"

namespace kogutozaurus{

class PK2SpriteRepository{
public:
    PK2SpriteRepository() = default;
    PK2SpriteRepository(const std::string& pk2_path);
    void addRoutes(httplib::Server& srv);

private:
    void Get(const httplib::Request & req, httplib::Response &res) const;

    void notFound(httplib::Response & res, const std::string &name) const{
        res.status = 404;
        res.set_content(std::string("Sprite with name: ")+name + " not found.",
        "text/plain");
    }
    
    //std::vector<PK2Sprite> mSprites;
    std::map<std::string, PK2Sprite> mSpritesMap;
    //mutable std::shared_mutex mSharedMutex;
};

}