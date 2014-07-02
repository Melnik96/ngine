#include "scene.h"

#include "convert.h"
#include <expat.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct scene* dae_convert(char* file_path) {
    int err = 0;
    XML_Parser expat = XML_ParserCreate(NULL);
    dae_COLLADA* collada = NULL;
    FILE* fp = NULL;
    void* data = NULL;
    size_t size = 0;
    
    struct scene* scene = scene_create("dae scene", true);
        // open input file
        fp = fopen(file_path, "rb");
        if(fp == NULL)
        {
            printf("could not open input file %s\n", file_path);
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
        convert_collada(file_path, collada, &scene);
    }
    if(collada != NULL)
    {
        dae_destroy(collada);
    }

    return err;
}
