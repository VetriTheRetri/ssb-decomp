#include <PR/ultratypes.h>
#include <PR/os.h>
#include <PR/sptask.h>

#include "macros.h"
#include "ssb64_types.h"

struct Weird80000F30 {
    u32 b00: 8;
    u32 b08: 8;
    u32 b10: 1;
};

// bss
u32 *D_80044EC0;
struct Unk80044ED4 *D_80044EC4;
struct Unk80044ED4 *D_80044EC8;
struct Unk80044ED4 *D_80044ECC;
struct Unk80044ED4 *D_80044ED0;
struct Unk80044ED4 *D_80044ED4;
struct Unk80044ED4 *D_80044ED8;
struct Unk80044ED4 *D_80044EDC;
struct Unk80044ED4 *D_80044EE0;
struct Unk80044ED4 *D_80044EE4;
OSViMode D_80044EE8;
OSViMode D_80044F38;
u32 D_80044F88[2];
void *D_80044F90[3];
void *D_80044F9C[1];
void *D_80044FA0;
u32 D_80044FA4;
s32 D_80044FA8;
u32 D_80044FAC;
u32 D_80044FB0;
u32 D_80044FB4;
u32 D_80044FB8;
u32 D_80044FBC; //bitflags? union?
u8 D_80044FC0[8];
u64 *D_80044FC8;
u32 D_80044FCC; //index into D_80044FC8?
u32 D_80044FD0; // unknown
u8 unref_80044FD4[4];
u8 D_80044FD8[32];
OSMesgQueue D_80044FF8;
u32 D_80045010;
OSMesgQueue *D_80045014;
u32 D_80045018;
s32 D_8004501C;
u32 *D_80045020;
u32 D_80045024;
void *D_80045028[3];
u8 D_80045034;
u8 D_80045035;
u8 extend_D_80045036;
u8 extend_D_80045037;
u8 extend_D_80045038[8];


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#pragma GLOBAL_ASM("game/nonmatching/thread3/weird_nops.s")

void func_80000920(s32 val) {
    D_8004501C = val;
}

s32 func_8000092C(void) {
    return D_8004501C;
}

void unref_80000938(void) {
    struct Unk80044ED4 *i = D_80044ECC, *j = D_80044EE4, *k = D_80044EDC;
    
    do {

    } while ( i || j || k );
}

struct Unk80000970 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8 pad08[0xc];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 pad18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ OSMesgQueue *mq;
    /* 0x24 */ struct Unk800009D8 *unk24;
};

void func_80000970(struct Unk80000970 *arg0) {
    OSMesg msgs[1];
    OSMesgQueue mq;

    osCreateMesgQueue(&mq, msgs, ARRAY_COUNT(msgs));
    arg0->unk14 = 0;
    arg0->unk1C = 1;
    arg0->mq = &mq;
    osSendMesg(&D_80044FF8, (OSMesg)arg0, OS_MESG_NOBLOCK);
    osRecvMesg(&mq, NULL, OS_MESG_BLOCK);
}

struct Unk800009D8 {
    /* 0x00 */ u8 pad00[4];
    /* 0x04 */ OSMesgQueue *mq;
};

void func_800009D8(struct Unk800009D8 *arg0, OSMesgQueue *mq, OSMesg *msg, u32 count) {
    struct Unk80000970 sp18;
    
    osCreateMesgQueue(mq, msg, count);
    arg0->mq = mq;
    sp18.unk00 = 3;
    sp18.unk04 = 100;
    sp18.unk24 = arg0;
    func_80000970(&sp18);
}

struct Unk80000A34 {
    /* 0x00 */ u8 pad00[0x70];
    /* 0x70 */ s32 unk70;
};


