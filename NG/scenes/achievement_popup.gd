extends PopupPanel

func _ready() -> void:
  var tween:Tween=create_tween()
  tween.tween_property(self, "position", Vector2i(475,0), 0.20)
  
  await get_tree().create_timer(1.0).timeout
  call_deferred("queue_free")
