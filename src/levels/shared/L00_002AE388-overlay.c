#include "common.h"
typedef struct {
    char pad80[0x80];
    float position[4];
    float rotation[4];
    char pad1fc[0x15c];
    short flag;
    char pad64c[0x44e];
    float heading;
    float pitch;
    char pad6a0[0x4c];
    float heading2;
    char pad6a8[0x4];
    char * target;
    char pad730[0x84];
    float matrix[12];
    float direction[4];
    float angles[4];
    char padc2c[0x4ac];
    int condition;
    char pade98[0x268];
    char * slots[2];
    char * overlay;
    int pending;
    char pad11a0[0x2f8];
    int timer;
    char pad2290[0x10ec];
    int resource;
    char pad229c[0x8];
    int mode;
    char pad22b8[0x18];
    unsigned char enabled;
    char pad22ba[0x1];
    unsigned char active;
    unsigned char dual;
    char pad22c3[0x7];
    unsigned char transformed;
    char pad2490[0x1cc];
    char * object;
    char pad24b0[0x1c];
    int animation;
    int savedMode;
    char pad24cc[0x14];
    int mode2;
    char pad24ec[0x1c];
    short flag2;
    char pad24f4[0x6];
    short selector;
} AnimationState;
extern AnimationState D_00189E20_26;
extern int hero_get_item_icon_id(int);
extern void cancel_hero_item_animation(void);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern void *moby_get_private_value_0(void *);
extern int hero_slot_item_id(int);
extern char *ref_L00_002AEB18_0(int,int);
extern void ref_L00_002AEB18_1(int,void *);
extern void ref_L00_002AEB18_2(int,void *,int,int,int,int);
extern void ref_L00_002AEB18_3(int,void *);
extern float ApproachValue(float *,float,float);
extern char g_hero_status_overlay_buffer[];
/* Shows or hides a small icon over the hero, picking the picture by what the hero is doing, and fades it. */
void hero_update_status_icon_overlay(void)
{
    int enabled=0,id=0,mode;
    float opacity=1.0f;
    unsigned char *data;
    char *overlay;
    if(D_00189E20_26.object) {
        data=moby_get_private_value_0(D_00189E20_26.object);
        enabled=1;
        id=0x72;
        if(data[0x2c]) {
            id=hero_get_item_icon_id((unsigned char)data[0x2c]);
            if(D_00189E20_26.mode==1) opacity=0.7f;
        }
    }
    if(D_00189E20_26.flag) {
        enabled=1;
        id=hero_get_item_icon_id(D_00189E20_26.selector);
    }
    if(D_00189E20_26.mode2==1) {
        int anim=((unsigned char *)D_00189E20_26.resource)[0x43];
        enabled=1;
        if((anim==0x51 || anim==0x7b || anim==0x57) && !D_00189E20_26.condition) enabled=0;
        opacity=0.8f; id=0x74;
    }
    mode=hero_slot_item_id(0);
    if((mode==30 || mode==28 || mode==29) && D_00189E20_26.enabled) {
        enabled=1; opacity=0.8f; id=0x6f;
    }
    if(enabled) {
        if(!D_00189E20_26.overlay) {
            D_00189E20_26.overlay=ref_L00_002AEB18_0(D_00189E20_26.resource,24);
            I(D_00189E20_26.overlay,8)=0;
        }
    } else {
        if(!D_00189E20_26.overlay) return;
        if(ApproachValue((float *)(D_00189E20_26.overlay+8),0.0f,0.05f)==0.0f)
            ref_L00_002AEB18_1(D_00189E20_26.resource,&D_00189E20_26.overlay);
    }
    overlay=D_00189E20_26.overlay;
    if(!overlay) return;
    if(!enabled) return;
    {
        ApproachValue((float *)(overlay+8),opacity,0.05f);
        P(D_00189E20_26.overlay,0x38)=g_hero_status_overlay_buffer;
        P(D_00189E20_26.overlay,0x3c)=g_hero_status_overlay_buffer+0x600;
        if((unsigned char)D_00189E20_26.overlay[0x23]!=id)
            ref_L00_002AEB18_2(D_00189E20_26.resource,D_00189E20_26.overlay,id,0,8,1);
        else ref_L00_002AEB18_3(D_00189E20_26.resource,D_00189E20_26.overlay);
    }
}


