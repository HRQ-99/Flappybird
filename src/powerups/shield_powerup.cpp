#include "shield_powerup.h"

#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/resource_loader.hpp"

using namespace godot;

void Shield::_ready()
{
  BasePowerUps::_ready();
  Ref<PackedScene> sprite = ResourceLoader::get_singleton()->load(bird_shield_path);
  bird_shield = sprite->instantiate();
}

void Shield::activate_power(godot::Node2D* body_entered)
{
  BasePowerUps::pre_activation();

  m_bird = Object::cast_to<Bird>(body_entered);
  m_bird->set_invincibility(true);
  m_bird->set_shield(true);
  m_bird->add_child(bird_shield);
}

void Shield::_bind_methods() {}
