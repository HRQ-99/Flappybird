#include "bird.h"
#include "godot_cpp/classes/input.hpp"

float Bird::s_gravity_multiplier = 1;

void Bird::_ready() {
  m_bird = this;
  m_invincible = false;
  m_speed = 150;
  s_gravity_multiplier = 1;
}

void Bird::_process(double delta) {
  Input *input = Input::get_singleton();

  if (input->is_action_just_pressed("Flap")) {
  } else if (input->is_action_just_pressed("Dive")) {
  }
}

void Bird::activate_shield() {}
void Bird::deactivate_shield() {}
void Bird::activate_pipe_destroyer() {}
void Bird::deactivate_pipe_destroyer() {}

void Bird::increase_bird_movespeed() {}

void Bird::rotate_sprite() {}

void Bird::save_score() {}

void Bird::_bind_methods() {}
