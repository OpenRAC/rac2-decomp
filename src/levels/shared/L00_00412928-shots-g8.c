#include "common.h"

/* func_L00_0041A5C0 reads its entry table through $gp, hence -G8. */

typedef unsigned int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
typedef struct { V pos, vel, accel; int next, active, handle, pad; } Entry;
typedef struct {
    char pad[0x18];
    char *target;
    int count;
    V point;
    char gap[0x10];
    V normal;
} Collision;
typedef struct { char pad[0x70]; float direct, splash; char rest[0x68]; } ClassEntry;

extern Entry *D_L00_001B144C __attribute__((sda));
extern Collision D_L00_001BF200;
extern char D_L00_001C3280[];
extern unsigned char D_00139568[];
extern char D_00189E20[];
extern ClassEntry D_L00_00262570[] NOT_SDA;

extern void func_00300190(void *, void *);
extern void func_002FEE70(int, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282F20(void *, void *, float);
extern void func_002FEE50(int);
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_002BE278(void *, void *, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_0032D758(void *, int, void *);
extern void func_002E5CF8(int, int, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0041B840(void *, void *, void *, void *);
extern void func_L00_0041AD40(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_001163B0(void);
extern float func_002A7878(float, float);

void func_L00_0041A5C0(char *object)
{
    V next, temp, small, angles, rot[4], direction;
    struct {
        V direction;
        char pad[8];
        unsigned char type, flag;
        unsigned short id;
        int pad2, enabled;
        char tail[12];
    } hit;
    char *state = *(char **)(object + 0x68);
    int i, index = *(int *)(state + 0x48);
    char *resident;
    Entry *e;
    char *target;
    int n, j, nextIndex;
    ClassEntry *c;

    for (i = 0; i < *(int *)(state + 0x44); i++) {
        resident = D_00189E20;
        e = D_L00_001B144C + index;
        if (i)
            func_00300190(e, e);
        if (e->handle >= 0)
            func_002FEE70(e->handle, &e->vel, e);
        func_00282CC0(&next, e, &e->vel);
        if (!e->active) {
            if (func_002761F8(e, &next, 0x10, object, 0)) {
                qcopy(e, &D_L00_001BF200.point);
                func_00282C88(&e->vel);
                func_00282F20(&temp, &D_L00_001BF200.normal, 0.1f);
                func_00282CC0(e, e, &temp);
                e->active = 1;
                func_002FEE50(e->handle);
                e->handle = -1;
                qcopy_nc(&e->accel, &temp);
                func_00282F20(&small, &temp, 0.01f);
                angles.f[0] = func_002A7878(-0.7853981853f, 0.7853981853f);
                angles.f[1] = func_002A7878(-0.7853981853f, 0.7853981853f);
                angles.f[2] = func_002A7878(-0.7853981853f, 0.7853981853f);
                func_00283410(rot, &angles);
                rot[3].f[0] = 0;
                rot[3].f[1] = 0;
                rot[3].f[2] = 0;
                func_002830C0(&small, &small, rot);
                func_002BE278(e, &small, 0, -1);
                func_00282C88(&angles);
                target = D_L00_001BF200.target;
                if (target && target != *(char **)(resident + 0x2290)
                    && ((*(unsigned short *)(target + 0x34) & 0x1000)
                        || *(short *)(*(char **)(target + 0x24) + 0x46) == 5)) {
                    nextIndex = index - 1;
                    func_00282CF0(&direction, target + 0x10, object + 0x10);
                    func_00282F20(&direction, &direction, 1);
                    func_00282F20(&hit, &hit, 1);
                    c = &D_L00_00262570[D_00139568[0x1d]];
                    func_002A8C00(&hit, object, 0x910000, &direction, c->direct);
                    hit.direction.q = direction.q;
                    hit.direction.f[3] = 5627.9248046875f;
                    hit.type = 9;
                    hit.enabled = 1;
                    hit.flag = 1;
                    hit.id = *(unsigned short *)(D_L00_001BF200.target + 0xaa);
                    func_002A8E20(D_L00_001BF200.target, &hit);
                    func_0032D758(D_L00_001BF200.target, 0x1d, object);
                    func_002E5CF8(1, 0, object);
                    n = func_00277F48(D_L00_001BF200.target + 0x10, 0x10, object, 0, 1.5f);
                    for (j = 0; j < n; j++) {
                        target = ((char **)D_L00_001C3280)[j];
                        if (target == *(char **)(resident + 0x2290))
                            continue;
                        func_00282CF0(&direction, target + 0x10, object + 0x10);
                        func_00282F20(&direction, &direction, 1);
                        func_00282F20(&hit, &hit, 1);
                        c = &D_L00_00262570[D_00139568[0x1d]];
                        func_002A8C00(&hit, object, 0x910000, &direction, c->splash);
                        hit.direction.q = direction.q;
                        hit.direction.f[3] = 5627.9248046875f;
                        hit.type = 9;
                        hit.enabled = 1;
                        hit.flag = 1;
                        hit.id = *(unsigned short *)(((char **)D_L00_001C3280)[j] + 0xaa);
                        func_002A8E20(((char **)D_L00_001C3280)[j], &hit);
                        func_0032D758(((char **)D_L00_001C3280)[j], 0x1d, object);
                        func_002E5CF8(1, 0, object);
                        /* The block must not end in the call: flow would pad it with a
                         * (use 0) insn, which lengthens the inner pointers' live ranges
                         * and hands `object` the wrong saved register. */
                        target = 0;
                    }
                } else {
                    nextIndex = index - 1;
                    if (func_001163B0() % 11 == 0)
                        func_L00_0041B840(object, &D_L00_001BF200.point, &temp, &angles);
                }
            } else {
                func_002FE880(e, &e->vel, 0.006f);
                nextIndex = index - 1;
            }
        } else {
            nextIndex = index - 1;
        }
        func_00282CC0(e, e, &e->vel);
        index = nextIndex;
        if (nextIndex < 0)
            index = 0x22;
        if (func_001163B0() % 7 == 0) {
            func_00282F20(&temp, &e->vel, 0.05f);
            func_L00_0041AD40(object, e, &e->vel);
        }
        if (func_001163B0() % 22 == 0) {
            func_00282F20(&temp, &e->vel, 0.05f);
            func_002BE278(e, &temp, 0, -1);
        }
    }
}
