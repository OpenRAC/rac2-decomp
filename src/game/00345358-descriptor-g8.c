#include "names.h"
/* Build the menu descriptor, retaining its default initialization before overrides. */
typedef struct { unsigned int lo; unsigned int hi; } Word2_462A8;

extern void DrawItemGrid(int *);

extern char D_00259CE0[];

extern Word2_462A8 D_001AE0B0 __attribute__((nosda));

extern int D_001AE440 __attribute__((sda));

extern int D_001AE444 __attribute__((sda));

extern int D_001AE448 __attribute__((sda));

extern int D_001AE450 __attribute__((sda));

extern int D_001AE458 __attribute__((sda));

extern int D_001AE460 __attribute__((sda));

extern int D_001AE468 __attribute__((sda));

static __inline__ void initDescriptor_462A8(int *f) { f[20] = 0; f[21] = 1; }

void item_grid_draw_page(char *menu)
{
    struct { Word2_462A8 q; int f[23] __attribute__((aligned(16))); } local;

    local.q = D_001AE0B0;

    initDescriptor_462A8(local.f);
    local.f[19] = *(int *)(menu + 0x494);
    local.f[21] = (*(int *)(menu + 0x498) == 0);
    local.f[3] = *(int *)(menu + 0x48C);
    local.f[4] = *(int *)(menu + 0x490);
    local.f[16] = (int)(menu + 0x448);
    local.f[9] = (int)&D_001AE468;
    local.f[1] = D_001AE440;
    local.f[2] = D_001AE444;
    local.f[0] = (int)D_00259CE0;
    local.f[17] = (int)(menu + 0x210);
    local.f[10] = (int)(menu + 0x130);
    local.f[12] = (int)(menu + 0x17C);
    local.f[15] = (int)(menu + 0x258);
    local.f[18] = *(int *)(menu + 0x400);
    local.f[8] = (int)&D_001AE460;
    local.f[7] = (int)&D_001AE458;
    local.f[6] = (int)&D_001AE450;
    local.f[5] = (int)&D_001AE448;
    local.f[14] = 0;
    local.f[11] = 0;
    local.f[13] = 0;
    local.f[20] = (int)&local.q;
    local.f[22] = 1;
    DrawItemGrid(local.f);
}
