#include "include_asm.h"

#include "common.h"
typedef int EffectQuad __attribute__((mode(TI)));
typedef struct { unsigned char b[256]; } EffectSlot;
extern EffectSlot *g_moby_l04_pool;
extern int g_game_tick_counter __attribute__((section(".data")));
extern void glow_l04_ring_init_pal(unsigned char *);
extern void *moby_create_at_parent_pose(unsigned char *,void *,float);
extern float FastAddRotations(float,float);
extern void math_update_wrapped_angle_offset(void *,void *,void *,float,float,float);
extern int math_fast_float_d(void *);
extern void glow_ring_update_pal(void *);
#define EFFECT_WORD(p,o) (*(int *)((p)+(o)))
#define EFFECT_PTR(p,o) (*(unsigned char **)((p)+(o)))
#define EFFECT_FLOAT(p,o) (*(float *)((p)+(o)))
#define EFFECT_FLAGS(p,o) (*(unsigned short *)((p)+(o)))
#define EFFECT_QUAD(p,o) (*(EffectQuad *)((p)+(o)))

/* Updates a three-part rotating effect and cycles its highlighted part. */
void rotating_effect_update_pal(unsigned char *moby) {
    unsigned char *vars=EFFECT_PTR(moby,0x68);
    float delta=0;
    int tick;
    if(EFFECT_WORD(vars,0x10)!=-1) {
        if ((unsigned)(g_moby_l04_pool[EFFECT_WORD(vars,0x10)].b[0x20]-2)>=2) return;
    }
    if(moby[0x20]==0) {
        EFFECT_FLOAT(moby,0x18)+=0.5f; EFFECT_FLOAT(vars,0x54)=0; EFFECT_WORD(vars,0)=0;
        EFFECT_FLOAT(vars,0x58)=EFFECT_FLOAT(moby,0x18); moby[0x30]=255; EFFECT_FLAGS(moby,0x32)=127;
        EFFECT_FLOAT(moby,0x2C)=EFFECT_FLOAT(EFFECT_PTR(moby,0x24),0x24);
        EFFECT_WORD(vars,4)=0; EFFECT_WORD(vars,8)=0; EFFECT_WORD(vars,12)=0;
        glow_l04_ring_init_pal(moby); moby[0x20]=1;
    }
    if(!EFFECT_PTR(vars,4))EFFECT_PTR(vars,4)=moby_create_at_parent_pose(moby,(void *)0xB1C,1.0f);
    if(!EFFECT_PTR(vars,8))EFFECT_PTR(vars,8)=moby_create_at_parent_pose(moby,(void *)0xB1D,1.0f);
    if(!EFFECT_PTR(vars,12))EFFECT_PTR(vars,12)=moby_create_at_parent_pose(moby,(void *)0xB1E,1.0f);
    if(!EFFECT_PTR(vars,4)||!EFFECT_PTR(vars,8)||!EFFECT_PTR(vars,12))return;
    EFFECT_FLOAT(moby,0xF8)=FastAddRotations(EFFECT_FLOAT(moby,0xF8),0.062831864f);
    math_update_wrapped_angle_offset(moby,vars+0x54,&delta,0.01f,0.12566373f,EFFECT_FLOAT(vars,0x58));
    tick=g_game_tick_counter;
    EFFECT_QUAD(EFFECT_PTR(vars,4),0x10)=EFFECT_QUAD(moby,0x10);
    EFFECT_QUAD(EFFECT_PTR(vars,8),0x10)=EFFECT_QUAD(moby,0x10);
    EFFECT_QUAD(EFFECT_PTR(vars,12),0x10)=EFFECT_QUAD(moby,0x10);
    EFFECT_QUAD(EFFECT_PTR(vars,4),0xF0)=EFFECT_QUAD(moby,0xF0);
    EFFECT_QUAD(EFFECT_PTR(vars,8),0xF0)=EFFECT_QUAD(moby,0xF0);
    EFFECT_QUAD(EFFECT_PTR(vars,12),0xF0)=EFFECT_QUAD(moby,0xF0);
    switch((tick%50)/12) {
    case 0: EFFECT_WORD(EFFECT_PTR(vars,4),0x78)=0x804040FF;EFFECT_WORD(EFFECT_PTR(vars,8),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(vars,12),0x78)=0x80000040;break;
    case 1: EFFECT_WORD(EFFECT_PTR(vars,4),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(vars,8),0x78)=0x804040FF;EFFECT_WORD(EFFECT_PTR(vars,12),0x78)=0x80000040;break;
    case 2: EFFECT_WORD(EFFECT_PTR(vars,4),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(vars,8),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(vars,12),0x78)=0x804040FF;break;
    case 3: EFFECT_WORD(EFFECT_PTR(vars,4),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(vars,8),0x78)=0x80000040;EFFECT_WORD(EFFECT_PTR(vars,12),0x78)=0x80000040;break;
    }
    if(math_fast_float_d(vars)) {
        EFFECT_FLAGS(moby,0x34)&=0xFFBE; EFFECT_FLAGS(EFFECT_PTR(vars,4),0x34)&=0xFFBE;
        EFFECT_FLAGS(EFFECT_PTR(vars,8),0x34)&=0xFFBE; EFFECT_FLAGS(EFFECT_PTR(vars,12),0x34)&=0xFFBE;
        glow_ring_update_pal(moby);
    }else{
        EFFECT_FLAGS(moby,0x34)|=0x41; EFFECT_FLAGS(EFFECT_PTR(vars,4),0x34)|=0x41;
        EFFECT_FLAGS(EFFECT_PTR(vars,8),0x34)|=0x41; EFFECT_FLAGS(EFFECT_PTR(vars,12),0x34)|=0x41;
    }
}
