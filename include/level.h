#pragma once

#include "bird.h"
#include "godot_cpp/classes/node2d.hpp"
#include "powerups.h"

class Level : public godot::Node2D
{
  GDCLASS(Level, Node2D)

 public:
  void _ready() override;
  void _process(double delta) override;

  void bird_died();
  void destroy_pipe(godot::Node* last_collision);

  void change_level_difficulty(DifficultyManager::DifficultyStage stage);
  godot::PackedFloat32Array get_move_pipe_distance_array() const;
  void set_move_pipe_distance_array(const godot::PackedFloat32Array move_distance_array);

  void set_game_paused_state(bool game_paused);
  bool get_game_paused_state() const;

  void set_game_score(int score);
  int get_game_score() const;

  void set_pipe_distance(float pipe_distance);
  float get_pipe_distance() const;

  void set_pipes_passed(int pipes_passed);
  int get_pipes_passed() const;

  void set_pipes_destroyed(int pipes_destroyed);
  int get_pipes_destroyed() const;

 private:
  Bird* m_bird;
  PowerUps* m_powerups = nullptr;
  Node2D* m_pipes_container = nullptr;
  bool m_game_paused = false;
  int m_score = 0;
  float m_next_pipe_location = 450;
  float move_pipe_distance = 450;
  int m_pipes_passed = 0;
  int m_pipes_destroyed = 0;
  godot::PackedFloat32Array move_pipe_distance_array = [] {
    godot::PackedFloat32Array arr;
    arr.append(450);
    arr.append(435);
    arr.append(420);
    arr.append(400);
    arr.append(375);
    arr.append(350);

    return arr;
  }();

  const int max_pipes = 5;
  const godot::String end_screen_scene_path = "uid://kk7t04lsbu4m";

  void spawn_powerup();

 protected:
  static void _bind_methods();
};
