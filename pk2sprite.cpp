#include "pk2sprite.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <stdexcept>


namespace pk2sprite
{

PK2Sprite::PK2Sprite(){
    //std::cout<<"PK2Sprite c-tor"<<std::endl;

    char*c = reinterpret_cast<char*>(this);
    size_t n = sizeof(PK2Sprite);
    for(size_t i=0;i<n;++i){
        c[i] = 0;
    }

    strcpy(this->version, "1.3");
    strcpy(this->bmp_path, "");
    
    for(int i=0;i<7;++i){
        strcpy(this->sound_path[i], "");
    }

    strcpy(this->name, "nameless sprite");
    strcpy(this->sprite_to_turn_into, "");
    strcpy(this->bonus_sprite, "");
    strcpy(this->ammo1, "");
    strcpy(this->ammo2, "");
}

std::map<std::string, int> soundsMap ={
    {"demage", SOUND_DAMAGE},
    {"destruction", SOUND_DESTRUCTION},
    {"attack1", SOUND_ATTACK1},
    {"attack2", SOUND_ATTACK2},
    {"random", SOUND_RANDOM},
    {"special1", SOUND_SPECIAL1},
    {"special2", SOUND_SPECIAL2}
};

void to_json(nlohmann::json& j, const PK2Sprite& c){

    using json = nlohmann::json;

    j["version"] = "2.0";

    j["type"] = c.sprite_type;
    j["bmp"] = c.bmp_path;

    json sounds;
    for(const std::pair<std::string, int> &p: soundsMap){
        sounds[p.first] = c.sound_path[p.second];
        
    }

    j["sounds"] = sounds;

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
    anim["frame_rate"] = c.frame_rate;

    j["animations"] = anim;
    json frame;

    //frame["rate"] = c.frame_rate;
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

    j["unused_data"] = unused_data;

    j["charge_time_projectile"] = c.charge_time_projectile;

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

inline void get_int_field(const nlohmann::json&j, const char*name, int& dest){
    if(j.contains(name)){
        dest = j[name].get<int>();
    }
}

inline void get_double_field(const nlohmann::json&j, const char*name, double& dest){
    if(j.contains(name)){
        dest = j[name].get<double>();
    }
}

inline void get_boolean_field(const nlohmann::json&j, const char*name, bool& dest){
    if(j.contains(name)){
        dest = j[name].get<bool>();
    }
}

void get_unsigned_char_field(const nlohmann::json&j, const char*name, unsigned char& dest){
    if(j.contains(name)){
        int temp = j[name].get<int>();
        dest = (unsigned char)temp;
    }
}

// I haven't tested this function yet, it may have bugs!
void from_json(const nlohmann::json&j, PK2Sprite& sprite){
    if(j.contains("ai")){
        const nlohmann::json& ai_table = j["ai"];

        std::size_t size = ai_table.size();
        if(size>10){
            throw std::length_error("Too many AI positions, max 10 allowed.");
        }
        for(std::size_t i=0;i<size;++i){
            sprite.AI[i] = ai_table[i];
        }
    }
    get_limited_str(j, "ammo1", sprite.ammo1, 100);
    get_limited_str(j, "ammo2", sprite.ammo2, 100);
    if(j.contains("animations")){
        const nlohmann::json& aj = j["animations"];

        get_unsigned_char_field(aj, "animations_number", sprite.animations_number);
        get_unsigned_char_field(aj, "frame_rate", sprite.frame_rate);
        get_unsigned_char_field(aj, "frames_number", sprite.frames_number);

        if(aj.contains("sequences")){
            const nlohmann::json& sj = aj["sequences"];
            std::size_t size = sj.size();
            if(size > 20){
                throw std::length_error("Too many animation sequences, max 20 allowed.");
            }
            for(std::size_t i=0;i<size;++i){
                get_boolean_field(sj, "loop", sprite.animation_sequences[i].loop);
                const nlohmann::json& sequence = sj["sequence"];
                std::size_t size2 = sequence.size();
                if(size2 > 10){
                    throw std::length_error("Too long animation sequence, max 10 allowed.");
                }

                for(std::size_t k=0;k<size2;++k){
                    int tmp = sj[k].get<int>();
                    sprite.animation_sequences[i].sequence[k] = (unsigned char)tmp;
                }
            }
        }
    }

    get_int_field(j, "attack1_time", sprite.attack1_time);
    get_int_field(j, "attack2_time", sprite.attack2_time);
    
    get_limited_str(j, "bmp", sprite.bmp_path, 100);

    get_boolean_field(j, "bonus_always", sprite.bonus_always);
    get_limited_str(j, "bonus_sprite", sprite.bonus_sprite, 100);
    get_unsigned_char_field(j, "bonuses_number", sprite.bonuses_number);

    get_boolean_field(j, "boss", sprite.boss);

    get_boolean_field(j, "can_glide", sprite.can_glide);

    get_boolean_field(j, "can_open_locks", sprite.can_open_locks);

    get_boolean_field(j, "can_swim", sprite.can_swim);

    get_int_field(j, "charge_time", sprite.charge_time);

    get_unsigned_char_field(j, "color", sprite.color);

    get_int_field(j, "demage", sprite.demage);
    get_unsigned_char_field(j, "demage_type", sprite.demage_type);

    get_boolean_field(j, "enemy", sprite.enemy);

    get_int_field(j, "energy", sprite.energy);

    if(j.contains("frame")){
        const nlohmann::json& fj = j["frame"];
        get_int_field(fj, "height", sprite.frame_height);
        get_int_field(fj, "pos_x", sprite.frame_x_pos);
        get_int_field(fj, "pos_y", sprite.frame_y_pos);

        get_int_field(fj, "space", sprite.space_between_frames);
        get_int_field(fj, "width", sprite.frame_width);
    }
    get_int_field(j, "height", sprite.height);

    get_int_field(j, "how_destroyed", sprite.how_destroyed);

    get_boolean_field(j, "is_wall", sprite.isWall);
    get_boolean_field(j, "is_wall_down", sprite.is_wall_down);
    get_boolean_field(j, "is_wall_left", sprite.is_wall_left);
    get_boolean_field(j, "is_wall_right", sprite.is_wall_rigth);
    get_boolean_field(j, "is_wall_up", sprite.is_wall_up);

    get_boolean_field(j, "makes_sounds", sprite.makes_sounds);

    get_unsigned_char_field(j, "max_jump_time", sprite.max_jump_time);

    get_double_field(j, "max_speed", sprite.max_speed);

    get_limited_str(j, "name", sprite.name, 30);

    get_int_field(j, "parallax_type", sprite.parallax_type);

    get_unsigned_char_field(j, "protection_type", sprite.protection_type);

    get_boolean_field(j, "random_sound_frequency", sprite.random_sound_frequency);

    get_int_field(j, "score", sprite.score);

    get_int_field(j, "sound_frequency", sprite.sound_frequency);
    if(j.contains("sounds") && j["sounds"].is_array()){

        const nlohmann::json& sj = j["sounds"];
        std::size_t size = sj.size();
        if(size>7){
            throw std::length_error("Too many sounds, max 7 allowed.");
        }
        for(std::size_t i=0;i<size;++i){
            get_limited_str(sj[i], "path", sprite.sound_path[i], 100);
            get_int_field(sj[i], "type", sprite.sound_types[i]);
        }
    }

    get_limited_str(j, "sprite_to_turn_into", sprite.sprite_to_turn_into, 100);
    
    get_int_field(j, "type", sprite.sprite_type);

    if(j.contains("unused_data")){
        const nlohmann::json& udj = j["unused_data"];
        
        get_boolean_field(udj, "is_transparent", sprite.is_transparent);
        get_unsigned_char_field(udj, "transparency", sprite.transparency);
    }

    get_int_field(j, "charge_time_projectile", sprite.charge_time_projectile);

    get_boolean_field(j, "vibrates", sprite.vibrates);
    
    get_double_field(j, "weight", sprite.weight);

    get_int_field(j, "width", sprite.width);
}

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


