/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy.
 * Compiled 552 bytes; retail 556 bytes.
 * Carrying checks: 0/5 in us, pal and us2. No strict linked qualification.
 * Moving the real world-pointer lifetime after the first call recovers the prologue. A measured partial camera view preserves field offsets and two real quadword copies. Packet constants/register priorities, copy/store scheduling and pointer publication still differ. Reopen with allocator evidence; C TI copies and reviewed qcopy helpers both stayed at 552 bytes.
 */
#include "common.h"
extern char *ref_L04_003A0FC8_00[] MACRO_ADDR;
extern int D_L04_001B201C[] MACRO_ADDR;
extern char D_L04_001B9580[];
typedef int PacketQuad __attribute__((mode(TI)));
typedef struct {
    char prefix[0x190];
    PacketQuad first, second;
    char gap1B0[0x60];
    float value210;
    char gap214[0x14];
    float value228, value22C;
} PacketCameraView;
extern char D_L04_001BDB80[];
extern char D_L04_002A78A0[];
extern unsigned short D_0010ED20[];
extern char D_0010ED30[];
extern int D_L04_001AD890 __attribute__((sda));
extern int D_L04_001AD884 __attribute__((sda));
extern int D_L04_001AD888 __attribute__((sda));
extern int D_L04_001AD88C __attribute__((sda));
extern void func_002833B8(void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002FC410(void *, int);
extern void func_00283788(void *, void *, void *);
extern void func_002FC870(void);

void func_L04_003A0FC8(void)
{
    float matrix[16] __attribute__((aligned(16)));
    char *world;
    PacketCameraView *camera;
    char *packet;
    char *end;
    char *start;
    func_002833B8(matrix, 1024.0f);
    world = D_L04_001B9580 + 0x100;
    func_00282D30(matrix + 12, world, -1024.0f);
    matrix[15] = 1.0f;
    if (D_L04_001B201C[0] != 8) {
        func_002FC410(D_0010ED30, D_0010ED20[0]);
        D_L04_001B201C[0] = 8;
    }
    *(int *)(ref_L04_003A0FC8_00[0] + 0) = 0x10000000;
    *(int *)(ref_L04_003A0FC8_00[0] + 4) = 0;
    *(int *)(ref_L04_003A0FC8_00[0] + 8) = 0x11000000;
    *(int *)(ref_L04_003A0FC8_00[0] + 12) = 0x01000404;
    packet = ref_L04_003A0FC8_00[0];
    *(int *)(packet + 0x10) = 0;
    *(int *)(packet + 0x14) = 0;
    *(int *)(packet + 0x18) = 0;
    *(int *)(packet + 0x1C) = 0x6C0C43A4;
    func_00283788(packet + 0x20, world - 0x100, matrix);
    func_00283788(packet + 0x60, world - 0x80, matrix);
    camera = (PacketCameraView *)D_L04_001BDB80;
    *(int *)(packet + 0xA8) = 0x412;
    *(int *)(packet + 0xA0) = 0x8000;
    *(int *)(packet + 0xA4) = 0x303EC000;
    *(float *)(packet + 0xAC) = camera->value210;
    qcopy(packet + 0xB0, &camera->first);
    qcopy(packet + 0xC0, &camera->second);
    *(float *)(packet + 0xD0) = camera->value22C;
    *(float *)(packet + 0xD4) = camera->value228;
    *(int *)(packet + 0xE4) = 0x020001D2;
    *(int *)(packet + 0xE8) = 0x15000000;
    *(int *)(packet + 0xE0) = 0x03000000;
    *(int *)(packet + 0xD8) = 0;
    *(int *)(packet + 0xDC) = 0;
    *(int *)(packet + 0xEC) = 0;
    end = packet + 0xF0;
    start = ref_L04_003A0FC8_00[0];
    *(unsigned int *)start |= ((end - start) >> 4) - 1;
    ref_L04_003A0FC8_00[0] = end;
    func_002FC870();
    *(unsigned int *)(ref_L04_003A0FC8_00[0] + 0) = 0x30000007;
    *(char **)(ref_L04_003A0FC8_00[0] + 4) = D_L04_002A78A0;
    *(int *)(ref_L04_003A0FC8_00[0] + 8) = 0;
    *(int *)(ref_L04_003A0FC8_00[0] + 12) = 0x50000007;
    D_L04_001AD890 = -1;
    D_L04_001AD884 = -1;
    D_L04_001AD888 = -1;
    ref_L04_003A0FC8_00[0] += 0x10;
    D_L04_001AD88C = -1;
}
