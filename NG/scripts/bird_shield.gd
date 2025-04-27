extends Area2D

signal shield_used

func _ready() -> void:
  move_local_y(24)
  shield_used.connect(get_parent().deactivate_shield)

func _on_body_entered(body: Node2D) -> void:
  call_deferred("emit_signal", "shield_used", body)
  call_deferred("queue_free")
