#include "names.h"
/* Turns a challenge number into the index of its saved "done" flag, or -1 when it has none. */
int arena_get_challenge_flag_index(unsigned int index)
{
    switch (index) {
    case 0: return 61;
    case 1: return 62;
    case 2: return 63;
    case 3: return 64;
    case 4: return 65;
    case 5: return 66;
    case 6: return 67;
    case 7: return 68;
    case 9: return 69;
    case 10: return 70;
    case 8: return 71;
    case 11: return 72;
    case 12: return 75;
    }
    return -1;
}
