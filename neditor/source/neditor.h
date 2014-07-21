#ifndef NEDITOR_H
#define NEDITOR_H

struct neditor {
  struct ngine* engine;
};

struct neditor* neditor_create();
void 		neditor_destroy();
struct neditor* neditor_intense();

#endif // NEDITOR_H
