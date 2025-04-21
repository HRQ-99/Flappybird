#include "user_config.h"

#include "godot_cpp/classes/audio_server.hpp"
#include "godot_cpp/classes/display_server.hpp"
#include "godot_cpp/classes/file_access.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "options_menu.h"

using namespace godot;

UserConfig::~UserConfig()
{
  m_options.clear();
  memdelete(config);
}

void UserConfig::_ready()
{
  if (!FileAccess::file_exists(SETTINGS_PATH))
  {
    create_default_config();
  }
  else
  {
    config->load(SETTINGS_PATH);
    load_user_config();
  }
}

void UserConfig::load_user_config()
{
  PackedStringArray display_section_keys = config->get_section_keys("display");
  bool fullscreen = config->get_value("display", m_options [UserConfig::FULLSCREEN]);
  bool custom_cursor = config->get_value("display", m_options [UserConfig::CUSTOM_CURSOR]);
  bool vsync = config->get_value("display", m_options [UserConfig::VSYNC]);
  if (fullscreen)
  {
    DisplayServer::get_singleton()->window_set_mode(godot::DisplayServer::WINDOW_MODE_EXCLUSIVE_FULLSCREEN);
  }
  else
  {
    DisplayServer::get_singleton()->window_set_mode(godot::DisplayServer::WINDOW_MODE_MAXIMIZED);
  }
  if (custom_cursor)
  {
    DisplayServer::get_singleton()->cursor_set_custom_image(ResourceLoader::get_singleton()->load(custom_cursor_image));
  }
  else
  {
    DisplayServer::get_singleton()->cursor_set_custom_image(nullptr);
  }
  if (vsync)
  {
    DisplayServer::get_singleton()->window_set_vsync_mode(godot::DisplayServer::VSYNC_ENABLED);
  }
  else
  {
    DisplayServer::get_singleton()->window_set_vsync_mode(godot::DisplayServer::VSYNC_DISABLED);
  }

  PackedStringArray audio_section_keys = config->get_section_keys("audio");
  float master_volume = config->get_value("audio", audio_section_keys.get((int)OptionsMenu::MASTER_BUS));
  float music_volume = config->get_value("audio", audio_section_keys.get((int)OptionsMenu::MUSIC_BUS));
  float effects_volume = config->get_value("audio", audio_section_keys.get((int)OptionsMenu::EFFECTS_BUS));
  AudioServer::get_singleton()->set_bus_volume_db((int)OptionsMenu::MASTER_BUS, Math::linear2db(master_volume));
  AudioServer::get_singleton()->set_bus_volume_db((int)OptionsMenu::MUSIC_BUS, Math::linear2db(music_volume));
  AudioServer::get_singleton()->set_bus_volume_db((int)OptionsMenu::EFFECTS_BUS, Math::linear2db(effects_volume));
}

void UserConfig::create_default_config()
{
  config->set_value("display", m_options [FULLSCREEN], true);
  config->set_value("display", m_options [CUSTOM_CURSOR], true);
  config->set_value("display", m_options [VSYNC], true);

  config->set_value("audio", m_options [MASTER_VOLUME], 1);
  config->set_value("audio", m_options [MUSIC_VOLUME], 1);
  config->set_value("audio", m_options [EFFECTS_VOLUME], 1);

  config->save(SETTINGS_PATH);
}

void UserConfig::save_display_config(Options key, Variant value)
{
  config->set_value("display", m_options [key], value);
  config->save(SETTINGS_PATH);
}

void UserConfig::save_audio_config(Options key, Variant value)
{
  config->set_value("audio", m_options [key], value);
  config->save(SETTINGS_PATH);
}

void UserConfig::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("load_user_config"), &UserConfig::load_user_config);

  ClassDB::bind_method(D_METHOD("create_default_config"), &UserConfig::create_default_config);

  ClassDB::bind_method(D_METHOD("save_display_config", "key", "value"), &UserConfig::save_display_config);

  ClassDB::bind_method(D_METHOD("save_audio_config", "key", "value"), &UserConfig::save_audio_config);

  ClassDB::bind_method(D_METHOD("get_user_config"), &UserConfig::get_user_config);

  BIND_ENUM_CONSTANT(FULLSCREEN);
  BIND_ENUM_CONSTANT(CUSTOM_CURSOR);
  BIND_ENUM_CONSTANT(VSYNC);

  BIND_ENUM_CONSTANT(MASTER_VOLUME);
  BIND_ENUM_CONSTANT(MUSIC_VOLUME);
  BIND_ENUM_CONSTANT(EFFECTS_VOLUME);
}

ConfigFile* UserConfig::get_user_config() { return config; }
