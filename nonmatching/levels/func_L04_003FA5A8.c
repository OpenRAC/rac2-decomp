/* func_L04_003FA5A8 - 568 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Goes in L04_003C8380.c (default flags; TI copies via Q16_B0e5d8f83
   assignments give lq/sq). 552 B vs 568. Structure decoded fully (see
   draft.c). Left: stack layout - retail has v0@0x00, v10@0x10, v20@0x20,
   v30@0x30, v40@0x40, v50@0x50 and the by-address params x,y,z at 0x60/64/68;
   draft puts v50 at 0x10 and x,y,z at 0x20. Also 0.8333333f must be
   0x3F555556 and 0.34906584f 0x3EB2B8C4 (draft gives ...5555 / ...B8C2: use
   0.83333337f and 0.3490659f), s2/s3 swapped (a2 pointer in $s2 in retail, s3
   = &v10), obj-field store order near 0x50/0x54. Declaration-order
   permutation of the quads was being tried (did not finish).
   Note: closeness counts for handoffs written before the d.sh fix were from
   the old masked diff. */

extern void *func_0029EFD0(void *a0);
extern void func_002AF000(unsigned char *a0, float f12, float f13, float f14);
extern unsigned char *func_L04_0040EC80(unsigned char *a0, void *a1, void *a2, float *a3, float *t0, float *t1, float f12, float f13);
extern void func_00282CF0(void *a0, void *a1, void *a2);
extern void func_L04_003F9ED0(unsigned char *a0, unsigned char *a1, void *a2, void *a3, void *t0, void *t1, void *t2);

/* Spawns the 0xABD object for the parent a0 at the position a1 and sets up its record. */
unsigned char *func_L04_003FA5A8(unsigned char *a0, void *a1, unsigned char *a2, float x, float y, float z, float f15, float f16) {
    unsigned char *obj = func_0029EFD0((void *)0xABD);
    unsigned char *state;
    Q16_B0e5d8f83 v0;
    Q16_B0e5d8f83 v10;
    Q16_B0e5d8f83 v20;
    Q16_B0e5d8f83 v30;
    Q16_B0e5d8f83 v40;
    Q16_B0e5d8f83 v50;

    if (obj != 0) {
        obj[0x30] = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0xFF;
        obj[0x31] = 1;
        obj[0x20] = 0;
        *(float *)(obj + 0xF8) = f15;
        *(float *)(obj + 0xF4) = f16;
        state = *(unsigned char **)(obj + 0x68);
        *(float *)(obj + 0x2C) = *(float *)(*(unsigned char **)(obj + 0x24) + 0x24) * 3.0f;
        if (a2 == 0) {
            func_002AF000((unsigned char *)&v10, 0.33333334f, f15, f16);
            v50 = *(Q16_B0e5d8f83 *)a1;
            a2 = func_L04_0040EC80(obj, &v50, &v10, &x, &y, &z, 0.34906584f, 30.0f);
        }
        *(unsigned char **)(state + 0x20) = a0;
        *(Q16_B0e5d8f83 *)(obj + 0x10) = *(Q16_B0e5d8f83 *)a1;
        *(int *)(state + 0x50) = -1;
        *(int *)(state + 0x48) = 1;
        *(float *)(state + 0x44) = 0.8333333f;
        *(int *)(state + 0x34) = 0;
        *(int *)(state + 0x38) = 0;
        *(int *)(state + 0x30) = 0;
        *(int *)(state + 0x54) = -1;
        *(unsigned char **)(state + 0x28) = a2;
        *(float *)(state + 0x3C) = x;
        *(int *)(state + 0x24) = 300;
        *(float *)(state + 0x40) = y;
        if (a2 != 0) {
            *(Q16_B0e5d8f83 *)state = *(Q16_B0e5d8f83 *)(a2 + 0x10);
            *(float *)(state + 8) = *(float *)(state + 8) + z;
            *(float *)(state + 0x2C) = z;
        }
        *(short *)(state + 0x4C) = (a0 != 0 && *(short *)(a0 + 0xAA) == 0xBBC) ? 0x3C : 1;
        *(short *)(state + 0x4E) = *(short *)(state + 0x4C);
        v0 = *(Q16_B0e5d8f83 *)(a0 + 0x10);
        ((float *)&v0)[2] = ((float *)a1)[2];
        func_00282CF0(&v10, a1, &v0);
        if (a2 != 0 && *(short *)(a2 + 0xAA) != 0xBBC)
            func_L04_003F9ED0(obj, state, &v0, &v10, &v40, &v20, &v30);
        func_002A0F48(obj);
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) + *(float *)(obj + 0x2C);
    }
    return obj;
}
