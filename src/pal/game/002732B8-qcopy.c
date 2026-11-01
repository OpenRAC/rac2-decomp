#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x20];
    unsigned char *obj;
    short flag;
    char pad26[10];
} F273418Mark;
typedef struct {
    F273418Mark e[6];
    int count;
} F273418Marks;
extern int D_0018C0B4;
extern int D_001A7348[] __attribute__((sda));
extern F273418Marks D_001B7600;
extern void func_PAL_00272B50(void);
extern void func_00279BD8(void *, void *);
extern void func_002729A0(void *, float, float);
extern float func_00283CE0(int);

void func_PAL_002732B8(void) {
    float base[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    F273418Mark *m;
    int i;

    if (D_0018C0B4 == 111) {
        D_001B7600.count = 0;
        return;
    }
    func_PAL_00272B50();
    if (D_001B7600.count != 0) {
        base[0] = func_00283CE0(D_001A7348[0]);
        base[1] = func_00283CE0(D_001A7348[1]);
        for (i = 0; i < D_001B7600.count; i++) {
            m = &D_001B7600.e[i];
            if (m->obj != 0 && m->obj[0x20] != 0xFE && m->obj[0x20] != 0xFD) {
                if (m->flag != 0) {
                    func_00279BD8(vec, m);
                    vec[0] = (vec[0] - func_00283CE0(D_001A7348[2])) * 0.0625f;
                    vec[1] = (vec[1] - func_00283CE0(D_001A7348[3])) * 0.0625f;
                } else {
                    qcopy(vec, base);
                }
                func_002729A0(m, vec[0], vec[1]);
            }
        }
        D_001B7600.count = 0;
    }
}
