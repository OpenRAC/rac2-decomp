/* func_PAL_002E7270 in its own unit (flags in config/cflags.txt: -O2 -G32 -Wa,-G32 -ffunction-sections),
 * the PAL copy of func_002E64A0 (src/game/002E64A0.c, where its notes are): the same C, where the two
 * rates become 0.0008f and 0.02f (the v1.01 values times 36/25 and 6/5 for 50 Hz) and each flag arm also
 * sets the piece's render field, which v1.01 sets only at the end of the loop.
 */
#include "common.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct {
    char header[0x10];
    float position[4];
    char pad20[4];
    char *model;
    char pad28[12];
    unsigned short flags;
    char pad36[0x32];
    char *state;
    char pad6c[0x2c];
    int render;
    char pad9c[0x20];
    unsigned char blocked;
    char padbd[3];
    float basis[3][4];
    float previous[4];
} Object;

typedef struct {
    float position[4];
    char gap[0x50];
    float focus[4];
} HeroPosition;

typedef struct {
    char prefix[0x80];
    HeroPosition hero;
    char gapF0[0x24c];
    Object *selected;
    int count;
    char gap344[0x1f4c];
    int collision;
} HeroGlobals;

typedef int Quad __attribute__((mode(TI)));

extern Object *D_00214920[];
extern char D_00214970[], D_00214978[];
extern int D_001A8BB0[] __attribute__((sda));
extern int D_001A8BB0_gp SDATA(D_001A8BB0);
extern int D_001A79F0[] __attribute__((sda));
extern float D_001ABF84 __attribute__((sda)), D_001ABF88 __attribute__((sda)), D_001ABF8C __attribute__((sda));
extern char D_001ABF18[16] __attribute__((sda)), D_001ABF28[16] __attribute__((sda));
extern char D_001ABF38[16] __attribute__((sda)), D_001ABF48[16] __attribute__((sda));
extern char D_001ABF58[16] __attribute__((sda)), D_001ABF68[16] __attribute__((sda));
extern char D_001ABF78[16] __attribute__((sda));
extern HeroGlobals D_00189E20;


extern void func_002E6178(void *);
extern float func_002A89A8(void *, int, float);
extern void func_PAL_002B4D38(void *, void *, int, int, void *, void *, void *, void *, void *, void *, void *);
extern void func_00282D60(void *, void *, float);
extern int func_00283DB8(void *, float);
extern float func_00282E80(void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_0029FC20(void *, int, void *), func_0029FCC0(void *, int, void *);
extern void func_00283098(void *, void *, void *), func_002AB6D8(void *, void *), func_002A10E8(void *);
extern void func_002AD6F0(void *, void *, void *, void *), func_PAL_002B5050(void *, void *, void *);

/* Spawns the equipment pieces if needed, then makes each piece follow the base object. */
void func_PAL_002E7270(Object *object)
{
    float p[4], old[4], matrix[16], previous[4], delta[4], offset[4];
    char *target;
    int i, j;
    unsigned char blocked;

    if (!D_00214920[0]) {
        func_002E6178(object);
        if (!D_001A8BB0[0]) {
            float height = func_002A89A8(object->position, 0, 0.5f);
            if (height != 0.0f)
                object->position[2] = height + D_001ABF84;
            D_001ABF88 = object->position[2];
        }
        func_PAL_002B4D38(object, D_00214970, 0, 0, D_001ABF48, D_001ABF58, D_001ABF18, D_001ABF78,
                      D_001ABF68, D_001ABF28, D_001ABF38);
    }
    target = 0;
    if (!D_001A8BB0[0]) {
        func_00282D60(p, object, 0.0009765625f);
        p[3] += 1.0f;
        if (func_00283DB8(p, 50.0f) == -1)
            return;
        if (!D_001A8BB0_gp) {
            blocked = 0;
            if (func_00282E80(object->position, ((char *)&D_00189E20.hero)) < 6.0f) {
                if (object->blocked) {
                    qcopy(p, ((char *)&D_00189E20.hero) + 0x60);
                    p[2] += 2.0f;
                    if (func_002761F8(((char *)&D_00189E20.hero) + 0x60, p, 0, D_00189E20.collision, 0))
                        blocked = 1;
                    else {
                        func_00282CF0(old, object->position, ((char *)&D_00189E20.hero));
                        old[2] = 0;
                        func_00282F20(old, old, 0.4f);
                        func_00282CC0(p, p, old);
                        blocked = func_002761F8(((char *)&D_00189E20.hero) + 0x60, p, 0, D_00189E20.collision, 0) != 0;
                    }
                } else {
                    qcopy(p, ((char *)&D_00189E20.hero) + 0x60);
                    p[2] += 2.0f;
                    blocked = func_002761F8(((char *)&D_00189E20.hero) + 0x60, p, 0, *(int *)(((char *)&D_00189E20.hero) + 0x2210), 0) != 0;
                }
            }
            object->blocked = blocked;
            if (object->blocked)
                func_002AA548(D_00214978, &D_001ABF8C, D_001ABF88 + 0.75f, 0.00080000004f, 0.00080000004f, 0.020000001f);
            else
                func_002AA548(D_00214978, &D_001ABF8C, D_001ABF88, 0.00080000004f, 0.00080000004f, 0.020000001f);
        }
    }
    func_0029FC20(object, 1, matrix);
    func_0029FCC0(object, 1, p);
    for (i = 0; D_00214920[i]; i++) {
        if (object->flags & 1) {
            D_00214920[i]->render = 0;
            D_00214920[i]->flags |= 0x41;
        } else {
            D_00214920[i]->flags &= 0xFFBE;
            D_00214920[i]->render = *(int *)(D_00214920[i]->model + 0x10);
        }
        {
            Object *part = D_00214920[i];
            qcopy(old, part->position);
            qcopy(previous, part->previous);
            {
                float *from = object->position;
                qcopy(part->position, from);
            }
        }
        for (j = 0; j < 3; j++) {
            D_00214920[i]->basis[j][0] = matrix[j * 4];
            D_00214920[i]->basis[j][1] = matrix[j * 4 + 1];
            D_00214920[i]->basis[j][2] = matrix[j * 4 + 2];
        }
        if (D_001A8BB0[0] == 2 && D_001A79F0[0] == 5) {
            *(Quad *)offset = 0;
            offset[0] = -0.3372f;
            offset[1] = -0.5364f;
            offset[2] = -1.79489f;
            func_00283098(offset, offset, D_00214920[i]->basis);
            func_00282CC0(delta, p, offset);
            qcopy(D_00214920[i]->position, delta);
        }
        func_002AB6D8(D_00214920[i]->basis, D_00214920[i]->previous);
        func_002A10E8(D_00214920[i]);
        {
            char *state = D_00214920[i]->state;
            func_00282CF0(delta, D_00214920[i]->position, old);
            func_002AD6F0(state + 0x20, delta, previous, D_00214920[i]->previous);
        }
        if (D_00189E20.count >= 2 && D_00189E20.selected == D_00214920[i])
            target = ((char *)&D_00189E20.hero);
        if (D_001A8BB0[0]) {
            D_00214920[i]->render = 0;
            object->render = 0;
        } else if (object->render)
            D_00214920[i]->render = *(int *)(D_00214920[i]->model + 0x10);
    }
    if (!D_001A8BB0[0])
        func_PAL_002B5050(object, D_00214970, target);
}
