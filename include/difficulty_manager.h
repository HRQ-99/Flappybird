#pragma once

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/timer.hpp"

class DifficultyManager : public godot::Node
{
  GDCLASS(DifficultyManager, godot::Node);

 public:
  enum DifficultyStage
  {
    Stage0,
    Stage1,
    Stage2,
    Stage3,
    Stage4,
    Stage5,
  };

  godot::Signal change_bird_difficulty;
  godot::Signal change_level_difficulty;

  DifficultyManager();
  void initialise_members();
  void _ready() override;

  void increase_difficulty_stage();
  DifficultyStage get_current_stage() const;
  void set_current_stage(const int stage_index);

  void set_difficulty_thresholds(const godot::PackedFloat32Array thresholds);
  godot::PackedFloat32Array get_difficulty_thresholds() const;

 private:
  godot::Array m_stages_array;
  int m_stage_index = 0;
  godot::Timer* m_difficulty_timer = nullptr;
  godot::PackedFloat32Array m_difficulty_thresholds = [] {
    godot::PackedFloat32Array arr;
    arr.append(50.0f);
    arr.append(60.0f);
    arr.append(90.0f);
    arr.append(100.0f);
    arr.append(200.0f);
    arr.append(700.0f);
    return arr;
  }();

 protected:
  static void _bind_methods();
};
VARIANT_ENUM_CAST(DifficultyManager::DifficultyStage);
