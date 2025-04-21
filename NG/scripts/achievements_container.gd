extends VBoxContainer

var achivement_scene:PackedScene = preload("res://scenes/base_achievement.tscn")
var achieves_dir:String = "res://achievements/"
var achievements:Array=[]

func _ready() -> void:
  var dir:DirAccess=DirAccess.open(achieves_dir)
  
  dir.list_dir_begin()
  var file_name:String =dir.get_next()
  while(file_name!=""):
    if (!dir.current_is_dir() && file_name.ends_with(".tres")):
      
      var file_path:String=achieves_dir+file_name
      var achievement:BaseAchievement=load(file_path)
      if (achievement):
        achievements.append(achievement)
        
    file_name=dir.get_next()
    
  for tmp_achievement in achievements:
    var achieve_node=achivement_scene.instantiate()
    achieve_node.achievement=tmp_achievement
    add_child(achieve_node)
    
