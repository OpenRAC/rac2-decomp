/* Nonmatching oscillator update, 2026-10-28. No C coverage credit.
 * Seven US probes, 0/4. Retained812/812B, frame0x70, diagnostic profile
 * -O2 -G0 -ffunction-sections -fno-gcse. Default approved qcopy and the
 * qualified initializer's grouped/barrier profile give848B; native C copy
 * gives840B, unchanged by narrow block/edge controls. Only then disabling
 * GCSE restores the retail's four FP constants and seven saved GPR roles.
 * Remaining: complete table-base address hoisted instead of its high half,
 * prologue/loop low-half schedule, and native copy offset/argument schedule.
 * Typed and byte canonical table views plus disabling strength reduction
 * produce identical full diff logs in the final three probes; stop.
 * No build option retained. Reopen with independent base/field lifetimes.
 *
 * Actual qualified L05_00398378.c corroborates the0xB0 stride, previous/
 * target whole-vector initialization, eighteen phase/rate/radius values,
 * timers and owner. The view retains16B transfer alignment, natural tail
 * alignment and an incomplete canonical byte table; no guessed24-entry bound.
 * One local difference receives all16B through subtract before vector-add
 * consumes it; only XYZ of that second input are semantically used. Prior
 * and target vectors are whole copies, and the interpolation writes16B.
 * Timer raw48B body returns integer status1/0/2. Existing math FP return
 * banks are preserved; raw-only interpolation/vector mutation return
 * hypotheses remain provisional. No non-clobbering helper, volatile field,
 * fabricated access, register pin, or extra initialization is introduced.
 */

#include "common.h"
typedef int OscillatorQuad __attribute__((mode(TI)));
typedef union { OscillatorQuad q; float f[4]; } OscillatorVector;
typedef struct {
    OscillatorVector first, second, previous, blended, target;
    float phaseA[3], rateA[3], radiusA[3];
    float phaseB[3], rateB[3], radiusB[3];
    int delay;
    unsigned char *owner;
    int life, initialLife, fading;
} OscillatorRecord;
/* Observed0xB0 stride and16-byte transfer alignment; allocation count unknown.
 * Qualified initializer L05_00398378.c fills the exact vectors/phase fields. */
extern unsigned char D_L05_00233560[];
extern float func_002A7878(float, float), func_00283B98(float, float);
extern float func_00283180(float), func_00283198(float);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282D08(void *, const void *, const void *, float);
extern int func_00282948(int *);

void func_L05_00398618(unsigned char *object)
{
    OscillatorVector difference;
    int i = 0;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    OscillatorRecord *record;
    float low = -0.1f, high = 0.1f, fast = 100.0f, slow = 50.0f;
    for (; i < 24; i++) {
        record = (OscillatorRecord *)(D_L05_00233560 + i * 0xB0);
        if (record->owner != object) continue;
        record->previous.f[0] += func_002A7878(low, high);
        record->previous.f[1] += func_002A7878(low, high);
        record->previous.f[2] += func_002A7878(low, high);
        func_00282CF0(&difference, &record->target, &record->previous);
        record->previous.q = *(OscillatorQuad *)(object + 0x10);
        func_00282CC0(&record->target, &record->previous, &difference);
        if (record->life) {
            record->phaseA[0] = func_00283B98(record->phaseA[0], record->rateA[0] * fast);
            record->phaseA[1] = func_00283B98(record->phaseA[1], record->rateA[1] * fast);
            record->phaseA[2] = func_00283B98(record->phaseA[2], record->rateA[2] * fast);
            record->phaseB[0] = func_00283B98(record->phaseB[0], record->rateB[0] * fast);
            record->phaseB[1] = func_00283B98(record->phaseB[1], record->rateB[1] * fast);
            record->phaseB[2] = func_00283B98(record->phaseB[2], record->rateB[2] * fast);
        } else {
            record->phaseA[0] = func_00283B98(record->phaseA[0], record->rateA[0] * slow);
            record->phaseA[1] = func_00283B98(record->phaseA[1], record->rateA[1] * slow);
            record->phaseA[2] = func_00283B98(record->phaseA[2], record->rateA[2] * slow);
            record->phaseB[0] = func_00283B98(record->phaseB[0], record->rateB[0] * slow);
            record->phaseB[1] = func_00283B98(record->phaseB[1], record->rateB[1] * slow);
            record->phaseB[2] = func_00283B98(record->phaseB[2], record->rateB[2] * slow);
        }
        record->first.f[0] = func_00283180(record->phaseA[0]) * record->radiusA[0];
        record->first.f[1] = func_00283198(record->phaseA[1]) * record->radiusA[1];
        record->first.f[2] = -func_00283198(record->phaseA[2]) * record->radiusA[2];
        record->second.f[0] = func_00283180(record->phaseB[0]) * record->radiusB[0];
        record->second.f[1] = func_00283198(record->phaseB[1]) * record->radiusB[1];
        record->second.f[2] = -func_00283198(record->phaseB[2]) * record->radiusB[2];
        if (*(int *)(state + 0x24)) func_00282D08(&record->blended, &record->previous, &record->target, 0.55f);
        else func_00282D08(&record->blended, &record->previous, &record->target, 0.4f);
        if (func_00282948(&record->life)) {
            if (!record->fading) record->fading = 1;
            if (func_00282948(&record->delay)) record->owner = 0;
        }
    }
}
