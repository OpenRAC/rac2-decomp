#include "names.h"
/* Turns a challenge number into the id of its matching entry, or -1 when it has none. */
int arena_get_challenge_display_id(unsigned int index)
{
    switch (index) {
    case 0: return 10;
    case 1: return 11;
    case 3: return 12;
    case 4: return 13;
    case 5: return 14;
    case 7: return 15;
    case 10: return 16;
    case 8: return 17;
    case 12: return 18;
    case 2:
    case 6:
    case 9:
    case 11:
        break;
    }
    return -1;
}
