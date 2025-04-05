#include "speed_boost.h"

using namespace godot;

void SpeedBoost::activate_power(Node2D* body_entered)
{
  BasePowerUps::pre_activation();

  m_bird = Object::cast_to<Bird>(body_entered);
  m_bird->set_speed_multiplier(m_bird->get_speed_multiplier() * m_speed_multiplier);
  m_bird->set_gravity_multiplier(m_bird->get_gravity_multiplier() * m_gravity_multiplier);
  m_bird->set_invincibility(m_invincible);

  m_timer->start();
}

void SpeedBoost::power_expired()
{
  m_bird->set_speed_multiplier(m_bird->get_speed_multiplier() / m_speed_multiplier);
  m_bird->set_gravity_multiplier(m_bird->get_gravity_multiplier() / m_gravity_multiplier);
  m_bird->set_invincibility(!m_invincible);

  call_deferred("queue_free");
}

void SpeedBoost::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_speed_multiplier"), &SpeedBoost::get_speed_multiplier);
  ClassDB::bind_method(D_METHOD("set_speed_multiplier", "speed_multiplier"), &SpeedBoost::set_speed_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed_multiplier"), "set_speed_multiplier", "get_speed_multiplier");

  ClassDB::bind_method(D_METHOD("get_gravity_multiplier"), &SpeedBoost::get_gravity_multiplier);
  ClassDB::bind_method(D_METHOD("set_gravity_multiplier", "gravity_multiplier"), &SpeedBoost::set_gravity_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity_multiplier"), "set_gravity_multiplier", "get_gravity_multiplier");

  ClassDB::bind_method(D_METHOD("get_invincible"), &SpeedBoost::get_invincible);
  ClassDB::bind_method(D_METHOD("set_invincible", "invincible"), &SpeedBoost::set_invincible);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "invincible"), "set_invincible", "get_invincible");
}

void SpeedBoost::set_speed_multiplier(float speed_multiplier) { m_speed_multiplier = speed_multiplier; }
float SpeedBoost::get_speed_multiplier() { return m_speed_multiplier; }

void SpeedBoost::set_gravity_multiplier(float gravity_multiplier) { m_gravity_multiplier = gravity_multiplier; }
float SpeedBoost::get_gravity_multiplier() { return m_gravity_multiplier; }

void SpeedBoost::set_invincible(bool invincible) { m_invincible = invincible; }
bool SpeedBoost::get_invincible() { return m_invincible; }
