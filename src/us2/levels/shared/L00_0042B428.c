/* func_US2_L00_0042B428, the USA v2.00 copy of func_L00_00429F68: the same C, with D_L00_001B19C8 and
   Giant Clank mode (D_0018C0D4 == 2) added to the guard. */
#include "common.h"

/* Partial layouts measured from the descriptor and hero accesses below. */
typedef struct Row_429F68 {
    float position[3];
    char pad[8];
    float pitch;
    float yaw;
    char *params;
} Row_429F68;

extern char *D_L00_001B1844 __attribute__((section(".sdata")));
extern char *D_L00_001B8E10;
typedef struct Hero_429F68 {
    char pad[0x80];
    float position[4];
    char pad90[0x230];
    float axis[4];
} Hero_429F68;
extern Hero_429F68 D_00189E20_6;
extern float func_00283248_1(float, float), func_00283C80(float, float);
extern float func_00283BE0(float, float), func_00283198(float), func_00283180(float);
extern void func_00282CF0(char *, char *, char *);
extern float func_00282DB0(char *, char *), func_00282DF0(char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0_4(char *, char *, char *);
extern int func_L00_00424978(char *);
extern void func_L00_00424940(char *);
extern int func_L00_00429CE8(char *);
extern int D_00138320;
extern int D_L00_001B19C8 __attribute__((section(".sdata")));
extern unsigned char D_0018C0D4;
extern float func_00282C48(float);
extern void func_L00_00424A08(int, float, float);
extern void func_L00_00424C00(void);
extern void func_L00_00424A50(float, float);
extern void func_L00_00424A88(int, float, float);
extern void func_L00_00424B20(float);
extern void func_L00_00424B48(int);
extern void func_L00_00424AD8(float, float, float);

/* Initializes and updates the aim - camera volume, including follow - camera offsets. */
void func_US2_L00_0042B428(char *camera)
{
    float position[4] __attribute__((aligned(16)));
    char to_position[16] __attribute__((aligned(16)));
    char gravity_offset[16] __attribute__((aligned(16)));
    char horizontal[16] __attribute__((aligned(16)));
    char *params = *(char **)(D_L00_001B1844 + *(short *)(camera + 0x84)*32 + 0x1C);
    char *camera_position, *state, *reset, *tail, *follow, *snap, *rig;
    float yaw, height, tangent, pitch;
    if (D_L00_001B19C8>=4 && func_L00_00429CE8(camera)) {
        if (func_L00_00424978(camera)<=0) {
            if (*(int *)(params + 0x20)) *(short *)(params + 0x26) = 1;
            *(int *)(params + 0x20) = 0;
            return;
        }
        if (!(D_00138320&4) || D_0018C0D4==2) goto run;
    }
    if (*(int *)(params + 0x20)) *(short *)(params + 0x26) = 1;
    *(int *)(params + 0x20) = 0;
    func_L00_00424940(camera);
    return;
run:
    if (*(int *)(params + 0x20)<2) {
        if (*(float *)(params + 0x2C)==0.0f && *(float *)(params + 0x30)==0.0f) {
            char *table = D_L00_001B1844;
            *(float *)(params + 0x2C) = *(float *)(table + *(short *)(camera + 0x84)*32 + 0x14);
            *(float *)(params + 0x30) = *(float *)(table + *(short *)(camera + 0x84)*32 + 0x18);
        }
        yaw = func_00283248_1(
            D_00189E20_6.position[0] - ((Row_429F68 *)D_L00_001B1844)[*(short *)(camera + 0x84)].position[0],
            D_00189E20_6.position[1] - ((Row_429F68 *)D_L00_001B1844)[*(short *)(camera + 0x84)].position[1]);
        if (func_00283C80(*(float *)(params + 0x30), yaw)>0.03490658849477768f)
            *(float *)(params + 0x44) = func_00283BE0(*(float *)(params + 0x30), yaw);
        position[0] = ((Row_429F68 *)D_L00_001B1844)[*(short *)(camera + 0x84)].position[0];
        position[1] = ((Row_429F68 *)D_L00_001B1844)[*(short *)(camera + 0x84)].position[1];
        position[2] = ((Row_429F68 *)D_L00_001B1844)[*(short *)(camera + 0x84)].position[2];
        position[3] = 0.0f;
        func_00282CF0(to_position, (char *)position, (char *)D_00189E20_6.position);
        height = func_00282DB0(to_position, (char *)D_00189E20_6.axis);
        func_00282D30(gravity_offset, (char *)D_00189E20_6.axis, height);
        func_00282CF0(horizontal, to_position, gravity_offset);
        *(float *)(params + 0x38) = func_00282DF0(horizontal);
        *(float *)(params + 0x3C) =  - height;
        pitch = *(float *)(params + 0x2C);
        if (func_00282C48(pitch)==1.5707964897155762f) *(float *)(params + 0x40) = 0.0f;
        else {
            tangent = func_00283198(pitch);
            tangent/=func_00283180(pitch);
            *(float *)(params + 0x40) = *(float *)(params + 0x3C) - *(float *)(params + 0x38)*tangent;
        }
        camera_position = D_L00_001B8E10;
        rig = *(char **)(camera_position + 0x70);
        camera_position+=0x30;
        follow = rig + 0x60;
        tail = rig + 0x160;
        snap = rig + 0x1F0;
        state = rig;
        reset = state + 0x20;
        qcopy(camera_position, position);
        *(float *)(tail + 0x2C) = *(float *)(params + 0x38);
        *(float *)(tail + 0x30) = *(float *)(params + 0x3C);
        *(float *)(reset + 0x28) = *(float *)(params + 0x44);
        *(float *)(follow + 0xB0) = *(float *)(params + 0x40);
        func_00282D30(gravity_offset, (char *)D_00189E20_6.axis,  - *(float *)(tail + 0x30));
        func_00282CC0_4(state + 0xB0, (char *)D_00189E20_6.position, gravity_offset);
        func_00282CF0(tail, (char *)position, state + 0xB0);
        qcopy(state + 0x170, tail);
        func_00282D30(gravity_offset, (char *)D_00189E20_6.axis,  - *(float *)(follow + 0xB0));
        func_00282CC0_4(state + 0xA0, (char *)D_00189E20_6.position, gravity_offset);
        qcopy(state + 0xF0, state + 0xA0);
        qcopy(follow, (char *)D_00189E20_6.position);
        qcopy(state + 0xC0, follow);
        qcopy(state, camera_position);
        qcopy(state + 0x210, camera_position);
        *(int *)(snap + 0x30) = 0;
        *(int *)(reset + 0x14) = 0;
        *(float *)(reset + 4) = *(float *)(follow + 0xB0);
        {
            float zero = *(float *)(reset + 0x14);
            float distance = *(float *)(tail + 0x30);
            *(float *)(reset + 8) = distance;
            *(short *)(reset + 2) = 0;
            *(float *)(reset + 0x18) = zero;
            *(float *)(reset + 0x10) = zero;
            *(float *)(reset + 0xC) = zero;
        }
    }
    ++*(int *)(params + 0x20);
    if (*(int *)(params + 0x20)>200) *(int *)(params + 0x20) = 200;
    if (*(float *)(params + 0x38)!=0.0f) {
        func_L00_00424A08(0, *(float *)(params + 0x38), 0.003f);
        func_L00_00424C00();
    }
    if (*(float *)(params + 0x3C)!=0.0f) func_L00_00424A50(*(float *)(params + 0x3C), 0.003f);
    if (*(float *)(params + 0x40)!=0.0f) func_L00_00424A88(0, *(float *)(params + 0x40), 0.005f);
    if (*(float *)(params + 0x28)!=0.0f) func_L00_00424B20(*(float *)(params + 0x28)*0.01745329424738884f);
    if (*(short *)(params + 0x24)==0) func_L00_00424B48(0);
    if (*(float *)(params + 0x44)!=0.0f) func_L00_00424AD8(*(float *)(params + 0x44), 60.0f, 60.0f);
}
