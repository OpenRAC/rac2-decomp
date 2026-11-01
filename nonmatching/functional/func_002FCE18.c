/* functional: medium. Carried from Ratchet & Clank (func_00235118, vif1_dma_interrupt_handler); rac2's instructions were compared word by word with rac1's and are the same, with the flag word at D_001AD520. VIF1 interrupt handler: reads VIF1_STAT (0x10009000); when VIF1_ERR-side word 0x10009030 is nonzero and the stall/interrupt bits (STAT & 0xC) are set, it clears bits of D_001AD520: all five low bits when STAT bits 28-30 are all set (then returns without acknowledging), otherwise bit 1, 2, 3 or 4 for the VIF interrupt codes 0x201, 0x202, 0x204 and 0x208 in STAT bits 16-25; then it writes STAT | 0x100 back to 0x10009000 to resume. Returns 0. Retail ends with sync and ei (it runs as an interrupt handler); the port drops both. */
extern unsigned int D_001AD520 __attribute__((sda));

int func_002FCE18(void) {
    unsigned int stat = *(volatile unsigned int *)0x10009000;
    unsigned int code = stat & 0x3FF0000;
    if (*(volatile unsigned int *)0x10009030 == 0 || (stat & 0xC) == 0) {
        return 0;
    }
    if ((stat & 0x70000000) == 0x70000000) {
        D_001AD520 &= ~0x1Fu;
        return 0;
    }
    if (code & 0x2000000) {
        switch (code) {
        case 0x2010000:
            D_001AD520 &= ~0x2u;
            break;
        case 0x2020000:
            D_001AD520 &= ~0x4u;
            break;
        case 0x2040000:
            D_001AD520 &= ~0x8u;
            break;
        case 0x2080000:
            D_001AD520 &= ~0x10u;
            break;
        }
    }
    *(volatile unsigned int *)0x10009000 = stat | 0x100;
    return 0;
}
