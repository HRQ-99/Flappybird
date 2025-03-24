extends TabContainer

@onready var fullscreen_checkbox:= $Display/DisplayVBox/Fullscreen/CheckBox
@onready var custom_cursor_checbkox:=$Display/DisplayVBox/CustomCursor/CheckBox
@onready var vsync_checkbox:=$Display/DisplayVBox/Vsync/CheckBox

@onready var master_volume_slider:=$Audio/AudioVBox/MasterVolume/Slider
@onready var music_volume_slider:=$Audio/AudioVBox/MusicVolume/Slider
@onready var effects_volume_slider:=$Audio/AudioVBox/EffectsVolume/Slider

#func change_fullscreen(toggled_on: bool) -> void:
  #pass # Replace with function body.
#
#func change_custom_cursor(toggled_on: bool) -> void:
  #pass # Replace with function body.
#
#func change_vsync(toggled_on: bool) -> void:
  #pass # Replace with function body.
#
#func change_master_volume(value_changed: bool) -> void:
  #pass # Replace with function body.
#
#func change_music_volume(value_changed: bool) -> void:
  #pass # Replace with function body.
#
#func change_effects_volume(value_changed: bool) -> void:
  #pass # Replace with function body.
