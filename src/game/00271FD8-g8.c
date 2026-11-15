/* Select camera collision masks from the hero state, location and ground selectors. */
typedef struct {
    unsigned char a[0x80];
    float x, y;
    unsigned char b[0x2a8];
    float water;
    unsigned char c[0x1160];
    unsigned char flags[9];
    unsigned char d[0xdf7];
    int mode;
    int e;
    int state;
}
HeroView;
extern HeroView D_00189E20;
extern char D_001B53A0[];
extern int D_001B1510 __attribute__((section(".sdata")));
extern int D_001B1514 __attribute__((section(".sdata")));
extern int D_001B150C __attribute__((sda));
extern int D_001A79F0 __attribute__((section(".sdata")));
extern float D_001B5348[];
/* Updates the follow camera state from the hero state, setting the camera distance and related values by mode. */
void func_00271FD8(void) {
    HeroView *p = &D_00189E20;
    char *s = D_001B53A0;
    D_001B1510 = 20;
    if ((unsigned)(p->state-17)<2 || p->mode==112) D_001B1510 = 52;
    {
        HeroView *p2 = &D_00189E20;
        if (p2->state!=17 && p2->water<D_001B5348[0]) D_001B1510 = 20;
    }
    if (D_001A79F0==6) {
        HeroView *g = &D_00189E20;
        if (g->x>485.7f && g->x<570.7f && g->y>250.0f && g->y<334.5f) D_001B1510 = 52;
    }
    D_001B1514 = D_001B1510;
    D_001B1510 = D_001B1510|128;
    D_001B150C = 180;
    {
        HeroView *p4 = &D_00189E20;
        if (((unsigned char *)p4)[0x1495]) {
            *(int *)(s+0xc0) = 0x100;
            D_001B150C = 0x1b4;
        }
        else if (((unsigned char *)p4)[0x149b]) {
            *(int *)(s+0xc0) = 0xb00;
            D_001B150C = 0xbb4;
        }
        else if (((unsigned char *)p4)[0x1496]) {
            *(int *)(s+0xc0) = 0x300;
            D_001B150C = 0x3b4;
        }
        else if (((unsigned char *)p4)[0x149c]) {
            *(int *)(s+0xc0) = 0xd00;
            D_001B150C = 0xdb4;
        }
        else if (((unsigned char *)p4)[0x1494]) {
            *(int *)(s+0xc0) = 0;
            D_001B150C = 180;
        }
        else D_001B150C = *(int *)(s+0xc0)|180;
    }
}
