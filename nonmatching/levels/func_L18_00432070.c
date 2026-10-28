/* Nonmatching: US/US2 660/668 bytes; absent from PAL. Default profile.
 * Three identical generated forms bound this attempt. Actual 15-entry switch
 * table was read from level18 data at 0x2C0BE0: 1 copies rotation, 2 is empty,
 * 8/9 navigate, other in-range cases turn. Typed float child-field scopes
 * and -fno-gcse tie. Remaining: source/destination pointer setup order,
 * third child pointer held across the angle check, and final AAA00 setup.
 * AAA00 really returns float through f0 after writing two float fields;
 * its stale void declarations elsewhere are not copied here. B50E0/B4FF0
 * and the seven-GPR/two-FP navigation helper return integer status. The
 * only full-vector transfer is aligned existing object rotation, 16 bytes;
 * all graph/state arguments refer to existing storage with no invented bound.
 * Reopen with a new pointer-lifetime or narrow scheduling witness.
 */
#include "common.h"

extern float func_00283C80(float,float);
extern void func_002B5278(void *,float);
extern void func_002B5258(void *);
/* AAA00 updates two real float fields and returns the second field. */
extern float func_002AAA00(float *,float,float,float,float,float *,int);
extern int func_002B50E0(void *,void *,float);
extern int func_002B4FF0(void *,void *,float);
/* Seven 32-bit GPR arguments, then independent f12/f13 parameters. */
extern int func_L02_0032E998(void *,void *,float *,void *,int,int *,int *,float,float);

void func_L18_00432070(unsigned char *object)
{
    unsigned char *state=*(unsigned char **)(object+0x68);
    int action=object[0x42];
    if(action==-1) action=object[0x43];
    switch(action) {
    case 1:
        {
            void *rotation=object+0xF0;
            unsigned char *child=*(unsigned char **)(state+0x7C0);
            if(child) qcopy(child+0xF0,rotation);
        }
        break;
    case 3: case 4: case 5: case 6: case 7:
    case 10: case 11: case 12: case 13: case 14: case 15:
        if(*(short *)(state+0x808)==1) {
            if(func_00283C80(*(float *)(state+0x7A4),*(float *)(object+0xF8))>0.6108652949333191f) {
                func_002B5278(object,*(float *)(state+0x7A4));
                break;
            }
            if(*(unsigned char **)(state+0x7C0))
                func_002AAA00((float *)(*(unsigned char **)(state+0x7C0)+0xF8),*(float *)(state+0x7A4),0.006981317885220051f,0.006981317885220051f,0.20943954586982727f,(float *)(state+0x7CC),0);
            func_002B5258(object);
            break;
        }
        if(*(short *)(state+0x808)==2)
            func_002B5278(object,*(float *)(state+0x7A4));
        else
            func_002B5258(object);
        if(*(unsigned char **)(state+0x7C0)) {
            float *velocity=(float *)(state+0x7CC);
            float *rotation=(float *)(*(unsigned char **)(state+0x7C0)+0xF8);
            func_002AAA00(rotation,*(float *)(object+0xF8),0.006981317885220051f,0.006981317885220051f,0.20943954586982727f,velocity,0);
        }
        break;
    case 8: case 9:
        if(*(int *)(state+0x7D4)!=-1) {
            void *target=state+0x750;
            func_L02_0032E998(object+0x10,target,(float *)(state+0x7DC),state+0x210,*(int *)(state+0x780),(int *)(state+0x78C),(int *)(state+0x7D8),0.0f,0.4f);
            func_002B50E0(object,target,*(float *)(state+0x7DC));
        } else
            func_002B4FF0(object,state+0x750,*(float *)(state+0x7A0));
        if(*(unsigned char **)(state+0x7C0)) {
            if(*(short *)(state+0x808)==1) {
                if(func_00283C80(*(float *)(state+0x7A4),*(float *)(object+0xF8))<0.6108652949333191f) {
                    float *velocity=(float *)(state+0x7CC);
                    unsigned char *child=*(unsigned char **)(state+0x7C0);
                    func_002AAA00((float *)(child+0xF8),*(float *)(state+0x7A4),0.006981317885220051f,0.006981317885220051f,0.20943954586982727f,velocity,0);
                }
            } else {
                float *velocity=(float *)(state+0x7CC);
                unsigned char *child=*(unsigned char **)(state+0x7C0);
                func_002AAA00((float *)(child+0xF8),*(float *)(object+0xF8),0.006981317885220051f,0.006981317885220051f,0.20943954586982727f,velocity,0);
            }
        }
        break;
    }
}
