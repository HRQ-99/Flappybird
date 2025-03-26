#include "options_menu.h"

#include "godot_cpp/classes/audio_server.hpp"
#include "godot_cpp/classes/check_box.hpp"
#include "godot_cpp/classes/display_server.hpp"
#include "godot_cpp/classes/h_slider.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;

void OptionsMenu::_ready()
{
  config = get_node<UserConfig>("/root/Game/UserConfig");
  config_file = config->UserConfig::get_user_config();

  connect("back_to_title_screen", Callable(get_tree()->get_current_scene(), "change_settings"));
  DisplayVBox = get_node<VBoxContainer>("Display/DisplayVBox");
  AudioVBox = get_node<VBoxContainer>("Audio/AudioVBox");

  DisplayVBox->get_node<CheckBox>("Fullscreen/CheckBox")->connect("toggled", Callable(this, "change_fullscreen"));
  DisplayVBox->get_node<CheckBox>("CustomCursor/CheckBox")->connect("toggled", Callable(this, "change_custom_cursor"));
  DisplayVBox->get_node<CheckBox>("Vsync/CheckBox")->connect("toggled", Callable(this, "change_vsync"));

  AudioVBox->get_node<HSlider>("MasterVolume/Slider")->connect("drag_ended", Callable(this, "change_master_volume"));
  AudioVBox->get_node<HSlider>("MusicVolume/Slider")->connect("drag_ended", Callable(this, "change_music_volume"));
  AudioVBox->get_node<HSlider>("EffectsVolume/Slider")->connect("drag_ended", Callable(this, "change_effects_volume"));

  set_current_selected();
}

void OptionsMenu::_input()
{
  if (Input::get_singleton()->is_action_just_pressed("Escape"))
  {
    set_visible(false);
    emit_signal("back_to_title_screen");
    call_deferred("queue_free");
  }
}

void OptionsMenu::set_current_selected()
{
  PackedStringArray display_section_keys = config_file->get_section_keys("display");
  DisplayVBox->get_node<CheckBox>("Fullscreen/CheckBox")
    ->set_pressed(config_file->get_value("display", config->UserConfig::m_options [UserConfig::FULLSCREEN]));
  DisplayVBox->get_node<CheckBox>("CustomCursor/CheckBox")
    ->set_pressed(config_file->get_value("display", config->UserConfig::m_options [UserConfig::CUSTOM_CURSOR]));
  DisplayVBox->get_node<CheckBox>("Vsync/CheckBox")
    ->set_pressed(config_file->get_value("display", config->UserConfig::m_options [UserConfig::VSYNC]));

  PackedStringArray audio_section_keys = config_file->get_section_keys("audio");

  AudioVBox->get_node<HSlider>("MasterVolume/Slider")
    ->set_value_no_signal(
      100 * (float)config_file->get_value("audio", config->UserConfig::m_options [UserConfig::MASTER_VOLUME]));
  AudioVBox->get_node<HSlider>("MusicVolume/Slider")
    ->set_value_no_signal(
      100 * (float)config_file->get_value("audio", config->UserConfig::m_options [UserConfig::MUSIC_VOLUME]));
  AudioVBox->get_node<HSlider>("EffectsVolume/Slider")
    ->set_value_no_signal(
      100 * (float)config_file->get_value("audio", config->UserConfig::m_options [UserConfig::EFFECTS_VOLUME]));
}

void OptionsMenu::change_fullscreen(bool toggled_on)
{
  if (toggled_on)
  {
    DisplayServer::get_singleton()->window_set_mode(godot::DisplayServer::WINDOW_MODE_EXCLUSIVE_FULLSCREEN);
  }
  else
  {
    DisplayServer::get_singleton()->window_set_mode(godot::DisplayServer::WINDOW_MODE_MAXIMIZED);
  }

  config->save_display_config(UserConfig::FULLSCREEN, toggled_on);
}

void OptionsMenu::change_custom_cursor(bool toggled_on)
{
  config->save_display_config(UserConfig::CUSTOM_CURSOR, toggled_on);
}

void OptionsMenu::change_vsync(bool toggled_on)
{
  if (toggled_on)
  {
    DisplayServer::get_singleton()->window_set_vsync_mode(godot::DisplayServer::VSYNC_ENABLED);
  }
  else
  {
    DisplayServer::get_singleton()->window_set_vsync_mode(godot::DisplayServer::VSYNC_DISABLED);
  }

  config->save_display_config(UserConfig::VSYNC, toggled_on);
}

void OptionsMenu::change_master_volume(bool value_changed)
{
  if (value_changed)
  {
    float slider_value = AudioVBox->get_node<HSlider>("MasterVolume/Slider")->get_value() / 100;
    AudioServer::get_singleton()->set_bus_volume_db((int)MASTER_BUS, Math::linear2db(slider_value));
    config->save_audio_config(UserConfig::MASTER_VOLUME, slider_value);
  }
}

void OptionsMenu::change_music_volume(bool value_changed)
{
  float slider_value = AudioVBox->get_node<HSlider>("MusicVolume/Slider")->get_value() / 100;
  AudioServer::get_singleton()->set_bus_volume_db((int)MUSIC_BUS, Math::linear2db(slider_value));
  config->save_audio_config(UserConfig::MUSIC_VOLUME, slider_value);
}

void OptionsMenu::change_effects_volume(bool value_changed)
{
  float slider_value = AudioVBox->get_node<HSlider>("EffectsVolume/Slider")->get_value() / 100;
  AudioServer::get_singleton()->set_bus_volume_db((int)EFFECTS_BUS, Math::linear2db(slider_value));
  config->save_audio_config(UserConfig::EFFECTS_VOLUME, slider_value);
}

void OptionsMenu::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("set_current_selected"), &OptionsMenu::set_current_selected);

  ClassDB::bind_method(D_METHOD("change_fullscreen", "toggled_on"), &OptionsMenu::change_fullscreen);

  ClassDB::bind_method(D_METHOD("change_custom_cursor", "toggled_on"), &OptionsMenu::change_custom_cursor);

  ClassDB::bind_method(D_METHOD("change_vsync", "toggled_on"), &OptionsMenu::change_vsync);

  ClassDB::bind_method(D_METHOD("change_master_volume", "value_changed"), &OptionsMenu::change_master_volume);

  ClassDB::bind_method(D_METHOD("change_music_volume", "value_changed"), &OptionsMenu::change_music_volume);

  ClassDB::bind_method(D_METHOD("change_effects_volume", "value_changed"), &OptionsMenu::change_effects_volume);

  ADD_SIGNAL(MethodInfo("back_to_title_screen"));

  BIND_ENUM_CONSTANT(MASTER_BUS);
  BIND_ENUM_CONSTANT(MUSIC_BUS);
  BIND_ENUM_CONSTANT(EFFECTS_BUS);
}
