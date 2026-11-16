#include "common.h"

/* Built with -frac2-keep-block-order (config/cflags.txt): the shared `return 0`
   block stays behind the projectile arm, as in retail. */

extern float g_shot_range_default __attribute__((sda));
extern float g_shot_range_receiver __attribute__((sda));
extern float g_shot_speed_default __attribute__((sda));
extern float g_shot_speed_receiver __attribute__((sda));
extern float g_shot_hit_height __attribute__((sda));
extern unsigned char g_shooter_class_data[];
/* The explosion table sits at another address in level 18; MACRO_ADDR keeps
   retail's adjacent lui/addiu pair. */
extern unsigned char ref_L18_00428428_00[] MACRO_ADDR;
extern void func_002C27F0(void *, int);
extern void func_0032C5E0(void *, int, void *);
extern int func_00336F00(void *, void *, int, int, int, int, float, float, float);
extern int enemy_get_kind_index(void *);
/* Argument layout of RAC1's spawn_explosion, with one more integer. */
extern void func_0033A400(void *, void *, void *, float, float, int, int, int, float, float, float, float,
                          int, float, int, int, int, int, int);
extern void func_002FB998(void *, int, void *, void *, float);
extern void func_00308BD8(void *, void *, float);
extern float func_00308AD0(void *, void *);
extern char *receiver_bot_spawn_streak_projectile(void *, void *, void *, int, int, float, float, float);

/* Fires from joint side + 2. When the sphere test at that point reports contact, it
   spawns an explosion there and sends a hit record to nearby objects; otherwise it
   launches a projectile along the facing, aimed at the target's height unless the
   byte at 0xBC is set. */
u8 *shooter_fire_shot(unsigned char *obj, int side) {
    unsigned char *state = *(unsigned char **)(obj + 0x68);
    float range = g_shot_range_default;
    float speed = g_shot_speed_default;
    int mask;
    float pos[4] __attribute__((aligned(16)));
    struct { float vec[4]; void *owner; int flags; unsigned char a, b; unsigned short kind; float value; int one; } hit __attribute__((aligned(16)));

    switch (*(short *)(obj + 0xAA)) {
    case 0xEC0 /* moby class 3776 */: func_002C27F0(g_shooter_class_data, 0xEC0 /* moby class 3776 */); break;
    case MOBY_CLASS_RECEIVER_BOT: range = g_shot_range_receiver; speed = g_shot_speed_receiver; break;
    case 0xED4 /* moby class 3796 */:
    default: range = g_shot_range_default; speed = g_shot_speed_default; break;
    }
    func_0032C5E0(obj, side + 2, pos);
    mask = 1;
    if (!obj[0xBC])
        mask = 0x10000;
    if (func_00336F00(obj, pos, mask, 1, 3, 0, 0.35f, (float)state[0x34], g_shot_hit_height)) {
        hit.owner = obj;
        hit.flags = 0x810001;
        hit.value = (float)state[0x34];
        hit.one = 1;
        qzero_nc(hit.vec);
        hit.vec[2] = g_shot_hit_height;
        hit.vec[3] = 5627.925f;
        hit.a = 2;
        hit.b = 3;
        hit.kind = *(unsigned short *)(obj + 0xAA);
        func_0033A400(obj, ref_L18_00428428_00, pos, 0.0f, 0.0f, 5, 2, 9, 0.0f, 0.0f, 9.0f, 1.1f, enemy_get_kind_index(obj), 0.0f, 0, 1, -2, 0, 0x810001);
        func_002FB998(pos, 16, obj, &hit, 1.0f);
    } else {
        speed *= 0.016666668f;
        func_00308BD8(hit.vec, obj + 0xC0, speed);
        if (!obj[0xBC]) {
            float t = func_00308AD0(pos, state + 0x220) / speed;
            hit.vec[2] = (*(float *)(state + 0x228) - pos[2]) / t;
        }
        return receiver_bot_spawn_streak_projectile(pos, obj, hit.vec, 1, 3, (float)state[0x34], range, g_shot_hit_height);
    }
    return 0;
}
