#pragma once
#include <ostream>
#include <istream>
#include "3rd_party/json.hpp"

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
namespace kogutozaurus
{

class PK2SpriteBadFormatException {};


class PK2SPRITE_ANIMATION
{
public:
    unsigned char    sequence[10]; // sequence
    unsigned char    frames;                            // frames
    bool  loop;                             // loop
};


class PK2Sprite
{
public:
    PK2Sprite();
    void clear();

    char version[4];
    int    sprite_type;											// sprite type
    char   bmp_path[100];								// bmp path
    char   sound_path[7][100];							// sound path (max 7)
    int    sound_types[7];										// sound types


    unsigned char     frames_number;										// number of frames
    PK2SPRITE_ANIMATION animation_sequences[20];							// animation sequences
    unsigned char     animations_number;									// number of animations
    unsigned char     frame_rate;										// frame rate
    int    frame_x_pos;											// x position of first frame
    int    frame_y_pos;											// y position of first frame
    int    frame_width;								// frame width
    int    frame_height;								// frame height
    int    space_between_frames;								// space between frames


    char   name[30];										// name
    int    width;											// width
    int    height;										// height
    double weight;											// weight (for jump and switches)
    bool   enemy;										// if sprite is a enemy
    int    energy;										//?sprite energy
    int    demage;										//?damage if it got hit
    unsigned char     demage_type;								//?damage type
    unsigned char     protection_type;										  //?protection type
    int    score;										// how much score
    int    AI[10];											// AI type (max 10)
    unsigned char     max_jump_time;										// max jump time
    double max_speed;										// max speed
    int    charge_time;										//?wait post shoot
    unsigned char     color;											// color
    bool   isWall;											// is a wall
    int    how_destroyed;									// how sprite is destroyed
    bool   can_open_locks;											// can sprite open locks
    bool   vibrates;										//?sprite randomly
    unsigned char     bonuses_number;									// number of bonuses
    int    attack1_time;									// attack 1 duration (frames)
    int    attack2_time;									// attack 2 duration (frames)
    int    parallax_type;								// parallax type (just to TYPE_BACKGROUND)


    char   sprite_to_turn_into[100];								// another sprite that this sprite may change
    char   bonus_sprite[100];								// bonus that this sprite gives
    char   ammo1[100];								// ammo 1 sprite
    char   ammo2[100];								// ammo 2 sprite


    bool   makes_sounds;									//?make sounds?
    int	   sound_frequency;										// sound frequency (def. 22050)
    bool   random_sound_frequency;										// use random frequency?


    bool   is_wall_up;                                      // if is wall at up
    bool   is_wall_down;                                      // if is wall at down
    bool   is_wall_rigth;                                  // if is wall at right
    bool   is_wall_left;                                // if is wall at left


    unsigned char     transparency;									// transparency //unused
    bool   is_transparent;											// if it is transparent //unused
    int    unused_charge_time2;										//*ammuspriten ampujalle aiheuttama charge_time
    bool   can_glide;										// can drip quietly down?
    bool   boss;											// if it is a boss //unused
    bool   bonus_always;									// if not there is 1/4 chance of droping bonus
    bool   can_swim;										// walk fast under water

    friend void to_json(nlohmann::json& j, const PK2Sprite& c);
    friend void from_json(const nlohmann::json&j, PK2Sprite& c);
};


PK2Sprite loadFromSPR(const std::string & filename);
PK2Sprite loadFromSPR(std::istream & in);

void saveToSPR(const PK2Sprite& sprite, const std::string&filename);
void saveToSPR(const PK2Sprite& sprite, std::ostream & out);



}