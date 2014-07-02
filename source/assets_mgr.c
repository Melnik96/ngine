#include "assets_mgr.h"

#include <malloc.h>
#include <string.h>
#include <stdio.h>

struct ngine_assets_mgr* assets_mgr_create() {
  struct ngine_assets_mgr* new_mgr = malloc(sizeof(struct ngine_assets_mgr));
  new_mgr->sources = NULL;
  new_mgr->src_num = 0;
}
void assets_mgr_add_source(struct ngine_assets_mgr* _self, int _type, const char* _url) {
  _self->sources = realloc(_self->sources, sizeof(struct ngine_asset_src)*(_self->src_num+1));
  _self->sources[_self->src_num].type = _type;
  _self->sources[_self->src_num].url  = _url;
  _self->src_num += 1;
}
int assets_mgr_get_file(struct ngine_assets_mgr* _self, int _type, const char* _name) {
  for(struct ngine_asset_src* cur_src = _self->sources; cur_src < _self->src_num*sizeof(struct ngine_asset_src); ++cur_src) {
    if(cur_src->type == _type) {
      int file = 0;
      if(file = fopen(strcat(cur_src->url, _name), "r+")) {
	return file;
      } else {
	continue;
      }
    }
  }
  return 0;
}
