extends Level

const pipe_scene_path:String = "uid://b3bholrqdxicg"
const pipe_scene:PackedScene = preload(pipe_scene_path)

const options_scene = "uid://bp6in13yhxgjd"
var options:PackedScene =preload(options_scene)

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
  
func increase_score() -> void:
  score+=1
  $"Level-UI/HBox/Score".text = "Score:" + var_to_str(score)
  
func toggle_invincible_label()->void:
  $"Level-UI/HBox/Godmode".visible = !$"Level-UI/HBox/Godmode".visible

func changing_settings() -> void:
  var opts=options.instantiate() as OptionsMenu
  opts.current_context=OptionsMenu.LEVEL
  get_parent().add_child(opts)
  
  $"Pause Screen".visible = false
  $"Level-UI".visible = false
  get_node("Bird/Camera").set_enabled(false)

func back_from_options() -> void:
  $"Pause Screen".visible = true
  $"Level-UI".visible = true
  get_node("Bird/Camera").set_enabled(true)
