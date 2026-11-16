#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

extern char *g_moby_instance_table __attribute__((sda));
extern char *D_L16_001B2B1C_2;
extern char g_hero_position[];
extern s32 func_00319BE8(char *, s32);

/* runs the object's start-up state once and marks the four sub-objects it carries as alive */
void moby_activate_linked(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *entry;
    u8 entryState;

    if (*(u8 *)(moby + 0x20) == 0)
        *(u8 *)(moby + 0x20) = 1;
    if (*(u8 *)(moby + 0x20) != 1)
        return;

    entry = (*(s32 *)vars << 8) + D_L16_001B2B1C_2;
    if (entry != 0) {
        entryState = *(u8 *)(entry + 0x20);
        if (entryState != 0xFE) {
            if (entryState != 0xFD)
                return;
        }
    }
    if (func_00319BE8(g_hero_position, *(s32 *)(vars + 4)) == 0)
        return;
    if (*(s32 *)(vars + 0x10) != -1)
        *(u8 *)(g_moby_instance_table + (*(s32 *)(vars + 0x10) << 8) + 0xBC) = 1;
    if (*(s32 *)(vars + 0x14) != -1)
        *(u8 *)(g_moby_instance_table + (*(s32 *)(vars + 0x14) << 8) + 0xBC) = 1;
    if (*(s32 *)(vars + 0x18) != -1)
        *(u8 *)(g_moby_instance_table + (*(s32 *)(vars + 0x18) << 8) + 0xBC) = 1;
    if (*(s32 *)(vars + 0x1C) != -1)
        *(u8 *)(g_moby_instance_table + (*(s32 *)(vars + 0x1C) << 8) + 0xBC) = 1;
    *(u8 *)(moby + 0x20) = 2;
}

extern s32 g_level_l16_word_c __attribute__((sda));
extern s32 g_level_l16_word_a __attribute__((sda));
extern s32 g_level_l16_word_b __attribute__((sda));
extern s32 g_level_word_d __attribute__((sda));
extern s32 g_unused_word_2 __attribute__((nosda));
extern f32 g_level_l16_float_param __attribute__((sda));
extern s32 func_003219A0(char *);
extern void func_00313DD0(char *, s32, s32);
extern f32 func_002E73F8(f32);
extern void func_0041ECF8(char *, f32);

extern f32 g_spark_dir_speed_min __attribute__((sda));
extern f32 g_float_data_unused_a __attribute__((nosda));
extern f32 g_float_data_unused_b __attribute__((nosda));
extern f32 g_float_data_unused_c __attribute__((nosda));
extern f32 g_spark_first_scale __attribute__((sda));
extern f32 g_float_data_unused_d __attribute__((nosda));
extern s32 g_spark_first_part_id __attribute__((sda));
extern s32 g_word_data_unused_a __attribute__((nosda));
extern s32 g_spark_first_kind_min __attribute__((sda));
extern s32 g_word_data_unused_b __attribute__((nosda));
extern s32 g_word_data_unused_c __attribute__((nosda));
extern s32 g_unused_word __attribute__((nosda));
extern s32 g_spark_count __attribute__((sda));
extern void func_003140C0(char *, f32, f32);
extern s32 func_00313EE0(s32, s32);
extern s32 func_00313EA0(s32);
extern s32 func_003320E0(char *, char *, u32, u32, f32, u32, u32);
extern f32 func_00313F38(f32, f32);
extern void func_002E7450(char *);
extern void func_002E7488(char *, char *, char *);

extern s32 g_held_object_ptr __attribute__((nosda));
extern s32 g_snivelak_target __attribute__((sda));
extern void func_002C4368(s32);
extern void func_00433698(s32);

/* clears the level state word and reseeds the two engine subsystems */
void turret_reset_camera_state(void) {
    g_held_object_ptr = 0;
    g_snivelak_target = 0;
    func_002C4368(0);
    func_00433698(3);
}

extern f32 g_subobject_spin_param __attribute__((sda));
extern f32 g_subobject_angle_scale __attribute__((sda));
extern void func_0031C698(char *, char *, char *, f32, f32, f32);

/* submits the sub-object at 0x68 with the level's angle scale */
void gfx_submit_subobject_angle_scale(char *moby) {
    char *self = moby;
    char *st = *(char **)(self + 0x68);

    func_0031C698(self, st + 4, st, g_subobject_spin_param, g_subobject_angle_scale * 0.000290888245f, -1.0f);
}

extern char g_hero_position[];
extern s32 g_turret_local_offset __attribute__((sda));
extern void func_002E7968(char *, s32 *, char *);
extern void func_002E7488(char *, char *, char *);

/* installs the two level matrices on the shared render object */
void turret_set_camera_matrices(char *moby) {
    char *obj = g_hero_position;

    func_002E7968(obj, &g_turret_local_offset, moby + 0xC0);
    func_002E7488(obj, obj, moby + 0x10);
    *(f32 *)(obj + 0x18) = *(f32 *)(moby + 0xF8);
}

extern f32 g_quad_packet_value_first __attribute__((sda));
extern f32 g_quad_packet_value_second __attribute__((sda));
extern f32 g_quad_packet_value_third __attribute__((sda));
extern f32 g_quad_packet_value_fourth __attribute__((sda));

