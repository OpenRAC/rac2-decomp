#include "common.h"

extern char D_L11_001B1E50[] __attribute__((sda));
extern char D_L11_001B1E70[] __attribute__((sda));
extern char D_L11_001B1E80[] __attribute__((sda));
extern char D_L11_001B1EA0[] __attribute__((sda));
extern char D_L11_001B1EB0[] __attribute__((sda));
extern char D_L11_001B1EE0[] __attribute__((sda));
extern char D_L11_001B1F20[] __attribute__((sda));
extern char D_L11_001B1F30[] __attribute__((sda));
extern char D_L11_001B1F50[] __attribute__((sda));
extern char D_L11_001B1F70[] __attribute__((sda));
extern char D_L11_001B43F0[] __attribute__((sda));
extern char D_L11_001B4430[] __attribute__((sda));
extern char D_L11_001B4450[] __attribute__((sda));
extern char D_L11_001B4490[] __attribute__((sda));
extern char D_L11_001B44B0[] __attribute__((sda));
extern char D_L11_001B44D0[] __attribute__((sda));
extern char D_L11_001B4510[] __attribute__((sda));
extern char D_L11_001B4550[] __attribute__((sda));
extern char D_L11_001B4570[] __attribute__((sda));
extern char D_L11_001B4580[] __attribute__((sda));
extern char D_L11_001B4588[] __attribute__((sda));
extern char D_L11_001B4598[] __attribute__((sda));
extern char D_L11_001B45A0[] __attribute__((sda));
extern char D_L11_001B45B8[] __attribute__((sda));
extern char D_L11_001B45D8[] __attribute__((sda));
extern char D_L11_001B45E0[] __attribute__((sda));
extern char D_L11_001B45F0[] __attribute__((sda));
extern char D_L11_001B4600[] __attribute__((sda));
extern char D_L11_001B4608[] __attribute__((sda));
extern char D_L11_001B4618[] __attribute__((sda));
extern char D_L11_001B4620[] __attribute__((sda));
extern char D_L11_001B4630[] __attribute__((sda));
extern char D_L11_001B4638[] __attribute__((sda));
extern char D_L11_001B4650[] __attribute__((sda));
extern char D_L11_001B4670[] __attribute__((sda));
extern char D_L11_001B4678[] __attribute__((sda));
extern char D_L11_001B4688[] __attribute__((sda));
extern char D_L11_001B4698[] __attribute__((sda));
extern char D_L11_001B46A0[] __attribute__((sda));
extern char D_L11_001B46A4[] __attribute__((sda));
extern char D_L11_001B46A8[] __attribute__((sda));
extern char D_L11_001B46AC[] __attribute__((sda));
extern char D_L11_001B46B0[] __attribute__((sda));
extern char D_L11_001B46B4[] __attribute__((sda));
extern char D_L11_001B46B8[] __attribute__((sda));
extern char D_L11_001B46BC[] __attribute__((sda));
extern char D_L11_001B46C0[] __attribute__((sda));
extern char D_L11_001B46C4[] __attribute__((sda));
extern char D_L11_002626B0[];
extern char D_L11_00262710[];
extern void func_00282D30_2(char *, char *, float);
extern void func_00282CC0(void *, void *, void *);

extern char *D_L11_001FF580[];
extern char D_L11_001B1DD0[], D_L11_001B1E00[], D_L11_001B1E28[];
extern void func_0026FEB8(char *, ...);

