#include "common.h"

extern int ref_L00_002A3B80_00;

/* Returns a stored level setting value. */
int level_get_setting_value(void)
{
    return ref_L00_002A3B80_00;
}

/* func_L00_002A3B88 is defined in L00_002A3B88-g8.c: its declarations of D_00189E20 and
   D_001A7398 conflict with this file's. */

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
extern void hero_update_collection_progress(void);
extern int math_random_int_range(int, int);


/* Sets up the hero at level start: clears its state, finds the hero object and resets its aim, health and timers. */
void InitializeHero(void)
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
        hero_update_collection_progress();
    ((HeroState *)g_hero_state)->i[0x24D0 / 4] = 4;
    ((HeroState *)g_hero_state)->i[0x24CC / 4] = D_001A7A00[0];
    ((HeroState *)g_hero_state)->h[0x24D4 / 2] = ((HeroState *)g_hero_state)->h[0x24CC / 2];
    ((HeroState *)g_hero_state)->i[0x11A0 / 4] = math_random_int_range(180, 300);
    ((HeroState *)g_hero_state)->f[0x11A4 / 4] = 0.007f;
    ((HeroState *)g_hero_state)->f[0x11A8 / 4] = 0.3f;
    ((HeroState *)g_hero_state)->f[0xEB0 / 4] = 0.97f;
    if (D_L00_001A8FF0[0] != 0)
        qcopy(&((HeroState *)g_hero_state)->q[0xB0 / 16], D_L00_001B1B10);
    ((HeroState *)g_hero_state)->i[0x18D4 / 4] = 0;
    if (D_001A7AFA[0] == 0)
        ((HeroState *)g_hero_state)->h[0x24FC / 2] = 1;
}

extern char g_hero_state[];
extern int g_current_map_index;
extern void hero_clear_queued_anim(void);
extern int hero_l00_set_action(int, int);
extern void trail_reset_slots(void);
/* Incomplete sda array: retail clears this word as `lui $at; sw` (compiler-notes.md). */
extern int D_001A73A0[] __attribute__((sda));

/* Sets the hero's starting aim, speed and camera values when a level begins. */
void hero_reset_start_aim_speed(void)
{
    char *base = g_hero_state;

    *(float *)(base + 0x264) = 0.45f;
    *(float *)(base + 0x250) = 0.8f;
    *(float *)(base + 0x254) = 0.7f;
    *(float *)(base + 0x258) = 0.8f;
    *(float *)(base + 0x25C) = 0.7f;
    *(unsigned char *)(base + 0x24F0) = g_current_map_index == 0x1A;
    D_001A73A0[0] = 0;
    *(int *)(base + 0x2294) = 0;
    *(float *)(base + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    hero_l00_set_action(0, 1);
    trail_reset_slots();
}

extern void func_002A1130(void *a0, int a1, int a2, int a3);

extern void mem_fast_helper_c(int a0, int a1, int a2);

extern void FlushCache(int a0);

/* walks one loaded entry of an owner's list and hands it to the vector routine when the
   tag bits are set, else to the count-driven copy, then polls and returns the caller's
   handle */
int anim_copy_entry_data(char *source, int rowIndex, int entryIndex, int dest)
{
    char *owner = *(char **)(source + 0x24);
    char **rows = (char **)(owner + 0x48);
    char *row = rows[rowIndex];
    int *words = (int *)(row + 0x1C);
    int entry = words[entryIndex];

    if (entry & 0xF0000000)
        func_002A1130(row + 0x1C + (*(unsigned char *)(row + 0x10) << 2) - -(*(unsigned char *)(row + 0x13) << 2), entry, dest, *(unsigned char *)(owner + 8));
    else
        mem_fast_helper_c(dest, entry, (*(short *)(entry + 6) + 1) << 4);
    FlushCache(0);
    return dest;
}
