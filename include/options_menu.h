#pragma once

#include "godot_cpp/classes/config_file.hpp"
#include "godot_cpp/classes/tab_container.hpp"
#include "godot_cpp/classes/v_box_container.hpp"
#include "user_config.h"

class OptionsMenu : public godot::TabContainer
{
  GDCLASS(OptionsMenu, TabContainer)

 public:
  enum AudioBuses
  {
    MASTER_BUS,
    MUSIC_BUS,
    EFFECTS_BUS
  };

  enum CalledFrom
  {
    TITLE_SCREEN,
    LEVEL
  };

  godot::Signal back_to_title_screen;
  godot::Signal back_to_level;

  void _ready() override;
  void _input();

  void set_current_context(CalledFrom context);
  CalledFrom get_current_context();

 private:
  UserConfig* config = nullptr;
  godot::ConfigFile* config_file = nullptr;
  godot::VBoxContainer* DisplayVBox;
  godot::VBoxContainer* AudioVBox;
  CalledFrom m_context = TITLE_SCREEN;

  const godot::String custom_cursor_image = "res://art/custom_cursor.png";

  void set_current_selected();

  void change_fullscreen(bool toggled_on);

  void change_custom_cursor(bool toggled_on);

  void change_vsync(bool toggled_on);

  void change_master_volume(bool value_changed);

  void change_music_volume(bool value_changed);

  void change_effects_volume(bool value_changed);

 protected:
  static void _bind_methods();
};

VARIANT_ENUM_CAST(OptionsMenu::AudioBuses);
VARIANT_ENUM_CAST(OptionsMenu::CalledFrom);
