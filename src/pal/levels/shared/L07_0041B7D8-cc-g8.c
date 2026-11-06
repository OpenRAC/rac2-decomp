/* func_PAL_L07_0041B7D8, the PAL copy of func_L07_00416510: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_0032D758 becomes func_PAL_0032F0B8; rename func_L07_002BE770 becomes func_PAL_L07_002BE8C8; rename func_L00_0041A5C0 becomes func_PAL_L00_0041F868; rename func_L00_0041BAE8 becomes func_PAL_L00_00420D90; lit 10.0f becomes 12.0f. */
#include "common.h"

typedef unsigned int UpdateQuad __attribute__((mode(TI)));
typedef union { UpdateQuad q; float f[4]; } UpdateVector;
typedef struct {
    UpdateVector position;
    int i10, flags;
    unsigned char kind, active;
    unsigned short owner;
    float value;
    int enabled;
    float extra;
} UpdateRequest;
typedef struct { unsigned char pad[0x38]; int sound; unsigned char tail[4]; } UpdateArc;
typedef struct { unsigned char pad[0x30]; int active; unsigned char tail[0xC]; } UpdatePoint;
typedef struct { unsigned char pad[0x514]; int active; unsigned char tail[0x18]; } UpdateBeam;
typedef struct { unsigned char pad[0x70]; float value; unsigned char tail[0x6C]; } UpdateMaterial;
typedef struct { unsigned char pad[0x74]; unsigned char active; unsigned char gap[0x13]; unsigned char *owner; } UpdateSound;

