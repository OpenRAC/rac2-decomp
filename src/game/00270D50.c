typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern char D_00189E20[];
extern char D_L00_001B8C80[];
extern void func_00282F20(float *, float *, float);
extern void func_00270B58(float *, float *, float *, float *, float *, float *);

/* Normalises the hero's vectors and fills the camera block with them for the current frame. */
void func_00270D50(void)
{
    Vector first;
    Vector second;
    Vector third;
    char *resident = D_00189E20;
    char *camera = D_L00_001B8C80 + 0x290;

    func_00282F20(first.f, (float *)(*(char **)(resident + 0x2290) + 0xC0), 1.0f);
    func_00282F20(second.f, (float *)(*(char **)(resident + 0x2290) + 0xD0), 1.0f);
    func_00282F20(third.f, (float *)(*(char **)(resident + 0x2290) + 0xE0), 1.0f);
    *(Quad *)(camera + 0x90) = first.q;
    *(Quad *)(camera + 0xA0) = third.q;
    func_00270B58((float *)(camera + 0x70), (float *)(camera + 0xC0),
                 (float *)(resident + 0x80), first.f, second.f, third.f);
    *(Quad *)(camera + 0xB0) = *(Quad *)(camera + 0xD0);
}
