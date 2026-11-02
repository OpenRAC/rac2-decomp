/* functional: medium. Written from the assembly: plain floats, the 128-byte records are copied with the same helpers; the helpers' exact roles (func_00282A88 clears, func_00282B78 combines) are taken from their use here and not re-checked, and the name of each data word is unknown. */

extern float D_001B5340[4];             /* the eye */
extern int D_001B1714;                  /* 0: cell found directly, 1: not */
extern char *D_001B1718;                /* the record last used */
extern int D_001B170C;                  /* mode: 0 hold, 1 clear, 2 corners, 3 directions */
extern char *D_001B1704;                /* mode 2: a box origin followed by 8 records */
extern char *D_001B1708;                /* mode 3: a centre followed by the direction records */
extern char D_001BADC0[128];            /* the result record */
extern char D_001BAE40[128];            /* scratch record */

extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_0027A0F8(int, int, int);
extern int func_0027A1D0(float x, int a, int b, int c, int d, int e, int g);
extern void func_00282B50(void *, void *, int);
extern void func_00282A88(void *, int);
extern void func_00282B78(void *, void *, void *, int);
extern void func_00282A60(void *, int, int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);

/* the bin of the angle of (x, y): 16 to a quarter turn */
static int bin_0027A288(float x, float y)
{
    return func_00283CF0(func_00283248(x, y) * 10.185916f);
}

/* Picks the 128-byte record for the eye's place and leaves it at D_001BADC0, with bit 7 of its
   last byte set. The eye's cell (a quarter-unit grid) is looked up; when the cell has none, the
   records of the cell's neighbours are combined, or, by mode, the box's corner, the direction
   record or the last record is used, or the result is filled with -1. */
void func_0027A288(void)
{
    int ix, iy, iz;
    int cell, nx, ny, nz;
    char *rec = 0;

    ix = func_00283CF0(D_001B5340[0] * 0.25f);
    iy = func_00283CF0(D_001B5340[1] * 0.25f);
    iz = func_00283CF0(D_001B5340[2] * 0.25f);
    cell = func_0027A0F8(ix, iy, iz);
    if (cell != 0) {
        D_001B1714 = 0;
        func_00282B50(D_001BADC0, (char *)cell, 128);
        D_001B1718 = (char *)cell;
        D_001BADC0[127] |= 0x80;
        return;
    }
    D_001B1714 = 1;

    if (D_001B170C == 0) {
        nx = func_0027A1D0(D_001B5340[0] * 0.25f - func_00283CE0(ix), ix - 1, iy, iz, ix + 1, iy, iz);
        ny = func_0027A1D0(D_001B5340[1] * 0.25f - func_00283CE0(iy), ix, iy - 1, iz, ix, iy + 1, iz);
        nz = func_0027A1D0(D_001B5340[2] * 0.25f - func_00283CE0(iz), ix, iy, iz - 1, ix, iy, iz + 1);
        if (nx != 0 || ny != 0 || nz != 0) {
            func_00282A88(D_001BAE40, 128);
            if (nx != 0) {
                func_00282B78(D_001BAE40, D_001BAE40, (char *)nx, 128);
            }
            if (ny != 0) {
                func_00282B78(D_001BAE40, D_001BAE40, (char *)ny, 128);
            }
            if (nz != 0) {
                func_00282B78(D_001BAE40, D_001BAE40, (char *)nz, 128);
            }
            D_001B1718 = D_001BAE40;
            func_00282B50(D_001BADC0, D_001BAE40, 128);
            D_001BADC0[127] |= 0x80;
            return;
        }
    }

    switch (D_001B170C) {
    case 0:
        if (D_001B1718 != 0) {
            func_00282B50(D_001BADC0, D_001B1718, 128);
        } else {
            func_00282A60(D_001BADC0, -1, 128);
        }
        break;
    case 1:
        func_00282A60(D_001BADC0, -1, 128);
        break;
    case 2:
        rec = D_001B1704;
        if (rec == 0) {
            if (D_001B1718 != 0) {
                func_00282B50(D_001BADC0, D_001B1718, 128);
            } else {
                func_00282A60(D_001BADC0, -1, 128);
            }
        } else {
            int bx = D_001B5340[0] - ((float *)rec)[0] > 0.0f;
            int by = D_001B5340[1] - ((float *)rec)[1] > 0.0f;
            int bz = D_001B5340[2] - ((float *)rec)[2] > 0.0f;

            func_00282B50(D_001BADC0, rec + (((bx << 2) + (by << 1) + bz) << 7) + 16, 128);
        }
        break;
    case 3:
        rec = D_001B1708;
        if (rec == 0) {
            if (D_001B1718 != 0) {
                func_00282B50(D_001BADC0, D_001B1718, 128);
            } else {
                func_00282A60(D_001BADC0, -1, 128);
            }
        } else {
            float a[4], b[4];
            float dx, dy, dz, b0;
            int s0 = 0;

            a[0] = ((float *)rec)[0];
            a[1] = ((float *)rec)[1];
            a[2] = ((float *)rec)[2];
            a[3] = 0.0f;
            dx = D_001B5340[0] - a[0];
            dy = D_001B5340[1] - a[1];
            dz = D_001B5340[2] - a[2];
            b[0] = dx;
            b[1] = dy;
            b[2] = dz;
            b[3] = 0.0f;
            b0 = dx;

            /* the flat direction in 16 bins per quarter, the distance replaces b[0] */
            if (dx > 0.0f && dy > 0.0f) {
                s0 = bin_0027A288(dx, dy) << 6;
                b0 = func_00282E80(D_001B5340, a);
            } else if (dx <= 0.0f && dy > 0.0f) {
                s0 = 1024;
                if (dx == 0.0f) {
                    b0 = dy;
                } else {
                    s0 = (bin_0027A288(dy, -dx) << 6) + 1024;
                    b0 = func_00282E80(D_001B5340, a);
                }
            } else if (dx < 0.0f && dy < 0.0f) {
                s0 = bin_0027A288(-dx, -dy) << 6;
                b0 = -func_00282E80(D_001B5340, a);
            } else if (dx >= 0.0f && dy < 0.0f) {
                s0 = 1024;
                if (dx == 0.0f) {
                    b0 = dy;
                } else {
                    s0 = (bin_0027A288(-dy, dx) << 6) + 1024;
                    b0 = -func_00282E80(D_001B5340, a);
                }
            }
            b[0] = b0;

            /* then the slope against that distance */
            if (dz > 0.0f && b0 > 0.0f) {
                s0 += bin_0027A288(dz, b0);
            } else if (dz <= 0.0f && b0 > 0.0f) {
                s0 += 16;
                if (dz != 0.0f) {
                    s0 += bin_0027A288(b0, -dz);
                }
            } else if (dz < 0.0f && b0 <= 0.0f) {
                s0 += 32;
                if (b0 != 0.0f) {
                    s0 += bin_0027A288(-dz, -b0);
                }
            } else if (dz >= 0.0f && b0 < 0.0f) {
                s0 += 48;
                if (dz != 0.0f) {
                    s0 += bin_0027A288(-b0, dz);
                }
            }
            func_00282B50(D_001BADC0, rec + (s0 << 7) + 16, 128);
        }
        break;
    default:
        break;
    }
    D_001BADC0[127] |= 0x80;
}
