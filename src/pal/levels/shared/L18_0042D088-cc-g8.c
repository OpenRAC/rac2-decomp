#include "names.h"
/* func_PAL_L18_0042D088, the PAL copy of func_L18_00428428: the same C, where rename-macro func_002ABBB8 becomes func_PAL_002AC718; rename func_002C27F0 becomes func_0026FEB8; rename func_0032C5E0 becomes func_0029FCC0; rename func_00336F00 becomes func_002A8C28; rename func_0033A400 becomes func_PAL_002AC718; rename func_002FB998 becomes func_00277F48; rename func_00308BD8 becomes func_00282F20; rename func_00308AD0 becomes func_00282E80. */
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
extern void STUB_printf(void *, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern int enemy_get_kind_index(void *);
/* Argument layout of RAC1's spawn_explosion, with one more integer. */
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float,
                          int, float, int, int, int, int, int);
extern int coll_process_hit(void *, int, void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern char *receiver_bot_spawn_streak_projectile(void *, void *, void *, int, int, float, float, float);

/* Fires from joint side + 2. When the sphere test at that point reports contact, it
   spawns an explosion there and sends a hit record to nearby objects; otherwise it
   launches a projectile along the facing, aimed at the target's height unless the
   byte at 0xBC is set (PAL: 50 Hz shot rates). */
u8 *shooter_fire_shot_pal(unsigned char *moby, int side) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float range = g_shot_range_default;
    float speed = g_shot_speed_default;
    int mask;
    float pos[4] __attribute__((aligned(16)));
    struct { float vec[4]; void *owner; int flags; unsigned char a, b; unsigned short kind; float value; int one; } hit __attribute__((aligned(16)));

    switch (*(short *)(moby + 0xAA)) {
    case 0xEC0 /* moby class 3776 */: STUB_printf(g_shooter_class_data, 0xEC0); break;
    case MOBY_CLASS_RECEIVER_BOT: range = g_shot_range_receiver; speed = g_shot_speed_receiver; break;
    case 0xED4 /* moby class 3796 */:
    default: range = g_shot_range_default; speed = g_shot_speed_default; break;
    }
    moby_transform_joint_to_world(moby, side + 2, pos);
    mask = 1;
    if (!moby[0xBC])
        mask = 0x10000;
    if (coll_sweep_from_object(moby, pos, mask, 1, 3, 0, 0.35f, (float)vars[0x34], g_shot_hit_height)) {
        hit.owner = moby;
        hit.flags = 0x810001;
        hit.value = (float)vars[0x34];
        hit.one = 1;
        qzero_nc(hit.vec);
        hit.vec[2] = g_shot_hit_height;
        hit.vec[3] = 5627.925f;
        hit.a = 2;
        hit.b = 3;
        hit.kind = *(unsigned short *)(moby + 0xAA);
        SpawnExplosionEffects_pal(moby, ref_L18_00428428_00, pos, 0.0f, 0.0f, 5, 2, 9, 0.0f, 0.0f, 9.0f, 1.1f, enemy_get_kind_index(moby), 0.0f, 0, 1, -2, 0, 0x810001);
        coll_process_hit(pos, 16, moby, &hit, 1.0f);
    } else {
        speed *= 0.020000001f;
        vec_scale_to_length(hit.vec, moby + 0xC0, speed);
        if (!moby[0xBC]) {
            float t = vec_distance_xy(pos, vars + 0x220) / speed;
            hit.vec[2] = (*(float *)(vars + 0x228) - pos[2]) / t;
        }
        return receiver_bot_spawn_streak_projectile(pos, moby, hit.vec, 1, 3, (float)vars[0x34], range, g_shot_hit_height);
    }
    return 0;
}
