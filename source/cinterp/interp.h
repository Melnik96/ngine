struct cinterp {
  struct string name;
};

struct code_exec_status {};

struct cinterp*          cinterp_create();
int                      cinterp_init(struct cinterp* _self);
struct code_exec_status* exec_code(const char* _code);