#ifdef NON_MATCHING
s32 unref_80000A34(struct Unk80000A34 *arg0) {
    void *nextFb; //1c
    void *tempA0_2;
    void *curFb; // temp_v0
    void *tempA0; // a0
    s32 i; // a0_2]

    if (!D_80044F9C[0]) {
        return 1;
    } 
    if (!D_80044FA0) {
        return 0;
    }

    nextFb = osViGetNextFramebuffer();
    curFb = osViGetCurrentFramebuffer();

    if (arg0->unk70 != -1) {
        tempA0 = D_80044F90[arg0->unk70];
        if (tempA0 && tempA0 != curFb && tempA0 != nextFb) {
            D_80044F9C[0] = tempA0;
            D_80044FA0 = tempA0;
            D_80044FC8 = 0;
            D_80044FAC = osGetCount();

            return 1;
        } // L80000AE8

        for (i = 0; i < ARRAY_COUNT(D_80044F90); i++) {
            tempA0_2 = D_80044F90[i];
            if (tempA0_2 && tempA0_2 != curFb && tempA0_2 != nextFb) {
                D_80044F9C[0] = tempA0_2;
                D_80044FC8 = 0;
                D_80044FAC = osGetCount();
                return 1;
            }
        }
    }

    return 0;
}
#else
#pragma GLOBAL_ASM("game/nonmatching/thread3/unref_80000A34.s")
#endif /* NON_MATCHING */

struct Unk80044ED4 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ struct Unk80044ED4 *unk0C; // next
    /* 0x10 */ struct Unk80044ED4 *unk10; // prev
    /* 0x14 */ s32 (*func)(struct Unk80044ED4 *);
    /* 0x18 */ u8 pad18[0x4];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ OSMesgQueue *unk20;
    /* 0x24 */ s32 *unk24;
    /* 0x28 */ OSTask task;
    /* 0x68 */ s32 *unk68;
    /* 0x6C */ s32 *unk6C;
    /* 0x70 */ u8 pad70[0x04];
    /* 0x74 */ s32 unk74;
    /* 0x78 */ u8 pad78[0x08];
    /* 0x80 */ u32 unk80;
};

s32 func_80000B54(UNUSED s32 arg0) {
    struct Unk80044ED4 *temp_v0;
    const s32 CHECK = 1;

    if (D_80044ECC != NULL && D_80044ECC->unk00 == CHECK) {
        return 0;
    }

    temp_v0 = D_80044ED4;
    while (temp_v0 != NULL) {
        if (temp_v0->unk00 == CHECK) {
            return 0;
        }
        temp_v0 = temp_v0->unk0C;
    }

    temp_v0 = D_80044EC4;
    while (temp_v0 != NULL) {
        if (temp_v0->unk00 == CHECK) {
            return 0;
        }
        temp_v0 = temp_v0->unk0C;
    }

    if (D_80044EE4 != NULL && D_80044EE4->unk00 == CHECK) {
        return 0;
    }

    temp_v0 = D_80044EDC;
    while (temp_v0 != NULL) {
        if (temp_v0->unk00 == CHECK) {
            return 0;
        }
        temp_v0 = temp_v0->unk0C;
    }

    if (D_80045034 != D_80045035) {
        return 0;
    }

    return 1;
}


void func_80000C64(struct Unk80044ED4 *arg0) {
    struct Unk80044ED4 *temp_v0;

    temp_v0 = D_80044EC8;
    while (temp_v0 != NULL && temp_v0->unk04 < arg0->unk04) {
        temp_v0 = temp_v0->unk10;
    }

    arg0->unk10 = temp_v0;
    if (temp_v0 != NULL) {
        arg0->unk0C = temp_v0->unk0C;
        temp_v0->unk0C = arg0;
    } else {
        arg0->unk0C = D_80044EC4;
        D_80044EC4 = arg0;
    }

    temp_v0 = arg0->unk0C;
    if (temp_v0 != NULL) {
        temp_v0->unk10 = arg0;
    } else {
        D_80044EC8 = arg0;
    }
}

void func_80000CF4(struct Unk80044ED4 *arg0) {
    if (arg0->unk10 != NULL) {
        arg0->unk10->unk0C = arg0->unk0C;
    } else {
        D_80044EC4 = arg0->unk0C;
    }

    if (arg0->unk0C != NULL) {
        arg0->unk0C->unk10 = arg0->unk10;
    } else {
        D_80044EC8 = arg0->unk10;
    }
}

