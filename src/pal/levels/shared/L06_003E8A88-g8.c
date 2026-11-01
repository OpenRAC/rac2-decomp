#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct {
    char x[10];
} Sequence;
extern Sequence D_L06_001AF700;
extern int D_001A79F0;
extern u8 D_0018C0D4 NOT_SDA;
extern char D_L06_001B9840[];
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[0x13];
    char *owner;
} Effect;
extern u8 D_00188660[];
extern void func_0026FEB8(char *, ...);
extern void func_0029F338(char *);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);
extern int func_00283CF0(float);
extern float func_00282C10(float);
extern float func_00282E48(void *, void *);
extern int func_00283DB8(void *, float);
extern void func_L00_002E6EF8(void *, void *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_00282948(void *);
extern void func_002E59F8(int);
typedef struct {
    float radius;
    int count;
    float step;
    int valid;
    u8 order[0x20];
    int effect;
    int timer;
} Data;
typedef struct {
    char pad0[0x20];
    u8 state;
    char pad21[0xF];
    u8 mode;
    char pad31[3];
    u16 flags;
    char pad36[0x32];
    Data *data;
    char pad6C[0x8C];
    float angle;
} Object;
extern char D_L06_001AFFA0[], D_L06_001AFFE0[];
extern Sequence D_L06_001B0000;
extern float D_L06_001AFF20 __attribute__((sda));
extern void func_PAL_L06_003E8E68(void);

void func_PAL_L06_003E8A88(char *obj) {
    Object *m = (Object *)obj;
    Data *data = m->data;
    /* State 0's shuffle and state 2's sphere share their temporary storage. */
    union {
        Sequence seq;
        Quad q;
        float f[4];
    } buffer;
    if (data->valid == -1) {
        func_0026FEB8(D_L06_001AFFA0);
        func_0026FEB8(D_L06_001AFFE0, *(short *)(obj + 0xB2));
        func_0029F338(obj);
    }
    switch (m->state) {
    case 0: {
        int i, j, k;
        float r;
        if (D_001A79F0 == 10 && D_0018C0D4 == 1) {
            func_0029F338(obj);
            break;
        }
        buffer.seq = D_L06_001B0000;
        for (i = 0; i < 10; i++) {
            for (j = 0; j < func_002A77E0(9); j++) {
                u8 b = buffer.seq.x[j + 1];
                buffer.seq.x[j + 1] = buffer.seq.x[j];
                buffer.seq.x[j] = b;
            }
        }
        for (k = 0; k < data->count; k++)
            data->order[k] = buffer.seq.x[k];
        r = func_00283B98(m->angle, 1.5707964897155762f);
        m->mode = 0x60;
        m->state = 1;
        m->angle = r;
        data->effect = -1;
        data->timer = ((s32)(func_00283CF0(D_L06_001AFF20 * 60.0f)) * 5 + 2) / 6;
        m->flags |= 0x41;
        break;
    }
    case 1: {
        float r, h;
        float sphere[4];
        r = data->radius * 0.5f;
        h = (float)data->count * data->step * 0.5f;
        *(Quad *)sphere = *(Quad *)(obj + 0x10);
        sphere[2] += h;
        sphere[3] = func_00282C10(h * h + r * r);
        if (func_00282E48(obj + 0x10, D_L06_001B9840) < 80.0f) {
            if ((float)func_00283DB8(sphere, 80.0f) >= 0.0f)
                func_L00_002E6EF8(func_PAL_L06_003E8E68, obj);
        }
        if (!func_002E59B0(obj, data->effect))
            data->effect = func_002E5CF8(0, 4, obj);
        break;
    }
    case 2: {
        int i;
        float r, h;
        func_00282948(&data->timer);
        i = data->effect;
        if (i != -1) {
            Effect *e = (Effect *)(D_00188660 + i * 0x70);
            if (e->owner == obj && e->active)
                func_002E59F8(i);
        }
        data->effect = -1;
        r = data->radius * 0.5f;
        h = (float)data->count * data->step * 0.5f;
        buffer.q = *(Quad *)(obj + 0x10);
        buffer.f[2] += h;
        buffer.f[3] = func_00282C10(h * h + r * r);
        if (func_00282E48(obj + 0x10, D_L06_001B9840) < 80.0f &&
            (float)func_00283DB8(&buffer, 80.0f) >= 0.0f)
            func_L00_002E6EF8(func_PAL_L06_003E8E68, obj);
        break;
    }
    }
}
