/* 8 November 2026 (Sonnet round 2): matching attempt improved to 14 differing rows (see nonmatching/game/func_003478F0.c); this functional variant is unchanged. */
/* functional: high. Same calls, arguments, reads and writes in retail's order; written without the near miss's register-allocation shaping. The bottom-row y adds the panel origin's x (pos[0]), exactly as retail does. */

/* Draws the 6x4 weapon grid of the weapon-select menu (owner o): for each cell of D_00259F58 (id at +6), the
 * slot background, then, when the weapon is owned (D_001A7AF8[id]), its icon, the ammo bar (max/current from
 * D_00239BA0 via the slot table D_00139568 and D_00139868), the bar colour from func_00336F20, the empty-ammo
 * tint and the highlight of the equipped weapon (func_0026F7A0(D_001F2880)), and the cell frame; then the
 * panel's fixed parts. */

extern void func_00335E68(void *, int);
extern int *func_00335E20(void *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00336320(void *);
extern void func_00336A78(void *);
extern void func_00336828(void *);
extern void func_00336920(void *, int, int);
extern void func_00336B90(void *, int);
extern void func_00336B98(void *, int);
extern void func_00336F20(int, int *, int *, int *);
extern void func_00336498(void *, int, int);
extern void func_00336548(void *);
extern int func_0026F7A0(void *);
extern void func_003472B8(void *);
extern void func_00347468(void *);

typedef struct { int x, y; } WeaponGridIntPair;
typedef struct { float x, y; } WeaponGridFloatPair;
typedef struct { short a, b, c, id, e; } WeaponGridCell;
typedef struct {
    char pad0[0x3c];
    unsigned short icon;      /* 0x3C */
    char pad3e[0x2e];
    int max;                  /* 0x6C */
    char pad70[0x18];
    unsigned short ammo;      /* 0x88 */
    char pad8a[0x56];
} WeaponGridRecord;           /* 0xE0 */

extern WeaponGridCell D_00259F58[];
extern unsigned char D_001A7AF8[];
extern unsigned char D_00139568[];
extern int D_00139868[];
extern int D_00139688[];
extern WeaponGridRecord D_00239BA0[];
extern void *D_001F2880;
extern int D_001AE750, D_001AE754, D_001AE748, D_001AE74C;
extern float D_001AE758, D_001AE75C;
extern WeaponGridIntPair D_001AE588, D_001AE590;
extern WeaponGridFloatPair D_001AE598, D_001AE5A0;

void func_003478F0(char *o)
{
    int row, col;

    if (*(int *)(o + 0x4f8) == 0)
        return;
    func_00336320(o);
    func_00336320(o + 0x4c);
    func_00336320(o + 0x130);
    for (row = 0; row < 6; row++) {
        WeaponGridCell *cell = &D_00259F58[row * 4];
        for (col = 0; col < 4; col++, cell++) {
            float fcol = (float)col, frow = (float)row;
            int id;
            {
                int *color = func_00335E20(o + 0x3b4);
                float x = D_001AE758 * fcol + (float)D_001AE750;
                float y = D_001AE75C * frow + (float)D_001AE754;
                float *pos;
                *color = 0x60241700;
                pos = *(float **)(o + 0x498);
                func_00335E38(o + 0x3b4, x + pos[0], y + pos[1], 0.0f, 0.0f);
            }
            *func_00335E20(o + 0x98) = 0x30f0c070;
            *func_00335E20(o + 0x3b4) = 0x60241700;
            func_00335E68(o + 0x1c8, 0);
            func_00335E68(o + 0x378, 0);
            id = cell->id;
            if (D_001A7AF8[id]) {
                float *pos;
                func_00336920(o + 0x378, D_00239BA0[D_00139568[id]].icon, 0);
                pos = *(float **)(o + 0x498);
                func_00335E38(o + 0x378,
                              (fcol * 53.5f + (float)D_001AE748) + pos[0],
                              (frow * 47.0f + (float)D_001AE74C) + pos[1], 0.0f, 0.0f);
                id = cell->id;
                if (D_00239BA0[D_00139568[id]].icon == 0xea7e) {
                    *func_00335E20(o + 0x378) = 0x80808080;
                } else {
                    WeaponGridIntPair base = D_001AE588, stride = D_001AE590;
                    int a, b, color;
                    func_00336B90(o + 0x1c8, D_00239BA0[D_00139568[id]].max);
                    func_00336B98(o + 0x1c8, D_00139868[cell->id] >> 5);
                    pos = *(float **)(o + 0x498);
                    func_00335E38(o + 0x1c8, (float)(stride.x * col + base.x) + pos[0],
                                  (float)(stride.y * row + base.y) + pos[1], 0.0f, 0.0f);
                    func_00335E68(o + 0x1c8, 1);
                    a = 0;
                    b = 0;
                    color = 0;
                    func_00336F20(cell->id, &a, &b, &color);
                    func_00336498(o + 0x1c8, a, b);
                    *func_00335E20(o + 0x378) = color;
                    if (D_00239BA0[D_00139568[cell->id]].max <= 0) {
                        func_00336B90(o + 0x1c8, 100);
                        func_00336B98(o + 0x1c8, 100);
                    }
                }
                id = cell->id;
                if (D_00139688[id] == 0 && D_00239BA0[D_00139568[id]].ammo != 0)
                    *func_00335E20(o + 0x3b4) = 0x60202080;
                func_00335E68(o + 0x378, 1);
                if (func_0026F7A0(D_001F2880) == cell->id)
                    *func_00335E20(o + 0x98) = 0x80ffde8d;
            }
            {
                WeaponGridFloatPair stride = D_001AE598, base = D_001AE5A0;
                float *pos = *(float **)(o + 0x498);
                /* retail adds pos[0] to both coordinates */
                func_00335E38(o + 0x98, (stride.x * fcol + base.x) + pos[0],
                              (stride.y * frow + base.y) + pos[0], 0.0f, 0.0f);
            }
            func_00336320(o + 0x3b4);
            func_00336828(o + 0x378);
            func_00336548(o + 0x1c8);
            func_00336320(o + 0x98);
        }
    }
    func_00336320(o + 0xe4);
    func_00336320(o + 0x17c);
    func_00336A78(o + 0x210);
    func_00336A78(o + 0x258);
    func_00336A78(o + 0x2a0);
    func_003472B8(o);
    func_00347468(o);
}
