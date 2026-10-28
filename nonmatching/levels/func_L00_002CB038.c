/* Retained complete C reconstruction: 468/476 bytes at game -O2 -G0.
 * US and US2: 0/27 local placements; PAL absent. No strict linked credit.
 * The historical screen inverted the eligibility guard; retail requires flag
 * 0x20 set and state !=0x31, after rejecting a negative screen index.
 * Retail func_L00_002AE888 returns a selected object pointer, not the older
 * integer declaration; all three GPR and four single-FP arguments are retained.
 * Named camera/angle lifetimes improve 464 to468 bytes. The narrow
 * keep-block-order control ties. Early clear-tail sharing, pointer priorities
 * and mixed absolute/GP counter scheduling still differ. Reopen with genuine
 * source/block-lifetime evidence, without aliases or volatile steering.
 */
#include "common.h"
extern unsigned char D_00189E20[];
extern unsigned char D_001A7A80[];
extern unsigned int D_00138320;
extern unsigned char D_00138180[];
extern unsigned int D_001A7390 __attribute__((sda));
extern int D_001A79F0;
extern unsigned char D_L00_001B8C80[];
struct ScreenDropStats {
    unsigned char prefix[0x1B0];
    unsigned short count;
    unsigned short reserved1B2;
    unsigned int best;
    unsigned int levels;
};
extern struct ScreenDropStats D_0018C750;
extern float func_00282E48(void *,void *);
/* Retail returns a selected object pointer from the candidate-object list. */
extern char *func_L00_002AE888(void *,float,float,float,float,int,int);

void func_L00_002CB038(void)
{
    unsigned char *hero=D_00189E20;
    int screen=*(int *)(hero+0x1248);
    char *object;
    if(screen<0) {
        *(int *)(hero+0x1450)=0;
        return;
    }
    if(!(D_001A7A80[screen]&0x20) || *(int *)(hero+0x2294)==0x31) {
        *(int *)(hero+0x1450)=0;
        return;
    }
    object=*(char **)(hero+0x1450);
    if(object) {
        char *position=object+0x10;
        if(30.0f<func_00282E48(hero+0x80,position))
            *(int *)(hero+0x1450)=0;
        if((D_00138320&3)!=3)
            *(int *)(hero+0x1450)=0;
        object=*(char **)(hero+0x1450);
        if(!object || (*(unsigned short *)(object+0x34)&0x1000))
            return;
        *(int *)(hero+0x1450)=0;
        if(D_0018C750.count<=0xFFFE)
            ++D_0018C750.count;
        if(D_001A7390>D_0018C750.best)
            D_0018C750.best=D_001A7390;
        D_0018C750.levels |= (1u<<D_001A79F0)|0x80000000u;
        return;
    }
    if((*(unsigned int *)(D_00138180+0x1A0)&3)==3 &&
       (*(unsigned int *)(D_00138180+0x1A4)&3)!=0) {
        float radius=25.0f;
        unsigned char *camera=D_L00_001B8C80;
        float nearAngle=0.6108652949333191f;
        float farAngle=1.2217305898666382f;
        float heading=*(float *)(camera+0x158);
        object=func_L00_002AE888(camera+0x370,radius,heading,nearAngle,farAngle,5,1);
        *(char **)(hero+0x1450)=object;
        if(!object)
            *(char **)(hero+0x1450)=func_L00_002AE888(hero,radius,
                *(float *)(hero+0x98),nearAngle,farAngle,5,1);
    }
}
