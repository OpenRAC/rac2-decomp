#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(unsigned char *, int, int);

extern void scale_vector(TI128 *, char *, float);

extern int math_fast_helper_a(TI128 *, float);

extern float mat_fast_helper_a(float, float);

/* The table is indexed in 128-byte records; position starts at offset 0x30. */
typedef struct { char bytes[128]; } EntryECE0;
extern EntryECE0 *g_shooter_mount_table __attribute__((nosda));

/* Resets the object and snaps it to its current path point. It also remembers where it started and which way it must turn to reach the path point. */
void path_reset_follower_to_point(char *moby)
{
    TI128 scratch;
    char *moby_alias = moby;
    char *vars;
    char *definition;
    unsigned short flags;
    int path_index;
    char *path_point;
    float pos_y, pos_x;

    vars = *(char **)(moby + 0x68);
    flags = *(unsigned short *)(moby + 0x34);
    definition = *(char **)(moby + 0x24);
    *(unsigned short *)(moby + 0x34) = (flags & 0xFFBE) | 0x1000;
    *(int *)(moby + 0x98) = *(int *)(definition + 0x10);
    moby_set_state((unsigned char *)moby, 3, -1);
    *(unsigned char *)(moby + 0x30) = 0xFF;
    *(unsigned short *)(moby + 0x32) = 0xFF;

    if (*(int *)(vars + 0x98) != 0) {
        scale_vector(&scratch, moby_alias, 0.0009765625f);
        path_index = math_fast_helper_a(&scratch, 128.0f);
        if (path_index != -1) {
            qcopy(moby + 0x10, &g_shooter_mount_table[*(int *)(vars + 0x98)].bytes[0x30]);
        }
    }

    path_index = *(int *)(vars + 0x94);
    path_point = (char *)(path_index * 128 + (int)g_shooter_mount_table);
    pos_x = *(float *)(moby + 0x10);
    pos_y = *(float *)(moby + 0x14);
    *(float *)(vars + 0xE8) = mat_fast_helper_a(*(float *)(path_point + 0x30) - pos_x, *(float *)(path_point + 0x34) - pos_y);
    qcopy(vars + 0xF0, moby + 0x10);
    qcopy(vars + 0xD0, &g_shooter_mount_table[*(int *)(vars + 0x94)].bytes[0x30]);
}
