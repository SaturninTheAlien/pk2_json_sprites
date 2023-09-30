//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################

/**
 * @brief 
 * This is a sprite mockup class for the purpose of conversion .spr to .sprv2 (.json)
 */


#pragma once

#include <stdexcept>
#include <vector>
#include <string>
#include <array>

#include "3rd_party/json.hpp"
#include "spriteclass_spr.hpp"

namespace pk2sprite
{

class PK2SpriteBadFormatException: public std::exception{
public:
    const char* what() const noexcept{
        return "Unsupported sprite format!";
    }
};

class PrototypeClass;

class SpriteAnimation{
public:
    SpriteAnimation(){};
    SpriteAnimation(const LegacySprAnimation& anim){
        this->loop = anim.loop;
        this->sequence = std::vector<int>(anim.sequence, anim.sequence + anim.frames);
    }
    bool loop = false;
    std::vector<int> sequence;

    friend void to_json(nlohmann::json& j, const SpriteAnimation& a);
    friend void from_json(const nlohmann::json&j, SpriteAnimation& a);
};

//Classes used in game
class PrototypeClass{
    public:

    std::string version = "2.0";

    std::string filename;
    std::string picture_filename;
    
    int     type = TYPE_NOTHING;

    std::array<std::string, SPRITE_SOUNDS_NUMBER> sound_files = {""};
    std::array<int, SPRITE_SOUNDS_NUMBER> sounds = {-1};

    //int     framet[SPRITE_MAX_FRAMEJA] = {0};
    std::vector<int>frames;
    std::vector<int>frames_mirror;
    //int     framet_peilikuva[SPRITE_MAX_FRAMEJA] = {0};
    int      frames_number            = 0;

    std::array<SpriteAnimation, SPRITE_ANIMATIONS_NUMBER> animations;
    //PK2SPRITE_ANIMAATIO animaatiot[SPRITE_MAX_ANIMAATIOITA] = {};
    //u8      animations_number       = 0;
    int      frame_rate         = 0;
    int     picture_frame_x             = 0;
    int     picture_frame_y             = 0;
    int     picture_frame_width  = 0;
    int     picture_frame_height = 0;

    std::string name;
    int     width    = 0;
    int     height   = 0;
    double  weight    = 0;

    bool    enemy     = false;
    int     energy        = 0;
    int     damage        = 0;
    int      damage_type = DAMAGE_IMPACT;
    int      immunity_type        = DAMAGE_NONE;
    int     score        = 0;

    std::vector<int> AI_v;
    int first_ai()const{
        return AI_v.empty()? 0 : AI_v[0];
    }

    int      max_jump    = 0;
    double  max_speed   = 3;
    int     charge_time  = 0;
    u8      color         = COLOR_NORMAL;
    bool    is_wall         = false;
    int     how_destroyed = FX_DESTRUCT_ANIMAATIO;
    bool    can_open_locks        = false;
    bool    vibrates      = false;
    int      bonuses_number = 1;
    int     attack1_time = 60;
    int     attack2_time = 60;

    int     parallax_type = 0;

    std::string transformation_sprite;
    std::string bonus_sprite;
    std::string ammo1_sprite;
    std::string ammo2_sprite;


    PrototypeClass* transformation     = nullptr;
    PrototypeClass* bonus      = nullptr;
    PrototypeClass* ammo1     = nullptr;
    PrototypeClass* ammo2     = nullptr;

    bool    makes_sounds = true;
    int     sound_frequency      = 22050;
    bool    random_sound_frequency    = true;

    bool    is_wall_up       = true;
    bool    is_wall_down       = true;
    bool    is_wall_right   = true;
    bool    is_wall_left = true;

    u8      effect       = EFFECT_NONE;
    bool    is_transparent       = false;
    int     projectile_charge_time    = 0;
    bool    can_glide    = false;
    bool    boss         = false;
    bool    bonus_always = false;
    bool    can_swim     = false;

    /**
     * @brief 
     * If true a sprite will be active even far from the camera
     */
    bool    always_active = false;   // 

    PrototypeClass();
    ~PrototypeClass();

    int     Load(const std::string& path, bool legacy_spr);
    bool    HasAI(int AI)const;

    void    SetProto10(PrototypeClass10 &proto);
    void    SetProto11(PrototypeClass11 &proto);
    void    SetProto12(PrototypeClass12 &proto);
    void    SetProto13(PrototypeClass13 &proto);

    void    SetProto20(const nlohmann::json& j);

    friend void to_json(nlohmann::json& j, const PrototypeClass& c);
};
}