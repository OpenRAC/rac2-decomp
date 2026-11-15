#include "include_asm.h"
#include "common.h"

extern unsigned char D_00139574;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_spawn_spark_puff(void *);
extern void part_l00_spawn_impact_burst(void *, void *, void *);


typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L02_001AC850 __attribute__((sda));
extern int D_L02_001B3D30 __attribute__((sda)), D_L02_001B3D38 __attribute__((sda));
extern Collision D_L02_001C0940;
extern Material D_L02_00264A70[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void part_emit_sparkle(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern void vec_clear_128(void *);
extern char *moby_spawn_scaled_effect(void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void part_spawn_spark_2(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);

extern void FastVecAdd(char *, char *, char *);

extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);

extern void moby_set_state(void *, int, int);

extern void anim_start_blended(void *, int, int, int);

extern int FastDecTimer(short *);

extern int ComputeRegionRouteHeading(char *, int, float *, char *, short, char *, char *, float, float);

extern int moby_step_controller(char *, int, float);

extern void moby_copy_joint_transform_to_object(char *, char *, int, int);

extern void value_set_and_smooth(char *, char *, float, int, int);

extern int coll_sweep_from_object(char *, void *, int, float, float, float, int, int, int);

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    int x, y, z, w;
} V16;

extern void func_31E6A0(char *, int, int);

extern void func_31E3C0(char *, int, int, int);

extern void func_31E2E8(char *, int, int);

extern void func_315578(char *, int, void *);

extern void func_2F2A78(void *, void *);

extern void func_2EF388(char *, char *, char *, char *, int);

extern void armed_enemy_release_held_object(char *, TI128 *);

extern void enemy_release_effect_record(char *);

extern void func_3FC1B0(char *, int);

extern void func_315348(char *, char *);

extern void func_2F1CC8(char *, int, int);

extern void func_316220(char *);

extern void func_3152D0(char *, int, char *);

extern void func_31EA58(char *, float, float);

extern void func_32B068(char *, int, char *, int, float, float, float, float);

extern void func_3FC248(char *, int, int);

extern void func_40D7B8(char *, int, void *);

extern int armed_enemy_has_partner_in_group(char *);

extern float func_2F2168(char *, char *, float);

extern float func_2F2648(float, float);

extern float func_2F30E8(float, float);

extern int func_31E770(int);

extern void func_332710(float, float, float, float);

extern void func_316150(char *, int, int, int);

extern void func_316180(char *, int *, int *, int *);

extern float moby_get_anim_value(char *);

extern void moby_transform_joint_to_world(char *, int, void *);

extern void coll_project_point_on_segment(void *, void *, void *, void *);

extern void FastVecSub(void *, void *, void *);

extern float FastVecLength(void *);

extern int PlayMobySound(int, int, char *);

/* Stores the quadword the caller passes into the record at +0xF0. */
/* func_L02_003CADA8 is a near miss: nonmatching/levels/func_L02_003CADA8.c */
/* func_L02_003CADA8 is matched in L02_003CADA8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Stores the quadword the caller passes into the record at +0xB0. */
/* func_L02_003D01F0 is a near miss: nonmatching/levels/func_L02_003D01F0.c */
/* func_L02_003D01F0 is matched in L02_003D01F0.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* Callers also supply a candidate pointer; this predicate only inspects arg0. */
/* Tells whether the enemy is holding its extra object and is in one of its attack states. */
int armed_enemy_is_holding_in_attack(char *self, void *candidate) {
    int result = 0;
    if (*(int *)(*(char **)(self + 0x68) + 0x2E4) != 0) {
        unsigned char state_byte = *(unsigned char *)(self + 0x20);
        if (state_byte == 0x13 || state_byte == 4 || *(unsigned char *)(self + 0x95) == 4 ||
            state_byte == 0x10 || state_byte == 0x11 || state_byte == 0x12)
            result = 1;
    }
    return result;
}

/* Walks the enemy along its path toward a point and turns it to face the way it is going. Returns the path result. */
int enemy_follow_path_toward_point(char *self, int target_point) {
    float turn_angle;
    char *state = *(char **)(self + 0x68);
    int result = ComputeRegionRouteHeading(self + 0x10, target_point, &turn_angle, state + 0x290, *(short *)(state + 0x3B6),
                              state + 0x3B8, state + 0x3BC, 0.0f, *(float *)(state + 0x50));
    moby_step_controller(self, target_point, turn_angle);
    return result;
}

/* Sends the enemy back to its idle pose, with or without its held object. */
void armed_enemy_return_to_idle(char *self) {
    char *state = *(char **)(self + 0x68);
    if (*(int *)(state + 0x2E4) != 0) {
        moby_set_state(self, 4, 2);
        if (*(unsigned char *)(self + 0x43) != 0)
            anim_start_blended(self, 0, 0, 0xA);
    } else {
        moby_set_state(self, 5, 2);
        if (*(unsigned char *)(self + 0x43) != 1)
            anim_start_blended(self, 1, 0, 0xA);
    }
}

/* End-of-frame upkeep for the enemy: counts timers, moves the held object and checks for hits. */
void armed_enemy_finish_frame(char *self) {
    char *state = *(char **)(self + 0x68);
    FastDecTimer((short *)(state + 0x2F4));
    if (*(unsigned short *)(self + 0x96) < 0xFFFF)
        (*(unsigned short *)(self + 0x96))++;
    if (*(int *)(state + 0x2E4) != 0) {
        moby_copy_joint_transform_to_object(self, *(char **)(state + 0x2E4), 2, 0);
        *(unsigned short *)(*(char **)(state + 0x2E4) + 0x34) &= 0xFFFD;
    }
    value_set_and_smooth(self, state + 0x210, 3.5f, 4, 1);
    coll_sweep_from_object(self, self + 0x10, 0x4000000, 1.5f, 1.0f, 1.0f, 0, 1, 0);
}

extern void *CreateMoby(int);

extern void func_002A0F48(char *);

/* Creates the extra object (moby class 2520) the enemy carries and copies the enemy's settings to it. */
void armed_enemy_spawn_held_object(char *self) {
    char *state = *(char **)(self + 0x68);
    *(char **)(state + 0x2E4) = CreateMoby(0x9D8 /* moby class 2520 */);
    if (*(char **)(state + 0x2E4) != 0) {
        *(unsigned char *)(*(char **)(state + 0x2E4) + 0x30) = *(unsigned char *)(self + 0x30);
        *(unsigned short *)(*(char **)(state + 0x2E4) + 0x32) = *(unsigned short *)(self + 0x32);
        *(unsigned char *)(*(char **)(state + 0x2E4) + 0x31) = 1;
        *(unsigned long long *)(*(char **)(state + 0x2E4) + 0x38) =
            *(unsigned long long *)(self + 0x38);
        func_002A0F48(*(char **)(state + 0x2E4));
        *(int *)(*(char **)(state + 0x2E4) + 0x98) = 0;
        *(int *)(*(char **)(*(char **)(state + 0x2E4) + 0x68) + 0x3C) = 1;
    }
}

typedef struct {
    float x, y, z, w;
    float pad[4];
} L02_Record20;

typedef struct {
    float x, y, z, w;
    float pad[12];
} L02_Record40;

/* sda in this -G0 unit gives retail's macro load (`lui $r,%hi ; lw $r,%lo($r)`, one register); a plain
   declaration splits it into two registers and interleaves the loads. */
extern L02_Record20 *D_L02_001B3C14 __attribute__((sda));

extern L02_Record20 *D_L02_001B3C18 __attribute__((sda));

extern L02_Record40 *D_L02_001B3BD0 __attribute__((sda));

extern int D_L02_001B3BD4 __attribute__((sda));

/* Walks the two record tables and shifts each record's x by one period (2000, and 2048000 for the
   second table, whose limit is scaled by 1024): down while x > 0 for the records on the flagged side
   of the limit (z below it when flag is set), up while x < 0 for the others. */
/* Shifts the sky and track records sideways by one full period so they wrap around, depending on which side of the limit they are on. */
void sky_shift_records_by_period(int flag, float limit) {
    L02_Record20 *record;
    int i;

    for (record = D_L02_001B3C14; record != D_L02_001B3C18; record++) {
        int flagged = record->z < limit ? flag : !flag;

        if (flagged) {
            if (record->x > 0.0f)
                record->x -= 2000.0f;
        } else {
            if (record->x < 0.0f)
                record->x += 2000.0f;
        }
    }
    limit *= 1024.0f;
    for (i = 0; i < D_L02_001B3BD4; i++) {
        L02_Record40 *wide_record = &D_L02_001B3BD0[i];
        int flagged = wide_record->z < limit ? flag : !flag;

        if (flagged) {
            if (wide_record->x > 0.0f)
                wide_record->x -= 2048000.0f;
        } else {
            if (wide_record->x < 0.0f)
                wide_record->x += 2048000.0f;
        }
    }
}

/* Multiplies two 3x3 rotation matrices and keeps the fourth column of the result unchanged. */
ASM_FUNC("asm/levels", func_L02_002F2B88);

/* func_L02_003007D8 is matched in L02_003007D8-g8.c (built with -G8 and -g). */

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} L02_Mob;

