#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

/* Partial table view: retail visits up to eight four-short rows. GP access
 * is independently evidenced; this is not a complete global extent claim. */
typedef struct { s16 row[8][4]; } RowTablePrefix;
extern RowTablePrefix D_L16_001B1710 __attribute__((sda));

extern u32 D_L16_001FE7C0[];

extern float func_L01_00311C18(void *, void *, void *, void *);

extern float func_00282E80(void *, void *);

/* Walks the level's table of short rows, keeping the closest match of the handle's
   measured pair in the handle and the winning row in the handle's second half. */
void func_L16_00410CC0(u8 *arg0, u8 *arg1)
{
    TI128 state;
    TI128 work;
    u32 *s4;
    u8 *fp;
    s32 next;
    u8 *dest;
    f32 best;
    f32 f;
    f32 g;
    s32 row;
    s32 count;
    s16 v;
    s16 *r;

    s4 = *(u32 **)(arg0 + 0x68);
    best = 2001.0f;
    fp = *(u8 **)(D_L16_001FE7C0 + s4[92]);
    qcopy(&state, arg1);
    dest = (u8 *)s4 + 0x200;
    for (row = 0; row < 8; row = next) {
        count = 0;
        v = D_L16_001B1710.row[row][0];
        next = row + 1;
        if (v == -1)
            continue;
        r = D_L16_001B1710.row[row];
        do {
            if (v >= row) {
                f = func_L01_00311C18(&work, fp + (row * 16 + 0x10), fp + (v * 16 + 0x10), arg1);
                g = vec_distance_xy(arg1, &work);
                if (g < best) {
                    best = g;
                    s4[0x7E] = v;
                    *(f32 *)((u8 *)s4 + 0x1FC) = f;
                    s4[0x7D] = row;
                    qcopy(&state, &work);
                }
            }
            count++;
            r++;
            if (count >= 4)
                break;
            v = *r;
        } while (v != -1);
    }
    qcopy(dest, &state);
}

void func_L16_00410FA8(u8 *arg0)
{
    s32 *p;
    s32 mask;
    s32 acc;
    s32 i;
    s32 j;
    s32 v;

    p = *(s32 **)(arg0 + 0x68);
    if (p[0x7D] == p[0x88] || p[0x7D] == p[0x89]) {
        p[0x8A] = p[0x7D];
        p[0x8B] = p[0x7E];
        return;
    }
    if (p[0x7E] == p[0x88] || p[0x7E] == p[0x89]) {
        p[0x8A] = p[0x7E];
        p[0x8B] = p[0x7D];
        return;
    }
    mask = (1 << p[0x7D]) | (1 << p[0x7E]);
    acc = 0;
    for (;;) {
        for (i = 0; i < 8; i++) {
            if ((mask >> i) & 1) {
                for (j = 0; j < 4 && (v = D_L16_001B1710.row[i][j]) != -1; j++) {
                    acc |= 1 << v;
                    if (v == p[0x88]) {
                        p[0x8A] = v;
                        p[0x8B] = i;
                        return;
                    }
                    if (v == p[0x89]) {
                        p[0x8A] = v;
                        p[0x8B] = i;
                        return;
                    }
                }
            }
        }
        mask |= acc;
    }
}
