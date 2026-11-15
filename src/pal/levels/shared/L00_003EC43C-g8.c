#include "include_asm.h"

#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
typedef struct { float f[4]; } __attribute__((aligned(16))) ChargeWeaponVec;
typedef struct {
char pad0[1888];
char camera[16];
char pad770[1160];
char * held;
char padbfc[1588];
int mask;
char pad1234[12];
int frame;
char pad1244[524];
char *selected;
char pad1454[3644];
char * player;
int mode;
char pad2298[36];
unsigned char locked;
char pad22bd[559];
short direction;
char pad24ee[70];
int timer;
} ChargeWeaponHero;
extern ChargeWeaponHero g_hero_state;
typedef struct { char pad[0x50]; float speed; char tail[0x8C]; } ChargeWeaponMaterial;
extern ChargeWeaponMaterial g_weapon_l00_table[];
typedef struct { char pad[0x1A0]; int pressed, released; } ChargeWeaponInput;
extern ChargeWeaponInput g_pad_state;
typedef struct { float values[18]; char pad[8]; ChargeWeaponVec a, b; char tail[16]; } ChargeWeaponEffect;
extern ChargeWeaponEffect D_L00_0024F7C0[];
extern char g_camera_l00_position[0x100];
extern unsigned char D_00139584 NOT_SDA;
typedef struct { int active; char gap[0x18]; float reticle; } ChargeWeaponEffects;
extern ChargeWeaponEffects D_L00_001B2B70 __attribute__((sda));
extern char *g_area_hit_targets[];
extern int D_L00_001B06D0 __attribute__((sda)), D_L00_001B06B8 __attribute__((sda)), D_L00_001B06D8 __attribute__((sda));
extern char *D_L00_001B06D4 __attribute__((sda));
extern float D_L00_001B06BC __attribute__((sda)), D_L00_001B06C0 __attribute__((sda)), D_L00_001B06C4 __attribute__((sda)), D_L00_001B06C8 __attribute__((sda)), D_L00_001B06CC __attribute__((sda));
extern void func_PAL_002A7E68(void *,int,int,int);
extern void AttachManipulator(void *,int,void *);
extern int AcquireEntitySlot(void *,int,void *);
extern int level_get_slot_body(int,int);
extern float math_random_signed_float_range(float,float), math_random_float_range(float,float);
extern void vec_clear_128(void *), sheepinator_clear_records(void);
extern void func_PAL_L00_002C4480(int,int);
extern int math_fast_float_d(void *), get_ammo(int);
extern void hud_add_moby_marker(void *,unsigned int,float,void *,float,int,int,float,int);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void vec_compute_object_to_target(char *,void *,void *,float);
extern char *part_start_effect_in_front_of_hero(void *,int,float,float,float,float,float);
extern char *moby_get_private_value_0(char *);
extern void cam_compute_view_direction(void *,void *,int),moby_forward_position_call(void *,void *,int);
extern void FastVecScale(void *,void *,float),FastVecAdd(void *,void *,void *);
extern float fast_vec_dist(void *,void *),math_fabs(float);
extern int vec_fast_helper_b(void *),sheepinator_is_mode_four(void),weapon_spend_ammo(int,int);
extern void PlayMobySound(int,int,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int coll_process_hit(void *,int,void *,int,float);
extern void FastVecSub(void *,void *,void *);
extern char *func_PAL_L00_003CF868(void *,int,void *,void *);
extern void ref_L00_003E8180_00(void *,void *),func_PAL_L00_003ECD58(void);
extern float fast_subtract_rotations(float,float),math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
typedef struct { float timer; int handle, anim, unknown; float charge, angle; char pad[8]; ChargeWeaponVec origin; float gap, sine, gap2, cosine; } ChargeWeaponVars;
typedef struct { char position[0x20]; unsigned char state; char pad21[0x22]; unsigned char animation; char pad44[0x1C]; unsigned char flags; char pad61[7]; ChargeWeaponVars *vars; } ChargeWeaponMoby;

void func_PAL_L00_003EC43C(ChargeWeaponMoby *obj) {
    ChargeWeaponVec velocity, origin, target, delta, point;
    int unused;
    char *hit = 0;
    ChargeWeaponVars *st = obj->vars;
    ChargeWeaponMaterial *material = &g_weapon_l00_table[D_00139584];
    float speed = material->speed * 0.020000001f;
    int i, enabled, count;
    switch (obj->state) {
    case 0: {
        int i;
        if (obj->animation != 0 || (obj->flags&2)) func_PAL_002A7E68(obj,1,0,0);
        AttachManipulator(obj,0,&st->origin);
        st->timer=0.36666667f;
        st->unknown=-1;
        st->charge=0;
        st->angle=0;
        obj->state=1;
        D_L00_001B2B70.reticle=-1.0f;
        D_L00_001B06D0=0;
        D_L00_001B06B8=0;
        st->handle=AcquireEntitySlot(obj,0,&unused);
        st->anim=level_get_slot_body(H(obj,0xAA),st->handle);
        for (i=0;i<4;i++) {
            D_L00_0024F7C0[i].values[0]=0; D_L00_0024F7C0[i].values[1]=0; D_L00_0024F7C0[i].values[2]=0;
            D_L00_0024F7C0[i].values[3]=math_random_signed_float_range(0.05f,0.3f);
            D_L00_0024F7C0[i].values[4]=math_random_signed_float_range(0.05f,0.3f);
            D_L00_0024F7C0[i].values[5]=math_random_signed_float_range(0.05f,0.3f);
            D_L00_0024F7C0[i].values[6]=math_random_float_range(0.25f,0.75f);
            D_L00_0024F7C0[i].values[7]=math_random_float_range(0.25f,0.75f);
            D_L00_0024F7C0[i].values[8]=math_random_float_range(0.25f,0.75f);
            D_L00_0024F7C0[i].values[9]=0; D_L00_0024F7C0[i].values[10]=0; D_L00_0024F7C0[i].values[11]=0;
            D_L00_0024F7C0[i].values[12]=math_random_signed_float_range(0.05f,0.3f);
            D_L00_0024F7C0[i].values[13]=math_random_signed_float_range(0.05f,0.3f);
            D_L00_0024F7C0[i].values[14]=math_random_signed_float_range(0.05f,0.3f);
            D_L00_0024F7C0[i].values[15]=math_random_float_range(0.25f,0.75f);
            D_L00_0024F7C0[i].values[16]=math_random_float_range(0.25f,0.75f);
            D_L00_0024F7C0[i].values[17]=math_random_float_range(0.25f,0.75f);
            vec_clear_128(&D_L00_0024F7C0[i].a);
            vec_clear_128(&D_L00_0024F7C0[i].b);
        }
        sheepinator_clear_records();
        break;
    }
    case 1:
        D_L00_001B2B70.reticle=-1;
        if (g_hero_state.selected) g_hero_state.held=g_hero_state.selected;
        if (!D_L00_001B06B8) D_L00_001B06B8=1;
        if (g_hero_state.mode==1) func_PAL_L00_002C4480(29,1);
        enabled=1;
        if (g_hero_state.mode==29) {
            if (!math_fast_float_d(&g_hero_state.timer)) enabled=0;
            {
                unsigned int color;
                if (st->timer!=0 && get_ammo(-1)) color=0x600000FF;
                else color=0x600FFF0F;
                hud_add_moby_marker(obj,color,1,0,0,38,-1,90,4);
            }
        } else g_hero_state.timer=33;
        moby_transform_joint_to_world(obj,0,&origin);
        if (g_hero_state.held) vec_compute_object_to_target(g_hero_state.held,&origin,&velocity,speed);
        else hit=part_start_effect_in_front_of_hero(&g_hero_state.camera,1,0.17453295f,0.17453295f,20,0.7853982448577881f,0.7853982448577881f);
        if (st->timer==0 && hit && get_ammo(-1)) {
            char *extra;
            /* The copy only writes target; no scalar local or source field aliases it. */
            qcopy_nc(&target,hit+0x10);
            extra=moby_get_private_value_0(hit);
            if (extra) {
                cam_compute_view_direction(hit+0x10,&delta,1);
                FastVecScale(&delta,&delta,F(extra,0x10));
                FastVecAdd(&target,&delta,hit+0x10);
            }
            {
                float scale=math_fabs(0.9f-fast_vec_dist(g_camera_l00_position,&target)*0.006666667f*0.65f);
                hud_add_moby_marker(obj,0xFF0FFF0F,scale,&target,0,38,-1,90,4);
            }
        }
        if (vec_fast_helper_b(st) && !g_hero_state.locked) {
            if ((g_pad_state.pressed&g_hero_state.mask) && enabled && !sheepinator_is_mode_four() && g_hero_state.frame>=19) {
                if (weapon_spend_ammo(-1,1)) {
                    D_L00_001B2B70.active=1;
                    PlayMobySound(2,0,obj);
                    switch (D_L00_001B06D0) {
                    case 0:
                        D_L00_001B06D0=1; st->charge=D_L00_001B06C4; st->timer=0.5f;
                        break;
                    case 2:
                        D_L00_001B06D0=1; st->timer=0.5f;
                        break;
                    }
                } else if ((g_pad_state.released&g_hero_state.mask) || D_L00_001B2B70.active==1) {
                    PlayMobySound(7,0,obj); D_L00_001B2B70.active=0;
                }
            }
        }
        switch (D_L00_001B06D0) {
        case 0:
            if (st->charge<D_L00_001B06C4) {
                st->charge+=D_L00_001B06C8;
                if (st->charge>D_L00_001B06C4) st->charge=D_L00_001B06C4;
            }
            break;
        case 1:
            st->charge+=D_L00_001B06BC;
            if (st->charge>D_L00_001B06CC) {
                moby_transform_joint_to_world(obj,0,&target);
                if (g_hero_state.direction==1) vec_scale_to_length(&velocity,(char *)obj+0xD0,-speed);
                else vec_scale_to_length(&velocity,&g_hero_state.camera,speed);
                count=coll_process_hit(&target,0,obj,0,1.0f);
                for(i=0;i<count;i++) {
                    char *candidate=g_area_hit_targets[i];
                    char *details=moby_get_private_value_0(candidate);
                    if (candidate==g_hero_state.player || !(U(candidate,0x34)&0x1000) || H(candidate,0xAA)==0xC87 || H(candidate,0xAA)==0xECC) continue;
                    qcopy(&point,candidate+0x10);
                    if (details) {
                        moby_forward_position_call(candidate,&delta,1);
                        FastVecScale(&delta,&delta,F(details,0x10));
                        FastVecAdd(&point,&delta,&point);
                    }
                    FastVecSub(&velocity,&point,&target);
                    vec_scale_to_length(&velocity,&velocity,speed);
                    break;
                }
                if (hit) {
                    char *extra;
                    qcopy(&delta,hit+0x10);
                    extra=moby_get_private_value_0(hit);
                    if (extra) {
                        cam_compute_view_direction(hit+0x10,&point,1);
                        FastVecScale(&point,&point,F(extra,0x10));
                        FastVecAdd(&delta,&point,hit+0x10);
                    }
                    FastVecSub(&velocity,&delta,&target);
                    vec_scale_to_length(&velocity,&velocity,speed);
                }
                D_L00_001B06D4=func_PAL_L00_003CF868(obj,st->handle,&target,&velocity);
                if (D_L00_001B06D4) *(ChargeWeaponMoby **)(D_L00_001B06D4+0xB8)=obj;
                D_L00_001B06D8=42; D_L00_001B06D0=2;
            }
            break;
        case 2:
            st->charge-=D_L00_001B06C0;
            if (st->charge<=D_L00_001B06C4) { st->charge=D_L00_001B06C4; D_L00_001B06D0=0; }
            break;
        }
        if (B(obj,0x31)) ref_L00_003E8180_00(func_PAL_L00_003ECD58,obj);
        st->angle=fast_subtract_rotations(st->angle,st->charge*0.37699118f);
        st->sine=math_fast_sin_or_cos_b(st->angle*0.5f);
        st->cosine=math_fast_sin_or_cos_a(st->angle*0.5f);
        break;
    }
}
