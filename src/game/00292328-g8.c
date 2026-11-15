#include "common.h"

typedef struct {
    u64 data;
    u64 tag1;
    u64 tag2;
} Func00292328Packet;

extern int D_001A7298 MACRO_ADDR;
extern void *D_001A7294 MACRO_ADDR;
extern u64 D_001A72A0[] MACRO_ADDR;
extern Func00292328Packet D_001C4DC0[];
extern u64 D_001A91D0 __attribute__((sda));
extern char *D_001CDB80[];
extern void tex_relocate_render_groups(void *, int, void *);

/* Builds a list of draw packets from the loaded texture words and sends them off to be drawn. */
void tex_build_draw_packets(void *param)
{
    int i;

    for (i = 0; i < D_001A7298; i++) {
        D_001C4DC0[i].data = D_001A72A0[i];
        D_001C4DC0[i].tag1 = 0x0000FFA0000000E0ULL;
        D_001C4DC0[i].tag2 = 0x0040000400004000ULL;
    }
    tex_relocate_render_groups(D_001A7294, 0, &D_001A91D0);
    D_001CDB80[0][9] = D_001CDB80[0][8];
}
