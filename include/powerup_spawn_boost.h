#pragma once

#include "godot_cpp/classes/area2d.hpp"
#include "godot_cpp/classes/timer.hpp"

class PowerUpSpawnBoost : public godot::Area2D
{
  GDCLASS(PowerUpSpawnBoost, Area2D)

 public:
  void _ready() override;

  void set_power_duration(float power_duration);
  float get_power_duration();

  void set_spawn_multiplier(float spawn_multiplier);
  float get_spawn_multiplier();

 private:
  godot::Timer* m_timer = nullptr;
  float m_power_duration = 12;
  float m_spawn_multiplier = 0.5;
  godot::Timer* m_level_powerup_spawn_timer = nullptr;
  const godot::String group_after_activation = "ActivatedPowerUp";

  virtual void activate_power(Node2D* body_entered);
  virtual void power_expired();
  virtual void music_fade_out(Node2D* body_entered);
  virtual void music_fade_in();
  virtual void despawn();

 protected:
  static void _bind_methods();
};
