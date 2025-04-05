#pragma once

#include "godot_cpp/classes/area2d.hpp"
#include "godot_cpp/classes/timer.hpp"

class BasePowerUps : public godot::Area2D
{
  GDCLASS(BasePowerUps, godot::Area2D)

 public:
  void _ready() override;

 protected:
  godot::Timer* m_timer = nullptr;
  float m_power_duration;
  const godot::String group_after_activation = "ActivatedPowerUp";

  virtual void activate_power(Node2D* body_entered);
  virtual void power_expired();
  void music_fade(Node2D* body_entered);
  void pre_activation();
  void despawn();

  static void _bind_methods();

  void set_power_duration(float power_duration);
  float get_power_duration();
};
