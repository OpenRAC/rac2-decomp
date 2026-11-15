#include "common.h"

typedef struct {
    char pad0[24];
    float f18;
    char pad1c[4];
    unsigned char f20;
    char pad21[116];
    unsigned char f95;
    char pad96[38];
    unsigned char fbc;
} F003C01C0obj;

typedef struct {
    char pad0[32];
    float f20;
    short f24;
    char pad26[8];
    unsigned char f2e;
    char pad2f[105];
    unsigned short f98;
    char pad9a[598];
    int f2f0;
    unsigned char f2f4;
    char pad2f5[3];
    int f2f8;
    int f2fc;
} F003C01C0s;

extern int func_002B0ED8(void *, void *, int);
extern int func_002B1350(void *, void *, void *, int);
extern void func_002B3BA8(void *, int, int, int, float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_L01_002F14E8(int, int, float);
extern char *D_L01_001B255C __attribute__((sda));
extern char *D_L01_001B264C __attribute__((sda));
extern float D_L01_001AFEE0 __attribute__((sda));
extern float D_L01_001AFEE4 __attribute__((sda));
extern float D_L01_001AFEE8 __attribute__((sda));
extern char D_00189EA0[];

void func_L01_003C01C0(F003C01C0obj *obj)
{
    F003C01C0s *s = *(F003C01C0s **)((char *)obj + 0x68);
    int old = obj->f20;

    if (func_002B0ED8(obj, (char *)s + 0x60, 0) || s->f2e == 2) {
        if (s->f20 <= 0.0f || s->f2e == 2) {
            s->f20 = 0.0f;
            if (s->f2e == 2 && !(s->f98 & 1)) {
                int zero __attribute__((mode(TI)));

                /* The cleared local is consumed only by the following call. */
                qzero_nc(&zero);
                ApplyObjectReaction(obj, (char *)s + 0x60, &zero, 4);
                s->f2e = 3;
                obj->f95 = 6;
                obj->fbc = 99;
                obj->f20 = 99;
            }
            if (s->f2f8 != -1) {
                D_L01_001B255C[s->f2f8 * 256 + 0xbc] = 1;
                if (s->f2fc != -1) {
                    int index = s->f2fc;
                    char *base = D_L01_001B264C;

                    /* Copying position leaves the separate transform row intact. */
                    qcopy_nc((char *)obj + 0x10, base + index * 128 + 0x30);
                    qcopy((char *)obj + 0xf0, base + index * 128 + 0x70);
                }
            }
        }
    }
    if (obj->f20 == 255) {
        obj->f20 = old;
    }
    func_002B3BA8(obj, s->f2f0, 0, 0, 0.0f, 0.0f);
    if (*(char **)((char *)s + 0x2e4)) {
        FastVecSub(*(char **)((char *)s + 0x2e4) + 0x20,
                     (char *)obj + 0x10, D_00189EA0);
        (*(char **)((char *)s + 0x2e4))[0x1f] = 1;
        *(float *)(*(char **)((char *)s + 0x2e4) + 0x10) =
            D_L01_001AFEE0 * 0.017453294f;
        if (s->f2f4 || (obj->f95 == 3 && obj->f20 == 2)) {
            *(float *)*(char **)((char *)s + 0x2e4) = D_L01_001AFEE8;
            *(int *)(*(char **)((char *)s + 0x2e4) + 0x34) = 6;
        } else {
            *(float *)*(char **)((char *)s + 0x2e4) = D_L01_001AFEE4;
            *(int *)(*(char **)((char *)s + 0x2e4) + 0x34) = 3;
        }
    }
    if (*(float *)(D_00189EA0 + 8) < obj->f18 + 20.0f &&
        (unsigned)(obj->f95 - 2) < 5) {
        func_L01_002F14E8(2, 0, s->f20 / IntToFloat(s->f24));
    }
}
