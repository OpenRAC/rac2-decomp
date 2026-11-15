#include "include_asm.h"
#include "names.h"

/* Selected-item prompt and panel; the model has 28-byte trailing records. */
typedef struct {
    char pad00[0x80];
    int index;
    int state;
    char pad88[0xBC];
    struct { int price; int rest[6]; } cells[0]; /* Variable-length trailing table. */
} UpgradeModel;
extern UpgradeModel D_L00_0022F7C0;
extern float D_L00_001B25E0 __attribute__((sda));
extern int D_001A79FC __attribute__((sda));
extern char D_L00_001AD788[7];
extern char D_L00_001AD790[5];
extern int func_00288FB8(int);
extern int func_0027FB40(int, int, unsigned long long, unsigned char *, int);
extern int func_0028E588(int, int);
extern void func_0028E868(int, int, int, int, int, int);

/* Draws the buy and back labels and the item picture and two text lines on the right of the panel. */
void func_L00_00378578(void) {
    UpgradeModel *model = &gPurchaseMenuModel;
    int index = model->index;
    if (model->state != 0) {
        if (model->cells[index].price <= D_001A79FC) {
            DrawTextCenteredMediumFont(438, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x113B), -1);
            DrawTextCenteredMediumFont(438, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x1138), -1);
        } else {
            DrawTextCenteredMediumFont(438, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                          (unsigned char *)GetLocalizedString(0x1124), -1);
        }
    } else {
        DrawTextCenteredMediumFont(438, (int)(D_L00_001B25E0 * 190.0f + 0.5f), 0x80F0F0F0ULL,
                      (unsigned char *)GetLocalizedString(0x1125), -1);
        DrawTextCenteredMediumFont(438, (int)(D_L00_001B25E0 * 214.0f + 0.5f), 0x80F0F0F0ULL,
                      (unsigned char *)GetLocalizedString(0x2D4F), -1);
    }
    DrawHudSprite(GetIconFrame(0xEAA8, 1), 402, (int)(D_L00_001B25E0 * 64.0f + 0.5f), 89,
                  (int)(D_L00_001B25E0 * 115.0f + 0.5f), 64);
    DrawTextCenteredMediumFont(445, (int)(D_L00_001B25E0 * 130.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)D_L00_001AD788, -1);
    DrawTextCenteredMediumFont(445, (int)(D_L00_001B25E0 * 148.0f + 0.5f), 0x80F0F0F0ULL,
                  (unsigned char *)D_L00_001AD790, -1);
}
