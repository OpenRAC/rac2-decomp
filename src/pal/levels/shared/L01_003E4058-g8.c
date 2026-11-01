#include "include_asm.h"

#include "common.h"
typedef int BounceWord128 __attribute__((mode(TI)));
typedef union { BounceWord128 word; float f[4]; } BounceVector;
typedef struct {
    BounceVector previous, position, velocity;
    unsigned char *hit;
    int *excluded;
    int mode;
    float radius, response, friction;
    int flags0, flags1, enabled, surface, active;
    float tolerance;
} BounceQuery;
extern void func_00282CC0(void *, void *, void *);
extern void func_00300190(void *, void *);
extern void func_00300248(int, int);
extern void func_002FEE70(int, void *, int);
extern void func_002FE880(void *, float *, float);
extern int func_002FE9D0(BounceQuery *);
extern int func_002AB1F0(unsigned char *);
extern void func_002FE8D8(void *, float *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_002E5CF8(int, int, char *);
extern char *ref_L00_003E7270_00(BounceWord128 *, BounceWord128 *);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern float func_00283B98(float, float);
extern void func_002A9288(void *, float);
extern float D_L00_001AFEC8;
extern float D_L00_001B0640 __attribute__((sda));
extern float D_L00_001B0644 __attribute__((sda));
extern unsigned char D_L00_001BF220[] __attribute__((nosda));
#define BF(p,o) (*(float *)((p)+(o)))
#define BI(p,o) (*(int *)((p)+(o)))
typedef struct {
    BounceVector previous;
    int excluded[2];
    BounceQuery query;
    BounceVector point, normal, offset;
} BounceWorkspace;

void func_PAL_L01_003ED1BC(unsigned char *object) {
    char *state = *(char **)(object + 0x68);
    BounceWorkspace work;
    int collision;
    char *info, *spawn;
    short category;
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
    case 1:
        qcopy(&work.previous, object + 0x10);
        func_00282CC0(object + 0x10, object + 0x10, state);
        func_00300190(object + 0x10, object + 0x10);
        func_00300248((int)state, (int)state);
        func_002FEE70(BI(state, 0x34), state, 0);
        func_002FE880(object + 0x10, (float *)state, D_L00_001AFEC8 * 0.00040000002f);
        work.excluded[0] = 0;
        work.excluded[1] = 0xA5A;
        qcopy(&work.query.previous, &work.previous);
        qcopy(&work.query.position, object + 0x10);
        qcopy(&work.query.velocity, state);
        work.query.hit = object;
        work.query.excluded = work.excluded;
        work.query.mode = 2;
        work.query.radius = 0.25f;
        work.query.response = D_L00_001B0640;
        work.query.friction = D_L00_001B0644;
        work.query.flags0 = 0;
        work.query.flags1 = 0;
        work.query.active = 0;
        collision = func_002FE9D0(&work.query);
        qcopy(object + 0x10, &work.query.position);
        qcopy(state, &work.query.velocity);
        qcopy(state + 0x20, &work.query.previous);
        if (collision == 2)
            object[0x20] = 2;
        if (work.query.hit) {
            category = *(short *)(*(char **)(work.query.hit + 0x24) + 0x46);
            if (category == 5 || category == 9 || (*(unsigned short *)(work.query.hit + 0x34) & 0x4000)) {
                info = (char *)func_002AB1F0(work.query.hit);
                func_002FE8D8(work.query.hit + 0x10, work.normal.f);
                qcopy(&work.point, object + 0x10);
                if (info) {
                    func_00282D30(&work.offset, &work.normal, BF(info, 0x10));
                    func_00282CC0(&work.point, &work.point, &work.offset);
                }
                func_00282D30(&work.normal, &work.normal, -3.0f);
                func_00282CC0(&work.normal, &work.normal, &work.point);
                object[0x20] = 2;
                qcopy(object + 0x10, D_L00_001BF220);
                qcopy(state + 0x20, D_L00_001BF220 + 0x20);
                func_00282F20(state + 0x20, state + 0x20, 1.0f);
                if (func_002761F8(&work.point, &work.normal, 2, work.query.hit, 0)) {
                    qcopy(object + 0x10, D_L00_001BF220);
                    qcopy(state + 0x20, D_L00_001BF220 + 0x20);
                    func_00282F20(state + 0x20, state + 0x20, 1.0f);
                }
            }
        }
        break;
    case 2:
        func_002E5CF8(0, 0, (char *)object);
        spawn = ref_L00_003E7270_00((BounceWord128 *)(object + 0x10), (BounceWord128 *)(state + 0x20));
        BI(spawn, 0xB8) = BI(state, 0x30);
        func_002FEE50(BI(state, 0x34));
        func_0029F338(object);
        return;
    }
    BF(object, 0xF0) = func_00283B98(BF(object, 0xF0), BF(state, 0x10));
    BF(object, 0xF4) = func_00283B98(BF(object, 0xF4), BF(state, 0x14));
    func_002A9288(object, 0.2f);
    if (BF(object, 0x10) < 2.0f || BF(object, 0x10) > 1021.0f ||
        BF(object, 0x14) < 2.0f || BF(object, 0x14) > 1021.0f ||
        BF(object, 0x18) < 2.0f || BF(object, 0x18) > 1021.0f) {
        func_002FEE50(BI(state, 0x34));
        func_0029F338(object);
    }
}
