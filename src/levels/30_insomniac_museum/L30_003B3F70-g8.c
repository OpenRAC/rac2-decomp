/* func_L30_003B3F70 updates a rideable hover moby: the prompt and boarding, turning, leaning,
 * thrust, ground height and collision, then the bobbing that runs in every state.
 * It needs -G8 for its small data, -ffast-math for min.s, and -g for the line label before
 * the first div.s, whose nop pair therefore depends on which statements share a source line. */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern float D_L30_001AF8EC __attribute__((sda));
extern float D_L30_001AF914 __attribute__((sda));
extern float D_L30_001AF8E4 __attribute__((sda));
extern float D_L30_001AF910 __attribute__((sda));
extern float D_L30_001AF8F0 __attribute__((sda));
extern float D_L30_001AF8B8 __attribute__((sda));
extern float D_L30_001AF8B0 __attribute__((sda));
extern float D_L30_001AF8D0 __attribute__((sda));
extern float D_L30_001AF8A4 __attribute__((sda));
extern float D_L30_001AF904 __attribute__((sda));
extern float D_L30_001AF8E8 __attribute__((sda));
extern float D_L30_001AF8F8 __attribute__((sda));
extern float D_L30_001AF8C8 __attribute__((sda));
extern float D_L30_001AF960 __attribute__((sda));
extern float D_L30_001AF8C4 __attribute__((sda));
extern float D_L30_001AF900 __attribute__((sda));
extern float D_L30_001AF90C __attribute__((sda));
extern float D_L30_001AF8C0 __attribute__((sda));
extern float D_L30_001AF8A8 __attribute__((sda));
extern float D_L30_001AF8D4 __attribute__((sda));
extern float D_L30_001AF95C __attribute__((sda));
extern float D_L30_001AF908 __attribute__((sda));
extern float D_L30_001AF8E0 __attribute__((sda));
extern float D_L30_001AF8CC __attribute__((sda));
extern float D_L30_001AF958 __attribute__((sda));
extern float D_L30_001AF8AC __attribute__((sda));
extern float D_L30_001AF954 __attribute__((sda));
extern float D_L30_001AF950 __attribute__((sda));
extern float D_L30_001AF8FC __attribute__((sda));
extern float D_L30_001AF964 __attribute__((sda));
extern float D_L30_001AF8BC __attribute__((sda));
extern float D_L30_001AF8B4 __attribute__((sda));
extern float D_L30_001AF8A0 __attribute__((sda));
extern float D_L30_001AF8F4 __attribute__((sda));
extern int D_L30_001AF8D8 __attribute__((sda));
extern int D_L30_001AF8DC __attribute__((sda));
extern char * part_find_owned_effect_slot(void *,int,int);
extern float func_002A0558(void *,void *);
extern int TryClaimNotice(int,int,int);
extern void hero_l00_set_action(int,int);
extern void set_hero_animation(int,int,float);
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
extern void part_spawn_spark_effect(void *,void *,float);
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
extern void coll_process_hit(void *,int,void *,void *,float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,float,float,float);
extern void gfx_add_draw_callback_first(void (*)(char *),void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern void hover_read_inputs_basic(float *,float *,float *,float *);
extern void hud_draw_vehicle_gauges(char *);
typedef struct {
    char pad00[0x80]; Vec position, rotation;
    char padA0[0x1830-0xA0]; void *vehicle;
    char pad1834[0x2290-0x1834]; char *moby; int mode;
} Hero;
typedef struct { char pad[0x18]; char *hit; int count; Vec vector, point, normal; } Collision;
extern Hero g_hero_state NOT_SDA;
extern Collision D_L30_001C0200 NOT_SDA;
extern char D_0018B650[] NOT_SDA;
extern int D_00138324 NOT_SDA;
extern char D_L30_001B9DC0[] NOT_SDA;

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
void UpdateHoverVehicleMoby(HoverMoby *obj) {
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
        if (hit && P(hit,0x20) && *(short *)(P(hit,0x20)+0xAA)!=0x853 /* moby class 2131 */) {
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
        obj->radius=cls->radius*D_L30_001AF950;
    }
    switch(obj->state) {
    case 0:
        qzero(st);
        st->health=D_L30_001AF964;
        obj->state=1;
        break;
    case 1:
        if(func_002A0558(obj,g_hero_state.moby)<D_L30_001AF8A0 && g_hero_state.mode!=0x31) {
            int request = TryClaimNotice(7,0x2798,1)!=0;
            if(D_00138324&16) in.active=request;
        }
        if(in.active) {
            hero_l00_set_action(0x31,0);
            set_hero_animation(D_L30_001AF8D8,0,15.0f);
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
            if(D_L30_001AF8DC!=D_L30_001AF8D8)set_hero_animation(D_L30_001AF8D8,0,15.0f);
            hover_read_inputs_basic(&in.x,&in.y,&in.z,&in.w);
        }
        st->throttle=in.y;
        in.z*=0.01745329424738884f;
        in.z*=D_L30_001AF908;
        speed=FastVecLength(st);
        cap=D_L30_001AF8C8*(1.0f/60.0f);
        limit=D_L30_001AF910*(1.0f/60.0f);
        {
            float amount=in.x*((speed<limit?speed:limit)/limit*D_L30_001AF90C+(1-D_L30_001AF90C));
            amount*=0.0002908882452175021f;
            st->heading=FastAddRotations(st->heading,D_L30_001AF8B8*amount);
        }
        {
            float rad=in.x*0.01745329424738884f;
            float lean=D_L30_001AF8F0*rad;
            lean*=D_L30_001AF8FC*in.y+(1-D_L30_001AF8FC);
            st->lean+=(lean-obj->rotation.f[0])*D_L30_001AF8EC;
        }
        frame.dir.f[0]=math_fast_sin_or_cos_a(st->heading);
        frame.dir.f[1]=math_fast_sin_or_cos_b(st->heading);
        frame.dir.f[2]=0;
        if(in.y<0)in.y*=D_L30_001AF8F4;
        sign=1.0f;
        if(in.y<0) sign=-1.0f;
        {
            float magnitude=math_fabs(in.x), throttle=IntegerPower(2,(cap-speed)/cap);
            float amount=in.y+D_L30_001AF8F8*magnitude*sign;
            amount*=0.00027777778450399637f;
            amount*=D_L30_001AF8C4;
            thrust=amount*throttle;
        }
        FastVecAdd(&frame.old,&obj->position,st);
        height=coll_probe_ground_height_below(&frame.old,0,0.5f);
        st->velocity.f[2]-=D_L30_001AF8E0*0.00027777778450399637f;
        if(height!=0) {
            target=height+D_L30_001AF8CC;
            if(target<frame.old.f[2]) {
                st->pitch=FastAddRotations(st->pitch,fast_subtract_rotations(in.z,st->pitch)*D_L30_001AF904);
                goto physics;
            } else if(frame.old.f[2]+0.1f<height) {
                frame.old.f[2]=height;
                FastVecScale(st,st,D_L30_001AF8E8);
            } else {
                st->velocity.f[2]+=((target-frame.old.f[2])*D_L30_001AF8D0-st->velocity.f[2])*D_L30_001AF8D0;
            }
            part_spawn_spark_effect(&D_L30_001C0200.vector,obj->basis,speed*0.9f);
            if(in.w>0) {
                float drag=1-D_L30_001AF914*in.w;
                st->velocity.f[0]*=drag;
                st->velocity.f[1]*=drag;
            }
            {
                Vec *right=&frame.matrix[0], *up, *ahead=&frame.matrix[2];
                vec_scale_to_length(ahead,&D_L30_001C0200.normal,1.0f);
                up=&frame.matrix[1];
                FastVecCross(up,obj->basis,ahead);
                FastVecCross(right,up,ahead);
            }
            qzero_nc(&frame.matrix[3]);
            mat_get_euler_angles(&frame.matrix[0],&frame.pos);
            st->pitch=FastAddRotations(st->pitch,fast_subtract_rotations(FastAddRotations(-frame.pos.f[1],in.z),st->pitch)*D_L30_001AF900);
            FastVecScale(st,st,D_L30_001AF8BC);
            matrix_from_basis_rows(frame.scratch.inverse,obj->basis);
            transform_vector(st,st,frame.scratch.inverse);
            st->velocity.f[1]*=D_L30_001AF8C0;
            matrix_mul_vec3(st,st,obj->basis);
            vec_scale_to_length(&frame.accel,obj->basis,thrust);
            FastVecAdd(st,st,&frame.accel);
        }
physics:
        make_hit_descriptor(&frame.matrix[0],obj,0x10000,st,D_L30_001AF954);
        qcopy_nc(&obj->position,&frame.old);
        moby_transform_joint_to_world(obj,0,&frame.matrix[3]);
        frame.matrix[3].f[2]+=D_L30_001AF8D4;
        FastVecSub(&frame.pos,&obj->position,&frame.matrix[3]);
        if(coll_test_point(&frame.matrix[3],0,obj,D_L30_001AF8D4) && D_L30_001C0200.hit!=g_hero_state.moby) {
            FastVecAdd(&obj->position,&D_L30_001C0200.point,&frame.pos);
            FastVecCross(&frame.scratch.contact.normal,&D_L30_001C0200.normal,st);
            FastVecCross(&frame.scratch.contact.delta,&frame.scratch.contact.normal,&D_L30_001C0200.normal);
            vec_scale_to_length(&frame.scratch.contact.delta,&frame.scratch.contact.delta,1.0f);
            vec_scale_to_length(st,&frame.scratch.contact.delta,FastVecDot(st,&frame.scratch.contact.delta));
            FastVecScale(st,st,D_L30_001AF8E4);
            part_spawn_spark_effect(&D_L30_001C0200.vector,obj->basis,0.0f);
        }
        speed = FastVecLength(st);
        if(D_L30_001AF960*(1.0f/60.0f)<speed) {
            frame.matrix[3].f[2]+=D_L30_001AF95C;
            coll_process_hit(&frame.matrix[3],0,obj,&frame.matrix[0],D_L30_001AF8D4);
            moby_transform_joint_to_world(obj,3,&frame.scratch.contact.delta);
            coll_process_hit(&frame.scratch.contact.delta,0,obj,&frame.matrix[0],D_L30_001AF958);
        }
        if(!in.active && P(D_0018B650,0)==obj && (D_00138324&16))obj->state=4;
        break;
    case 4:
        obj->flags=obj->mclass->flags;
        I(g_hero_state.moby,0x9c)=0;
        hero_l00_set_action(0,1);
        g_hero_state.vehicle=0;
        obj->state=1;
        break;
    case 5:
        obj->flags=obj->mclass->flags;
        I(g_hero_state.moby,0x9c)=0;
        hero_l00_set_action(0,1);
        moby_transform_joint_to_world(obj,0,&frame.dir);
        SpawnExplosionEffects(obj,st,&frame.dir,0.0f,0.0f,10,3,16,4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,1,-1,0,0x810001);
        moby_mark_spawned(obj);
        return;
    case 2:
    case 6:
        break;
    }
    st->baseHeight=obj->position.f[2];
    st->phase=FastAddRotations(st->phase,D_L30_001AF8A8*0.0002908882452175021f);
    st->bob=math_fast_sin_or_cos_b(st->phase)*D_L30_001AF8A4;
    obj->position.f[2]+=st->bob;
    moby_scale_owner_words_by_angles(obj,&st->tiltX,&st->tiltY,D_L30_001AF8AC*0.01745329424738884f,D_L30_001AF8B0*0.0002908882452175021f,D_L30_001AF8B4*0.0002908882452175021f);
    obj->rotation.f[2]=st->heading;
    obj->rotation.f[0]=FastAddRotations(obj->rotation.f[0],st->lean);
    obj->rotation.f[1]=FastAddRotations(obj->rotation.f[1],st->pitch);
    if(obj->state==3) {
        moby_transform_joint_to_world(obj,1,&g_hero_state.position);
        qcopy_nc(&g_hero_state.rotation,&obj->rotation);
        gfx_add_draw_callback_first(hud_draw_vehicle_gauges,obj);
    }
    obj->flags=obj->mclass->flags;
    if(obj->interaction && fast_vec_dist(&obj->position,D_L30_001B9DC0)<64.0f) {
        moby_update_ground_check(obj);
        obj->touchTimer=60;
    }
}
