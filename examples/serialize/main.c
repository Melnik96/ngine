#include "serialize.h"

enum g_type {
  GT_ACUSTIC,
  GT_ELECTRO
};

enum t_type {
  TT_REDWOOD,
  TT_ALDER
};

struct guitar {
  struct owner* owner;
  g_type type;
  char model[64];
  t_type tree;
  int num_strings;
  char color[16];
};

struct owner {
  char name[64];
};


int main() {
  struct owner Dima;
  struct owner Andriy;
  Dima.name = "Dmitro Melnichuk";
  Dima.name = "Andriy Moroz";
  
  struct guitar SX = {Dima,GT_ACUSTIC,"SX ...",TT_ALDER,6,"red"};
  struct guitar Ibanez = {Andriy,GT_ELECTRO,"Ibanez ...",TT_REDWOOD,6,"orange"};
  
  
  struct ptr_offset_32 ptr_offset1[] = {
    {SX.owner, offsetof(struct guitar, owner), 0, sizeof(*(SX.owner))}
  };
  
  struct dna and = {
    ENDIAN_LITTLE,
    ARCH_X86
  };
  
  void* sdata = serialize(&SX, sizeof(SX), &and, ptr_offset1, 1);
  FILE* sdata_file = fopen("./sdata", "w");
  fputs((char*)sdata, sdata_file);
  fwrite(sdata, 1, *(uint32_t*)(sdata+2), sdata_file);
  fclose(sdata_file);
  //deserialize
  struct engine* engine_des;
  engine_des = deserialize(sdata);
  printf("deserialized data struct: engine      gl_ver = %s\n", engine_des->gl_ver);
}
