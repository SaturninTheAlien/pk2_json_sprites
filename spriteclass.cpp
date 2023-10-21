//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#include <fstream>
#include "spriteclass.hpp"
#include <iostream>
#include <cstring>
#include <algorithm>

namespace pk2sprite
{
	
const char* current_json_sprite_version = "2.0";

void to_json(nlohmann::json& j, const SpriteAnimation& a){
	j["loop"] = a.loop;
	j["sequence"] = a.sequence; 
}

void from_json(const nlohmann::json&j, SpriteAnimation& a){
	a.loop = j["loop"].get<bool>();
	a.sequence = j["sequence"].get<std::vector<int>>();
}

/* -------- SpriteClass Prototyyppi ------------------------------------------------------------------ */

PrototypeClass::PrototypeClass(){}

PrototypeClass::~PrototypeClass(){}

void PrototypeClass::SetProto10(PrototypeClass10 &proto){
	this->picture_filename = proto.picture;
	this->name = proto.name;

	this->transformation_sprite = proto.transformation_sprite;
	this->bonus_sprite = proto.bonus_sprite;
	this->ammo1_sprite = proto.ammo1_sprite;
	this->ammo2_sprite = proto.ammo2_sprite;

	for (int i=0;i<SPRITE_SOUNDS_NUMBER;i++) {
		this->sound_files[i] = proto.sound_files[i];
		this->sounds[i] = proto.sounds[i];
	}

	//animations_number		= proto.animations_number;
	can_open_locks				= proto.can_open_locks;
	energy				= proto.energy;
	is_wall				= proto.is_wall;
	frames_number				= proto.frames_number;
	frame_rate			= proto.frame_rate;
	picture_frame_x				= proto.picture_frame_x;
	picture_frame_y				= proto.picture_frame_y;
	picture_frame_width	= proto.picture_frame_width;
	picture_frame_height	= proto.picture_frame_height;
	height				= proto.height;
	charge_time			= proto.charge_time;
	width				= proto.width;
	max_jump			= proto.max_jump;
	max_speed			= proto.max_speed;
	weight				= proto.weight;
	score				= proto.score;
	immunity_type				= proto.immunity_type;
	how_destroyed		= proto.how_destroyed;
	type				= proto.sprite_type;
	damage				= proto.damage;
	color				= proto.color;
	enemy			= proto.enemy;


	for (int i=0;i<5;i++){
		if(proto.AI[i]!=0){
			this->AI_v.push_back(proto.AI[i]);
		}
	}

	for(int i=0;i<SPRITE_ANIMATIONS_NUMBER;++i){
		this->animations[i] = proto.animaatiot[i];
	}
}
void PrototypeClass::SetProto11(PrototypeClass11 &proto){
	this->picture_filename = proto.picture;
	this->name = proto.name;

	this->transformation_sprite = proto.transformation_sprite;
	this->bonus_sprite = proto.bonus_sprite;
	this->ammo1_sprite = proto.ammo1_sprite;
	this->ammo2_sprite = proto.ammo2_sprite;

	for (int i=0;i<SPRITE_SOUNDS_NUMBER;i++) {
		this->sound_files[i] = proto.sound_files[i];
		this->sounds[i] = proto.sounds[i];
	}

	//animations_number		= proto.animations_number;
	can_open_locks				= proto.can_open_locks;
	bonuses_number        = proto.bonuses_number;
	energy				= proto.energy;
	is_wall				= proto.is_wall;
	frames_number				= proto.frames_number;
	frame_rate			= proto.frame_rate;
	attack1_time		= proto.attack1_time;
	attack2_time		= proto.attack2_time;
	picture_frame_x				= proto.picture_frame_x;
	picture_frame_y				= proto.picture_frame_y;
	picture_frame_width	= proto.picture_frame_width;
	picture_frame_height	= proto.picture_frame_height;
	height				= proto.height;
	charge_time			= proto.charge_time;
	width				= proto.width;
	max_jump			= proto.max_jump;
	max_speed			= proto.max_speed;
	weight				= proto.weight;
	parallax_type		= proto.parallax_type;
	score				= proto.score;
	immunity_type				= proto.immunity_type;
	vibrates				= proto.vibrates;
	how_destroyed		= proto.how_destroyed;
	type				= proto.sprite_type;
	damage				= proto.damage;
	damage_type		= proto.damage_type;
	color				= proto.color;
	enemy			= proto.enemy;

	for (int i=0;i<5;i++){
		if(proto.AI[i]!=0){
			this->AI_v.push_back(proto.AI[i]);
		}
	}

	/*for (int i=0;i<SPRITE_MAX_ANIMAATIOITA;i++) {
		for (int j=0;j<ANIMATION_SEQUENCE_SIZE;j++)
			animaatiot[i].sekvenssi[j] = proto.animaatiot[i].sekvenssi[j];

		animaatiot[i].looppi  = proto.animaatiot[i].looppi;
		animaatiot[i].frames_number = proto.animaatiot[i].frames_number;
	}*/
	for(int i=0;i<SPRITE_ANIMATIONS_NUMBER;++i){
		this->animations[i] = proto.animaatiot[i];
	}
}
void PrototypeClass::SetProto12(PrototypeClass12 &proto){

	this->picture_filename = proto.picture;
	this->name = proto.name;

	this->transformation_sprite = proto.transformation_sprite;
	this->bonus_sprite = proto.bonus_sprite;
	this->ammo1_sprite = proto.ammo1_sprite;
	this->ammo2_sprite = proto.ammo2_sprite;

	for (int i=0;i<SPRITE_SOUNDS_NUMBER;i++) {
		//strncpy(sound_files[aani], proto.sound_files[aani], 13);
		this->sound_files[i] = proto.sound_files[i];
		this->sounds[i] = proto.sounds[i];
	}

	sound_frequency			= proto.sound_frequency;
	//animations_number		= proto.animations_number;
	can_open_locks				= proto.can_open_locks;
	bonuses_number        = proto.bonuses_number;
	energy				= proto.energy;
	is_wall				= proto.is_wall;
	is_wall_up			= proto.is_wall_up;
	is_wall_down			= proto.is_wall_down;
	is_wall_right		= proto.is_wall_right;
	is_wall_left		= proto.is_wall_left;
	frames_number				= proto.frames_number;
	frame_rate			= proto.frame_rate;
	attack1_time		= proto.attack1_time;
	attack2_time		= proto.attack2_time;
	picture_frame_x				= proto.picture_frame_x;
	picture_frame_y				= proto.picture_frame_y;
	picture_frame_width	= proto.picture_frame_width;
	picture_frame_height	= proto.picture_frame_height;
	height				= proto.height;
	charge_time			= proto.charge_time;
	width				= proto.width;
	max_jump			= proto.max_jump;
	max_speed			= proto.max_speed;
	weight				= proto.weight;
	parallax_type		= proto.parallax_type;
	score				= proto.score;
	random_sound_frequency			= proto.random_sound_frequency;
	immunity_type				= proto.immunity_type;
	vibrates				= proto.vibrates;
	makes_sounds		= proto.makes_sounds;
	how_destroyed		= proto.how_destroyed;
	type				= proto.sprite_type;
	damage				= proto.damage;
	damage_type		= proto.damage_type;
	color				= proto.color;
	enemy			= proto.enemy;

	for (int i=0;i<5;i++){
		if(proto.AI[i]!=0){
			this->AI_v.push_back(proto.AI[i]);
		}
	}

	/*for (int i=0;i<SPRITE_MAX_ANIMAATIOITA;i++) {
		for (int j=0;j<ANIMATION_SEQUENCE_SIZE;j++)
			animaatiot[i].sekvenssi[j] = proto.animaatiot[i].sekvenssi[j];

		animaatiot[i].looppi  = proto.animaatiot[i].looppi;
		animaatiot[i].frames_number = proto.animaatiot[i].frames_number;
	}*/

	for(int i=0;i<SPRITE_ANIMATIONS_NUMBER;++i){
		this->animations[i] = proto.animaatiot[i];
	}
}
void PrototypeClass::SetProto13(PrototypeClass13 &proto){
	this->picture_filename = proto.picture;
	this->name = proto.name;

	this->transformation_sprite = proto.transformation_sprite;
	this->bonus_sprite = proto.bonus_sprite;
	this->ammo1_sprite = proto.ammo1_sprite;
	this->ammo2_sprite = proto.ammo2_sprite;

	for (int i=0;i<SPRITE_SOUNDS_NUMBER;i++) {
		this->sound_files[i] = proto.sound_files[i];
		this->sounds[i] = proto.sounds[i];
	}

	sound_frequency			= proto.sound_frequency;
	//animations_number		= proto.animations_number;
	can_open_locks				= proto.can_open_locks;
	bonuses_number        = proto.bonuses_number;
	energy				= proto.energy;
	is_wall				= proto.is_wall;
	is_wall_up			= proto.is_wall_up;
	is_wall_down			= proto.is_wall_down;
	is_wall_right		= proto.is_wall_right;
	is_wall_left		= proto.is_wall_left;
	frames_number				= proto.frames_number;
	frame_rate			= proto.frame_rate;
	attack1_time		= proto.attack1_time;
	attack2_time		= proto.attack2_time;
	picture_frame_x				= proto.picture_frame_x;
	picture_frame_y				= proto.picture_frame_y;
	picture_frame_width	= proto.picture_frame_width;
	picture_frame_height	= proto.picture_frame_height;
	height				= proto.height;
	charge_time			= proto.charge_time;
	width				= proto.width;
	max_jump			= proto.max_jump;
	max_speed			= proto.max_speed;
	weight				= proto.weight;
	parallax_type		= proto.parallax_type;
	score				= proto.score;
	random_sound_frequency			= proto.random_sound_frequency;
	immunity_type				= proto.immunity_type;
	vibrates				= proto.vibrates;
	makes_sounds		= proto.makes_sounds;
	how_destroyed		= proto.how_destroyed;
	type				= proto.sprite_type;
	damage				= proto.damage;
	damage_type		= proto.damage_type;
	color				= proto.color;
	enemy			= proto.enemy;

	effect		= proto.effect;
	is_transparent				= proto.is_transparent;
	projectile_charge_time			= proto.projectile_charge_time;
	can_glide			= proto.can_glide;
	boss				= proto.boss;
	bonus_always			= proto.bonus_always;
	can_swim			= proto.can_swim;

	for (int i=0;i<10;i++){
		if(proto.AI[i]!=0){
			this->AI_v.push_back(proto.AI[i]);
		}
	}

	/*for (int i=0;i<SPRITE_MAX_ANIMAATIOITA;i++) {
		for (int j=0;j<ANIMATION_SEQUENCE_SIZE;j++)
			animaatiot[i].sekvenssi[j] = proto.animaatiot[i].sekvenssi[j];

		animaatiot[i].looppi  = proto.animaatiot[i].looppi;
		animaatiot[i].frames_number = proto.animaatiot[i].frames_number;
	}*/

	for(int i=0;i<SPRITE_ANIMATIONS_NUMBER;++i){
		this->animations[i] = proto.animaatiot[i];
	}
}

const std::map<std::string, int> jsonAnimationsMap = {
	{"idle", ANIMATION_IDLE},
    {"walking", ANIMATION_WALKING},
    {"jump_up", ANIMATION_JUMP_UP},
    {"jump_down", ANIMATION_JUMP_DOWN},
    {"squat", ANIMATION_SQUAT},
    {"damage", ANIMATION_DAMAGE},
    {"death", ANIMATION_DEATH},
    {"attack1", ANIMATION_ATTACK1},
    {"attack2", ANIMATION_ATTACK2}
};

const std::map<std::string, int> jsonSoundsMap ={
    {"damage", SOUND_DAMAGE},
    {"destruction", SOUND_DESTRUCTION},
    {"attack1", SOUND_ATTACK1},
    {"attack2", SOUND_ATTACK2},
    {"random", SOUND_RANDOM},
    /*{"special1", SOUND_SPECIAL1},
    {"special2", SOUND_SPECIAL2}*/
};

const std::map<std::string ,u8> jsonColorsMap={
	{"gray", COLOR_GRAY},
	{"blue", COLOR_BLUE},
	{"red", COLOR_RED},
	{"green", COLOR_GREEN},
	{"orange", COLOR_ORANGE},
	{"violet", COLOR_VIOLET},
	{"turquoise", COLOR_TURQUOISE},
	{"normal", COLOR_NORMAL}
};

void jsonReadString(const nlohmann::json& j, const std::string name, std::string& target){
	if(j.contains(name)){
		target = j[name].get<std::string>();
	}
}

void jsonReadInt(const nlohmann::json& j, const std::string name, int& target){
	if(j.contains(name)){
		target = j[name].get<int>();
	}
}

void jsonReadDouble(const nlohmann::json& j, const std::string name, double& target ){
	if(j.contains(name)){
		target = j[name].get<double>();
	}
}

void jsonReadBool(const nlohmann::json& j, const std::string name, bool& target){
	if(j.contains(name)){
		target = j[name].get<bool>();
	}
}

void jsonReadEnumU8(const nlohmann::json& j, const std::string name, u8& target){
	if(j.contains(name)){
		int res = j[name].get<int>();
		target= (u8) res;
	}
}

void PrototypeClass::SetProto20(const nlohmann::json& j){
	if(j.contains("ai")){
		this->AI_v.clear();
		this->AI_v = j["ai"].get<std::vector<int>>();
	}

	jsonReadString(j, "ammo1", this->ammo1_sprite);


	jsonReadString(j, "ammo2", this->ammo2_sprite);

	if(j.contains("animations")){
		const nlohmann::json& j_animations = j["animations"]; 
		for(std::pair<std::string, int> p: jsonAnimationsMap){
			if(j_animations.contains(p.first)){
				this->animations[p.second] = j_animations[p.first].get<SpriteAnimation>();
			}
		}
	}

	jsonReadBool(j, "always_active", this->always_active);

	jsonReadInt(j, "attack1_time", this->attack1_time);

	jsonReadInt(j, "attack2_time", this->attack2_time);

	jsonReadBool(j, "bonus_always", this->bonus_always);

	jsonReadString(j, "bonus", this->bonus_sprite);

	jsonReadInt(j, "bonuses_number", this->bonuses_number);

	jsonReadBool(j, "boss", this->boss);

	jsonReadBool(j, "can_glide", this->can_glide);

	jsonReadBool(j, "can_open_locks", this->can_open_locks);

	jsonReadBool(j, "can_swim", this->can_swim);

	jsonReadInt(j, "charge_time", this->charge_time);

	jsonReadEnumU8(j, "color", this->color);

	jsonReadInt(j, "damage", this->damage);

	jsonReadInt(j, "damage_type", this->damage_type);

	jsonReadEnumU8(j, "effect", this->effect);

	jsonReadBool(j, "enemy", this->enemy);

	jsonReadInt(j, "energy", this->energy);

	if(j.contains("frame")){
		const nlohmann::json& j_frame = j["frame"];
		this->picture_frame_x = j_frame["pos_x"].get<int>();
		this->picture_frame_y = j_frame["pos_y"].get<int>();
		this->picture_frame_width  = j_frame["width"].get<int>();
		this->picture_frame_height = j_frame["height"].get<int>();
	}

	jsonReadInt(j, "frame_rate", this->frame_rate);

	jsonReadInt(j, "frames_number", this->frames_number);

	jsonReadInt(j, "how_destroyed", this->how_destroyed);

	jsonReadInt(j, "immunity_type", this->immunity_type);

	jsonReadBool(j, "is_transparent", this->is_transparent);

	jsonReadBool(j, "is_wall", this->is_wall);

	jsonReadBool(j, "is_wall_down", this->is_wall_down);

	jsonReadBool(j, "is_wall_left", this->is_wall_left);

	jsonReadBool(j, "is_wall_right", this->is_wall_right);

	jsonReadBool(j, "is_wall_up", this->is_wall_up);

	jsonReadBool(j, "makes_sounds", this->makes_sounds);

	jsonReadInt(j, "max_jump", this->max_jump);

	jsonReadDouble(j, "max_speed", this->max_speed);

	jsonReadString(j, "name", this->name);

	jsonReadInt(j, "parallax_type", this->parallax_type);

	jsonReadString(j, "picture", this->picture_filename);

	jsonReadInt(j, "projectile_charge_time", this->projectile_charge_time);

	jsonReadBool(j, "random_sound_frequency", this->random_sound_frequency);

	jsonReadInt(j, "score", this->score);

	if(j.contains("size")){
		const nlohmann::json& size = j["size"];
		this->width = size["width"].get<int>();
		this->height = size["height"].get<int>();
	}

	jsonReadInt(j, "sound_frequency", this->sound_frequency);

	if(j.contains("sounds")){
		const nlohmann::json& j_sounds = j["sounds"];
		for(std::pair<std::string, int> p: jsonSoundsMap){
			this->sounds[p.second] = -1;
			jsonReadString(j_sounds, p.first, this->sound_files[p.second]);
		}
	}

	jsonReadString(j, "transformation", this->transformation_sprite);

	jsonReadInt(j, "type", this->type);

	jsonReadBool(j, "vibrates", this->vibrates);

	jsonReadDouble(j, "weight", this->weight);
}

int PrototypeClass::Load(const std::string& path, bool legacy_spr){

	if(legacy_spr){
		std::ifstream file(path, std::ios::binary|std::ios::in);

		char versio[4];
		file.read(versio, 4);

		//Not used versions

		/*if (strcmp(versio,"1.0") == 0){
			PrototypeClass10 proto;
			file.read(reinterpret_cast<char*>(&proto), sizeof(proto));
			this->SetProto10(proto);
		}
		else if (strcmp(versio,"1.1") == 0){
			PrototypeClass11 proto;
			file.read(reinterpret_cast<char*>(&proto), sizeof(proto));
			this->SetProto11(proto);
		}
		else 
		if (strcmp(versio,"1.2") == 0){
			PrototypeClass12 proto;
			file.read(reinterpret_cast<char*>(&proto), sizeof(proto));
			this->SetProto12(proto);
		}
		else */
		
		if (strcmp(versio,"1.3") == 0){
			PrototypeClass13 proto;
			file.read(reinterpret_cast<char*>(&proto), sizeof(proto));
			this->SetProto13(proto);
		}
		else {
			throw PK2SpriteBadFormatException();
		}

		/**
		 * @brief 
		 * Update dependecies to the new format.
		 */
		if(!this->ammo1_sprite.empty()){
			this->ammo1_sprite += "2";
		}
		if(!this->ammo2_sprite.empty()){
			this->ammo2_sprite += "2";
		}
		if(!this->bonus_sprite.empty()){
			this->bonus_sprite += "2";
		}
		if(!this->transformation_sprite.empty()){
			this->transformation_sprite += "2";
		}

		this->version = versio;
		file.close();
	}
	else{
		std::ifstream file(path);
		const nlohmann::json proto = nlohmann::json::parse(file);

		if(!proto.contains("version") || !proto["version"].is_string()){
			std::cerr<<"Incorrect JSON, no string \"version\" field"<<std::endl;
			return -1;
		}
		std::string version = proto["version"].get<std::string>();
		if(version==current_json_sprite_version){
			this->SetProto20(proto);
		}
		else{
			throw PK2SpriteBadFormatException();
		}
	}

	if(this->frames_number>0){
		this->frames.resize(this->frames_number);
		this->frames_mirror.resize(this->frames_number);
	}
	return 0;
}

bool PrototypeClass::HasAI(int ai)const{
	return std::find(this->AI_v.begin(), this->AI_v.end(), ai) != this->AI_v.end();
}


void to_json(nlohmann::json& j, const PrototypeClass& c){
	using json = nlohmann::json;

    j["version"] = current_json_sprite_version;

    j["type"] = c.type;
    j["picture"] = c.picture_filename;

    json sounds;
    for(const std::pair<std::string, int> &p: jsonSoundsMap){
        sounds[p.first] = c.sound_files[p.second];        
    }

    j["sounds"] = sounds;
    j["frames_number"] = c.frames_number;
    j["frame_rate"] = c.frame_rate;

    json animations;
    for(const std::pair<std::string, int>&p :jsonAnimationsMap){
        animations[p.first] = c.animations[p.second];
    }

    j["animations"] = animations;


    json frame;
    frame["pos_x"] = c.picture_frame_x;
    frame["pos_y"] = c.picture_frame_y;
    frame["width"] = c.picture_frame_width;
    frame["height"] = c.picture_frame_height;

    j["frame"] = frame;

    j["name"] = c.name;
    json size;
	size["width"]  = c.width;
	size["height"] = c.height;

	j["size"] = size;
    j["weight"] = c.weight;
    j["enemy"] = c.enemy;
    j["energy"] = c.energy;
    j["damage"] = c.damage;
    j["damage_type"] = c.damage_type;
    j["immunity_type"] = c.immunity_type;
    j["score"] = c.score;

    j["ai"] = c.AI_v;
    j["max_jump"] = c.max_jump;
    j["max_speed"] = c.max_speed;
    j["charge_time"] = c.charge_time;

	j["color"] = c.color;

	for(const std::pair<std::string, u8>& p:jsonColorsMap){
		if(p.second==c.color){
			j["color"] = p.first;
			break;
		}
	}

    j["is_wall"] = c.is_wall;
    j["how_destroyed"] = c.how_destroyed;
    j["can_open_locks"] = c.can_open_locks;
    j["vibrates"] = c.vibrates;
    j["bonuses_number"] = c.bonuses_number;
    j["attack1_time"] = c.attack1_time;
    j["attack2_time"] = c.attack2_time;
    j["parallax_type"] = c.parallax_type;
    j["transformation"] = c.transformation_sprite;
    j["bonus"] = c.bonus_sprite;
    j["ammo1"] = c.ammo1_sprite;
    j["ammo2"] = c.ammo2_sprite;
    j["makes_sounds"] = c.makes_sounds;
    j["sound_frequency"] = c.sound_frequency;
    j["random_sound_frequency"] = c.random_sound_frequency;
    j["is_wall_up"] = c.is_wall_up;
    j["is_wall_down"] = c.is_wall_down;
    j["is_wall_right"] = c.is_wall_right;
    j["is_wall_left"] = c.is_wall_left;

    j["effect"] = c.effect;
    j["is_transparent"] = c.is_transparent;

    j["projectile_charge_time"] = c.projectile_charge_time;

    j["can_glide"] = c.can_glide;
    j["boss"] = c.boss;
    j["bonus_always"] = c.bonus_always;
    j["can_swim"] = c.can_swim;

	j["always_active"] = c.always_active;
}

}