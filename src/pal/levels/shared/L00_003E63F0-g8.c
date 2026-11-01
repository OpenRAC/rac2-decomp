#include "include_asm.h"

#include "common.h"
struct E2CounterState {
    int slot;
    char pad_04[0x0c];
    int field_10;
};
extern char *ref_L00_003E2180_00(int);
extern struct E2Player { char p[0x760]; float v[4]; char p2[0x1500-0x770]; int flag; char p3[0x24ec-0x1504]; short mode; } ref_L00_003E2180_01 NOT_SDA;
extern unsigned char ref_L00_003E2180_02 NOT_SDA;
extern struct E2Weapon { char p[0x50]; float speed; char p2[224-0x54]; } ref_L00_003E2180_03[] NOT_SDA;
extern void ref_L00_003E2180_04(void *, void *, float);
extern char *ref_L00_003E2180_05(char *);
extern void ref_L00_003E2180_06(void *, void *, int);
extern void ref_L00_003E2180_07(void *, void *, float);
extern void ref_L00_003E2180_08(void *, void *, void *);
extern void ref_L00_003E2180_09(void *, void *, void *);
extern void ref_L00_003E2180_10(void *, void *, float, float, float);
extern void ref_L00_003E2180_11(char *);
extern int ref_L00_003E2180_12(float);
extern float ref_L00_003E2180_13(int);
extern float ref_L00_003E2180_14(float, float);
extern float ref_L00_003E2180_15(void);
extern int ref_L00_003E2180_16(int, int);
extern int ref_L00_003E2180_17 SDATA(ref_L00_003E2180_17);
extern float ref_L00_003E2180_18 SDATA(ref_L00_003E2180_18);
extern void ref_L00_003E2180_19(char *);
extern int ref_L00_003E2180_20(char *, float, float, float, int);
extern void ref_L00_003E2180_21(void *, char *);
extern void ref_L00_003E2180_22(void);
extern void ref_L00_003E2180_23(char *);

/* Creates a moving effect aimed at a target or along the player direction. */
char *func_PAL_L00_003E6400(char *pos, char *parent, char *target, float scale)
{
    float point[4], offset[4];
    char *object = ref_L00_003E2180_00(0xbfe);
    char *state, *data;
    float speed, lifetime;
    int valid, count;
    if (object) {
        state = *(char **)(object + 0x68);
        *(unsigned char *)(object + 0x30) = 255;
        *(unsigned short *)(object + 0x34) = 256;
        *(unsigned short *)(object + 0x32) = 255;
        object[0x31] = 1;
        *(char **)(object + 0xb8) = parent;
        object[0x20] = 0;
        *(float *)(state + 0x30) = scale;
        speed = ((struct E2Weapon *)((char *)ref_L00_003E2180_03 + ref_L00_003E2180_02 * 224))->speed * (0.020000001f);
        if (ref_L00_003E2180_01.mode == 1) {
            ref_L00_003E2180_04(state + 0x20, parent + 0xd0, -speed);
        } else if (target) {
            qcopy(point, target + 0x10);
            data = ref_L00_003E2180_05(target);
            if (data) {
                ref_L00_003E2180_06(target + 0x10, offset, 1);
                ref_L00_003E2180_07(offset, offset, *(float *)(data + 0x10));
                ref_L00_003E2180_08(point, point, offset);
            }
            ref_L00_003E2180_09(state + 0x20, point, pos);
            ref_L00_003E2180_04(state + 0x20, state + 0x20, speed);
        } else if (ref_L00_003E2180_01.flag) {
            ref_L00_003E2180_10(state + 0x20, pos, speed, 30.0f, 0.349065899848938f);
        } else {
            ref_L00_003E2180_04(state + 0x20, ref_L00_003E2180_01.v, speed);
        }
        qcopy(object + 0x10, pos);
        *(float *)(state + 0x2c) = speed;
        ref_L00_003E2180_11(object);
        lifetime = *(float *)(state + 0x30);
        lifetime /= speed;
        *(int *)(state + 0x38) = ref_L00_003E2180_12(lifetime);
        *(float *)(state + 0x3c) = 1.0f / ref_L00_003E2180_13(*(int *)(state + 0x38));
        *(float *)(object + 0x2c) = *(float *)(*(char **)(object + 0x24) + 0x24) * 6.0f;
        object[0x20] = 0;
        *(char **)(state + 0x1c) = target;
        if (target) {
            data = ref_L00_003E2180_05(target);
            if (data) *(unsigned short *)(data + 0x1e) |= 0x80;
        }
        *(float *)(state + 0x40) = 1.0f;
        *(float *)(state + 0x44) = ref_L00_003E2180_14(0.0f, 0.06981317698955536f);
        *(float *)(state + 0x48) = ref_L00_003E2180_14(0.0f, 0.13962635397911072f);
        *(float *)(state + 0x4c) = ref_L00_003E2180_14(0.0f, 0.27925270795822144f);
        *(float *)(object + 0xf0) = ref_L00_003E2180_15();
        *(float *)(object + 0xf4) = ref_L00_003E2180_15();
        *(float *)(object + 0xf8) = ref_L00_003E2180_15();
        *(float *)(state + 4) = ref_L00_003E2180_15();
        *(float *)(state + 8) = ref_L00_003E2180_15();
        *(float *)(state + 12) = ref_L00_003E2180_15();
        *(int *)(state + 0x14) = *(short *)(*(char **)(parent + 0x68) + 0x12);
        *(int *)(state + 0x18) = *(short *)(parent + 0xaa);
        valid = ref_L00_003E2180_16(*(int *)(state + 0x18), *(int *)(state + 0x14));
        if (!valid) {
            ref_L00_003E2180_19(object);
            return 0;
        }
        count = ref_L00_003E2180_17;
        ((struct E2CounterState *)state)->field_10 = 0;
        ref_L00_003E2180_18 = 0.0f;
        if ((unsigned int)count >= 16) ref_L00_003E2180_17 = 0;
        ((struct E2CounterState *)state)->slot = ref_L00_003E2180_17;
        if (++ref_L00_003E2180_17 >= 16) ref_L00_003E2180_17 = 0;
        *(int *)(state + 0x34) = ref_L00_003E2180_20(object, 1.0f, 1.0f, 1.0f, 0);
        ref_L00_003E2180_21(ref_L00_003E2180_22, object);
        ref_L00_003E2180_23(object);
    }
    return object;
}
