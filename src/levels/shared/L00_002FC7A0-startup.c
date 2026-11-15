#include "names.h"
typedef struct {
    short id, animation;
    float scale;
} StartupEntry;
typedef struct { StartupEntry entries[13]; } StartupTable;
typedef struct {
    unsigned char pad00[0x30];
    int state;
    unsigned char pad34[0x10];
    short count;
    unsigned char pad46[0x146];
    unsigned char *objects[0];
} StartupContext;

extern StartupTable D_L00_002A0E60;
extern unsigned char D_001A7A40 __attribute__((section(".sdata")));
extern StartupContext D_L00_001BCAC0;
extern unsigned char D_L00_0022F600[];
extern float D_L00_001A8FC8 __attribute__((section(".sdata")));
extern int D_001A79F0 __attribute__((section(".sdata")));
extern void func_L00_00311238(void *, int, void *);

/* Starts the configured startup animation for eligible objects in the level. */
void func_L00_002FC980(void)
{
    StartupTable table;
    int i;
    if (D_001A7A40) {
        table = D_L00_002A0E60;
        for (i = 0; i < D_L00_001BCAC0.count; i++) {
            unsigned char *object = D_L00_001BCAC0.objects[i];
            int j;
            if (*(int *)(object + 0x54))
                continue;
            for (j = 0; table.entries[j].id; j++) {
                if (*(short *)(object + 0xaa) == table.entries[j].id) {
                    float scale = table.entries[j].scale;
                    int k;
                    for (k = 0; k < 7; k++) {
                        if (!D_L00_0022F600[k * 64 + 1])
                            break;
                    }
                    if (k < 7) {
                        unsigned char *slot = D_L00_0022F600 + k * 64;
                        func_L00_00311238(object, table.entries[j].animation, slot);
                        *(float *)(slot + 0x20) = scale;
                        *(float *)(slot + 0x24) = scale;
                        *(float *)(slot + 0x28) = scale;
                    }
                }
            }
        }
        if (gCurrentMapIndex == 6 && D_L00_001BCAC0.state == 1)
            D_L00_001A8FC8 = -0.25f;
    }
}
