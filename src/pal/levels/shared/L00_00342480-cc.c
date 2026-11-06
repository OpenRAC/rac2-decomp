/* func_PAL_L00_00342480, the PAL copy of func_L00_0033FFB8: the same C, where scale lifetime / 2; wrap particle (((int)({e}) * 5 + 2) / 6); rewrap func_002A77E0(255); rewrap lifetime. */
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern unsigned char *D_L00_001FEAD8;

unsigned char *func_PAL_L00_00342480(Quadword *position, Quadword *velocity, int lifetime) {
    unsigned char *particle = func_002B9030(0x66);
    unsigned char *motion;
    if (particle) {
        motion = particle + 0x20;
        particle[9] = func_00283CF0(2.0f) + 0x40;
        particle[3] = 0x44;
        particle[1] = 0;
        particle[2] = *D_L00_001FEAD8;
        *(float *)(particle + 0xC) = func_002A7878(0.03f, 0.175f) * 210000.0f;
        particle[8] = func_002A77E0(255);
        *(short *)(particle + 0xA) = (((int)(lifetime) * 5 + 2) / 6);
        *(Quadword *)(particle + 0x10) = *position;
        *(Quadword *)motion = *velocity;
        *(float *)(motion + 0xC) = func_002A7878(4.6f, 8.6f) * 0.00040000002f;
        *(float *)(motion + 0x18) = *(float *)(particle + 0xC) * 2.0f;
        *(short *)(motion + 0x16) = func_002A7820(0, 3);
        *(short *)(motion + 0x14) = (((int)(lifetime / 2) * 5 + 2) / 6);
        *(float *)(motion + 0x1C) = func_002A7940();
    }
    return particle;
}
