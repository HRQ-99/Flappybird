#include "level.h"

#include "bird.h"
#include "godot_cpp/classes/canvas_layer.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/rich_text_label.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "powerups.h"

using namespace godot;

Level::~Level()
{
  // memdelete(m_powerups);
  // memdelete(m_pipes_container);
  // memdelete(m_powerups_container);
}

void Level::_ready()
{
  m_bird = get_node<Bird>("Bird");
  m_game_paused = false;
  m_score = 0;

  m_pipes_container = memnew(Node2D);
  m_pipes_container->set_name("Pipes Container");
  add_child(m_pipes_container);

  m_powerups = memnew(PowerUps);

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
  Node2D* first_pipe_pair = Object::cast_to<Node2D>(m_pipes_container->get_child(0));
  float location_x_first_pipe_pair = first_pipe_pair->get_global_position() [0];
  if (m_bird->get_global_position() [0] - location_x_first_pipe_pair > 1000)
  {
    first_pipe_pair->queue_free();

    Node2D* pipe_pair = Object::cast_to<Node2D>(call("make_pipe_pair"));
    if (pipe_pair != nullptr)
    {
      m_pipes_container->add_child(pipe_pair);
      pipe_pair->move_local_x(m_next_pipe_location);
      m_next_pipe_location += move_pipe_distance;
    }
  }
}

void Level::spawn_powerup()
{
  const Vector2 powerup_scale = Vector2(0.1, 0.1);
  const Vector2 powerup_position = Vector2(m_next_pipe_location + (move_pipe_distance / 2), 130);

  String scene_path = m_powerups->get_random_powerup();

  Ref<PackedScene> scene = ResourceLoader::get_singleton()->load(scene_path);
  Node* powerup = scene->instantiate();
  Object::cast_to<Node2D>(powerup)->apply_scale(powerup_scale);
  Object::cast_to<Node2D>(powerup)->set_position(powerup_position);
  add_child(powerup);
}

void Level::bird_died()
{
  set_game_paused_state(true);
  Ref<PackedScene> end_screen_scene = ResourceLoader::get_singleton()->load(end_screen_scene_path);
  Node* end_screen = end_screen_scene->instantiate();
  end_screen->get_node<RichTextLabel>("Margin/VBox/ScoreLabel")->set_text("Score:" + String::num_int64(m_score));
  add_child(end_screen);
}

void Level::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("spawn_powerup"), &Level::spawn_powerup);
  ClassDB::bind_method(D_METHOD("bird_died"), &Level::bird_died);

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
