#include "achievement_manager.h"

#include "bird.h"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/resource_saver.hpp"
#include "godot_cpp/classes/rich_text_label.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/scene_tree_timer.hpp"
#include "godot_cpp/classes/texture_rect.hpp"
#include "godot_cpp/classes/worker_thread_pool.hpp"
#include "level.h"
#include "save_game.h"

using namespace godot;

void AchievementManager::_ready()
{
  m_achievement_unlock_status = SaveGame::initialising_achievements(this);
  if (!m_achievement_unlock_status [BEETHOVEN])
  {
    check_beethoven();
  }
}

void AchievementManager::_process(double delta)
{
  if (has_user_signal(m_restart_afk_signal_name) && Input::get_singleton()->is_anything_pressed())
  {
    emit_signal(m_restart_afk_signal_name);
  }
}

void AchievementManager::unlock_achievement(Achievements achievement_enum)
{
  Ref<Resource> achievement = ResourceLoader::get_singleton()->load(achievements_paths [achievement_enum]);
  achievement->call("achieved");
  create_popup(achievement);
  SaveGame::achievement_unlocked(this, achievement_enum);
  m_achievement_unlock_status [achievement_enum] = true;
}

void AchievementManager::create_popup(Ref<Resource> achievement)
{
  Ref<PackedScene> packed_scene = ResourceLoader::get_singleton()->load(popup_scene_path);
  Node* popup = packed_scene->instantiate();
  popup->get_node<TextureRect>("Split/Texture")->set_texture(achievement->get("sprite"));
  popup->get_node<RichTextLabel>("Split/UnlockText")->set_text("You have unlocked " + String(achievement->get("name")));
  add_child(popup);
}

void AchievementManager::check_level_achievements()
{
  if (!m_achievement_unlock_status [SCORE_100])
  {
    get_tree()->create_timer(40)->connect("timeout", Callable(this, "check_scoring_100"));
  }
  if (!m_achievement_unlock_status [ADDICTED])
  {
    check_addicted_attempt_100();
  }
  if (!m_achievement_unlock_status [PIPE_HATER])
  {
    get_tree()->create_timer(80)->connect("timeout", Callable(this, "check_pipe_hater"));
  }
  if (!m_achievement_unlock_status [POWERUPS_5])
  {
    check_powerups_5();
  }
  if (!m_achievement_unlock_status [AFK])
  {
    check_afk();
  }
  if (!m_achievement_unlock_status [SPEEDSTER])
  {
    check_speedster();
  }

  if (!m_achievement_unlock_status [BEETHOVEN] && has_user_signal(m_not_bethoven_signal_name))
  {
    emit_signal(m_not_bethoven_signal_name);
  }
}

void AchievementManager::check_scoring_100()
{
  Timer* score_100_timer = memnew(Timer);
  score_100_timer->set_wait_time(100);
  score_100_timer->set_one_shot(true);
  get_tree()->get_first_node_in_group(group_of_level)->add_child(score_100_timer);
  score_100_timer->connect("timeout", Callable(this, "unlock_achievement").bind(SCORE_100));
  score_100_timer->start();
}

void AchievementManager::check_addicted_attempt_100()
{
  if (SaveGame::check_attempt_100())
  {
    unlock_achievement(ADDICTED);
  }
}

void AchievementManager::check_beethoven()
{
  add_user_signal(m_not_bethoven_signal_name);

  Timer* music_30_minute = memnew(Timer);
  music_30_minute->set_wait_time(1800);
  music_30_minute->set_one_shot(true);
  music_30_minute->set_autostart(true);
  get_parent()->call_deferred("add_child", music_30_minute);
  music_30_minute->connect("timeout", Callable(this, "unlock_achievement").bind(BEETHOVEN));
  connect(m_not_bethoven_signal_name, Callable(this, m_not_bethoven_signal_name).bind(music_30_minute));
}

void AchievementManager::not_beethoven(Timer* music_timer) { music_timer->set_paused(true); }

void AchievementManager::check_pipe_hater()
{
  Level* level = Object::cast_to<Level>(get_tree()->get_first_node_in_group("Level"));
  if (level->get_pipes_destroyed() >= 2)
  {
    unlock_achievement(PIPE_HATER);
    return;
  }
  call_deferred("delay_check_pipe_hater");
}

