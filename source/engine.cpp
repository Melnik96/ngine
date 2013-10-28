// #include "import/blender/bBlenderFile.h"
// #include "import/blender/bMain.h"
// #include "import/blender/blend263/Blender.h"
// 
// #include "engine.h"
// 
// int neng_deserialize_blend(struct sc_obj* _top_obj, void* _blend) {
//   bParse::bBlenderFile bf(_blend);
//   bf.parse(0);
//   if(!bf.ok()) { printf("import blender file error\n"); }
//   
//   bParse::bMain* bm = bf.getMain();
//   
//   Blender::Scene* sc = bm->getScene();
//   
// //   sc->obedit->mat->;
//   
//   /**
//    * 1. objects(entity, cameras, lights) with parent-childs model
//    * 2. materials(color, phys data)
//    * 3. logic
//    */
// }
