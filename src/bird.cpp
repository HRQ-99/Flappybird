#include "bird.h"

#include "godot_cpp/classes/camera2d.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/property_tweener.hpp"
#include "godot_cpp/classes/tween.hpp"

using namespace godot;

void Bird::_physics_process(double delta)
{
  Input *input = Input::get_singleton();

  set_velocity(Vector2(m_speed * m_speed_multiplier, m_fallspeed * m_gravity_multiplier));

  if (input->is_action_just_pressed("Flap"))
  {
    set_velocity(Vector2(m_speed * m_speed_multiplier, m_flyspeed + m_fallspeed));
  }
  else if (input->is_action_pressed("Dive"))
  {
    set_velocity(Vector2(m_speed * m_speed_multiplier, m_fallspeed * m_dive_multiplier));
  }

  move_and_slide();

  int collision_count = get_slide_collision_count();

  if (collision_count > 0)
  {
    Node *last_collision = cast_to<Node>(get_last_slide_collision()->get_collider());

    if ((last_collision->get_name()) != (String) "Boundary")
    {
      if (!m_invincible && !m_pipe_destroyer_active)
      {
        set_process_mode(PROCESS_MODE_DISABLED);
        emit_signal("bird_died");
      }
      else if (m_pipe_destroyer_active)
      {
        emit_signal("pipe_destroyed", last_collision);
      }
      else if (m_shield_active)
      {
        emit_signal("pipe_destroyed", last_collision);
      }
    }
  }

  if (input->is_action_just_pressed("Godmode"))
  {
    set_invincibility(!m_invincible);
    emit_signal("toggle_invincibility_label");
  }
}

void Bird::apply_camera_effect(float power_duration)
{
  Ref<Tween> tween = create_tween();
  Camera2D *camera = get_node<Camera2D>("Camera");
  const float og_pixel_smoothing = camera->get_position_smoothing_speed();
  const Vector2 og_offset = camera->get_offset();
  const float zoom_duration_half = 0.25;
  const float smoothing_duration_half = (power_duration - zoom_duration_half) / 2;

  tween->tween_property(camera, "zoom", Vector2(0.8, 0.8), zoom_duration_half);
  tween->tween_property(camera, "position_smoothing_speed", 2, smoothing_duration_half);
  tween->tween_property(camera, "position_smoothing_speed", og_pixel_smoothing, smoothing_duration_half);
  tween->tween_property(camera, "zoom", Vector2(1, 1), zoom_duration_half);
}

void Bird::deactivate_shield(Node2D *last_collision)
{
  emit_signal("pipe_destroyed", last_collision);
  set_shield(false);
  set_invincibility(false);
}

void Bird::activate_pipe_destroyer(float scale_multiplier)
{
  m_pipe_destroyer_active = true;
  Ref<Tween> scale_tween = create_tween();
  scale_tween->tween_property(this, "scale", get_scale() * scale_multiplier, 1);
}
void Bird::deactivate_pipe_destroyer(float scale_multiplier)
{
  m_pipe_destroyer_active = false;
  Ref<Tween> scale_tween = create_tween();
  scale_tween->tween_property(this, "scale", get_scale() / scale_multiplier, 1);
}

void Bird::change_bird_difficulty(DifficultyManager::DifficultyStage stage) { m_speed = m_bird_speed_array [stage]; }

void Bird::rotate_sprite() {}

