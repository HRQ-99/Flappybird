#pragma once

#include "achievement_manager.h"
#include "godot_cpp/classes/resource.hpp"

class SaveGame : public godot::Resource
{
  GDCLASS(SaveGame, godot::Resource)

 public:
  const godot::String SAVE_DIRE = "user://savegame.tres";

  void save_game(float game_score);
  static godot::Dictionary initialising_achievements(AchievementManager *achievement_manager);
  static void achievement_unlocked(AchievementManager *achievement_manager,
                                   AchievementManager::Achievements achievement_enum);

  static bool check_attempt_100();

 private:
  godot::Array m_attempt_number;
  godot::Array m_game_score;
  godot::Dictionary m_achievements_unlock_status;

  void set_attempt_number(const godot::Array &value);
  godot::Array get_attempt_number() const;

  void set_game_score(const godot::Array &value);
  godot::Array get_game_score() const;

  void set_achievements_unlock_status(const godot::Dictionary &dict);
  godot::Dictionary get_achievements_unlock_status();

 protected:
  static void _bind_methods();
};
