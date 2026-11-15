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
extern UpdatePlayer g_hero_state;
typedef struct { unsigned char pad[0x1A0]; int held, pressed; } UpdateInput;
extern UpdateInput g_pad_state;
typedef struct { unsigned char pad[0x1D]; unsigned char material; } UpdateSettings;
extern UpdateSettings g_item_slot_to_record;
extern unsigned char g_sound_state[] NOT_SDA;
extern UpdateMaterial D_L07_002628A0[] NOT_SDA;
extern unsigned char *D_L07_001C36C0[];
extern unsigned char *D_L07_001B18B8 __attribute__((sda));
extern unsigned char *D_L07_001B18BC __attribute__((sda));
extern unsigned char *D_L07_001B18C0 __attribute__((sda));
extern int D_L07_001A8FF0;
extern int D_L07_001A8F00;
extern void table_clear_entry_flag(int);
extern int AcquireEntitySlot(void *, int, void *);
extern unsigned char *level_get_slot_body(int, int);
extern unsigned char *mem_align_up_sixteen_alt(void *);
extern void snd_stop_voice(int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern int math_fast_float_d(void *);
extern int get_ammo(int);
extern void weapon_spend_ammo(int, int);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int coll_process_hit(float, void *, int, void *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, float, void *);
extern void QueueMobyImpact(void *, void *);
extern void func_PAL_0032F0B8(void *, int, void *);
extern void func_PAL_L07_002BE8C8(int, int);
extern void vec_clear_128(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_compute_object_to_target(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void AppendVectorRingEntry(void *, void *, void *, int);
extern void func_PAL_L00_0041F868(void *);
extern void lava_gun_update_ring_entries(void *);
extern void func_PAL_L00_00420D90(void *);
extern void gfx_add_draw_callback_third(void *, void *);
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

    if (g_hero_state.mode == 3 && D_L07_001B18BC) {
        for (; i < 35; i++) {
            unsigned char *entry = D_L07_001B18BC + i * 0x40;
            if (UI(entry, 0x38) >= 0) {
                table_clear_entry_flag(UI(entry, 0x38));
                UI(entry, 0x38) = -1;
            }
        }
    }
    if (object[0x20] == 0) {
        UI(data, 0x34) = AcquireEntitySlot(object, 0, &scratch);
        D_L07_001B18C0 = level_get_slot_body(*(short *)(object + 0xAA), UI(data, 0x34));
        D_L07_001B18B8 = mem_align_up_sixteen_alt(D_L07_001B18C0 + 0x33E0);
        D_L07_001B18BC = mem_align_up_sixteen_alt(D_L07_001B18B8 + 0x1F40);
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
    if (g_hero_state.mode == 3) {
        int index = UI(data, 0x38);
        if (index != -1 && ((UpdateSound *)(g_sound_state + index * 0x70))->owner == object && ((UpdateSound *)(g_sound_state + index * 0x70))->active)
            snd_stop_voice(index);
        UI(data, 0x38) = -1;
        return;
    }
    moby_transform_joint_to_world(object, 0, data);
    if (object[0x42] == object[0x43] && (object[0x60] & 2))
        anim_start_blended_with_flags(object, 1, 0, 2, 0);
    allowed = 1;
    if (g_hero_state.weapon == 0x1D) {
        if (!math_fast_float_d(&g_hero_state.timer)) allowed = 0;
    } else g_hero_state.timer = 33;
    if ((g_pad_state.held & g_hero_state.mask) && allowed &&
        get_ammo(-1) && !g_hero_state.disabled) {
        math_spring_float_to_goal((float *)(data + 0x50), (float *)(data + 0x54), 10.0f, 0.009000001f, 0.0024f, 12.0f);
        if (UI(data, 0x60) % 10 == 0) weapon_spend_ammo(-1, 1);
        UI(data, 0x60)++;
        if (!snd_is_voice_playing_for_owner(object, UI(data, 0x38)))
            UI(data, 0x38) = PlayMobySound(0, 4, object);
        if (object[0x43] != 2) func_PAL_002A7E68(object, 2, 0, 0);
        count = coll_process_hit(0.5f, data, 16, object, 0);
        if (count > 0) {
            int remaining;
            targets = D_L07_001C36C0;
            remaining = count;
            do {
                if (*targets != g_hero_state.object) {
                    FastVecSub(&delta, *targets + 0x10, object + 0x10);
                    vec_scale_to_length(&delta, &delta, 1.0f);
                    vec_scale_to_length(&request, &request, 1.0f);
                    make_hit_descriptor(&request, object, 0x910000,
                        ((UpdateMaterial *)((unsigned int)D_L07_002628A0 + g_item_slot_to_record.material * sizeof(UpdateMaterial)))->value, &delta);
                    request.position.q = delta.q;
                    request.enabled = 1;
                    request.position.f[3] = 5627.925f;
                    request.kind = 9;
                    request.active = 1;
                    request.owner = *(unsigned short *)(*targets + 0xAA);
                    QueueMobyImpact(*targets, &request);
                    func_PAL_0032F0B8(*targets, 0x1D, object);
                    PlayMobySound(1, 0, object);
                }
                targets++;
            } while (--remaining);
        }
    } else {
        int index = UI(data, 0x38);
        if (index != -1 && ((UpdateSound *)(g_sound_state + index * 0x70))->owner == object && ((UpdateSound *)(g_sound_state + index * 0x70))->active)
            snd_stop_voice(index);
        UI(data, 0x38) = -1;
        if ((g_pad_state.pressed & g_hero_state.mask) && !get_ammo(-1) && !g_hero_state.disabled)
            PlayMobySound(2, 0, object);
        math_spring_float_to_goal((float *)(data + 0x50), (float *)(data + 0x54), 0.0f, 0.072000004f, 0.012f, 0.15f);
        UI(data, 0x60) = 0;
    }
    if (g_hero_state.weapon == 1) func_PAL_L07_002BE8C8(0x1D, 1);
    moby_transform_joint_to_world(object, 0, data);
    vec_clear_128(&vector);
    vector.f[1] = -1.0f;
    matrix_mul_vec3(&vector, &vector, object + 0xC0);
    vector.f[2] += 0.02f;
    vec_scale_to_length(&vector, &vector, UF(data, 0x50) * 0.05f);
    if (g_hero_state.view) {
        g_hero_state.camera = g_hero_state.view;
        vec_compute_object_to_target(g_hero_state.view, data, &vector, UF(data, 0x50) * 0.05f);
        if (D_L07_001A8FF0) {
            FastVecScale(&delta, object + 0xE0, 0.02f);
            FastVecAdd(&vector, &vector, &delta);
        } else vector.f[2] += 0.02f;
    }
    qcopy(data + 0x10, data);
    if (g_hero_state.weapon)
        math_apply_axis_rotation_to_quat(&vector, &vector, g_hero_state.object + 0xD0, -0.098174773f);
    if (UF(data, 0x50) != 0.0f) AppendVectorRingEntry(object, data, &vector, 33);
    UF(data, 0x58) -= 0.1f;
    if (UF(data, 0x58) <= -8.0f) UF(data, 0x58) += 8.0f;
    UF(data, 0x5C) -= 0.025f;
    if (UF(data, 0x5C) <= -8.0f) UF(data, 0x5C) += 8.0f;
    if (UF(data, 0x50) != 0.0f) {
        func_PAL_L00_0041F868(object);
        lava_gun_update_ring_entries(object);
    } else {
        UI(data, 0x44) = 0;
        UI(data, 0x3C) = 0;
        UI(data, 0x48) = 0;
        UI(data, 0x40) = 0;
    }
    func_PAL_L00_00420D90(object);
    if (D_L07_001A8F00 != 2 && object[0x31])
        gfx_add_draw_callback_third(ref_L07_00416510_00, object);
}
