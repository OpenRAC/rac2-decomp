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
extern float D_001AD5C8[] MACRO_ADDR;
extern int D_001AD5A4 __attribute__((sda)), D_001AD5AC __attribute__((sda));
extern float func_00282C10(float);
extern float func_00282C48(float);

/* Adds a ripple bump to the water surface patches around a point and copies edge values to neighbouring patches. */
void func_002FD1B8(SurfacePatch *patch, int count, int mode,
                  float x, float y, float radius, float strength)
{
    SurfacePatch *patches = patch;
    int n;
    for (n = 0; n < count; n++) {
        float centerY = patch->y + D_001AD5C8[1];
        float centerX = patch->x + D_001AD5C8[0];
        float gridY = (y - centerY) / D_001AD5C8[3];
        float gridX = (x - centerX) / D_001AD5C8[2];
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
        rowY = centerY + D_001AD5C8[3] * (float)firstY;
        for (row = firstY; row <= lastY; row++) {
            columnX = patch->x + D_001AD5C8[0] + D_001AD5C8[2] * (float)firstX;
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
                    if (FloatAbs(impulse) < FloatAbs(patch->samples[D_001AD5A4].rows[row][column]))
                        impulse = patch->samples[D_001AD5A4].rows[row][column];
                } else impulse += patch->samples[D_001AD5AC].rows[row][column];
                page = D_001AD5A4;
                patch->samples[D_001AD5A4].rows[row][column] = impulse;
                if (row < 2 && patch->neighbor[0] != 255) {
                    if (row == 0) patches[patch->neighbor[0]].samples[page].top[column] = patch->samples[page].rows[row][column];
                    else patches[patch->neighbor[0]].samples[page].top2[column] = impulse;
                }
                if (column < 2 && patch->neighbor[1] != 255) {
                    if (column == 0) patches[patch->neighbor[1]].samples[D_001AD5A4].left[row] = patch->samples[D_001AD5A4].rows[row][column];
                    else patches[patch->neighbor[1]].samples[D_001AD5A4].left2[row] = patch->samples[D_001AD5A4].rows[row][column];
                }
                if (row == 15 && patch->neighbor[2] != 255)
                    patches[patch->neighbor[2]].samples[D_001AD5A4].bottom[column] = patch->samples[D_001AD5A4].rows[row][column];
                if (column == 15 && patch->neighbor[3] != 255)
                    patches[patch->neighbor[3]].samples[D_001AD5A4].right[row] = patch->samples[D_001AD5A4].rows[row][column];
                if (patch->neighbor[4] != 255) {
                    if (column == 0 && row == 0) patches[patch->neighbor[4]].samples[D_001AD5A4].corners[3] = patch->samples[D_001AD5A4].rows[0][0];
                    if (column == 1 && row == 0) patches[patch->neighbor[4]].samples[D_001AD5A4].corners[4] = patch->samples[D_001AD5A4].rows[0][1];
                    if (column == 0 && row == 1) patches[patch->neighbor[4]].samples[D_001AD5A4].corners[5] = patch->samples[D_001AD5A4].rows[1][0];
                }
                if (patch->neighbor[5] != 255 && column == 15 && row == 0)
                    patches[patch->neighbor[5]].samples[D_001AD5A4].corners[2] = patch->samples[D_001AD5A4].rows[0][15];
                if (patch->neighbor[6] != 255 && column == 0 && row == 15)
                    patches[patch->neighbor[6]].samples[D_001AD5A4].corners[1] = patch->samples[D_001AD5A4].rows[15][0];
                if (patch->neighbor[7] != 255 && column == 15 && row == 15)
                    patches[patch->neighbor[7]].samples[D_001AD5A4].corners[0] = patch->samples[D_001AD5A4].rows[15][15];
                columnX += D_001AD5C8[2];
            }
            rowY += D_001AD5C8[3];
        }
        patch++;
    }
}