/* initialises the level object's scale/limit table */
void gfx_init_quad_packet_table(char *table) {
    f32 first = g_quad_packet_value_first;
    f32 second = g_quad_packet_value_second;
    f32 third = g_quad_packet_value_third;
    f32 fourth = g_quad_packet_value_fourth;

    *(long long *)(table + 112) = 0LL;
    *(int *)(table + 80) = 0;
    *(int *)(table + 84) = 0;
    *(float *)(table + 88) = 1.0f;
    *(int *)(table + 92) = 0;
    *(int *)(table + 96) = 0;
    *(float *)(table + 100) = 1.0f;
    *(float *)(table + 104) = 1.0f;
    *(float *)(table + 108) = 1.0f;
    *(float *)(table + 8) = first;
    *(float *)(table + 24) = second;
    *(long long *)(table + 128) = 0x0000FF9000000260LL;
    *(float *)(table + 40) = first;
    *(float *)(table + 4) = third;
    *(float *)(table + 36) = fourth;
    *(int *)(table + 0) = 0;
    *(int *)(table + 16) = 0;
    *(int *)(table + 32) = 0;
    *(int *)(table + 48) = 0;
    *(float *)(table + 12) = 1.0f;
    *(float *)(table + 28) = 1.0f;
    *(float *)(table + 44) = 1.0f;
    *(float *)(table + 56) = second;
    *(float *)(table + 20) = third;
    *(float *)(table + 52) = fourth;
    *(float *)(table + 60) = 1.0f;
}

/* The id-list walk below reads D_L16_001B2B1C as a bare symbol (a second name for the 4-byte
   `sda` pointer above, declared as a 12-byte array so the assembler keeps its loads absolute),
   while D_L16_001B2B38 is a plain int: its `.extern` comes last in the file, which leaves a load
   in a branch delay slot on $gp and every other load on `lui`/`lw`. */
extern unsigned char *D_L16_001B2B1C_base[3] __asm__("D_L16_001B2B1C") __attribute__((sda));
extern s32 g_group_id_limit;
extern unsigned short *g_group_l16_id_lists[];
extern s32 g_moby_spin_offset_vec __attribute__((sda));
extern void matrix_mul_vec3(char *, char *, char *);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecSub(char *, char *, char *);
extern void vec_transform_by_object_or_given(char *, char *, char *, s32);
extern void euler_rotation_basis(char *, char *);

/* Builds a transform in buf0 from the object's +0xC0 and +0x10 blocks, then, for every entity of
   the object's group (byte 0x21): derives buf1 from buf0 and the entity's position, has
   func_002AFDD8 fill buf2, stores the argument at +0xF4 (negated for class 0x125D) and rewrites
   the entity's +0x10 block from its +0xC0 frame and the two buffers. */
void moby_spin_group_entities(char *self, f32 spin) {
    char buf0[0x10];
    char buf1[0x10];
    char buf2[0x10];
    char buf3[0x10];
    unsigned short *idList;
    char *entity;
    f32 spinValue;

    matrix_mul_vec3(buf0, (char *)&g_moby_spin_offset_vec, self + 0xC0);
    FastVecAdd(buf0, buf0, self + 0x10);
    for (idList = g_group_l16_id_lists[*(u8 *)(self + 0x21)];
         *(u8 *)(self + 0x21) != 0xFF && *(u8 *)(self + 0x21) <= g_group_id_limit && idList != 0 &&
         ((idList != 0 && (short)idList[-1] >= 0) || idList == g_group_l16_id_lists[*(u8 *)(self + 0x21)]);
         idList++) {
        entity = (char *)D_L16_001B2B1C_base[0] + ((*idList & 0x7FFF) << 8);
        if (entity == 0)
            break;
        FastVecSub(buf1, buf0, entity + 0x10);
        vec_transform_by_object_or_given(entity, buf2, buf1, 0);
        spinValue = spin;
        if (*(short *)(entity + 0xAA) == 0x125D)
            spinValue = -spinValue;
        *(f32 *)(entity + 0xF4) = spinValue;
        euler_rotation_basis(entity + 0xC0, entity + 0xF0);
        matrix_mul_vec3(buf2, buf2, entity + 0xC0);
        FastVecSub(buf3, buf2, buf1);
        FastVecSub(entity + 0x10, entity + 0x10, buf3);
    }
}

extern s32 g_player_stats;
extern void func_002E7788(char *, char *, f32);
extern char g_hero_state[];
extern void func_00315728(char *, char *, s32, char *, f32);
extern void func_00315948(char *, char *);

/* next frame: arms the object once the shared render state names it, then hands its box to the collision pass */
void trigger_box_update(char *moby) {
    char buf[0x30];
    char extent[0x10];
    char *hero;
    char *lockedTarget;

    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x20) = 1;
        *(u8 *)(moby + 0x31) = 0;
        *(u16 *)(moby + 0x34) |= 1;
    }
    if (*(u8 *)(moby + 0x20) != 1)
        return;
    hero = g_hero_state;
    lockedTarget = *(char **)(hero + 0x33C);
    if (lockedTarget == 0 || lockedTarget != moby)
        return;
    if (*(s32 *)(hero + 0x340) == 0)
        return;
    *(s32 *)(extent + 0) = 0;
    *(f32 *)(extent + 4) = 1.0f;
    *(s32 *)(extent + 8) = 0;
    *(f32 *)(extent + 0xC) = 1.0f;
    func_002E7788(extent, extent, 10.0f);
    func_00315728(buf, moby, 1, extent, (f32)(g_player_stats * 200));
    *(u16 *)(buf + 0x1A) = *(u16 *)(moby + 0xAA);
    func_00315948(*(char **)(hero + 0x2290), buf);
}
