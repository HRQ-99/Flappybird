extends Level

const pipe_scene_path: ="uid://b3bholrqdxicg"
const pipe_scene:=preload(pipe_scene_path)

func _physics_process(_delta: float) -> void:
 pass

func make_pipe_pair()->Node2D:
  printerr("here")
  var top_pipe:=pipe_scene.instantiate() as StaticBody2D
  top_pipe.rotation_degrees=180
  top_pipe.position.y=0

  var bottom_pipe:=pipe_scene.instantiate() as StaticBody2D
  bottom_pipe.position.y=0

  var pipe_pair:Node2D= Node2D.new()
  pipe_pair.add_children(top_pipe,bottom_pipe)
  pipe_pair.position.y=300
  pipe_pair.scale=Vector2(5,7)

  #pipes_container.add_child(pipe_pair)
  return pipe_pair
