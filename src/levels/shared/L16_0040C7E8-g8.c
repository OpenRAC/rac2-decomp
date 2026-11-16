#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;

/* Retail index arithmetic establishes the 256/128-byte pool strides and
   the position offsets. The remaining bytes retain their real storage. */
typedef struct { char prefix[0x10]; Quad position; char rest[0xE0]; } ObjectPoolRecord256;
extern ObjectPoolRecord256 *g_moby_instance_table __attribute__((sda));
typedef struct { char prefix[0x30]; Quad position; char rest[0x40]; } PointPoolRecord128;
extern PointPoolRecord128 *g_beam_definition_table __attribute__((nosda));
typedef struct { int pointIndex; int objectIndex; } PositionChoice;
/* Looks up the position of the launch target, either a point or an object, and copies it out. */
void moby_get_launch_target_pos(char *object, Vector *destination) {
    PositionChoice *choice=*(PositionChoice **)(object+0x68);
    int index=choice->objectIndex;
    if (index==-1)
        destination->q=g_beam_definition_table[choice->pointIndex].position;
    else
        destination->q=g_moby_instance_table[index].position;
}
