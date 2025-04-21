#pragma once

#include "godot_cpp/classes/config_file.hpp"
#include "godot_cpp/classes/node.hpp"

class UserConfig : public godot::Node
{
  GDCLASS(UserConfig, godot::Node)

 public:
  const godot::String SETTINGS_PATH = "user://settings.ini";

  enum Options
  {
    FULLSCREEN,
    CUSTOM_CURSOR,
    VSYNC,
    MASTER_VOLUME,
    MUSIC_VOLUME,
    EFFECTS_VOLUME
  };

  godot::Dictionary m_options = [] {
    godot::Dictionary dict;
    dict [FULLSCREEN] = "fullscreen";
    dict [CUSTOM_CURSOR] = "custom_cursor";
    dict [VSYNC] = "vsync";
    dict [MASTER_VOLUME] = "master_volume";
    dict [MUSIC_VOLUME] = "music_volume";
    dict [EFFECTS_VOLUME] = "effects_volume";
    return dict;
  }();

  void _ready() override;

  void load_user_config();

  void save_display_config(Options key, godot::Variant value);

  void save_audio_config(Options key, godot::Variant value);

  godot::ConfigFile* get_user_config();

 private:
  ~UserConfig();

  godot::ConfigFile* config = memnew(godot::ConfigFile);
  const godot::String custom_cursor_image = "res://art/custom_cursor.png";

  void create_default_config();

 protected:
  static void _bind_methods();
};
VARIANT_ENUM_CAST(UserConfig::Options);
