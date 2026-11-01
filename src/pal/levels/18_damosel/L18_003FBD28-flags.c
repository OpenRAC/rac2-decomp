#include "include_asm.h"

#include "common.h"
extern void func_PAL_002B5E30(void *,float);
extern void func_PAL_002B5E10(void *);
extern int func_L02_0032E998(void *,void *,void *,void *,int,void *,void *,float,float);
extern int func_PAL_002B5C98(void *,void *,float);
extern int func_PAL_002B5BA8(void *,void *,float);
extern void func_002A7750(void *,int,int);
extern void func_002ACB48(void *,float);

void func_PAL_L18_003FCB78(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    int mode = obj[0x42];
    if (mode<0) return;
    if (mode<6) goto low;
    if (mode>=8) return;
    goto high;
low:
        if (*(s16 *)(state+0x766)) func_PAL_002B5E30(obj,*(float *)(state+0x724));
        else func_PAL_002B5E10(obj);
    return;
high:
        if (*(int *)(state+0x71C)!=-1 && *(s16 *)(state+0x76A)) {
            u8 *p=state+0x700;
            func_L02_0032E998(obj+0x10,p,state+0x748,state+0x200,*(int *)(state+0x730),state+0x73C,state+0x740,0.0f,0.4f);
            func_PAL_002B5C98(obj,p,*(float *)(state+0x748));
        } else func_PAL_002B5BA8(obj,state+0x700,*(float *)(state+0x720));
        if (obj[0x20]!=9 && obj[0x20]!=4 && obj[0x20]!=3) {
            if (*(int *)(state+0x190)>=5) func_002A7750(obj,3,-1);
            if (*(int *)(state+0x1A4)&3) {
                func_002ACB48(obj+0x10,0.01f);
                func_002A7750(obj,3,-1);
            }
        }

}
