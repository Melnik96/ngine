/* 
 * awol.c - Another Wavefront OBJ Loader
 * Ed Markowski (2014)
 */
#include "awol.h"

/*
 * Initialize an empty awol_material. 
 * The map_K* strings are image files specified by the MTL file,
 * use the image library of your choice to load them. They include
 * the directory from which they are to be loaded.
 */
static struct awol_material* create_material(void)
{
    struct awol_material* material;
    material = (struct awol_material*)malloc(sizeof(struct awol_material));
    material->name = NULL;
    memset(material->Ka, 0, 3*sizeof(float));
    memset(material->Kd, 0, 3*sizeof(float));
    memset(material->Ks, 0, 3*sizeof(float));
    memset(material->Ke, 0, 3*sizeof(float));
    material->Tr = 0.0f;
    material->Ns = 0.0f;
    material->illum = 0;
    material->map_Ka = NULL;
    material->map_Kd = NULL;
    material->map_Ks = NULL;
    material->map_Ke = NULL;
    return material;
}

/*
 * Initialize an empty draw chunk.
 * Draw chunks are divided by usemtl calls.
 */
static struct awol_chunk* create_chunk(void)
{
    struct awol_chunk* chunk;
    chunk = (struct awol_chunk*)malloc(sizeof(struct awol_chunk));
    chunk->tri_index = NULL;
    chunk->mtl_index = 0;
    chunk->max_tri = 0;
    return chunk;
}

/*
 * Initialize an empty awol_model. 
 * Stores most data from the OBJ and MTL file.
 * Designed to be easy to use to render 3D models.
 */
static struct awol_model* create_model(void)
{
    struct awol_model* model;
    model = (struct awol_model*)malloc(sizeof(struct awol_model));
    model->vertices = NULL;
    model->textures = NULL;
    model->normals = NULL;
    model->chunk = NULL;
    model->max_chunk = 0;
    model->mtl = NULL;
    model->max_mtl = 0;
    return model;
}

/*
 * Clean up any dynamically allocated material memory. 
 * material - Preferably an initialized struct awol_material.
 */
static void destroy_material(struct awol_material* material)
{
    /* maybe assert a warning */
    if (NULL == material) return;
    if (NULL != material->name)
    {
        free(material->name);
        material->name = NULL;
    }
    if (NULL != material->map_Ka)
    {
        free(material->map_Ka);
        material->map_Ka = NULL;
    }
    if (NULL != material->map_Kd)
    {
        free(material->map_Kd);
        material->map_Kd = NULL;
    }
    if (NULL != material->map_Ks)
    {
        free(material->map_Ks);
        material->map_Ks = NULL;
    }
    if (NULL != material->map_Ke)
    {
        free(material->map_Ke);
        material->map_Ke = NULL;
    }
    free(material);
}

/*
 * Clean up any dynamically allocated draw chunk memory. 
 * chunk - Preferably an initialized struct awol_chunk.
 */
static void destroy_chunk(struct awol_chunk* chunk)
{
    /* maybe assert a warning */
    if (NULL == chunk) return;
    /* delete the array of indices */
    if (NULL != chunk->tri_index)
    {
        free(chunk->tri_index);
        chunk->tri_index = NULL;
    }
    free(chunk);
}

/*
 * Clean up any dynamically allocated model memory. 
 * model - Preferably an initialized struct awol_model.
 */
static void destroy_model(struct awol_model* model)
{
    /* why are you doing this? */
    if (NULL == model) return;
    /* delete geometric vertices */
    if (NULL != model->vertices)
    {
        free(model->vertices);
        model->vertices = NULL;
    }
    /* delete texture coordinates */
    if (NULL != model->textures)
    {
        free(model->textures);
        model->textures = NULL;
    }
    /* delete normal vertices */
    if (NULL != model->normals)
    {
        free(model->normals);
        model->normals = NULL;
    }
    /* delete all of the draw chunks */
    for (int ci = 0; ci < model->max_chunk; ++ci)
    {
        if (NULL != model->chunk[ci])
        {
            destroy_chunk(model->chunk[ci]);
            model->chunk[ci] = NULL;
        }
    }
    free(model->chunk);
    /* delete all of the materials */
    for (int mi = 0; mi < model->max_mtl; ++mi)
    {
        if (NULL != model->mtl[mi])
        {
            destroy_material(model->mtl[mi]);
            model->mtl[mi] = NULL;
        }
    }
    free(model->mtl);
    free(model);
}

