#include "common.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

extern int FloatToInt(f32);

extern u8 *part_l17_spawn_fading(f32, s32, s32, s32);

extern f32 g_effect_spawner_seconds __attribute__((sda));

extern void moby_set_state(void *, s32, s32);

extern void *part_find_owned_effect_slot(void *, s32, s32);

extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);

extern char *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32, s32);

extern void moby_mark_spawned(void *);

extern s32 g_hit_burst_piece_param __attribute__((sda));

extern s32 g_hit_burst_piece_table_c __attribute__((sda));

extern s32 g_hit_burst_piece_table_b __attribute__((sda));

extern s32 g_hit_burst_piece_table_a __attribute__((sda));


extern char *g_moby_l17_pool __attribute__((sda));

typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(short *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))

/* The 0x30-byte record func_L04_0033CB88 fills with its defaults. */
typedef struct {
    s32 i00;
    f32 f04;
    f32 f08;
    f32 f0C;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[8];
} L17Timer;

/* The object's state record, as far as func_L17_003E41A8 uses it. Its stores are struct
   members, so the sda float D_L17_001B0CA8 (a fixed scalar) is read ahead of them. */
typedef struct {
    u8 pad000[0x28];
    u8 b28;
    u8 b29;
    u8 pad02A[6];
    f32 f30;
    u8 b34;
    u8 pad035[0x13];
    u8 b48;
    u8 pad049;
    u8 b4A;
    u8 pad04B[0x15];
    u8 ai[0x10];
    u8 b70;
    u8 b71;
    u8 pad072[4];
    u8 b76;
    u8 b77;
    u8 pad078[4];
    f32 f7C;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    f32 f90;
    f32 f94;
    u8 pad098[4];
    f32 f9C;
    u8 pad0A0[8];
    s32 iA8;
    u8 pad0AC[0x20];
    u8 bCC;
    u8 bCD;
    u8 bCE;
    u8 bCF;
    u8 pad0D0[2];
    u8 bD2;
    u8 bD3;
    u8 pad0D4[0x1C];
    s32 iF0;
    f32 fF4;
    u8 pad0F8[0x18];
    Quad v110;
    f32 f120;
    u8 pad124[0x1C];
    L17Timer t140;
    u8 pad170[0x30];
    u8 *target;
    u8 pad1A4[0x16C];
    u8 *p310;
    u8 pad314[0x1C];
    f32 f330;
    u8 pad334[0xC];
    f32 f340;
    u8 pad344[0x8C];
    union { Quad q; f32 f[4]; } v3D0;
    u8 pad3E0[0x20];
    s16 h400;
    u8 pad402[2];
    s16 h404;
    u8 pad406[2];
    u8 *p408;
    f32 f40C;
    u8 pad410[8];
    s32 i418;
    s32 i41C;
    s32 i420;
    s32 i424;
    s32 i428;
    u8 pad42C[4];
    f32 f430;
    u8 pad434[0x1C];
    s32 i450;
} L17Vars;

