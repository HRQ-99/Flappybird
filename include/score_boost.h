#pragma once

#include "bird.h"
#include "godot_cpp/classes/area2d.hpp"
#include "godot_cpp/classes/timer.hpp"

class ScoreBoost : public godot::Area2D
{
  GDCLASS(ScoreBoost, Area2D)

 public:
  void _ready() override;

  void set_score_multiplier(float speed_multiplier);
  float get_score_multiplier();

  void set_power_duration(float power_duration);
  float get_power_duration();

 private:
  Bird* _bird = nullptr;
  godot::Timer* m_timer = nullptr;
  float m_score_multiplier = 0.5;
  float m_power_duration = 20;

  virtual void activate_power(Node2D* body_entered);
  virtual void power_expired();
  virtual void music_fade_out(Node2D* body_entered);
  virtual void music_fade_in();

 protected:
  static void _bind_methods();
};
