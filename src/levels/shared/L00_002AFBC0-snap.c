#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec5250;

/* The fields of the resident hero block (D_00189E20) this unit reads. */
typedef struct {
    u8 pad0[0x80];
    Vec5250 position;   /* 0x80; its z is the scalar the low path eases */
    u8 pad90[0xF0 - 0x90];
    Vec5250 vF0;        /* 0xF0 */
    u8 pad100[0x120 - 0x100];
    Vec5250 v120;       /* 0x120 */
    u8 pad130[0x240 - 0x130];
    Vec5250 anchor;     /* 0x240 */
    u8 pad250[0x264 - 0x250];
    f32 reach;          /* 0x264 */
    u8 pad268[0x287 - 0x268];
    u8 easing;          /* 0x287 */
    u8 pad288[0x2D0 - 0x288];
    Vec5250 goal;       /* 0x2D0 */
    u8 pad2E0[0x318 - 0x2E0];
    f32 goalZ;          /* 0x318 */
    f32 x31C;           /* 0x31C */
    u8 pad320[0x344 - 0x320];
    f32 rate;           /* 0x344: state of the easing calls */
    u8 pad348[0x34E - 0x348];
    s16 lock;           /* 0x34E */
    u8 pad350[0x22C3 - 0x350];
    u8 vectorMode;      /* 0x22C3 */
} Hero5250;

extern Hero5250 D_00189E20;

extern float func_00282C48(float);
extern float func_L00_002D3B00(Vec5250 *);
extern float func_00282E80(Vec5250 *, Vec5250 *);
extern float func_002AA458(Vec5250 *, Vec5250 *, float *, float, float, float);
/* Declared with the EE's independent bank order (a0, f12, a1, f13-f15), as in
 * src/game/00322CC0.c: the value, the target, the rate, then the three gains. */
extern float func_002AA3A8(float *, float, float *, float, float, float);

/* Eases the hero's position toward its goal unless the lock at +0x34E is held: in vector
 * mode (+0x22C3) the vector at +0x80 follows the one at +0x2D0 while +0x31C is negative,
 * in scalar mode its z follows +0x318 while below it.  Within one step of the goal (the
 * difference below the step from +0xF0 plus 0.01) it snaps there instead when easing is
 * off (+0x287 clear) or the anchor at +0x240 is more than half of +0x264 away; with the
 * lock held or the goal passed, the easing rate at +0x344 is cleared. */
void func_L00_002B5250(void)
{
    Hero5250 *hero = &D_00189E20;
    float d;

    if (D_00189E20.vectorMode != 0) {
        if (D_00189E20.lock == 0 && D_00189E20.x31C < 0.0f) {
            d = func_00282C48(D_00189E20.x31C);
            if (d < func_00282C48(func_L00_002D3B00(&hero->vF0)) + 0.01f) {
                if (D_00189E20.easing == 0
                    || vec_distance_xy(&hero->anchor, &hero->position) > D_00189E20.reach * 0.5f) {
                    qcopy(&hero->position, &hero->goal);
                    return;
                }
                func_002AA458(&hero->position, &hero->goal, &hero->rate,
                              0.05f, 0.21f, 0.0833333358f);
            } else {
                func_002AA458(&D_00189E20.position, &D_00189E20.goal, &D_00189E20.rate,
                              0.05f, 0.21f, 0.0833333358f);
            }
        } else {
            D_00189E20.rate = 0.0f;
        }
    } else {
        if (D_00189E20.lock == 0 && D_00189E20.position.z < D_00189E20.goalZ) {
            d = func_00282C48(D_00189E20.position.z - D_00189E20.goalZ);
            if (d < func_00282C48(D_00189E20.vF0.z) + 0.01f) {
                if (D_00189E20.easing == 0
                    || vec_distance_xy(&hero->anchor, &hero->position) > D_00189E20.reach * 0.5f) {
                    D_00189E20.position.z = D_00189E20.goalZ;
                    return;
                }
                func_002AA3A8(&hero->position.z, D_00189E20.goalZ, &hero->rate,
                              0.05f, 0.17f, 0.0833333358f);
            } else {
                if (D_00189E20.v120.z < 0.0f) {
                    D_00189E20.position.z -= D_00189E20.v120.z;
                    if (D_00189E20.goalZ < D_00189E20.position.z)
                        D_00189E20.position.z = D_00189E20.goalZ;
                }
                func_002AA3A8(&D_00189E20.position.z, D_00189E20.goalZ, &D_00189E20.rate,
                              0.05f, 0.17f, 0.0833333358f);
            }
        } else {
            D_00189E20.rate = 0.0f;
        }
    }
}
