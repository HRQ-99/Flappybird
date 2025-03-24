extends Level

const level_scene_path:String = "uid://cwhmyaen74sbb"
const level_scene:PackedScene = preload(level_scene_path)

const pipe_scene_path:String = "uid://b3bholrqdxicg"
const pipe_scene:PackedScene = preload(pipe_scene_path)

func _physics_process(_delta: float) -> void:
 pass

func make_pipe_pair()->Node2D:
  var top_pipe:=pipe_scene.instantiate() as StaticBody2D
  top_pipe.rotation_degrees=180
  top_pipe.position.y= randf_range(15,20)

  var bottom_pipe:=pipe_scene.instantiate() as StaticBody2D
  bottom_pipe.position.y= randf_range(40, 50)

  var pipe_pair:Node2D= Node2D.new()
  pipe_pair.add_child(top_pipe)
  pipe_pair.add_child(bottom_pipe)
  pipe_pair.scale=Vector2(4,5)

  return pipe_pair

func restart_level()->void:
  get_tree().paused=false
  var lvl:Level=level_scene.instantiate()
  get_tree().current_scene.add_child(lvl)
  call_deferred("queue_free")
  
func increase_score() -> void:
  score+=1
  $"Level-UI/HBox/Score".text = "Score:" + var_to_str(score)
