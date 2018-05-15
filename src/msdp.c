/**
 * msdp.c -- support functions for MSDP
 * spec at http://tintin.sourceforge.net/msdp/
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mud.h"
#include "utils.c"

/**
 * MSDP_FLAGS - enum to keep track of properties of MSDP commands. 
 * No. Bit flags.
 */
typedef enum
{
    MSDP_NONE           = -1,   // Invalid Flag
    MSDP_COMMAND        = (1 << 0),
    MSDP_LIST           = (1 << 1),
    MSDP_SENDABLE       = (1 << 2),
    MSDP_REPORTABLE     = (1 << 3),
    MSDP_CONFIGURABLE   = (1 << 4),
    MSDP_REPORTED       = (1 << 5),
    MSDP_UPDATED        = (1 << 6),

    MSDP_END,
} MSDP_FLAGS;

struct Command
{
    char *name;
    int8_t commandFlags;
    Handler funcPointer;
};


struct Command msdp_table[] =
{
    /** General */
    {   "CLIENT_NAME",                          MSDP_CONFIGURABLE|MSDP_REPORTABLE,          NULL},
    {   "CLIENT_VERSION",                       MSDP_NONE,                                  NULL},
    {   "PLUGIN_ID",                            MSDP_NONE,                                  NULL},

    /** Combat */
    {   "OPPONENT_LEVEL",                       MSDP_NONE,                                  NULL},
    {   "OPPONENT_HEALTH",                      MSDP_NONE,                                  NULL},
    {   "OPPONENT_HEALTH_MAX",                  MSDP_NONE,                                  NULL},
    {   "OPPONENT_NAME",                        MSDP_NONE,                                  NULL},
    {   "OPPONENT_STRENGTH",                    MSDP_NONE,                                  NULL},

    /** World Stuff */
    {   "ROOM_VNUM",                            MSDP_NONE,                                  NULL},
    {   "ROOM_NAME",                            MSDP_NONE,                                  NULL},
    {   "ROOM_AREA",                            MSDP_NONE,                                  NULL},
    {   "ROOM_COORDS",                          MSDP_NONE,                                  NULL},
    {   "ROOM_TERRAIN",                         MSDP_NONE,                                  NULL},
    {   "ROOM_EXITS",                           MSDP_NONE,                                  NULL},
    {   "WORLD_TIME",                           MSDP_NONE,                                  NULL},

    
};

const unsigned char msdp_head[] = {IAC, SB, TELOPT_MSDP, 0};
const unsigned char msdp_tailp[] = {IAC, SE, 0};

bool msdpEnable(D_S *sock)
{
    sock->msdp_enabled = true;
    return sock->msdp_enabled;
}
