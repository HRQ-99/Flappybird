extends Node

const level_scene_path:String = "uid://cwhmyaen74sbb"
const level_scene:PackedScene = preload(level_scene_path)

var backgrounds={
  "level": preload("res://art/background_1.png"),
  "game":preload("res://art/background_2.png")
}

func change_background(key:String)-> void:
  get_node("Background/BackgroundSprite").set_texture(backgrounds[key])

func starting_level()->void:
  change_background("level")
  $MainUI.visible=false
  
func restart_level() -> void:
  get_tree().paused=false
  get_tree().get_first_node_in_group("Level").queue_free()
  var lvl:Level=level_scene.instantiate()
  add_child(lvl)
  
func change_settings()->void:
  $MainUI.visible= not $MainUI.visible
  $Background/BackgroundSprite.flip_h = not $Background/BackgroundSprite.flip_h
  
func back_to_title_screen()->void:
  change_background("game")
  $MainUI.visible=true