typedef struct {
    u8 pad00[0x30];
    s32 mode;
    u8 pad34[0x44 - 0x34];
    s16 count;
    u8 pad46[0x18C - 0x46];
    L02_Mob *mobs[1];
} L02_MobList;

extern L02_MobList D_L02_001BE200;

/* sda in this -G0 unit gives the bare-symbol load: retail has it as `lui`/`lw` after the loop and,
   as the filler of the first branch's delay slot, as the one-instruction `$gp` form gas makes of
   it there. */
extern int g_current_map_index __attribute__((sda));

extern void anim_start_startup_animations(void);

extern void UpdateEquipmentPieces(void *);

extern void math_store_angle_update_result(void *, void *, int, int, float);

extern void gfx_add_draw_callback_first(void *, void *);

extern void cutscene_draw_intro_overlays(void *);

/* Walks the level's list of mobs (the same walk as func_L04_0031D630): the ones of type 0xE29 get
   the 0x800 flag, the ones of type 0xD54 are handed to func_002E64A0 and the ones of type 0xFA0
   that hold a 0x68 pointer give that pointer's block (from +0xC) to func_L00_00326048; the 0xD54
   test reads the type without the null check, as retail does. When the game state is 2 and the
   list's word at +0x30 is 2 as well, it then queues func_L02_003007D8. */
