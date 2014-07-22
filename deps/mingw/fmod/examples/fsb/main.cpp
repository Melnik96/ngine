/*===============================================================================================
 FSB Example
 Copyright (c), Firelight Technologies Pty, Ltd 2004-2014.

 This example demonstrates the usage of the FSB format, generated by the FSBank tool.
 It is simply a packed file format, with sounds contained within.  This is a cross platform
 format that is useful to keep the data format optimal for the platform you are targeting.
 (ie PS2, Xbox, Gamecube have native compression formats)
===============================================================================================*/
#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include "../../api/inc/fmod.hpp"
#include "../../api/inc/fmod_errors.h"

//#include "../media/example.h"   /* Header with FSB indicies. */

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


int main(int argc, char *argv[])
{
    FMOD::System     *system;
    FMOD::Sound      *fsb;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    int               key, count, numsubsounds;
    unsigned int      version;

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        return 0;
    }

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    result = system->createSound("../media/example.fsb", FMOD_DEFAULT, 0, &fsb);
    ERRCHECK(result);

    printf("===================================================================\n");
    printf("FSB Example.  Copyright (c) Firelight Technologies 2004-2014.\n");
    printf("===================================================================\n");
    printf("\n");

    result = fsb->getNumSubSounds(&numsubsounds);
    ERRCHECK(result);

    for (count = 0; count < numsubsounds; count++)
    {
        FMOD::Sound *subsound;
        char name[256];

        result = fsb->getSubSound(count, &subsound);
        ERRCHECK(result);

        result = subsound->getName(name, 256);
        ERRCHECK(result);

        printf("Press '%c' to play \"%s\"\n", '1' + count, name);
    }
    printf("Press 'Esc' to quit\n");
    printf("\n");

    /*
        Main loop.
    */
    do
    {
        if (_kbhit())
        {
            key = _getch();

            if (key >= '1' && key < '1' + numsubsounds)
            {
                FMOD::Sound *subsound;
                int index = key - '1';

                fsb->getSubSound(index, &subsound);
               
                result = system->playSound(FMOD_CHANNEL_FREE, subsound, false, &channel);
                ERRCHECK(result);
            }
        }

        system->update();

        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            bool         playing = 0;
            bool         paused = 0;
            int          channelsplaying = 0;

            if (channel)
            {
                FMOD::Sound *currentsound = 0;

                result = channel->isPlaying(&playing);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                result = channel->getPaused(&paused);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }

                result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                {
                    ERRCHECK(result);
                }
               
                channel->getCurrentSound(&currentsound);
                if (currentsound)
                {
                    result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
                    if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
                    {
                        ERRCHECK(result);
                    }
                }
            }

            system->getChannelsPlaying(&channelsplaying);

            printf("Time %02d:%02d:%02d/%02d:%02d:%02d : %s : Channels Playing %2d\r", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped", channelsplaying);
        }

        Sleep(10);

    } while (key != 27);

    printf("\n");

    /*
        Shut down
    */
    result = fsb->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    return 0;
}


