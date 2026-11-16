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
extern Moby *CreateMoby(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_init_child_from_parent(void *a0, int a1);
extern void set_moby_color(void *moby, int r, int g, int b);

/* Keeps five child mobies (class 0xF10 for an owner of class 0xCEF, 0xF0F otherwise)
   streaming along the owner's forward axis, spawning them on the first call: each call
   moves every child 1/12 unit on, wrapping from the end back to the start, and as a child
   travels it shrinks, fades in over the first quarter of the way and out over the last,
   and turns from yellow (252 + 2g, 224g, 6g with g = (1 - t)^4) to red. */
void UpdateChildMobyStream_pal(Moby *moby)
{
    StreamVars *vars = moby->vars;
    Moby **children;
    float *offsets;
    Moby *child;
    float first;
    float spacing;
    float start;
    float end;
    float min_scale;
    float max_scale = 0.24f;
    float length;
    float scale_range;
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
        min_scale = 0.14f;
        id = 0xF10;
    } else {
        first = -1.5f;
        id = 0xF0F;
        max_scale = 0.21f;
        spacing = 0.75f;
        start = -1.5f;
        end = 1.5f;
        min_scale = 0.114f;
    }
    children = vars->children;
    offsets = vars->offsets;
    length = end - first;
    scale_range = max_scale - min_scale;

    if (moby->state == 0) {
        for (i = 0; i < 5; i++) {
            child = CreateMoby(id);
            if (child) {
                moby_init_child_from_parent(child, 0);
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

        FastVecScale(&shift, moby->forward, offset);
        FastVecAdd(children[i]->position, moby->position, &shift);
        FastVecScale(&shift, moby->up, 0.15f);
        FastVecAdd(children[i]->position, children[i]->position, &shift);

        t = (offset - start) / length;
        children[i]->scale = children[i]->mclass->scale * (min_scale + (1 - t) * scale_range);
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
        set_moby_color(children[i], 252 + (int)(alpha * 2), (int)(alpha * 224), (int)(alpha * 6));
    }
}
