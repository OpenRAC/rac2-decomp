#include "common.h"
extern u8 *func_0029EFD0(int);
extern float func_00283B98(float,float);
extern u8 D_00189E20[];
typedef struct { u8 pad[0x2290]; u8 *current; } ResidentView;

/* Create the three orbiting children with evenly spaced headings. */
void func_L02_00410E58(u8 *object)
{
    u8 **slot=(u8 **)(*(u8 **)(object+0x68)+0x14);
    int i=0;
    do {
        *slot=CreateMoby(0xC61 /* moby class 3169 */);
        *(u16 *)(*slot+0x32)=0x40;
        (*slot)[0x31]=1;
        *(u64 *)(*slot+0x38)=*(u64 *)(((ResidentView *)gHeroState)->current+0x38);
        *(u16 *)(*slot+0x34)=*(u16 *)(object+0x34);
        {
            u8 *child=*slot;
            float heading;
            qcopy(child+0x10,object+0x10);
            qcopy(child+0xF0,object+0xF0);
            heading=FastAddRotations(*(float *)(child+0xF8),(float)i*2.0943954f);
            *(float *)(*slot+0xF8)=heading;
        }
        slot++;
        i++;
    } while (i<3);
}
