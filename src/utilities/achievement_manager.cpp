#include "achievement_manager.h"

#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/resource_saver.hpp"
#include "godot_cpp/classes/rich_text_label.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/texture_rect.hpp"
#include "godot_cpp/classes/timer.hpp"
#include "save_game.h"

using namespace godot;

void AchievementManager::_ready() { m_achievement_unlock_status = SaveGame::initialising_achievements(this); }

void AchievementManager::_process(double delta) {}

void AchievementManager::unlock_achievement(Achievements achievement_enum)
{
  Ref<Resource> achievement = ResourceLoader::get_singleton()->load(achievements_paths [achievement_enum]);
  achievement->call("achieved");
  create_popup(achievement);
  ResourceSaver::get_singleton()->save(achievement);
  SaveGame::achievement_unlocked(this, achievement_enum);
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
  if (!scored_100)
  {
    check_scoring_100();
  }
}

void AchievementManager::check_scoring_100()
{
  Timer* score_100_timer = memnew(Timer);
  score_100_timer->set_wait_time(5);
  score_100_timer->set_one_shot(true);
  get_tree()->get_first_node_in_group(group_of_level)->add_child(score_100_timer);
  score_100_timer->connect("timeout", Callable(this, "unlock_achievement").bind(SCORE_100));
  score_100_timer->start();
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

  ClassDB::bind_method(D_METHOD("check_scoring_100"), &AchievementManager::check_scoring_100);

  BIND_ENUM_CONSTANT(SCORE_100);
}

Array AchievementManager::get_achievements_enum_array() { return achievements_enum_array; }
void AchievementManager::set_achievements_enum_array(godot::Array enum_array) { achievements_enum_array = enum_array; }
