/* Current retained result, 1 November 2026: 3604/3604 bytes, not exact. Restore the actual integer return
 * of func_00288870 even though this caller discards it. The measured mode-3 allocation and loop-induction
 * differences remain.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G8 -ffunction-sections.
 * Earlier measurements below remain historical where superseded by this note.
 */
/*
 * Tier: Claude Opus 5.5 (xhigh), task v1807 (opus-1), 31 October 2026.
 * Best check.py: 3604/3604 bytes, 0 of 28 places, first difference at +0x150; 48
 * aligned rows differ once relocations are masked, nearly all from six causes.
 * Build it as its own unit, src/game/002F9BC0-preview-g8.c (default -O2 -G8
 * -ffunction-sections), in place of the INCLUDE_ASM marker. All declarations it
 * needs are below. PAL and US2: in neither catalogue. No link check was run.
 *
 * What this draft recovered, from the dumps (keep these):
 * - selectedPart[n++] with a counter, not a pointer: its address is a giv, which is
 *   what puts addiu $s4,$s3,0x54 in the preheader.
 * - Loop 2 hoists: the move_movables threshold measured here is 61 (it drops by 3 per
 *   move). Retail's second pass moves only 0x80000000 and 0x100, so N must be 56..58.
 *   N is 56 with `selected` set at the top of the body (life > 1, moved in pass 1)
 *   and the (unsigned short) cast on the id; one insn fewer also hoists `1` into $fp.
 *   Set drawMask first: it must precede `1` and the colour among the movables.
 * - flags before unk23: retail's lhu sits between the stores (the load cannot pass
 *   aliasing stores), which fixes the source order of that store group.
 * - `state` shared by the #7/#9 blocks (after the equipment loop, and in mode 0): as
 *   block-local pseudos they get $s0 from local-alloc, which gives the %hi pseudo an
 *   $s0 preference (set_preference on the lo_sum). regs_someone_prefers then blocks
 *   $s0 in pass 0 for every higher-priority pseudo. Sharing them removes it, and the
 *   mode-3 rows base, #5 and the parts base all fall into retail's $s0/$s0/$s4.
 * - D_001B2980[i] through one per-iteration pointer: a single giv, allocated before i.
 * - kind/value/armor as separate variables (one reused int gave wrong registers).
 * - D_001A8C20..58 and D_001A8B00 are macro (MACRO_ADDR) symbols: always-adjacent
 *   lui/addiu, one RTL insn, which also fixes the mode-1 delay slot (ld $s0).
 *
 * What still differs, with the mechanism where known:
 * 1. Mode-3 tail: retail has state $s0, moby $s1; here they are swapped, and the first
 *    block's $v0/$v1 are too. Cause: update_equiv_regs doubles the live length of a
 *    REG_EQUIV pseudo, so state scores 42/128 = 0.33 against moby's 27/49 = 0.55 and
 *    moby takes $s0 first. Fixing it needs state without the equivalence, or an $s0
 *    preference on state alone (on %hi it breaks the item above, because insn #3
 *    kills %hi and expand_preferences merges the two). Tried and worse: state shared
 *    with #3/#7/#9 (live 728), one variable for D_001B2980 and &D_0021F240.
 *    Once this is fixed, write the three tail stores as field9c, resourceActive,
 *    field90: that gives retail's 0x90, 0x9C, 0x8C order. With $s1 today that order
 *    cross-jumps onto the else arm's sw 0x8C($s1) and loses 8 bytes, so this draft
 *    keeps field90, field9c, resourceActive.
 * 2. First loop head (+0x150): retail does sll 8 before the addu of &classes.ids[n]
 *    and uses count $v0, objects $a1, address $a0; here $v1/$a0/$v0. Neither id-first
 *    nor an index local changed it.
 * 3. Mode 3 render/flags: $a1/$a2 swapped. Local-alloc takes the shortest range first;
 *    flags is one insn shorter than render, retail needs a tie (then pseudo order).
 *    Writing flags first swaps the registers correctly but breaks the insn order.
 * 4. D_001A7AF0 load: retail has it before the table's la; here sched2 delays it one
 *    cycle on its dependence on sw objectCount. Scalar sda goes through $gp (-8 bytes),
 *    nosda splits it through a temporary, `long` changed nothing. An untested idea is
 *    a scalar with an assembler -G0 profile; that may break the $gp names here.
 * 5. Bit 6 index: retail has dsrl $v0,$v0,5 + andi 2; here srl. Tried: unsigned long
 *    long casts inline (fold to srl/sra) and a 64-bit local (dsra 6). Needs a form
 *    keeping a DImode shift that combine still merges with the index scaling.
 * 6. addiu $s4,$s3,0x54 is two rows early: retail's order implies the giv is reduced
 *    in pass 2, after the hoists. Here `selected` moves in pass 1 and it reduces there.
 *    Without `selected` (index on state directly), state+84 is a pass-2 movable and
 *    N = 57 starves 0x100; N cannot reach the required 55 (56 at best, by count).
 *
 * No volatile, asm, register pins, do/while(0) or compiler changes are used.
 */