void func_80000D44(struct Unk80044ED4 *arg0) {
    struct Unk80044ED4 *temp_v0;

    temp_v0 = D_80044ED8;
    while (temp_v0 != NULL && temp_v0->unk04 < arg0->unk04) {
        temp_v0 = temp_v0->unk10;
    }

    arg0->unk10 = temp_v0;
    if (temp_v0 != NULL) {
        arg0->unk0C = temp_v0->unk0C;
        temp_v0->unk0C = arg0;
    } else {
        arg0->unk0C = D_80044ED4;
        D_80044ED4 = arg0;
    }

    temp_v0 = arg0->unk0C;
    if (temp_v0 != NULL){
        temp_v0->unk10 = arg0;
    } else {
        D_80044ED8 = arg0;
    }
}

void func_80000DD4(struct Unk80044ED4 *arg0) {
    if (arg0->unk10 != NULL) {
        arg0->unk10->unk0C = arg0->unk0C;
    } else {
        D_80044ED4 = arg0->unk0C;
    }

    if (arg0->unk0C != NULL) {
        arg0->unk0C->unk10 = arg0->unk10;
    } else {
        D_80044ED8 = arg0->unk10;
    }
}

void func_80000E24(struct Unk80044ED4 *arg0) {
    arg0->unk0C = NULL;
    arg0->unk10 = D_80044EE0;
    if (D_80044EE0 != NULL) {
        D_80044EE0->unk0C = arg0;
    } else {
        D_80044EDC = arg0;
    }
    D_80044EE0 = arg0;
}

void func_80000E5C(struct Unk80044ED4 *arg0) {
    if (arg0->unk10 != NULL) {
        arg0->unk10->unk0C = arg0->unk0C;
    } else {
        D_80044EDC = arg0->unk0C;
    }

    if (arg0->unk0C != NULL) {
        arg0->unk0C->unk10 = arg0->unk10;
    } else {
        D_80044EE0 = arg0->unk10;
    }
}

void func_80000EAC(void) {
    D_80044EE8 = D_80044F38;
    osViSetMode(&D_80044EE8);
   
    // probably bitfield
    osViBlack((D_80044FBC << 4) >> 31);
    D_80044F88[0] = 0;
}

