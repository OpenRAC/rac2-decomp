typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef struct { u32 items[5]; } NativeTable20;
extern const NativeTable20 LVL_7_SIBERIUS_D_001A8EB0;
void LVL_7_SIBERIUS_FUN_002CD8F0(s32 *object) {
    object[0]=0; object[1]=0; object[2]=0; object[3]=0; object[4]=0;
}
u32 LVL_7_SIBERIUS_FUN_002E9FF0(s32 index) {
    NativeTable20 values=LVL_7_SIBERIUS_D_001A8EB0;
    return values.items[index];
}

u32 LVL_7_SIBERIUS_FUN_002ACDF0(u8 *object,u32 value) {
    if(value==255) value=object[0xa9];
    return value;
}

extern u32 LVL_7_SIBERIUS_D_0018C0B4;
u32 LVL_7_SIBERIUS_FUN_002CC898(void) {
    return LVL_7_SIBERIUS_D_0018C0B4;
}

s32 LVL_7_SIBERIUS_FUN_002D9AC8(f32 a,f32 b,f32 t) {
 f32 difference=b-a;
 f32 squared=t*t;
 a=a*t;
 difference=difference*squared;
 a=a+difference;
 return (s32)a;
}

extern u8 LVL_7_SIBERIUS_D_00189E20[];

typedef struct {
    u8 prefix[0x1220];
    u32 field1220;
    u8 gap[0x20];
    s32 field1244, field1248;
} NativeIndexedFieldsView;

u32 LVL_7_SIBERIUS_FUN_002ACC88(s32 index) {
 NativeIndexedFieldsView *p=(NativeIndexedFieldsView *)((u8 *)&LVL_7_SIBERIUS_D_00189E20+index*0x50);
 if(p->field1244==2) return p->field1220;
 return 0;
}

s32 LVL_7_SIBERIUS_FUN_002ACCC0(s32 index) {
 NativeIndexedFieldsView *p=(NativeIndexedFieldsView *)((u8 *)&LVL_7_SIBERIUS_D_00189E20+index*0x50);
 if(p->field1244==2) return p->field1248;
 return -1;
}

s32 LVL_7_SIBERIUS_FUN_002AD8E0(s32 value) {
 switch(value) {case 1:return 0x72;case 2:return 0x70;case 3:return 0x6e;default:return 0;}
}

/* Frozen Batch A A01-shared-108; acknowledged claim 8fc9d5f80b3d5f44a785f41c0f987dca4231aa565dd750932d09299d0bf9e9c4. */
typedef int BatchA_A01_s32;

extern BatchA_A01_s32 BatchA_A01_D_001A7B90;
extern BatchA_A01_s32 BatchA_A01_D_001A7BB8 __attribute__((sda));
extern BatchA_A01_s32 BatchA_A01_FUN_00124418(void);
extern BatchA_A01_s32 BatchA_A01_FUN_001257D0(BatchA_A01_s32, BatchA_A01_s32, BatchA_A01_s32, BatchA_A01_s32);

void LVL_7_SIBERIUS_FUN_002E5838(void) {
    BatchA_A01_FUN_00124418();
    if (BatchA_A01_D_001A7B90 != 0) BatchA_A01_D_001A7BB8 = 0;
    if (*(BatchA_A01_s32 *)0x001a7bb8 != 0) BatchA_A01_FUN_001257D0(0,0,0x50,1);
    else BatchA_A01_FUN_001257D0(0,1,BatchA_A01_D_001A7B90 != 0 ? 3 : 2,0);
}

/* Frozen Batch A A02-list-add-88; acknowledged claim 38ceeb041b6ba12996de10c402ca54295587db96246845b83b2ec894986b096f. */
typedef unsigned char BatchA_A02_u8;
typedef int BatchA_A02_s32;
typedef struct { char _0[0x10]; BatchA_A02_u8 n; char _11[3]; BatchA_A02_s32 off; char _18[4]; BatchA_A02_s32 ent[1]; } BatchA_A02_Blk;
void LVL_7_SIBERIUS_FUN_002F5310(int *a0, int a1){
  BatchA_A02_Blk *r;
  int i;
  a0 += a1;
  r = *(BatchA_A02_Blk **)((char *)a0 + 0x48);
  if (r->off) r->off = (int)r + r->off;
  for (i = 0; i < r->n; i++) r->ent[i] = (int)r + r->ent[i];
}

/* Frozen Batch A A03-counter-mod50-80; acknowledged claim b5e8cf533fd3cee3cb2dcdd0bf7be9549f6cc39cd932c589176487a8b170abee. */
typedef int BatchA_A03_s32;
extern BatchA_A03_s32 BatchA_A03_D_001A8FE0[] __attribute__((sda));
extern BatchA_A03_s32 BatchA_A03_D_001A7BC0[] __attribute__((sda));
extern BatchA_A03_s32 BatchA_A03_D_001A7B90[] __attribute__((sda));
void LVL_7_SIBERIUS_FUN_0034E590(void)
{
    if (BatchA_A03_D_001A8FE0[0] == 0) {
        BatchA_A03_s32 n = BatchA_A03_D_001A7BC0[0] + 1;
        BatchA_A03_D_001A7BC0[0] = n;
        if (n % 50 == 0) {
            if (BatchA_A03_D_001A7B90[0]) {
                BatchA_A03_D_001A7BC0[0] = n + 10;
            }
        }
    }
}

/* Frozen Batch A A05-store-rotation-52; acknowledged claim 43a7518b17439f6bdc9390be9d4164b47eec4bed94a72d581fdec3b883b0a554. */
typedef unsigned char BatchA_A05_u8;
typedef unsigned short BatchA_A05_u16;
typedef short BatchA_A05_s16;
typedef unsigned int BatchA_A05_u32;
typedef int BatchA_A05_s32;
typedef float BatchA_A05_f32;
typedef short BatchA_A05_BatchAs16;
typedef unsigned short BatchA_A05_BatchAu16;
typedef struct { BatchA_A05_u8 b[0x50]; BatchA_A05_BatchAs16 f50; BatchA_A05_BatchAs16 f52; BatchA_A05_u8 c[0x20]; BatchA_A05_BatchAs16 f74; BatchA_A05_BatchAs16 f76; BatchA_A05_u8 d[0x20]; BatchA_A05_BatchAs16 f98; BatchA_A05_BatchAs16 f9a; } BatchA_A05_BatchA52;
extern BatchA_A05_BatchA52 BatchA_A05_BatchA_D001A63A8;
void LVL_7_SIBERIUS_FUN_00324478(BatchA_A05_s32 a0) {
    if (a0 != 0) { BatchA_A05_BatchA_D001A63A8.f76 = 0; BatchA_A05_BatchA_D001A63A8.f74 = -0x8000; }
    BatchA_A05_BatchA_D001A63A8.f9a = 0;
    BatchA_A05_BatchA_D001A63A8.f50 = -0x8000;
    BatchA_A05_BatchA_D001A63A8.f52 = 0;
    BatchA_A05_BatchA_D001A63A8.f98 = -0x8000;
}

/* Frozen Batch A A06-inline-init-40; acknowledged claim f87e1c08ece3f12938d297032a913cd328169b7754a3ddd6dc5186c16697eb73. */
typedef unsigned char BatchA_A06_u8;
typedef unsigned short BatchA_A06_u16;
typedef short BatchA_A06_s16;
typedef unsigned int BatchA_A06_u32;
typedef int BatchA_A06_s32;
typedef float BatchA_A06_f32;
typedef short BatchA_A06_BatchAs16;
typedef unsigned short BatchA_A06_BatchAu16;
void LVL_7_SIBERIUS_FUN_00318CC0(void *a0, char *a1){
    if (*(BatchA_A06_s32 *)(a1 + 0x14C) == 0) {
        *(void **)(a1 + 0x144) = a0;
        *(BatchA_A06_s32 *)(a1 + 0x14C) = 1;
        *(BatchA_A06_BatchAs16 *)(a1 + 0x142) = 0;
        *(BatchA_A06_s32 *)(a1 + 0x148) = 0;
        *(BatchA_A06_BatchAs16 *)(a1 + 0x140) = 0;
    }
}

/* Frozen Batch A A07-sda-multi-eq-44; acknowledged claim 6adc81ebaa8d8c8d04aa1aa3c8950e1d91861a258898c3cce6be7f792e8bdcf3. */
typedef unsigned char BatchA_A07_u8;
typedef unsigned short BatchA_A07_u16;
typedef short BatchA_A07_s16;
typedef unsigned int BatchA_A07_u32;
typedef int BatchA_A07_s32;
typedef float BatchA_A07_f32;
typedef short BatchA_A07_BatchAs16;
typedef unsigned short BatchA_A07_BatchAu16;
extern BatchA_A07_s32 BatchA_A07_BatchA_D001A79F0a[] __attribute__((sda));
BatchA_A07_s32 LVL_7_SIBERIUS_FUN_002CC7F8(void) {
    BatchA_A07_s32 v = BatchA_A07_BatchA_D001A79F0a[0];
    return (v == 0x16) | (v == 0x2CE) | (v == 0x17);
}

/* Frozen Batch A A08-sda-offset-40; acknowledged claim 1c862bca494fc9285ae124fddbbb78dd145686c54c3afa751addc9271a2f8b70. */
typedef unsigned char BatchA_A08_u8;
typedef unsigned short BatchA_A08_u16;
typedef short BatchA_A08_s16;
typedef unsigned int BatchA_A08_u32;
typedef int BatchA_A08_s32;
typedef float BatchA_A08_f32;
typedef short BatchA_A08_BatchAs16;
typedef unsigned short BatchA_A08_BatchAu16;
extern BatchA_A08_s32 BatchA_A08_BatchA_D001A904C[] __attribute__((sda));
void LVL_7_SIBERIUS_FUN_00302BF0(BatchA_A08_s32 a0, BatchA_A08_s32 a1) {
    BatchA_A08_s32 base = BatchA_A08_BatchA_D001A904C[0];
    BatchA_A08_s32 *p;
    if (base == 0) return;
    p = (BatchA_A08_s32 *)(base + 0x38000);
    p[0x7368/4] = a0;
    p[0x736C/4] = a1;
}

/* Frozen Batch A A11-sda-3store-28; acknowledged claim 9b61d4cdd097ce0a56790793fdd6c129d3f0d822e40e788cde17e6418bdea65f. */
typedef unsigned char BatchA_A11_u8;
typedef unsigned short BatchA_A11_u16;
extern BatchA_A11_u8 BatchA_A11_D_001A63A8[];
void LVL_7_SIBERIUS_FUN_003244B0(void) {
    BatchA_A11_u8 *p = BatchA_A11_D_001A63A8;
    *(BatchA_A11_u16 *)(p + 0x50) = 4;
    *(BatchA_A11_u16 *)(p + 0x98) = 4;
    *(BatchA_A11_u16 *)(p + 0x74) = 4;
}

/* Frozen Batch A A13-eq-getter-20; acknowledged claim 88eaf851f31627d1562797f83f79f60446fca428598034e69d6748fe46ec5a79. */
typedef unsigned char BatchA_A13_u8;
typedef unsigned short BatchA_A13_u16;
typedef short BatchA_A13_s16;
typedef unsigned int BatchA_A13_u32;
typedef int BatchA_A13_s32;
typedef float BatchA_A13_f32;
typedef short BatchA_A13_BatchAs16;
typedef unsigned short BatchA_A13_BatchAu16;
extern unsigned int BatchA_A13_BatchA_D001A79F0b[] __attribute__((sda));
unsigned int LVL_7_SIBERIUS_FUN_002CC6C0(void) { return BatchA_A13_BatchA_D001A79F0b[0] == 0x19u; }

/* Frozen Batch A A14-struct-2field-20; acknowledged claim 3e0e0bb01b3da304ddd50c7212de48bebcbf96d3b2d117369779044d96f69b21. */
typedef unsigned int BatchA_A14_u32;
typedef struct { unsigned char pad[0x2494]; BatchA_A14_u32 a; BatchA_A14_u32 b; } BatchA_A14_S;
extern BatchA_A14_S BatchA_A14_D_00189E20;
void LVL_7_SIBERIUS_FUN_002C7F50(void) {
    BatchA_A14_D_00189E20.a = 0;
    BatchA_A14_D_00189E20.b = 0;
}

/* Frozen Batch A A16-sda-byte-16; acknowledged claim 3b1980407c8765dd4baf122f505692e49c411cbff6089e896e8b3921ce208b41. */
typedef unsigned char BatchA_A16_u8;
typedef unsigned short BatchA_A16_u16;
typedef short BatchA_A16_s16;
typedef unsigned int BatchA_A16_u32;
typedef int BatchA_A16_s32;
typedef float BatchA_A16_f32;
typedef short BatchA_A16_BatchAs16;
typedef unsigned short BatchA_A16_BatchAu16;
extern BatchA_A16_u8 BatchA_A16_BatchA_D001A7A0A[] __attribute__((sda));
int LVL_7_SIBERIUS_FUN_002EA5E0(void) { return BatchA_A16_BatchA_D001A7A0A[0] != 0; }

extern void LVL_7_SIBERIUS_FUN_002CD648(f32, f32, f32, f32, s32, s32);

void LVL_7_SIBERIUS_FUN_002CD0F0(u8 *object) {
 object[0x1d]=0;
 if (*(f32 *)(object+0x10)>=0.0f)
  LVL_7_SIBERIUS_FUN_002CD648(1.1243411302566528f,0.005f,0.2f,0.0f,0,3);
}

/* Scalar GS setup wrapper; pinned standard integer arguments and helper calls. */
extern void LVL_7_SIBERIUS_FUN_002E6848(int width, int height, int address, int mode);
extern void LVL_7_SIBERIUS_FUN_003715E0(unsigned int reg, unsigned long value);
extern void LVL_7_SIBERIUS_FUN_002E6BB0(int width, int height);

void LVL_7_SIBERIUS_FUN_002DB868(int width, int height)
{
    int sum = width + height;
    int address;

    if (sum > 16)
        sum = 16;
    address = 0x3ff000 - (4 << sum);
    address = (address >> 13) << 13;
    LVL_7_SIBERIUS_FUN_002E6848(width, height, address, 1);
    LVL_7_SIBERIUS_FUN_003715E0(0x47, 0x30000UL);
    LVL_7_SIBERIUS_FUN_003715E0(0x42, 0x8000000044UL);
    LVL_7_SIBERIUS_FUN_002E6BB0(0x100, 0x100);
    LVL_7_SIBERIUS_FUN_003715E0(0x42, 0x8000000044UL);
}

s32 LVL_7_SIBERIUS_FUN_002ACCF8(s32 index) {
 s32 value=LVL_7_SIBERIUS_FUN_002ACCC0(index);
 if(value==12 || value==17) return 1;
 return 0;
}

s32 LVL_7_SIBERIUS_FUN_002ACD30(s32 index) {
 return LVL_7_SIBERIUS_FUN_002ACCC0(index)==47;
}

s32 LVL_7_SIBERIUS_FUN_002B1FE0(u8 *object) {
 if(object==0) return 0;
 return *(short *)(object+0xaa)==71;
}

/* Update the measured fields of the first matching key among13records. */
typedef struct { unsigned int fields[25]; int key; unsigned int busy; unsigned int tail[9]; } UpdateRecord;
typedef char UpdateRecordSize[(sizeof(UpdateRecord) == 144) ? 1 : -1];
extern UpdateRecord LVL_7_SIBERIUS_D_0027E030[13];
void LVL_7_SIBERIUS_FUN_002ED0F8(int key, unsigned int value)
{
    int i;
    for (i = 0; i < 13; i++) {
        if (LVL_7_SIBERIUS_D_0027E030[i].key == key) break;
    }
    if (i < 13) {
        LVL_7_SIBERIUS_D_0027E030[i].fields[9] = value;
        if (LVL_7_SIBERIUS_D_0027E030[i].busy == 0)
            LVL_7_SIBERIUS_D_0027E030[i].fields[1] = value;
    }
}

typedef struct {
    u8 prefix[0xa7];
    u8 fielda7;
} OrbitalBitmapView;
extern u8 LVL_7_SIBERIUS_D_001395B8[];
u32 LVL_7_SIBERIUS_FUN_002FBCF0(s32 index) {
    s32 slot=index/8;
    u32 bit=index%8;
    u32 previous=0;
    if(bit<8) {
        OrbitalBitmapView *state=(OrbitalBitmapView *)(LVL_7_SIBERIUS_D_001395B8+slot);
        previous=((s32)state->fielda7>>bit)&1;
    }
    return previous;
}

typedef struct {
    u32 field00,field04;
    s32 field08;
    u8 gap0c[4];
} OrbitalPairTableView16;
extern u8 LVL_7_SIBERIUS_D_00231780[];
s32 LVL_7_SIBERIUS_FUN_00373EC0(u32 key,u32 owner) {
    OrbitalPairTableView16 *entry=(OrbitalPairTableView16 *)LVL_7_SIBERIUS_D_00231780;
    s32 checked=0;
    do {
        ++checked;
        if(entry->field04==key && entry->field00==owner) return entry->field08;
        ++entry;
    } while(checked<32);
    return -1;
}

/* Apply nonzero signed halfword overrides to indexed rows of selected objects. */
typedef struct {
    unsigned int first;
    unsigned char reserved04[0x1c];
    unsigned int second;
    unsigned char reserved24[0x0f];
    unsigned char key;
    unsigned char reserved34[0x1c];
} ListOverrideRow;
typedef struct {
    unsigned char reserved00[0x0f];
    unsigned char count;
    unsigned char reserved10[0x0c];
    ListOverrideRow *rows;
} ListOverrideObject;
typedef struct { short first; short second; } ListOverridePair;
extern int LVL_7_SIBERIUS_D_0022E040[];
extern ListOverrideObject *LVL_7_SIBERIUS_D_00226B40[];
extern ListOverridePair LVL_7_SIBERIUS_D_0022DA40[];
void LVL_7_SIBERIUS_FUN_00360CD0(void)
{
    int *selected = LVL_7_SIBERIUS_D_0022E040;
    while (*selected >= 0) {
        ListOverrideObject *object = LVL_7_SIBERIUS_D_00226B40[*selected];
        int i = 0;
        ListOverrideRow *row = object->rows;
        while (i < object->count) {
            ListOverridePair *pair = &LVL_7_SIBERIUS_D_0022DA40[row->key];
            if (pair->first != 0)
                row->first = (row->first & 0xffffc000u) | pair->first;
            if (pair->second != 0)
                row->second = (row->second & 0xffffc000u) | pair->second;
            i++;
            row++;
        }
        selected++;
    }
}

/* Finds the first matching object in the thirty resident records. */
typedef struct {
    u8 field00[0x14];
    void *field14;
    u8 field18[8];
} NativeObjectSearchRecord32;
extern NativeObjectSearchRecord32 LVL_7_SIBERIUS_D_002537F0[];
s32 LVL_7_SIBERIUS_FUN_003E42E0(void *object) {
    s32 result = -1;
    s32 index;
    for (index = 0; index < 30; index++) {
        if (LVL_7_SIBERIUS_D_002537F0[index].field14 == object) {
            result = index;
            break;
        }
    }
    return result;
}

typedef struct { u8 prefix[0xaa]; short class_id; } ClassFilterObject;
typedef struct {
    u8 prefix[0x33c];
    ClassFilterObject *fallback;
    u8 middle[0x14f0];
    ClassFilterObject *primary;
    u8 trailing[0xa60];
    s32 mode;
} ClassFilterRoot;

s32 LVL_7_SIBERIUS_FUN_002CC758(s32 selection) {
    s32 found = 0;
    ClassFilterObject *primary = ((ClassFilterRoot *)LVL_7_SIBERIUS_D_00189E20)->primary;
    ClassFilterObject *fallback = ((ClassFilterRoot *)LVL_7_SIBERIUS_D_00189E20)->fallback;
    if (((ClassFilterRoot *)LVL_7_SIBERIUS_D_00189E20)->mode == 0x31) {
        if (primary) {
            switch (selection) {
                case 0: found = primary->class_id == 0xfbf; break;
                case 1: found = primary->class_id == 0x905; break;
                case 2: found = primary->class_id == 0xeef; break;
            }
        } else if (fallback && selection == 3) {
            found = fallback->class_id == 0xc20;
        }
    }
    return found;
}

/* Select one of three measured pointer slots for the requested kind. */
extern void *LVL_7_SIBERIUS_D_0018C0B0;
extern void *LVL_7_SIBERIUS_D_0018B134;
extern void *LVL_7_SIBERIUS_D_0018B040;
void *LVL_7_SIBERIUS_FUN_002A55C0(int kind)
{
    if (kind == 0 || kind == 2 || kind == 3 || kind == 4 || kind == 5)
        return LVL_7_SIBERIUS_D_0018C0B0;
    if (kind == 1)
        return LVL_7_SIBERIUS_D_0018B134;
    if (kind == 6)
        return LVL_7_SIBERIUS_D_0018B040;
    return 0;
}

/* Find a mapped record by its unsigned halfword class and return its opaque word. */
typedef struct {
    unsigned int marker;
    unsigned char reserved04[0x38];
    unsigned short class_code;
    unsigned char reserved3E[0xa2];
} MappedClassEntry;
typedef char MappedClassStride[(sizeof(MappedClassEntry) == 0xe0) ? 1 : -1];
extern unsigned char LVL_7_SIBERIUS_D_00139568[];
extern MappedClassEntry LVL_7_SIBERIUS_D_002628A0[];
unsigned int LVL_7_SIBERIUS_FUN_002E9CC8(unsigned int key)
{
    int i;
    for (i = 0; i < 56; i++) {
        MappedClassEntry *record = &LVL_7_SIBERIUS_D_002628A0[LVL_7_SIBERIUS_D_00139568[i]];
        if (record->class_code == key)
            return record->marker;
    }
    return 0;
}

/* Relocates serialized header offsets and compacts each row in its original storage. */
typedef unsigned long long NativeCompactU64;
typedef union {
    s32 field00[4];
    struct {
        NativeCompactU64 field00;
        short field08;
        short field0A;
        unsigned short field0C;
        unsigned short field0E;
    } compact;
} NativeCompactRow16;
typedef struct {
    u8 field00[6];
    short field06;
    u8 field08[4];
    f32 field0C;
    u32 field10;
    u32 field14;
    u32 field18;
    u32 field1C;
    u32 field20;
} NativeCompactHeader;
extern s32 LVL_7_SIBERIUS_FUN_002E4050(s32 value);
NativeCompactHeader *LVL_7_SIBERIUS_FUN_00376220(NativeCompactHeader *header) {
    u32 base = (u32)header;
    NativeCompactRow16 *source;
    s32 index;
    header->field10 += base;
    header->field14 += base;
    header->field18 += base;
    header->field1C += base;
    if (header->field20 != 0) header->field20 += base;
    index = 0;
    source = (NativeCompactRow16 *)header->field18;
    header->field0C *= 0.0032116016f;
    if (header->field06 > 0) {
        do {
            s32 first = source->field00[0];
            s32 second = source->field00[1];
            s32 third = source->field00[2];
            s32 fourth = source->field00[3];
            ((NativeCompactRow16 *)header->field18)[index].compact.field0A = first >> 4;
            source++;
            ((NativeCompactRow16 *)header->field18)[index].compact.field08 = second >> 4;
            ((NativeCompactRow16 *)header->field18)[index].compact.field0C = LVL_7_SIBERIUS_FUN_002E4050(third);
            ((NativeCompactRow16 *)header->field18)[index].compact.field0E = LVL_7_SIBERIUS_FUN_002E4050(fourth);
            ((NativeCompactRow16 *)header->field18)[index].compact.field00 = 0;
            index++;
        } while (index < header->field06);
    }
    return header;
}

extern s32 LVL_7_SIBERIUS_D_001A79F0;
s32 LVL_7_SIBERIUS_FUN_002CC6D8(void) {
    s32 found = 0;
    if (LVL_7_SIBERIUS_D_001A79F0 == 25 || LVL_7_SIBERIUS_D_001A79F0 == 5 ||
        LVL_7_SIBERIUS_D_001A79F0 == 10 || LVL_7_SIBERIUS_D_001A79F0 == 15) {
        found = 1;
    }
    return found;
}

typedef struct {
    u8 field0;
    u8 active;
    u8 middle[4];
    unsigned short count;
    u8 trailing[8];
} ConditionalResetSlot;
typedef char ConditionalResetSlotSize[(sizeof(ConditionalResetSlot) == 16) ? 1 : -1];
extern ConditionalResetSlot LVL_7_SIBERIUS_D_001B9040[8];
void LVL_7_SIBERIUS_FUN_002CCB20(void) {
    ConditionalResetSlot *slot = LVL_7_SIBERIUS_D_001B9040;
    s32 remaining = 7;
    do {
        if (slot->active) {
            slot->active = 0;
            slot->count = 0;
        }
        --remaining;
        ++slot;
    } while (remaining >= 0);
}

typedef struct {
    u8 prefix[0x40];
    s32 mode;
    u8 between[0x14];
    s32 state;
} StateTransitionView;
typedef char StateTransitionViewSize[(sizeof(StateTransitionView) == 0x5c) ? 1 : -1];
extern StateTransitionView LVL_7_SIBERIUS_D_001BF340;
void LVL_7_SIBERIUS_FUN_002E9630(void) {
    if (LVL_7_SIBERIUS_D_001BF340.mode == 7 && LVL_7_SIBERIUS_D_001BF340.state == 1) {
        LVL_7_SIBERIUS_D_001BF340.state = 2;
    }
}

/* Substitute the first percent selector in a record's localized text. */
typedef struct {
    unsigned char gap0[10];
    short text_id;
    short mapped_key;
    unsigned char gap0e[26];
} DobboFormatRow396;
typedef struct {
    unsigned char gap0[32];
    DobboFormatRow396 *rows;
} DobboFormatRoot396;
typedef struct {
    unsigned char gap0[0x80];
    int amount;
    unsigned char gap84[0x5c];
} DobboFormatMapped396;
typedef char DobboFormatRowStride396[(sizeof(DobboFormatRow396) == 40) ? 1 : -1];
typedef char DobboFormatMappedStride396[(sizeof(DobboFormatMapped396) == 0xe0) ? 1 : -1];
extern DobboFormatRoot396 LVL_7_SIBERIUS_D_001C97E0;
extern const char LVL_7_SIBERIUS_D_001A9A20[];
extern const char LVL_7_SIBERIUS_D_001A9A28[];
extern const unsigned char *LVL_7_SIBERIUS_FUN_002EA888(int);
extern void BOOT_FUN_00115DA8(char *, const char *, ...);
void LVL_7_SIBERIUS_FUN_002FF370(int index, unsigned char *output)
{
    unsigned char temporary[80];
    const unsigned char *source = LVL_7_SIBERIUS_FUN_002EA888(LVL_7_SIBERIUS_D_001C97E0.rows[index].text_id);
    unsigned char *p = temporary;
    if (!source)
        return;
    while (*source && *source != '%')
        *output++ = *source++;
    if (!*source) {
        *output = *source;
        return;
    }
    ++source;
    if (*source == 'b') {
        int key = LVL_7_SIBERIUS_D_001C97E0.rows[index].mapped_key;
        DobboFormatMapped396 *record = (DobboFormatMapped396 *)&LVL_7_SIBERIUS_D_002628A0[LVL_7_SIBERIUS_D_00139568[key]];
        BOOT_FUN_00115DA8((char *)temporary, LVL_7_SIBERIUS_D_001A9A20, record->amount);
    } else {
        BOOT_FUN_00115DA8((char *)temporary, LVL_7_SIBERIUS_D_001A9A28);
    }
    ++source;
    while (*p)
        *output++ = *p++;
    while (*source)
        *output++ = *source++;
    *output = 0;
}

typedef struct { u8 prefix[0xc38]; f32 plane; f32 depth; } GornFloatInterval64;

int LVL_7_SIBERIUS_FUN_002B2690(f32 value)
{
    GornFloatInterval64 *root = (GornFloatInterval64 *)LVL_7_SIBERIUS_D_00189E20;
    if (value < root->plane) {
        if (root->plane - value <= root->depth)
            return 1;
    }
    return 0;
}

/* Update the observed two-axis selection fields and their combined index. */
typedef struct {
    unsigned char gap0[0x43c];
    int column, row, index, mode;
} DobboGridState312;
extern int LVL_7_SIBERIUS_FUN_003555E8(int, unsigned int, void *);
void LVL_7_SIBERIUS_FUN_00435628(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        LVL_7_SIBERIUS_FUN_003555E8(3, 0, 0);
        --state->row;
        if (state->row < 0) {
            if (state->column == 0) {
                state->mode = 2;
                state->row = 1;
                state->column = 3;
            } else if (state->column == 1) {
                state->row = state->column;
            }
        }
    } else if (buttons & 0x4000) {
        int row;
        LVL_7_SIBERIUS_FUN_003555E8(3, 0, 0);
        row = state->row + 1;
        state->row = row > 1 ? 0 : row;
    } else if (buttons & 0x8000) {
        LVL_7_SIBERIUS_FUN_003555E8(3, 0, 0);
        --state->column;
        if (state->column < 0) {
            state->column = 3;
            state->row = 1;
            state->mode = 2;
        }
    } else if (buttons & 0x2000) {
        LVL_7_SIBERIUS_FUN_003555E8(3, 0, 0);
        ++state->column;
        if (state->column >= 2)
            state->column = 0;
    }
    state->index = state->column + state->row * 2;
}

extern void *LVL_7_SIBERIUS_D_001B2240[16];
extern u32 LVL_7_SIBERIUS_D_001B2280[16];

int LVL_7_SIBERIUS_FUN_00307708(void *object)
{
    int index;
    for (index = 0; index < 16; ++index) {
        if (LVL_7_SIBERIUS_D_001B2240[index] == 0 ||
            LVL_7_SIBERIUS_D_001B2240[index] == object) {
            LVL_7_SIBERIUS_D_001B2240[index] = object;
            LVL_7_SIBERIUS_D_001B2280[index] = 0;
            return index;
        }
    }
    return -1;
}

/* Append an observed point index and update the original geometric descriptor. */
typedef struct {
    unsigned char gap0[0x10];
    float plane[4];
    unsigned char gap20[0x10];
    float (*points)[4];
    unsigned char gap34[0x25];
    unsigned char indices[3];
    unsigned char count;
} OozlaAppendDescriptor164;
typedef struct {
    unsigned char gap0[0x68];
    OozlaAppendDescriptor164 *descriptor;
    unsigned char gap6c[0x54];
    float transform[3][4];
} OozlaAppendObject164;
typedef char OozlaAppendDescriptorCount164[((int)&((OozlaAppendDescriptor164 *)0)->count == 0x5c) ? 1 : -1];
extern void LVL_7_SIBERIUS_FUN_002D2B28(OozlaAppendObject164 *, int, const float *);
extern void LVL_7_SIBERIUS_FUN_002E4340(float *, const float *, const float *);
extern void LVL_7_SIBERIUS_FUN_002E47D0(float *, const float *, const float *);
extern void LVL_7_SIBERIUS_FUN_002D2E70(OozlaAppendObject164 *, float *, const float *);
unsigned int LVL_7_SIBERIUS_FUN_002D2A80(OozlaAppendObject164 *object, unsigned int index, const float *direction)
{
    float difference[4];
    OozlaAppendDescriptor164 *descriptor = object->descriptor;
    descriptor->indices[descriptor->count] = index;
    ++descriptor->count;
    LVL_7_SIBERIUS_FUN_002D2B28(object, (int)descriptor->count - 1, direction);
    if (descriptor->count != 1) {
        LVL_7_SIBERIUS_FUN_002E4340(difference, descriptor->points[descriptor->indices[0]], descriptor->points[descriptor->indices[1]]);
        LVL_7_SIBERIUS_FUN_002E47D0(difference, difference, &object->transform[0][0]);
        LVL_7_SIBERIUS_FUN_002D2E70(object, descriptor->plane, difference);
    }
    return descriptor->count;
}

typedef struct { f32 x, y, z, w; } JammingParameterRow;
typedef struct {
    u8 prefix[0x30];
    JammingParameterRow rows[4];
    f32 weights[3];
} JammingParameterRows;
void LVL_7_SIBERIUS_FUN_0043AAA0(f32 weight, f32 x, f32 y, f32 z, f32 w, JammingParameterRows *object, s32 index) {
    object->rows[index].x = x;
    object->rows[index].y = y;
    object->rows[index].z = z;
    object->rows[index].w = w;
    object->weights[index] = weight;
}

typedef struct { f32 x, y, z, w; } JammingGridRow;
typedef struct { JammingGridRow rows[3]; } JammingGridGroup;
typedef struct { u8 prefix[0x2c]; JammingGridGroup groups[2]; } JammingGridObject;
void LVL_7_SIBERIUS_FUN_0043AF38(f32 x, f32 y, f32 z, f32 w, JammingGridObject *object, s32 row, s32 group) {
    object->groups[group].rows[row].x = x;
    object->groups[group].rows[row].y = y;
    object->groups[group].rows[row].z = z;
    object->groups[group].rows[row].w = w;
}

extern unsigned char D_19B278[];

int LVL_7_SIBERIUS_FUN_0031D0E8(void)
{
    int count = 0;
    int i;

    for (i = 0; i < 0x1C; i++) {
        int j;

        for (j = 0; j < 4; j++) {
            if (D_19B278[i * 4 + j] != 0)
                count++;
        }
    }
    if (count < 0)
        count = 0;
    if (count > 0x28)
        count = 0x28;
    return count;
}

typedef struct { u8 before[0x68]; s32 active; u8 gap[6]; short state; } CallState;
extern u8 LVL_7_SIBERIUS_D_001A63A8[];
extern void FUN_00133400(s32);
s32 LVL_7_SIBERIUS_FUN_00323E48(void) {
    if (((CallState *)LVL_7_SIBERIUS_D_001A63A8)->active==0) return 0;
    if (((CallState *)LVL_7_SIBERIUS_D_001A63A8)->state!=3) return 0;
    FUN_00133400(((CallState *)LVL_7_SIBERIUS_D_001A63A8)->active); ((CallState *)LVL_7_SIBERIUS_D_001A63A8)->state=4;
    return 1;
}

f32 LVL_7_SIBERIUS_FUN_00310A38(f32 value, s32 count) {
    f32 factor = 1.0f - value;
    f32 product = factor;
    for (; count > 1; --count)
        product = product * factor;
    return 1.0f - product;
}

typedef struct {
    u8 pad0000[0x0000];
} ResidentBase1395B8;

s32 LVL_7_SIBERIUS_FUN_002FBC70(s32 index)
{
    s32 byte = index / 8;
    s32 bit = index % 8;
    s32 old;

    if ((u32)bit < 8) {
        old = (LVL_7_SIBERIUS_D_001395B8[byte + 0xA7] >> bit) & 1;
    } else {
        old = 0;
    }
    if ((u32)bit < 8) {
        LVL_7_SIBERIUS_D_001395B8[byte + 0xA7] |= 1 << bit;
    }
    return old;
}

/* Prototype775 is a research label. Field names below describe only the
 * independently observed byte23 and binary32 word2C operations. */
typedef struct {
    u8 pad00[0x23];
    u8 field23;
    u8 pad24[8];
    f32 field2C;
} NativeUpdate775View;

extern void LVL_7_SIBERIUS_FUN_00306800(NativeUpdate775View *object);

void LVL_7_SIBERIUS_FUN_00394AF8(NativeUpdate775View *object)
{
    object->field2C *= 1.025f;
    object->field23 -= 3;
    if (object->field23 < 4)
        LVL_7_SIBERIUS_FUN_00306800(object);
}


/* One fixed ordinary scalar source hypothesis. Byte offset and mask are
   measured; no original object/class/field name or allocation claim. The
   observed callers pass scalar one and ignore the result. */
void LVL_7_SIBERIUS_FUN_0031FAB0(unsigned char *entity, int enabled) {
    if (enabled)
        entity[0xBE] |= 4;
    else
        entity[0xBE] &= 0xFB;
}


/* One fixed ordinary scalar query. Signed halfword width, offset and
   equality constant are measured; no original class or field-name claim. */
int LVL_7_SIBERIUS_FUN_003157E8(const unsigned char *entity) {
    return *(const signed short *)(entity + 0xAA) == 0x0CDB;
}


void LVL_7_SIBERIUS_FUN_002A70E0(void)
{
}


unsigned int LVL_7_SIBERIUS_FUN_002CC828(void)
{
    return 0;
}


void LVL_7_SIBERIUS_FUN_002E3648(void)
{
}


void LVL_7_SIBERIUS_FUN_002EA620(void)
{
}


void LVL_7_SIBERIUS_FUN_002EB3D0(void)
{
}


void LVL_7_SIBERIUS_FUN_002F2C68(void)
{
}


void LVL_7_SIBERIUS_FUN_002F69D0(void)
{
}


void LVL_7_SIBERIUS_FUN_002FF728(void)
{
}


unsigned int LVL_7_SIBERIUS_FUN_003654F8(void)
{
    return 0;
}


void LVL_7_SIBERIUS_FUN_00369FD0(void)
{
}


void LVL_7_SIBERIUS_FUN_00370FE8(void)
{
}


void LVL_7_SIBERIUS_FUN_00374970(void)
{
}


void LVL_7_SIBERIUS_FUN_00378050(void)
{
}


void LVL_7_SIBERIUS_FUN_003E0B08(void)
{
}


void LVL_7_SIBERIUS_FUN_0040E190(void)
{
}


void LVL_7_SIBERIUS_FUN_0040F6B0(void)
{
}


void LVL_7_SIBERIUS_FUN_00428260(void)
{
}


void LVL_7_SIBERIUS_FUN_00429CD0(void)
{
}


void LVL_7_SIBERIUS_FUN_00429F20(void)
{
}


void LVL_7_SIBERIUS_FUN_0042A418(void)
{
}


void LVL_7_SIBERIUS_FUN_00432C90(void)
{
}


void LVL_7_SIBERIUS_FUN_004338E8(void)
{
}


void LVL_7_SIBERIUS_FUN_0043F6F0(void)
{
}


void LVL_7_SIBERIUS_FUN_00441A80(void)
{
}


void LVL_7_SIBERIUS_FUN_00443318(void)
{
}
void LVL_7_SIBERIUS_FUN_003A9E10(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003B1F68(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003C0950(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003C77F8(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003CAB80(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003CB8D0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003D2068(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003DBED0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003DD278(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_0040C390(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_004150F0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

extern u8 LVL_7_SIBERIUS_F62e6ff2b_D_00189E20[];
extern u8 LVL_7_SIBERIUS_F62e6ff2b_D_00188660[];

typedef struct {
    u8 pad0[4640];
    u32 field4640;
    u8 gap[4204];
    u32 field8848;
} NativeView;

s32 LVL_7_SIBERIUS_FUN_003551E0(s32 id)
{
    u8 *record;
    u8 *cursor;
    s32 limit;

    limit = 52;
    if (id == 0 || (((NativeView *)&LVL_7_SIBERIUS_F62e6ff2b_D_00189E20)->field8848 != (u32)id &&
                    ((NativeView *)&LVL_7_SIBERIUS_F62e6ff2b_D_00189E20)->field4640 != (u32)id))
        limit = 42;

    id = 0;
    if (limit != 0) {
        record = (u8 *)&LVL_7_SIBERIUS_F62e6ff2b_D_00188660;
        if (record[116] != 0) {
            cursor = record + 116;
            do {
                id++;
                if (id >= limit)
                    break;
                cursor += 112;
            } while (*cursor != 0);
        }
    }
    return (id != limit) ? id : 52;
}
void LVL_7_SIBERIUS_FUN_0039A038(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 88) = 0;
    *(float *)(p + 96) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(int *)(p + 84) = 0;
    *(float *)(p + 92) = 1.0f;
    *(int *)(p + 100) = 0;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003D4BC8(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 88) = 0;
    *(float *)(p + 96) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(int *)(p + 84) = 0;
    *(float *)(p + 92) = 1.0f;
    *(int *)(p + 100) = 0;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
typedef struct { int v[12]; } Blob;
extern Blob LVL_7_SIBERIUS_F6894d7c1_D_001A8E60;
int LVL_7_SIBERIUS_FUN_002E98F8(int x)
{
    Blob b;
    int i;
    b = LVL_7_SIBERIUS_F6894d7c1_D_001A8E60;
    for (i = 0; b.v[i]; i++)
        if (x == b.v[i])
            return 1;
    return 0;
}
void LVL_7_SIBERIUS_FUN_0037E250(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003808D8(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003E9B08(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_003ED798(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_004177E0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 8) = 0;
    *(float *)(p + 24) = 2.0f;
    *(int *)(p + 40) = 0;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
typedef struct { short key; short val; } Entry;

extern Entry *LVL_7_SIBERIUS_Fc68ad20a_D_0018C2B8;

int LVL_7_SIBERIUS_FUN_002C7F68(int key, int *out)
{
    Entry *e = LVL_7_SIBERIUS_Fc68ad20a_D_0018C2B8;
    Entry *p;

    if (e == 0)
        return 0;
    if (e->key == -1)
        goto notfound;
    p = e;
    for (;;) {
        if (key == p->key) {
            *out = p->val;
            return 1;
        }
        p++;
        if (p->key == -1)
            goto notfound;
    }
notfound:
    *out = 0;
    return 0;
}
typedef struct {
    int f0;
    short f4;
    unsigned char f6;
    char pad[0x18 - 7];
    int f18;
    int f1C;
} Blk;

extern Blk LVL_7_SIBERIUS_F55a1acb8_D_001A63A8;
extern short LVL_7_SIBERIUS_F55a1acb8_D_001A63AC;
extern int LVL_7_SIBERIUS_F55a1acb8_FUN_00133688(void);
extern void LVL_7_SIBERIUS_F55a1acb8_FUN_0011AEA0(int);

void LVL_7_SIBERIUS_FUN_00324F18(int x)
{
    unsigned char c;
    int q;
    int arg;

    if (x != 1)
        return;

    if (LVL_7_SIBERIUS_F55a1acb8_FUN_00133688()) {
        LVL_7_SIBERIUS_F55a1acb8_D_001A63AC = 2;
        return;
    }

    LVL_7_SIBERIUS_F55a1acb8_FUN_0011AEA0(0);

    c = LVL_7_SIBERIUS_F55a1acb8_D_001A63A8.f6;
    q = LVL_7_SIBERIUS_F55a1acb8_D_001A63A8.f18;
    LVL_7_SIBERIUS_F55a1acb8_D_001A63A8.f4 = 0;
    arg = c < 1;
    LVL_7_SIBERIUS_F55a1acb8_D_001A63A8.f6 = 0;

    if (q != 0) {
        int cb = LVL_7_SIBERIUS_F55a1acb8_D_001A63A8.f1C;
        LVL_7_SIBERIUS_F55a1acb8_D_001A63A8.f18 = 0;
        LVL_7_SIBERIUS_F55a1acb8_D_001A63A8.f1C = 0;
        ((void (*)(int, int))q)(cb, arg);
    }
}
extern char LVL_7_SIBERIUS_Fa2dbe766_D_00189E20[];

int LVL_7_SIBERIUS_FUN_003BA460(float f12)
{
    char *b;

    if (f12 <= 0.0f)
        goto fail;
    b = LVL_7_SIBERIUS_Fa2dbe766_D_00189E20;
    if (*(short *)(*(int *)(b + 8848) + 170) != 0)
        goto fail;
    if (*(unsigned char *)(b + 8884) != 0)
        goto fail;
    if (*(int *)(b + 8852) == 49)
        goto fail;
    if (*(int *)(b + 8860) == 20)
        goto fail;
    if (*(int *)(b + 9420) > 0)
        goto ok;
fail:
    return 0;
ok:
    return 1;
}
struct Rec { s32 f0, f1, f2, f3, f4, f5, f6, f7, f8, f9; };
extern struct Rec LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[32];
void LVL_7_SIBERIUS_FUN_002D8C18(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f,
                                       s32 g, s32 h, s32 i, s32 j, s32 idx) {
    if ((unsigned)idx < 32) {
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f0 = a;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f1 = b;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f2 = c;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f3 = d;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f4 = e;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f5 = f;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f6 = g;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f7 = h;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f8 = i;
        (LVL_7_SIBERIUS_F480de5ac_D_001BC9C8[idx]).f9 = j;

    }
}
typedef unsigned short u16;

void LVL_7_SIBERIUS_FUN_0033C410(void) {
    *(u16 *)0x1aa842 = *(u8 *)0x1a7bc9 ? 3 : 0;
    *(u16 *)0x1aa85a = *(u8 *)0x1a7bca ? 3 : 0;
    *(u16 *)0x1aa872 = *(u8 *)0x1a7bcb ? 3 : 0;
    *(u16 *)0x1aa88a = *(u8 *)0x1a7bcc ? 3 : 0;
    *(u16 *)0x1aa8a2 = *(u8 *)0x1a7bce ? 3 : 0;
}
void LVL_7_SIBERIUS_FUN_00403EB8(char *object)
{
    char *o = object;
    int *q = *(int **)(o + 104);

    if (*(unsigned char *)(o + 32))
        return;

    q[2] = 64;
    q[4] = 50;
    q[0] = 0;
    q[3] = -1;
    q[5] = 0;
    *(unsigned char *)(o + 32) = 1;
    q[6] = -1;

    *(float *)(o + 44) = *(float *)(*(int *)(o + 36) + 36) * 0.8f;
}
extern char LVL_7_SIBERIUS_Fea34650e_D_00189E20[];

void LVL_7_SIBERIUS_FUN_002C9058(void)
{
    char *b = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
    char *p;
    int i;

    p = *(char **)(b + 3096);
    *(unsigned short *)(p + 52) &= 0xFFFE;

    for (i = 0; i < 7; i++) {
        p = *(char **)(b + 4640 + i * 80);
        if (p != 0)
            *(unsigned short *)(p + 52) &= 0xFFFE;
        p = *(char **)(b + 4644 + i * 80);
        if (p != 0)
            *(unsigned short *)(p + 52) &= 0xFFFE;
        p = *(char **)(b + 4648 + i * 80);
        if (p != 0)
            *(unsigned short *)(p + 52) &= 0xFFFE;
    }

    if (1) {
        char *c = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
        p = *(char **)(c + 4892);
        if (p != 0)
            *(unsigned short *)(p + 52) &= 0xFFFE;
    }

    if (1) {
        char *c = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
        if (*(unsigned char *)(c + 8884) == 1) {
            c = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
            p = *(char **)(c + 6244);
            if (p != 0)
                *(unsigned short *)(p + 52) &= 0xFFFE;
        }
    }

    if (1) {
        char *c = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
        if (*(short *)(c + 9468) != 0 || *(int *)(c + 8860) == 31) {
            c = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
            p = *(char **)(c + 4880);
            if (p != 0)
                *(unsigned short *)(p + 52) |= 0x41;
            c = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
            p = *(char **)(c + 4884);
            if (p != 0)
                *(unsigned short *)(p + 52) |= 0x41;
            c = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
            p = *(char **)(c + 4892);
            if (p != 0)
                *(unsigned short *)(p + 52) |= 0x41;
        }
    }

    if (1) {
        char *c = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
        if ((*(unsigned char *)(c + 8894) != 0 && *(int *)(c + 4680) == 10) ||
            *(unsigned char *)(c + 8895) != 0) {
            char *d = LVL_7_SIBERIUS_Fea34650e_D_00189E20;
            p = *(char **)(d + 4640);
            if (p != 0)
                *(unsigned short *)(p + 52) |= 0x41;
        }
    }
}
void LVL_7_SIBERIUS_FUN_003D52A0(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
void LVL_7_SIBERIUS_FUN_00417778(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

struct Slot { s32 w; s32 rest[4]; };
struct Table1 { char pad[19264]; struct Slot slots[48]; };
struct Table2 { char pad[52]; s32 slots[4]; };

extern struct Table1 LVL_7_SIBERIUS_Fee2b87d1_D_0014B540;
extern struct Table2 LVL_7_SIBERIUS_Fee2b87d1_D_00152CD0;

s32 LVL_7_SIBERIUS_FUN_002FB3B0(s32 value) {
    s32 i = 0;
    s32 *q;
    if (LVL_7_SIBERIUS_Fee2b87d1_D_0014B540.slots[0].w == value) goto after1;
    while (++i < 48) {
        if (LVL_7_SIBERIUS_Fee2b87d1_D_0014B540.slots[i].w == value) break;
    }
after1:
    if (i == 48) return 1;
    value = 0;
    if (LVL_7_SIBERIUS_Fee2b87d1_D_00152CD0.slots[0] == i) goto after2;
    while (++value < 3) {
        if (LVL_7_SIBERIUS_Fee2b87d1_D_00152CD0.slots[value] == i) break;
    }
after2:
    return value != 3;
}
extern void LVL_7_SIBERIUS_F0b67d264_FUN_00115E38(char *a, int b, char *c);
extern char LVL_7_SIBERIUS_F0b67d264_D_001ADD58[];
extern char LVL_7_SIBERIUS_F0b67d264_D_001ADD78[];

void LVL_7_SIBERIUS_FUN_00428278(int *p, unsigned int n, int a2, int a3)
{
    if (n < 4)
        LVL_7_SIBERIUS_F0b67d264_FUN_00115E38(LVL_7_SIBERIUS_F0b67d264_D_001ADD58, 37, LVL_7_SIBERIUS_F0b67d264_D_001ADD78);

    p[1] = a3;
    p[2] = n;
    p[4] = 0;
    p[5] = 0;
    p[3] = 0;
    p[0] = a2;
}
/* Family 430eca3b2fc8d2b0 (112 B, 2 placements).
   A search over the resident table reached through LVL_7_SIBERIUS_F430eca3b_D_001AA7B0: the first entry
   is tested outside the loop, the loop scans the rest, and the found index is
   re-read.  Every access names the global itself, so cc1 merges the loads into
   one register and keeps the index arithmetic (no strength reduction), which
   is the retail shape.  The one small-data global LVL_7_SIBERIUS_F430eca3b_D_001A79F0 is loaded in the
   branch delay slot, so the qualified small-data profile is required. */

extern int *LVL_7_SIBERIUS_F430eca3b_D_001AA7B0 __attribute__((sda));
extern int LVL_7_SIBERIUS_F430eca3b_D_001A79F0 __attribute__((sda));

int LVL_7_SIBERIUS_FUN_002FC838(int a0)
{
    int r = -1;
    int i = 0;

    if (LVL_7_SIBERIUS_F430eca3b_D_001AA7B0[0] == a0) {
        r = 0;
    } else {
        while (i < 28) {
            if (LVL_7_SIBERIUS_F430eca3b_D_001AA7B0[i] == a0) {
                r = i;
                break;
            }
            i++;
        }
    }
    if (LVL_7_SIBERIUS_F430eca3b_D_001AA7B0[r] == 0 && LVL_7_SIBERIUS_F430eca3b_D_001A79F0) {
        r = -1;
    }
    return r;
}
/* attempt 3: the project's existing (boot-qualified) spelling: -G0 profile plus
   an explicit `sda` attribute on the one resident word that retail addresses
   through $gp.  Used here as a control, to measure what -G8 changes. */

typedef struct __attribute__((packed)) { unsigned char mode[4]; } CdMode;

extern CdMode LVL_7_SIBERIUS_F1157be91_D_001A63E8;
extern unsigned char LVL_7_SIBERIUS_F1157be91_D_001A7900[] __attribute__((sda));
extern int LVL_7_SIBERIUS_F1157be91_D_001A7430[] __attribute__((sda));
extern int LVL_7_SIBERIUS_F1157be91_D_001A7434 __attribute__((sda));
extern int LVL_7_SIBERIUS_F1157be91_FUN_001334B8(int, int, int, CdMode *);
extern int LVL_7_SIBERIUS_F1157be91_FUN_00133230(void);
extern int LVL_7_SIBERIUS_F1157be91_FUN_00132028(void);

int LVL_7_SIBERIUS_FUN_00324DA0(int a0, int a1, int a2) {
    CdMode mode = LVL_7_SIBERIUS_F1157be91_D_001A63E8;
    mode.mode[1] = LVL_7_SIBERIUS_F1157be91_D_001A7900[0];
    LVL_7_SIBERIUS_F1157be91_D_001A7430[0] = 0;
    LVL_7_SIBERIUS_F1157be91_D_001A7434 = 0;
    LVL_7_SIBERIUS_F1157be91_FUN_001334B8(a1, a2, a0, &mode);
    LVL_7_SIBERIUS_F1157be91_FUN_00133230();
    LVL_7_SIBERIUS_F1157be91_FUN_00132028();
    return 1;
}
typedef struct {
    u8 field00[0x218]; signed short field218; u8 field21A[0x12e];
    signed short field348; u8 field34A[4]; signed short field34E;
    u8 field350[0x1147]; u8 field1497; u8 field1498[2]; u8 field149A;
    u8 field149B[0xdf9]; s32 field2294;
} NativeModeResident;
extern NativeModeResident LVL_7_SIBERIUS_F4e5bde81_D_00189E20;
extern s32 LVL_7_SIBERIUS_F4e5bde81_D_001A8FF0 __attribute__((sda));
extern volatile u8 LVL_7_SIBERIUS_F4e5bde81_D_001A7B08[4] __attribute__((sda));
extern s32 LVL_7_SIBERIUS_F4e5bde81_D_001A8FF4 __attribute__((sda));
s32 LVL_7_SIBERIUS_FUN_002C93B0(void) {
    s32 result = LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field348;
    if (LVL_7_SIBERIUS_F4e5bde81_D_001A8FF0 != 0 && LVL_7_SIBERIUS_F4e5bde81_D_001A8FF4 == 0) result = 2;
    if (LVL_7_SIBERIUS_F4e5bde81_D_001A8FF4 != 0 || LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field2294 == 59 ||
        (LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field2294 == 110 && LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field149A == 0) ||
        LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field2294 == 109 || LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field218 != 0 ||
        (LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field1497 != 0 && LVL_7_SIBERIUS_F4e5bde81_D_001A7B08[3] != 0 &&
         LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field2294 == 0 && LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field34E < 4)) result = 1;
    if (result == 1 && LVL_7_SIBERIUS_F4e5bde81_D_00189E20.field149A != 0) result = 0;
    return result;
}
typedef short s16;

typedef struct {
    u8 f0; u8 f1; u8 f2; u8 f3;
    s16 f4; s16 f6; s16 f8; s16 fA; s16 fC;
    u8 fE; u8 fF;
} Slot;

extern Slot LVL_7_SIBERIUS_F777b9bda_D_001B9040[8] __attribute__((nosda));

int LVL_7_SIBERIUS_FUN_002CC948(Slot *src)
{
    int count;
    int i;
    int free;

    count = 0;
    while (count < 8 && src[count].f0 != 255)
        count++;

    free = 0;
    for (i = 0; i < 8 && free < count; i++) {
        if (LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f0 == 0)
            free++;
    }

    if (free != count)
        return -1;

    for (free = 0; free < count; free++) {
        i = 0;
        while (i < 8 && LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f0 != 0)
            i++;
        if (i < 8) {
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f0 = src[free].f0;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f1 = src[free].f1;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f2 = src[free].f2;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f3 = src[free].f3;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f4 = src[free].f4;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f6 = src[free].f6;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].f8 = src[free].f8;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].fA = src[free].fA;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].fC = src[free].fC;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].fE = src[free].fE - src[free].fF;
            LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].fF = src[free].fF;
            if (LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].fA + LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].fC == 0)
                LVL_7_SIBERIUS_F777b9bda_D_001B9040[i].fA++;
        }
    }
    return i;
}
/* 3777c7f5d4234584 - nested scan over a table, 260 B, no arguments. */

extern int LVL_7_SIBERIUS_F3777c7f5_D_002208E0 __attribute__((nosda));
extern char *LVL_7_SIBERIUS_F3777c7f5_D_0021EE60[];
struct Pair {
    short a;
    short b;
};
extern struct Pair LVL_7_SIBERIUS_F3777c7f5_D_002203E0[];
struct Item {
    char *ptr;
    int extra;
};

void LVL_7_SIBERIUS_FUN_003509C8(void)
{
    int *p;
    int *entry;
    struct Item *items;
    char *node;
    char *block;
    char *slot;
    struct Pair *pair;
    short value;
    int i;
    int j;

    p = &LVL_7_SIBERIUS_F3777c7f5_D_002208E0;
    if (*p < 0)
        return;
    while (*p >= 0) {
        entry = (int *)LVL_7_SIBERIUS_F3777c7f5_D_0021EE60[*p];
        for (i = 0; i < *(short *)((char *)entry + 40); i++) {
            items = (struct Item *)((char *)entry + 64);
            node = *(char **)((char *)items + (i << 3));
            block = node + 16;
            slot = block + (*(int *)(block + 4) << 4) + 16;
            for (j = 0; j < *(int *)block; j++) {
                pair = &LVL_7_SIBERIUS_F3777c7f5_D_002203E0[*(unsigned char *)(slot + 19)];
                value = pair->a;
                if (value != 0)
                    *(int *)(slot + 48) = (*(int *)(slot + 48) & 0xFFFFC000) | value;
                value = pair->b;
                if (value != 0)
                    *(int *)(slot + 32) = (*(int *)(slot + 32) & 0xFFFFC000) | value;
                slot += 64;
            }
        }
        p++;
    }
}

extern u8 LVL_7_SIBERIUS_Fc895cb79_D_001D1D00[];

void LVL_7_SIBERIUS_FUN_00306858(u8 *param_1)
{
    if (param_1[66] != 255) {
        u8 *tbl = (u8 *)(*(volatile int *)(param_1 + 36) + 72);

        *(int *)(param_1 + 88) = *(int *)(*(int *)(tbl + (*(volatile u8 *)(param_1 + 66) << 2)) + (param_1[64] << 2) + 28);
        param_1[110] = *(u8 *)(*(int *)(tbl + (*(volatile u8 *)(param_1 + 66) << 2)) + 18);
        param_1[108] = *(u8 *)(*(int *)(tbl + (*(volatile u8 *)(param_1 + 66) << 2)) + 17);
    } else {
        param_1[108] = 255;
        param_1[110] = 0;
        *(int *)(param_1 + 88) = (int)(LVL_7_SIBERIUS_Fc895cb79_D_001D1D00 + (param_1[64] << 11));
    }

    *(int *)(param_1 + 92) = *(int *)(*(int *)(*(volatile int *)(param_1 + 36) + (param_1[67] << 2) + 72) + (param_1[65] << 2) + 28);
}
extern void LVL_7_SIBERIUS_F0477ffed_FUN_00115DA8(int a, char *fmt, ...);
extern char LVL_7_SIBERIUS_F0477ffed_D_001AD630[]; extern char LVL_7_SIBERIUS_F0477ffed_D_001AD640[]; extern char LVL_7_SIBERIUS_F0477ffed_D_001AD648[];
void LVL_7_SIBERIUS_FUN_0036B9D0(int out, int v) {
    if (v > 999999) {
        LVL_7_SIBERIUS_F0477ffed_FUN_00115DA8(out, LVL_7_SIBERIUS_F0477ffed_D_001AD630, v / 1000000, (v / 1000) % 1000, v % 1000);
    } else if (v >= 1000) {
        LVL_7_SIBERIUS_F0477ffed_FUN_00115DA8(out, LVL_7_SIBERIUS_F0477ffed_D_001AD640, v / 1000, v % 1000);
    } else {
        LVL_7_SIBERIUS_F0477ffed_FUN_00115DA8(out, LVL_7_SIBERIUS_F0477ffed_D_001AD648, v);
    }
}
extern void LVL_7_SIBERIUS_F7b754363_FUN_00115E38(char *a, int b, char *c);
extern char LVL_7_SIBERIUS_F7b754363_D_001ADD58[];
extern char LVL_7_SIBERIUS_F7b754363_D_001ADDA0[];

int LVL_7_SIBERIUS_FUN_00428300(unsigned int *p)
{
    unsigned int *n = (unsigned int *)p[5];
    unsigned int offset;
    unsigned int result;

    if (n != 0) {
        p[5] = n[0];
        p[4] = p[4] + 1;
        return (int)n;
    }

    offset = p[3];

    if (p[1] < offset + p[2]) {
        LVL_7_SIBERIUS_F7b754363_FUN_00115E38(LVL_7_SIBERIUS_F7b754363_D_001ADD58, 83, LVL_7_SIBERIUS_F7b754363_D_001ADDA0);
        return 0;
    }

    p[3] = offset + p[2];
    result = p[0] + offset;
    p[4] = p[4] + 1;
    return result;
}
/* RAC2 family 4615e05e7f21cb33 - 192 bytes, 2 placements.
 * Slot4615e05e allocator: find the first free of six 64-byte slots, fill it in and
 * link it at the head of the context's list.
 */

typedef struct Slot4615e05e {
    short          f00;    /* +0x00 */
    short          f02;    /* +0x02 */
    unsigned char  f04;    /* +0x04 */
    char           pad05[7];
    unsigned char *f0C;    /* +0x0C */
    int            f10;    /* +0x10 */
    int            f14;    /* +0x14 */
    int            f18;    /* +0x18 */
    int            f1C;    /* +0x1C */
    char           pad20[32];
} Slot4615e05e;                    /* 64 bytes */

typedef struct Mid {
    char           pad00[0x1C];
    char          *f1C;    /* +0x1C */
} Mid;

typedef struct Ctx {
    char           pad00[0x24];
    Mid           *f24;    /* +0x24 */
    char           pad28[0x28];
    int            f50;    /* +0x50 */
} Ctx;

extern Slot4615e05e LVL_7_SIBERIUS_F4615e05e_D_001D1B80[6];
extern unsigned char LVL_7_SIBERIUS_F4615e05e_D_001C9D80[];

Slot4615e05e *LVL_7_SIBERIUS_FUN_00306F88(Ctx *ctx, int index)
{
    int i;
    Slot4615e05e *slot;
    unsigned char *p;

    for (i = 0; i < 6; i++) {
        if (LVL_7_SIBERIUS_F4615e05e_D_001D1B80[i].f04 == 0) {
            break;
        }
    }
    slot = &LVL_7_SIBERIUS_F4615e05e_D_001D1B80[i];
    slot->f04 = 1;
    slot->f00 = index;
    slot->f10 = (int)(LVL_7_SIBERIUS_F4615e05e_D_001C9D80 + i * 5376);
    slot->f14 = (int)ctx->f24;
    p = (unsigned char *)*(unsigned int *)(ctx->f24->f1C + (short)index * 4 + 4);
    slot->f02 = p[2];
    slot->f0C = p + (p[0] + 4);
    slot->f1C = ctx->f50;
    ctx->f50 = (int)slot;
    return slot;
}
typedef struct {
    short key;
    short index;
    int value;
} Query;

typedef struct {
    int key;
    int value;
} Entry32fd6f60;

extern Entry32fd6f60 LVL_7_SIBERIUS_F32fd6f60_D_002A4100[];

void LVL_7_SIBERIUS_FUN_003558E8(Query *query)
{
    int i;

    i = 0;
    while (LVL_7_SIBERIUS_F32fd6f60_D_002A4100[i].key != -1 && LVL_7_SIBERIUS_F32fd6f60_D_002A4100[i].key != query->key)
        i++;
    query->index = i;
    query->value = LVL_7_SIBERIUS_F32fd6f60_D_002A4100[i].value;
}
typedef struct {
    unsigned char key;
    unsigned char reserved01[11];
    int target;
} Row167abba11e;
typedef struct {
    unsigned char reserved00[32];
    Row167abba11e *rows;
} ListObject7abba11e;
typedef struct {
    short first;
    short second;
} Pair7abba11e;

extern int LVL_7_SIBERIUS_F7abba11e_D_001DD980[];
extern ListObject7abba11e *LVL_7_SIBERIUS_F7abba11e_D_001DA340[];
extern Pair7abba11e LVL_7_SIBERIUS_F7abba11e_D_001DD1C0[];

void LVL_7_SIBERIUS_FUN_00307C30(void)
{
    int *selected;
    ListObject7abba11e *object;
    Row167abba11e *row;
    unsigned char *keys;
    unsigned int *dst;
    Pair7abba11e *pair;
    int *next;

    selected = LVL_7_SIBERIUS_F7abba11e_D_001DD980;
    while (*selected >= 0) {
        next = selected + 1;
        object = LVL_7_SIBERIUS_F7abba11e_D_001DA340[*selected];
        row = object->rows;
        for (;;) {
            keys = (unsigned char *)row;
            dst = (unsigned int *)(row->target & 0x7FFFFFFF);
            if (*keys != 255) {
                do {
                    pair = &LVL_7_SIBERIUS_F7abba11e_D_001DD1C0[*keys];
                    if (pair->first != 0) {
                        dst[12] = (dst[12] & 0xFFFFC000u) | pair->first;
                    }
                    keys++;
                    if (pair->second != 0) {
                        dst[16] = (dst[16] & 0xFFFFC000u) | pair->second;
                    }
                    dst += 16;
                } while (*keys != 255);
            }
            if (row->target < 0) {
                goto out;
            }
            row++;
        }
out:
        ;
        selected = next;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_abf21065e887d7a9_FallbackU32;

typedef struct Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout {
    unsigned char unknown_00[0x90];
    Rac2Native_abf21065e887d7a9_FallbackU32 flags_90;
    Rac2Native_abf21065e887d7a9_FallbackU32 unknown_94;
    Rac2Native_abf21065e887d7a9_FallbackU32 flags_98;
} Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout;


extern Rac2Native_abf21065e887d7a9_FallbackPredicate112Layout LVL_7_SIBERIUS_Fabf21065e887d7a9_AT00305278_ROLE00;

int LVL_7_SIBERIUS_FUN_00305278(void)
{
    if ((LVL_7_SIBERIUS_Fabf21065e887d7a9_AT00305278_ROLE00.flags_90 & 0x10000u) == 0 &&
        (LVL_7_SIBERIUS_Fabf21065e887d7a9_AT00305278_ROLE00.flags_98 & 0x04000000u) != 0)
        return 0;
    if ((LVL_7_SIBERIUS_Fabf21065e887d7a9_AT00305278_ROLE00.flags_90 & 0x10000u) != 0 &&
        (LVL_7_SIBERIUS_Fabf21065e887d7a9_AT00305278_ROLE00.flags_98 & 0x04000000u) != 0)
        return 1;
    return 0;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner {
    unsigned char prefix_00[0x120];
    void *slots_120[10];
    int count_148;
    int active_14c;
} Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;


extern void LVL_7_SIBERIUS_F5b4b17178a13f443_AT003190F0_ROLE00(void *object);

void LVL_7_SIBERIUS_FUN_003190F0(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *owner)
{
    int index;
    if (owner->active_14c != 0) {
        for (index = 0; index < owner->count_148; ++index) {
            if (owner->slots_120[index] != 0) {
                LVL_7_SIBERIUS_F5b4b17178a13f443_AT003190F0_ROLE00(owner->slots_120[index]);
                owner->slots_120[index] = 0;
            }
        }
        owner->active_14c = 0;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_acdcf1600d770d3b_ScalarConfigure116State {
    unsigned char prefix_00[0x60];
    unsigned int value_60;
    int value_64;
    unsigned char selector_68;
    unsigned char axis_69;
    unsigned char mode_6a;
    unsigned char dirty_6b;
} Rac2Native_acdcf1600d770d3b_ScalarConfigure116State;


extern Rac2Native_acdcf1600d770d3b_ScalarConfigure116State LVL_7_SIBERIUS_Facdcf1600d770d3b_AT003559D0_ROLE00[];

void LVL_7_SIBERIUS_FUN_003559D0(unsigned int value, unsigned int selector, int other,
                        unsigned int axis, unsigned int mode)
{
    Rac2Native_acdcf1600d770d3b_ScalarConfigure116State *state = LVL_7_SIBERIUS_Facdcf1600d770d3b_AT003559D0_ROLE00;
    state->value_60 = value;
    if (state->selector_68 != selector) {
        state->dirty_6b |= 1;
        state->selector_68 = selector;
    }
    if (state->value_64 != other) {
        state->dirty_6b |= 4;
        state->value_64 = other;
    }
    if (state->axis_69 != axis || state->mode_6a != mode) {
        state->dirty_6b |= 2;
        state->axis_69 = axis;
        state->mode_6a = mode;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_b1b523716b470b36_FamilyNative192Vector {
    float x;
    float y;
    float z;
    float w;
} Rac2Native_b1b523716b470b36_FamilyNative192Vector;


extern void LVL_7_SIBERIUS_Fb1b523716b470b36_AT0037D3B0_ROLE01(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);
extern void LVL_7_SIBERIUS_Fb1b523716b470b36_AT0037D3B0_ROLE00(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);

void LVL_7_SIBERIUS_FUN_0037D3B0(void *object)
{
    Rac2Native_b1b523716b470b36_FamilyNative192Vector input;
    Rac2Native_b1b523716b470b36_FamilyNative192Vector output;
    char *base = (char *)object;
    char *state;
    char *source;
    char *kind;
    char *extra;

    input.w = 0.0f;
    state = *(char **)(base + 0x68);
    input.x = *(float *)(state + 0x74);
    input.y = *(float *)(state + 0x78);
    input.z = *(float *)(state + 0x7c);
    source = *(char **)(state + 0x70);
    LVL_7_SIBERIUS_Fb1b523716b470b36_AT0037D3B0_ROLE01(&output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(source + 0x10), &input);
    LVL_7_SIBERIUS_Fb1b523716b470b36_AT0037D3B0_ROLE00((Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10), &output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10));
    source = *(char **)(state + 0x70);
    *(float *)(state + 0x74) = *(float *)(source + 0x10);
    *(float *)(state + 0x78) = *(float *)(source + 0x14);
    *(float *)(state + 0x7c) = *(float *)(source + 0x18);
    kind = *(char **)(source + 0x24);
    if (*(short *)(kind + 0x46) == 0x12) {
        extra = *(char **)(source + 0x68);
        if (*(unsigned char *)(extra + 0x14) == 0) {
            *(unsigned char *)(base + 0x20) = 7;
        }
    }
}


extern void LVL_7_SIBERIUS_Fb1b523716b470b36_AT0037FE58_ROLE01(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);
extern void LVL_7_SIBERIUS_Fb1b523716b470b36_AT0037FE58_ROLE00(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);

void LVL_7_SIBERIUS_FUN_0037FE58(void *object)
{
    Rac2Native_b1b523716b470b36_FamilyNative192Vector input;
    Rac2Native_b1b523716b470b36_FamilyNative192Vector output;
    char *base = (char *)object;
    char *state;
    char *source;
    char *kind;
    char *extra;

    input.w = 0.0f;
    state = *(char **)(base + 0x68);
    input.x = *(float *)(state + 0x74);
    input.y = *(float *)(state + 0x78);
    input.z = *(float *)(state + 0x7c);
    source = *(char **)(state + 0x70);
    LVL_7_SIBERIUS_Fb1b523716b470b36_AT0037FE58_ROLE01(&output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(source + 0x10), &input);
    LVL_7_SIBERIUS_Fb1b523716b470b36_AT0037FE58_ROLE00((Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10), &output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10));
    source = *(char **)(state + 0x70);
    *(float *)(state + 0x74) = *(float *)(source + 0x10);
    *(float *)(state + 0x78) = *(float *)(source + 0x14);
    *(float *)(state + 0x7c) = *(float *)(source + 0x18);
    kind = *(char **)(source + 0x24);
    if (*(short *)(kind + 0x46) == 0x12) {
        extra = *(char **)(source + 0x68);
        if (*(unsigned char *)(extra + 0x14) == 0) {
            *(unsigned char *)(base + 0x20) = 7;
        }
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;


extern void LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT0038EE88_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_7_SIBERIUS_FUN_0038EE88(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT0038EE88_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT00393968_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_7_SIBERIUS_FUN_00393968(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT00393968_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_86f665335d9cb905_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_86f665335d9cb905_AnalysisOwner;


extern void LVL_7_SIBERIUS_F86f665335d9cb905_AT003B0AF8_ROLE00(Rac2Native_86f665335d9cb905_AnalysisOwner *owner, void *context);

void LVL_7_SIBERIUS_FUN_003B0AF8(Rac2Native_86f665335d9cb905_AnalysisOwner *owner)
{
    LVL_7_SIBERIUS_F86f665335d9cb905_AT003B0AF8_ROLE00(owner, owner->context_68);
}


extern void LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003B7D28_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_7_SIBERIUS_FUN_003B7D28(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003B7D28_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003BD3A0_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_7_SIBERIUS_FUN_003BD3A0(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003BD3A0_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003D56C8_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_7_SIBERIUS_FUN_003D56C8(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003D56C8_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003D9D98_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_7_SIBERIUS_FUN_003D9D98(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003D9D98_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


extern void LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003F3E48_ROLE00(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

void LVL_7_SIBERIUS_FUN_003F3E48(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        LVL_7_SIBERIUS_F9cdc323a4d0c2fbd_AT003F3E48_ROLE00(1.0f, context, context->vector_10, 0);
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Owner {
    unsigned char unknown_00[0x7d];
    unsigned char value_7d;
    short value_7e;
    unsigned char unknown_80[6];
    short identity_86;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Owner;

typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Global {
    unsigned char unknown_00[0x2294];
    int mode_2294;
    unsigned char unknown_2298[0x208];
    int identity_24a0;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Global;


extern Rac2Native_6af85cabb56d3b41_SmallConditional52Global LVL_7_SIBERIUS_F6af85cabb56d3b41_AT00425B40_ROLE00;

void LVL_7_SIBERIUS_FUN_00425B40(Rac2Native_6af85cabb56d3b41_SmallConditional52Owner *owner)
{
    if (LVL_7_SIBERIUS_F6af85cabb56d3b41_AT00425B40_ROLE00.identity_24a0 != owner->identity_86 &&
        LVL_7_SIBERIUS_F6af85cabb56d3b41_AT00425B40_ROLE00.mode_2294 != 6) {
        owner->value_7d = 0;
        owner->value_7e = 3;
    }
}


void LVL_7_SIBERIUS_FUN_00426FD0(float factor, void *context,
                                   float *destination,
                                   const float *first, const float *second)
{
    float complement = 1.0f - factor;
    destination[0] = complement * first[0] + factor * second[0];
    destination[1] = complement * first[1] + factor * second[1];
    destination[2] = complement * first[2] + factor * second[2];
    destination[3] = complement * first[3] + factor * second[3];
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout {
    unsigned char unknown_00[8];
    float first_0;
    float second_0;
    float first_1;
    float second_1;
    float first_2;
    float second_2;
    float first_3;
    float second_3;
} Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout;


void LVL_7_SIBERIUS_FUN_00427180(float factor,
                                     const Rac2Native_81be3b52930eb806_FallbackInterleavedFloat4Layout *source,
                                     float *destination)
{
    float complement = 1.0f - factor;
    destination[0] = complement * source->first_0 + factor * source->second_0;
    destination[1] = complement * source->first_1 + factor * source->second_1;
    destination[2] = complement * source->first_2 + factor * source->second_2;
    destination[3] = complement * source->first_3 + factor * source->second_3;
}


void LVL_7_SIBERIUS_FUN_0042C4E0(float first, float second, float **cell)
{
    (*cell)[0] = first;
    (*cell)[1] = second;
}


void LVL_7_SIBERIUS_FUN_00434508(float first, float second, float **cell)
{
    (*cell)[0] = first;
    (*cell)[1] = second;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_79744baad5ad7f65_ScalarChange48Owner {
    unsigned int field_00;
    int value_04;
    unsigned char gap_08[0x3ec];
    int counter_3f4;
    int counter_3f8;
    int previous_3fc;
} Rac2Native_79744baad5ad7f65_ScalarChange48Owner;


extern unsigned char LVL_7_SIBERIUS_F79744baad5ad7f65_AT0043B978_ROLE00[];

void LVL_7_SIBERIUS_FUN_0043B978(Rac2Native_79744baad5ad7f65_ScalarChange48Owner *owner, int value)
{
    int previous = owner->value_04;
    if (previous != value && LVL_7_SIBERIUS_F79744baad5ad7f65_AT0043B978_ROLE00[0] == 0) {
        owner->previous_3fc = previous;
        owner->counter_3f8 = 180;
        owner->counter_3f4 = 300;
    }
    owner->value_04 = value;
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef int Rac2Native_6b0741c38bf00fee_s32;

typedef unsigned char Rac2Native_6b0741c38bf00fee_u8;

typedef long Rac2Native_6b0741c38bf00fee_s64;

typedef unsigned long Rac2Native_6b0741c38bf00fee_u64;


extern Rac2Native_6b0741c38bf00fee_u8 LVL_7_SIBERIUS_F6b0741c38bf00fee_AT002A6288_ROLE00[];
extern void LVL_7_SIBERIUS_F6b0741c38bf00fee_AT002A6288_ROLE01(Rac2Native_6b0741c38bf00fee_u64, Rac2Native_6b0741c38bf00fee_s64, Rac2Native_6b0741c38bf00fee_s64, Rac2Native_6b0741c38bf00fee_s32);
extern void LVL_7_SIBERIUS_F6b0741c38bf00fee_AT002A6288_ROLE02(short, short, short);

void LVL_7_SIBERIUS_FUN_002A6288(void) {
 LVL_7_SIBERIUS_F6b0741c38bf00fee_AT002A6288_ROLE01(LVL_7_SIBERIUS_F6b0741c38bf00fee_AT002A6288_ROLE00[1],0,1,0x32);
 LVL_7_SIBERIUS_F6b0741c38bf00fee_AT002A6288_ROLE02(0x16,7,0);
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef int Rac2Native_28c929cadd7aca24_s32;

typedef unsigned char Rac2Native_28c929cadd7aca24_u8;

typedef struct {
    Rac2Native_28c929cadd7aca24_u8 prefix[0xc40];
    Rac2Native_28c929cadd7aca24_s32 selected;
    Rac2Native_28c929cadd7aca24_s32 index;
    Rac2Native_28c929cadd7aca24_u8 gap[0x1648];
    Rac2Native_28c929cadd7aca24_u8 *object;
} Rac2Native_28c929cadd7aca24_NativeResidentView;


extern Rac2Native_28c929cadd7aca24_NativeResidentView LVL_7_SIBERIUS_F28c929cadd7aca24_AT002C8460_ROLE00;

void LVL_7_SIBERIUS_FUN_002C8460(Rac2Native_28c929cadd7aca24_s32 selected, Rac2Native_28c929cadd7aca24_s32 index) {
    if (selected >= 0) {
        Rac2Native_28c929cadd7aca24_u8 *object = LVL_7_SIBERIUS_F28c929cadd7aca24_AT002C8460_ROLE00.object;
        Rac2Native_28c929cadd7aca24_s32 offset = object[0x43] * 4;
        Rac2Native_28c929cadd7aca24_u8 *table = *(Rac2Native_28c929cadd7aca24_u8 **)(object + 0x24);
        Rac2Native_28c929cadd7aca24_u8 *entry = *(Rac2Native_28c929cadd7aca24_u8 **)(table + offset + 0x48);
        if (index < entry[0x10]) {
            LVL_7_SIBERIUS_F28c929cadd7aca24_AT002C8460_ROLE00.selected = selected;
            LVL_7_SIBERIUS_F28c929cadd7aca24_AT002C8460_ROLE00.index = index;
        }
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef float Rac2Native_5fc519c90e0e763a_f32;


extern void LVL_7_SIBERIUS_F5fc519c90e0e763a_AT002C9728_ROLE00(Rac2Native_5fc519c90e0e763a_f32);

void LVL_7_SIBERIUS_FUN_002C9728(Rac2Native_5fc519c90e0e763a_f32 value) {
 LVL_7_SIBERIUS_F5fc519c90e0e763a_AT002C9728_ROLE00(-value);
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_74a5d71aacb394c6_u32;

typedef struct {
    Rac2Native_74a5d71aacb394c6_u32 first[64];
    Rac2Native_74a5d71aacb394c6_u32 second[64];
    unsigned char gap[0x20];
    int count;
    Rac2Native_74a5d71aacb394c6_u32 current;
} Rac2Native_74a5d71aacb394c6_ExtraIndexState48;


void LVL_7_SIBERIUS_FUN_00375D38(Rac2Native_74a5d71aacb394c6_ExtraIndexState48 *state, int index) {
    state->first[index] = 0;
    state->second[index] = 0;
    if (--state->count == 0) {
        state->current = 0;
    }
}


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_03c444112283bc5f_u32;


extern Rac2Native_03c444112283bc5f_u32 LVL_7_SIBERIUS_F03c444112283bc5f_AT00380800_ROLE00[139];

void LVL_7_SIBERIUS_FUN_00380800(void)
{
    int i;
    LVL_7_SIBERIUS_F03c444112283bc5f_AT00380800_ROLE00[138] = 5;
    LVL_7_SIBERIUS_F03c444112283bc5f_AT00380800_ROLE00[137] = 0;
    LVL_7_SIBERIUS_F03c444112283bc5f_AT00380800_ROLE00[136] = 0;
    for (i = 0; i < 64; ++i) {
        LVL_7_SIBERIUS_F03c444112283bc5f_AT00380800_ROLE00[i] = 0;
        LVL_7_SIBERIUS_F03c444112283bc5f_AT00380800_ROLE00[i + 64] = 0;
    }
    for (i = 7; i >= 0; --i)
        LVL_7_SIBERIUS_F03c444112283bc5f_AT00380800_ROLE00[i + 128] = 0;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_7_SIBERIUS_FUN_002A54C8(unsigned long param_1)
{
  return param_1;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_7_SIBERIUS_FUN_002C9F60(unsigned long param_1)
{
  return param_1;
}


/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int LVL_7_SIBERIUS_FUN_002D2430(void) {
    return 1;
}


/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int LVL_7_SIBERIUS_FUN_002D2438(void) {
    return 1;
}


extern void LVL_7_SIBERIUS_QWEN_11a4c157d102_AT002EA3A0_ROLE000(unsigned char *);

void LVL_7_SIBERIUS_FUN_002EA3A0(void *owner)
{
    LVL_7_SIBERIUS_QWEN_11a4c157d102_AT002EA3A0_ROLE000(owner);
}



void LVL_7_SIBERIUS_QWEN_407ee6f17a73_AT002EA440_ROLE001(int);
void LVL_7_SIBERIUS_QWEN_407ee6f17a73_AT002EA440_ROLE000(void*);

void LVL_7_SIBERIUS_FUN_002EA440(void *param)
{
  LVL_7_SIBERIUS_QWEN_407ee6f17a73_AT002EA440_ROLE001((int)param);
  *(unsigned int *)param = 0;
  LVL_7_SIBERIUS_QWEN_407ee6f17a73_AT002EA440_ROLE000(param);
}


void LVL_7_SIBERIUS_QWEN_5696fcf76f0c_AT00307F18_ROLE000(unsigned int *dst, unsigned int val, int size);

void LVL_7_SIBERIUS_FUN_00307F18(void)
{
    LVL_7_SIBERIUS_QWEN_5696fcf76f0c_AT00307F18_ROLE000((unsigned int *)0x70003A00, 0x40000000, 0x3C0);
}


unsigned int LVL_7_SIBERIUS_FUN_00322878(unsigned int param_1)
{
    unsigned int inner_ptr;
    unsigned int result;

    inner_ptr = *(unsigned int *)(param_1 + 0x68);
    result = *(unsigned int *)(inner_ptr + 0x18);
    return result;
}


/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls FUN_0027C540(0)
 *   - Calls FUN_0029C138()
 *   - Calls FUN_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */
extern void LVL_7_SIBERIUS_QWEN_523e38f49b74_AT0033C760_ROLE000(long);
extern void LVL_7_SIBERIUS_QWEN_523e38f49b74_AT0033C760_ROLE002(void);
extern void LVL_7_SIBERIUS_QWEN_523e38f49b74_AT0033C760_ROLE001(void);

int LVL_7_SIBERIUS_FUN_0033C760(void)
{
  LVL_7_SIBERIUS_QWEN_523e38f49b74_AT0033C760_ROLE000(0);
  LVL_7_SIBERIUS_QWEN_523e38f49b74_AT0033C760_ROLE002();
  LVL_7_SIBERIUS_QWEN_523e38f49b74_AT0033C760_ROLE001();
  return 0;
}


unsigned long long LVL_7_SIBERIUS_FUN_0033CB60(void);

extern void LVL_7_SIBERIUS_QWEN_f47929f95774_AT0033CB60_ROLE000(long);
extern void LVL_7_SIBERIUS_QWEN_f47929f95774_AT0033CB60_ROLE002(void);
extern void LVL_7_SIBERIUS_QWEN_f47929f95774_AT0033CB60_ROLE001(void);

unsigned long long LVL_7_SIBERIUS_FUN_0033CB60(void)
{
  LVL_7_SIBERIUS_QWEN_f47929f95774_AT0033CB60_ROLE000(0);
  LVL_7_SIBERIUS_QWEN_f47929f95774_AT0033CB60_ROLE002();
  LVL_7_SIBERIUS_QWEN_f47929f95774_AT0033CB60_ROLE001();
  return 0;
}


/* Function at 0x002cd8c0: FUN_002CD8C0
 * 
 * Disassembly summary:
 * - 12 instructions, 48 bytes total
 * - Prologue: save ra, allocate 16-byte stack frame
 * - Three calls to external functions:
 *   1. FUN_0027C540(0)
 *   2. FUN_0029C450()
 *   3. FUN_0027C660()
 * - Epilogue: restore ra, return 0, deallocate stack
 * - No local variables used
 * - Return type is void-like; returns zero in v0
 * - Delay slots are_NOP/unused in this case
 */

/* External function declarations (exact addresses from task metadata) */
extern void LVL_7_SIBERIUS_QWEN_cb305b1f1210_AT0033CE00_ROLE000(long);
extern void LVL_7_SIBERIUS_QWEN_cb305b1f1210_AT0033CE00_ROLE002(void);
extern void LVL_7_SIBERIUS_QWEN_cb305b1f1210_AT0033CE00_ROLE001(void);

long long LVL_7_SIBERIUS_FUN_0033CE00(void)
{
    LVL_7_SIBERIUS_QWEN_cb305b1f1210_AT0033CE00_ROLE000(0LL);
    LVL_7_SIBERIUS_QWEN_cb305b1f1210_AT0033CE00_ROLE002();
    LVL_7_SIBERIUS_QWEN_cb305b1f1210_AT0033CE00_ROLE001();
    return 0LL;
}


extern void LVL_7_SIBERIUS_QWEN_c23b3406f982_AT003421F8_ROLE000(long);
extern void LVL_7_SIBERIUS_QWEN_c23b3406f982_AT003421F8_ROLE002(void);
extern void LVL_7_SIBERIUS_QWEN_c23b3406f982_AT003421F8_ROLE001(void);

int LVL_7_SIBERIUS_FUN_003421F8(void)
{
    LVL_7_SIBERIUS_QWEN_c23b3406f982_AT003421F8_ROLE000(0);
    LVL_7_SIBERIUS_QWEN_c23b3406f982_AT003421F8_ROLE002();
    LVL_7_SIBERIUS_QWEN_c23b3406f982_AT003421F8_ROLE001();
    return 0;
}


void LVL_7_SIBERIUS_QWEN_68cf9ebb5ee2_AT00342368_ROLE000(long);
void LVL_7_SIBERIUS_QWEN_68cf9ebb5ee2_AT00342368_ROLE001(void);
void LVL_7_SIBERIUS_QWEN_68cf9ebb5ee2_AT00342368_ROLE002(void);

unsigned long long LVL_7_SIBERIUS_FUN_00342368(void)
{
    LVL_7_SIBERIUS_QWEN_68cf9ebb5ee2_AT00342368_ROLE000(0);
    LVL_7_SIBERIUS_QWEN_68cf9ebb5ee2_AT00342368_ROLE002();
    LVL_7_SIBERIUS_QWEN_68cf9ebb5ee2_AT00342368_ROLE001();
    return 0;
}



/* 
 * Function: FUN_002D2EE0
 * 
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls FUN_0027C540(0) (with zero argument)
 * - Calls FUN_0029C7A0()
 * - Calls FUN_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */

extern void LVL_7_SIBERIUS_QWEN_68f040eb20c9_AT00342420_ROLE000(long arg0);
extern void LVL_7_SIBERIUS_QWEN_68f040eb20c9_AT00342420_ROLE002(void);
extern void LVL_7_SIBERIUS_QWEN_68f040eb20c9_AT00342420_ROLE001(void);

unsigned long long LVL_7_SIBERIUS_FUN_00342420(void)
{
    LVL_7_SIBERIUS_QWEN_68f040eb20c9_AT00342420_ROLE000(0);
    LVL_7_SIBERIUS_QWEN_68f040eb20c9_AT00342420_ROLE002();
    LVL_7_SIBERIUS_QWEN_68f040eb20c9_AT00342420_ROLE001();
    return 0;
}


/* External function declarations as per target specification */
extern void LVL_7_SIBERIUS_QWEN_92ea7c2f4a5c_AT003427D0_ROLE000(long);
extern void LVL_7_SIBERIUS_QWEN_92ea7c2f4a5c_AT003427D0_ROLE001(void);
extern void LVL_7_SIBERIUS_QWEN_92ea7c2f4a5c_AT003427D0_ROLE002(void);

/* Implementation matching decompiled output */
long LVL_7_SIBERIUS_FUN_003427D0(void)
{
  LVL_7_SIBERIUS_QWEN_92ea7c2f4a5c_AT003427D0_ROLE000(0);
  LVL_7_SIBERIUS_QWEN_92ea7c2f4a5c_AT003427D0_ROLE002();
  LVL_7_SIBERIUS_QWEN_92ea7c2f4a5c_AT003427D0_ROLE001();
  return 0;
}


/* External functions declared with exact aliases from task.externals */
extern void LVL_7_SIBERIUS_QWEN_d01c568afacc_AT003428D0_ROLE000(long param_1);
extern void LVL_7_SIBERIUS_QWEN_d01c568afacc_AT003428D0_ROLE001(void);
extern void LVL_7_SIBERIUS_QWEN_d01c568afacc_AT003428D0_ROLE002(void);

/* Candidate function: FUN_002d3390 */
unsigned long long LVL_7_SIBERIUS_FUN_003428D0(void)
{
    LVL_7_SIBERIUS_QWEN_d01c568afacc_AT003428D0_ROLE000(0);
    LVL_7_SIBERIUS_QWEN_d01c568afacc_AT003428D0_ROLE002();
    LVL_7_SIBERIUS_QWEN_d01c568afacc_AT003428D0_ROLE001();
    return 0;
}


/* Target: FUN_002d5540 on MIPS (SCUS_972.68, -O2 -G0 -ffunction-sections)
 * Calls three externals: FUN_0027C540(int), FUN_0029CED8(void), FUN_0027C660(void)
 * Returns 0. Stack frame size 16 bytes. Delay slots filled.
 */
extern void LVL_7_SIBERIUS_QWEN_093381cf82c3_AT00344A80_ROLE000(long);
extern void LVL_7_SIBERIUS_QWEN_093381cf82c3_AT00344A80_ROLE002(void);
extern void LVL_7_SIBERIUS_QWEN_093381cf82c3_AT00344A80_ROLE001(void);

long long LVL_7_SIBERIUS_FUN_00344A80(void)
{
    LVL_7_SIBERIUS_QWEN_093381cf82c3_AT00344A80_ROLE000(0);
    LVL_7_SIBERIUS_QWEN_093381cf82c3_AT00344A80_ROLE002();
    LVL_7_SIBERIUS_QWEN_093381cf82c3_AT00344A80_ROLE001();
    return 0;
}


/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int LVL_7_SIBERIUS_FUN_0034E748(void) {
    return 1;
}


/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_4ecc6b5a4034_u8;
typedef unsigned int QwenRecovery_4ecc6b5a4034_u32;

/* Minimum external views; neither declaration allocates original game storage. */
typedef struct {
    QwenRecovery_4ecc6b5a4034_u8 prefix[0x24];
    QwenRecovery_4ecc6b5a4034_u32 word;
    QwenRecovery_4ecc6b5a4034_u8 tail[8];
} QwenRecovery_4ecc6b5a4034_ExtraResetRecord164;



extern QwenRecovery_4ecc6b5a4034_ExtraResetRecord164 LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE000[100];
extern QwenRecovery_4ecc6b5a4034_u32 LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE001[139];

void LVL_7_SIBERIUS_FUN_0037DD88(void)
{
    int i;
    for (i = 99; i >= 0; --i)
        LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE000[i].word = 0;
    LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE001[138] = 5;
    LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE001[137] = 0;
    LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE001[136] = 0;
    for (i = 0; i < 64; ++i) {
        LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE001[i] = 0;
        LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE001[i + 64] = 0;
    }
    for (i = 7; i >= 0; --i)
        LVL_7_SIBERIUS_QWEN_4ecc6b5a4034_AT0037DD88_ROLE001[i + 128] = 0;
}



void LVL_7_SIBERIUS_FUN_00427EF0(int param_1, unsigned int param_2)
{
  *(unsigned int*)(param_1 + 0x44) = param_2;
  return;
}


void LVL_7_SIBERIUS_FUN_00427EF8(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0x40) = param_2;
  return;
}


void LVL_7_SIBERIUS_FUN_00428050(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0x40) = param_2;
  return;
}


void LVL_7_SIBERIUS_FUN_004281A0(int param_1, unsigned int param_2)
{
  *(unsigned int*)(param_1 + 0x44) = param_2;
  return;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_7_SIBERIUS_FUN_00428270(unsigned long param_1)
{
  return param_1;
}


extern void LVL_7_SIBERIUS_QWEN_df8fc8ba49cf_AT0042AC38_ROLE000(unsigned char *owner, int value);

void LVL_7_SIBERIUS_FUN_0042AC38(unsigned char *owner, int value)
{
    LVL_7_SIBERIUS_QWEN_df8fc8ba49cf_AT0042AC38_ROLE000(owner + 8, value);
}



void* LVL_7_SIBERIUS_FUN_0042F638(void* param_1);

extern void LVL_7_SIBERIUS_QWEN_f353c206e726_AT0042F638_ROLE000(int);
extern unsigned long long LVL_7_SIBERIUS_QWEN_f353c206e726_AT0042F638_ROLE001(unsigned long long);

void* LVL_7_SIBERIUS_FUN_0042F638(void* param_1)
{
  LVL_7_SIBERIUS_QWEN_f353c206e726_AT0042F638_ROLE000((int)param_1 + 8);
  LVL_7_SIBERIUS_QWEN_f353c206e726_AT0042F638_ROLE001((int)param_1 + 0x2b0);
  return param_1;
}


extern int LVL_7_SIBERIUS_QWEN_f2f9288a4e34_AT0042F7D8_ROLE000(int);

int LVL_7_SIBERIUS_FUN_0042F7D8(int owner)
{
    int result;
    result = LVL_7_SIBERIUS_QWEN_f2f9288a4e34_AT0042F7D8_ROLE000(owner);
    return *(int *)(owner + 0x378) + result * 0x14;
}



extern int LVL_7_SIBERIUS_QWEN_e41cd63258f5_AT0042F810_ROLE000(unsigned char *);

int LVL_7_SIBERIUS_FUN_0042F810(int owner)
{
    return LVL_7_SIBERIUS_QWEN_e41cd63258f5_AT0042F810_ROLE000((unsigned char *)(owner + 0x2b0));
}



void LVL_7_SIBERIUS_QWEN_f29f80950ce7_AT00432F30_ROLE000(int);

void LVL_7_SIBERIUS_FUN_00432F30(int param_1)
{
  LVL_7_SIBERIUS_QWEN_f29f80950ce7_AT00432F30_ROLE000(param_1 + 0x228);
  return;
}


extern void LVL_7_SIBERIUS_QWEN_bf824305b9f7_AT00433848_ROLE000(unsigned char *owner, float *records);

void LVL_7_SIBERIUS_FUN_00433848(unsigned char *owner, float *records)
{
    *(float **)(owner + 0x250) = records;
    LVL_7_SIBERIUS_QWEN_bf824305b9f7_AT00433848_ROLE000(owner + 0x188, records);
}



void LVL_7_SIBERIUS_QWEN_61faeca45963_AT00433B10_ROLE000(int param_1);

void LVL_7_SIBERIUS_FUN_00433B10(int param_1)
{
  LVL_7_SIBERIUS_QWEN_61faeca45963_AT00433B10_ROLE000(param_1 + 0x188);
  return;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_7_SIBERIUS_FUN_00433C78(unsigned long param_1)
{
  return param_1;
}


extern int LVL_7_SIBERIUS_QWEN_6add11b33414_AT00434A28_ROLE000(unsigned char *owner);

int LVL_7_SIBERIUS_FUN_00434A28(unsigned char *owner)
{
    return LVL_7_SIBERIUS_QWEN_6add11b33414_AT00434A28_ROLE000(owner + 0x298);
}



extern void LVL_7_SIBERIUS_QWEN_de961518de48_AT00434A48_ROLE000(unsigned char *owner);

void LVL_7_SIBERIUS_FUN_00434A48(unsigned char *owner)
{
    LVL_7_SIBERIUS_QWEN_de961518de48_AT00434A48_ROLE000(owner + 0x298);
}



extern unsigned long long LVL_7_SIBERIUS_QWEN_7ba3cdeeb16b_AT00439368_ROLE000(unsigned long long);

unsigned long long LVL_7_SIBERIUS_FUN_00439368(unsigned long long value)
{
    LVL_7_SIBERIUS_QWEN_7ba3cdeeb16b_AT00439368_ROLE000(value);
    return value;
}



void LVL_7_SIBERIUS_FUN_004395B0(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0xb8) = param_2;
  return;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_7_SIBERIUS_FUN_0043A610(unsigned long param_1)
{
  return param_1;
}


void LVL_7_SIBERIUS_FUN_0043A950(int *param_1)
{
    param_1[0x150 / sizeof(int)] = 0;
}


void LVL_7_SIBERIUS_FUN_0043AAF0(int param_1, int param_2) {
    *(int *)(param_1 + 0x84) = param_2;
}


void LVL_7_SIBERIUS_FUN_0043AB38(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 32) = param_2;
  return;
}


/* Target: FUN_003427B0 — identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

unsigned long LVL_7_SIBERIUS_FUN_0043FA90(unsigned long param_1)
{
  return param_1;
}


/* Returns the constant integer 1. Matches FUN_0012F940 disassembly and decompilation. */
int LVL_7_SIBERIUS_FUN_00441B80(void) {
    return 1;
}


extern int LVL_7_SIBERIUS_QWEN_cc83cb329fcb_AT004433C0_ROLE000(unsigned char *);

int LVL_7_SIBERIUS_FUN_004433C0(int *owner)
{
    int result;
    long status;
    status = LVL_7_SIBERIUS_QWEN_cc83cb329fcb_AT004433C0_ROLE000((unsigned char *)owner);
    if (status == 0)
        result = *owner + owner[2] * 0xd0000;
    else
        result = 0;
    return result;
}

extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(char *local, char *first, char *second);
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4310(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_7_SIBERIUS_FUN_00399A80(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_7_SIBERIUS_Fc936841d_FUN_002E4310((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(char *local, char *first, char *second);
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4310(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_7_SIBERIUS_FUN_003AA070(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_7_SIBERIUS_Fc936841d_FUN_002E4310((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(char *local, char *first, char *second);
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4310(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_7_SIBERIUS_FUN_003B22E8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_7_SIBERIUS_Fc936841d_FUN_002E4310((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(char *local, char *first, char *second);
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4310(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_7_SIBERIUS_FUN_003C13A8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_7_SIBERIUS_Fc936841d_FUN_002E4310((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(char *local, char *first, char *second);
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4310(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_7_SIBERIUS_FUN_003D4610(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_7_SIBERIUS_Fc936841d_FUN_002E4310((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(char *local, char *first, char *second);
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4310(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_7_SIBERIUS_FUN_003DDD50(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_7_SIBERIUS_Fc936841d_FUN_002E4310((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(char *local, char *first, char *second);
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4310(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_7_SIBERIUS_FUN_0040C710(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_7_SIBERIUS_Fc936841d_FUN_002E4310((char *)&object[index - 1], (char *)&object[index - 2], local);
}
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(char *local, char *first, char *second);
extern void LVL_7_SIBERIUS_Fc936841d_FUN_002E4310(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif


void LVL_7_SIBERIUS_FUN_00415088(Vec16_Fc936841d *object, int index)
{
    char local[16];

    LVL_7_SIBERIUS_Fc936841d_FUN_002E4340(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    LVL_7_SIBERIUS_Fc936841d_FUN_002E4310((char *)&object[index - 1], (char *)&object[index - 2], local);
}



extern void LVL_7_SIBERIUS_F01bd4546_FUN_00427328(char *p, int v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(char *p, int v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(char *p, int v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(char *p, int v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(char *p, int v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(char *p, int v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(char *p, int v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(char *p, float v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(char *p, float v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(char *p, float v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(char *p, float v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(char *p, float v);
extern void LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(char *p, float v);

void LVL_7_SIBERIUS_FUN_0043E050(char *self, int x)
{
    char *p1, *p2, *p3, *p4, *p5, *p6;

    *(s32 *)(self + 5492) = x;
    if (*(s32 *)(self + 5496) != 0) {
        *(s32 *)(self + 5496) = 0;
        LVL_7_SIBERIUS_F01bd4546_FUN_00427328(self + 1464, 0);
        p1 = self + 3052;
        p2 = self + 3188;
        p3 = self + 3324;
        p4 = self + 3460;
        p5 = self + 3596;
        p6 = self + 3732;
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(p1, 1);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(p2, 1);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(p3, 1);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(p4, 1);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(p5, 1);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AAF8(p6, 1);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(p1, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(p2, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(p3, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(p4, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(p5, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        LVL_7_SIBERIUS_F01bd4546_FUN_0043AB40(p6, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
    }
}
extern void LVL_7_SIBERIUS_F70997ba9_FUN_003715E0(int a, int b);
extern void LVL_7_SIBERIUS_F70997ba9_FUN_002DC440(int a);
extern void *LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(int id);
extern int LVL_7_SIBERIUS_F70997ba9_FUN_002DF0F8(void *p, int i);
extern void LVL_7_SIBERIUS_F70997ba9_FUN_002DF080(void);
extern void LVL_7_SIBERIUS_F70997ba9_FUN_002DF518(int a, int b, long c, void *d, int e);
extern void LVL_7_SIBERIUS_F70997ba9_FUN_002DF070(void);
extern void LVL_7_SIBERIUS_F70997ba9_FUN_002DC560(void);

int LVL_7_SIBERIUS_FUN_00348CD8(int *arg0)
{
    int min;
    int v;
    int slot;
    int count;
    int off;

    LVL_7_SIBERIUS_F70997ba9_FUN_003715E0(66, 68);
    LVL_7_SIBERIUS_F70997ba9_FUN_003715E0(71, 11);
    LVL_7_SIBERIUS_F70997ba9_FUN_002DC440(0);
    min = LVL_7_SIBERIUS_F70997ba9_FUN_002DF0F8(LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11613), -1);
    v = LVL_7_SIBERIUS_F70997ba9_FUN_002DF0F8(LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11625), -1);
    if (v >= min)
        min = v;
    if (*(int *)0x1A79F0 != 0) {
        v = LVL_7_SIBERIUS_F70997ba9_FUN_002DF0F8(LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11614), -1);
        if (v >= min)
            min = v;
    }
    v = LVL_7_SIBERIUS_F70997ba9_FUN_002DF0F8(LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11626), -1);
    if (v >= min)
        min = v;
    v = LVL_7_SIBERIUS_F70997ba9_FUN_002DF0F8(LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11627), -1);
    if (v >= min)
        min = v;
    v = LVL_7_SIBERIUS_F70997ba9_FUN_002DF0F8(LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11599), -1);
    if (v >= min)
        min = v;
    slot = (arg0[8] - min) >> 1;
    if (slot <= 1)
        slot = 2;
    count = arg0[9] / (*(int *)0x1A79F0 != 0 ? 7 : 6);
    LVL_7_SIBERIUS_F70997ba9_FUN_002DF080();
    off = count - 6;
    LVL_7_SIBERIUS_F70997ba9_FUN_002DF518(slot, off, 0x80FFA888L, LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11613), -1);
    off += count;
    LVL_7_SIBERIUS_F70997ba9_FUN_002DF518(slot, off, 0x80FFA888L, LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11625), -1);
    off += count;
    LVL_7_SIBERIUS_F70997ba9_FUN_002DF518(slot, off, 0x80FFA888L, LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11626), -1);
    off += count;
    LVL_7_SIBERIUS_F70997ba9_FUN_002DF518(slot, off, 0x80FFA888L, LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11627), -1);
    off += count;
    LVL_7_SIBERIUS_F70997ba9_FUN_002DF518(slot, off, 0x80FFA888L, LVL_7_SIBERIUS_F70997ba9_FUN_002EA888(11599), -1);
    LVL_7_SIBERIUS_F70997ba9_FUN_002DF070();
    LVL_7_SIBERIUS_F70997ba9_FUN_002DC560();
    return 2;
}
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(float);

void LVL_7_SIBERIUS_FUN_00399648(int unused, float *p, int n)
{
    float *v;
    int count;
    if (n <= 0)
        return;
    v = p;
    count = n;
    do {
        v[0] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[0], v[3]);
        v[1] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[1], v[4]);
        v[2] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[2], v[5]);
        v[9] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[9], v[12]);
        v[10] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[10], v[13]);
        v[11] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[11], v[14]);
        v[20] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E4900(v[0]) * v[6];
        v[21] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(v[1]) * v[7];
        v[22] = -LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(v[2]) * v[8];
        v[24] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E4900(v[9]) * v[15];
        v[25] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(v[10]) * v[16];
        v[26] = -LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(v[11]) * v[17];
        v += 32;
    } while (--count != 0);
}
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(float);

void LVL_7_SIBERIUS_FUN_003D41D8(int unused, float *p, int n)
{
    float *v;
    int count;
    if (n <= 0)
        return;
    v = p;
    count = n;
    do {
        v[0] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[0], v[3]);
        v[1] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[1], v[4]);
        v[2] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[2], v[5]);
        v[9] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[9], v[12]);
        v[10] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[10], v[13]);
        v[11] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E5318(v[11], v[14]);
        v[20] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E4900(v[0]) * v[6];
        v[21] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(v[1]) * v[7];
        v[22] = -LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(v[2]) * v[8];
        v[24] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E4900(v[9]) * v[15];
        v[25] = LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(v[10]) * v[16];
        v[26] = -LVL_7_SIBERIUS_F307ea0ee_FUN_002E4918(v[11]) * v[17];
        v += 32;
    } while (--count != 0);
}
#ifndef RAC2_T_WORKER_F9E2CD219
#define RAC2_T_WORKER_F9E2CD219
typedef struct {
    unsigned char pad00[76];
    short field4C;
    unsigned char pad4E[2];
    int field50;
    float field54;
    float field58;
} Worker_F9e2cd219;
#endif


#ifndef RAC2_T_OWNER_F9E2CD219
#define RAC2_T_OWNER_F9E2CD219
typedef struct {
    unsigned char pad00[104];
    Worker_F9e2cd219 *child;
} Owner_F9e2cd219;
#endif


extern float LVL_7_SIBERIUS_F9e2cd219_FUN_00310A10(float value);
extern void LVL_7_SIBERIUS_F9e2cd219_FUN_00316C58(void *out, void *in, void *tmp, int mode, float value);
extern void LVL_7_SIBERIUS_F9e2cd219_FUN_0037DA48(void *owner, void *out);

void LVL_7_SIBERIUS_FUN_0037D960(Owner_F9e2cd219 *self)
{
    Worker_F9e2cd219 *child = self->child;

    LVL_7_SIBERIUS_F9e2cd219_FUN_00316C58((char *)child + 48, (char *)child + 16, (char *)child + 32, 0,
            LVL_7_SIBERIUS_F9e2cd219_FUN_00310A10(child->field54));

    child->field54 = child->field54 + child->field58;
    LVL_7_SIBERIUS_F9e2cd219_FUN_0037DA48(self, (char *)child + 48);

    if (child->field54 > 0.9f)
        child->field50 = 1;
    else
        child->field50 = 0;

    if (child->field54 >= 1.0f) {
        child->field54 = 1.0f;
        child->field4C = 1;
    }
}
#ifndef RAC2_T_WORKER_F9E2CD219
#define RAC2_T_WORKER_F9E2CD219
typedef struct {
    unsigned char pad00[76];
    short field4C;
    unsigned char pad4E[2];
    int field50;
    float field54;
    float field58;
} Worker_F9e2cd219;
#endif


#ifndef RAC2_T_OWNER_F9E2CD219
#define RAC2_T_OWNER_F9E2CD219
typedef struct {
    unsigned char pad00[104];
    Worker_F9e2cd219 *child;
} Owner_F9e2cd219;
#endif


extern float LVL_7_SIBERIUS_F9e2cd219_FUN_00310A10(float value);
extern void LVL_7_SIBERIUS_F9e2cd219_FUN_00316C58(void *out, void *in, void *tmp, int mode, float value);
extern void LVL_7_SIBERIUS_F9e2cd219_FUN_003804E8(void *owner, void *out);

void LVL_7_SIBERIUS_FUN_00380400(Owner_F9e2cd219 *self)
{
    Worker_F9e2cd219 *child = self->child;

    LVL_7_SIBERIUS_F9e2cd219_FUN_00316C58((char *)child + 48, (char *)child + 16, (char *)child + 32, 0,
            LVL_7_SIBERIUS_F9e2cd219_FUN_00310A10(child->field54));

    child->field54 = child->field54 + child->field58;
    LVL_7_SIBERIUS_F9e2cd219_FUN_003804E8(self, (char *)child + 48);

    if (child->field54 > 0.9f)
        child->field50 = 1;
    else
        child->field50 = 0;

    if (child->field54 >= 1.0f) {
        child->field54 = 1.0f;
        child->field4C = 1;
    }
}
extern void LVL_7_SIBERIUS_F6df9730c_FUN_002E4188(char *dst, int *src, int count);

void LVL_7_SIBERIUS_FUN_002FEF48(char *dst, unsigned char *src)
{
    int table[256];
    int tmp[16];
    int *q;
    int i, j, k;

    for (i = 0; i < 256; i++) {
        table[i] = 0;
        if (i & 0x01) table[i] = 0x0000000f;
        if (i & 0x02) table[i] |= 0x000000f0;
        if (i & 0x04) table[i] |= 0x00000f00;
        if (i & 0x08) table[i] |= 0x0000f000;
        if (i & 0x10) table[i] |= 0x000f0000;
        if (i & 0x20) table[i] |= 0x00f00000;
        if (i & 0x40) table[i] |= 0x0f000000;
        if (i & 0x80) table[i] |= 0xf0000000;
    }
    for (j = 0; j < 128; j++) {
        char *next;
        q = tmp;
        next = dst + 64;
        for (k = 15; k >= 0; k--) {
            *q++ = table[*src++];
        }
        LVL_7_SIBERIUS_F6df9730c_FUN_002E4188(dst, tmp, 64);
        dst = next;
        LVL_7_SIBERIUS_F6df9730c_FUN_002E4188(dst, tmp, 64);
        dst += 64;
        LVL_7_SIBERIUS_F6df9730c_FUN_002E4188(dst, tmp, 64);
        dst += 64;
        LVL_7_SIBERIUS_F6df9730c_FUN_002E4188(dst, tmp, 64);
        dst += 64;
    }
}
extern void LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2600(void *);
extern void LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2440(void *);
extern int LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2818(void *);
extern void LVL_7_SIBERIUS_Fdb046c5d_FUN_002E45F0(float, void *, void *);
extern void LVL_7_SIBERIUS_Fdb046c5d_FUN_002E4440(void *, void *, void *);
extern void LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2DA0(void *, void *, void *);
extern void LVL_7_SIBERIUS_Fdb046c5d_FUN_0031B290(void *, void *, int);
extern int LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2EC0(void *, void *, void *, float, float);
extern int LVL_7_SIBERIUS_Fdb046c5d_FUN_00355488(int, int, void *);
extern void LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2A80(void *, int, void *);
extern int LVL_7_SIBERIUS_Fdb046c5d_FUN_00355488(int, int, void *);
extern void LVL_7_SIBERIUS_Fdb046c5d_FUN_00355868(int, void *);
extern char LVL_7_SIBERIUS_Fdb046c5d_D_001BF680[];

int LVL_7_SIBERIUS_FUN_002D2028(char *obj)
{
    float buf[4];
    float out[4];
    char *p;
    char *s1;
    unsigned char k;
    int r;
    int s4;
    int s5;

    p = *(char **)(obj + 104);
    k = *(unsigned char *)(p + 92);
    if (k >= 3)
        return 1;
    if (k != 0)
        LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2600(obj);
    else
        LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2440(obj);

    s5 = LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2818(obj);
    if (s5 == -1)
        return 0;

    s1 = LVL_7_SIBERIUS_Fdb046c5d_D_001BF680;
    s4 = -1;
    LVL_7_SIBERIUS_Fdb046c5d_FUN_002E45F0(1.0f, s1, s1);
    LVL_7_SIBERIUS_Fdb046c5d_FUN_002E4440(buf, s1, p);
    LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2DA0(obj, p + 16, buf);
    LVL_7_SIBERIUS_Fdb046c5d_FUN_0031B290(obj + 16, out, 1);
    r = LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2EC0(p, s1, out, *(float *)(p + 56), *(float *)(p + 60));
    if (r == 0) {
        if (*(unsigned char *)(p + 94) != 255 && *(unsigned char *)(p + 92) == 0)
            s4 = LVL_7_SIBERIUS_Fdb046c5d_FUN_00355488(*(unsigned char *)(p + 94), 0, obj);
        LVL_7_SIBERIUS_Fdb046c5d_FUN_002D2A80(obj, s5, out);
    } else {
        if (*(unsigned char *)(p + 94) != 255)
            s4 = LVL_7_SIBERIUS_Fdb046c5d_FUN_00355488(*(unsigned char *)(p + 94), 0, obj);
    }
    if (s4 != -1)
        LVL_7_SIBERIUS_Fdb046c5d_FUN_00355868(s4, p + 32);
    return 0;
}
extern void LVL_7_SIBERIUS_F7242f0a4_FUN_002E4398(char *out, void *source, float value);
extern void LVL_7_SIBERIUS_F7242f0a4_FUN_0041CD50(char *buffer, int mode);
extern void LVL_7_SIBERIUS_F7242f0a4_FUN_0041CBF0(int value, char *buffer);
extern void LVL_7_SIBERIUS_F7242f0a4_FUN_002E4310(char *first, char *second, char *third);
extern float LVL_7_SIBERIUS_F7242f0a4_FUN_002E4418(void *owner, char *buffer);

extern int LVL_7_SIBERIUS_F7242f0a4_D_001B9260[];

void LVL_7_SIBERIUS_FUN_0041D418(void *owner, int flag, float value)
{
    char buffer[32];
    int *root = LVL_7_SIBERIUS_F7242f0a4_D_001B9260;

    LVL_7_SIBERIUS_F7242f0a4_FUN_002E4398(buffer, root + 8, value);
    if (flag)
        LVL_7_SIBERIUS_F7242f0a4_FUN_0041CD50(buffer + 16, 1);
    else
        LVL_7_SIBERIUS_F7242f0a4_FUN_0041CBF0(root[-4], buffer + 16);
    LVL_7_SIBERIUS_F7242f0a4_FUN_002E4310(buffer, buffer, buffer + 16);
    LVL_7_SIBERIUS_F7242f0a4_FUN_002E4398(owner, root + 12, LVL_7_SIBERIUS_F7242f0a4_FUN_002E4418(root + 12, buffer));
}
extern char LVL_7_SIBERIUS_F45821cfb_D_001C6F80[];
extern void LVL_7_SIBERIUS_F45821cfb_FUN_002E42D8(char *);

void LVL_7_SIBERIUS_FUN_004400B8(void)
{
    float *p = (float *)LVL_7_SIBERIUS_F45821cfb_D_001C6F80;

    p[224] = 0.4f;
    p[225] = 0.8f;
    p[226] = 1.2f;
    *(int *)&p[227] = 0;
    p[228] = 0.577f;
    p[229] = 0.577f;
    p[230] = -0.577f;
    *(int *)&p[231] = 0;
    LVL_7_SIBERIUS_F45821cfb_FUN_002E42D8((char *)&p[232]);
    LVL_7_SIBERIUS_F45821cfb_FUN_002E42D8((char *)&p[236]);
}
extern char LVL_7_SIBERIUS_Fd8e166aa_D_001BC640[];

void LVL_7_SIBERIUS_FUN_002D9798(void)
{
    char *g = LVL_7_SIBERIUS_Fd8e166aa_D_001BC640;
    int i = 0;
    int *table = *(int **)(g + 8);
    char *p = (char *)table + table[*(unsigned char *)0x1A7BB4];
    int n = *(int *)p;

    *(char **)(g + 12) = p + 8;
    *(int *)(g + 16) = n;
    for (i = 0; i < *(int *)(g + 16); i++) {
        char *q = *(char **)(g + 12);
        char *r = q - 8;

        *(int *)(q + i * 16) = *(int *)(q + i * 16) + (int)r;
    }
}
extern char LVL_7_SIBERIUS_F7cb419c1_D_001FF080[];

extern int LVL_7_SIBERIUS_F7cb419c1_FUN_0034DB58(int arg);

int LVL_7_SIBERIUS_FUN_00344350(void)
{
    char *p = LVL_7_SIBERIUS_F7cb419c1_D_001FF080;

    *(int *)(p + 460) = LVL_7_SIBERIUS_F7cb419c1_FUN_0034DB58(*(int *)(p + 460));
    return 0;
}
extern char LVL_7_SIBERIUS_F0a76d85b_D_001B90C0[];

extern void LVL_7_SIBERIUS_F0a76d85b_FUN_002E4AE0(char *p);
extern void LVL_7_SIBERIUS_F0a76d85b_FUN_002D9F60(void);

void LVL_7_SIBERIUS_FUN_00440148(void)
{
    char *p = LVL_7_SIBERIUS_F0a76d85b_D_001B90C0;

    *(int *)(p + 320) = 0;
    *(int *)(p + 324) = 0;
    *(int *)(p + 328) = 0;
    LVL_7_SIBERIUS_F0a76d85b_FUN_002E4AE0(p + 880);
    LVL_7_SIBERIUS_F0a76d85b_FUN_002D9F60();
}
extern char LVL_7_SIBERIUS_F391de845_D_001B9200[];
extern float LVL_7_SIBERIUS_F391de845_FUN_002E44D0(char *a, char *b);
extern float LVL_7_SIBERIUS_F391de845_FUN_00353ED8(void *self, float d, float x, float y);

float LVL_7_SIBERIUS_FUN_00353FD0(char *self, char *p)
{
    float v = LVL_7_SIBERIUS_F391de845_FUN_002E44D0(p, LVL_7_SIBERIUS_F391de845_D_001B9200);
    float *q = *(float **)(self + 8);

    return LVL_7_SIBERIUS_F391de845_FUN_00353ED8(q, v, q[0], q[1]);
}
extern int LVL_7_SIBERIUS_F2f080549_D_001A8FF4 __attribute__((sda));
extern char LVL_7_SIBERIUS_F2f080549_D_001B1F50[] __attribute__((sda));
extern char LVL_7_SIBERIUS_F2f080549_D_001A9000[] __attribute__((sda));
extern float LVL_7_SIBERIUS_F2f080549_FUN_002E44D0(char *a, char *b);

float LVL_7_SIBERIUS_FUN_0031B668(char *p)
{
    float v;

    if (LVL_7_SIBERIUS_F2f080549_D_001A8FF4 == 0) {
        v = LVL_7_SIBERIUS_F2f080549_FUN_002E44D0(p, LVL_7_SIBERIUS_F2f080549_D_001B1F50);
    } else {
        v = 100.0f - LVL_7_SIBERIUS_F2f080549_FUN_002E44D0(p, LVL_7_SIBERIUS_F2f080549_D_001A9000);
    }
    return v;
}
extern char LVL_7_SIBERIUS_Fa76f1772_D_001BF660[];
extern void LVL_7_SIBERIUS_Fa76f1772_FUN_002E4340(char *local, char *data);
extern float LVL_7_SIBERIUS_Fa76f1772_FUN_002E4418(char *local, char *p);

int LVL_7_SIBERIUS_FUN_004208F0(int a0, int a1)
{
    char local[16];
    int s0;
    int r;

    if (a1 != 1) {
        r = 0;
    } else {
        s0 = *(int *)(a0 + 112) + 352;
        LVL_7_SIBERIUS_Fa76f1772_FUN_002E4340(local, LVL_7_SIBERIUS_Fa76f1772_D_001BF660);
        r = LVL_7_SIBERIUS_Fa76f1772_FUN_002E4418(local, (char *)s0) < 0.0f ? 1 : 0;
    }
    return r;
}
extern void LVL_7_SIBERIUS_F46b43b72_FUN_00324CA8(int value, char *target);
extern void LVL_7_SIBERIUS_F46b43b72_FUN_00324E70(int value);

extern int LVL_7_SIBERIUS_F46b43b72_D_001BCF00[];
extern int LVL_7_SIBERIUS_F46b43b72_D_0014B540[];

int LVL_7_SIBERIUS_FUN_002FAA90(int index)
{
    int j = index + 1;
    int *d = LVL_7_SIBERIUS_F46b43b72_D_001BCF00;
    int *b = LVL_7_SIBERIUS_F46b43b72_D_0014B540;
    int *t = (int *)((char *)b + 25416);
    int n = d[12] * 332;
    int hold = d[28];
    int j4 = j * 4;
    int cur = *(int *)((char *)t + (n + index * 4));
    int next = *(int *)((char *)t + (j4 + n));

    n = next - cur;
    if (n > 0) {
        LVL_7_SIBERIUS_F46b43b72_FUN_00324CA8(hold, (char *)(cur + b[6341]));
        LVL_7_SIBERIUS_F46b43b72_FUN_00324E70(0);
    }
    return 1;
}
extern void LVL_7_SIBERIUS_Fa2d20de7_FUN_00310C98(void *object, float first, float second);
extern void LVL_7_SIBERIUS_Fa2d20de7_FUN_002E4310(char *first, char *second, void *third);
extern int LVL_7_SIBERIUS_Fa2d20de7_FUN_002D4510(void *first, char *second, int mode, int value, int extra);
extern void LVL_7_SIBERIUS_Fa2d20de7_FUN_002E4340(void *first, void *second, void *third);
extern void LVL_7_SIBERIUS_Fa2d20de7_FUN_002E4398(void *first, void *second, float value);

extern short LVL_7_SIBERIUS_Fa2d20de7_D_001B9200[];
extern short LVL_7_SIBERIUS_Fa2d20de7_D_001BF660[];
extern int LVL_7_SIBERIUS_Fa2d20de7_D_001886CC[];

void LVL_7_SIBERIUS_FUN_00353D88(void *object)
{
    LVL_7_SIBERIUS_Fa2d20de7_FUN_00310C98(object, 0.5f, 6.0f);
    LVL_7_SIBERIUS_Fa2d20de7_FUN_002E4310(object, object, LVL_7_SIBERIUS_Fa2d20de7_D_001B9200);
    if (LVL_7_SIBERIUS_Fa2d20de7_FUN_002D4510(LVL_7_SIBERIUS_Fa2d20de7_D_001B9200, object, 130, LVL_7_SIBERIUS_Fa2d20de7_D_001886CC[0], 0)) {
        LVL_7_SIBERIUS_Fa2d20de7_FUN_002E4340(object, LVL_7_SIBERIUS_Fa2d20de7_D_001BF660, LVL_7_SIBERIUS_Fa2d20de7_D_001B9200);
        LVL_7_SIBERIUS_Fa2d20de7_FUN_002E4398(object, object, 0.75f);
        LVL_7_SIBERIUS_Fa2d20de7_FUN_002E4310(object, object, LVL_7_SIBERIUS_Fa2d20de7_D_001B9200);
    }
}
extern char LVL_7_SIBERIUS_F15d5f4fb_D_001B90C0[];
extern char LVL_7_SIBERIUS_F15d5f4fb_D_00189E20[];
extern float LVL_7_SIBERIUS_F15d5f4fb_FUN_002E49C8(float a, float b);
extern float LVL_7_SIBERIUS_F15d5f4fb_FUN_002E5400(float a, float b);
extern float LVL_7_SIBERIUS_F15d5f4fb_FUN_002E44D0(char *a, char *b);

void LVL_7_SIBERIUS_FUN_00424C48(char *o)
{
    char *B = LVL_7_SIBERIUS_F15d5f4fb_D_001B90C0;
    char *D = LVL_7_SIBERIUS_F15d5f4fb_D_00189E20;
    float *p = *(float **)(D + 8848);
    float r = LVL_7_SIBERIUS_F15d5f4fb_FUN_002E5400(*(float *)(B + 344),
                      LVL_7_SIBERIUS_F15d5f4fb_FUN_002E49C8(p[4] - *(float *)(B + 320),
                              p[5] - *(float *)(B + 324)));

    if (r < 0.5585054f) {
        r = LVL_7_SIBERIUS_F15d5f4fb_FUN_002E44D0(D + 128, B + 320);
        if (r < 8.0f) {
            *(char *)(B + 659) = 0;
            *(short *)(o + 126) = 2;
            *(float *)(B + 692) = 0.018f;
            *(float *)(B + 680) = 0.018f;
        } else {
            *(short *)(o + 126) = 4;
        }
    } else {
        *(short *)(o + 126) = 4;
    }
    *(char *)(o + 125) = 0;
}

#ifndef RAC2_T_S8_F4778F810
#define RAC2_T_S8_F4778F810
typedef signed char s8_F4778f810;
#endif

#ifndef RAC2_T_S16_F4778F810
#define RAC2_T_S16_F4778F810
typedef signed short s16_F4778f810;
#endif

#ifndef RAC2_T_U16_F4778F810
#define RAC2_T_U16_F4778F810
typedef unsigned short u16_F4778f810;
#endif





extern void LVL_7_SIBERIUS_F4778f810_FUN_0031B3E0(char *a, char *b, char *c, f32 d);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E47D0(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E50D8(char *a, char *b);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E4EB8(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E47D0(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E4340(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E4340(char *a, char *b, char *c);

#ifndef RAC2_T_V4_F4778F810
#define RAC2_T_V4_F4778F810
typedef struct {
    f32 x, y, z, w;
} V4_F4778f810;
#endif


#ifndef RAC2_T_SUB_F4778F810
#define RAC2_T_SUB_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x10];
    u8 at020[0x28];
    f32 f048;
} Sub_F4778f810;
#endif


#ifndef RAC2_T_OBJ_F4778F810
#define RAC2_T_OBJ_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x58];
    char *p068;
    u8 pad06C[0xC0 - 0x6C];
    u8 at0C0[0x10];
} Obj_F4778f810;
#endif


void LVL_7_SIBERIUS_FUN_002D2440(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *p = (Sub_F4778f810 *)obj->p068;

    LVL_7_SIBERIUS_F4778f810_FUN_0031B3E0((char *)obj + 0x10, (char *)p, (char *)p, p->f048);
    LVL_7_SIBERIUS_F4778f810_FUN_002E4310((char *)obj + 0x10, (char *)obj + 0x10, (char *)p);
    LVL_7_SIBERIUS_F4778f810_FUN_002E47D0((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    LVL_7_SIBERIUS_F4778f810_FUN_002E50D8((char *)p + 0x10, (char *)&tmp[3]);
    LVL_7_SIBERIUS_F4778f810_FUN_002E4EB8((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    LVL_7_SIBERIUS_F4778f810_FUN_002E47D0((char *)&tmp[1], (char *)p + 0x20, (char *)obj + 0xC0);
    LVL_7_SIBERIUS_F4778f810_FUN_002E4340((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    LVL_7_SIBERIUS_F4778f810_FUN_002E4340((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}

#ifndef RAC2_T_S8_F4778F810
#define RAC2_T_S8_F4778F810
typedef signed char s8_F4778f810;
#endif

#ifndef RAC2_T_S16_F4778F810
#define RAC2_T_S16_F4778F810
typedef signed short s16_F4778f810;
#endif

#ifndef RAC2_T_U16_F4778F810
#define RAC2_T_U16_F4778F810
typedef unsigned short u16_F4778f810;
#endif





extern void LVL_7_SIBERIUS_F4778f810_FUN_0031B3E0(char *a, char *b, char *c, f32 d);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E47D0(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E50D8(char *a, char *b);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E4EB8(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E47D0(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E4340(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4778f810_FUN_002E4340(char *a, char *b, char *c);

#ifndef RAC2_T_V4_F4778F810
#define RAC2_T_V4_F4778F810
typedef struct {
    f32 x, y, z, w;
} V4_F4778f810;
#endif


#ifndef RAC2_T_SUB_F4778F810
#define RAC2_T_SUB_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x10];
    u8 at020[0x28];
    f32 f048;
} Sub_F4778f810;
#endif


#ifndef RAC2_T_OBJ_F4778F810
#define RAC2_T_OBJ_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x58];
    char *p068;
    u8 pad06C[0xC0 - 0x6C];
    u8 at0C0[0x10];
} Obj_F4778f810;
#endif


void LVL_7_SIBERIUS_FUN_002D2520(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *p = (Sub_F4778f810 *)obj->p068;

    LVL_7_SIBERIUS_F4778f810_FUN_0031B3E0((char *)obj + 0x10, (char *)p, (char *)p, p->f048);
    LVL_7_SIBERIUS_F4778f810_FUN_002E4310((char *)obj + 0x10, (char *)obj + 0x10, (char *)p);
    LVL_7_SIBERIUS_F4778f810_FUN_002E47D0((char *)&tmp[0], (char *)p + 0x20, (char *)obj + 0xC0);
    LVL_7_SIBERIUS_F4778f810_FUN_002E50D8((char *)p + 0x10, (char *)&tmp[3]);
    LVL_7_SIBERIUS_F4778f810_FUN_002E4EB8((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    LVL_7_SIBERIUS_F4778f810_FUN_002E47D0((char *)&tmp[1], (char *)p + 0x20, (char *)obj + 0xC0);
    LVL_7_SIBERIUS_F4778f810_FUN_002E4340((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    LVL_7_SIBERIUS_F4778f810_FUN_002E4340((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}


extern void LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(int arg0, int arg1, int arg2, int arg3);
extern int LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(float value);
extern void LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(int arg0, int arg1, int arg2, int arg3);
extern int LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(float value);
extern void LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(int arg0, int arg1, int arg2, int arg3);
extern int LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(float value);
extern void LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(int arg0, int arg1, int arg2, int arg3);
extern int LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(float value);
extern void LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(int arg0, int arg1, int arg2, int arg3);
extern int LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(float value);
extern void LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(int arg0, int arg1, int arg2, int arg3);

#ifndef RAC2_T_RESIDENTSTATE_FD160FB9C
#define RAC2_T_RESIDENTSTATE_FD160FB9C
typedef struct {
    u8 pad000[0x1b8];
    int f1B8;
    u8 pad1bc[0xc2c - 0x1bc];
    int fC2C;
    u8 padc30[0x149d - 0xc30];
    u8 b149D;
    u8 pad149e[0x2290 - 0x149e];
    u8 *p2290;
    int f2294;
} ResidentState_Fd160fb9c;
#endif


extern ResidentState_Fd160fb9c LVL_7_SIBERIUS_Fd160fb9c_D_00189E20;

void LVL_7_SIBERIUS_FUN_002A6520(void)
{
    int selector;

    if (LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.f2294 == 2) {
        if (LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.f1B8 < 15)
            return;
    }

    selector = LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.b149D;

    if (LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.f2294 == 2) {
        if (LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.f1B8 == 22)
            LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(selector, 0, 1, 30);
    }

    switch (LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.p2290[67]) {
    case 3:
        if (LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.fC2C != 0)
            return;
        if (LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(49.5f) != 0)
            LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(selector, 0, 1, 30);
        if (LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(17.0f) != 0)
            LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(selector, 1, 1, 30);
        return;
    case 4:
        if (LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.fC2C != 0)
            return;
        if (LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(12.5f) != 0)
            LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(selector, 0, 1, 30);
        if (LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(1.0f) != 0)
            LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(selector, 1, 1, 30);
        return;
    case 20:
        if (LVL_7_SIBERIUS_Fd160fb9c_D_00189E20.fC2C != 0)
            return;
        if (LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(8.0f) != 0)
            LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(selector, 0, 1, 30);
        if (LVL_7_SIBERIUS_Fd160fb9c_FUN_002B2690(21.0f) != 0)
            LVL_7_SIBERIUS_Fd160fb9c_FUN_002A62C8(selector, 1, 1, 30);
        return;
    }
}
#ifndef RAC2_T_PERSISTENT_F882F1178
#define RAC2_T_PERSISTENT_F882F1178
typedef struct {
    unsigned char pad0[4960];
    void *p1360;
    void *p1364;
    void *p1368;
    unsigned char pad1[4512];
    float f250C;
    float f2510;
    float f2514;
} Persistent_F882f1178;
#endif


#ifndef RAC2_T_NODE_F882F1178
#define RAC2_T_NODE_F882F1178
typedef struct {
    unsigned char pad[120];
    int field120;
} Node_F882f1178;
#endif


extern Persistent_F882f1178 LVL_7_SIBERIUS_F882f1178_D_00189E20;
extern int LVL_7_SIBERIUS_F882f1178_D_001A8F00 __attribute__((sda));

extern float LVL_7_SIBERIUS_F882f1178_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F882f1178_FUN_002E4918(float);
extern int LVL_7_SIBERIUS_F882f1178_FUN_002E54B8(int, int, float);
extern float LVL_7_SIBERIUS_F882f1178_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F882f1178_FUN_002E5318(float, float);
extern float LVL_7_SIBERIUS_F882f1178_FUN_002E4918(float);
extern int LVL_7_SIBERIUS_F882f1178_FUN_002E54B8(int, int, float);
extern void LVL_7_SIBERIUS_F882f1178_FUN_0031CA40(int, float *, int, int, float);
extern void LVL_7_SIBERIUS_F882f1178_FUN_0031CA40(int, float *, int, int, float);

void LVL_7_SIBERIUS_FUN_002CA9E8(void)
{
    Node_F882f1178 *node;

    node = (Node_F882f1178 *)LVL_7_SIBERIUS_F882f1178_D_00189E20.p1360;
    if (node != 0) {
        if (*(int *)0x1A8F00 == 2)
            LVL_7_SIBERIUS_F882f1178_D_00189E20.f250C = LVL_7_SIBERIUS_F882f1178_FUN_002E5318(LVL_7_SIBERIUS_F882f1178_D_00189E20.f250C, 0.020362177863717079f);
        else
            LVL_7_SIBERIUS_F882f1178_D_00189E20.f250C = LVL_7_SIBERIUS_F882f1178_FUN_002E5318(LVL_7_SIBERIUS_F882f1178_D_00189E20.f250C, 0.034906592220067978f);
        node->field120 = LVL_7_SIBERIUS_F882f1178_FUN_002E54B8(0xd2d2d2, 0x285050,
                                 LVL_7_SIBERIUS_F882f1178_FUN_002E4918(LVL_7_SIBERIUS_F882f1178_D_00189E20.f250C) * 0.5f + 0.5f);
    }
    node = (Node_F882f1178 *)LVL_7_SIBERIUS_F882f1178_D_00189E20.p1364;
    if (node != 0) {
        if (LVL_7_SIBERIUS_F882f1178_D_001A8F00 != 2) {
            float limit;
            int which;

            limit = LVL_7_SIBERIUS_F882f1178_FUN_002E5318(LVL_7_SIBERIUS_F882f1178_D_00189E20.f2510, 0.049451004713773727f);
            LVL_7_SIBERIUS_F882f1178_D_00189E20.f2510 = limit;
            which = 0x1ee628;
            if (limit > 0.0f && limit < 1.9198623895645142f) {
                which = 0x1e1ed2;
            }
            node->field120 = LVL_7_SIBERIUS_F882f1178_FUN_002E54B8(node->field120, which, 0.070000000298023224f);
        } else {
            LVL_7_SIBERIUS_F882f1178_D_00189E20.f2510 = LVL_7_SIBERIUS_F882f1178_FUN_002E5318(LVL_7_SIBERIUS_F882f1178_D_00189E20.f2510, 0.026179943233728409f);
            node->field120 = LVL_7_SIBERIUS_F882f1178_FUN_002E54B8(0x1e1ed2, 0x1e1e50,
                                     LVL_7_SIBERIUS_F882f1178_FUN_002E4918(LVL_7_SIBERIUS_F882f1178_D_00189E20.f2510) * 0.5f + 0.5f);
        }
    }
    if (LVL_7_SIBERIUS_F882f1178_D_00189E20.p1368 != 0) {
        if (LVL_7_SIBERIUS_F882f1178_D_001A8F00 == 2)
            LVL_7_SIBERIUS_F882f1178_FUN_0031CA40((int)LVL_7_SIBERIUS_F882f1178_D_00189E20.p1368, &LVL_7_SIBERIUS_F882f1178_D_00189E20.f2514, 0xdcdcdc, 0x323232,
                    0.026179943233728409f);
        else
            LVL_7_SIBERIUS_F882f1178_FUN_0031CA40((int)LVL_7_SIBERIUS_F882f1178_D_00189E20.p1368, &LVL_7_SIBERIUS_F882f1178_D_00189E20.f2514, 0xdcdcdc, 0x323232,
                    0.040724355727434158f);
    }
}
extern void LVL_7_SIBERIUS_F8411efa9_FUN_003C77F8(char *pkt);
extern long long LVL_7_SIBERIUS_F8411efa9_FUN_002DC778(char *p);
extern float LVL_7_SIBERIUS_F8411efa9_FUN_002E49C8(float x, float y);
extern float LVL_7_SIBERIUS_F8411efa9_FUN_002E4488(char *p);
extern float LVL_7_SIBERIUS_F8411efa9_FUN_002E49C8(float x, float y);
extern void LVL_7_SIBERIUS_F8411efa9_FUN_002E4B90(float *matrix, float *quat);
extern void LVL_7_SIBERIUS_F8411efa9_FUN_002E45F0(float *off, char *src, float scale);
extern void LVL_7_SIBERIUS_F8411efa9_FUN_003C7880(char *pkt, float angle);
extern void LVL_7_SIBERIUS_F8411efa9_FUN_002E0C08(char *pkt, float *matrix, int mode);

void LVL_7_SIBERIUS_FUN_003C7AA0(char *pos, int a1, int a2, char *a3, int t0,
                                        char *src, float f12, float f13)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    LVL_7_SIBERIUS_F8411efa9_FUN_003C77F8(pkt);
    r = LVL_7_SIBERIUS_F8411efa9_FUN_002DC778(a3);

    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;

    quat[3] = 0.0f;
    quat[2] = LVL_7_SIBERIUS_F8411efa9_FUN_002E49C8(*(float *)(src + 0), *(float *)(src + 4));
    quat[1] = -LVL_7_SIBERIUS_F8411efa9_FUN_002E49C8(LVL_7_SIBERIUS_F8411efa9_FUN_002E4488(src), *(float *)(src + 8));
    quat[0] = f13;

    LVL_7_SIBERIUS_F8411efa9_FUN_002E4B90(m, quat);
    LVL_7_SIBERIUS_F8411efa9_FUN_002E45F0(off, src, 0.025f);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    LVL_7_SIBERIUS_F8411efa9_FUN_003C7880(pkt, f12);
    LVL_7_SIBERIUS_F8411efa9_FUN_002E0C08(pkt, m, 0);
}
extern void LVL_7_SIBERIUS_F8411efa9_FUN_003CB8D0(char *pkt);
extern long long LVL_7_SIBERIUS_F8411efa9_FUN_002DC778(char *p);
extern float LVL_7_SIBERIUS_F8411efa9_FUN_002E49C8(float x, float y);
extern float LVL_7_SIBERIUS_F8411efa9_FUN_002E4488(char *p);
extern float LVL_7_SIBERIUS_F8411efa9_FUN_002E49C8(float x, float y);
extern void LVL_7_SIBERIUS_F8411efa9_FUN_002E4B90(float *matrix, float *quat);
extern void LVL_7_SIBERIUS_F8411efa9_FUN_002E45F0(float *off, char *src, float scale);
extern void LVL_7_SIBERIUS_F8411efa9_FUN_003CB958(char *pkt, float angle);
extern void LVL_7_SIBERIUS_F8411efa9_FUN_002E0C08(char *pkt, float *matrix, int mode);

void LVL_7_SIBERIUS_FUN_003CB9C0(char *pos, int a1, int a2, char *a3, int t0,
                                        char *src, float f12, float f13)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    LVL_7_SIBERIUS_F8411efa9_FUN_003CB8D0(pkt);
    r = LVL_7_SIBERIUS_F8411efa9_FUN_002DC778(a3);

    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;

    quat[3] = 0.0f;
    quat[2] = LVL_7_SIBERIUS_F8411efa9_FUN_002E49C8(*(float *)(src + 0), *(float *)(src + 4));
    quat[1] = -LVL_7_SIBERIUS_F8411efa9_FUN_002E49C8(LVL_7_SIBERIUS_F8411efa9_FUN_002E4488(src), *(float *)(src + 8));
    quat[0] = f13;

    LVL_7_SIBERIUS_F8411efa9_FUN_002E4B90(m, quat);
    LVL_7_SIBERIUS_F8411efa9_FUN_002E45F0(off, src, 0.025f);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    LVL_7_SIBERIUS_F8411efa9_FUN_003CB958(pkt, f12);
    LVL_7_SIBERIUS_F8411efa9_FUN_002E0C08(pkt, m, 0);
}
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);

void LVL_7_SIBERIUS_FUN_003C0AF8(char *p, float scale)
{
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p, p, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 16, p + 16, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 32, p + 32, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 48, p + 48, scale);
}
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);

void LVL_7_SIBERIUS_FUN_003C7880(char *p, float scale)
{
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p, p, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 16, p + 16, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 32, p + 32, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 48, p + 48, scale);
}
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);

void LVL_7_SIBERIUS_FUN_003CAC08(char *p, float scale)
{
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p, p, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 16, p + 16, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 32, p + 32, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 48, p + 48, scale);
}
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);

void LVL_7_SIBERIUS_FUN_003CB958(char *p, float scale)
{
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p, p, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 16, p + 16, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 32, p + 32, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 48, p + 48, scale);
}
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);

void LVL_7_SIBERIUS_FUN_003D20F0(char *p, float scale)
{
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p, p, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 16, p + 16, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 32, p + 32, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 48, p + 48, scale);
}
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);

void LVL_7_SIBERIUS_FUN_003DBF58(char *p, float scale)
{
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p, p, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 16, p + 16, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 32, p + 32, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 48, p + 48, scale);
}
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);
extern void LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(char *dst, char *src, float scale);

void LVL_7_SIBERIUS_FUN_003DD300(char *p, float scale)
{
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p, p, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 16, p + 16, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 32, p + 32, scale);
    LVL_7_SIBERIUS_F2c74c194_FUN_002E4398(p + 48, p + 48, scale);
}




extern u8 LVL_7_SIBERIUS_F458c670e_D_00189E20[];

extern void LVL_7_SIBERIUS_F458c670e_FUN_00313E98(f32 *a, f32 *b, f32 c, f32 d, f32 e, f32 f);
extern f32 LVL_7_SIBERIUS_F458c670e_FUN_002E4280(f32 v);
extern void LVL_7_SIBERIUS_F458c670e_FUN_00313DD8(f32 *p, f32 v, f32 w);

#ifndef RAC2_T_RES_F458C670E
#define RAC2_T_RES_F458C670E
typedef struct {
    u8 pad000[0x88];
    f32 f088;
    u8 pad08C[0x1B8 - 0x08C];
    s32 i1B8;
    u8 pad1BC[0x330 - 0x1BC];
    f32 f330;
    u8 pad334[0x790 - 0x334];
    f32 f790;
    f32 f794;
    u8 pad798[4];
    f32 f79C;
    f32 f7A0;
    u8 pad7A4[0x9B0 - 0x7A4];
    f32 f9B0;
    u8 pad9B4[0xA3C - 0x9B4];
    f32 fA3C;
    u8 padA40[0x2294 - 0xA40];
    s32 i2294;
    u8 pad2298[4];
    s32 i229C;
    u8 pad22A0[4];
    s32 i22A4;
    u8 pad22A8[8];
    s32 i22B0;
} Res_F458c670e;
#endif


void LVL_7_SIBERIUS_FUN_002C1B78(void)
{
    f32 old, v, r, sum;

    if (((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->i1B8 >= 11
        || ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f790 < 0.0f
        || ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->i22A4 == 17
        || ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->i22B0 == 17) {
        if (((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->i2294 == 53) {
            LVL_7_SIBERIUS_F458c670e_FUN_00313E98(&((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f790,
                    &((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->fA3C,
                    0.0f, 0.03f, 0.3f, 0.025000002f);
            ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f794 = 0.0f;
        } else {
            old = ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f790;
            v = ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f794;
            ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f794 =
                v - (old * 0.005f + v * 0.045f);
            r = LVL_7_SIBERIUS_F458c670e_FUN_002E4280(old);
            if (r < 0.001f) {
                if (((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f794 < 0.0001f)
                    ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f794 = 0.0f;
            }
        }
    }
    sum = ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f790
        + ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f794;
    ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f790 = sum;
    if (((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->i2294 == 53) {
        if (sum > 0.0f) {
            if (((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f794 > 0.0f)
                ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f794 = 0.0f;
            LVL_7_SIBERIUS_F458c670e_FUN_00313DD8(&((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f790,
                    0.0f, 0.011666667f);
        }
    }
    if (((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->i2294 != 124) {
        f32 x = ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f330;
        if (((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->i229C == 22)
            x = ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f9B0;
        LVL_7_SIBERIUS_F458c670e_FUN_00313E98(&((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f79C,
                &((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f7A0,
                x, 0.027f, 0.3f, 0.0f);
    }
    ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f088 =
        (((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f79C + (-0.12f))
        + ((Res_F458c670e *)LVL_7_SIBERIUS_F458c670e_D_00189E20)->f790;
}
extern void LVL_7_SIBERIUS_F40487154_FUN_002E4B70(char *a, char *b);
extern float LVL_7_SIBERIUS_F40487154_FUN_002E4918(float value);
extern void LVL_7_SIBERIUS_F40487154_FUN_002E4398(char *a, char *b, float value);
extern float LVL_7_SIBERIUS_F40487154_FUN_002E5318(float value, float scale);

void LVL_7_SIBERIUS_FUN_003CE930(char *object)
{
    char *data;
    float x;
    float y;
    float z;

    data = *(char **)(object + 104);
    LVL_7_SIBERIUS_F40487154_FUN_002E4B70(object + 192, object + 240);
    x = LVL_7_SIBERIUS_F40487154_FUN_002E4918(*(float *)(data + 4)) * 0.15f + 0.35000002f;
    y = LVL_7_SIBERIUS_F40487154_FUN_002E4918(*(float *)(data + 8)) * 0.15f + 0.35000002f;
    z = LVL_7_SIBERIUS_F40487154_FUN_002E4918(*(float *)(data + 12)) * 0.15f + 0.35000002f;
    LVL_7_SIBERIUS_F40487154_FUN_002E4398(object + 192, object + 192, x);
    LVL_7_SIBERIUS_F40487154_FUN_002E4398(object + 208, object + 208, y);
    LVL_7_SIBERIUS_F40487154_FUN_002E4398(object + 224, object + 224, z);
    *(float *)(data + 4) = LVL_7_SIBERIUS_F40487154_FUN_002E5318(*(float *)(data + 4), 0.5f);
    *(float *)(data + 8) = LVL_7_SIBERIUS_F40487154_FUN_002E5318(*(float *)(data + 8), 0.5f);
    *(float *)(data + 12) = LVL_7_SIBERIUS_F40487154_FUN_002E5318(*(float *)(data + 12), 0.5f);
}
extern void LVL_7_SIBERIUS_F40487154_FUN_002E4B70(char *a, char *b);
extern float LVL_7_SIBERIUS_F40487154_FUN_002E4918(float value);
extern void LVL_7_SIBERIUS_F40487154_FUN_002E4398(char *a, char *b, float value);
extern float LVL_7_SIBERIUS_F40487154_FUN_002E5318(float value, float scale);

void LVL_7_SIBERIUS_FUN_003D97E8(char *object)
{
    char *data;
    float x;
    float y;
    float z;

    data = *(char **)(object + 104);
    LVL_7_SIBERIUS_F40487154_FUN_002E4B70(object + 192, object + 240);
    x = LVL_7_SIBERIUS_F40487154_FUN_002E4918(*(float *)(data + 4)) * 0.15f + 0.35000002f;
    y = LVL_7_SIBERIUS_F40487154_FUN_002E4918(*(float *)(data + 8)) * 0.15f + 0.35000002f;
    z = LVL_7_SIBERIUS_F40487154_FUN_002E4918(*(float *)(data + 12)) * 0.15f + 0.35000002f;
    LVL_7_SIBERIUS_F40487154_FUN_002E4398(object + 192, object + 192, x);
    LVL_7_SIBERIUS_F40487154_FUN_002E4398(object + 208, object + 208, y);
    LVL_7_SIBERIUS_F40487154_FUN_002E4398(object + 224, object + 224, z);
    *(float *)(data + 4) = LVL_7_SIBERIUS_F40487154_FUN_002E5318(*(float *)(data + 4), 0.5f);
    *(float *)(data + 8) = LVL_7_SIBERIUS_F40487154_FUN_002E5318(*(float *)(data + 8), 0.5f);
    *(float *)(data + 12) = LVL_7_SIBERIUS_F40487154_FUN_002E5318(*(float *)(data + 12), 0.5f);
}
extern int LVL_7_SIBERIUS_F6eb4f363_FUN_00310A98(int mode);
extern float LVL_7_SIBERIUS_F6eb4f363_FUN_00312A60(char *object, char *local);
extern void LVL_7_SIBERIUS_F6eb4f363_FUN_002E4398(char *local, int value, float scale);
extern float LVL_7_SIBERIUS_F6eb4f363_FUN_00310B30(float low, float high);
extern void LVL_7_SIBERIUS_F6eb4f363_FUN_0032CD30(char *object, char *local, float amount, float base);

void LVL_7_SIBERIUS_FUN_0037D2A0(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (LVL_7_SIBERIUS_F6eb4f363_FUN_00310A98(5))
        return;
    base = LVL_7_SIBERIUS_F6eb4f363_FUN_00312A60(object + 16, local);
    LVL_7_SIBERIUS_F6eb4f363_FUN_002E4398(local, value, 0.25f);
    LVL_7_SIBERIUS_F6eb4f363_FUN_0032CD30(object + 16, local, LVL_7_SIBERIUS_F6eb4f363_FUN_00310B30(0.05f, 0.1f) * 210000.0f, base);
}
extern int LVL_7_SIBERIUS_F6eb4f363_FUN_00310A98(int mode);
extern float LVL_7_SIBERIUS_F6eb4f363_FUN_00312A60(char *object, char *local);
extern void LVL_7_SIBERIUS_F6eb4f363_FUN_002E4398(char *local, int value, float scale);
extern float LVL_7_SIBERIUS_F6eb4f363_FUN_00310B30(float low, float high);
extern void LVL_7_SIBERIUS_F6eb4f363_FUN_0032CD30(char *object, char *local, float amount, float base);

void LVL_7_SIBERIUS_FUN_0037FD48(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (LVL_7_SIBERIUS_F6eb4f363_FUN_00310A98(5))
        return;
    base = LVL_7_SIBERIUS_F6eb4f363_FUN_00312A60(object + 16, local);
    LVL_7_SIBERIUS_F6eb4f363_FUN_002E4398(local, value, 0.25f);
    LVL_7_SIBERIUS_F6eb4f363_FUN_0032CD30(object + 16, local, LVL_7_SIBERIUS_F6eb4f363_FUN_00310B30(0.05f, 0.1f) * 210000.0f, base);
}
extern int LVL_7_SIBERIUS_F6eb4f363_FUN_00310A98(int mode);
extern float LVL_7_SIBERIUS_F6eb4f363_FUN_00312A60(char *object, char *local);
extern void LVL_7_SIBERIUS_F6eb4f363_FUN_002E4398(char *local, int value, float scale);
extern float LVL_7_SIBERIUS_F6eb4f363_FUN_00310B30(float low, float high);
extern void LVL_7_SIBERIUS_F6eb4f363_FUN_0032CD30(char *object, char *local, float amount, float base);

void LVL_7_SIBERIUS_FUN_00386148(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (LVL_7_SIBERIUS_F6eb4f363_FUN_00310A98(5))
        return;
    base = LVL_7_SIBERIUS_F6eb4f363_FUN_00312A60(object + 16, local);
    LVL_7_SIBERIUS_F6eb4f363_FUN_002E4398(local, value, 0.25f);
    LVL_7_SIBERIUS_F6eb4f363_FUN_0032CD30(object + 16, local, LVL_7_SIBERIUS_F6eb4f363_FUN_00310B30(0.05f, 0.1f) * 210000.0f, base);
}
extern int LVL_7_SIBERIUS_Fc10c1216_FUN_002E3FB0(char *);
extern void LVL_7_SIBERIUS_Fc10c1216_FUN_003263C0(char *);
extern int LVL_7_SIBERIUS_Fc10c1216_FUN_002E5470(float);
extern void LVL_7_SIBERIUS_Fc10c1216_FUN_002E4310(char *, char *, char *);

void LVL_7_SIBERIUS_FUN_0032BFC0(char *p)
{
    float *q = (float *)(p + 32);

    if (0.0f < q[3])
        q[1] = q[1] + q[3] * 0.007f;
    else if (0.03f < q[1])
        q[1] = q[1] + q[3] * 0.007f;
    else {
        q[1] = q[1] + q[3] * 1.4000000664964318275452e-03f;
        *(float *)(p + 12) = *(float *)(p + 12) + 5460.0f;
    }

    if (q[1] <= 0.0244f || LVL_7_SIBERIUS_Fc10c1216_FUN_002E3FB0(p + 10) != 0) {
        LVL_7_SIBERIUS_Fc10c1216_FUN_003263C0(p);
        return;
    }

    if (q[1] >= 0.12f) {
        q[3] = -q[3];
        q[1] = q[1] + q[3] * 0.007f;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 5460.0f;
    *(int *)(p + 4) = (*(int *)(p + 4) & 0xffffff) | (LVL_7_SIBERIUS_Fc10c1216_FUN_002E5470(q[1] * 255.0f) << 24);
    q[2] = q[2] + 0.002f;
    if (q[2] > 1.0f)
        q[2] = q[2] - 1.0f;
    *(char *)(p + 8) = (char)(q[2] * 255.0f);
    LVL_7_SIBERIUS_Fc10c1216_FUN_002E4310(p + 16, p + 16, (char *)(q + 4));
}
#ifndef RAC2_T_V4_F904CC63B
#define RAC2_T_V4_F904CC63B
typedef __attribute__((mode(TI))) int V4_F904cc63b;
#endif


extern char *LVL_7_SIBERIUS_F904cc63b_FUN_00316FD8(char *p);
extern void LVL_7_SIBERIUS_F904cc63b_FUN_002E4B90(V4_F904cc63b *dst, char *src);
extern void LVL_7_SIBERIUS_F904cc63b_FUN_002E4310(V4_F904cc63b *dst, V4_F904cc63b *a, char *b);
extern void LVL_7_SIBERIUS_F904cc63b_FUN_002E4340(V4_F904cc63b *dst, V4_F904cc63b *a, char *b);
extern void LVL_7_SIBERIUS_F904cc63b_FUN_002E4E18(V4_F904cc63b *dst, V4_F904cc63b *src);
extern void LVL_7_SIBERIUS_F904cc63b_FUN_002E47D0(V4_F904cc63b *dst, V4_F904cc63b *a, V4_F904cc63b *b);

int LVL_7_SIBERIUS_FUN_00317258(char *a0, char *a1, char *a2, char *a3)
{
    V4_F904cc63b b0[4];
    V4_F904cc63b b1[1];
    V4_F904cc63b b2[4];
    V4_F904cc63b b3[4];
    char *p;

    p = LVL_7_SIBERIUS_F904cc63b_FUN_00316FD8(a1);
    if (p == 0)
    {
        *(V4_F904cc63b *)a3 = 0;
        return 0;
    }
    LVL_7_SIBERIUS_F904cc63b_FUN_002E4B90(b0, p);
    LVL_7_SIBERIUS_F904cc63b_FUN_002E4310(b1, (V4_F904cc63b *)a2, p + 16);
    LVL_7_SIBERIUS_F904cc63b_FUN_002E4340(b1, b1, a1 + 16);
    if (*(int *)(p + 60) & 2)
    {
        LVL_7_SIBERIUS_F904cc63b_FUN_002E4B90(b3, p + 32);
        LVL_7_SIBERIUS_F904cc63b_FUN_002E4E18(b2, b3);
        LVL_7_SIBERIUS_F904cc63b_FUN_002E47D0(b1, b1, b2);
        LVL_7_SIBERIUS_F904cc63b_FUN_002E47D0(b1, b1, (V4_F904cc63b *)(a1 + 192));
    }
    else
    {
        LVL_7_SIBERIUS_F904cc63b_FUN_002E47D0(b1, b1, b0);
    }
    LVL_7_SIBERIUS_F904cc63b_FUN_002E4310(b1, b1, a1 + 16);
    LVL_7_SIBERIUS_F904cc63b_FUN_002E4340((V4_F904cc63b *)a3, b1, a2);
    return 1;
}
extern int LVL_7_SIBERIUS_F250fbfa4_FUN_002E3FB0(char *p);
extern void LVL_7_SIBERIUS_F250fbfa4_FUN_003263C0(char *p);
extern void LVL_7_SIBERIUS_F250fbfa4_FUN_002E4310(char *p0, char *p1, char *p2);

void LVL_7_SIBERIUS_FUN_00335BE8(char *a0)
{
    char local[16];
    char *s1 = a0;
    char *s0;
    int a1;
    int v1;
    char *p;

    if (LVL_7_SIBERIUS_F250fbfa4_FUN_002E3FB0(a0 + 10) != 0) {
        LVL_7_SIBERIUS_F250fbfa4_FUN_003263C0(a0);
        return;
    }
    s0 = a0 + 32;
    a1 = *(int *)(s1 + 4);
    v1 = (a1 >> 24) + *(unsigned char *)(s0 + 20);
    *(int *)(s1 + 4) = (a1 & 0x00ffffff) | (v1 << 24);
    p = s1 + 16;
    *(float *)(local + 0) = *(float *)(s1 + 32);
    *(float *)(local + 4) = *(float *)(s0 + 4);
    *(float *)(local + 8) = *(float *)(s0 + 8);
    *(int *)(local + 12) = 0;
    LVL_7_SIBERIUS_F250fbfa4_FUN_002E4310(p, p, local);
    *(float *)(s0 + 8) = *(float *)(s0 + 8) - *(float *)(s0 + 12);
    *(unsigned char *)(s1 + 8) = *(unsigned char *)(s1 + 8) + *(unsigned char *)(s0 + 21);
    *(float *)(s1 + 12) = *(float *)(s1 + 12) + *(float *)(s0 + 16);
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042D200(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042D640(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042D8F8(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042DE80(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042E908(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042EBD0(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042EF98(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042F248(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(char *p);

char *LVL_7_SIBERIUS_FUN_0042F440(char *object)
{
    LVL_7_SIBERIUS_Ffb202470_FUN_0042C018(object + 8);
    return object;
}
extern void LVL_7_SIBERIUS_Fe524d931_FUN_0042C2F0(char *p);
extern void LVL_7_SIBERIUS_Fe524d931_FUN_0042C4E0(char *p, float x, float y);
extern void LVL_7_SIBERIUS_Fe524d931_FUN_003555E8(int a, int b, int c);
extern void LVL_7_SIBERIUS_Fe524d931_FUN_002E6678(void);
extern short LVL_7_SIBERIUS_Fe524d931_D_001A6480[];

int LVL_7_SIBERIUS_FUN_0042D360(char *object, int mask)
{
    char *sub = object + 8;
    short oldx;
    short oldy;
    int *v;

    LVL_7_SIBERIUS_Fe524d931_FUN_0042C2F0(sub);
    v = *(int **)(object + 684);
    LVL_7_SIBERIUS_Fe524d931_FUN_0042C4E0(sub, *(float *)v, *(float *)(v + 1));
    if ((mask & 0x40) != 0 && *(int *)(object + 680) == 0)
        LVL_7_SIBERIUS_Fe524d931_FUN_003555E8(4, 0, 0);
    if ((mask & 0xf000) != 0) {
        short *p = LVL_7_SIBERIUS_Fe524d931_D_001A6480;
        oldx = p[180];
        oldy = p[181];
        if ((mask & 0x1000) != 0) {
            ((unsigned short *)p)[181] = ((unsigned short *)p)[181] - 1;
            if ((short)((unsigned short *)p)[181] < -32)
                p[181] = -32;
        }
        if ((mask & 0x4000) != 0) {
            unsigned short *q = (unsigned short *)LVL_7_SIBERIUS_Fe524d931_D_001A6480;
            q[181] = q[181] + 1;
            if ((short)q[181] > 32)
                ((short *)q)[181] = 32;
        }
        if ((mask & 0x8000) != 0) {
            unsigned short *q = (unsigned short *)LVL_7_SIBERIUS_Fe524d931_D_001A6480;
            q[180] = q[180] - 1;
            if ((short)q[180] < -40)
                ((short *)q)[180] = -40;
        }
        if ((mask & 0x2000) != 0) {
            unsigned short *q = (unsigned short *)LVL_7_SIBERIUS_Fe524d931_D_001A6480;
            q[180] = q[180] + 1;
            if ((short)q[180] > 40)
                ((short *)q)[180] = 40;
        }
        {
            short *q = LVL_7_SIBERIUS_Fe524d931_D_001A6480;
            if (oldx != q[180] || oldy != q[181])
                LVL_7_SIBERIUS_Fe524d931_FUN_003555E8(4, 0, 0);
        }
        LVL_7_SIBERIUS_Fe524d931_FUN_002E6678();
    }
    return (mask >> 6) & 1;
}
extern void LVL_7_SIBERIUS_F0b028b34_FUN_00441D50(char *a, unsigned int b, int c, int d);
extern void LVL_7_SIBERIUS_F0b028b34_FUN_00441D50(char *a, unsigned int b, int c, int d);
extern void LVL_7_SIBERIUS_F0b028b34_FUN_00441CE0(int a);

int LVL_7_SIBERIUS_FUN_00441DF0(int *p)
{
    int i;

    p[17] = 1;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[22] = 0;
    p[23] = 0;
    for (i = 0; i < p[21]; i++) {
        *(long long *)((char *)p[20] + i * 24) = -1;
        *(long long *)((char *)p[20] + i * 24 + 8) = -1;
        *(int *)((char *)p[20] + i * 24 + 16) = 0;
        *(int *)((char *)p[20] + i * 24 + 20) = 0;
    }
    for (i = 0; i < p[2]; i++) {
        LVL_7_SIBERIUS_F0b028b34_FUN_00441D50((char *)(p[1] + i * 16), (i * 2048 + p[0]) & 0x0FFFFFFF, 3, 128);
    }
    LVL_7_SIBERIUS_F0b028b34_FUN_00441D50((char *)(p[1] + i * 16), p[1] & 0x0FFFFFFF, 2, 0);
    *(volatile unsigned int *)0x1000B420 = 0;
    *(volatile unsigned int *)0x1000B410 = p[0] & 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B430 = p[1] & 0x0FFFFFFF;
    LVL_7_SIBERIUS_F0b028b34_FUN_00441CE0(5);
    return 1;
}
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_00375A78(char *a, char *b);
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4398(char *a, char *b, float f);
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_00373958(char *a, char *b);
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4398(char *a, char *b, float f);
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4398(char *a, char *b, float f);
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4310(char *a, char *b, char *c);
extern int LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E54B8(unsigned int a, int b, float f);
extern void LVL_7_SIBERIUS_Fbdd4a4aa_FUN_003263C0(char *a);

void LVL_7_SIBERIUS_FUN_003379B8(int *obj)
{
    char *a = (char *)obj + 16;
    char *b = (char *)obj + 32;
    char tmp[16];

    LVL_7_SIBERIUS_Fbdd4a4aa_FUN_00375A78(a, a);
    *(int *)(b + 16) = *(int *)(b + 16) - 1;
    if (*(int *)(b + 16) < 0)
        *(int *)(b + 16) = 0;
    *(unsigned char *)((char *)obj + 8) = *(unsigned char *)((char *)obj + 8) + 1;
    LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4310(a, b, a);
    *(float *)((char *)obj + 12) = *(float *)((char *)obj + 12) + 1.5750000000000000000000e+03f;
    LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4398(b, b, 9.9000000953674316406250e-01f);
    LVL_7_SIBERIUS_Fbdd4a4aa_FUN_00373958(a, tmp);
    if ((*(int *)((char *)obj + 4) & 0xFF) < 32) {
        LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4398(tmp, tmp, 1.5000000130385160446167e-03f);
        LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4310(b, b, tmp);
    } else {
        LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4398(tmp, tmp, -7.5000000651925802230835e-04f);
        LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E4310(b, b, tmp);
    }
    *(int *)((char *)obj + 4) = LVL_7_SIBERIUS_Fbdd4a4aa_FUN_002E54B8(*(unsigned int *)((char *)obj + 4) & 0x00FFFFFF, 0, 2.5000000372529029846191e-02f)
        | (*(int *)(b + 16) << 24);
    if (*(int *)(b + 16) == 0)
        LVL_7_SIBERIUS_Fbdd4a4aa_FUN_003263C0((char *)obj);
}
#ifndef RAC2_T_OBJ_F7B2F1854
#define RAC2_T_OBJ_F7B2F1854
typedef struct Obj_F7b2f1854 {
    int *f0;
    int *f4;
    int *f8;
    int *f12;
    int *f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
} Obj_F7b2f1854;
#endif


extern int *LVL_7_SIBERIUS_F7b2f1854_FUN_00428300(int n);
extern int *LVL_7_SIBERIUS_F7b2f1854_FUN_00428268(int size, int *p);
extern void LVL_7_SIBERIUS_F7b2f1854_FUN_00427328(Obj_F7b2f1854 *o, int v);

void LVL_7_SIBERIUS_FUN_00427488(Obj_F7b2f1854 *o, int a1, int count)
{
    int *p;
    int n;

    o->f44 = count;
    if (count != 0) {
        p = LVL_7_SIBERIUS_F7b2f1854_FUN_00428268(16, LVL_7_SIBERIUS_F7b2f1854_FUN_00428300(count));
        n = o->f44;
        o->f0 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = LVL_7_SIBERIUS_F7b2f1854_FUN_00428268(16, LVL_7_SIBERIUS_F7b2f1854_FUN_00428300(n));
        n = o->f44;
        o->f8 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = LVL_7_SIBERIUS_F7b2f1854_FUN_00428268(16, LVL_7_SIBERIUS_F7b2f1854_FUN_00428300(n));
        n = o->f44;
        o->f4 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = LVL_7_SIBERIUS_F7b2f1854_FUN_00428268(16, LVL_7_SIBERIUS_F7b2f1854_FUN_00428300(n));
        n = o->f44;
        o->f12 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;

        p = LVL_7_SIBERIUS_F7b2f1854_FUN_00428268(16, LVL_7_SIBERIUS_F7b2f1854_FUN_00428300(n));
        o->f16 = p;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p[0] = 0;
    }
    o->f40 = a1;
    o->f32 = 0;
    o->f20 = 0;
    o->f28 = 0;
    o->f24 = 0;
    o->f36 = 0;
    LVL_7_SIBERIUS_F7b2f1854_FUN_00427328(o, 1);
}
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427B90(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);

char *LVL_7_SIBERIUS_FUN_00434E68(char *p)
{
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 76);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 152);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 228);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 304);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 380);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 456);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 528);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427B90(p + 600);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 664);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 736);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 808);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 880);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 952);
    return p;
}
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427B90(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(char *p);

char *LVL_7_SIBERIUS_FUN_004368C8(char *p)
{
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 76);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 152);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 228);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 304);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427668(p + 380);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 456);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 528);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427B90(p + 600);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 664);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 736);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 808);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 880);
    LVL_7_SIBERIUS_F449e2f67_FUN_00427E28(p + 952);
    return p;
}
extern char *LVL_7_SIBERIUS_Ffc961fca_FUN_00316FD8(char *a1);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E4B90(char *dst, char *src);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E4310(char *dst, char *src, char *tail);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E4340(char *dst, char *src, char *tail);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E4B90(char *dst, char *src);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E4E18(char *dst, char *src);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E47D0(char *dst, char *src, char *tail);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E47D0(char *dst, char *src, char *tail);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E47D0(char *dst, char *src, char *tail);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E4310(char *dst, char *src, char *tail);
extern void LVL_7_SIBERIUS_Ffc961fca_FUN_002E4EB8(char *dst, char *src, char *tail);

void LVL_7_SIBERIUS_FUN_00391790(char *o0, char *o1)
{
    char b0[64];
    char b1[64];
    char b2[64];
    char *r = LVL_7_SIBERIUS_Ffc961fca_FUN_00316FD8(o1);

    if (r == 0)
        return;
    LVL_7_SIBERIUS_Ffc961fca_FUN_002E4B90(b0, r);
    LVL_7_SIBERIUS_Ffc961fca_FUN_002E4310(o0 + 16, o0 + 16, r + 16);
    LVL_7_SIBERIUS_Ffc961fca_FUN_002E4340(o0 + 16, o0 + 16, o1 + 16);
    if ((*(int *)(r + 60) & 2) != 0) {
        LVL_7_SIBERIUS_Ffc961fca_FUN_002E4B90(b2, r + 32);
        LVL_7_SIBERIUS_Ffc961fca_FUN_002E4E18(b1, b2);
        LVL_7_SIBERIUS_Ffc961fca_FUN_002E47D0(o0 + 16, o0 + 16, b1);
        LVL_7_SIBERIUS_Ffc961fca_FUN_002E47D0(o0 + 16, o0 + 16, o1 + 192);
    } else {
        LVL_7_SIBERIUS_Ffc961fca_FUN_002E47D0(o0 + 16, o0 + 16, b0);
    }
    LVL_7_SIBERIUS_Ffc961fca_FUN_002E4310(o0 + 16, o0 + 16, o1 + 16);
    LVL_7_SIBERIUS_Ffc961fca_FUN_002E4EB8(o0 + 192, b0, o0 + 192);
}
extern int LVL_7_SIBERIUS_Fd1c348f5_FUN_002E3FB0(char *p);
extern int LVL_7_SIBERIUS_Fd1c348f5_FUN_002E5470(float v);
extern int LVL_7_SIBERIUS_Fd1c348f5_FUN_002E3FB0(char *p);
extern void LVL_7_SIBERIUS_Fd1c348f5_FUN_003263C0(char *p);
extern int LVL_7_SIBERIUS_Fd1c348f5_FUN_002E5470(float v);

void LVL_7_SIBERIUS_FUN_00329B28(char *p)
{
    char *q = p + 32;
    int r;
    int v;
    float f;

    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + *(unsigned char *)(q + 8);
    *(float *)(p + 24) = *(float *)(p + 24) + *(float *)(q + 16);
    *(float *)(p + 12) = *(float *)(p + 12) * *(float *)(q + 12);
    if (*(int *)(q + 4) == 0) {
        r = LVL_7_SIBERIUS_Fd1c348f5_FUN_002E3FB0(p + 10);
        if (r != 0) {
            *(int *)(q + 4) = 1;
            *(short *)(p + 10) = 30;
            *(int *)(p + 4) = *(int *)(q + 20) | 0x7f000000;
        } else {
            f = (float)(10 - *(short *)(p + 10)) * 9.6000003814697265625000e+00f;
            v = LVL_7_SIBERIUS_Fd1c348f5_FUN_002E5470(f);
            *(int *)(p + 4) = ((v + 32) << 24) | *(int *)(q + 20);
        }
    } else {
        r = LVL_7_SIBERIUS_Fd1c348f5_FUN_002E3FB0(p + 10);
        if (r != 0) {
            LVL_7_SIBERIUS_Fd1c348f5_FUN_003263C0(p);
        } else {
            f = (float)*(short *)(p + 10) * 4.2333333492279052734375e+00f;
            v = LVL_7_SIBERIUS_Fd1c348f5_FUN_002E5470(f);
            *(int *)(p + 4) = (v << 24) | *(int *)(q + 20);
        }
    }
}
extern void LVL_7_SIBERIUS_F2d5993bb_FUN_002E4098(char *p, int a1, int a2);
extern void LVL_7_SIBERIUS_F2d5993bb_FUN_002E40E8(char *p, int a1, int a2);
extern int LVL_7_SIBERIUS_F2d5993bb_FUN_003022E8(char *p, int a1);

int LVL_7_SIBERIUS_FUN_003023D0(char *out, int mult, int *recs)
{
    int off = 0;
    char *p = out + 8;
    char *r;
    int v;
    int w;

    if (*(int *)recs != 0) {
        r = (char *)recs;
        do {
            off += 8;
            v = *(int *)(r + 0) + mult * *(int *)(r + 4);
            *(int *)(p + 0) = *(int *)(r + 8);
            *(int *)(p + 4) = *(int *)(r + 4);
            p += 8;
            if (*(int *)(r + 8) == 6000)
                LVL_7_SIBERIUS_F2d5993bb_FUN_002E4098(p, 0, *(int *)(r + 4));
            else
                LVL_7_SIBERIUS_F2d5993bb_FUN_002E40E8(p, v, *(int *)(r + 4));
            w = *(int *)(r + 4);
            r += 16;
            p += w;
            off += w;
            p = (char *)(((int)p + 3) & ~3);
            off = (off + 3) & ~3;
        } while (*(int *)r != 0);
    }
    off += 8;
    *(int *)(p + 4) = 0;
    *(int *)(p + 0) = -1;
    v = LVL_7_SIBERIUS_F2d5993bb_FUN_003022E8(out + 8, off);
    *(int *)(out + 4) = v;
    *(int *)(out + 0) = off;
    return off + 8;
}
extern int LVL_7_SIBERIUS_F77a1e64d_FUN_003157A8(char *object);
extern float *LVL_7_SIBERIUS_F77a1e64d_FUN_00314CE0(char *object);

int LVL_7_SIBERIUS_FUN_003CEA58(char *object)
{
    float *p;

    if (LVL_7_SIBERIUS_F77a1e64d_FUN_003157A8(object) != 0)
        return 0;
    p = LVL_7_SIBERIUS_F77a1e64d_FUN_00314CE0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}
extern int LVL_7_SIBERIUS_F77a1e64d_FUN_003157A8(char *object);
extern float *LVL_7_SIBERIUS_F77a1e64d_FUN_00314CE0(char *object);

int LVL_7_SIBERIUS_FUN_003D9910(char *object)
{
    float *p;

    if (LVL_7_SIBERIUS_F77a1e64d_FUN_003157A8(object) != 0)
        return 0;
    p = LVL_7_SIBERIUS_F77a1e64d_FUN_00314CE0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}
extern int LVL_7_SIBERIUS_F77a1e64d_FUN_003157A8(char *object);
extern float *LVL_7_SIBERIUS_F77a1e64d_FUN_00314CE0(char *object);

int LVL_7_SIBERIUS_FUN_0041CB90(char *object)
{
    float *p;

    if (LVL_7_SIBERIUS_F77a1e64d_FUN_003157A8(object) != 0)
        return 0;
    p = LVL_7_SIBERIUS_F77a1e64d_FUN_00314CE0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}
extern void LVL_7_SIBERIUS_Fb342d477_D_0011AC60(int value);
extern void LVL_7_SIBERIUS_Fb342d477_FUN_00441CE0(int value);
extern void LVL_7_SIBERIUS_Fb342d477_FUN_00441C70(int value);
extern void LVL_7_SIBERIUS_Fb342d477_D_0011AC40(int value);

int LVL_7_SIBERIUS_FUN_004422A0(int *p)
{
    LVL_7_SIBERIUS_Fb342d477_D_0011AC60(p[16]);
    p[17] = 0;
    LVL_7_SIBERIUS_Fb342d477_FUN_00441CE0(5);
    p[7] = *(volatile int *)0x1000B410;
    p[8] = *(volatile int *)0x1000B430;
    p[9] = *(volatile int *)0x1000B420;
    p[10] = *(volatile int *)0x1000B400;
    if (*(volatile int *)0x10002010 & 0xF0)
        while (*(volatile int *)0x10002010 & 0xF0)
            ;
    LVL_7_SIBERIUS_Fb342d477_FUN_00441C70(0);
    p[11] = *(volatile int *)0x1000B010;
    p[12] = *(volatile int *)0x1000B020;
    p[13] = *(volatile int *)0x1000B000;
    p[14] = *(volatile int *)0x10002020;
    p[15] = *(volatile int *)0x10002010;
    LVL_7_SIBERIUS_Fb342d477_D_0011AC40(p[16]);
    return 1;
}
/* Family 0e7bb6a8908d30dc -- 244 bytes, 28 placements (1 boot + 27 levels). */

extern char *LVL_7_SIBERIUS_F0e7bb6a8_FUN_00316FD8(char *a);
extern void LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4B90(char *dst, char *src);
extern void LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4E18(char *dst, char *src);
extern void LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4E18(char *dst, char *src);
extern void LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4340(char *dst, char *a, char *b);
extern void LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E47F8(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4B90(char *dst, char *src);
extern void LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4F08(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F0e7bb6a8_FUN_003152C0(char *a, char *b);

int LVL_7_SIBERIUS_FUN_00317520(char *unused, char *obj, char *arg2, char *arg3, char *arg4, char *arg5)
{
    char buf0[64];
    char buf1[16];
    char buf2[64];
    char *p;

    p = LVL_7_SIBERIUS_F0e7bb6a8_FUN_00316FD8(obj);
    if (p == 0)
        return 0;
    if (*(int *)(p + 60) & 0x40) {
        LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4B90(buf0, obj + 240);
        LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4E18(buf0, buf0);
    } else {
        LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4E18(buf0, obj + 192);
    }
    LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4340(buf1, arg2, obj + 16);
    LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E47F8(arg4, buf1, buf0);
    LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4B90(buf2, arg3);
    LVL_7_SIBERIUS_F0e7bb6a8_FUN_002E4F08(buf2, buf0, buf2);
    LVL_7_SIBERIUS_F0e7bb6a8_FUN_003152C0(buf2, arg5);
    return 1;
}
extern void LVL_7_SIBERIUS_Fa2a84657_FUN_002E43B0(float *tmp, char *v, float k);
extern void LVL_7_SIBERIUS_Fa2a84657_FUN_002E4328(float *tmp, char *a, char *v);
extern int LVL_7_SIBERIUS_Fa2a84657_FUN_002E3FB0(char *field);
extern void LVL_7_SIBERIUS_Fa2a84657_FUN_003263C0(unsigned char *p);

void LVL_7_SIBERIUS_FUN_0032F750(unsigned char *p)
{
    float tmp[4];
    char *v;
    int n;

    v = (char *)p + 32;
    LVL_7_SIBERIUS_Fa2a84657_FUN_002E43B0(tmp, v, 9.4999998807907104492188e-01f);
    *(float *)(v + 8) = *(float *)(v + 8) + 1.3888889225199818611145e-03f;
    LVL_7_SIBERIUS_Fa2a84657_FUN_002E4328(tmp, (char *)p + 16, v);

    n = *(int *)(p + 4) + (int)0xFE000000;
    *(int *)(p + 4) = n;
    if (((unsigned)(n & 0xFF000000) - 1) > 0x5EFFFFFFu || LVL_7_SIBERIUS_Fa2a84657_FUN_002E3FB0((char *)p + 10) != 0) {
        LVL_7_SIBERIUS_Fa2a84657_FUN_003263C0(p);
    } else {
        float f0;
        float f1;

        f1 = *(float *)(p + 12);
        f0 = 2.1000000000000000000000e+05f - f1;
        f0 = f0 * 7.0000000298023223876953e-02f;
        f1 = f1 + f0;
        *(float *)(p + 12) = f1;
        p[8] = p[8] + 1;
    }
}
extern int LVL_7_SIBERIUS_F750245c6_D_001A7340 __attribute__((sda));
extern void LVL_7_SIBERIUS_F750245c6_FUN_002F1758(int a, int b, int c, int d, char *e, int f);
void LVL_7_SIBERIUS_FUN_0033E5E0(int a0, char *a1)
{
    int h, k, p, m;
    k = a0 / 2 + 5;
    h = LVL_7_SIBERIUS_F750245c6_D_001A7340 / 2;
    m = h - k;
    p = h + k;
    LVL_7_SIBERIUS_F750245c6_FUN_002F1758(m - 2, 312, p + 4, 314, a1, 0);
    LVL_7_SIBERIUS_F750245c6_FUN_002F1758(m - 2, 333, p + 4, 335, a1, 0);
    LVL_7_SIBERIUS_F750245c6_FUN_002F1758(m - 2, 313, m, 334, a1, 0);
    LVL_7_SIBERIUS_F750245c6_FUN_002F1758(p + 2, 313, p + 4, 334, a1, 0);
}
extern float LVL_7_SIBERIUS_Fe617c30b_FUN_002E5460(int a);
extern void LVL_7_SIBERIUS_Fe617c30b_FUN_002E4398(char *p, char *q, float f);
extern void LVL_7_SIBERIUS_Fe617c30b_FUN_002E4310(char *p, char *q, char *r);
extern int LVL_7_SIBERIUS_Fe617c30b_FUN_00312ED0(int a, int b, float f);
extern int LVL_7_SIBERIUS_Fe617c30b_FUN_002E3FB0(char *p);
extern void LVL_7_SIBERIUS_Fe617c30b_FUN_003263C0(char *p);

void LVL_7_SIBERIUS_FUN_003281A8(char *a0)
{
    char *s0 = a0 + 32;
    int x;
    int u;
    int t;
    float f;

    x = *(int *)(s0 + 28);
    t = *(short *)(a0 + 10);
    u = *(short *)(s0 + 24) * (x - t) / x + *(short *)(s0 + 26);

    f = LVL_7_SIBERIUS_Fe617c30b_FUN_002E5460(u) * 1000.0f;
    *(float *)(a0 + 12) = f;
    LVL_7_SIBERIUS_Fe617c30b_FUN_002E4398(s0, s0, 9.8000001907348632812500e-01f);
    LVL_7_SIBERIUS_Fe617c30b_FUN_002E4310(a0 + 16, a0 + 16, s0);
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + 1;
    f = LVL_7_SIBERIUS_Fe617c30b_FUN_002E5460(*(int *)(s0 + 28));
    *(int *)(a0 + 4) = LVL_7_SIBERIUS_Fe617c30b_FUN_00312ED0(*(int *)(s0 + 20), *(int *)(s0 + 16),
                               (float)*(short *)(a0 + 10) / f);
    if (LVL_7_SIBERIUS_Fe617c30b_FUN_002E3FB0(a0 + 10) != 0)
        LVL_7_SIBERIUS_Fe617c30b_FUN_003263C0(a0);
}
extern int LVL_7_SIBERIUS_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F4a4e68d9_FUN_0043F990(int);

void LVL_7_SIBERIUS_FUN_00302CF0(void)
{
    int value = LVL_7_SIBERIUS_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F4a4e68d9_FUN_0043F990(value + 0x36F28);
}
extern int LVL_7_SIBERIUS_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F4a4e68d9_FUN_0043F9B0(int);

void LVL_7_SIBERIUS_FUN_00303320(void)
{
    int value = LVL_7_SIBERIUS_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F4a4e68d9_FUN_0043F9B0(value + 0x36F28);
}
extern int LVL_7_SIBERIUS_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F4a4e68d9_FUN_0043F950(int);

void LVL_7_SIBERIUS_FUN_00303570(void)
{
    int value = LVL_7_SIBERIUS_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F4a4e68d9_FUN_0043F950(value + 0x36F28);
}
extern int LVL_7_SIBERIUS_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F4a4e68d9_FUN_0043F9D0(int);

void LVL_7_SIBERIUS_FUN_003035A0(void)
{
    int value = LVL_7_SIBERIUS_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F4a4e68d9_FUN_0043F9D0(value + 0x36F28);
}
extern int LVL_7_SIBERIUS_F4a4e68d9_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F4a4e68d9_FUN_00429568(int);

void LVL_7_SIBERIUS_FUN_003041B0(void)
{
    int value = LVL_7_SIBERIUS_F4a4e68d9_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F4a4e68d9_FUN_00429568(value + 0x36F28);
}
extern void LVL_7_SIBERIUS_F42d2147f_FUN_002E45F0(char *a0, char *a1, float f);
extern void LVL_7_SIBERIUS_F42d2147f_FUN_002E4398(char *a0, char *a1, float f);
extern void LVL_7_SIBERIUS_F42d2147f_FUN_002E4310(char *a0, char *a1, char *a2);
extern char LVL_7_SIBERIUS_F42d2147f_D_00189E20[];
extern char LVL_7_SIBERIUS_F42d2147f_D_00189EA0[];

void LVL_7_SIBERIUS_FUN_00422D00(char *object)
{
    char local[16];
    char buf[16];
    char *p = LVL_7_SIBERIUS_F42d2147f_D_00189E20;
    unsigned char v;

    LVL_7_SIBERIUS_F42d2147f_FUN_002E45F0(local, (char *)(*(int *)(p + 8848) + 224), 1.0f);
    v = *(unsigned char *)(p + 8884);
    if (v == 2) {
        LVL_7_SIBERIUS_F42d2147f_FUN_002E4398(buf, local, 9.5f);
    } else if (v == 1) {
        LVL_7_SIBERIUS_F42d2147f_FUN_002E4398(buf, local, 0.75f);
    } else {
        LVL_7_SIBERIUS_F42d2147f_FUN_002E4398(buf, local, 1.6f);
    }
    LVL_7_SIBERIUS_F42d2147f_FUN_002E4310(object + 48, LVL_7_SIBERIUS_F42d2147f_D_00189EA0, buf);
    LVL_7_SIBERIUS_F42d2147f_FUN_002E4310(object + 48, LVL_7_SIBERIUS_F42d2147f_D_00189EA0 + 208, object + 48);
}
extern char LVL_7_SIBERIUS_F93479d13_D_00189E20[];
extern void LVL_7_SIBERIUS_F93479d13_FUN_00306800(char *entry);
extern void LVL_7_SIBERIUS_F93479d13_FUN_00306800(char *entry);

void LVL_7_SIBERIUS_FUN_002AFFB0(int slot, int value)
{
    char *e;
    void (*fn)(char *);

    {
        char *p = LVL_7_SIBERIUS_F93479d13_D_00189E20 + slot * 80;

        *(int *)(p + 4660) = value;
        if (*(int *)(p + 4676) != 3) {
            *(int *)(p + 4676) = 3;
            e = *(char **)(p + 4640);
            if (e != 0) {
                if (*(unsigned char *)(e + 32) != 254) {
                    if (*(unsigned char *)(e + 32) != 253) {
                        fn = *(void (**)(char *))(e + 100);
                        if (fn != 0)
                            fn(e);
                    }
                }
            }
        }
    }
    {
        char *q = LVL_7_SIBERIUS_F93479d13_D_00189E20 + slot * 80;

        e = *(char **)(q + 4640);
        *(int *)(q + 4676) = 0;
        *(int *)(q + 4680) = 0;
        if (e != 0) {
            LVL_7_SIBERIUS_F93479d13_FUN_00306800(e);
            *(char **)(q + 4640) = 0;
        }
        e = *(char **)(q + 4644);
        if (e != 0 && slot != 3) {
            LVL_7_SIBERIUS_F93479d13_FUN_00306800(e);
            *(char **)(q + 4644) = 0;
        }
    }
}
extern char LVL_7_SIBERIUS_F5fa3e1af_D_00189E20[];
extern float LVL_7_SIBERIUS_F5fa3e1af_FUN_002E42D8(float *buf);
extern float LVL_7_SIBERIUS_F5fa3e1af_FUN_002E4458(float *buf);

void LVL_7_SIBERIUS_FUN_003C8E70(char *obj)
{
    float buf[2];
    char *d = LVL_7_SIBERIUS_F5fa3e1af_D_00189E20;
    char *e = *(char **)(obj + 104);
    float a, b, x;

    a = -*(float *)(d + 8112);
    *(float *)(e + 20) = a;
    b = -*(float *)(d + 8116);
    *(float *)(e + 16) = b;

    if (a > 1.0f) {
        *(float *)(e + 20) = 1.0f;
    } else if (a < -1.0f) {
        *(float *)(e + 20) = -1.0f;
    }

    x = *(float *)(e + 16);
    if (x > 1.0f) {
        *(float *)(e + 16) = 1.0f;
    } else if (x < -1.0f) {
        *(float *)(e + 16) = -1.0f;
    }
    LVL_7_SIBERIUS_F5fa3e1af_FUN_002E42D8(buf);
    buf[0] = *(float *)(e + 16);
    buf[1] = *(float *)(e + 20);
    *(float *)(e + 48) = LVL_7_SIBERIUS_F5fa3e1af_FUN_002E4458(buf);
}


extern int LVL_7_SIBERIUS_F9a90bcc4_FUN_00310A98(int count);

int LVL_7_SIBERIUS_FUN_0031DDB0(u8 *owner, int b, int *outIndex,
                                       float *o0, float *o1, float *o2, float *o3,
                                       float *o4, float *o5, float *o6)
{
    int n;
    int count;
    int i;
    int k;
    int left;
    u8 *p;

    n = 0;
    count = *(u8 *)(*(int *)(owner + 36) + 12);
    if (count != 0) {
        int *t = (int *)(*(int *)(owner + 36) + 72);
        u8 *q;
        left = count;
        do {
            q = *(u8 **)(*t + 20);
            if (q != 0 && *q == b)
                n++;
            t++;
            left--;
        } while (left != 0);
    }

    if (n != 0)
        goto second;

    return 0;

found:
    *o0 = *(float *)(p + 8) * 0.016666668f;
    *o1 = *(float *)(p + 12) * 0.016666668f;
    *o2 = *(float *)(p + 16) * 0.00027777778f;
    *o3 = *(float *)(p + 20) * 0.00027777778f;
    *o6 = *(float *)(p + 4) * 0.00027777778f;
    *o4 = *(float *)(p + 24);
    *o5 = *(float *)(p + 28);
    *outIndex = i;
    return 1;

second:
    k = LVL_7_SIBERIUS_F9a90bcc4_FUN_00310A98(n);
    for (i = 0; i < *(u8 *)(*(int *)(owner + 36) + 12); i++) {
        char *tbl = (char *)(*(int *)(owner + 36) + 72);
        char *e = *(char **)(tbl + i * 4);
        p = *(u8 **)(e + 20);
        if (p == 0 || *p != b)
            continue;
        if (k == 0)
            goto found;
        k--;
    }
    return 0;
}


extern void LVL_7_SIBERIUS_Feda2e14e_FUN_002E4310(void *out, void *in, void *src);
extern int LVL_7_SIBERIUS_Feda2e14e_FUN_002E3FB0(void *p);
extern void LVL_7_SIBERIUS_Feda2e14e_FUN_003263C0(void *self);
extern float LVL_7_SIBERIUS_Feda2e14e_FUN_002E5460(int n);
extern int LVL_7_SIBERIUS_Feda2e14e_FUN_002E54B8(int handle, int previous, float ratio);
extern char LVL_7_SIBERIUS_Feda2e14e_D_00189E20[];

void LVL_7_SIBERIUS_FUN_00330950(u8 *self)
{
    char *s2 = (char *)self + 32;
    int n;
    float a;
    float b;

    if (*(int *)(s2 + 28) == 1) {
        char *base = LVL_7_SIBERIUS_Feda2e14e_D_00189E20;
        *(float *)(self + 16) = *(float *)(base + 128) + *(float *)(s2 + 16);
        *(float *)(self + 20) = *(float *)(base + 132) + *(float *)(s2 + 20);
        *(float *)(self + 24) = *(float *)(base + 136) + *(float *)(s2 + 24);
        LVL_7_SIBERIUS_Feda2e14e_FUN_002E4310(self + 16, self + 16, s2);
        *(float *)(s2 + 16) = *(float *)(self + 16) - *(float *)(base + 128);
        *(float *)(s2 + 20) = *(float *)(self + 20) - *(float *)(base + 132);
        *(float *)(s2 + 24) = *(float *)(self + 24) - *(float *)(base + 136);
    } else {
        LVL_7_SIBERIUS_Feda2e14e_FUN_002E4310(self + 16, self + 16, s2);
    }

    if (*(float *)(self + 16) < 2.0f || *(float *)(self + 16) > 1021.0f
        || *(float *)(self + 20) < 2.0f || *(float *)(self + 20) > 1021.0f
        || *(float *)(self + 24) < 2.0f || *(float *)(self + 24) > 1021.0f) {
        LVL_7_SIBERIUS_Feda2e14e_FUN_003263C0(self);
        return;
    }

    if (LVL_7_SIBERIUS_Feda2e14e_FUN_002E3FB0((char *)self + 10) != 0) {
        LVL_7_SIBERIUS_Feda2e14e_FUN_003263C0(self);
        return;
    }

    n = *(int *)(self + 4) & 0xFFFFFF;
    a = LVL_7_SIBERIUS_Feda2e14e_FUN_002E5460(*(short *)(self + 10) - 1);
    b = LVL_7_SIBERIUS_Feda2e14e_FUN_002E5460(*(short *)(self + 10));
    *(int *)(self + 4) = LVL_7_SIBERIUS_Feda2e14e_FUN_002E54B8(n, *(int *)(self + 4), a / b);
}
extern void LVL_7_SIBERIUS_Feb99aa89_FUN_002C95E8(char *target, int mode, float value, float zero, float scale);
extern int LVL_7_SIBERIUS_Feb99aa89_FUN_002D4510(char *first, char *second, int mode, int flag, int extra);
extern float LVL_7_SIBERIUS_Feb99aa89_FUN_002E44D0(char *source, short *table);

extern short LVL_7_SIBERIUS_Feb99aa89_D_001BF660[];
extern float LVL_7_SIBERIUS_Feb99aa89_D_0018A084;

int LVL_7_SIBERIUS_FUN_002AA778(float *out, float scale, float amount)
{
    char buffer[32];

    LVL_7_SIBERIUS_Feb99aa89_FUN_002C95E8(buffer, 1, LVL_7_SIBERIUS_Feb99aa89_D_0018A084 - 0.02f, 0.0f, scale);
    LVL_7_SIBERIUS_Feb99aa89_FUN_002C95E8(buffer + 16, 1, amount, 0.0f, scale);
    if (LVL_7_SIBERIUS_Feb99aa89_FUN_002D4510(buffer, buffer + 16, 2, 0, 0)) {
        if (out)
            *out = LVL_7_SIBERIUS_Feb99aa89_FUN_002E44D0(buffer, LVL_7_SIBERIUS_Feb99aa89_D_001BF660);
        return 1;
    }
    return 0;
}
#ifndef RAC2_T_V4_FC3CB9262
#define RAC2_T_V4_FC3CB9262
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
#endif


extern void LVL_7_SIBERIUS_Fc3cb9262_FUN_002E4310(char *a, char *b, char *c);
extern int LVL_7_SIBERIUS_Fc3cb9262_FUN_002E5470(float f);
extern int LVL_7_SIBERIUS_Fc3cb9262_FUN_002E3FB0(char *a);
extern void LVL_7_SIBERIUS_Fc3cb9262_FUN_003263C0(char *a);

void LVL_7_SIBERIUS_FUN_00335638(char *a0)
{
    V4_Fc3cb9262 buf;
    char *s0 = a0 + 32;
    float f0;
    float f1;
    float f2;

    f1 = *(float *)(s0 + 16) + 1.0000000474974513053894e-03f;
    f2 = *(float *)(s0 + 8) - 3.0000000260770320892334e-03f;
    *(float *)(s0 + 16) = f1;
    *(float *)(s0 + 8) = f2;
    f0 = *(float *)(s0 + 20) * f1 * 2.1000000000000000000000e+05f;
    buf = *(V4_Fc3cb9262 *)s0;
    *(float *)(a0 + 12) = f0;
    LVL_7_SIBERIUS_Fc3cb9262_FUN_002E4310(a0 + 16, a0 + 16, (char *)&buf);
    *(int *)(a0 + 4) = (LVL_7_SIBERIUS_Fc3cb9262_FUN_002E5470((float)*(short *)(a0 + 10)) << 24) | 0x00FFD2D2;
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + *(unsigned char *)(s0 + 24);
    if (LVL_7_SIBERIUS_Fc3cb9262_FUN_002E3FB0(a0 + 10) != 0)
        LVL_7_SIBERIUS_Fc3cb9262_FUN_003263C0(a0);
}
extern void LVL_7_SIBERIUS_Fc186f630_FUN_002E45F0(char *local, char *a, float k);
extern float LVL_7_SIBERIUS_Fc186f630_FUN_002E4418(char *a, char *src);
extern void LVL_7_SIBERIUS_Fc186f630_FUN_002E4398(char *dst, char *src, float k);
extern void LVL_7_SIBERIUS_Fc186f630_FUN_002E4340(char *dst, char *src, char *local);

extern char LVL_7_SIBERIUS_Fc186f630_D_00189E20[];            /* 0x00189E20 */

#ifndef RAC2_T_V4_FC186F630
#define RAC2_T_V4_FC186F630
typedef int V4_Fc186f630 __attribute__((mode(TI)));
#endif


void LVL_7_SIBERIUS_FUN_002C9910(char *dst, char *src)
{
    char local[16];
    char *base;
    float f;

    base = LVL_7_SIBERIUS_Fc186f630_D_00189E20;
    switch (*(unsigned char *)(base + 8899)) {
    case 0:
        *(V4_Fc186f630 *)dst = *(V4_Fc186f630 *)src;
        *(int *)(dst + 8) = 0;
        break;
    case 1:
        LVL_7_SIBERIUS_Fc186f630_FUN_002E45F0(local, base + 672, 1.0f);
        f = LVL_7_SIBERIUS_Fc186f630_FUN_002E4418(local, src);
        LVL_7_SIBERIUS_Fc186f630_FUN_002E4398(local, local, f);
        LVL_7_SIBERIUS_Fc186f630_FUN_002E4340(dst, src, local);
        break;
    case 2:
        f = LVL_7_SIBERIUS_Fc186f630_FUN_002E4418(base + 704, src);
        LVL_7_SIBERIUS_Fc186f630_FUN_002E4398(local, base + 704, f);
        LVL_7_SIBERIUS_Fc186f630_FUN_002E4340(dst, src, local);
        break;
    }
}


#ifndef RAC2_T_TI_F41EB487E
#define RAC2_T_TI_F41EB487E
typedef int TI_F41eb487e __attribute__((mode(TI)));
#endif


extern void LVL_7_SIBERIUS_F41eb487e_FUN_002E47F8(void *a, void *b, void *c);
extern void LVL_7_SIBERIUS_F41eb487e_FUN_002E4398(void *a, void *b, float value);
extern void LVL_7_SIBERIUS_F41eb487e_FUN_002B74C8(void *a, void *b, int c, float p, float q, float r);
extern void LVL_7_SIBERIUS_F41eb487e_FUN_002E4340(void *a, void *b, void *c);
extern void LVL_7_SIBERIUS_F41eb487e_FUN_002E4310(void *a, void *b, void *c);


#ifndef RAC2_T_VEC4_F41EB487E
#define RAC2_T_VEC4_F41EB487E
typedef struct {
    int a;
    int b;
    float c;
    float d;
} Vec4_F41eb487e;
#endif


#ifndef RAC2_T_RESIDENTSTATE_F41EB487E
#define RAC2_T_RESIDENTSTATE_F41EB487E
typedef struct {
    u8 pad000[0x80];
    u8 area080[0x218 - 0x80];
    short h218;
    u8 pad21a[0x2a0 - 0x21a];
    TI_F41eb487e q2A0;
    u8 pad2b0[0x2c0 - 0x2b0];
    u8 area2C0[0x31c - 0x2c0];
    float f31C;
    u8 pad320[0x34e - 0x320];
    short h34E;
    u8 pad350[0x22c3 - 0x350];
    u8 b22C3;
} ResidentState_F41eb487e;
#endif


extern ResidentState_F41eb487e LVL_7_SIBERIUS_F41eb487e_D_00189E20;

void LVL_7_SIBERIUS_FUN_002B7788(void)
{
    u8 scratch[64];
    Vec4_F41eb487e A, B, C;
    float hi = 0.035f;
    float lo = 0.3f;

    *(TI_F41eb487e *)&A = 0;
    *(TI_F41eb487e *)&B = 0;
    *(TI_F41eb487e *)&C = 0;

    A.c = 1.0f;
    B.c = 0.8f;
    C.c = 0.8f;

    LVL_7_SIBERIUS_F41eb487e_FUN_002E47F8(&B, &B, &LVL_7_SIBERIUS_F41eb487e_D_00189E20);

    *(TI_F41eb487e *)&A = *(TI_F41eb487e *)&LVL_7_SIBERIUS_F41eb487e_D_00189E20.q2A0;
    if (LVL_7_SIBERIUS_F41eb487e_D_00189E20.b22C3 == 2) {
        LVL_7_SIBERIUS_F41eb487e_FUN_002E4398(&A, &LVL_7_SIBERIUS_F41eb487e_D_00189E20.area2C0, -1.0f);
    }

    if (LVL_7_SIBERIUS_F41eb487e_D_00189E20.b22C3 == 1 && (LVL_7_SIBERIUS_F41eb487e_D_00189E20.h34E < 10 || LVL_7_SIBERIUS_F41eb487e_D_00189E20.f31C < 1.0f))
        *(TI_F41eb487e *)&A = *(TI_F41eb487e *)&LVL_7_SIBERIUS_F41eb487e_D_00189E20.q2A0;

    if (LVL_7_SIBERIUS_F41eb487e_D_00189E20.h34E != 0 && LVL_7_SIBERIUS_F41eb487e_D_00189E20.h218 != 0) {
        lo = 0.001f;
        hi = lo;
    }

    LVL_7_SIBERIUS_F41eb487e_FUN_002B74C8(&A, scratch, 0, hi, lo, 0.0f);

    if (LVL_7_SIBERIUS_F41eb487e_D_00189E20.b22C3 == 1 && LVL_7_SIBERIUS_F41eb487e_D_00189E20.h34E != 0) {
        LVL_7_SIBERIUS_F41eb487e_FUN_002E47F8(&C, &C, scratch);
        LVL_7_SIBERIUS_F41eb487e_FUN_002E4340(&LVL_7_SIBERIUS_F41eb487e_D_00189E20.area080, &LVL_7_SIBERIUS_F41eb487e_D_00189E20.area080, &C);
        LVL_7_SIBERIUS_F41eb487e_FUN_002E4310(&LVL_7_SIBERIUS_F41eb487e_D_00189E20.area080, &LVL_7_SIBERIUS_F41eb487e_D_00189E20.area080, &B);
    }
}
extern void LVL_7_SIBERIUS_F1edea3ae_FUN_002CD8F0(char *p);
extern void LVL_7_SIBERIUS_F1edea3ae_FUN_002CD8F0(char *p);
extern void LVL_7_SIBERIUS_F1edea3ae_FUN_002E42C8(char *p);
extern void LVL_7_SIBERIUS_F1edea3ae_FUN_004243C0(char *p);

void LVL_7_SIBERIUS_FUN_004244F8(char *self)
{
    char *q = (char *)*(int **)(self + 112) + 176;
    float *f;

    *(int *)(q + 64) = 0;
    f = (float *)*(int **)(self + 112);
    f[40] = 3.0000001192092895507812e-01f;
    f[41] = 3.0000001192092895507812e-01f;
    f[39] = 0.0f;
    f[42] = 0.0f;
    *(int *)(q + 68) = 0;
    f[43] = 0.0f;
    f[18] = 9.9000000953674316406250e-01f;
    f[15] = 3.9999999105930328369141e-02f;
    f[16] = 3.9999999105930328369141e-02f;
    f[17] = 3.9999999105930328369141e-02f;
    f[10] = 7.0000000298023223876953e-02f;
    f[11] = 1.0000000000000000000000e+00f;
    f[19] = 3.9999999105930328369141e-02f;
    f[12] = 7.0000000298023223876953e-02f;
    f[13] = 1.0000000000000000000000e+00f;
    f[14] = 7.0000000298023223876953e-02f;

    LVL_7_SIBERIUS_F1edea3ae_FUN_002CD8F0((char *)f + 80);
    LVL_7_SIBERIUS_F1edea3ae_FUN_002CD8F0((char *)f);
    LVL_7_SIBERIUS_F1edea3ae_FUN_002E42C8((char *)f + 144);
    LVL_7_SIBERIUS_F1edea3ae_FUN_004243C0(self);

    *(short *)(self + 126) = 0;
}
extern int LVL_7_SIBERIUS_Fb4cfb7e0_FUN_00310A98(int x);

void LVL_7_SIBERIUS_FUN_003F9C08(char *self)
{
    float *p = *(float **)(self + 104);
    float *q = p;
    int *w;
    int c;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *q = (float)LVL_7_SIBERIUS_Fb4cfb7e0_FUN_00310A98(255);
        q++;
    }

    p[4] = -1.0000000000000000000000e+00f;
    p[5] = -2.2500000000000000000000e+00f;
    p[6] = 1.2500000000000000000000e+00f;
    p[7] = 2.5000000000000000000000e+00f;

    j = 3;
    w = (int *)(p + 11);
    c = 255;
    for (; j >= 0; j--)
    {
        *w = c;
        w--;
        c -= 64;
    }

    p[12] = 2.5000000000000000000000e+00f;
    p[13] = 3.0000000000000000000000e+00f;
    p[15] = 2.5000000000000000000000e+00f;
    p[14] = 3.0000000000000000000000e+00f;
}
extern int LVL_7_SIBERIUS_Ff4dd22f3_FUN_002E3FB0(char *p);
extern void LVL_7_SIBERIUS_Ff4dd22f3_FUN_003263C0(char *p);
extern void LVL_7_SIBERIUS_Ff4dd22f3_FUN_002E4310(char *p, char *q, float *v);

void LVL_7_SIBERIUS_FUN_00335E58(char *self)
{
    char *p = self + 32;
    float v[4];
    int a1;

    if (LVL_7_SIBERIUS_Ff4dd22f3_FUN_002E3FB0(self + 10) != 0)
    {
        LVL_7_SIBERIUS_Ff4dd22f3_FUN_003263C0(self);
        return;
    }

    a1 = *(int *)(self + 4);
    *(int *)(self + 4) = (a1 & 0xffffff) | (((a1 >> 24) + (int)*(unsigned char *)(p + 20)) << 24);
    v[0] = *(float *)(self + 32);
    v[1] = *(float *)(p + 4);
    v[2] = *(float *)(p + 8);
    v[3] = 0.0f;
    LVL_7_SIBERIUS_Ff4dd22f3_FUN_002E4310(self + 16, self + 16, v);
    *(unsigned char *)(self + 8) += *(unsigned char *)(p + 21);
    *(float *)(self + 12) += *(float *)(p + 16);
    *(float *)(p + 8) -= *(float *)(p + 12);
}
extern void LVL_7_SIBERIUS_Fbbb7bee1_FUN_002E4070(int value);

void LVL_7_SIBERIUS_FUN_003710F0(int mask)
{
    while (*(volatile int *)0x10008000 & 0x100)
        LVL_7_SIBERIUS_Fbbb7bee1_FUN_002E4070(16);
    *(volatile int *)0x10008020 = 0;
    *(volatile int *)0x10008030 = mask & 0x0FFFFFFF;
    *(volatile int *)0x10008000 = 325;
    while (*(volatile int *)0x10008000 & 0x100)
        LVL_7_SIBERIUS_Fbbb7bee1_FUN_002E4070(16);
}
extern void LVL_7_SIBERIUS_F624a0727_FUN_00427F38(char *target);
#ifndef RAC2_T_ENTRY_F624A0727
#define RAC2_T_ENTRY_F624A0727
typedef struct { char pad[8]; short n; void (*fn)(char *); } ENTRY_F624a0727;
#endif


void LVL_7_SIBERIUS_FUN_0042C410(char *object)
{
    char *r = object + 12;
    char *q = object + 60;
    char *p = object + 392;
    int i;

    for (i = 4; i >= 0; i--) {
        if (*(short *)p != 0) {
            ENTRY_F624a0727 *t = *(ENTRY_F624a0727 **)q;
            t->fn(r + t->n);
        }
        r += 76;
        q += 76;
        p += 2;
    }
    if (*(int *)(object + 656) != 0) {
        LVL_7_SIBERIUS_F624a0727_FUN_00427F38(object + 408);
        if (*(int *)(object + 660) != 0) {
            if (*(int *)(object + 668) != 0)
                LVL_7_SIBERIUS_F624a0727_FUN_00427F38(object + 552);
            if (*(int *)(object + 664) != 0)
                LVL_7_SIBERIUS_F624a0727_FUN_00427F38(object + 480);
        }
    }
}
extern int LVL_7_SIBERIUS_F44faa168_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F44faa168_FUN_0043E2F0(int value, int argument);

void LVL_7_SIBERIUS_FUN_00302AD0(int argument)
{
    int value = LVL_7_SIBERIUS_F44faa168_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F44faa168_FUN_0043E2F0(value + 0x376C8, argument);
}
extern int LVL_7_SIBERIUS_F44faa168_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F44faa168_FUN_0043E360(int value, int argument);

void LVL_7_SIBERIUS_FUN_00302B48(int argument)
{
    int value = LVL_7_SIBERIUS_F44faa168_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F44faa168_FUN_0043E360(value + 0x376C8, argument);
}
extern int LVL_7_SIBERIUS_F44faa168_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F44faa168_FUN_0043E368(int value, int argument);

void LVL_7_SIBERIUS_FUN_00302B80(int argument)
{
    int value = LVL_7_SIBERIUS_F44faa168_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F44faa168_FUN_0043E368(value + 0x376C8, argument);
}
extern int LVL_7_SIBERIUS_F44faa168_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F44faa168_FUN_0043E370(int value, int argument);

void LVL_7_SIBERIUS_FUN_00304040(int argument)
{
    int value = LVL_7_SIBERIUS_F44faa168_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F44faa168_FUN_0043E370(value + 0x376C8, argument);
}
extern void LVL_7_SIBERIUS_Fd06ec510_FUN_003848D8(char *object);
extern void LVL_7_SIBERIUS_Fd06ec510_FUN_003844C0(char *object);
extern float LVL_7_SIBERIUS_Fd06ec510_FUN_002E5318(float value, float step);
extern void LVL_7_SIBERIUS_Fd06ec510_FUN_003843C0(char *object);
extern void LVL_7_SIBERIUS_Fd06ec510_FUN_00375A78(char *target, char *source);
extern void LVL_7_SIBERIUS_Fd06ec510_FUN_00375B30(char *target, char *source);
extern void LVL_7_SIBERIUS_Fd06ec510_FUN_00385D90(char *object);

void LVL_7_SIBERIUS_FUN_003841D8(char *object)
{
    char *s0 = object;
    unsigned char mode = *(unsigned char *)(s0 + 32);
    char *s1 = *(char **)(s0 + 104);
    float result;

    switch (mode) {
    case 0:
        if (*(int *)(s1 + 20) != 0) {
            LVL_7_SIBERIUS_Fd06ec510_FUN_003848D8(s0);
        } else {
            LVL_7_SIBERIUS_Fd06ec510_FUN_003844C0(s0);
        }
        result = LVL_7_SIBERIUS_Fd06ec510_FUN_002E5318(*(float *)(s0 + 240), 3.4906592220067977905273e-02f);
        *(float *)(s0 + 240) = result;
        result = LVL_7_SIBERIUS_Fd06ec510_FUN_002E5318(*(float *)(s0 + 244), 1.3089971244335174560547e-01f);
        *(float *)(s0 + 244) = result;
        LVL_7_SIBERIUS_Fd06ec510_FUN_003843C0(s0);
        break;
    case 1:
        LVL_7_SIBERIUS_Fd06ec510_FUN_00375A78((char *)(s0 + 16), (char *)(s0 + 16));
        LVL_7_SIBERIUS_Fd06ec510_FUN_00375B30(s1, s1);
        LVL_7_SIBERIUS_Fd06ec510_FUN_00385D90(s0);
        break;
    }
}
extern float LVL_7_SIBERIUS_F500f9762_FUN_002E5460(int index);
extern int LVL_7_SIBERIUS_F500f9762_FUN_002E5470(float value);
extern void LVL_7_SIBERIUS_F500f9762_FUN_003084A8(int first, char *a, char *b, char *c);

void LVL_7_SIBERIUS_FUN_003153E8(int first, char *object)
{
    char *s0 = object;
    short s1 = *(short *)(s0 + 0);
    unsigned short total;
    float limit;
    int result;

    if (s1 != 0 && *(short *)(s0 + 2) == 0)
        return;
    total = *(unsigned short *)(s0 + 12);
    *(short *)(s0 + 2) = 0;
    *(short *)(s0 + 0) = total;
    if (s1 != 0) {
        limit = LVL_7_SIBERIUS_F500f9762_FUN_002E5460(*(short *)(s0 + 14));
        result = LVL_7_SIBERIUS_F500f9762_FUN_002E5470((float)*(short *)(s0 + 12) * ((float)s1 / limit));
        *(short *)(s0 + 0) = (short)result;
        if ((short)result <= 0)
            *(short *)(s0 + 0) = 1;
    } else {
        int a, b, c;
        LVL_7_SIBERIUS_F500f9762_FUN_003084A8(first, (char *)&a, (char *)&b, (char *)&c);
        *(char *)(s0 + 4) = (unsigned char)a;
        *(char *)(s0 + 5) = (unsigned char)b;
        *(char *)(s0 + 6) = (unsigned char)c;
    }
}
extern void LVL_7_SIBERIUS_F8ad956d6_FUN_004277E0(char *target);
extern void LVL_7_SIBERIUS_F8ad956d6_FUN_003715E0(int marker, int code);
extern void LVL_7_SIBERIUS_F8ad956d6_FUN_002FCD88(int first, int second);
extern void LVL_7_SIBERIUS_F8ad956d6_FUN_0034A4A8(char *target);
extern void LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(char *target);

void LVL_7_SIBERIUS_FUN_0042B8A8(char *object)
{
    char *s0 = object;

    if (*(int *)(s0 + 1024) == 0)
        return;
    LVL_7_SIBERIUS_F8ad956d6_FUN_004277E0(s0 + 8);
    LVL_7_SIBERIUS_F8ad956d6_FUN_004277E0(s0 + 84);
    LVL_7_SIBERIUS_F8ad956d6_FUN_003715E0(66, 68);
    LVL_7_SIBERIUS_F8ad956d6_FUN_003715E0(71, 11);
    LVL_7_SIBERIUS_F8ad956d6_FUN_002FCD88(0, 1);
    LVL_7_SIBERIUS_F8ad956d6_FUN_0034A4A8(0);
    LVL_7_SIBERIUS_F8ad956d6_FUN_004277E0(s0 + 160);
    LVL_7_SIBERIUS_F8ad956d6_FUN_004277E0(s0 + 236);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 312);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 384);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 456);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 528);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 600);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 672);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 744);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 816);
    LVL_7_SIBERIUS_F8ad956d6_FUN_00427F38(s0 + 888);
}
extern void LVL_7_SIBERIUS_Fccb147a4_FUN_003263C0(char *a, char *b);
extern void LVL_7_SIBERIUS_Fccb147a4_FUN_00375A78(char *a, char *b);

void LVL_7_SIBERIUS_FUN_00330EB0(char *obj)
{
    char *sub = obj + 32;
    int w;
    int n;

    switch (*(unsigned char *)(sub + 2)) {
    case 2:
        *(float *)(obj + 16) = *(float *)(*(char **)(sub + 4) + 16) + *(float *)(sub + 16);
        *(float *)(obj + 20) = *(float *)(*(char **)(sub + 4) + 20) + *(float *)(sub + 20);
        *(float *)(obj + 24) = *(float *)(*(char **)(sub + 4) + 24) + *(float *)(sub + 24);
        break;
    case 1:
        goto tail;
    }
    w = *(int *)(obj + 4);
    n = (w >> 24);
    n = n - *(short *)(obj + 32);
    if (n <= 0) {
        LVL_7_SIBERIUS_Fccb147a4_FUN_003263C0(obj, sub);
        return;
    }
    *(int *)(obj + 4) = (w & 0xffffff) | (n << 24);
tail:
    if (*(unsigned char *)(sub + 3) != 0) {
        obj += 16;
        LVL_7_SIBERIUS_Fccb147a4_FUN_00375A78(obj, obj);
    }
}
extern void LVL_7_SIBERIUS_Fa5914967_FUN_002E45F0(float *a, float *b, float c);

void LVL_7_SIBERIUS_FUN_00314B18(float (*m)[4])
{
    int k;
    int i;
    float v[4];

    for (k = 0; k < 3; k++) {
        v[3] = 0.0f;
        for (i = 0; i < 3; i++)
            v[i] = m[i][k];
        LVL_7_SIBERIUS_Fa5914967_FUN_002E45F0(v, v, 1.0f);
        for (i = 0; i < 3; i++)
            m[i][k] = v[i];
    }
}
extern char *LVL_7_SIBERIUS_F476e86a4_FUN_004272D0(char *p);
extern char *LVL_7_SIBERIUS_F476e86a4_FUN_004272D0(char *p);
extern void LVL_7_SIBERIUS_F476e86a4_FUN_00427988(char *p, int a, int b);
extern void LVL_7_SIBERIUS_F476e86a4_FUN_004279C8(char *p, int a, int b);
extern void LVL_7_SIBERIUS_F476e86a4_FUN_004281A0(char *p, int a);

void LVL_7_SIBERIUS_FUN_0043F6F8(char *a0, int a1, int a2, int a3, int t0)
{
    char *base = a0 + a1 * 72;
    float *p;
    char *vt;

    p = (float *)LVL_7_SIBERIUS_F476e86a4_FUN_004272D0(base);
    p[0] = (float)a2;
    p = (float *)LVL_7_SIBERIUS_F476e86a4_FUN_004272D0(base);
    p[1] = (float)a3;
    LVL_7_SIBERIUS_F476e86a4_FUN_00427988(base, t0, t0);
    LVL_7_SIBERIUS_F476e86a4_FUN_004279C8(base, t0, t0);
    LVL_7_SIBERIUS_F476e86a4_FUN_004281A0(base, t0 << 24);
    vt = *(char **)(base + 48);
    (*(void (**)(char *))(vt + 12))(base + *(short *)(vt + 8));
}
extern int LVL_7_SIBERIUS_Fcdb4d905_FUN_002DA340(int a, int b, int c);

int LVL_7_SIBERIUS_FUN_002DA418(float x, int a, int b, int c, int d, int e, int g)
{
    int r, p, q, s;
    if (x < 0.5f) {
        r = LVL_7_SIBERIUS_Fcdb4d905_FUN_002DA340(a, b, c);
        if (r) return r;
        p = d;
        q = e;
        s = g;
    } else {
        r = LVL_7_SIBERIUS_Fcdb4d905_FUN_002DA340(d, e, g);
        if (r) return r;
        p = a;
        q = b;
        s = c;
    }
    return LVL_7_SIBERIUS_Fcdb4d905_FUN_002DA340(p, q, s);
}
extern char *LVL_7_SIBERIUS_F97fc4e13_FUN_0034EE30(int a0, int a1);
extern void LVL_7_SIBERIUS_F97fc4e13_FUN_002E40E8(char *target, char *base, int len);

void LVL_7_SIBERIUS_FUN_0034EE78(char *a0)
{
    int i = 0;

    if (i < *(int *)a0) {
        int one = 1;
        char *d = a0 + 8;
        char *e = a0 + 4;

        do {
            char *obj = LVL_7_SIBERIUS_F97fc4e13_FUN_0034EE30(*(short *)(e + 14), *(short *)(e + 12));
            if (obj != 0) {
                char *t;
                if (*(short *)(e + 10) == one)
                    t = (char *)(*(int *)e + (int)obj);
                else
                    t = (char *)(*(int *)e + *(int *)(obj + 104));
                LVL_7_SIBERIUS_F97fc4e13_FUN_002E40E8(t, d, *(unsigned short *)(e + 8));
            }
            i++;
            d += 16;
            e += 16;
        } while (i < *(int *)a0);
    }
}
extern char *LVL_7_SIBERIUS_F1fa78648_FUN_00320648(int a0, int a1);
extern char *LVL_7_SIBERIUS_F1fa78648_FUN_00320678(int a0, int a1);
extern int LVL_7_SIBERIUS_F1fa78648_FUN_002E3FB0(char *a0);
extern float LVL_7_SIBERIUS_F1fa78648_FUN_002E5318(float a0, float a1);

int LVL_7_SIBERIUS_FUN_003E1F08(int *a0)
{
    int i;
    int count = 0;
    char *base;
    char *rec;
    char *obj;

    rec = *(char **)((char *)a0 + 104);
    base = LVL_7_SIBERIUS_F1fa78648_FUN_00320648(3076, *(short *)(rec + 26));
    base = base + *(int *)(LVL_7_SIBERIUS_F1fa78648_FUN_00320678(3076, *(short *)(rec + 26)) + 4);
    obj = base + 16;
    rec = base;

    for (i = 119; i >= 0; i--) {
        if (*(short *)(rec + 18) != 0) {
            if (LVL_7_SIBERIUS_F1fa78648_FUN_002E3FB0(obj) != 0) {
                *(short *)(rec + 18) = 0;
            } else {
                count++;
                *(float *)(rec + 24) = LVL_7_SIBERIUS_F1fa78648_FUN_002E5318(*(float *)(rec + 24), *(float *)(rec + 28));
            }
        }
        obj += 64;
        rec += 64;
    }
    return count;
}
extern void LVL_7_SIBERIUS_F6402b823_FUN_004277E0(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_004277E0(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_004277E0(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_004277E0(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00427F38(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00427F38(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00427F38(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00427328(char *a, int b);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00436730(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00436550(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00436460(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00436640(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_00435E00(char *a);
extern void LVL_7_SIBERIUS_F6402b823_FUN_004277E0(char *a);

void LVL_7_SIBERIUS_FUN_00436820(char *obj)
{
    if (*(int *)(obj + 1080) != 0) {
        char *s0 = obj + 456;

        LVL_7_SIBERIUS_F6402b823_FUN_004277E0(obj);
        LVL_7_SIBERIUS_F6402b823_FUN_004277E0(obj + 76);
        LVL_7_SIBERIUS_F6402b823_FUN_004277E0(obj + 152);
        LVL_7_SIBERIUS_F6402b823_FUN_004277E0(obj + 228);
        LVL_7_SIBERIUS_F6402b823_FUN_00427F38(s0);
        LVL_7_SIBERIUS_F6402b823_FUN_00427F38(obj + 664);
        LVL_7_SIBERIUS_F6402b823_FUN_00427F38(s0);
        LVL_7_SIBERIUS_F6402b823_FUN_00427328(obj + 528, 0);
        LVL_7_SIBERIUS_F6402b823_FUN_00436730(obj);
        LVL_7_SIBERIUS_F6402b823_FUN_00436550(obj);
        LVL_7_SIBERIUS_F6402b823_FUN_00436460(obj);
        LVL_7_SIBERIUS_F6402b823_FUN_00436640(obj);
        LVL_7_SIBERIUS_F6402b823_FUN_00435E00(obj);
        LVL_7_SIBERIUS_F6402b823_FUN_004277E0(obj + 380);
    }
}
extern void LVL_7_SIBERIUS_F36efd143_FUN_00427488(char *a);
extern void *LVL_7_SIBERIUS_F36efd143_FUN_00428300(char *a);
extern void *LVL_7_SIBERIUS_F36efd143_FUN_00428268(int size, void *b);
extern void *LVL_7_SIBERIUS_F36efd143_FUN_00428300(char *a);
extern void *LVL_7_SIBERIUS_F36efd143_FUN_00428268(int size, void *b);
void LVL_7_SIBERIUS_FUN_004276A0(char *obj)
{
    int *p;
    int x;
    LVL_7_SIBERIUS_F36efd143_FUN_00427488(obj);
    if (*(int *)(obj + 44) != 0) {
        p = (int *)LVL_7_SIBERIUS_F36efd143_FUN_00428268(16, LVL_7_SIBERIUS_F36efd143_FUN_00428300(*(int *)(obj + 44)));
        *(int *)(obj + 52) = (int)p;
        x = *(int *)(obj + 44);
        p[1] = 0; p[2] = 0; p[3] = 0; p[0] = 0;
        p = (int *)LVL_7_SIBERIUS_F36efd143_FUN_00428268(16, LVL_7_SIBERIUS_F36efd143_FUN_00428300(x));
        *(int *)(obj + 56) = (int)p;
        {
            float *f = (float *)*(int *)(obj + 4);
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
            p[0] = 0;
            f[0] = 1.0f;
            *(float *)(*(int *)(obj + 4) + 4) = 1.0f;
            *(float *)(*(int *)(obj + 4) + 8) = 1.0f;
        }
    }
    *(int *)(obj + 68) = 0;
    *(int *)(obj + 72) = 0;
}
extern int LVL_7_SIBERIUS_F29eece9b_FUN_00355260(char *p, int a1, char *a2, int a3, int a4);
extern char LVL_7_SIBERIUS_F29eece9b_D_00188660[];

int LVL_7_SIBERIUS_FUN_00355488(int index, int a1, char *a2)
{
    int v0;
    int v1;
    int r;
    char *p;

    if (a2 == 0)
        return -1;
    v0 = *(int *)(a2 + 36);
    if (v0 == 0)
        return -1;
    v1 = *(int *)(v0 + 40);
    if (v1 == 0)
        return -1;
    v0 = *(unsigned char *)(v0 + 13);
    if (index >= v0)
        return -1;
    r = LVL_7_SIBERIUS_F29eece9b_FUN_00355260((char *)(v1 + index * 32), a1, a2, 0, 1024);
    if (r >= 0) {
        p = &LVL_7_SIBERIUS_F29eece9b_D_00188660[r * 112];
        *(int *)(p + 136) = (int)a2;
        *(short *)(p + 126) = (short)index;
    }
    return r;
}
extern void LVL_7_SIBERIUS_F081de6c9_FUN_00427488(char *s, int a1, char *a2);
extern int LVL_7_SIBERIUS_F081de6c9_FUN_00428300(int x);
extern int *LVL_7_SIBERIUS_F081de6c9_FUN_00428268(int n, int x);

void LVL_7_SIBERIUS_FUN_00427BD0(char *s1, int a1, char *a2)
{
    LVL_7_SIBERIUS_F081de6c9_FUN_00427488(s1, a1, a2);
    if (a2 != 0) {
        int *v = LVL_7_SIBERIUS_F081de6c9_FUN_00428268(16, LVL_7_SIBERIUS_F081de6c9_FUN_00428300(*(int *)(s1 + 44)));

        *(int **)(s1 + 52) = v;
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
        v[0] = 0;
    }
    ((int *)*(int **)(s1 + 52))[0] = 0;
    ((int *)*(int **)(s1 + 52))[1] = 0;
    *(float *)(*(char **)s1 + 0) = 100.0f;
    *(float *)(*(char **)s1 + 4) = 100.0f;
    *(float *)(*((char **)s1 + 1) + 0) = 64.0f;
    *(float *)(*((char **)s1 + 1) + 4) = 64.0f;
    *(int *)(s1 + 56) = 0;
}
extern void LVL_7_SIBERIUS_F15a8b7f0_FUN_002E4398(char *first, char *second, float blend);
extern void LVL_7_SIBERIUS_F15a8b7f0_FUN_002E4310(char *first, char *second, char *third);
extern void LVL_7_SIBERIUS_F15a8b7f0_FUN_003263C0(char *object);

void LVL_7_SIBERIUS_FUN_0032FFC8(char *object)
{
    int count;
    int low;
    int high;

    LVL_7_SIBERIUS_F15a8b7f0_FUN_002E4398(object + 32, object + 32, 0.975f);
    LVL_7_SIBERIUS_F15a8b7f0_FUN_002E4310(object + 16, object + 16, object + 32);
    *(float *)(object + 12) += 6300.0f;
    count = *(unsigned char *)(object + 4) - 4;
    if (count <= 0)
        LVL_7_SIBERIUS_F15a8b7f0_FUN_003263C0(object);
    else {
        low = (count << 8) | 0x60000000;
        high = (count << 16) | low;
        *(int *)(object + 4) = high | count;
    }
}
extern void LVL_7_SIBERIUS_F8b17817c_FUN_00427668(char *block);
extern void LVL_7_SIBERIUS_F8b17817c_FUN_00427E28(char *block);
extern void LVL_7_SIBERIUS_F8b17817c_FUN_00427B90(char *block);

char *LVL_7_SIBERIUS_FUN_0042C580(char *object)
{
    int index;
    char *block;

    LVL_7_SIBERIUS_F8b17817c_FUN_00427668(object);
    LVL_7_SIBERIUS_F8b17817c_FUN_00427668(object + 76);
    LVL_7_SIBERIUS_F8b17817c_FUN_00427668(object + 152);
    block = object + 228;
    for (index = 2; index != -1; index--) {
        LVL_7_SIBERIUS_F8b17817c_FUN_00427668(block);
        block += 76;
    }
    LVL_7_SIBERIUS_F8b17817c_FUN_00427E28(object + 472);
    LVL_7_SIBERIUS_F8b17817c_FUN_00427E28(object + 544);
    LVL_7_SIBERIUS_F8b17817c_FUN_00427E28(object + 616);
    LVL_7_SIBERIUS_F8b17817c_FUN_00427B90(object + 688);
    LVL_7_SIBERIUS_F8b17817c_FUN_00427B90(object + 748);
    return object;
}
extern int LVL_7_SIBERIUS_Fbfc8418e_FUN_002E3FB0(char *handle);
extern void LVL_7_SIBERIUS_Fbfc8418e_FUN_00306800(char *object);

void LVL_7_SIBERIUS_FUN_00408768(char *object)
{
    char *handle = *(char **)(object + 104);

    if (LVL_7_SIBERIUS_Fbfc8418e_FUN_002E3FB0(handle) == 0)
        LVL_7_SIBERIUS_Fbfc8418e_FUN_002E3FB0(handle + 4);
    else
        LVL_7_SIBERIUS_Fbfc8418e_FUN_00306800(object);
}
extern int LVL_7_SIBERIUS_Fbfc8418e_FUN_002E3FB0(char *handle);
extern void LVL_7_SIBERIUS_Fbfc8418e_FUN_00306800(char *object);

void LVL_7_SIBERIUS_FUN_00415970(char *object)
{
    char *handle = *(char **)(object + 104);

    if (LVL_7_SIBERIUS_Fbfc8418e_FUN_002E3FB0(handle) == 0)
        LVL_7_SIBERIUS_Fbfc8418e_FUN_002E3FB0(handle + 4);
    else
        LVL_7_SIBERIUS_Fbfc8418e_FUN_00306800(object);
}
extern void LVL_7_SIBERIUS_Ff26f272a_FUN_002D0118(char *first, char *second, char *third);
extern float LVL_7_SIBERIUS_Ff26f272a_FUN_002E5318(float value, float reference);
extern void LVL_7_SIBERIUS_Ff26f272a_FUN_002E4B90(char *out, char *source);
extern void LVL_7_SIBERIUS_Ff26f272a_FUN_002E4DF8(char *object, char *out);

void LVL_7_SIBERIUS_FUN_004243C0(char *object)
{
    float local[16];
    char *child = *(char **)(object + 112);

    child += 176;
    LVL_7_SIBERIUS_Ff26f272a_FUN_002D0118(object + 48, object + 80, child);
    *(float *)(object + 80) = LVL_7_SIBERIUS_Ff26f272a_FUN_002E5318(*(float *)(object + 80), *(float *)(child + 24));
    *(int *)(object + 64) = 0;
    *(float *)(object + 68) = LVL_7_SIBERIUS_Ff26f272a_FUN_002E5318(*(float *)(object + 84), *(float *)(object + 92));
    *(float *)(object + 72) = LVL_7_SIBERIUS_Ff26f272a_FUN_002E5318(3.14159265f, *(float *)(object + 80));
    *(float *)(object + 72) = LVL_7_SIBERIUS_Ff26f272a_FUN_002E5318(*(float *)(object + 72), *(float *)(object + 96));
    *(int *)(object + 76) = 0;
    LVL_7_SIBERIUS_Ff26f272a_FUN_002E4B90((char *)local, object + 64);
    LVL_7_SIBERIUS_Ff26f272a_FUN_002E4DF8(object, (char *)local);
}
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427890(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427B90(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(char *p);

void *LVL_7_SIBERIUS_FUN_00437B38(char *p)
{
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p + 0x4c);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p + 0x98);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p + 0xe4);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p + 0x130);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p + 0x17c);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427890(p + 0x1c8);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(p + 0x210);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(p + 0x258);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(p + 0x2a0);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(p + 0x2e8);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427E28(p + 0x330);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427B90(p + 0x378);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p + 0x3b4);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p + 0x400);
    LVL_7_SIBERIUS_F5a9e4f98_FUN_00427668(p + 0x44c);

    return p;
}
extern void LVL_7_SIBERIUS_F72a1dff5_FUN_0043AF80(char *p, int a);
extern void LVL_7_SIBERIUS_F72a1dff5_FUN_0043AF80(char *p, int a);
extern void LVL_7_SIBERIUS_F72a1dff5_FUN_0043AF80(char *p, int a);
extern void LVL_7_SIBERIUS_F72a1dff5_FUN_0043AAF8(char *p, int a);
extern void LVL_7_SIBERIUS_F72a1dff5_FUN_0043AF80(char *p, int a);
extern void LVL_7_SIBERIUS_F72a1dff5_FUN_00427DE0(char *p, void *b, int c);
extern void LVL_7_SIBERIUS_F72a1dff5_FUN_00427DE0(char *p, void *b, int c);

void LVL_7_SIBERIUS_FUN_0043DFB0(char *p, void *a1, int a2)
{
    *(int *)(p + 0x1564) = a2;
    if (*(int *)(p + 0x1568) != 0) {
        *(int *)(p + 0x1568) = 0;
        LVL_7_SIBERIUS_F72a1dff5_FUN_0043AF80(p + 0xf1c, 0);
        LVL_7_SIBERIUS_F72a1dff5_FUN_0043AF80(p + 0xfb0, 0);
        LVL_7_SIBERIUS_F72a1dff5_FUN_0043AF80(p + 0x1044, 0);
        LVL_7_SIBERIUS_F72a1dff5_FUN_0043AAF8(p + 0x10d8, 1);
        LVL_7_SIBERIUS_F72a1dff5_FUN_0043AF80(p + 0x1160, 0);
        LVL_7_SIBERIUS_F72a1dff5_FUN_00427DE0(p + 0x148, a1, 0);
    }
    if (*(int *)(p + 0x157c) != 0) {
        LVL_7_SIBERIUS_F72a1dff5_FUN_00427DE0(p + 0x148, a1, 0);
    }
}
extern void LVL_7_SIBERIUS_Fa03721e9_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_Fa03721e9_FUN_003263C0(char *p);

void LVL_7_SIBERIUS_FUN_00331738(char *p)
{
    char *q = p + 32;

    LVL_7_SIBERIUS_Fa03721e9_FUN_002E4310(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + *(float *)(q + 16);
    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + 1;
    if (--*(short *)(p + 10) == 0) {
        *(unsigned int *)(p + 4) = *(unsigned int *)(p + 4) + 0xff000000;
        *(short *)(p + 10) = 2;
    }
    if ((*(unsigned int *)(p + 4) & 0xff000000) == 0)
        LVL_7_SIBERIUS_Fa03721e9_FUN_003263C0(p);
}
extern char *LVL_7_SIBERIUS_F8622720f_D_001A904C __attribute__((sda));
extern char *LVL_7_SIBERIUS_F8622720f_D_001A904C __attribute__((sda));
extern char *LVL_7_SIBERIUS_F8622720f_D_001A904C __attribute__((sda));
extern char *LVL_7_SIBERIUS_F8622720f_D_001A904C __attribute__((sda));
extern char *LVL_7_SIBERIUS_F8622720f_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F8622720f_FUN_00427850(char *dst, char *src, int value);

void LVL_7_SIBERIUS_FUN_00439A48(char *object, int *values)
{
    LVL_7_SIBERIUS_F8622720f_FUN_00427850(object,       LVL_7_SIBERIUS_F8622720f_D_001A904C + 0x8710, values[0]);
    LVL_7_SIBERIUS_F8622720f_FUN_00427850(object + 304, LVL_7_SIBERIUS_F8622720f_D_001A904C + 0x8710, values[2]);
    LVL_7_SIBERIUS_F8622720f_FUN_00427850(object + 76,  LVL_7_SIBERIUS_F8622720f_D_001A904C + 0x8710, values[4]);
    LVL_7_SIBERIUS_F8622720f_FUN_00427850(object + 152, LVL_7_SIBERIUS_F8622720f_D_001A904C + 0x8710, values[8]);
    LVL_7_SIBERIUS_F8622720f_FUN_00427850(object + 228, LVL_7_SIBERIUS_F8622720f_D_001A904C + 0x8710, values[6]);
}
extern unsigned char LVL_7_SIBERIUS_F1f401dc9_D_00189E20[];
extern float LVL_7_SIBERIUS_F1f401dc9_FUN_002E4488(char *object);
extern void LVL_7_SIBERIUS_F1f401dc9_FUN_002E4B90(char *dst, char *src);
extern void LVL_7_SIBERIUS_F1f401dc9_FUN_002E4E18(char *dst, char *src);
extern void LVL_7_SIBERIUS_F1f401dc9_FUN_002E47F8(char *dst, char *src, char *extra);

float LVL_7_SIBERIUS_FUN_002C9A08(char *arg)
{
    char first[64];
    char second[64];
    char third[16];
    unsigned char *p = LVL_7_SIBERIUS_F1f401dc9_D_00189E20;
    int flag = p[8899];

    if (flag == 0)
        return LVL_7_SIBERIUS_F1f401dc9_FUN_002E4488(arg);
    if (flag < 0)
        return 0.0f;
    if (flag >= 3)
        return 0.0f;
    LVL_7_SIBERIUS_F1f401dc9_FUN_002E4B90(first, (char *)(*(int *)(p + 8848) + 240));
    LVL_7_SIBERIUS_F1f401dc9_FUN_002E4E18(second, first);
    LVL_7_SIBERIUS_F1f401dc9_FUN_002E47F8(third, arg, second);
    return LVL_7_SIBERIUS_F1f401dc9_FUN_002E4488(third);
}
extern void LVL_7_SIBERIUS_F280d7406_FUN_002E4310(char *dst, char *left, char *right);
extern void LVL_7_SIBERIUS_F280d7406_FUN_00375A78(char *dst, char *src);
extern int LVL_7_SIBERIUS_F280d7406_FUN_002E5470(float value);
extern void LVL_7_SIBERIUS_F280d7406_FUN_003263C0(char *object);

void LVL_7_SIBERIUS_FUN_0032A858(char *a)
{
    char *p1 = a + 16;
    char *p2 = a + 32;
    char *p3 = a + 48;
    int v;

    LVL_7_SIBERIUS_F280d7406_FUN_002E4310(p1, p1, p3);
    LVL_7_SIBERIUS_F280d7406_FUN_002E4310(p2, p2, p3);
    LVL_7_SIBERIUS_F280d7406_FUN_00375A78(p1, p1);
    LVL_7_SIBERIUS_F280d7406_FUN_00375A78(p2, p2);
    v = *(int *)(a + 4) - (LVL_7_SIBERIUS_F280d7406_FUN_002E5470(*(float *)(p3 + 12)) << 24);
    *(int *)(a + 4) = v;
    *(int *)(a + 12) = v;
    if (v < 0)
        LVL_7_SIBERIUS_F280d7406_FUN_003263C0(a);
}
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00437770(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00437890(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00437998(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(char *p);
extern void LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(char *p);

void LVL_7_SIBERIUS_FUN_00437A98(char *a0)
{
    if (*(int *)(a0 + 1160) == 0)
        return;
    LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(a0);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(a0 + 76);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(a0 + 152);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(a0 + 228);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(a0 + 456);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00437770(a0);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00437890(a0);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00437998(a0);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_004277E0(a0 + 380);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(a0 + 736);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(a0 + 664);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(a0 + 808);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(a0 + 880);
    LVL_7_SIBERIUS_Fd1c2476b_FUN_00427F38(a0 + 952);
}
extern int LVL_7_SIBERIUS_Fb77d67f1_FUN_002E3F80(char *p);
extern void LVL_7_SIBERIUS_Fb77d67f1_FUN_003263C0(char *p);

void LVL_7_SIBERIUS_FUN_003289D8(char *a0)
{
    char *p = a0 + 32;

    if (LVL_7_SIBERIUS_Fb77d67f1_FUN_002E3F80(p) != 0) {
        LVL_7_SIBERIUS_Fb77d67f1_FUN_003263C0(a0);
        return;
    }
    *(float *)(a0 + 12) = *(float *)(a0 + 12) + *(float *)(p + 4);
    if (*(int *)(a0 + 32) < 6)
        *(int *)(a0 + 4) = (*(int *)(a0 + 4) & 0xFFFFFF)
                         | ((*(int *)(a0 + 32) * 127 / 6) << 24);
}
extern void LVL_7_SIBERIUS_Faac80289_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_Faac80289_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_Faac80289_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_Faac80289_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_Faac80289_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_Faac80289_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_Faac80289_FUN_00427668(char *p);
extern void LVL_7_SIBERIUS_Faac80289_FUN_00427E28(char *p);

char *LVL_7_SIBERIUS_FUN_00439990(char *a0)
{
    char *p = a0 + 536;
    int i;

    LVL_7_SIBERIUS_Faac80289_FUN_00427668(a0);
    LVL_7_SIBERIUS_Faac80289_FUN_00427668(a0 + 76);
    LVL_7_SIBERIUS_Faac80289_FUN_00427668(a0 + 152);
    LVL_7_SIBERIUS_Faac80289_FUN_00427668(a0 + 228);
    LVL_7_SIBERIUS_Faac80289_FUN_00427668(a0 + 304);
    LVL_7_SIBERIUS_Faac80289_FUN_00427668(a0 + 380);
    LVL_7_SIBERIUS_Faac80289_FUN_00427668(a0 + 456);

    for (i = 6; i != -1; i--) {
        LVL_7_SIBERIUS_Faac80289_FUN_00427E28(p);
        p += 72;
    }
    return a0;
}
extern int LVL_7_SIBERIUS_Ff67aa9df_D_001A7350 __attribute__((sda));
extern int LVL_7_SIBERIUS_Ff67aa9df_D_001A7354 __attribute__((sda));
extern void LVL_7_SIBERIUS_Ff67aa9df_FUN_002DE988(void *v, void *x);

void LVL_7_SIBERIUS_FUN_002DEA48(int i0, int i1, int i2, int i3, int tag, void *x)
{
    long long v[4];

    v[0] = (((i0 << 4) + LVL_7_SIBERIUS_Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i1 << 4) + LVL_7_SIBERIUS_Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[1] = (((i2 << 4) + LVL_7_SIBERIUS_Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i1 << 4) + LVL_7_SIBERIUS_Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[2] = (((i0 << 4) + LVL_7_SIBERIUS_Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i3 << 4) + LVL_7_SIBERIUS_Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    v[3] = (((i2 << 4) + LVL_7_SIBERIUS_Ff67aa9df_D_001A7350) - 8)
         | ((long long)(((i3 << 4) + LVL_7_SIBERIUS_Ff67aa9df_D_001A7354) - 8) << 16)
         | ((long long)tag << 32);
    LVL_7_SIBERIUS_Ff67aa9df_FUN_002DE988(v, x);
}
extern void LVL_7_SIBERIUS_Fc558ca70_FUN_0042C2F0(char *p);
extern void LVL_7_SIBERIUS_Fc558ca70_FUN_0042C4E0(char *p, float a, float b);
extern void LVL_7_SIBERIUS_Fc558ca70_FUN_003555E8(int a, int b, int c);

extern volatile unsigned char LVL_7_SIBERIUS_Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char LVL_7_SIBERIUS_Fc558ca70_D_001A7B94 __attribute__((sda));

int LVL_7_SIBERIUS_FUN_0042DFE0(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    LVL_7_SIBERIUS_Fc558ca70_FUN_0042C2F0(p);
    q = *(float **)(a0 + 684);
    LVL_7_SIBERIUS_Fc558ca70_FUN_0042C4E0(p, q[0], q[1]);
    if (a1 & 0x1000) {
        LVL_7_SIBERIUS_Fc558ca70_FUN_003555E8(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        LVL_7_SIBERIUS_Fc558ca70_FUN_003555E8(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        LVL_7_SIBERIUS_Fc558ca70_FUN_003555E8(4, 0, 0);
        switch (*(int *)(a0 + 680)) {
        case 0:
            LVL_7_SIBERIUS_Fc558ca70_D_001A7B95 = LVL_7_SIBERIUS_Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            LVL_7_SIBERIUS_Fc558ca70_D_001A7B94 = LVL_7_SIBERIUS_Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}
extern void LVL_7_SIBERIUS_Fb7feb893_FUN_0042C2F0(char *p);
extern void LVL_7_SIBERIUS_Fb7feb893_FUN_0042C4E0(char *p, float a, float b);
extern void LVL_7_SIBERIUS_Fb7feb893_FUN_003555E8(int a, int b, int c);

extern volatile unsigned char LVL_7_SIBERIUS_Fb7feb893_D_001A7BB2 __attribute__((sda));
extern volatile unsigned char LVL_7_SIBERIUS_Fb7feb893_D_001A7BB3 __attribute__((sda));

int LVL_7_SIBERIUS_FUN_0042ED30(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    LVL_7_SIBERIUS_Fb7feb893_FUN_0042C2F0(p);
    q = *(float **)(a0 + 684);
    LVL_7_SIBERIUS_Fb7feb893_FUN_0042C4E0(p, q[0], q[1]);
    if (a1 & 0x1000) {
        LVL_7_SIBERIUS_Fb7feb893_FUN_003555E8(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        LVL_7_SIBERIUS_Fb7feb893_FUN_003555E8(3, 0, 0);
        v = *(int *)(a0 + 680);
        *(int *)(a0 + 680) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        LVL_7_SIBERIUS_Fb7feb893_FUN_003555E8(4, 0, 0);
        switch (*(int *)(a0 + 680)) {
        case 0:
            LVL_7_SIBERIUS_Fb7feb893_D_001A7BB2 = LVL_7_SIBERIUS_Fb7feb893_D_001A7BB2 == 0;
            break;
        case 1:
            LVL_7_SIBERIUS_Fb7feb893_D_001A7BB3 = LVL_7_SIBERIUS_Fb7feb893_D_001A7BB3 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}
#ifndef RAC2_T_V4_F213135AA
#define RAC2_T_V4_F213135AA
typedef struct { float x, y, z, w; } V4_F213135aa;
#endif


extern float LVL_7_SIBERIUS_F213135aa_FUN_00310B30(float a, float b);
extern float LVL_7_SIBERIUS_F213135aa_FUN_00310B30(float a, float b);
extern void LVL_7_SIBERIUS_F213135aa_FUN_002E4B70(char *a, char *b);
extern void LVL_7_SIBERIUS_F213135aa_FUN_002E45F0(char *a, char *b, float f);
extern void LVL_7_SIBERIUS_F213135aa_FUN_002E4340(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F213135aa_FUN_002E4440(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F213135aa_FUN_002E45F0(char *a, char *b, float f);
extern void LVL_7_SIBERIUS_F213135aa_FUN_00315158(char *a, char *b, float f);

int LVL_7_SIBERIUS_FUN_00377EB0(char *obj, char *obj2, float x, float y)
{
    V4_F213135aa m0, m1, m2;
    char *s1;
    char *s3;
    float f22;

    s1 = *(char **)(obj + 104);
    if (*(unsigned char *)(obj + 32) == 4)
        return 0;
    f22 = 0.0f;
    if (x == 0.0f)
        x = LVL_7_SIBERIUS_F213135aa_FUN_00310B30(-30.0f, 30.0f) * 1.7453294247388839721680e-02f;
    if (y == 0.0f)
        y = LVL_7_SIBERIUS_F213135aa_FUN_00310B30(f22, 30.0f) * 1.7453294247388839721680e-02f;
    s3 = s1 + 32;
    if (*(unsigned char *)(obj + 32) == 3) {
        LVL_7_SIBERIUS_F213135aa_FUN_002E4B70((char *)&m0, s1 + 16);
        LVL_7_SIBERIUS_F213135aa_FUN_002E45F0(s3, (char *)&m2, 1.3333334028720855712891e-01f);
    }
    *(float *)(s1 + 100) = f22;
    *(float *)(s1 + 76) = x;
    *(float *)(s1 + 72) = y;
    *(char **)(s1 + 96) = obj2;
    LVL_7_SIBERIUS_F213135aa_FUN_002E4340((char *)&m1, obj2 + 16, obj + 16);
    s1 = s1 + 48;
    LVL_7_SIBERIUS_F213135aa_FUN_002E4440((char *)&m0, s3, (char *)&m1);
    LVL_7_SIBERIUS_F213135aa_FUN_002E45F0(s1, (char *)&m0, 1.0f);
    LVL_7_SIBERIUS_F213135aa_FUN_00315158(s1, s1, 2.0943954586982727050781e-01f);
    *(unsigned char *)(obj + 32) = 4;
    return 1;
}
extern void LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C2F0(char *p);
extern void LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C4E0(char *p, float x, float y);
extern int LVL_7_SIBERIUS_Fb1bbe20c_FUN_003555E8(int a, int b, int c);
extern volatile unsigned char LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 __attribute__((sda));

int LVL_7_SIBERIUS_FUN_0042F0F8(char *object, int flags)
{
    float *vec;

    LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C2F0(object + 8);
    vec = *(float **)(object + 684);
    LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C4E0(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = LVL_7_SIBERIUS_Fb1bbe20c_FUN_003555E8(4, 0, 0);
        (void)discarded;
        LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 = (LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}
extern void LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C2F0(char *p);
extern void LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C4E0(char *p, float x, float y);
extern int LVL_7_SIBERIUS_Fb1bbe20c_FUN_003555E8(int a, int b, int c);
extern volatile unsigned char LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 __attribute__((sda));

int LVL_7_SIBERIUS_FUN_0042F3A8(char *object, int flags)
{
    float *vec;

    LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C2F0(object + 8);
    vec = *(float **)(object + 684);
    LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C4E0(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = LVL_7_SIBERIUS_Fb1bbe20c_FUN_003555E8(4, 0, 0);
        (void)discarded;
        LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 = (LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}
extern void LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C2F0(char *p);
extern void LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C4E0(char *p, float x, float y);
extern int LVL_7_SIBERIUS_Fb1bbe20c_FUN_003555E8(int a, int b, int c);
extern volatile unsigned char LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 __attribute__((sda));

int LVL_7_SIBERIUS_FUN_0042F5A0(char *object, int flags)
{
    float *vec;

    LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C2F0(object + 8);
    vec = *(float **)(object + 684);
    LVL_7_SIBERIUS_Fb1bbe20c_FUN_0042C4E0(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = LVL_7_SIBERIUS_Fb1bbe20c_FUN_003555E8(4, 0, 0);
        (void)discarded;
        LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 = (LVL_7_SIBERIUS_Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_0030B908(unsigned char *a, int b, unsigned char *c);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4868(unsigned char *a, long long v);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4868(unsigned char *a, long long v);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E47F8(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E47F8(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4398(unsigned char *a, unsigned char *b, float f);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4398(unsigned char *a, unsigned char *b, float f);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E47D0(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E47D0(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4310(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4310(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4310(unsigned char *a, unsigned char *b, unsigned char *c);
extern void LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4398(unsigned char *a, unsigned char *b, float f);
extern float LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E44D0(unsigned char *a, unsigned char *b);

void LVL_7_SIBERIUS_FUN_00306CC8(
    unsigned char *obj, unsigned int index, unsigned char *dest)
{
    unsigned char m0[16];
    unsigned char m1[16];
    unsigned char *base;
    unsigned char *p;
    short n;

    base = *(unsigned char **)(obj + 36);
    p = base + ((unsigned int)*(unsigned char *)(base + 44) << 4);
    p = p + ((index << 4) + 64u);
    n = *(short *)(p + 6);
    if (n < *(short *)(p + 14))
        n = *(short *)(p + 14);
    if (n >= 0)
        LVL_7_SIBERIUS_Ff2d8e5ad_FUN_0030B908(obj, n + 1, (unsigned char *)0x80000000u);
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4868(m0, *(long long *)(p));
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4868(m1, *(long long *)(p + 8));
    *(float *)(m0 + 12) = 1.0f;
    *(float *)(m1 + 12) = 1.0f;
    if (n >= 0) {
        LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E47F8(m0, m0, (unsigned char *)
            (((unsigned int)*(short *)(p + 6) << 6) + 0x70000000u));
        LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E47F8(m1, m1, (unsigned char *)
            (((unsigned int)*(short *)(p + 14) << 6) + 0x70000000u));
    }
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4398(m0, m0, *(float *)(obj + 44) * 0.0009765625f);
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4398(m1, m1, *(float *)(obj + 44) * 0.0009765625f);
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E47D0(m0, m0, obj + 192);
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E47D0(m1, m1, obj + 192);
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4310(m0, m0, obj + 16);
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4310(m1, m1, obj + 16);
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4310(dest, m0, m1);
    LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E4398(dest, dest, 0.5f);
    *(float *)(dest + 12) = LVL_7_SIBERIUS_Ff2d8e5ad_FUN_002E44D0(dest, m0);
}
extern void LVL_7_SIBERIUS_F5a19df7a_FUN_003715E0(unsigned int a, unsigned long b);
extern void LVL_7_SIBERIUS_F5a19df7a_FUN_003C0100(char *p);
extern void LVL_7_SIBERIUS_F5a19df7a_FUN_003C04D8(char *p);
extern char *LVL_7_SIBERIUS_F5a19df7a_FUN_00310AD8(int a, int b);
extern float LVL_7_SIBERIUS_F5a19df7a_FUN_00310BF8(void);
extern void LVL_7_SIBERIUS_F5a19df7a_FUN_003C0D00(char *a, int b, float e, char *c, float f, int d, int g);

void LVL_7_SIBERIUS_FUN_003C0B60(char *p)
{
    char *q;
    char *o;
    char *r;
    float v;
    float w;

    q = p + 16;
    o = *(char **)(p + 104);
    LVL_7_SIBERIUS_F5a19df7a_FUN_003715E0(0x47, 0x53001UL);
    LVL_7_SIBERIUS_F5a19df7a_FUN_003C0100(p);
    LVL_7_SIBERIUS_F5a19df7a_FUN_003C04D8(p);

    v = *(float *)(o + 24);
    v = v * 0.5f;
    r = LVL_7_SIBERIUS_F5a19df7a_FUN_00310AD8(80, 96);
    w = LVL_7_SIBERIUS_F5a19df7a_FUN_00310BF8();
    LVL_7_SIBERIUS_F5a19df7a_FUN_003C0D00(q, 0x103080, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 3.00000011920928955078125e-01f;
    r = LVL_7_SIBERIUS_F5a19df7a_FUN_00310AD8(80, 96);
    w = LVL_7_SIBERIUS_F5a19df7a_FUN_00310BF8();
    LVL_7_SIBERIUS_F5a19df7a_FUN_003C0D00(q, 0xFFFFFF, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 6.99999988079071044921875e-01f;
    r = LVL_7_SIBERIUS_F5a19df7a_FUN_00310AD8(8, 22);
    w = LVL_7_SIBERIUS_F5a19df7a_FUN_00310BF8();
    LVL_7_SIBERIUS_F5a19df7a_FUN_003C0D00(q, 0x803010, v, r, w, 11, 2);

    v = *(float *)(o + 24);
    v = v * 4.49999988079071044921875e-01f;
    r = LVL_7_SIBERIUS_F5a19df7a_FUN_00310AD8(32, 64);
    w = LVL_7_SIBERIUS_F5a19df7a_FUN_00310BF8();
    LVL_7_SIBERIUS_F5a19df7a_FUN_003C0D00(q, 0x803010, v, r, w, 11, 2);

    LVL_7_SIBERIUS_F5a19df7a_FUN_003715E0(0x47, 0x5360bUL);
}
extern float LVL_7_SIBERIUS_Fb1c9893c_FUN_00310BF8(void);
extern float LVL_7_SIBERIUS_Fb1c9893c_FUN_00310B30(float, float);
extern float LVL_7_SIBERIUS_Fb1c9893c_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_Fb1c9893c_FUN_002E4918(float);
extern void LVL_7_SIBERIUS_Fb1c9893c_FUN_002E47D0(float *dst, float *src, char *table);
extern void LVL_7_SIBERIUS_Fb1c9893c_FUN_002E4310(float *dst, float *src, int arg);
extern int LVL_7_SIBERIUS_Fb1c9893c_D_001A8FF0 __attribute__((sda));
extern void LVL_7_SIBERIUS_Fb1c9893c_FUN_002D1A48(char *self, int a1, int a2, int a3, char *p4, char *p5,
                    float *buf, int b3, float fa, float fb);

void LVL_7_SIBERIUS_FUN_0031CC18(char *self, int mask, int arg2,
                                        unsigned char arg3,
                                        float f0, float f1, float f2, float f3)
{
    float buf[3];
    float v;
    float k;
    float fa;
    float fb;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        v = LVL_7_SIBERIUS_Fb1c9893c_FUN_00310BF8();
        k = LVL_7_SIBERIUS_Fb1c9893c_FUN_00310B30(f0, f1) * (1.0f / 60.0f);
        buf[0] = LVL_7_SIBERIUS_Fb1c9893c_FUN_002E4900(v) * k;
        buf[1] = LVL_7_SIBERIUS_Fb1c9893c_FUN_002E4918(v) * k;
        buf[2] = 0.0f;
        buf[2] = LVL_7_SIBERIUS_Fb1c9893c_FUN_00310B30(f2, f3) * (1.0f / 60.0f);
        if (LVL_7_SIBERIUS_Fb1c9893c_D_001A8FF0 != 0)
            LVL_7_SIBERIUS_Fb1c9893c_FUN_002E47D0(buf, buf, self + 192);
        LVL_7_SIBERIUS_Fb1c9893c_FUN_002E4310(buf, buf, arg2);
        fa = LVL_7_SIBERIUS_Fb1c9893c_FUN_00310B30(90.0f, 270.0f);
        fb = LVL_7_SIBERIUS_Fb1c9893c_FUN_00310B30(10.0f, 20.0f);
        LVL_7_SIBERIUS_Fb1c9893c_FUN_002D1A48(self, 2, *(short *)(self + 170), i, self + 16, self + 240,
                buf, arg3, fa, fb);
    }
}
extern int LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E3FB0(char *p);
extern void LVL_7_SIBERIUS_Fdd54ca5d_FUN_003263C0(char *self);
extern float LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E5460(int v);
extern float LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E5460(int v);
extern int LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E5470(float f);
extern void LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E4310(char *dst, char *src, char *vec);
extern void LVL_7_SIBERIUS_Fdd54ca5d_FUN_00375A78(char *dst, char *src);
extern void LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E4398(char *dst, char *table, float scale);
extern void LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E4310(char *dst, char *src, char *vec);
extern void LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E4398(char *dst, char *table, float scale);
extern char LVL_7_SIBERIUS_Fdd54ca5d_D_0018A0E0[];

void LVL_7_SIBERIUS_FUN_0032EE48(char *self)
{
    float vec[4];
    float tmp[4];
    char *s1;
    char *p;
    float f20;
    float t;
    unsigned int v;

    if (LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E3FB0(self + 10)) {
        LVL_7_SIBERIUS_Fdd54ca5d_FUN_003263C0(self);
        return;
    }
    s1 = self + 32;
    f20 = LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E5460(*(short *)(s1 + 30));
    t = LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E5460(*(short *)(s1 + 28));
    v = LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E5470(f20 * ((float)*(short *)(self + 10) / t));
    v = v << 24;
    v = v | (*(unsigned char *)(s1 + 19) << 16);
    v = v | (*(unsigned char *)(s1 + 18) << 8);
    v = v | *(unsigned char *)(s1 + 17);
    *(unsigned int *)(self + 4) = v;
    vec[3] = 0.0f;
    vec[0] = *(float *)(self + 32);
    vec[1] = *(float *)(s1 + 4);
    vec[2] = *(float *)(s1 + 8);
    LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E4310((char *)self + 16, (char *)self + 16, (char *)vec);
    if (*(float *)(self + 28) != 0.0f) {
        if (*(float *)(self + 28) == 2.0f)
            LVL_7_SIBERIUS_Fdd54ca5d_FUN_00375A78((char *)self + 16, (char *)self + 16);
        *(float *)(self + 28) = 2.0f;
    }
    p = (char *)tmp;
    LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E4398(p, LVL_7_SIBERIUS_Fdd54ca5d_D_0018A0E0, *(float *)(s1 + 12));
    LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E4310((char *)vec, (char *)vec, p);
    LVL_7_SIBERIUS_Fdd54ca5d_FUN_002E4398((char *)vec, (char *)vec, *(float *)(s1 + 24));
    *(float *)s1 = vec[0];
    *(float *)(s1 + 4) = vec[1];
    *(float *)(s1 + 8) = vec[2];
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(s1 + 16);
    *(float *)(self + 12) = *(float *)(self + 12) + *(float *)(s1 + 20);
}
extern float LVL_7_SIBERIUS_Fb5729173_FUN_002E44D0(char *a, char *b);
extern float LVL_7_SIBERIUS_Fb5729173_FUN_002E49C8(float x, float y);
extern float LVL_7_SIBERIUS_Fb5729173_FUN_002E5400(float x, float y);
extern float LVL_7_SIBERIUS_Fb5729173_FUN_002E4508(char *a, char *b);
extern int LVL_7_SIBERIUS_Fb5729173_FUN_003157A8(char *a);

float LVL_7_SIBERIUS_FUN_0031A300(char *a0, char *a1, int *a2,
                                       float p1, float p2, float p3, float p4)
{
    float best = p4;
    float hi = p3;
    float radius;
    float reach = p2;
    float far;
    float near;
    float tmp;

    *a2 = 0;
    far = LVL_7_SIBERIUS_Fb5729173_FUN_002E44D0(a0, a1 + 16);
    if (reach < far) {
        *a2 = 1;
    }

    reach = 0.0f;
    radius = LVL_7_SIBERIUS_Fb5729173_FUN_002E5400(LVL_7_SIBERIUS_Fb5729173_FUN_002E49C8(((float *)(a1 + 16))[0] - ((float *)a0)[0],
                             ((float *)(a1 + 16))[1] - ((float *)a0)[1]), p1);
    near = LVL_7_SIBERIUS_Fb5729173_FUN_002E4508(a0, a1 + 16);
    tmp = LVL_7_SIBERIUS_Fb5729173_FUN_002E5400(LVL_7_SIBERIUS_Fb5729173_FUN_002E49C8(near, ((float *)(a1 + 16))[2] - ((float *)a0)[2]), 0.0f);

    if (reach < hi) {
        if (hi < radius) {
            *a2 = 1;
        }
    }
    if (0.0f < best) {
        if (best < tmp) {
            *a2 = 1;
        }
    }

    reach = far + radius * far;
    if (LVL_7_SIBERIUS_Fb5729173_FUN_003157A8(a1) != 0) {
        reach = reach + 8.0f;
    }
    return reach;
}
struct family_27f9_object {
    unsigned char reserved[248];
    float heading;
};

extern float LVL_7_SIBERIUS_F27f9be8e_FUN_002E5360(float p, float x);
extern float LVL_7_SIBERIUS_F27f9be8e_FUN_002E4280(float t);
extern float LVL_7_SIBERIUS_F27f9be8e_FUN_002E4280(float t);
extern float LVL_7_SIBERIUS_F27f9be8e_FUN_002E4280(float t);
extern float LVL_7_SIBERIUS_F27f9be8e_FUN_002E4280(float t);
extern float LVL_7_SIBERIUS_F27f9be8e_FUN_002E5318(float x, float y);

float LVL_7_SIBERIUS_FUN_00311238(struct family_27f9_object *a0,
                                         float *a1,
                                         float p1, float p2, float p3, float p4)
{
    float t;
    float v;
    float f3;
    float out;

    t = LVL_7_SIBERIUS_F27f9be8e_FUN_002E5360(p1, a0->heading);
    v = t * 6.3661971092224121093750e+00f;
    if (v > 1.0f) {
        v = 1.0f;
    } else {
        if (v < -1.0f) {
            v = -1.0f;
        }
    }
    f3 = a1[0];
    a1[0] = f3 + (p2 * v - p3 * f3);
    if (p4 != 0.0f) {
        if (a1[0] > p4) {
            a1[0] = p4;
        } else {
            if (a1[0] < -p4) {
                a1[0] = -p4;
            }
        }
    }
    if (LVL_7_SIBERIUS_F27f9be8e_FUN_002E4280(t) < a1[0]) {
        a1[0] = LVL_7_SIBERIUS_F27f9be8e_FUN_002E4280(t);
    } else {
        if (a1[0] < -LVL_7_SIBERIUS_F27f9be8e_FUN_002E4280(t)) {
            a1[0] = -LVL_7_SIBERIUS_F27f9be8e_FUN_002E4280(t);
        }
    }
    out = LVL_7_SIBERIUS_F27f9be8e_FUN_002E5318(a0->heading, a1[0]);
    a0->heading = out;
    return out;
}

#ifndef RAC2_T_S16_FC94396F4
#define RAC2_T_S16_FC94396F4
typedef signed short s16_Fc94396f4;
#endif




#ifndef RAC2_T_FAMILYC94396F4VECTOR_FC94396F4
#define RAC2_T_FAMILYC94396F4VECTOR_FC94396F4
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} FamilyC94396F4Vector_Fc94396f4;
#endif


#ifndef RAC2_T_FAMILYC94396F4STATE_FC94396F4
#define RAC2_T_FAMILYC94396F4STATE_FC94396F4
typedef struct {
    u8 reserved0[846];
    s16_Fc94396f4 gate;
    u8 reserved1[8004];
    s32 state;
    u8 reserved2[43];
    u8 mode;
} FamilyC94396F4State_Fc94396f4;
#endif


extern FamilyC94396F4State_Fc94396f4 LVL_7_SIBERIUS_Fc94396f4_D_00189E20;
extern u8 LVL_7_SIBERIUS_Fc94396f4_D_0018A0E0[];

extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002E45F0(u8 *buffer, u8 *table, f32 parameter);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002C9B88(u8 *buffer, FamilyC94396F4Vector_Fc94396f4 *source, f32 zero);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002C9B08(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, f32 zero);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002E4310(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, u8 *buffer);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002E4310(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, u8 *buffer);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002E45F0(u8 *buffer, u8 *table, f32 parameter);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002E45F0(u8 *buffer, u8 *table, f32 parameter);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002C9B88(u8 *buffer, FamilyC94396F4Vector_Fc94396f4 *source, f32 zero);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002C9B08(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, f32 zero);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002E4310(FamilyC94396F4Vector_Fc94396f4 *destination,
                    FamilyC94396F4Vector_Fc94396f4 *source, u8 *buffer);
extern void LVL_7_SIBERIUS_Fc94396f4_FUN_002E4310(FamilyC94396F4Vector_Fc94396f4 *destination,
                     FamilyC94396F4Vector_Fc94396f4 *source, u8 *buffer);

void LVL_7_SIBERIUS_FUN_002C9470(FamilyC94396F4Vector_Fc94396f4 *destination,
                                      FamilyC94396F4Vector_Fc94396f4 *source,
                                      f32 parameter)
{
    u8 first[16];
    u8 second[16];

    switch (LVL_7_SIBERIUS_Fc94396f4_D_00189E20.mode) {
    case 0:
        destination->z = source->z - parameter;
        return;
    case 1:
        LVL_7_SIBERIUS_Fc94396f4_FUN_002E45F0(first, (u8 *)&LVL_7_SIBERIUS_Fc94396f4_D_00189E20 + 672, -parameter);
        LVL_7_SIBERIUS_Fc94396f4_FUN_002C9B88(second, source, 0.0f);
        LVL_7_SIBERIUS_Fc94396f4_FUN_002C9B08(destination, destination, 0.0f);
        LVL_7_SIBERIUS_Fc94396f4_FUN_002E4310(destination, destination, second);
        LVL_7_SIBERIUS_Fc94396f4_FUN_002E4310(destination, destination, first);
        return;
    case 2:
        if (LVL_7_SIBERIUS_Fc94396f4_D_00189E20.state == 58 && LVL_7_SIBERIUS_Fc94396f4_D_00189E20.gate == 0) {
            LVL_7_SIBERIUS_Fc94396f4_FUN_002E45F0(first, (u8 *)&LVL_7_SIBERIUS_Fc94396f4_D_00189E20 + 672, -parameter);
        } else {
            LVL_7_SIBERIUS_Fc94396f4_FUN_002E45F0(first, LVL_7_SIBERIUS_Fc94396f4_D_0018A0E0, parameter);
        }
        LVL_7_SIBERIUS_Fc94396f4_FUN_002C9B88(second, source, 0.0f);
        LVL_7_SIBERIUS_Fc94396f4_FUN_002C9B08(destination, destination, 0.0f);
        LVL_7_SIBERIUS_Fc94396f4_FUN_002E4310(destination, destination, second);
        LVL_7_SIBERIUS_Fc94396f4_FUN_002E4310(destination, destination, first);
        return;
    default:
        return;
    }
}
extern int LVL_7_SIBERIUS_F3c007b59_FUN_002E3FB0(void *p);
extern void LVL_7_SIBERIUS_F3c007b59_FUN_003263C0(void *p);
extern unsigned int LVL_7_SIBERIUS_F3c007b59_FUN_002E5470(float x);

#ifndef RAC2_T_OBJ_F3C007B59
#define RAC2_T_OBJ_F3C007B59
typedef struct {
    unsigned char pad0[4];
    unsigned int w04;
    unsigned char c08;
    unsigned char c09;
    unsigned char c10;
    unsigned char c11;
    float f12;
    unsigned char pad16[8];
    float f24;
    unsigned char pad28[4];
    float f36;
    float f40;
    float f44;
} OBJ_F3c007b59;
#endif


void LVL_7_SIBERIUS_FUN_0032A5D8(OBJ_F3c007b59 *o)
{
    float *p = (float *)((char *)o + 32);
    float f;
    float y;

    f = p[1] + p[3] * 1.3000000268220901489258e-02f;
    p[1] = f;
    if (f <= 0.0f || LVL_7_SIBERIUS_F3c007b59_FUN_002E3FB0(&o->c10) != 0) {
        LVL_7_SIBERIUS_F3c007b59_FUN_003263C0(o);
    } else {
        f = p[1];
        if (2.1999999880790710449219e-01f <= f) {
            y = p[3];
            y = -y;
            p[3] = y;
            p[1] = f + y * 1.3000000268220901489258e-02f;
        }
        o->f12 = o->f12 + 8.1900000000000000000000e+03f;
        o->w04 = (o->w04 & 0xFFFFFFu) |
                 (LVL_7_SIBERIUS_F3c007b59_FUN_002E5470(p[1] * 2.5500000000000000000000e+02f) << 24);
        p[2] = p[2] + 1.2000000104308128356934e-02f;
        if (p[2] > 1.0f)
            p[2] = p[2] - 1.0f;
        o->c08 = (unsigned char)(p[2] * 2.5500000000000000000000e+02f);
        o->f24 = o->f24 - 1.9999999552965164184570e-02f;
    }
}
extern void LVL_7_SIBERIUS_F043c77a5_FUN_00417778(void *dst);
extern long long LVL_7_SIBERIUS_F043c77a5_FUN_002DC778(int id);
extern float LVL_7_SIBERIUS_F043c77a5_FUN_002E49C8(float x, float y);
extern float LVL_7_SIBERIUS_F043c77a5_FUN_002E4488(void *vec);
extern void LVL_7_SIBERIUS_F043c77a5_FUN_002E4B90(void *dst, void *src);
extern void LVL_7_SIBERIUS_F043c77a5_FUN_002E4398(void *dst, void *src, float scale);
extern void LVL_7_SIBERIUS_F043c77a5_FUN_002E0C08(void *dst, void *src, int flag);

#ifndef RAC2_T_BLOCK_F043C77A5
#define RAC2_T_BLOCK_F043C77A5
typedef struct { int q[4]; } BLOCK_F043c77a5;
#endif


#ifndef RAC2_T_LOC_F043C77A5
#define RAC2_T_LOC_F043C77A5
typedef struct {
    BLOCK_F043c77a5 b0;
    BLOCK_F043c77a5 b1;
    BLOCK_F043c77a5 b2;
    BLOCK_F043c77a5 b3;
    int   k0, k1, k2, k3;
    int   z80, z84, z88;
    float f92, f96;
    int   z100;
    float f104, f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float v192, v196, v200, v204;
    float v208, f212, f216, v220;
} LOC_F043c77a5;
#endif


void LVL_7_SIBERIUS_FUN_004189E0(void *unused, float *b, float *a, int k, float f)
{
    LOC_F043c77a5 local;
    float x;

    LVL_7_SIBERIUS_F043c77a5_FUN_00417778(&local);
    local.z80 = 0;
    local.f92 = 1.0f;
    local.f96 = 1.0f;
    local.f104 = 1.0f;
    local.f108 = 1.0f;
    local.z84 = 0;
    local.z88 = 0;
    local.z100 = 0;
    local.v120 = LVL_7_SIBERIUS_F043c77a5_FUN_002DC778(11);
    local.v128 = 0xFF9000000260LL;
    local.v136 = 0x0000008000000048LL;
    local.k3 = k;
    local.k2 = k;
    local.k1 = k;
    local.k0 = k;
    local.v112 = 0;
    local.v220 = 0.0f;
    local.f216 = LVL_7_SIBERIUS_F043c77a5_FUN_002E49C8(a[0], a[1]);
    x = LVL_7_SIBERIUS_F043c77a5_FUN_002E49C8(LVL_7_SIBERIUS_F043c77a5_FUN_002E4488(a), a[2]);
    local.f212 = -x;
    local.v208 = 0.0f;
    LVL_7_SIBERIUS_F043c77a5_FUN_002E4B90(&local.m00, &local.v208);
    local.v192 = b[0];
    local.v196 = b[1];
    local.v200 = b[2];
    local.v204 = 1.0f;
    LVL_7_SIBERIUS_F043c77a5_FUN_002E4398(&local.b0, &local.b0, f);
    LVL_7_SIBERIUS_F043c77a5_FUN_002E4398(&local.b1, &local.b1, f);
    LVL_7_SIBERIUS_F043c77a5_FUN_002E4398(&local.b2, &local.b2, f);
    LVL_7_SIBERIUS_F043c77a5_FUN_002E4398(&local.b3, &local.b3, f);
    LVL_7_SIBERIUS_F043c77a5_FUN_002E0C08(&local, &local.m00, 0);
}
extern int LVL_7_SIBERIUS_F7cacd225_FUN_002E3FB0(short *p);
extern void LVL_7_SIBERIUS_F7cacd225_FUN_003263C0(char *o);
extern float LVL_7_SIBERIUS_F7cacd225_FUN_002E5460(int n);
extern float LVL_7_SIBERIUS_F7cacd225_FUN_002E5460(int n);
extern int LVL_7_SIBERIUS_F7cacd225_FUN_002E54B8(int a, int b, float q);

#ifndef RAC2_T_OBJ_F7CACD225
#define RAC2_T_OBJ_F7CACD225
typedef struct {
    int pad0;
    int f4;
    short pad8;
    short s10;
    float f12;
    float f16;
    float f20;
    float f24;
    int pad28;
    int f32;
} Obj_F7cacd225;
#endif


void LVL_7_SIBERIUS_FUN_00333168(Obj_F7cacd225 *o)
{
    int v;

    if (o->f16 < 2.0f || o->f16 > 1021.0f ||
        o->f20 < 2.0f || o->f20 > 1021.0f ||
        o->f24 < 2.0f || o->f24 > 1021.0f ||
        LVL_7_SIBERIUS_F7cacd225_FUN_002E3FB0(&o->s10) != 0) {
        LVL_7_SIBERIUS_F7cacd225_FUN_003263C0((char *)o);
        return;
    }
    v = o->f32;
    if (v != 0) {
        o->f12 = o->f12 * 0.99f;
        o->f4 = LVL_7_SIBERIUS_F7cacd225_FUN_002E54B8(0x30FFFFFF, o->f4, LVL_7_SIBERIUS_F7cacd225_FUN_002E5460(o->s10 - 1) / LVL_7_SIBERIUS_F7cacd225_FUN_002E5460(o->s10));
    } else {
        o->f12 = o->f12 * 0.95f;
        o->f4 = LVL_7_SIBERIUS_F7cacd225_FUN_002E54B8(0x603F1008, o->f4, LVL_7_SIBERIUS_F7cacd225_FUN_002E5460(o->s10 - 1) / LVL_7_SIBERIUS_F7cacd225_FUN_002E5460(o->s10));
    }
}
extern float LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(float a);
extern float LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(float a);
extern float LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(float a);
extern float LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(float a);
extern float LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(float a);
extern float LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(float a);
extern float LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(float a);
extern float LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(float a);

#ifndef RAC2_T_OBJ_FF454DD77
#define RAC2_T_OBJ_FF454DD77
typedef struct {
    float f0;
} Obj_Ff454dd77;
#endif


void LVL_7_SIBERIUS_FUN_00313C88(Obj_Ff454dd77 *o, float a, float b, float c, float d)
{
    if (LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(a) < o->f0)
        o->f0 = LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(a);
    else if (o->f0 < -LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(a))
        o->f0 = -LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(a);

    o->f0 = o->f0 + (b * a - c * o->f0);
    if (0.0f < d) {
        if (d < o->f0)
            o->f0 = d;
        else if (o->f0 < -d)
            o->f0 = -d;
    }

    if (LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(a) < o->f0)
        o->f0 = LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(a);
    else if (o->f0 < -LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(a))
        o->f0 = -LVL_7_SIBERIUS_Ff454dd77_FUN_002E4280(a);
}
#ifndef RAC2_T_V4_F5621621C
#define RAC2_T_V4_F5621621C
typedef int V4_F5621621c __attribute__((mode(TI)));
#endif


extern float LVL_7_SIBERIUS_F5621621c_FUN_002E49C8(float a, float b);
extern float LVL_7_SIBERIUS_F5621621c_FUN_002E4900(float a);
extern float LVL_7_SIBERIUS_F5621621c_FUN_002E4918(float a);
extern void LVL_7_SIBERIUS_F5621621c_FUN_00312638(int v, void *rec);

#ifndef RAC2_T_VEC16_F5621621C
#define RAC2_T_VEC16_F5621621C
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_F5621621c;
#endif


#ifndef RAC2_T_NODE_F5621621C
#define RAC2_T_NODE_F5621621C
typedef struct {
    char pad[16];
    float f16;
    float f20;
} Node_F5621621c;
#endif


#ifndef RAC2_T_REC_F5621621C
#define RAC2_T_REC_F5621621C
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    int i16;
    int i20;
    signed char b24;
    signed char b25;
    unsigned short h26;
    float f28;
    int i32;
} Rec_F5621621c;
#endif


void LVL_7_SIBERIUS_FUN_003131B8(void *a0, Vec16_F5621621c *src, int *p, int n,
                                        int t0, int t1, int t2, int t3,
                                        float f1, float f2, float f3)
{
    Vec16_F5621621c vec;
    Vec16_F5621621c *vp = &vec;
    Rec_F5621621c rec;
    int i;
    int *q;

    *(V4_F5621621c *)&vec = *(V4_F5621621c *)src;
    if (n <= 0) return;
    for (q = p, i = n; i != 0; i--, q++) {
        Node_F5621621c *v = (Node_F5621621c *)*q;
        float t;
        if ((int)*q == t0) continue;
        rec.i16 = (int)a0;
        rec.h26 = *(unsigned short *)((char *)a0 + 170);
        rec.i20 = t1;
        rec.f28 = f1;
        rec.i32 = t1;
        rec.b24 = t2;
        rec.b25 = t3;
        t = LVL_7_SIBERIUS_F5621621c_FUN_002E49C8(v->f16 - vp->x, v->f20 - vp->y);
        rec.f0 = LVL_7_SIBERIUS_F5621621c_FUN_002E4900(t) * f2;
        rec.f4 = LVL_7_SIBERIUS_F5621621c_FUN_002E4918(t) * f2;
        rec.f8 = f3;
        rec.f12 = 5.6279248046875000000000e3f;
        LVL_7_SIBERIUS_F5621621c_FUN_00312638(*q, &rec);
    }
}
extern void LVL_7_SIBERIUS_F966dbf73_FUN_00310A98(int a);
extern void LVL_7_SIBERIUS_F966dbf73_FUN_00310A98(int a);
extern float LVL_7_SIBERIUS_F966dbf73_FUN_00310B30(float a, float b);
extern unsigned int LVL_7_SIBERIUS_F966dbf73_FUN_00310AD8(int a, int b);
extern void LVL_7_SIBERIUS_F966dbf73_FUN_00310D80(char *p, float a, float b);
extern char *LVL_7_SIBERIUS_F966dbf73_FUN_0032B038(float fa, float fb, float fc, float fd, char *p, int z,
                     char *local, unsigned int v, int one);

void LVL_7_SIBERIUS_FUN_003B8268(char *unused, char *arg)
{
    char local[16];
    float f;
    int i;
    unsigned int v;
    unsigned int w;
    unsigned int x;
    char *r;

    i = 19;
    do {
        LVL_7_SIBERIUS_F966dbf73_FUN_00310A98(2);
        i = i - 1;
        LVL_7_SIBERIUS_F966dbf73_FUN_00310A98(2);
        f = LVL_7_SIBERIUS_F966dbf73_FUN_00310B30(70000.0f, 150000.0f);
        v = LVL_7_SIBERIUS_F966dbf73_FUN_00310AD8(10, 127);
        w = (v << 8) | 0x7f000000U;
        x = (v << 16) | w;
        v = x | v;
        LVL_7_SIBERIUS_F966dbf73_FUN_00310D80(local, 1.6666668670950457453728e-05f,
                6.6666672937572002410889e-03f);
        r = LVL_7_SIBERIUS_F966dbf73_FUN_0032B038(0.3f, 1.0f, 1.01f, f, arg, 0, local, v, 1);
        if (r != 0) {
            char *q = r + 32;

            *(short *)(r + 10) = 120;
            *(int *)(q + 4) = 2;
            *(char *)(q + 10) = 127;
            *(char *)(q + 11) = *(unsigned char *)(r + 10);
        }
    } while (i >= 0);
}
extern char LVL_7_SIBERIUS_F024e7577_D_00189E20[];
extern float LVL_7_SIBERIUS_F024e7577_FUN_00313DD8(float *p, float a, float b);

void LVL_7_SIBERIUS_FUN_002A9BB0(float *a0, float *a1, float f12)
{
    char *base = LVL_7_SIBERIUS_F024e7577_D_00189E20;
    float v[2];

    v[0] = -*(float *)(base + 8112);
    v[1] = *(float *)(base + 8116);
    LVL_7_SIBERIUS_F024e7577_FUN_00313DD8(a1 + 2, v[0], f12);
    if (a1[2] > 1.0f) a1[2] = 1.0f;
    if (a1[2] < -1.0f) a1[2] = -1.0f;
    a0[0] = a1[2];
    LVL_7_SIBERIUS_F024e7577_FUN_00313DD8(a1 + 1, v[1], f12);
    if (a1[1] > 1.0f) a1[1] = 1.0f;
    if (a1[1] < -1.0f) a1[1] = -1.0f;
    a0[1] = a1[1];
}
extern float LVL_7_SIBERIUS_F229bff2f_FUN_002E4280(float t);

float LVL_7_SIBERIUS_FUN_002CDAE8(float *p, float a, float b, float c, float d, float lim)
{
    float t = b - a;
    float x = *p;
    float r;

    x += c * t - d * x;
    *p = x;
    if (lim != 0.0f) {
        if (x > lim) *p = lim;
        else if (x < -lim) *p = -lim;
    }
    r = LVL_7_SIBERIUS_F229bff2f_FUN_002E4280(t);
    if (r < *p) {
        *p = LVL_7_SIBERIUS_F229bff2f_FUN_002E4280(t);
    } else {
        float s = -LVL_7_SIBERIUS_F229bff2f_FUN_002E4280(t);
        if (*p < s) {
            *p = -LVL_7_SIBERIUS_F229bff2f_FUN_002E4280(t);
        }
    }
    return a + *p;
}
#ifndef RAC2_T_S_F49AFCBFE
#define RAC2_T_S_F49AFCBFE
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    float f16;
    int i20;
    float f24;
    int i28;
    int i32;
    int i36;
    int i40;
} S_F49afcbfe;
#endif


extern void LVL_7_SIBERIUS_F49afcbfe_FUN_0043AF38(S_F49afcbfe *x, int a, int b, float p, float q, float r, float s);

void LVL_7_SIBERIUS_FUN_0043AE38(S_F49afcbfe *x)
{
    float z;

    x->f0 = 1.0f;
    x->f4 = 1.0f;
    x->f8 = 1.0f;
    x->f12 = 1.0f;
    x->f16 = 0.0f;
    x->f24 = 6.6665999591350555419922e-02f;
    x->i28 = 0;
    x->i32 = 0;
    x->i36 = 0;
    x->i40 = 0;
    z = x->f16;
    LVL_7_SIBERIUS_F49afcbfe_FUN_0043AF38(x, 0, 0, z, z, z, z);
    LVL_7_SIBERIUS_F49afcbfe_FUN_0043AF38(x, 0, 1, z, z, z, z);
    LVL_7_SIBERIUS_F49afcbfe_FUN_0043AF38(x, 1, 0, z, z, z, z);
    LVL_7_SIBERIUS_F49afcbfe_FUN_0043AF38(x, 1, 1, z, z, z, z);
}
extern void LVL_7_SIBERIUS_Fa6f6f46f_FUN_002E4DD8(char *a, char *b);
extern void LVL_7_SIBERIUS_Fa6f6f46f_FUN_0030C708(char *a, int b, int c, char *d);
extern void LVL_7_SIBERIUS_Fa6f6f46f_FUN_002E4F08(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_Fa6f6f46f_FUN_002E4398(char *a, char *b, float c);
extern void LVL_7_SIBERIUS_Fa6f6f46f_FUN_002E4310(char *a, char *b, char *c);

void LVL_7_SIBERIUS_FUN_00307A68(char *a0, int n, int a2, char *a3)
{
    char buf[64];
    float f20;
    int i;

    f20 = *(float *)(a0 + 44) * 0.0009765625f;
    LVL_7_SIBERIUS_Fa6f6f46f_FUN_002E4DD8(buf, a0 + 192);
    LVL_7_SIBERIUS_Fa6f6f46f_FUN_0030C708(a0, n, a2, a3);
    for (i = 0; i < n; i++) {
        LVL_7_SIBERIUS_Fa6f6f46f_FUN_002E4F08(a3 + i * 64, buf, a3 + i * 64);
        LVL_7_SIBERIUS_Fa6f6f46f_FUN_002E4398(a3 + i * 64 + 48, a3 + i * 64 + 48, f20);
        LVL_7_SIBERIUS_Fa6f6f46f_FUN_002E4310(a3 + i * 64 + 48, a3 + i * 64 + 48, a0 + 16);
    }
}
extern int LVL_7_SIBERIUS_F33c6e7a2_D_001A8FF0 __attribute__((sda));
extern int LVL_7_SIBERIUS_F33c6e7a2_D_001A8FF4 __attribute__((sda));
extern char LVL_7_SIBERIUS_F33c6e7a2_D_00189E20[];
extern void LVL_7_SIBERIUS_F33c6e7a2_FUN_002E42E8(char *a);
extern void LVL_7_SIBERIUS_F33c6e7a2_FUN_0031B218(char *a, char *b, int c);
extern void LVL_7_SIBERIUS_F33c6e7a2_FUN_002E4340(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F33c6e7a2_FUN_002E45F0(char *a, char *b, float f12);
extern void LVL_7_SIBERIUS_F33c6e7a2_FUN_002E4398(char *a, char *b, float f12);

void LVL_7_SIBERIUS_FUN_0031B290(char *a0, char *a1, int a2)
{
    char *p;
    float f20;

    if (LVL_7_SIBERIUS_F33c6e7a2_D_001A8FF0 == 0) {
        LVL_7_SIBERIUS_F33c6e7a2_FUN_002E42E8(a1);
    } else if (LVL_7_SIBERIUS_F33c6e7a2_D_001A8FF4 != 0) {
        LVL_7_SIBERIUS_F33c6e7a2_FUN_0031B218(a0, a1, 1);
    } else {
        p = LVL_7_SIBERIUS_F33c6e7a2_D_00189E20;
        f20 = 1.0f;
        if (0.0f < *(float *)(p + 188))
            f20 = -1.0f;
        LVL_7_SIBERIUS_F33c6e7a2_FUN_002E4340(a1, p + 176, a0);
        LVL_7_SIBERIUS_F33c6e7a2_FUN_002E45F0(a1, a1, f20);
    }
    if (a2 == 0)
        LVL_7_SIBERIUS_F33c6e7a2_FUN_002E4398(a1, a1, -1.0f);
}
extern int LVL_7_SIBERIUS_F5ac03a17_FUN_002E3FB0(char *p);
extern void LVL_7_SIBERIUS_F5ac03a17_FUN_003263C0(char *p);
extern int LVL_7_SIBERIUS_F5ac03a17_FUN_002E5470(float f);
extern int LVL_7_SIBERIUS_F5ac03a17_FUN_002E5470(float f);
extern void LVL_7_SIBERIUS_F5ac03a17_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F5ac03a17_FUN_002E4398(char *a, char *b, float f);

void LVL_7_SIBERIUS_FUN_00328DB0(char *p)
{
    char *q = p + 32;
    float v;
    int a, b;
    int h;

    v = *(float *)(q + 28) + (-0.04f);
    *(float *)(q + 28) = v;
    if (v <= 0.0f || LVL_7_SIBERIUS_F5ac03a17_FUN_002E3FB0(p + 10) != 0) {
        LVL_7_SIBERIUS_F5ac03a17_FUN_003263C0(p);
        return;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 12000.0f;
    if (*(float *)(q + 24) < 0.225f) {
        *(float *)(q + 24) = *(float *)(q + 24) + 0.0484f;
    }
    a = LVL_7_SIBERIUS_F5ac03a17_FUN_002E5470(*(float *)(q + 24) * 255.0f) & 0xff;
    b = LVL_7_SIBERIUS_F5ac03a17_FUN_002E5470(*(float *)(q + 28) * 255.0f);
    h = *(unsigned short *)(p + 4);
    *(int *)(p + 4) = h | (a << 16) | (b << 24);
    LVL_7_SIBERIUS_F5ac03a17_FUN_002E4310(p + 16, p + 16, q);
    LVL_7_SIBERIUS_F5ac03a17_FUN_002E4398(q, q, 0.9f);
    *(char *)(p + 8) = *(unsigned char *)(p + 8) - 1;
}
extern void LVL_7_SIBERIUS_F1fd779a1_FUN_0030C708(char *p, int one, int *w, char *out);
extern void LVL_7_SIBERIUS_F1fd779a1_FUN_002E4398(char *a, char *out, float f);
extern void LVL_7_SIBERIUS_F1fd779a1_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F1fd779a1_FUN_002E47D0(char *a, char *b, char *c);

void LVL_7_SIBERIUS_FUN_0039A0C8(char *p, int v, char *a, char *b)
{
    char out0[48];
    char out48[16];
    int w;
    float f;

    f = *(float *)(p + 44) * 0.0009765625f;
    w = v;
    LVL_7_SIBERIUS_F1fd779a1_FUN_0030C708(p, 1, &w, out0);
    LVL_7_SIBERIUS_F1fd779a1_FUN_002E4398(a, out48, f);
    LVL_7_SIBERIUS_F1fd779a1_FUN_002E4310(a, a, b);
    LVL_7_SIBERIUS_F1fd779a1_FUN_002E47D0(a, a, p + 192);
    LVL_7_SIBERIUS_F1fd779a1_FUN_002E4310(a, a, p + 16);
}
extern void LVL_7_SIBERIUS_F1fd779a1_FUN_0030C708(char *p, int one, int *w, char *out);
extern void LVL_7_SIBERIUS_F1fd779a1_FUN_002E4398(char *a, char *out, float f);
extern void LVL_7_SIBERIUS_F1fd779a1_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F1fd779a1_FUN_002E47D0(char *a, char *b, char *c);

void LVL_7_SIBERIUS_FUN_003D4C58(char *p, int v, char *a, char *b)
{
    char out0[48];
    char out48[16];
    int w;
    float f;

    f = *(float *)(p + 44) * 0.0009765625f;
    w = v;
    LVL_7_SIBERIUS_F1fd779a1_FUN_0030C708(p, 1, &w, out0);
    LVL_7_SIBERIUS_F1fd779a1_FUN_002E4398(a, out48, f);
    LVL_7_SIBERIUS_F1fd779a1_FUN_002E4310(a, a, b);
    LVL_7_SIBERIUS_F1fd779a1_FUN_002E47D0(a, a, p + 192);
    LVL_7_SIBERIUS_F1fd779a1_FUN_002E4310(a, a, p + 16);
}
extern float LVL_7_SIBERIUS_F4a600262_FUN_002E5460(int a);
extern int LVL_7_SIBERIUS_F4a600262_FUN_002E5470(float f);
extern int LVL_7_SIBERIUS_F4a600262_FUN_002E54B8(int a, int b, float f);
extern float LVL_7_SIBERIUS_F4a600262_FUN_00310B30(float a, float b);
extern void LVL_7_SIBERIUS_F4a600262_FUN_002E4310(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F4a600262_FUN_002E4398(char *a, char *b, float f);
extern void LVL_7_SIBERIUS_F4a600262_FUN_00375A78(char *a, char *b);
extern void LVL_7_SIBERIUS_F4a600262_FUN_00375B30(char *a, char *b);
extern int LVL_7_SIBERIUS_F4a600262_FUN_002E3FB0(char *p);
extern void LVL_7_SIBERIUS_F4a600262_FUN_003263C0(char *p);

void LVL_7_SIBERIUS_FUN_00337D58(char *p)
{
    char *s0 = p + 32;
    char *s3 = p + 16;
    float r1, r2, r3, r4;
    int x, y;

    r1 = LVL_7_SIBERIUS_F4a600262_FUN_002E5460(*(short *)(p + 10));
    r2 = LVL_7_SIBERIUS_F4a600262_FUN_002E5460(*(int *)(s0 + 24));
    r1 = r1 / r2;
    r3 = LVL_7_SIBERIUS_F4a600262_FUN_002E5460(*(int *)(s0 + 16));
    x = LVL_7_SIBERIUS_F4a600262_FUN_002E5470(r3 * r1);
    y = LVL_7_SIBERIUS_F4a600262_FUN_002E54B8(0, *(int *)(s0 + 20), r1 * 0.5f);
    *(char *)(p + 8) = *(unsigned char *)(p + 8) + 1;
    r4 = LVL_7_SIBERIUS_F4a600262_FUN_00310B30(0.004f, 0.012f);
    *(float *)(p + 12) = *(float *)(p + 12) + r4 * 210000.0f;
    LVL_7_SIBERIUS_F4a600262_FUN_002E4310(s3, s3, s0);
    LVL_7_SIBERIUS_F4a600262_FUN_002E4398(s0, s0, 0.99f);
    LVL_7_SIBERIUS_F4a600262_FUN_00375A78(s3, s3);
    LVL_7_SIBERIUS_F4a600262_FUN_00375B30(s0, s0);
    *(int *)(p + 4) = y | (x << 24);
    if (LVL_7_SIBERIUS_F4a600262_FUN_002E3FB0(p + 10) != 0) {
        LVL_7_SIBERIUS_F4a600262_FUN_003263C0(p);
    }
}
extern void LVL_7_SIBERIUS_F0cbe9be2_FUN_002B26E8(int arg0, float arg1);
extern float LVL_7_SIBERIUS_F0cbe9be2_FUN_002B7B60(char *arg0, int arg1);
extern float LVL_7_SIBERIUS_F0cbe9be2_FUN_002E5360(float arg0, float arg1);
extern float LVL_7_SIBERIUS_F0cbe9be2_FUN_002E5400(float arg0, float arg1);
extern char LVL_7_SIBERIUS_F0cbe9be2_D_00189E20[];

int LVL_7_SIBERIUS_FUN_002BDF08(void)
{
    char *p = LVL_7_SIBERIUS_F0cbe9be2_D_00189E20;
    float value;
    int result;
    int state;

    result = 2;
    if (*(short *)(p + 5204) != 0) {
        state = *(unsigned char *)(p + 5207);
        if (state == 0)
            result = 0;
        else if (state == 3)
            result = 3;
        else if (state == 2)
            result = 2;
        else
            result = 1;
    } else {
        LVL_7_SIBERIUS_F0cbe9be2_FUN_002B26E8(0, 1.0f);
        if (*(unsigned char *)(p + 8899) != 0)
            value = LVL_7_SIBERIUS_F0cbe9be2_FUN_002B7B60(p + 400, 0);
        else
            value = LVL_7_SIBERIUS_F0cbe9be2_FUN_002E5360(*(float *)(p + 416), *(float *)(p + 152));
        if (LVL_7_SIBERIUS_F0cbe9be2_FUN_002E5400(value, 3.1415929794311523437500e+00f) < 7.8539824485778808593750e-01f)
            result = 3;
        else if (LVL_7_SIBERIUS_F0cbe9be2_FUN_002E5400(value, -1.5707964897155761718750e+00f) < 7.8539824485778808593750e-01f)
            result = 1;
        else if (LVL_7_SIBERIUS_F0cbe9be2_FUN_002E5400(value, 1.5707964897155761718750e+00f) < 7.8539824485778808593750e-01f)
            result = 0;
    }
    return result;
}
extern void LVL_7_SIBERIUS_Ffea5082f_FUN_002E4760(void *a, void *b, void *c);
extern float LVL_7_SIBERIUS_Ffea5082f_FUN_002E4458(void *a);
extern float LVL_7_SIBERIUS_Ffea5082f_FUN_002E4418(void *a, void *b);
extern void LVL_7_SIBERIUS_Ffea5082f_FUN_00313DD8(float *p, float a, float b);
extern void LVL_7_SIBERIUS_Ffea5082f_FUN_002E45F0(void *a, void *b, float f);

int LVL_7_SIBERIUS_FUN_002D2EC0(void *p, void *q, void *r, float f12, float f13)
{
    float saved;
    float t;
    float v;

    LVL_7_SIBERIUS_Ffea5082f_FUN_002E4760(p, p, q);
    saved = LVL_7_SIBERIUS_Ffea5082f_FUN_002E4458(p);
    v = LVL_7_SIBERIUS_Ffea5082f_FUN_002E4418(r, q);
    if (v > 0.7f) {
        t = saved * f12;
        if (t < f13) t = f13;
        LVL_7_SIBERIUS_Ffea5082f_FUN_00313DD8(&saved, 0.0f, t);
        LVL_7_SIBERIUS_Ffea5082f_FUN_002E45F0(p, p, saved);
    }
    if (saved != 0.0f) return 1;
    return 0;
}
extern float LVL_7_SIBERIUS_F118c2370_FUN_00310BF8(void);
extern float LVL_7_SIBERIUS_F118c2370_FUN_00310B30(float a, float b);
extern float LVL_7_SIBERIUS_F118c2370_FUN_002E4900(float a);
extern float LVL_7_SIBERIUS_F118c2370_FUN_002E4918(float a);
extern int LVL_7_SIBERIUS_F118c2370_FUN_00310AD8(int a, int b);
extern int LVL_7_SIBERIUS_F118c2370_FUN_00310A98(int a);
extern void LVL_7_SIBERIUS_F118c2370_FUN_0032D140(char *p, float *q, int a, int b);

void LVL_7_SIBERIUS_FUN_003CCA88(char *a0)
{
    float v[3];
    float a;
    float b;
    int i;
    int m;
    int n;

    for (i = 47; i >= 0; i--) {
        a = LVL_7_SIBERIUS_F118c2370_FUN_00310BF8();
        b = LVL_7_SIBERIUS_F118c2370_FUN_00310B30(0.0f, 0.050000004f);
        v[0] = LVL_7_SIBERIUS_F118c2370_FUN_002E4900(a) * b;
        v[1] = LVL_7_SIBERIUS_F118c2370_FUN_002E4918(a) * b;
        v[2] = LVL_7_SIBERIUS_F118c2370_FUN_00310B30(0.050000004f, 1.0833334177732467651367e-01f);
        m = LVL_7_SIBERIUS_F118c2370_FUN_00310AD8(90, 120);
        n = LVL_7_SIBERIUS_F118c2370_FUN_00310A98(2);
        LVL_7_SIBERIUS_F118c2370_FUN_0032D140(a0 + 16, v, n, m);
    }
}
extern float LVL_7_SIBERIUS_F63cf942f_FUN_002E4900(float x);
extern float LVL_7_SIBERIUS_F63cf942f_FUN_002E5360(float a, float b);
extern float LVL_7_SIBERIUS_F63cf942f_FUN_002E5318(float a, float b);

void LVL_7_SIBERIUS_FUN_00311178(float *a0, float *a1, float *a2, float t)
{
    float k;

    k = (1.0f - LVL_7_SIBERIUS_F63cf942f_FUN_002E4900(t * 3.1415927f)) * 0.5f;
    a0[0] = LVL_7_SIBERIUS_F63cf942f_FUN_002E5318(a1[0], LVL_7_SIBERIUS_F63cf942f_FUN_002E5360(a2[0], a1[0]) * k);
    a0[1] = LVL_7_SIBERIUS_F63cf942f_FUN_002E5318(a1[1], LVL_7_SIBERIUS_F63cf942f_FUN_002E5360(a2[1], a1[1]) * k);
    a0[2] = LVL_7_SIBERIUS_F63cf942f_FUN_002E5318(a1[2], LVL_7_SIBERIUS_F63cf942f_FUN_002E5360(a2[2], a1[2]) * k);
}
extern float LVL_7_SIBERIUS_F846f1d58_FUN_002CDAE8(int *dst, float a, float b, float c, float d, float e);

void LVL_7_SIBERIUS_FUN_0041E258(char *a0, float *a1, float *a2,
                                        float f12, float f13, float f14)
{
    int *p = *(int **)(a0 + 112);

    a1[0] = LVL_7_SIBERIUS_F846f1d58_FUN_002CDAE8(p + 64, a1[0], a2[0], f12, f13, f14);
    a1[1] = LVL_7_SIBERIUS_F846f1d58_FUN_002CDAE8(p + 65, a1[1], a2[1], f12, f13, f14);
    a1[2] = LVL_7_SIBERIUS_F846f1d58_FUN_002CDAE8(p + 66, a1[2], a2[2], f12, f13, f14);
}
extern char LVL_7_SIBERIUS_Fbfa3ff84_D_00189F80[];

extern float LVL_7_SIBERIUS_Fbfa3ff84_FUN_002C9A08(void *p);
extern void LVL_7_SIBERIUS_Fbfa3ff84_FUN_002C9B08(void *a, void *b, float f);
extern void LVL_7_SIBERIUS_Fbfa3ff84_FUN_002C9B88(void *a, void *b, float f);
extern void LVL_7_SIBERIUS_Fbfa3ff84_FUN_002E4310(void *a, void *b, void *c);
extern void LVL_7_SIBERIUS_Fbfa3ff84_FUN_002E42D8(void *a);

void LVL_7_SIBERIUS_FUN_002B7AA0(float a0)
{
    char *p = LVL_7_SIBERIUS_Fbfa3ff84_D_00189F80;
    float x = a0;
    float r = LVL_7_SIBERIUS_Fbfa3ff84_FUN_002C9A08(p);
    float d;

    if (0.001f < r) {
        LVL_7_SIBERIUS_Fbfa3ff84_FUN_002C9B08(p, p, 0.0f);
        d = r - x;
        if (d < 0.0f)
            d = 0.0f;
        LVL_7_SIBERIUS_Fbfa3ff84_FUN_002C9B88(p, p, d);
        LVL_7_SIBERIUS_Fbfa3ff84_FUN_002E4310(p - 112, p - 112, p);
    } else {
        LVL_7_SIBERIUS_Fbfa3ff84_FUN_002E42D8(p);
    }
}
#ifndef RAC2_T_V4_FE23FE324
#define RAC2_T_V4_FE23FE324
typedef int V4_Fe23fe324 __attribute__((mode(TI)));
#endif


extern char LVL_7_SIBERIUS_Fe23fe324_D_00189E20[];
extern void LVL_7_SIBERIUS_Fe23fe324_FUN_002E42D8();
extern void LVL_7_SIBERIUS_Fe23fe324_FUN_002E4B90();
extern void LVL_7_SIBERIUS_Fe23fe324_FUN_002E47F8();
extern void LVL_7_SIBERIUS_Fe23fe324_FUN_002E4310();

void LVL_7_SIBERIUS_FUN_002C9850(V4_Fe23fe324 *a0, V4_Fe23fe324 *a1, float f)
{
    char *p = LVL_7_SIBERIUS_Fe23fe324_D_00189E20;
    unsigned char raw = p[8899];
    int state = raw;
    float m[4][4];
    float v[4];

    if (state == 0) {
        *a0 = *a1;
        ((float *)a0)[2] += f;
        return;
    }
    if (state < 0)
        return;
    if (state >= 3)
        return;
    LVL_7_SIBERIUS_Fe23fe324_FUN_002E42D8(v);
    v[2] = f;
    LVL_7_SIBERIUS_Fe23fe324_FUN_002E4B90(m, *(int *)(p + 8848) + 240);
    LVL_7_SIBERIUS_Fe23fe324_FUN_002E47F8(v, v, m);
    LVL_7_SIBERIUS_Fe23fe324_FUN_002E4310(a0, a1, v);
}
extern void LVL_7_SIBERIUS_F38a60c3d_FUN_0043AAA0(char *o, int n, float a, float b, float c, float d, float e);
extern void LVL_7_SIBERIUS_F38a60c3d_FUN_0043AAD8(char *o, int n, float a, float b);

void LVL_7_SIBERIUS_FUN_0043A998(char *o)
{
    float v;

    *(int *)(o + 24) = 0;
    *(float *)(o + 40) = 0.0f;
    v = *(float *)(o + 24);
    *(float *)(o + 44) = 0.0f;
    *(float *)(o + 128) = 0.0f;
    *(float *)(o + 36) = 0.005f;
    LVL_7_SIBERIUS_F38a60c3d_FUN_0043AAA0(o, 0, v, v, v, v, v);
    LVL_7_SIBERIUS_F38a60c3d_FUN_0043AAA0(o, 1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    *(int *)(o + 132) = 2;
    LVL_7_SIBERIUS_F38a60c3d_FUN_0043AAD8(o, 0, v, v);
    *(int *)(o + 32) = 0;
    *(int *)(o + 28) = 1;
}
extern float LVL_7_SIBERIUS_Fb4148aec_FUN_002E5360(float b, float a);
extern float LVL_7_SIBERIUS_Fb4148aec_FUN_002E4280(float t);
extern float LVL_7_SIBERIUS_Fb4148aec_FUN_002E4280(float t);
extern float LVL_7_SIBERIUS_Fb4148aec_FUN_002E4280(float t);
extern float LVL_7_SIBERIUS_Fb4148aec_FUN_002E4280(float t);
extern void LVL_7_SIBERIUS_Fb4148aec_FUN_002E5318(float a, float c);

void LVL_7_SIBERIUS_FUN_002E5768(float a, float b, float c)
{
    float t = LVL_7_SIBERIUS_Fb4148aec_FUN_002E5360(b, a);

    if (t <= 0.0f)
        c = -c;
    if (LVL_7_SIBERIUS_Fb4148aec_FUN_002E4280(t) < c)
        c = LVL_7_SIBERIUS_Fb4148aec_FUN_002E4280(t);
    else if (c < -LVL_7_SIBERIUS_Fb4148aec_FUN_002E4280(t))
        c = -LVL_7_SIBERIUS_Fb4148aec_FUN_002E4280(t);
    LVL_7_SIBERIUS_Fb4148aec_FUN_002E5318(a, c);
}
extern float LVL_7_SIBERIUS_Fc8641365_FUN_002E5318(float x);
extern float LVL_7_SIBERIUS_Fc8641365_FUN_002E4918(float x);
extern float LVL_7_SIBERIUS_Fc8641365_FUN_002E5318(float x);
extern float LVL_7_SIBERIUS_Fc8641365_FUN_002E4918(float x);

void LVL_7_SIBERIUS_FUN_00319428(float *a0, float *a1, float *a2,
                                        float b, float unused, float c)
{
    if (c > 0.0f) {
        float r = LVL_7_SIBERIUS_Fc8641365_FUN_002E5318(*a1);

        *a1 = r;
        a0[6] = LVL_7_SIBERIUS_Fc8641365_FUN_002E4918(r) * b + c;
    } else {
        float r = LVL_7_SIBERIUS_Fc8641365_FUN_002E5318(*a1);

        *a1 = r;
        a0[6] = a0[6] - *a2;
        *a2 = LVL_7_SIBERIUS_Fc8641365_FUN_002E4918(*a1) * b;
        a0[6] = a0[6] + *a2;
    }
}
extern int LVL_7_SIBERIUS_F6c3d1d31_FUN_0035D5B0();
extern int LVL_7_SIBERIUS_F6c3d1d31_FUN_0035E5D0();
extern float LVL_7_SIBERIUS_F6c3d1d31_FUN_002E44D0();
extern int LVL_7_SIBERIUS_F6c3d1d31_FUN_002E3F80();

int LVL_7_SIBERIUS_FUN_0035EA28(int *a0)
{
    int s2 = 0;
    int s1 = LVL_7_SIBERIUS_F6c3d1d31_FUN_0035D5B0(a0);
    float f20 = 1.0f;

    if (LVL_7_SIBERIUS_F6c3d1d31_FUN_0035E5D0(a0) == 2)
        f20 = 8.0f;

    if (s1 != 0) {
        if (LVL_7_SIBERIUS_F6c3d1d31_FUN_002E44D0((char *)a0 + 16, (char *)s1 + 96) < f20)
            s2 = LVL_7_SIBERIUS_F6c3d1d31_FUN_0035E5D0(a0) != 8;

        s2 = LVL_7_SIBERIUS_F6c3d1d31_FUN_002E3F80((char *)s1 + 304) != 0 ? 1 : s2;
    }

    return s2;
}
extern int LVL_7_SIBERIUS_F0440d2f1_FUN_002E47F8(float *, char *, char *);
extern float LVL_7_SIBERIUS_F0440d2f1_FUN_002E49C8(float, float);
extern float LVL_7_SIBERIUS_F0440d2f1_FUN_00314388(float *, char *, int, float, float, float, float);
extern void LVL_7_SIBERIUS_F0440d2f1_FUN_002B2A70(float, float, float);
extern char LVL_7_SIBERIUS_F0440d2f1_D_00189FB0[];

void LVL_7_SIBERIUS_FUN_002B2AF0(int a0, float a1, float a2, float a3)
{
    float tmp[2];
    char *p = LVL_7_SIBERIUS_F0440d2f1_D_00189FB0;
    float out;
    float r;

    LVL_7_SIBERIUS_F0440d2f1_FUN_002E47F8(tmp, p, p - 336);
    r = LVL_7_SIBERIUS_F0440d2f1_FUN_002E49C8(tmp[0], tmp[1]);
    out = 0.0f;
    *(float *)(p + 24) = LVL_7_SIBERIUS_F0440d2f1_FUN_00314388(&out, p + 20, a0, r, a1, a2, a3);
    LVL_7_SIBERIUS_F0440d2f1_FUN_002B2A70(0.0f, 0.0f, out);
}
extern void LVL_7_SIBERIUS_F8cb0f4c0_FUN_00313C88(float *, float);
extern float LVL_7_SIBERIUS_F8cb0f4c0_FUN_002E4280(float);

float LVL_7_SIBERIUS_FUN_00313E98(float *a0, float *a1, float f1, float f2,
                                         float f3, float f4)
{
    float s = f1;
    float u = f4;
    float t;
    float r;

    LVL_7_SIBERIUS_F8cb0f4c0_FUN_00313C88(a1, s - a0[0]);
    t = s - (a0[0] + a1[0]);
    a0[0] = a0[0] + a1[0];
    r = LVL_7_SIBERIUS_F8cb0f4c0_FUN_002E4280(t);
    u = u * 0.01f;
    if (r < u) {
        a0[0] = s;
        a1[0] = 0.0f;
        return a1[0];
    }
    return t;
}
extern void LVL_7_SIBERIUS_F44de46a7_FUN_002E45F0(void *, float);
extern void LVL_7_SIBERIUS_F44de46a7_FUN_002E4440(void *, void *, void *);
extern void LVL_7_SIBERIUS_F44de46a7_FUN_002E4398(void *, void *, float);
extern float LVL_7_SIBERIUS_F44de46a7_FUN_002E4458(void *);
extern float LVL_7_SIBERIUS_F44de46a7_FUN_002E4248(float);
extern void LVL_7_SIBERIUS_F44de46a7_FUN_002E50D8(void *, void *);
extern void LVL_7_SIBERIUS_F44de46a7_FUN_002E4EB8(void *, void *, void *);
extern void LVL_7_SIBERIUS_F44de46a7_FUN_002E40E8(void *, void *, int);

void LVL_7_SIBERIUS_FUN_0031B710(void *a0, void *a1, void *a2)
{
    float buf[12];
    float m[4];
    float q[4];
    float x;

    LVL_7_SIBERIUS_F44de46a7_FUN_002E45F0(q, 1.0f);
    LVL_7_SIBERIUS_F44de46a7_FUN_002E4440(m, q, (char *)a0 + 32);
    LVL_7_SIBERIUS_F44de46a7_FUN_002E4398(m, m, 0.5f);
    x = LVL_7_SIBERIUS_F44de46a7_FUN_002E4458(m);
    m[3] = -LVL_7_SIBERIUS_F44de46a7_FUN_002E4248(1.0f - x * x);
    LVL_7_SIBERIUS_F44de46a7_FUN_002E50D8(m, buf);
    LVL_7_SIBERIUS_F44de46a7_FUN_002E4EB8(a0, buf, a0);
    if (a2 != 0)
        LVL_7_SIBERIUS_F44de46a7_FUN_002E40E8(a2, buf, 48);
}
extern float LVL_7_SIBERIUS_Ffaf24891_FUN_002E4900(float x);
extern float LVL_7_SIBERIUS_Ffaf24891_FUN_002E4900(float x);
extern float LVL_7_SIBERIUS_Ffaf24891_FUN_002E4900(float x);
extern float LVL_7_SIBERIUS_Ffaf24891_FUN_002E4918(float x);
extern float LVL_7_SIBERIUS_Ffaf24891_FUN_002E4918(float x);
extern void LVL_7_SIBERIUS_Ffaf24891_FUN_002E4310(float *out, float *in, void *q);

void LVL_7_SIBERIUS_FUN_002D0118(float *out, float *p, void *q)
{
    float t;

    t = LVL_7_SIBERIUS_Ffaf24891_FUN_002E4900(p[1]);
    out[0] = p[2] * t * LVL_7_SIBERIUS_Ffaf24891_FUN_002E4900(p[0]);
    t = LVL_7_SIBERIUS_Ffaf24891_FUN_002E4900(p[1]);
    out[1] = p[2] * t * LVL_7_SIBERIUS_Ffaf24891_FUN_002E4918(p[0]);
    out[2] = p[2] * LVL_7_SIBERIUS_Ffaf24891_FUN_002E4918(p[1]);
    out[3] = 0.0f;
    LVL_7_SIBERIUS_Ffaf24891_FUN_002E4310(out, out, q);
}
extern float LVL_7_SIBERIUS_Fc3394786_FUN_00310B30(void);
extern float LVL_7_SIBERIUS_Fc3394786_FUN_00310BF8(void);
extern float LVL_7_SIBERIUS_Fc3394786_FUN_00310BF8(void);
extern float LVL_7_SIBERIUS_Fc3394786_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_Fc3394786_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_Fc3394786_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_Fc3394786_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_Fc3394786_FUN_002E4900(float);

void LVL_7_SIBERIUS_FUN_00310D80(float *out)
{
    float back = LVL_7_SIBERIUS_Fc3394786_FUN_00310B30();
    float a = LVL_7_SIBERIUS_Fc3394786_FUN_00310BF8();
    float b = LVL_7_SIBERIUS_Fc3394786_FUN_00310BF8();
    float value;

    value = LVL_7_SIBERIUS_Fc3394786_FUN_002E4900(a) * LVL_7_SIBERIUS_Fc3394786_FUN_002E4918(b);
    value = value * back;
    out[0] = value;
    value = LVL_7_SIBERIUS_Fc3394786_FUN_002E4918(a) * LVL_7_SIBERIUS_Fc3394786_FUN_002E4918(b);
    value = value * back;
    out[1] = value;
    out[2] = LVL_7_SIBERIUS_Fc3394786_FUN_002E4900(b) * back;
}
extern unsigned int LVL_7_SIBERIUS_F95518630_FUN_002E5470(float x);
extern unsigned int LVL_7_SIBERIUS_F95518630_FUN_002E5470(float x);
extern unsigned int LVL_7_SIBERIUS_F95518630_FUN_002E5470(float x);
extern unsigned int LVL_7_SIBERIUS_F95518630_FUN_002E5470(float x);

int LVL_7_SIBERIUS_FUN_00314988(float r, float g, float b, float a)
{
    unsigned int cr = LVL_7_SIBERIUS_F95518630_FUN_002E5470(r * 255.0f) & 0xff;
    unsigned int cg = LVL_7_SIBERIUS_F95518630_FUN_002E5470(g * 255.0f) & 0xff;
    unsigned int cb = LVL_7_SIBERIUS_F95518630_FUN_002E5470(b * 255.0f) & 0xff;
    unsigned int ca = LVL_7_SIBERIUS_F95518630_FUN_002E5470(a * 255.0f) & 0xff;
    unsigned int packed = cr;

    packed |= cg << 8;
    packed |= cb << 16;
    packed |= ca << 24;
    return packed;
}
extern float LVL_7_SIBERIUS_F197ee8cc_FUN_002E4900(float v);
extern float LVL_7_SIBERIUS_F197ee8cc_FUN_002E4918(float v);
extern void LVL_7_SIBERIUS_F197ee8cc_FUN_002E47F8(void *p, void *q, char *data);
extern void LVL_7_SIBERIUS_F197ee8cc_FUN_002E4310(void *p, void *q, char *data);

extern char LVL_7_SIBERIUS_F197ee8cc_D_00189E20[];

void LVL_7_SIBERIUS_FUN_002C95E8(float *p, int flag, float scale, float value, float height)
{
    p[0] = LVL_7_SIBERIUS_F197ee8cc_FUN_002E4900(value) * scale;
    p[1] = LVL_7_SIBERIUS_F197ee8cc_FUN_002E4918(value) * scale;
    p[2] = height;
    LVL_7_SIBERIUS_F197ee8cc_FUN_002E47F8(p, p, LVL_7_SIBERIUS_F197ee8cc_D_00189E20);
    if (flag != 0)
        LVL_7_SIBERIUS_F197ee8cc_FUN_002E4310(p, p, LVL_7_SIBERIUS_F197ee8cc_D_00189E20 + 128);
}
extern float LVL_7_SIBERIUS_F3392e4bc_FUN_002E4280(float d);

#ifndef RAC2_T_ROW_F3392E4BC
#define RAC2_T_ROW_F3392E4BC
typedef float Row_F3392e4bc[4];
#endif


float LVL_7_SIBERIUS_FUN_002AF200(Row_F3392e4bc *a, Row_F3392e4bc *b)
{
    float sum = 0.0f;
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            sum += LVL_7_SIBERIUS_F3392e4bc_FUN_002E4280(a[i][j] - b[i][j]);
    return sum;
}
extern void LVL_7_SIBERIUS_F2b6b96d1_FUN_0030C708(char *, int, int *, char *);
extern void LVL_7_SIBERIUS_F2b6b96d1_FUN_002E4398(char *, char *, float);
extern void LVL_7_SIBERIUS_F2b6b96d1_FUN_002E4DD8(char *, char *);
extern void LVL_7_SIBERIUS_F2b6b96d1_FUN_002E4F08(char *, char *, char *);
extern void LVL_7_SIBERIUS_F2b6b96d1_FUN_002E4310(char *, char *, char *);

void LVL_7_SIBERIUS_FUN_003078A0(char *p1, int p2, char *p3)
{
    int n;
    char buf[64];
    float f;

    n = p2;
    f = *(float *)(p1 + 44) * 0.0009765625f;
    LVL_7_SIBERIUS_F2b6b96d1_FUN_0030C708(p1, 1, &n, p3);
    LVL_7_SIBERIUS_F2b6b96d1_FUN_002E4398(p3 + 48, p3 + 48, f);
    LVL_7_SIBERIUS_F2b6b96d1_FUN_002E4DD8(buf, p1 + 192);
    LVL_7_SIBERIUS_F2b6b96d1_FUN_002E4F08(p3, buf, p3);
    LVL_7_SIBERIUS_F2b6b96d1_FUN_002E4310(p3 + 48, p3 + 48, p1 + 16);
}
extern void LVL_7_SIBERIUS_F3258c258_FUN_0030C5B0(char *);
extern void LVL_7_SIBERIUS_F3258c258_FUN_002E4398(char *, char *, float);
extern void LVL_7_SIBERIUS_F3258c258_FUN_002E47D0(char *, char *, char *);
extern void LVL_7_SIBERIUS_F3258c258_FUN_002E4310(char *, char *, char *);

void LVL_7_SIBERIUS_FUN_003079C8(char *p1, int n, char *p3, char *p4)
{
    float f = *(float *)(p1 + 44) * 0.0009765625f;

    LVL_7_SIBERIUS_F3258c258_FUN_0030C5B0(p1);
    if (n > 0) {
        do {
            LVL_7_SIBERIUS_F3258c258_FUN_002E4398(p4, p4, f);
            LVL_7_SIBERIUS_F3258c258_FUN_002E47D0(p4, p4, p1 + 192);
            LVL_7_SIBERIUS_F3258c258_FUN_002E4310(p4, p4, p1 + 16);
            p4 += 16;
        } while (--n != 0);
    }
}
extern float LVL_7_SIBERIUS_F94baa797_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F94baa797_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F94baa797_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_F94baa797_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F94baa797_FUN_002E4918(float);

void LVL_7_SIBERIUS_FUN_0031A0B8(float *p, float a, float b, float c)
{
    p[0] = LVL_7_SIBERIUS_F94baa797_FUN_002E4900(b) * a * LVL_7_SIBERIUS_F94baa797_FUN_002E4900(c);
    p[1] = LVL_7_SIBERIUS_F94baa797_FUN_002E4918(b) * a * LVL_7_SIBERIUS_F94baa797_FUN_002E4900(c);
    p[2] = LVL_7_SIBERIUS_F94baa797_FUN_002E4918(c) * a;
}
extern int LVL_7_SIBERIUS_Fcf85f2f4_FUN_002E3FB0(short *);
extern void LVL_7_SIBERIUS_Fcf85f2f4_FUN_003263C0(char *);
extern float LVL_7_SIBERIUS_Fcf85f2f4_FUN_002E5460(int);
extern int LVL_7_SIBERIUS_Fcf85f2f4_FUN_002E54B8(int, int, float);

struct T {
    float a;
    float b;
    int c;
    int d;
    float e;
};

void LVL_7_SIBERIUS_FUN_0032F840(char *p)
{
    if (LVL_7_SIBERIUS_Fcf85f2f4_FUN_002E3FB0((short *)(p + 10)) != 0) {
        LVL_7_SIBERIUS_Fcf85f2f4_FUN_003263C0(p);
    } else {
        struct T *t = (struct T *)(p + 32);
        float k = LVL_7_SIBERIUS_Fcf85f2f4_FUN_002E5460(*(short *)(p + 10)) * t->e;

        *(int *)(p + 4) = LVL_7_SIBERIUS_Fcf85f2f4_FUN_002E54B8(t->d, t->c, k);
        *(float *)(p + 12) = ((t->a - t->b) * k + t->b) * 210000.0f;
    }
}


extern f32 LVL_7_SIBERIUS_F3e5a3249_FUN_002E4900 (f32);

f32 LVL_7_SIBERIUS_FUN_00310F80 (f32 a, f32 b, f32 t)
{
  f32 u;
  if (t == 0.0f)
    return a;
  if (t == 1.0f)
    return b;
  u = (1.0f - LVL_7_SIBERIUS_F3e5a3249_FUN_002E4900 (t * 3.1415927f)) * 0.5f;
  return a + (b - a) * u;
}


extern s32 LVL_7_SIBERIUS_F45041a5f_FUN_0034DA90 (s32);
extern s32 LVL_7_SIBERIUS_F45041a5f_FUN_0034DA90 (s32);
extern s32 LVL_7_SIBERIUS_F45041a5f_FUN_0034DA90 (s32);
extern s32 LVL_7_SIBERIUS_F45041a5f_FUN_0034DA90 (s32);

s32 LVL_7_SIBERIUS_FUN_00349778 (s32 self)
{
  *(s32 *) (self + 68) = 0;
  *(s32 *) (self + 72) = LVL_7_SIBERIUS_F45041a5f_FUN_0034DA90 (*(s32 *) (self + 52) & 0x200);
  *(s32 *) (self + 76) = LVL_7_SIBERIUS_F45041a5f_FUN_0034DA90 (*(s32 *) (self + 52) & 0x200);
  if ((*(s32 *) (self + 52) & 0x200) == 0)
    {
      if (*(s32 *) (self + 72) == 0)
        *(s32 *) (self + 72) = LVL_7_SIBERIUS_F45041a5f_FUN_0034DA90 (1);
      if (*(s32 *) (self + 76) == 0)
        *(s32 *) (self + 76) = LVL_7_SIBERIUS_F45041a5f_FUN_0034DA90 (1);
    }
  *(s32 *) (self + 92) = 0;
  *(s32 *) (self + 80) = -1;
  *(s32 *) (self + 84) = -1;
  return 0;
}
extern char *LVL_7_SIBERIUS_F5580c116_FUN_00320648();
extern int *LVL_7_SIBERIUS_F5580c116_FUN_00320678();

void LVL_7_SIBERIUS_FUN_0039FA18(char *a0)
{
	int s1;
	int v1;
	int x;
	int i;
	int end;
	short *p;

	s1 = (int)LVL_7_SIBERIUS_F5580c116_FUN_00320648(1483, a0);
	v1 = *LVL_7_SIBERIUS_F5580c116_FUN_00320678(1483, a0);
	x = s1 + v1;
	p = (short *)(s1 + 8866);
	for (i = 79; i >= 0; i--) {
		*p = 0;
		p = p - 56;
	}
	s1 = x;
	end = s1 + 288;
	do {
		*(short *)(s1 + 80) = 0;
		*(int *)(s1 + 84) = 0;
		*(int *)(s1 + 88) = 0;
		s1 = s1 + 96;
	} while (s1 < end);
}



extern s32 LVL_7_SIBERIUS_F037efef1_FUN_002E54B8(s32, s32, f32);

void LVL_7_SIBERIUS_FUN_00427040(s32 *unused, s32 *dst, s32 *left, s32 *right, f32 scale) {
    dst[0] = LVL_7_SIBERIUS_F037efef1_FUN_002E54B8(left[0], right[0], scale);
    dst[1] = LVL_7_SIBERIUS_F037efef1_FUN_002E54B8(left[1], right[1], scale);
    dst[2] = LVL_7_SIBERIUS_F037efef1_FUN_002E54B8(left[2], right[2], scale);
    dst[3] = LVL_7_SIBERIUS_F037efef1_FUN_002E54B8(left[3], right[3], scale);
}


extern void LVL_7_SIBERIUS_F2d77341b_FUN_002E4310(void *, void *, void *);
extern s32 LVL_7_SIBERIUS_F2d77341b_FUN_002E3F80(void *);
extern void LVL_7_SIBERIUS_F2d77341b_FUN_003263C0(void *);

void LVL_7_SIBERIUS_FUN_0032BC78(s32 *self) {
    s32 *base = (s32 *)((char *)self + 32);
    s32 *state = (s32 *)((char *)self + 16);
    LVL_7_SIBERIUS_F2d77341b_FUN_002E4310(state, state, base);
    self[1] = (self[1] & 0x00ffffff) + ((base[6] * base[4] / base[5]) << 24);
    if (LVL_7_SIBERIUS_F2d77341b_FUN_002E3F80((s32 *)((char *)self + 48)) != 0) {
        LVL_7_SIBERIUS_F2d77341b_FUN_003263C0(self);
    }
}
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427668(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427668(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427668(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427668(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);
extern void LVL_7_SIBERIUS_F252d542a_FUN_00427E28(char *object);

char *LVL_7_SIBERIUS_FUN_0042AF00(char *object)
{
    LVL_7_SIBERIUS_F252d542a_FUN_00427668(object + 8);
    LVL_7_SIBERIUS_F252d542a_FUN_00427668(object + 84);
    LVL_7_SIBERIUS_F252d542a_FUN_00427668(object + 160);
    LVL_7_SIBERIUS_F252d542a_FUN_00427668(object + 236);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 312);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 384);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 456);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 528);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 600);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 672);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 744);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 816);
    LVL_7_SIBERIUS_F252d542a_FUN_00427E28(object + 888);
    return object;
}
extern void LVL_7_SIBERIUS_Fb344bd8e_FUN_00427890(void *p);
extern void LVL_7_SIBERIUS_Fb344bd8e_FUN_00427890(void *p);
extern void LVL_7_SIBERIUS_Fb344bd8e_FUN_0043C538(void *p);
extern void LVL_7_SIBERIUS_Fb344bd8e_FUN_00427B90(void *p);
extern void LVL_7_SIBERIUS_Fb344bd8e_FUN_00429098(void *p);
extern void LVL_7_SIBERIUS_Fb344bd8e_FUN_00429098(void *p);

unsigned char *LVL_7_SIBERIUS_FUN_0043F4B8(unsigned char *a0)
{
    unsigned char *p;
    int i;

    for (i = 25, p = a0; i != -1; i--) {
        LVL_7_SIBERIUS_Fb344bd8e_FUN_00427890(p);
        p += 72;
    }
    LVL_7_SIBERIUS_Fb344bd8e_FUN_00427890(a0 + 1872);
    LVL_7_SIBERIUS_Fb344bd8e_FUN_0043C538(a0 + 1952);
    LVL_7_SIBERIUS_Fb344bd8e_FUN_00427B90(a0 + 7472);
    LVL_7_SIBERIUS_Fb344bd8e_FUN_00429098(a0 + 7532);
    LVL_7_SIBERIUS_Fb344bd8e_FUN_00429098(a0 + 8124);
    return a0;
}
#ifndef RAC2_T_V4_F61E33AD9
#define RAC2_T_V4_F61E33AD9
typedef int V4_F61e33ad9 __attribute__((mode(TI)));
#endif


extern float LVL_7_SIBERIUS_F61e33ad9_FUN_002E4280(float f);
extern void LVL_7_SIBERIUS_F61e33ad9_FUN_002E4508(void *a, void *b);
extern void LVL_7_SIBERIUS_F61e33ad9_FUN_002E44D0(void *a, void *b);

void LVL_7_SIBERIUS_FUN_00337EC0(void *a0, void *a1, float scale)
{
    V4_F61e33ad9 l0;
    V4_F61e33ad9 l1;
    float *p0;
    float *p1;
    float t;
    float u;

    l0 = *(V4_F61e33ad9 *)a0;
    l1 = *(V4_F61e33ad9 *)a1;
    p0 = (float *)&l0;
    p1 = (float *)&l1;
    if (0.0f < scale) {
        t = p0[2];
        u = p1[2];
        if (LVL_7_SIBERIUS_F61e33ad9_FUN_002E4280(t - u) < scale) {
            LVL_7_SIBERIUS_F61e33ad9_FUN_002E4508(p0, p1);
            return;
        }
    }
    LVL_7_SIBERIUS_F61e33ad9_FUN_002E44D0(p0, p1);
}
extern void *LVL_7_SIBERIUS_Fb8d1f7f1_FUN_002A5448(void *p);
extern void LVL_7_SIBERIUS_Fb8d1f7f1_FUN_002C8158(void *a, void *b, float f);

extern unsigned char LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20[];

void LVL_7_SIBERIUS_FUN_002AE5F0(void)
{
    if (LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20[8888] == 0)
        return;
    if (*(int *)(LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20 + 3736) != 0) {
        *(int *)(LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20 + 3748) = 1;
    } else if (*(int *)(LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20 + 8852) == 0) {
        if (*(unsigned char *)(*(int *)(LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20 + 8848) + 67) == *(int *)(LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20 + 9392)) {
            LVL_7_SIBERIUS_Fb8d1f7f1_FUN_002C8158(LVL_7_SIBERIUS_Fb8d1f7f1_FUN_002A5448(0), 0, -2.0f);
        }
    }
    LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20[8888] = 0;
    LVL_7_SIBERIUS_Fb8d1f7f1_D_00189E20[8890] = 0;
}
extern char LVL_7_SIBERIUS_Fd337d953_D_00189E20[];
extern void LVL_7_SIBERIUS_Fd337d953_FUN_002E47F8(char *dst, char *src, char *extra);

#ifndef RAC2_T_V4_FD337D953
#define RAC2_T_V4_FD337D953
typedef int V4_Fd337d953 __attribute__((mode(TI)));
#endif


void LVL_7_SIBERIUS_FUN_002C9C18(char *dst, char *src, float k)
{
    char *base = LVL_7_SIBERIUS_Fd337d953_D_00189E20;
    int flag = *(unsigned char *)(base + 8899);

    if (flag == 0) {
        *(V4_Fd337d953 *)dst = *(V4_Fd337d953 *)src;
        *(float *)(dst + 8) = *(float *)(dst + 8) * k;
        return;
    }
    if (flag < 0)
        return;
    if (flag >= 3)
        return;
    LVL_7_SIBERIUS_Fd337d953_FUN_002E47F8(dst, src, base + 64);
    *(float *)(dst + 8) = *(float *)(dst + 8) * k;
    LVL_7_SIBERIUS_Fd337d953_FUN_002E47F8(dst, dst, base);
}
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_0042C018(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427B90(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427668(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);
extern void LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(void *);

char *LVL_7_SIBERIUS_FUN_0042FB08(char *object)
{
    LVL_7_SIBERIUS_F1b9be9ff_FUN_0042C018(object + 8);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427B90(object + 684);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 744);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 816);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 888);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427668(object + 960);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 1040);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 1112);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 1184);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 1256);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 1328);
    LVL_7_SIBERIUS_F1b9be9ff_FUN_00427E28(object + 1400);
    return object;
}
extern void *LVL_7_SIBERIUS_Fdd95b44d_FUN_002EA888(int);
extern void *LVL_7_SIBERIUS_Fdd95b44d_FUN_002EA888(int);
extern void *LVL_7_SIBERIUS_Fdd95b44d_FUN_002EA888(int);
extern void LVL_7_SIBERIUS_Fdd95b44d_FUN_0042C518(void *, void *, void *, void *);
extern void LVL_7_SIBERIUS_Fdd95b44d_FUN_0042C570(void *, float);

void LVL_7_SIBERIUS_FUN_0042ACE0(int *self)
{
    void *a;
    void *b;
    void *c;
    void *sub = (void *)(self + 2);

    a = LVL_7_SIBERIUS_Fdd95b44d_FUN_002EA888(11677);
    b = LVL_7_SIBERIUS_Fdd95b44d_FUN_002EA888(11676);
    c = LVL_7_SIBERIUS_Fdd95b44d_FUN_002EA888(11599);

    LVL_7_SIBERIUS_Fdd95b44d_FUN_0042C518(sub, a, b, c);
    LVL_7_SIBERIUS_Fdd95b44d_FUN_0042C570(sub, 0.0f);

    self[191] = 1;
}
extern void LVL_7_SIBERIUS_F62b44aca_FUN_002E42D8(void *);
extern void LVL_7_SIBERIUS_F62b44aca_FUN_002A9DB0(void *, float, float, float);
extern unsigned char LVL_7_SIBERIUS_F62b44aca_D_0018C0D4[];

void LVL_7_SIBERIUS_FUN_002A9EB8(float a, float b, float c)
{
    float buf[4];

    LVL_7_SIBERIUS_F62b44aca_FUN_002E42D8(buf);

    if (LVL_7_SIBERIUS_F62b44aca_D_0018C0D4[0] == 1)
        buf[2] = 0.35f;
    else
        buf[2] = 0.6f;

    LVL_7_SIBERIUS_F62b44aca_FUN_002A9DB0(buf, a, b, c);
}
extern int LVL_7_SIBERIUS_Ffe57d182_FUN_002C7D90(int, void *, void *);
extern void LVL_7_SIBERIUS_Ffe57d182_FUN_003106E8(void *, int, int, int);
extern void LVL_7_SIBERIUS_Ffe57d182_FUN_003106E8(void *, int, int, int);
extern char LVL_7_SIBERIUS_Ffe57d182_D_00189E20[];

void LVL_7_SIBERIUS_FUN_002C7AD8(void)
{
    char *p = LVL_7_SIBERIUS_Ffe57d182_D_00189E20;
    void *s0;
    void *s1;
    int buf[2];

    s0 = *(void **)(p + 4880);
    s1 = *(void **)(p + 4884);

    if (s0 == 0)
        return;
    if (s1 == 0)
        return;

    if (*(unsigned char *)((char *)s0 + 67) != 1)
        return;

    if (LVL_7_SIBERIUS_Ffe57d182_FUN_002C7D90(0, buf, buf + 1) == 0)
        return;

    LVL_7_SIBERIUS_Ffe57d182_FUN_003106E8(s0, buf[0], 0, 7);
    LVL_7_SIBERIUS_Ffe57d182_FUN_003106E8(s1, buf[1], 0, 7);
}
extern float LVL_7_SIBERIUS_F101cea20_FUN_00310B30(float, float);
extern float LVL_7_SIBERIUS_F101cea20_FUN_00310B30(float, float);
extern float LVL_7_SIBERIUS_F101cea20_FUN_00310B30(float, float);

void LVL_7_SIBERIUS_FUN_00316788(float *vector, float scale)
{
    float negative = -scale;

    vector[0] = vector[0] + LVL_7_SIBERIUS_F101cea20_FUN_00310B30(negative, scale);
    vector[1] = vector[1] + LVL_7_SIBERIUS_F101cea20_FUN_00310B30(negative, scale);
    vector[2] = vector[2] + LVL_7_SIBERIUS_F101cea20_FUN_00310B30(negative, scale);
}
extern int LVL_7_SIBERIUS_F61cc5848_FUN_002EA888(int);
extern int LVL_7_SIBERIUS_F61cc5848_FUN_002EA888(int);
extern int LVL_7_SIBERIUS_F61cc5848_FUN_002EA888(int);
extern void LVL_7_SIBERIUS_F61cc5848_FUN_0042C518(char *, int, int, int);
extern void LVL_7_SIBERIUS_F61cc5848_FUN_0042C570(char *, float);

void LVL_7_SIBERIUS_FUN_0042AC60(char *p)
{
    int first = LVL_7_SIBERIUS_F61cc5848_FUN_002EA888(11678);
    int second = LVL_7_SIBERIUS_F61cc5848_FUN_002EA888(11676);

    LVL_7_SIBERIUS_F61cc5848_FUN_0042C518(p + 8, first, second, LVL_7_SIBERIUS_F61cc5848_FUN_002EA888(11599));
    LVL_7_SIBERIUS_F61cc5848_FUN_0042C570(p + 8, 0.0f);
    *(int *)(p + 764) = 0;
}
extern int LVL_7_SIBERIUS_F32d48737_D_001A8FD8 __attribute__((sda));
extern int LVL_7_SIBERIUS_F32d48737_D_001A8FDC __attribute__((sda));
extern void LVL_7_SIBERIUS_F32d48737_FUN_0042C2E8(int *p, int flag);
extern void LVL_7_SIBERIUS_F32d48737_FUN_0042C2E8(int *p, int flag);
extern void LVL_7_SIBERIUS_F32d48737_FUN_0042C410(int *p);
extern void LVL_7_SIBERIUS_F32d48737_FUN_004277E0(int *p);

void LVL_7_SIBERIUS_FUN_0042AE78(int *obj)
{
    if (LVL_7_SIBERIUS_F32d48737_D_001A8FD8 != 0 || LVL_7_SIBERIUS_F32d48737_D_001A8FDC != 0 || obj[192] != 0)
        LVL_7_SIBERIUS_F32d48737_FUN_0042C2E8(obj + 2, 0);
    if (obj[191] == 1)
        LVL_7_SIBERIUS_F32d48737_FUN_0042C2E8(obj + 2, 1);
    LVL_7_SIBERIUS_F32d48737_FUN_0042C410(obj + 2);
    LVL_7_SIBERIUS_F32d48737_FUN_004277E0(obj + 170);
}
extern int LVL_7_SIBERIUS_F455be788_D_001A904C __attribute__((sda));
extern int LVL_7_SIBERIUS_F455be788_FUN_00432A20(int x);

int LVL_7_SIBERIUS_FUN_0033E6C8(int *obj)
{
    if (LVL_7_SIBERIUS_F455be788_D_001A904C != 0)
        obj[13] = LVL_7_SIBERIUS_F455be788_FUN_00432A20(LVL_7_SIBERIUS_F455be788_D_001A904C + 0x3BE08);
    return 0;
}
extern int LVL_7_SIBERIUS_F455be788_D_001A904C __attribute__((sda));
extern int LVL_7_SIBERIUS_F455be788_FUN_00432A20(int x);

int LVL_7_SIBERIUS_FUN_003447D0(int *obj)
{
    if (LVL_7_SIBERIUS_F455be788_D_001A904C != 0)
        obj[13] = LVL_7_SIBERIUS_F455be788_FUN_00432A20(LVL_7_SIBERIUS_F455be788_D_001A904C + 0x3BE08);
    return 0;
}
#ifndef RAC2_T_NODE16_F23626AD8
#define RAC2_T_NODE16_F23626AD8
typedef struct Node16_F23626ad8 Node16_F23626ad8;
#endif

#ifndef RAC2_T_NODE104_F23626AD8
#define RAC2_T_NODE104_F23626AD8
typedef struct Node104_F23626ad8 Node104_F23626ad8;
#endif

#ifndef RAC2_T_NODE24_F23626AD8
#define RAC2_T_NODE24_F23626AD8
typedef struct Node24_F23626ad8 Node24_F23626ad8;
#endif


struct Node16_F23626ad8 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_F23626ad8 {
    unsigned char pad0[16];
    Node16_F23626ad8 *p16;
};

struct Node24_F23626ad8 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_F23626ad8 *p104;
};

#ifndef RAC2_T_OBJ_F23626AD8
#define RAC2_T_OBJ_F23626AD8
typedef struct Obj_F23626ad8 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[16];
    Node24_F23626ad8 *f24;
} Obj_F23626ad8;
#endif


extern void LVL_7_SIBERIUS_F23626ad8_FUN_00308478(Node24_F23626ad8 *a, unsigned char b, unsigned char c, unsigned char d);

void LVL_7_SIBERIUS_FUN_0040B3E0(Obj_F23626ad8 *p)
{
    Node24_F23626ad8 *s;
    Node16_F23626ad8 *d;
    int v;

    LVL_7_SIBERIUS_F23626ad8_FUN_00308478(p->f24, p->u.b.b4, p->u.b.b5, p->u.b.h6);
    s = p->f24;
    if ((s->h52 & 0x20) == 0)
        return;
    d = ((Node104_F23626ad8 *)s->p104)->p16;
    if (d == 0)
        return;
    if (d->h0 == 0)
        return;
    d->b4 = p->u.b.b4;
    d->b5 = p->u.f4 >> 8;
    v = p->u.b.h6;
    d->b6 = v;
}
#ifndef RAC2_T_REC_F4EC78016
#define RAC2_T_REC_F4EC78016
typedef struct Rec_F4ec78016 {
    int f0;
    unsigned char pad4[6];
    short h10;
    unsigned char pad12[20];
    int f32;
} Rec_F4ec78016;
#endif


#ifndef RAC2_T_SLOT_F4EC78016
#define RAC2_T_SLOT_F4EC78016
typedef struct Slot_F4ec78016 {
    int f0;
    unsigned char pad4[108];
} Slot_F4ec78016;
#endif


#ifndef RAC2_T_GLOBALS_F4EC78016
#define RAC2_T_GLOBALS_F4EC78016
typedef struct Globals_F4ec78016 {
    unsigned char pad0[108];
    short h108;
    short h110;
    short h112;
    unsigned char pad114[18];
    int f132;
} Globals_F4ec78016;
#endif


extern Slot_F4ec78016 LVL_7_SIBERIUS_F4ec78016_D_00188660[];
extern Globals_F4ec78016 LVL_7_SIBERIUS_F4ec78016_D_001A63A8[];

extern void LVL_7_SIBERIUS_F4ec78016_FUN_00323A78(int a, int b, int c, int d);

void LVL_7_SIBERIUS_FUN_00324FB8(void *a0, long a1)
{
    Rec_F4ec78016 *n = (Rec_F4ec78016 *)a1;
    Slot_F4ec78016 *p;
    int i;

    if (n == 0)
        return;
    n->f0 = (int)a0;
    i = n->f32;
    if (i >= 0) {
        p = LVL_7_SIBERIUS_F4ec78016_D_00188660 + i;
        *(int *)((char *)p + 112) = (int)a0;
    }
    if (a0 != 0) {
        if (n->h10 == 1)
            n->h10 = 2;
    } else {
        LVL_7_SIBERIUS_F4ec78016_FUN_00323A78(LVL_7_SIBERIUS_F4ec78016_D_001A63A8->h108, LVL_7_SIBERIUS_F4ec78016_D_001A63A8->h112, LVL_7_SIBERIUS_F4ec78016_D_001A63A8->f132, LVL_7_SIBERIUS_F4ec78016_D_001A63A8->h110);
    }
}
#ifndef RAC2_T_V4_FA012328C
#define RAC2_T_V4_FA012328C
typedef int V4_Fa012328c __attribute__((mode(TI)));
#endif


extern char LVL_7_SIBERIUS_Fa012328c_D_00189F20[];
extern char LVL_7_SIBERIUS_Fa012328c_D_00189F30[] __attribute__((sda));

extern void LVL_7_SIBERIUS_Fa012328c_FUN_002B26D0(void);
extern void LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(void *p);
extern void LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(void *p);
extern void LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(void *p);
extern void LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(void *p);
extern void LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(void *p);
extern void LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(void *p);
extern void LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(void *p);
extern void LVL_7_SIBERIUS_Fa012328c_FUN_003256A8(void);

void LVL_7_SIBERIUS_FUN_002B18D0(void)
{
    char *p;

    *(volatile V4_Fa012328c *)LVL_7_SIBERIUS_Fa012328c_D_00189F30 = 0;
    LVL_7_SIBERIUS_Fa012328c_FUN_002B26D0();
    p = LVL_7_SIBERIUS_Fa012328c_D_00189F20;
    LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(p);
    LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(p - 16);
    LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(p + 16);
    LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(p + 32);
    LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(p + 48);
    LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(p + 96);
    LVL_7_SIBERIUS_Fa012328c_FUN_002E42D8(p - 96);
    p = p - 256;
    *(int *)(p + 420) = 0;
    *(int *)(p + 376) = 0;
    *(int *)(p + 368) = 0;
    LVL_7_SIBERIUS_Fa012328c_FUN_003256A8();
}
#ifndef RAC2_T_NODE16_FE48725C6
#define RAC2_T_NODE16_FE48725C6
typedef struct Node16_Fe48725c6 Node16_Fe48725c6;
#endif

#ifndef RAC2_T_NODE104_FE48725C6
#define RAC2_T_NODE104_FE48725C6
typedef struct Node104_Fe48725c6 Node104_Fe48725c6;
#endif

#ifndef RAC2_T_NODE24_FE48725C6
#define RAC2_T_NODE24_FE48725C6
typedef struct Node24_Fe48725c6 Node24_Fe48725c6;
#endif


struct Node16_Fe48725c6 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_Fe48725c6 {
    unsigned char pad0[16];
    Node16_Fe48725c6 *p16;
};

struct Node24_Fe48725c6 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_Fe48725c6 *p104;
};

#ifndef RAC2_T_OBJ_FE48725C6
#define RAC2_T_OBJ_FE48725C6
typedef struct Obj_Fe48725c6 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[12];
    Node24_Fe48725c6 *f24;
} Obj_Fe48725c6;
#endif


extern void LVL_7_SIBERIUS_Fe48725c6_FUN_00308478(Node24_Fe48725c6 *a, unsigned char b, unsigned char c, unsigned char d);

void LVL_7_SIBERIUS_FUN_003E4260(Obj_Fe48725c6 *p)
{
    Node24_Fe48725c6 *s;
    Node16_Fe48725c6 *d;
    int v;

    LVL_7_SIBERIUS_Fe48725c6_FUN_00308478(p->f24, p->u.b.b4, p->u.b.b5, p->u.b.h6);
    s = p->f24;
    if ((s->h52 & 0x20) == 0)
        return;
    d = ((Node104_Fe48725c6 *)s->p104)->p16;
    if (d == 0)
        return;
    if (d->h0 == 0)
        return;
    d->b4 = p->u.b.b4;
    d->b5 = p->u.f4 >> 8;
    v = p->u.b.h6;
    d->b6 = v;
}
extern int LVL_7_SIBERIUS_F9032bf17_D_001A904C __attribute__((sda));
extern void LVL_7_SIBERIUS_F9032bf17_FUN_00429578(int *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

void LVL_7_SIBERIUS_FUN_00302D20(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int value = LVL_7_SIBERIUS_F9032bf17_D_001A904C;

    if (value != 0)
        LVL_7_SIBERIUS_F9032bf17_FUN_00429578((int *)(value + 0x36F28), a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
extern void LVL_7_SIBERIUS_F7a8d0dad_FUN_00429CD8(char *a0);
extern void LVL_7_SIBERIUS_F7a8d0dad_FUN_00429F20(char *a0);
extern void LVL_7_SIBERIUS_F7a8d0dad_FUN_00429CD0(char *a0);

void LVL_7_SIBERIUS_FUN_00429F28(char *a0)
{
    if (*(float *)(*(int *)(a0 + 4)) == 0.0f)
        return;

    switch (*(int *)(a0 + 456))
    {
    case 0:
        LVL_7_SIBERIUS_F7a8d0dad_FUN_00429CD8(a0);
        break;
    case 2:
        LVL_7_SIBERIUS_F7a8d0dad_FUN_00429F20(a0);
        break;
    }

    LVL_7_SIBERIUS_F7a8d0dad_FUN_00429CD0(a0);
}
extern void LVL_7_SIBERIUS_F8e0a750e_FUN_002E4340(float *p);
extern float LVL_7_SIBERIUS_F8e0a750e_FUN_002E4488(float *p);
extern float LVL_7_SIBERIUS_F8e0a750e_FUN_002E49C8(float a, float b);
extern float LVL_7_SIBERIUS_F8e0a750e_FUN_002E49C8(float a, float b);
extern void LVL_7_SIBERIUS_F8e0a750e_FUN_002E5360(float a, float b);
extern float LVL_7_SIBERIUS_F8e0a750e_FUN_002E4458(float *p);

int LVL_7_SIBERIUS_FUN_002D01C8(float *a0)
{
    float local[3];
    float t;

    LVL_7_SIBERIUS_F8e0a750e_FUN_002E4340(local);
    a0[1] = LVL_7_SIBERIUS_F8e0a750e_FUN_002E49C8(LVL_7_SIBERIUS_F8e0a750e_FUN_002E4488(local), local[2]);

    t = LVL_7_SIBERIUS_F8e0a750e_FUN_002E49C8(local[0], local[1]);
    LVL_7_SIBERIUS_F8e0a750e_FUN_002E5360(t, a0[0]);
    a0[0] = t;

    a0[2] = LVL_7_SIBERIUS_F8e0a750e_FUN_002E4458(local);

    return 0;
}



extern f32 LVL_7_SIBERIUS_Fe985fe67_FUN_00310BF8(void);
extern f32 LVL_7_SIBERIUS_Fe985fe67_FUN_00310B30(f32, f32);
extern void LVL_7_SIBERIUS_Fe985fe67_FUN_0031A0B8(s32, f32, f32, f32);

void LVL_7_SIBERIUS_FUN_00310C98(s32 a0, f32 a1, f32 a2) {
    f32 x = LVL_7_SIBERIUS_Fe985fe67_FUN_00310BF8();
    f32 y = LVL_7_SIBERIUS_Fe985fe67_FUN_00310BF8();
    f32 z = LVL_7_SIBERIUS_Fe985fe67_FUN_00310B30(a1, a2);
    LVL_7_SIBERIUS_Fe985fe67_FUN_0031A0B8(a0, z, x, y);
}



#ifndef RAC2_T_V4S_F31E44309
#define RAC2_T_V4S_F31E44309
typedef struct {
    f32 x, y, z, w;
} V4S_F31e44309;
#endif


extern V4S_F31e44309 LVL_7_SIBERIUS_F31e44309_D_00189E20[];

extern void LVL_7_SIBERIUS_F31e44309_FUN_002E4398(V4S_F31e44309 *, V4S_F31e44309 *, f32);

void LVL_7_SIBERIUS_FUN_002B4CA0(f32 a0) {
    V4S_F31e44309 *p = &LVL_7_SIBERIUS_F31e44309_D_00189E20[17];
    LVL_7_SIBERIUS_F31e44309_FUN_002E4398(p, p, a0);
    LVL_7_SIBERIUS_F31e44309_FUN_002E4398(p + 1, p + 1, a0);
    LVL_7_SIBERIUS_F31e44309_FUN_002E4398(p - 2, p - 2, a0);
    LVL_7_SIBERIUS_F31e44309_FUN_002E4398(p + 5, p + 5, a0);
    LVL_7_SIBERIUS_F31e44309_D_00189E20[27].y = LVL_7_SIBERIUS_F31e44309_D_00189E20[27].y * a0;
}



#ifndef RAC2_T_V4_F36D8A248
#define RAC2_T_V4_F36D8A248
typedef struct {
    f32 x, y, z, w;
} V4_F36d8a248;
#endif


#ifndef RAC2_T_M4_F36D8A248
#define RAC2_T_M4_F36D8A248
typedef struct {
    V4_F36d8a248 r[4];
} M4_F36d8a248;
#endif


extern void LVL_7_SIBERIUS_F36d8a248_FUN_002E4B90(M4_F36d8a248 *, V4_F36d8a248 *);
extern void LVL_7_SIBERIUS_F36d8a248_FUN_002E4F08(M4_F36d8a248 *, M4_F36d8a248 *, V4_F36d8a248 *);
extern void LVL_7_SIBERIUS_F36d8a248_FUN_003152C0(M4_F36d8a248 *, V4_F36d8a248 *);

void LVL_7_SIBERIUS_FUN_00318C40(u8 *a0, f32 a1, f32 a2, f32 a3) {
    V4_F36d8a248 in;
    M4_F36d8a248 m1;
    M4_F36d8a248 m2;
    in.x = a1;
    in.y = a2;
    in.z = a3;
    LVL_7_SIBERIUS_F36d8a248_FUN_002E4B90(&m1, &in);
    LVL_7_SIBERIUS_F36d8a248_FUN_002E4B90(&m2, (V4_F36d8a248 *)(a0 + 240));
    LVL_7_SIBERIUS_F36d8a248_FUN_002E4F08(&m2, &m2, &m1);
    LVL_7_SIBERIUS_F36d8a248_FUN_003152C0(&m2, (V4_F36d8a248 *)(a0 + 240));
}



extern f32 LVL_7_SIBERIUS_F53c67c85_FUN_002E4918(f32);
extern f32 LVL_7_SIBERIUS_F53c67c85_FUN_002E5318(f32, f32);
extern void LVL_7_SIBERIUS_F53c67c85_FUN_002E54B8(s32, s32, f32);

void LVL_7_SIBERIUS_FUN_0031C9C0(f32 *a0, s32 a1, s32 a2, f32 a3) {
    f32 v = LVL_7_SIBERIUS_F53c67c85_FUN_002E4918(a0[0]);
    f32 s = v * 0.5f + 0.5f;
    a0[0] = LVL_7_SIBERIUS_F53c67c85_FUN_002E5318(a0[0], a3);
    LVL_7_SIBERIUS_F53c67c85_FUN_002E54B8(a1, a2, s);
}



#ifndef RAC2_T_V4_F6B9E759F
#define RAC2_T_V4_F6B9E759F
typedef struct {
    f32 x, y, z, w;
} V4_F6b9e759f;
#endif


#ifndef RAC2_T_M4_F6B9E759F
#define RAC2_T_M4_F6B9E759F
typedef struct {
    V4_F6b9e759f r[4];
} M4_F6b9e759f;
#endif


extern V4_F6b9e759f LVL_7_SIBERIUS_F6b9e759f_D_00189EA0[];

extern void LVL_7_SIBERIUS_F6b9e759f_FUN_002E4B90(M4_F6b9e759f *, V4_F6b9e759f *);
extern void LVL_7_SIBERIUS_F6b9e759f_FUN_002E4F08(M4_F6b9e759f *, M4_F6b9e759f *, V4_F6b9e759f *);
extern void LVL_7_SIBERIUS_F6b9e759f_FUN_003152C0(M4_F6b9e759f *, V4_F6b9e759f *);

void LVL_7_SIBERIUS_FUN_002B2A70(f32 a1, f32 a2, f32 a3) {
    V4_F6b9e759f in;
    M4_F6b9e759f m1;
    M4_F6b9e759f m2;
    in.x = a1;
    in.y = a2;
    in.z = a3;
    LVL_7_SIBERIUS_F6b9e759f_FUN_002E4B90(&m1, &in);
    LVL_7_SIBERIUS_F6b9e759f_FUN_002E4B90(&m2, &LVL_7_SIBERIUS_F6b9e759f_D_00189EA0[1]);
    LVL_7_SIBERIUS_F6b9e759f_FUN_002E4F08(&m2, &m2, &m1);
    LVL_7_SIBERIUS_F6b9e759f_FUN_003152C0(&m2, &LVL_7_SIBERIUS_F6b9e759f_D_00189EA0[1]);
}
extern float LVL_7_SIBERIUS_F741d8ff0_FUN_002E5360(float x, float y);
extern float LVL_7_SIBERIUS_F741d8ff0_FUN_002E4900(float x);
extern float LVL_7_SIBERIUS_F741d8ff0_FUN_002E5318(float x, float y);

float LVL_7_SIBERIUS_FUN_00311018(float a, float b, float c)
{
    float t;
    float u;

    t = LVL_7_SIBERIUS_F741d8ff0_FUN_002E5360(b, a);
    u = LVL_7_SIBERIUS_F741d8ff0_FUN_002E4900(c * 3.1415927f);
    t = t * 0.5f;
    return LVL_7_SIBERIUS_F741d8ff0_FUN_002E5318(a, t * (1.0f - u));
}
extern void LVL_7_SIBERIUS_Fd534a00c_FUN_0031B290(void *a, void *b, int c);
extern void LVL_7_SIBERIUS_Fd534a00c_FUN_002E45F0(float f, void *a, void *b);
extern void LVL_7_SIBERIUS_Fd534a00c_FUN_002E4310(char *target, char *first, char *local);

extern int LVL_7_SIBERIUS_Fd534a00c_D_001A8FF0 __attribute__((sda));

void LVL_7_SIBERIUS_FUN_0031B3E0(void *p, float *a1, float *a2, float f)
{
    float buf[4];

    if (LVL_7_SIBERIUS_Fd534a00c_D_001A8FF0 == 0) {
        a1[2] = a2[2] - f;
    } else {
        LVL_7_SIBERIUS_Fd534a00c_FUN_0031B290(p, buf, 0);
        LVL_7_SIBERIUS_Fd534a00c_FUN_002E45F0(f, buf, buf);
        LVL_7_SIBERIUS_Fd534a00c_FUN_002E4310((char *)a1, (char *)a2, (char *)buf);
    }
}
extern void LVL_7_SIBERIUS_F652b70cf_FUN_00427668(void *);
extern void LVL_7_SIBERIUS_F652b70cf_FUN_00427B90(void *);
extern void LVL_7_SIBERIUS_F652b70cf_FUN_00427E28(void *);

void *LVL_7_SIBERIUS_FUN_0042B968(char *p)
{
    int i;
    char *q = p + 4;

    for (i = 3; i != -1; i--) {
        LVL_7_SIBERIUS_F652b70cf_FUN_00427668(q);
        q += 76;
    }
    LVL_7_SIBERIUS_F652b70cf_FUN_00427B90(p + 308);
    LVL_7_SIBERIUS_F652b70cf_FUN_00427E28(p + 368);
    return p;
}
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_0042C410();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_0034A4A8();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_00427CE8();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_004277E0();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38();
extern void LVL_7_SIBERIUS_F9e73b90d_FUN_00430250();

void LVL_7_SIBERIUS_FUN_004304F8(char *p)
{
    LVL_7_SIBERIUS_F9e73b90d_FUN_0042C410(p + 8);
    LVL_7_SIBERIUS_F9e73b90d_FUN_0034A4A8(0);
    LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38(p + 744);
    LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38(p + 816);
    LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38(p + 888);
    LVL_7_SIBERIUS_F9e73b90d_FUN_00427CE8(p + 684);
    LVL_7_SIBERIUS_F9e73b90d_FUN_004277E0(p + 960);
    LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38(p + 1400);
    LVL_7_SIBERIUS_F9e73b90d_FUN_00427F38(p + 1328);
    LVL_7_SIBERIUS_F9e73b90d_FUN_00430250(p);
}
extern int LVL_7_SIBERIUS_Fc40b1162_FUN_002E3FB0();
extern void LVL_7_SIBERIUS_Fc40b1162_FUN_003263C0();

void LVL_7_SIBERIUS_FUN_0032CCF8(char *p)
{
    if (LVL_7_SIBERIUS_Fc40b1162_FUN_002E3FB0(p + 10)) {
        LVL_7_SIBERIUS_Fc40b1162_FUN_003263C0(p);
    }
}
extern int LVL_7_SIBERIUS_Fc40b1162_FUN_002E3FB0();
extern void LVL_7_SIBERIUS_Fc40b1162_FUN_003263C0();

void LVL_7_SIBERIUS_FUN_00336828(char *p)
{
    if (LVL_7_SIBERIUS_Fc40b1162_FUN_002E3FB0(p + 10)) {
        LVL_7_SIBERIUS_Fc40b1162_FUN_003263C0(p);
    }
}
extern char LVL_7_SIBERIUS_F2dbfd8df_D_00189E20[];
extern char LVL_7_SIBERIUS_F2dbfd8df_D_001A63A8[];
extern short LVL_7_SIBERIUS_F2dbfd8df_D_00152C2A;

extern void LVL_7_SIBERIUS_F2dbfd8df_FUN_00324478();
extern void LVL_7_SIBERIUS_F2dbfd8df_FUN_00354258();
extern void LVL_7_SIBERIUS_F2dbfd8df_FUN_002EA738();
extern void LVL_7_SIBERIUS_F2dbfd8df_FUN_00356BA0();

void LVL_7_SIBERIUS_FUN_00356E30(void)
{
    char *p = LVL_7_SIBERIUS_F2dbfd8df_D_00189E20;
    char *q;
    unsigned short v;

    if (*(int *)(p + 9420) <= 0) {
        *(int *)(p + 9420) = 1;
    }
    LVL_7_SIBERIUS_F2dbfd8df_FUN_00324478(0);

    q = LVL_7_SIBERIUS_F2dbfd8df_D_001A63A8;
    v = *(unsigned short *)(q + 114);
    if ((unsigned short)(v - 6) >= 2) {
        *(unsigned short *)(q + 114) = 5;
    }
    LVL_7_SIBERIUS_F2dbfd8df_FUN_00354258();
    LVL_7_SIBERIUS_F2dbfd8df_FUN_002EA738();
    LVL_7_SIBERIUS_F2dbfd8df_FUN_00356BA0(0);
    LVL_7_SIBERIUS_F2dbfd8df_D_00152C2A = 0;
}
extern char LVL_7_SIBERIUS_F0a1df9d9_D_001A8F20[] __attribute__((sda));
extern void LVL_7_SIBERIUS_F0a1df9d9_FUN_00307940(int a, int b, void *c);
extern int LVL_7_SIBERIUS_F0a1df9d9_FUN_003A2ED0(int a, void *b, int c, char *d, float e, float f, float g, float h);
void LVL_7_SIBERIUS_FUN_0039C880(int a0)
{
    int buf[4];
    int s0;
    int v;

    s0 = *(int *)(a0 + 104);
    LVL_7_SIBERIUS_F0a1df9d9_FUN_00307940(a0, 0, buf);
    v = LVL_7_SIBERIUS_F0a1df9d9_FUN_003A2ED0(a0, buf, *(int *)(s0 + 16), LVL_7_SIBERIUS_F0a1df9d9_D_001A8F20, *(float *)(s0 + 24), 2.0f, 5.0f, 0.6f);
    if (v != 0) {
        *(int *)(v + 184) = a0;
    }
}
#ifndef RAC2_T_V4_FB6552688
#define RAC2_T_V4_FB6552688
typedef int V4_Fb6552688 __attribute__((mode(TI)));
#endif


extern char *LVL_7_SIBERIUS_Fb6552688_FUN_0035D5B0(char *);
extern void LVL_7_SIBERIUS_Fb6552688_FUN_002E45F0(V4_Fb6552688 *, char *, float);
extern void LVL_7_SIBERIUS_Fb6552688_FUN_002E4310(char *, V4_Fb6552688 *, char *);
extern void LVL_7_SIBERIUS_Fb6552688_FUN_0035E8B0(char *);

void LVL_7_SIBERIUS_FUN_0035E7D8(char *a0)
{
    V4_Fb6552688 buf;
    char *p;

    p = LVL_7_SIBERIUS_Fb6552688_FUN_0035D5B0(a0);
    if (p == 0)
        return;
    LVL_7_SIBERIUS_Fb6552688_FUN_002E45F0(&buf, a0 + 192, 8.0f);
    LVL_7_SIBERIUS_Fb6552688_FUN_002E4310(p + 96, &buf, a0 + 16);
    LVL_7_SIBERIUS_Fb6552688_FUN_0035E8B0(a0);
    *(int *)(p + 304) = 300;
}
extern void LVL_7_SIBERIUS_Fe824cd8c_FUN_004277E0(char *);
extern void LVL_7_SIBERIUS_Fe824cd8c_FUN_004277E0(char *);
extern void LVL_7_SIBERIUS_Fe824cd8c_FUN_004277E0(char *);
extern void LVL_7_SIBERIUS_Fe824cd8c_FUN_004277E0(char *);
extern void LVL_7_SIBERIUS_Fe824cd8c_FUN_00427F38(char *);
extern void LVL_7_SIBERIUS_Fe824cd8c_FUN_00432F10(char *);
extern void LVL_7_SIBERIUS_Fe824cd8c_FUN_00432F30(char *);
extern void LVL_7_SIBERIUS_Fe824cd8c_FUN_00432F50(char *);

void LVL_7_SIBERIUS_FUN_004330E8(char *a0)
{
    if (*(int *)(a0 + 544) == 0)
        return;
    LVL_7_SIBERIUS_Fe824cd8c_FUN_004277E0(a0);
    LVL_7_SIBERIUS_Fe824cd8c_FUN_004277E0(a0 + 152);
    LVL_7_SIBERIUS_Fe824cd8c_FUN_004277E0(a0 + 76);
    LVL_7_SIBERIUS_Fe824cd8c_FUN_004277E0(a0 + 228);
    LVL_7_SIBERIUS_Fe824cd8c_FUN_00427F38(a0 + 464);
    LVL_7_SIBERIUS_Fe824cd8c_FUN_00432F10(a0);
    LVL_7_SIBERIUS_Fe824cd8c_FUN_00432F30(a0);
    LVL_7_SIBERIUS_Fe824cd8c_FUN_00432F50(a0);
}
extern int LVL_7_SIBERIUS_F18321eff_D_001A79F0 __attribute__((sda));
extern int LVL_7_SIBERIUS_F18321eff_FUN_002CC758(int);
int LVL_7_SIBERIUS_FUN_002A7068(void)
{
    int v = LVL_7_SIBERIUS_F18321eff_D_001A79F0;
    int r = 0;
    if (v >= 8) {
        if (v < 10 || v == 19) {
            if (LVL_7_SIBERIUS_F18321eff_FUN_002CC758(1) != 0 || LVL_7_SIBERIUS_F18321eff_FUN_002CC758(2) != 0)
                r = 1;
        }
    }
    return r;
}
extern void LVL_7_SIBERIUS_F20b0faf7_FUN_002C9CA8(int, int);
extern void LVL_7_SIBERIUS_F20b0faf7_FUN_002C9C18(int, int, float);
extern void LVL_7_SIBERIUS_F20b0faf7_FUN_002C9B88(int, int);
extern void LVL_7_SIBERIUS_F20b0faf7_FUN_002C9B08(int, int, float);

void LVL_7_SIBERIUS_FUN_002B1A80(int a, int b, float x, float y)
{
    if (b != 0) {
        LVL_7_SIBERIUS_F20b0faf7_FUN_002C9CA8(a, a);
        LVL_7_SIBERIUS_F20b0faf7_FUN_002C9C18(a, a, y);
    } else {
        LVL_7_SIBERIUS_F20b0faf7_FUN_002C9B88(a, a);
        LVL_7_SIBERIUS_F20b0faf7_FUN_002C9B08(a, a, y);
    }
}
extern float LVL_7_SIBERIUS_F5ff747c4_FUN_002E5460(int);

float LVL_7_SIBERIUS_FUN_0031C8B0(int a0, int a1)
{
    float r = LVL_7_SIBERIUS_F5ff747c4_FUN_002E5460(a0 % a1);
    float s = LVL_7_SIBERIUS_F5ff747c4_FUN_002E5460(a1);

    return 2.0f * r * 3.1415927f / s - 3.1415927f;
}
extern void LVL_7_SIBERIUS_Fac72d004_FUN_0043AAF8(char *, int);
extern void LVL_7_SIBERIUS_Fac72d004_FUN_0043AAF8(char *, int);
extern void LVL_7_SIBERIUS_Fac72d004_FUN_0043AAF8(char *, int);
extern void LVL_7_SIBERIUS_Fac72d004_FUN_0043AAF8(char *, int);

void LVL_7_SIBERIUS_FUN_0043C4C8(char *p, int a1)
{
    *(int *)(p + 1012) = a1;
    if (*(int *)(p + 1024) == 0)
        return;
    *(int *)(p + 1024) = 0;
    *(int *)(p + 12) = 1;
    LVL_7_SIBERIUS_Fac72d004_FUN_0043AAF8(p + 468, 1);
    LVL_7_SIBERIUS_Fac72d004_FUN_0043AAF8(p + 604, 1);
    LVL_7_SIBERIUS_Fac72d004_FUN_0043AAF8(p + 740, 1);
    LVL_7_SIBERIUS_Fac72d004_FUN_0043AAF8(p + 876, 1);
}
extern int LVL_7_SIBERIUS_Fd1d0f3f8_FUN_002DF0D8(char *, int);

void LVL_7_SIBERIUS_FUN_004292F0(char *p, int a1, int a2, float f12, float f13)
{
    char *q = p + 168;

    *(float *)(*(int *)p) = f12;
    *(float *)(*(int *)p + 4) = f13;
    p[423] = 0;
    *(int *)(p + 440) = a2;
    *(int *)(p + 472) = (int)q;
    *(int *)(p + 468) = LVL_7_SIBERIUS_Fd1d0f3f8_FUN_002DF0D8(q, -1);
    *(int *)(p + 432) = 1;
    *(float *)(*(int *)(p + 4)) = 1.0f;
}
extern void LVL_7_SIBERIUS_Fe2589056_FUN_002ED080(char *, int);

void LVL_7_SIBERIUS_FUN_002ECF08(char *p)
{
    int fp;

    LVL_7_SIBERIUS_Fe2589056_FUN_002ED080(p, *(int *)(p + 32));
    fp = *(int *)(p + 48);
    *(int *)(p + 4) = *(int *)(p + 36);
    *(int *)(p + 20) = *(int *)(p + 52);
    *(int *)(p + 24) = *(int *)(p + 56);
    *(int *)(p + 12) = *(int *)(p + 44);
    *(int *)(p + 8) = *(int *)(p + 40);
    *(int *)(p + 16) = fp;
    if (fp != 0)
        ((void (*)(char *))fp)(p);
    *(int *)(p + 104) = 0;
}
extern int LVL_7_SIBERIUS_Fe8d026c6_FUN_0034D8E0(int);
extern int LVL_7_SIBERIUS_Fe8d026c6_FUN_0034DA90(int);
extern int LVL_7_SIBERIUS_Fe8d026c6_FUN_00338FA0(void);
extern int LVL_7_SIBERIUS_Fe8d026c6_FUN_002E9698(void);
extern int LVL_7_SIBERIUS_Fe8d026c6_FUN_0042AC28(int);
extern int LVL_7_SIBERIUS_Fe8d026c6_D_001A904C __attribute__((sda));

int LVL_7_SIBERIUS_FUN_0034BFF8(char *a0)
{
    int v;

    LVL_7_SIBERIUS_Fe8d026c6_FUN_0034D8E0(1);
    v = LVL_7_SIBERIUS_Fe8d026c6_FUN_0034DA90(0);
    *(int *)(a0 + 76) = 0;
    *(int *)(a0 + 72) = v;
    LVL_7_SIBERIUS_Fe8d026c6_FUN_00338FA0();
    LVL_7_SIBERIUS_Fe8d026c6_FUN_002E9698();
    v = *(int *)0x1A8FD8;
    if (v != 0) {
        v = LVL_7_SIBERIUS_Fe8d026c6_D_001A904C;
        if (v != 0) {
            LVL_7_SIBERIUS_Fe8d026c6_FUN_0042AC28(v + 0x3CAA8);
        }
    }
    return 0;
}


extern int LVL_7_SIBERIUS_F1c1f8608_FUN_002E4398(void *, void *, float);
extern int LVL_7_SIBERIUS_F1c1f8608_FUN_002E4310(void *, void *, void *);
extern int LVL_7_SIBERIUS_F1c1f8608_FUN_003263C0(void *);

void LVL_7_SIBERIUS_FUN_0032F488(char *a0)
{
    char *p = a0;
    char *q = p + 32;
    int v;

    LVL_7_SIBERIUS_F1c1f8608_FUN_002E4398(q, q, 0.975f);
    LVL_7_SIBERIUS_F1c1f8608_FUN_002E4310(p + 16, p + 16, q);
    *(float *)(p + 12) = *(float *)(p + 12) + 14700.0f;
    *(u8 *)(p + 8) = *(u8 *)(p + 8) + *(u8 *)(q + 16);
    v = *(int *)(p + 4) + 0xFE000000;
    *(int *)(p + 4) = v;
    if (v < 0) {
        LVL_7_SIBERIUS_F1c1f8608_FUN_003263C0(p);
    }
}
#ifndef RAC2_T_V4_F876460D6
#define RAC2_T_V4_F876460D6
typedef int V4_F876460d6 __attribute__((mode(TI)));
#endif


extern void LVL_7_SIBERIUS_F876460d6_FUN_002E42D8(char *p);
extern float LVL_7_SIBERIUS_F876460d6_FUN_002E49C8(float a, float b);
extern void LVL_7_SIBERIUS_F876460d6_FUN_002E4B90(char *dst, char *src);
extern void LVL_7_SIBERIUS_F876460d6_FUN_002E4F08(char *a, char *b, char *c);
extern float LVL_7_SIBERIUS_F876460d6_FUN_002E49C8(float a, float b);
extern void LVL_7_SIBERIUS_F876460d6_FUN_002E4BB0(char *dst, char *src);
extern void LVL_7_SIBERIUS_F876460d6_FUN_002E4F08(char *a, char *b, char *c);
extern float LVL_7_SIBERIUS_F876460d6_FUN_002E49C8(float a, float b);

void LVL_7_SIBERIUS_FUN_003152C0(float *src, float *out)
{
    V4_F876460d6 tmp[4];
    float m[16];
    float local[4];
    float a, b, c;

    *(V4_F876460d6 *)(m + 0) = *(V4_F876460d6 *)(src + 0);
    *(V4_F876460d6 *)(m + 4) = *(V4_F876460d6 *)(src + 4);
    *(V4_F876460d6 *)(m + 8) = *(V4_F876460d6 *)(src + 8);
    *(V4_F876460d6 *)(m + 12) = *(V4_F876460d6 *)(src + 12);
    LVL_7_SIBERIUS_F876460d6_FUN_002E42D8((char *)(m + 12));
    m[15] = 1.0f;
    a = LVL_7_SIBERIUS_F876460d6_FUN_002E49C8(m[0], m[1]);
    local[0] = 0.0f;
    local[1] = 0.0f;
    local[2] = -a;
    LVL_7_SIBERIUS_F876460d6_FUN_002E4B90((char *)tmp, (char *)local);
    LVL_7_SIBERIUS_F876460d6_FUN_002E4F08((char *)m, (char *)tmp, (char *)m);
    b = LVL_7_SIBERIUS_F876460d6_FUN_002E49C8(m[0], -m[2]);
    local[0] = 0.0f;
    local[2] = 0.0f;
    local[1] = -b;
    LVL_7_SIBERIUS_F876460d6_FUN_002E4BB0((char *)tmp, (char *)local);
    LVL_7_SIBERIUS_F876460d6_FUN_002E4F08((char *)m, (char *)tmp, (char *)m);
    c = LVL_7_SIBERIUS_F876460d6_FUN_002E49C8(m[5], m[6]);
    out[2] = a;
    out[1] = b;
    out[0] = c;
    local[1] = 0.0f;
    local[0] = -c;
    local[2] = 0.0f;
}
extern int LVL_7_SIBERIUS_F9a4b4d8b_FUN_002E3FB0(char *);
extern void LVL_7_SIBERIUS_F9a4b4d8b_FUN_003263C0(char *);
extern void LVL_7_SIBERIUS_F9a4b4d8b_FUN_002E4310(char *, char *, char *);
extern void LVL_7_SIBERIUS_F9a4b4d8b_FUN_00375A78(char *, char *);

#ifndef RAC2_T_VEC16_F9A4B4D8B
#define RAC2_T_VEC16_F9A4B4D8B
typedef struct {
    float f[4];
} Vec16_F9a4b4d8b;
#endif


void LVL_7_SIBERIUS_FUN_00334360(char *obj)
{
    Vec16_F9a4b4d8b local;
    char *s1;
    char *s2;
    int a;
    int v1;

    if (LVL_7_SIBERIUS_F9a4b4d8b_FUN_002E3FB0(obj + 10) != 0) {
        LVL_7_SIBERIUS_F9a4b4d8b_FUN_003263C0(obj);
        return;
    }

    a = *(int *)(obj + 4);
    s1 = obj + 32;
    *(int *)(obj + 4) = (a & 0x00ffffff) | (((a >> 24) + *(unsigned char *)(s1 + 20)) << 24);

    s2 = obj + 16;
    local.f[0] = *(float *)(obj + 32);
    local.f[1] = *(float *)(s1 + 4);
    local.f[2] = *(float *)(s1 + 8);
    local.f[3] = 0.0f;
    LVL_7_SIBERIUS_F9a4b4d8b_FUN_002E4310(s2, s2, (char *)&local);

    *(float *)(s1 + 8) = *(float *)(s1 + 8) - *(float *)(s1 + 12);

    if (*(float *)(obj + 28) != 0.0f) {
        if (*(float *)(obj + 28) == 2.0f)
            LVL_7_SIBERIUS_F9a4b4d8b_FUN_00375A78(s2, s2);
        *(float *)(obj + 28) = 2.0f;
    }
    v1 = *(unsigned char *)(s1 + 21);

    *(unsigned char *)(obj + 8) = *(unsigned char *)(obj + 8) + v1;
    *(float *)(obj + 12) += *(float *)(s1 + 16);
}
extern void LVL_7_SIBERIUS_F187f348a_FUN_002E45F0(char *, char *, float);
extern void LVL_7_SIBERIUS_F187f348a_FUN_002E4440(char *, char *, char *);
extern void LVL_7_SIBERIUS_F187f348a_FUN_002E45F0(char *, char *, float);
extern void LVL_7_SIBERIUS_F187f348a_FUN_002E4440(char *, char *, char *);

void LVL_7_SIBERIUS_FUN_0039F570(char *obj, char *arg)
{
    char *base = obj + 192;
    char *other = obj + 208;
    float one = 1.0f;

    LVL_7_SIBERIUS_F187f348a_FUN_002E45F0(base, (char *)(*(int *)(obj + 104)), one);
    LVL_7_SIBERIUS_F187f348a_FUN_002E4440(other, base, arg);
    LVL_7_SIBERIUS_F187f348a_FUN_002E45F0(other, other, one);
    LVL_7_SIBERIUS_F187f348a_FUN_002E4440(obj + 224, other, base);
}
extern void LVL_7_SIBERIUS_F187f348a_FUN_002E45F0(char *, char *, float);
extern void LVL_7_SIBERIUS_F187f348a_FUN_002E4440(char *, char *, char *);
extern void LVL_7_SIBERIUS_F187f348a_FUN_002E45F0(char *, char *, float);
extern void LVL_7_SIBERIUS_F187f348a_FUN_002E4440(char *, char *, char *);

void LVL_7_SIBERIUS_FUN_003E0650(char *obj, char *arg)
{
    char *base = obj + 192;
    char *other = obj + 208;
    float one = 1.0f;

    LVL_7_SIBERIUS_F187f348a_FUN_002E45F0(base, (char *)(*(int *)(obj + 104)), one);
    LVL_7_SIBERIUS_F187f348a_FUN_002E4440(other, base, arg);
    LVL_7_SIBERIUS_F187f348a_FUN_002E45F0(other, other, one);
    LVL_7_SIBERIUS_F187f348a_FUN_002E4440(obj + 224, other, base);
}
extern float LVL_7_SIBERIUS_F6417c3cd_FUN_002E5360(float, float);
extern float LVL_7_SIBERIUS_F6417c3cd_FUN_002E4280(float);
extern void LVL_7_SIBERIUS_F6417c3cd_FUN_002E5318(float, float);

void LVL_7_SIBERIUS_FUN_002CDBD0(char *obj, float p1, float p2, float p3, float p4, float p5)
{
    float r;
    float t;
    float d;
    float neg;

    r = LVL_7_SIBERIUS_F6417c3cd_FUN_002E5360(p2, p1);
    t = *(float *)obj;
    d = p3 * r - p4 * t;
    t = t + d;
    *(float *)obj = t;

    if (p5 != 0.0f) {
        if (t > p5) {
            *(float *)obj = p5;
        } else {
            neg = -p5;
            if (t < neg)
                *(float *)obj = neg;
        }
    }

    if (LVL_7_SIBERIUS_F6417c3cd_FUN_002E4280(r) < *(float *)obj) {
        *(float *)obj = LVL_7_SIBERIUS_F6417c3cd_FUN_002E4280(r);
    } else if (*(float *)obj < -LVL_7_SIBERIUS_F6417c3cd_FUN_002E4280(r)) {
        *(float *)obj = -LVL_7_SIBERIUS_F6417c3cd_FUN_002E4280(r);
    }

    LVL_7_SIBERIUS_F6417c3cd_FUN_002E5318(p1, *(float *)obj);
}
#ifndef RAC2_T_SRC_F66766F2B
#define RAC2_T_SRC_F66766F2B
typedef struct {
    char pad0[35];        /* 0   */
    unsigned char f35;    /* 35  */
    char pad36[8];        /* 36  */
    float f44;            /* 44  */
    unsigned char f48;    /* 48  */
    unsigned char f49;    /* 49  */
    unsigned short f50;   /* 50  */
    unsigned short f52;   /* 52  */
    char pad54[2];        /* 54  */
    long long f56;        /* 56  */
    char pad64[34];       /* 64  */
    unsigned char f98;    /* 98  */
    char pad99[21];       /* 99  */
    int f120;             /* 120 */
    unsigned short f124;  /* 124 */
    char pad126[26];      /* 126 */
    int f152;             /* 152 */
    char pad156[14];      /* 156 */
    short f170;           /* 170 */
} Src_F66766f2b;
#endif


#ifndef RAC2_T_LIST_F66766F2B
#define RAC2_T_LIST_F66766F2B
typedef struct {
    char pad0[256];       /* 0   */
    int a[4];             /* 256 */
    int b[4];             /* 272 */
    Src_F66766f2b *c[4];            /* 288 */
    float d[4];           /* 304 */
    int pad320;           /* 320 */
    Src_F66766f2b *src;             /* 324 */
    int count;            /* 328 */
} List_F66766f2b;
#endif


extern Src_F66766f2b *LVL_7_SIBERIUS_F66766f2b_FUN_00306498(short);

void LVL_7_SIBERIUS_FUN_00318CE8(List_F66766f2b *obj, int a1, int a2, float v)
{
    Src_F66766f2b *q;
    short n;

    if (obj->count == 4)
        return;
    if (a2 >= 9)
        return;

    q = LVL_7_SIBERIUS_F66766f2b_FUN_00306498(obj->src->f170);
    if (q == 0)
        return;

    n = q->f170;
    q->f124 = obj->src->f124;
    q->f50 = obj->src->f50;
    q->f56 = obj->src->f56;
    q->f44 = obj->src->f44;
    q->f120 = obj->src->f120;
    q->f49 = 1;
    q->f52 = 2058;
    q->f48 = 0;
    q->f152 = 0;
    if (n == 0)
        q->f98 = 0;
    q->f35 = a1;

    obj->b[obj->count] = a2;
    obj->a[obj->count] = a1;
    obj->d[obj->count] = v;
    obj->c[obj->count] = q;
    obj->count = obj->count + 1;
}
extern int LVL_7_SIBERIUS_F7b0b4597_FUN_00310AD8(int, int);
extern float LVL_7_SIBERIUS_F7b0b4597_FUN_00310B30(float, float);
extern float LVL_7_SIBERIUS_F7b0b4597_FUN_00310BF8(void);
extern void LVL_7_SIBERIUS_F7b0b4597_FUN_002E3438(char *, int, int, int, float, float, float);

void LVL_7_SIBERIUS_FUN_00399AE8(int p0, int p1, int p2, int p3, float v)
{
    int r;
    float s;
    float t;

    r = LVL_7_SIBERIUS_F7b0b4597_FUN_00310AD8(p3 >> 1, p3);
    p2 = p2 | (r << 24);
    s = LVL_7_SIBERIUS_F7b0b4597_FUN_00310B30(v * 0.75f, v);
    s = s + s;
    t = LVL_7_SIBERIUS_F7b0b4597_FUN_00310BF8();
    LVL_7_SIBERIUS_F7b0b4597_FUN_002E3438((char *)p1, 44, p2, 1, s, 0.08f, t);
}
extern int LVL_7_SIBERIUS_F7b0b4597_FUN_00310AD8(int, int);
extern float LVL_7_SIBERIUS_F7b0b4597_FUN_00310B30(float, float);
extern float LVL_7_SIBERIUS_F7b0b4597_FUN_00310BF8(void);
extern void LVL_7_SIBERIUS_F7b0b4597_FUN_002E3438(char *, int, int, int, float, float, float);

void LVL_7_SIBERIUS_FUN_003D4678(int p0, int p1, int p2, int p3, float v)
{
    int r;
    float s;
    float t;

    r = LVL_7_SIBERIUS_F7b0b4597_FUN_00310AD8(p3 >> 1, p3);
    p2 = p2 | (r << 24);
    s = LVL_7_SIBERIUS_F7b0b4597_FUN_00310B30(v * 0.75f, v);
    s = s + s;
    t = LVL_7_SIBERIUS_F7b0b4597_FUN_00310BF8();
    LVL_7_SIBERIUS_F7b0b4597_FUN_002E3438((char *)p1, 44, p2, 1, s, 0.08f, t);
}
#ifndef RAC2_T_V4_FC6BD459E
#define RAC2_T_V4_FC6BD459E
typedef int V4_Fc6bd459e __attribute__((mode(TI)));
#endif


extern void LVL_7_SIBERIUS_Fc6bd459e_FUN_002E4340(float *local, void *a1, void *a0);
extern float LVL_7_SIBERIUS_Fc6bd459e_FUN_002E4458(float *local);
extern void LVL_7_SIBERIUS_Fc6bd459e_FUN_00313C88(void *a2, float r, float f1, float f2, float f3);
extern void LVL_7_SIBERIUS_Fc6bd459e_FUN_002E45F0(float *local, float *local2, float v);
extern void LVL_7_SIBERIUS_Fc6bd459e_FUN_002E4310(void *a0, void *a0b, float *local);
extern float LVL_7_SIBERIUS_Fc6bd459e_FUN_002E4280(float t);

float LVL_7_SIBERIUS_FUN_00313F48(void *a0, void *a1, void *a2, float f1, float f2, float f3)
{
    float local[4];
    float r;
    float u;

    LVL_7_SIBERIUS_Fc6bd459e_FUN_002E4340(local, a1, a0);
    r = LVL_7_SIBERIUS_Fc6bd459e_FUN_002E4458(local);
    LVL_7_SIBERIUS_Fc6bd459e_FUN_00313C88(a2, r, f1, f2, f3);
    LVL_7_SIBERIUS_Fc6bd459e_FUN_002E45F0(local, local, *(float *)a2);
    LVL_7_SIBERIUS_Fc6bd459e_FUN_002E4310(a0, a0, local);
    r = r - *(float *)a2;
    u = LVL_7_SIBERIUS_Fc6bd459e_FUN_002E4280(r);
    if (!(u < f3 * 0.01f))
        return r;
    *(V4_Fc6bd459e *)a0 = *(V4_Fc6bd459e *)a1;
    *(float *)a2 = 0.0f;
    return *(float *)a2;
}
extern void  LVL_7_SIBERIUS_F856af239_FUN_0031A0B8(char *p, float a, float b, float c);
extern void  LVL_7_SIBERIUS_F856af239_FUN_002E4310(char *p, char *q, char *r);
extern int   LVL_7_SIBERIUS_F856af239_FUN_002D4510(void *a, void *b, int c, int d, int e);
extern void  LVL_7_SIBERIUS_F856af239_FUN_002C9690(void *p, int n, float a, float b, float c);
extern void  LVL_7_SIBERIUS_F856af239_FUN_002E4340(void *dst, void *src, void *arg);
extern float LVL_7_SIBERIUS_F856af239_FUN_002E49C8(float a, float b);
extern float LVL_7_SIBERIUS_F856af239_FUN_002E4488(void *p);
extern char  LVL_7_SIBERIUS_F856af239_D_001B90C0[];
extern char  LVL_7_SIBERIUS_F856af239_D_001BF660[];
extern char  LVL_7_SIBERIUS_F856af239_D_00189E20[];

int LVL_7_SIBERIUS_FUN_002B8250(void)
{
    char buf[48];
    char *base = LVL_7_SIBERIUS_F856af239_D_001B90C0;
    char *res;
    float v;

    LVL_7_SIBERIUS_F856af239_FUN_0031A0B8(buf, 10.0f, *(float *)(base + 344), -*(float *)(base + 340));
    LVL_7_SIBERIUS_F856af239_FUN_002E4310(buf, buf, base + 320);
    res = LVL_7_SIBERIUS_F856af239_D_00189E20;
    if (LVL_7_SIBERIUS_F856af239_FUN_002D4510(base + 320, buf, 4, *(int *)(res + 8848), 0)) {
        LVL_7_SIBERIUS_F856af239_FUN_002C9690(buf + 16, 1, 0.5f, 0.0f, 0.5f);
        LVL_7_SIBERIUS_F856af239_FUN_002E4340(buf + 32, LVL_7_SIBERIUS_F856af239_D_001BF660, buf + 16);
        v = LVL_7_SIBERIUS_F856af239_FUN_002E49C8(*(float *)(buf + 32), *(float *)(buf + 36));
        *(float *)(res + 3076) = v;
        v = LVL_7_SIBERIUS_F856af239_FUN_002E4488(buf + 32);
        *(float *)(res + 3080) = LVL_7_SIBERIUS_F856af239_FUN_002E49C8(v, *(float *)(buf + 40));
        return 1;
    }
    return 0;
}
#ifndef RAC2_T_V4_F0FBA48D3
#define RAC2_T_V4_F0FBA48D3
typedef int V4_F0fba48d3 __attribute__((mode(TI)));
#endif


extern void LVL_7_SIBERIUS_F0fba48d3_FUN_002E4340(void *b, void *c, void *d);
extern void LVL_7_SIBERIUS_F0fba48d3_FUN_002E45F0(void *dst, void *src, float x);
extern void LVL_7_SIBERIUS_F0fba48d3_FUN_002E4310(void *c, void *c2, void *s);
extern void LVL_7_SIBERIUS_F0fba48d3_FUN_002E4340(void *b, void *c, void *p);
extern void LVL_7_SIBERIUS_F0fba48d3_FUN_002E45F0(void *dst, void *src, float y);
extern void LVL_7_SIBERIUS_F0fba48d3_FUN_002E4310(void *b, void *p, void *s);
extern void LVL_7_SIBERIUS_F0fba48d3_FUN_002E4340(void *b, void *s, void *e);

void LVL_7_SIBERIUS_FUN_00420440(char *a0, void *a1, void *a2, void *a3,
                                      void *a4, float t0, float t1)
{
    V4_F0fba48d3 b0, b1, b2, b3;
    void *p = (void *)(*(int *)(a0 + 112));

    p = (void *)((int)p + 176);

    LVL_7_SIBERIUS_F0fba48d3_FUN_002E4340(&b0, a2, a3);
    LVL_7_SIBERIUS_F0fba48d3_FUN_002E45F0(&b1, &b0, t0);
    LVL_7_SIBERIUS_F0fba48d3_FUN_002E4310(a2, a2, &b1);
    LVL_7_SIBERIUS_F0fba48d3_FUN_002E4340(&b2, a2, p);
    LVL_7_SIBERIUS_F0fba48d3_FUN_002E45F0(&b2, &b2, t1);
    LVL_7_SIBERIUS_F0fba48d3_FUN_002E4310(&b3, p, &b2);
    LVL_7_SIBERIUS_F0fba48d3_FUN_002E4340(a1, &b3, a4);
}
extern float LVL_7_SIBERIUS_F21bf1d75_D_001A8900 __attribute__((sda));

extern void LVL_7_SIBERIUS_F21bf1d75_FUN_002E4340(float *out, char *a, char *b);
extern void LVL_7_SIBERIUS_F21bf1d75_FUN_002E4370(float *out, char *a, char *b, float k);
extern float LVL_7_SIBERIUS_F21bf1d75_FUN_002E4458(float *v);
extern void LVL_7_SIBERIUS_F21bf1d75_FUN_002E45F0(float *out, float *in, float k);

void LVL_7_SIBERIUS_FUN_00421D10(char *obj)
{
    char *p = *(char **)(obj + 112);
    char *r = p + 496;
    char *q = p + 352;
    float buf[4];
    float a, b, c;

    if (*(short *)(p + 16) <= 0) return;
    LVL_7_SIBERIUS_F21bf1d75_FUN_002E4340(buf, p, p + 176);
    LVL_7_SIBERIUS_F21bf1d75_FUN_002E4370((float *)q, q, (char *)buf, LVL_7_SIBERIUS_F21bf1d75_D_001A8900);
    a = LVL_7_SIBERIUS_F21bf1d75_FUN_002E4458((float *)q);
    b = *(float *)(q + 44);
    if (b < a) {
        a = b;
        LVL_7_SIBERIUS_F21bf1d75_FUN_002E45F0((float *)q, (float *)q, a);
        c = *(float *)(q + 44);
    } else {
        float d = b - *(float *)(r + 48);
        if (a < d) {
            a = d;
            LVL_7_SIBERIUS_F21bf1d75_FUN_002E45F0((float *)q, (float *)q, a);
        }
        c = *(float *)(q + 44);
    }
    *(float *)(r + 48) = c - a;
}
extern float LVL_7_SIBERIUS_F8629a204_FUN_002E4918(float x);
extern float LVL_7_SIBERIUS_F8629a204_FUN_002E4918(float x);
extern float LVL_7_SIBERIUS_F8629a204_FUN_002E4918(float x);
extern float LVL_7_SIBERIUS_F8629a204_FUN_002E4900(float x);
extern float LVL_7_SIBERIUS_F8629a204_FUN_002E5318(float x, float y);
extern float LVL_7_SIBERIUS_F8629a204_FUN_002E5318(float x, float y);

void LVL_7_SIBERIUS_FUN_003194E0(float *out, float *p, float *q,
                                        float k1, float k2, float k3)
{
    out[60] = k1 * LVL_7_SIBERIUS_F8629a204_FUN_002E4918(*p) * LVL_7_SIBERIUS_F8629a204_FUN_002E4918(*q);
    out[61] = k1 * LVL_7_SIBERIUS_F8629a204_FUN_002E4918(*p) * LVL_7_SIBERIUS_F8629a204_FUN_002E4900(*q);
    *p = LVL_7_SIBERIUS_F8629a204_FUN_002E5318(*p, k2);
    *q = LVL_7_SIBERIUS_F8629a204_FUN_002E5318(*q, k3);
}
extern char LVL_7_SIBERIUS_Fd653e601_D_00189E20[];

extern void LVL_7_SIBERIUS_Fd653e601_FUN_002E47F8(void *a, void *b, void *c);
extern void LVL_7_SIBERIUS_Fd653e601_FUN_002E47F8(void *a, void *b, void *c);

void LVL_7_SIBERIUS_FUN_002C9CA8(float *dst, void *src, float scale)
{
    char *d = LVL_7_SIBERIUS_Fd653e601_D_00189E20;
    int v = *(unsigned char *)(d + 8899);

    switch (v) {
    case 0:
        dst[0] = dst[0] * scale;
        dst[1] = dst[1] * scale;
        break;
    case 1:
    case 2:
        LVL_7_SIBERIUS_Fd653e601_FUN_002E47F8(dst, src, d + 64);
        dst[0] = dst[0] * scale;
        dst[1] = dst[1] * scale;
        LVL_7_SIBERIUS_Fd653e601_FUN_002E47F8(dst, dst, d);
        break;
    }

}
extern int LVL_7_SIBERIUS_F4aea17e5_FUN_002EA888 ();
extern void LVL_7_SIBERIUS_F4aea17e5_FUN_002DF518 (int v, int p7, long k, int r, int m1);
extern int LVL_7_SIBERIUS_F4aea17e5_FUN_002EA888 ();
extern void LVL_7_SIBERIUS_F4aea17e5_FUN_002DF9E8 (int v, int p7, long k, int r, int m1);

int LVL_7_SIBERIUS_FUN_003390C8 (int *p)
{
  int a = p[6];
  int t = p[8] >> 1;
  int diff = a - t;
  int sum = a + t;
  int r;

  r = LVL_7_SIBERIUS_F4aea17e5_FUN_002EA888 (4412);
  LVL_7_SIBERIUS_F4aea17e5_FUN_002DF518 (diff, p[7], (long) 0x80f0f0f0, r, -1);
  r = LVL_7_SIBERIUS_F4aea17e5_FUN_002EA888 (4408);
  LVL_7_SIBERIUS_F4aea17e5_FUN_002DF9E8 (sum, p[7], (long) 0x80f0f0f0, r, -1);
  return 0;
}
extern void LVL_7_SIBERIUS_F5979c03f_FUN_0042C2F0 (char *object);
extern void LVL_7_SIBERIUS_F5979c03f_FUN_0042C4E0 (char *object, float x, float y);
extern int LVL_7_SIBERIUS_F5979c03f_FUN_003555E8 (int a, int b, int c);

int LVL_7_SIBERIUS_FUN_0042EA68 (char *object, int flags)
{
  volatile unsigned char *g = (volatile unsigned char *) 0x1A7B96;
  float *vec;
  int discarded;

  LVL_7_SIBERIUS_F5979c03f_FUN_0042C2F0 (object + 8);
  vec = *(float **) (object + 684);
  LVL_7_SIBERIUS_F5979c03f_FUN_0042C4E0 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 680) == 0)
    {
      discarded = LVL_7_SIBERIUS_F5979c03f_FUN_003555E8 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}
extern void LVL_7_SIBERIUS_F9ebc9e57_FUN_002E4098 (char *node, int zero, int size);

void LVL_7_SIBERIUS_FUN_00307670 (char *list, char *node)
{
  char *cur;

  if (node == 0)
    return;

  if (*(char **) (list + 84) == node)
    {
      *(char **) (list + 84) = *(char **) (node + 8);
    }
  else if (*(char **) (list + 84) != 0)
    {
      cur = *(char **) (list + 84);
      while (*(char **) (cur + 8) != 0 && *(char **) (cur + 8) != node)
        cur = *(char **) (cur + 8);
      if (*(char **) (cur + 8) == node)
        *(char **) (cur + 8) = *(char **) (node + 8);
    }
  LVL_7_SIBERIUS_F9ebc9e57_FUN_002E4098 (node, 0, 64);
}
extern void LVL_7_SIBERIUS_Fac2822b7_FUN_002E4B08 (float *local);
extern void LVL_7_SIBERIUS_Fac2822b7_FUN_003766B0 (char *object, float a, float b, int flags, float d, float *local);

void LVL_7_SIBERIUS_FUN_00376570 (char *object, int flags, float a, float b, float c, float d)
{
  float local[16];

  if (flags >> 24)
    {
      c = c * *(float *) (object + 12);
      LVL_7_SIBERIUS_Fac2822b7_FUN_002E4B08 (local);
      local[0] = c;
      local[10] = c;
      LVL_7_SIBERIUS_Fac2822b7_FUN_003766B0 (object, a, b, flags, d, local);
    }
}
extern float LVL_7_SIBERIUS_Fff49167b_FUN_00314228 (float x, int a1, float y);
extern float LVL_7_SIBERIUS_Fff49167b_FUN_002E5318 (float x, float y);
extern float LVL_7_SIBERIUS_Fff49167b_FUN_00314228 (float x, int a1, float y);

void LVL_7_SIBERIUS_FUN_003142F0 (float *p, int a1, float fx, float fl)
{
  float v;

  v = LVL_7_SIBERIUS_Fff49167b_FUN_00314228 (fx, a1, p[0]);
  if (fl < v)
    v = fl;
  else if (v < -fl)
    v = -fl;
  v = LVL_7_SIBERIUS_Fff49167b_FUN_002E5318 (p[0], v);
  p[0] = v;
  LVL_7_SIBERIUS_Fff49167b_FUN_00314228 (fx, a1, v);
}
#ifndef RAC2_T_T16_FD6E0D08A
#define RAC2_T_T16_FD6E0D08A
typedef struct { float x; float y; int pad[2]; } T16_Fd6e0d08a;
#endif


extern void *LVL_7_SIBERIUS_Fd6e0d08a_FUN_00322878(void *, void *);
extern void LVL_7_SIBERIUS_Fd6e0d08a_FUN_00322EB0(void *, void *, int, int);
extern float LVL_7_SIBERIUS_Fd6e0d08a_FUN_002E49C8(float, float);
extern void LVL_7_SIBERIUS_Fd6e0d08a_FUN_00321BB0(void *, void *, float);
extern float LVL_7_SIBERIUS_Fd6e0d08a_FUN_002E4508(void *, void *);

int LVL_7_SIBERIUS_FUN_00322DA8(char *s1, char *s2)
{
    char *s0;
    float r;

    s0 = (char *)LVL_7_SIBERIUS_Fd6e0d08a_FUN_00322878(s1, s2);
    if (s0 == 0)
        return 0;
    if ((int)s2 != *(int *)(s0 + 196))
        LVL_7_SIBERIUS_Fd6e0d08a_FUN_00322EB0(s1, s2, -1, 0);
    r = LVL_7_SIBERIUS_Fd6e0d08a_FUN_002E49C8(((T16_Fd6e0d08a *)(s2 + (*(short *)(s0 + 200) << 4)))[1].x - ((T16_Fd6e0d08a *)s1)[1].x,
                ((T16_Fd6e0d08a *)(s2 + (*(short *)(s0 + 200) << 4)))[1].y - ((T16_Fd6e0d08a *)s1)[1].y);
    LVL_7_SIBERIUS_Fd6e0d08a_FUN_00321BB0(s1, &((T16_Fd6e0d08a *)s2)[*(short *)(s0 + 202) + 1], r);
    if (LVL_7_SIBERIUS_Fd6e0d08a_FUN_002E4508(&((T16_Fd6e0d08a *)s1)[1], &((T16_Fd6e0d08a *)s2)[*(short *)(s0 + 200) + 1])
        <= *(float *)(s0 + 52)) {
        if (*(short *)(s0 + 202) == *(short *)(s0 + 200))
            return 1;
        if (*(short *)(s0 + 202) < *(short *)(s0 + 200))
            *(short *)(s0 + 200) = (unsigned short)*(short *)(s0 + 200) - 1;
        else
            *(short *)(s0 + 200) = (unsigned short)*(short *)(s0 + 200) + 1;
    }
    return 0;
}
extern void LVL_7_SIBERIUS_F981a31f4_FUN_0030C708(char *a, int b, char *c, char *d);
extern void LVL_7_SIBERIUS_F981a31f4_FUN_002E4398(char *a, char *b, float f);
extern void LVL_7_SIBERIUS_F981a31f4_FUN_002E47D0(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F981a31f4_FUN_002E4310(char *a, char *b, char *c);

void LVL_7_SIBERIUS_FUN_00307940(char *a0, int a1, char *a2)
{
    char buf[80];
    float x;

    x = *(float *)(a0 + 44);
    *(int *)(buf + 64) = a1;
    x = x * 0.0009765625f;
    LVL_7_SIBERIUS_F981a31f4_FUN_0030C708(a0, 1, buf + 64, buf);
    LVL_7_SIBERIUS_F981a31f4_FUN_002E4398(a2, buf + 48, x);
    LVL_7_SIBERIUS_F981a31f4_FUN_002E47D0(a2, a2, a0 + 192);
    LVL_7_SIBERIUS_F981a31f4_FUN_002E4310(a2, a2, a0 + 16);
}
extern unsigned char LVL_7_SIBERIUS_F67dd0d3f_D_00189E20[];

extern void LVL_7_SIBERIUS_F67dd0d3f_FUN_002E4640(char *a, int b, float f);
extern void LVL_7_SIBERIUS_F67dd0d3f_FUN_002E47F8(char *a, char *b, char *c);

void LVL_7_SIBERIUS_FUN_002C9B88(char *a0, int a1, float f12)
{
    unsigned char *d = LVL_7_SIBERIUS_F67dd0d3f_D_00189E20;
    float f20;
    int v;

    f20 = f12;
    v = d[8899];
    if (v == 0) {
        LVL_7_SIBERIUS_F67dd0d3f_FUN_002E4640(a0, a1, f12);
        return;
    }
    if (v < 0)
        return;
    if (v >= 3)
        return;
    LVL_7_SIBERIUS_F67dd0d3f_FUN_002E47F8(a0, a1, (char *)d + 64);
    LVL_7_SIBERIUS_F67dd0d3f_FUN_002E4640(a0, a0, f20);
    LVL_7_SIBERIUS_F67dd0d3f_FUN_002E47F8(a0, a0, (char *)d);
}
extern char LVL_7_SIBERIUS_F280ccf7a_D_00189E20[];

extern int LVL_7_SIBERIUS_F280ccf7a_FUN_002C7D90(int, int *, int *);

void LVL_7_SIBERIUS_FUN_002C7EC8(void)
{
    char *d = LVL_7_SIBERIUS_F280ccf7a_D_00189E20;
    int a;
    int b;
    int *o;

    if (*(unsigned char *)(d + 8884) != 0)
        return;
    if (*(int *)(d + 4916) != 2)
        return;
    if (LVL_7_SIBERIUS_F280ccf7a_FUN_002C7D90(*(unsigned char *)(*(int *)(d + 8848) + 67), &a, &b) == 0)
        return;
    o = (int *)*(int *)(d + 4880);
    if (o != 0)
        *(float *)((char *)o + 72) = *(float *)(d + 3104);
    o = (int *)*(int *)(d + 4884);
    if (o != 0)
        *(float *)((char *)o + 72) = *(float *)(d + 3104);
}
#ifndef RAC2_T_S36_F39E097FB
#define RAC2_T_S36_F39E097FB
typedef struct { int w[9]; } S36_F39e097fb;
#endif


extern int LVL_7_SIBERIUS_F39e097fb_D_0018C0B0;
extern char LVL_7_SIBERIUS_F39e097fb_D_0018AA70[];
extern S36_F39e097fb LVL_7_SIBERIUS_F39e097fb_D_001A7F68;

extern void LVL_7_SIBERIUS_F39e097fb_FUN_00307A68(int, int, S36_F39e097fb *, char *);

void LVL_7_SIBERIUS_FUN_002A9F40(int a0)
{
    S36_F39e097fb buf;

    if (a0 == 0)
        a0 = LVL_7_SIBERIUS_F39e097fb_D_0018C0B0;
    buf = LVL_7_SIBERIUS_F39e097fb_D_001A7F68;
    LVL_7_SIBERIUS_F39e097fb_FUN_00307A68(a0, 9, &buf, LVL_7_SIBERIUS_F39e097fb_D_0018AA70);
}
extern void LVL_7_SIBERIUS_F7d9c8805_FUN_00427668(int);
extern void LVL_7_SIBERIUS_F7d9c8805_FUN_00427E28(int);
extern void LVL_7_SIBERIUS_F7d9c8805_FUN_00427E28(int);
extern void LVL_7_SIBERIUS_F7d9c8805_FUN_00427E28(int);

int LVL_7_SIBERIUS_FUN_0042C018(int a0)
{
	char *p = (char *)a0 + 12;
	int i;

	for (i = 4; i != -1; i--) {
		LVL_7_SIBERIUS_F7d9c8805_FUN_00427668(p);
		p += 76;
	}
	LVL_7_SIBERIUS_F7d9c8805_FUN_00427E28(a0 + 408);
	LVL_7_SIBERIUS_F7d9c8805_FUN_00427E28(a0 + 480);
	LVL_7_SIBERIUS_F7d9c8805_FUN_00427E28(a0 + 552);
	return a0;
}
extern void LVL_7_SIBERIUS_Fac6231ce_FUN_002E4340(float *, int, int);
extern void LVL_7_SIBERIUS_Fac6231ce_FUN_002E4E18(float *, int);
extern void LVL_7_SIBERIUS_Fac6231ce_FUN_002E47F8(float *, float *, float *);

float LVL_7_SIBERIUS_FUN_00314BD8(int a0, int a1, int a2, int a3)
{
	float v[24];
	float *m = v + 4;

	LVL_7_SIBERIUS_Fac6231ce_FUN_002E4340(v, a2, a0);
	LVL_7_SIBERIUS_Fac6231ce_FUN_002E4E18(v + 8, a1);
	LVL_7_SIBERIUS_Fac6231ce_FUN_002E47F8(m, v, v + 8);
	return m[a3];
}
extern int LVL_7_SIBERIUS_F09d4d860_FUN_003256C0(int, int, int *);
extern int LVL_7_SIBERIUS_F09d4d860_FUN_002E4268(int);

int LVL_7_SIBERIUS_FUN_00325760(int a0, int a1, int a2, int a3)
{
	int r = 0;
	int a;
	int b;

	if (LVL_7_SIBERIUS_F09d4d860_FUN_003256C0(a0, a2, &a)) {
		if (LVL_7_SIBERIUS_F09d4d860_FUN_003256C0(a1, a2, &b))
			r = LVL_7_SIBERIUS_F09d4d860_FUN_002E4268(a - b) < a3;
	}
	return r;
}
extern char LVL_7_SIBERIUS_F79501aca_D_0014B540[];
extern short LVL_7_SIBERIUS_F79501aca_D_00152CE4[];
void LVL_7_SIBERIUS_F79501aca_FUN_002FB020(int, int, int, int);

void LVL_7_SIBERIUS_FUN_002FB948(int id, int arg)
{
    int i;
    int *p = (int *)LVL_7_SIBERIUS_F79501aca_D_0014B540;

    for (i = 0; i < 48; i++) {
        if (p[i * 5 + 4816] == id)
            break;
    }
    if (i != 48) {
        LVL_7_SIBERIUS_F79501aca_D_00152CE4[0] = (short)i;
        LVL_7_SIBERIUS_F79501aca_FUN_002FB020(i, -1, arg, 1);
    }
}
extern int LVL_7_SIBERIUS_F1bd62089_D_001A904C __attribute__((sda));
extern int LVL_7_SIBERIUS_F1bd62089_FUN_00432D88(int a, int b);

int LVL_7_SIBERIUS_FUN_00303988(int a0)
{
    int v = LVL_7_SIBERIUS_F1bd62089_D_001A904C;

    if (v != 0) {
        return LVL_7_SIBERIUS_F1bd62089_FUN_00432D88(v + 0x3BE08, a0);
    }
    return 0;
}
extern int LVL_7_SIBERIUS_F1bd62089_D_001A904C __attribute__((sda));
extern int LVL_7_SIBERIUS_F1bd62089_FUN_00432D88(int a, int b);

int LVL_7_SIBERIUS_FUN_003039F8(int a0)
{
    int v = LVL_7_SIBERIUS_F1bd62089_D_001A904C;

    if (v != 0) {
        return LVL_7_SIBERIUS_F1bd62089_FUN_00432D88(v + 0x3BE08, a0);
    }
    return 0;
}
extern int LVL_7_SIBERIUS_Fbd51b1fa_D_001A904C __attribute__((sda));
extern int LVL_7_SIBERIUS_Fbd51b1fa_FUN_00429C68(int a, int b, int c);

int LVL_7_SIBERIUS_FUN_00304130(int a0, int a1)
{
    int v = LVL_7_SIBERIUS_Fbd51b1fa_D_001A904C;

    if (v == 0) return a0;
    return LVL_7_SIBERIUS_Fbd51b1fa_FUN_00429C68(v + 0x36F28, a0, a1);
}
extern int LVL_7_SIBERIUS_Fbd51b1fa_D_001A904C __attribute__((sda));
extern int LVL_7_SIBERIUS_Fbd51b1fa_FUN_00429500(int a, int b, int c);

int LVL_7_SIBERIUS_FUN_00304170(int a0, int a1)
{
    int v = LVL_7_SIBERIUS_Fbd51b1fa_D_001A904C;

    if (v == 0) return a0;
    return LVL_7_SIBERIUS_Fbd51b1fa_FUN_00429500(v + 0x36F28, a0, a1);
}
extern void LVL_7_SIBERIUS_Ffee684c2_FUN_00371440(int);
extern void LVL_7_SIBERIUS_Ffee684c2_FUN_002E5838(void);
extern void LVL_7_SIBERIUS_Ffee684c2_FUN_002E5AA0(int, int, int, int, int, int);
extern void LVL_7_SIBERIUS_Ffee684c2_FUN_002E5AA0(int, int, int, int, int, int);

void LVL_7_SIBERIUS_FUN_002E6FD0(void)
{
    LVL_7_SIBERIUS_Ffee684c2_FUN_00371440(1);
    LVL_7_SIBERIUS_Ffee684c2_FUN_002E5838();
    if (*(int *)0x001A7BB8 != 0)
        LVL_7_SIBERIUS_Ffee684c2_FUN_002E5AA0(512, 416, 640, 448, 0, 0);
    else
        LVL_7_SIBERIUS_Ffee684c2_FUN_002E5AA0(512, 416, 512, 448, 0, 0);
}
extern char LVL_7_SIBERIUS_Fcc134e7e_D_00189E20[];
extern void LVL_7_SIBERIUS_Fcc134e7e_FUN_00306800(int);

struct S {
    char pad[52];
    unsigned short flags;
};

void LVL_7_SIBERIUS_FUN_002C2DC8(void)
{
    char *g = LVL_7_SIBERIUS_Fcc134e7e_D_00189E20;
    int v;
    struct S *p;
    struct S *q;

    v = *(int *)(g + 6228);
    if (v != 0) {
        LVL_7_SIBERIUS_Fcc134e7e_FUN_00306800(v);
        *(int *)(g + 6228) = 0;
    }
    p = *(struct S **)(g + 4880);
    if (p != 0)
        p->flags &= ~0x41;
    q = *(struct S **)(g + 4884);
    if (q != 0)
        q->flags &= ~0x41;
}
extern void LVL_7_SIBERIUS_F10bf3d29_FUN_002E4E18(char *a, char *b);
extern void LVL_7_SIBERIUS_F10bf3d29_FUN_002E47D0(char *a, char *b, char *c);
extern void LVL_7_SIBERIUS_F10bf3d29_FUN_002E47D0(char *a, char *b, char *c);

void LVL_7_SIBERIUS_FUN_0031B090(char *a0, char *a1, char *a2, char *a3)
{
    char buf[64];

    if (a3 == 0) {
        LVL_7_SIBERIUS_F10bf3d29_FUN_002E4E18(buf, a0 + 192);
        LVL_7_SIBERIUS_F10bf3d29_FUN_002E47D0(a1, a2, buf);
    } else {
        LVL_7_SIBERIUS_F10bf3d29_FUN_002E47D0(a1, a2, a3);
    }
}
extern void LVL_7_SIBERIUS_F3b16bab7_FUN_004277E0(char *a);
extern void LVL_7_SIBERIUS_F3b16bab7_FUN_004277E0(char *a);
extern void LVL_7_SIBERIUS_F3b16bab7_FUN_004277E0(char *a);
extern void LVL_7_SIBERIUS_F3b16bab7_FUN_004277E0(char *a);
extern void LVL_7_SIBERIUS_F3b16bab7_FUN_00427F38(char *a);
extern void LVL_7_SIBERIUS_F3b16bab7_FUN_00427F38(char *a);
extern void LVL_7_SIBERIUS_F3b16bab7_FUN_00427F38(char *a);

void LVL_7_SIBERIUS_FUN_0042AA58(char *a0)
{
    if (*(int *)(a0 + 664) == 0)
        return;
    LVL_7_SIBERIUS_F3b16bab7_FUN_004277E0(a0 + 8);
    LVL_7_SIBERIUS_F3b16bab7_FUN_004277E0(a0 + 84);
    LVL_7_SIBERIUS_F3b16bab7_FUN_004277E0(a0 + 160);
    LVL_7_SIBERIUS_F3b16bab7_FUN_004277E0(a0 + 236);
    LVL_7_SIBERIUS_F3b16bab7_FUN_00427F38(a0 + 312);
    LVL_7_SIBERIUS_F3b16bab7_FUN_00427F38(a0 + 384);
    LVL_7_SIBERIUS_F3b16bab7_FUN_00427F38(a0 + 456);
}
extern int LVL_7_SIBERIUS_F489adc25_FUN_002E9EE0(int a, char *b);
extern void LVL_7_SIBERIUS_F489adc25_FUN_002E9C00(int a);

void LVL_7_SIBERIUS_FUN_002F29F0(char *a0)
{
    int i;

    for (i = 0; i < 56; i++) {
        if (LVL_7_SIBERIUS_F489adc25_FUN_002E9EE0(i, a0) == 0)
            continue;
        if (i != 0)
            LVL_7_SIBERIUS_F489adc25_FUN_002E9C00(i);
    }
}
extern int LVL_7_SIBERIUS_F4f96b231_FUN_002EA888(int a);
extern void LVL_7_SIBERIUS_F4f96b231_FUN_00427EF8(char *a, int b);

void LVL_7_SIBERIUS_FUN_00439B08(char *a0, int a1, int *a2)
{
    int i;

    *(int *)(a0 + 1092) = a1;
    for (i = 0; i < a1; i++)
        LVL_7_SIBERIUS_F4f96b231_FUN_00427EF8(a0 + 536 + i * 72, LVL_7_SIBERIUS_F4f96b231_FUN_002EA888(a2[i]));
}
extern float LVL_7_SIBERIUS_F77438389_FUN_002E4918(float x);
extern void LVL_7_SIBERIUS_F77438389_FUN_002E4398(void *a0, int a1, float x);
extern float LVL_7_SIBERIUS_F77438389_FUN_002E4900(float x);

void LVL_7_SIBERIUS_FUN_00315158(void *a0, int a1, float x)
{
    float h = x * 0.5f;
    float t = LVL_7_SIBERIUS_F77438389_FUN_002E4918(h);

    LVL_7_SIBERIUS_F77438389_FUN_002E4398(a0, a1, t);
    *(float *)((char *)a0 + 12) = LVL_7_SIBERIUS_F77438389_FUN_002E4900(h);
}
extern int LVL_7_SIBERIUS_F8fdb4153_FUN_00443400(void *a0);

int LVL_7_SIBERIUS_FUN_00443410(volatile int *a0)
{
    int d, n;

    if (LVL_7_SIBERIUS_F8fdb4153_FUN_00443400((void *)a0) != 0)
        return 0;
    d = a0[2] - a0[3];
    n = a0[4];
    d = d + n;
    return a0[1] + (d % n) * 0x138c0;
}
extern void LVL_7_SIBERIUS_Fabac7e02_FUN_00427668(void *p);
extern void LVL_7_SIBERIUS_Fabac7e02_FUN_00427668(void *p);
extern void LVL_7_SIBERIUS_Fabac7e02_FUN_00427668(void *p);
extern void LVL_7_SIBERIUS_Fabac7e02_FUN_00427668(void *p);
extern void LVL_7_SIBERIUS_Fabac7e02_FUN_00427E28(void *p);
extern void LVL_7_SIBERIUS_Fabac7e02_FUN_00427E28(void *p);
extern void LVL_7_SIBERIUS_Fabac7e02_FUN_00427E28(void *p);
extern void LVL_7_SIBERIUS_Fabac7e02_FUN_00427E28(void *p);

void *LVL_7_SIBERIUS_FUN_0042A4D0(char *a0)
{
    LVL_7_SIBERIUS_Fabac7e02_FUN_00427668(a0 + 8);
    LVL_7_SIBERIUS_Fabac7e02_FUN_00427668(a0 + 84);
    LVL_7_SIBERIUS_Fabac7e02_FUN_00427668(a0 + 160);
    LVL_7_SIBERIUS_Fabac7e02_FUN_00427668(a0 + 236);
    LVL_7_SIBERIUS_Fabac7e02_FUN_00427E28(a0 + 312);
    LVL_7_SIBERIUS_Fabac7e02_FUN_00427E28(a0 + 384);
    LVL_7_SIBERIUS_Fabac7e02_FUN_00427E28(a0 + 456);
    LVL_7_SIBERIUS_Fabac7e02_FUN_00427E28(a0 + 528);
    return a0;
}
extern void LVL_7_SIBERIUS_Fce0d9a7a_FUN_00428390(int a, int b);

void LVL_7_SIBERIUS_FUN_00427370(char *a0, int a1)
{
    if (a1 != *(int *)(a0 + 4)) {
        if (*(int *)(a0 + 44) != 0 && *(int *)(a0 + 24) == 0) {
            LVL_7_SIBERIUS_Fce0d9a7a_FUN_00428390(*(int *)(a0 + 44), *(int *)(a0 + 4));
            *(int *)(a0 + 24) = 1;
        }
        *(int *)(a0 + 4) = a1;
    }
}
extern int LVL_7_SIBERIUS_F0a35c0b5_FUN_002CC738(void);
extern int LVL_7_SIBERIUS_F0a35c0b5_D_0018C0B4;

int LVL_7_SIBERIUS_FUN_002CC830(void)
{
    int result = 0;
    int mode;
    if (LVL_7_SIBERIUS_F0a35c0b5_FUN_002CC738() != 0) goto out;
    if (LVL_7_SIBERIUS_F0a35c0b5_D_0018C0B4 != 49) goto out;
    mode = *(int *)0x001A79F0;
    if (mode != 4 && mode != 11) goto out;
    result = 1;
out:
    return result;
}
extern void LVL_7_SIBERIUS_Fc2cf0de2_FUN_00422AC8(int);
extern void LVL_7_SIBERIUS_Fc2cf0de2_FUN_00421D10(int);
extern void LVL_7_SIBERIUS_Fc2cf0de2_FUN_00421818(int, float *, float *);
extern void LVL_7_SIBERIUS_Fc2cf0de2_FUN_00421998(int, float, float);
extern void LVL_7_SIBERIUS_Fc2cf0de2_FUN_00420C40(int);
extern void LVL_7_SIBERIUS_Fc2cf0de2_FUN_00422550(int);
extern void LVL_7_SIBERIUS_Fc2cf0de2_FUN_00421DE0(int);

void LVL_7_SIBERIUS_FUN_00422BC0(int object)
{
    float x;
    float y;

    LVL_7_SIBERIUS_Fc2cf0de2_FUN_00422AC8(object);
    LVL_7_SIBERIUS_Fc2cf0de2_FUN_00421D10(object);
    LVL_7_SIBERIUS_Fc2cf0de2_FUN_00421818(object, &x, &y);
    LVL_7_SIBERIUS_Fc2cf0de2_FUN_00421998(object, x, y);
    LVL_7_SIBERIUS_Fc2cf0de2_FUN_00420C40(object);
    LVL_7_SIBERIUS_Fc2cf0de2_FUN_00422550(object);
    LVL_7_SIBERIUS_Fc2cf0de2_FUN_00421DE0(object);
}
extern void LVL_7_SIBERIUS_Fd59cca7a_D_00115AC0(void *, int, int);
extern void LVL_7_SIBERIUS_Fd59cca7a_FUN_00429358(void *, int, int, float, float);

void LVL_7_SIBERIUS_FUN_00429C68(int object, int value, int count)
{
    int limit = (count == -1) ? 180 : count;
    int inner = object + 7532;

    LVL_7_SIBERIUS_Fd59cca7a_D_00115AC0((void *)(object + 7700), value, 254);
    LVL_7_SIBERIUS_Fd59cca7a_FUN_00429358((void *)inner, 1, limit, 255.0f, 123.0f);
}
extern void LVL_7_SIBERIUS_Fe68884be_D_00115AC0(void *, int, int);
extern void LVL_7_SIBERIUS_Fe68884be_FUN_00429358(void *, int, int, float, float);

void LVL_7_SIBERIUS_FUN_00429500(int object, int value, int count)
{
    int limit = (count == -1) ? 360 : count;
    int inner = object + 8124;

    LVL_7_SIBERIUS_Fe68884be_D_00115AC0((void *)(object + 8292), value, 255);
    LVL_7_SIBERIUS_Fe68884be_FUN_00429358((void *)inner, 1, limit, 255.0f, 80.0f);
}
extern void LVL_7_SIBERIUS_F076896f4_FUN_0043AF80(void *, int);
extern void LVL_7_SIBERIUS_F076896f4_FUN_0043AF80(void *, int);
extern void LVL_7_SIBERIUS_F076896f4_FUN_0043AF80(void *, int);
extern void LVL_7_SIBERIUS_F076896f4_FUN_0043AF80(void *, int);

void LVL_7_SIBERIUS_FUN_0043E2F0(int *self, int value)
{
    self[1371] = value;
    if (self[1372] != 0) {
        self[1372] = 0;
        LVL_7_SIBERIUS_F076896f4_FUN_0043AF80((char *)self + 4596, 0);
        LVL_7_SIBERIUS_F076896f4_FUN_0043AF80((char *)self + 4744, 0);
        LVL_7_SIBERIUS_F076896f4_FUN_0043AF80((char *)self + 4892, 0);
        LVL_7_SIBERIUS_F076896f4_FUN_0043AF80((char *)self + 5040, 0);
    }
}


extern void LVL_7_SIBERIUS_F4c55616a_FUN_00427668(u8 *);
extern void LVL_7_SIBERIUS_F4c55616a_FUN_00427B90(u8 *);
extern void LVL_7_SIBERIUS_F4c55616a_FUN_00427E28(u8 *);
extern void LVL_7_SIBERIUS_F4c55616a_FUN_00433C78(u8 *);

u8 *LVL_7_SIBERIUS_FUN_004346C8(u8 *a0) {
    LVL_7_SIBERIUS_F4c55616a_FUN_00427668(a0);
    LVL_7_SIBERIUS_F4c55616a_FUN_00427668(a0 + 76);
    LVL_7_SIBERIUS_F4c55616a_FUN_00427668(a0 + 152);
    LVL_7_SIBERIUS_F4c55616a_FUN_00427B90(a0 + 228);
    LVL_7_SIBERIUS_F4c55616a_FUN_00427E28(a0 + 432);
    LVL_7_SIBERIUS_F4c55616a_FUN_00427E28(a0 + 504);
    LVL_7_SIBERIUS_F4c55616a_FUN_00427E28(a0 + 576);
    LVL_7_SIBERIUS_F4c55616a_FUN_00433C78(a0 + 664);
    return a0;
}

#ifndef RAC2_T_S16_F570CFB4B
#define RAC2_T_S16_F570CFB4B
typedef short s16_F570cfb4b;
#endif



extern void LVL_7_SIBERIUS_F570cfb4b_FUN_003263C0(u8 *);

void LVL_7_SIBERIUS_FUN_003320B0(u8 *a0) {
    s16_F570cfb4b *p = (s16_F570cfb4b *)(a0 + 10);
    if (--*p == 0) {
        *(s32 *)(a0 + 4) += 0xff000000;
        *p = 2;
    }
    if ((*(s32 *)(a0 + 4) & 0xff000000) == 0) {
        LVL_7_SIBERIUS_F570cfb4b_FUN_003263C0(a0);
    }
}


extern void LVL_7_SIBERIUS_F65f0250b_FUN_00427668(u8 *);
extern void LVL_7_SIBERIUS_F65f0250b_FUN_00427B90(u8 *);
extern void LVL_7_SIBERIUS_F65f0250b_FUN_00427E28(u8 *);
extern void LVL_7_SIBERIUS_F65f0250b_FUN_00439368(u8 *);

u8 *LVL_7_SIBERIUS_FUN_00432688(u8 *a0) {
    LVL_7_SIBERIUS_F65f0250b_FUN_00427668(a0);
    LVL_7_SIBERIUS_F65f0250b_FUN_00427668(a0 + 76);
    LVL_7_SIBERIUS_F65f0250b_FUN_00427668(a0 + 152);
    LVL_7_SIBERIUS_F65f0250b_FUN_00427668(a0 + 228);
    LVL_7_SIBERIUS_F65f0250b_FUN_00427668(a0 + 304);
    LVL_7_SIBERIUS_F65f0250b_FUN_00427B90(a0 + 380);
    LVL_7_SIBERIUS_F65f0250b_FUN_00427E28(a0 + 464);
    LVL_7_SIBERIUS_F65f0250b_FUN_00439368(a0 + 552);
    return a0;
}
extern void LVL_7_SIBERIUS_Fd179801d_FUN_00324E70(int);
extern int LVL_7_SIBERIUS_Fd179801d_FUN_00324CA8(char *, int, int);
extern void LVL_7_SIBERIUS_Fd179801d_FUN_00324E70(int);

int LVL_7_SIBERIUS_FUN_00324E10(char *p, int x, int y)
{
    int v;

    LVL_7_SIBERIUS_Fd179801d_FUN_00324E70(1);
    v = LVL_7_SIBERIUS_Fd179801d_FUN_00324CA8(p, x, y);
    LVL_7_SIBERIUS_Fd179801d_FUN_00324E70(1);
    return v;
}
extern float LVL_7_SIBERIUS_F7e66fb31_FUN_002E4508(char *, float *);
extern float LVL_7_SIBERIUS_F7e66fb31_FUN_002E4280(float);

int LVL_7_SIBERIUS_FUN_0031FF48(char *p, char *q, float f12, float f13)
{
    float v = LVL_7_SIBERIUS_F7e66fb31_FUN_002E4508(q, (float *)(p + 16));

    if (!(v < f12))
        return 0;
    if (LVL_7_SIBERIUS_F7e66fb31_FUN_002E4280(*(float *)(q + 8) - *(float *)(p + 24)) < f13)
        return 1;
    return 0;
}
extern int LVL_7_SIBERIUS_F1f748010_FUN_00320620(int, int);
extern void LVL_7_SIBERIUS_F1f748010_FUN_00306800(char *);
extern void LVL_7_SIBERIUS_F1f748010_FUN_003E0FC0(char *);
extern void LVL_7_SIBERIUS_F1f748010_FUN_003E17B8(char *);
extern void LVL_7_SIBERIUS_F1f748010_FUN_003E1FC0(char *);

void LVL_7_SIBERIUS_FUN_003E0BA0(char *p)
{
    if (LVL_7_SIBERIUS_F1f748010_FUN_00320620(3076, *(short *)(*(int *)(p + 104) + 26)) == 0)
        LVL_7_SIBERIUS_F1f748010_FUN_00306800(p);
    else {
        LVL_7_SIBERIUS_F1f748010_FUN_003E0FC0(p);
        LVL_7_SIBERIUS_F1f748010_FUN_003E17B8(p);
        LVL_7_SIBERIUS_F1f748010_FUN_003E1FC0(p);
    }
}
extern char *LVL_7_SIBERIUS_Fdc7ffbd9_FUN_00306498(int);

char *LVL_7_SIBERIUS_FUN_003876A8(char *p)
{
    char *o = LVL_7_SIBERIUS_Fdc7ffbd9_FUN_00306498(167);
    int *v;

    if (o != 0) {
        v = *(int **)(o + 104);
        v[1] = (int)p;
        v[0] = 0;
        v[2] = 0;
        v[3] = 0;
        *(unsigned char *)(o + 48) = 255;
        *(short *)(o + 50) = 126;
        o[49] = 0;
        o[32] = 0;
    }
    return o;
}
extern int LVL_7_SIBERIUS_F953b9ef6_FUN_00427F00(void *);
extern int LVL_7_SIBERIUS_F953b9ef6_FUN_002DC778(int);
extern void LVL_7_SIBERIUS_F953b9ef6_FUN_002DF618(float, float, float, int, int, int, int, int);

void LVL_7_SIBERIUS_FUN_00427F38(char *o)
{
    float f20;
    int s4;
    int r;
    int s2v;
    char *p0;
    char *p1;

    if (*(float *)(*(char **)(o + 16)) == 0.0f) {
        return;
    }
    if (*(int *)(o + 64) == 0) {
        return;
    }
    s4 = LVL_7_SIBERIUS_F953b9ef6_FUN_00427F00(o);
    f20 = *(float *)(*(char **)(o));
    switch (*(int *)(o + 68)) {
    case 0:
        break;
    case 1:
        f20 = f20 - (float)(s4 >> 1);
        break;
    case 2:
        f20 = f20 - (float)s4;
        break;
    }
    p0 = *(char **)(o);
    p1 = *(char **)(o + 4);
    s2v = *(int *)(*(char **)(o + 12));
    r = LVL_7_SIBERIUS_F953b9ef6_FUN_002DC778(*(int *)(o + 56));
    LVL_7_SIBERIUS_F953b9ef6_FUN_002DF618(f20, *(float *)(p0 + 4), *(float *)(p1), s2v, *(int *)(o + 64),
            s4, r, *(int *)(o + 52));
}
#ifndef RAC2_T_V4_F6A70B950
#define RAC2_T_V4_F6A70B950
typedef int V4_F6a70b950 __attribute__((mode(TI)));
#endif


extern char LVL_7_SIBERIUS_F6a70b950_D_00189E20[];
extern float LVL_7_SIBERIUS_F6a70b950_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F6a70b950_FUN_002E4918(float);
extern float LVL_7_SIBERIUS_F6a70b950_FUN_002E4900(float);
extern float LVL_7_SIBERIUS_F6a70b950_FUN_002E4918(float);
extern void LVL_7_SIBERIUS_F6a70b950_FUN_002E4B90(float *m, char *src);
extern void LVL_7_SIBERIUS_F6a70b950_FUN_002E47F8(float *dst, float *src, float *m);
extern void LVL_7_SIBERIUS_F6a70b950_FUN_002E4310(V4_F6a70b950 *out, V4_F6a70b950 *in, float *v);

void LVL_7_SIBERIUS_FUN_002C9748(V4_F6a70b950 *out, V4_F6a70b950 *in, float scale)
{
    char *p = LVL_7_SIBERIUS_F6a70b950_D_00189E20;
    unsigned char mode;
    float z;

    mode = *(unsigned char *)(p + 8899);

    switch (mode) {
    case 0:
        *out = *in;
        *(float *)out += LVL_7_SIBERIUS_F6a70b950_FUN_002E4900(*(float *)(*(int *)(p + 8848) + 248)) * scale;
        *(float *)((char *)out + 4) += LVL_7_SIBERIUS_F6a70b950_FUN_002E4918(*(float *)(*(int *)(p + 8848) + 248)) * scale;
        break;
    case 1:
    case 2: {
        float m[16];
        float v[4];

        z = 0.0f;
        v[0] = LVL_7_SIBERIUS_F6a70b950_FUN_002E4900(z) * scale;
        v[1] = LVL_7_SIBERIUS_F6a70b950_FUN_002E4918(z) * scale;
        v[2] = z;
        LVL_7_SIBERIUS_F6a70b950_FUN_002E4B90(m, (char *)*(int *)(p + 8848) + 240);
        LVL_7_SIBERIUS_F6a70b950_FUN_002E47F8(v, v, m);
        LVL_7_SIBERIUS_F6a70b950_FUN_002E4310(out, in, v);
        break;
    }
    }
}
#ifndef RAC2_T_V4_FBFDC087A
#define RAC2_T_V4_FBFDC087A
typedef int V4_Fbfdc087a __attribute__((mode(TI)));
#endif


extern char LVL_7_SIBERIUS_Fbfdc087a_D_00189EB0[];
extern void LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4B90(float *m, char *p);
extern void LVL_7_SIBERIUS_Fbfdc087a_FUN_002E47F8(float *dst, float *src, float *m);
extern void LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4B90(float *m, char *p);
extern void LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4F08(float *m, float *m2, float *e);
extern void LVL_7_SIBERIUS_Fbfdc087a_FUN_002E47F8(float *dst, float *src, float *m);
extern void LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4340(float *c, float *a, float *b);
extern void LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4310(char *a, char *b, float *c);
extern void LVL_7_SIBERIUS_Fbfdc087a_FUN_003152C0(float *m, char *p);

void LVL_7_SIBERIUS_FUN_002A9DB0(V4_Fbfdc087a *src, float x, float y, float z)
{
    char *p = LVL_7_SIBERIUS_Fbfdc087a_D_00189EB0;
    float q[4];
    float a[4];
    float b[4];
    float c[4];
    float m[16];
    float e[16];
    float v[4];

    *(V4_Fbfdc087a *)q = *src;
    LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4B90(m, p);
    LVL_7_SIBERIUS_Fbfdc087a_FUN_002E47F8(a, q, m);
    v[0] = x;
    v[1] = y;
    v[2] = z;
    LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4B90(e, v);
    LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4F08(m, m, e);
    LVL_7_SIBERIUS_Fbfdc087a_FUN_002E47F8(b, q, m);
    LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4340(c, a, b);
    LVL_7_SIBERIUS_Fbfdc087a_FUN_002E4310(p - 16, p - 16, c);
    LVL_7_SIBERIUS_Fbfdc087a_FUN_003152C0(m, p);
}
extern float LVL_7_SIBERIUS_Fa580e594_FUN_002E5460(int a);
extern float LVL_7_SIBERIUS_Fa580e594_FUN_002E5460(int a);
extern float LVL_7_SIBERIUS_Fa580e594_FUN_002E5460(int a);
extern float LVL_7_SIBERIUS_Fa580e594_FUN_002E5460(int a);

float LVL_7_SIBERIUS_FUN_003069F8(char *s1)
{
    char *p;
    char *q;
    float t;

    if (*(unsigned char *)(s1 + 66) != 255)
        p = *(char **)(s1 + 88);
    else
        p = *(char **)(s1 + 92);

    if (*(float *)(s1 + 68) == 0.0f)
        return LVL_7_SIBERIUS_Fa580e594_FUN_002E5460(*(short *)(p + 4)) * 0.0625f;

    if (*(unsigned char *)(s1 + 66) != *(unsigned char *)(s1 + 67) ||
        *(unsigned char *)(s1 + 64) > *(unsigned char *)(s1 + 65))
        return LVL_7_SIBERIUS_Fa580e594_FUN_002E5460(*(short *)(p + 4)) * 0.0625f + *(float *)(s1 + 68);

    q = *(char **)(s1 + 92);
    t = LVL_7_SIBERIUS_Fa580e594_FUN_002E5460(*(short *)(p + 4)) * (1.0f - *(float *)(s1 + 68));
    t = t + LVL_7_SIBERIUS_Fa580e594_FUN_002E5460(*(short *)(q + 4)) * *(float *)(s1 + 68);
    return t * 0.0625f;
}
extern float LVL_7_SIBERIUS_Fd03b762f_FUN_002E5460(int a0);
extern int LVL_7_SIBERIUS_Fd03b762f_FUN_002E5470(float x);

int LVL_7_SIBERIUS_FUN_0035D4A0(int a0, int *p0, int *p1, int *p2)
{
    float t;
    int a;
    int b;
    int c;
    int d;
    int e;

    t = LVL_7_SIBERIUS_Fd03b762f_FUN_002E5460(a0);
    a = LVL_7_SIBERIUS_Fd03b762f_FUN_002E5470(t * (1.0f / 3600.0f));
    *p0 = a;
    b = LVL_7_SIBERIUS_Fd03b762f_FUN_002E5470((float)a * 3600.0f);
    t = t - (float)b;
    c = LVL_7_SIBERIUS_Fd03b762f_FUN_002E5470(t * 0.01666667f);
    *p1 = c;
    d = LVL_7_SIBERIUS_Fd03b762f_FUN_002E5470((float)c * 60.0f);
    t = t - (float)d;
    e = LVL_7_SIBERIUS_Fd03b762f_FUN_002E5470(t * (5.0f / 3.0f));
    e = e > 99 ? 0 : e;
    *p2 = e;
    return e;
}
extern void LVL_7_SIBERIUS_Fc7a982c7_FUN_003109C8(char *arg, int mode, int value);
extern void LVL_7_SIBERIUS_Fc7a982c7_FUN_003F9C08(char *arg);
extern void LVL_7_SIBERIUS_Fc7a982c7_FUN_003F9CE0(char *arg);
extern float LVL_7_SIBERIUS_Fc7a982c7_FUN_002E4508(char *arg, char *table);
extern float LVL_7_SIBERIUS_Fc7a982c7_FUN_002E4280(float value);
extern void LVL_7_SIBERIUS_Fc7a982c7_FUN_0031CBC8(int arg, int value);
extern void LVL_7_SIBERIUS_Fc7a982c7_FUN_002E9B20(int arg);
extern void LVL_7_SIBERIUS_Fc7a982c7_FUN_00317788(int arg);
extern void LVL_7_SIBERIUS_Fc7a982c7_FUN_00306800(char *arg);
extern char LVL_7_SIBERIUS_Fc7a982c7_D_00189EA0[];
extern unsigned char LVL_7_SIBERIUS_Fc7a982c7_D_001A7B2E __attribute__((sda));
void LVL_7_SIBERIUS_FUN_003F9EC0(char *arg)
{
    int *object = *(int **)(arg + 104);
    unsigned char state = *(unsigned char *)(arg + 32);

    switch (state) {
    case 0:
        *(unsigned char *)(arg + 48) = 255;
        if (LVL_7_SIBERIUS_Fc7a982c7_D_001A7B2E != 0 && object[17] != 0) {
            LVL_7_SIBERIUS_Fc7a982c7_FUN_00306800((char *)object[17]);
            LVL_7_SIBERIUS_Fc7a982c7_FUN_00306800(arg);
            return;
        } else {
            LVL_7_SIBERIUS_Fc7a982c7_FUN_003109C8(arg, 1, -1);
            LVL_7_SIBERIUS_Fc7a982c7_FUN_003F9C08(arg);
        }
        break;
    case 1:
        LVL_7_SIBERIUS_Fc7a982c7_FUN_003F9CE0(arg);
        if (LVL_7_SIBERIUS_Fc7a982c7_FUN_002E4508(arg + 16, LVL_7_SIBERIUS_Fc7a982c7_D_00189EA0) < 2.0f) {
            if (LVL_7_SIBERIUS_Fc7a982c7_FUN_002E4280(*(float *)(arg + 24) - *(float *)(LVL_7_SIBERIUS_Fc7a982c7_D_00189EA0 + 8)) < 2.0f) {
                LVL_7_SIBERIUS_Fc7a982c7_FUN_0031CBC8(4658, -1);
                LVL_7_SIBERIUS_Fc7a982c7_FUN_002E9B20(54);
                LVL_7_SIBERIUS_Fc7a982c7_FUN_00317788(54);
                if (object[17] != 0) {
                    LVL_7_SIBERIUS_Fc7a982c7_FUN_00306800((char *)object[17]);
                    LVL_7_SIBERIUS_Fc7a982c7_FUN_00306800(arg);
                    return;
                }
                object[16] = 120;
            }
        }
        break;
    }
}
