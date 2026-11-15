#include "include_asm.h"
#include "names.h"

extern char D_L00_0025A920[];
extern void ref_L00_00417700_00(void *, void *);
extern float func_002A7878(float, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);

/* Redraws each lightning arc owned by this object and adds glow sprites while the arc is idle. */
void func_L00_00417700(char *moby)
{
    int tableAddress = (int)gSparkRecords_L00;
    char *glowPos = (char *)(tableAddress + 0x30);
    char *entry = (char *)tableAddress;
    int i;
    for (i = 0; i < 24; i++, entry += 0xB0, glowPos += 0xB0) {
        if (*(char **)(glowPos + 0x6C) == moby) {
            ref_L00_00417700_00(moby, entry);
            if (*(int *)(glowPos + 0x70) == 0) {
                DrawBillboardQuad_00281EB8(glowPos, 0x31, 0x3F7F0000, 1, RandomFloatRange(0.125f, 0.25f) * 5.0f, 1.25f, 0.0f);
                DrawBillboardQuad_00281EB8(glowPos, 0x31, 0x5F7F7F7F, 1, RandomFloatRange(0.0625f, 0.125f) * 5.0f, 1.24f, 0.0f);
                DrawBillboardQuad_00281EB8(glowPos, 0xB, 0x103F0000, 1, RandomFloatRange(0.15f, 0.35f) * 5.0f, 1.23f, 0.0f);
            }
        }
    }
}
