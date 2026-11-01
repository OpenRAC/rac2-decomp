#include "include_asm.h"

#include "common.h"
typedef struct __attribute__((packed, aligned(4))) { long long a; int b; } QueryParams;
typedef struct { char *target; int zero; } QueryExclude;
typedef struct { char *item; } Candidate;
typedef struct { unsigned char pad[28]; unsigned char entry; } DamageClasses;
typedef struct { char pad[112]; float value; char tail[108]; } DamageClass;
typedef struct { char pad[0x2290]; char *player; } PlayerRef;
typedef struct { char pad[132]; int value; } SoundRecord;
extern char D_L00_001C3280[];
extern const QueryParams D_L00_001B0140;
extern char D_00139568[];
extern char D_L00_001BF220[];
extern char D_00188660[];
extern char D_00189E20[];
extern char D_L00_00262570[];
extern int D_L00_001B0134 SDATA(D_L00_001B0134);
extern void func_00300190(void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002E5F40(int, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282C88(void *);
extern void func_002B00B0(void *, void *, int);
extern void func_PAL_00320D00(void *, int, int);
extern void func_PAL_0032F0B8(void *, int, int);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_PAL_0031F230(void *, void *, int);
extern void func_PAL_0031FF78(void *);
extern void func_0031E6E8(void *);
extern void func_002E59F8(int);
extern void func_PAL_0031F500(void *);
extern void func_0031E3A8(void *);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern void ref_L00_003CA730_00(void *, void *);
extern int func_002A7820(int, int);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277258(void *, int, void *, float);
extern int func_00282948(void *);
extern int func_002E5CF8(int, int, void *);
extern int func_002E59B0(void *, int);
extern int func_002B4038(int, int);
extern char *func_002AB1F0(void *);
extern char *func_002AF580(void *, void *, float, float, int *, void *, int, void *,
                           float, float, float, int, void *);

void func_PAL_0031EBA0(char *self)
{
    char old[16] __attribute__((aligned(16)));
    union { char v[16]; QueryParams params; } temp __attribute__((aligned(16)));
    union {
        char raw[32];
        struct { char *targets[4]; QueryExclude exclude; } query;
    } event __attribute__((aligned(16)));
    int count, i, j, n;
    char *state = *(char **)(self + 0x68), *obj, *data;

    func_00300190(self + 0x10, self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        *(unsigned char *)(self + 0x20) = 1;
        *(int *)(state + 0x20) = -1;
        *(int *)(state + 0x24) = -1;
    case 1:
        qcopy(old, self + 0x10);
        func_002FEE70(*(int *)(state + 0x44), state, 0);
        func_00282CC0(self + 0x10, self + 0x10, state);
        func_002E5F40(*(int *)(state + 0x20), *(int *)(state + 0x24) + func_002A7820(-200, 200));
        n = func_00277F48(self + 0x10, 0, self, 0, 0.45f);
        for (i = 0; i < n; i++) {
            obj = ((Candidate *)D_L00_001C3280)[i].item;
            data = func_002AB1F0(obj);
            if (*(short *)(obj + 0xAA) == 0xC4A || obj == ((PlayerRef *)D_00189E20)->player
                || !(*(short *)(obj + 0x34) & 0x1000))
                continue;
            if (data) {
                qcopy(self + 0x10, obj + 0x10);
                func_002B00B0(obj, temp.v, 1);
                func_00282D30(temp.v, temp.v, *(float *)(data + 0x10));
                func_00282CC0(self + 0x10, self + 0x10, temp.v);
            }
            *(char **)(state + 0x38) = obj;
            *(int *)(state + 0x10) = 12;
            *(unsigned char *)(self + 0x20) = 2;
            qcopy(temp.v, state);
            func_00282C88(state);
            func_00282F20(temp.v, temp.v, 0.040000003f);
            func_002A8C00(event.raw, self, 0x210000, temp.v,
                          ((DamageClass *)D_L00_00262570)[((DamageClasses *)D_00139568)->entry].value);
            *(unsigned char *)(event.raw + 24) = 1;
            *(unsigned char *)(event.raw + 25) = 3;
            *(short *)(event.raw + 26) = *(short *)(self + 0xAA);
            func_002A8E20(obj, event.raw);
            func_PAL_00320D00(self + 0x10, 10, 1);
            func_PAL_0032F0B8(obj, 28, *(int *)(self + 0xB8));
            break;
        }
        if (!*(char **)(state + 0x38)) {
            int hit;
            if (func_002761F8(old, self + 0x10, 2, self, 0))
                hit = 1;
            else
                hit = func_00277258(self + 0x10, 2, self, 0.1f) != 0;
            if (hit == 1) {
                qcopy(self + 0x10, D_L00_001BF220);
                func_00282D30(temp.v, D_L00_001BF220 + 0x20, 0.0009765625f);
                func_00282F20(temp.v, temp.v, 0.1f);
                func_00282CC0(self + 0x10, temp.v, self + 0x10);
                *(int *)(state + 0x10) = 12;
                *(unsigned char *)(self + 0x20) = 2;
                func_PAL_00320D00(self + 0x10, 15, 0);
            }
        }
        if (func_00282948(state + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            *(int *)(state + 0x10) = 134;
        }
        break;
    case 2: {
        char *info;
        if (*(char **)(state + 0x38)) {
            info = func_002AB1F0(*(char **)(state + 0x38));
            if (info) {
                func_002B00B0(*(char **)(state + 0x38), temp.v, 1);
                func_00282D30(temp.v, temp.v, *(float *)(info + 0x10));
                func_00282CC0(self + 0x10, temp.v, *(char **)(state + 0x38) + 0x10);
            }
        }
        if (func_00282948(state + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            temp.params = D_L00_001B0140;
            event.query.exclude = (QueryExclude){*(char **)(state + 0x38), 0};
            func_002AF580(self + 0x10, self + 0xC0, 6.2831855f, 6.2831855f, &count,
                          event.query.targets, 3, &event.query.exclude,
                          10.0f, 0.0f, 0.0f, 0, &temp.params);
            for (i = 0; i < count; i++) {
                for (j = 4; j >= 0; j--)
                    func_PAL_0031F230(self, event.query.targets[i], 10);
                func_002E5CF8(1, 0, self);
            }
        }
        break;
    }
    case 3:
        break;
    case 4: {
        char *info;
        if (*(char **)(state + 0x38)) {
            if (!D_L00_001B0134) {
                D_L00_001B0134 = 1;
                func_002E5CF8(3, 0, self);
            }
            info = func_002AB1F0(*(char **)(state + 0x38));
            if (info) {
                func_002B00B0(*(char **)(state + 0x38), temp.v, 1);
                func_00282D30(temp.v, temp.v, *(float *)(info + 0x10));
                func_00282CC0(self + 0x10, temp.v, *(char **)(state + 0x38) + 0x10);
            }
        }
        if (!*(int *)(state + 0x1C)) {
            func_0031E6E8(self);
            if (!*(char **)(state + 0x38)) {
                func_PAL_00320D00(self + 0x10, 10, 1);
                func_002E5CF8(2, 0, self);
            }
        }
    }
    }
    if (*(unsigned char *)(self + 0x20) != 4) {
        if (!func_002E59B0(self, *(int *)(state + 0x20)))
            *(int *)(state + 0x20) = func_002E5CF8(0, 4, self);
        if (*(int *)(state + 0x24) == -1) {
            char *rec = D_00188660 + *(int *)(state + 0x20) * 112;
            *(int *)(state + 0x24) = ((SoundRecord *)rec)->value;
        }
    } else if (*(int *)(state + 0x20) != -1) {
        char *rec = D_00188660 + *(int *)(state + 0x20) * 112;
        if (*(char **)(rec + 0x88) == self && *(unsigned char *)(rec + 0x74))
            func_002E59F8(*(int *)(state + 0x20));
        *(int *)(state + 0x20) = -1;
    }
    func_PAL_0031F500(self);
    func_0031E3A8(self);
    if (!func_002B4038(*(int *)(state + 0x40), *(int *)(state + 0x3C))) {
        func_002FEE50(*(int *)(state + 0x44));
        func_0029F338(self);
    } else {
        ref_L00_003CA730_00((void *)func_PAL_0031FF78, self);
    }
}
