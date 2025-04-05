#pragma once

#include "base_powerups.h"
#include "bird.h"

class SpeedBoost : public BasePowerUps
{
  GDCLASS(SpeedBoost, BasePowerUps)

 public:
  void set_speed_multiplier(float speed_multiplier);
  float get_speed_multiplier();

  void set_gravity_multiplier(float gravity_multiplier);
  float get_gravity_multiplier();

  void set_invincible(bool invincible);
  bool get_invincible();

 private:
  Bird* m_bird = nullptr;
  float m_speed_multiplier = 5;
  float m_gravity_multiplier = 0.01;
  bool m_invincible = true;

  virtual void activate_power(Node2D* body_entered) override;
  virtual void power_expired() override;

  static void _bind_methods();
};
