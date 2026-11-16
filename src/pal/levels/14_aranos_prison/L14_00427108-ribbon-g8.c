#include "include_asm.h"

#include "common.h"
extern int g_ribbon_l14_core_color __attribute__((sda));
extern int g_ribbon_l14_halo_color __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
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
extern void ResetBoltPointsToLine(void *self);
extern void part_rebuild_lightning_bolt(void *self);
extern void gfx_add_draw_callback_third(void (*callback)(char *), void *object);
extern void func_PAL_L14_00427E08(char *object);
extern int gfx_add_point_light(float *position, float range, float radius, int color);
extern int g_ribbon_l14_segment_count __attribute__((sda));
extern float g_ribbon_l14_core_width __attribute__((sda));
extern float g_ribbon_l14_halo_width __attribute__((sda));
extern char *g_effect_path_table[];
extern char g_ribbon_buffers[][0x280];

/* Moves the ribbon's head to the object's position, eases its height and adds it to the
   head; when the state is dirty, refreshes the newest four points of the ribbon's row from
   the shape table and queues the draw callback. On the first update it resets the state. */
void ribbon_update_pal(char *self)
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
    FastVecAdd(&st->next, &st->pos, v);
    /* The new head is copied back into v as well; v is not used again. */
    qcopy(v, &st->next);
    g_ribbon_l14_segment_count = 20;
    ResetBoltPointsToLine(self);

    if (st->dirty != 0) {
        part_rebuild_lightning_bolt(self);
        count = g_ribbon_l14_segment_count;
        src = g_effect_path_table[st->shape];
        for (i = count - 4; i < count; i++) {
            qcopy_nc(&g_ribbon_buffers[st->row][i * 16], src + i * 16 + 0x10);
        }
        gfx_add_draw_callback_third(func_PAL_L14_00427E08, self);
    }

    if (*(unsigned char *)(self + 0x20) == 0) {
        st->dirty = 0;
        st->handle = gfx_add_point_light((float *)&st->pos, 0.0f, 0.0f, 0);
        *(unsigned char *)(self + 0x20) = 1;
        st->count = g_ribbon_l14_segment_count;
        st->coreColor = g_ribbon_l14_core_color;
        st->haloColor = g_ribbon_l14_halo_color;
        st->f40 = g_ribbon_l14_core_width;
        st->f44 = g_ribbon_l14_halo_width;
        st->mode = -1;
    }
}
