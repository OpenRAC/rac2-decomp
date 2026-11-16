#include "include_asm.h"

#include "common.h"
#define BI(p, o) (*(int *)((p) + (o)))
#define BS(p, o) (*(short *)((p) + (o)))
#define BU(p, o) (*(unsigned short *)((p) + (o)))
#define BF(p, o) (*(float *)((p) + (o)))
#define BP(p, o) (*(unsigned char **)((p) + (o)))
typedef struct {
    unsigned char pad[0x80];
    float x, y, z, w;
    float rest[2];
    float angle;
    unsigned char pad2[0x2294 - 0x9C];
    int state;
    int unknown;
    int mode;
    unsigned char pad3[0x22B4 - 0x22A0];
    unsigned char locked;
} PlayerInteractionView;
extern unsigned char g_hero_state[];
#define PLAYER ((PlayerInteractionView *)D_00189E20)
extern int g_frame_counter_4;
extern int g_current_map_index __attribute__((section(".sdata")));
extern unsigned char g_pad_held_flags[];
extern float g_vendor_glow_phase __attribute__((sda));
extern float g_vendor_rotation_a __attribute__((sda));
extern float g_vendor_rotation_b __attribute__((sda));
extern float math_fast_sin_or_cos_b(float);
extern float math_fabs(float);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);
extern void moby_mark_spawned(void *);
extern void AttachManipulator(void *, int, void *);
extern void func_002A0F48(void *);
extern int flag_is_byte_set(void);
extern unsigned char *CreateMoby(int);
extern void save_mark_matching_level_slots(void);
extern void level_set_bit_in_flag_table(int, int);
extern void ref_L01_003808C0_00(void *, void *);
extern void build_axis_rotation_quaternion(void *, int, float);
extern void DrawVendorEffects(void);
extern int TryClaimNotice(int, int, int);
extern int request_begin_slot(int, int, void *, int, char *);

