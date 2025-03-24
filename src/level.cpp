#include "level.h"

#include "bird.h"
#include "godot_cpp/classes/canvas_layer.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/rich_text_label.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;

void Level::_ready()
{
  m_game_paused = false;
  m_score = 0;
  m_pipes_container = memnew(Node2D);
  m_pipes_container->set_name("Pipes Container");
  add_child(m_pipes_container);

  for (int i = 0; i < max_pipes; i++)
  {
    Node2D* pipe_pair = Object::cast_to<Node2D>(call("make_pipe_pair"));
    if (pipe_pair)
    {
      m_pipes_container->add_child(pipe_pair);
      pipe_pair->move_local_x(m_next_pipe_location);
      m_next_pipe_location += move_pipe_distance;
    }
  }
}

void Level::_process(double delta)
{
  Node2D* first_pipe_pair = Object::cast_to<Node2D>(m_pipes_container->get_children() [0]);
  float location_x_first_pipe_pair = first_pipe_pair->get_global_position() [0];
  if (get_node<Bird>("Bird")->get_global_position() [0] - location_x_first_pipe_pair > 1000)
  {
    first_pipe_pair->queue_free();

    Node2D* pipe_pair = Object::cast_to<Node2D>(call("make_pipe_pair"));
    if (pipe_pair)
    {
      m_pipes_container->add_child(pipe_pair);
      pipe_pair->move_local_x(m_next_pipe_location);
      m_next_pipe_location += move_pipe_distance;
    }
  }
}

void Level::_input()
{
  Input* input = Input::get_singleton();
  if (input->is_action_just_pressed("Escape"))
  {
    set_game_paused_state(!m_game_paused);
  }

  if (input->is_action_just_pressed("Godmode"))
  {
    Bird* _bird = Object::cast_to<Bird>(get_node<Node2D>("Bird"));
    bool invincible = !(_bird->get_invincibility());
    _bird->set_invincibility(invincible);
    get_node<RichTextLabel>("Level-UI/HBox/Godmode")->set_visible(invincible);
  }
}

void Level::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_game_paused_state"), &Level::get_game_paused_state);
  ClassDB::bind_method(D_METHOD("set_game_paused_state", "game_paused"), &Level::set_game_paused_state);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "game_paused"), "set_game_paused_state", "get_game_paused_state");

  ClassDB::bind_method(D_METHOD("get_game_score"), &Level::get_game_score);
  ClassDB::bind_method(D_METHOD("set_game_score", "score"), &Level::set_game_score);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "score"), "set_game_score", "get_game_score");

  ClassDB::bind_method(D_METHOD("get_pipe_distance"), &Level::get_pipe_distance);
  ClassDB::bind_method(D_METHOD("set_pipe_distance", "pipe_distance"), &Level::set_pipe_distance);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "pipe_distance"), "set_pipe_distance", "get_pipe_distance");
}

void Level::set_game_paused_state(bool game_paused)
{
  m_game_paused = game_paused;
  get_tree()->set_pause(game_paused);
  get_node<CanvasLayer>("Pause Screen")->set_visible(m_game_paused);
}
bool Level::get_game_paused_state() const { return m_game_paused; }

void Level::set_game_score(int score) { m_score = score; }
int Level::get_game_score() const { return m_score; }

void Level::set_pipe_distance(float pipe_distance) { move_pipe_distance = pipe_distance; }
float Level::get_pipe_distance() const { return move_pipe_distance; }
