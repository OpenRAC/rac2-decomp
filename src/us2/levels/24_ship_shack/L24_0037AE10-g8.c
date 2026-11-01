#include "include_asm.h"

typedef struct { float x,y,z,w; } Point;
typedef struct {
    unsigned char pad0[0x80];
    Point position;
    unsigned char pad90[8];
    float heading;
    unsigned char pad9c[0x2294-0x9c];
    int mode;
    unsigned char pad2298[4];
    int activity;
} PlayerView;
extern unsigned char D_00189E20[];
extern int D_L24_001AEBB8 __attribute__((sda));
extern int D_L24_001AEBBC __attribute__((sda));
extern int D_L24_001A8F00;
extern unsigned int D_00138324 __attribute__((nosda));
extern void func_002A7750(unsigned char *, unsigned char, int);
extern void func_L00_00326048(char *, float *, int, int, float);
extern float func_00282E80(void *, void *);
extern float func_00282C48(float);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern int func_002B0C28(int, int, int);
extern int func_002B49E0(int, int, int, int, unsigned char *);

void func_US2_L24_0037AE10(unsigned char *object)
{
    unsigned int permitted;
    int selected;
    float *animation = *(float **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        func_002A7750(object, 1, -1);
        break;
    case 1:
        permitted = 1;
        selected = 0;
        func_L00_00326048((char *)object, animation,
                          D_L24_001AEBB8, D_L24_001AEBBC, 0.043633237f);
        if (((PlayerView *)D_00189E20)->activity && ((PlayerView *)D_00189E20)->mode != 3) {
            if (((PlayerView *)D_00189E20)->activity != 1) permitted = 0;
        }
        if (func_00282E80(object + 0x10, &((PlayerView *)D_00189E20)->position) > 3.0f ||
            func_00282C48(((PlayerView *)D_00189E20)->position.z - *(float *)(object + 0x18)) > 0.7f)
            permitted = 0;
        if (func_00283C80(((PlayerView *)D_00189E20)->heading,
              func_00283248(*(float *)(object + 0x10) - ((PlayerView *)D_00189E20)->position.x,
                            *(float *)(object + 0x14) - ((PlayerView *)D_00189E20)->position.y)) > 1.5707965f)
            permitted = 0;
        if (((PlayerView *)D_00189E20)->mode == 0x1c || ((PlayerView *)D_00189E20)->mode == 0x31) permitted = 0;
        if (permitted) selected = func_002B0C28(1, 0x12EB, 1) != 0;
        if ((D_00138324 & 0x10) && selected) {
            func_002B49E0(5, 1, (int)object, 0, 0);
            object[0x20] = 2;
        }
        break;
    case 2:
        if (!D_L24_001A8F00) object[0x20] = 1;
        break;
    }
}
