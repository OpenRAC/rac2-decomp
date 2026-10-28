/* Retained meaningful C; not matching. 2026-10-28 default game G8 profile:
 * 600/600 bytes at the sole US placement. Five compiles compare raw and typed
 * state views, independent initialization ordering and named conversion units.
 * Reversing two independent byte initializations fixes the prefix through+0x70.
 * Remaining FP temporaries and independent store order differ in the setup.
 * The damage/group guard is >=2 OR mode==2 and contains both group helpers.
 * Canonical helper returns/widths are retained; aim point is a real pointer,
 * and sound creation returns int. The tuning owner is incomplete and both
 * adjacent floats are read through one SDATA view. No volatile or raw aliases.
 * State prefix covers every direct access through+0x268, and the copied spawn
 * vector is16 bytes. No extra initialization or padding was introduced.
 * Reopen with a measured FP-value/member-group lifetime or unit-profile witness.
 * US2/PAL and linked builds were not run for this near miss.
 */
#include "common.h"
typedef int CreatureQuad __attribute__((mode(TI)));
extern int func_00283CF0(float);
extern void func_002A7750(void *, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002E5CF8(int, int, char *);
extern int func_002B0ED8(char *, char *, int);
extern void func_L07_003E5AC8(unsigned char *);
extern void func_L07_003E5D80(unsigned char *);
extern int func_002B3BA8(char *, int, CreatureQuad *, int, float, float);
extern void func_L07_003E6148(char *);
extern float D_L07_001B0AA0[] SDATA(D_L07_001B0AA0);
extern char D_L07_001B9200[];
extern unsigned char D_00188660[];
struct SiberiusMotion {
    char unknown0[0x2e];
    unsigned char mode;
    char unknown2f[0x1];
    int timer;
    char unknown34[0x14];
    unsigned char turn_rate;
    char unknown49[0x1];
    unsigned char speed_rate;
    char unknown4b[0x15];
    unsigned char step_count;
    char unknown61[0x1f];
    float blend;
    int blend_timer;
    char unknown88[0x4];
    float damping;
    char unknown90[0x8];
    int control;
    char unknown9c[0xc];
    float scale_a;
    float scale_b;
    char unknownb0[0x17];
    unsigned char enabled;
    char unknownc8[0x58];
    float probe;
    int probe_timer;
    char unknown128[0x18];
    float acceleration_a;
    float acceleration_b;
    float speed;
    char unknown14c[0xc];
    unsigned int flags;
    char unknown15c[0xb8];
    int sound_index;
    short spawn_mode;
    char unknown21a[0x6];
    float spawn_position[4];
    char unknown230[0x30];
    void * host;
    int sound_handle;
};
void func_L07_003E56B8(unsigned char *object)
{
    struct SiberiusMotion *data = *(struct SiberiusMotion **)(object + 0x68);
    if (!object[0x20]) {
        float acceleration, speed;
        data->turn_rate = func_00283CF0(15.0f);
        data->speed_rate = func_00283CF0(2.4f);
        data->step_count = 7;
        data->mode = 1;
        data->enabled = 1;
        {
            float acceleration_unit = 0.0002777777845f;
            float speed_unit = 0.016666668f;
            acceleration = D_L07_001B0AA0[0] * acceleration_unit;
            speed = D_L07_001B0AA0[1] * speed_unit;
        }
        data->control = 3;
        data->blend = 0.5f;
        data->damping = 0.15f;
        data->scale_a = 1.0f;
        data->probe = 0.45f;
        data->acceleration_a = acceleration;
        data->speed = speed;
        data->flags |= 0x15;
        data->blend_timer = 0;
        data->scale_b = 1.0f;
        data->probe_timer = 0;
        data->acceleration_b = acceleration;
        data->timer = 0;
        qcopy(data->spawn_position, object + 0x10);
        if (data->spawn_mode) func_002A7750(object, 1, 0);
        else {
            *(int *)(object + 0x98) = 0;
            *(unsigned short *)(object + 0x34) = (*(unsigned short *)(object + 0x34) | 0x41) & 0xefff;
            func_002A7750(object, 8, 4);
        }
    }
    if (object[0x31] && func_00282E48(object + 0x10, D_L07_001B9200) < 24.0f) {
        func_002A93B0(object);
        object[0x6f] = 22;
    }
    if (object[0x95] != 4) {
        unsigned char *record = D_00188660 + data->sound_handle * 0x70;
        if (*(void **)(record + 0x88) != object || !record[0x74])
            data->sound_handle = func_002E5CF8(1, 4, (char *)object);
    }
    if (func_002B0ED8((char *)object, (char *)data + 0x50, 0) >= 2 || data->mode == 2) {
        func_L07_003E5AC8(object);
        func_L07_003E5D80(object);
    }
    func_002B3BA8((char *)object, data->sound_index, 0, 0, 0.0f, 0.0f);
    if (data->host && object[0x20] != 8) func_L07_003E6148((char *)object);
}