void func_80000F30(u32, u32, u32, s16, s16, s16, s16);
/*
OSViMode *func_80000F30(u32 arg0, u32 arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    u32 sp20;
    s32 sp1C;
    s32 sp14;
    u32 sp0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_lo;
    s32 temp_t6_3;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_t9_2;
    u32 temp_t0;
    u32 temp_t1;
    u32 temp_t4;
    u32 temp_t6;
    u32 temp_t6_2;
    u32 temp_t7;
    u32 temp_t7_2;
    u32 temp_t7_3;
    u32 phi_t9;
    s32 phi_t2;
    u32 phi_t1;
    s32 phi_v1;
    s32 phi_a0;
    u32 phi_t0;
    s32 phi_a0_2;
    u32 phi_a0_3;
    s32 phi_a0_4;
    s32 phi_t9_2;
    s32 phi_a0_5;

    //if ((arg0 >= 0x141U) || (phi_t2 = 1, ((arg1 < 0xF1U) == 0))) {
    //    phi_t2 = 0;
    //} else {
    //
    //}

    phi_t2 = arg0 < 0x141 && arg1 > 0xF1 ? 1 : 0;
    // L80000F5C

    if ((arg2 & 4) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 | 0x40);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl | 0x40);
    }
    if ((arg2 & 8) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 & 0xFFBF);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl & -0x41);
    }
    if ((arg2 & 0x10) != 0) {
        temp_t7 = D_80044F38.comRegs.ctrl & -4;
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 & 0xFFDF);
        D_80044F38.comRegs.ctrl = temp_t7;
        D_80044F38.comRegs.ctrl = (u32) (temp_t7 | 2);
    }
    if ((arg2 & 0x20) != 0) {
        temp_t7_2 = D_80044F38.comRegs.ctrl & -4;
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 | 0x20);
        D_80044F38.comRegs.ctrl = temp_t7_2;
        D_80044F38.comRegs.ctrl = (u32) (temp_t7_2 | 3);
    }
    if ((arg2 & 0x40) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 | 0x10);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl | 8);
    }
    if ((arg2 & 0x80) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 & 0xFFEF);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl & -9);
    }
    if ((arg2 & 0x1000) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 | 2);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl | 4);
    }
    if ((arg2 & 0x2000) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 & 0xFFFD);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl & -5);
    }
    if ((arg2 & 0x4000) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 | 1);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl | 0x10000);
    }
    if ((arg2 & 0x8000) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 & 0xFFFE);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl & 0xFFFEFFFF);
    }
    if ((arg2 << 0xF) < 0) {
        D_80044FBC.unk1 = (u8) (D_80044FBC.unk1 | 0x80);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl | 0x10);
    }
    if ((arg2 << 0xE) < 0) {
        D_80044FBC.unk1 = (u8) (D_80044FBC.unk1 & 0xFF7F);
        D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl & -0x11);
    }
    if ((arg2 & 0x100) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 | 8);
    }
    if ((arg2 & 0x200) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 & 0xFFF7);
    }
    if ((arg2 & 0x400) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 | 4);
    }
    if ((arg2 & 0x800) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 & 0xFFFB);
    }
    if ((arg2 & 1) != 0) {
        D_80044FBC.unk0 = (u8) ((D_80044FBC.unk0 & 0xFF7F) | 0x80);
    }
    if ((arg2 & 2) != 0) {
        D_80044FBC.unk0 = (u8) (D_80044FBC.unk0 & 0xFF7F);
    }
    D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl & -0x301);
    if (((u32) D_80044FBC.unk0 >> 0x1F) != 0) {
        phi_a0_5 = 0x100;
        if ((D_80044FBC.unk0 & 1) != 0) {
            phi_a0_5 = 0;
        }
        phi_t9 = D_80044F38.comRegs.ctrl | phi_a0_5;
        phi_t1 = (u32) (D_80044FBC.unk0 << 5) >> 0x1F;
        phi_t0 = (u32) (D_80044FBC.unk0 * 4) >> 0x1F;
block_47:
        D_80044F38.comRegs.ctrl = phi_t9;
    } else {
        temp_t1 = (u32) (D_80044FBC.unk0 << 5) >> 0x1F;
        if ((temp_t1 == 0) && (temp_t0 = (u32) (D_80044FBC.unk0 * 4) >> 0x1F, (temp_t0 == 1))) {
            D_80044F38.comRegs.ctrl = (u32) (D_80044F38.comRegs.ctrl | 0x300);
            phi_t1 = temp_t1;
            phi_t0 = temp_t0;
        } else {
            phi_t9 = D_80044F38.comRegs.ctrl | 0x200;
            phi_t1 = temp_t1;
            phi_t0 = (u32) (D_80044FBC.unk0 * 4) >> 0x1F;
            goto block_47;
        }
    }
    if (phi_t2 != 0) {
        if ((D_80044FBC.unk0 * 2) < 0) {
            phi_v1 = 0;
        } else {
            phi_v1 = 1;
        }
    } else {
        phi_v1 = 1;
        if (phi_t1 != 0) {
            phi_v1 = 0;
        }
    }
    temp_a3 = phi_t2 == 0;
    temp_a1 = (s32) ((arg5 & 0xFFFE) << 0x10) >> 0x10;
    temp_a2 = (s32) ((arg6 & 0xFFFE) << 0x10) >> 0x10;
    if ((temp_a3 != 0) && (phi_v1 == 0)) {
        sp14 = 2;
    } else {
        sp14 = 1;
    }
    if (phi_t2 != 0) {
        phi_a0_3 = 1U;
    } else {
        phi_a0_3 = 2U;
    }
    temp_t4 = arg1 << 0xB;
    temp_lo = ((u32) (temp_t4 / (u32) ((temp_a2 - temp_a1) + 0x1E0)) / phi_a0_3) * sp14;
    if ((temp_a3 != 0) && (phi_v1 != 0)) {
        phi_a0 = 2;
    } else {
        phi_a0 = 1;
    }
    D_80044F38.comRegs.width = (u32) (phi_a0 * arg0);
    if (D_NF_80000300 == 1) {
        D_80044F38.comRegs.burst = 0x3E52239U;
        D_80044F38.comRegs.vSync = 0x20CU;
        D_80044F38.comRegs.hSync = 0xC15U;
        D_80044F38.comRegs.leap = 0xC150C15U;
        D_80044F38.comRegs.hStart = 0x6C02ECU;
        D_80044F38.unk30 = 0x2501FFU;
        D_80044F38.unk34 = 0xE0204;
    }
    if (2 == D_NF_80000300) {
        D_80044F38.comRegs.burst = 0x4651E39U;
        D_80044F38.comRegs.vSync = 0x20CU;
        D_80044F38.comRegs.hSync = 0xC10U;
        D_80044F38.comRegs.leap = 0xC1C0C1CU;
        D_80044F38.comRegs.hStart = 0x6C02ECU;
        D_80044F38.unk30 = 0x2501FFU;
        D_80044F38.unk34 = 0xE0204;
    }
    sp0 = D_80044F38.comRegs.hStart;
    D_80044F38.unk44 = (u32) D_80044F38.unk30;
    temp_t6 = (u32) D_80044F38.comRegs.hStart >> 0x10;
    sp20 = temp_t6;
    sp1C = D_80044F38.comRegs.hStart & 0xFFFF;
    temp_t9 = temp_t6 + arg3;
    sp20 = (u32) temp_t9;
    if (temp_t9 < 0) {
        sp20 = 0U;
    }
    temp_t8 = sp1C + arg4;
    sp1C = temp_t8;
    if (temp_t8 < 0) {
        sp1C = 0;
    }
    D_80044F38.comRegs.hStart = (u32) ((sp20 << 0x10) | sp1C);
    temp_t6_2 = (u32) D_80044F38.unk30 >> 0x10;
    sp0 = D_80044F38.unk30;
    sp20 = temp_t6_2;
    temp_t9_2 = temp_t6_2 + temp_a1;
    sp1C = D_80044F38.unk30 & 0xFFFF;
    sp20 = (u32) temp_t9_2;
    if (temp_t9_2 < 0) {
        sp20 = 0U;
    }
    temp_t8_2 = sp1C + temp_a2;
    sp1C = temp_t8_2;
    if (temp_t8_2 < 0) {
        sp1C = 0;
    }
    D_80044F38.unk30 = (u32) ((sp20 << 0x10) | sp1C);
    temp_t7_3 = (u32) D_80044F38.unk44 >> 0x10;
    sp0 = D_80044F38.unk44;
    sp20 = temp_t7_3;
    temp_t6_3 = temp_t7_3 + temp_a1;
    sp1C = D_80044F38.unk44 & 0xFFFF;
    sp20 = (u32) temp_t6_3;
    if (temp_t6_3 < 0) {
        sp20 = 0U;
    }
    temp_t8_3 = sp1C + temp_a2;
    sp1C = temp_t8_3;
    if (temp_t8_3 < 0) {
        sp1C = 0;
    }
    D_80044F38.unk44 = (u32) ((sp20 << 0x10) | sp1C);
    D_80044F38.unk48 = (s32) D_80044F38.unk34;
    if ((phi_t2 != 0) && (phi_v1 != 0)) {
        D_80044F38.comRegs.vSync = (u32) (D_80044F38.comRegs.vSync + 1);
        if (2 == D_NF_80000300) {
            D_80044F38.comRegs.hSync = (u32) (D_80044F38.comRegs.hSync + 0x40001);
        }
        if (2 == D_NF_80000300) {
            D_80044F38.comRegs.leap = (u32) (D_80044F38.comRegs.leap + 0xFFFCFFFE);
        }
    } else {
        D_80044F38.unk30 = (u32) (D_80044F38.unk30 + 0xFFFDFFFE);
        if (2 == D_NF_80000300) {
            D_80044F38.unk34 = (s32) (D_80044F38.unk34 + 0xFFFCFFFE);
        }
        if (D_NF_80000300 == 0) {
            D_80044F38.unk48 = (s32) (D_80044F38.unk48 + 0x2FFFE);
        }
    }
    D_80044F38.comRegs.vCurrent = 0U;
    D_80044F38.comRegs.xScale = (u32) ((u32) (arg0 << 0xA) / (u32) ((arg4 - arg3) + 0x280));
    phi_a0_2 = 2;
    if (phi_t0 == 0) {
        phi_a0_2 = 1;
    }
    D_80044F38.fldRegs = (OSViFieldRegs *) ((phi_a0_2 * arg0) * 2);
    if (phi_t0 == 0) {
        sp14 = 1;
    } else {
        sp14 = 2;
    }
    phi_a0_4 = 2;
    if (phi_t2 != 0) {
        phi_a0_4 = 1;
    }
    D_80044F38.unk2C = temp_lo;
    D_80044F38.unk40 = temp_lo;
    D_80044F38.unk3C = (s32) (((phi_a0_4 * arg0) * 2) * sp14);
    if (phi_t1 != 0) {
        if (temp_t4 < 0xB4000U) {
            D_80044F38.unk2C = (s32) (temp_lo + 0x3000000);
            phi_t9_2 = temp_lo + 0x1000000;
        } else {
            D_80044F38.unk2C = (s32) (D_80044F38.unk2C + 0x2000000);
            phi_t9_2 = D_80044F38.unk40 + 0x2000000;
        }
        D_80044F38.unk40 = phi_t9_2;
    }
    D_80044F38.unk38 = 2;
    D_80044F38.unk4C = 2;
    *D_80044F88 = 1U;
    return &D_80044F38;
}
*/
#pragma GLOBAL_ASM("game/nonmatching/thread3/func_80000F30.s")

