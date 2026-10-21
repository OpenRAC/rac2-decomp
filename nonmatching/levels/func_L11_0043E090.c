/* Exact at every place, but the build refuses it: the function's own bytes are the
   C's, but the switch table it jumps through (jtbl_002BB020) lives in the level's .data
   at 0x002BB020, and a C switch makes the compiler emit its own
   table into a section, where it cannot be placed at that address.  The function
   stays assembly.  From the wave that matched the rest of its file. */

int func_L11_0043E090(unsigned int index)
{
    switch (index) {
    case 0: return 10;
    case 1: return 11;
    case 2: return 12;
    case 3: return 13;
    case 4: return 14;
    case 5: return 15;
    case 6: return 16;
    case 7: return 17;
    case 8: return 18;
    case 9:
    case 10:
    case 11:
    case 12:
        break;
    }
    return -1;
}
