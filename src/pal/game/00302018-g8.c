/* func_PAL_00302018, the PAL copy of func_00300F58: the same C, where the per-frame constants are
   rescaled for 50 Hz and the two hop lengths go through the float form of the 5/6 scale. */
#include "common.h"

#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
typedef struct PickupMoby PickupMoby;
typedef struct {
    float position[4], rotation[4], velocity[4], spin[4];
    u8 pad40[2], activated, pad43[5];
    float angleX, angleZ, random0;
    u8 flags54, flags55, hopLength, hopRemaining;
    float random1;
    PickupMoby *surface, *target;
    float acceleration, initialHeight;
} BoltVars;
struct PickupMoby {
    u8 pad00[0x10]; float position[4];
    u8 state, pad21[3]; char *pClass;
    u8 pad28[4]; float scale;
    u8 renderDistance, visible; u16 updateDistance, flags;
    u8 pad36[0x2D]; u8 opacity; u8 pad64[4]; BoltVars *pVars;
    u8 pad6C[0x3E]; u16 classId; u8 flagsAC[4]; u8 uid; u8 padB1; s16 mission;
    u8 padB4[0xC]; float orientation[12];
};
typedef struct {
    float position[4];
    u8 pad90[0x50]; float boltTarget[4];
    u8 padF0[0x60]; float velocity[4];
    u8 pad160[0x170]; float cameraPosition[4];
    u8 pad2E0[0x1FB0]; PickupMoby *moby;
    u8 pad2294[0x210]; float pickupRadius, pickupHeight;
    u8 pad24AC[0x20]; int magnetEnabled;
} BoltHeroMotion;
typedef struct {
    float matrix[16], rotation[4];
    u8 pad50[0x30]; BoltHeroMotion motion;
} BoltHero;
typedef struct {
    u8 pad00[0x18]; PickupMoby *surface; u8 pad1C[4];
    float position[4]; u8 pad30[0x10]; float normal[4];
} BoltCollision;
extern BoltHero g_hero_state;
extern BoltCollision g_collision_hit;
extern char g_render_command_flags[] __attribute__((sda));
extern char g_moby_group_flags[];
/* Only the prefix is fixed here; collection entries continue after it. */
typedef struct { u8 prefix[0x464]; u8 collected[0]; } BoltCollectionTable;
extern BoltCollectionTable g_bolt_collection_table, g_bolt_collection_checkpoint;
/* The 0x40-byte player-stat block is saved/restored by func_002DE990. */
typedef struct { int bolts; u8 prefix[0x18]; int pendingBolts; u8 suffix[0x20]; } BoltPlayerStats;
extern BoltPlayerStats g_player_bolts __attribute__((sda));
typedef struct { PickupMoby *start, *end, *active; void *aux; } BoltMobyPool;
extern BoltMobyPool g_moby_pool_end __attribute__((sda));
extern char *g_moby_light_color SDATA(D_001AE8E0);
extern char *D_001B1B60_gp SDATA(D_001B1B60);
extern int g_current_map_index SDATA(D_001A79F0);
extern float g_moby_scale_mult_a SDATA(D_001AE8B0), g_moby_scale_mult_b SDATA(D_001AE8B4);
extern float g_moby_scale_mult_c SDATA(D_001AE8B8), g_moby_scale_mult_d SDATA(D_001AE8BC);
extern float g_moby_scale_mult_e SDATA(D_001AE8C0), g_moby_scale_mult_f SDATA(D_001AE8C4), g_moby_scale_mult_g SDATA(D_001AE8C8);
extern int math_random_int_below(int);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern int CollLine(void *,void *,int,int,int);
extern void vec_clear_128(void *);
extern float mat_fast_helper_a(float,float),vec_length_xy(void *),vec_distance_xy(void *,void *),FastVecLength(void *),math_fabs(float);
extern char *moby_get_private_value_2(void *);
extern int moby_get_attachment_rotation_angles(void *,void *,void *,void *,void *,void *);
extern float math_random_angle(void),math_random_float_range(float,float),IntToFloat(int);
extern int FloatToInt(float);
extern void moby_set_light_color(void *,void *),get_moby_color(void *,int *,int *,int *);
extern void gfx_pack_render_command_fields(void *,int,int,int,int),set_moby_color(void *,int,int,int);
extern void quaternion_to_rotation_basis(void *,void *),multiply_matrix3x3(void *,void *,void *),vec_fast_normalize(void *,void *,void *);
extern int coll_test_point(void *,int,void *,float),GetCollHitMaterial(void);
extern void mat_get_euler_angles(void *,void *),mat_build_rotation_from_angles(void *,void *);
extern void func_00301F18(void *,void *,int);
extern void vec_fast_normalize3(void *,void *,void *,float),lerp_vector(void *,void *,void *,float);
extern int pickup_start_fly_to_target_pal(void *,void *,float,float);
extern void moby_mark_spawned(void *),part_spawn_trail_puff_pal(void *,int),transform_vector(void *,void *,void *);
extern void vec_clamp_length(void *,float), matrix_mul_vec3(void *,void *,void *), euler_rotation_basis(void *,void *);
extern f32 ApproachValue(void *,float,float);
extern void CollectBolts_pal(void *);
extern int PlayMobySound(int,int,void *);

