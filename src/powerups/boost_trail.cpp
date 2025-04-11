#include "boost_trail.h"

#include "godot_cpp/classes/timer.hpp"

using namespace godot;

void BoostTrail::_ready() { curve = memnew(Curve2D); }

void BoostTrail::_process(double delta)
{
  if (m_bird)
  {
    curve->add_point(m_bird->get_global_position());

    if (curve->get_baked_points().size() > max_bake_points)
    {
      curve->remove_point(0);
    }

    set_points(curve->get_baked_points());
  }
}

void BoostTrail::initialize(Bird* bird, float duration)
{
  m_bird = bird;
  move_local_y(4);

  Timer* timer = get_node<Timer>("Timer");
  timer->set_wait_time(duration);
  timer->connect("timeout", Callable(this, "expired"));
}

void BoostTrail::expired() { queue_free(); }

void BoostTrail::_bind_methods() { ClassDB::bind_method(D_METHOD("expired"), &BoostTrail::expired); }
