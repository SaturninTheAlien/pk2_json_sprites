#include "pk2sprite.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <stdexcept>


namespace kogutozaurus
{

PK2Sprite::PK2Sprite()
{
    //std::cout<<"PK2Sprite c-tor"<<std::endl;

    char*c = reinterpret_cast<char*>(this);
    size_t n = sizeof(PK2Sprite);
    for(size_t i=0;i<n;++i)
    {
        c[i] = 0;
    }

    strcpy(this->version, "1.3");
    strcpy(this->bmp_path, "");
    
    for(int i=0;i<7;++i)
    {
        strcpy(this->sound_path[i], "");
    }

    strcpy(this->name, "nameless sprite");
    strcpy(this->sprite_to_turn_into, "");
    strcpy(this->bonus_sprite, "");
    strcpy(this->ammo1, "");
    strcpy(this->ammo2, "");
}


void to_json(nlohmann::json& j, const PK2Sprite& c){

    using json = nlohmann::json;

    j["type"] = c.sprite_type;
    j["bmp"] = c.bmp_path;

    std::vector<json> v1;
    for(int i=0;i<7;++i)
    {
        if( *c.sound_path[i] != '\0')
        {
            json sound;
            sound["path"] = c.sound_path[i];
            sound["type"] = c.sound_types[i];
            v1.emplace_back(sound);
        }
    }
    j["sounds"] = v1;

    json anim;
    anim["frames_number"] = c.frames_number;
    anim["animations_number"] = c.animations_number;

    std::vector<json> sequences;

    for(int i=0;i<20;++i)
    {
        
        const PK2SPRITE_ANIMATION& s = c.animation_sequences[i];
        if(s.frames!=0)
        {
            json anim_seqence;

            int frames_number = s.frames;
            if(frames_number>10) frames_number = 10;

            //anim_seqence["frames_number"] = frames_number;
            anim_seqence["sequence"] = std::vector<int>(s.sequence, s.sequence + frames_number);
            anim_seqence["loop"] = s.loop;
            sequences.emplace_back(anim_seqence);
        }
    }
    anim["sequences"] = sequences;

    j["animations"] = anim;
    json frame;

    frame["rate"] = c.frame_rate;
    frame["pos_x"] = c.frame_x_pos;
    frame["pos_y"] = c.frame_y_pos;
    frame["width"] = c.frame_width;
    frame["height"] = c.frame_height;
    frame["space"] = c.space_between_frames;

    j["frame"] = frame;

    j["name"] = c.name;
    j["width"] = c.width;
    j["height"] = c.height;
    j["weight"] = c.weight;
    j["enemy"] = c.enemy;
    j["energy"] = c.energy;
    j["demage"] = c.demage;
    j["demage_type"] = c.demage_type;
    j["protection_type"] = c.protection_type;
    j["score"] = c.score;

    std::vector<int> ai_vec;

    for(int i=0;i<10;++i)
    {
        if(c.AI[i]!=0)
        {
            ai_vec.emplace_back(c.AI[i]);
        }
    }

    j["ai"] = ai_vec;
    j["max_jump_time"] = c.max_jump_time;
    j["max_speed"] = c.max_speed;
    j["charge_time"] = c.charge_time;
    j["color"] = c.color;
    j["is_wall"] = c.isWall;
    j["how_destroyed"] = c.how_destroyed;
    j["can_open_locks"] = c.can_open_locks;
    j["vibrates"] = c.vibrates;
    j["bonuses_number"] = c.bonuses_number;
    j["attack1_time"] = c.attack1_time;
    j["attack2_time"] = c.attack2_time;
    j["parallax_type"] = c.parallax_type;
    j["sprite_to_turn_into"] = c.sprite_to_turn_into;
    j["bonus_sprite"] = c.bonus_sprite;
    j["ammo1"] = c.ammo1;
    j["ammo2"] = c.ammo2;
    j["makes_sounds"] = c.makes_sounds;
    j["sound_frequency"] = c.sound_frequency;
    j["random_sound_frequency"] = c.random_sound_frequency;
    j["is_wall_up"] = c.is_wall_up;
    j["is_wall_down"] = c.is_wall_down;
    j["is_wall_right"] = c.is_wall_rigth;
    j["is_wall_left"] = c.is_wall_left;

    json unused_data;

    unused_data["transparency"] = c.transparency;
    unused_data["is_transparent"] = c.is_transparent;
    unused_data["charge_time2"] = c.unused_charge_time2;

    j["unused_data"] = unused_data;

    j["can_glide"] = c.can_glide;
    j["boss"] = c.boss;
    j["bonus_always"] = c.bonus_always;
    j["can_swim"] = c.can_swim;
}


void get_limited_str(const nlohmann::json&j, const char*name, char* dest, std::size_t n){

    if(j.contains(name) && j[name].is_string()){
        std::string s = j[name].get<std::string>();
        if(s.size() +1 >= n){
            throw std::length_error("String: \""+s+"\" is too long!");
        }
        std::strncpy(dest, s.c_str(), n);
    }
}

/*
void from_json(const nlohmann::json&j, PK2Sprite& sprite){

    j.at("type").get_to(sprite.sprite_type);
    get_limited_str(j, "bmp", sprite.bmp_path, 100);

    if(j.contains("sounds")){
        const nlohmann::json& sj = j["sounds"];
        if(sj.is_array()){
            std::size_t sj_size = sj.size();
            if(sj_size > 7){
                throw std::length_error("Too many sounds, max 10 allowed");
            }

            for(std::size_t i=0;i<sj_size;++i){
                const nlohmann::json& sound = sj[i];
                if(sound.is_object()){
                    if(sound.contains("type")){
                        j.at("type").get_to(sprite.sound_types[i]);
                    }
                    get_limited_str(sound, "path", sprite.sound_path[i], 100);
                }
            }
        }
    }

    if(j.contains("animations") && j["animations"].is_object()){
        const nlohmann::json& animations = j["animations"];
        animations.at("frames_number").get_to(sprite.frames_number);
        animations.at("animations_number").get_to(sprite.animations_number);


    }
    
    get_limited_str(j, "name", sprite.name, 30);
    
    j.at("is_wall_up").get_to(sprite.is_wall_up);
    j.at("is_wall_left").get_to(sprite.is_wall_left);
    j.at("is_wall_down").get_to(sprite.is_wall_down);
    j.at("is_wall_right").get_to(sprite.is_wall_up);

    if(j.contains("unused_data")){

        const nlohmann::json& u_j = j["unused_data"];
        if(u_j.is_object()){
            u_j.at("transparency").get_to(sprite.transparency);
            u_j.at("is_transparent").get_to(sprite.is_transparent);
            u_j.at("charge_time2").get_to(sprite.unused_charge_time2);
        }
    }
    j.at("can_glide").get_to(sprite.can_glide);
    j.at("bonus_always").get_to(sprite.bonus_always);
    j.at("can_swim").get_to(sprite.can_swim);
    throw std::runtime_error("Sprite from json not finished yet!");
}

PK2SpriteBinary::PK2SpriteBinary(const std::string& filename){
    std::ifstream in(filename, std::ios::binary);
    in.read(this->mData, 1668);

    if(!in.good()){
        throw std::runtime_error(std::string("File not found: ") + filename);
    }

    in.close();
}




PK2Sprite PK2SpriteBinary::toSPR() const{
    std::string v(this->mData);
    std::cout<<"v.size() = "<<v.size()<<std::endl;
    if(v!="1.3"){
        throw PK2SpriteBadFormatException();
    }

    PK2Sprite sprite;
    char* ptr = reinterpret_cast<char*>(&sprite);
    
    memcpy(ptr, this->mData, 1140);
    memcpy(ptr+1144, this->mData + 1144, 528);

    return sprite;
}
*/

PK2Sprite loadFromSPR(const std::string & filename)
{
    std::ifstream in;
    in.open(filename.c_str(), std::ios::binary|std::ios::in);

    if(!in.good())
    {
        throw std::runtime_error("File not found: "+filename);
    }
    PK2Sprite sprite = loadFromSPR(in);
    in.close();
    return sprite;
}

PK2Sprite loadFromSPR(std::istream & in)
{
    //PK2Sprite sprite;

    //char* ptr = reinterpret_cast<char*>(&sprite);

    PK2Sprite sprite;
    char* ptr = reinterpret_cast<char*>(&sprite);
    in.read(ptr, 1140);

    if(std::string(sprite.version)!="1.3"){
        throw PK2SpriteBadFormatException();//std::runtime_error("Incorrect sprite format");
    }

    ptr+=1144;
    in.read(ptr, 528);
    return sprite;
}

void saveToSPR(const PK2Sprite& sprite, const std::string&filename)
{
    std::ofstream out;
    out.open(filename.c_str(), std::ios::binary|std::ios::out);
    
    if(!out.good())
    {
        throw std::runtime_error("Cannot create file: "+filename);
    }

    saveToSPR(sprite, out);
    out.close();
}

void saveToSPR(const PK2Sprite& sprite, std::ostream & out)
{
    const char* ptr = reinterpret_cast<const char*>(&sprite);
    out.write(ptr, 1140);
    ptr+=1144;
    out.write(ptr, 528);
}

}


