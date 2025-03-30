extends CanvasLayer

signal back_to_title_screen
signal restart_level

func _ready() -> void:
  back_to_title_screen.connect(get_node("/root/Game/").back_to_title_screen)
  restart_level.connect(get_parent().restart_level)

func _input(event: InputEvent) -> void:
  if (event.is_action_pressed("Restart")):
    restart_level.emit()
    
  if (event.is_action_pressed("Escape")):
    back_to_title_screen.emit()
    get_parent().queue_free()
