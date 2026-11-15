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

extern s32 D_L00_001A8FF4[] __attribute__((sda));
extern s32 D_L00_001A8FF0[] __attribute__((sda));
extern u8 D_00139578[];
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
extern float mat_fast_helper_a(float, float);
extern struct { char pad[0x80]; float x, y; } g_hero_state;
extern short D_L00_001B2030[] __attribute__((sda));
extern void AddMobyToIndexList(void *, short *, short);

/* Spawn class 0xEB0, initialize its timer and weapon-dependent rate,
   transfer the source link state, and add it to the short-index list. */
/* Turns a thrown object into a Dark Sheep (moby class 3760) at the same spot. */
Moby403730 *dark_sheep_spawn_from_object(Moby403730 *self) {
    f32 mtx[16] __attribute__((aligned(16)));
    Moby403730 *m;
    Vars403730 *vars;
    Link403730 *link;
    Weapon403730 *w;
    f32 rate;

    m = CreateMoby(0xEB0 /* Dark Sheep */);
    if (m != 0) {
        m->alpha = 0x7F;
        m->f32 = 0x7F;
        m->f31 = 1;
        vars = m->vars;
        m->scale = math_random_float_range(0.85f, 1.15f);
        qcopy(m->pos, self->pos);
        if (D_L00_001A8FF4[0] != 0 || D_L00_001A8FF0[0] != 0) {
            copy_matrix_rotation(mtx, self->mtx);
            mat_get_euler_angles(mtx, m->rot);
        } else {
            vec_clear_128(m->rot);
            m->rot[2] = mat_fast_helper_a(m->pos[0] - g_hero_state.x, m->pos[1] - g_hero_state.y);
        }
        m->state = 1;
        vars->f56 = 0;
        vars->delay = math_random_int_range(0x78, 0x12C);
        vars->f70 = 600;
        vars->f74 = 15;
        vars->f5C = 0;
        vars->f78 = 0;
        m->state = 4;
        m->f98 = m->cls->f10;
        w = &g_weapon_l00_table[D_00139578[0]];
        rate = 1.0f;
        if (w->f4 != 0) {
            rate = 4.0f;
        }
        vars->rate = rate;
        vars->f60 = -1;
        if (m->flags & 0x1000) {
            SetDeathBits(self, 0, 3);
        }
        link = moby_get_private_value_0(self);
        if (link != 0 && link->mode == 1) {
            link->mode = 2;
        } else {
            moby_mark_spawned(self);
        }
        AddMobyToIndexList(m, D_L00_001B2030, 31);
        func_002A0F48(m);
    }
    return m;
}