void func_L11_004577F8(int *outX, int *outY, int selector, int frame,
                       int *previousCurve, int *segment, char *object)
{
    float point[4], delta[4];
    int *origins;
    float *velocities, *durations, *starts;
    int count, curve = -1, i; /* the -1 load is shared with the first selector test */
    char *path;
    float time, start;

    if (selector == -1 && frame >= 0 && frame <= 54) {
        path = D_L11_001FF580[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)frame) /
                   (*(float *)(path + 0x1C) * 54.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46A0;
        origins = (int *)D_L11_001B1E50;
        velocities = (float *)D_L11_001B43F0;
        durations = (float *)D_L11_001B4570;
        starts = (float *)D_L11_001B4608;
        count = 4;
        curve = 1;
    } else if (selector == -1 && frame >= 54 && frame <= 110) {
        path = D_L11_001FF580[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 54)) /
                   (*(float *)(path + 0x1C) * 56.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46A4;
        origins = (int *)D_L11_001B1E70;
        velocities = (float *)D_L11_001B4430;
        durations = (float *)D_L11_001B4580;
        starts = (float *)D_L11_001B4618;
        count = 2;
        curve = 2;
    } else if (selector == 0) {
        path = D_L11_001FF580[*(int *)(object + 0x1AC)];
        start = (*(float *)(path + 0x1C) * (float)frame) /
                   (*(float *)(path + 0x1C) * (float)*(int *)path);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46A8;
        origins = (int *)D_L11_001B1E80;
        velocities = (float *)D_L11_001B4450;
        durations = (float *)D_L11_001B4588;
        starts = (float *)D_L11_001B4620;
        count = 4;
        curve = 3;
    } else if (selector == -1 && frame >= 110 && frame <= 118) {
        path = D_L11_001FF580[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 110)) /
                   (*(float *)(path + 0x1C) * 8.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46AC;
        origins = (int *)D_L11_001B1EA0;
        velocities = (float *)D_L11_001B4490;
        durations = (float *)D_L11_001B4598;
        starts = (float *)D_L11_001B4630;
        count = 2;
        curve = 4;
    } else if (selector == -1 && frame >= 118 && frame <= 313) {
        path = D_L11_001FF580[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 118)) /
                   (*(float *)(path + 0x1C) * 195.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46B0;
        origins = (int *)D_L11_001B1EB0;
        velocities = (float *)D_L11_002626B0;
        durations = (float *)D_L11_001B45A0;
        starts = (float *)D_L11_001B4638;
        count = 6;
        curve = 5;
    } else if (selector == 1) {
        path = D_L11_001FF580[*(int *)(object + 0x1B0)];
        start = (*(float *)(path + 0x1C) * (float)frame) /
                   (*(float *)(path + 0x1C) * (float)*(int *)path);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46B4;
        origins = (int *)D_L11_001B1EE0;
        velocities = (float *)D_L11_00262710;
        durations = (float *)D_L11_001B45B8;
        starts = (float *)D_L11_001B4650;
        count = 8;
        curve = 6;
    } else if (selector == -1 && frame >= 313 && frame <= 321) {
        path = D_L11_001FF580[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 313)) /
                   (*(float *)(path + 0x1C) * 8.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46B8;
        origins = (int *)D_L11_001B1F20;
        velocities = (float *)D_L11_001B44B0;
        durations = (float *)D_L11_001B45D8;
        starts = (float *)D_L11_001B4670;
        count = 2;
        curve = 7;
    } else if (selector == -1 && frame >= 321 && frame <= 468) {
        path = D_L11_001FF580[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 321)) /
                   (*(float *)(path + 0x1C) * 147.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46BC;
        origins = (int *)D_L11_001B1F30;
        velocities = (float *)D_L11_001B44D0;
        durations = (float *)D_L11_001B45E0;
        starts = (float *)D_L11_001B4678;
        count = 4;
        curve = 8;
    } else if (selector == 2) {
        path = D_L11_001FF580[*(int *)(object + 0x1B4)];
        start = (*(float *)(path + 0x1C) * (float)frame) /
                   (*(float *)(path + 0x1C) * (float)*(int *)path);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46C0;
        origins = (int *)D_L11_001B1F50;
        velocities = (float *)D_L11_001B4510;
        durations = (float *)D_L11_001B45F0;
        starts = (float *)D_L11_001B4688;
        count = 4;
        curve = 9;
    } else if (selector == -1 && frame >= 468 && frame <= 500) {
        path = D_L11_001FF580[*(int *)(object + 0x1A8)];
        start = (*(float *)(path + 0x1C) * (float)(frame - 468)) /
                   (*(float *)(path + 0x1C) * 32.0f);
        if (start > 1.0f) start = 1.0f;
        time = start * *(float *)D_L11_001B46C4;
        origins = (int *)D_L11_001B1F70;
        velocities = (float *)D_L11_001B4550;
        durations = (float *)D_L11_001B4600;
        starts = (float *)D_L11_001B4698;
        count = 2;
        curve = 10;
    } else {
        STUB_printf(D_L11_001B1DD0);
        *previousCurve = -1;
        *segment = 0;
        *outX = 0;
        *outY = 0;
        return;
    }

    if (curve != *previousCurve) {
        start = 0.0f;
        for (i = 0; start <= time; i++) {
            start = durations[i] + start;
            if (time < start) {
                start -= durations[i];
                break;
            }
        }
        *segment = i;
        *previousCurve = curve;
    } else {
        i = *segment;
        start = starts[i];
        if (time < start) {
            while (start > time) {
                i--;
                if (i < 0) {
                    i = count;
                    STUB_printf(D_L11_001B1E00);
                }
                start -= durations[i];
            }
        } else if (time > start) {
            do {
                start += durations[i];
                if (start < time) {
                    i++;
                    if (i >= count) {
                        STUB_printf(D_L11_001B1E28);
                        i = 0;
                    }
                }
            } while (start < time);
        }
        start = starts[i];
        *segment = i;
    }
    point[0] = (float)origins[i * 2];
    point[1] = (float)origins[i * 2 + 1];
    point[2] = 0.0f;
    func_00282D30_2((char *)delta, (char *)(velocities + i * 4), time - start);
    FastVecAdd(point, point, delta);
    *outX = (int)point[0];
    *outY = (int)point[1];
}
