#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[4];
    u8 f4;
    u8 pad05[0xE0 - 5];
} Weapon403730;

typedef struct {
    u8 pad00[0x10];
    s32 f10;
} Class403730;

typedef struct {
    u8 pad00[0x54];
    s16 delay;
    s16 f56;
    u8 pad58[4];
    s32 f5C;
    s32 f60;
    u8 pad64[4];
    f32 rate;
    u8 pad6C[4];
    s32 f70;
    s32 f74;
    s32 f78;
} Vars403730;

typedef struct {
    u8 pad00[0xE];
    u8 mode;
    u8 pad0F[0x17 - 0xF];
    u8 f17;
} Link403730;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 state;
    u8 pad21[3];
    Class403730 *cls;
    u8 pad28[8];
    u8 alpha;
    u8 f31;
    s16 f32;
    u16 flags;
    u8 pad36[0x48 - 0x36];
    f32 scale;
    u8 pad4C[0x68 - 0x4C];
    Vars403730 *vars;
    u8 pad6C[0x98 - 0x6C];
    s32 f98;
    u8 pad9C[0xC0 - 0x9C];
    f32 mtx[12];
    f32 rot[4];
} Moby403730;

extern s32 g_enemy_ai_frozen[] __attribute__((sda));
extern s32 g_hero_height_zone_active[] __attribute__((sda));
extern u8 g_sheepinator_weapon_index[];
extern Weapon403730 g_weapon_l00_table[];

extern void vec_clear_128(void *);
extern void copy_matrix_rotation(void *, void *);
extern Moby403730 *CreateMoby(int);
extern void moby_mark_spawned(void *);
extern void func_002A0F48(void *);
extern void SetDeathBits(void *, int, int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern Link403730 *moby_get_private_value_0(void *);
extern void mat_get_euler_angles(float *, float *);
extern void sheep_add_to_active_list(void *);

/* func_US2_L00_00404C18, the USA v2.00 copy of func_L00_00403730: the same C, where the flags test reads source and a link already in mode 2 also takes the mode-2 arm. */
/* Spawns moby 0xE7D at source's position: random scale, orientation copied from source's matrix or randomised, then starts it in state 4. */
Moby403730 *sheep_spawn_from_object_us2(Moby403730 *source) {
    f32 mtx[16] __attribute__((aligned(16)));
    Moby403730 *sheep;
    Vars403730 *vars;
    Link403730 *link;
    Weapon403730 *weapon;
    f32 rate;

    sheep = CreateMoby(MOBY_CLASS_SHEEP);
    if (sheep != 0) {
        sheep->alpha = 0x7F;
        sheep->f32 = 0x7F;
        sheep->f31 = 1;
        vars = sheep->vars;
        sheep->scale = math_random_float_range(0.85f, 1.15f);
        qcopy(sheep->pos, source->pos);
        if (g_enemy_ai_frozen[0] != 0 || g_hero_height_zone_active[0] != 0) {
            copy_matrix_rotation(mtx, source->mtx);
            mat_get_euler_angles(mtx, sheep->rot);
        } else {
            vec_clear_128(sheep->rot);
            sheep->rot[2] = math_random_angle();
        }
        sheep->state = 0;
        vars->f56 = 0;
        vars->delay = math_random_int_range(0x78, 0x12C);
        vars->f70 = 600;
        vars->f74 = 30;
        vars->f5C = 0;
        vars->f78 = 0;
        sheep->state = 4;
        sheep_add_to_active_list(sheep);
        sheep->f98 = sheep->cls->f10;
        weapon = &g_weapon_l00_table[g_sheepinator_weapon_index[0]];
        rate = 1.0f;
        if (weapon->f4 != 0) {
            rate = 4.0f;
        }
        vars->rate = rate;
        vars->f60 = -1;
        link = moby_get_private_value_0(source);
        link->f17 = 0x10;
        if (source->flags & 0x1000) {
            SetDeathBits(source, 0, 3);
        }
        if ((link != 0 && link->mode == 1) || link->mode == 2) {
            link->mode = 2;
        } else {
            moby_mark_spawned(source);
        }
        func_002A0F48(sheep);
    }
    return sheep;
}
