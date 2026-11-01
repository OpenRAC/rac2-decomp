#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct { TI128 pos; TI128 dir; float target[4]; int owner, kind, busy; float scale; int state, count, pad[2]; } EffectRecord;
extern EffectRecord *D_L00_001B2B50;

extern void func_00282F20(char *a, char *b, float c);

extern void func_00282DD8(char *a, char *b, char *c);

extern float func_002A7940(void);
extern void func_L00_003E6778(char *, int, float, float, int);
extern void func_00282CC0(void *, void *, void *);

extern float func_00283B98(float a, float b);

void func_L00_003E64F8(char *owner, int a1, void *a2, void *a3, float f12)
{
    EffectRecord *base = D_L00_001B2B50;
    EffectRecord *rec;
    TI128 local;
    float v;
    int i = 0;
    int j;

    do {
        rec = &base[i];
        if (rec->owner == 0) {
            rec->kind = a1;
            rec->scale = f12;
            rec->owner = (int)owner;
            rec->busy = 0;
            qcopy(rec, a3);
            qcopy(rec->target, a2);
            rec->target[2] = *(float *)((char *)owner + 0x18);
            func_00282F20((char *)&local, (char *)a3, 2.0f);
            func_00282CC0((char *)&local, (char *)&local, (char *)rec->target);
            func_00282DD8((char *)&rec->dir, (char *)rec->target, (char *)&local);
            v = func_002A7940();
            for (j = 47; j >= 0; j--) {
                func_L00_003E6778((char *)rec, 2, v, 0.0f, 0);
                v = func_00283B98(v, 0.1336848f);
            }
            rec->state = 0;
            base[i].count = 0;
            break;
        }
    } while (++i <= 0);
}
