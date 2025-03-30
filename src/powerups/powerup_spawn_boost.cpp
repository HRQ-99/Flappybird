#include "powerup_spawn_boost.h"

#include "godot_cpp/classes/audio_stream_player2d.hpp"
#include "godot_cpp/classes/property_tweener.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/tween.hpp"

using namespace godot;

void PowerUpSpawnBoost::_ready()
{
  m_timer = get_node<Timer>("Timer");
  m_timer->set_wait_time(m_power_duration);
  m_timer->connect("timeout", Callable(this, "power_expired"));

  connect("body_entered", Callable(this, "activate_power"));
  get_node<Area2D>("MusicFadeArea")->connect("body_entered", Callable(this, "music_fade_out"));
}

void PowerUpSpawnBoost::activate_power(Node2D* body_entered)
{
  call_deferred("set_monitorable", false);
  set_visible(false);

  m_level_powerup_spawn_timer = get_parent()->get_node<Timer>("PowerUpSpawnTimer");
  m_level_powerup_spawn_timer->set_wait_time(m_level_powerup_spawn_timer->get_wait_time() * m_spawn_multiplier);

  get_node<AudioStreamPlayer2D>("Effect")->play();
  get_node<AudioStreamPlayer2D>("Effect")->connect("finished", Callable(this, "music_fade_in"));
  m_timer->start();
}

void PowerUpSpawnBoost::power_expired()
{
  m_level_powerup_spawn_timer->set_wait_time(m_level_powerup_spawn_timer->get_wait_time() / m_spawn_multiplier);
  call_deferred("queue_free");
}

void PowerUpSpawnBoost::music_fade_out(Node2D* body_entered)
{
  Ref<Tween> music_fade = get_tree()->get_current_scene()->create_tween();
  music_fade->tween_property(get_tree()->get_current_scene()->get_node<AudioStreamPlayer2D>("BackgroundMusic"),
                             "volume_db", -30.0, 1.0);
}

void PowerUpSpawnBoost::music_fade_in()
{
  get_tree()->get_current_scene()->get_node<AudioStreamPlayer2D>("BackgroundMusic")->set_volume_db(0);
}

void PowerUpSpawnBoost::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("activate_power", "body_entered"), &PowerUpSpawnBoost::activate_power);
  ClassDB::bind_method(D_METHOD("power_expired"), &PowerUpSpawnBoost::power_expired);
  ClassDB::bind_method(D_METHOD("music_fade_out", "body_entered"), &PowerUpSpawnBoost::music_fade_out);
  ClassDB::bind_method(D_METHOD("music_fade_in"), &PowerUpSpawnBoost::music_fade_in);

  ClassDB::bind_method(D_METHOD("get_spawn_multiplier"), &PowerUpSpawnBoost::get_spawn_multiplier);
  ClassDB::bind_method(D_METHOD("set_spawn_multiplier", "spawn_multiplier"), &PowerUpSpawnBoost::set_spawn_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "spawn_multiplier"), "set_spawn_multiplier", "get_spawn_multiplier");

  ClassDB::bind_method(D_METHOD("get_power_duration"), &PowerUpSpawnBoost::get_power_duration);
  ClassDB::bind_method(D_METHOD("set_power_duration", "power_duration"), &PowerUpSpawnBoost::set_power_duration);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "power_duration"), "set_power_duration", "get_power_duration");
}

void PowerUpSpawnBoost::set_spawn_multiplier(float spawn_multiplier) { m_spawn_multiplier = spawn_multiplier; }
float PowerUpSpawnBoost::get_spawn_multiplier() { return m_spawn_multiplier; }

void PowerUpSpawnBoost::set_power_duration(float power_duration) { m_power_duration = power_duration; }
float PowerUpSpawnBoost::get_power_duration() { return m_power_duration; }