/*
 * Print a material struct if it exists. Mostly for debugging.
 * material - The material to be printed.
 */
static void print_material(struct awol_material* mtl)
{
    if (NULL == mtl) return;
    /* don't assume something is allocated */
    if (NULL != mtl->name)
        fprintf(stdout, "name:  %s\n", mtl->name);
    fprintf(stdout,
            "Ka:    %f %f %f\n"
            "Kd:    %f %f %f\n"
            "Ks:    %f %f %f\n"
            "Ke:    %f %f %f\n"
            "Tr:    %f\n"
            "Ns:    %f\n"
            "illum: %d\n",
            mtl->Ka[0], mtl->Ka[1], mtl->Ka[2],
            mtl->Kd[0], mtl->Kd[1], mtl->Kd[2],
            mtl->Ks[0], mtl->Ks[1], mtl->Ks[2],
            mtl->Ke[0], mtl->Ke[1], mtl->Ke[2],
            mtl->Tr, mtl->Ns, mtl->illum);
    if (NULL != mtl->map_Ka)
        fprintf(stdout, "map_Ka %s\n", mtl->map_Ka);
    if (NULL != mtl->map_Kd)
        fprintf(stdout, "map_Kd %s\n", mtl->map_Kd);
    if (NULL != mtl->map_Ks)
        fprintf(stdout, "map_Ks %s\n", mtl->map_Ks);
    if (NULL != mtl->map_Ke)
        fprintf(stdout, "map_Ke %s\n", mtl->map_Ke);
}

/*
 * Determines the directory that filename is in and returns it. 
 * filename - The filename contains the directory.
 */
static char* extract_directory(const char* filename)
{
    size_t offset = 0;
    char* directory = NULL;
    char* slashptr = NULL;

    while (NULL != (slashptr = strstr((char*)filename+offset, AWOL_SLASH)))
        offset = (size_t)(slashptr-filename)+1; 

    directory = (char*)calloc(offset+1, sizeof(char));
    memcpy(directory, filename, offset*sizeof(char));
    directory[offset] = '\0';

    return directory;
}

/*
 * Count the number of newmtl occurences in the MTL file.
 * mtlpath - A Wavefront MTL file to be processed.
 */
static int count_newmtl(const char* mtlpath)
{
    int nmtl_c = 0;

    FILE* fp;

    if (NULL == mtlpath)
        fprintf(stderr, "(null) value passed to count_newmtl.\n"); 
    else if (NULL == (fp = fopen(mtlpath, "r")))
        fprintf(stderr, "%s does not exist.\n", mtlpath);
    else
    {
        char ch;
        char buff[6];
        int b_offset = 0;

        const char* newmtl = "newmtl";
        /* count the number newmtl statements */
        while (EOF != (ch = fgetc(fp)))
        {
            buff[b_offset] = tolower(ch);
            if (buff[b_offset] != newmtl[b_offset])
                b_offset = 0;
            else
            {
                if (5 == b_offset)
                {
                    ++nmtl_c;
                    b_offset = 0;
                    continue;
                }
                ++b_offset;
            }
        }
        fclose(fp);
    }

    return nmtl_c;
}

/*
 * Create an array of struct material that contains all unique materials.
 * mtlpath - The MTL file corresponding to the OBJ file.
 * mtl_c - The number of materials in the MTL file.
 */
static struct awol_material** load_mtl(const char* mtlpath, int* newmtl_c)
{
    fprintf(stdout, "AWOL LOADING: \"%s\"\n", mtlpath);

    FILE* fp;
    if (NULL == (fp = fopen(mtlpath, "r")))
    {
        fprintf(stderr,
                "AWOL ERROR: \"%s\" does not exist. Make sure the MTL file" 
                " is in the same directory as the corresponding OBJ file.\n",
                mtlpath);
        *newmtl_c = 0;
        return NULL;
    }    

