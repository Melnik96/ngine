#define new(type_name) malloc(sizeof(type_name))
#define newc(type_name) calloc(1, sizeof(type_name))

/**
 * Dinamic Struct size
 */
#define dsize(type_name) type_name##_size

#define new_s(type_name) malloc(dsize(type_name))


// TODO
//  - dynamic(size) struct allocation
