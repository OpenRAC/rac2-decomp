/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections.
 * Compiled 508 bytes; retail 508 bytes.
 * Carrying checks: 0/28 in us, pal and us2. No strict linked qualification.
 * Right size, but register priorities, named hardware-register address forms, hardware-load order and division/store scheduling differ. Both physical hardware reads are represented without invented volatile. Reopen with a permitted hardware-address view and a real access-order explanation.
 */
extern int func_0011AC60(int);
extern int func_0011AC40(int);
extern void func_0034F780(int);
extern void func_00350808(unsigned int);
extern int func_00350750(unsigned char *, int);
extern void func_00350878(unsigned long *, unsigned long, unsigned long, unsigned long);
extern unsigned int D_1000B400;
extern int D_1000B410;
extern unsigned char ref_L00_00350BC8_00[];

int func_00350BC8(int *stream)
{
    int submitted = 0;
    unsigned int status;
    int slot, sectors, i;
    int used, offset;
    func_0011AC60(stream[0x10]);
    if (!stream[0x11]) {
        func_0034F780((int)ref_L00_00350BC8_00);
        return 0;
    }
    func_00350808(5);
    status = D_1000B400;
    used = func_00350750((unsigned char *)stream, D_1000B410);
    offset = (used + stream[2] - stream[3]) % stream[2];
    stream[4] -= offset;
    stream[3] = (stream[3] + offset) % stream[2];
    slot = (stream[3] + stream[4]) % stream[2];
    sectors = stream[5] / 2048;
    stream[5] -= sectors * 2048;
    if (sectors > 0) {
        int end = (stream[3] + stream[4] + stream[2] - 1) % stream[2];
        submitted = 1;
        func_00350878((unsigned long *)(stream[1] + (end << 4)),
                       stream[0] + (end << 11), 3, 0x80);
        for (i = 0; i < sectors; i++) {
            func_00350878((unsigned long *)(stream[1] + (slot << 4)),
                           stream[0] + (slot << 11), i == sectors - 1 ? 0 : 3, 0x80);
            slot = (slot + 1) % stream[2];
        }
    }
    stream[4] += sectors;
    if (stream[4] != 0) {
        if (submitted)
            status = (status & 0x0FFFFFFF) | 0x30000000;
        func_00350808(status | 0x100);
    }
    func_0011AC40(stream[0x10]);
    return 1;
}
