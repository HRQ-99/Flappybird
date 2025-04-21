extends HSplitContainer

@export var achievement:BaseAchievement


func _ready() -> void:
  name=achievement.name
  $VBox/Name.text=achievement.name
  $Texture.texture=achievement.sprite
  $VBox/AchivementText.text=achievement.text
  
  if (achievement.unlocked):
    $VBox/AchivementText.visible=true