void Bird::_bind_methods()
{
  ADD_SIGNAL(MethodInfo("bird_died"));
  ADD_SIGNAL(MethodInfo("toggle_invincibility_label"));
  ADD_SIGNAL(MethodInfo("pipe_destroyed", PropertyInfo(Variant::OBJECT, "last_collision")));

  ClassDB::bind_method(D_METHOD("change_bird_difficulty", "difficulty_stage"), &Bird::change_bird_difficulty);
  ClassDB::bind_method(D_METHOD("deactivate_shield", "last_collision"), &Bird::deactivate_shield);

  ClassDB::bind_method(D_METHOD("get_speed_array"), &Bird::get_speed_array);
  ClassDB::bind_method(D_METHOD("set_speed_array", "speed_array"), &Bird::set_speed_array);
  ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "move_speed_array"), "set_speed_array", "get_speed_array");

  ClassDB::bind_method(D_METHOD("get_speed"), &Bird::get_speed);
  ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Bird::set_speed);
  ClassDB::bind_method(D_METHOD("get_final_speed"), &Bird::get_final_speed);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");

  ClassDB::bind_method(D_METHOD("get_fallspeed"), &Bird::get_fallspeed);
  ClassDB::bind_method(D_METHOD("set_fallspeed", "p_fallspeed"), &Bird::set_fallspeed);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "fall speed"), "set_fallspeed", "get_fallspeed");

  ClassDB::bind_method(D_METHOD("get_flyspeed"), &Bird::get_flyspeed);
  ClassDB::bind_method(D_METHOD("set_flyspeed", "p_flyspeed"), &Bird::set_flyspeed);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "flyspeed"), "set_flyspeed", "get_flyspeed");

  ClassDB::bind_method(D_METHOD("get_speed_multiplier"), &Bird::get_speed_multiplier);
  ClassDB::bind_method(D_METHOD("set_speed_multiplier", "p_speed_multiplier"), &Bird::set_speed_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed multiplier"), "set_speed_multiplier", "get_speed_multiplier");

  ClassDB::bind_method(D_METHOD("get_dive_multiplier"), &Bird::get_dive_multiplier);
  ClassDB::bind_method(D_METHOD("set_dive_multiplier", "p_dive_multiplier"), &Bird::set_dive_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "dive multiplier"), "set_dive_multiplier", "get_dive_multiplier");

  ClassDB::bind_method(D_METHOD("get_gravity_multiplier"), &Bird::get_gravity_multiplier);
  ClassDB::bind_method(D_METHOD("set_gravity_multiplier", "p_gravity_multiplier"), &Bird::set_gravity_multiplier);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "gravity multiplier"), "set_gravity_multiplier", "get_gravity_multiplier");

  ClassDB::bind_method(D_METHOD("get_invincibility"), &Bird::get_invincibility);
  ClassDB::bind_method(D_METHOD("set_invincibility", "p_invincibility"), &Bird::set_invincibility);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "invincible"), "set_invincibility", "get_invincibility");

  ClassDB::bind_method(D_METHOD("get_shield"), &Bird::get_shield);
  ClassDB::bind_method(D_METHOD("set_shield", "p_shield"), &Bird::set_shield);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "shield"), "set_shield", "get_shield");

  ClassDB::bind_method(D_METHOD("get_pipe_destroyer"), &Bird::get_pipe_destroyer);
  ClassDB::bind_method(D_METHOD("set_pipe_destroyer", "p_pipe_destroyer"), &Bird::set_pipe_destroyer);
  ADD_PROPERTY(PropertyInfo(Variant::BOOL, "pipe destroyer"), "set_pipe_destroyer", "get_pipe_destroyer");
}

void Bird::set_speed_array(const godot::PackedFloat32Array speed_array) { m_bird_speed_array = speed_array; }
PackedFloat32Array Bird::get_speed_array() const { return m_bird_speed_array; }

void Bird::set_speed(const float p_speed) { m_speed = p_speed; }
float Bird::get_speed() const { return m_speed; }
float Bird::get_final_speed() const { return m_speed * m_speed_multiplier; }

void Bird::set_fallspeed(const float p_fallspeed) { m_fallspeed = p_fallspeed; }
float Bird::get_fallspeed() const { return m_fallspeed; }

void Bird::set_flyspeed(const float p_flyspeed) { m_flyspeed = p_flyspeed; }
float Bird::get_flyspeed() const { return m_flyspeed; }

void Bird::set_dive_multiplier(const float p_dive_multiplier) { m_dive_multiplier = p_dive_multiplier; }
float Bird::get_dive_multiplier() const { return m_dive_multiplier; }

void Bird::set_speed_multiplier(const float p_speed_multiplier) { m_speed_multiplier = p_speed_multiplier; }
float Bird::get_speed_multiplier() const { return m_speed_multiplier; }

void Bird::set_gravity_multiplier(const float p_gravity_multiplier) { m_gravity_multiplier = p_gravity_multiplier; }
float Bird::get_gravity_multiplier() const { return m_gravity_multiplier; }

void Bird::set_invincibility(const bool p_invincible) { m_invincible = p_invincible; }
bool Bird::get_invincibility() const { return m_invincible; }

void Bird::set_shield(const bool p_shield_active) { m_shield_active = p_shield_active; }
bool Bird::get_shield() const { return m_shield_active; }

void Bird::set_pipe_destroyer(const bool p_pipe_destroyer) { m_pipe_destroyer_active = p_pipe_destroyer; }
bool Bird::get_pipe_destroyer() const { return m_pipe_destroyer_active; }
