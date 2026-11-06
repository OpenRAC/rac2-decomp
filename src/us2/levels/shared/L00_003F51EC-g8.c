#include "common.h"

/* func_US2_L00_003F51EC, the USA v2.00 copy of func_L00_003F3D70: the same C, where each of the three
 * shots passes a fifth argument to func_US2_L00_003AB8F8: 5, then 5 or 10, then 5 or 15 with a target. */

typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char D_00189E20[];
extern unsigned char D_00138180[];
#define H ((Hero *)D_00189E20)
#define PAD ((Hero *)D_00138180)

typedef int ShotWord128 __attribute__((mode(TI)));
typedef union { ShotWord128 word; float f[4]; } ShotVector;
typedef struct { char prefix[0x50]; float speed, cooldown; char suffix[0xE0-0x58]; } ShotTuning;
extern ShotTuning D_L00_00262570[];

extern unsigned char D_00139568[];

extern float D_L00_001B08F8 __attribute__((sda));
extern float D_L00_0025C64C[];
extern void func_L00_0037E000(void *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_US2_L00_002C4560(int, int);
extern void func_00273318(void *, unsigned int, int, int, int, int, float, float, float);
extern int func_00282948(void *);
extern int func_002829D8(void *);
extern int func_L00_002D3F30(int, int);
extern int func_L00_002D4040(int);
extern void func_0029FCC0(char *, int, char *);
extern int func_002E5CF8(int, int, char *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_0037FA90(char *, char *, float, float, float);
extern void func_L00_0032A1A8(char *, char *, char *, float);
extern char *func_US2_L00_003AB8F8(void *, void *, void *, void *, int);
extern void func_002AFFD8(char *, char *, int);
extern void func_002AB668(void *, int, float);
extern void func_002ACDE8(void *, void *, void *);

void func_US2_L00_003F51EC(unsigned char *object) {
    char *state = *(char **)(object + 0x68);
    ShotVector aim, velocity, position, direction, rotation, rotated;
    char *spawn, *target;
    unsigned int color;
    int allowed;
    float speed;
    ShotTuning *entry;
    int second, third;
    if (object[0x20] == 0)
        object[0x20] = 1;
    func_L00_0037E000(H->ptr[2212]);
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        func_002A75E0(object, 1, 0, 2, 0);
    *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24) * D_L00_001B08F8;
    D_L00_0025C64C[0] = 0.1f;
    if (H->i[2213] == 1)
        func_US2_L00_002C4560(0x1D, 1);
    if (H->i[2213] == 0x1D) {
        if (*(float *)state > 0.0f && func_L00_002D4040(-1))
            color = 0x600000FF;
        else color = 0x600FFF0F;
        func_00273318(object, color, 0, 0x27, -1, 4, 2.0f, 0.0f, 90.0f);
    }
    if (H->ptr[1300])
        H->ptr[766] = H->ptr[1300];
    allowed = 1;
    if (H->i[2213] == 0x1D) {
        if (!func_00282948(&H->i[2381])) allowed = 0;
    } else H->i[2381] = 0x28;
    if (func_002829D8(state) && !H->b[8892] && H->i[1168] > 22 && allowed) {
        if ((PAD->u[104] & H->u[1164]) && func_L00_002D3F30(-1, 1)) {
            func_0029FCC0((char *)object, 0, (char *)&aim);
            func_002E5CF8(0, 0, (char *)object);
            func_002A75E0(object, 2, 0, 2, 0);
            speed = (D_L00_00262570 + D_00139568[0x18])->speed * 0.016666668f;
            if (H->h[4726] == 1) {
                func_00282F20(&velocity, object + 0xD0, -speed);
                qcopy(&position, &aim);
            } else {
                func_00282F20(&velocity, &(*(ShotVector *)&H->b[0x760]), speed);
                qcopy(&position, &aim);
                if (H->i[1344])
                    func_L00_0037FA90((char *)&velocity, (char *)&position, speed, 32.0f, 0.6981318f);
            }
            target = 0;
            second = 5;
            third = 5;
            if (H->ptr[766]) {
                func_L00_0032A1A8(H->ptr[766], (char *)&position, (char *)&velocity, speed);
                second = 10;
                target = H->ptr[766];
                third = 15;
            }
            spawn = func_US2_L00_003AB8F8(&position, &velocity, object, target, 5);
            if (spawn)
                *(unsigned char **)(spawn + 0xB8) = object;
            if (H->h[420] != 0)
                qcopy(&direction, H->ptr[2212] + 0xE0);
            else
                func_002AFFD8((char *)object + 0x10, (char *)&direction, 1);
            func_002AB668(&rotation, (int)&direction, -0.122173056f);
            func_002ACDE8(&rotated, &velocity, &rotation);
            spawn = func_US2_L00_003AB8F8(&position, &rotated, object, target, second);
            if (spawn)
                *(unsigned char **)(spawn + 0xB8) = object;
            func_002AB668(&rotation, (int)&direction, 0.122173056f);
            func_002ACDE8(&rotated, &velocity, &rotation);
            spawn = func_US2_L00_003AB8F8(&position, &rotated, object, target, third);
            if (spawn)
                *(unsigned char **)(spawn + 0xB8) = object;
            entry = D_L00_00262570 + D_00139568[0x18];
            *(float *)state = 1.0f / entry->cooldown;
        } else if ((PAD->u[105] & H->u[1164]) && !func_L00_002D4040(-1) && !H->b[8892]) {
            func_002E5CF8(0, 0, (char *)object);
        }
    }
}
