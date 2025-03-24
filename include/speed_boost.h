#pragma once

#include "bird.h"
#include "godot_cpp/classes/area2d.hpp"
#include "godot_cpp/classes/timer.hpp"

class SpeedBoost : public godot::Area2D
{
  GDCLASS(SpeedBoost, Area2D)

 public:
  void _ready() override;
  void set_speed_multiplier(float speed_multiplier);
  float get_speed_multiplier();

  void set_gravity_multiplier(float gravity_multiplier);
  float get_gravity_multiplier();

  void set_power_duration(float power_duration);
  float get_power_duration();

  void set_invincible(bool invincible);
  bool get_invincible();

 private:
  Bird* _bird = nullptr;
  godot::Timer* m_timer = nullptr;
  float m_speed_multiplier = 5;
  float m_gravity_multiplier = 0.01;
  float m_power_duration = 5;
  bool m_invincible = true;

  virtual void activate_power(Node2D* body_entered);
  virtual void power_expired();
  virtual void music_fade_out(Node2D* body_entered);
  virtual void music_fade_in();

 protected:
  static void _bind_methods();
};
