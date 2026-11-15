/* Museum weapon update: initializes its effect records, draws the aiming reticle,
 * advances the charge/recovery cycle and spawns a projectile toward a target.
 * The catalogue name retains the old entry; retail begins at 0x003E1E98.
 */
#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
typedef struct { float f[4]; } __attribute__((aligned(16))) MuseumWeaponVec;
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
} MuseumWeaponHero;
extern MuseumWeaponHero g_hero_state;
typedef struct { char pad[0x50]; float speed; char tail[0x8C]; } MuseumWeaponMaterial;
extern MuseumWeaponMaterial D_L30_002693F0[];
typedef struct { char pad[0x1A0]; int pressed, released; } MuseumWeaponInput;
extern MuseumWeaponInput g_pad_state;
typedef struct { float values[18]; char pad[8]; MuseumWeaponVec a, b; char tail[16]; } MuseumWeaponEffect;
extern MuseumWeaponEffect D_L30_00256050[];
extern char D_L30_001B9DC0[0x100];
extern unsigned char D_00139584 NOT_SDA;
/* These measured fields share the block at 0x001B3B40. Its full 0x20-byte
 * extent keeps the reticle reset absolute while the small globals below use GP.
 */
typedef struct { int active; char gap[0x18]; float reticle; } MuseumWeaponEffects;
extern MuseumWeaponEffects D_L30_001B3B40 __attribute__((sda));
extern char *D_L30_001C4280[];
extern int D_L30_001B0C08 __attribute__((sda)), D_L30_001B0BF0 __attribute__((sda)), D_L30_001B0C10 __attribute__((sda));
extern char *D_L30_001B0C0C __attribute__((sda));
extern float D_L30_001B0BF4 __attribute__((sda)), D_L30_001B0BF8 __attribute__((sda)), D_L30_001B0BFC __attribute__((sda)), D_L30_001B0C00 __attribute__((sda)), D_L30_001B0C04 __attribute__((sda));
extern void anim_start_blended(void *,int,int,int);
extern void AttachManipulator(void *,int,void *);
extern int AcquireEntitySlot(void *,int,void *);
extern u8 *level_get_slot_body(int,int);
extern float math_random_signed_float_range(float,float), math_random_float_range(float,float);
extern void vec_clear_128(void *), sheepinator_clear_records(void);
extern s32 hero_l00_set_action(int,int);
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
extern int PlayMobySound(int,int,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int coll_process_hit(void *,int,void *,int,float);
extern void FastVecSub(void *,void *,void *);
extern char *SpawnParticlePoolMoby(void *,int,void *,void *);
extern void gfx_queue_draw_callback(void *,void *),plasma_coil_draw_beams(void);
extern float fast_subtract_rotations(float,float),math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
typedef struct { float timer; int handle, anim, unknown; float charge, angle; char pad[8]; MuseumWeaponVec origin; float gap, sine, gap2, cosine; } MuseumWeaponVars;
typedef struct { char position[0x20]; unsigned char state; char pad21[0x22]; unsigned char animation; char pad44[0x1C]; unsigned char flags; char pad61[7]; MuseumWeaponVars *vars; } MuseumWeaponMoby;
/* Updates the Plasma Coil weapon (moby class 3146, Plasma Coil): it draws the aiming reticle, charges and recovers, and fires a projectile at the target. */
void UpdateMuseumChargedWeapon(MuseumWeaponMoby *obj) {
    MuseumWeaponVec velocity, origin, target, delta, point;
    int unused;
    char *hit = 0;
    MuseumWeaponVars *st = obj->vars;
    MuseumWeaponMaterial *material = &D_L30_002693F0[D_00139584];
    float speed = material->speed * 0.016666668f;
    int i, enabled, count;
    switch (obj->state) {
    case 0: {
        int i;
        if (obj->animation != 0 || (obj->flags&2)) anim_start_blended(obj,1,0,0);
        AttachManipulator(obj,0,&st->origin);
        st->timer=0.36666667f;
        st->unknown=-1;
        st->charge=0;
        st->angle=0;
        obj->state=1;
        D_L30_001B3B40.reticle=-1.0f;
        D_L30_001B0C08=0;
        D_L30_001B0BF0=0;
        st->handle=AcquireEntitySlot(obj,0,&unused);
        st->anim=level_get_slot_body(H(obj,0xAA),st->handle);
        for (i=0;i<4;i++) {
            D_L30_00256050[i].values[0]=0; D_L30_00256050[i].values[1]=0; D_L30_00256050[i].values[2]=0;
            D_L30_00256050[i].values[3]=math_random_signed_float_range(0.05f,0.3f);
            D_L30_00256050[i].values[4]=math_random_signed_float_range(0.05f,0.3f);
            D_L30_00256050[i].values[5]=math_random_signed_float_range(0.05f,0.3f);
            D_L30_00256050[i].values[6]=math_random_float_range(0.25f,0.75f);
            D_L30_00256050[i].values[7]=math_random_float_range(0.25f,0.75f);
            D_L30_00256050[i].values[8]=math_random_float_range(0.25f,0.75f);
            D_L30_00256050[i].values[9]=0; D_L30_00256050[i].values[10]=0; D_L30_00256050[i].values[11]=0;
            D_L30_00256050[i].values[12]=math_random_signed_float_range(0.05f,0.3f);
            D_L30_00256050[i].values[13]=math_random_signed_float_range(0.05f,0.3f);
            D_L30_00256050[i].values[14]=math_random_signed_float_range(0.05f,0.3f);
            D_L30_00256050[i].values[15]=math_random_float_range(0.25f,0.75f);
            D_L30_00256050[i].values[16]=math_random_float_range(0.25f,0.75f);
            D_L30_00256050[i].values[17]=math_random_float_range(0.25f,0.75f);
            vec_clear_128(&D_L30_00256050[i].a);
            vec_clear_128(&D_L30_00256050[i].b);
        }
        sheepinator_clear_records();
        break;
    }
    case 1:
        D_L30_001B3B40.reticle=-1;
        if (g_hero_state.selected) g_hero_state.held=g_hero_state.selected;
        if (!D_L30_001B0BF0) D_L30_001B0BF0=1;
        if (g_hero_state.mode==1) hero_l00_set_action(29,1);
        enabled=1;
        if (g_hero_state.mode==29) {
            if (!math_fast_float_d(&g_hero_state.timer)) enabled=0;
            {
                unsigned int color;
                if (st->timer!=0 && get_ammo(-1)) color=0x600000FF;
                else color=0x600FFF0F;
                hud_add_moby_marker(obj,color,1,0,0,38,-1,90,4);
            }
        } else g_hero_state.timer=40;
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
                float scale=math_fabs(0.9f-fast_vec_dist(D_L30_001B9DC0,&target)*0.006666667f*0.65f);
                hud_add_moby_marker(obj,0xFF0FFF0F,scale,&target,0,38,-1,90,4);
            }
        }
        if (vec_fast_helper_b(st) && !g_hero_state.locked) {
            if ((g_pad_state.pressed&g_hero_state.mask) && enabled && !sheepinator_is_mode_four() && g_hero_state.frame>=23) {
                if (weapon_spend_ammo(-1,1)) {
                    D_L30_001B3B40.active=1;
                    PlayMobySound(2,0,obj);
                    switch (D_L30_001B0C08) {
                    case 0:
                        D_L30_001B0C08=1; st->charge=D_L30_001B0BFC; st->timer=0.5f;
                        break;
                    case 2:
                        D_L30_001B0C08=1; st->timer=0.5f;
                        break;
                    }
                } else if ((g_pad_state.released&g_hero_state.mask) || D_L30_001B3B40.active==1) {
                    PlayMobySound(7,0,obj); D_L30_001B3B40.active=0;
                }
            }
        }
        switch (D_L30_001B0C08) {
        case 0:
            if (st->charge<D_L30_001B0BFC) {
                st->charge+=D_L30_001B0C00;
                if (st->charge>D_L30_001B0BFC) st->charge=D_L30_001B0BFC;
            }
            break;
        case 1:
            st->charge+=D_L30_001B0BF4;
            if (st->charge>D_L30_001B0C04) {
                moby_transform_joint_to_world(obj,0,&target);
                if (g_hero_state.direction==1) vec_scale_to_length(&velocity,(char *)obj+0xD0,-speed);
                else vec_scale_to_length(&velocity,&g_hero_state.camera,speed);
                count=coll_process_hit(&target,0,obj,0,1.0f);
                for(i=0;i<count;i++) {
                    char *candidate=D_L30_001C4280[i];
                    char *details=moby_get_private_value_0(candidate);
                    if (candidate==g_hero_state.player || !(U(candidate,0x34)&0x1000) || H(candidate,0xAA)==0xC87 /* moby class 3207 */ || H(candidate,0xAA)==0xECC /* moby class 3788 */) continue;
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
                D_L30_001B0C0C=SpawnParticlePoolMoby(obj,st->handle,&target,&velocity);
                if (D_L30_001B0C0C) *(MuseumWeaponMoby **)(D_L30_001B0C0C+0xB8)=obj;
                D_L30_001B0C10=50; D_L30_001B0C08=2;
            }
            break;
        case 2:
            st->charge-=D_L30_001B0BF8;
            if (st->charge<=D_L30_001B0BFC) { st->charge=D_L30_001B0BFC; D_L30_001B0C08=0; }
            break;
        }
        if (B(obj,0x31)) gfx_queue_draw_callback(plasma_coil_draw_beams,obj);
        st->angle=fast_subtract_rotations(st->angle,st->charge*0.3141593f);
        st->sine=math_fast_sin_or_cos_b(st->angle*0.5f);
        st->cosine=math_fast_sin_or_cos_a(st->angle*0.5f);
        break;
    }
}