    /* extract directory from mtlpath */
    char* dir = extract_directory(mtlpath); 

    /* create an array of empty materials */
    struct awol_material** mtls;
    mtls = (struct awol_material**)malloc(*newmtl_c*sizeof(struct awol_material*));
    for (int mi = 0; mi < *newmtl_c; ++mi)
        mtls[mi] = create_material();

    char ch;
    char buff[1024];
    int b_offset = 0;
    int newmtl_i = -1;  /* new mtl index */
    size_t t0, t1, ws;  /* temp and white-space offset */
    while (EOF != (ch = fgetc(fp)))
    {
        if ('\n' != ch)
        {
            buff[b_offset++] = ch;
            continue;
        }

        /* skip empty lines */
        if (0 == b_offset) continue;
        /* process line -- bug fixed */
        t0 = (isalnum(buff[b_offset-1])) ? 0 : 1; 
        buff[b_offset-t0] = '\0';
        /* skip white-space at the beginning of a line */
        ws = 0; while (' ' == buff[ws] || '\t' == buff[ws]) ++ws;

        /* skip comments */
        if ('#' == buff[ws])
        {
            b_offset = 0;
            continue;
        }

        /* make a lowercase copy of the line buff */
        t0 = strlen(buff+ws);
        char* buff_lc = (char*)calloc(t0+1, sizeof(char));
        strncpy(buff_lc, buff+ws, t0);
        buff_lc[t0] = '\0';
        for (size_t ii = 0; ii < t0; ++ii)
            if (isalpha(buff_lc[ii]))
                buff_lc[ii] = tolower(buff_lc[ii]);

        /* set material name */
        if (strstr(buff_lc, "newmtl"))
        {
            ++newmtl_i;
            t1 = t0-strlen("newmtl ");
            mtls[newmtl_i]->name = (char*)calloc(t1+1, sizeof(char)); 
            strncpy(mtls[newmtl_i]->name, buff+ws+7, t1);
            mtls[newmtl_i]->name[t1] = '\0';
        }
        /* set texture file */
        else if (strstr(buff_lc, "map_k"))
        {
            t0 = strlen(dir);
            t1 = strlen(buff+ws)-7; /* 7 == strlen("map_k* ") */
            switch (buff_lc[5])
            {
                case ('a') : /* ambient */
                    mtls[newmtl_i]->map_Ka = (char*)calloc(t0+t1+1, sizeof(char));
                    /* append texture file string to directory */
                    strncat(mtls[newmtl_i]->map_Ka, dir, t0);
                    strncat(mtls[newmtl_i]->map_Ka, buff+ws+7, t1);
                    mtls[newmtl_i]->map_Ka[t0+t1] = '\0';
                    break;
                case ('d') : /* diffuse */
                    mtls[newmtl_i]->map_Kd = (char*)calloc(t0+t1+1, sizeof(char));
                    /* append texture file string to directory */
                    strncat(mtls[newmtl_i]->map_Kd, dir, t0);
                    strncat(mtls[newmtl_i]->map_Kd, buff+ws+7, t1);
                    mtls[newmtl_i]->map_Kd[t0+t1] = '\0';
                    break;
                case ('s') : /* specular */
                    mtls[newmtl_i]->map_Ks = (char*)calloc(t0+t1+1, sizeof(char));
                    /* append texture file string to directory */
                    strncat(mtls[newmtl_i]->map_Ks, dir, t0);
                    strncat(mtls[newmtl_i]->map_Ks, buff+ws+7, t1);
                    mtls[newmtl_i]->map_Ks[t0+t1] = '\0';
                    break;
                case ('e') : /* emissive */
                    mtls[newmtl_i]->map_Ke = (char*)calloc(t0+t1+1, sizeof(char));
                    /* append texture file string to directory */
                    strncat(mtls[newmtl_i]->map_Ke, dir, t0);
                    strncat(mtls[newmtl_i]->map_Ke, buff+ws+7, t1);
                    mtls[newmtl_i]->map_Ke[t0+t1] = '\0';
                    break;
                default : /* others not supported atm */ break;
            }
        }
        /* set color */
        else if ('k' == buff_lc[0])
        {
            switch (buff_lc[1])
            {
                case ('a') : /* ambient color */
                    sscanf(buff+ws+3, "%f %f %f",
                           mtls[newmtl_i]->Ka,
                           mtls[newmtl_i]->Ka+1,
                           mtls[newmtl_i]->Ka+2);
                    break;
                case ('d') : /* diffuse color */
                    sscanf(buff+ws+3, "%f %f %f",
                           mtls[newmtl_i]->Kd,
                           mtls[newmtl_i]->Kd+1,
                           mtls[newmtl_i]->Kd+2);
                    break;
                case ('s') : /* specular color */
                    sscanf(buff+ws+3, "%f %f %f",
                           mtls[newmtl_i]->Ks,
                           mtls[newmtl_i]->Ks+1,
                           mtls[newmtl_i]->Ks+2);
                    break;
                case ('e') : /* emissive color */
                    sscanf(buff+ws+3, "%f %f %f",
                           mtls[newmtl_i]->Ke,
                           mtls[newmtl_i]->Ke+1,
                           mtls[newmtl_i]->Ke+2);
                    break;
                default: /* others not supported atm */ break;
            }
        }
        /* set transparency value */
        else if (strstr(buff_lc, "d ") || strstr(buff_lc, "tr"))
        {
            sscanf(buff+ws+2, "%f", &(mtls[newmtl_i]->Tr));
        }
        /* set illumination value */
        else if (strstr(buff_lc, "illum"))
        {
            sscanf(buff+ws+6, "%d", &(mtls[newmtl_i]->illum));           
        }
        /* set shininess value */
        else if (strstr(buff_lc, "ns"))
        {
            sscanf(buff+ws+3, "%f", &(mtls[newmtl_i]->Ns));
        }

        /* free lowercase copy */
        free(buff_lc);
        /* reset buff index */
        b_offset = 0;
    }
    free(dir);
    fclose(fp);

