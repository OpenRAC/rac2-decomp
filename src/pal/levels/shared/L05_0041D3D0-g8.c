#include "include_asm.h"

#include "common.h"
extern int D_L05_001B0FC0 __attribute__((sda));
extern float D_L05_001B0FC4 __attribute__((sda));
extern float D_L05_001B0FC8 __attribute__((sda));
extern float D_L05_001B0FCC __attribute__((sda));
extern float D_L05_001B0FD0 __attribute__((sda));
extern int D_L05_001B0FD4 __attribute__((sda));
extern int D_L05_001B0FD8 __attribute__((sda));
extern float D_L05_001B0FDC __attribute__((sda));
extern float D_L05_001B0FE0 __attribute__((sda));
extern float D_L05_001B0FE4 __attribute__((sda));
extern float D_L05_001B0FE8 __attribute__((sda));
extern int D_L05_001B0FEC __attribute__((sda));
extern int D_L05_001B0FF4 __attribute__((sda));
extern float D_L05_001B0FF8 __attribute__((sda));
extern float D_L05_001B0FFC __attribute__((sda));
extern float D_L05_001B1000 __attribute__((sda));
extern float D_L05_001B1004 __attribute__((sda));
extern int D_L05_001B1008 __attribute__((sda));
extern int D_L05_001B100C __attribute__((sda));
extern float D_L05_001B1010 __attribute__((sda));
extern float D_L05_001B1014 __attribute__((sda));
extern float D_L05_001B1018 __attribute__((sda));
extern float D_L05_001B101C __attribute__((sda));
extern int D_L05_001B1020 __attribute__((sda));
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern void func_L05_00418D68(void *, void *, int, float, float, float, int);
extern void func_PAL_L05_0041E068(char *);
extern int func_L05_0037AC00(void);
extern void func_PAL_L05_0041DB88(char *);
typedef int BeamVec __attribute__((mode(TI)));

