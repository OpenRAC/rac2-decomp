/* func_PAL_L20_00312A28, the PAL copy of func_L20_00310E38: the same C, where each level timer
 * takes the 5/6 scale at its use, 0x37 becomes 0x2E and 0x46 becomes 0x3A. The 0xFA0 test takes
 * USA v2.00's `D_001A79F0 != 0x33` and `wanted`. */
#include "common.h"

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
extern YeedilStatePrefix g_yeedil_state_prefix;
extern u32 g_current_map_index;
typedef struct { u8 before_owner[0x5C0]; int owner; } YeedilHeroPrefix;
extern YeedilHeroPrefix g_hero_state;
extern u8 g_hero_matrix[];
typedef struct {
    Vector origin, point;
    float unknown20, scale;
} YeedilCameraPrefix;
extern YeedilCameraPrefix g_yeedil_camera_prefix;
extern u8 g_level_script_matrix[];
typedef struct {
    u8 before_effect[0x160];
    float scale1;
    int unknown164, count1, state1;
    u8 before_effect2[0x10];
    float scale2;
    int unknown184, count2;
} YeedilEffectPrefix;
extern YeedilEffectPrefix g_hero_l20_extra_state;
extern int g_level_script_state_limit __attribute__((sda));
extern int g_level_script_lower_a __attribute__((sda));
extern int g_level_script_upper_a __attribute__((sda));
extern int g_level_script_lower_b __attribute__((sda));
extern int g_level_script_upper_b __attribute__((sda));
extern Vector g_level_script_offset_vec SDATA(D_L20_001A9420);
extern int g_level_script_flags[] __attribute__((sda));
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

void func_PAL_L20_00312A28(void *incoming)
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
        for (i = 0; i < g_yeedil_state_prefix.count; ++i) {
            u8 *object;
            object = g_yeedil_state_prefix.refs.objects[i];
            if (object && *(s16 *)(object+0xAA) == 0xE29)
                *(u16 *)(object+0x34) |= 0x800;
            if (*(s16 *)(object+0xAA) == 0xD54)
                UpdateEquipmentPieces(object);
            if (object) {
                int wanted = 0xFA0;
                if (*(s16 *)(object+0xAA) == wanted && g_current_map_index != 0x33 && *(void **)(object+0x68))
                    math_store_angle_update_result((char *)object,(float *)(*(u8 **)(object+0x68)+0xC),
                                      0x80AAAAD2,0x80396464,0.07330384f);
            }

        }
    }
    if (g_current_map_index != 20) return;
    {
        if ((u32)(g_yeedil_state_prefix.mode-4) < 2) {
            {
                YeedilHeroPrefix *hero = &g_hero_state;
                int owner = g_yeedil_state_prefix.refs.named.owner;
                hero->owner = owner;
                if (g_yeedil_state_prefix.mode == 4) {
                    hero->owner = g_yeedil_state_prefix.refs.named.secondary_owner;
                    target = g_yeedil_state_prefix.refs.named.secondary_target;
                    lower = (g_level_script_lower_a * 5 + 2) / 6;
                    upper = (g_level_script_upper_a * 5 + 2) / 6;
                } else {
                    /* Same value as the store above. It leaves no instruction of its
                     * own, but it keeps owner live into this arm. */
                    hero->owner = owner;
                    lower = (g_level_script_lower_b * 5 + 2) / 6;
                    target = g_yeedil_state_prefix.refs.named.alternate;
                    upper = (g_level_script_upper_b * 5 + 2) / 6;
                }
                {
                    YeedilCameraPrefix *camera = &g_yeedil_camera_prefix;
                    if (g_yeedil_state_prefix.state == lower) {
                        mem_clear(camera,0,0x50);
                        g_level_script_flags[0] = 1;
                        camera->scale = 0.8f;
                    }
                    if (lower < g_yeedil_state_prefix.state && g_yeedil_state_prefix.state < upper) {
                        moby_transform_joint_point(target,0,matrix);
                        copy_matrix3x4(g_hero_matrix,matrix);
                        value = camera->scale;
                        value += (12.0f-value)*0.08400001f;
                        camera->scale = value;
                        moby_transform_joint_to_world(target,0,camera);
                        vec_scale_to_length(&camera->point,g_hero_matrix,camera->scale);
                        FastVecAdd(&camera->point,camera,&camera->point);
                        InitializeBoltPointChain(target);
                        beam_update_chain_points(target);
                        gfx_add_draw_callback_third(beam_draw_ribbons_level,target);
                        if (g_yeedil_state_prefix.mode == 5 && g_yeedil_state_prefix.state == upper-1) {
                            offset.q = 0;
                            offset.f[0] = 18.0f; offset.f[1] = -2.5f; offset.f[2] = 1.0f;
                            matrix_mul_vec3(&offset,&offset,g_level_script_matrix);
                            FastVecAdd(&offset,&offset,g_level_script_matrix-0x230);
                            FastVecSub(&work,g_level_script_matrix-0x230,&offset);
                            vec_scale_to_length(&work,&work,1.0f);
                            part_spawn_blast_effect_moby(*(void **)(g_hero_matrix-0x170),&offset,&work,0.0f);
                        }
                    } else g_hero_state.owner = 0;
                }
            }
        }
    }
    {
        int i;
        u8 *object;
        if ((u32)(g_yeedil_state_prefix.mode-2) < 3) {
            for (i = 0; i < g_yeedil_state_prefix.count; ++i) {
                u16 word;
                object = g_yeedil_state_prefix.refs.objects[i];
                word = *(u16 *)(object+0xAA);
                if ((u32)(word-0xD0E) < 2) {
                    *(u16 *)(object+0x7C) = word = (s16)word == 0xD0F ? 15 : 0x3FF;
                }
                if (*(s16 *)(object+0xAA) == 0xCE0) {
                    /* Set ahead of the load: with the division in the loop only its
                     * longer life lets loop.c move it out in the first pass. */
                    int wanted = 3;
                    if (g_yeedil_state_prefix.mode != wanted || g_yeedil_state_prefix.state < (g_level_script_state_limit * 5 + 2) / 6)
                        EmitScaledObjectParticles(object);
                }
            }
        }
        if (g_yeedil_state_prefix.mode == 3) {
            /* The second division's result is unused, so flow deletes its div. Its zero-divide
             * guard stays and prints nothing (mips.md div_trap: a guard anti-dependent on an
             * earlier guard). As the last guard before the branch it stops reorg merging this
             * branch's `ld $s0` slot into the slot of the mode test. */
            int divisor = 6;
            int limit = (g_level_script_state_limit * 5 + 2) / divisor;
            int state = g_yeedil_state_prefix.state;
            int unused = (g_level_script_state_limit * 5 + 2) / divisor;
            if (state == limit) {
                qcopy(matrix,(u8 *)g_yeedil_state_prefix.refs.named.target+0x10);
                FastVecAdd(matrix,matrix,&g_level_script_offset_vec);
                SpawnExplosion(matrix,0,0x19,0x14,0x14,0x14,0x2D,1,1.0f,20.0f,1,1,0,0);
                {
                    YeedilEffectPrefix *effect = &g_hero_l20_extra_state;
                    effect->scale1 = 0.09f;
                    effect->count1 = 0x2E;
                    effect->scale2 = 0.08f;
                    effect->count2 = 0x3A;
                    effect->state1 = 0;
                }
            }
        }
    }
}
