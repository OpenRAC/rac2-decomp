#include "common.h"

/* Three height planes per patch, including mirrored edges and corner samples. */
typedef struct {
    float x, y;
    u8 header08[4];
    u8 neighbor[8];
    u8 header14[0x50 - 0x14];
    struct {
        float rows[16][16];
        float bottom[16], right[16], top[16], left[16];
        float top2[16], left2[16], corners[16];
    } samples[3];
} SurfacePatch;

/* Grid offsets and cell sizes are adjacent members of the ripple parameters. */
extern float g_disturb_grid_params[] MACRO_ADDR;
extern int g_disturb_page_current __attribute__((sda)), g_disturb_page_other __attribute__((sda));
extern float square_root(float);
extern float math_fabs(float);

/* Adds a ripple bump to the water surface patches around a point and copies edge values to neighbouring patches. */
void RippleDisturb(SurfacePatch *patch, int count, int mode,
                  float x, float y, float radius, float strength)
{
    SurfacePatch *patches = patch;
    int n;
    for (n = 0; n < count; n++) {
        float centerY = patch->y + g_disturb_grid_params[1];
        float centerX = patch->x + g_disturb_grid_params[0];
        float gridY = (y - centerY) / g_disturb_grid_params[3];
        float gridX = (x - centerX) / g_disturb_grid_params[2];
        int firstY = (int)(gridY - radius);
        int lastY = (int)(gridY + radius);
        int row, column, firstX, lastX;
        float rowY, columnX;
        if (firstY < 0) firstY = 0;
        if (lastY > 15) lastY = 15;
        firstX = (int)(gridX - radius);
        lastX = (int)(gridX + radius);
        if (lastX > 15) lastX = 15;
        if (firstX < 0) firstX = 0;
        rowY = centerY + g_disturb_grid_params[3] * (float)firstY;
        for (row = firstY; row <= lastY; row++) {
            columnX = patch->x + g_disturb_grid_params[0] + g_disturb_grid_params[2] * (float)firstX;
            for (column = firstX; column <= lastX; column++) {
                float dy = y - rowY;
                float squaredY = dy * dy;
                float dx = x - columnX;
                float distanceSquared = dx * dx + squaredY;
                float impulse;
                int page;
                if (distanceSquared < 1.0f) impulse = strength;
                else impulse = strength / square_root(distanceSquared);
                if (mode == 0) {
                    if (math_fabs(impulse) < math_fabs(patch->samples[g_disturb_page_current].rows[row][column]))
                        impulse = patch->samples[g_disturb_page_current].rows[row][column];
                } else impulse += patch->samples[g_disturb_page_other].rows[row][column];
                page = g_disturb_page_current;
                patch->samples[g_disturb_page_current].rows[row][column] = impulse;
                if (row < 2 && patch->neighbor[0] != 255) {
                    if (row == 0) patches[patch->neighbor[0]].samples[page].top[column] = patch->samples[page].rows[row][column];
                    else patches[patch->neighbor[0]].samples[page].top2[column] = impulse;
                }
                if (column < 2 && patch->neighbor[1] != 255) {
                    if (column == 0) patches[patch->neighbor[1]].samples[g_disturb_page_current].left[row] = patch->samples[g_disturb_page_current].rows[row][column];
                    else patches[patch->neighbor[1]].samples[g_disturb_page_current].left2[row] = patch->samples[g_disturb_page_current].rows[row][column];
                }
                if (row == 15 && patch->neighbor[2] != 255)
                    patches[patch->neighbor[2]].samples[g_disturb_page_current].bottom[column] = patch->samples[g_disturb_page_current].rows[row][column];
                if (column == 15 && patch->neighbor[3] != 255)
                    patches[patch->neighbor[3]].samples[g_disturb_page_current].right[row] = patch->samples[g_disturb_page_current].rows[row][column];
                if (patch->neighbor[4] != 255) {
                    if (column == 0 && row == 0) patches[patch->neighbor[4]].samples[g_disturb_page_current].corners[3] = patch->samples[g_disturb_page_current].rows[0][0];
                    if (column == 1 && row == 0) patches[patch->neighbor[4]].samples[g_disturb_page_current].corners[4] = patch->samples[g_disturb_page_current].rows[0][1];
                    if (column == 0 && row == 1) patches[patch->neighbor[4]].samples[g_disturb_page_current].corners[5] = patch->samples[g_disturb_page_current].rows[1][0];
                }
                if (patch->neighbor[5] != 255 && column == 15 && row == 0)
                    patches[patch->neighbor[5]].samples[g_disturb_page_current].corners[2] = patch->samples[g_disturb_page_current].rows[0][15];
                if (patch->neighbor[6] != 255 && column == 0 && row == 15)
                    patches[patch->neighbor[6]].samples[g_disturb_page_current].corners[1] = patch->samples[g_disturb_page_current].rows[15][0];
                if (patch->neighbor[7] != 255 && column == 15 && row == 15)
                    patches[patch->neighbor[7]].samples[g_disturb_page_current].corners[0] = patch->samples[g_disturb_page_current].rows[15][15];
                columnX += g_disturb_grid_params[2];
            }
            rowY += g_disturb_grid_params[3];
        }
        patch++;
    }
}
