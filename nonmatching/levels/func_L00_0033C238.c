/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections.
 * Compiled 484 bytes; retail 484 bytes.
 * Carrying checks: 0/27 in us and us2; PAL ABSENT. No strict linked qualification.
 * Right size; the mode load and velocity stores have different FPR/scheduling order. Separate deletion guards recover the retail block order. Fourth vector lanes remain unassigned as in retail. Reopen with a measured macro-address/load model and source lifetimes.
 */
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002B9180(void *);
extern int func_L00_0031C998(int, int, float);
extern int func_00282978(short *);
extern int D_L00_001A8F00[] __attribute__((sda));

void func_L00_0033C238(unsigned char *particle)
{
    float velocity[4];
    float relative[4];
    float transformed[4];
    char *data = (char *)particle + 0x20;
    char *settings = *(char **)(data + 0x1C);
    int mode;
    int lifetime = *(int *)(settings + 0xC);
    int fraction = *(short *)(settings + 8) * (lifetime - *(short *)(particle + 0xA)) / lifetime;
    *(float *)(particle + 0xC) = func_00283CE0(fraction + *(short *)(settings + 0xA)) * 1000.0f;
    velocity[0] = *(float *)(particle + 0x20);
    velocity[1] = *(float *)(data + 4);
    velocity[2] = *(float *)(data + 8);
    func_00282D30(velocity, velocity, 0.9800000190734863f);
    *(float *)(particle + 0x20) = velocity[0];
    mode = D_L00_001A8F00[0];
    *(float *)(data + 4) = velocity[1];
    *(float *)(data + 8) = velocity[2];
    if (mode == 0) {
        unsigned char *owner = *(unsigned char **)(data + 0xC);
        if (!owner) goto discard;
        if (owner[0x20] == 0xFE) goto discard;
        if (owner[0x20] == 0xFD) goto discard;
        relative[0] = *(float *)(data + 0x10);
        relative[1] = *(float *)(data + 0x14);
        relative[2] = *(float *)(data + 0x18);
        func_00282CC0(relative, relative, velocity);
        *(float *)(data + 0x10) = relative[0];
        *(float *)(data + 0x14) = relative[1];
        *(float *)(data + 0x18) = relative[2];
        func_00283098(transformed, relative, *(char **)(data + 0xC) + 0xC0);
        func_00282CC0(particle + 0x10, *(char **)(data + 0xC) + 0x10, transformed);
        goto update;
discard:
        func_002B9180(particle);
        return;
    } else {
        func_00282CC0(particle + 0x10, particle + 0x10, velocity);
    }
update:
    particle[8]++;
    *(int *)(particle + 4) = func_L00_0031C998(*(int *)(settings + 4), *(int *)settings,
                      (float)*(short *)(particle + 0xA) / func_00283CE0(*(int *)(settings + 0xC)));
    if (func_00282978((short *)(particle + 0xA)))
        func_002B9180(particle);
}
