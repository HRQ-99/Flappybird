#include "powerups.h"

#include "godot_cpp/classes/random_number_generator.hpp"

using namespace godot;

PowerUps::PowerUps()
{
  initialise_members();
  rng = memnew(RandomNumberGenerator);
}

PowerUps::~PowerUps() { memdelete(rng); }

void PowerUps::initialise_members()
{
  powerups_scenes_path [SPEED_BOOST] = "uid://cgxa8yeutalpu";
  powerups_scenes_path [SCORE_BOOST] = "uid://5e1h0515ot2h";
  //  powerups_scenes_path [SHIELD] = "";
  powerups_scenes_path [PIPE_DESTROYER] = "uid://bxpo0kcteytsv";
  powerups_scenes_path [POWER_UP_SPAWN_BOOST] = "uid://coyndodm4v3l1";

  powerups_enum_array.append(SPEED_BOOST);
  powerups_enum_array.append(SCORE_BOOST);
  powerups_enum_array.append(PIPE_DESTROYER);
  powerups_enum_array.append(POWER_UP_SPAWN_BOOST);
}

String PowerUps::get_random_powerup()
{
  rng->randomize();
  int chosen_powerup_index = rng->randi_range(0, powerups_enum_array.size() - 1);
  return powerups_scenes_path [powerups_enum_array [chosen_powerup_index]];
}

void PowerUps::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("initialise_static_members"), &PowerUps::initialise_members);
  ClassDB::bind_method(D_METHOD("get_random_powerup"), &PowerUps::get_random_powerup);

  ClassDB::bind_method(D_METHOD("get_powerups_scenes_path"), &PowerUps::get_powerups_scenes_path);
  ClassDB::bind_method(D_METHOD("set_powerups_scenes_path", "scenes_path"), &PowerUps::set_powerups_scenes_path);
  ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "powerups_scenes_path"), "set_powerups_scenes_path",
               "get_powerups_scenes_path");

  ClassDB::bind_method(D_METHOD("get_powerups_enum_array"), &PowerUps::get_powerups_enum_array);
  ClassDB::bind_method(D_METHOD("set_powerups_enum_array", "enum_array"), &PowerUps::set_powerups_enum_array);
  ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "powerups_enum_array"), "set_powerups_enum_array",
               "get_powerups_enum_array");

  BIND_ENUM_CONSTANT(SPEED_BOOST);
  BIND_ENUM_CONSTANT(SCORE_BOOST);
  // BIND_ENUM_CONSTANT(SHIELD);
  BIND_ENUM_CONSTANT(PIPE_DESTROYER);
  BIND_ENUM_CONSTANT(POWER_UP_SPAWN_BOOST);
}

void PowerUps::set_powerups_enum_array(godot::Array enum_array) { powerups_enum_array = enum_array; }
Array PowerUps::get_powerups_enum_array() const { return powerups_enum_array; }

void PowerUps::set_powerups_scenes_path(godot::Dictionary scenes_path) { powerups_scenes_path = scenes_path; }
Dictionary PowerUps::get_powerups_scenes_path() const { return powerups_scenes_path; }
