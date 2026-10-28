/* func_L11_00441FB8 - 436 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Best draft ~412-420 bytes vs 436. Structure right. Differences are in the
   `mode == 0` block:
   retail loads a1 (`lw $a1,0x160($s2)`) in the delay slots of a `bnel` and of
   the `b` that join before one `jal func_332CE8`, then `nop` in the call
   slot;
   mine uses `bne` with `addiu $a0` in the slot and puts a1 elsewhere.
   Retail's vector copy is `addiu $v1,$s1,0x10; lq $v0,0($v1); sq $v0,0($sp)`
   (mine qcopy uses $a0 as address reg).
   Also (hit = z < base[2] + (e == D_0018C0B0 ? 0.5f : 3.0f)) with no `? 1 :
   0` matches the tail. */

/* replaces the INCLUDE_ASM marker in src/levels/11_joba/L11_0043E1A0.c (default -G0 flags); needs the externs below (drop the TI128 typedef) */
extern int func_L00_003206B8(void *, int);
extern u8 *func_L11_004417E8(u8 *object);
extern u8 *D_0018C0B0;

/* Tells whether the entity lies in the object's reach: a point test, then height bands by mode. */
s32 func_L11_00441FB8(u8 *object, u8 *e, s32 mode)
{
    u8 *state = *(u8 **)(object + 0x68);
    s32 hit;
    f32 pos[4];
    void *point;
    f32 *base;
    JobaPolygonHeaderView *header;

    hit = func_L00_003206B8(e + 0x10, *(s32 *)(state + 0x1E4)) == 0;
    if (*(s16 *)(e + 0xAA) != 0 && (*(u16 *)(e + 0x34) & 2))
        return 0;
    if (hit)
        return hit;
    if (mode == 0) {
        point = e + 0x10;
        if (*(s16 *)(e + 0xAA) == 0xD4B) {
            qcopy(pos, e + 0x10);
            pos[2] -= 0.8f;
            point = pos;
        }
        hit = (s16)func_L00_003206B8(point, *(s32 *)(state + 0x160));
    }
    if (hit)
        return hit;
    if (*(s16 *)(state + 0x1FA) == 3) {
        hit = *(f32 *)(e + 0x18) < ((f32 *)func_L11_004417E8(object))[2] + (e == D_0018C0B0 ? 0.5f : 3.0f);
    }
    if (hit)
        return hit;
    if (*(s16 *)(state + 0x1FA) == 2 || *(s16 *)(state + 0x1FA) == 4) {
        header = D_L11_001FF580[*(s32 *)(state + 0x1C8)];
        base = (f32 *)func_L11_004417E8(object);
        if (*(f32 *)(e + 0x18) < base[2] + 0.5f)
            hit = func_002A8AF0((f32 *)(e + 0x10), (f32 *)(header + 1), header->field00) == 0;
    }
    return hit;
}
