#include "register_types.h"

#include <gdextension_interface.h>

#include "bird.h"
#include "level.h"
#include "options_menu.h"
#include "speed_boost.h"

using namespace godot;

void initialize_module(ModuleInitializationLevel p_level)
{
  if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
  {
    return;
  }

  GDREGISTER_RUNTIME_CLASS(Bird);
  GDREGISTER_RUNTIME_CLASS(Level);
  GDREGISTER_RUNTIME_CLASS(SpeedBoost);
  GDREGISTER_RUNTIME_CLASS(OptionsMenu);
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
