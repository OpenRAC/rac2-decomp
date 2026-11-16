#include "names.h"
/* GPT-6.1 Sol high, task v0887; USA v1.01.
 * Best: 1144/1144 bytes, 0/1 places. Profile: -O2 -G8 -ffunction-sections -g.
 * Frame and saved-register set agree; object is s4 instead of s2, with the
 * position/velocity addresses correspondingly shifted. Conditional retirement
 * argument scheduling/likely branches still differ. All declarations follow.
 * Corrects the prior draft: the first age interval also installs the callback;
 * its third particle reverses the second particle's spin. Retail's first last
 * particle call branches into the second interval's shared call/hook tail.
 * Ordinary TI impact copies recover the store in the predicate-call delay slot.
 * A 16-byte MACRO_ADDR velocity declaration prevents address hoisting across
 * particle calls. Separate branch-local sizes recover f22 versus f20.
 * Explicit collision labels and a shared expiry label reach retail size, but
 * merging expiry removes an object reference and lowers its allocation priority.
 * Keeping separate expiry calls recovers the GPR allocation at 1152 bytes.
 * Next: original collision/expiry CFG and source lifetime evidence, without
 * artificial references. No linked build was run because no checker match exists.
 * 1 November 2026: the shared expiry tail copied into the guard arm takes this
 * from 54 rows to 14 (object in s2, retail's frame and order). Left: the two
 * impact branches are bnel with a0=object where retail has bnez with a0=impact
 * in the slot (reorg's simple pass, fall-through), and two mov.s/t2 orders.
 * Writing func_L11_00434F48 per arm makes the a0 load right but keeps bnel.
 */
#include "common.h"

/* func_L11_00434580: a thrown projectile's per-frame update. Each frame it advances along its
   velocity and tests for a hit; frames below 25 always spawn the trail particles, frames 25-33
   only while the projectile is still moving, and at 34 it expires. On a hit it snaps to the
   impact point and, unless the predicate says otherwise, bursts (6 or 3 pieces) and is removed.
   Built -G8 -g in its own unit (the particle colours are $gp-relative).
   Each arm spells out its own hit tail; jump2's cross-jumping merges them after allocation,
   which is why the object keeps $s2 and each arm loads the impact pointer before the shared
   burst call. The particle call's last two arguments are declared float-then-int (the same
   $t2/$f14 registers) so the $t2 zero lands in the call's delay slot as in retail. */
typedef int Quad34580 __attribute__((mode(TI)));
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float vec_distance_xy(void *,void *);
extern void make_hit_descriptor(void *,void *,int,void *,float);
extern int CollLine(void *,void *,int,void *,void *);
extern int flag_is_third_pending_set(void *);
extern void part_l11_spawn_impact_burst(float *,int);
extern void moby_set_flag_bit(void *,int);
extern void moby_mark_spawned(void *);
extern float math_random_float_range(float,float);
extern int math_random_int_range(int,int);
extern void *part_spawn_ground_effect(void *,int,float,float,unsigned int,int,int,void *,float,int);
extern void gfx_add_draw_callback_third(void *,void *);
extern char g_aim_position[];
extern char g_identity_l11_matrix[16] MACRO_ADDR;
extern unsigned int g_thrown_projectile_spark_color_a __attribute__((sda));
extern unsigned int g_thrown_projectile_spark_color_b __attribute__((sda));
extern unsigned int g_thrown_projectile_spark_color_c __attribute__((sda));
extern unsigned int g_thrown_projectile_spark_color_d __attribute__((sda));
extern void projectile_run_trail_steps(char *);
/* Moves a thrown projectile each frame, spawns its trail, and bursts into pieces when it hits something or runs out of time. */
void thrown_l11_projectile_update(char *obj) {
    float vel[4]; char collision[48]; float pos[4],pos2[4];
    char *vars=*(char **)(obj+0x68);
    float scale=*(float *)(vars+0x3C);
    float *impact;
    *(float *)(vars+0x38)+=1;
    if (*(float *)(vars+0x38)<25) {
        float size; int sign;
        *(float *)(vars+0x34)+=1;
        vec_scale_to_length(vars+0x10,vars+0x20,*(float *)(vars+0x34));
        vec_scale_to_length(vel,vars+0x20,0.06666667f);
        make_hit_descriptor(collision,obj,0x10001,vel,scale);
        *(unsigned short *)(collision+0x1A)=*(unsigned short *)(obj+0xAA);
        FastVecAdd(vars+0x10,vars,vars+0x10);
        if(CollLine(vars,vars+0x10,0,obj,collision)) {
            impact=(float *)g_aim_position;
            *(Quad34580 *)(vars+0x10)=*(Quad34580 *)impact;
            if(!flag_is_third_pending_set(obj)) {
                part_l11_spawn_impact_burst(impact,6);
                moby_set_flag_bit(obj,1);
            }
            moby_mark_spawned(obj); return;
        }
        size=math_random_float_range(1,4);
        sign=math_random_int_range(25,35); if(!sign) sign--;
        qcopy(pos,vars+0x10); pos[2]-=0.1f;
        part_spawn_ground_effect(pos,15,size*0.3f,size,g_thrown_projectile_spark_color_a,0,sign,g_identity_l11_matrix,0.0f,0);
        sign = -sign;
        part_spawn_ground_effect(vars,10,size*0.3f,size,g_thrown_projectile_spark_color_b,0,sign,g_identity_l11_matrix,0.0f,0);
        part_spawn_ground_effect(vars,10,size*0.04f,size*0.4f,g_thrown_projectile_spark_color_c,1,-sign,g_identity_l11_matrix,0.0f,0);
        gfx_add_draw_callback_third(projectile_run_trail_steps,obj);
        return;
    } else if (*(float *)(vars+0x38)>=25 && *(float *)(vars+0x38)<34) {
        if(vec_distance_xy(vars,vars+0x10)>1) {
            float size; int sign;
            *(float *)(vars+0x34)+=1;
            vec_scale_to_length(vars+0x10,vars+0x20,*(float *)(vars+0x34));
            vec_scale_to_length(vel,vars+0x20,0.06666667f);
            make_hit_descriptor(collision,obj,0x10001,vel,scale);
            *(unsigned short *)(collision+0x1A)=*(unsigned short *)(obj+0xAA);
            FastVecAdd(vars+0x10,vars,vars+0x10);
            if(CollLine(vars,vars+0x10,0,obj,collision)) {
                impact=(float *)g_aim_position;
            *(Quad34580 *)(vars+0x10)=*(Quad34580 *)impact;
                if(!flag_is_third_pending_set(obj)) {
                    part_l11_spawn_impact_burst(impact,3);
                    moby_set_flag_bit(obj,1);
                }
                moby_mark_spawned(obj); return;
            }
            vec_scale_to_length(pos,vars+0x20,1.66666675f);
            FastVecAdd(vars,vars,pos);
            size=math_random_float_range(1,4);
            sign=math_random_int_range(25,35); if(!sign) sign--;
            qcopy(pos2,vars+0x10); pos2[2]-=0.1f;
            part_spawn_ground_effect(pos2,15,size*0.3f,size,g_thrown_projectile_spark_color_a,0,sign,g_identity_l11_matrix,0.0f,0);
            part_spawn_ground_effect(pos2,20,size*0.4f,size*0.2f,g_thrown_projectile_spark_color_d,1,-sign,g_identity_l11_matrix,0.0f,0);
            gfx_add_draw_callback_third(projectile_run_trail_steps,obj);
            return;

        }
        return;
    }
    moby_mark_spawned(obj);
}
