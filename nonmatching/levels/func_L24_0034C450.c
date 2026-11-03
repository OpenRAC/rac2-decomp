/* 2 November 2026 retail recheck; this supersedes conflicting historical notes below.
 * Fresh US corrects stale retained note:34C458 is addiu sp,sp,+0x20 (positive residue), not negative prologue. True coherent body starts34C460(+16), with loaded pointer286890->34C460. Prefix follows prior completed return and has no external static entry. Reopen on reviewed16-byte entry correction; old+8/280-byte body hypothesis is superseded.
 * No matching credit, generator change or ASM_FUNC classification.
 */
/* func_L24_0034C450 (288 bytes, 1 place) -- NEAR MISS, not integrated.
   state: the catalogue's extent is eight bytes too long: it starts at 0x34C450
   on a `sw $t3,0x40($v1)` that belongs to the code before this function (the
   previous function's `jr $ra` is at 0x34C444 and its delay slot at 0x34C448);
   this function's own prologue (addiu $sp,$sp,-0x20) starts at 0x34C458. The
   body here is the 280 bytes from 0x34C458, so no C can fill the first eight
   bytes of the catalogued extent. That is a fix in tools/levels.py, not in C.
   With the body alone this source gives 292 bytes against the retail's 280 (the
   frame is 0x10 here and 0x20 there, and the loop's records are addressed
   differently); the rest of the shape (the loop over the level order, the
   12-byte records it writes, the search for the current object) is what is
   measured here.

   What is measured and right:
   - the unit must be a -G8 sibling (src/levels/24_ship_shack/L24_0034C450-g8.c):
     the 0x1AA770 pointer is read with `lw $a0,-0x4880($gp)`.
   - the level order is g_anAvailableLevelOrder (0x139948), read as words; the
     loop walks it while the count is under 28 and the next word is not zero.
   - each record written is 12 bytes: the u16 at 0x28AE20 + n * 12, the u16 at
     0x28AE24 + n * 12, the constant 3, the address 0x2868E0 and the count.
   - the search compares the words of the 0x1AA770 array with the word at
     0x1C8ED0 (the base is D_L24_001C8CA0 + 0x230) and leaves the index in the
     object's field at +0x40.
   Tried and not enough: the record written through a struct of twelve bytes
   (the compiler then keeps the record's fields in registers); the level order
   read as a byte array; the search written as a for loop over the array. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u32 *D_00139948[];
extern u32 **D_001AA770 __attribute__((sda));
extern u8 D_L24_001C8CA0[];
extern u16 D_L24_0021C7F0[];
extern u16 D_L24_0028AE20[];
extern u16 D_L24_0028AE24[];
extern u32 D_L24_002868E0;

/* Fills the level's table of the objects in play and tells the object which
   entry of the level's list is its own. */
void func_L24_0034C450(u8 *a0) {
    u8 *obj = a0;
    u32 *order = D_00139948;
    u32 **arr = D_001AA770;
    u32 cur = *(u32 *)(D_L24_001C8CA0 + 0x230);
    s32 i = 0;
    s32 j;

    if (*order != 0) {
        do {
            u16 *e = D_L24_0021C7F0 + i * 6;
            u32 v = *order++;
            e[1] = 3;
            *(u32 *)(e + 2) = D_L24_002868E0;
            e[4] = D_L24_0028AE24[v * 6];
            e[0] = D_L24_0028AE20[v * 6];
            i++;
        } while (i < 28 && *order != 0);
    }
    D_L24_0021C7F0[i * 6] = 0;
    *(u32 *)(obj + 0x40) = 0;
    *(u16 *)(obj + 0x30) |= 0x8000;
    if (arr[0] != 0) {
        j = 0;
        while (arr[j] != 0) {
            if (arr[j] == cur) {
                *(u32 *)(obj + 0x40) = j;
                break;
            }
            j++;
        }
    }
}
