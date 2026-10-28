/* func_L12_00389988 - 568 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Needs unit flags -O2 -G8 -ffunction-sections -Wa,-G64 (arrays must be
   declared <= the assembler -G for the gp addiu; sizes in the draft are
   guesses [1][4][3], [4][4], [4][2]). Packet struct is 0x90 bytes (frame
   0xE0). Block 2 uses pointer vars ux/uy (s7/fp, kept from the prologue),
   block 1 does not. 560 vs 568 B. Remaining: retail table base regs s4=lui
   view of the stride-8 float array +4, s5=gp view, s6=Q; mine allocates them
   in another order and keeps t-copies of the uv pointers. */

#include "include_asm.h"

typedef int Quadword __attribute__((mode(TI)));

typedef struct {
    float v[4][4];
    int color[4];
    float uv[4][2];
    float tail[8];
} QuadPacket;

extern short D_L12_001AEE80[1][4][3] __attribute__((sda));
extern short D_L12_001AEE82[1][4][3];
extern float D_L12_001AEE40[4][4] __attribute__((sda));
extern float D_L12_001AEE98[4][2] __attribute__((sda));
extern float D_L12_001AEE9C[4][2];
extern int D_L12_001AEF48 __attribute__((sda));
extern int D_L12_001AEE34 __attribute__((sda));
extern int D_L12_001AEE38 __attribute__((sda));

extern void func_00281DE8(void *, int, int, int);
extern void func_00280B90(void *, int, int);

/* Draws the two textured quad groups of the object's marker. */
void func_L12_00389988(char *object) {
    char *state = *(char **)(object + 0x68);
    QuadPacket pkt;
    float *uy = &pkt.uv[0][1];
    float *ux = &pkt.uv[0][0];
    int face;
    int k;

    func_00281DE8(&pkt, D_L12_001AEF48, 2, 0x80);
    pkt.color[0] = D_L12_001AEE34;
    pkt.color[3] = D_L12_001AEE34;
    pkt.color[2] = D_L12_001AEE34;
    pkt.color[1] = D_L12_001AEE34;
    for (face = 0; face < 1; face++) {
        for (k = 0; k < 4; k++) {
            *(Quadword *)pkt.v[k] = *(Quadword *)D_L12_001AEE40[D_L12_001AEE80[face][k][0]];
            pkt.uv[k][0] = D_L12_001AEE98[D_L12_001AEE82[face][k][0]][0] + *(float *)(state + 0x10);
            pkt.uv[k][1] = D_L12_001AEE9C[D_L12_001AEE82[face][k][0]][0];
        }
        func_00280B90(&pkt, 0, 0);
    }
    func_00281DE8(&pkt, D_L12_001AEF48 + 1, 0, 0x80);
    pkt.color[0] = D_L12_001AEE38;
    pkt.color[3] = D_L12_001AEE38;
    pkt.color[2] = D_L12_001AEE38;
    pkt.color[1] = D_L12_001AEE38;
    for (face = 0; face < 1; face++) {
        for (k = 0; k < 4; k++) {
            *(Quadword *)pkt.v[k] = *(Quadword *)D_L12_001AEE40[D_L12_001AEE80[face][k][0]];
            ux[k * 2] = D_L12_001AEE98[D_L12_001AEE82[face][k][0]][0] + *(float *)(state + 0x10);
            uy[k * 2] = D_L12_001AEE9C[D_L12_001AEE82[face][k][0]][0];
        }
        func_00280B90(&pkt, 0, 0);
    }
}