/* Goes through every moby in the level and flags, updates or sets up the special ones, then queues the intro overlay. */
void level_update_moby_list_effects(void) {
    int i;

    anim_start_startup_animations();
    for (i = 0; i < D_L02_001BE200.count; i++) {
        L02_Mob *mob = D_L02_001BE200.mobs[i];

        if (mob != 0 && mob->type == 0xE29 /* moby class 3625 */)
            mob->flags |= 0x800;
        if (mob->type == 0xD54 /* moby class 3412 */)
            UpdateEquipmentPieces(mob);
        if (mob != 0 && mob->type == 0xFA0 /* moby class 4000 */ && mob->p68 != 0)
            math_store_angle_update_result(mob, (u8 *)mob->p68 + 0xC, 0x80AAAAD2, 0x80396464, 0.0610865355f);
    }
    if (g_current_map_index == 2 && D_L02_001BE200.mode == 2)
        gfx_add_draw_callback_first(cutscene_draw_intro_overlays, 0);
}

/* func_L02_0033C760 is matched in L02_0033C760.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_0033C8B8 is matched in L02_0033C8B8-g.c (built with -g). */



/* func_L02_00363D78 is defined in L02_00363D78.c. */

/* Projects the sky effects to the screen and submits them for drawing. */
ASM_FUNC("asm/levels", func_L02_00364A18);

ASM_FUNC("asm/levels", func_L02_00364D3C);