extern float g_grulch_frame_scalar __attribute__((sda));
extern u8 g_grulch_init_bytes[4] __attribute__((sda));
extern u8 g_tether_origin_pos[];
extern char g_str_returned_null[]; /* "returned null\n" */
extern u8 *g_hero_moby NOT_SDA;
extern float coll_probe_ground_height_below(void *, int, float);
extern void MoveCtl_Init(void *);
extern int math_random_int_range(int, int);
extern void hero_copy_field_to_moby(void *);
extern void anim_start_blended(void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern void moby_l17_set_group_alert_flag(void *);
extern int weapon_select_aim_target(void *, int, int, int, float, float);
extern void STUB_printf(void *, ...);


/* The player block at D_00189E20, as far as the two updates below use it. */
typedef struct {
    u8 pad000[0x80];
    f32 pos[4];                 /* 0x80: the point IsPointInCuboid tests */
    u8 pad090[0x162];
    u16 status;                 /* 0x1F2 */
    u8 pad1F4[0x148];
    u8 *target;                 /* 0x33C: compared with the updating object */
    u8 pad340[0xE];
    s16 state;                  /* 0x34E */
    u8 pad350[0x268];
    f32 speed;                  /* 0x5B8 */
    u8 pad5BC[0x1CD8];
    s32 mode;                   /* 0x2294 */
} L17Player;
extern L17Player g_hero_state;

/* The level's save record: one collected flag per object id from 0x464. */
typedef struct { u8 pad[0x464]; u8 collected[0]; } L17SaveState;
extern L17SaveState g_level_l17_save_state;

/* The current level, read with the lw macro: absolute in ordinary flow, $gp in a
   delay slot. */
extern s32 g_current_map_index MACRO_ADDR;
/* Per-level save nibbles, 0x400 bytes a level, two object ids a byte. */
extern u8 g_moby_nibble_table[];
/* Per-level object flags, 16 bytes a level. */
extern u8 g_moby_group_flags[];

/* Paths: a count, then 16-byte points from 0x10. */
extern u8 *g_path_l17_table[];

extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_random_angle(void);
extern s32 flag_set_first_pending(void *);
extern s32 IsPointInCuboid(void *, s32);
extern int ForceClaimNotice(s32, s32, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void moby_set_flag_bit(void *, s32);
extern void cam_lock_entry(s32);
extern s32 hero_l13_set_move_state_pal(s32, s32);

/* func_PAL_L17_00424368's state record. */
typedef struct {
    s32 group;                  /* 0x0: handed to func_L00_00429020 once, then -1 */
    f32 phase;                  /* 0x4: colour pulse angle */
    s32 cuboid;                 /* 0x8: IsPointInCuboid index, negative for none */
    s32 linked;                 /* 0xC: 0x100-byte record at D_L17_001B2C1C, -1 for none */
    f32 speed;                  /* 0x10: given to the player block when nonzero */
} L17PadVars;

/* Pulses the object's colour. While the player block's target is this object it shows
   the lit colour and sets the player's status and speed; the first time (group set, id
   not collected, save nibble still zero) it also hands its group to func_L00_00429020,
   counts the id in its save nibble and passes the linked record to func_L00_003294F0.
   With the player inside its cuboid in mode 0x82 it calls func_PAL_L13_002CF0A0(6, 1). */
void target_pad_update_pal(u8 *obj)
{
    L17PadVars *vars = *(L17PadVars **)(obj + 0x68);
    s32 shade, nibble;
    u16 id;
    u8 *counter;

    vars->phase = FastAddRotations(vars->phase, 0.12566373f);
    shade = FloatToInt(math_fast_sin_or_cos_b(vars->phase) * 128.0f);
    if (shade > 128)
        shade = 128;
    else if (shade < 32)
        shade = 32;
    switch (obj[0x20]) {
    case 0:
        if (flag_set_first_pending(obj))
            *(u16 *)(obj + 0x34) |= 0x10;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        flag_set_first_pending(obj);
        if (g_hero_state.target == obj) {
            if (vars->group != -1) {
                id = *(u16 *)(obj + 0xB2);
                if (!g_level_l17_save_state.collected[(s16)id]) {
                    nibble = g_moby_nibble_table[((s16)id >> 1) + (g_current_map_index << 10)];
                    nibble = ((id & 1) ? nibble >> 4 : nibble) & 7;
                    if (!nibble) {
                        u16 slot;

                        cam_lock_entry(vars->group);
                        slot = *(u16 *)(obj + 0xB2);
                        if (slot & 1) {
                            counter = g_moby_nibble_table + (((s16)slot >> 1) + (g_current_map_index << 10));
                            if (((*counter >> 4) & 7) != 7)
                                *counter += 16;
                        } else {
                            counter = g_moby_nibble_table + (((s16)slot >> 1) + (g_current_map_index << 10));
                            if ((*counter & 7) != 7)
                                *counter += 1;
                        }
                        if (vars->linked != -1)
                            moby_set_flag_bit(g_moby_l17_pool + (vars->linked << 8), 1);
                        vars->group = -1;
                    }
                }
            }
            ForceClaimNotice(12, 0x1349, 1);
            *(s32 *)(obj + 0x78) = (0x80 << 24) | (shade << 8);
            g_hero_state.status = 2;
            if (vars->speed != 0)
                g_hero_state.speed = vars->speed;
        } else
            *(s32 *)(obj + 0x78) = (0x80 << 24) | shade;
        break;
    }
    if (vars->cuboid >= 0 && IsPointInCuboid(g_hero_state.pos, vars->cuboid)
        && g_hero_state.mode == 0x82)
        hero_l13_set_move_state_pal(6, 1);
}

/* func_L17_00420E08's state record. */
typedef struct {
    s32 path;                   /* 0x0: index into D_L17_001FE880, -1 for none */
    f32 marker;                 /* 0x4: point w values equal to it are cleared */
    s32 trigger;                /* 0x8: nonzero activates the object as well */
    f32 phase;                  /* 0xC: colour pulse angle */
} L17SwitchVars;

/* A path seen from its i-th point, i * 16 bytes in: the points follow a 16-byte header. */
typedef struct { u8 header[0x10]; f32 x, y, z, w; } L17PathPoint;