/* $ valgrind -v --leak-check=full ./test_awol <OBJ file> */
#include <stdio.h>
#include <string.h>
#include "awol.h"

int main(int argc, char** argv)
{
    if (1 == argc)
    {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return -1;
    }
    struct awol_model* model = awol_create_model(argv[1]);
    printf("num_chunks %i", model->max_chunk);
    if (!model) return -1;
    awol_destroy_model(model);
    model = NULL;
    return 0;
}