/* Updates a MegaCorp vendor: pulses its glow, spawns its display child, shows the buy prompt when the hero is near and facing it, and starts the shop when the button is pressed (PAL). */
void megacorp_vendor_update_pal(unsigned char *moby) {
    unsigned char *vars=BP(moby,0x68);
    unsigned char *hero, *near_hero, *child;
    int color,other;
    int i,can_use,show,accepted;
    float distance,height;
    float phase,amplitude;
    g_vendor_glow_phase+=0.05f;
    if(g_vendor_glow_phase>3.14f) g_vendor_glow_phase=-3.14f;
    color=0x20100;other=0x80F0F0B0;
    if(BI(vars,0x94)==2) {color=0x101;other=0x8080;}
    BI(moby,0x78)=color*((int)(math_fast_sin_or_cos_b(g_vendor_glow_phase)*24.0f)+96)|0x80000000;
    if(BP(vars,0xC)) BI(BP(vars,0xC),0x78)=other|0x80000000;
    if(BI(vars,0x94)==3) {
        BU(moby,0x34)|=1;moby[0x31]=0;BI(moby,0x98)=0;
        if(BP(vars,0xC)) {BU(BP(vars,0xC),0x34)|=1;BP(vars,0xC)[0x31]=0;}
    }
    switch(moby[0x20]) {
case 0:
        if(BI(vars,0x98) && !flag_is_byte_set()) {moby_mark_spawned(moby);return;}
        moby[0x20]=1;BI(vars,0)=0;BI(vars,4)=0;
        BP(vars,0xC)=CreateMoby(0x477);
        BU(BP(vars,0xC),0x34)|=2;
        BS(BP(vars,0xC),0x32)=0x40;
        BF(BP(vars,0xC),0x10)=BF(moby,0x10);
        BF(BP(vars,0xC),0x14)=BF(moby,0x14);
        BF(BP(vars,0xC),0x18)=BF(moby,0x18)+1.95f;
        if(BI(vars,0x94)==3) BF(BP(vars,0xC),0x18)-=30.0f;
        BP(vars,0xC)[0x63]=0x20;BF(vars,0x90)=0;
        for(i=0;i<2;i++) AttachManipulator(BP(vars,0xC),i,vars+0x10+i*0x40);
        func_002A0F48(BP(vars,0xC));
        break;
case 1:
        if(BF(vars,0x90)>0) BF(vars,0x90)-=0.1f;
        if(BF(vars,0x90)<=0) BU(BP(vars,0xC),0x34)|=1;
        if(!(g_frame_counter_4&7)) {
            hero=(unsigned char *)&PLAYER->x;
            if(vec_distance_xy(moby+0x10,hero)<=16.0f && math_fabs(BF(moby,0x18)-BF(hero,8))<=8.0f) {
                moby[0x20]=2;BU(BP(vars,0xC),0x34)&=0xFFFE;
                if(BI(vars,0x94)==2) save_mark_matching_level_slots();
                level_set_bit_in_flag_table(g_current_map_index,BI(vars,0x94));
            }
        }
        if(BI(vars,0x94)==3) break;
        ref_L01_003808C0_00(DrawVendorEffects,moby);
        build_axis_rotation_quaternion(vars+0x20,2,g_vendor_rotation_a);
        build_axis_rotation_quaternion(vars+0x60,2,g_vendor_rotation_b);
        g_vendor_rotation_a=FastAddRotations(g_vendor_rotation_a,0.01f);
        phase=FastAddRotations(g_vendor_rotation_b,-0.02f);
        child=BP(vars,0xC);
        amplitude=BF(vars,0x90)*BF(BP(child,0x24),0x24)*2.5f;
        g_vendor_rotation_b=phase;
        BF(child,0x2C)=amplitude;
        func_002A0F48(BP(vars,0xC));
        break;
case 2:
        if(BF(vars,0x90)<1) BF(vars,0x90)+=0.1f;
        near_hero=(unsigned char *)&PLAYER->x;
        distance=vec_distance_xy(moby+0x10,near_hero);
        height=math_fabs(BF(moby,0x18)-BF(near_hero,8));
        if(!(g_frame_counter_4&7) && (distance>18.0f || height>10.0f)) {moby[0x20]=1;return;}
        if(BI(vars,0x94)!=3) {
            ref_L01_003808C0_00(DrawVendorEffects,moby);
            build_axis_rotation_quaternion(vars+0x20,2,g_vendor_rotation_a);
            build_axis_rotation_quaternion(vars+0x60,2,g_vendor_rotation_b);
            g_vendor_rotation_a=FastAddRotations(g_vendor_rotation_a,0.01f);
            phase=FastAddRotations(g_vendor_rotation_b,-0.02f);
            child=BP(vars,0xC);
            amplitude=BF(vars,0x90)*BF(BP(child,0x24),0x24)*2.5f;
            g_vendor_rotation_b=phase;
            BF(child,0x2C)=amplitude;
            func_002A0F48(BP(vars,0xC));
        }
        can_use=1;show=1;
        if(PLAYER->mode!=0 && PLAYER->state!=3 && PLAYER->mode!=1) {can_use=0;show=0;}
        if(PLAYER->state==28 || PLAYER->state==49) {can_use=0;show=0;}
        if(PLAYER->locked) {can_use=0;show=0;}
        if(distance>4.0f || height>2.0f) {can_use=0;show=0;}
        if(FastDiffRots(PLAYER->angle,mat_fast_helper_a(BF(moby,0x10)-PLAYER->x,BF(moby,0x14)-PLAYER->y))>1.5707964f) {can_use=0;show=0;}
        accepted=0;
        if(show) {
            int text=0x12EB;
            if(BI(vars,0x94)==2) text=0x1350;
            else if(BI(vars,0x94)==4) text=0x1351;
            accepted=TryClaimNotice(1,text,1)!=0;
        }
        if((BI(g_pad_held_flags,0)&16) && can_use && accepted) moby[0x20]=4;
        break;
case 3:
        break;
case 4:
        if(BF(vars,0x90)>0) BF(vars,0x90)-=0.1f;
        if(BF(vars,0x90)<=0) {
            BU(BP(vars,0xC),0x34)|=1;request_begin_slot(5,1,moby,0,0);moby[0x20]=3;break;
        }
        if(BI(vars,0x94)==3) break;
        ref_L01_003808C0_00(DrawVendorEffects,moby);
        build_axis_rotation_quaternion(vars+0x20,2,g_vendor_rotation_a);
        build_axis_rotation_quaternion(vars+0x60,2,g_vendor_rotation_b);
        g_vendor_rotation_a=FastAddRotations(g_vendor_rotation_a,0.01f);
        phase=FastAddRotations(g_vendor_rotation_b,-0.02f);
        child=BP(vars,0xC);
        amplitude=BF(vars,0x90)*BF(BP(child,0x24),0x24)*2.5f;
        g_vendor_rotation_b=phase;
        BF(child,0x2C)=amplitude;
        func_002A0F48(BP(vars,0xC));
        break;
    }
}
