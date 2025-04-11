extends CanvasLayer

const level_scene = "uid://cwhmyaen74sbb"
var level:PackedScene = preload(level_scene)

const options_scene = "uid://bp6in13yhxgjd"
var options:PackedScene =preload(options_scene)

signal starting_level
signal changing_settings

func _ready() -> void:
  get_node("UI-Center/UI-VBox/StartButton").grab_focus()

func _on_start_button_pressed() -> void:
  var lvl :Level= level.instantiate()
  get_tree().current_scene.add_child(lvl)
  starting_level.emit()

func _on_options_button_pressed() -> void:
  var opts=options.instantiate() as OptionsMenu
  opts.current_context=OptionsMenu.TITLE_SCREEN
  get_tree().current_scene.add_child(opts)
  changing_settings.emit()
  
func _on_achievements_button_pressed() -> void:
  pass # Replace with function body.

func _on_exit_button_pressed() -> void:
  GameCleanup.new().exit_game()
  get_tree().quit()
