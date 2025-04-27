#pragma once

#include "difficulty_manager.h"
#include "godot_cpp/classes/character_body2d.hpp"

class Bird : public godot::CharacterBody2D
{
  GDCLASS(Bird, CharacterBody2D)

 public:
  godot::Signal bird_died;
  godot::Signal toggle_invincibility_label;
  godot::Signal pipe_destroyed;

  void _physics_process(double delta) override;

  void apply_camera_effect(float power_duration);
  void deactivate_shield(godot::Node2D* last_collision);
  void activate_pipe_destroyer(float scale_multiplier);
  void deactivate_pipe_destroyer(float scale_multiplier);

  void change_bird_difficulty(DifficultyManager::DifficultyStage stage);
  void set_speed_array(const godot::PackedFloat32Array speed_array);
  godot::PackedFloat32Array get_speed_array() const;

  void set_speed(const float p_speed);
  float get_speed() const;
  float get_final_speed() const;

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

  godot::PackedFloat32Array m_bird_speed_array = [] {
    godot::PackedFloat32Array arr;
    arr.append(80);
    arr.append(85);
    arr.append(90);
    arr.append(95);
    arr.append(100);
    arr.append(110);
    return arr;
  }();

  static void rotate_sprite();

 protected:
  static void _bind_methods();
};
