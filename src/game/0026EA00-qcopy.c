#include "include_asm.h"
#include "common.h"

/* The three resident copy helpers in this unit need the grouped `lq`/`sq`
   profile with its scheduler barrier (-frac2-qcopy -frac2-qcopy-barrier). */

typedef int TI128 __attribute__((mode(TI)));

extern char D_001B5490[];
extern char D_001B5570[];
extern int func_00271130(void *, void *);
extern int func_002712D8(void *, void *);

/* Runs the current object through the resident visibility test, then copies
   its four 16-byte blocks into the resident snapshots and clears the test
   state. */
void func_002718B8(char *object)
{
    unsigned char *state = (unsigned char *)D_001B5490;
    char *dest;
    int ok;

    if (state[2] == 0)
        ok = func_00271130(object, state + 0x10);
    else
        ok = func_002712D8(object, state + 0x70);
    if (ok == 0)
        return;

    dest = D_001B5570;
    *(TI128 *)(dest + 0x00) = *(TI128 *)object;
    *(TI128 *)(dest + 0x10) = *(TI128 *)(object + 0x10);
    *(TI128 *)(dest + 0x20) = *(TI128 *)(object + 0x20);
    *(TI128 *)(dest - 0x230) = *(TI128 *)(object + 0x30);
    *(short *)state = 0;
    state[2] = 0;
}

/* Copies the resident object's saved vectors back into its working ones. */
void func_00270EA8(void)
{
    unsigned char *object = (unsigned char *)D_001B5490;

    if (object[2] != 0) {
        *(TI128 *)(object + 0x50) = *(TI128 *)(object + 0xC0);
        *(TI128 *)(object + 0x60) = *(TI128 *)(object + 0xD0);
    }
}

extern char D_00189F70[];
extern void func_00282CC0(char *first, char *second, char *third);

/* Copies the resident object's two vectors and asks the engine to rebuild its
   matrix when the object's type says so. */
void func_00270E30(void)
{
    unsigned char *object = (unsigned char *)D_001B5490;

    if (object[2] == 0) {
        *(TI128 *)(object + 0xC0) = *(TI128 *)(object + 0x50);
        if (object[3] == 2)
            func_00282CC0((char *)(object + 0xC0), D_00189F70, (char *)(object + 0xC0));
        *(TI128 *)(object + 0xD0) = *(TI128 *)(object + 0x60);
    }
}

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
extern void func_00272CB0(void);
extern void func_00279BD8(void *, void *);
extern void func_002729A0(void *, float, float);
extern float func_00283CE0(int);

void func_00273418(void) {
    float base[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    F273418Mark *m;
    int i;

    if (D_0018C0B4 == 111) {
        D_001B7600.count = 0;
        return;
    }
    func_00272CB0();
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

extern char D_001B5200[];
extern char D_0018B2F0[];
extern unsigned char D_001A7A44[] __attribute__((sda));
extern void func_002721C8(void);
extern void func_00272280(void);
extern void func_00271FD8(void);
extern void func_00271B90(void);
extern void func_00270A48(void);
extern void func_00270EE0(void *);
extern int func_0026F7B8(void);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern void func_00271958(void *, int);
extern void func_00271E88(void);
extern void func_002735A0(void *);
extern void func_00270018(void);

void func_00272368(void) {
    char *d = D_001B5200;
    char *obj;
    char *p;
    char *q;
    char *r;

    *(int *)(d + 0x404) = *(int *)(d + 0x404) + 1;
    func_002721C8();
    func_00272280();
    func_00271FD8();
    func_00271B90();
    func_00270A48();
    obj = *(char **)(d + 0x190);
    if ((unsigned)(*(unsigned short *)(d + 0x290) - 1) < 2)
        func_00270EE0(*(void **)(d + 0x194));
    if (*(short *)(d + 0x290) == 3) {
        func_002718B8(obj);
    } else {
        qcopy(d + 0x140, obj + 0x30);
        qcopy(d + 0x370, obj);
        qcopy(d + 0x380, obj + 0x10);
        qcopy(d + 0x390, obj + 0x20);
    }
    if (func_0026F7B8()) {
        p = D_001B5200 + 0x140;
        qcopy(p, D_0018B2F0);
        qcopy(p + 0x230, D_0018B2F0 + 0x10);
        func_00282DD8(p + 0x240, p + 0x230, D_0018B2F0 - 0x14B0);
        func_00282F20(p + 0x240, p + 0x240, 1.0f);
        func_00282DD8(p + 0x250, p + 0x240, p + 0x230);
        func_00282F20(p + 0x250, p + 0x250, 1.0f);
    }
    q = D_001B5200 + 0x370;
    func_002AB6D8(q, q - 0x220);
    func_00271958(q - 0x210, 0);
    func_00271958(q - 0x200, 1);
    func_00271958(q - 0x1F0, 2);
    func_00271E88();
    func_002735A0(q - 0x230);
    if (D_001A7A44[0])
        func_00282DD8(q + 0x10, q + 0x20, q);
    func_00270018();
    qzero(q + 0x50);
}
