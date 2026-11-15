#include "common.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

extern int FloatToInt(f32);

extern u8 *part_l17_spawn_fading(f32, s32, s32, s32);

extern f32 D_L17_001B04B8 __attribute__((sda));

extern void moby_set_state(void *, s32, s32);

extern void *part_find_owned_effect_slot(void *, s32, s32);

extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);

extern char *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, s32, s32);

extern void moby_mark_spawned(void *);

extern s32 D_L17_001B1E00 __attribute__((sda));

extern s32 D_L17_001B1DE0 __attribute__((sda));

extern s32 D_L17_001B1DD8 __attribute__((sda));

extern s32 D_L17_001B1DD0 __attribute__((sda));

/* Counts the record's own timer down once, then hands the sub-object's four packed
   colour bytes and the measured scale to the level's own setter. */
/* Every so often creates a small light effect with its own colour and size, then waits and
   does it again (moby class 2477). */
void effect_l17_spawner_update(s32 moby)
{
    s32 moby_addr = moby;
    u32 *vars = *(u32 **)(moby_addr + 0x68);
    u32 packed;
    s32 frames;
    f32 scale;

    if (*(u8 *)(moby_addr + 0x20) == 0) {
        u8 one = 1;

        *(u8 *)(moby_addr + 0x30) = 0xFF;
        *(u16 *)(moby_addr + 0x96) = one;
        *(u8 *)(moby_addr + 0x20) = one;
    }
    {
        s32 remaining = (s32)*(u16 *)(moby_addr + 0x96) - 1;

        *(u16 *)(moby_addr + 0x96) = remaining;
        if ((u16)remaining != 0)
            return;
    }
    packed = vars[3] << 24;
    packed |= vars[2] << 16;
    packed |= vars[1] << 8;
    packed |= vars[0];
    scale = *(f32 *)&vars[4] * 210000.0f;
    frames = FloatToInt(D_L17_001B04B8 * 60.0f);
    if (part_l17_spawn_fading(scale, moby_addr, packed, frames) != 0)
        *(u16 *)(moby_addr + 0x96) = FloatToInt(D_L17_001B04B8 * 60.0f);
    else
        *(u16 *)(moby_addr + 0x96) = 1;
}

/* Sets the object's stage up: the first stage asks the level's own spawner for a child and
   gives up its handle, the second one only releases the handle. */
/* Waits until something hits it, then bursts into an effect and removes itself. */
void hit_l17_burst_update(s32 moby)
{
    u8 state = *(u8 *)(moby + 0x20);

    switch (state) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010001, 0) != 0) {
            moby_set_state(moby, 2, -1);
            *(u8 *)(moby + 0xA8) = 0xFF;
        }
        break;
    case 2:
        part_explode_object_into_pieces(moby, &D_L17_001B1DE0, &D_L17_001B1DD8, &D_L17_001B1DD0,
                          0xFFFF, 0, D_L17_001B1E00, 0, 0xFFFF, 0xFF, 0);
        SpawnExplosion(moby + 0x10, 0, 12, 10, 10, 10, 0, 0,
                      *(f32 *)(moby + 0x2C) * 10.0f, 20.0f, 1, 0, 0, 0);
        moby_mark_spawned(moby);
        break;
    }
}


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

extern float D_L17_001B0CA8 __attribute__((sda));
extern u8 D_L17_001B0CB8[4] __attribute__((sda));
extern u8 D_L17_001B9BC0[];
extern char D_L17_001B0CC8[]; /* "returned null\n" */
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

/* Sets the state record up on the first update (the tuning block in field order), then
   handles damage and keeps a target, falling back to D_0018C0B0 when the record has none. */
/* Sets up a Smolgian creature the first time it updates (speeds, turn rates, timers),
   then checks for hits and picks the target it will chase. */
