#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef union {
    TI128 q;
    float f[4];
} L20_0039BB18_V4;

extern float D_L20_001AEC68 __attribute__((sda));

extern int math_fast_float_d(int *);
extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, u8, u8, int, float);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void part_draw_glow_trail(void *);

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
/* Measured level-state prefix; no full allocation size is inferred. */
typedef struct {
    u8 before_mode[0x30];
    int mode, state;
    u8 before_count[0xC];
    s16 count;
    u8 before_objects[0x146];
    union {
        void *objects[0];
        struct {
            u8 before_target[0xC];
            void *target;
            int owner;
            u8 before_alternate[8];
            void *alternate;
            u8 before_secondary_owner[8];
            int secondary_owner;
            void *secondary_target;
        } named;
    } refs;
} YeedilStatePrefix;
extern YeedilStatePrefix D_L20_001BDCC0;
extern u32 g_current_map_index;
typedef struct { u8 before_owner[0x5C0]; int owner; } YeedilHeroPrefix;
extern YeedilHeroPrefix g_hero_state;
extern u8 D_0018A550[];
typedef struct {
    Vector origin, point;
    float unknown20, scale;
} YeedilCameraPrefix;
extern YeedilCameraPrefix D_L20_001C6AE0;
extern u8 D_L20_001BA1F0[];
typedef struct {
    u8 before_effect[0x160];
    float scale1;
    int unknown164, count1, state1;
    u8 before_effect2[0x10];
    float scale2;
    int unknown184, count2;
} YeedilEffectPrefix;
extern YeedilEffectPrefix D_L20_001B9E80;
extern int D_L20_001A9430 __attribute__((sda));
extern int D_L20_001A9434 __attribute__((sda));
extern int D_L20_001A9438 __attribute__((sda));
extern int D_L20_001A943C __attribute__((sda));
extern int D_L20_001A9440 __attribute__((sda));
extern Vector D_L20_001A9420 SDATA(D_L20_001A9420);
extern int D_L20_001AF3B0[] __attribute__((sda));
extern void anim_start_startup_animations(void *);
extern void UpdateEquipmentPieces(void *);
extern void math_store_angle_update_result(char *,float *,s32,s32,float);
extern void mem_clear(void *,int,int);
extern void moby_transform_joint_point(void *,int,void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void copy_matrix3x4(void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void InitializeBoltPointChain(void *);
extern void beam_update_chain_points(void *);
extern void gfx_add_draw_callback_third(void (*)(void *),void *);
extern void beam_draw_ribbons_level(void *);
extern char *part_spawn_blast_effect_moby(void *,void *,void *,float);
extern void EmitScaledObjectParticles(void *);
extern void *SpawnExplosion(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);

/* Updates the glowing particle effect (moby class 4802). It fades the effect in while its owner is close, spawns drifting sparks
 * every frame, and removes itself once it has faded out. */
void UpdateYeedilParticleEmitter(void *moby)
{
    L20_0039BB18_V4 pos;
    L20_0039BB18_V4 vel;
    u32 vars;
    float drift;
    float angle;
    float radius_rand;
    float fade_rand;
    float zero_target;
    u32 frame_count;
    unsigned long long prev_count;
    int lifetime;
    int color_seed;
    float speed_rand;
    float size_rand;
    float size_rand2;

    vars = *(u32 *)((u32)moby + 0x68);
    if (math_fast_float_d((int *)(vars + 4)) != 0)
        goto pathA;
    frame_count = *(u16 *)((u32)moby + 0x96);
    prev_count = frame_count++;
    *(u16 *)((u32)moby + 0x96) = frame_count;
    if (prev_count < 11)
        goto check;
    if (*(u16 *)(*(u32 *)((u32)moby + 0xB8) + 0x34) & 1)
        goto pathA;
check:
    if (vec_distance_xy((void *)((u32)moby + 0x10),
                      (void *)(*(u32 *)((u32)moby + 0xB8) + 0x10)) > 0.1f) {
pathA:
        zero_target = 0.0f;
        ApproachValue((float *)vars, zero_target, 0.016666667f);
        if (*(float *)vars == 0.0f) {
            moby_mark_spawned(moby);
            goto end;
        }
    } else {
        ApproachValue((float *)vars, 1.0f, 0.016666667f);
    }

    drift = D_L20_001AEC68;
    {
        float v = *(float *)(vars + 0xC) + drift * 0.016666667f;
        *(float *)(vars + 0xC) = v;
        if (v > 1.0f) {
            *(float *)(vars + 0xC) = v - 1.0f;
        } else if (v < -1.0f) {
            *(float *)(vars + 0xC) = v + 1.0f;
        } else {
            goto skip;
        }
    }
skip:
    fade_rand = math_random_float_range(0.1f, 0.3f);
    lifetime = math_random_int_range(30, 60);
    vel.q = 0;
    speed_rand = math_random_float_range(0.5f, 2.0f);
    vel.f[2] = -speed_rand * 0.016666667f;
    pos.q = vel.q;
    radius_rand = math_random_float_range(0.0f, 1.0f);
    angle = math_random_angle();
    vel.f[0] = math_fast_sin_or_cos_a(angle) * radius_rand;
    vel.f[1] = math_fast_sin_or_cos_b(angle) * radius_rand;
    vel.f[2] = 0.0f;
    size_rand = math_random_float_range(1.0f, 10.0f);
    vel.f[2] = size_rand;
    size_rand2 = math_random_float_range(1.0f, 10.0f);
    if (!(vel.f[2] > size_rand2)) {
        ;
    } else {
        vel.f[2] = size_rand2;
    }
    FastVecAdd(&vel, &vel, moby + 0x10);
    {
        u8 particle_count = lifetime;
        color_seed = math_random_int_below(255);
        part_spawn_hero_relative(&vel, &pos, 0x60107080, particle_count, color_seed & 0xFF, 0, fade_rand);
    }
    gfx_add_draw_callback_first(part_draw_glow_trail, moby);
end:
    return;
}


/* Runs the Yeedil level script each frame. It tweaks some objects in the level and moves the camera for the cutscene steps. */
void level_script_update(void *incoming)
{
    int lower, upper;
    void *target;
    /* 29FC20 uses the fourth row at output+0x30; 83678 copies only
    * the first three rows. The same workspace later holds one vector. */
    Vector matrix[4], work, offset;
    float value;

    anim_start_startup_animations(incoming);
    {
        int i;
        for (i = 0; i < D_L20_001BDCC0.count; ++i) {
            u8 *object;
            object = D_L20_001BDCC0.refs.objects[i];
            if (object && *(s16 *)(object+0xAA) == 0xE29 /* moby class 3625 */)
                *(u16 *)(object+0x34) |= 0x800;
            if (*(s16 *)(object+0xAA) == 0xD54 /* moby class 3412 */)
                UpdateEquipmentPieces(object);
            if (object && *(s16 *)(object+0xAA) == MOBY_CLASS_TV_SCREENS && *(void **)(object+0x68))
                math_store_angle_update_result((char *)object,(float *)(*(u8 **)(object+0x68)+0xC),
                                  0x80AAAAD2,0x80396464,0.06108653545f);

        }
    }
    if (g_current_map_index != 20) return;
    {
        if ((u32)(D_L20_001BDCC0.mode-4) < 2) {
            {
                YeedilHeroPrefix *hero = &g_hero_state;
                int owner = D_L20_001BDCC0.refs.named.owner;
                hero->owner = owner;
                if (D_L20_001BDCC0.mode == 4) {
                    hero->owner = D_L20_001BDCC0.refs.named.secondary_owner;
                    target = D_L20_001BDCC0.refs.named.secondary_target;
                    lower = D_L20_001A9434;
                    upper = D_L20_001A9438;
                } else {
                    lower = D_L20_001A943C;
                    /* Same value as the store above. It leaves no instruction of its
                     * own, but it keeps owner live into this arm. */
                    hero->owner = owner;
                    target = D_L20_001BDCC0.refs.named.alternate;
                    upper = D_L20_001A9440;
                }
                {
                    YeedilCameraPrefix *camera = &D_L20_001C6AE0;
                    if (D_L20_001BDCC0.state == lower) {
                        mem_clear(camera,0,0x50);
                        D_L20_001AF3B0[0] = 1;
                        camera->scale = 0.8f;
                    }
                    if (lower < D_L20_001BDCC0.state && D_L20_001BDCC0.state < upper) {
                        moby_transform_joint_point(target,0,matrix);
                        copy_matrix3x4(D_0018A550,matrix);
                        value = camera->scale;
                        value += (12.0f-value)*0.07f;
                        camera->scale = value;
                        moby_transform_joint_to_world(target,0,camera);
                        vec_scale_to_length(&camera->point,D_0018A550,camera->scale);
                        FastVecAdd(&camera->point,camera,&camera->point);
                        InitializeBoltPointChain(target);
                        beam_update_chain_points(target);
                        gfx_add_draw_callback_third(beam_draw_ribbons_level,target);
                        if (D_L20_001BDCC0.mode == 5 && D_L20_001BDCC0.state == upper-1) {
                            offset.q = 0;
                            offset.f[0] = 18.0f; offset.f[1] = -2.5f; offset.f[2] = 1.0f;
                            matrix_mul_vec3(&offset,&offset,D_L20_001BA1F0);
                            FastVecAdd(&offset,&offset,D_L20_001BA1F0-0x230);
                            FastVecSub(&work,D_L20_001BA1F0-0x230,&offset);
                            vec_scale_to_length(&work,&work,1.0f);
                            part_spawn_blast_effect_moby(*(void **)(D_0018A550-0x170),&offset,&work,0.0f);
                        }
                    } else g_hero_state.owner = 0;
                }
            }
        }
    }
    {
        int i;
        u8 *object;
        if ((u32)(D_L20_001BDCC0.mode-2) < 3) {
            for (i = 0; i < D_L20_001BDCC0.count; ++i) {
                u16 word;
                object = D_L20_001BDCC0.refs.objects[i];
                word = *(u16 *)(object+0xAA);
                if ((u32)(word-0xD0E /* Megacorp Trooper Torso, Legs */) < 2) {
                    *(u16 *)(object+0x7C) = word = (s16)word == 0xD0F ? 15 : 0x3FF;
                }
                if (*(s16 *)(object+0xAA) == 0xCE0 /* moby class 3296 */ && (D_L20_001BDCC0.mode != 3 || D_L20_001BDCC0.state < D_L20_001A9430))
                    EmitScaledObjectParticles(object);
            }
        }
        if (D_L20_001BDCC0.mode == 3 && D_L20_001BDCC0.state == D_L20_001A9430) {
            qcopy(matrix,(u8 *)D_L20_001BDCC0.refs.named.target+0x10);
            FastVecAdd(matrix,matrix,&D_L20_001A9420);
            SpawnExplosion(matrix,0,0x19,0x14,0x14,0x14,0x2D,1,1.0f,20.0f,1,1,0,0);
            {
                YeedilEffectPrefix *effect = &D_L20_001B9E80;
                effect->scale1 = 0.09f;
                effect->count1 = 0x37;
                effect->scale2 = 0.08f;
                effect->count2 = 0x46;
                effect->state1 = 0;
            }
        }
    }
}

/* func_L20_0039BEC8 (1,252 bytes, Yeedil): the trail packet renderer. This unit builds with
 * -frac2-gcse-hash-fp-112 (config/cflags.txt): PRE's reaching registers, and so the spill slots at
 * sp+0x148..0x168, are created in retail's order (docs/build/compiler-notes.md). Owner standard
 * of 12 November 2026. */
/* 9 November 2026 (o148): loop 3 now `float width = -(i > 1 ? B4 : 7C);` passing width: the neg.s $f12,$f0 register is fixed (27 -> 24 rows, all 24 PRE spill-slot offsets; check.py us/pal/us2 0/1, +0x8c). Forced S=129 then leaves only the obj+16 slot swap (5 rows). Slot model: only S=129 (max_cuid 256..259; ours 269) with the obj+16 base pseudo R in 113..128 or 242..257 gives retail order (S=161 swaps sp+64/sp+208, fixed hashes). A late `char *base = object;` block after loop 1 gives R=150; loop-1 pointer locals pos/cp/odd reach R=134 but reshuffle the giv registers, and only adding `Pair *uv` reaches 128, which changes size (310/314). cse1 already deletes redundant address insns, so these spellings do not lower max_cuid; no honest -11 insn route found. */
/* 9 November 2026 (o143, set-once constant lever): forced-S sweep of the s31 base (max_cuid 268, 135 buckets): S=129 gives 8 rows, S=161 9, every other odd S 125..181 18-30. Set-once constant locals only add insns (+1 each), and S=161 would need +54, so the lever does not reach it; no C change. */
/* 9 November 2026 (Codex, inline-helper/lifetime follow-up): 311 new C
 * variants checked with game -O2 -G8 -ffunction-sections: 255 combinations
 * of matrix/direction/normal/rotation/fade/depth/scale helpers, 7 object-copy
 * placements within loop 1, 1 typed object prefix, 8 negative-scale helpers,
 * and 40 complete-loop helper/order/counter forms. None beats the retained
 * 1252-byte, 27-word baseline (relocation immediate bits excluded). A normal
 * helper gives 51 words; direction or rotation helpers shorten to 1244;
 * complete loop-1/2 helpers give 1236/1244 and 1220 respectively. Object-copy
 * placements and the typed prefix tie; moving width selection inside a
 * negative-scale helper gives 1252/31 or 1256/126. The closest complete
 * loop-3 helper gives 1252/28. Rechecked the retained body with check.py in
 * USA v1.01, v2.00 and PAL: each 0/1, first +0x8c. No linked build run.
 * Reopen on a source shape that preserves indexed-loop reloads while changing
 * PRE expression order/count, rather than these equivalent helper wrappers.
 */
/* 9 November 2026 (o81, PRE slot solve): fresh -dG dump: 135 buckets, 268 insns at gcse (266 at addressof + jump if-conversion cmov setup). Retail slot order sp+304, sp+64, sp+208, sp+80, sp+84, sp+256, obj+16, sp+272, sp+288 (ours sp+288 first, obj+16 before sp+256). Over S 11..799 only S=129 works (max_cuid 256..259, need 9..12 fewer insns) and the obj+16 base pseudo (PRE copy at end of bb 5, after loop 1) must be 113..127, 242..256 or 371..385 (ours 85). In our numbering 113..127 is the middle of loop 1 and a late declaration lands at ~149, so the base cannot move there by declaration order; not a small change, no C tried. */
/* 9 November 2026 (Sonnet round, s48): re-measured 1252/1252, 3 masked / 27 unmasked rows (all PRE spill-slot order). Every -frac2-* and -fno-gcse/-fno-cse-follow-jumps/-fno-rerun-loop-opt singly and in pairs: none better (qcopy, -fno-gcse break size; zero-ti-barrier 55). do-while(0) groups of 1-3 statements around each simple statement (116 variants): none better. */
/* 8 November 2026 (Sonnet round, lesson 49 + declaration sweep): re-measured 1252/1252, 28 differing words. Locals checked: object/arg copy (writing ((char *)arg) everywhere is byte-identical, pseudo numbers do not move), width as expression (204/123 words, worse), vars set later (300, worse), negw temp (28, tie). Every single declaration move among packet/matrix/rotated/direction/tangent/normal/vars/color: no gain. Permuter (-j2, 1500 s) only junk (undefined helpers). Still the PRE slot order plus the loop-3 neg.s register. */
/* 8 November 2026 (Sonnet round, lesson 48 sweep): every single statement move of 1-6 places inside a run of simple statements, every top-level simple statement moved up to 6 top-level items, and pairs of the best singles: no variant beats the base (27 words); moves either tie or get worse. */
/* 8 November 2026 (named-local slot order, the func_00281A08 technique): slots 0x148..0x168 hold, in retail, &normal, &packet.color, rotated, &uv.x, &uv.y, rotated+12, (obj+0x10 at 0x160), &direction, &tangent; ours put &tangent first, the rest in the same order. Named locals take slots before every PRE register (arg 0x140, vars 0x144 already do), so one named pointer can only move &tangent earlier, not last; moving it last would need eight named stack pointers, which get hard registers or fold back (as in func_L00_0038E880 and func_L13_0041AD00). Not pursued further. */
/* 8 November 2026 (round 12): size is already 1252/1252; only the PRE spill-slot order and the loop-3 neg.s register differ. gcse hash of (plus (reg R) c) is (14029 + R + c) mod N (frame reg 1); over N 11..999 only N=129 (max_cuid 256..259, ours 268..271) gives retail's order, with the obj+0x10 base pseudo in 113..127. A late `char *object = arg;` after loop 1 (top uses via arg) gives base 149, plus per-iteration pos/color pointers 133, code unchanged but the insn count is not. Pointer-cursor loops reach base 113/115 and 261..265 insns but give 1212/1228 bytes (retail reloads sp+0x40/0x50/0x54 from PRE slots before loop 2, so its loops are indexed). Single-table `D_L20_001AEC80_gp[i].y` / `D_L20_001AECB8_gp[i].y` with -Wa,--r5900-la-addend=sn gives the same output as the D_..84/BC NOT_SDA views. No -f flag tried (cse-follow-jumps, expensive-optimizations, force-addr, thread-jumps, ...) gives 129 buckets; the color ternary on loads or an if/else around the loop-3 call changes size. No RAC1 twin found. */
/* 7 November 2026 (round 9): -fcall-used-hi1/lo1/accum1 do not change the gcse PRE order here; no constant pseudo-number or cuid offset shared by the hash-order near misses fixes it (docs/build/compiler-notes.md, patch 0055). */
/*
 * func_L20_0039BEC8 -- non-matching draft
 * Tier: Claude Opus 5.5, xhigh effort, task v2204 (opus-1).
 * Target file: src/levels/20_yeedil/L20_002DEBE0-g8.c (-G8), replacing
 *   INCLUDE_ASM("asm/levels", func_L20_0039BEC8);
 * Best check.py: "20_yeedil: instruction at +0x8c differs" /
 *   "func_L20_0039BEC8: 0 of 1 places match"; 1252/1252 bytes.
 * What differs (all else, incl. prologue, loop-1 allocation and the four
 *   D_L20_001AECD8 colour loads, matches apart from relocations):
 *   - PRE spill-slot order of the hoisted sp+X addresses (0x148..0x168).
 *     Retail order normal,color,rotated,uv.x,uv.y,rotated+12,obj+0x10,dir,
 *     tangent is reproduced by the gcse hash model only with a 129-bucket
 *     expression table (ours: 135, i.e. ~12 fewer insns at gcse time) and
 *     an obj+0x10 base pseudo numbered 113..127 (ours: reg 85), so the
 *     original probably spells the post-loop-1 part differently (inline
 *     helper taking the object pointer?).
 *   - third loop: retail loads width into $f0 then neg.s $f12,$f0; ours
 *     loads into $f12 (preference through the neg). Shared outer `width`
 *     changes nothing.
 * Needs from the g8 file: u32/u64, qcopy, SDATA/NOT_SDA, and the existing
 *   externs func_002A7878(float,float) and func_002A7940(void).
 * FastTweenColor (func_00283D38) prototype (int from, int to, float t) is
 *   what fixes loop-1 s6/s7/fp; D_L20_001AECD8 as incomplete sda array
 *   (indices 1..3 become unsplit CONST lui/lw loads) plus a SDATA view
 *   for index 0 reproduces the colour-argument loads.
 */
typedef union { Quad q; float f[4]; } Vec;
typedef struct { float x, y; } Pair;
typedef struct { Vec position[4]; u32 color[4]; Pair uv[4]; u64 descriptor[4]; } TrailPacket;
extern int D_L20_001AEC6C __attribute__((sda)), D_L20_001AECA0 __attribute__((sda));
extern u32 D_L20_001AEC70[2] __attribute__((sda)), D_L20_001AECA8[2] __attribute__((sda));
extern float D_L20_001AEC84[] __attribute__((sda)) NOT_SDA, D_L20_001AECBC[] __attribute__((sda)) NOT_SDA;
extern Pair D_L20_001AEC80_gp[4] SDATA(D_L20_001AEC80) __attribute__((sda));
extern Pair D_L20_001AECB8_gp[4] SDATA(D_L20_001AECB8) __attribute__((sda));
extern float D_L20_001AEC78 __attribute__((sda)), D_L20_001AEC7C __attribute__((sda)), D_L20_001AECB4 __attribute__((sda));
extern u32 D_L20_001AECD8_gp SDATA(D_L20_001AECD8) __attribute__((sda));
extern u32 D_L20_001AECD8[] __attribute__((sda));
extern float D_L20_001AECE8 __attribute__((sda)), D_L20_001AECEC;
extern float D_L20_001B9FC0[4];
extern void copy_matrix_rotation(void *,void *);
extern u64 GetEffectTextureDescriptor(int);
extern int FastTweenColor(int, int, float);
extern void vec_store_helper(void *);
extern void euler_rotation_basis(void *,void *);
extern void gfx_transform_and_draw_entries(void *,int,void *,int,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_transform_by_object_or_given(char *,char *,char *,char *);
extern void vec_scale_to_length(void *,void *,float);
extern void draw_world_quad(void *,void *,int);
extern void gfx_draw_billboard_quad(void *,int,u32,int,float,float,float);



/* Draws the glowing trail for the particle effect: two crossed ribbons and some sparkles, faded by the effect's strength. */
void part_draw_glow_trail(void *arg)
{
    char *object = arg;
    TrailPacket packet;
    float matrix[16], rotated[16];
    Vec direction, tangent, normal;
    float *vars = *(float **)(object + 0x68);

    u32 color;
    copy_matrix_rotation(matrix, object + 0xc0);
    qcopy(matrix + 12, object + 0x10);
    packet.descriptor[1] = GetEffectTextureDescriptor(D_L20_001AEC6C);
    packet.descriptor[0] = 0;
    packet.descriptor[2] = 0xff9000000260ULL;
    packet.descriptor[3] = 0x8000000048ULL;
    {
        int i;
        for (i = 0; i < 4; i++) {
            u32 color;
            packet.uv[i].x = D_L20_001AEC80_gp[i].x;
            packet.uv[i].y = D_L20_001AEC84[i * 2];
            color = D_L20_001AEC70[(i & 1) ? 0 : 1];
            packet.color[i] = color;
            packet.color[i] = FastTweenColor(color & 0xffffff, color, vars[0]);
            vec_store_helper(&packet.position[i]);
            packet.position[i].f[0] = D_L20_001AEC7C;
            if ((i & 1) == 0) packet.position[i].f[2] = D_L20_001AEC78;
            else packet.position[i].f[2] = 0.0f;
        }
    }
    *(Quad *)(rotated + 12) = 0;
    rotated[14] = 0.19634954631328583f;
    euler_rotation_basis(rotated, rotated + 12);
    gfx_transform_and_draw_entries(&packet, 1, rotated, 32, matrix);
    FastVecSub(&direction, D_L20_001B9FC0, object + 0x10);
    vec_transform_by_object_or_given(object, (char *)&direction, (char *)&direction, 0);
    normal.q = 0;
    normal.f[0] = direction.f[1];
    normal.f[1] = -direction.f[0];
    normal.f[3] = 1.0f;
    tangent.q = normal.q;
    direction.f[2] = 0.0f;
    packet.descriptor[1] = GetEffectTextureDescriptor(D_L20_001AECA0);
    {
        int i;
        for (i = 0; i < 4; i++) {
            u32 color;
            float width;
            packet.uv[i].x = D_L20_001AECB8_gp[i].x + vars[3];
            packet.uv[i].y = D_L20_001AECBC[i * 2];
            color = D_L20_001AECA8[(i & 1) ? 0 : 1];
            packet.color[i] = color;
            packet.color[i] = FastTweenColor(color & 0xffffff, color, vars[0]);
            width = i > 1 ? D_L20_001AECB4 : D_L20_001AEC7C;
            vec_scale_to_length(&packet.position[i], &tangent, width);
            if ((i & 1) == 0) packet.position[i].f[2] = D_L20_001AEC78;
            else packet.position[i].f[2] = 0.0f;
        }
    }
    draw_world_quad(&packet, matrix, 0);
    {
        int i;
        for (i = 0; i < 4; i++) {
            float width = -(i > 1 ? D_L20_001AECB4 : D_L20_001AEC7C);
            vec_scale_to_length(&packet.position[i], &tangent, width);
            if ((i & 1) == 0) packet.position[i].f[2] = D_L20_001AEC78;
            else packet.position[i].f[2] = 0.0f;
        }
    }
    draw_world_quad(&packet, matrix, 0);
    qcopy(&normal, object + 0x10);
    normal.f[2] += 0.333f;
    color = FastTweenColor(D_L20_001AECD8_gp, D_L20_001AECD8[1], math_random_float_range(0.0f,1.0f));
    color = FastTweenColor(color & 0xffffff, color, vars[0]);
    gfx_draw_billboard_quad(&normal, 11, color, 1, D_L20_001AECE8, 0.0f, math_random_angle());
    color = FastTweenColor(D_L20_001AECD8[2], D_L20_001AECD8[3], math_random_float_range(0.0f,1.0f));
    color = FastTweenColor(color & 0xffffff, color, vars[0]);
    gfx_draw_billboard_quad(&normal, 11, color, 1, D_L20_001AECEC, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(object + 0x10, 49, color, 1, D_L20_001AECEC, 0.0f, math_random_angle());
}

/* func_L20_002DEBE0 is in the sibling file L20_002DEBE0-decider.c. */
