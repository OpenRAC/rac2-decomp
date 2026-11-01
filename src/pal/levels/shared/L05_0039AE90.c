#include "include_asm.h"

#include "common.h"
typedef struct {
    float f[38];
    int timer;
    char *owner;
    int active;
    int pad;
    int dying;
    int pad2;
} Record233560;
extern Record233560 D_L05_00233560[24];
extern void func_PAL_L00_003F6A90(char *, char *);
extern float func_002A7878(float, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);

/* func_L05_00397F48 is in L05_00397F48-g8.c. */

/* Walks the twenty-four records, and for each one the object owns updates it and, while it is
   not active, lays the three colours over its vector. */
void func_PAL_L05_0039AE90(char *arg0)
{
    int i;
    for (i = 0; i < 24; i++) {
        Record233560 *rec = &D_L05_00233560[i];
        float *pos = &rec->f[12];
        if (rec->owner == arg0) {
            func_PAL_L00_003F6A90(arg0, (char *)rec);
            if (rec->active == 0) {
                func_00281EB8(pos, 0x31, 0x3F0000FF, 1, func_002A7878(0.065f, 0.1f) * 5.0f, 1.25f, 0.0f);
                func_00281EB8(pos, 0x31, 0x5F7F7F7F, 1, func_002A7878(0.0325f, 0.06f) * 5.0f, 1.24f, 0.0f);
                func_00281EB8(pos, 0xB, 0x1000003F, 1, func_002A7878(0.07f, 0.15f) * 5.0f, 1.23f, 0.0f);
            }
        }
    }
}


