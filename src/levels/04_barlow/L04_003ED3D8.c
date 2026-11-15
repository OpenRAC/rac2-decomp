#include "common.h"
extern unsigned char g_sound_state[];
extern void func_00382AF8(int);
extern float func_0030EFA8(void *,void *);
typedef struct { char data[256]; } L04MoverTrigger;
extern L04MoverTrigger *g_moby_l04_pool[] __attribute__((sda));
extern int func_0034C4C8(void *);
extern int func_0030E9D8(void *);
extern void func_0030EDC8(void *, void *, void *);
extern void func_0030F090(void *, void *, float);
extern void func_0030ED98(void *, void *, void *);
extern int func_00382DF8(int, int, void *);
/* Moves the object to a target point when triggered, plays a sound while it moves, then moves it back to where it started. */
void triggered_l04_mover_update(char *moby)
{
    float delta[4], step[4];
    char *vars = *(char **)(moby+0x68);
    switch ((unsigned char)moby[0x20]) {
    case 0:
        *(char **)(vars+0xc) = (char *)&g_moby_l04_pool[0][*(int *)vars];
        moby[0x20] = 1;
        qcopy(vars+0x10,moby+0x10);
        *(float *)(vars+0x20)=340.57f;
        *(float *)(vars+0x24)=219.92f;
        *(float *)(vars+0x28)=*(float *)(moby+0x18);
        *(int *)(vars+0x34)=-1;
        break;
    case 1:
        if (func_0034C4C8(*(void **)(vars+0xc)) && func_0030E9D8(vars+8)) {
            moby[0x20]=3;
            *(char **)(vars+0xc)=(char *)&g_moby_l04_pool[0][*(int *)(vars+4)];
        }
        break;
    case 3: {
        func_0030EDC8(delta,vars+0x20,moby+0x10);
        func_0030F090(step,delta,0.07f);
        func_0030ED98(moby+0x10,moby+0x10,step);
        if (*(int *)(vars+0x38)==1) {
            char *sound=(char *)g_sound_state+*(int *)(vars+0x34)*0x70;
            if (*(char **)(sound+0x88)!=moby || !*(unsigned char *)(sound+0x74))
                *(int *)(vars+0x34)=func_00382DF8(0,4,moby);
        }
        if (func_0030EFA8(moby+0x10,vars+0x20)<0.4f) {
            moby[0x20]=2;
            if (*(int *)(vars+0x38)==1) {
                func_00382DF8(1,0,moby);
                if (*(int *)(vars+0x34)!=-1) {
                    char *sound=(char *)g_sound_state+*(int *)(vars+0x34)*0x70;
                    if (*(char **)(sound+0x88)==moby && *(unsigned char *)(sound+0x74)) func_00382AF8(*(int *)(vars+0x34));
                }
                *(int *)(vars+0x34)=-1;
            }
        }
        break;
    }
    case 2:
        if (func_0034C4C8(*(void **)(vars+0xc))) {
            *(unsigned short *)(moby+0x34)&=0xffbe;
            *(int *)(moby+0x98)=*(int *)(*(char **)(moby+0x24)+0x10);
            moby[0x20]=4;
        }
        break;
    case 4: {
        func_0030EDC8(delta,vars+0x10,moby+0x10);
        func_0030F090(step,delta,0.07f);
        func_0030ED98(moby+0x10,moby+0x10,step);
        if (*(int *)(vars+0x38)==1) {
            char *sound=(char *)g_sound_state+*(int *)(vars+0x34)*0x70;
            if (*(char **)(sound+0x88)!=moby || !*(unsigned char *)(sound+0x74))
                *(int *)(vars+0x34)=func_00382DF8(0,4,moby);
        }
        if (func_0030EFA8(moby+0x10,vars+0x10)<0.1f) {
            qcopy(moby+0x10,vars+0x10);
            moby[0x20]=5;
            if (*(int *)(vars+0x38)==1) {
                func_00382DF8(1,0,moby);
                if (*(int *)(vars+0x34)!=-1) {
                    char *sound=(char *)g_sound_state+*(int *)(vars+0x34)*0x70;
                    if (*(char **)(sound+0x88)==moby && *(unsigned char *)(sound+0x74)) func_00382AF8(*(int *)(vars+0x34));
                }
                *(int *)(vars+0x34)=-1;
            }
        }
        break;
    }
    }
}
