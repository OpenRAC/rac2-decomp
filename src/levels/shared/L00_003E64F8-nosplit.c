#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct { TI128 pos; TI128 dir; float target[4]; int owner, kind, busy; float scale; int state, count, pad[2]; } EffectRecord;
extern EffectRecord *g_blast_effect_records;

extern void vec_scale_to_length(char *a, char *b, float c);

extern void FastVecCross(char *a, char *b, char *c);

extern float math_random_angle(void);
extern char *AllocateOwnedEffectParticle(char *, int, float, float, int);
extern void FastVecAdd(void *, void *, void *);

extern float FastAddRotations(float a, float b);

/* Takes a free blast record for the owner and fills it, then adds 48 pieces around it. */
void blast_init_effect_record(char *owner, int kind, void *target_pos, void *start_vec, float scale)
{
    EffectRecord *base = g_blast_effect_records;
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
            qcopy(rec, start_vec);
            qcopy(rec->target, target_pos);
            rec->target[2] = *(float *)((char *)owner + 0x18);
            vec_scale_to_length((char *)&local, (char *)start_vec, 2.0f);
            FastVecAdd((char *)&local, (char *)&local, (char *)rec->target);
            FastVecCross((char *)&rec->dir, (char *)rec->target, (char *)&local);
            v = math_random_angle();
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
