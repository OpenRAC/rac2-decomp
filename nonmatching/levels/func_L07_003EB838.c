/* Retained near miss, 2026-10-28: 624/636 bytes after five forms.
 * Separating initialization/update cursors restores the retail saved-register
 * order. Three final lifetime/profile forms tie; -fno-regmove adds no benefit.
 * First mismatch is the saved-position destination register at+0x2c; the
 * update path also coalesces address lifetimes that retail keeps separate.
 * Three local vectors are complete16-byte objects. State spans through+0x31c,
 * including existing16-byte Euler storage; setup writesXYZ12, without inventing
 * initialization for its existing fourth word. Object direct accesses reach
 * the16-byte slot at+0xf0. Damage helper inputs read16 bytes each.
 * The damage helper return remains the existing integer contract provisionally:
 * mixed retailv0 paths do not establish void, and a current wrapper consumesv0.
 * Its second32-bit slot is opaque here (an explicitly converted stored pointer).
 * Resolve real consumers/donor before treating this as a canonical interface.
 * No raw aliases, ordinary-field volatile, forced registers or extra accesses.
 * Reopen on a supported genuine cursor lifetime witness and interface evidence.
 */
#include "common.h"
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_002AD0B0(unsigned char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);
extern int func_002AD5F8(char *, char *, char *, char *, char *, char *);
extern int func_002AD470(char *, char *, char *, char *, char *, char *);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_002B0408(void *, void *, void *);
extern void func_002AB6D8(float *, float *);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern char D_L07_001BF640[];
extern int func_002A8F70(void *, unsigned int, unsigned int, void *, void *, float);
extern void *D_0018C0B0;
extern char D_001A8F20[];
void func_L07_003EB838(unsigned char *object)
{
    float start[4], end[4], delta[4];
    char *data = *(char **)(object + 0x68);
    char *previous_position = data + 0x2e0;
    char *attached = *(char **)(data + 0x314);
    if (!attached) {
        char *position;
        unsigned char *definition;
        char *hit;
        char *platform;
        position = (char *)object + 0x10;
        qcopy(start, position);
        qcopy(end, position);
        start[2] += 2.0f;
        end[2] -= 3.0f;
        if (!func_002761F8(start, end, 0, object, 0)) return;
        hit = D_L07_001BF640;
        platform = *(char **)(hit + 0x18);
        if (!platform) return;
        definition = (unsigned char *)func_002AD0B0((unsigned char *)platform);
        if (*(unsigned int *)(definition + 0x3c) & 2) {
            *(char **)(data + 0x314) = *(char **)(hit + 0x18);
            func_00282CF0(delta, position, *(char **)(data + 0x314) + 0x10);
            func_002AFDD8(*(char **)(data + 0x314), (char *)delta, (char *)delta, 0);
            *(float *)(data + 0x318) = delta[2] - 1.0f;
            func_002AD5F8((char *)object, *(char **)(data + 0x314), position, (char *)object + 0xf0, data + 0x2f0, data + 0x300);
        }
        *(unsigned int *)(data + 0x88) |= 0x100;
        return;
    }
    {
        char *position;
        char *rotation;
        char *saved_position;
        qcopy(previous_position, object + 0x10);
        saved_position = (char *)object + 0x10;
        if (object[0x20] == 7 || object[0x20] == 11) {
            rotation = (char *)object + 0xf0;
            func_002AD470((char *)object, attached, data + 0x2f0, data + 0x300, saved_position, rotation);
        } else {
            rotation = (char *)object + 0xf0;
            func_002AD0E0(object, attached, saved_position, rotation, saved_position, rotation);
        }
        position = (char *)object + 0xc0;
        func_002833F0(position, rotation);
        func_002B0408(position, *(char **)(data + 0x314) + 0xe0, 0);
        func_002AB6D8((float *)position, (float *)rotation);
        if (object[0x95] == 3) {
            func_00282CF0(start, saved_position, *(char **)(data + 0x314) + 0x10);
            func_002AFDD8(*(char **)(data + 0x314), (char *)start, (char *)start, 0);
            start[2] = *(float *)(data + 0x318);
            func_00283098(start, start, *(char **)(data + 0x314) + 0xc0);
            *(float *)(data + 0x180) = start[2] + *(float *)(*(char **)(data + 0x314) + 0x18);
            if (*(float *)(object + 0x18) < *(float *)(data + 0x180))
                func_002A8F70(object, (unsigned int)D_0018C0B0, 0x10000, saved_position, D_001A8F20, 7.0f);
        }
    }
}
