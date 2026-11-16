#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

/* func_L16_004165B0 is defined in L16_004165B0-fx-g8.c. */

extern void func_002E74B8(char *, char *, char *);
extern void func_002E7788(char *, char *, f32);
extern void func_003E9FF0(char *, char *, char *, f32);
extern int func_00357288(s32, s32, char *);
extern f32 func_002E73F8(f32);
extern f32 func_00313F98(f32, f32);
extern f32 func_00313F38(f32, f32);
extern void func_002D4CC8(char *, s32, s32, s32, char *, char *, char *, s32, f32, f32);
extern void func_003140C0(char *, f32, f32);
extern char g_turret_debris_vectors[];

/* lays the object's ten measurement points out along a ring and asks the engine to arm them */
void turret_explode_into_debris(char *moby) {
    char buf0[0x10];
    char buf1[0x10];
    f32 speed;
    f32 size;
    s16 classId;
    s32 i;

    func_002E74B8(buf0, g_turret_debris_vectors, moby + 0x10);
    func_002E7788(buf0, buf0, 1.0f);
    func_003E9FF0(moby, moby + 0x10, buf0, 0.0f);
    func_00357288(0, 0, moby);
    for (i = 0; i < 5; i++) {
        func_003140C0(buf1, 0.0833333358168602f, 0.25f);
        *(f32 *)(buf1 + 8) = func_002E73F8(*(f32 *)(buf1 + 8));
        classId = *(s16 *)(moby + 0xAA);
        speed = func_00313F98(90.0f, 180.0f);
        size = func_00313F38(10.0f, 20.0f);
        func_002D4CC8(moby, 2, classId, i, moby + 0x10, moby + 0xF0, buf1, 0xFF, speed, size);
    }
}

/* the horizontal speed the object carries in its data block */
f32 turret_get_horizontal_speed(char *moby) {
    return *(f32 *)(*(char **)(moby + 0x68) + 0x78);
}

/* func_L16_00416EC8 uses its dedicated quadword-copy and G16 profile. */

/* func_L16_00416FB0 is defined in L16_004165B0-aim-g8.c. */

/* func_L16_00417210 is defined in L16_00417210-g8.c. */

/* the model index the object's data block points at */
s32 turret_get_model_index(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    return *(s32 *)(vars + 0x60);
}

/* func_L16_00417798 is defined in L16_00417798-g8.c. */

/* func_L16_00417990 is defined in L16_00417990-g8.c. */

/* func_L16_00417DB0 is defined in L16_00417DB0.c. */



/* func_L16_004189A0 is defined in L16_004189A0.c. */

/* func_L16_00418E38 is defined in L16_004165B0-blend-g8.c. */

/* func_L16_00419140 is defined in L16_00419140-g8.c. */


extern char g_hero_state[];
extern void func_00315728(char *, char *, s32, char *, f32);
extern void func_00315948(char *, char *);

extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern s32 vec_fast_helper_b(char *);
extern void gfx_submit_subobject_angle_scale(char *);
extern void moby_set_state(char *, s32, s32);

/* Controls the timed rotation cycle and restores the original settings. */
void rotation_cycle_update(char *self) {
    char *vars = *(char **)(self + 0x68);
    f32 firstTime, secondTime, savedAngle;
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        *(s32 *)(vars + 0) = 0;
        *(s32 *)(vars + 4) = 0;
        *(s32 *)(vars + 8) = 0;
        *(s32 *)(vars + 12) = 0;
        *(s32 *)(vars + 16) = 0;
        firstTime = *(f32 *)(vars + 20);
        savedAngle = *(f32 *)(self + 0xF0);
        secondTime = *(f32 *)(vars + 24);
        *(f32 *)(vars + 40) = savedAngle;
        *(s32 *)(vars + 36) = *(u8 *)(self + 0xBC);
        *(f32 *)(vars + 32) = secondTime;
        *(f32 *)(vars + 28) = firstTime;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (*(u8 *)(self + 0xBC))
            moby_set_state(self, 4, -1);
        break;
    case 4:
        if (*(s32 *)(vars + 16) < 180) {
            *(f32 *)(self + 0xF0) = FastAddRotations(*(f32 *)(self + 0xF0), 0.0872664749622345f);
            *(s32 *)(vars + 16) += 5;
        } else moby_set_state(self, 2, -1);
        break;
    case 2:
        if (vec_fast_helper_b(vars + 20)) moby_set_state(self, 3, -1);
        break;
    case 3:
        if (vec_fast_helper_b(vars + 24)) moby_set_state(self, 5, -1);
        gfx_submit_subobject_angle_scale(self);
        break;
    case 5:
        if (*(s32 *)(vars + 16) > 0) {
            *(f32 *)(self + 0xF0) = fast_subtract_rotations(*(f32 *)(self + 0xF0), 0.0872664749622345f);
            *(s32 *)(vars + 16) -= 5;
        } else {
            *(u8 *)(self + 0xBC) = *(u8 *)(vars + 36);
            *(f32 *)(vars + 20) = *(f32 *)(vars + 28);
            *(f32 *)(vars + 24) = *(f32 *)(vars + 32);
            firstTime = *(f32 *)(vars + 40);
            *(f32 *)(self + 0xF0) = firstTime;
            moby_set_state(self, 1, -1);
        }
        break;
    }
}


/* func_L16_0041C990 is defined in L16_0041C990-g8.c. */


/* func_L16_0041CF80 is defined in L16_0041CF80.c. */

/* func_L16_0041E370 lives in L16_0041E370.c. */


/* func_L16_0041ECF8 lives in L16_004165B0-g8.c (it takes the address of a $gp global). */

/* func_L16_0041EE90 is defined in L16_0041EE90-g8.c. */

extern void func_002E74B8(char *, char *, char *);
extern s32 func_00313EE0(s32, s32);
extern s32 func_00313EA0(s32);
extern s32 func_003320E0(char *, char *, u32, u32, f32, u32, u32);
extern s32 func_002E8648(f32);

/* spawns the level's score pickup effect for this object */
void part_spawn_score_particle(char *moby) {
    char buf[0x10];
    char *vars = *(char **)(moby + 0x68);
    char *particle;
    s32 color;
    s32 alpha;

    func_002E74B8(buf, moby + 0x10, vars);
    color = func_00313EE0(3, 7) & 0xFF;
    alpha = func_00313EA0(0xFF) & 0xFF;
    particle = (char *)func_003320E0(buf, vars, 0x60006080, color, 2.5f, alpha, 0);
    if (particle == 0)
        return;
    particle[9] = (u8)(func_002E8648(4.0f) - 16);
}

/* func_L16_0041F1F0 lives in L16_0041F1F0.c. */

/* func_L16_0041F360 is defined in L16_0041F360-g8.c. */

/* func_L16_0041F360 is defined in L16_004165B0-ring-g8.c. */


