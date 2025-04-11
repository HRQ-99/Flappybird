#pragma once

#include "bird.h"
#include "godot_cpp/classes/curve2d.hpp"
#include "godot_cpp/classes/line2d.hpp"

class BoostTrail : public godot::Line2D
{
  GDCLASS(BoostTrail, godot::Line2D)

 public:
  void _ready() override;
  void _process(double delta) override;

  void initialize(Bird* bird, float duration);
  void expired();

 private:
  Bird* m_bird = nullptr;
  godot::Curve2D* curve = nullptr;
  const int max_bake_points = 80;

 protected:
  static void _bind_methods();
};
