#include "include_asm.h"
#include "common.h"

/* func_L00_003DC2D0 is matched in its own unit, src/levels/shared/L00_003DC2D0.c (default flags). */

extern int D_L00_001B043C __attribute__((sda));

extern int D_L00_001B2B44 __attribute__((sda));

int func_L00_003DE260(void)
{
    char *p = (char *)D_L00_001B043C;

    if (p == 0)
        return 0;
    return (unsigned int)((unsigned char)p[0x20] - 5) < 3;
}

int func_L00_003DF108(void)
{
    if (D_L00_001B043C == 0)
        return 0;
    return D_L00_001B2B44;
}

extern void func_L00_003B8138(void);

/* Writes the object's state byte (7 when arg0 is zero, 5 otherwise), lets the shared
 * updater run, then writes the caller's value in the object's slot - 10 when it is -1. */
void func_L00_003DF6B0(int arg0, int arg1)
{
    char *p = (char *)D_L00_001B043C;
    int a = arg1;
    char *q;

    if (p == 0)
        return;
    q = *(char **)(p + 0x68);
    if (arg0 != 0)
        p[0x20] = 5;
    else
        p[0x20] = 7;
    func_L00_003B8138();
    if (a != -1)
        *(int *)(q + 0x20) = a;
    else
        *(int *)(q + 0x20) = 10;
}

extern int D_L00_001B19C8[] __attribute__((sda));

extern char *D_L00_001B1EA8[] __attribute__((sda));

extern float D_L00_001B0430 __attribute__((sda));

extern float func_002EE2B0(char *a, char *b);

extern void func_00381F80(char *a, char *b);

/* walks the object list once the shared flag is set, stopping at either special state and
   otherwise acting on the entries whose handle reports type 0x13 */
void func_L00_003DF030(char *arg)
{
    char *o;

    if ((D_L00_001B19C8[0] & 1) == 0)
        return;

    for (o = D_L00_001B1EA8[0]; o != 0; o = *(char **)(o + 40)) {
        unsigned char state = *(unsigned char *)(o + 32);

        if (state == 0xFE)
            return;
        if (state == 0xFD)
            return;
        if (o == 0 || *(int *)(o + 36) == 0 || *(short *)(*(int *)(o + 36) + 70) != 0x13)
            continue;
        if (func_002EE2B0(o + 16, arg + 16) < D_L00_001B0430)
            func_00381F80(o, arg);
    }
}

/* A moby's update distance (0x30) and draw distance (0x32), as in RAC1's moby layout. */
struct BFObject {
    char pad[0x30];
    unsigned char field_30;
    unsigned char field_31;
    unsigned short field_32;
};

extern char *ref_L00_003DBF50_00(int);
extern float ref_L00_003DBF50_01(void);
extern float ref_L00_003DBF50_02(float, float);
extern int ref_L00_003DBF50_03 SDATA(ref_L00_003DBF50_03);
extern char *ref_L00_003DBF50_04;
extern char *ref_L00_003DBF50_05;
extern char *ref_L00_003DBF50_06;
extern char *ref_L00_003DBF50_07(char *);
extern void ref_L00_003DBF50_08(void);
/* The resident block at 0x189E20 (hero position at +0x80, hero moby at +0x2290). */
extern struct BFPlayer { char pad[0xbf8]; char *target; } D_00189E20 NOT_SDA;
extern float ref_L00_003DBF50_10(char *);
extern void ref_L00_003DBF50_11(char *, char *, char *, float);
extern void ref_L00_003DBF50_12(char *, char *);
extern float ref_L00_003DBF50_13 SDATA(ref_L00_003DBF50_13);
extern float ref_L00_003DBF50_14 SDATA(ref_L00_003DBF50_14);
extern void ref_L00_003DBF50_15(void *, void *, float);
extern int ref_L00_003DBF50_16(char *, float, float, float, int);

