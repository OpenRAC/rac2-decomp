#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    u8 pad00[0x24];
    float scale;                 
} MobyClass;
typedef struct {
    u8 pad00[0x10];
    float position[4];           
    u8 state;                    
    u8 pad21[0x23 - 0x21];
    u8 alpha;                    
    MobyClass *mclass;           
    u8 pad28[0x2C - 0x28];
    float scale;                 
    u8 pad30[0x68 - 0x30];
    void *vars;                  
    u8 pad6C[0xAA - 0x6C];
    s16 oClass;                  
    u8 padAC[0xC0 - 0xAC];
    float forward[4];            
    u8 padD0[0xE0 - 0xD0];
    float up[4];                 
    Quad rotation;               
} Moby;
typedef struct {
    u8 pad00[0x04];
    Moby *children[5];           
    float offsets[5];            
} StreamVars;
extern Moby *func_0029EFD0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002B37E8(void *a0, int a1);
extern void func_002A0488(void *moby, int r, int g, int b);

/* Keeps five child mobies (class 0xF10 for an owner of class 0xCEF, 0xF0F otherwise)
   streaming along the owner's forward axis, spawning them on the first call: each call
   moves every child 1/12 unit on, wrapping from the end back to the start, and as a child
   travels it shrinks, fades in over the first quarter of the way and out over the last,
   and turns from yellow (252 + 2g, 224g, 6g with g = (1 - t)^4) to red. */
void func_PAL_L04_003CB9F8(Moby *moby)
{
    StreamVars *vars = moby->vars;
    Moby **children;
    float *offsets;
    Moby *child;
    float first;
    float spacing;
    float start;
    float end;
    float minScale;
    float maxScale = 0.24f;
    float length;
    float scaleRange;
    float offset;
    float t;
    float alpha;
    int id;
    int i;
    Quad shift;

    if (moby->oClass == 0xCEF) {
        first = -2;
        spacing = 0.85f;
        start = -2;
        end = 1.4f;
        minScale = 0.14f;
        id = 0xF10;
    } else {
        first = -1.5f;
        id = 0xF0F;
        maxScale = 0.21f;
        spacing = 0.75f;
        start = -1.5f;
        end = 1.5f;
        minScale = 0.114f;
    }
    children = vars->children;
    offsets = vars->offsets;
    length = end - first;
    scaleRange = maxScale - minScale;

    if (moby->state == 0) {
        for (i = 0; i < 5; i++) {
            child = func_0029EFD0(id);
            if (child) {
                func_002B37E8(child, 0);
                child->rotation = moby->rotation;
                children[i] = child;
                offsets[i] = first;
            } else {
                children[i] = 0;
            }
            first += spacing;
        }
        moby->state = 1;
    }

    for (i = 0; i < 5; i++) {
        offset = offsets[i];
        offset += 0.10000001f;
        if (offset > end)
            offset = start;
        offsets[i] = offset;

        func_00282D30(&shift, moby->forward, offset);
        func_00282CC0(children[i]->position, moby->position, &shift);
        func_00282D30(&shift, moby->up, 0.15f);
        func_00282CC0(children[i]->position, children[i]->position, &shift);

        t = (offset - start) / length;
        children[i]->scale = children[i]->mclass->scale * (minScale + (1 - t) * scaleRange);
        if (t < 0.25f)
            alpha = t * 4;
        else if (t > 0.75f)
            alpha = 1 - (t - 0.75f) * 4;
        else
            alpha = 1;
        children[i]->alpha = (int)(alpha * 128);

        alpha = 1 - t;              /* now the colour fade g */
        alpha *= alpha;
        alpha *= alpha;
        func_002A0488(children[i], 252 + (int)(alpha * 2), (int)(alpha * 224), (int)(alpha * 6));
    }
}
