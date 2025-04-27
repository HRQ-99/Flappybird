#include "register_types.h"

#include <gdextension_interface.h>

#include "achievement_manager.h"
#include "base_powerups.h"
#include "bird.h"
#include "boost_trail.h"
#include "difficulty_manager.h"
#include "level.h"
#include "options_menu.h"
#include "pipe_destroyer.h"
#include "powerup_spawn_boost.h"
#include "powerups.h"
#include "save_game.h"
#include "score_boost.h"
#include "shield_powerup.h"
#include "speed_boost.h"
#include "user_config.h"

using namespace godot;

void initialize_module(ModuleInitializationLevel p_level)
{
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
  {
    return;
  }

  GDREGISTER_RUNTIME_CLASS(Bird);
  GDREGISTER_RUNTIME_CLASS(Level);
  GDREGISTER_RUNTIME_CLASS(OptionsMenu);
  GDREGISTER_RUNTIME_CLASS(UserConfig);
  GDREGISTER_RUNTIME_CLASS(SaveGame);
  GDREGISTER_RUNTIME_CLASS(DifficultyManager);
  GDREGISTER_RUNTIME_CLASS(AchievementManager);

  GDREGISTER_RUNTIME_CLASS(BasePowerUps);
  GDREGISTER_RUNTIME_CLASS(PowerUps);
  GDREGISTER_RUNTIME_CLASS(SpeedBoost);
  GDREGISTER_RUNTIME_CLASS(ScoreBoost);
  GDREGISTER_RUNTIME_CLASS(PowerUpSpawnBoost);
  GDREGISTER_RUNTIME_CLASS(PipeDestroyer);
  GDREGISTER_RUNTIME_CLASS(Shield);

  GDREGISTER_RUNTIME_CLASS(BoostTrail);
}

void uninitialize_module(ModuleInitializationLevel p_level)
{
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
  {
    return;
  }
}

extern "C"
{
  // Initialization.
  GDExtensionBool GDE_EXPORT NEXTGAME_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                                           const GDExtensionClassLibraryPtr p_library,
                                           GDExtensionInitialization *r_initialization)
  {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_module);
    init_obj.register_terminator(uninitialize_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
  }
}
