#include "common.h"

/* State of the object preview (see 002FC8D0.c). */
typedef struct {
    short s00;
    short frames;
    float rate;
    char pad08[0x34 - 0x08];
    unsigned char phase;
    unsigned char spin;
} PreviewState;

extern PreviewState D_001B2310 __attribute__((sda));
extern short D_001A6480[];
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_002FC560(int, long long);
extern void func_0027DE50(int, int, int, int, u64);

void func_002FFCF8(void)
{
    int v;
    func_002FC560(0x42, 0x44);
    v = func_00283CF0((1.0f - func_00283CE0(D_001B2310.frames) * D_001B2310.rate) * 255.0f);
    func_0027DE50(0, D_001A6480[0xA9], 0, D_001A6480[0xA8], (u64)(v << 24));
}