/* Spawns moby class 0xB2E at pos for parent and sets its state up (the three shared buffers
 * on first use), hands dir to the target record at D_00189E20 + 0xBF8 when there is one,
 * and passes dir with a random spread and a random speed through ref_L00_003DBF50_15. */
char *func_L00_003DBF50(char *parent, int arg, char *pos, char *dir)
{
    float velocity[4];
    char *object = ref_L00_003DBF50_00(0xb2e);
    char *state;
    float length;

    if (object) {
        object[0x20] = 0;
        state = *(char **)(object + 0x68);
        ((struct BFObject *)object)->field_30 = 255;
        ((struct BFObject *)object)->field_32 = 255;
        *(float *)(state + 0x64) = ref_L00_003DBF50_01();
        *(float *)(state + 0x68) = ref_L00_003DBF50_02(0.3723369836807251f, 0.6283186078071594f);
        *(int *)(state + 0x74) = *(short *)(parent + 0xaa);
        *(int *)(state + 0x7c) = 0;
        qcopy(object + 0x10, pos);
        *(float *)(object + 0x2c) = ref_L00_003DBF50_02(0.01f, 0.0125f);
        *(unsigned short *)(object + 0x34) |= 0x100;
        *(int *)(object + 0x78) = 0x7f4080ff;
        *(int *)(state + 0x70) = arg;
        {
            char *parentState = *(char **)(parent + 0x68);

            if (!ref_L00_003DBF50_03) {
                char *p = *(char **)(parentState + 8);

                ref_L00_003DBF50_04 = p;
                p = ref_L00_003DBF50_07(p + 0x100);
                ref_L00_003DBF50_05 = p;
                p = ref_L00_003DBF50_07(p + 0x4b00);
                ref_L00_003DBF50_06 = p;
                ref_L00_003DBF50_07(p + 0xa0);
                ref_L00_003DBF50_08();
                ref_L00_003DBF50_03 = 1;
            }
        }
        if (D_00189E20.target) {
            length = ref_L00_003DBF50_10(dir);
            if (length == 0.0f)
                length = 1.0f;
            ref_L00_003DBF50_11(D_00189E20.target, pos, dir, length);
            qcopy(state, dir);
        } else {
            ref_L00_003DBF50_12(object, state);
        }
        qcopy(velocity, dir);
        velocity[0] += ref_L00_003DBF50_02(-0.15f, 0.15f);
        velocity[1] += ref_L00_003DBF50_02(-0.15f, 0.15f);
        length = ref_L00_003DBF50_02(ref_L00_003DBF50_13 * (1.0f / 60.0f),
                                     ref_L00_003DBF50_14 * (1.0f / 60.0f));
        ref_L00_003DBF50_15(velocity, velocity, length * 0.5f);
        *(int *)(state + 0x6c) = 96;
        *(int *)(state + 0x60) = 680;
        *(int *)(state + 0x78) = ref_L00_003DBF50_16(object, 1.0f, 1.0f, 1.0f, 0);
    }
    return object;
}


