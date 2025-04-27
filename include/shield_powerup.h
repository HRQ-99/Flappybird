#include "base_powerups.h"
#include "bird.h"

class Shield : public BasePowerUps
{
  GDCLASS(Shield, BasePowerUps)

 public:
  void _ready() override;

 private:
  Bird* m_bird = nullptr;
  godot::Node* bird_shield = nullptr;
  const godot::String bird_shield_path = "uid://drjsjv5i2ksf";

  void activate_power(godot::Node2D* body_entered) override;

  static void _bind_methods();
};
