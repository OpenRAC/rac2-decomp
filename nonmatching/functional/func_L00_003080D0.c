/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Claude Opus 5.5 (opus-1), v1655, 2026-10-30: 820/820 bytes, 0/27 US places
 * (also 0/27 PAL and US v2.00). Profile: default -O2 -G0 -ffunction-sections
 * (src/levels/shared/L00_002FC7A0.c, in place of the marker).
 * Frame, spill slots, all callee-saved and caller-saved (sq/lq) roles, mask base,
 * reload choices and control flow now agree with retail; only two local register
 * choices differ (about ten instructions):
 *  - +0x128..+0x14C: the first colour sample takes x&31 in v0 and the samples
 *    pointer in v1 (retail v1/v0). sched1 puts the floating `sampleRow = y & 31`
 *    (its pseudo crosses calls, so it is not pinned after the call) into the call's
 *    cycle, ahead of x&31; local-alloc then gives x&31 v0. Retail evidently had
 *    x&31 first after the call.
 *  - +0x29C..+0x2C4: the inner nibble `sample` takes v0 (retail v1); it is the top
 *    global allocno and nothing excludes v0 here.
 * Measured levers (keep them): one sampleRow variable assigned in two steps
 * (`= r & 31; *= 16`) for both rows (s5, intermediate in s5); one regionRow for the
 * first and the loop call (t0); dy computed before the inner loop and the mask read
 * as *(mask[0] + (dx / 8 + (dy << 2))) (a shift is hoisted, a `* 4` is not; dx/8
 * first keeps dy4 from preferring a0, which otherwise pushes row to a1);
 * declarations x, y, maxY, maxX, minY, minX (spill slot order); bounds computed
 * minY, minX, maxY, maxX and clamped minY, maxY, minX, maxX (minY before x in
 * allocation, retail reload registers). Ties: separate value/sample byte, the
 * pointer-split first sample, regionRow before the bounds. `int sample` gives sra.
 */
typedef struct Map80D0 {
    unsigned char pad00[0xc];
    unsigned char *bitmap;
    unsigned char pad10[0x18];
    int active;
    unsigned char pad2c[0xc];
    unsigned char *samples;
    unsigned char pad3c[0x174];
    unsigned char mask[32][4];
} Map80D0;
extern Map80D0 D_L00_001C93A0;
extern int D_001A79F0 __attribute__((sda));
extern int func_L00_00308538(void);
extern int func_L00_00308700(int);
extern void func_00297FE8(float, float, float *, float *, int);
void func_L00_003080D0(float *position)
{
    float px, py;
    int x, y, maxY, maxX, minY, minX;
    int row, col;
    int colour;
    int regionRow, sampleRow;
    unsigned char sample;
    unsigned char *cell;
    int bit;
    if (D_L00_001C93A0.active == 0)
        return;
    if (func_L00_00308538())
        return;
    func_00297FE8(position[0], position[1], &px, &py, D_001A79F0);
    x = (int)(px * 512.0f) + 1;
    y = (int)(py * 512.0f) + 1;
    if (x < 0 || y < 0 || x >= 512 || y >= 512)
        return;
    minY = y - 16;
    minX = x - 16;
    maxY = y + 16;
    maxX = x + 16;
    if (minY < 0) minY = 0;
    if (maxY >= 512) maxY = 511;
    if (minX < 0) minX = 0;
    if (maxX >= 512) maxX = 511;
    regionRow = (y >> 5) * 16;
    func_L00_00308700((x >> 5) + regionRow);
    sampleRow = y & 31;
    sampleRow *= 16;
    {
        unsigned char value = *(D_L00_001C93A0.samples + (x & 31) / 2 + sampleRow);
        if (x & 1) value >>= 4;
        else value &= 15;
        colour = value;
    }
    for (row = minY; row < maxY; row++) {
        int dy;
        dy = row - y + 16;
        regionRow = (row >> 5) * 16;
        sampleRow = row & 31;
        sampleRow *= 16;
        for (col = minX; col < maxX; col++) {
            cell = D_L00_001C93A0.bitmap + row * 64 + col / 8;
            if (*cell != 0) {
                bit = 1 << (col & 7);
                if (*cell & bit) {
                    int dx = col - x + 16;
                    if ((*(D_L00_001C93A0.mask[0] + (dx / 8 + (dy << 2))) >> (dx % 8)) & 1)
                        continue;
                    func_L00_00308700((col >> 5) + regionRow);
                    sample = *(D_L00_001C93A0.samples + (col & 31) / 2 + sampleRow);
                    if (col & 1) sample >>= 4;
                    else sample &= 15;
                    if (colour == sample)
                        *cell &= ~bit;
                }
            }
        }
    }
}