typedef struct {
    unsigned char pad0[0xBF8]; unsigned char *camera;
    unsigned char padBFC[0x1230-0xBFC]; int mask;
    unsigned char pad1234[0x1244-0x1234]; int mode;
    unsigned char pad1248[0x1450-0x1248]; unsigned char *view;
    unsigned char pad1454[0x2290-0x1454]; unsigned char *object; int weapon;
    unsigned char pad2298[0x22BC-0x2298]; unsigned char disabled;
    unsigned char pad22BD[0x2534-0x22BD]; int timer;
} UpdatePlayer;
extern UpdatePlayer D_00189E20;
typedef struct { unsigned char pad[0x1A0]; int held, pressed; } UpdateInput;
extern UpdateInput D_00138180;
typedef struct { unsigned char pad[0x1D]; unsigned char material; } UpdateSettings;
extern UpdateSettings D_00139568;
extern unsigned char D_00188660[] NOT_SDA;
extern UpdateMaterial D_L07_002628A0[] NOT_SDA;
extern unsigned char *D_L07_001C36C0[];
extern unsigned char *D_L07_001B18B8 __attribute__((sda));
extern unsigned char *D_L07_001B18BC __attribute__((sda));
extern unsigned char *D_L07_001B18C0 __attribute__((sda));
extern int D_L07_001A8FF0;
extern int D_L07_001A8F00;
extern void func_002FEE50(int);
extern int func_L00_00329E90(void *, int, void *);
extern unsigned char *func_L00_0032A088(int, int);
extern unsigned char *func_L00_0041A490(void *);
extern void func_002E59F8(int);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_00282948(void *);
extern int func_L00_002D4040(int);
extern void func_L00_002D3F30(int, int);
extern float func_002AA3A8(float *, float *, float, float, float, float);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_00277F48(float, void *, int, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8E20(void *, void *);
extern void func_PAL_0032F0B8(void *, int, void *);
extern void func_PAL_L07_002BE8C8(int, int);
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_0032A1A8(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_0041ABB8(void *, void *, void *, int);
extern void func_PAL_L00_0041F868(void *);
extern void func_L00_0041A500(void *);
extern void func_PAL_L00_00420D90(void *);
extern void func_L00_002E6EF8(void *, void *);
extern void ref_L07_00416510_00(void);

#define UI(p,o) (*(int *)((p)+(o)))
#define UF(p,o) (*(float *)((p)+(o)))
#define UP(p,o) (*(unsigned char **)((p)+(o)))

/* Updates the held weapon, target damage requests, sound and beam effects. */
void func_PAL_L07_0041B7D8(unsigned char *object)
{
    UpdateVector vector, delta;
    UpdateRequest request;
    int scratch;
    unsigned char *data = UP(object, 0x68);
    int i = 0;
    int allowed;
    int count;
    unsigned char **targets;

    if (D_00189E20.mode == 3 && D_L07_001B18BC) {
        for (; i < 35; i++) {
            unsigned char *entry = D_L07_001B18BC + i * 0x40;
            if (UI(entry, 0x38) >= 0) {
                func_002FEE50(UI(entry, 0x38));
                UI(entry, 0x38) = -1;
            }
        }
    }
    if (object[0x20] == 0) {
        UI(data, 0x34) = func_L00_00329E90(object, 0, &scratch);
        D_L07_001B18C0 = func_L00_0032A088(*(short *)(object + 0xAA), UI(data, 0x34));
        D_L07_001B18B8 = func_L00_0041A490(D_L07_001B18C0 + 0x33E0);
        D_L07_001B18BC = func_L00_0041A490(D_L07_001B18B8 + 0x1F40);
        for (i = 124; i >= 0; i--)
            ((UpdatePoint *)D_L07_001B18B8)[i].active = 1;
        for (i = 9; i >= 0; i--)
            ((UpdateBeam *)D_L07_001B18C0)[i].active = 0;
        {
            int inactive = -1;
            i = 34;
            do {
                ((UpdateArc *)D_L07_001B18BC)[i].sound = inactive;
            } while (--i >= 0);
        }
        UI(data, 0x3C) = 0;
        UI(data, 0x48) = 0;
        UI(data, 0x40) = 0;
        UI(data, 0x44) = 0;
        UI(data, 0x54) = 0;
        UI(data, 0x50) = 0;
        UI(data, 0x58) = 0;
        UI(data, 0x5C) = 0;
        UI(data, 0x60) = 0;
        UI(data, 0x64) = 0;
        object[0x20] = 1;
        UI(data, 0x38) = -1;
    }
    if (D_00189E20.mode == 3) {
        int index = UI(data, 0x38);
        if (index != -1 && ((UpdateSound *)(D_00188660 + index * 0x70))->owner == object && ((UpdateSound *)(D_00188660 + index * 0x70))->active)
            func_002E59F8(index);
        UI(data, 0x38) = -1;
        return;
    }
    func_0029FCC0(object, 0, data);
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        func_002A75E0(object, 1, 0, 2, 0);
    allowed = 1;
    if (D_00189E20.weapon == 0x1D) {
        if (!func_00282948(&D_00189E20.timer)) allowed = 0;
    } else D_00189E20.timer = 33;
    if ((D_00138180.held & D_00189E20.mask) && allowed &&
        func_L00_002D4040(-1) && !D_00189E20.disabled) {
        func_002AA3A8((float *)(data + 0x50), (float *)(data + 0x54), 10.0f, 0.009000001f, 0.0024f, 12.0f);
        if (UI(data, 0x60) % 10 == 0) func_L00_002D3F30(-1, 1);
        UI(data, 0x60)++;
        if (!func_002E59B0(object, UI(data, 0x38)))
            UI(data, 0x38) = func_002E5CF8(0, 4, object);
        if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 0, 0);
        count = func_00277F48(0.5f, data, 16, object, 0);
        if (count > 0) {
            int remaining;
            targets = D_L07_001C36C0;
            remaining = count;
            do {
                if (*targets != D_00189E20.object) {
                    func_00282CF0(&delta, *targets + 0x10, object + 0x10);
                    func_00282F20(&delta, &delta, 1.0f);
                    func_00282F20(&request, &request, 1.0f);
                    func_002A8C00(&request, object, 0x910000,
                        ((UpdateMaterial *)((unsigned int)D_L07_002628A0 + D_00139568.material * sizeof(UpdateMaterial)))->value, &delta);
                    request.position.q = delta.q;
                    request.enabled = 1;
                    request.position.f[3] = 5627.925f;
                    request.kind = 9;
                    request.active = 1;
                    request.owner = *(unsigned short *)(*targets + 0xAA);
                    func_002A8E20(*targets, &request);
                    func_PAL_0032F0B8(*targets, 0x1D, object);
                    func_002E5CF8(1, 0, object);
                }
                targets++;
            } while (--remaining);
        }
    } else {
        int index = UI(data, 0x38);
        if (index != -1 && ((UpdateSound *)(D_00188660 + index * 0x70))->owner == object && ((UpdateSound *)(D_00188660 + index * 0x70))->active)
            func_002E59F8(index);
        UI(data, 0x38) = -1;
        if ((D_00138180.pressed & D_00189E20.mask) && !func_L00_002D4040(-1) && !D_00189E20.disabled)
            func_002E5CF8(2, 0, object);
        func_002AA3A8((float *)(data + 0x50), (float *)(data + 0x54), 0.0f, 0.072000004f, 0.012f, 0.15f);
        UI(data, 0x60) = 0;
    }
    if (D_00189E20.weapon == 1) func_PAL_L07_002BE8C8(0x1D, 1);
    func_0029FCC0(object, 0, data);
    func_00282C88(&vector);
    vector.f[1] = -1.0f;
    func_00283098(&vector, &vector, object + 0xC0);
    vector.f[2] += 0.02f;
    func_00282F20(&vector, &vector, UF(data, 0x50) * 0.05f);
    if (D_00189E20.view) {
        D_00189E20.camera = D_00189E20.view;
        func_L00_0032A1A8(D_00189E20.view, data, &vector, UF(data, 0x50) * 0.05f);
        if (D_L07_001A8FF0) {
            func_00282D30(&delta, object + 0xE0, 0.02f);
            func_00282CC0(&vector, &vector, &delta);
        } else vector.f[2] += 0.02f;
    }
    qcopy(data + 0x10, data);
    if (D_00189E20.weapon)
        func_002ACEC0(&vector, &vector, D_00189E20.object + 0xD0, -0.098174773f);
    if (UF(data, 0x50) != 0.0f) func_L00_0041ABB8(object, data, &vector, 33);
    UF(data, 0x58) -= 0.1f;
    if (UF(data, 0x58) <= -8.0f) UF(data, 0x58) += 8.0f;
    UF(data, 0x5C) -= 0.025f;
    if (UF(data, 0x5C) <= -8.0f) UF(data, 0x5C) += 8.0f;
    if (UF(data, 0x50) != 0.0f) {
        func_PAL_L00_0041F868(object);
        func_L00_0041A500(object);
    } else {
        UI(data, 0x44) = 0;
        UI(data, 0x3C) = 0;
        UI(data, 0x48) = 0;
        UI(data, 0x40) = 0;
    }
    func_PAL_L00_00420D90(object);
    if (D_L07_001A8F00 != 2 && object[0x31])
        func_L00_002E6EF8(ref_L07_00416510_00, object);
}
