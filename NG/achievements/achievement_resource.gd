@tool
extends Resource
class_name BaseAchievement

@export var name:String
@export var sprite:Texture2D
@export var text:String
@export var unlocked:bool

func achieved()->void:
  unlocked = true
