extends Node

var backgrounds={
  "level": preload("res://art/background_1.png"),
  "game":preload("res://art/background_2.png")
}

func change_background(key:String)-> void:
  get_node("Background/BackgroundSprite").set_texture(backgrounds[key])

func starting_level()->void:
  change_background("level")
  $MainUI.visible=false
  
func change_settings()->void:
  $MainUI.visible= not $MainUI.visible
  $Background/BackgroundSprite.flip_h = not $Background/BackgroundSprite.flip_h
  
func back_to_title_screen()->void:
  change_background("game")
  $MainUI.visible=true
