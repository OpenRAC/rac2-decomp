#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern float g_vehicle_lean_rate __attribute__((sda));
extern float g_vehicle_drag_coeff __attribute__((sda));
extern float g_vehicle_ground_friction __attribute__((sda));
extern float g_vehicle_l30_speed_limit __attribute__((sda));
extern float g_vehicle_lean_scale __attribute__((sda));
extern float g_vehicle_l30_turn_rate __attribute__((sda));
extern float g_vehicle_tilt_y_rate __attribute__((sda));
extern float g_vehicle_l30_hover_spring __attribute__((sda));
extern float g_vehicle_l30_bob_amplitude __attribute__((sda));
extern float g_vehicle_pitch_rate_idle __attribute__((sda));
extern float g_vehicle_air_friction __attribute__((sda));
extern float g_vehicle_steer_scale __attribute__((sda));
extern float g_vehicle_l30_max_speed __attribute__((sda));
extern float g_vehicle_l30_min_speed __attribute__((sda));
extern float g_vehicle_amount_scale __attribute__((sda));
extern float g_vehicle_pitch_rate_moving __attribute__((sda));
extern float g_vehicle_speed_blend __attribute__((sda));
extern float g_vehicle_l30_vertical_damping __attribute__((sda));
extern float g_vehicle_bob_speed __attribute__((sda));
extern float g_vehicle_l30_probe_radius __attribute__((sda));
extern float g_vehicle_l30_ground_offset __attribute__((sda));
extern float g_vehicle_input_z_scale __attribute__((sda));
extern float g_vehicle_l30_gravity __attribute__((sda));
extern float g_vehicle_hover_height __attribute__((sda));
extern float g_vehicle_contact_damage __attribute__((sda));
extern float g_vehicle_tilt_x_degrees __attribute__((sda));
extern float g_vehicle_hit_damage __attribute__((sda));
extern float g_vehicle_radius_scale __attribute__((sda));
extern float g_vehicle_lean_blend __attribute__((sda));
extern float g_vehicle_start_health __attribute__((sda));
extern float g_vehicle_l30_velocity_damping __attribute__((sda));
extern float g_vehicle_tilt_z_rate __attribute__((sda));
extern float g_vehicle_pickup_distance __attribute__((sda));
extern float g_vehicle_reverse_scale __attribute__((sda));
extern int g_vehicle_idle_anim __attribute__((sda));
extern int g_vehicle_current_anim __attribute__((sda));
extern char * part_find_owned_effect_slot(void *,int,int);
extern float func_002A0558(void *,void *);
extern int TryClaimNotice(int,int,int);
extern s32 func_PAL_L00_002C4480(int,int);
extern void set_hero_animation_pal(int,int,float);
extern float FastVecLength(void *);
extern float FastAddRotations(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fabs(float);
extern float IntegerPower(int,float);
extern void FastVecAdd(void *,void *,void *);
extern float coll_probe_ground_height_below(void *,int,float);
extern float fast_subtract_rotations(float,float);
extern void FastVecScale(void *,void *,float);
extern void part_spawn_spark_effect_pal(void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern void mat_get_euler_angles(void *,void *);
extern void matrix_from_basis_rows(void *,void *);
extern void transform_vector(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void make_hit_descriptor(void *,void *,int,void *,float);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void FastVecSub(void *,void *,void *);
extern int coll_test_point(void *,int,void *,float);
extern float FastVecDot(void *,void *);
extern int coll_process_hit(void *,int,void *,void *,float);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,float,float,float);
extern void gfx_add_draw_callback_first(void (*)(char *),void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern void hover_read_inputs_basic(float *,float *,float *,float *);
extern void hud_draw_vehicle_gauges_pal(char *);
typedef struct {
    char pad00[0x80]; Vec position, rotation;
    char padA0[0x1830-0xA0]; void *vehicle;
    char pad1834[0x2290-0x1834]; char *moby; int mode;
} Hero;
typedef struct { char pad[0x18]; char *hit; int count; Vec vector, point, normal; } Collision;
extern Hero g_hero_state NOT_SDA;
extern Collision g_collision_l30_result NOT_SDA;
extern char g_held_object_ptr[] NOT_SDA;
extern int g_pad_held_flags NOT_SDA;
extern char g_camera_l30_position[] NOT_SDA;
typedef struct { char pad[0x10]; int flags; char pad14[0x10]; float radius; } MobyClass;
typedef struct {
    Vec velocity, other;
    float lean, pitch, heading;
    float gap2C[3];
    float phase, bob, tiltX, tiltY, baseHeight, throttle, health;
} HoverState;
typedef struct {
    char pad00[0x10]; Vec position;
    u8 state; char pad21[3]; MobyClass *mclass;
    char pad28[4]; float radius;
    u8 pad30, interaction; char pad32[0x68-0x32];
    HoverState *data; char pad6C[3]; u8 touchTimer;
    char pad70[0x98-0x70]; int flags;
    char pad9C[0xA8-0x9C]; u8 damageFlag;
    char padA9[0xC0-0xA9]; Vec basis[3]; Vec rotation;
} HoverMoby;

void func_PAL_L30_003B7808(HoverMoby *obj) {
    struct {
        Vec dir, accel, old;
        Vec matrix[4];
        Vec pos;
        union { Vec inverse[4]; struct { Vec delta, normal; } contact; } scratch;
    } frame;
    struct { float x,y,z,w; int active; } in;
    float limit, speed, cap, sign, thrust, height, target;
    HoverState *st=obj->data;
    char *hit;
    if (obj->state) {
        obj->position.f[2]=st->baseHeight;
        hit=part_find_owned_effect_slot(obj,0x30001,0);
        if (hit && P(hit,0x20) && *(short *)(P(hit,0x20)+0xAA)!=0x853) {
            st->health-=F(hit,0x2c);
            if(st->health<=0) obj->state=5;
        }
        obj->damageFlag=255;
    } else {
        st->baseHeight=obj->position.f[2];
    }
    {
        MobyClass *cls=obj->mclass;
        in.active=0;
        obj->radius=cls->radius*g_vehicle_radius_scale;
    }
    switch(obj->state) {
    case 0:
        qzero(st);
        st->health=g_vehicle_start_health;
        obj->state=1;
        break;
    case 1:
        if(func_002A0558(obj,g_hero_state.moby)<g_vehicle_pickup_distance && g_hero_state.mode!=0x31) {
            int request = TryClaimNotice(7,0x12EA,1)!=0;
            if(g_pad_held_flags&16) in.active=request;
        }
        if(in.active) {
            func_PAL_L00_002C4480(0x31,0);
            set_hero_animation_pal(g_vehicle_idle_anim,0,15.0f);
            qcopy_nc(&g_hero_state.rotation,&obj->rotation);
            qcopy_nc(&g_hero_state.position,&obj->position);
            g_hero_state.vehicle=obj;
            obj->state=3;
            I(g_hero_state.moby,0x9c)=-1;
        }
        /* fall through */
    case 3:
        obj->flags=0;
        in.w=in.z=in.y=in.x=0.0f;
        if(obj->state==3) {
            if(g_vehicle_current_anim!=g_vehicle_idle_anim)set_hero_animation_pal(g_vehicle_idle_anim,0,15.0f);
            hover_read_inputs_basic(&in.x,&in.y,&in.z,&in.w);
        }
        st->throttle=in.y;
        in.z*=0.01745329424738884f;
        in.z*=g_vehicle_input_z_scale;
        speed=FastVecLength(st);
        cap=g_vehicle_l30_max_speed*(0.020000001f);
        limit=g_vehicle_l30_speed_limit*(0.020000001f);
        {
            float amount=in.x*((speed<limit?speed:limit)/limit*g_vehicle_speed_blend+(1-g_vehicle_speed_blend));
            amount*=0.0003490659f;
            st->heading=FastAddRotations(st->heading,g_vehicle_l30_turn_rate*amount);
        }
        {
            float rad=in.x*0.01745329424738884f;
            float lean=g_vehicle_lean_scale*rad;
            lean*=g_vehicle_lean_blend*in.y+(1-g_vehicle_lean_blend);
            st->lean+=(lean-obj->rotation.f[0])*g_vehicle_lean_rate;
        }
        frame.dir.f[0]=math_fast_sin_or_cos_a(st->heading);
        frame.dir.f[1]=math_fast_sin_or_cos_b(st->heading);
        frame.dir.f[2]=0;
        if(in.y<0)in.y*=g_vehicle_reverse_scale;
        sign=1.0f;
        if(in.y<0) sign=-1.0f;
        {
            float magnitude=math_fabs(in.x), throttle=IntegerPower(2,(cap-speed)/cap);
            float amount=in.y+g_vehicle_steer_scale*magnitude*sign;
            amount*=0.00040000002f;
            amount*=g_vehicle_amount_scale;
            thrust=amount*throttle;
        }
        FastVecAdd(&frame.old,&obj->position,st);
        height=coll_probe_ground_height_below(&frame.old,0,0.5f);
        st->velocity.f[2]-=g_vehicle_l30_gravity*0.00040000002f;
        if(height!=0) {
            target=height+g_vehicle_hover_height;
            if(target<frame.old.f[2]) {
                st->pitch=FastAddRotations(st->pitch,fast_subtract_rotations(in.z,st->pitch)*g_vehicle_pitch_rate_idle);
                goto physics;
            } else if(frame.old.f[2]+0.1f<height) {
                frame.old.f[2]=height;
                FastVecScale(st,st,g_vehicle_air_friction);
            } else {
                st->velocity.f[2]+=((target-frame.old.f[2])*g_vehicle_l30_hover_spring-st->velocity.f[2])*g_vehicle_l30_hover_spring;
            }
            part_spawn_spark_effect_pal(&g_collision_l30_result.vector,obj->basis,speed*0.9f);
            if(in.w>0) {
                float drag=1-g_vehicle_drag_coeff*in.w;
                st->velocity.f[0]*=drag;
                st->velocity.f[1]*=drag;
            }
            {
                Vec *right=&frame.matrix[0], *up, *ahead=&frame.matrix[2];
                vec_scale_to_length(ahead,&g_collision_l30_result.normal,1.0f);
                up=&frame.matrix[1];
                FastVecCross(up,obj->basis,ahead);
                FastVecCross(right,up,ahead);
            }
            qzero_nc(&frame.matrix[3]);
            mat_get_euler_angles(&frame.matrix[0],&frame.pos);
            st->pitch=FastAddRotations(st->pitch,fast_subtract_rotations(FastAddRotations(-frame.pos.f[1],in.z),st->pitch)*g_vehicle_pitch_rate_moving);
            FastVecScale(st,st,g_vehicle_l30_velocity_damping);
            matrix_from_basis_rows(frame.scratch.inverse,obj->basis);
            transform_vector(st,st,frame.scratch.inverse);
            st->velocity.f[1]*=g_vehicle_l30_vertical_damping;
            matrix_mul_vec3(st,st,obj->basis);
            vec_scale_to_length(&frame.accel,obj->basis,thrust);
            FastVecAdd(st,st,&frame.accel);
        }
physics:
        make_hit_descriptor(&frame.matrix[0],obj,0x10000,st,g_vehicle_hit_damage);
        qcopy_nc(&obj->position,&frame.old);
        moby_transform_joint_to_world(obj,0,&frame.matrix[3]);
        frame.matrix[3].f[2]+=g_vehicle_l30_probe_radius;
        FastVecSub(&frame.pos,&obj->position,&frame.matrix[3]);
        if(coll_test_point(&frame.matrix[3],0,obj,g_vehicle_l30_probe_radius) && g_collision_l30_result.hit!=g_hero_state.moby) {
            FastVecAdd(&obj->position,&g_collision_l30_result.point,&frame.pos);
            FastVecCross(&frame.scratch.contact.normal,&g_collision_l30_result.normal,st);
            FastVecCross(&frame.scratch.contact.delta,&frame.scratch.contact.normal,&g_collision_l30_result.normal);
            vec_scale_to_length(&frame.scratch.contact.delta,&frame.scratch.contact.delta,1.0f);
            vec_scale_to_length(st,&frame.scratch.contact.delta,FastVecDot(st,&frame.scratch.contact.delta));
            FastVecScale(st,st,g_vehicle_ground_friction);
            part_spawn_spark_effect_pal(&g_collision_l30_result.vector,obj->basis,0.0f);
        }
        speed = FastVecLength(st);
        if(g_vehicle_l30_min_speed*(0.020000001f)<speed) {
            frame.matrix[3].f[2]+=g_vehicle_l30_ground_offset;
            coll_process_hit(&frame.matrix[3],0,obj,&frame.matrix[0],g_vehicle_l30_probe_radius);
            moby_transform_joint_to_world(obj,3,&frame.scratch.contact.delta);
            coll_process_hit(&frame.scratch.contact.delta,0,obj,&frame.matrix[0],g_vehicle_contact_damage);
        }
        if(!in.active && P(g_held_object_ptr,0)==obj && (g_pad_held_flags&16))obj->state=4;
        break;
    case 4:
        obj->flags=obj->mclass->flags;
        I(g_hero_state.moby,0x9c)=0;
        func_PAL_L00_002C4480(0,1);
        g_hero_state.vehicle=0;
        obj->state=1;
        break;
    case 5:
        obj->flags=obj->mclass->flags;
        I(g_hero_state.moby,0x9c)=0;
        func_PAL_L00_002C4480(0,1);
        moby_transform_joint_to_world(obj,0,&frame.dir);
        SpawnExplosionEffects_pal(obj,st,&frame.dir,0.0f,0.0f,10,3,16,4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,1,-1,0,0x810001);
        moby_mark_spawned(obj);
        return;
    case 2:
    case 6:
        break;
    }
    st->baseHeight=obj->position.f[2];
    st->phase=FastAddRotations(st->phase,g_vehicle_bob_speed*0.0003490659f);
    st->bob=math_fast_sin_or_cos_b(st->phase)*g_vehicle_l30_bob_amplitude;
    obj->position.f[2]+=st->bob;
    moby_scale_owner_words_by_angles(obj,&st->tiltX,&st->tiltY,g_vehicle_tilt_x_degrees*0.01745329424738884f,g_vehicle_tilt_y_rate*0.0003490659f,g_vehicle_tilt_z_rate*0.0003490659f);
    obj->rotation.f[2]=st->heading;
    obj->rotation.f[0]=FastAddRotations(obj->rotation.f[0],st->lean);
    obj->rotation.f[1]=FastAddRotations(obj->rotation.f[1],st->pitch);
    if(obj->state==3) {
        moby_transform_joint_to_world(obj,1,&g_hero_state.position);
        qcopy_nc(&g_hero_state.rotation,&obj->rotation);
        gfx_add_draw_callback_first(hud_draw_vehicle_gauges_pal,obj);
    }
    obj->flags=obj->mclass->flags;
    if(obj->interaction && fast_vec_dist(&obj->position,g_camera_l30_position)<64.0f) {
        moby_update_ground_check(obj);
        obj->touchTimer=60;
    }
}
