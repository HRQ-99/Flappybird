#pragma once

#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class MainGame : public Node {
  GDCLASS(MainGame, Node)

public:
  MainGame();
  ~MainGame();

  void _process(double delta) override;
  void _ready() override;

protected:
  const String background_image = ("res://art/background_2.png");
  const Vector2 scale = *new Vector2(0.35, 0.35);
  const Vector2 background_position = *new Vector2(319, 180);

  static void _bind_methods();
};
