#include "main_game.h"
#include "godot_cpp/classes/canvas_layer.hpp"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/sprite2d.hpp"
#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/core/memory.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

MainGame::MainGame() {
  CanvasLayer *main_ui = memnew(CanvasLayer);
  main_ui->set_name("MainUI");
  this->add_child(main_ui);

  Sprite2D *background = memnew(Sprite2D);
  background->set_name("Background");
  const Ref<Texture2D> background_texture =
      ResourceLoader::get_singleton()->load(background_image);
  background->set_texture(background_texture);
  background->apply_scale(scale);
  background->set_position(background_position);
  this->add_child(background);
}

MainGame::~MainGame() {}

void MainGame::_ready() {}

void MainGame::_process(double delta) {}

void MainGame::_bind_methods() {}
