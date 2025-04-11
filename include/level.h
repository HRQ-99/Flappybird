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
  void set_game_paused_state(bool game_paused);
  bool get_game_paused_state() const;

  void set_game_score(int score);
  int get_game_score() const;

  void set_pipe_distance(float pipe_distance);
  float get_pipe_distance() const;

 private:
  Bird* m_bird;
  PowerUps* m_powerups = nullptr;
  Node2D* m_pipes_container = nullptr;
  bool m_game_paused = false;
  int m_score = 0;
  float m_next_pipe_location = 450;
  float move_pipe_distance = 450;

  const int max_pipes = 5;
  const godot::String end_screen_scene_path = "uid://kk7t04lsbu4m";

  ~Level();
  void spawn_powerup();

 protected:
  static void _bind_methods();
};
