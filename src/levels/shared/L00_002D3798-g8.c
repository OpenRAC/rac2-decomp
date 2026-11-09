#include "common.h"

/* func_L00_002D5940 is here rather than in L00_002D3798.c because its tuning floats are read
   through $gp (-G8). */

typedef int Quad5940 __attribute__((mode(TI)));

typedef struct {
    float bounds[4];            /* 0x00; [3] is the radius */
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x10];
    unsigned char drawn;        /* 0x31 */
    char pad32[0x2];
    unsigned short modeBits;    /* 0x34 */
    char pad36[0x2E];
    void (*update)(void *);     /* 0x64 */
    char pad68[0x42];
    short oClass;               /* 0xAA */
    char padAC[0x14];
    float rotMatrix[3][4];      /* 0xC0 */
    float rotation[4];          /* 0xF0 */
} Moby5940;

typedef struct {
    char pad0000[0x80];
    float position[4];          /* 0x0080 */
    char pad0090[0xC0];
    float velocity[4];          /* 0x0150 */
    char pad0160[0x14];
    float speed;                /* 0x0174 */
    char pad0178[0x1C8];
    int f340;                   /* 0x0340 */
    char pad0344[0x3EC];
    float transform[12];        /* 0x0730 */
    Quad5940 vector760;         /* 0x0760 */
    Quad5940 vector770;         /* 0x0770 */
    char pad0780[0xAA0];
    Moby5940 *object;           /* 0x1220 */
    char pad1224[0xC];
    int flags;                  /* 0x1230 */
    char pad1234[0x8];
    unsigned char visible;      /* 0x123C */
    char pad123D[0xB];
    int weapon;                 /* 0x1248 */
    char pad124C[0x254];
    float transitionPos[4];     /* 0x14A0 */
    float transitionRot[4];     /* 0x14B0 */
    float rotation[4];          /* 0x14C0 */
    char pad14D0[0x28];
    float blend;                /* 0x14F8 */
    float blendVelocity;        /* 0x14FC */
    char pad1500[0x4];
    float offsetVelocity;       /* 0x1504 */
    float offset;               /* 0x1508 */
    float offsetTarget;         /* 0x150C */
    float angle;                /* 0x1510 */
    float angleVelocity;        /* 0x1514 */
    char pad1518[0xD78];
    int owner;                  /* 0x2290 */
} Hero5940;

extern Hero5940 D_00189E20;
extern char D_L00_001B8FF0[], D_L00_001B8DC0[], D_L00_001BF220[];
extern Quad5940 D_L00_001B8DD0;
/* Incomplete sda arrays are read with the assembler's lui/load macro, as in retail. */
extern unsigned char D_001A7A44[] __attribute__((sda));
extern int D_L00_001B19C8[] __attribute__((sda));
extern float D_L00_001A7FE4[] __attribute__((sda));
extern const float D_L00_001A7FE0 __attribute__((sda));
extern float D_L00_001A7CE0 __attribute__((sda)), D_L00_001A7CE4 __attribute__((sda));

extern int func_L00_002ADED8(int);
extern void func_002A0F48(void *);
extern char *func_L00_002F3DA8(int);
extern int func_L00_002D6418(void);
extern void func_00283658(void *, void *);
extern void func_002AA2E8(float *, float, float);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_00283B98(float, float), func_00283198(float);
extern void func_002830C0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00283410(void *, void *), func_00283738(void *, void *, void *);
extern void func_002AB6D8(void *, void *), func_002A91F0(void *, void *);
extern void func_00283098(void *, void *, void *), func_00282D08(void *, void *, void *, float);
extern void func_00283810(void *, void *, void *, float), func_00283958(void *, void *);
extern void func_00282D30(void *, void *, float), func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_00283678(void *, void *);

/* Places the hero's held object (D_00189E20.object): from the weapon's mount offset and
   rotation, a turning bob angle, the blend from the transition pose while blend < 1, and a
   ground probe that limits the vertical offset to [-1.5, 0]. */
