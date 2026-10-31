/* Nonmatching reconstruction; game compiler, -O2 -G8 -ffunction-sections.
   us: 16_snivelak: 716 bytes, expected 764.
   us2: 16_snivelak: 716 bytes, expected 764.
   pal: func_L16_00418E38 is in neither catalogue of pal.
   716 bytes against 764; the three interpolation segments and completion paths are reconstructed. The retail spills two incrementing global-table pointers; the current loop uses different allocation. Reopen with matching pointer lifetimes. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef int quad __attribute__((mode(TI)));
extern f32 D_L16_001B1C40 __attribute__((sda));
extern f32 D_L16_001B1C50 __attribute__((sda));
extern f32 D_L16_001B1C5C __attribute__((sda));
extern char D_L16_001B9B00[];
extern void func_002AA548(char *, char *, f32, f32, f32, f32);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282D30(char *, char *, f32);
extern void func_00282CC0(char *, char *, char *);
extern void func_L16_00419140(char *);
extern s32 func_002A9640(char *, u32, s32);
extern void func_0032C700(char *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern void func_0029F338(char *);
extern s32 func_00277258(char *, s32, char *, f32);
extern void func_002A7750(char *, s32, s32);
extern void func_00282F20(char *, char *, f32);
extern void func_0032DA58(char *, char *, char *, f32);
extern void func_002A8C28(char *, char *, u32, s32, s32, s32, f32, f32, f32);

/* Blends three motion segments and finishes with the object's destruction effect. */
void func_L16_00418E38(char *self) {
    char delta[16];
    char *st = *(char **)(self + 0x68);
    char *position = self + 16;
    char *current;
    char *next;
    f32 *weight, *rate, *limit, *gain;
    s32 i;
    if (*(u8 *)(self + 0x20) == 0) {
        *(quad *)position = *(quad *)st;
        current = st;
        next = st + 16;
        weight = (f32 *)(st + 0x40);
        rate = (f32 *)(st + 0x50);
        limit = &D_L16_001B1C40;
        gain = &D_L16_001B1C50;
        for (i = 0; i < 3; i++, current += 16, next += 16, weight++, rate++, limit++, gain++) {
            if (i == 0 || weight[-1] > D_L16_001B1C5C)
                func_002AA548((char *)weight, (char *)rate, 1.0f, *limit * 0.00027777778450399637f,
                              *limit * 0.00027777778450399637f, *gain * 0.01666666753590107f);
            func_00282CF0(delta, next, current);
            func_00282D30(delta, delta, *weight);
            func_00282CC0(position, position, delta);
        }
        func_L16_00419140(self);
        if (func_002A9640(self, 0x10000, 0)) {
            func_0032C700(position, 0, 0, 0, 0, 20, 45, 1, 1, 0, 0, 0, 1.0f, 20.0f);
            func_0029F338(self);
        } else if (*(f32 *)(st + 0x48) >= 1.0f || (*(f32 *)(st + 0x44) >= 0.5f && func_00277258(position, 0, self, 0.5f)))
            func_002A7750(self, 1, -1);
    } else if (*(u8 *)(self + 0x20) == 1) {
        func_00282CF0(delta, D_L16_001B9B00, position);
        func_00282F20(delta, delta, 1.0f);
        func_0032DA58(self, position, delta, 0.0f);
        func_002A8C28(self, position, 0x10001, 0, 1, 0, 2.0f, 5.0f, 1.0f);
        func_0029F338(self);
    }
}
