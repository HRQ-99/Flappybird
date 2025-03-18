#pragma once

#include <godot_cpp/core/class_db.hpp>

#include "godot_cpp/classes/character_body2d.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace godot;

class Bird : public CharacterBody2D
{
  GDCLASS(Bird, CharacterBody2D)

 public:
  virtual void _ready() override;
  virtual void _process(double delta) override;

  void activate_shield();
  void deactivate_shield();
  void activate_pipe_destroyer();
  void deactivate_pipe_destroyer();

  void increase_bird_movespeed();

 private:
  Bird *m_bird = this;
  const float m_fallspeed = 150;
  const float m_flyspeed = -1500;
  const float m_dive_multiplier = 5;

  float m_speed = 150;

  bool m_invincible = false;
  bool m_shield_active = false;
  bool m_pipe_destroyer_active = false;

  static float s_gravity_multiplier;
  static void rotate_sprite();

  void save_score();

 protected:
  static void _bind_methods();
};
