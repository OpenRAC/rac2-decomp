/* func_PAL_L00_002A4788, the PAL copy of func_L00_002A4928: the same C, where func_L00_002D5EB8
   becomes func_PAL_L00_002D6408; 180 becomes 150; 300 becomes 250. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct {
    char pad0[0x10];
    Vector pos;             /* 0x10 */
    char pad20[0x14];
    unsigned short flags;   /* 0x34 */
    char pad36[0x2C];
    unsigned char b62;      /* 0x62 */
    char pad63[0x1B];
    unsigned char b7E;      /* 0x7E */
    char pad7F[0x2B];
    short oclass;           /* 0xAA */
    char padAC[0x14];
    Vector basis;           /* 0xC0 */
    char padD0[0x10];
    Vector fwd;             /* 0xE0 */
    Vector axis;            /* 0xF0 */
} Moby;
typedef union {
    unsigned char b[0x2540];
    unsigned short h[0x12A0];
    int i[0x950];
    float f[0x950];
    Moby *m[0x950];
    Quad q[0x254];
} HeroState;
typedef struct { Vector pos, rot; } Placement;
typedef struct {
    char pad0;
    unsigned char attached; /* 0x01 */
    char pad2[0x3E];
    Vector rot;             /* 0x40 */
    Vector rot_vel;         /* 0x50 */
    Vector rot_target;      /* 0x60 */
    Vector pos;             /* 0x70 */
    Vector pos_vel;         /* 0x80 */
    Vector pos_target;      /* 0x90 */
    char padA0[0x10];
} Record;

extern char g_hero_state[];
extern int D_001A79F0_1[] __attribute__((sda));
extern int D_001A7398[] __attribute__((sda));
extern int D_001A7A00[] __attribute__((sda));
extern unsigned char D_001A7AFA[] __attribute__((sda));
extern Moby *D_L00_001B1E9C[] __attribute__((sda));
extern Moby *D_L00_001B1EA0[] __attribute__((sda));
extern int D_L00_001A8FF0[] __attribute__((sda));
extern Quad D_L00_001BF220;
extern Quad D_L00_001B1B10[] __attribute__((sda));
extern char D_00152C70[];
extern Record D_L00_0025BE10[];

extern void mem_clear(void *, int, int);
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void vec_clear_128(void *);
extern void hero_l00_update_ground_contact(void);
extern void update_hero_moby(void);
extern void anim_start_object_at_frame(int, int);
extern void func_PAL_L00_002D6408(void);
extern int math_random_int_range(int, int);


void func_PAL_L00_002A4788(void)
{
    int saved[7];
    Vector near, far;
    Moby *actor;
    int i;

    for (i = 0; i < 7; i++)
        saved[i] = ((HeroState *)g_hero_state)->i[0x1248 / 4 + i * 0x14];
    mem_clear(g_hero_state, 0, 0x2540);
    for (i = 0; i < 7; i++)
        saved[i] = ((HeroState *)g_hero_state)->i[0x1248 / 4 + i * 0x14];

    for (i = 0; &D_L00_001B1E9C[0][i] < D_L00_001B1EA0[0]; i++) {
        actor = &D_L00_001B1E9C[0][i];
        if (actor->oclass == 0) {
            (((HeroState *)g_hero_state)->m[0x2290 / 4]) = actor;
            euler_rotation_basis(&actor->basis, &actor->axis);
            vec_scale_to_length(&far, &(((HeroState *)g_hero_state)->m[0x2290 / 4])->fwd, -3.0f);
            vec_scale_to_length(&near, &(((HeroState *)g_hero_state)->m[0x2290 / 4])->fwd, 1.0f);
            FastVecAdd(&near, &near, &((HeroState *)g_hero_state)->q[8]);
            FastVecAdd(&far, &far, &((HeroState *)g_hero_state)->q[8]);
            if (CollLine(&near, &far, 2, (((HeroState *)g_hero_state)->m[0x2290 / 4]), 0) != 0)
                qcopy(&((HeroState *)g_hero_state)->q[8], &D_L00_001BF220);
            (((HeroState *)g_hero_state)->m[0x2290 / 4])->flags |= 2;
            ((HeroState *)g_hero_state)->m[0xC18 / 4] = (((HeroState *)g_hero_state)->m[0x2290 / 4]);
            ((HeroState *)g_hero_state)->f[0x98 / 4] = (((HeroState *)g_hero_state)->m[0x2290 / 4])->axis.f[2];
            qcopy(&((HeroState *)g_hero_state)->q[8], &(((HeroState *)g_hero_state)->m[0x2290 / 4])->pos);
            hero_l00_update_ground_contact();
            update_hero_moby();
            anim_start_object_at_frame(0, 0);
            qcopy(&((Placement *)D_00152C70)->pos, &((HeroState *)g_hero_state)->q[8]);
            qcopy(&((Placement *)D_00152C70)->rot, &((HeroState *)g_hero_state)->q[9]);
            break;
        }
    }
    if (D_001A79F0_1[0] == 1 || D_001A79F0_1[0] == 8)
        (((HeroState *)g_hero_state)->m[0x2290 / 4])->b7E |= 1;
    (((HeroState *)g_hero_state)->m[0x2290 / 4])->b62 = 0xFF;
    if (D_001A7398[0] == 0)
        D_001A7398[0] = 30;

    for (i = 0; i < 40; i++) {
        D_L00_0025BE10[i].attached = 0;
        vec_clear_128(&D_L00_0025BE10[i].rot_target);
        vec_clear_128(&D_L00_0025BE10[i].rot);
        vec_clear_128(&D_L00_0025BE10[i].rot_vel);
        vec_clear_128(&D_L00_0025BE10[i].pos_target);
        vec_clear_128(&D_L00_0025BE10[i].pos);
        vec_clear_128(&D_L00_0025BE10[i].pos_vel);
    }
    for (i = 0; i < 9; i++)
        ((HeroState *)g_hero_state)->i[0x242C / 4 + i] = -1;
    ((HeroState *)g_hero_state)->f[0x24A4 / 4] = 2.125f;
    ((HeroState *)g_hero_state)->f[0x24A8 / 4] = 1.25f;
    if (D_001A7A00[0] == 0)
        func_PAL_L00_002D6408();
    ((HeroState *)g_hero_state)->i[0x24D0 / 4] = 4;
    ((HeroState *)g_hero_state)->i[0x24CC / 4] = D_001A7A00[0];
    ((HeroState *)g_hero_state)->h[0x24D4 / 2] = ((HeroState *)g_hero_state)->h[0x24CC / 2];
    ((HeroState *)g_hero_state)->i[0x11A0 / 4] = math_random_int_range(150, 250);
    ((HeroState *)g_hero_state)->f[0x11A4 / 4] = 0.007f;
    ((HeroState *)g_hero_state)->f[0x11A8 / 4] = 0.3f;
    ((HeroState *)g_hero_state)->f[0xEB0 / 4] = 0.97f;
    if (D_L00_001A8FF0[0] != 0)
        qcopy(&((HeroState *)g_hero_state)->q[0xB0 / 16], D_L00_001B1B10);
    ((HeroState *)g_hero_state)->i[0x18D4 / 4] = 0;
    if (D_001A7AFA[0] == 0)
        ((HeroState *)g_hero_state)->h[0x24FC / 2] = 1;
}
