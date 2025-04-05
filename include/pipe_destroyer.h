#pragma once

#include "base_powerups.h"
#include "bird.h"

class PipeDestroyer : public BasePowerUps
{
  GDCLASS(PipeDestroyer, BasePowerUps)

 public:
  void set_scale_multiplier(float scale_multiplier);
  float get_scale_multiplier();

 private:
  Bird* m_bird;
  float m_bird_scale_multiplier = 6;

  void activate_power(Node2D* body_entered) override;
  void power_expired() override;

  static void _bind_methods();
};