/* Moves a flying piece of debris, makes sparks where it hits a wall and then breaks it up. */
void debris_update_with_sparks(unsigned char *moby) {
    struct {
        Vec old, velocity, normal;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
        Vec position, spread;
    } frame;
    char *vars = *(char **)(moby + 0x68), *position = (char *)moby + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, vars, position);
    part_steer_effect_direction(*(int *)(vars + 0x1C), vars, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(vars, vars);
    vec_add_object_direction_scaled(position, vars, 0.0030555557f);
    part_emit_sparkle(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)D_L02_00264A70 + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(vars + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(D_L02_001B3D30, D_L02_001B3D38, 1,
                *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(moby + 0x10);
            frame.position.f[1] = *(float *)(moby + 0x14);
            frame.position.f[2] = D_L02_001C0940.point.f[2];
            effect = moby_spawn_scaled_effect(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = math_random_angle();
                speed = math_random_float_range(0.0f, 0.050000004f);
                frame.spread.f[0] = math_fast_sin_or_cos_a(angle) * speed;
                frame.spread.f[1] = math_fast_sin_or_cos_b(angle) * speed;
                frame.spread.f[2] = math_random_float_range(0.050000004f, 0.10833334f);
                lifetime = math_random_int_range(90, 120);
                part_spawn_spark_2(&frame.position, spread, math_random_int_below(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &D_L02_001C0940;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == 0xC0 /* moby class 192 */) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = &D_L02_001C0940;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L02_001AC850 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, vars, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, vars, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (moby[0xBC]) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        part_spawn_big_explosion(moby, &frame.velocity, &frame.normal);
    }
}



/* Moves a flying piece of debris and breaks it up when it hits something or has bounced too often. */
void debris_l02_update(char *moby) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *vars = *(char **)(moby + 0x68);
    char *position = moby + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, vars);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    part_spawn_spark_puff(moby);
    frame.packet.moby = moby;
    frame.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L02_00264A70)->material;
    qcopy(&frame.packet.vector, vars);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(moby + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, moby, &frame.packet)) {
        collision = &D_L02_001C0940;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == 0xC0 /* moby class 192 */) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = &D_L02_001C0940;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L02_001AC850 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            moby[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = moby + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, vars, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L02_001C0940;
            if (collision->count <= 0)
                goto finish;
            moby[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, vars, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, vars);
    }
finish:
    if (*(unsigned char *)(moby + 0xBC)) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 20)
            part_spawn_big_explosion(moby, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst(moby, &frame.velocity, &frame.normal);
    }
}



/* func_L02_003CA4A8 is defined in L02_003CA4A8-g8.c. */

/* func_L02_003CAE68 is matched in L02_003CAE68.c (built with -frac2-qcopy). */

/* func_L02_003CB090 is matched in L02_003CB090.c (built with -mno-split-addresses). */


