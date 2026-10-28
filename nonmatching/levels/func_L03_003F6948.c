/* Retained meaningful C; not matching. 2026-10-28 game -O2 -G0
 * -ffunction-sections:604/604 bytes at the sole US place. Nine compiles.
 * Separate cleanup/vertex/render indices restore GPR allocation. Explicit
 * cleanup arms prevent adjacent-state range folding; a shared callback avoids
 * duplicated calls. The G0 ordinary incomplete sda UV owner plus its documented
 * SDATA view fixes absolute/GP address construction without shortened bounds.
 * Remaining null/class cleanup branches are annulled with count reloads in
 * their slots instead of ordinary branches and the retail object-argument move.
 * gcse-unsplit-edges and its keep-block-order combination tie; disabling GCSE
 * worsens to584 bytes and is not retained. No volatile/raw aliases introduced.
 * Renderer reads one64-byte contiguous basis and0x90-byte packet; both are
 * declared at those complete extents. Init writes state tail32 and the loop
 * writes vertices64, colors16, UV32 before any render call. GP owners remain
 * incomplete: template read64, color read8, UV read32 and scale read4 bytes.
 * Cleanup helper is canonical void(entity,index); list producer caps30 slots
 * and direct state reads include count at+0x3bc. No synthetic initialization.
 * Reopen with a measured cleanup-edge scheduling witness; no strict credit.
 */
#include "common.h"
typedef int BeamQuad __attribute__((mode(TI)));
struct BeamDrawPacket { float vertex[4][4]; unsigned int color[4]; float uv[4][2]; long state[4]; };
extern void func_L03_003F6918(unsigned char *, int);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern BeamQuad D_L03_001B10A0[] SDATA(D_L03_001B10A0);
extern unsigned int D_L03_001B1100[] SDATA(D_L03_001B1100);
struct BeamUV { float u, v; };
extern struct BeamUV D_L03_001B10E0[] __attribute__((sda));
/* Retail deliberately uses both GP and absolute address views of this same
 * unknown-size UV owner. Both views read its complete 32-byte used span. */
extern struct BeamUV D_L03_001B10E0_gp[] SDATA(D_L03_001B10E0);
extern float D_L03_001B1064[] SDATA(D_L03_001B1064);
extern float D_L03_001B9980[];
/* The renderer reads a complete 64-byte basis and 0x90-byte draw packet.
 * The packet initializer writes the 0x20-byte state tail; this routine fills
 * all 64 vertex,16 color and32 UV bytes before rendering. No smaller packet
 * or separate 16-byte pseudo-matrix is substituted for those read extents. */
void func_L03_003F6948(unsigned char *object)
{
    float basis[4][4];
    struct BeamDrawPacket packet;
    unsigned char *data = *(unsigned char **)(object + 0x68);
    int i;
    float scale;
    for (i = 0; i < *(int *)(data + 0x3bc); i++) {
        unsigned char *child = *(unsigned char **)(data + 0x340 + i * 4);
        if (child) {
        if (*(short *)(child + 0xaa) == 0xa72) {
            unsigned char state = child[0x20];
            if (state == 0xfe) goto remove_child;
            if (state != 0xfd) goto next_child;
remove_child:
            func_L03_003F6918(object, i);
        }
        }
next_child: ;
    }
    if (!*(int *)(data + 0x3bc)) return;
    func_00281DE8(&packet, 5, 1, 128);
    {
        int vertex;
    for (vertex = 0; vertex < 4; vertex++) {
        qcopy(packet.vertex[vertex], D_L03_001B10A0 + vertex);
        packet.color[vertex] = D_L03_001B1100[vertex >> 1];
        packet.uv[vertex][0] = D_L03_001B10E0_gp[vertex].u;
        packet.uv[vertex][1] = D_L03_001B10E0[vertex].v;
    }
    }
    scale = D_L03_001B1064[0] * 0.016666668f;
    {
        int beam;
    for (beam = 0; beam < *(int *)(data + 0x3bc); beam++) {
        unsigned char *child = *(unsigned char **)(data + 0x340 + beam * 4);
        unsigned char *segment = *(unsigned char **)(child + 0x68);
        qcopy(basis[3], child + 0x10);
        basis[3][3] = 1.0f;
        func_00282CF0(basis[0], D_L03_001B9980, basis[3]);
        func_00282F20(basis[1], segment, (float)*(short *)(segment + 0x12) * scale);
        func_00282DD8(basis[2], basis[1], basis[0]);
        func_00282F20(basis[2], basis[2], 1.0f);
        func_00282DD8(basis[0], basis[1], basis[2]);
        func_00280B90(&packet, basis, 0);
    }
    }
}
