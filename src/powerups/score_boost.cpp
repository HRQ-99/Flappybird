#include "score_boost.h"

#include "godot_cpp/classes/audio_stream_player2d.hpp"
#include "godot_cpp/classes/property_tweener.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/timer.hpp"
#include "godot_cpp/classes/tween.hpp"

using namespace godot;

void ScoreBoost::_ready()
{
  m_timer = get_node<Timer>("Timer");
  m_timer->set_wait_time(m_power_duration);
  m_timer->connect("timeout", Callable(this, "power_expired"));

  connect("body_entered", Callable(this, "activate_power"));
  get_node<Area2D>("MusicFadeArea")->connect("body_entered", Callable(this, "music_fade_out"));
}

void ScoreBoost::activate_power(Node2D* body_entered)
{
  Timer* spawn_timer = get_parent()->get_node<Timer>("ScoreTimer");
  spawn_timer->set_wait_time(spawn_timer->get_wait_time() * m_score_multiplier);
}

void ScoreBoost::power_expired()
{
  Timer* spawn_timer = get_parent()->get_node<Timer>("ScoreTimer");
  spawn_timer->set_wait_time(spawn_timer->get_wait_time() / m_score_multiplier);
}

void ScoreBoost::music_fade_out(Node2D* body_entered)
{
  Ref<Tween> music_fade = get_tree()->get_current_scene()->create_tween();
  music_fade->tween_property(get_tree()->get_current_scene()->get_node<AudioStreamPlayer2D>("BackgroundMusic"),
                             "volume_db", -30.0, 1.0);
}

void ScoreBoost::music_fade_in()
{
  get_tree()->get_current_scene()->get_node<AudioStreamPlayer2D>("BackgroundMusic")->set_volume_db(0);
}

void ScoreBoost::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("activate_power", "body_entered"), &ScoreBoost::activate_power);
  ClassDB::bind_method(D_METHOD("power_expired"), &ScoreBoost::power_expired);
  ClassDB::bind_method(D_METHOD("music_fade_out", "body_entered"), &ScoreBoost::music_fade_out);
  ClassDB::bind_method(D_METHOD("music_fade_in"), &ScoreBoost::music_fade_in);

  ClassDB::bind_method(D_METHOD("get_score_multiplier"), &ScoreBoost::get_score_multiplier);
  ClassDB::bind_method(D_METHOD("set_score_multiplier", "score_multiplier"), &ScoreBoost::set_score_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score_multiplier"), "set_score_multiplier", "get_score_multiplier");

  ClassDB::bind_method(D_METHOD("get_power_duration"), &ScoreBoost::get_power_duration);
  ClassDB::bind_method(D_METHOD("set_power_duration", "power_duration"), &ScoreBoost::set_power_duration);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "power_duration"), "set_power_duration", "get_power_duration");
}

void ScoreBoost::set_score_multiplier(float score_multiplier) { m_score_multiplier = score_multiplier; }
float ScoreBoost::get_score_multiplier() { return m_score_multiplier; }

void ScoreBoost::set_power_duration(float power_duration) { m_power_duration = power_duration; }
float ScoreBoost::get_power_duration() { return m_power_duration; }
