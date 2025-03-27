#pragma once

#include "godot_cpp/classes/resource.hpp"

class SaveGame : public godot::Resource
{
  GDCLASS(SaveGame, godot::Resource)

 public:
  godot::Array attempt_number;
  godot::Array game_score;

  inline static godot::String SAVE_DIRE = "user://user_save.tres";
};