extern u16 *g_entity_group_lists[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *g_moby_l02_pool[] __attribute__((sda));
extern int D_L02_001B35B8[] __attribute__((sda));

/* Returns the first entity of the group's id list whose state byte is 0x17, or 0. */
u8 *group_find_entity_in_state(int group) {
    u16 *entry;
    u8 *entity;

    for (entry = g_entity_group_lists[group];
         (u8)group != 0xFF && group <= D_L02_001B35B8[0] && entry != 0 &&
         ((s16)entry[-1] >= 0 || entry == g_entity_group_lists[group]);
         entry++) {
        entity = g_moby_l02_pool[0] + ((*entry & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x20] == 0x17)
            return entity;
    }
    return 0;
}

/* Resets the actor's aim record and hands its descriptor to the object system. */
/* func_L02_003CD668 is defined in L02_003CD668.c. */



/* func_L02_003D0408 is defined in L02_003D0408-g8.c. */

extern int FloatToInt(float);

extern float math_random_float_range(float, float);

extern float fast_vec_dist(void *, void *);

extern void moby_update_ground_check(char *);

extern void *part_find_owned_effect_slot(char *, int, int);

extern void moby_apply_damage_to_object(char *, char *, int);

extern void part_spawn_dust_pairs(char *, int);

extern void armed_enemy_drop_held_and_reset(char *, int, int);

extern void armed_enemy_find_partner(char *);

extern char g_camera_l02_position;

extern int math_random_int_below(int);


extern float vec_distance_xy(char *, char *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern int math_random_int_below(int);

/* Picks the idle variant the actor should play, from its distance and heading. */
/* Starts a close-range attack when the target is near and in front. Returns 1 if an attack began. */
int armed_enemy_try_close_attack(char *object) {
    char *state = *(char **)(object + 0x68);
    float dist;
    float ang;

    if (armed_enemy_has_partner_in_group(object) != 0)
        return 0;
    dist = 100.0f;
    ang = 1.0f;
    if (*(char **)(state + 0x2E0) != 0) {
        dist = vec_distance_xy(object + 0x10, *(char **)(state + 0x2E0) + 0x10);
        ang = mat_fast_helper_a(*(float *)(*(char **)(state + 0x2E0) + 0x10) - *(float *)(object + 0x10),
                            *(float *)(*(char **)(state + 0x2E0) + 0x14) - *(float *)(object + 0x14));
    }
    if (dist < 4.0f) {
        if (FastDiffRots(ang, *(float *)(object + 0xF8)) < 0.26179942f) {
            if (math_random_int_below(5) == 0) {
                moby_set_state(object, 0xC, 5);
                if (*(u8 *)(object + 0x43) != 7)
                    anim_start_blended(object, 7, 0, 0xA);
            } else if (*(int *)(state + 0x2E4) != 0) {
                moby_set_state(object, 0x12, 6);
                if (*(u8 *)(object + 0x43) != 0xD)
                    anim_start_blended(object, 0xD, 8, 0xF);
            } else {
                moby_set_state(object, 0xF, 6);
                if (*(u8 *)(object + 0x43) != 0xA)
                    anim_start_blended(object, 0xA, 8, 0xF);
            }
            return 1;
        }
    }
    return 0;
}

/* func_L02_003D18D8 is defined in L02_002ED7B0-g8.c (it reaches D_L02_001B359C through $gp). */

/* func_L02_003D1998 is matched in L02_002ED7B0-g8.c (built with -G8: it reads D_L02_001B35B8
   through $gp). */

/* Chooses the variant the actor plays from how far along the path it has come. */
void armed_enemy_update_attack_variant(char *object) {
    float start[4], end[4], closest[4], remaining[4], span[4];
    char *state;
    float time, fraction;

    time = moby_get_anim_value(object);
    state = *(char **)(object + 0x68);
    if (19.0f <= time && time <= 31.0f) {
        moby_transform_joint_to_world(object, 0, start);
        moby_transform_joint_to_world(object, 1, end);
        coll_project_point_on_segment(closest, start, end, *(char **)(state + 0x2E0) + 0x10);
        FastVecSub(remaining, closest, end);
        FastVecSub(span, start, end);
        fraction = FastVecLength(remaining);
        fraction /= FastVecLength(span);
        if (fraction < 0.0f)
            fraction = 0.0f;
        if (fraction > 1.0f)
            fraction = 1.0f;
        if (coll_sweep_from_object(object, closest, 0x10001, fraction * 0.35f + 0.15f,
                          (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0) &&
            *(short *)(state + 0x2F8) == 0) {
            PlayMobySound(5, 0, object);
            *(short *)(state + 0x2F8) = 1;
        }
        coll_sweep_from_object(object, end, 0x10001, 0.5f,
                      (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0);
    }
}

extern void func_002F1F70(void *, void *, void *);

extern void func_0032B468(char *, int, char *, char *, int, int, float *, void *, void *, float);

extern void func_003144D8(char *);

/* `sda` on an array of unknown size: each use is a fresh absolute `lui`/`addiu`, as retail has
   it, where a plain declaration is kept in a saved register across the calls. */
extern char D_L02_001A8F20[] __attribute__((sda));

/* When the actor is drawn and still holds its sub-object, builds a vector from 0.1 and 1/6,
   offsets it by the vector at D_L02_001A8F20 and passes both to func_0032B468 with the
   sub-object's +0x10 and +0xF0 records; then releases the sub-object in every case. The
   caller's quadword is copied to the stack (as retail does) and not read again. */
/* Lets go of the object the enemy holds: spawns a small burst for it and frees it. */
void armed_enemy_release_held_object(char *self, TI128 *pos) {
    char *state = *(char **)(self + 0x68);
    float copy[4];
    float vec[4];

    *(TI128 *)copy = *pos;
    if (*(unsigned char *)(self + 0x31) != 0 && *(char **)(state + 0x2E4) != 0) {
        func_31EA58((char *)vec, 0.10000000894069672f, 0.16666667163372040f);
        func_002F1F70(vec, vec, D_L02_001A8F20);
        func_0032B468(self, 0x9D8, *(char **)(state + 0x2E4) + 0x10, *(char **)(state + 0x2E4) + 0xF0,
                    0, 0, vec, D_L02_001A8F20, D_L02_001A8F20, 0.0027777778450399637f);
    }
    func_003144D8(*(char **)(state + 0x2E4));
    *(char **)(state + 0x2E4) = 0;
}

/* Brings the actor into its armed state and re-registers its sub-object. */
void armed_enemy_setup(char *self, int delay) {
    char *state = *(char **)(self + 0x68);

    *(short *)(state + 0x2F6) = 0;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    func_332710(0.0055555556900799274f, 0.10333333909511566f, 0.0034906589426100254f,
                0.41887909173965454f);
    func_31E6A0(self, 3, 1);
    if (*(unsigned char *)(self + 0x43) != 0)
        func_31E3C0(self, 0, 0, 0xA);
    *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x24) + 0x10);
    *(unsigned char *)(state + 0x6A) = 0;
    *(unsigned char *)(state + 0x2E) = 1;
    *(unsigned char *)(self + 0x7F) = 0;
    *(unsigned char *)(self + 0x31) = 1;
    *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) | 0x1000) & 0xFFB8;
    armed_enemy_spawn_held_object(self);
    *(short *)(state + 0x2FC) = delay;
    *(short *)(state + 0x88) = 0;
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_316150(self, *(unsigned char *)(state + 0x54), *(unsigned char *)(state + 0x55),
                    *(unsigned char *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
    if (*(char **)(state + 0x2E4) != 0) {
        int a, b, c;

        func_316180(self, &a, &b, &c);
        func_316150(*(char **)(state + 0x2E4), a, b, c);
    }
}

extern void mem_clear(char *, int, int);

extern void AttachManipulator(char *, int, char *);

extern void vec_random_direction(char *, float, float);

extern void part_spawn_masked_debris(char *, int, char *, float, float, float, float, int);

extern void moby_set_anim_type_three(char *, int, int);

extern void part_queue_moby_for_glow(char *, int, void *);

/* Re-arms the actor: passes a copy of its sub-object's +0x10 quadword to func_L02_003D1ED0 and,
   while the effect record at +0x290 is not yet set up (byte +0x291 clear), resets and registers
   it, scales it by 0.0001 and starts the effect; then clears the word at +0x98. A clear flag1
   also calls func_L02_003FC248; a clear flag2 hands func_L02_003D2390 to func_L01_003E9CF8,
   otherwise func_L02_003D2390 runs at once. */
/* Puts the enemy down: drops its held object, shrinks its effect and hides it. */
void armed_enemy_drop_held_and_reset(char *self, int flag1, int flag2) {
    char *state = *(char **)(self + 0x68);
    float vec[4];

    if (*(char **)(state + 0x2E4) != 0) {
        *(TI128 *)vec = *(TI128 *)(*(char **)(state + 0x2E4) + 0x10);
        armed_enemy_release_held_object(self, (TI128 *)vec);
    }
    if (*(unsigned char *)(state + 0x291) == 0) {
        mem_clear(state + 0x290, 0, 0x40);
        AttachManipulator(self, 3, state + 0x290);
        *(float *)(state + 0x2B0) = *(float *)(state + 0x2B4) = *(float *)(state + 0x2B8) = 0.0001f;
        *(unsigned char *)(state + 0x292) = 1;
        vec_random_direction((char *)vec, 0.016666668f, 0.050000004f);
        part_spawn_masked_debris(self, 0x20, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(int *)(self + 0x98) = 0;
    if (flag1 == 0)
        moby_set_anim_type_three(self, 0, -1);
    if (flag2 == 0)
        part_queue_moby_for_glow(self, 0, enemy_release_effect_record);
    else
        enemy_release_effect_record(self);
}

extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);

/* Same body as func_L02_003F1A88, with this function's own callees. */
/* Picks a random spot a few steps away from the target point for the enemy to walk to. */
void armed_enemy_pick_point_near_target(char *self, char *target_point) {
    char *state;
    float angle;
    float radius;

    angle = mat_fast_helper_a(*(float *)(self + 0x10) - *(float *)target_point,
                          *(float *)(self + 0x14) - *(float *)(target_point + 4));
    angle += math_random_float_range(-0.78539824f, 0.78539824f);
    radius = math_random_float_range(-2.0f, 2.0f) + 8.0f;
    state = *(char **)(self + 0x68);
    qcopy(state + 0x2D0, target_point);
    *(float *)(state + 0x2D0) += radius * math_fast_sin_or_cos_a(angle);
    *(float *)(state + 0x2D4) += radius * math_fast_sin_or_cos_b(angle);
}