    fprintf(stdout, "AWOL LOADED: \"%s\"\n", mtlpath);
    return mtls;
}

/*
 * Count the occurences of f until the next usemtl call.
 * This is inefficient and you should fix it.
 * file - The OBJ file.
 * f_offset - The char offset into the file when this is called.
 */
static int ftnu(const char* file, long f_offset)
{
    int triangles = 0;
    FILE* fp;
    fp = fopen(file, "r");
    fseek(fp, f_offset*sizeof(char), SEEK_SET);
    char ch;
    char buff[1024];
    int b_offset = 0;
    size_t t0 = 0;
    while (EOF != (ch = fgetc(fp)))
    {
        if ('\n' != ch)
        {
            buff[b_offset++] = ch;
            continue;
        }

        /* skip empty lines */
        if (0 == b_offset) continue;
        /* newline/carriage-return bug fix */
        t0 = (isalnum(buff[b_offset-1])) ? 0 : 1; 
        buff[b_offset-t0] = '\0';

        if ('f' == buff[0]) ++triangles;
        else if (strstr(buff, "usemtl")) break;
        b_offset = 0;
    }
    fclose(fp);
    return triangles;
}

/*
 * Read a face with v/vt/vn indices.
 * TODO: buffer format enforcement
 * buff - current line buffer
 * f_i - pointer to current face count
 * tri_index - pointer to array of vertex attribute indices
 */
static void read_f_vvtvn(char* buff, int* f_i, int* tri_index)
{
    int f = *f_i;
    sscanf(buff+1, "%d/%d/%d %d/%d/%d %d/%d/%d",
           tri_index+f,   tri_index+f+1, tri_index+f+2,
           tri_index+f+3, tri_index+f+4, tri_index+f+5,
           tri_index+f+6, tri_index+f+7, tri_index+f+8);
    for (int ii = 0; ii < 9; ++ii)
         --tri_index[f+ii];
    *f_i += 9;
}

/*
 * Read a face with v/vt indices.
 * TODO: buffer format enforcement
 * buff - current line buffer
 * f_i - pointer to current face count
 * tri_index - pointer to array of vertex attribute indices
 */
