#include "base_powerups.h"

#include "godot_cpp/classes/audio_stream_player.hpp"
#include "godot_cpp/classes/audio_stream_player2d.hpp"
#include "godot_cpp/classes/property_tweener.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/tween.hpp"

using namespace godot;

void BasePowerUps::activate_power(Node2D* body_entered) {}
void BasePowerUps::power_expired() {}

void BasePowerUps::_ready()
{
  m_timer = this->get_node<Timer>("Timer");
  m_timer->set_wait_time(m_power_duration);
  m_timer->connect("timeout", Callable(this, "power_expired"));
  get_node<Timer>("DespawnTimer")->connect("timeout", Callable(this, "despawn"));

  connect("body_entered", Callable(this, "activate_power"));
}

void BasePowerUps::pre_activation()
{
  call_deferred("set_monitoring", false);
  set_visible(false);
  add_to_group(group_after_activation);

  AudioStreamPlayer* music = get_tree()->get_current_scene()->get_node<AudioStreamPlayer>("BackgroundMusic");
  Ref<Tween> music_fade = create_tween();
  music_fade->tween_property(music, "volume_db", -30.0, 1.0);
  get_node<AudioStreamPlayer2D>("Effect")->play();
  music_fade->tween_property(music, "volume_db", 0, 1.0);
}

void BasePowerUps::despawn()
{
  if (!is_in_group(group_after_activation))
  {
    call_deferred("queue_free");
  }
}

void BasePowerUps::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("activate_power", "body_entered"), &BasePowerUps::activate_power);
  ClassDB::bind_method(D_METHOD("power_expired"), &BasePowerUps::power_expired);
  ClassDB::bind_method(D_METHOD("pre_activation"), &BasePowerUps::pre_activation);
  ClassDB::bind_method(D_METHOD("despawn"), &BasePowerUps::despawn);

  ClassDB::bind_method(D_METHOD("get_power_duration"), &BasePowerUps::get_power_duration);
  ClassDB::bind_method(D_METHOD("set_power_duration", "power_duration"), &BasePowerUps::set_power_duration);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "power_duration"), "set_power_duration", "get_power_duration");
}

void BasePowerUps::set_power_duration(float power_duration) { m_power_duration = power_duration; }
float BasePowerUps::get_power_duration() { return m_power_duration; }
