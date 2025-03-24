#pragma once

#include "godot_cpp/classes/config_file.hpp"
#include "godot_cpp/classes/node.hpp"

class UserConfig : public godot::Node
{
  GDCLASS(UserConfig, godot::Node)

 public:
  const godot::String SETTINGS_PATH = "user://settings.ini";

  enum Sections
  {
    DISPLAY,
    AUDIO
  };
  enum Options
  {
    FULLSCREEN,
    CUSTOM_CURSOR,
    VSYNC,
    MASTER_VOLUME,
    MUSIC_VOLUME,
    EFFECTS_VOLUME
  };

  void _ready() override;

 private:
  godot::ConfigFile* config;
  void create_default_config();

  void save_display_config(godot::String key, godot::Variant value);
  void load_display_config();

  void save_audio_config(godot::String key, godot::Variant value);
  void load_audio_config();

 protected:
  static void _bind_methods();
};
