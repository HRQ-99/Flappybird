@tool
extends Sprite2D

func changing_shader_aspect_ratio() -> void:
  material.set_shader_param("aspect_ratio", scale.y/scale.x)
