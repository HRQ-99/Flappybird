#pragma once

#include "godot_cpp/classes/resource.hpp"

class SaveGame : public godot::Resource
{
  GDCLASS(SaveGame, godot::Resource)

 public:
  godot::String SAVE_DIRE = "user://savegame.tres";

  void save_game(float game_score);

 private:
  godot::Array m_attempt_number;
  godot::Array m_game_score;

  // void set_attempt_number(int attempt_number);
  // int get_attempt_number();
  //
  // void set_game_score(int game_score);
  // int get_game_score();

  void set_attempt_number(const godot::Array &value);
  godot::Array get_attempt_number() const;

  void set_game_score(const godot::Array &value);
  godot::Array get_game_score() const;

 protected:
  static void _bind_methods();
};