void AchievementManager::delay_check_pipe_hater()
{
  get_tree()->create_timer(0.5)->connect("timeout", Callable(this, "check_pipe_hater"));
}

void AchievementManager::check_powerups_5()
{
  if (get_tree()->get_node_count_in_group("ActivatedPowerUp") >= 5)
  {
    unlock_achievement(POWERUPS_5);
    return;
  }
  call_deferred("delay_check_powerups");
}

void AchievementManager::delay_check_powerups()
{
  get_tree()->create_timer(0.5)->connect("timeout", Callable(this, "check_powerups_5"));
}

void AchievementManager::check_afk()
{
  add_user_signal(m_restart_afk_signal_name);

  Timer* afk_timer = memnew(Timer);
  afk_timer->set_wait_time(5);
  afk_timer->set_one_shot(true);
  afk_timer->set_autostart(true);
  get_parent()->call_deferred("add_child", afk_timer);
  afk_timer->connect("timeout", Callable(this, "unlock_achievement").bind(AFK));
  connect(m_restart_afk_signal_name, Callable(this, m_restart_afk_signal_name).bind(afk_timer));
}

void AchievementManager::restart_afk(Timer* afk_timer) { afk_timer->start(); }

void AchievementManager::check_speedster()
{
  Bird* bird = Object::cast_to<Bird>(get_tree()->get_first_node_in_group("Bird"));
  if (bird->get_final_speed() >= 1600)
  {
    unlock_achievement(SPEEDSTER);
    return;
  }
  call_deferred("delay_check_speedster");
}

void AchievementManager::delay_check_speedster()
{
  get_tree()->create_timer(0.5)->connect("timeout", Callable(this, "check_speedster"));
}

void AchievementManager::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_achievements_enum_array"), &AchievementManager::get_achievements_enum_array);
  ClassDB::bind_method(D_METHOD("set_achievements_enum_array", "enum_array"),
                       &AchievementManager::set_achievements_enum_array);
  ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "achievements_enum_array"), "set_achievements_enum_array",
               "get_achievements_enum_array");

  ClassDB::bind_method(D_METHOD("unlock_achievement", "achievement_resource_path"),
                       &AchievementManager::unlock_achievement);
  ClassDB::bind_method(D_METHOD("create_popup", "achievement"), &AchievementManager::create_popup);
  ClassDB::bind_method(D_METHOD("check_level_achievements"), &AchievementManager::check_level_achievements);

  // ClassDB::bind_method(D_METHOD("check_scoring_100"), &AchievementManager::check_scoring_100);
  // ClassDB::bind_method(D_METHOD("check_addicted_attempt_100"), &AchievementManager::check_addicted_attempt_100);
  //  ClassDB::bind_method(D_METHOD("check_beethoven"), &AchievementManager::check_beethoven);
  ClassDB::bind_method(D_METHOD("check_pipe_hater"), &AchievementManager::check_pipe_hater);
  ClassDB::bind_method(D_METHOD("delay_check_pipe_hater"), &AchievementManager::delay_check_pipe_hater);
  ClassDB::bind_method(D_METHOD("not_beethoven"), &AchievementManager::not_beethoven);
  ClassDB::bind_method(D_METHOD("check_powerups_5"), &AchievementManager::check_powerups_5);
  ClassDB::bind_method(D_METHOD("delay_check_powerups"), &AchievementManager::delay_check_powerups);
  ClassDB::bind_method(D_METHOD("restart_afk"), &AchievementManager::restart_afk);
  ClassDB::bind_method(D_METHOD("check_speedster"), &AchievementManager::check_speedster);
  ClassDB::bind_method(D_METHOD("delay_check_speedster"), &AchievementManager::delay_check_speedster);

  BIND_ENUM_CONSTANT(SCORE_100);
  BIND_ENUM_CONSTANT(ADDICTED);
  BIND_ENUM_CONSTANT(BEETHOVEN);
  BIND_ENUM_CONSTANT(PIPE_HATER);
  BIND_ENUM_CONSTANT(POWERUPS_5);
  BIND_ENUM_CONSTANT(AFK);
  BIND_ENUM_CONSTANT(SPEEDSTER);
}

Array AchievementManager::get_achievements_enum_array() { return achievements_enum_array; }
void AchievementManager::set_achievements_enum_array(godot::Array enum_array) { achievements_enum_array = enum_array; }
