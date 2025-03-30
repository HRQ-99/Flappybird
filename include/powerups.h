#pragma once

#include "godot_cpp/classes/resource.hpp"

class PowerUps : public godot::Resource
{
  GDCLASS(PowerUps, godot::Resource)

 public:
  PowerUps();

  enum PowerupsEnum
  {
    SPEED_BOOST,
    SCORE_BOOST,
    // PIPE_DESTROYER,
    // POWER_UP_SPAWN_BOOST,
    // SHIELD,
    //  GUIDE,
  };

  godot::Array powerups_enum_array;

  godot::Dictionary powerups_scenes_path;

  godot::String get_random_powerup();

  void set_powerups_enum_array(godot::Array enum_array);
  godot::Array get_powerups_enum_array() const;

  void set_powerups_scenes_path(godot::Dictionary scenes_path);
  godot::Dictionary get_powerups_scenes_path() const;

 private:
  void initialise_static_members();

 protected:
  static void _bind_methods();
};
VARIANT_ENUM_CAST(PowerUps::PowerupsEnum);
