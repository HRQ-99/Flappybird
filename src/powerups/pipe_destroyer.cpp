#include "pipe_destroyer.h"

using namespace godot;

void PipeDestroyer::activate_power(Node2D* body_entered)
{
  BasePowerUps::pre_activation();

  m_bird = Object::cast_to<Bird>(body_entered);
  m_bird->activate_pipe_destroyer(m_bird_scale_multiplier);
  m_timer->start();
}

void PipeDestroyer::power_expired()
{
  m_bird->deactivate_pipe_destroyer(m_bird_scale_multiplier);
  call_deferred("queue_free");
}

void PipeDestroyer::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_scale_multiplier"), &PipeDestroyer::get_scale_multiplier);
  ClassDB::bind_method(D_METHOD("set_scale_multiplier", "scale_multiplier"), &PipeDestroyer::set_scale_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "scale_multiplier"), "set_scale_multiplier", "get_scale_multiplier");
}

void PipeDestroyer::set_scale_multiplier(float scale_multiplier) { m_bird_scale_multiplier = scale_multiplier; }
float PipeDestroyer::get_scale_multiplier() { return m_bird_scale_multiplier; }
