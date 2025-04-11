#include "powerup_spawn_boost.h"

using namespace godot;

void PowerUpSpawnBoost::activate_power(Node2D* body_entered)
{
  BasePowerUps::pre_activation();

  m_level_powerup_spawn_timer = get_parent()->get_node<Timer>("PowerUpSpawnTimer");
  m_level_powerup_spawn_timer->set_wait_time(m_level_powerup_spawn_timer->get_wait_time() * m_spawn_multiplier);

  m_timer->start();
}

void PowerUpSpawnBoost::power_expired()
{
  m_level_powerup_spawn_timer->set_wait_time(m_level_powerup_spawn_timer->get_wait_time() / m_spawn_multiplier);
  call_deferred("queue_free");
}

void PowerUpSpawnBoost::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_spawn_multiplier"), &PowerUpSpawnBoost::get_spawn_multiplier);
  ClassDB::bind_method(D_METHOD("set_spawn_multiplier", "spawn_multiplier"), &PowerUpSpawnBoost::set_spawn_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_multiplier"), "set_spawn_multiplier", "get_spawn_multiplier");
}

void PowerUpSpawnBoost::set_spawn_multiplier(float spawn_multiplier) { m_spawn_multiplier = spawn_multiplier; }
float PowerUpSpawnBoost::get_spawn_multiplier() { return m_spawn_multiplier; }
