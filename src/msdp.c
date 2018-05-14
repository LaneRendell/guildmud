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

/**
 * MSDP_FLAGS - enum to keep track of properties of MSDP commands. 
 * No. Bit flags.
 */
typedef enum
{
    MSDP_NONE           = -1,   // Invalid Flag
    MSDP_COMMAND        = (1 << 0),
    MSDP_LIST           = (1 << 1),
    MSDP_SENDABLE       = (1 << 2)
    MSDP_REPORTABLE     = (1 << 3),
    MSDP_CONFIGURABLE   = (1 << 4),
    MSDP_REPORTED       = (1 << 5),
    MSDP_UPDATED        = (1 << 6),

    MSDP_END,
} MSDP_FLAGS;



const unsigned char msdp_head[] = {IAC, SB, TELOPT_MSDP, 0};
const unsigned char msdp_tailp[] = {IAC, SE, 0};

/**
 * MSDP numeric list corresponding to spec variables.
 * Use this 
 */
typedef enum msdp_commands
{
    MSDP_NONE = -1,
};

bool msdpEnable(D_S *sock)
{
    sock->msdp_enabled = true;
    return sock->msdp_enabled;
}
