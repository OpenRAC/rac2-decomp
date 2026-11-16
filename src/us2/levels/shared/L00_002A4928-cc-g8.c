/* func_US2_L00_002A4928, the USA v2.00 copy of func_L00_002A4928: the same C, where rename func_L00_002D5EB8 becomes func_US2_L00_002D6258. */
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
extern int g_menu_choice_table[] __attribute__((sda));
extern int g_player_stats[] __attribute__((sda));
extern unsigned char g_barlow_hint_inside_flag[] __attribute__((sda));
extern Moby *g_moby_array_base[] __attribute__((sda));
extern Moby *g_moby_array_end_sentinel[] __attribute__((sda));
extern int g_hero_locked_flag[] __attribute__((sda));
extern Quad g_hero_l00_position;
extern Quad g_camera_offset_vector[] __attribute__((sda));
extern char g_hero_placement[];
extern Record g_hero_item_attach_records[];

extern void mem_clear(void *, int, int);
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void vec_clear_128(void *);
extern void hero_l00_update_ground_contact(void);
extern void update_hero_moby(void);
extern void anim_start_object_at_frame(int, int);
extern void hero_update_collection_progress_us2(void);
extern int math_random_int_range(int, int);


/* Sets up the hero at level start: clears its state, finds the hero object and resets its aim, health and timers. */
void InitializeHero_us2(void)
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

    for (i = 0; &g_moby_array_base[0][i] < g_moby_array_end_sentinel[0]; i++) {
        actor = &g_moby_array_base[0][i];
        if (actor->oclass == 0) {
            (((HeroState *)g_hero_state)->m[0x2290 / 4]) = actor;
            euler_rotation_basis(&actor->basis, &actor->axis);
            vec_scale_to_length(&far, &(((HeroState *)g_hero_state)->m[0x2290 / 4])->fwd, -3.0f);
            vec_scale_to_length(&near, &(((HeroState *)g_hero_state)->m[0x2290 / 4])->fwd, 1.0f);
            FastVecAdd(&near, &near, &((HeroState *)g_hero_state)->q[8]);
            FastVecAdd(&far, &far, &((HeroState *)g_hero_state)->q[8]);
            if (CollLine(&near, &far, 2, (((HeroState *)g_hero_state)->m[0x2290 / 4]), 0) != 0)
                qcopy(&((HeroState *)g_hero_state)->q[8], &g_hero_l00_position);
            (((HeroState *)g_hero_state)->m[0x2290 / 4])->flags |= 2;
            ((HeroState *)g_hero_state)->m[0xC18 / 4] = (((HeroState *)g_hero_state)->m[0x2290 / 4]);
            ((HeroState *)g_hero_state)->f[0x98 / 4] = (((HeroState *)g_hero_state)->m[0x2290 / 4])->axis.f[2];
            qcopy(&((HeroState *)g_hero_state)->q[8], &(((HeroState *)g_hero_state)->m[0x2290 / 4])->pos);
            hero_l00_update_ground_contact();
            update_hero_moby();
            anim_start_object_at_frame(0, 0);
            qcopy(&((Placement *)g_hero_placement)->pos, &((HeroState *)g_hero_state)->q[8]);
            qcopy(&((Placement *)g_hero_placement)->rot, &((HeroState *)g_hero_state)->q[9]);
            break;
        }
    }
    if (D_001A79F0_1[0] == 1 || D_001A79F0_1[0] == 8)
        (((HeroState *)g_hero_state)->m[0x2290 / 4])->b7E |= 1;
    (((HeroState *)g_hero_state)->m[0x2290 / 4])->b62 = 0xFF;
    if (g_menu_choice_table[0] == 0)
        g_menu_choice_table[0] = 30;

    for (i = 0; i < 40; i++) {
        g_hero_item_attach_records[i].attached = 0;
        vec_clear_128(&g_hero_item_attach_records[i].rot_target);
        vec_clear_128(&g_hero_item_attach_records[i].rot);
        vec_clear_128(&g_hero_item_attach_records[i].rot_vel);
        vec_clear_128(&g_hero_item_attach_records[i].pos_target);
        vec_clear_128(&g_hero_item_attach_records[i].pos);
        vec_clear_128(&g_hero_item_attach_records[i].pos_vel);
    }
    for (i = 0; i < 9; i++)
        ((HeroState *)g_hero_state)->i[0x242C / 4 + i] = -1;
    ((HeroState *)g_hero_state)->f[0x24A4 / 4] = 2.125f;
    ((HeroState *)g_hero_state)->f[0x24A8 / 4] = 1.25f;
    if (g_player_stats[0] == 0)
        hero_update_collection_progress_us2();
    ((HeroState *)g_hero_state)->i[0x24D0 / 4] = 4;
    ((HeroState *)g_hero_state)->i[0x24CC / 4] = g_player_stats[0];
    ((HeroState *)g_hero_state)->h[0x24D4 / 2] = ((HeroState *)g_hero_state)->h[0x24CC / 2];
    ((HeroState *)g_hero_state)->i[0x11A0 / 4] = math_random_int_range(180, 300);
    ((HeroState *)g_hero_state)->f[0x11A4 / 4] = 0.007f;
    ((HeroState *)g_hero_state)->f[0x11A8 / 4] = 0.3f;
    ((HeroState *)g_hero_state)->f[0xEB0 / 4] = 0.97f;
    if (g_hero_locked_flag[0] != 0)
        qcopy(&((HeroState *)g_hero_state)->q[0xB0 / 16], g_camera_offset_vector);
    ((HeroState *)g_hero_state)->i[0x18D4 / 4] = 0;
    if (g_barlow_hint_inside_flag[0] == 0)
        ((HeroState *)g_hero_state)->h[0x24FC / 2] = 1;
}

extern char g_hero_state[];
/* Incomplete sda array: retail clears this word as `lui $at; sw` (compiler-notes.md). */
/* walks one loaded entry of an owner's list and hands it to the vector routine when the
   tag bits are set, else to the count-driven copy, then polls and returns the caller's
   handle */
