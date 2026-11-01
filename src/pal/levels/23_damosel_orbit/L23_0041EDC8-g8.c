#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int D_L23_001B1438 __attribute__((sda));
extern int D_L23_001B1440 __attribute__((sda));
extern float D_L23_001B1448 __attribute__((sda));
extern float D_L23_001B144C __attribute__((sda));
extern float D_L23_001B1580 __attribute__((sda));
extern float D_L23_001B1584 __attribute__((sda));
extern float D_L23_001B1588 __attribute__((sda));
extern float D_L23_001B158C __attribute__((sda));
extern int D_L23_001B1648 __attribute__((sda));
extern int D_L23_001B140C __attribute__((sda));
extern int D_L23_001B36AC;
extern Quad D_L23_001B3850 MACRO_ADDR;
extern Quad D_L23_001B3870 MACRO_ADDR;
extern float D_L23_001B3728;
extern int D_L23_001B3784;
extern char D_L23_001B3860[] MACRO_ADDR;
extern char D_L23_001B36C0[] MACRO_ADDR;
extern char *D_0018C0B0 __attribute__((nosda));
extern void func_00282C88(Quad *);
extern void func_0029FC20(char *, int, char *);
extern void func_0029FCC0(char *, int, char *);
extern void func_00282D30(char *, char *, float);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern float func_00282DB0(char *, char *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282DD8(char *, char *, char *);
extern float func_002831B0(float);
extern float func_00283C28(float);
extern float func_00283B98(float, float);
extern void func_0029F978(unsigned char *, unsigned int, unsigned char *);
extern void func_00283898(void *, int, float);
extern float func_00283BE0(float, float);
extern void func_PAL_L23_00420FF8(char *, float, float);

/* Update the aiming direction and its signed turn rate. */
int func_PAL_L23_0041F0D8(char *object, char *target) {
    struct { Quad zero, matrix[4], axis, direction, cross; } local;
    char *state = *(char **)(object + 0x68);
    char *direction;
    float speed, dot, angle;
    unsigned int mode;
    func_00282C88(&local.zero);
    ((float *)&local.zero)[3] = 1.0f;
    ((unsigned char *)state)[0x473] = 1;
    *(Quad *)(state + 0x480) = local.zero;
    func_0029FC20(object, 39, (char *)local.matrix);
    qcopy(&D_L23_001B3850, &local.matrix[3]);
    qcopy(&D_L23_001B3870, &local.matrix[0]);
    if (D_L23_001B1438) return 0;
    local.axis = 0;
    ((float *)&local.axis)[2] = 1.0f;
    ((float *)&local.axis)[3] = 1.0f;
    func_00282D30(state + 0x4A0, (char *)&local.axis,
        (float)D_L23_001B1440 * D_L23_001B1448 * D_L23_001B144C);
    func_0029FCC0(object, 42, (char *)&local.axis);
    func_00282CF0((char *)&local.direction, target, (char *)&local.axis);
    func_00282F20((char *)&local.direction, (char *)&local.direction, 1.0f);
    D_L23_001B3728 = func_00282DB0((char *)&local.direction, (char *)&D_L23_001B3870);
    D_L23_001B3784 = func_002761F8(D_L23_001B3860, D_L23_001B36C0, 16, D_0018C0B0, 0) == 0;
    direction = (char *)&local.direction;
    speed = D_L23_001B1580 * 0.0003490659f;
    if (((unsigned char *)state)[0x404] && ((unsigned char *)state)[0x405]) {
        mode = ((unsigned char *)object)[0x20];
        if ((unsigned char)mode != 7 || D_L23_001B1648 / 2 < D_L23_001B36AC) {
            if ((unsigned char)mode == 16) speed = D_L23_001B1584 * 0.0003490659f;
            else if ((unsigned)(mode - 13) < 3) speed = D_L23_001B1588 * 0.0003490659f;
        }
        func_00282DD8((char *)&local.cross, direction, (char *)&D_L23_001B3870);
        dot = func_00282DB0((char *)&local.cross, object + 0xD0);
        angle = func_002831B0(dot);
        func_00283C28(angle + 1.5707964f);
        if (dot < 0.0f) *(float *)(state + 0x57C) = -speed;
        else *(float *)(state + 0x57C) = speed;
        *(float *)(state + 0x578) = func_00283B98(*(float *)(state + 0x578), *(float *)(state + 0x57C));
        if (((unsigned char *)state)[0x4B1] == 0) func_0029F978((unsigned char *)object, 39, (unsigned char *)state + 0x4B0);
        func_00283898(state + 0x4C0, 1, *(float *)(state + 0x578));
        *(float *)(state + 0x578) = func_00283BE0(*(float *)(state + 0x578), *(float *)(state + 0x57C) * 0.0003490659f);
        func_PAL_L23_00420FF8(object, 1.0f, 1.0f);
        return 1;
    }
    if ((unsigned)((unsigned char)object[0x20] - 13) < 2) D_L23_001B140C = 1;
    if (!((unsigned char *)state)[0x404]) {
        *(float *)(state + 0x57C) = -(D_L23_001B158C * 0.0003490659f);
        if (*(float *)(state + 0x578) > 0.0f) {
            *(float *)(state + 0x578) += *(float *)(state + 0x57C);
            if (((unsigned char *)state)[0x4B1] == 0) func_0029F978((unsigned char *)object, 39, (unsigned char *)state + 0x4B0);
            func_00283898(state + 0x4C0, 1, *(float *)(state + 0x578));
            *(float *)(state + 0x578) = func_00283BE0(*(float *)(state + 0x578), *(float *)(state + 0x57C) * 0.0003490659f);
            func_PAL_L23_00420FF8(object, -1.0f, -1.0f);
        }
    }
    return 0;
}
