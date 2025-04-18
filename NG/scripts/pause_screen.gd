extends CanvasLayer

signal changing_settins
signal back_to_title_screen

func _ready() -> void:
  back_to_title_screen.connect(get_node("/root/Game/").back_to_title_screen)
  $CenterContainer/VBoxContainer/RestartButton.connect("pressed" , get_tree().current_scene.restart_level)
  
func _input(event: InputEvent) -> void:
  if (event.is_action_pressed("Escape")):
    get_parent().call(StringName("set_game_paused_state"), !get_parent().game_paused)

func _on_resume_button_pressed() -> void:
  get_parent().call(StringName("set_game_paused_state"), false)
  
func _on_options_button_pressed() -> void:
  changing_settins.emit()
  
func _on_go_to_title_button_pressed() -> void:
  get_tree().paused=false
  back_to_title_screen.emit()
  get_parent().queue_free()

func _on_exit_game_button_pressed() -> void:
  GameCleanup.new().exit_game()
  get_tree().quit()
