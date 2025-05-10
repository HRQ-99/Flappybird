#pragma once

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/timer.hpp"
#include "godot_cpp/variant/dictionary.hpp"
#include "godot_cpp/variant/string.hpp"

class AchievementManager : public godot::Node
{
  GDCLASS(AchievementManager, godot::Node)

 public:
  void _ready() override;
  void _process(double delta) override;

  enum Achievements
  {
    SCORE_100,
    ADDICTED,
    BEETHOVEN,
    PIPE_HATER,
    POWERUPS_5,
    AFK,
    SPEEDSTER,
  };

  godot::Array achievements_enum_array = [] {
    godot::Array arr;
    arr.append(SCORE_100);
    arr.append(ADDICTED);
    arr.append(BEETHOVEN);
    arr.append(PIPE_HATER);
    arr.append(POWERUPS_5);
    arr.append(AFK);
    arr.append(SPEEDSTER);
    return arr;
  }();

  godot::Array get_achievements_enum_array();
  void set_achievements_enum_array(godot::Array enum_array);

  godot::Dictionary get_achievements_unlock_status();

 private:
  const godot::String group_of_level = "Level";
  const godot::String popup_scene_path = "uid://mbtl17frp3nx";
  godot::Dictionary m_achievements_unlock_status;

  const godot::String m_not_bethoven_signal_name = "not_beethoven";
  const godot::String m_restart_afk_signal_name = "restart_afk";

  godot::Dictionary achievements_paths = [] {
    godot::Dictionary dict;
    dict [SCORE_100] = "uid://5tiqrxgexltv";
    dict [ADDICTED] = "uid://t2r77785emd5";
    dict [BEETHOVEN] = "uid://c6gsw57y27n3b";
    dict [PIPE_HATER] = "uid://c7hi8ysnov1qc";
    dict [POWERUPS_5] = "uid://b34qpsdjfads5";
    dict [AFK] = "uid://dp15wbk7d0vm6";
    dict [SPEEDSTER] = "uid://200vv0qoqfxw";
    return dict;
  }();

  void unlock_achievement(Achievements achievement_resource_path);
  void create_popup(godot::Ref<godot::Resource> achievement);
  void check_level_achievements();

  void check_scoring_100();
  void check_addicted_attempt_100();
  void check_beethoven();
  void not_beethoven(godot::Timer* music_timer);
  void check_pipe_hater();
  void delay_check_pipe_hater();
  void check_powerups_5();
  void delay_check_powerups();
  void check_afk();
  void restart_afk(godot::Timer* afk_timer);
  void check_speedster();
  void delay_check_speedster();

 protected:
  static void _bind_methods();
};
VARIANT_ENUM_CAST(AchievementManager::Achievements);
