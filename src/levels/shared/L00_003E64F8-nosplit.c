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

/* Takes a free blast record for the owner and fills it, then adds 48 pieces around it. */
void func_L00_003E64F8(char *owner, int kind, void *targetPos, void *startVec, float scale)
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
            rec->kind = kind;
            rec->scale = scale;
            rec->owner = (int)owner;
            rec->busy = 0;
            qcopy(rec, startVec);
            qcopy(rec->target, targetPos);
            rec->target[2] = *(float *)((char *)owner + 0x18);
            vec_scale_to_length((char *)&local, (char *)startVec, 2.0f);
            FastVecAdd((char *)&local, (char *)&local, (char *)rec->target);
            FastVecCross((char *)&rec->dir, (char *)rec->target, (char *)&local);
            v = RandomAngle();
            for (j = 47; j >= 0; j--) {
                AllocateOwnedEffectParticle((char *)rec, 2, v, 0.0f, 0);
                v = FastAddRotations(v, 0.1336848f);
            }
            rec->state = 0;
            base[i].count = 0;
            break;
        }
    } while (++i <= 0);
}
