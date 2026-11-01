#include "include_asm.h"

#include "common.h"
extern int D_L14_001B1680 __attribute__((sda));
extern int D_L14_001B1684 __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    TI128 pos;           
    TI128 next;          
    float height;        
    int handle;          
    int pad28;           
    int count;           
    int mode;            
    int shape;           
    int row;             
    int dirty;           
    float f40;           
    float f44;           
    int coreColor;       
    int haloColor;       
} RibbonOwnerState;
extern void func_L11_0046BC08(void *self);
extern void func_L14_00422498(void *self);
extern void func_L00_002E6EF8(void (*callback)(char *), void *object);
extern void func_PAL_L14_00427E08(char *object);
extern int func_00291308(float *position, float range, float radius, int color);
extern int D_L14_001B1618 __attribute__((sda));
extern float D_L14_001B1688 __attribute__((sda));
extern float D_L14_001B168C __attribute__((sda));
extern char *D_L14_001FE1C0[];
extern char D_L14_002594F0[][0x280];

/* Moves the ribbon's head to the object's position, eases its height and adds it to the
   head; when the state is dirty, refreshes the newest four points of the ribbon's row from
   the shape table and queues the draw callback. On the first update it resets the state. */
void func_PAL_L14_00427720(char *self)
{
    RibbonOwnerState *st = *(RibbonOwnerState **)(self + 0x68);
    float v[4] __attribute__((aligned(16)));
    char *src;
    int count;
    int i;

    qcopy(&st->pos, self + 0x10);
    qcopy(&st->next, &st->pos);
    st->height += (6.0f - st->height) * 0.08400001f + 12.0f;
    v[0] = 0;
    v[1] = st->height;
    v[2] = 0;
    func_00282CC0(&st->next, &st->pos, v);
    /* The new head is copied back into v as well; v is not used again. */
    qcopy(v, &st->next);
    D_L14_001B1618 = 20;
    func_L11_0046BC08(self);

    if (st->dirty != 0) {
        func_L14_00422498(self);
        count = D_L14_001B1618;
        src = D_L14_001FE1C0[st->shape];
        for (i = count - 4; i < count; i++) {
            qcopy_nc(&D_L14_002594F0[st->row][i * 16], src + i * 16 + 0x10);
        }
        func_L00_002E6EF8(func_PAL_L14_00427E08, self);
    }

    if (*(unsigned char *)(self + 0x20) == 0) {
        st->dirty = 0;
        st->handle = func_00291308((float *)&st->pos, 0.0f, 0.0f, 0);
        *(unsigned char *)(self + 0x20) = 1;
        st->count = D_L14_001B1618;
        st->coreColor = D_L14_001B1680;
        st->haloColor = D_L14_001B1684;
        st->f40 = D_L14_001B1688;
        st->f44 = D_L14_001B168C;
        st->mode = -1;
    }
}
