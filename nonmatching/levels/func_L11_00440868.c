/* func_L11_00440868 (264 bytes, 1 place) -- NEAR MISS, not integrated.
   state: 272 bytes, 59 of 66 words differ from retail; the loop body and the two
   class handlers are right, the head and the block order are not.

   check.py (11_joba), with the source below, compiled in src/levels/11_joba/L11_0043E1A0.c
   (-O2 -G0 -ffunction-sections):
     0044089C  beql  $v0, $zero, +0x2F   |  bnez  $v1, +0x11
     004408A0  daddu $v0, $zero, $zero   |  daddu $a2, $v1, $zero
   What is measured and right:
   - the level's class table base D_L11_001B359C is read inside the loop, absolutely
     (`lui $v1,0x1B ; lw $v1,0x359C($v1)`), so the unit is -G0: with -G8 the load would
     be a $gp access;
   - the record pointer stays in $s0 and the state in $s1 across the two calls, and the
     handlers take the record: func_L11_003F2F38(record) and func_L11_00439950(record);
   - the two class ids are 0xB3A (counts state+0x11C) and 0xD4A (counts state+0x118);
     the record's 0xB8 word takes the object before both;
   - the class list is walked with the retail's sign test on the u16 entry: the list
     ends at the first entry with the high bit set.
   Tried and not enough:
   - the guard as `q = table[index]; if (q) { p = q; ... }` (the two-names shape that
     matches func_L08_00328BB0): it inverts the index guard and moves both handler
     blocks out of the loop;
   - one name for the list and one for the cursor (the shape that matches
     func_L11_00440238): the head still comes out with the guard inverted, the table
     address hoisted out of the loop and the two handler blocks moved before the loop.
   28 October 2026 (DrLegitamate): the table load is solved. Declared as the
   incomplete-array alias `extern u8 *D_L11_001B359C_base[] __asm__("D_L11_001B359C")
   __attribute__((sda));` and read as `D_L11_001B359C_base[0]`, it stays inside the loop
   as retail's `lui $v1,%hi ; lw $v1,%lo($v1)` (the same declaration matched the sibling
   func_L11_004411C8). With it the body is 268 bytes against 264 and the handler blocks
   still come out before the loop with the list guard inverted. Not changed by: early
   `continue` instead of the nested test, `else if` for the second handler, a `for (;;)`
   loop with the sign test and `break` at the bottom, nor by -frac2-keep-block-order or
   -frac2-gcse-unsplit-edges (alone or together, in a sibling unit).
   Next idea: a shape that keeps the guard's sense (retail branches on the null list)
   and keeps the handler blocks inside the loop body, which is where retail has them. */

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

extern u8 *D_L11_001FC420[];
extern u8 *D_L11_001B359C;

extern void func_L11_003F2F38(u8 *);

extern void func_L11_00439950(u8 *);

/* Finds the class record the identifier names: the first live record of the state's
   class list whose identifier matches, and hands it to the class's handler. */
u8 *func_L11_00440868(u8 *obj, s32 id) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 index = *(s32 *)(state + 0xC0);
    u16 *cursor;
    u8 *record;
    u8 *list;

    if (index == 0xFF) {
        return 0;
    }
    list = D_L11_001FC420[index];
    if (list == 0) {
        return 0;
    }
    cursor = (u16 *)list;
    do {
        u16 value = *cursor;
        record = D_L11_001B359C + ((value & 0x7FFF) << 8);

        if (record != 0 && record[0x20] != 0xFE && record[0x20] != 0xFD &&
            *(s16 *)(record + 0xAA) == id && record[0x20] == 1) {
            *(u32 *)(record + 0xB8) = (u32)obj;
            if (id == 0xB3A) {
                func_L11_003F2F38(record);
                *(s32 *)(state + 0x11C) += 1;
                return record;
            }
            if (id == 0xD4A) {
                func_L11_00439950(record);
                *(s32 *)(state + 0x118) += 1;
                return record;
            }
        }
    } while (*(s16 *)cursor++ >= 0);
    return 0;
}
