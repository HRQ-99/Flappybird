extends CanvasLayer
signal back_to_title_screen

func _ready() -> void:
  back_to_title_screen.connect(get_parent().change_settings)
  
func _input(event: InputEvent) -> void:
  if(event.is_action_pressed("Escape")):
    back_to_title_screen.emit()
    queue_free()