void func_800016D8(void) {
    void * cur;
    void * next;

    if (D_80045035 != D_80045034) {
        next = osViGetNextFramebuffer();
        cur = osViGetCurrentFramebuffer();
        if (next == cur) {
            osViSwapBuffer(D_80045028[D_80045035]);
            if (D_80045035 == 2) {
                D_80045035 = 0;
            } else {
                D_80045035 += 1;
            }
        }
    }
}

void func_80001764(void *arg0) {
    D_80045028[D_80045034] = arg0;
    if (D_80045034 == 2) {
        D_80045034 = 0;
    } else {
        D_80045034 += 1;
    }
    func_800016D8();
}

/// could be (void *arg0) -> void
/// checks for arg0 == -1, though
void func_800017B8(s32 arg0) {
    void *temp;

    if (D_80044F88[0] != 0) {
        if (D_80045020 == NULL) {
            func_80000EAC();
        }
    }

    if (D_80045010 != 0) {
        osSendMesg(D_80045014, (OSMesg)1, OS_MESG_NOBLOCK);
        if (arg0 == -1) {
            D_80044FA8 = (s32)(uintptr_t) D_80044F9C[0];
            D_80044F9C[0] = NULL;
        } else {
            D_80044FA8 = arg0;
        }
    } else {
        if (arg0 == -1) {
            func_80001764(D_80044F9C[0]);
            // permutater solution
            temp = D_80044F9C[0]; if (temp == D_80044FA0) { 
                D_80044FA4 = 1; 
            }
            D_80044FA8 = (s32)(uintptr_t) temp;
            D_80044F9C[0] = NULL;
        } else {
            func_80001764((void *)arg0);
            D_80044FA8 = arg0;
        }
    }
    // OS_CYCLES_TO_NSEC?
    D_80044FB4 = (u32) ((u32) (osGetCount() - D_80044FAC) / 0xB9BU);
}

