/* Nonmatching preview transform: USA 516/512 bytes, 0/28 placements at -O2 -G8.
 * Eight bounded trials: initial 528; unfactored class tests 532; branch-scoped
 * work-vector lifetime removed a saved register and reduced the best faithful
 * control flow to 516. Named position/basis views and an EE FP-first scale
 * declaration tied; -fno-schedule-insns also tied. Retained canonical bank order.
 * Remaining differences are position/add argument materialization and the
 * forward-factor load versus a shared pointer setup in the branch delay slot.
 * Reopen with original source lifetime or scheduling evidence, not ABI changes.
 *
 * Verified contracts: 282D30/282CC0/2833F0/2A0F48 are void; 283B98 returns float.
 * 300048 has a real unused object formal: both carrying USA releases explicitly
 * supply the object in a0. The canonical existing definition was repaired and
 * still checks 28/28 in USA and USA v2; neither PAL catalogue carries it.
 * The basis writer fills exactly 3 rows (0x30 bytes); offset and temporary are
 * complete aligned 16-byte vectors. No uninitialized vector lanes or nc copies.
 * D_001AD808 remains incomplete storage; five measured float accesses span20
 * bytes. Current RAC1 pause/menu preview helpers were inspected, not equivalent.
 */
/* Screened, not matched in wave 13 (worker g3): 16 call(s), 0 $gp-relative small-data access(es), MMI words [none], float constants [none]. The body is straight-line code
   whose register allocation and the materialisation of its constant addresses have to be
   reproduced word for word; no C was written in this wave. */

#include "common.h"

typedef struct {
    char reserved00[0x10];
    float position[4];
    char reserved20[0x8A];
    short classId;
    char reservedAC[0x44];
    float rotation[4];
} PreviewObjectPrefix;

extern float D_001B5340[];
extern float D_001B5570[];
extern unsigned char D_001B2345;
extern float D_001AD808[] SDATA(D_001AD808);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_002833F0(void *, void *);
extern void func_002A0F48(void *);
extern void func_00300048(void *);

/* Position and rotate the preview using the class-specific camera distance. */
void func_002FF968(PreviewObjectPrefix *object)
{
    float offset[4] __attribute__((aligned(16)));
    float basis[12] __attribute__((aligned(16)));
    float temporary[4] __attribute__((aligned(16)));
    int special = object->classId == 0xC5A || object->classId == 0xA65;
    int compact = 0;
    float *work;
    float *basisRows;
    float *position;
    if (object->classId == 0x879 || object->classId == 0xAF6 ||
        object->classId == 0x907 || object->classId == 0xE7A || special)
        compact = 1;
    if (special) {
        func_00282D30(offset, D_001B5570, 2.5f);
    } else if (compact) {
        func_00282D30(offset, D_001B5570, 2.0f);
    } else {
        func_00282D30(offset, D_001B5570, 3.0f);
    }
    func_00282CC0(object->position, D_001B5340, offset);
    position = object->position;
    if (D_001B2345)
        object->rotation[0] = func_00283B98(object->rotation[0], 0.03490659f);
    else
        object->rotation[2] = func_00283B98(object->rotation[2], 0.03490659f);
    /* The retail basis helper writes exactly three complete rows, 0x30 bytes. */
    basisRows = basis;
    func_002833F0(basisRows, object->rotation);
    if (D_001B2345) {
        float forward;
        if (compact) {
            work = temporary;
            func_00282D30(work, basisRows + 4, D_001AD808[4]);
            func_00282CC0(position, position, work);
            forward = D_001AD808[3];
        } else {
            work = temporary;
            func_00282D30(work, basisRows + 4, D_001AD808[1]);
            func_00282CC0(position, position, work);
            forward = D_001AD808[0];
        }
        func_00282D30(work, basisRows, forward);
        func_00282CC0(position, position, work);
    } else {
        work = temporary;
        func_00282D30(work, basisRows + 8, D_001AD808[2]);
        func_00282CC0(position, position, work);
    }
    func_002A0F48(object);
    func_00300048(object);
}
