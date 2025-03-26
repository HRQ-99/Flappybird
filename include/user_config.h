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

  // godot::Dictionary m_options =
  // godot::Dictionary(godot::Dictionary(), godot::Variant::INT, godot::StringName("Options"), godot::Variant(),
  // godot::Variant::STRING, godot::StringName("String"), godot::Variant());
  godot::Dictionary m_options;
  void _ready() override;

  void load_user_config();

  void save_display_config(Options key, godot::Variant value);
  void load_display_config();

  void save_audio_config(Options key, godot::Variant value);
  void load_audio_config();

  godot::ConfigFile* get_user_config();

 private:
  UserConfig();
  ~UserConfig();

  godot::ConfigFile* config = memnew(godot::ConfigFile);

  void create_default_config();

 protected:
  static void _bind_methods();
};
VARIANT_ENUM_CAST(UserConfig::Options);
