#include "common.h"

typedef int Vec128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x46];
    short kind;
} Type2318;
typedef struct {
    char pad0[0x10];
    float pos[4];
    unsigned char state;
    char pad1[3];
    Type2318 *type;
    char pad2[0x34 - 0x28];
    unsigned short flags;
    char pad3[0x78 - 0x36];
    int colour;
    char pad4[0xc0 - 0x7c];
    float mat[16];
} Obj2318;

extern unsigned char D_001A7B00[] __attribute__((sda));
extern int func_00282948(void *);
extern Obj2318 *D_L00_001FACE0[];
extern int func_002AB1F0(void *);
extern float func_00282E20(void *);
typedef struct {
    char pad[9];
    unsigned char index;
} ItemSelector2318;
extern ItemSelector2318 D_00139568;
extern unsigned char D_00139571;
typedef struct {
    char pad0[4];
    unsigned char flag;
    char pad1[0x58 - 5];
    int count;
    char pad2[224 - 0x5c];
} Record2318;
extern Record2318 D_L00_00262570[];
extern void func_L00_0040B838(void *, int, void *, int);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
typedef struct {
    char pad[0x64];
    unsigned char *owner;
} Owner2318;
extern Owner2318 D_L00_001FE940;
extern char D_L00_001A8F20[] MACRO_ADDR;
extern char *func_002C16C0(void *, void *, int, int, int, int, float, float, float, float, float);

extern int func_L00_002ADEA0(int);
extern void func_00282CF0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
typedef struct {
    char pad0[0x80]; float position[4];
    char pad1[0x98-0x90]; float heading;
    char pad2[0x1314-0x9c]; Obj2318 *weapon;
    char pad3[0x18d0-0x1318]; Obj2318 *target; int active, timer;
    char pad4[0x2010-0x18dc]; float point[4] __attribute__((aligned(16)));
    char pad5[0x2290-0x2020]; int owner;
    char pad6[0x22b4-0x2294]; unsigned char mode;
    char pad7[0x24fc-0x22b5]; short blocked;
} Hero2318;
extern Hero2318 D_00189E20;

void func_L00_002B2318(void) {
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float angle;
    int i;
    int j;
    int k;
    char *effect;
    Record2318 *record;

    if (D_00189E20.active && !D_00189E20.mode && (D_001A7B00[1] || D_001A7B00[0x41])) {
        if ((func_L00_002ADEA0(3) == 3 || func_L00_002ADEA0(3) == 2) && !D_00189E20.blocked) {
            if (func_00282948(&D_00189E20.timer)) {
                Obj2318 *object;
                for (k = 0; (object = D_L00_001FACE0[k]) != 0; k++) {
                    if (object->type && object->type->kind == 5 && object && object->state != 254 && object->state != 253 && func_002AB1F0(object)) {
                        func_00282CF0(v, object->pos, D_00189E20.position);
                        if (!(16.0f < func_00282E20(v))) D_00189E20.target = object;
                    }
                }
                if (D_00189E20.target && D_00189E20.target->type->kind == 5 && D_00189E20.target->state != 254 && D_00189E20.target->state != 253
                    && func_002761F8(D_00189E20.point, D_00189E20.target->pos, 0, D_00189E20.owner, 0)) {
                    func_00282CF0(v, D_00189E20.target->pos, D_00189E20.position);
                    if (func_00282E20(v) < 16.0f) {
                        record = &D_L00_00262570[D_00139568.index];
                        if (record->count > 0) {
                            if (record->flag) func_L00_0040B838(D_00189E20.point, D_00189E20.owner, D_00189E20.target, 1);
                            else func_L00_0040B838(D_00189E20.point, D_00189E20.owner, D_00189E20.target, 0);
                            { Record2318 *r = &D_L00_00262570[D_00139568.index];
                            D_00189E20.timer = 120;
                            r->count--; }
                        } else {
                            D_00189E20.active = 0;
                            D_L00_00262570[D_00139568.index].count = 30;
                        }
                    }
                }
            } else {
                angle = func_00283C80(func_00283248(D_00189E20.target->pos[0] - D_00189E20.position[0], D_00189E20.target->pos[1] - D_00189E20.position[1]), D_00189E20.heading);
                if (angle > 1.3962636f && D_L00_00262570[D_00139568.index].flag) {
                    Obj2318 *weapon = D_00189E20.weapon;
                    weapon->colour = 0x800000ff;
                    weapon->flags |= 0x10;
                    qcopy(v, D_00189E20.point);
                    func_0029FCC0(weapon, 6, a);
                    func_0029FCC0(weapon, 7, b);
                    *(Vec128 *)c = 0;
                    *(Vec128 *)d = 0;
                    c[0] = -0.025f; c[1] = 0.01f; c[2] = 0.04f;
                    d[0] = -0.025f; d[1] = -0.01f; d[2] = 0.04f;
                    func_00283098(c, c, weapon->mat);
                    func_00282CC0(a, a, c);
                    func_00283098(d, d, weapon->mat);
                    func_00282CC0(b, b, d);
                    for (i = 0; i < 30; i++) {
                        a[0] += func_002A78D8(0.0f, 0.004f);
                        a[1] += func_002A78D8(0.0f, 0.004f);
                        a[2] += func_002A78D8(0.0f, 0.004f);
                        b[0] += func_002A78D8(0.0f, 0.004f);
                        b[1] += func_002A78D8(0.0f, 0.004f);
                        b[2] += func_002A78D8(0.0f, 0.004f);
                        effect = func_002C16C0(a, D_L00_001A8F20, 2, 127, 0x2020ff, func_00283CF0(func_002A78D8(1.0f, -1.0f)), 25200.0f, 500.0f, 1.0f, 0.0f, 0.0f);
                        if (effect) effect[2] = *D_L00_001FE940.owner;
                        effect = func_002C16C0(b, D_L00_001A8F20, 2, 127, 0x2020ff, func_00283CF0(func_002A78D8(1.0f, -1.0f)), 25200.0f, 500.0f, 1.0f, 0.0f, 0.0f);
                        if (effect) effect[2] = *D_L00_001FE940.owner;
                    }
                }
                qcopy(v, D_00189E20.point);
                if (angle < 1.3962636f) {
                    for (j = 0; j < 20; j++) {
                        a[0] = v[0] + func_002A78D8(0.0f, 0.04f);
                        a[1] = v[1] + func_002A78D8(0.0f, 0.04f);
                        a[2] = v[2] + func_002A78D8(0.0f, 0.04f);
                        record = &D_L00_00262570[D_00139568.index];
                        /* Identical arms: retail still reads this flag into $v0 and the next call clobbers it, the
                           dead load jump2's cross-jump leaves. One arm is 36 bytes short of retail. */
                        if (record->flag) {
                            effect = func_002C16C0(a, D_L00_001A8F20, 2, 127, 0x20ff20, func_00283CF0(func_002A78D8(1.0f, -1.0f)), 31500.002f, 500.0f, 1.0f, 0.0f, 0.0f);
                            if (effect) effect[2] = *D_L00_001FE940.owner;
                        } else {
                            effect = func_002C16C0(a, D_L00_001A8F20, 2, 127, 0x20ff20, func_00283CF0(func_002A78D8(1.0f, -1.0f)), 31500.002f, 500.0f, 1.0f, 0.0f, 0.0f);
                            if (effect) effect[2] = *D_L00_001FE940.owner;
                        }
                    }
                }
            }
        }
    }
}