/* Update a bolt pickup through initialization, falling, hopping, idle and collection. */
void UpdateBoltPickupMoby_pal(PickupMoby *pickup)
{
    /* The matrix scratch overlaps vectors used in mutually exclusive states. */
    union {
        struct { float vector[4], other[4], basis[12]; } ground;
        struct { float basis[12], offset[4], angles[4]; } attract;
    } scratch;
    float matrix[12];
    int color_r,color_g,color_b;
    BoltVars *vars=pickup->pVars;
    switch(pickup->state) {
    case 0: {
        int collided;
        pickup->state=3;
        pickup->opacity=20;
        pickup->flags|=0x100;
        pickup->renderDistance=32;
        pickup->updateDistance=32;
        if(!math_random_int_below(2)) vars->flags55|=1;
        vec_scale_to_length(scratch.ground.vector,&pickup->orientation[8],0.2f);
        FastVecAdd(scratch.ground.vector,scratch.ground.vector,&pickup->position[0]);
        vec_scale_to_length(scratch.ground.other,&pickup->orientation[8],-3.0f);
        FastVecAdd(scratch.ground.other,scratch.ground.other,&pickup->position[0]);
        collided=CollLine(scratch.ground.vector,scratch.ground.other,0x22,0,0);
        if(!vars->flags54&&collided) {
            qcopy_nc(vars->position,&g_collision_hit.position[0]);
            vec_clear_128(&vars->rotation[0]);
            vars->rotation[2]=mat_fast_helper_a(g_collision_hit.normal[0],g_collision_hit.normal[1]);
            vars->rotation[1]=mat_fast_helper_a(g_collision_hit.normal[2],vec_length_xy(&g_collision_hit.normal[0]));
            if(g_collision_hit.surface&&moby_get_private_value_2(g_collision_hit.surface)) {
                PickupMoby *surface=g_collision_hit.surface;
                vars->surface=surface;
                moby_get_attachment_rotation_angles(pickup,surface,vars->position,&vars->rotation[0],vars->position,&vars->rotation[0]);
            }
        }
        else {
            qcopy_nc(vars->position,&pickup->position[0]);
            vec_clear_128(&vars->rotation[0]);
        }
        vars->random0=math_random_angle();
        vars->random1=math_random_angle();
        vars->initialHeight=pickup->position[2];
        moby_set_light_color(pickup,g_moby_light_color);
        get_moby_color(pickup,&color_r,&color_g,&color_b);
        gfx_pack_render_command_fields(pickup,0,13,0,0);
        set_moby_color(pickup,color_r,color_g,color_b);
        switch((s16)(pickup->classId-13)) {
        case 0:pickup->scale=F(pickup->pClass,0x24)*g_moby_scale_mult_a;
            break;
        case 1:pickup->scale=F(pickup->pClass,0x24)*g_moby_scale_mult_b;
            break;
        case 2:pickup->scale=F(pickup->pClass,0x24)*g_moby_scale_mult_c;
            break;
        case 3:pickup->scale=F(pickup->pClass,0x24)*g_moby_scale_mult_d;
            break;
        case 4:pickup->scale=F(pickup->pClass,0x24)*g_moby_scale_mult_e;
            break;
        case 5:pickup->scale=F(pickup->pClass,0x24)*g_moby_scale_mult_f;
            break;
        case 6:pickup->scale=F(pickup->pClass,0x24)*g_moby_scale_mult_g;
            break;
        }
        break;
    }
    case 1: {
        float distance, t;
        distance=vec_distance_xy(&pickup->position[0],&g_hero_state.motion.position[0]);
        if(!vars->activated&&distance<g_hero_state.motion.pickupRadius&&math_fabs(pickup->position[2]-g_hero_state.motion.position[2])<g_hero_state.motion.pickupHeight) vars->activated=1;
        vars->velocity[2]-=0.0043200003f;
        FastVecAdd(&pickup->position[0],&pickup->position[0],&vars->velocity[0]);
        quaternion_to_rotation_basis(&vars->spin[0],scratch.ground.basis);
        multiply_matrix3x3(&pickup->orientation[0],scratch.ground.basis,&pickup->orientation[0]);
        if(pickup->position[2]<vars->initialHeight-2.0f&&pickup->position[2]<g_hero_state.motion.position[2]-2.0f) {
            t=math_random_float_range(-15.0f,15.0f);
            pickup_start_fly_to_target_pal(pickup,g_hero_state.motion.moby,t*0.017453294f,0);
            goto sparkle;
        }
        if(coll_test_point(&pickup->position[0],0x22,pickup,0.25f)) {
            qcopy_nc(vars->position,&g_collision_hit.position[0]);
            vec_clear_128(&vars->rotation[0]);
            vars->rotation[2]=mat_fast_helper_a(g_collision_hit.normal[0],g_collision_hit.normal[1]);
            vars->rotation[1]=mat_fast_helper_a(g_collision_hit.normal[2],vec_length_xy(&g_collision_hit.normal[0]));
            FastVecSub(scratch.ground.vector,&pickup->position[0],&g_collision_hit.position[0]);
            vec_fast_normalize(&vars->velocity[0],&vars->velocity[0],scratch.ground.vector);
            if(g_hero_state.motion.magnetEnabled && (vars->activated ||
            (vec_distance_xy(&pickup->position[0],&g_hero_state.motion.position[0]) < g_hero_state.motion.pickupRadius &&
            math_fabs(pickup->position[2]-g_hero_state.motion.position[2]) < g_hero_state.motion.pickupHeight) ||
            GetCollHitMaterial() != -1)) {
                vec_scale_to_length(&vars->velocity[0],&vars->velocity[0],0.16000001f);
                pickup_start_fly_to_target_pal(pickup,g_hero_state.motion.moby,0,0);
            }
            else if(mat_fast_helper_a(scratch.ground.vector[2],vec_length_xy(scratch.ground.vector))<0.78539824f&&mat_fast_helper_a(g_collision_hit.normal[2],vec_length_xy(&g_collision_hit.normal[0]))<0.78539824f) {
                pickup->state=2;
                vars->hopLength=vars->hopRemaining=FloatToInt((math_random_float_range(30,40)*5.0f+2.0f)*0.16666667f);
                if(g_collision_hit.surface&&moby_get_private_value_2(g_collision_hit.surface)) {
                    PickupMoby *surface=g_collision_hit.surface;
                    vars->surface=surface;
                    moby_get_attachment_rotation_angles(pickup,surface,vars->position,&vars->rotation[0],vars->position,&vars->rotation[0]);
                }
                mat_get_euler_angles(&pickup->orientation[0],scratch.ground.other);
                mat_build_rotation_from_angles(&vars->spin[0],scratch.ground.other);
            }
        }
        goto sparkle;
    }
    case 2: {
        float distance, r, s;
        distance=vec_distance_xy(&pickup->position[0],&g_hero_state.motion.position[0]);
        if(!vars->activated&&distance<g_hero_state.motion.pickupRadius&&math_fabs(pickup->position[2]-g_hero_state.motion.position[2])<g_hero_state.motion.pickupHeight)vars->activated=1;
        func_00301F18(pickup,scratch.ground.other,0);
        scratch.ground.other[2]+=0.25f;
        mat_get_euler_angles(&pickup->orientation[0],scratch.ground.vector);
        mat_build_rotation_from_angles(scratch.ground.basis,scratch.ground.vector);
        r=1.0f/
        IntToFloat(vars->hopRemaining);
        s=IntToFloat(vars->hopRemaining) / IntToFloat(vars->hopLength);
        vec_fast_normalize3(&vars->spin[0],&vars->spin[0],scratch.ground.basis,r);
        lerp_vector(&pickup->position[0],&pickup->position[0],scratch.ground.other,s);
        s-=0.5f;
        pickup->position[2]+=(0.25f-s*s)*0.025f*vars->hopLength;
        quaternion_to_rotation_basis(&vars->spin[0],&pickup->orientation[0]);
        if(--vars->hopRemaining==0){
            pickup->state=3;
            vars->hopLength=vars->hopRemaining=FloatToInt((math_random_float_range(10,20)*5.0f+2.0f)*0.16666667f);
        }
        goto sparkle;
    }
    case 3: {
        int v;
        BoltHeroMotion *motion = &g_hero_state.motion;
        float distance, s;
        distance=vec_distance_xy(&pickup->position[0],motion->position);
        if(vars->activated || (distance<g_hero_state.motion.pickupRadius&&math_fabs(pickup->position[2]-g_hero_state.motion.position[2])<g_hero_state.motion.pickupHeight)) {
            pickup_start_fly_to_target_pal(pickup,motion->moby,0,0);
        }
        else if((u32)D_001B1B60_gp<(u32)pickup&&distance>32.0f&&!pickup->visible) {
            switch((s16)(pickup->classId-13)) {
            default:case 0:v=1;
                break;
            case 1:v=5;
                break;
            case 2:v=20;
                break;
            case 3:v=50;
                break;
            case 4:v=100;
                break;
            case 5:v=500;
                break;
            case 6:v=1000;
                break;
            }
            g_player_bolts.pendingBolts+=v;
            moby_mark_spawned(pickup);
            return;
        }
        else {
            if(pickup->visible||vars->surface) {
                func_00301F18(pickup,0,0);
                if(vars->hopRemaining){
                    s=IntToFloat(vars->hopRemaining) / IntToFloat(vars->hopLength);
                    s-=0.5f;
                    pickup->position[2]+=(0.25f-s*s)*0.0125f*vars->hopLength;
                    --vars->hopRemaining;
                }
            }
            else if(vars->hopRemaining)--vars->hopRemaining;
        }
    sparkle:
        if(pickup->visible)part_spawn_trail_puff_pal(pickup,1);
        break;
    }
    case 4: {
        int v;
        float speed;
        float t, s;
        v=0;
        if((s16)vars->target->classId==0){
            FastVecSub(scratch.ground.vector,&pickup->position[0],&g_hero_state.motion.cameraPosition[0]);
            transform_vector(scratch.ground.vector,scratch.ground.vector,&g_hero_state.rotation[0]);
            if(scratch.ground.vector[2]<0)v=1;
        }
        if(v){
            vec_scale_to_length(scratch.ground.vector,&g_hero_state.matrix[8],0.16000001f);
            FastVecSub(scratch.ground.other,scratch.ground.vector,&vars->velocity[0]);
            vec_clamp_length(scratch.ground.other,0.020000001f);
            FastVecAdd(&vars->velocity[0],&vars->velocity[0],scratch.ground.other);
        }
        else {
            t=0.0096f;
            if(FastVecLength(&vars->velocity[0])>t){
                vec_scale_to_length(scratch.ground.vector,&vars->velocity[0],t);
                FastVecSub(&vars->velocity[0],&vars->velocity[0],scratch.ground.vector);
            }
            ApproachValue(&vars->acceleration,0.64000005f,t);
        }
        speed=FastVecLength(&g_hero_state.motion.velocity[0]);
        if(speed>0.080000006f){
            vec_scale_to_length(scratch.ground.vector,&g_hero_state.motion.velocity[0],speed-0.080000006f);
            FastVecAdd(&pickup->position[0],&pickup->position[0],scratch.ground.vector);
        }
        quaternion_to_rotation_basis(&vars->spin[0],scratch.attract.basis);
        multiply_matrix3x3(&pickup->orientation[0],scratch.attract.basis,&pickup->orientation[0]);
        FastVecAdd(&pickup->position[0],&pickup->position[0],&vars->velocity[0]);
        if((s16)vars->target->classId==0)FastVecSub(scratch.attract.offset,&g_hero_state.motion.boltTarget[0],&pickup->position[0]);
        else FastVecSub(scratch.attract.offset,vars->target->position,&pickup->position[0]);
        if(FastVecLength(scratch.attract.offset)>vars->acceleration) {
            if(vars->angleZ!=0||vars->angleX!=0){
                matrix_mul_vec3(scratch.attract.offset,scratch.attract.offset,&g_hero_state.rotation[0]);
                s=mat_fast_helper_a(scratch.attract.offset[0],scratch.attract.offset[1]);
                vec_clear_128(scratch.attract.angles);
                scratch.attract.angles[1]=vars->angleX;
                if(s<1.5707964f&&s>-1.5707964f)scratch.attract.angles[1]=-scratch.attract.angles[1];
                scratch.attract.angles[2]=vars->angleZ;
                euler_rotation_basis(matrix,scratch.attract.angles);
                matrix_mul_vec3(scratch.attract.offset,scratch.attract.offset,matrix);
                matrix_mul_vec3(scratch.attract.offset,scratch.attract.offset,g_hero_state.matrix);
            }
            vec_scale_to_length(scratch.attract.offset,scratch.attract.offset,vars->acceleration);
            FastVecAdd(&pickup->position[0],&pickup->position[0],scratch.attract.offset);
            goto sparkle_attract;
        }
        {
            CollectBolts_pal(pickup);
            PlayMobySound(0,32,pickup);
            if(pickup<g_moby_pool_end.start){
                g_bolt_collection_table.collected[pickup->mission]=pickup->uid+2;
                {
                    int uid = pickup->uid;
                    if (uid != 255) {
                        int index = uid & 255;
                        if (B(g_render_command_flags, index) & 128)
                            goto delete_pickup;
                        {
                            int row = 16 * g_current_map_index;
                            if (!(B(g_moby_group_flags, index + row) & 128))
                                goto delete_pickup;
                        }
                    }
                    g_bolt_collection_checkpoint.collected[pickup->mission] = uid + 2;
                }
            }
        delete_pickup:
            moby_mark_spawned(pickup);
            goto done;
        }
        break;
    }
    }
    return;
sparkle_attract:
    if(pickup->visible)part_spawn_trail_puff_pal(pickup,0);
done:;
}
