#pragma once

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/resource.hpp"

class AchievementManager : public godot::Node
{
  GDCLASS(AchievementManager, godot::Node)

 public:
  void _ready() override;
  void _process(double delta) override;

  enum Achievements
  {
    SCORE_100,
  };

  godot::Array achievements_enum_array = [] {
    godot::Array arr;
    arr.append(SCORE_100);
    return arr;
  }();

  godot::Array get_achievements_enum_array();
  void set_achievements_enum_array(godot::Array enum_array);

 private:
  const godot::String group_of_level = "Level";
  const godot::String popup_scene_path = "uid://mbtl17frp3nx";
  bool scored_100 = false;
  godot::Dictionary m_achievement_unlock_status;

  godot::Dictionary achievements_paths = [] {
    godot::Dictionary dict;
    dict [SCORE_100] = "uid://dnlwmgfi382ab";
    return dict;
  }();

  void unlock_achievement(Achievements achievement_resource_path);
  void create_popup(godot::Ref<godot::Resource> achievement);
  void check_level_achievements();

  void check_scoring_100();

 protected:
  static void _bind_methods();
};
VARIANT_ENUM_CAST(AchievementManager::Achievements);
