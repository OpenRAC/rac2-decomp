extern void func_00282D30(void *, void *, float);

/* Projects a world point to screen coordinates (rac1's project_to_screen): builds the
   camera matrix from the identity with the negated, scaled camera position, transforms
   the point and divides by depth around the 2048 centre, in 1/16 pixel units. Retail
   compiles this with -g (the nop pair before div.s). */
typedef struct {
    char pad_0[0x140];
    float unk140;
    float unk144;
    float unk148;
} CameraView279BD8;
typedef struct {
    float unk0;
    float unk4;
    float unk8;
} ScreenPoint279BD8;
typedef struct {
    char pad_0[0x30];
    float v30;
    float v34;
    float v38;
    char pad_3C[4];
    float v40;
    char pad_44[0x3C];
    char blk80[0x0C];
    float v8C;
    float v90;
    float v94;
    float v98;
    float v9C;
} Locals279BD8;
extern CameraView279BD8 D_001B5200;
extern float D_001B9250[];
extern void func_00283388(void *);
extern void func_00283788(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);

/* Projects a world position to screen coordinates using the camera matrices and writes the result to screen_out. */
void func_00279BD8(ScreenPoint279BD8 *screen_out, void *world_pos)
{
    Locals279BD8 L;
    float scale;
    float y;
    float x;

    func_00283388(&L);
    L.v30 = -D_001B5200.unk140 * 1024.0f;
    L.v34 = -D_001B5200.unk144 * 1024.0f;
    L.v38 = -D_001B5200.unk148 * 1024.0f;
    func_00283788(&L.v40, (char *)&D_001B5200 + 0x40, &L);
    func_00282D30(&L.blk80, world_pos, 1024.0f);
    L.v8C = 1.0f;
    func_002830C0(&L.v90, &L.blk80, &L.v40);
    scale = D_001B9250[0] / L.v9C;
    screen_out->unk8 = L.v98 * 0.0009765625f;
    x = L.v90 * scale + 2048.0f;
    y = L.v94 * scale + 2048.0f;
    L.v90 = x;
    L.v94 = y;
    screen_out->unk0 = x * 16.0f;
    screen_out->unk4 = y * 16.0f;
}
