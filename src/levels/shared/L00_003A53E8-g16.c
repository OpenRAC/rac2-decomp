#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
struct Rac2Native_5f824a0e369ccf7b_src_record { u8 b0,b1,b2,b3; u16 s4,s6,s8,s10,s12; u8 e,f; };
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L00_00294900[];
extern u8 g_item_slot_to_record[];
extern float D_L00_001AF670[4] __attribute__((sda));
extern unsigned int D_L00_001AF680 __attribute__((sda));
extern unsigned int D_L00_001AF684 __attribute__((sda));
extern unsigned int D_L00_001AF688 __attribute__((sda));
extern unsigned int D_L00_001AF68C __attribute__((sda));
extern unsigned int D_L00_001AF690 __attribute__((sda));
extern int D_L00_001AF6B4 __attribute__((sda));
typedef struct {
    char pad0[0x730];
    float a550[4];
    float a560[4];
    float a570[4];
    float a580[4];
    char pad4[0x488];
    char * aa18;
    char pad5[0x634];
    unsigned int b050;
    char pad6[0xC];
    int b060;
    char pad7[0x20C];
    int b270;
    char pad8[0xE3C];
    char * c0b0;
    int c0b4;
    char pad10[0x4];
    int c0bc;
    char pad11[0x18];
    u8 c0d8;
    char pad12[0x3];
    u8 c0dc;
    char pad13[0x22F];
    short c30c;
    char pad14[0x46];
    int c354;
} GameView;
typedef struct { char pad[0x1A0]; unsigned int b320, b324; } InputView;
extern GameView g_hero_state NOT_SDA;
extern InputView g_pad_state NOT_SDA;
/* Only this measured prefix of the level's pulse-curve state is used here. */
typedef struct { float start; int reserved,ticks,mode; float next; int reserved2,nextTicks; } PulseCurvePrefix;
typedef struct { char pad[0x160]; PulseCurvePrefix pulse; } CameraView;
extern CameraView D_L00_001B8C80 NOT_SDA;
typedef struct { char p0[0x28]; unsigned int animation; char p1[0x28]; float rate; char p2[0x18]; float power; char tail[0x6C]; } WeaponEntry;
extern WeaponEntry g_weapon_l00_table[];
extern char *g_area_hit_targets[];
extern int FastDecTimer(void *),math_fast_float_d(void *),vec_fast_helper_b(void *);
extern int PlayMobySound(int,int,char *);
extern void anim_start_blended_with_flags(void *,int,int,int,int),anim_start_blended(void *,int,int,int);
extern int hero_l00_set_action(int,int);
extern int get_ammo(int),weapon_spend_ammo(int,int);
extern void hud_add_moby_marker(void *,unsigned int,void *,int,int,int,float,float,float);
extern void start_equipped_item_animation(void);
extern void slot_reset_active(int);
extern int slot_copy_records_to_free(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern float math_random_angle(void),IntToFloat(int),math_random_float_range(float,float),FastAddRotations(float,float);
extern void beam_draw_ring_and_core(void *);
/* The binder: func_L00_002E6EF8 in 23 programs, its twin func_L08_002F2D10 in levels 08, 09,
   19 and 30, so the call carries a name without an address. */
extern void ref_L00_003A53E8_00(void (*)(void *),void *);
extern void vec_compute_object_to_target(char *,char *,void *,float);
extern void moby_transform_joint_to_world(char *,int,char *),SpawnLayeredParticleBurst(void *,void *);
extern void FastVecScale(void *,void *,float),FastVecAdd(void *,void *,void *);
extern int coll_process_hit(float,void *,int,void *,int);
extern void QueueMobyImpact(void *,void *);
extern int StartAttachedEffect(void *,int,void *);
extern void euler_to_matrix(void *,void *),copy_matrix3x4(void *,void *),multiply_matrix3x3(void *,void *,void *);
extern void math_build_axis_angle_quat(void *,int,float),vec_rotate_by_quaternion(void *,void *,void *);
extern char *beam_trace_and_apply_damage(void *,void *,void *,void *);

static inline void SetCameraPulse(CameraView *camera, float amount, int ticks)
{
    camera->pulse.start = amount;
    camera->pulse.ticks = ticks;
    camera->pulse.next = amount;
    camera->pulse.nextTicks = ticks;
    camera->pulse.mode = 0;
}

/* Control the two-stage blast and trace its individual fan rays. */
/* Per-frame update for the Blitz Gun moby: charges the blast, fires it in a fan of rays and damages what the rays hit. */
void blitz_gun_update(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    char damage[0x30];
    float probe[4], side[4], forward[4], up[4], bias[4];
    float frame[3][4], orientation[3][4], matrix[4][4];
    float origin[4], rotatedBias[4];
    char *hits[20]; int masks[20];
    float rotation[4], ray[4], start[4], end[4];
    int ready, count, i;
    float step, angle;
    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x20) = 1;
        *(int *)(state + 0x4C) = -1;
        *(short *)(state + 8) = 0;
        *(short *)(state + 10) = 0;
    }
    if (*(u8 *)(moby + 0x20) == 6 && FastDecTimer(state + 4)) {
        PlayMobySound(2,0,moby);
        *(u8 *)(moby + 0x20) = 1;
    }
    if (*(u8 *)(moby + 0x42) == *(u8 *)(moby + 0x43)) {
        int flags = *(u8 *)(moby + 0x60);
        if (flags & 2)
            anim_start_blended_with_flags(moby,1,0,2,0);
    }
    if (g_hero_state.c0b4 == 1)
        hero_l00_set_action(29,1);
    vec_fast_helper_b(state);
    if (g_hero_state.c0b4 == 29) {
        unsigned int color;
        if (*(float *)state > 0.0f && get_ammo(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        hud_add_moby_marker(moby,color,0,0x21,-1,4,1.3f,0.0f,90.0f);
    }
    {
        char *owner = moby;
        char *self;
        if (g_hero_state.b270)
            g_hero_state.aa18 = (char *)g_hero_state.b270;
        ready = 1;
        if (g_hero_state.c0b4 == 29) {
            if (!math_fast_float_d(&g_hero_state.c354))
                ready = 0;
        } else
            g_hero_state.c354 = 40;
        if (*(u8 *)(moby + 0x20) == 1 && !g_hero_state.c0dc && *(float *)state == 0.0f &&
            g_hero_state.b060 >= 23 && ready) {
            if ((g_pad_state.b320 & g_hero_state.b050) && weapon_spend_ammo(-1,1)) {
                WeaponEntry *weapon = g_weapon_l00_table + g_item_slot_to_record[0x1A];
                if (*(u8 *)(g_hero_state.c0b0 + 0x43) == weapon->animation ||
                    g_hero_state.c0bc || g_hero_state.c30c) {
                    unsigned short startup = D_L00_001AF680;
                    unsigned short delay = D_L00_001AF688;
                    unsigned short cooldown = D_L00_001AF690;
                    *(short *)(state + 6) = startup;
                    *(short *)(state + 8) = delay;
                    *(short *)(state + 10) = cooldown;
                    *(int *)(state + 0x48) = 1;
                } else {
                    unsigned short delay = D_L00_001AF684;
                    unsigned short cooldown = D_L00_001AF68C;
                    *(short *)(state + 6) = 2;
                    *(short *)(state + 8) = delay;
                    *(short *)(state + 10) = cooldown;
                    *(int *)(state + 0x48) = 0;
                }
                start_equipped_item_animation();
                *(int *)(state + 0x4C) = slot_copy_records_to_free(D_L00_00294900);
                *(u8 *)(moby + 0x20) = 2;
                *(float *)(state + 0xC) = math_random_angle();
                anim_start_blended(moby,2,0,0);
                *(float *)(state + 0x20) = 1.0f / IntToFloat(*(short *)(state + 8));
                *(float *)(state + 0x24) = 1.0f / IntToFloat(*(short *)(state + 10));
                *(float *)(state + 0x28) = math_random_angle();
                {
                    float phase = math_random_angle();
                    int ticks = D_L00_001AF6B4;
                    *(float *)(state + 0x2C) = phase;
                    *(int *)(state + 0x40) = ticks;
                    *(float *)(state + 0x44) = 1.0f / IntToFloat(ticks);
                }
            } else if (g_pad_state.b324 & g_hero_state.b050) {
                PlayMobySound(4,0,moby);
            }
            if (!((g_pad_state.b320 & g_hero_state.b050) && get_ammo(-1) && g_hero_state.c0d8) &&
                *(int *)(state + 0x4C) >= 0) {
                slot_reset_active(*(int *)(state + 0x4C));
                *(int *)(state + 0x4C) = -1;
            }
        }
        if (*(short *)(state + 6) == 0) {
            FastDecTimer(state + 10);
            FastDecTimer(state + 8);
            math_fast_float_d(state + 0x40);
            if (*(unsigned long *)(state + 8) & 0xFFFFFFFF)
                ref_L00_003A53E8_00(beam_draw_ring_and_core,moby);
        }
        if ((unsigned int)(*(u8 *)(moby + 0x20) - 2) >= 2 || !FastDecTimer(state + 6))
            return;
        self = owner;
        if (g_hero_state.aa18) {
            vec_compute_object_to_target(g_hero_state.aa18,state + 0x10,g_hero_state.a580,1.0f);
            qcopy(g_hero_state.a550, g_hero_state.a580);
        }
        if (*(u8 *)(moby + 0x20) == 2) {
            *(u8 *)(moby + 0x20) = 3;
            moby_transform_joint_to_world(moby,0,state + 0x10);
            SpawnLayeredParticleBurst(moby,state + 0x10);
            qcopy(state + 0x30, g_hero_state.a580);
            ref_L00_003A53E8_00(beam_draw_ring_and_core,moby);
            PlayMobySound(0,0,moby);
            if (*(int *)(state + 0x48))
                SetCameraPulse(&D_L00_001B8C80, 0.12f, 30);
            else
                SetCameraPulse(&D_L00_001B8C80, 0.06f, 30);
            return;
        }
        *(u8 *)(moby + 0x20) = 6;
        *(short *)(state + 4) = 28;
        {
        unsigned short id = *(unsigned short *)(moby + 0xAA);
        WeaponEntry *weapon = g_weapon_l00_table + g_item_slot_to_record[0x1A];
        float power = weapon->power;
        *(int *)(damage + 0x14) = 0x10000;
        *(int *)(damage + 0x20) = 1;
        *(u8 *)(damage + 0x18) = 3;
        *(u8 *)(damage + 0x19) = 2;
        *(short *)(damage + 0x1A) = id;
        *(float *)(damage + 0x1C) = power;
        *(char **)(damage + 0x10) = moby;
        }
        FastVecScale(probe,moby + 0xD0,-1.35f);
        FastVecAdd(probe,probe,moby + 0x10);
        FastVecScale(side,self + 0xC0,0.275f);
        FastVecAdd(probe,probe,side);
        count = coll_process_hit(1.5f,probe,1,g_hero_state.c0b0,0);
        for (i = 0; i < count; i++) {
            if (g_area_hit_targets[i] != g_hero_state.c0b0) {
                FastVecScale(damage,moby + 0xD0,-1.5f);
                *(float *)(damage + 0xC) = 5627.9248046875f;
                QueueMobyImpact(g_area_hit_targets[i],damage);
                StartAttachedEffect(g_area_hit_targets[i],26,moby);
            }
        }
        euler_to_matrix(matrix,D_L00_001AF670);
        copy_matrix3x4(orientation,matrix);
        moby_transform_joint_to_world(moby,0,(char *)origin);
        if (g_hero_state.c30c == 1) {
            FastVecScale(forward,moby + 0xD0,-1.0f);
            FastVecScale(up,self + 0xC0,-1.0f);
            FastVecScale(bias,moby + 0xE0,0.1f);
            multiply_matrix3x3(frame,self + 0xC0,orientation);
        } else {
            qcopy(forward, g_hero_state.a550);
            qcopy(up, g_hero_state.a560);
            FastVecScale(bias,g_hero_state.a570,-0.1f);
            multiply_matrix3x3(frame,g_hero_state.a550,orientation);
        }
        qcopy(state + 0x30, forward);
        {
        int rayCount, rayIndex, clearIndex, restoreIndex;
        
        
        step = 1.0471977f;
        angle = 0.0f;
        rayCount = 0;
        for (clearIndex = 0; clearIndex < 20; clearIndex++) { hits[clearIndex] = 0; masks[clearIndex] = 0; }
        {
            for (rayIndex = 19; rayIndex >= 0; rayIndex--) {
                char *hit;
                float spread = math_random_float_range(0.01f,0.3272492588f);
                math_build_axis_angle_quat(rotation,(int)up,spread);
                vec_rotate_by_quaternion(ray,forward,rotation);
                vec_rotate_by_quaternion(rotatedBias,bias,rotation);
                angle = FastAddRotations(math_random_float_range(step * 0.5f,step * 1.5f),angle);
                math_build_axis_angle_quat(rotation,(int)forward,angle);
                vec_rotate_by_quaternion(ray,ray,rotation);
                vec_rotate_by_quaternion(rotatedBias,rotatedBias,rotation);
                FastVecScale(ray,ray,32.0f);
                FastVecAdd(start,origin,rotatedBias);
                FastVecAdd(end,start,ray);
                hit = beam_trace_and_apply_damage(moby,start,end,damage);
                if (hit) {
                    masks[rayCount] = *(int *)(hit + 0x98);
                    hits[rayCount++] = hit;
                    *(int *)(hit + 0x98) = 0;
                }
            }
        }
        for (restoreIndex = 0; restoreIndex < rayCount; restoreIndex++)
            *(int *)(hits[restoreIndex] + 0x98) = masks[restoreIndex];
        }
        {
            WeaponEntry *weapon = g_weapon_l00_table + g_item_slot_to_record[0x1A];
            *(float *)state = 1.0f / weapon->rate;
        }
    }
}
