#include "user_config.h"

#include "godot_cpp/classes/file_access.hpp"

using namespace godot;

void UserConfig::_ready()
{
  if (!FileAccess::file_exists(SETTINGS_PATH))
  {
    create_default_config();
  }
  else
  {
    config->load(SETTINGS_PATH);
  }
}

void UserConfig::create_default_config() {}

void UserConfig::save_display_config(String key, Variant value)
{
  config->set_value("display", key, value);
  config->save(SETTINGS_PATH);
}
void UserConfig::load_display_config() {}

void UserConfig::save_audio_config(String key, Variant value)
{
  config->set_value("display", key, value);
  config->save(SETTINGS_PATH);
}
void UserConfig::load_audio_config() {}

void UserConfig::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("create_default_config"), &UserConfig::create_default_config);

  ClassDB::bind_method(D_METHOD("save_display_config", "key", "value"), &UserConfig::save_display_config);
  ClassDB::bind_method(D_METHOD("load_display_config"), &UserConfig::load_display_config);

  ClassDB::bind_method(D_METHOD("save_audio_config", "key", "value"), &UserConfig::save_audio_config);
  ClassDB::bind_method(D_METHOD("load_audio_config"), &UserConfig::load_audio_config);
}
