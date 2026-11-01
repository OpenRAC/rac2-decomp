#include "include_asm.h"

typedef struct { int colors[6]; } Colors1043;
extern Colors1043 ref_L00_002AC728_00, ref_L00_002AC728_01;
extern float ref_L00_002AC728_02[];
extern int func_002A77E0(int);
extern void func_002BBCB0(void *, void *, int, int, float, int, int, float, int, int);
extern void func_PAL_003096D0(void *, void *, void *, int, int, int, int, int, float);
extern void func_002E5CF8(int, int, void *);
extern void func_00312B70(void *, void *, int, int);
extern void func_00282C88(char *p);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);

void func_PAL_002AD288(unsigned char *object, void *position, int sound, float scale, float radius)
{
    float zero[3];
    Colors1043 first, second;
    float speed, energy;
    int i, life;
    int *a, *b;
    func_00282C88((char *)zero);
    for (i=2;i>=0;i--) {
        speed = func_002A7878(8.0f,10.0f) * 0.020000001f;
        energy = scale * 400000.0f;
        first = ref_L00_002AC728_00;
        second = ref_L00_002AC728_01;
        a = &first.colors[func_002A77E0(6)];
        b = &second.colors[func_002A77E0(6)];
        life = func_002A7820(12,17);
        func_002BBCB0(position,zero,*a,*b,energy,life,func_002A7820(21,25),speed*scale,0,0);
    }
    if (object) {
        func_PAL_003096D0(object,position,zero,17,127,64,0,48,scale*4.0f);
        func_PAL_003096D0(object,position,zero,24,96,32,0,32,scale*3.0f);
        if (object[0x20] != 0xfe)
            if (object[0x20] != 0xfd)
                if (sound != -1) func_002E5CF8(sound,0,object);
    }
    if (radius != 0.0f) {
        if (radius > 0.0f) {
            ref_L00_002AC728_02[9]=radius;
            ref_L00_002AC728_02[10]=radius;
            ref_L00_002AC728_02[8]=radius;
        } else {
            ref_L00_002AC728_02[9]=13.0f;
            ref_L00_002AC728_02[10]=13.0f;
            ref_L00_002AC728_02[8]=13.0f;
        }
        func_00312B70(ref_L00_002AC728_02,position,0,0);
    }
}
