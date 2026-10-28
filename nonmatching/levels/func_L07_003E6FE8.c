/* Retained meaningful C; not matching. 2026-10-28 default game G0 profile:
 * 600/600 bytes at the sole US place. Seven compiles establish an exact
 * prefix through+0x130, then swapped position/Euler cursors in s1/s0 versus
 * retail s0/s1. Shared cursor scope fixes the outer object/state allocation.
 * Separate incoming attached-object and new collision-object variables fix
 * the a1 argument lifetime; forming the actual hit base after the probe fixes
 * its address construction. An ordinary MACRO_ADDR early-base trial worsens
 * to608 bytes and was reverted. Narrow -fno-regmove and an early-return CFG
 * tie the final default object. No volatile or raw aliases were introduced.
 * AD0B0 retains its actual integer stored-address result; AD5F8, AD470 and
 * AD0E0 retain integer returns and complete six-pointer contracts. Direct
 * state extent is0x340, object extent0x100, local vectors16 bytes each and
 * hit-record direct read extent0x1c. Existing state Euler storage has16 bytes;
 * setup writes12 XYZ bytes, and later builders read the full existing slot.
 * No new uninitialized local Euler slot or synthetic initialization is used.
 * Reopen with a measured update-path cursor lifetime/coalescing witness.
 * US2/PAL and linked builds were not run for this near miss.
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
/* Three 16-byte local vectors are written completely by measured quadword
 * copies/difference transforms. The platform setup writes relative position
 * +0x310 for 16 bytes and Euler angles +0x320 for 12. The Euler padding word is not written here; downstream matrix
 * builders load its complete16-byte existing-state slot. No new local Euler
 * object or artificial zero store substitutes for that existing storage. */
void func_L07_003E6FE8(unsigned char *object)
{
    float start[4], end[4], delta[4];
    char *data = *(char **)(object + 0x68);
    char *position;
    char *attached = *(char **)(data + 0x338);
    if (!attached) {
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
            *(char **)(data + 0x338) = *(char **)(hit + 0x18);
            func_00282CF0(delta, position, *(char **)(data + 0x338) + 0x10);
            func_002AFDD8(*(char **)(data + 0x338), (char *)delta, (char *)delta, 0);
            *(float *)(data + 0x33c) = delta[2] - 1.0f;
            func_002AD5F8((char *)object, *(char **)(data + 0x338), position, (char *)object + 0xf0, data + 0x310, data + 0x320);
        }
        *(unsigned int *)(data + 0x88) |= 0x100;
        return;
    }
    {
        char *rotation;
        char *saved_position;
        if (object[0x20] == 9 || object[0x20] == 11) {
            position = (char *)object + 0x10;
            rotation = (char *)object + 0xf0;
            func_002AD470((char *)object, attached, data + 0x310, data + 0x320, position, rotation);
            saved_position = position;
        } else {
            position = (char *)object + 0x10;
            rotation = (char *)object + 0xf0;
            func_002AD0E0(object, attached, position, rotation, position, rotation);
            saved_position = position;
        }
        position = (char *)object + 0xc0;
        func_002833F0(position, rotation);
        func_002B0408(position, *(char **)(data + 0x338) + 0xe0, 0);
        func_002AB6D8((float *)position, (float *)rotation);
        if (*(unsigned short *)(object + 0x34) & 0x8000)
            func_00282D30(object + 0xd0, object + 0xd0, -1.0f);
        if (object[0x95] == 3) {
            func_00282CF0(start, saved_position, *(char **)(data + 0x338) + 0x10);
            func_002AFDD8(*(char **)(data + 0x338), (char *)start, (char *)start, 0);
            start[2] = *(float *)(data + 0x33c);
            func_00283098(start, start, *(char **)(data + 0x338) + 0xc0);
            *(float *)(data + 0x180) = start[2] + *(float *)(*(char **)(data + 0x338) + 0x18);
        }
    }
}
