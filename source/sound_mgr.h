/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef SOUND_MGR_H
#define SOUND_MGR_H

#include "math/vector.h"
#include <fmodex/fmod.h>

struct sound_mgr {
  struct FMOD_SYSTEM*	fmod_sound;
};

struct sound {
  struct FMOD_SOUND* fmod_snd;
};

struct speaker {
  vec3 velocity;
  struct FMOD_CHANNEL* fmod_channel;
};

// void speaker_play_sound(sc_obj* _speaker, sound* _snd);
FMOD_CHANNEL* speaker_play_fmod(struct ngine_sc_obj* _speaker, FMOD_SYSTEM* _fmod_sys, FMOD_SOUND* _snd, char _paused);

// struct sound* sound_create(sound_mgr* _snd_mgr, char* _snd_name, uint32_t _fmod_mode, char _paused);

#endif // SOUND_MGR_H