#include "common.h"

typedef struct { int id, kind, resource, value, extra, owned; } PreviewItem;
typedef struct { int id, resource, value; } PreviewArmor;
typedef struct { int mask, bits, value, unknown, text, price, extra; } PreviewEquipment;
typedef struct PreviewMoby PreviewMoby;
typedef struct {
    char pad[0x10]; unsigned char frames, unused11, unused12, triggers;
    char pad14[8]; unsigned int data[1];
} PreviewAnimation;
typedef struct { char pad[8]; unsigned char count; char gap[0x3F]; PreviewAnimation *anim[1]; } PreviewClass;
struct PreviewMoby {
    char pad00[0x20];
    unsigned char state, unk21, unk22, unk23;
    PreviewClass *pclass;
    int unk28;
    float scale;
    unsigned char opacity, render; unsigned short drawMask;
    unsigned short flags;
    char pad36[0xA];
    unsigned char frame, frame2, anim, anim2;
    char pad44[0x14];
    int animData, animData2;
    char pad60[2]; unsigned char unk62, unk63;
    char pad64[0x14];
    unsigned int color;
    short unk7c;
    char pad7e[0x1A];
    int unk98;
    char pad9c[0xE];
    short classId;
    char padac[0x44];
    int rotX, rotY;
    float rotZ;
    char padfc[4];
};
typedef struct {
    char pad00[0x1C]; int buffer;
    int animBuffers[2]; int unused28; PreviewMoby *objects;
    int unused30, objectCount;
    char pad38[0x14]; int equipment;
    int mode, selectedPart[2];
    char pad5c[0x14]; int previous;
    char pad74[0xC]; int selected, unused84, modelActive, resourceActive;
    int field90, unused94; float scale; int field9c;
    int fielda0, fielda4; float x, y, z;
    char padb4[0xC]; float position[4];
    char padd0[0x70];
    union { PreviewItem item[64]; PreviewArmor armor[128]; PreviewEquipment equipment[54]; int ammo[96][4]; } rows;
    int count, field744, field748, field74c, field750;
    char pad754[0xC];
} PreviewState;
typedef struct { int ids[5]; } PreviewClasses;
extern PreviewState D_0021F240;
extern PreviewClasses D_001AD500;
extern int D_001A7290[] MACRO_ADDR;
extern int D_001AD250[] SDATA(D_001AD250);
extern int D_001A8B00[] MACRO_ADDR;
extern int D_001A7AF0[] MACRO_ADDR;
extern short D_001A8C20[] MACRO_ADDR, D_001A8C28[] MACRO_ADDR, D_001A8C30[] MACRO_ADDR, D_001A8C38[] MACRO_ADDR, D_001A8C40[] MACRO_ADDR, D_001A8C48[] MACRO_ADDR, D_001A8C50[] MACRO_ADDR, D_001A8C58[] MACRO_ADDR;
extern float D_001B1390[] MACRO_ADDR;
typedef struct { float m[16]; } PreviewTransform;
extern PreviewTransform D_001B2980[];
extern float D_001A7C94[] MACRO_ADDR;
extern char D_001AD1D0[] SDATA(D_001AD1D0);
extern unsigned char D_001A7BB1;
typedef struct { char pad[0x370]; float x, y; } PreviewCamera;
extern PreviewCamera D_001B5200;
extern int D_00152C00[];
extern unsigned char D_00139568[];
typedef struct { char pad[0x46]; short text; char pad48[0x98]; } PreviewInfo;
extern PreviewInfo D_00239BA0[];
extern void func_002FB170(void), func_002F88D8(char *);
extern char *func_00288FB8(int);
extern void func_002923C0(void *), func_002926B8(int);
extern float func_00283248(float, float), func_00283B98(float, float), func_00283BE0(float, float);
extern void func_0029F0C8(void *, int), func_002A0468(void *, int, int, int, int);
extern void func_002A0F48(void *), func_0029F390(void *);
extern void func_00282A60(void *, int, int), func_0029F978(void *, unsigned int, void *);
extern void func_002A1130(void *, unsigned int, long long, unsigned int);
extern int func_00288870(void *, int, int);
extern short func_002B7CE0(int);
extern void func_00294BC8(int, int);

