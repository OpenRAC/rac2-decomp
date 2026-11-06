/* Special map coordinates for the current level. The absolute aliases name
 * the same adjoining float blocks as the GP scalars; offset accesses retain
 * retail's absolute loads. The four coordinate pairs occupy 32 bytes, hence
 * this unit's -G32 profile.
 */
extern float absolute_D_001A9410[] __attribute__((section(".sdata")));
extern float absolute_D_001A9680[] __attribute__((section(".sdata")));
extern float absolute_D_001A9678[] __attribute__((section(".sdata")));
extern float absolute_D_001A9670[] __attribute__((section(".sdata")));
extern float D_001A9410 __attribute__((sda));
extern float D_001A9680 __attribute__((sda));
extern float D_L00_001A9760 __attribute__((sda));
extern float D_001A9670 __attribute__((sda));
extern int D_001A8CC0 __attribute__((section(".sdata")));
extern int D_001A79F0 __attribute__((section(".sdata")));
extern int D_001C4F40 __attribute__((nosda));
typedef struct {
    unsigned char reserved00[0x80];
    float x, y, z;
} MapPlayerView;

extern MapPlayerView D_00189E20;
extern float D_001A9678 __attribute__((sda));
extern float D_001A9688[8] __attribute__((sda));
extern float D_001A968C[] __attribute__((section(".sdata")));
extern int func_003005A0(void);
extern void func_00297FE8(float, float, float *, float *, int);
/* Callers pass (x, y, &u, &v, level): the player's coordinates in $f12/$f13, the two result
 * pointers in $a2/$a3 and the level number on the stack. This body keys on the global level
 * and the player view, so the coordinates and the level are unused. */
int func_00297218(float unused_x, float unused_y, float *x, float *y, int unused_level)
{
    int found = 0;
    if (D_001A8CC0) {
        if (D_001A79F0 == 2) {
            *x = D_001A9670;
            *y = absolute_D_001A9670[1];
            found = 1;
        } else if (D_001A79F0 == 11) {
            *x = D_001A9678;
            *y = absolute_D_001A9678[1];
            found = 1;
        }
    }
    if (D_001A79F0 == 7 && func_003005A0() >= 0 && func_003005A0() < 4) {
        found = 1;
        *x = D_001A9688[func_003005A0() * 2];
        *y = D_001A968C[func_003005A0() * 2];
    } else if (D_001A79F0 == 20) {
        if (D_001C4F40 == 2) {
            found = 1;
            *x = D_001A9680;
            *y = absolute_D_001A9680[1];
        } else if (D_001C4F40 == 0) {
            if (D_00189E20.x >= D_001A9410 && D_00189E20.y <= absolute_D_001A9410[1] &&
                D_00189E20.x <= absolute_D_001A9410[2] && D_00189E20.y >= absolute_D_001A9410[3]) {
                found = 1;
                func_00297FE8(D_00189E20.x, D_00189E20.y, x, y, 20);
                *x += D_L00_001A9760;
                *y += absolute_D_001A9410[5];
            }
        }
    }
    return found;
}
