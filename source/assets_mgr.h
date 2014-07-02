#ifndef __ASSETS_MGR_H__
#define __ASSETS_MGR_H__

enum ngine_asset_type {
  NGINE_MODEL_ASSET = 0,
  NGINE_IMAGE_ASSET = 1,
  NGINE_FONT_ASSET = 2,
  NGINE_SOUND_ASSET = 3,
  NGINE_SHADER_ASSET = 4,
};

struct ngine_asset_src {
  int 	type;
  char* url;
};

struct ngine_assets_mgr {
  struct ngine_asset_src* sources; int src_num;
};

struct ngine_assets_mgr* 	ngine_assets_mgr_create();
void 				ngine_assets_mgr_add_source(struct ngine_assets_mgr* _self, int _type, const char* _url);
// return FILE or sock
int 				ngine_assets_mgr_get_file(struct ngine_assets_mgr* _self, int _type, const char* _name);
// files over network transmit p2p protocol

#endif /* __ASSETS_MGR__ */