void func_800018E0(struct Unk80044ED4 *arg0) {
    if (D_80044ECC != 0) {
        osSpTaskYield();
        D_80044ECC->unk08 = 4;
        func_80000D44(D_80044ECC);
        arg0->unk08 = 3;
    } else {
        osSpTaskStart(&arg0->task);
        arg0->unk08 = 2;
    }
    D_80044ECC = arg0;
}

void func_80001968(struct Unk80044ED4 *arg0) {
    D_80044FB0 = osGetCount();

    if ((D_80044ECC != NULL) && (D_80044ECC->unk08 == 2)) {
        osSpTaskYield();
        D_80044ECC->unk08 = 4;
        arg0->unk08 = 3;
    } else {
        osSpTaskStart(&arg0->task);
        arg0->unk08 = 2;
    }
    D_80044ED0 = arg0;
}
/*
	28 00 u32	type;
	2C 04 u32	flags;
	30 08 u64	*ucode_boot;
	34 0c u32	ucode_boot_size;

	38 10 u64	*ucode;
	3c 14 u32	ucode_size;
	40 18 u64	*ucode_data;
	44 1c u32	ucode_data_size;

	48 20 u64	*dram_stack;
	4c 24 u32	dram_stack_size;
	50 28 u64	*output_buff;
	54 2c u64	*output_buff_size;

	58 30 u64	*data_ptr;
	5c 34 u32	data_size;
	60 38 u64	*yield_data_ptr;
	64 3c u32	yield_data_size;
*/

