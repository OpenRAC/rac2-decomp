/* func_PAL_L07_0037B708, the PAL copy of func_L07_00378AE0: the same C, where rename func_L07_00379020 becomes func_PAL_L07_0037BC50; rename func_L07_00336860 becomes func_PAL_L07_00338B98; expr 0.055555556f becomes 0.020000001f; expr 0.027777778f becomes 0.010000001f; expr 0.13888888f becomes 0.050000004f; lit 4.0f becomes 4.8f. */

#include "common.h"

typedef struct {
    float x, y, z, w;
} V;

/* Mixed address forms are deliberate: retail loads these with lui+lw (MACRO_ADDR),
 * a split %hi/%lo pair (nosda) or $gp (sda/SDATA). */
extern int D_001A79F0 MACRO_ADDR;
extern int D_L07_001B1E08 MACRO_ADDR;
extern int D_L07_001C9780 __attribute__((nosda));
extern char *D_L07_001AEC08 __attribute__((sda));
extern char *D_L07_001ADAAC MACRO_ADDR;
extern float D_L07_001AEC10[] SDATA(D_L07_001AEC10);
extern float D_L07_001AEC14[] MACRO_ADDR;
extern V D_L07_001B9200[];   /* hero position (hero + 0x140) */
extern float D_L07_001B90C0[]; /* hero */
extern V D_L07_001B2550 MACRO_ADDR;

extern void func_PAL_L07_0037BC50(void *);
extern void func_002A7750(void *, int, int);
extern void func_L02_0031E9E8(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002B3868(void *);
extern int func_L00_00329520(void *, int);
extern char *func_PAL_L07_00338B98(void *, void *, int, int);

typedef struct {
    char pad00[0x20];
    unsigned char state;
    char pad21[0xF];
    unsigned char alpha;
    char pad31[3];
    unsigned short flags;
    char pad36[0x32];
    void *data;
} Object;

typedef struct {
    float speed;
    float fall;
    int enabled;
    float scale;
    int group;
    char pad14[0x1C];
    V axisA;
    V axisB;
    V origin;
    V previous;
} Data;

void func_PAL_L07_0037B708(Object *obj) {
    V pos, vel, tmp, point;
    Data *data = (Data *)obj->data;
    int j, i, k;
    float lo, hi;
    V *hero_pos;

    switch (obj->state) {
    case 0:
        obj->alpha = 255;
        obj->flags |= 0x100;
        if (D_001A79F0 == 7 && D_L07_001B1E08) {
            func_PAL_L07_0037BC50(obj);
            func_002A7750(obj, 1, -1);
        }
        data->speed = 1.5f;
        data->fall = 2.5f;
        data->enabled = 1;
        D_L07_001AEC08 = (char *)obj;
        break;
    case 1:
        if (D_001A79F0 == 7 && D_L07_001C9780 == 1) {
            func_002A7750(obj, 2, -1);
            break;
        }
        for (i = 0; i < func_002A77E0(2); i++) {
            func_L02_0031E9E8(&pos, 15.0f);
            pos.z += 7.0f;
            func_00282CC0(&pos, &pos, &D_L07_001B9200);
            func_00282D30(&tmp, &D_L07_001B9200[35], 4.0f);
            func_00282CC0(&pos, &tmp, &pos);
            func_L02_0031E9E8(&vel, data->speed * (0.020000001f));
            vel.z = -(data->fall * (0.020000001f)) * func_002A7878(0.8f, 1.2f);
            if (!func_L00_00329520(&pos, data->group))
                func_PAL_L07_00338B98(&pos, &vel, 0, 0);
        }
        func_00282D30(&point, &D_L07_001B9200[35], 4.0f);
        func_00282CC0(&tmp, &point, &D_L07_001B9200);
        func_00282CF0(&D_L07_001B2550, &tmp, &data->previous);
        data->scale = func_00282DF0(&D_L07_001B2550) * 3.3333333f;
        if (data->scale > 1.0f)
            data->scale = 1.0f;
        else if (data->scale < 0.0f)
            data->scale = 0.0f;
        func_00282D30(&D_L07_001B2550, &D_L07_001B2550, data->scale);
        qcopy_nc(&data->previous, &tmp);
        break;
    case 2:
        if (func_002B3868(obj))
            D_L07_001B2550.z -= 60.0f;
        if (D_001A79F0 == 7 && D_L07_001C9780 != 1) {
            func_002A7750(obj, 1, -1);
            break;
        }
        if (!D_L07_001ADAAC)
            break;
        hero_pos = D_L07_001B9200;
        j = *(short *)(D_L07_001ADAAC + 0xAA) - 0x11D9;
        lo = D_L07_001AEC10[j * 2];
        hi = D_L07_001AEC14[j * 2];
        for (k = 0; k < 6; k++) {
            func_00282D30(&tmp, &data->axisA, func_002A7878(-25.0f, 25.0f));
            func_00282CC0(&pos, &tmp, &data->origin);
            func_00282D30(&tmp, &data->axisB, func_002A7878(lo, hi));
            func_00282CC0(&pos, &tmp, &pos);
            func_00282CC0(&pos, &pos, hero_pos);
            func_00282CF0(&pos, &pos, D_L07_001ADAAC + 0x10);
            pos.z -= D_L07_001B90C0[0x148 / 4] - *(float *)(D_L07_001ADAAC + 0x18);
            func_L02_0031E9E8(&vel, 0.050000004f);
            vel.z = data->fall * (func_002A7878(0.8f, 1.2f) * (-0.010000001f));
            func_PAL_L07_00338B98(&pos, &vel, 1, 0);
        }
        func_00282CF0(&D_L07_001B2550, hero_pos, &data->previous);
        func_00282D30(&tmp, D_L07_001ADAAC + 0xC0, 1.2f);
        func_00282CC0(&D_L07_001B2550, &tmp, &D_L07_001B2550);
        qcopy_nc(&data->previous, hero_pos);
        break;
    }
}
