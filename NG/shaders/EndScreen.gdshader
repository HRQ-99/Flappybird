shader_type canvas_item;

uniform vec2 tiled_factor =vec2(.9,.9);
uniform float aspect_ratio = 0.5625;
uniform vec2 time_scale =vec2(1.0,1.0);
uniform vec2 offset_scale = vec2(2.0, 4.0);
uniform vec2 amplitude = vec2(.04, .05);

void vertex() {}

void fragment() {
  vec2 tiled_uv = UV * tiled_factor;
  tiled_uv.y*=aspect_ratio;

  vec2 waves_offset;
  waves_offset.x=cos(TIME * time_scale.x + tiled_uv.x + tiled_uv.y) * offset_scale.x;
  waves_offset.y=sin(TIME *time_scale.y + tiled_uv.x + tiled_uv.y) * offset_scale.y;

  COLOR=texture(TEXTURE, tiled_uv + waves_offset * amplitude);
}