#ifdef NON_MATCHING

s32 func_80001A00(struct Unk80044ED4 *arg0) {
    s32 sp4C = 0;

    switch (arg0->unk00) {
        case 1:
            if (arg0->unk68 != NULL) {
                *arg0->unk68 |= (s32) D_80044F9C[0];
                osWritebackDCache(arg0->unk68, sizeof(s32 *));
            }
            //L80001A6C
            if ((uintptr_t) arg0->task.t.output_buff == (uintptr_t)-1) {
                arg0->task.t.output_buff = &D_80044FC8[D_80044FCC];
                osWritebackDCache(&arg0->task.t.output_buff, sizeof(u64 *));
            }
            // L80001A98
            if (arg0->unk74 == 1) {
                osInvalDCache(D_80044FC0, sizeof(D_80044FC0));
            }
            // L80001AB4
            func_800018E0(arg0);
            sp4C = 1;
            break;
        case 2:
            osWritebackDCacheAll();
            func_80001968(arg0);
            sp4C = 1;
            break;
        case 3:
            *arg0->unk24 = *D_80044EC0;
            D_80044EC0 = (u32 *)arg0->unk24;
            if (arg0->unk20 != NULL) {
                osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
            }
            break;
        case 4:
            func_80000F30(
                arg0->unk24, 
                arg0->task.t.type,
                arg0->task.t.flags,
                ((s16 *) &arg0->task.t.ucode_boot)[0],
                ((s16 *) &arg0->task.t.ucode_boot)[1],
                ((s16 *) &arg0->task.t.ucode_boot_size)[0],
                ((s16 *) &arg0->task.t.ucode_boot_size)[1]
            );

            if (arg0->unk20 != NULL) {
                osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
            }
            break;
        case 5:
            // v0 = &D_80044F90
            // a0 = &D_80044F9C
            // v1 = arg0
            // L80001B7C
            {
            s32 i;
            for (i = 0; i < ARRAY_COUNT(D_80044F90); i++) {
                D_80044F90[i] = arg0[i].unk24;
            }
            }
            if (arg0->unk20 != NULL) {
                osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
            }
            break;
        case 6:
            // really big
            {
            struct Unk80044ED4 *v1 = NULL;
            struct Unk80044ED4 *v0;
            // a0 = D_80044ECC;
            if (D_80044ECC != NULL) {
                if (D_80044ECC->unk00 == 1) {
                    if (arg0->task.t.type == D_80044ECC->unk80) {
                        v1 = D_80044ECC;
                    }
                }
            }
            // L80001BEC
            v0 = D_80044ED4;
            while (v0 != NULL) {
                if (v0->unk00 == 1) {
                    if (arg0->task.t.type == v0->unk80) {
                        v1 = v0;
                    }
                }
                // L80001C20
                v0 = v0->unk0C;
            }
            //L80001C28
            v0 = D_80044EC4;
            while (v0 != NULL) {
                if (v0->unk00 == 1) {
                    if (arg0->task.t.type == v0->unk80) {
                        v1 = v0;
                    }
                }
                //L80001C5C
                v0 = v0->unk0C;
            }
            //L80001C64
            v0 = D_80044EE4;
            if (v0 != NULL) {
                if (v0->unk00 == 1) {
                    if (arg0->task.t.type == D_80044ECC->unk80) {
                        v1 = v0;
                    }
                }
            }
            // L80001C94
            v0 = D_80044EDC;
            while (v0 != NULL) {
                if (v0->unk00 == 1) {
                    if (arg0->task.t.type == v0->unk80) {
                        v1 = v0;
                    }
                }
                v0 = v0->unk0C;
            }
            // L80001CD0
            if (v1 != NULL) {
                v1->unk1C = arg0->unk1C;
                v1->unk20 = arg0->unk20;
                v1->unk6C = arg0->unk24;
            } else {
                //L80001CF8
                if (arg0->unk24 != NULL) {
                    func_800017B8(arg0->unk20);
                }
                //L80001D0C
                if (arg0->unk20 != NULL) {
                    osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
                }
            }
            }
            break;
        case 7:
            if (arg0->unk20 != NULL) {
                osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
            }
            break;
        case 8:
            D_80044FCC = (uintptr_t)arg0->unk24;
            D_80044FD0 = arg0->task.t.type;
            if (arg0->unk20 != NULL) {
                osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
            }
            break;
        case 9:
            D_80045010 = 1;
            D_80045014 = (OSMesgQueue *)arg0->unk24;
            if (arg0->unk20 != NULL) {
                osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
            }
            break;
        case 10:
            D_80045010 = 0;
            if (arg0->unk20 != NULL) {
                osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
            }
            break;
        case 11:
            {
            struct Unk80044ED4 *a0 = D_80044EC4;
            //struct Unk80044ED4 *sp34;
            while (a0 != NULL) {
                if (a0->unk00 == 1 || a0->unk00 == 4) {
                    //sp34 = a0->unk0C;
                    func_80000CF4(a0);
                    //a0 = sp34;
                } 
                // L80001E28
                a0 = a0->unk0C;
            }
            }
            // L80001E30
            D_80044FA0 = NULL;
            if (arg0->unk20 != NULL) {
                osSendMesg(arg0->unk20, (OSMesg)arg0->unk1C, OS_MESG_NOBLOCK);
            }
            break;
    }
    // L80001E50

    return sp4C;
}
#else 
s32 func_80001A00(struct Unk80044ED4 *arg0);
#pragma GLOBAL_ASM("game/nonmatching/thread3/func_80001A00.s")
#endif /* NON_MATCHING */

