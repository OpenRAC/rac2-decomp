#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L22_002B7B08);

#include "common.h"
extern char D_00189E20[];
extern void func_L00_002D36E0(void *, float, float, float, int);
extern float func_L00_002D3A58(void *);
extern float func_00282E20(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern float func_L00_002D3EA8(void *);
extern float func_00282DB0(void *, void *);
typedef struct {
    char pad0[0x18]; void *object; int count;
    char pad20[0x20]; float normal[4];
} CollisionResult;
extern CollisionResult D_L22_001C00C0;

void func_PAL_L22_002B8CB8(int force) {
    float start[4], end[4], extended_start[4], extended_end[4];
    float reach, scale, zero, angle;
    int hit;
    char *velocity = D_00189E20 + 0xF0;
    if (func_L00_002D3A58(velocity) < 0.002f) return;
    {
        char *g = velocity - 0xF0;
        reach = 0.37f;
        scale = 0.5f;
        if ((unsigned)(*(int *)(g + 0x229C) - 17) < 2) {
            reach = 0;
            scale = 0.7f;
        } else if (*(u8 *)(g + 0x22B4) == 1) {
            reach = 0.35f;
            scale = 0.27f;
        } else if (*(u8 *)(g + 0x22B4) == 2) {
            reach = 1;
            scale = 5;
        }
        zero = 0;
        func_L00_002D36E0(start, zero, zero, reach, 1);
        func_L00_002D36E0(extended_start, zero, zero, reach * 0.3f, 1);
    }
    if (force != 0 || func_00282E20(D_00189E20 + 0xF0) < 0.01f) {
        func_00282F20(end, D_00189E20, scale);
        func_00282F20(extended_end, D_00189E20, scale * 1.4f);
    } else {
        func_L00_002D3B58(end, D_00189E20 + 0xF0, 0);
        func_00282F20(end, end, scale);
        func_00282D30(extended_end, end, 1.4f);
    }
    func_00282CC0(end, end, start);
    hit = -1;
    func_00282CC0(extended_end, extended_end, extended_start);
    {
        char *g = D_00189E20;
        if (func_002761F8(extended_start, extended_end, 2, *(void **)(g + 0x2290), 0) && D_L22_001C00C0.count > 0)
            hit = func_00278E78();
    }
    angle = 0;
    {
        char *g = D_00189E20;
        if (func_002761F8(start, end, 2, *(void **)(g + 0x2290), 0) && D_L22_001C00C0.count > 0)
            angle = func_L00_002D3EA8(D_L22_001C00C0.normal);
    }
    if (angle >= 0.8726647f || hit == 8 || hit == 12) {
        char *g = D_00189E20;
        CollisionResult *contact = &D_L22_001C00C0;
        float *normal = contact->normal;
        float dot;
        *(void **)(g + 0x270) = contact->object;
        func_L00_002D3B58(normal, normal, 0);
        func_00282F20(normal, normal, 1);
        dot = func_00282DB0(normal, g + 0xF0);
        if (dot < 0) {
            func_00282D30(normal, normal, -dot);
            func_00282CC0(g + 0xF0, g + 0xF0, normal);
        }
    }
}

