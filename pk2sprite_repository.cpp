#include "pk2sprite_repository.h"
#include <string>
#include <filesystem>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

namespace pk2sprite{
namespace fs = std::filesystem;

PK2SpriteRepository::PK2SpriteRepository(const std::string& pk2_path){

    for (const auto & entry : fs::directory_iterator(pk2_path)){
        if(entry.is_regular_file()){
            fs::path p = entry.path();
            std::string filename = p.filename().string();
            if(filename.size()>4 && filename.substr(filename.size()-4,4)==".spr"){

                //std::cout<<filename<<std::endl;
                try{
                    PrototypeClass sprite;
                    sprite.Load(p.string(), true);
                    this->mSpritesMap.emplace(std::make_pair(filename.substr(0, filename.size() -4),
                    sprite));
                    
                    
                    /*nlohmann::json sprite_j = sprite;

                    std::ostringstream os;
                    os<<"./json_sprites/"<<filename<<"2";
                    std::string new_path = os.str();
                    //std::cout<<new_path<<std::endl;

                    std::ofstream file_out(new_path.c_str());
                    file_out << sprite_j.dump(4);
                    file_out.close();*/
                }
                catch(const PK2SpriteBadFormatException& e){
                    //std::cout<<filename<<std::endl;
                }               
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