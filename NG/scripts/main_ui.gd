extends CanvasLayer

const level_scene = "uid://cwhmyaen74sbb"
var level:= preload(level_scene)

func _on_start_button_pressed() -> void:
 var lvl := level.instantiate()
 add_child(lvl)



func _on_achievements_button_pressed() -> void:
  pass # Replace with function body.


func _on_options_button_pressed() -> void:
  pass # Replace with function body.

func _on_exit_button_pressed() -> void:
  GameCleanup.new().exit_game()
  get_tree().quit()
