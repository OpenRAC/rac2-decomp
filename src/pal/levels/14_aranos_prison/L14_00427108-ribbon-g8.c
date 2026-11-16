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
extern void gfx_draw_ribbon_pair_pal(char *object);
extern int gfx_add_point_light(float *position, float range, float radius, int color);
extern int g_ribbon_l14_segment_count __attribute__((sda));
extern float g_ribbon_l14_core_width __attribute__((sda));
extern float g_ribbon_l14_halo_width __attribute__((sda));
extern char *g_effect_path_table[];
extern char g_ribbon_buffers[][0x280];

/* Moves the ribbon's head to the object's position, eases its height and adds it to the
   head; when the state is dirty, refreshes the newest four points of the ribbon's row from
   the shape table and queues the draw callback. On the first update it resets the state. */
void ribbon_update_pal(char *moby)
{
    RibbonOwnerState *ribbon = *(RibbonOwnerState **)(moby + 0x68);
    float up[4] __attribute__((aligned(16)));
    char *path;
    int count;
    int i;

    qcopy(&ribbon->pos, moby + 0x10);
    qcopy(&ribbon->next, &ribbon->pos);
    ribbon->height += (6.0f - ribbon->height) * 0.08400001f + 12.0f;
    up[0] = 0;
    up[1] = ribbon->height;
    up[2] = 0;
    FastVecAdd(&ribbon->next, &ribbon->pos, up);
    /* The new head is copied back into up as well; up is not used again. */
    qcopy(up, &ribbon->next);
    g_ribbon_l14_segment_count = 20;
    ResetBoltPointsToLine(moby);

    if (ribbon->dirty != 0) {
        part_rebuild_lightning_bolt(moby);
        count = g_ribbon_l14_segment_count;
        path = g_effect_path_table[ribbon->shape];
        for (i = count - 4; i < count; i++) {
            qcopy_nc(&g_ribbon_buffers[ribbon->row][i * 16], path + i * 16 + 0x10);
        }
        gfx_add_draw_callback_third(gfx_draw_ribbon_pair_pal, moby);
    }

    if (*(unsigned char *)(moby + 0x20) == 0) {
        ribbon->dirty = 0;
        ribbon->handle = gfx_add_point_light((float *)&ribbon->pos, 0.0f, 0.0f, 0);
        *(unsigned char *)(moby + 0x20) = 1;
        ribbon->count = g_ribbon_l14_segment_count;
        ribbon->coreColor = g_ribbon_l14_core_color;
        ribbon->haloColor = g_ribbon_l14_halo_color;
        ribbon->f40 = g_ribbon_l14_core_width;
        ribbon->f44 = g_ribbon_l14_halo_width;
        ribbon->mode = -1;
    }
}
