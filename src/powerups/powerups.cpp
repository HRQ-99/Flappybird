#include "powerups.h"

using namespace godot;

PowerUps::PowerUps() { initialise_static_members(); }

void PowerUps::initialise_static_members()
{
  powerups_scenes_path [SPEED_BOOST] = "uid://cgxa8yeutalpu";
  powerups_scenes_path [SCORE_BOOST] = "uid://5e1h0515ot2h";
  //  powerups_scenes_path [SHIELD] = "";
  //  powerups_scenes_path [PIPE_DESTROYER] = "";
  //  powerups_scenes_path [POWER_UP_SPAWN_BOOST] = "";

  powerups_enum_array.append(SPEED_BOOST);
  powerups_enum_array.append(SCORE_BOOST);
}

String PowerUps::get_random_powerup()
{
  int count = powerups_enum_array.size() - 1;
  int chosen_powerup_index = call("randi_range", 0, count);
  return powerups_scenes_path [powerups_enum_array [chosen_powerup_index]];

  return "";
}

void PowerUps::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("initialise_static_members"), &PowerUps::initialise_static_members);
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
  // BIND_ENUM_CONSTANT(PIPE_DESTROYER);
  // BIND_ENUM_CONSTANT(POWER_UP_SPAWN_BOOST);
}

void PowerUps::set_powerups_enum_array(godot::Array enum_array) { powerups_enum_array = enum_array; }
Array PowerUps::get_powerups_enum_array() const { return powerups_enum_array; }

void PowerUps::set_powerups_scenes_path(godot::Dictionary scenes_path) { powerups_scenes_path = scenes_path; }
Dictionary PowerUps::get_powerups_scenes_path() const { return powerups_scenes_path; }
