#include "include_asm.h"

#include "common.h"
extern int func_002829D8(void *);
extern int D_L00_001B19C8 __attribute__((sda));
extern float D_L00_001B0748 __attribute__((sda));
extern float D_L00_001B074C __attribute__((sda));
extern float D_L00_001B0750 __attribute__((sda));
extern float D_L00_001B0754 __attribute__((sda));
extern float D_L00_001B0758 __attribute__((sda));
extern int D_L00_001A8F00[] MACRO_ADDR;
extern char D_L00_001B8FF0[];
extern char D_00189EA0[];
extern char D_L00_00262570[][224];
typedef struct { char pad[0x1F]; unsigned char selected; } Selection3EB8E8;
extern Selection3EB8E8 D_00139568;
extern unsigned char *D_L00_001FEA14 NOT_SDA;
extern char D_L00_001A8F20[] __attribute__((sda));
extern void func_0029FCC0(char *, int, void *);
extern char *func_L00_00324D18(void *, void *, int, float, float, float, float, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern char *func_002AB1F0(char *);
extern int func_002A77E0(int);
extern char *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L00_003F10D8(void *, char *, char *);
extern void func_002E5CF8(int, int, char *);
extern float func_002A7878(float, float);
typedef struct {
    char pad[0x24];
    unsigned char phase;
    unsigned char shots;
    char pad26[2];
    char *target;
    char pad2C[12];
    int slot;
    float cooldown;
} State3EB8E8;

void func_PAL_L00_003EFC00(char *self, State3EB8E8 *st)
{
    float pos[4], v[4], target[4], dir[4];
    char *obj, *part, *bone;
    int angle;
    float dot;
    char *entry;

    if (!func_002829D8(&st->cooldown) || D_L00_001B19C8 % 4 != st->slot)
        return;
    func_0029FCC0(self, 1, pos);
    st->phase ^= 1;
    obj = func_L00_00324D18(pos, D_L00_001B8FF0, 0, D_L00_001B074C * 0.01745329424738884f,
                            D_L00_001B0750 * 0.01745329424738884f, D_L00_001B0748,
                            D_L00_001B074C * 0.01745329424738884f, D_L00_001B0750 * 0.01745329424738884f);
    if (obj) {
        if ((*(short *)(obj + 0xAA) == 0xEE1 || *(short *)(obj + 0xAA) == 0xEC0 || *(short *)(obj + 0xAA) == 0xED4) &&
            *(unsigned char *)(*(char **)(obj + 0x68) + 0x3B1) == 255) {
            st->target = 0;
            return;
        }
        if (*(short *)(obj + 0xAA) == 0xEF4) {
            st->target = 0;
            return;
        }
        st->target = obj;
        if (*(unsigned char *)(self + 0x43) != 2)
            func_PAL_002A7E68(self, 2, 0, 4);
        func_00282CF0(v, self + 0x10, D_00189EA0);
        dot = func_00282DB0(v, self + 0xE0);
        if (D_L00_001A8F00[0] != 2 && *(unsigned char *)(self + 0x42) == *(unsigned char *)(self + 0x43) &&
            *(unsigned char *)(self + 0x42) == 2 && dot > 1.1f) {
            qcopy_nc(target, obj + 0x10);
            bone = func_002AB1F0(obj);
            if (bone)
                target[2] += *(float *)(bone + 0x10);
            else
                target[2] += D_L00_001B0758;
            angle = func_002A77E0(255);
            part = func_002C65A0(pos, D_L00_001A8F20, 2, 0x202080, angle, 127, 16, 420000.0f, 420000.0f, 0.0f, 0);
            if (part)
                part[2] = *D_L00_001FEA14;
            part = func_002C65A0(pos, D_L00_001A8F20, 2, 0x601080, (angle + 128) % 255, 127, 16,
                                 420000.0f, 420000.0f, 0.0f, 0);
            if (part)
                part[2] = *D_L00_001FEA14;
            func_00282CF0(dir, target, pos);
            func_00282F20(dir, dir, D_L00_001B0754);
            func_00282CC0(pos, pos, dir);
            func_PAL_L00_003F10D8(pos, self, obj);
            func_002E5CF8(0, 0, self);
            {
                int selected = D_00139568.selected;
                entry = D_L00_00262570[selected];
            }
            dot = func_002A7878(0.0f, 0.17f);
            st->cooldown = 1.0f / *(float *)(entry + 0x54) + dot;
            st->shots++;
        }
    } else {
        st->target = 0;
    }
}
