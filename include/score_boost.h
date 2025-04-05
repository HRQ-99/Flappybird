#pragma once

#include "base_powerups.h"

class ScoreBoost : public BasePowerUps
{
  GDCLASS(ScoreBoost, BasePowerUps)

 public:
  void set_score_multiplier(float speed_multiplier);
  float get_score_multiplier();

 private:
  godot::Timer* m_level_score_timer = nullptr;
  float m_score_multiplier = 0.5;

  virtual void activate_power(Node2D* body_entered) override;
  virtual void power_expired() override;

  static void _bind_methods();
};
