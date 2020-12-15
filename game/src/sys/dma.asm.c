#include <PR/ultratypes.h>
#include <PR/os.h>
#include "ssb_types.h"

#include "sys/dma.h"
#include "sys/thread3.h"

u8 gPiHandle[8];
u8 D_80045048[20];
u32 D_8004505C;
u8 Extend_D_8004505C[92];
OSMesg D_800450BC;
OSMesgQueue sDmaMesgQ; // D_800450C0
u32 D_800450D8;
u32 D_800450DC;
u8 D_800450E0[16];
u8 D_800450F0[24];
u8 D_80045108[8];
u8 D_80045110[8];
u8 D_80045118[32];
u8 D_80045138[24];
u8 D_80045150[16];
u8 D_80045160[24];
u8 D_80045178[16];
u8 D_80045188[24];
u32 D_800451A0;
u32 D_800451A4;
u8 D_800451A8[16];
u32 D_800451B8;
u32 D_800451BC;
u8 Extend_D_800451BC[24];
u32 D_800451D8;
u32 D_800451DC;
u8 Extend_D_800451DC[24];
u32 D_800451F8;
u32 D_800451FC;
u8 Extend_D_800451FC[24];
u32 D_80045218;
u32 D_8004521C;
u8 Extend_D_8004521C[8];
u16 D_80045228;
u16 D_8004522A;
u32 fake_2C_extend_D_8004522A;
u8 Extend_D_8004522A[32];


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

// create_dma_mq
void ssb_create_dma_mq(void) {
    osCreateMesgQueue(&sDmaMesgQ, &D_800450BC, OS_MESG_BLOCK);
}

// dma_copy
void ssb_data_dma(OSPiHandle *handle, u32 physAddr, uintptr_t vAddr, u32 size, u8 direction) {
    OSIoMesg mesg; //sp48

    if (direction == OS_WRITE) {
        osWritebackDCache((void *)vAddr, size);
    } else {
        osInvalDCache((void *)vAddr, size);
    }

    mesg.hdr.pri = OS_MESG_PRI_NORMAL;
    mesg.hdr.retQueue = &sDmaMesgQ;
    mesg.size = 0x10000;

    while (size > 0x10000) {
        mesg.dramAddr = (void *)vAddr;
        mesg.devAddr = physAddr;

        if (!D_80045020) {
            osEPiStartDma(handle, &mesg, direction);
        }
        osRecvMesg(&sDmaMesgQ, NULL, OS_MESG_BLOCK);
        size -= 0x10000;
        physAddr += 0x10000;
        vAddr += 0x10000;
    }

    if (size != 0) {
        mesg.dramAddr = (void *)vAddr;
        mesg.devAddr = physAddr;
        mesg.size = size;

        if (!D_80045020) {
            osEPiStartDma(handle, &mesg, direction);
        }
        osRecvMesg(&sDmaMesgQ, NULL, OS_MESG_BLOCK);
    }
}

#pragma GLOBAL_ASM("game/nonmatching/dma/load_overlay.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/ssb_rom_copy_no_writeback.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/ssb_rom_copy_writeback.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/maybe_setup_pi_handle.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80002DA4.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80002DE0.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80002E18.s")

// Possible thread6.c start?
#pragma GLOBAL_ASM("game/nonmatching/dma/func_800035E0.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_800035FC.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80003648.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80003690.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/unref_800036B4.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80003C00.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80003CC4.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80003DD4.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80003F98.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80004000.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_800040A0.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80004284.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_800042E8.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80004310.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80004368.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80004394.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_800043C0.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80004474.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_80004494.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_800044B4.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/func_800044D4.s")

#pragma GLOBAL_ASM("game/nonmatching/dma/thread6.s")
#pragma GCC diagnostic pop
