extends CanvasLayer

const LEVEL = preload("res://scenes/level.tscn")
const OPTIONS_MENU = preload("res://scenes/options_menu.tscn")
const ACHIEVEMENTS = preload("res://scenes/achievements.tscn")

signal starting_level
signal changing_settings

func _ready() -> void:
  get_node("UI-Center/UI-VBox/StartButton").grab_focus()

func _on_start_button_pressed() -> void:
  var lvl :Level= LEVEL.instantiate()
  get_tree().current_scene.add_child(lvl)
  starting_level.emit()

func _on_options_button_pressed() -> void:
  var opts=OPTIONS_MENU.instantiate() as OptionsMenu
  opts.current_context=OptionsMenu.TITLE_SCREEN
  get_tree().current_scene.add_child(opts)
  changing_settings.emit()
  
func _on_achievements_button_pressed() -> void:
  var achievements: = ACHIEVEMENTS.instantiate()
  get_tree().current_scene.add_child(achievements)
  changing_settings.emit()
  

func _on_exit_button_pressed() -> void:
  GameCleanup.new().exit_game()
  get_tree().quit()
