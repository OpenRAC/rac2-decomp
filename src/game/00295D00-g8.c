#include "include_asm.h"
#include "names.h"

/* The map screen's pan/zoom update. Its unit is -G8 -g: the two screen-size words
   are $gp reads and the divisions carry the statement-boundary padding. */

extern int map_refresh_ready_flag(void);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int g_map_overlay_state[];
extern void map_empty_stub(void);
extern char g_pad_state[];
extern int D_001A95C0 __attribute__((sda));
extern int D_001A95C4 __attribute__((sda));

/* Map screen pan/zoom update: returns 1 (after func_002E5E58(0x13)) while the pad
   word +0x1C4 has 0x510 set, 0 when the map has nothing open (+0x24) or no slot
   (+0x234 < 0). Otherwise scales the slot's zoom (+0xB4) by 1 - speed * 0.02,
   clamps it to [0.65, 4], pans x/y (+0x108 / +0x15C) by the pad velocities times
   3000000 / zoom and clamps them to [lo, 0x10000000 - lo]. */
int map_update_overlay_pan_zoom(void)
{
    char *padState;
    char *mapState;
    float *zoom;
    int *panX;
    int *panY;

    map_empty_stub();
    map_refresh_ready_flag();
    padState = g_pad_state;
    if (*(int *)(padState + 0x1C4) & 0x510) {
        snd_play_from_global_bank(0x13, 0, 0);
        return 1;
    }
    mapState = (char *)g_map_overlay_state;
    if (*(int *)(mapState + 0x24) == 0)
        return 0;
    if (*(int *)(mapState + 0x234) < 0)
        return 0;
    zoom = (float *)(mapState + 0xB4);
    zoom[*(int *)(mapState + 0x234)] *= 1.0f - *(float *)(padState + 0x144) * 0.02f;
    if (zoom[*(int *)(mapState + 0x234)] > 4.0f)
        zoom[*(int *)(mapState + 0x234)] = 4.0f;
    if (zoom[*(int *)(mapState + 0x234)] < 0.65f)
        zoom[*(int *)(mapState + 0x234)] = 0.65f;
    panX = (int *)(mapState + 0x108);
    panY = (int *)(mapState + 0x15C);
    {
        float scale = 3000000.0f / zoom[*(int *)(mapState + 0x234)];
        panX[*(int *)(mapState + 0x234)] += (int)(*(float *)(padState + 0x148) * scale);
        panY[*(int *)(mapState + 0x234)] += (int)(*(float *)(padState + 0x14C) * scale);
    }
    {
        float curZoom = zoom[*(int *)(mapState + 0x234)];
        int minX = (int)((float)(0x1000 - D_001A95C0 * 16) / curZoom) << 15;
        int minY = (int)((float)(0xD00 - D_001A95C4 * 16) / curZoom) << 15;
        int maxX = 0x10000000 - minX;
        int maxY = 0x10000000 - minY;

        if (panX[*(int *)(mapState + 0x234)] < minX)
            panX[*(int *)(mapState + 0x234)] = minX;
        if (panX[*(int *)(mapState + 0x234)] > maxX)
            panX[*(int *)(mapState + 0x234)] = maxX;
        if (panY[*(int *)(mapState + 0x234)] < minY)
            panY[*(int *)(mapState + 0x234)] = minY;
        if (panY[*(int *)(mapState + 0x234)] > maxY)
            panY[*(int *)(mapState + 0x234)] = maxY;
    }
    return 0;
}
