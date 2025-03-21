#pragma once

#include <godot_cpp/classes/node2d.hpp>

using namespace godot;

class Level : public Node2D
{
  GDCLASS(Level, Node2D)

 public:
  Level();
  ~Level();

  virtual void _ready() override;
  virtual void _process(double delta) override;
  virtual void _input();

  void set_game_paused_state(bool game_paused);
  bool get_game_paused_state() const;

  void set_game_score(float score);
  bool get_game_score() const;

  void set_pipes_container(Node2D* pipes_container);
  Node2D* get_pipes_container();

 private:
  bool m_game_paused = false;
  float m_score = 0;
  Node2D* m_pipes_container;
  float m_next_pipe_location = 450;
  const float move_pipe_distance = 800;

  const int max_pipes = 5;

  virtual Node2D* make_pipe_pair();

 protected:
  static void _bind_methods();
};
