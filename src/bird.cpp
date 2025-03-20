#include "bird.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/print_string.hpp>

void Bird::_ready()
{
  m_bird = this;
  m_invincible = false;
  // make it equal to value from difficulty manager
  Bird::set_speed(150);
  m_gravity_multiplier = 1;
}

void Bird::_physics_process(double delta)
{
  Input *input = Input::get_singleton();

  if (input->is_action_just_pressed("Flap"))
  {
    set_velocity(Vector2(m_speed, m_flyspeed));
  }
  else if (input->is_action_just_pressed("Dive"))
  {
    set_velocity(Vector2(m_speed, m_fallspeed * m_dive_multiplier));
  }
  else
  {
    set_velocity(Vector2(m_speed, m_fallspeed * m_gravity_multiplier));
  }

  move_and_slide();

  int collision_count = m_bird->get_slide_collision_count();

  if (!m_invincible && collision_count > 0)
  {
    Node *last_collision = cast_to<Node>((m_bird->get_last_slide_collision())->get_collider());

    if ((last_collision->get_name()) != (String) "Boundary")
    {
      if (!m_pipe_destroyer_active)
      {
        m_bird->set_process_mode(PROCESS_MODE_DISABLED);
        print_line("GAME OVER");
        save_score();
        // TODO change to end screen
      }
      else if (m_pipe_destroyer_active)
      {
        last_collision->queue_free();
      }
    }
  }
}

void Bird::activate_shield()
{
  set_shield(true);
  set_invincibility(true);
}
void Bird::deactivate_shield()
{
  set_shield(false);
  set_invincibility(false);
}
void Bird::activate_pipe_destroyer() {}
void Bird::deactivate_pipe_destroyer() {}

void Bird::increase_bird_movespeed() {}

void Bird::rotate_sprite() {}

void Bird::save_score() {}

void Bird::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_speed"), &Bird::get_speed);
  ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Bird::set_speed);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

  ClassDB::bind_method(D_METHOD("get_fallspeed"), &Bird::get_fallspeed);
  ClassDB::bind_method(D_METHOD("set_fallspeed", "p_fallspeed"), &Bird::set_fallspeed);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fall speed"), "set_fallspeed", "get_fallspeed");

  ClassDB::bind_method(D_METHOD("get_flyspeed"), &Bird::get_flyspeed);
  ClassDB::bind_method(D_METHOD("set_flyspeed", "p_flyspeed"), &Bird::set_flyspeed);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "flyspeed"), "set_flyspeed", "get_flyspeed");

  ClassDB::bind_method(D_METHOD("get_dive_multiplier"), &Bird::get_dive_multiplier);
  ClassDB::bind_method(D_METHOD("set_dive_multiplier", "p_dive_multiplier"), &Bird::set_dive_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "dive multiplier"), "set_dive_multiplier", "get_dive_multiplier");

  ClassDB::bind_method(D_METHOD("get_gravity_multiplier"), &Bird::get_gravity_multiplier);
  ClassDB::bind_method(D_METHOD("set_gravity_multiplier", "p_gravity_multiplier"), &Bird::set_gravity_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity multiplier"), "set_gravity_multiplier", "get_gravity_multiplier");

  ClassDB::bind_method(D_METHOD("get_invincibility"), &Bird::get_invincibility);
  ClassDB::bind_method(D_METHOD("set_invincibility", "p_invincibility"), &Bird::set_invincibility);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "invincible"), "set_invincibility", "get_invincibility");

  ClassDB::bind_method(D_METHOD("get_shield"), &Bird::get_shield);
  ClassDB::bind_method(D_METHOD("set_shield", "p_shield"), &Bird::set_shield);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "shield"), "set_shield", "get_shield");

  ClassDB::bind_method(D_METHOD("get_pipe_destroyer"), &Bird::get_pipe_destroyer);
  ClassDB::bind_method(D_METHOD("set_pipe_destroyer", "p_pipe_destroyer"), &Bird::set_pipe_destroyer);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "pipe destroyer"), "set_pipe_destroyer", "get_pipe_destroyer");
}

void Bird::set_speed(const float p_speed) { m_speed = p_speed; }
float Bird::get_speed() const { return m_speed; }

void Bird::set_fallspeed(const float p_fallspeed) { m_fallspeed = p_fallspeed; }
float Bird::get_fallspeed() const { return m_fallspeed; }

void Bird::set_flyspeed(const float p_flyspeed) { m_flyspeed = p_flyspeed; }
float Bird::get_flyspeed() const { return m_flyspeed; }

void Bird::set_dive_multiplier(const float p_dive_multiplier) { m_dive_multiplier = p_dive_multiplier; }
float Bird::get_dive_multiplier() const { return m_dive_multiplier; }

void Bird::set_gravity_multiplier(const float p_gravity_multiplier) { m_dive_multiplier = p_gravity_multiplier; }
float Bird::get_gravity_multiplier() const { return m_gravity_multiplier; }

void Bird::set_invincibility(const bool p_invincible) { m_invincible = p_invincible; }
bool Bird::get_invincibility() const { return m_invincible; }

void Bird::set_shield(const bool p_shield_active) { m_shield_active = p_shield_active; }
bool Bird::get_shield() const { return m_shield_active; }

void Bird::set_pipe_destroyer(const bool p_pipe_destroyer) { m_pipe_destroyer_active = p_pipe_destroyer; }
bool Bird::get_pipe_destroyer() const { return m_pipe_destroyer_active; }
