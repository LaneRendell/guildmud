#include "..\mud.h"

const unsigned char msdp_head[] =  {IAC, SB, TELOPT_MSDP, 0};
const unsigned char msdp_tailp[] = {IAC, SE, 0};