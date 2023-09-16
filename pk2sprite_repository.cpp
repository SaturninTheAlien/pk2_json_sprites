#include "pk2sprite_repository.h"
#include <filesystem>
#include <algorithm>
#include <iostream>

namespace pk2sprite{
namespace fs = std::filesystem;

PK2SpriteRepository::PK2SpriteRepository(const std::string& pk2_path){

    for (const auto & entry : fs::directory_iterator(pk2_path)){
        if(entry.is_regular_file()){
            fs::path p = entry.path();
            std::string filename = p.filename();
            if(filename.size()>4 && filename.substr(filename.size()-4,4)==".spr"){

                try{
                    PK2Sprite sprite = loadFromSPR(p);
                    this->mSpritesMap.emplace(std::make_pair(filename.substr(0, filename.size() -4),
                    sprite));

                    for(int i=0;i<7;++i){
                        if(sprite.sound_types[i]!=-1){
                            std::cout<<filename<<": "<<sprite.sound_types[i]<<std::endl;
                        }
                    }

                }
                catch(const PK2SpriteBadFormatException& e){}               
            }            
        }
    }
}

void PK2SpriteRepository::addRoutes(httplib::Server& srv){
    srv.Get("/api/sprites", [this](const httplib::Request &req, httplib::Response & res){
        this->Get(req, res);
    });
}

void PK2SpriteRepository::Get(const httplib::Request & req, httplib::Response &res) const{
    
    if(req.has_param("name")){
        std::string name = req.get_param_value("name");
        auto it = this->mSpritesMap.find(name);
        if(it!=this->mSpritesMap.end()){
            json_response(res, it->second);
        }
        else{

            json_not_found_response(res,
            std::string("Sprite with name: ")+ name+" not found.");
        }
    }
    else{
        json_response(res, this->mSpritesMap);
    }
}

}