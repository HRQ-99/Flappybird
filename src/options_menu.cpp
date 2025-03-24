#include "options_menu.h"

#include "godot_cpp/classes/check_box.hpp"
#include "godot_cpp/classes/h_slider.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;

void OptionsMenu::_ready()
{
  connect("back_to_title_screen", Callable(get_tree()->get_current_scene(), "change_settings"));
  DisplayVBox = get_node<VBoxContainer>("Display/DisplayVBox");
  AudioVBox = get_node<VBoxContainer>("Audio/AudioVBox");

  DisplayVBox->get_node<CheckBox>("Fullscreen/CheckBox")->connect("toggled", Callable(this, "change_fullscreen"));
  DisplayVBox->get_node<CheckBox>("CustomCursor/CheckBox")->connect("toggled", Callable(this, "change_custom_cursor"));
  DisplayVBox->get_node<CheckBox>("Vsync/CheckBox")->connect("toggled", Callable(this, "change_vsync"));

  AudioVBox->get_node<HSlider>("MasterVolumer/Slider")->connect("drag_ended", Callable(this, "change_master_volume"));
  AudioVBox->get_node<HSlider>("MusicVolumer/Slider")->connect("drag_ended", Callable(this, "change_music_volume"));
  AudioVBox->get_node<HSlider>("EffectsVolumer/Slider")->connect("drag_ended", Callable(this, "change_effects_volume"));
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

void OptionsMenu::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("change_fullscreen", "toggled_on"), &OptionsMenu::change_fullscreen);

  ClassDB::bind_method(D_METHOD("change_custom_cursor", "toggled_on"), &OptionsMenu::change_custom_cursor);

  ClassDB::bind_method(D_METHOD("change_vsync", "toggled_on"), &OptionsMenu::change_vsync);

  ClassDB::bind_method(D_METHOD("change_master_volume", "value_changed"), &OptionsMenu::change_master_volume);

  ClassDB::bind_method(D_METHOD("change_music_volume", "value_changed"), &OptionsMenu::change_music_volume);

  ClassDB::bind_method(D_METHOD("change_effects_volume", "value_changed"), &OptionsMenu::change_effects_volume);

  ADD_SIGNAL(MethodInfo("back_to_title_screen"));
}

void OptionsMenu::change_fullscreen(bool toggled_on) { print_line(toggled_on); }

void OptionsMenu::change_custom_cursor(bool toggled_on) {}

void OptionsMenu::change_vsync(bool toggled_on) {}

void OptionsMenu::change_master_volume(bool value_changed) {}

void OptionsMenu::change_music_volume(bool value_changed) {}

void OptionsMenu::change_effects_volume(bool value_changed) {}
