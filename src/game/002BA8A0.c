#include "names.h"
/* func_002BA8A0: the particle record's constructor. The source's field 8 is nudged up
 * by 0.2 before the 16-byte copy, which is qcopy() (retail copies the updated value and
 * keeps both addresses in registers), and the header stores are in retail's order. The
 * record's global byte and the float-to-int callee differ between the boot and the
 * levels, hence the two ref_ names. */
#include "common.h"

extern char *part_alloc(int size);

extern int ref_002BA8A0_01(float f);

/* The byte at the level's own global, whose address differs from program to program. */
extern unsigned char *ref_002BA8A0_00;


/* Allocates a one-byte record, nudges the source's field 8 up by 0.2, copies the source's
 * first 16 bytes into the record and fills the record's header. */
void part_spawn_glow(void *a0, int a1)
{
    char *obj = (char *)part_alloc(1);
    unsigned char byte;
    int r;

    if (obj == 0)
        return;
    *(float *)((char *)a0 + 8) = *(float *)((char *)a0 + 8) + 0.2f;
    qcopy(obj + 0x10, a0);
    *(int *)(obj + 4) = (a1 << 24) | 0x00907070;
    r = ref_002BA8A0_01(2.0f);
    *(char *)(obj + 9) = (char)(r + 0x40);
    *(char *)(obj + 3) = 0x44;
    *(char *)(obj + 1) = 0;
    byte = *ref_002BA8A0_00;
    *(int *)(obj + 0x20) = a1;
    *(float *)(obj + 0xC) = 63000.00390625f;
    *(unsigned char *)(obj + 8) = 0xA0;
    *(short *)(obj + 0xA) = 0x1B;
    *(char *)(obj + 2) = byte;
}
