/* Nonmatching reconstruction. Profile: -O2 -G8 -ffunction-sections.
 * 488/488 bytes; 0/28 in US, US2 and PAL. Packet scheduling differs at +0x11C onward; the SDK upload setup also uses different relocatable temporary registers. Camera fields at +0,+0x80,+0x100 are measured distinct fields, not an inferred packed matrix. Reopen with the measured call scheduling/symbol model.
 * No complete strict linked validation or matching credit.
 */
#include "common.h"

typedef struct { f32 first[16]; u8 gap40[0x40]; f32 second[16]; u8 gapC0[0x40]; f32 position[4]; } Camera;
typedef struct { u8 before[0x190]; f32 light0[4], light1[4]; u8 gap[0x210 - 0x1B0]; f32 fog; u8 gap214[0x228 - 0x214]; f32 parameter, distance; } Lighting;
extern Camera D_001B5240;
extern Lighting D_001B9040;
extern s32 D_L00_001B169C[] __attribute__((sda));
extern u16 D_0010ED20;
extern u8 D_0010ED30[];
extern u8 *D_001B22A8[] __attribute__((sda));
extern f32 D_001A86F0 __attribute__((sda));
extern void func_002833B8(void *, f32);
extern void func_00282D30(void *, void *, f32);
extern void func_002FC410(u32, u32);
extern void func_00283788(void *, void *, void *);
extern void func_002FC870(void);

void func_00280328(void)
{
    f32 matrix[16] __attribute__((aligned(16)));
    u8 *packet, *cursor;
    func_002833B8(matrix, 1024.0f);
    func_00282D30(matrix + 12, D_001B5240.position, -1024.0f);
    matrix[15] = 1.0f;
    if (D_L00_001B169C[0] != 8) {
        func_002FC410((u32)D_0010ED30, D_0010ED20);
        D_L00_001B169C[0] = 8;
    }
    *(u32 *)(D_001B22A8[0] + 0) = 0x10000000;
    *(u32 *)(D_001B22A8[0] + 4) = 0;
    *(u32 *)(D_001B22A8[0] + 8) = 0x11000000;
    *(u32 *)(D_001B22A8[0] + 0xC) = 0x01000404;
    packet = D_001B22A8[0];
    *(u32 *)(packet + 0x10) = 0;
    *(u32 *)(packet + 0x14) = 0;
    *(u32 *)(packet + 0x18) = 0;
    *(u32 *)(packet + 0x1C) = 0x6C0C43A4;
    cursor = packet + 0x20;
    func_00283788(cursor, D_001B5240.first, matrix);
    *(f32 *)(cursor + 0x38) += D_001A86F0;
    cursor = packet + 0x60;
    func_00283788(cursor, D_001B5240.second, matrix);
    *(f32 *)(cursor + 0x38) += D_001A86F0;
    *(u32 *)(packet + 0xA0) = 0x8000;
    *(u32 *)(packet + 0xA4) = 0x303EC000;
    *(u32 *)(packet + 0xA8) = 0x412;
    *(f32 *)(packet + 0xAC) = D_001B9040.fog;
    qcopy(packet + 0xB0, D_001B9040.light0);
    qcopy(packet + 0xC0, D_001B9040.light1);
    *(f32 *)(packet + 0xD0) = D_001B9040.distance;
    *(f32 *)(packet + 0xD4) = D_001B9040.parameter;
    *(u32 *)(packet + 0xE0) = 0x03000000;
    *(u32 *)(packet + 0xE4) = 0x020001D2;
    *(u32 *)(packet + 0xE8) = 0x15000000;
    *(u32 *)(packet + 0xD8) = 0;
    *(u32 *)(packet + 0xDC) = 0;
    *(u32 *)(packet + 0xEC) = 0;
    cursor = packet + 0xF0;
    *(u32 *)D_001B22A8[0] |= ((cursor - D_001B22A8[0]) >> 4) - 1;
    D_001B22A8[0] = cursor;
    func_002FC870();
}
