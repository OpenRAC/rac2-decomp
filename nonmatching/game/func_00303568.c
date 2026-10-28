/* func_00303568 - 460 bytes.  Worker attempt, 27 October 2026 (draft below).

   Dropped-quality draft (380 B vs 460). Logic decoded: bilinear sample in
   8-wide grid of 16B points (ref_L00_00303568_00 = 0x222AE0 in L00). Retail
   keeps 9 callee regs live (s0..s7,fp), spills int ix to sp+0, keeps
   &g[cell].x in s5 and &g[cell].y in s6 and bases grid/grid+4 in s3/s7; mine
   CSEs these so is 80 B short. Tried struct cells, float* gx/gy, px/py
   pointers. */

/* replaces the marker in src/game/00300618.c */
extern float ref_L00_00303568_00[];
extern float func_002A7878(float, float);
extern float func_00283CB8(float);

/* Picks a random point inside a cell of an eight-wide grid of 16-byte points and writes the
   point bilinearly interpolated from the cell's corners. */
void func_00303568(char *object, float *out)
{
    char *owner = *(char **)(object + 0x68);
    float *gx = ref_L00_00303568_00;
    float *gy = ref_L00_00303568_00 + 1;
    float fx = func_002A7878(0.0f, 6.99f);
    int ix = (int)fx;
    float fy = func_002A7878(0.0f, 6.99f);
    int iy = (int)fy;
    int cell = *(int *)(owner + 0x40) * 64 + iy * 8 + ix;
    float t;

    float *px = gx + cell * 4;
    float *py = gy + cell * 4;

    out[0] = *px;
    out[1] = *py;
    t = func_00283CB8(fx);
    out[0] += (gx[(cell + 1) * 4] - *px) * t;
    out[1] += (gy[(cell + 1) * 4] - *py) * t;
    t = func_00283CB8(fy);
    out[0] += (gx[(cell + 8) * 4] - *px) * t;
    out[1] += (gy[(cell + 8) * 4] - *py) * t;
    out[3] = 1.0f;
    out[2] = px[2];
}
