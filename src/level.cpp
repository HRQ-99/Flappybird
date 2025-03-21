#include "level.h"

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/core/print_string.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "godot_cpp/classes/canvas_layer.hpp"
#include "godot_cpp/classes/input.hpp"

Level::Level() {}

Level::~Level() {}

void Level::_ready()
{
  m_game_paused = false;
  m_score = 0;
  m_pipes_container = memnew(Node2D);
  m_pipes_container->set_name("Pipes Container");
  this->add_child(m_pipes_container);

  for (int i = 0; i < max_pipes; i++)
  {
    Node2D* pipe_pair = Object::cast_to<Node2D>(call("make_pipe_pair"));
    if (pipe_pair)
    {
      m_pipes_container->add_child(pipe_pair);
      pipe_pair->move_local_x(m_next_pipe_location);
      m_next_pipe_location += move_pipe_distance;
      print_line(m_next_pipe_location);
    }
  }
}

void Level::_process(double delta) {}

void Level::_input()
{
  Input* input = Input::get_singleton();
  if (input->is_action_just_pressed("Escape"))
  {
    m_game_paused = !m_game_paused;
    this->set_game_paused_state(m_game_paused);
    this->get_node<CanvasLayer>("Pause Screen")->set_visible(!m_game_paused);
  }
}

// overridden in gdscript
Node2D* Level::make_pipe_pair() { return nullptr; }

void Level::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("make_pipe_pair"), &Level::make_pipe_pair);

  ClassDB::bind_method(D_METHOD("get_game_paused_state"), &Level::get_game_paused_state);
  ClassDB::bind_method(D_METHOD("set_game_paused_state", "game_paused"), &Level::set_game_paused_state);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "game_paused"), "set_game_paused_state", "get_game_paused_state");

  ClassDB::bind_method(D_METHOD("get_game_score"), &Level::get_game_score);
  ClassDB::bind_method(D_METHOD("set_game_score", "score"), &Level::set_game_score);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score"), "set_game_score", "get_game_score");

  ClassDB::bind_method(D_METHOD("get_pipes_container"), &Level::get_pipes_container);
  ClassDB::bind_method(D_METHOD("set_pipes_container", "pipes_container"), &Level::set_pipes_container);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "pipes_container", PROPERTY_HINT_RESOURCE_TYPE, "Node2D"),
               "set_pipes_container", "get_pipes_container");
}

void Level::set_game_paused_state(bool game_paused) { m_game_paused = game_paused; }
bool Level::get_game_paused_state() const { return m_game_paused; }

void Level::set_game_score(float score) {}
bool Level::get_game_score() const { return m_game_paused; }

void Level::set_pipes_container(Node2D* pipes_container) { m_pipes_container = pipes_container; }
Node2D* Level::get_pipes_container() { return m_pipes_container; }
