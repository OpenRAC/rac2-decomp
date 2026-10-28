/* func_L01_003CBFF0 - 544 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   9 masked diff lines, all registers in the block at 0xB4: retail loads idx
   into $a0, base ($gp 0x356C, delay slot of beq) into $v1 (ent=$v1), E0 value
   in $v0;
   draft has idx $v1, base/ent $v0, E0 $a0. Tried local id (breaks the jump
   threading: beq target 0x29 instead of 0x2C), id*256, &base[id<<8],
   statement order of the 0xF0 copy (moves base load out of delay slot).
   Everything else (2088 as sda array tied form, constants, order) matches. */

/* in L01_003CAFE0.c; needs common.h include (its u8..f32 typedefs removed) and these decls: */
extern s32 func_00283CF0(f32 a0); extern void func_L01_003377C8(void *a0); extern void func_002A7398(void *a0, s32 a1, s32 a2); extern void func_002A7750(void *a0, s32 a1, s32 a2);
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda)); extern u8 *D_L01_001FE180[]; extern s32 D_L01_001B2088[] __attribute__((sda));
void func_L01_003CBFF0(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    u8 *ent;

    state[0x48] = func_00283CF0(5.0f);
    state[0x4A] = func_00283CF0(32.0f);
    state[0x29] = 1;
    *(f32 *)(a0 + 0x2C) = *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24) * 2.5f;
    qcopy(state + 0x80, a0 + 0x10);
    if (D_L01_001B2088[0] == 0 && a0[0x21] != 0xFF)
        **(s32 **)(state + 0xD8) = 0;
    *(f32 *)(state + 0x30) = 2.0f;
    state[0x2A] = 8;
    state[0x2E] = 3;
    state[0x28] = 3;
    *(s32 *)(state + 0xBC) = 0;
    if (*(s32 *)(state + 0xB8) != -1)
        func_L01_003377C8(D_L01_001FE180[*(s32 *)(state + 0xB8)]);
    *(s32 *)(state + 0xF0) = *(s32 *)(state + 0xE8);
    if (state[0xDD] != 0)
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) | 0x8000;
    if (*(s32 *)(state + 0xB4) != -1) {
        ent = D_L01_001B255C_base[0] + (*(s32 *)(state + 0xB4) << 8);
        *(s32 *)(state + 0xF0) = *(s32 *)(state + 0xE0);
        if (ent != 0 && ent[0x20] != 0xFE && ent[0x20] != 0xFD) {
            *(u16 *)(a0 + 0x32) = 0x3FF;
            a0[0x30] = 0xFF;
            if (0.0f < *(f32 *)(state + 0xD0))
                *(f32 *)(a0 + 0x18) = *(f32 *)(state + 0xD0);
            if (*(s32 *)(state + 0xC8) != 0)
                func_002A7398(a0, 8, 0);
            else
                func_002A7398(a0, 5, 0);
            func_002A7750(a0, 0, 1);
        } else {
            *(s32 *)(state + 0xB4) = -1;
        }
    }
    if (*(s32 *)(state + 0xB4) == -1) {
        if (0.0f < *(f32 *)(state + 0xD4))
            *(f32 *)(a0 + 0x18) = *(f32 *)(state + 0xD4);
        *(s32 *)(state + 0xBC) = 0x78;
        func_002A7398(a0, 0, 0);
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) & 0xEFFF;
        *(f32 *)(a0 + 0x48) = 0.0f;
        func_002A7750(a0, 0, 4);
    }
}
