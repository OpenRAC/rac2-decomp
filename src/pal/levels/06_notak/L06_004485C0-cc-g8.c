#include "names.h"
/* func_PAL_L06_004485C0, the PAL copy of func_L06_00443A38: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_L06_00443F30 becomes func_PAL_L06_00448AB8; rename func_002A6C58 becomes func_PAL_002A7650; rename func_002AC728 becomes func_PAL_002AD288. */
#include "common.h"

extern void moby_set_state(char *, int, int);
extern void anim_start_blended_pal(char *, int, int, int);
extern int moby_apply_damage_to_object_pal(char *, char *, int);
typedef struct {
    char pad00[0x1830]; unsigned char *player;
    char pad1834[0xA60]; int mode;
} ControllerGlobals;
extern ControllerGlobals g_hero_state;
extern char g_effect_target_records[], g_hero_l06_position[];
extern int g_effect_group_counts[] SDATA(D_L06_001B1858);
extern int g_effect_context_a SDATA(D_L06_001B187C);
extern int g_effect_context_b SDATA(D_L06_001B1880);
extern int g_moby_l06_group_count;
extern char *g_path_record_table;
extern float g_creature_wander_time_a __attribute__((sda));
extern char g_str_notak_debug_a[];
extern char g_str_notak_debug_b[];
extern void STUB_printf(const char *, ...);
extern void math_trap_always(void);
extern int FloatToInt(float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void actor_alert_group_and_markers(u8 *);
extern void moby_l06_explode_and_remove_pal(char *);
extern void SetDeathBits_pal(void *, int, int);
extern void part_spawn_explosion_with_sparks_pal(void *, void *, int, float, float);
extern void moby_mark_spawned(void *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);

/* A Notak enemy's update (spawn-time setup, then the shared distance, target and ground
   checks). The fields are indexed through typed pointers so their MEMs are in-struct: the
   sda and table loads after the angle call may then move above the word stores, as in
   retail. The setup's store order is the one that gives retail's schedule and FP registers. */
#define B(o) (v[o])
#define H(o) (((short *)v)[(o) / 2])
#define I(o) (((int *)v)[(o) / 4])
#define F(o) (((float *)v)[(o) / 4])

void notak_enemy_update_pal(u8 *moby)
{
    u8 *v = *(u8 **)(moby + 0x68);
    int hit;

    if (moby[0x20] == 0) {
        char *rec;

        if (g_moby_l06_group_count < moby[0x21]) {
            STUB_printf(g_str_notak_debug_a);
            STUB_printf(g_str_notak_debug_b);
            math_trap_always();
        }
        moby[0x30] = 0x40;
        qcopy(v + 0x2E0, moby + 0x10);
        F(0x324) = 1.0f;
        B(0x48) = FloatToInt(15.0f);
        B(0x4A) = FloatToInt(4.8f);
        H(0x88) = 0;
        B(0x60) = 8;
        I(0x98) = 3;
        F(0x108) = 0.5f;
        F(0x80) = 0.2f;
        F(0x84) = 0.2f;
        B(0x28) = 3;
        F(0x30) = 0.333f;
        F(0x8C) = 0.4f;
        F(0x100) = F(0x324) * 0.6f;
        F(0x134) = 0.05f;
        F(0x104) = F(0x324) * 0.5f;
        F(0x10C) = 0.5f;
        I(0x138) |= 0x80;
        F(0x110) = 1.57079649f;
        F(0x130) = 0.52359885f;
        F(0x1DC) = math_random_signed_float_range(18.0f, 22.0f) * 0.0174532942f;
        B(0x1E8) = 7;
        B(0x1E9) = 6;
        H(0x1E2) = 100;
        H(0x1E4) = 150;
        F(0x1D4) = 3.0f;
        F(0x1D0) = g_creature_wander_time_a * 0.020000001f;
        rec = g_path_record_table + I(0x210) * 0x30;
        if (*(short *)(rec + 0x30) != 0)
            I(0x13C) = **(int **)(rec + 0x3C);
        F(0x328) = math_random_angle();
        if (I(0x214) != 0) {
            *(int *)(moby + 0x98) = 0;
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
            moby_set_state((char *)moby, 9, 4);
            if (moby[0x43] != 10)
                anim_start_blended_pal((char *)moby, 10, 0, 0);
        } else {
            moby_set_state((char *)moby, 1, 0);
            if (moby[0x43] != 0)
                anim_start_blended_pal((char *)moby, 0, 0, 0);
        }
    }
    if (moby[0x31] != 0 && fast_vec_dist(moby + 0x10, g_hero_l06_position) < 24.0f) {
        moby_update_ground_check(moby);
        moby[0x6F] = 0x16;
    }
    hit = moby_apply_damage_to_object_pal((char *)moby, (char *)(v + 0x50), 0);
    if (hit != 0) {
        actor_alert_group_and_markers(moby);
        if (hit >= 4)
            moby_l06_explode_and_remove_pal((char *)moby);
    }
    if (*(float *)(moby + 0x18) < 48.0f) {
        SetDeathBits_pal(moby, 0, 3);
        part_spawn_explosion_with_sparks_pal(moby, moby + 0x10, -1, 1.0f, 13.0f);
        moby_mark_spawned(moby);
    } else if (moby[0x95] != 3 && moby[0x95] != 4) {
        H(0x314) = weapon_select_aim_target(moby, I(0x210), 16.0f, 0.0f, 0, 0);
    }
}

#undef B
#undef H
#undef I
#undef F

void actor_alert_group_and_markers(u8 *arg0);

/* The id-list walks below read D_L06_001B281C as a bare symbol (a second name for the 4-byte
   `sda` pointer above, declared as a 12-byte array so the assembler keeps its loads absolute),
   while D_L06_001B2838 is a plain int: its `.extern` comes last in the file, which leaves a load
   in a branch delay slot on $gp and every other load on `lui`/`lw`. */
extern int g_moby_l06_group_count;
/* Overlays for an owner (L06Obj) and the state block it points to (L06Cfg); only the fields the
   next two functions touch are named. */
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L06Cfg;

typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L06Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L06Obj;

typedef struct {
    int a;
    int b;
} L06ColorPair;

extern void marker_draw_group(L06Obj *);
extern L06ColorPair g_marker_color_pairs[];
/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   colour pair and, when its stamp is not the current one, refreshes every live class-0xDB0
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L06_00444300 for the owner. */
/* D_L06_001B10A0 is only used for its address, taken through $gp. D_L06_001B10B0 is one 8-byte
   object: its first word is loaded in a branch delay slot (so on $gp), its second as a bare
   symbol, which is how retail loads the two colours. */
/* For every live class-0xDB0 entity in the owner's group, builds the marker's vector from the
   entity's size and stored position and hands it to func_L00_00325AE8 with the colour pair
   blended by the entity's pulse. */
void marker_draw_group(L06Obj *self);

/* The level's three turn angles, in degrees (37, 41 and 70); the step below turns them into
   radians per frame. The first one is read through $gp, the other two absolutely. */
/* Turns the owner's three angles by the level's step, then walks the owner's eight records:
   each gets a fresh object, scaled and blended against the owner's own axes. `axes` is the
   scratch area func_32DE28 fills; its first vector is the one the objects are given. */
