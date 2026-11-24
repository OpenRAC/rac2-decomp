#include "names.h"
/* func_L00_002C8CB0 (348 bytes, 22 places), in its own unit for the approved qcopy helper.
 * The two final transitions are an if/else that joins at one `return 1`: flow puts a
 * `(use (const_int 0))` after the else arm's call, which ends its block, so jump2 cross-jumps
 * only the 0x34 arm into the first transition's call and the 0x32 arm keeps its own call, as
 * retail does. Separate `return 1` statements, or a shared mode variable, merge all three. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern char g_hero_state[];
extern int g_pad_pressed_flags;
extern int g_hero_ledge_move_flag;
extern s32 hero_l00_set_move_state(int mode, int flag);
extern int CollLine(void *start, void *end, int flags, void *object, int mode);
/* Decides which ledge-grab or climb move the hero starts when close to a ledge, if any. */
int hero_try_start_ledge_move(void)
{
    char *pre = g_hero_state;
    char *base;
    char *object;
    Vector start, end;
    if (*(int *)(pre + 0x229c) == 0x11) {
        if (*(float *)(pre + 0x330) + 0.4f < *(float *)(pre + 0x88)) {
            g_hero_ledge_move_flag = 0;
            hero_l00_set_move_state(6, 1);
            return 1;
        }
    } else if (*(int *)(pre + 0x2294) != 0x67 && *(int *)(pre + 0x2294) != 0x73) {
        *(int *)(pre + 0x24c0) = 10000;
    }
    base = g_hero_state;
    if (*(short *)(base + 0x1fe) != 0)
        goto fail;
    object = *(char **)(base + 0x2290);
    if (*(int *)(*(char **)(object + 0x24) + 0x134) == 0)
        goto fail;
    if (*(int *)(base + 0x229c) != 0x12)
        goto fail;
    qcopy(&start, base + 0x80);
    start.v[2] = *(float *)(base + 0x330) + 0.01f;
    qcopy(&end, &start);
    end.v[2] += 0.3f;
    if (CollLine(&start, &end, 2, object, 0) == 0)
        goto fail;
    if (*(short *)(base + 0x24fc) == 0 && (g_pad_pressed_flags & 10) != 0)
        hero_l00_set_move_state(0x34, 1);
    else
        hero_l00_set_move_state(0x32, 1);
    return 1;
fail:
    return 0;
}
