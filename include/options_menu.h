#pragma once

#include "godot_cpp/classes/config_file.hpp"
#include "godot_cpp/classes/tab_container.hpp"
#include "godot_cpp/classes/v_box_container.hpp"

class OptionsMenu : public godot::TabContainer
{
  GDCLASS(OptionsMenu, TabContainer)

 public:
  godot::Signal back_to_title_screen;

  void _ready() override;
  void _input();

 private:
  godot::ConfigFile* config = nullptr;
  godot::VBoxContainer* DisplayVBox;
  godot::VBoxContainer* AudioVBox;

  void change_fullscreen(bool toggled_on);

  void change_custom_cursor(bool toggled_on);

  void change_vsync(bool toggled_on);

  void change_master_volume(bool value_changed);

  void change_music_volume(bool value_changed);

  void change_effects_volume(bool value_changed);

 protected:
  static void _bind_methods();
};
