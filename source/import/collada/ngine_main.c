#include "scene.h"

#include "convert.h"
#include <expat.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAIN_USAGE \
    "Required arguments\n" \
    "  -dae                Path to input collada file\n" \
    "  -o [FILE]           Path to outputtaascene file\n" \
    "\n" \
    "Options\n" \
    "  -up [Y|Z]           Up axis for exported obj file\n"

typedef struct main_args_s main_args;

struct main_args_s
{
    taa_scene_upaxis upaxis;
    const char* dae;
    const char* out;
};

int main(int argc, char* argv[]) {
    int err = 0;
    XML_Parser expat = XML_ParserCreate(NULL);
    main_args args;
    dae_COLLADA* collada = NULL;
    FILE* fp = NULL;
    void* data = NULL;
    size_t size = 0;
    
    struct scene* scene = scene_create("dae scene", true);
        // open input file
        fp = fopen("path_to_dae", "rb");
        if(fp == NULL)
        {
            printf("could not open input file %s\n", args.dae);
            err = -1;
        }
        
    if(err == 0)
    {
        // get allocate file buffer
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        data = XML_GetBuffer(expat, size);
        if(data == NULL)
        {
            printf("could not allocate memory of size %u", (unsigned) size);
            err = -1;
        }
    }
    if(err == 0)
    {
        // read file
        if(fread(data, 1, size, fp) != size)
        {
            printf("error reading file\n");
            err = -1;
        }
    }
    if(fp != NULL)
    {
        fclose(fp);
    }
    if(err == 0)
    {
        // parse the dae data
        daeu_xml_parser parser;
        collada = dae_create();
        daeu_xml_create(collada, &parser);
        XML_SetElementHandler(
            expat,
            daeu_xml_startelement,
            daeu_xml_endelement);
        XML_SetCharacterDataHandler(expat, daeu_xml_chardata);
        XML_SetUserData(expat, parser);
        if(XML_ParseBuffer(expat, size, 1) != XML_STATUS_OK)
        {
            printf("error parsing xml\n");
            err = -1;
        }
        daeu_xml_destroy(parser);
    }
    XML_ParserFree(expat);
    if(err == 0)
    {
        // convert to taa_scene
        convert_collada(args.dae, collada, &scene);
    }
    if(collada != NULL)
    {
        dae_destroy(collada);
    }
    if(err == 0)
    {
        // convert up axis
        taa_scene_convert_upaxis(&scene, args.upaxis);
    }
    if(err == 0)
    {
        // open output file
        fp = fopen(args.out, "wb");
        if(fp == NULL)
        {
            printf("could not open output file %s\n", args.out);
            err = -1;
        }
    }
    if(err == 0)
    {
        // export
        taa_filestream outfs;
        taa_filestream_create(fp, 1024 * 1024, taa_FILESTREAM_WRITE, &outfs);
        taa_scenefile_serialize(&scene, &outfs);
        taa_filestream_destroy(&outfs);
        fclose(fp);
    }
    taa_scene_destroy(&scene);

    return err;
}