extern float func_00283B98(float, float);
extern void func_00282C88(void *);
extern void func_002833F0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A8C00(void *, int, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern int func_002A8C28(int, float, void *, int, float, float, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002AD330(void *, int, void *, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_002AD0E0(void *, int, void *, void *, void *, void *);
extern void func_002AD250(void *, int, void *, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int,
                          float, int, int, int, int, int);
extern void func_0029F338(void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L00_003DFDC0(void *);
extern int D_L00_001BF218 NOT_SDA;
extern int D_L00_001B0518 __attribute__((sda));
extern char D_L00_001A8F20[] MACRO_ADDR;

/* state 0: advances the object by its data's velocity; a collision deals damage and destroys it unless
   D_L00_001BF218 equals the data's type, otherwise it spawns three trail particles and grows its scale
   factor; state 1: spawns an explosion and deletes the object */
void func_L00_003DF710(char *object)
{
    float scale[4];
    float next[4];
    char query[48];
    float velocity[4];
    float zero[4];
    float pos[4];
    char *data = *(char **)(object + 0x68);
    float size0, size1, size2, spread;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(float *)(data + 0x18) = func_00283B98(*(float *)(data + 0x18), *(float *)(data + 0x1c));
        func_00282C88(scale);
        scale[1] = *(float *)(data + 0x18) * 0.25f;
        scale[0] = *(float *)(data + 0x18) * 0.5f;
        scale[2] = *(float *)(data + 0x18);
        func_002833F0(object + 0xc0, scale);
        func_00282CC0(next, object + 0x10, data);
        func_002A8C00(query, *(int *)(data + 0x10), 1, data, *(float *)(data + 0x14));
        *(unsigned short *)(query + 0x1a) = *(unsigned short *)(object + 0xaa);
        if (func_002761F8(object + 0x10, next, 0, object, query) || func_00277258(object + 0x10, 0, object, 0.3f)) {
            if (D_L00_001BF218) {
                if (D_L00_001BF218 != *(int *)(data + 0x10)) {
                    func_002A8C28(*(int *)(data + 0x10), 0.3f, object + 0x10, 0x10001, *(float *)(data + 0x14), 0, 0, 1, 0);
                    func_002A7750(object, 1, -1);
                    return;
                }
            } else {
                func_002A8C28(*(int *)(data + 0x10), 0.3f, object + 0x10, 0x10001, *(float *)(data + 0x14), 0, 0, 1, 0);
                func_002A7750(object, 1, -1);
                return;
            }
        }
        qcopy(object + 0x10, next);
        func_00282D30(velocity, data, -0.5f);
        func_00282C88(zero);
        if (*(int *)(data + 0x24)) {
            func_002AD330(object, *(int *)(data + 0x24), object + 0x10, pos);
            func_00282CC0(velocity, velocity, pos);
        }
        size0 = func_002A7878(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = func_002A7878(0.2f, 0.4f);
        func_002C65A0(object + 0x10, velocity, 5, D_L00_001B0518, 3, 0x4f, 0, size0,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        qcopy(pos, object + 0x10);
        pos[0] += func_002A78D8(0.0f, 0.15f);
        pos[1] += func_002A78D8(0.0f, 0.15f);
        pos[2] += func_002A78D8(0.0f, 0.15f);
        size1 = func_002A7878(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = func_002A7878(0.1f, 0.3f);
        func_002C65A0(pos, velocity, 5, D_L00_001B0518, 7, 0x5f, 0, size1,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        pos[0] += func_002A78D8(0.0f, 0.15f);
        pos[1] += func_002A78D8(0.0f, 0.15f);
        pos[2] += func_002A78D8(0.0f, 0.15f);
        size2 = func_002A7878(1.0f, 1.5f) * (*(float *)(data + 0x20) * 210000.0f);
        spread = func_002A7878(0.2f, 0.4f);
        func_002C65A0(pos, velocity, 5, D_L00_001B0518, 12, 0x7f, 0, size2,
                      spread * (*(float *)(data + 0x20) * 210000.0f), 0.0f, 0);
        if (*(int *)(data + 0x24)) {
            func_002AD0E0(object, *(int *)(data + 0x24), object + 0x10, object + 0xf0, object + 0x10, object + 0xf0);
            func_002AD250(object, *(int *)(data + 0x24), data, data);
        }
        break;
    case 1:
        func_002ABBB8(object, D_L00_001A8F20, object + 0x10, 0.0f, 0.0f, 10, 0, 16, 0.0f, 0.0f, 9.0f, 1.0f, -1,
                      15.0f, 0, 9, -1, 0, 0x810001);
        func_0029F338(object);
        return;
    }
    if (*(float *)(data + 0x20) < 1.0f)
        *(float *)(data + 0x20) += 0.025f;
    *(float *)(object + 0x2c) = func_002A7878(0.01f, 0.0125f) * *(float *)(data + 0x20);
    func_L00_002E6EF8(func_L00_003DFDC0, object);
}
