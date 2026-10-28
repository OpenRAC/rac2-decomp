/* func_L05_0042BB10 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/levels/shared/L05_0042BB10-g8.c: 464/464 bytes.
 * US: 0/4 local places; PAL: 0/4 local places; US2: 0/4 local places.
 * No strict linked build was run because no local placement matched.
 * Only two non-relocation words differ in the displayed comparison: +0x108 retail daddu s5,s0,zero versus C s2,s0,zero, and +0x120 retail daddu s2,s5,zero versus C s5,s2,zero. Earlier packet lifetime worsened allocation. Reopen with genuine packet/destination lifetime evidence; later symbol bindings remain unqualified until the first mismatch closes.
 */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
/* Layout shared with the current QuadPacket declaration in 0027F128.c. */
typedef struct { unsigned char prefix[0x70]; long clear, font, texture, flags; } QuadPacket;
typedef struct { Vector position, scaled; QuadPacket packet; Vector up, basis[4]; } QuadScratch;
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00281DE8(QuadPacket *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(QuadPacket *, void *, int);
extern int D_L05_001B172C __attribute__((sda));
extern float D_L05_001B1730 __attribute__((sda));
extern float D_L05_001B1734 __attribute__((sda));
extern Vector D_L05_001B96C0;
extern Vector D_L05_001AA240[];

void func_L05_0042BB10(char *object)
{
    QuadScratch scratch;
    Vector *source;
    Vector *destination;
    int i;
    func_002FC560(0x47, 0x53001ULL);
    scratch.position.f[0] = *(float *)(object + 0x10);
    scratch.position.f[1] = *(float *)(object + 0x14);
    scratch.position.f[2] = *(float *)(object + 0x18);
    scratch.position.f[3] = 1.0f;
    func_00282D30(&scratch.scaled, object + 0xC0, D_L05_001B1734);
    func_00282CC0(&scratch.position, &scratch.position, &scratch.scaled);
    func_00281DE8(&scratch.packet, D_L05_001B172C, 2, 128);
    scratch.up.q = 0;
    *(unsigned int *)(scratch.packet.prefix + 0x4C) = 0x80808080u;
    *(unsigned int *)(scratch.packet.prefix + 0x48) = 0x80808080u;
    *(unsigned int *)(scratch.packet.prefix + 0x44) = 0x80808080u;
    *(unsigned int *)(scratch.packet.prefix + 0x40) = 0x80808080u;
    *(float *)(scratch.packet.prefix + 0x5C) = 5.0f;
    *(float *)(scratch.packet.prefix + 0x60) = 5.0f;
    *(float *)(scratch.packet.prefix + 0x68) = 5.0f;
    *(float *)(scratch.packet.prefix + 0x6C) = 5.0f;
    *(float *)(scratch.packet.prefix + 0x50) = 0.0f;
    *(float *)(scratch.packet.prefix + 0x54) = 0.0f;
    *(float *)(scratch.packet.prefix + 0x58) = 0.0f;
    *(float *)(scratch.packet.prefix + 0x64) = 0.0f;
    scratch.up.f[2] = 1.0f;
    scratch.up.f[3] = 1.0f;
    qcopy(&scratch.basis[3], &scratch.position);
    func_00282CF0(&scratch.basis[0], &D_L05_001B96C0, &scratch.basis[3]);
    func_00282F20(&scratch.basis[0], &scratch.basis[0], 1.0f);
    func_00282DD8(&scratch.basis[1], &scratch.basis[0], &scratch.up);
    func_00282F20(&scratch.basis[1], &scratch.basis[1], 1.0f);
    func_00282DD8(&scratch.basis[2], &scratch.basis[1], &scratch.basis[0]);
    source = D_L05_001AA240;
    destination = (Vector *)scratch.packet.prefix;
    for (i = 3; i >= 0; i--) {
        func_00282D30(destination, source, D_L05_001B1730);
        source++;
        func_002830C0(destination, destination, scratch.basis);
        destination++;
    }
    func_00280B90(&scratch.packet, 0, 0);
}