void func_L00_002D5940(void) {
    Moby5940 *obj = D_00189E20.object;
    char *mount;
    float m[16], rot[16], offset[4], temp[4], a[4], b[4];
    float turn, height, scale, target;
    int state;

    if (!obj)
        return;
    if (obj->oClass == 0x47) {
        if (!D_00189E20.visible && !obj->state) {
            obj->drawn = 0;
            obj->modeBits |= 1;
        } else {
            obj->drawn = 1;
            obj->modeBits &= ~1;
        }
        return;
    }
    if (func_L00_002ADED8(0)) {
        obj->modeBits |= 1;
        obj->drawn = 0;
        if (obj->update)
            obj->update(obj);
        func_002A0F48(obj);
        return;
    }

    mount = func_L00_002F3DA8(D_00189E20.weapon);
    func_00283658(m, D_L00_001B8FF0);
    qcopy_nc(&m[12], D_L00_001B8FF0 - 0x230);
    m[15] = 1.0f;
    qcopy_nc(offset, mount);
    offset[0] += D_00189E20.offset;
    if (D_001A7A44[0] && !func_L00_002D6418())
        offset[1] = -offset[1];

    /* Turn rate in degrees per second (FE4 while moving, FE0 otherwise) to radians per frame. */
    if (D_00189E20.speed > 0.02f)
        turn = D_L00_001A7FE4[0] * 0.0002908882452175021f;
    else
        turn = D_L00_001A7FE0 * 0.0002908882452175021f;
    func_002AA2E8(&D_00189E20.angleVelocity, turn, 0.006981317885220051f);
    D_00189E20.angle = func_00283B98(D_00189E20.angle, D_00189E20.angleVelocity);
    offset[2] += func_00283198(D_00189E20.angle) * 0.02f;

    func_002830C0(obj->position, offset, m);
    if (!func_L00_002D6418())
        func_00282CC0(obj->position, obj->position, D_00189E20.velocity);
    func_00283410(rot, mount + 0x10);
    func_00283738(obj->rotMatrix, m, rot);
    func_002AB6D8(obj->rotMatrix, obj->rotation);
    func_002A91F0(D_00189E20.rotation, obj->rotation);

    if (D_00189E20.blend < 1.0f) {
        func_002AA548(&D_00189E20.blend, &D_00189E20.blendVelocity, 1.0f,
                      D_L00_001A7CE0 * 0.016666667f, D_L00_001A7CE4 * 0.00027777778f,
                      D_L00_001A7CE0 * 0.016666667f);
        func_00283098(temp, D_00189E20.transitionPos, &D_00189E20);
        func_00282CC0(temp, temp, D_00189E20.position);
        func_00282D08(obj->position, temp, obj->position, D_00189E20.blend);
        func_002A91F0(a, obj->rotation);
        func_00283810(b, D_00189E20.transitionRot, a, D_00189E20.blend);
        func_00283958(b, obj->rotMatrix);
    }

    obj->drawn = 1;
    obj->modeBits &= ~1;
    func_002A0F48(obj);

    if ((D_L00_001B19C8[0] ^ 1) & 1) {
        scale = 0.0009765625f;
        height = obj->bounds[3] * scale;
        func_00282D30(temp, obj->bounds, scale);
        func_00282F20(a, obj->rotMatrix[1], height * -1.2f);
        func_00282CC0(a, a, temp);
        if (func_002761F8(D_L00_001B8DC0, a, 0, D_00189E20.owner, 0)) {
            target = (D_00189E20.offset - height) + func_00282E48(D_L00_001BF220, temp);
            D_00189E20.offsetTarget = target;
            if (target > 0.0f)
                D_00189E20.offsetTarget = 0.0f;
            else if (target < -1.5f)
                D_00189E20.offsetTarget = -1.5f;
        } else {
            D_00189E20.offsetTarget = 0;
        }
    }

    func_002AA548(&D_00189E20.offset, &D_00189E20.offsetVelocity, D_00189E20.offsetTarget,
                  0.0041666669f, 0.0041666669f, 0.083333336f);
    func_00283678(D_00189E20.transform, m);
    qcopy_nc(&D_00189E20.vector760, m);
    qcopy_nc(&D_00189E20.vector770, &D_L00_001B8DD0);

    state = func_L00_002D6418();
    if (state)
        D_00189E20.flags |= 5;
    if (obj->update)
        obj->update(obj);
    if (state)
        D_00189E20.flags &= ~5;
}

/* func_L00_002D5EB8 */
extern int D_0018C350[];
extern unsigned char D_001A7A00[] __attribute__((sda));
extern int D_0018C2EC[];
extern unsigned char D_001A7A28[] MACRO_ADDR;
extern unsigned char D_00139568[];
extern int D_L00_001A903C;
extern unsigned short D_0018C958 __attribute__((section(".data")));
extern int D_00139868[];
extern int D_001A7398[] MACRO_ADDR;
extern unsigned char D_001A7AF8[] MACRO_ADDR;

/* One 0xE0-byte entry of D_L00_00262570, indexed through D_00139568. */
typedef struct {
    int exists;                 /* 0x00 */
    unsigned char state;        /* 0x04 */
    char pad05[0x7];
    int index;                  /* 0x0C */
    char pad10[0x3A];
    short value;                /* 0x4A */
    char pad4C[0x20];
    int limit;                  /* 0x6C */
    char pad70[0x70];
} Entry1269;

