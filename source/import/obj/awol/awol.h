/*
 * awol.h - Another Wavefront OBJ Loader
 * Ed Markowski (2014)
 */
#ifndef AWOL_H_
#define AWOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (defined _WIN64 || defined _WIN32)
    #define AWOL_SLASH "\\"
#else
    #define AWOL_SLASH "/"
#endif

/* awol_material struct */
struct awol_material
{
    char* name;     /* material name    */
    float Ka[3];    /* ambient color    */
    float Kd[3];    /* diffuse color    */
    float Ks[3];    /* specular color   */
    float Ke[3];    /* emissive color   */
    float Tr;       /* transparency     */
    float Ns;       /* shininess        */
    int illum;      /* illumination     */
    char* map_Ka;   /* ambient texture  */
    char* map_Kd;   /* diffuse texture  */
    char* map_Ks;   /* specular texture */
    char* map_Ke;   /* emissive texture */
};

/* awol_chunk struct */
struct awol_chunk 
{
    int mtl_index;       /* Specifies which material to use.       */
    int max_tri;         /* The number of triangles in the chunk.  */
    int* tri_index;      /* Each index contains 3 sets of v/vt/vn. */
};

/* awol_model struct */
struct awol_model
{
    float* vertices;             /* geometric vertex array */
    float* textures;             /* texture vertex array   */
    float* normals;              /* vertex normal array    */
    struct awol_chunk** chunk;   /* array of draw chunks   */
    int max_chunk;               /* number of draw chunks  */
    struct awol_material** mtl;  /* array of materials     */
    int max_mtl;                 /* number of materials    */
};

/* AWOL Interface */
struct awol_model* awol_create_model(const char* objpath);
void awol_destroy_model(struct awol_model* model);
void awol_print_material(struct awol_material* material);

#ifdef __cplusplus
}
#endif

#endif
