#include "include_asm.h"
#include "common.h"

extern void func_002B0A68(void *, int, void *, int, float, float, float, float);
extern void func_0029F338(void *);

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

/* Waits for a trigger and then keeps puffing out a small burst of effect particles until the object is removed. */
void func_L08_003D3E00(unsigned char *moby) {
    int state = moby[0x20];
    Quad puff;

    switch (state) {
    case 0:
        moby[0x20] = 1;
        break;
    case 1:
        if (moby[0xBC] != 0)
            moby[0x20] = 2;
        break;
    case 2:
        qzero(&puff);
        puff.f[2] = 0.15f;
        SpawnDebrisForMaskedParts(moby, 0x7F, &puff, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        MarkMobySpawned(moby);
        break;
    }
}
