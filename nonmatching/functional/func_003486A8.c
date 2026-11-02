/* functional: high. Same calls, arguments, reads and writes as retail, in retail's order; differs from the near miss in two behaviours it got wrong: the 0x43C store happens before the func_00348578 call (retail's delay slot) and the first func_00336390 call also gets D_001A8CFC + 0x8710. */

/* Initialises the menu panel `self` (owner may be null): resets its state, allocates its 16-byte origin
 * (250, 190) from the owner's pool, loads the seven sprite elements (D_001ADC10..D_001AE5B8) and the seven
 * 0x48-byte slots at +0x218 (D_001AE5C8, scale 1, colour 0x80F0F0F0, flag words at +0x418 set to 1), sets the
 * element colours and their text entries 0x1C..0x20, 0x73, 0x74 from the table at D_001A8CFC + 0x8710, then
 * func_003489E8(self, 0). */

extern void func_00348578(unsigned char *, int);
extern int func_00336E40(void *);
extern void *func_00336DA8(int, int);
extern void func_003361E0(void *, void *, void *);
extern void *func_003369A8(void *, void *, void *);
extern void func_00336A38(void *, int);
extern void func_00335F88(char *, float, float, float, float);
extern int func_00335E20(unsigned char *);
extern void func_00336390(char *, char *, int);
extern int func_003489E8(void *, int);
extern char D_001ADC10[];
extern char D_001ADC18[];
extern char D_001ADC28[];
extern char D_001ADFC0[];
extern char D_001ADFC8[];
extern char D_001AE5B0[];
extern char D_001AE5B8[];
extern char D_001AE5C8[];
extern char *D_001A8CFC __attribute__((section(".sdata")));

void func_003486A8(unsigned char *self, void *owner)
{
    unsigned char *slot;
    int *flags;
    int i;

    *(int *)(self + 0x43C) = 0;
    func_00348578(self, 0);
    *(void **)(self + 0x438) = owner;
    if (owner) {
        int *list = (int *)func_00336DA8(16, func_00336E40(owner));
        *(int **)(self + 0x434) = list;
        list[0] = 0;
        list[1] = 0;
        list[2] = 0;
        list[3] = 0;
    }
    *(int *)(self + 0x440) = 1;
    (*(float **)(self + 0x434))[0] = 250.0f;
    (*(float **)(self + 0x434))[1] = 190.0f;
    func_003361E0(self, D_001ADC10, owner);
    func_003361E0(self + 0x130, D_001ADC18, owner);
    func_003361E0(self + 0x4C, D_001ADC28, owner);
    func_003361E0(self + 0x98, D_001ADFC0, owner);
    func_003361E0(self + 0xE4, D_001ADFC8, owner);
    func_003361E0(self + 0x17C, D_001AE5B0, owner);
    func_003361E0(self + 0x1C8, D_001AE5B8, owner);
    *(int *)(self + 0x410) = 0;
    *(int *)(self + 0x444) = 0;
    slot = self + 0x218;
    flags = (int *)(self + 0x418);
    for (i = 6; i >= 0; i--) {
        func_003369A8(slot, D_001AE5C8, owner);
        func_00336A38(slot, 0);
        func_00335F88((char *)slot, 1.0f, 0.0f, 0.0f, 0.0f);
        *(int *)func_00335E20(slot) = 0x80F0F0F0;
        *flags = 1;
        flags++;
        slot += 0x48;
    }
    *(int *)func_00335E20(self) = 0x60442D00;
    *(int *)func_00335E20(self + 0x130) = 0x55F0C070;
    *(int *)func_00335E20(self + 0x4C) = 0x55F0C070;
    *(int *)func_00335E20(self + 0x98) = 0x55F0C070;
    *(int *)func_00335E20(self + 0xE4) = 0x80FFDE8D;
    *(int *)func_00335E20(self + 0x17C) = 0x70FFFEED;
    *(int *)func_00335E20(self + 0x1C8) = 0x60442D00;
    func_00336390((char *)self, D_001A8CFC + 0x8710, 0x1C);
    func_00336390((char *)self + 0x130, D_001A8CFC + 0x8710, 0x1D);
    func_00336390((char *)self + 0x4C, D_001A8CFC + 0x8710, 0x1E);
    func_00336390((char *)self + 0x98, D_001A8CFC + 0x8710, 0x1F);
    func_00336390((char *)self + 0xE4, D_001A8CFC + 0x8710, 0x20);
    func_00336390((char *)self + 0x17C, D_001A8CFC + 0x8710, 0x73);
    func_00336390((char *)self + 0x1C8, D_001A8CFC + 0x8710, 0x74);
    func_003489E8(self, 0);
}
