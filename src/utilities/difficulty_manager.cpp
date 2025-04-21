#include "difficulty_manager.h"

using namespace godot;

DifficultyManager::DifficultyManager() { initialise_members(); }

void DifficultyManager::initialise_members()
{
  m_stages_array.append(Stage0);
  m_stages_array.append(Stage1);
  m_stages_array.append(Stage2);
  m_stages_array.append(Stage3);
  m_stages_array.append(Stage4);
  m_stages_array.append(Stage5);
}

void DifficultyManager::_ready()
{
  m_difficulty_timer = get_node<Timer>("DifficultyTimer");
  m_difficulty_timer->set_wait_time(m_difficulty_thresholds [m_stage_index]);
}

void DifficultyManager::increase_difficulty_stage()
{
  if (m_stage_index < 5)
  {
    m_stage_index++;
  }
  m_difficulty_timer->set_wait_time(m_difficulty_thresholds [m_stage_index]);

  emit_signal("change_bird_difficulty", m_stages_array [m_stage_index]);
  emit_signal("change_level_difficulty", m_stages_array [m_stage_index]);
}

void DifficultyManager::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("increase_difficulty_stage"), &DifficultyManager::increase_difficulty_stage);

  ClassDB::bind_method(D_METHOD("get_current_stage"), &DifficultyManager::get_current_stage);
  ClassDB::bind_method(D_METHOD("set_current_stage", "stage_index"), &DifficultyManager::set_current_stage);
  ADD_PROPERTY(
    PropertyInfo(Variant::INT, "current_stage", PROPERTY_HINT_ENUM, "Stage0, Stage1, Stage2, Stage3, Stage4, Stage5"),
    "set_current_stage", "get_current_stage");

  ClassDB::bind_method(D_METHOD("get_difficulty_thresholds"), &DifficultyManager::get_difficulty_thresholds);
  ClassDB::bind_method(D_METHOD("set_difficulty_thresholds", "thresholds"),
                       &DifficultyManager::set_difficulty_thresholds);
  ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "difficulty_thresholds"), "set_difficulty_thresholds",
               "get_difficulty_thresholds");

  ADD_SIGNAL(MethodInfo("change_bird_difficulty", PropertyInfo(Variant::INT, "difficulty_stage", PROPERTY_HINT_ENUM,
                                                               "Stage0, Stage1, Stage2, Stage3, Stage4, Stage5")));

  ADD_SIGNAL(MethodInfo("change_level_difficulty", PropertyInfo(Variant::INT, "difficulty_stage", PROPERTY_HINT_ENUM,
                                                               "Stage0, Stage1, Stage2, Stage3, Stage4, Stage5")));
  BIND_ENUM_CONSTANT(Stage0);
  BIND_ENUM_CONSTANT(Stage1);
  BIND_ENUM_CONSTANT(Stage2);
  BIND_ENUM_CONSTANT(Stage3);
  BIND_ENUM_CONSTANT(Stage4);
  BIND_ENUM_CONSTANT(Stage5);
}

DifficultyManager::DifficultyStage DifficultyManager::get_current_stage() const
{
  return static_cast<DifficultyStage>(int(m_stages_array [m_stage_index]));
}
void DifficultyManager::set_current_stage(const int stage_index)
{
  m_stage_index = stage_index;

  emit_signal("change_bird_difficulty", m_stages_array [m_stage_index]);
  emit_signal("change_level_difficulty", m_stages_array [m_stage_index]);
}

void DifficultyManager::set_difficulty_thresholds(const PackedFloat32Array thresholds)
{
  m_difficulty_thresholds = thresholds;
}
PackedFloat32Array DifficultyManager::get_difficulty_thresholds() const { return m_difficulty_thresholds; }
