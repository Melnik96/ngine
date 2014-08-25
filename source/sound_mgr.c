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

#include <fmodex/fmod.h>

#include "sc_node.h"

#include "sound_mgr.h"

// struct sound* sound_create(sound_mgr* _self, char* _snd_name, uint32_t _fmod_mode, char _paused) {
//   struct sound* new_snd = calloc(1, sizeof(struct sound));
//   FMOD_System_CreateSound(_self->fmod_sound, _snd_name, _fmod_mode, 0, &new_snd->fmod_snd);
// }

// void speaker_play_sound(struct sc_obj* _speaker, struct sound* _snd) {
//   FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, _snd->fmod_snd, 0, &channel);
// }

FMOD_CHANNEL* speaker_play_fmod(struct ngine_sc_node* _speaker, FMOD_SYSTEM* _fmod_sys, FMOD_SOUND* _snd, char _paused) {
  FMOD_CHANNEL* channel = NULL;
  FMOD_System_PlaySound(_fmod_sys, FMOD_CHANNEL_FREE, _snd, 1, &channel);
  FMOD_Channel_Set3DAttributes(channel, &_speaker->pos, &(vec3){0,0,0});
  
  _speaker->attached_obj = channel;
  
  if(!_paused) {
    FMOD_Channel_SetPaused(channel, 0);
  }
  
  return channel;
}
