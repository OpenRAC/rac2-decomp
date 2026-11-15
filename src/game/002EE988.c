#include "include_asm.h"
#include "names.h"

/* func_002EE988 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int V4 __attribute__((mode(TI)));
extern int moby_get_motion_data(unsigned char *owner);
extern unsigned int scene_get_state_word(void);
extern void FastVecSub(void *a0, void *a1, void *a2);
extern float FastVecLength(char *a0);
extern void FastVecScale(char *a0, char *a1, float f);
extern void func_00282F20_10(V4 *, char *, float);
extern void func_00282CC0_26(char *, V4 *, char *);
extern int CollLine(char *a0, char *a1, int mode, char *self, int flag);
extern int coll_test_point(char *a0, int mode, char *self, float scale);
extern V4 D_001BAFA0;
extern V4 D_001BAFB0;
extern char *D_001B1C54 __attribute__((sda));
extern int D_00214F90[];

/* Keeps the follower's push vector inside its allowed range and stops it from going into walls or the ground. */
void follower_clamp_push_vector(char *owner)
{
    float offset[4];
    float pushDir[4];
    float pushVec[4];
    float oldPos[4];
    float newPos[4];
    char *object;
    char *pos;
    char *table;
    float dist;

    if (scene_get_state_word() != 0)
        return;
    object = (char *)moby_get_motion_data((unsigned char *)owner);
    if (object == 0)
        return;
    pos = object + 0x60;
    table = D_001B1C54 + D_00214F90[0] * 128;
    FastVecSub(offset, pos, table + 0x30);
    dist = FastVecLength((char *)offset);
    if (*(float *)table < dist) {
        func_00282F20_10((V4 *)offset, (char *)offset, dist - (dist - *(float *)table));
        func_00282CC0_26(pos, (V4 *)offset, table + 0x30);
    }
    if (CollLine(owner + 0x10, pos, 2, owner, 0)) {
        V4 *pd = (V4 *)oldPos;
        V4 *pe;
        *pd = D_001BAFA0;
        FastVecScale((char *)pushDir, (char *)&D_001BAFA0 + 0x20, 0.00097656f);
        func_00282F20_10((V4 *)pushVec, (char *)pushDir, 5.0f);
        pe = (V4 *)newPos;
        func_00282CC0_26((char *)pe, pd, (char *)pushVec);
        *(V4 *)pos = *pe;
    }
    if (coll_test_point(pos, 2, owner, 5.0f)) {
        *(V4 *)pos = D_001BAFB0;
    }
}