typedef char PreviewMobySize[(sizeof(PreviewMoby) == 0x100) ? 1 : -1];
typedef char PreviewStateSize[(sizeof(PreviewState) == 0x760) ? 1 : -1];

void func_002FB1A0(void)
{
    PreviewClasses classes;
    int parts[20] __attribute__((aligned(16)));
    PreviewInfo info;

    PreviewMoby *moby;
    PreviewState *state;
    int mode;
    float facing;
    if (D_0021F240.resourceActive) func_002FB170();
    mode = D_0021F240.mode;
    moby = D_0021F240.objects;
    D_0021F240.objectCount = 1;
    if (mode == 3) {
        D_0021F240.objectCount = 0;
        classes = D_001AD500;
        if (D_0021F240.rows.armor[D_0021F240.selected].value == 0) {
            func_002F88D8(func_00288FB8(0x3188));
        } else {
            if (D_001A7290[0] != D_0021F240.rows.armor[D_0021F240.selected].value)
                func_002923C0((void *)D_0021F240.rows.armor[D_0021F240.selected].value);
            func_002F88D8(func_00288FB8(D_001AD250[D_0021F240.rows.armor[D_0021F240.selected].value]));
        }
        facing = func_00283B98(func_00283248(D_001B5200.x, D_001B5200.y), 1.7453294f);
        while (classes.ids[D_0021F240.objectCount] >= 0) {
            PreviewMoby *moby = &D_0021F240.objects[D_0021F240.objectCount];
            func_0029F0C8(moby, classes.ids[D_0021F240.objectCount]);
            func_002A0468(moby, 0x202020, 14, 14, 0);
            moby->opacity = 0;
            moby->unk23 = 0;
            moby->state = 0;
            moby->unk98 = 0;
            moby->rotX = 0; moby->rotY = 0; moby->rotZ = 0;
            moby->color = 0x80808080;
            moby->drawMask = 64;
            moby->render = 1;
            moby->flags = 0x2010;
            moby->unk62 = 255;
            func_002A0F48(moby);
            moby->anim = 0; moby->anim2 = 0;
            func_0029F390(moby);
            if (D_001A7290[0]) moby->rotZ = facing;
            if (D_001A7290[0] == 4 && moby->classId == 0x50A) moby->flags |= 1;
            if (D_001A7290[0] >= 3 && moby->classId == 0xA73) moby->flags |= 1;
            D_0021F240.objectCount++;
        }
        func_00282A60(D_001B1390, 0, 0x40);
        func_0029F978(D_0021F240.objects, 24, D_001B1390);
        D_001B1390[10] = D_001A7C94[0];
        D_001B1390[9] = D_001B1390[8] = D_001A7C94[0] * 0.97f;
        if (D_001A7290[0] < 3) {
            int i;
            func_00282A60(&D_001B2980[0], 0, 0x40);
            func_00282A60(&D_001B2980[1], 0, 0x40);
            for (i = 0; i < 2; i++) {
                PreviewTransform *transform = &D_001B2980[i];
                func_0029F978(D_0021F240.objects, i + 22, transform);
                transform->m[8] = 0.01f;
                transform->m[9] = 0.01f;
                transform->m[10] = 0.01f;
            }
        }
        {
            PreviewMoby *moby = D_0021F240.objects;
            PreviewClass *pc = moby->pclass;
            PreviewAnimation *anim = pc->anim[moby->anim];
            if (anim->data[0] & 0xF0000000) {
                func_002A1130((char *)&anim->data[anim->frames] + anim->triggers * 4,
                             anim->data[moby->frame], D_0021F240.animBuffers[0], pc->count);
                moby->animData = D_0021F240.animBuffers[0];
            }
            pc = moby->pclass;
            anim = pc->anim[moby->anim2];
            if (anim->data[0] & 0xF0000000) {
                func_002A1130((char *)&anim->data[anim->frames] + anim->triggers * 4,
                             anim->data[moby->frame2], D_0021F240.animBuffers[1], pc->count);
                moby->animData2 = D_0021F240.animBuffers[1];
            }
        }
        D_0021F240.position[0] = -9.0f; D_0021F240.position[1] = 4.5f; D_0021F240.position[2] = -1.0f;
        D_0021F240.scale = 3.5f; D_0021F240.modelActive = 1;
        D_0021F240.field90 = 0; D_0021F240.field9c = 0; D_0021F240.resourceActive = 0;
    } else if (mode == 2) {
        int index = D_0021F240.selected;
        int kind;
        int value;
        int armor;
        D_0021F240.objectCount = 10;
        D_0021F240.equipment = (D_001A7AF0[0] & ~D_0021F240.rows.equipment[index].value) | D_0021F240.rows.equipment[index].unknown;
        parts[0] = D_001A8C20[D_0021F240.equipment & 3] << 16;
        if (D_0021F240.rows.equipment[index].value == 3) parts[0] |= 0x80000000;
        parts[1] = D_001A8C28[(D_0021F240.equipment & 12) >> 2] << 16;
        parts[2] = parts[1] | 0x8000;
        if (D_0021F240.rows.equipment[index].value == 12) { parts[1] |= 0x80000000; parts[2] |= 0x80000000; }
        parts[3] = D_001A8C50[(D_0021F240.equipment & 0xC00) >> 10] << 16;
        parts[4] = parts[3] | 0x8000;
        if (D_0021F240.rows.equipment[index].value == 0xC00) { parts[3] |= 0x80000000; parts[4] |= 0x80000000; }
        parts[5] = D_001A8C30[(D_0021F240.equipment & 0x30) >> 4] << 16;
        if (D_0021F240.rows.equipment[index].value == 0x30) parts[5] |= 0x80000000;
        parts[6] = D_001A8C38[((unsigned)D_0021F240.equipment >> 6) & 1] << 16;
        parts[7] = parts[6] | 0x8000;
        if (D_0021F240.rows.equipment[index].value == 0x40) { parts[6] |= 0x80000000; parts[7] |= 0x80000000; }
        parts[8] = D_001A8C48[(D_0021F240.equipment & 0x200) >> 9] << 16;
        parts[9] = parts[8] | 0x8000;
        if (D_0021F240.rows.equipment[index].value == 0x200) { parts[8] |= 0x80000000; parts[9] |= 0x80000000; }
        kind = (D_0021F240.equipment & 0x180) >> 7;
        if (kind) {
            int n = D_0021F240.objectCount;
            parts[n] = parts[n + 1] = D_001A8C40[kind] << 16;
            parts[n + 1] |= 0x8000;
            if (D_0021F240.rows.equipment[index].value == 0x180) {
                parts[n] |= 0x80000000;
                parts[n + 1] |= 0x80000000;
            }
            D_0021F240.objectCount += 2;
        }
        parts[D_0021F240.objectCount] = D_001A8C58[(D_0021F240.equipment & 0xC000) >> 14] << 16;
        if (D_0021F240.rows.equipment[index].value == 0xC000) parts[D_0021F240.objectCount] |= 0x80000000;
        D_0021F240.objectCount++;
        if (D_0021F240.equipment & 0x1000) {
            parts[D_0021F240.objectCount] = 0x10E20000;
            if (D_0021F240.rows.equipment[index].value == 0x1000) parts[D_0021F240.objectCount] = 0x90E20000;
            D_0021F240.objectCount++;
        }
        if (D_0021F240.equipment & 0x2000) {
            parts[D_0021F240.objectCount] = 0x10E40000;
            if (D_0021F240.rows.equipment[index].value == 0x2000) parts[D_0021F240.objectCount] = 0x90E40000;
            D_0021F240.objectCount++;
        }
        parts[D_0021F240.objectCount++] = 0x10E30000;
        D_0021F240.fielda4 = 0;
        value = D_0021F240.rows.equipment[index].value;
        if (value == 0xC00 || value == 0x200 || value == 12 || value == 3 || value == 0x40) {
            D_0021F240.x = 0.346f; D_0021F240.y = 0.3227f; D_0021F240.z = -0.7141964f;
        } else if (value == 0x30 || value == 0x2000) {
            D_0021F240.x = 0.0225f; D_0021F240.y = 0.0239f; D_0021F240.z = func_00283BE0(-3.0301f, 1.5707964f);
        } else if (value == 0x1000 || value == 0x180) {
            D_0021F240.x = -0.587f; D_0021F240.y = 0.165f; D_0021F240.z = 0.4842037f;
        } else if (value == 0x1F0000) {
            D_0021F240.x = (index & 1) ? 0.533f : 0.566f;
            D_0021F240.y = (index & 1) ? 0.3203f : 0.165f;
            D_0021F240.z = (index & 1) ? -0.90089637f : -0.13629639f;
        } else if (value == 0xC000) {
            D_0021F240.x = -0.5f; D_0021F240.y = -0.4f; D_0021F240.z = func_00283BE0(-2.1f, 1.5707964f);
        } else {
            D_0021F240.x = 0; D_0021F240.y = 0; D_0021F240.z = -1.5707964f;
        }
        {
            int i;
            int n = 0;
            D_0021F240.selectedPart[1] = D_0021F240.selectedPart[0] = -1;
            for (i = 0; i < D_0021F240.objectCount; i++) {
                PreviewState *loopState = &D_0021F240;
                int *selected = loopState->selectedPart;
                PreviewMoby *moby = &loopState->objects[i];
                func_0029F0C8(moby, (unsigned short)((unsigned)parts[i] >> 16) & 0x7FFF);
                func_002A0468(moby, 0x202020, 14, 14, 0);
                if ((unsigned)parts[i] & 0x80000000) selected[n++] = i;
                moby->drawMask = 0x100;
                moby->render = 1;
                moby->color = 0x80808080;
                moby->opacity = 0;
                moby->flags = (unsigned short)parts[i] | 0x2010;
                moby->unk23 = 255;
                moby->state = 0;
                moby->unk98 = 0;
                moby->scale = 1.0f;
                loopState->position[0] = -19.0f; loopState->position[1] = -2.0f; loopState->position[2] = 3.0f;
                loopState->scale = 1.0f;
                moby->rotX = 0; moby->rotY = 0; moby->rotZ = -1.5707964f;
                func_002A0F48(moby);
            }
        }
        state = &D_0021F240;
        state->modelActive = 1; state->field9c = 0; state->resourceActive = 0; state->field90 = 0;
        func_002F88D8(func_00288FB8(state->rows.equipment[state->selected].extra));
        armor = ((unsigned)state->equipment >> 16) & 0x1F;
        if (D_00152C00[12] != armor) func_002926B8(armor);
    } else if (mode == 0) {
        D_0021F240.field750 = 0;
        if (D_0021F240.rows.item[D_0021F240.selected].kind == 1) {
            func_0029F0C8(moby, 0xCDB);
            func_002A0468(moby, 0x202020, 14, 14, 0);
            moby->drawMask = 64; moby->color = 0x80808080; moby->flags = 0x2010;
            moby->render = 1; moby->opacity = 0; moby->unk23 = 0; moby->state = 0; moby->unk98 = 0; moby->unk7c = 1;
            D_0021F240.scale = 3.5f;
            qcopy(D_0021F240.position, D_001AD1D0);
            if (D_001A7BB1) D_0021F240.position[2] -= 0.55f;
            moby->rotX = 0; moby->rotY = 0; moby->rotZ = 0;
            D_0021F240.field9c = 0;
            func_002A0F48(moby);
            D_0021F240.modelActive = 1; D_0021F240.field90 = 0;
        } else {
            if (D_0021F240.rows.item[D_0021F240.selected].owned) {
                int special = 0;
                switch (D_0021F240.rows.item[D_0021F240.selected].id) {
                case 12: case 14: case 17: case 18: case 53: special = 1;
                }
                func_00288870(&info, D_0021F240.rows.item[D_0021F240.selected].id, special ? 1 : 2);
                func_002F88D8(func_00288FB8(info.text));
            } else {
                func_002F88D8(func_00288FB8((D_00139568[D_0021F240.rows.item[D_0021F240.selected].id] + D_00239BA0)->text));
            }
            func_002B7CE0(1);
            state = &D_0021F240;
            func_00294BC8(state->rows.item[state->selected].resource, state->buffer);
            state->resourceActive = 1; state->previous = state->selected; state->modelActive = 0;
        }
    } else if (mode == 1) {
        if (D_0021F240.count) {
            func_002F88D8(func_00288FB8(D_001A8B00[D_0021F240.rows.ammo[D_0021F240.selected][0]]));
            func_002B7CE0(1);
            func_00294BC8(D_0021F240.rows.ammo[D_0021F240.selected][3], D_0021F240.buffer);
            D_0021F240.resourceActive = 1; D_0021F240.previous = D_0021F240.selected; D_0021F240.modelActive = 0;
        }
    } else {
        D_0021F240.resourceActive = 0; D_0021F240.modelActive = 0;
    }
}
