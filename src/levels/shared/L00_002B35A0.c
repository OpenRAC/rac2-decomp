#include "common.h"
extern u8 D_00189E20_1[];
extern int FastDecTimer(char *);
typedef int AnimQuad __attribute__((mode(TI)));
typedef struct { u8 pad[0x158]; float value; u8 gap[0x370-0x15c]; AnimQuad vector; } AnimBase;
extern AnimBase D_L00_001B8C80;
extern void hero_steer_heading(int, float, float, float);
/* Copies the hero turning values from the animation data and slows the turn depending on which way the hero is leaning. */
void hero_update_turn_from_anim(void)
{
    u8 *hero=D_00189E20_1;
    float factor;
    *(float *)(hero+0x1458)=*(float *)(hero+0x1a0);
    qcopy_nc(hero+0x1440,hero+0x190);
    FastDecTimer(hero+0x146c);
    FastDecTimer(hero+0x146e);
    factor=1.0f;
    if(hero[0x22b4]==0) {
        if(hero[0x1457]==0) {
            *(short *)(hero+0x146e)=5;
            if(*(short *)(hero+0x146c)!=0) factor=-0.25f;
        } else if(hero[0x1457]==1) {
            *(short *)(hero+0x146c)=5;
            if(*(short *)(hero+0x146e)!=0)
                factor=(4.0f-(float)*(short *)(hero+0x146e))*0.25f;
        }
    }
    {
        u8 *hero_block=D_00189E20_1;
        AnimBase *anim=&D_L00_001B8C80;
        *(float *)(hero_block+0x1a0)=anim->value;
        *(float *)(hero_block+0x1b4)*=factor;
        qcopy_nc(hero_block+0x190,&anim->vector);
        *(float *)(hero_block+0x1a4)=*(float *)(hero_block+0x145c);
        hero_steer_heading(0,0.037f,0.25f,0.2036217749118805f);
        {
            float saved=*(float *)(hero_block+0x1a4);
            *(float *)(hero_block+0x1a8)=0.0f;
            *(float *)(hero_block+0x145c)=saved;
        }
        *(float *)(hero_block+0x1a4)=0.0f;
    }
}
