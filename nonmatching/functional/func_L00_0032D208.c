/* functional: high. Same reads, writes and calls as retail, in the same order (read in full against level 00's code, including the unrun handle-close call and stream-open block); register use differs. func_00132818 is the catalogue's name for the entry at 0x132828 that retail calls. */
/* func_L00_0032D208 (260 bytes): closes the three stream handles at D_00188660+0x17A4, waits for the IOP, then opens stream `index` of the table at D_0014B540+0x52E0 (relative to +0x529C) into handle index+1 (-1 while opening) and resumes. */
/* GPT-6.1 Sol low tier, v0439, current pinned compiler, default -O2 -G0.
 * check.py: 252 bytes versus 260 retail, 0 of 27 places match (USA v1.01).
 * Unsigned handle stores recover retail's lui/ori 0xffffffff constant;
 * AddressBank fields recover the 0x52e0 and 0x529c load offsets.
 * Polling-loop padding matches. Remaining: resident high-half lifetime,
 * entry saves/address copies, shifted-index register and handle arithmetic.
 * Direct global addressing plus unsigned(index+1) prevents index folding but
 * loses s3 and its save, yielding 248 bytes; a local base restores 252 bytes.
 * Resident callee boundary is fixed upstream: canonical func_00132818
 * resolves to the actual entry 0x00132828. No linking validation or PAL/US2
 * checks performed. All declarations required by the draft follow.
 */
extern unsigned char D_00188660[];
typedef struct { char pad[0x529c]; int base; char gap[0x40]; int entries[3][2]; } AddressBank;
extern AddressBank D_0014B540;
extern void func_00132858(int handle);
extern void func_00133230(void);
extern int func_00132028(void);
extern int func_00132818(void);
extern unsigned int func_00132318(int address, int mode);
void func_L00_0032D208(int index)
{
    unsigned char *base = D_00188660;
    unsigned int *handle = (unsigned int *)(base + 0x17a4);
    int i = 2;
    int address;
    do {
        i--;
        if (*handle != 0) {
            func_00132858(*handle);
            *handle = 0;
        }
        handle++;
    } while (i >= 0);
    func_00133230();
    while (func_00132028() != 0) { }
    func_00132818();
    while (func_00132028() != 0) { }
    address = D_0014B540.entries[index][0];
    if (address != 0) {
        address += D_0014B540.base;
        handle = (unsigned int *)(base + 0x17a0) + (unsigned int)(index + 1);
        *handle = -1;
        *handle = func_00132318(address, 0);
    }
    func_00132818();
}
