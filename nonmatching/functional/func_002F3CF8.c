/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* 0 of 28 placements match in USA v1.01, PAL, and USA v2.00.
   Four checker invocations covered two plain-C forms; the best was 44 bytes
   against 40 retail bytes. The byte-pointer form emits an extra address
   calculation and uses $v0 rather than retail's $at; the loop also schedules
   its nops differently. Retail uses $at as a working register, which is useful
   handwritten-code evidence for review, not an ASM_FUNC classification. */
void func_002F3CF8(volatile int *ptr)
{
    volatile int *status = (volatile int *)((volatile char *)ptr - 0x2C00);
    while (*status & 0x100)
        ;
}