void func_80001E64(void) {
    s32 phi_a0;
    s32 phi_v0;
    s32 phi_v1;
    struct Unk80044ED4 *phi_s0;
    struct Unk80044ED4 *temp_s1;
    s32 phi_s2 = 0;
    s32 phi_s4;
    s32 phi_s7;


    phi_s7 = D_80044ECC != NULL ? D_80044ECC->unk04 : -1;

    // L80001EB0
    if (D_80044ED0 != NULL) {
        phi_s7 = D_80044ED0->unk04;
    }
    // L80001ECC
    phi_s4 = D_80044ED4 != NULL ? D_80044ED4->unk04 : -1;

    // L80001EE8
    phi_s0 = D_80044EC4;
    while (phi_s2 == 0) {
        // L80001EEC
        phi_v0 = phi_s0 != NULL ? phi_s0->unk04 : - 1;

        // L80001EFC
        if (phi_s4 >= phi_v0) {
            phi_v1 = 0;
            phi_a0 = phi_s4;
        } else {
            phi_v1 = 1;
            phi_a0 = phi_v0;
        }
        // L80001F18
        if (phi_s7 >= phi_a0) {
            phi_s2 = 1;
        } else {
            switch (phi_v1) {
                case 0:
                    // L80001F48
                    osSpTaskStart(&D_80044ED4->task);
                    phi_s2 = 1;
                    D_80044ED4->unk08 = 2;
                    D_80044ECC = D_80044ED4;
                    func_80000DD4(D_80044ED4);
                    break;
                case 1: 
                    // L80001F80
                    if (phi_s0->func == NULL || phi_s0->func(phi_s0) != 0) {
                        // L80001F98
                        phi_s2 = func_80001A00(phi_s0);
                        temp_s1 = phi_s0->unk0C;
                        func_80000CF4(phi_s0);
                        phi_s0 = temp_s1;
                    } else {
                        phi_s0 = phi_s0->unk0C;
                    }
                    break;
            }
        }
    }
}

#pragma GLOBAL_ASM("game/nonmatching/thread3/func_80001FF4.s")

#pragma GLOBAL_ASM("game/nonmatching/thread3/func_8000205C.s")

#pragma GLOBAL_ASM("game/nonmatching/thread3/func_800020D0.s")

#pragma GLOBAL_ASM("game/nonmatching/thread3/func_80002340.s")

#pragma GLOBAL_ASM("game/nonmatching/thread3/func_800024EC.s")

#pragma GLOBAL_ASM("game/nonmatching/thread3/thread3_scheduler.s")

#pragma GLOBAL_ASM("game/nonmatching/thread3/func_800029D8.s")

#pragma GCC diagnostic pop