static void read_f_vvt(char* buff, int* f_i, int* tri_index)
{
    int f = *f_i;
    sscanf(buff+1, "%d/%d %d/%d %d/%d",
           tri_index+f,   tri_index+f+1,
           tri_index+f+2, tri_index+f+3,
           tri_index+f+4, tri_index+f+5);
    for (int ii = 0; ii < 6; ++ii)
         --tri_index[f+ii];
    *f_i += 6;
}

/*
 * Create a model from the specified Wavefront OBJ file. 
 * It's assumed that there exists a corresponding MTL file
 * and texture files in the same directory.
 * objfile - The path to the object file.
 */
struct awol_model* awol_create_model(const char* objfile)
{
    fprintf(stdout, "AWOL LOADING: \"%s\"\n", objfile);

    FILE* fp;
    /* check if the file can even be found or opened */
    if (NULL == strstr(objfile, ".obj"))
    {
        fprintf(stderr, "AWOL ERROR: \"%s\" is not an OBJ file.\n", objfile);
        return NULL;
    }
    else if (NULL == (fp = fopen(objfile, "r")))
    {
        fprintf(stderr, "AWOL ERROR: Can't open %s!\n", objfile);
        return NULL;
    }

    /* initialize the model to be returned */
    struct awol_model* model = create_model();

    size_t t0, t1;    /* temp */
    int v_c  = 0;     /* v count  (OBJ) */
    int vt_c = 0;     /* vt count (OBJ) */
    int vn_c = 0;     /* vn count (OBJ) */
    int f_c  = 0;     /* f count  (OBJ) */
    int usemtl_c = 0; /* usemtl count (OBJ) */
    int newmtl_c = 0; /* newmtl count (MTL) */

    /* mtllib path and current directory */
    char* mtllib = NULL;
    char* dir = extract_directory(objfile);

    char ch;
    char buff[1024];
    int b_offset = 0;

    /* count all of the parameters */
    while (EOF != (ch = fgetc(fp)))
    {
        /* store a line */
        if ('\n' != ch)
        {
            buff[b_offset++] = ch;
            continue;
        }

        /* skip empty lines */
        if (0 == b_offset) continue;
        /* time to process line -- fixed bug */
        t0 = (isalnum(buff[b_offset-1])) ? 0 : 1; 
        buff[b_offset-t0] = '\0';

        switch (buff[0])
        {
            case('v'):
                switch (buff[1])
                {
                    /* geometric vertex */
                    case (' ') : ++v_c; break;
                    /* texture vertex */
                    case ('t') : ++vt_c; break;
                    /* vertex normal */
                    case ('n') : ++vn_c; break;
                    /* don't care */
                    default : break;
                }
                break;
            /* face */
            case ('f') : ++f_c; break;
            /* usemtl */
            case ('u') : ++usemtl_c; break;
            /* load mtllib -- Note that this occurs first. */
            case ('m') :
                /* Assuming one mtllib parameter per OBJ file! */
                if (NULL != strstr(buff, "mtllib"))
                {
                    t0 = strlen(dir);
                    t1 = strlen(buff)-7;
                    /* append mtllib name to directory */ 
                    mtllib = (char*)calloc(t0+t1+1, sizeof(char));
                    strncat(mtllib, dir, t0);
                    strncat(mtllib, buff+7, t1);
                    mtllib[t0+t1] = '\0';
                    /* count instances of "newmtl" in MTL file */
                    newmtl_c = count_newmtl(mtllib);
                    model->max_mtl = count_newmtl(mtllib);
                    /* get a list of all materials from MTL file */
                    model->mtl = load_mtl(mtllib, &(model->max_mtl));
                }
                break;
            /* don't care */
            default : break;
        }
        b_offset = 0;
    }

    fprintf(stdout,
            "AWOL: %s : %d triangles, %d usemtl calls, and %d newmtl calls.\n",
            objfile, f_c, usemtl_c, newmtl_c);

    /* set number of chunks */
    model->max_chunk = usemtl_c;
    /* allocate memory for the awol_chunk array */
    model->chunk = (struct awol_chunk**)
        malloc(model->max_chunk*sizeof(struct awol_chunk*));
    /* initialize the draw chunks */
    for (int ci = 0; ci < model->max_chunk; ++ci)
        model->chunk[ci] = create_chunk();

