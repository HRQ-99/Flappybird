#pragma once

#include "base_powerups.h"

class PowerUpSpawnBoost : public BasePowerUps
{
  GDCLASS(PowerUpSpawnBoost, BasePowerUps)

 private:
  float m_spawn_multiplier = 0.5;
  godot::Timer* m_level_powerup_spawn_timer = nullptr;

  virtual void activate_power(Node2D* body_entered) override;
  virtual void power_expired() override;

  void set_spawn_multiplier(float spawn_multiplier);
  float get_spawn_multiplier();

  static void _bind_methods();
};