extern Entry1269 D_L00_00262570[];
extern int func_L00_002D5E30(int *, int *, int *);
extern void func_0028A180(int, int);
extern void func_L00_003F1300(void);
extern void func_L00_0030C7F8(int);
extern void func_002B0A18(int, int);
extern int func_002E5E58(int, int, void *);
extern int func_00288D58(void);
extern int func_00287F60(int);
extern void func_L00_0037E6A8(int, int);
extern void func_00287EB0(int);
extern void func_00288508(int);
extern int ref_L00_002D5EB8_00 __attribute__((sda));

static inline int special(int i)
{
    int r = 0;

    switch (i) {
    case 12:
    case 14:
    case 17:
    case 18:
    case 53:
        r = 1;
        break;
    }
    return r;
}

static inline int unlocked(Entry1269 *e, int i)
{
    if (e->state >= 2 || (e->state == 1 && special(i)))
        return 1;
    return 0;
}

static inline int owned(int i)
{
    if (D_L00_00262570[D_00139568[i]].exists) {
        int n = func_00287F60(i);
        if (n >= 2 || (n == 1 && special(i)))
            return 1;
    }
    return 0;
}

void func_L00_002D5EB8(void)
{
    int count, i, j, ok;

    if ((D_L00_001B19C8[0] & 15) == 1 && D_L00_001B19C8[0] != 1)
        return;
    count = 4;
    {
        int *p = D_0018C350;
        func_L00_002D5E30(p, p - 1, &count);
    }
    for (j = 0; j < 10; j++)
        if (D_001A7A28[j])
            count++;
    if (*(int *)D_001A7A00 != count) {
        if (ref_L00_002D5EB8_00 >= 11 && *(int *)D_001A7A00 < count) {
            if (!D_0018C958)
                func_0028A180(0x9A9, 0);
            func_L00_003F1300();
            func_L00_0030C7F8(0x168);
            func_002B0A18(0x1235, -1);
            func_002E5E58(6, 0, 0);
        }
        D_0018C2EC[0] = count;
        *(int *)D_001A7A00 = count;
    }

    for (i = 0; i < 56; i++) {
        if ((D_L00_00262570 + D_00139568[i])->state) {
            if (!func_00288D58())
                continue;
            if (func_00287F60(i) == 1)
                continue;
        }
        {
            Entry1269 *e = &D_L00_00262570[D_00139568[i]];
            int sel = 0;
            if (e->exists)
                sel = e->state == 3;
            if (sel)
                continue;
        }
        if (func_00287F60(i) <= 0)
            continue;
        {
            Entry1269 *e = &D_L00_00262570[D_00139568[i]];
            if ((D_00139868[i] >> 5) < e->limit || e->limit <= 0)
                continue;
            if (i == 31 || i == 9 || i == 45) {
                func_L00_0037E6A8(i, D_L00_00262570[D_00139568[i]].value);
                continue;
            }
            if (D_00189E20.weapon == i) {
                if (!D_00189E20.f340)
                    continue;
                if (D_001A7398[e->index] != i)
                    continue;
                func_L00_0037E6A8(i, e->value);
                continue;
            }
        }
        if (func_00288D58()) {
            Entry1269 *e = &D_L00_00262570[D_00139568[i]];
            if (!e->exists)
                continue;
            if (unlocked(e, i)) {
                if (owned(i)) {
                    func_00287EB0(i);
                    func_00288508(i);
                }
            }
        } else {
            func_00287EB0(i);
            func_00288508(i);
        }
    }

    if ((D_L00_001B19C8[0] & 127) || D_001A7A00[0x7A])
        return;
    ok = 1;
    for (i = 0; i < 56; i++) {
        int ex = D_L00_00262570[D_00139568[i]].exists;
        if (ex && i == 10)
            continue;
        if (ex && i == 9)
            continue;
        if (ex) {
            if (!D_001A7AF8[i]) {
                ok = 0;
                break;
            }
            if (i == 14 || i == 12 || i == 17 || i == 18 || i == 53)
                continue;
            if (func_00287F60(i) <= 0)
                continue;
            if (!D_L00_00262570[D_00139568[i]].state) {
                ok = 0;
                break;
            }
        }
    }
    if (ok && !D_001A7A00[0x7A]) {
        D_001A7A00[0x7A] = 1;
        func_002E5E58(1, 0, 0);
        func_002B0A18(0x1233, -1);
        D_L00_001A903C = 1;
    }
}
