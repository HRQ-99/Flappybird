#include "speed_boost.h"

#include "godot_cpp/classes/audio_stream_player2d.hpp"
#include "godot_cpp/classes/property_tweener.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/tween.hpp"

using namespace godot;

void SpeedBoost::_ready()
{
  m_timer = get_node<Timer>("Timer");
  m_timer->set_wait_time(m_power_duration);
  m_timer->connect("timeout", Callable(this, "power_expired"));

  connect("body_entered", Callable(this, "activate_power"));
  get_node<Area2D>("MusicFadeArea")->connect("body_entered", Callable(this, "music_fade_out"));
}

void SpeedBoost::activate_power(Node2D* body_entered)
{
  call_deferred("set_monitorable", false);
  set_visible(false);

  _bird = Object::cast_to<Bird>(body_entered);
  _bird->set_speed_multiplier(_bird->get_speed_multiplier() * m_speed_multiplier);
  _bird->set_gravity_multiplier(_bird->get_gravity_multiplier() * m_gravity_multiplier);
  _bird->set_invincibility(m_invincible);

  get_node<AudioStreamPlayer2D>("Effect")->play();
  get_node<AudioStreamPlayer2D>("Effect")->connect("finished", Callable(this, "music_fade_in"));
  m_timer->start();
}

void SpeedBoost::power_expired()
{
  _bird->set_speed_multiplier(_bird->get_speed_multiplier() / m_speed_multiplier);
  _bird->set_gravity_multiplier(_bird->get_gravity_multiplier() / m_gravity_multiplier);
  _bird->set_invincibility(!m_invincible);

  call_deferred("queue_free");
}

void SpeedBoost::music_fade_out(Node2D* body_entered)
{
  Ref<Tween> music_fade = get_tree()->get_current_scene()->create_tween();
  music_fade->tween_property(get_tree()->get_current_scene()->get_node<AudioStreamPlayer2D>("BackgroundMusic"),
                             "volume_db", -30.0, 1.0);
}

void SpeedBoost::music_fade_in()
{
  get_tree()->get_current_scene()->get_node<AudioStreamPlayer2D>("BackgroundMusic")->set_volume_db(0);
}

void SpeedBoost::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("activate_power", "body_entered"), &SpeedBoost::activate_power);
  ClassDB::bind_method(D_METHOD("power_expired"), &SpeedBoost::power_expired);
  ClassDB::bind_method(D_METHOD("music_fade_out", "body_entered"), &SpeedBoost::music_fade_out);
  ClassDB::bind_method(D_METHOD("music_fade_in"), &SpeedBoost::music_fade_in);

  ClassDB::bind_method(D_METHOD("get_speed_multiplier"), &SpeedBoost::get_speed_multiplier);
  ClassDB::bind_method(D_METHOD("set_speed_multiplier", "speed_multiplier"), &SpeedBoost::set_speed_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed_multiplier"), "set_speed_multiplier", "get_speed_multiplier");

  ClassDB::bind_method(D_METHOD("get_gravity_multiplier"), &SpeedBoost::get_gravity_multiplier);
  ClassDB::bind_method(D_METHOD("set_gravity_multiplier", "gravity_multiplier"), &SpeedBoost::set_gravity_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity_multiplier"), "set_gravity_multiplier", "get_gravity_multiplier");

  ClassDB::bind_method(D_METHOD("get_power_duration"), &SpeedBoost::get_power_duration);
  ClassDB::bind_method(D_METHOD("set_power_duration", "power_duration"), &SpeedBoost::set_power_duration);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "power_duration"), "set_power_duration", "get_power_duration");

  ClassDB::bind_method(D_METHOD("get_invincible"), &SpeedBoost::get_invincible);
  ClassDB::bind_method(D_METHOD("set_invincible", "invincible"), &SpeedBoost::set_invincible);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "invincible"), "set_invincible", "get_invincible");
}

void SpeedBoost::set_speed_multiplier(float speed_multiplier) { m_speed_multiplier = speed_multiplier; }
float SpeedBoost::get_speed_multiplier() { return m_speed_multiplier; }

void SpeedBoost::set_gravity_multiplier(float gravity_multiplier) { m_gravity_multiplier = gravity_multiplier; }
float SpeedBoost::get_gravity_multiplier() { return m_gravity_multiplier; }

void SpeedBoost::set_power_duration(float power_duration) { m_power_duration = power_duration; }
float SpeedBoost::get_power_duration() { return m_power_duration; }

void SpeedBoost::set_invincible(bool invincible) { m_invincible = invincible; }
bool SpeedBoost::get_invincible() { return m_invincible; }
