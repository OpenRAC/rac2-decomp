/* functional: high. Same reads, writes and calls as retail; only instruction order of two loads differs. */
/* func_002FC280 - retained near miss, USA v1.01.
 *
 * Profile: -O2 -G8 -ffunction-sections (the two viewport scratch words are read and
 * written through $gp, so the body needs the -G8 sibling).
 * Last verdict: 28 places, 316/316 bytes, `boot: instruction at +0x40 differs`.
 * Everything from the packet body to the epilogue is exact, including the fail path's
 * `sw $0,-0x1AD0($gp); jal; nop`, the annulled `bnel` store and the four separate
 * packet-pointer reloads.
 *
 * Remaining difference: in the prologue the D_001B22A8 reload (two instructions,
 * `lui;lw`) and the `D_001B22A0[index]` load are in the opposite order. Retail:
 *   lw $a1,0($v1)          (table entry)
 *   lui $a2,%hi(D_001B22A8); lw $a2,%lo($a2)
 * this draft:
 *   lui $a2,...; lw $a2,...  then lw $a1,0($v1)
 * Tried: the subtraction written first, a `base` local read before the pointer, a
 * `flags` local for the read-modify-write, and `used = table; used = ptr - used`.
 * All keep the volatile pointer load first. Reopen with a source form that makes the
 * table load schedule ahead of the volatile small-data load.
 *
 * Notes for requalification:
 *  - D_001B22A8 must be `unsigned char * volatile` for the four packet stores to reload
 *    it (retail reloads every time); the non-volatile form keeps one copy in $a3.
 *  - D_001AD520 must be volatile for the fail path's store to land before the call
 *    instead of in its delay slot.
 *  - D_001B22B4 is read absolutely at entry and through $gp later, hence the measured
 *    second name D_001B22B4.
 */
extern volatile int D_001AD520 __attribute__((sda));
extern int D_001B22B8 __attribute__((sda));
extern int D_001B22B4;
extern int D_001B22B0;
extern int D_001B22A0[];
extern unsigned char * volatile D_001B22A8;
extern int func_00126F38(int);
extern void func_0011AEA0(int);
extern void func_00127220(void *, int);
extern void func_002FC3C0(int);
extern void func_002FC220(void);
extern void func_002F0FA0(void);

/* Waits for the display-list buffer to free up and opens the next packet. */
void func_002FC280(void)
{
    int flags;
    int used;
    int ready = 0;
    char *packet;

    flags = D_001AD520 | 0x1F;
    used = D_001B22A0[D_001B22B4];
    used = (int)D_001B22A8 - used;
    D_001AD520 = flags;
    if (used > D_001B22B0) {
        if (used < D_001B22B8)
            D_001B22B8 = used;
        ready = 1;
    }
    if (!ready || D_001B22B4 == 0) {
        *(int *)(D_001B22A8 + 0) = 0x70000000;
        *(int *)(D_001B22A8 + 4) = 0;
        *(int *)(D_001B22A8 + 8) = 0;
        *(int *)(D_001B22A8 + 12) = 0;
        packet = (char *)func_00126F38(1);
        *(int *)packet |= 0xC0;
        func_0011AEA0(0);
        func_00127220(packet, D_001B22A0[D_001B22B4]);
        if (ready) {
            func_002FC3C0(1);
            func_002FC220();
        }
    } else {
        D_001AD520 = 0;
        func_002F0FA0();
    }
}