    int f_i  = 0;       /* face index       */
    int v_i  = 0;       /* vertex index     */
    int vt_i = 0;       /* texture index    */
    int vn_i = 0;       /* normal index     */
    int dc_i = -1;      /* draw chunk index */
    int t_c = 0;        /* triangle count   */
    long f_offset = 0L; /* char offset      */

    /* allocate memory for model vertex data */
    model->vertices = (float*)calloc(3*v_c, sizeof(float));
    model->textures = (float*)calloc(2*vt_c, sizeof(float));
    model->normals = vn_c ? (float*)calloc(3*vn_c, sizeof(float)) : NULL;

    /* store the data */
    fseek(fp, 0L, SEEK_SET);
    while (EOF != (ch = fgetc(fp)))
    {
        ++f_offset;
        /* store a line */
        if ('\n' != ch)
        {
            buff[b_offset++] = ch;
            continue;
        }

        /* skip empty lines */
        if (0 == b_offset) continue;
        /* time to process a line */
        t0 = (isalnum(buff[b_offset-1])) ? 0 : 1; 
        buff[b_offset-t0] = '\0';

        switch (buff[0])
        {
            /* vertex data */
            case('v') :
                switch (buff[1])
                {
                    /* geometric vertex */
                    case (' ') :
                        sscanf(buff+1, "%f %f %f",
                               model->vertices+v_i,
                               model->vertices+v_i+1,
                               model->vertices+v_i+2);
                        v_i += 3;
                        break;
                    /* texture vertex */
                    case ('t') :
                        sscanf(buff+2, "%f %f",
                               model->textures+vt_i,
                               model->textures+vt_i+1);
                        vt_i += 2;
                        break;
                    /* vertex normal */
                    case ('n') :
                        sscanf(buff+2, "%f %f %f",
                               model->normals+vn_i,
                               model->normals+vn_i+1,
                               model->normals+vn_i+2);
                        vn_i += 3;
                        break;
                    /* don't care */
                    default : break;
                }
                break;
            /* face */
            case ('f') :
                if (vn_c)
                    read_f_vvtvn(buff, &f_i, model->chunk[dc_i]->tri_index);
                else
                    read_f_vvt(buff, &f_i, model->chunk[dc_i]->tri_index);
                break;
            /* usemtl */
            case ('u') :
                if (NULL != strstr(buff, "usemtl"))
                {
                    ++dc_i;
                    /* Were there normals or not? */
                    t0 = (0 != vn_c) ? 9 : 6;
                    /* count the number of triangles for chunk - slow way */
                    t_c = ftnu(objfile, f_offset);
                    model->chunk[dc_i]->max_tri = t_c;
                    model->chunk[dc_i]->tri_index = (int*)calloc(t0*t_c,sizeof(int)); 
                    /* reset face index */
                    f_i = 0;
                    /* set the mtl for the current draw chunk */
                    t0 = strlen("usemtl ");
                    t1 = strlen(buff)-t0;
                    for (int mi = 0; mi < model->max_mtl; ++mi)
                    {
                        /* search for name in model->mtl array */
                        if (!strncmp(model->mtl[mi]->name, buff+t0, t1))
                        {
                            model->chunk[dc_i]->mtl_index = mi;
                            break;
                        }
                    }
                }
                break;
            /* don't care */
            default : break;
        }
        b_offset = 0;
    }
    if (NULL != mtllib) free(mtllib);
    if (NULL != dir) free(dir);
    fclose(fp);

    fprintf(stdout, "AWOL LOADED: \"%s\"\n", objfile);
    return model;
}

/*
 * Pass the model to be destroyed to the internal destructor.
 * model - The struct model that is to be destroyed.
 */
void awol_destroy_model(struct awol_model* model)
{
    destroy_model(model);
}

/*
 * Pass this material to the internal print function.
 * mtl - The struct material that is to be printed.
 */
void awol_print_material(struct awol_material* mtl)
{
    print_material(mtl);
}