void grulch_init_state_check_hits(u8 *obj)
{
    L17Vars *vars = *(L17Vars **)(obj + 0x68);
    u8 *hit;
    u8 *target;
    int result;

    obj[0x23] = 128;
    if (obj[0x20] == 0) {
        float ground = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
        float radius = F(*(u8 **)(obj + 0x24), 0x24);

        F(obj, 0x18) = ground;
        F(obj, 0x2C) = radius;
        qzero_nc(obj + 0xF0);
        if (vars->i428 != -1) {
            F(obj, 0x18) = F((u8 *)g_moby_l17_pool + vars->i428 * 256, 0x18) + 1.4f;
            H(obj, 0x34) |= 0x41;
            I(obj, 0x98) = 0;
        }
        vars->i420 = 0;
        vars->i424 = 0;
        vars->b48 = FloatToInt(15.0f);
        vars->b4A = FloatToInt(4.0f);
        vars->b29 = 1;
        vars->b70 = 7;
        vars->iA8 = 3;
        vars->b71 = 9;
        vars->b76 = 12;
        vars->b77 = 15;
        vars->f7C = 0.4166667f;
        vars->f80 = 0.050000004f;
        vars->f84 = 0.0030555557f;
        vars->f88 = 0.0055555557f;
        vars->f8C = 0.00055555557f;
        vars->f90 = 0.35f;
        vars->f94 = 0.35f;
        vars->f9C = 0.4f;
        vars->bCC = 6;
        vars->bCD = 11;
        vars->bCE = 6;
        vars->bCF = 11;
        vars->bD2 = 6;
        vars->bD3 = 11;
        MoveCtl_Init(&vars->t140);
        vars->t140.f0C = 2.5f;
        vars->t140.f08 = 2.0f;
        vars->t140.i00 = FloatToInt(D_L17_001B0CA8 * 1024.0f);
        vars->t140.f04 = D_L17_001B0CA8;
        vars->t140.f24 = vars->f40C * (1.0f / 60.0f);
        if (vars->v3D0.f[3] != 12439.4f) {
            vars->v3D0.q = *(Quad *)(obj + 0x10);
            vars->v3D0.f[3] = 12439.4f;
        }
        qcopy_nc(&vars->v110, &vars->v3D0);
        vars->f120 = 0.5f;
        vars->h400 = math_random_int_range(120, 700);
        vars->i41C = 0;
        hero_copy_field_to_moby(obj);
        vars->f340 = F(obj, 0x2C);
        vars->f330 = vars->f30;
        vars->b28 = 0;
        vars->i418 = 0;
        vars->p310 = D_L17_001B0CB8;
        vars->f430 = (float)vars->b34;
        moby_set_state(obj, 1, 0);
        if (obj[0x43])
            anim_start_blended(obj, 0, 0, 0);
        vars->i450 = vars->i428;
    }
    if (obj[0x31] && fast_vec_dist(obj + 0x10, D_L17_001B9BC0) < 24.0f) {
        moby_update_ground_check(obj);
        obj[0x6F] = 22;
    }
    hit = (u8 *)part_find_owned_effect_slot(obj, 0x230000, 0);
    if (hit && hit[0x28] == 8) {
        obj[0x20] = 9;
        obj[0xBC] = 4;
    }
    result = moby_apply_damage_to_object(obj, vars->ai, 0);
    if (result) {
        if (result == 5) {
            vars->iF0 = 0;
            vars->fF4 = 0.8377582f;
        }
        moby_l17_set_group_alert_flag(obj);
    }
    vars->h404 = weapon_select_aim_target(obj, -1, 0, 0, 15.0f, 3.0f);
    target = vars->target;
    if (!target) {
        STUB_printf(D_L17_001B0CC8);
        target = g_hero_moby;
    }
    vars->p408 = target;
}


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
extern L17SaveState D_L17_0021EBB0;

/* The current level, read with the lw macro: absolute in ordinary flow, $gp in a
   delay slot. */
extern s32 g_current_map_index MACRO_ADDR;
/* Per-level save nibbles, 0x400 bytes a level, two object ids a byte. */
extern u8 D_0019B4A8[];
/* Per-level object flags, 16 bytes a level. */
extern u8 D_0019B2E8[];

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
extern s32 hero_change_action(s32, s32);

/* func_L17_0041EAA8's state record. */
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
   With the player inside its cuboid in mode 0x82 it calls func_L13_002CEF00(6, 1). */
