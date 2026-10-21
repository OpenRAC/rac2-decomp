/* Exact at every place, but the build refuses it: the function's own bytes are the
   C's, but the switch table it jumps through (jtbl_002BB060) lives in the level's .data
   at 0x002BB060, and a C switch makes the compiler emit its own
   table into a section, where it cannot be placed at that address.  The function
   stays assembly.  From the wave that matched the rest of its file. */

int func_L11_0043E108(unsigned int index)
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
    case 8: return 69;
    case 9: return 70;
    case 10: return 71;
    case 11: return 72;
    case 12: return 75;
    }
    return -1;
}
