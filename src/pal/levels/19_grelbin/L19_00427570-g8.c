/* func_PAL_L19_00427570, the PAL copy of func_L19_00421E80: the same behaviour, where the first
   countdown becomes ((x + 60) * 5 + 2) / 6 and its 60 becomes 50. The division's trap check keeps
   stores from crossing it, so the setup here runs in field order. */
typedef unsigned char u8;
/* The resident position is copied as a complete 16-byte vector elsewhere. */
extern float D_00189EA0[4];
typedef struct { u8 prefix[0x160]; float strength; u8 unknown164[4]; int ticks,mode; } CameraShakeView;
extern CameraShakeView D_L19_001B9900;
extern void func_002A7750(u8 *,u8,int);
extern int func_002ACBC8(void *,int);
extern int func_002B3868(u8 *);
extern int func_002E5CF8(int,int,char *);
extern int func_00282948(int *);
extern float func_002AA548(float *,float *,float,float,float,float);
extern float func_00282C48(float);
extern void func_L19_00422238(void *);

/* Trigger the rise, wait and fall cycle while maintaining the attached effects. */
void func_PAL_L19_00427570(u8 *object)
{
    char *state=*(char **)(object+0x68);
    switch(object[0x20]) {
    case 0:
        *(int *)(state+0x0C)=0;
        *(float *)(state+0x10)=0.55f;
        *(float *)(state+0x14)=0.01f;
        *(float *)(state+0x18)=0.05f;
        *(int *)(state+0x1C)=((*(int *)(state+0x5C)+60)*5+2)/6;
        *(int *)(state+0x20)=50;
        *(int *)(state+0x24)=0;
        *(float *)(state+0x28)=1.0f;
        *(int *)(state+0x2C)=3;
        *(float *)(state+0x30)=105000.0f;
        *(unsigned int *)(state+0x34)=0x80803C14;
        *(unsigned int *)(state+0x38)=0x60400000;
        *(int *)(state+0x3C)=10;
        *(int *)(state+0x40)=55;
        *(int *)(state+0x44)=1;
        *(float *)(state+0x48)=210000.0f;
        *(unsigned int *)(state+0x4C)=0x80808080;
        *(unsigned int *)(state+0x50)=0x40804040;
        *(int *)(state+0x54)=0;
        *(int *)(state+0x58)=40;
        func_002A7750(object,1,-1);
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0,*(int *)state)) func_002A7750(object,2,-1);
        break;
    case 2:
        if (func_002B3868(object)) func_002E5CF8(0,0,(char *)object);
        if (func_00282948((int *)(state+0x1C))) func_002A7750(object,3,-1);
        *(float *)(state+0x24)+=(float)(60-*(int *)(state+0x1C))*0.25f;
        break;
    case 3:
        if (*(float *)(object+0x18)<*(float *)(state+8)) func_002A7750(object,4,-1);
        *(float *)(state+0x24)+=1.5f;
        func_002AA548((float *)(object+0x18),(float *)(state+0x0C),
            *(float *)(state+8)-20.0f,*(float *)(state+0x14),99999.0f,*(float *)(state+0x10));
        break;
    case 4:
        if (func_002B3868(object)) {
            func_002E5CF8(1,0,(char *)object);
            D_L19_001B9900.strength=1.0f;
            D_L19_001B9900.ticks=20;
            D_L19_001B9900.mode=0;
        }
        if (func_00282C48((*(float *)(object+0x18)-*(float *)(state+8))+*(float *)(state+0x28))<0.03f)
            func_002A7750(object,5,-1);
        func_002AA548((float *)(object+0x18),(float *)(state+0x0C),
            *(float *)(state+8)-*(float *)(state+0x28),99999.0f,*(float *)(state+0x18),*(float *)(state+0x10));
        break;
    case 5:
        break;
    }
    func_L19_00422238(object);
}
