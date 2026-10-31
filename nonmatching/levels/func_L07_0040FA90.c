/* Historical source only: this draft has a false third matrix-copy argument
 * and split 48+16-byte storage. Use func_L07_0040FA90-matrix.c for the corrected
 * two-pointer call and complete 64-byte matrix. Neither version is a match. */
/* func_L07_0040FA90 - 444 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Right size (444). 19 masked diff lines, all register allocation: retail
   state=s4, cur(sp+0x40)=s5, index=s6, hi(0x2A)=s7,
   src=s1, wp=s2; mine state=s5, cur=s4, index=s7, hi=s6, src=s2, wp=s1; plus
   last addu operand order (v1,v1,v0 vs v0,v0,v1).
   Tried: declaration order permutations (no effect), statement order of the 3
   inits and 3 increments (no effect), using rec as the loop pointer
   (18 lines but s0/s1 clash). MACRO_ADDR on D_L07_001B1F40 and *out=0 before
   the call were needed to get the structure. */

/* goes in L07_003F4578-g8.c (-G8, qcopy from common.h; D_L07_001B1F40 must be MACRO_ADDR, which is fine for func_L07_0040F468 too) */
extern u8 D_L07_002A0100[];
extern u8 *D_L07_001B1F40 MACRO_ADDR;
extern s32 *D_L07_001FDEC0[];
extern void func_2E4DD8(f32 *out, u8 *a, u8 *b);
extern void func_2E47F8(u8 *a, u8 *b, f32 *c);

#define REC(i) (D_L07_002A0100 + (i) * 0x120)
#define W(p) (*(f32 *)((p) + 0xC))

void func_L07_0040FA90(u8 *a0, s32 index)
{
    f32 base[12];
    f32 pos[4];
    f32 cur[4];
    u8 *state = *(u8 **)(a0 + 0x68);
    s32 *out;
    u8 *src;
    u8 *rec;
    u8 *dst;
    u8 *wp;
    u8 *entry;
    f32 w;

    if (*(s32 *)(state + 0xBC) == -1)
        return;
    entry = D_L07_001B1F40 + *(s32 *)(state + 0xBC) * 0x30;
    out = D_L07_001FDEC0[**(s32 **)(entry + 0x3C)];
    *out = 0;
    func_2E4DD8(base, a0 + 0xC0, entry);
    qcopy(pos, a0 + 0x10);
    pos[3] = 1.0f;
    rec = REC(index);
    if (W(rec) == 1.0f) {
        src = rec;
        wp = REC(index) + 0xC;
        dst = (u8 *)out + 0x10;
        do {
            func_2E47F8(dst, src, base);
            dst += 0x10;
            wp += 0x10;
            src += 0x10;
            (*out)++;
        } while (*(f32 *)wp == 1.0f);
    }
    qcopy(cur, REC(index) + *out * 0x10);
    w = cur[3];
    cur[3] = 1.0f;
    func_2E47F8(D_L07_001B1F40 + (*(s32 *)(state + 0xBC) * 0x30 + 0x20), (u8 *)cur, base);
    ((f32 *)(D_L07_001B1F40 + *(s32 *)(state + 0xBC) * 0x30))[11] = w;
}
