#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

/* Copies the position and the rotation out of an object into two separate vectors. */
void moby_copy_pos_rot(char *object, char *out_position, char *out_rotation) {
    *(TI128 *)out_position = *(TI128 *)(object + 0x10);
    *(TI128 *)out_rotation = *(TI128 *)(object + 0xF0);
}
