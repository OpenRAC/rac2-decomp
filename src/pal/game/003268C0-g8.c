#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x20];
    unsigned char state;
    char pad21[0x47];
    char *data;
    char pad6c[0x29];
    unsigned char f95;
    unsigned short timer;
} TurnObject;
typedef struct {
    char pad00[0x26];
    char f26[2];
    char pad28[0x28];
    char f50[0x220];
    char f270[2];
    char f272[0x2E];
    char f2A0[0xC];
    float turnAngle;
    char pad2b0[0x14];
    int f2C4;
    char pad2c8[0x20];
    float turnRate;
    char pad2ec[0x10];
    char f2FC[0x234];
    char f530[0x80];
    char f5B0[1];
} TurnData;
extern void func_PAL_002AC3C0(void *, void *);
extern int func_00282978(void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_PAL_002B14F8(void *, void *, int, int, float);
extern float func_00283B98(float, float);
extern void func_PAL_003273B8(void *, float, void *, int, void *);
extern char D_001A8BD0[] __attribute__((sda));
extern void func_00325430(void);
extern void func_0027CFD0(void (*)(void), void *);
extern void func_00325DA0(void *, void *);

/* Steer the object toward its turn target and update its joint chains. */
void func_PAL_003268C0(TurnObject *object)
{
    TurnData *data = (TurnData *)object->data;

    if (object->f95 != 0 && object->state != 3 && object->f95 != 5 && data->f2C4 == 0) {
        data->turnAngle = func_00283B98(data->turnAngle, data->turnRate * 0.017453294f);
        func_PAL_003273B8(object, data->turnAngle, data->f2A0, 1, D_001A8BD0);
    } else {
        func_PAL_003273B8(object, data->turnAngle, data->f2A0, 0, D_001A8BD0);
    }
    func_PAL_002AC3C0(object, data->f50);
    func_00282978(data->f270);
    func_00282978(data->f272);
    func_00282978(data->f26);
    func_002AEC48(object, data->f530, 7, 0.0432f, 0.43200004f);
    func_002AEC48(object, data->f5B0, 8, 0.0432f, 0.43200004f);
    if (object->timer < 65535)
        object->timer++;
    if (object->state == 4 || object->state == 5 || object->f95 == 2 || object->state == 10)
        func_0027CFD0(func_00325430, object);
    func_00325DA0(object, data->f2FC);
    func_PAL_002B14F8(object, data->f530, 7, 1, 2.5f);
}
