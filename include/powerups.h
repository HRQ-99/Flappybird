#pragma once

#include "godot_cpp/classes/random_number_generator.hpp"
#include "godot_cpp/classes/resource.hpp"

class PowerUps : public godot::Resource
{
  GDCLASS(PowerUps, godot::Resource)

 public:
  PowerUps();
  ~PowerUps();

  enum PowerupsEnum
  {
    SPEED_BOOST,
    SCORE_BOOST,
    PIPE_DESTROYER,
    POWER_UP_SPAWN_BOOST,
    SHIELD,
    //  GUIDE,
  };

  godot::Array powerups_enum_array = [] {
    godot::Array arr;
    arr.append(SPEED_BOOST);
    arr.append(SCORE_BOOST);
    arr.append(PIPE_DESTROYER);
    arr.append(POWER_UP_SPAWN_BOOST);
    arr.append(SHIELD);
    return arr;
  }();

  godot::Dictionary powerups_scenes_path = [] {
    godot::Dictionary dict;
    dict [SPEED_BOOST] = "uid://cgxa8yeutalpu";
    dict [SCORE_BOOST] = "uid://5e1h0515ot2h";
    dict [SHIELD] = "uid://c4diibrcpf0v5";
    dict [PIPE_DESTROYER] = "uid://bxpo0kcteytsv";
    dict [POWER_UP_SPAWN_BOOST] = "uid://coyndodm4v3l1";
    return dict;
  }();

  godot::String get_random_powerup();

  void set_powerups_enum_array(godot::Array enum_array);
  godot::Array get_powerups_enum_array() const;

  void set_powerups_scenes_path(godot::Dictionary scenes_path);
  godot::Dictionary get_powerups_scenes_path() const;

 private:
  godot::RandomNumberGenerator* rng;

 protected:
  static void _bind_methods();
};
VARIANT_ENUM_CAST(PowerUps::PowerupsEnum);
