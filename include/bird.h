#pragma once

#include "godot_cpp/classes/character_body2d.hpp"

class Bird : public godot::CharacterBody2D
{
  GDCLASS(Bird, CharacterBody2D)

 public:
  godot::Signal bird_died;
  godot::Signal toggle_invincibility_label;

  void _ready() override;
  void _physics_process(double delta) override;

  void activate_shield();
  void deactivate_shield();
  void activate_pipe_destroyer(float scale_multiplier);
  void deactivate_pipe_destroyer(float scale_multiplier);

  void increase_bird_movespeed();

  void set_speed(const float p_speed);
  float get_speed() const;

  void set_fallspeed(const float p_fallspeed);
  float get_fallspeed() const;

  void set_flyspeed(const float p_flyspeed);
  float get_flyspeed() const;

  void set_speed_multiplier(const float p_speed_multiplier);
  float get_speed_multiplier() const;

  void set_dive_multiplier(const float p_dive_multiplier);
  float get_dive_multiplier() const;

  void set_gravity_multiplier(const float p_gravity_multiplier);
  float get_gravity_multiplier() const;

  void set_invincibility(const bool p_invincible);
  bool get_invincibility() const;

  void set_shield(const bool p_shield_active);
  bool get_shield() const;

  void set_pipe_destroyer(const bool p_pipe_destroyer);
  bool get_pipe_destroyer() const;

 private:
  float m_speed = 80;
  float m_fallspeed = 60;
  float m_flyspeed = -300;
  float m_speed_multiplier = 1;
  float m_dive_multiplier = 5;
  float m_gravity_multiplier = 1;

  bool m_invincible = false;
  bool m_shield_active = false;
  bool m_pipe_destroyer_active = false;

  static void rotate_sprite();

 protected:
  static void _bind_methods();
};
