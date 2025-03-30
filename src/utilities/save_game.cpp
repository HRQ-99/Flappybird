#include "save_game.h"

#include "godot_cpp/classes/file_access.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/resource_saver.hpp"

using namespace godot;

void SaveGame::save_game(float game_score)
{
  if (FileAccess::file_exists(SAVE_DIRE))
  {
    Ref<SaveGame> save_file = (ResourceLoader::get_singleton()->load(SAVE_DIRE));

    Array attempt_number_array = save_file->m_attempt_number;
    Array score_array = save_file->m_game_score;

    attempt_number_array.append((int)attempt_number_array.get(attempt_number_array.size() - 1) + 1);
    score_array.append((int)game_score);

    ResourceSaver::get_singleton()->save(save_file, SAVE_DIRE);
    return;
  }

  Ref<SaveGame> save_file;
  save_file.instantiate();

  save_file->m_attempt_number.append(1);
  save_file->m_game_score.append((int)game_score);

  ResourceSaver::get_singleton()->save(save_file, SAVE_DIRE);

  // memdelete(save_file);
}

void SaveGame::_bind_methods()
{
  ClassDB::bind_method(godot::D_METHOD("save_game", "game_score"), &SaveGame::save_game);

  ClassDB::bind_method(D_METHOD("get_attempt_number"), &SaveGame::get_attempt_number);
  ClassDB::bind_method(D_METHOD("set_attempt_number", "value"), &SaveGame::set_attempt_number);
  ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "m_attempt_number"), "set_attempt_number", "get_attempt_number");

  ClassDB::bind_method(D_METHOD("get_game_score"), &SaveGame::get_game_score);
  ClassDB::bind_method(D_METHOD("set_game_score", "value"), &SaveGame::set_game_score);
  ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "m_game_score"), "set_game_score", "get_game_score");
}

void SaveGame::set_attempt_number(const Array &value) { m_attempt_number = value; }
Array SaveGame::get_attempt_number() const { return m_attempt_number; }

void SaveGame::set_game_score(const Array &value) { m_game_score = value; }
Array SaveGame::get_game_score() const { return m_game_score; }
