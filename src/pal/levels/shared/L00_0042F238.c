#include "include_asm.h"

#include "common.h"
extern char *D_L00_001B1844 __attribute__((section(".sdata")));
extern char *D_L00_001B8E10;
extern char D_00189EA0[];
extern float func_00282C48(float);
extern float func_00282E80(char *, char *);
extern int func_002ACBC8(char *, int);
extern int func_L00_003206B8(char *, int);
extern int func_002ACCA8(char *, int);
typedef struct { char pad[0x30]; char pos[16]; char rest[0x40]; } Entry_b0898;
extern Entry_b0898 *D_L00_001B1F8C __attribute__((section(".sdata")));
typedef struct {
 char pad[0x80]; char position[16]; char pad90[0x174-0x90]; float speed; char pad178[0x2294-0x178]; int mode;
 char pad2298[0x22B4-0x2298]; unsigned char flag;
} Global_b0898;
extern Global_b0898 D_00189E20_b0898;

int func_PAL_L00_0042F238(char *a)
{
    char *owner = D_L00_001B8E10;
    char *sub = *(char **)(owner + 0x70);
    char *move = sub + 0x160;
    char *rot = sub + 0x1C0;
    char *p = *(char **)(D_L00_001B1844 + *(short *)(a + 0x84) * 32 + 28);
    unsigned int mode;
    if (*(short *)(owner + 0x86) != 0) return 0;
    mode = D_00189E20_b0898.flag - 1U < 2U;
    if (*(short *)(p + 0x4A) && !mode) return 0;
    if (*(short *)(p + 0x48) && mode) return 0;
    if (*(int *)(p + 0x34)) {
        if (func_00282C48(*(float *)(move + 0x34)) > 0.01f) return 0;
        if (func_00282C48(*(float *)(rot + 8)) > 0.01f) return 0;
    }
    if ((unsigned int)(D_00189E20_b0898.mode - 0x62) >= 2 && D_00189E20_b0898.speed > 0.020000001f) return 0;
    if (*(int *)(p + 0xC) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && func_00282E80(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(p + 0xC)].pos) < 3.0f) return 1;
        if (func_002ACBC8(D_00189EA0, *(int *)(p + 0xC))) return 1;
    }
    if (*(int *)(p + 0x10) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && func_00282E80(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(p + 0x10)].pos) < 3.0f) return 1;
        if (func_L00_003206B8(D_00189EA0, *(int *)(p + 0x10))) return 1;
    }
    if (*(int *)(p + 8) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && func_00282E80(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(p + 8)].pos) < 3.0f) return 1;
        if (func_002ACCA8(D_00189EA0, *(int *)(p + 8))) return 1;
    }
    *(short *)(p + 0x26) = 1;
    return 0;
}


typedef struct Row_429F68 {
    float position[3];
    char pad[8];
    float pitch;
    float yaw;
    char *params;
} Row_429F68;
typedef struct Hero_429F68 {
    char pad[0x80];
    float position[4];
    char pad90[0x230];
    float axis[4];
} Hero_429F68;
extern Hero_429F68 D_00189E20_6;
extern float func_00283248(float, float), func_00283C80(float, float);
extern float func_00283BE0(float, float), func_00283198(float), func_00283180(float);
extern void func_00282CF0(char *, char *, char *);
extern float func_00282DB0(char *, char *), func_00282DF0(char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_L00_00424978(char *);
extern void func_L00_00424940(char *);
extern int func_PAL_L00_0042F238(char *);
extern int D_00138320;
extern void func_L00_00424A08(int, float, float);
extern void func_L00_00424C00(void);
extern void func_L00_00424A50(float, float);
extern void func_L00_00424A88(int, float, float);
extern void func_L00_00424B20(float);
extern void func_L00_00424B48(int);
extern void func_PAL_L00_00429FC8(float, float, float);

/* Initializes and updates the aim - camera volume, including follow - camera offsets. */
void func_PAL_L00_0042F4B8(char *camera)
{
    float position[4] __attribute__((aligned(16)));
    char to_position[16] __attribute__((aligned(16)));
    char gravity_offset[16] __attribute__((aligned(16)));
    char horizontal[16] __attribute__((aligned(16)));
    char *params = *(char **)(D_L00_001B1844 + *(short *)(camera + 0x84)*32 + 0x1C);
    char *camera_position, *state, *reset, *tail, *follow, *snap, *rig;
    float yaw, height, tangent, pitch;
    if (func_PAL_L00_0042F238(camera)) {
        if (func_L00_00424978(camera)<=0) {
            if (*(int *)(params + 0x20)) *(short *)(params + 0x26) = 1;
            *(int *)(params + 0x20) = 0;
            return;
        }
        if (!(D_00138320&4)) goto run;
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
        yaw = func_00283248(
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
        func_00282CC0(state + 0xB0, (char *)D_00189E20_6.position, gravity_offset);
        func_00282CF0(tail, (char *)position, state + 0xB0);
        qcopy(state + 0x170, tail);
        func_00282D30(gravity_offset, (char *)D_00189E20_6.axis,  - *(float *)(follow + 0xB0));
        func_00282CC0(state + 0xA0, (char *)D_00189E20_6.position, gravity_offset);
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
    if (*(int *)(params + 0x20)>167) *(int *)(params + 0x20) = 167;
    if (*(float *)(params + 0x38)!=0.0f) {
        func_L00_00424A08(0, *(float *)(params + 0x38), 0.003f);
        func_L00_00424C00();
    }
    if (*(float *)(params + 0x3C)!=0.0f) func_L00_00424A50(*(float *)(params + 0x3C), 0.003f);
    if (*(float *)(params + 0x40)!=0.0f) func_L00_00424A88(0, *(float *)(params + 0x40), 0.005f);
    if (*(float *)(params + 0x28)!=0.0f) func_L00_00424B20(*(float *)(params + 0x28)*0.01745329424738884f);
    if (*(short *)(params + 0x24)==0) func_L00_00424B48(0);
    if (*(float *)(params + 0x44)!=0.0f) func_PAL_L00_00429FC8(*(float *)(params + 0x44), 60.0f, 60.0f);
}


#define SDA_OBJ __attribute__((section(".sdata")))
extern char *D_L00_001B1844 SDA_OBJ;
extern char D_L00_001ADD98[] SDA_OBJ;
extern char D_L00_001ADD38[] SDA_OBJ;
extern char D_L00_001ADD78[] SDA_OBJ;
extern char D_L00_001ADD58[] SDA_OBJ;
extern int D_L00_001A8F00 __attribute__((sda));
extern void func_PAL_L00_0042F4B8(char *);

/* Looks the owner's table entry up (index half-word at +0x84, 0x20 bytes per entry, the
   entry's own pointer at +0x1C) and clears its flag half-word at +0x26 and its word at
   +0x20, but only when the entry is still idle, the global gate allows it and the extra
   check accepts the owner. */
int func_PAL_L00_0042F9B0(char *a0)
{
    char *p = *(char **)(D_L00_001B1844 + *(short *)(a0 + 0x84) * 0x20 + 0x1C);

    if (*(short *)(p + 0x26) != 0) {
        return 0;
    }
    if (D_L00_001A8F00 != 0) {
        if (func_PAL_L00_0042F238(a0) != 0) {
            *(short *)(p + 0x26) = 0;
            *(int *)(p + 0x20) = 0;
            return 0;
        }
    }
    func_PAL_L00_0042F4B8(a0);
    return 0;
}