/* A glowing pad that pulses its colour and reacts when the player targets it. */
void target_pad_update(u8 *obj)
{
    L17PadVars *pad_vars = *(L17PadVars **)(obj + 0x68);
    s32 shade, nibble;
    u16 id;
    u8 *counter;

    pad_vars->phase = FastAddRotations(pad_vars->phase, 0.10471977f);
    shade = FloatToInt(math_fast_sin_or_cos_b(pad_vars->phase) * 128.0f);
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
            if (pad_vars->group != -1) {
                id = *(u16 *)(obj + 0xB2);
                if (!D_L17_0021EBB0.collected[(s16)id]) {
                    nibble = D_0019B4A8[((s16)id >> 1) + (g_current_map_index << 10)];
                    nibble = ((id & 1) ? nibble >> 4 : nibble) & 7;
                    if (!nibble) {
                        u16 slot;

                        cam_lock_entry(pad_vars->group);
                        slot = *(u16 *)(obj + 0xB2);
                        if (slot & 1) {
                            counter = D_0019B4A8 + (((s16)slot >> 1) + (g_current_map_index << 10));
                            if (((*counter >> 4) & 7) != 7)
                                *counter += 16;
                        } else {
                            counter = D_0019B4A8 + (((s16)slot >> 1) + (g_current_map_index << 10));
                            if ((*counter & 7) != 7)
                                *counter += 1;
                        }
                        if (pad_vars->linked != -1)
                            moby_set_flag_bit(g_moby_l17_pool + (pad_vars->linked << 8), 1);
                        pad_vars->group = -1;
                    }
                }
            }
            ForceClaimNotice(12, 0x27F7, 1);
            *(s32 *)(obj + 0x78) = (0x80 << 24) | (shade << 8);
            g_hero_state.status = 2;
            if (pad_vars->speed != 0)
                g_hero_state.speed = pad_vars->speed;
        } else
            *(s32 *)(obj + 0x78) = (0x80 << 24) | shade;
        break;
    }
    if (pad_vars->cuboid >= 0 && IsPointInCuboid(g_hero_state.pos, pad_vars->cuboid)
        && g_hero_state.mode == 0x82)
        hero_change_action(6, 1);
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

/* Starts at a random phase and goes straight to the active state when its level flag
   (D_0019B2E8, bit 0x80) is set; otherwise it pulses its grey until the player block
   targets it in state 0 or, with the trigger set, the flag becomes set. Activating sets
   the lit colour, plays sound 0 (from state 1 only) and clears the w of every point of
   its path that equals the marker. */
/* A glowing switch that pulses until the player targets it, then lights up and opens
   its path. */
void switch_l17_update(u8 *obj)
{
    L17SwitchVars *vars = *(L17SwitchVars **)(obj + 0x68);
    s32 shade;

    switch (obj[0x20]) {
    case 0: {
        s32 level;

        vars->phase = math_random_angle();
        level = g_current_map_index;
        *(f32 *)(obj + 0x18) -= 0.35f;
        if (D_0019B2E8[obj[0xB0] + level * 16] & 0x80) {
            obj[0xBC] = 2;
            *(u32 *)(obj + 0x78) = 0x80208020;
            obj[0x20] = 2;
            if (vars->path != -1) {
                s32 i;

                for (i = 0; i < *(s32 *)g_path_l17_table[vars->path]; i++) {
                    if (((L17PathPoint *)(g_path_l17_table[vars->path] + (i << 4)))->w == vars->marker)
                        ((L17PathPoint *)(g_path_l17_table[vars->path] + (i << 4)))->w = 0;
                }
            }
        } else
            obj[0x20] = 1;
        break;
    }
    case 1:
        vars->phase = FastAddRotations(vars->phase, 0.10471977f);
        shade = FloatToInt((math_fast_sin_or_cos_b(vars->phase) * 4.0f - 3.0f) * 128.0f);
        if (shade > 128)
            shade = 128;
        else if (shade < 32)
            shade = 32;
        {
            u32 green = (shade << 8) | (0x80 << 24);

            *(u32 *)(obj + 0x78) = ((shade << 16) | green) | shade;
        }
        if ((g_hero_state.target == obj && !g_hero_state.state)
            || (vars->trigger && (D_0019B2E8[obj[0xB0] + g_current_map_index * 16] & 0x80))) {
            obj[0x20] = 2;
            obj[0xBC] = 1;
            *(u32 *)(obj + 0x78) = 0x80208020;
            PlayMobySound(0, 0, obj);
            if (vars->path != -1) {
                s32 i;

                for (i = 0; i < *(s32 *)g_path_l17_table[vars->path]; i++) {
                    if (((L17PathPoint *)(g_path_l17_table[vars->path] + (i << 4)))->w == vars->marker)
                        ((L17PathPoint *)(g_path_l17_table[vars->path] + (i << 4)))->w = 0;
                }
            }
        }
        break;
    }
}
