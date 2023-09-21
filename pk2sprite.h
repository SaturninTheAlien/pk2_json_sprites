#pragma once
#include <ostream>
#include <istream>
#include "3rd_party/json.hpp"
#include <stdexcept>
#include <map>

#include <cstdint>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef unsigned int uint;


/*
#define PK2SPRITE_CURRENT_VERSION "1.3"

#define MAX_SPRITEJA       850
#define MAX_PROTOTYYPPEJA  100

#define SPRITE_MAX_FRAMEJA      50
#define SPRITE_MAX_ANIMAATIOITA 20
#define SPRITE_MAX_AI           10
#define ANIMATION_SEQUENCE_SIZE 10
#define SPRITE_MAX_SOUNDS        7
#define	DAMAGE_TIME             50
*/
namespace pk2sprite
{

class PK2SpriteBadFormatException: public std::exception{
public:
    const char* what() const noexcept{
        return "Unsupported sprite format!";
    }
};


class PK2SPRITE_ANIMATION
{
public:
    unsigned char    sequence[10]; // sequence
    unsigned char    frames;                            // frames
    bool  loop;                             // loop
};

enum {

    SOUND_DAMAGE,
    SOUND_DESTRUCTION,
    SOUND_ATTACK1,
    SOUND_ATTACK2,
    SOUND_RANDOM,
    SOUND_SPECIAL1,
    SOUND_SPECIAL2

};




class PK2Sprite
{
public:
    PK2Sprite();
    u32     sprite_type;                             // sprite type
    char    picture[100];                  // bmp path

    /**
     * @brief 
     * Sound files.
     * The index determines the sound type:
     * 0 -> damage
     * 1 -> destruction
     * 2 -> attack1
     * 3 -> attack2
     * 4 -> random
     * 5 -> special1
     * 6 -> special2
     */
    char    sound_files[7][100];
    /**
     * @brief 
     * This field is unused, seems to be -1 in all legacy sprites.
     * Although it's copied to SpritePrototype, but later is replaced while the sound loading.
     */
    u32     sounds[7];                           

    u8      frames_number;                            // number of frames
    PK2SPRITE_ANIMATION animaatiot[20];         // animation sequences
    
    /**
     * @brief 
     * unused variable
     */
    u8      animations_number;                       // number of animations
    
    
    u8      frame_rate;                         // frame rate
    u32     picture_frame_x;                             // x position of first frame
    u32     picture_frame_y;                             // y position of first frame
    u32     picture_frame_width;                  // frame width
    u32     picture_frame_height;                 // frame height
    u32     picture_frame_space;                    // space between frames //unused


    char    name[30];                           // name
    u32     width;                             // width
    u32     height;                            // height
    double  weight;                             // weight (for jump and switches)
    bool    enemy;                         // if sprite is a enemy
    u32     energy;                            //?sprite energy
    u32     damage;                            //?damage if it got hit
    u8      damage_type;                     // damage type
    u8      immunity_type;                            // immunity type
    u32     score;                            // how much score
    u32     AI[10];                             // AI type (max 10)
    u8      max_jump;                          // max jump time
    double  max_speed;                         // max speed
    u32     charge_time;                        // wait post shoot
    u8      color;                               // color
    bool    is_wall;                               // is a wall
    u32     how_destroyed;                       // how sprite is destroyed
    bool    can_open_locks;                              // can sprite open locks
    bool    vibrates;                            // vibrate sprite randomly
    u8      bonuses_number;                       // number of bonuses
    u32     attack1_time;                       // attack 1 duration (frames)
    u32     attack2_time;                       // attack 2 duration (frames)
    u32     parallax_type;                    // parallax type (just to TYPE_BACKGROUND)


    char    transformation_sprite[100];                 // another sprite that this sprite may change
    char    bonus_sprite[100];                  // bonus that this sprite gives
    char    ammo1_sprite[100];                 // ammo 1 sprite
    char    ammo2_sprite[100];                 // ammo 2 sprite


    bool    makes_sounds;                      //?make sounds?
    u32     sound_frequency;                           // sound frequency (def. 22050)
    bool    random_sound_frequency;                         // use random frequency?


    bool    is_wall_up;                          // if is wall at up
    bool    is_wall_down;                          // if is wall at down
    bool    is_wall_right;                      // if is wall at right
    bool    is_wall_left;                    // if is wall at left


    u8      effect;                             // sprite effect
    bool    is_transparent;                             // if it is transparent //unused
    u32     projectile_charge_time;                          //?charge_time inflicted by projectile sprites on the shooter
    bool    can_glide;                          // can drip quietly down?
    bool    boss;                               // if it is a boss //unused
    bool    bonus_always;                       // if not there is 1/4 chance of droping bonus
    bool    can_swim;                           // walk fast under water

    bool checkAnimation()const;

    friend void to_json(nlohmann::json& j, const PK2Sprite& c);
    //friend void from_json(const nlohmann::json&j, PK2Sprite& c);
};


PK2Sprite loadFromSPR(const std::string & filename);
PK2Sprite loadFromSPR(std::istream & in);

void saveToSPR(const PK2Sprite& sprite, const std::string&filename);
void saveToSPR(const PK2Sprite& sprite, std::ostream & out);



}