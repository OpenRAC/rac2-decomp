/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G0 -ffunction-sections.
 * us: 09_dobbo: 1380 bytes, expected 1408; us2: 09_dobbo: 1380 bytes, expected 1408; pal: ABSENT.
 * Complete five-byte light-key interpolation, visibility release, owner/offset flags and handle
 * lifecycle. The 32-byte light row and all 16-byte vectors have their real extents. Invisible
 * lights release their existing handle before advancing the key. FP assignment, packed key reads
 * and store schedule differ.
 * Reopen: Independent key-field lifetime and FP interpolation source-order witness.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
typedef struct {u8 r,g,b,range,frames;} LightKey;
typedef struct {float red,green,blue,power;float position[4];} Light;
extern u8 *D_L09_001B285C NOT_SDA;
extern Light D_L09_001C7B80[];
extern int func_00282978(void *),func_00282948(void *),func_00283DB8(void *,float);
extern float func_00283CE0(int),func_002A7878(float,float);
extern void func_00291450(int),func_0029F338(void *),func_00282D30(void *,void *,float);
extern void func_00283098(void *,void *,void *),func_00282CC0(void *,void *,void *);
extern int func_L00_002FCF18(void *,float,float,float,float,float);

/* Advances the five-byte light-key sequence, interpolating its RGB/range and
 * tracking an optional owner transform. All copied vectors retain sixteen bytes.
 */
void func_L09_0039BA18(u8 *object)
{
    u8 *state,*owner;
    float sphere[4],origin[4],offset[4];
    LightKey *key,*next;
    float r,g,b,range,ratio,oldR,oldG,oldB,oldRange;
    int duration,handle,save;
    if (!object) return;
    state = P(object,0x68);
    if (!state) return;
    if (*(short *)(state+0x28) != -1 && func_00282978(state+0x28)) {
        handle = *(s8 *)(state+0x2E);
        if (handle != -1) func_00291450(handle);
        state[0x2E] = -1;
        func_0029F338(object);
        return;
    }
    switch (object[0x20]) {
    case 0:
        object[0x30] = 255;
        qcopy(state+0x10,object+0x10);
        I(state,0xC) = I(state,0x24);
        state[0x2E] = -1;
        if (I(state,0x20) != -1) P(state,0x34) = D_L09_001B285C + (I(state,0x20)<<8);
        state[0x2D] = 0;
        I(state,0x30) = state[0x2F];
        object[0x20] = 1;
        break;
    case 1:
        if (func_00282948(state+0x30)) object[0x20] = 2;
        break;
    case 2:
        key = (LightKey *)(state+0x38) + state[0x2D];
        oldR = func_00283CE0(key->r) * 0.01f;
        oldG = func_00283CE0(key->g) * 0.01f;
        oldB = func_00283CE0(key->b) * 0.01f;
        oldRange = func_00283CE0(key->range);
        duration = key->frames;
        ratio = func_00283CE0(I(state,0x30)) / func_00283CE0(duration);
        if (state[0x2C] < state[0x2D] + 1) {
            if (I(state,0x24) & 0x4000) next = (LightKey *)(state+0x38);
            else next = key;
        } else next = key + 1;
        r = func_00283CE0(next->r) * 0.01f;
        g = func_00283CE0(next->g) * 0.01f;
        b = func_00283CE0(next->b) * 0.01f;
        range = func_00283CE0(next->range);
        g = oldG + (g-oldG)*ratio;
        r = oldR + (r-oldR)*ratio;
        range = oldRange + (range-oldRange)*ratio;
        b = oldB + (b-oldB)*ratio;
        qcopy(sphere,object+0x10);
        sphere[3] = range;
        if (func_00283DB8(sphere,255.0f) != -1) {
            owner = P(state,0x34);
            if ((I(state,0x24) & 0x1000000) && owner && (H(owner,0x34)&1)) {
                handle = *(s8 *)(state+0x2E);
                if (handle != -1) func_00291450(handle);
                state[0x2E] = -1;
            } else {
                if (owner) qcopy(origin,owner+0x10);
                else qcopy(origin,state+0x10);
                if (!(I(state,0x24) & 0x800000)) {
                    if (I(state,0x24) & 0x100000) {
                        if (I(state,0x24) & 0x200000) {
                            offset[0] = func_002A7878(-F(state,0),F(state,0));
                            offset[1] = func_002A7878(-F(state,4),F(state,4));
                            offset[2] = func_002A7878(-F(state,8),F(state,8));
                        } else {
                            save = I(state,0xC); I(state,0xC) = 0;
                            func_00282D30(offset,state,func_002A7878(F(state,0xC),1.0f));
                            I(state,0xC) = save;
                        }
                    } else {
                        save = I(state,0xC); I(state,0xC) = 0;
                        qcopy(offset,state);
                        I(state,0xC) = save;
                    }
                    if ((I(state,0x24)&0x400000) && P(state,0x34))
                        func_00283098(offset,offset,P(state,0x34)+0xC0);
                    func_00282CC0(object+0x10,origin,offset);
                } else qcopy(object+0x10,origin);
                handle = *(s8 *)(state+0x2E);
                if (handle == -1) {
                    state[0x2E] = func_L00_002FCF18(object+0x10,range,
                        func_00283CE0(state[0x2A])*0.01f,r,g,b);
                } else {
                    Light *light = &D_L09_001C7B80[handle];
                    qcopy(light->position,object+0x10);
                    light->position[3] = range;
                    light->red = r; light->green = g; light->blue = b;
                    light->power = func_00283CE0(state[0x2A])*0.01f;
                }
            }
        } else {
            handle = *(s8 *)(state+0x2E);
            if (handle != -1) func_00291450(handle);
            state[0x2E] = -1;
        }
        I(state,0x30)++;
        if (I(state,0x30) >= duration) {
            I(state,0x30) = 0;
            state[0x2D]++;
            if (state[0x2C] < state[0x2D]) {
                if (I(state,0x24)&0x4000) state[0x2D] = 0;
                else object[0x20] = 3;
            }
        }
        break;
    case 3:
        handle = *(s8 *)(state+0x2E);
        if (handle != -1) func_00291450(handle);
        state[0x2E] = -1; func_0029F338(object);
        break;
    }
}
