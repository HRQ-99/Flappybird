#include "score_boost.h"

using namespace godot;

void ScoreBoost::activate_power(Node2D* body_entered)
{
  BasePowerUps::pre_activation();

  m_level_score_timer = get_parent()->get_node<Timer>("ScoreTimer");
  m_level_score_timer->set_wait_time(m_level_score_timer->get_wait_time() * m_score_multiplier);
}

void ScoreBoost::power_expired()
{
  m_level_score_timer->set_wait_time(m_level_score_timer->get_wait_time() / m_score_multiplier);
  call_deferred("queue_free");
}

void ScoreBoost::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_score_multiplier"), &ScoreBoost::get_score_multiplier);
  ClassDB::bind_method(D_METHOD("set_score_multiplier", "score_multiplier"), &ScoreBoost::set_score_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score_multiplier"), "set_score_multiplier", "get_score_multiplier");
}

void ScoreBoost::set_score_multiplier(float score_multiplier) { m_score_multiplier = score_multiplier; }
float ScoreBoost::get_score_multiplier() { return m_score_multiplier; }
