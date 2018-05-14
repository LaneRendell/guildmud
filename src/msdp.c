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

const unsigned char msdp_head[] =  {IAC, SB, TELOPT_MSDP, 0};
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