void func_PAL_L05_0041D3D0(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *attachment = *(char **)(state + 0x4C);
    float pos[4], direction[4], offset[4], offset2[4], offset3[4];
    float offsetX, offsetZ;

    if (attachment && *(short *)(attachment + 0xAA) == 0x10D9) {
        float factor, length, length2, width, height, width2, height2, extent, extent2;
        int count, count2, color, color2;

        offsetX = -0.135f;
        offsetZ = 0.1f;
        *(BeamVec *)offset = 0;
        offset[1] = 0.045f;
        offset[0] = offsetX;
        offset[2] = offsetZ;
        offset[3] = 1.0f;
        func_00283098(pos, offset, object + 0xC0);
        func_00282CC0(pos, pos, object + 0x10);
        factor = func_00283CE0(*(int *)(state + 0x34)) / func_00283CE0(7);
        factor *= 0.5f;
        length = D_L05_001B0FCC + (D_L05_001B1000 - D_L05_001B0FCC) * factor;
        length2 = D_L05_001B0FE4 + (D_L05_001B1018 - D_L05_001B0FE4) * factor;
        count = func_00283CF0((float)D_L05_001B0FD4 + (float)(D_L05_001B1008 - D_L05_001B0FD4) * factor);
        length = -length;
        length2 = -length2;
        count2 = func_00283CF0((float)D_L05_001B0FEC + (float)(D_L05_001B1020 - D_L05_001B0FEC) * factor);
        width = (D_L05_001B0FC4 + (D_L05_001B0FF8 - D_L05_001B0FC4) * factor) * 0.5f;
        width2 = (D_L05_001B0FDC + (D_L05_001B1010 - D_L05_001B0FDC) * factor) * 0.5f;
        height = (D_L05_001B0FC8 + (D_L05_001B0FFC - D_L05_001B0FC8) * factor) * 0.5f;
        height2 = (D_L05_001B0FE0 + (D_L05_001B1014 - D_L05_001B0FE0) * factor) * 0.5f;
        extent = D_L05_001B0FD0 + (D_L05_001B1004 - D_L05_001B0FD0) * factor;
        extent2 = D_L05_001B0FE8 + (D_L05_001B101C - D_L05_001B0FE8) * factor;

        color = func_00283D38(D_L05_001B0FC0, D_L05_001B0FF4, factor);
        color2 = func_00283D38(D_L05_001B0FD8, D_L05_001B100C, factor);
        func_00282D30(direction, object + 0xC0, length);
        func_L05_00418D68(pos, direction, count, width, height, extent, color);
        func_00282D30(direction, object + 0xC0, length2);
        func_L05_00418D68(pos, direction, count2, width2, height2, extent2, color2);
        *(BeamVec *)offset2 = 0;
        offset2[1] = -0.045f;
        offset2[0] = offsetX;
        offset2[2] = offsetZ;
        offset2[3] = 1.0f;
        func_00283098(pos, offset2, object + 0xC0);
        func_00282CC0(pos, pos, object + 0x10);
        func_00282D30(direction, object + 0xC0, length);
        func_L05_00418D68(pos, direction, count, width, height, extent, color);
        func_00282D30(direction, object + 0xC0, length2);
        func_L05_00418D68(pos, direction, count2, width2, height2, extent2, color2);
        *(BeamVec *)offset3 = 0;
        offset3[2] = 0.07f;
        offset3[0] = offsetX;
        offset3[3] = 1.0f;
        func_00283098(pos, offset3, object + 0xC0);
        func_00282CC0(pos, pos, object + 0x10);
        func_00282D30(direction, object + 0xC0, length);
        func_L05_00418D68(pos, direction, count, width + width, height + height, extent, color);
        func_00282D30(direction, object + 0xC0, length2);
        func_L05_00418D68(pos, direction, count2, width2 + width2, height2 + height2, extent2, color2);
    } else {
        float factor, length, length2, width, height, width2, height2, extent, extent2;
        int count, count2, color, color2;

        *(BeamVec *)offset = 0;
        offset[0] = -0.135f;
        offset[2] = 0.07f;
        offset[3] = 1.0f;
        func_00283098(pos, offset, object + 0xC0);
        func_00282CC0(pos, pos, object + 0x10);
        factor = func_00283CE0(*(int *)(state + 0x34)) / func_00283CE0(7);
        length = D_L05_001B0FCC + (D_L05_001B1000 - D_L05_001B0FCC) * factor;
        length2 = D_L05_001B0FE4 + (D_L05_001B1018 - D_L05_001B0FE4) * factor;
        count = func_00283CF0((float)D_L05_001B0FD4 + (float)(D_L05_001B1008 - D_L05_001B0FD4) * factor);
        count2 = func_00283CF0((float)D_L05_001B0FEC + (float)(D_L05_001B1020 - D_L05_001B0FEC) * factor);
        width = D_L05_001B0FC4 + (D_L05_001B0FF8 - D_L05_001B0FC4) * factor;
        width2 = D_L05_001B0FDC + (D_L05_001B1010 - D_L05_001B0FDC) * factor;
        height = D_L05_001B0FC8 + (D_L05_001B0FFC - D_L05_001B0FC8) * factor;
        height2 = D_L05_001B0FE0 + (D_L05_001B1014 - D_L05_001B0FE0) * factor;
        extent = D_L05_001B0FD0 + (D_L05_001B1004 - D_L05_001B0FD0) * factor;
        extent2 = D_L05_001B0FE8 + (D_L05_001B101C - D_L05_001B0FE8) * factor;
        color = func_00283D38(D_L05_001B0FC0, D_L05_001B0FF4, factor);
        color2 = func_00283D38(D_L05_001B0FD8, D_L05_001B100C, factor);
        func_00282D30(direction, object + 0xC0, -length);
        func_L05_00418D68(pos, direction, count, width, height, extent, color);
        func_00282D30(direction, object + 0xC0, -length2);
        func_L05_00418D68(pos, direction, count2, width2, height2, extent2, color2);
    }
    func_PAL_L05_0041E068(object);
    if (func_L05_0037AC00())
        func_PAL_L05_0041DB88(object);
}
