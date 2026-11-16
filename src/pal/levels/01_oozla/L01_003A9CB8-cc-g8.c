#include "names.h"
/* func_PAL_L01_003A9CB8, the PAL copy of func_L01_003A6638: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002ABBB8 becomes func_PAL_002AC718; rename func_L01_002BEB90 becomes func_PAL_L01_002BEC60; scale (*(u16 *)(object+0x34) | 0x41); wrap (vertical*maximum-F(state,0x4C)) (({e}) * 1.2f); lit 6 becomes 5; lit 5 becomes 2; rewrap object; rewrap D_L01_001AF878. */
/* func_PAL_L01_003A9CB8: the update of a moby steered with the stick, by its state byte at +0x20.
 * State 0 copies the yaw at +0x18 to +0x44 and starts animation 1. State 1 turns and moves the
 * moby, probes the move with collision lines and slides along what they hit; on Circle it spawns
 * an explosion, damages the mobys in range and starts the timer at +0x40 (state 2). State 2 waits
 * for the timer, then calls func_003355A8 and func_PAL_L01_002BEC60 and deletes the moby, as state 1
 * does when the moby leaves the 2..1021 box. */
#include "common.h"

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
typedef int OozlaQuad __attribute__((mode(TI)));
extern float g_hover_turn_rate_scale __attribute__((sda));
extern float g_hover_collision_radius __attribute__((sda));
extern int g_hover_state_flags __attribute__((sda));
extern float g_moby_probe_length __attribute__((sda));
extern float g_hover_vertical_smoothing __attribute__((sda));
extern float g_hover_adjust_length __attribute__((sda));
extern float g_hover_edge_length_a __attribute__((sda));
extern float g_hover_edge_length_b __attribute__((sda));
extern float g_hover_path_length __attribute__((sda));
extern float g_hover_offset_length __attribute__((sda));
extern float g_hover_shift_speed __attribute__((sda));
extern float g_hover_max_step_speed __attribute__((sda));
extern float g_hover_push_strength __attribute__((sda));
extern float g_hover_max_angle_degrees __attribute__((sda));
extern float g_debris_velocity_vector[] MACRO_ADDR;
extern u8 g_item_slot_to_record[];
extern char g_pad_state[];
typedef struct { u8 pad[0x1A4]; u32 flags; } OozlaInput;
typedef struct { u8 pad[0x50]; float speed; u8 gap[0x1C]; float material; u8 tail[0x6C]; } OozlaMaterial;
extern OozlaMaterial g_action_table[];
extern u8 g_collision_l01_hit[];
extern u8 g_contact_moby_list[];
extern int g_hero_misc_flag;
extern void anim_start_blended_pal(void *,int,int,int);
extern void hero_get_clamped_stick_tilt(float *,float *);
extern float FastAddRotations(float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void moby_move_with_collision(void *);
extern float FastVecLength(void *);
extern void gfx_draw_vehicle_beam(void *,void *);
extern void euler_to_matrix(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern float math_fabs(float);
extern void FastVecScale(void *,void *,float);
extern int CollLine(void *,void *,int,void *,void *);
extern float FastVecDot(void *,void *);
extern float math_fast_angle_helper(float);
extern void copy_matrix_rotation(void *,void *);
extern void copy_matrix3x4(void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void multiply_matrix(void *,void *,void *);
extern void mat_get_euler_angles(void *,void *);
extern void matrix_from_basis_rows(void *,void *);
extern void transform_vector(void *,void *,void *);
extern s32 func_L00_002EE4D8(void *,void *,float);
extern void SpawnExplosionEffects_pal(char *owner, void *direction, float *position,
    float radius, float damage, int sparks, int flashes, int smoke,
    float glow, float white, float cutoff, float scale, int sound, float blast,
    int shake, int debris, int quality, unsigned char channels, int flags);
extern int coll_process_hit(void *,int,void *,void *,float);
extern void moby_queue_knockback_for_nodes(void *,void *,void *,int,int,int,int,int,float,float,float);
extern int math_fast_float_d(void *);
extern void cam_set_mode_state(int);
extern int SetHeroMoveState_pal(int,int);
extern void moby_mark_spawned(void *);
extern void part_queue_ground_shadow(void *,float);
/* Updates a moby the player steers with the stick: it moves, slides along walls, and explodes on Circle (PAL version). */
void steered_moby_update_pal(u8 *moby)
{
    float previous[4], velocity[4], position[4];
    float horizontal, vertical;
    float maximum, speed, progress, sign, angle, half;
    u8 *state = *(u8 **)(moby+0x68);
    int collision, count;
    /* Arguments named for the callees' parameters. They are set before the switch and read
       in its cases, so gcse folds them; they bring the RTL count to the 536 insns (269 hash
       buckets) that give retail's spill-slot order at 0x1B8-0x1C8. */
    int line_flags = 0;          /* CollLine flags */
    void *line_packet = 0;       /* CollLine result packet: none */
    int detonate = 0x20;        /* PAD_CIRCLE in the pressed mask */
    int sphere_flags = 0x10;     /* func_00277F48 flags */
    void *sphere_hit = 0;        /* func_00277F48 result: none */
    int spared = 0;             /* func_002A9850: no moby is left out */
    float *explosion_at = 0;     /* SpawnExplosionEffects position: the owner's */
    int sparks = 10, flashes = 3, smoke = 16;

    qcopy(previous, (moby+0x10));
    switch (moby[0x20]) {
    case 0:
        F(state,0x44) = F(state,0x18);
        moby[0x20] = 1;
        if (moby[0x43] != 1) anim_start_blended_pal(moby,1,0,10);
        break;
    case 1:
        /* The vectors' block closes inside the matrices' block, so both sets of slots are freed
           and merged; the displacement block below then reuses them from the rotation matrix
           on (retail: displacement 0x50, inverse 0x60, center 0xA0). */
        {
            float rotation[16], basis[4][4], matrix[16];
            {
                float start[4], angles[4], finish[4], shift[4], offset[4], hit[4], normal[4], force[4], adjustment[4], edge[4];

                hero_get_clamped_stick_tilt(&horizontal,&vertical);
                F(state,0x18) = F(state,0x44) = FastAddRotations(F(state,0x44),g_hover_turn_rate_scale*(horizontal*0.0003490659f));
                maximum = ((OozlaMaterial *)((u32)g_action_table + g_item_slot_to_record[0x20]*sizeof(OozlaMaterial)))->speed*0.020000001f;
                F(state,0x4C) += (((vertical*maximum-F(state,0x4C))) * 1.2f)*g_hover_vertical_smoothing;
                speed = F(state,0x4C)/maximum;
                F(moby,0x48) = speed+speed+horizontal;
                vec_scale_to_length(velocity,g_debris_velocity_vector,F(state,0x4C));
                matrix_mul_vec3(velocity,velocity,moby+0xC0);
                velocity[2] += F(state,0x54);
                FastVecAdd(position,moby+0x10,velocity);
                qcopy((moby+0x10), position);
                moby_move_with_collision(moby);
                if (F(state,0x4C) < 0.0f) F(state,0x4C) = -FastVecLength(velocity);
                else F(state,0x4C) = FastVecLength(velocity);
                gfx_draw_vehicle_beam(moby,state);
                *(OozlaQuad *)angles = 0;
                angles[2] = g_hover_turn_rate_scale*(horizontal*0.0003490659f);
                *(OozlaQuad *)start = *(OozlaQuad *)angles;
                qzero_nc(rotation);
                qzero_nc(basis[0]);
                qzero_nc(matrix);
                euler_to_matrix(rotation,start);
                progress = 0.0f;
                collision = 0;
                while (progress <= g_hover_path_length && !collision) {
                    sign = vertical < 0.0f ? -1.0f : 1.0f;
                    vec_scale_to_length(angles,moby+0xE0,g_moby_probe_length);
                    FastVecAdd(angles,angles,moby+0x10);
                    vec_scale_to_length(shift,moby+0xC0,g_hover_shift_speed*progress*sign);
                    FastVecAdd(angles,angles,shift);
                    vec_scale_to_length(offset,moby+0xE0,g_hover_offset_length);
                    FastVecSub(finish,moby+0x10,offset);
                    FastVecScale(normal,velocity,math_fabs(vertical));
                    half = g_hover_path_length*0.5f;
                    FastVecScale(shift,normal,(g_hover_push_strength*(half-progress))/half);
                    FastVecAdd(finish,finish,shift);
                    collision = CollLine(angles,finish,line_flags,moby,line_packet);
                    progress += 1.0f;
                }
                if (collision) {
                    qcopy(hit, (g_collision_l01_hit+0x20));
                    vec_scale_to_length(normal,moby+0xE0,1.0f);
                    vec_scale_to_length(force,g_collision_l01_hit+0x40,1.0f);
                    angle = 1.5707964f-math_fast_angle_helper(FastVecDot(normal,force));
                    if (g_hover_max_angle_degrees*0.017453294f < angle) {
                        qcopy((moby+0x10), previous);
                    } else {
                        vec_scale_to_length(adjustment,g_collision_l01_hit+0x40,g_hover_adjust_length);
                        vec_scale_to_length(angles,moby+0xE0,g_moby_probe_length);
                        FastVecSub(finish,moby+0x10,angles);
                        FastVecAdd(angles,angles,moby+0x10);
                        if (CollLine(angles,finish,line_flags,moby,line_packet)) {
                            vec_scale_to_length(edge,g_collision_l01_hit+0x40,g_hover_edge_length_a);
                            FastVecAdd(adjustment,adjustment,edge);
                        }
                        vec_scale_to_length(edge,moby+0xE0,g_hover_edge_length_b);
                        FastVecAdd(adjustment,adjustment,edge);
                        copy_matrix_rotation(basis[0],moby+0xC0);
                        vec_scale_to_length(basis[2],adjustment,-1.0f);
                        FastVecCross(basis[1],basis[2],basis[0]);
                        FastVecCross(basis[0],basis[1],basis[2]);
                        multiply_matrix(matrix,basis[0],rotation);
                        mat_get_euler_angles(matrix,moby+0xF0);
                        FastVecSub(edge,hit,moby+0x10);
                        vec_scale_to_length(edge,edge,
                            g_hover_max_step_speed*0.020000001f < FastVecLength(edge)
                            ? g_hover_max_step_speed*0.020000001f : FastVecLength(edge));
                        FastVecAdd(moby+0x10,moby+0x10,edge);
                        F(state,0x54) = 0.0f;
                    }
                } else {
                    qcopy((moby+0x10), previous);
                    copy_matrix_rotation(basis[0],moby+0xC0);
                    copy_matrix3x4(moby+0xC0,matrix);
                    multiply_matrix(matrix,basis[0],rotation);
                    copy_matrix3x4(moby+0xC0,matrix);
                }
            }
        }
        moby_move_with_collision(moby);
        {
            float displacement[4], inverse[16], center[4];

            matrix_from_basis_rows(inverse,moby+0xC0);
            FastVecSub(displacement,moby+0x10,previous);
            transform_vector(displacement,displacement,inverse);
            func_L00_002EE4D8(displacement,displacement,math_fabs(F(state,0x4C)));
            matrix_mul_vec3(displacement,displacement,moby+0xC0);
            FastVecAdd(moby+0x10,previous,displacement);
            if (((OozlaInput *)g_pad_state)->flags & detonate) {
                SpawnExplosionEffects_pal((char *)moby,velocity,explosion_at,0.0f,0.0f,sparks,flashes,smoke,4.0f,2.0f,0.0f,1.0f,1,20.0f,1,1,-1,0,0x810001);
                count = coll_process_hit(moby+0x10,sphere_flags,moby,sphere_hit,g_hover_collision_radius);
                *(OozlaQuad *)center = *(OozlaQuad *)(moby+0x10);
                moby_queue_knockback_for_nodes(moby,center,g_contact_moby_list,count,spared,0x830000,3,2,((OozlaMaterial *)((u32)g_action_table + g_item_slot_to_record[0x20]*sizeof(OozlaMaterial)))->material,1.0f,1.0f);
                I(state,0x40) = (((int)(g_hover_state_flags) * 5 + 2) / 6);
                I(moby,0x98) = 0;
                *(u16 *)(moby+0x34) = (*(u16 *)(moby+0x34) | 0x41)&0xEFFF;
                g_hero_misc_flag = 0;
                moby[0x20] = 2;
            }
        }
        if (F(moby,0x10)<2.0f || F(moby,0x10)>1021.0f || F(moby,0x14)<2.0f || F(moby,0x14)>1021.0f || F(moby,0x18)<2.0f || F(moby,0x18)>1021.0f) {
            moby_mark_spawned(moby);
            return;
        }
        break;
    case 2:
        if (math_fast_float_d(state+0x40)) {
            cam_set_mode_state(0);
            SetHeroMoveState_pal(0,1);
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    part_queue_ground_shadow(moby,g_moby_probe_length);
}
