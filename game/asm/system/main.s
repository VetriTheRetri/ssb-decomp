.include "macros.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .text

.align 4
#unref_80000460:
#  /* 001060 80000460 3C028004 */       lui $v0, %hi(D_80040CE0)
#  /* 001064 80000464 03E00008 */        jr $ra
#  /* 001068 80000468 24420CE0 */     addiu $v0, $v0, %lo(D_80040CE0)
#
#unref_8000046C:
#  /* 00106C 8000046C 3C028004 */       lui $v0, %hi(D_80040E90)
#  /* 001070 80000470 03E00008 */        jr $ra
#  /* 001074 80000474 24420E90 */     addiu $v0, $v0, %lo(D_80040E90)
#
#unref_80000478:
#  /* 001078 80000478 03E00008 */        jr $ra
#  /* 00107C 8000047C 24023400 */     addiu $v0, $zero, 0x3400

#glabel check_sp_imem
#  /* 001080 80000480 3C0EA400 */       lui $t6, %hi(D_NF_A4001000)
#  /* 001084 80000484 8DCF1000 */        lw $t7, %lo(D_NF_A4001000)($t6)
#  /* 001088 80000488 240117D7 */     addiu $at, $zero, 0x17d7
#  /* 00108C 8000048C 24180001 */     addiu $t8, $zero, 1
#  /* 001090 80000490 15E10003 */       bne $t7, $at, .L800004A0
#  /* 001094 80000494 3C018004 */       lui $at, %hi(D_80044D40)
#  /* 001098 80000498 03E00008 */        jr $ra
#  /* 00109C 8000049C A0384D40 */        sb $t8, %lo(D_80044D40)($at)
#
#  .L800004A0:
#  /* 0010A0 800004A0 3C018004 */       lui $at, %hi(D_80044D40)
#  /* 0010A4 800004A4 A0204D40 */        sb $zero, %lo(D_80044D40)($at)
#  /* 0010A8 800004A8 03E00008 */        jr $ra
#  /* 0010AC 800004AC 00000000 */       nop 

#glabel check_sp_dmem
#  /* 0010B0 800004B0 3C0EA400 */       lui $t6, %hi(D_NF_A4000000)
#  /* 0010B4 800004B4 8DCF0000 */        lw $t7, %lo(D_NF_A4000000)($t6)
#  /* 0010B8 800004B8 2401FFFF */     addiu $at, $zero, -1
#  /* 0010BC 800004BC 24180001 */     addiu $t8, $zero, 1
#  /* 0010C0 800004C0 15E10003 */       bne $t7, $at, .L800004D0
#  /* 0010C4 800004C4 3C018004 */       lui $at, %hi(D_80044D41)
#  /* 0010C8 800004C8 03E00008 */        jr $ra
#  /* 0010CC 800004CC A0384D41 */        sb $t8, %lo(D_80044D41)($at)
#
#  .L800004D0:
#  /* 0010D0 800004D0 3C018004 */       lui $at, %hi(D_80044D41)
#  /* 0010D4 800004D4 A0204D41 */        sb $zero, %lo(D_80044D41)($at)
#  /* 0010D8 800004D8 03E00008 */        jr $ra
#  /* 0010DC 800004DC 00000000 */       nop 

# glabel fatal_thread_stack_overflow
#   /* 0010E0 800004E0 27BDFFE8 */     addiu $sp, $sp, -0x18
#   /* 0010E4 800004E4 00802825 */        or $a1, $a0, $zero
#   /* 0010E8 800004E8 AFBF0014 */        sw $ra, 0x14($sp)
#   /* 0010EC 800004EC 3C048004 */       lui $a0, %hi(D_8003D650)
#   /* 0010F0 800004F0 0C008D89 */       jal fatal_printf
#   /* 0010F4 800004F4 2484D650 */     addiu $a0, $a0, %lo(D_8003D650)
#   .L800004F8:
#   /* 0010F8 800004F8 1000FFFF */         b .L800004F8
#   /* 0010FC 800004FC 00000000 */       nop 
#   /* 001100 80000500 8FBF0014 */        lw $ra, 0x14($sp)
#   /* 001104 80000504 27BD0018 */     addiu $sp, $sp, 0x18
#   /* 001108 80000508 03E00008 */        jr $ra
#   /* 00110C 8000050C 00000000 */       nop 

glabel check_stack_probes
  /* 001110 80000510 3C0E8004 */       lui $t6, %hi(D_8003FB08)
  /* 001114 80000514 8DCEFB08 */        lw $t6, %lo(D_8003FB08)($t6)
  /* 001118 80000518 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 00111C 8000051C 3C0F8004 */       lui $t7, %hi(D_8003FB0C)
  /* 001120 80000520 AFBF0014 */        sw $ra, 0x14($sp)
  /* 001124 80000524 15C00005 */      bnez $t6, .L8000053C
  /* 001128 80000528 8DEFFB0C */        lw $t7, %lo(D_8003FB0C)($t7)
  /* 00112C 8000052C 3C01FEDC */       lui $at, (0xFEDCBA98 >> 16) # 4275878552
  /* 001130 80000530 3421BA98 */       ori $at, $at, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 001134 80000534 11E10003 */       beq $t7, $at, .L80000544
  /* 001138 80000538 00000000 */       nop 
  .L8000053C:
  /* 00113C 8000053C 0C000138 */       jal fatal_thread_stack_overflow
  /* 001140 80000540 00002025 */        or $a0, $zero, $zero
  .L80000544:
  /* 001144 80000544 3C188004 */       lui $t8, %hi(D_8003FEB8)
  /* 001148 80000548 8F18FEB8 */        lw $t8, %lo(D_8003FEB8)($t8)
  /* 00114C 8000054C 3C198004 */       lui $t9, %hi(D_8003FEBC)
  /* 001150 80000550 8F39FEBC */        lw $t9, %lo(D_8003FEBC)($t9)
  /* 001154 80000554 17000004 */      bnez $t8, .L80000568
  /* 001158 80000558 3C01FEDC */       lui $at, (0xFEDCBA98 >> 16) # 4275878552
  /* 00115C 8000055C 3421BA98 */       ori $at, $at, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 001160 80000560 13210003 */       beq $t9, $at, .L80000570
  /* 001164 80000564 00000000 */       nop 
  .L80000568:
  /* 001168 80000568 0C000138 */       jal fatal_thread_stack_overflow
  /* 00116C 8000056C 24040001 */     addiu $a0, $zero, 1
  .L80000570:
  /* 001170 80000570 3C088004 */       lui $t0, %hi(D_80040168)
  /* 001174 80000574 8D080168 */        lw $t0, %lo(D_80040168)($t0)
  /* 001178 80000578 3C098004 */       lui $t1, %hi(D_8004016C)
  /* 00117C 8000057C 8D29016C */        lw $t1, %lo(D_8004016C)($t1)
  /* 001180 80000580 15000004 */      bnez $t0, .L80000594
  /* 001184 80000584 3C01FEDC */       lui $at, (0xFEDCBA98 >> 16) # 4275878552
  /* 001188 80000588 3421BA98 */       ori $at, $at, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 00118C 8000058C 11210003 */       beq $t1, $at, .L8000059C
  /* 001190 80000590 00000000 */       nop 
  .L80000594:
  /* 001194 80000594 0C000138 */       jal fatal_thread_stack_overflow
  /* 001198 80000598 24040003 */     addiu $a0, $zero, 3
  .L8000059C:
  /* 00119C 8000059C 3C0A8004 */       lui $t2, %hi(D_80040EC8)
  /* 0011A0 800005A0 8D4A0EC8 */        lw $t2, %lo(D_80040EC8)($t2)
  /* 0011A4 800005A4 3C0B8004 */       lui $t3, %hi(D_80040ECC)
  /* 0011A8 800005A8 8D6B0ECC */        lw $t3, %lo(D_80040ECC)($t3)
  /* 0011AC 800005AC 15400004 */      bnez $t2, .L800005C0
  /* 0011B0 800005B0 3C01FEDC */       lui $at, (0xFEDCBA98 >> 16) # 4275878552
  /* 0011B4 800005B4 3421BA98 */       ori $at, $at, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 0011B8 800005B8 51610004 */      beql $t3, $at, .L800005CC
  /* 0011BC 800005BC 8FBF0014 */        lw $ra, 0x14($sp)
  .L800005C0:
  /* 0011C0 800005C0 0C000138 */       jal fatal_thread_stack_overflow
  /* 0011C4 800005C4 24040005 */     addiu $a0, $zero, 5
  /* 0011C8 800005C8 8FBF0014 */        lw $ra, 0x14($sp)
  .L800005CC:
  /* 0011CC 800005CC 27BD0018 */     addiu $sp, $sp, 0x18
  /* 0011D0 800005D0 03E00008 */        jr $ra
  /* 0011D4 800005D4 00000000 */       nop 

glabel thread5_main
  /* 0011D8 800005D8 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 0011DC 800005DC AFBF001C */        sw $ra, 0x1c($sp)
  /* 0011E0 800005E0 AFA40020 */        sw $a0, 0x20($sp)
  /* 0011E4 800005E4 0C00E390 */       jal osCreateViManager
  /* 0011E8 800005E8 240400FE */     addiu $a0, $zero, 0xfe
  /* 0011EC 800005EC 0C00D7B8 */       jal osCartRomInit
  /* 0011F0 800005F0 00000000 */       nop 
  /* 0011F4 800005F4 3C018004 */       lui $at, %hi(D_80045040)
  /* 0011F8 800005F8 0C000B45 */       jal maybe_setup_pi_handle
  /* 0011FC 800005FC AC225040 */        sw $v0, %lo(D_80045040)($at)
  /* 001200 80000600 3C058004 */       lui $a1, %hi(D_80044E28)
  /* 001204 80000604 3C068004 */       lui $a2, %hi(D_80044D60)
  /* 001208 80000608 24C64D60 */     addiu $a2, $a2, %lo(D_80044D60)
  /* 00120C 8000060C 24A54E28 */     addiu $a1, $a1, %lo(D_80044E28)
  /* 001210 80000610 24040096 */     addiu $a0, $zero, 0x96
  /* 001214 80000614 0C00CB38 */       jal osCreatePiManager
  /* 001218 80000618 24070032 */     addiu $a3, $zero, 0x32
  /* 00121C 8000061C 0C000A98 */       jal ssb_create_dma_mq
  /* 001220 80000620 00000000 */       nop 
  /* 001224 80000624 3C04B000 */       lui $a0, (0xB0000B70 >> 16) # 2952792944
  /* 001228 80000628 3C058004 */       lui $a1, %hi(D_80044C40)
  /* 00122C 8000062C 24A54C40 */     addiu $a1, $a1, %lo(D_80044C40)
  /* 001230 80000630 34840B70 */       ori $a0, $a0, (0xB0000B70 & 0xFFFF) # 2952792944
  /* 001234 80000634 0C000B28 */       jal ssb_rom_copy_no_writeback
  /* 001238 80000638 24060100 */     addiu $a2, $zero, 0x100
  /* 00123C 8000063C 0C000120 */       jal check_sp_imem
  /* 001240 80000640 00000000 */       nop 
  /* 001244 80000644 0C00012C */       jal check_sp_dmem
  /* 001248 80000648 00000000 */       nop 
  /* 00124C 8000064C 3C048004 */       lui $a0, %hi(D_80044D48)
  /* 001250 80000650 3C058004 */       lui $a1, %hi(D_80044D44)
  /* 001254 80000654 24A54D44 */     addiu $a1, $a1, %lo(D_80044D44)
  /* 001258 80000658 24844D48 */     addiu $a0, $a0, %lo(D_80044D48)
  /* 00125C 8000065C 0C00D120 */       jal osCreateMesgQueue
  /* 001260 80000660 24060001 */     addiu $a2, $zero, 1
  /* 001264 80000664 3C0E8004 */       lui $t6, %hi(D_80040530)
  /* 001268 80000668 25CE0530 */     addiu $t6, $t6, %lo(D_80040530)
  /* 00126C 8000066C 3C048004 */       lui $a0, %hi(D_8003FF80)
  /* 001270 80000670 3C068000 */       lui $a2, %hi(thread3_scheduler)
  /* 001274 80000674 240F0078 */     addiu $t7, $zero, 0x78
  /* 001278 80000678 AFAF0014 */        sw $t7, 0x14($sp)
  /* 00127C 8000067C 24C62518 */     addiu $a2, $a2, %lo(thread3_scheduler)
  /* 001280 80000680 2484FF80 */     addiu $a0, $a0, %lo(D_8003FF80)
  /* 001284 80000684 AFAE0010 */        sw $t6, 0x10($sp)
  /* 001288 80000688 24050003 */     addiu $a1, $zero, 3
  /* 00128C 8000068C 0C00C788 */       jal osCreateThread
  /* 001290 80000690 00003825 */        or $a3, $zero, $zero
  /* 001294 80000694 3C19FEDC */       lui $t9, (0xFEDCBA98 >> 16) # 4275878552
  /* 001298 80000698 3739BA98 */       ori $t9, $t9, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 00129C 8000069C 24180000 */     addiu $t8, $zero, 0
  /* 0012A0 800006A0 3C018004 */       lui $at, %hi(D_8004016C)
  /* 0012A4 800006A4 3C048004 */       lui $a0, %hi(D_8003FF80)
  /* 0012A8 800006A8 2484FF80 */     addiu $a0, $a0, %lo(D_8003FF80)
  /* 0012AC 800006AC AC380168 */        sw $t8, %lo(D_80040168)($at)
  /* 0012B0 800006B0 0C00E464 */       jal osStartThread
  /* 0012B4 800006B4 AC39016C */        sw $t9, %lo(D_8004016C)($at)
  /* 0012B8 800006B8 3C048004 */       lui $a0, %hi(D_80044D48)
  /* 0012BC 800006BC 24844D48 */     addiu $a0, $a0, %lo(D_80044D48)
  /* 0012C0 800006C0 00002825 */        or $a1, $zero, $zero
  /* 0012C4 800006C4 0C00C084 */       jal osRecvMesg
  /* 0012C8 800006C8 24060001 */     addiu $a2, $zero, 1
  /* 0012CC 800006CC 3C088004 */       lui $t0, %hi(D_80040CE0)
  /* 0012D0 800006D0 25080CE0 */     addiu $t0, $t0, %lo(D_80040CE0)
  /* 0012D4 800006D4 3C048004 */       lui $a0, %hi(D_80040530)
  /* 0012D8 800006D8 3C068002 */       lui $a2, %hi(thread4)
  /* 0012DC 800006DC 2409006E */     addiu $t1, $zero, 0x6e
  /* 0012E0 800006E0 AFA90014 */        sw $t1, 0x14($sp)
  /* 0012E4 800006E4 24C6FF64 */     addiu $a2, $a2, %lo(thread4)
  /* 0012E8 800006E8 24840530 */     addiu $a0, $a0, %lo(D_80040530)
  /* 0012EC 800006EC AFA80010 */        sw $t0, 0x10($sp)
  /* 0012F0 800006F0 24050004 */     addiu $a1, $zero, 4
  /* 0012F4 800006F4 0C00C788 */       jal osCreateThread
  /* 0012F8 800006F8 00003825 */        or $a3, $zero, $zero
  /* 0012FC 800006FC 3C0BFEDC */       lui $t3, (0xFEDCBA98 >> 16) # 4275878552
  /* 001300 80000700 356BBA98 */       ori $t3, $t3, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 001304 80000704 240A0000 */     addiu $t2, $zero, 0
  /* 001308 80000708 3C018004 */       lui $at, %hi(D_8004071C)
  /* 00130C 8000070C 3C048004 */       lui $a0, %hi(D_80040530)
  /* 001310 80000710 24840530 */     addiu $a0, $a0, %lo(D_80040530)
  /* 001314 80000714 AC2A0718 */        sw $t2, %lo(D_80040718)($at)
  /* 001318 80000718 0C00E464 */       jal osStartThread
  /* 00131C 8000071C AC2B071C */        sw $t3, %lo(D_8004071C)($at)
  /* 001320 80000720 3C048004 */       lui $a0, %hi(D_80044D48)
  /* 001324 80000724 24844D48 */     addiu $a0, $a0, %lo(D_80044D48)
  /* 001328 80000728 00002825 */        or $a1, $zero, $zero
  /* 00132C 8000072C 0C00C084 */       jal osRecvMesg
  /* 001330 80000730 24060001 */     addiu $a2, $zero, 1
  /* 001334 80000734 3C0C8004 */       lui $t4, %hi(D_80044C40)
  /* 001338 80000738 258C4C40 */     addiu $t4, $t4, %lo(D_80044C40)
  /* 00133C 8000073C 3C048004 */       lui $a0, %hi(D_80044290)
  /* 001340 80000740 3C068000 */       lui $a2, %hi(thread6)
  /* 001344 80000744 240D0073 */     addiu $t5, $zero, 0x73
  /* 001348 80000748 AFAD0014 */        sw $t5, 0x14($sp)
  /* 00134C 8000074C 24C64770 */     addiu $a2, $a2, %lo(thread6)
  /* 001350 80000750 24844290 */     addiu $a0, $a0, %lo(D_80044290)
  /* 001354 80000754 AFAC0010 */        sw $t4, 0x10($sp)
  /* 001358 80000758 24050006 */     addiu $a1, $zero, 6
  /* 00135C 8000075C 0C00C788 */       jal osCreateThread
  /* 001360 80000760 00003825 */        or $a3, $zero, $zero
  /* 001364 80000764 3C0FFEDC */       lui $t7, (0xFEDCBA98 >> 16) # 4275878552
  /* 001368 80000768 35EFBA98 */       ori $t7, $t7, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 00136C 8000076C 240E0000 */     addiu $t6, $zero, 0
  /* 001370 80000770 3C018004 */       lui $at, %hi(D_8004447C)
  /* 001374 80000774 3C048004 */       lui $a0, %hi(D_80044290)
  /* 001378 80000778 24844290 */     addiu $a0, $a0, %lo(D_80044290)
  /* 00137C 8000077C AC2E4478 */        sw $t6, %lo(D_80044478)($at)
  /* 001380 80000780 0C00E464 */       jal osStartThread
  /* 001384 80000784 AC2F447C */        sw $t7, %lo(D_8004447C)($at)
  /* 001388 80000788 3C048004 */       lui $a0, %hi(D_80044D48)
  /* 00138C 8000078C 24844D48 */     addiu $a0, $a0, %lo(D_80044D48)
  /* 001390 80000790 00002825 */        or $a1, $zero, $zero
  /* 001394 80000794 0C00C084 */       jal osRecvMesg
  /* 001398 80000798 24060001 */     addiu $a2, $zero, 1
  /* 00139C 8000079C 0C001AE0 */       jal func_80006B80
  /* 0013A0 800007A0 00000000 */       nop 
  /* 0013A4 800007A4 3C048004 */       lui $a0, %hi(D_8003B6B0)
  /* 0013A8 800007A8 0C000AF9 */       jal load_overlay
  /* 0013AC 800007AC 2484B6B0 */     addiu $a0, $a0, %lo(D_8003B6B0)
  /* 0013B0 800007B0 0C028660 */       jal load_overlay_set
  /* 0013B4 800007B4 00002025 */        or $a0, $zero, $zero
  /* 0013B8 800007B8 8FBF001C */        lw $ra, 0x1c($sp)
  /* 0013BC 800007BC 27BD0020 */     addiu $sp, $sp, 0x20
  /* 0013C0 800007C0 03E00008 */        jr $ra
  /* 0013C4 800007C4 00000000 */       nop 

glabel thread1_idle
  /* 0013C8 800007C8 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 0013CC 800007CC AFBF001C */        sw $ra, 0x1c($sp)
  /* 0013D0 800007D0 0C008CCE */       jal start_thread8
  /* 0013D4 800007D4 AFA40020 */        sw $a0, 0x20($sp)
  /* 0013D8 800007D8 3C0E8004 */       lui $t6, %hi(D_80044290)
  /* 0013DC 800007DC 25CE4290 */     addiu $t6, $t6, %lo(D_80044290)
  /* 0013E0 800007E0 3C048004 */       lui $a0, %hi(D_80040CE0)
  /* 0013E4 800007E4 3C068000 */       lui $a2, %hi(thread5_main)
  /* 0013E8 800007E8 240F0032 */     addiu $t7, $zero, 0x32
  /* 0013EC 800007EC AFAF0014 */        sw $t7, 0x14($sp)
  /* 0013F0 800007F0 24C605D8 */     addiu $a2, $a2, %lo(thread5_main)
  /* 0013F4 800007F4 24840CE0 */     addiu $a0, $a0, %lo(D_80040CE0)
  /* 0013F8 800007F8 AFAE0010 */        sw $t6, 0x10($sp)
  /* 0013FC 800007FC 24050005 */     addiu $a1, $zero, 5
  /* 001400 80000800 0C00C788 */       jal osCreateThread
  /* 001404 80000804 8FA70020 */        lw $a3, 0x20($sp)
  /* 001408 80000808 3C088004 */       lui $t0, %hi(D_8003B6D4)
  /* 00140C 8000080C 8D08B6D4 */        lw $t0, %lo(D_8003B6D4)($t0)
  /* 001410 80000810 3C19FEDC */       lui $t9, (0xFEDCBA98 >> 16) # 4275878552
  /* 001414 80000814 3739BA98 */       ori $t9, $t9, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 001418 80000818 24180000 */     addiu $t8, $zero, 0
  /* 00141C 8000081C 3C018004 */       lui $at, %hi(D_80040ECC)
  /* 001420 80000820 AC380EC8 */        sw $t8, %lo(D_80040EC8)($at)
  /* 001424 80000824 15000004 */      bnez $t0, .L80000838
  /* 001428 80000828 AC390ECC */        sw $t9, %lo(D_80040ECC)($at)
  /* 00142C 8000082C 3C048004 */       lui $a0, %hi(D_80040CE0)
  /* 001430 80000830 0C00E464 */       jal osStartThread
  /* 001434 80000834 24840CE0 */     addiu $a0, $a0, %lo(D_80040CE0)
  .L80000838:
  /* 001438 80000838 00002025 */        or $a0, $zero, $zero
  /* 00143C 8000083C 0C00D1E4 */       jal osSetThreadPri
  /* 001440 80000840 00002825 */        or $a1, $zero, $zero
  .L80000844:
  /* 001444 80000844 1000FFFF */         b .L80000844
  /* 001448 80000848 00000000 */       nop 
  /* 00144C 8000084C 00000000 */       nop 
# Maybe start of new file
  /* 001450 80000850 00000000 */       nop 
  /* 001454 80000854 00000000 */       nop 
  /* 001458 80000858 00000000 */       nop 
  /* 00145C 8000085C 00000000 */       nop 
# Maybe start of new file
  /* 001460 80000860 8FBF001C */        lw $ra, 0x1c($sp)
  /* 001464 80000864 27BD0020 */     addiu $sp, $sp, 0x20
  /* 001468 80000868 03E00008 */        jr $ra
  /* 00146C 8000086C 00000000 */       nop 

glabel ssb_main
  /* 001470 80000870 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 001474 80000874 3C0FFEDC */       lui $t7, (0xFEDCBA98 >> 16) # 4275878552
  /* 001478 80000878 AFBF001C */        sw $ra, 0x1c($sp)
  /* 00147C 8000087C 35EFBA98 */       ori $t7, $t7, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 001480 80000880 240E0000 */     addiu $t6, $zero, 0
  /* 001484 80000884 3C018004 */       lui $at, %hi(D_8003FB0C)
  /* 001488 80000888 AC2EFB08 */        sw $t6, %lo(D_8003FB08)($at)
  /* 00148C 8000088C AC2FFB0C */        sw $t7, %lo(D_8003FB0C)($at)
  /* 001490 80000890 0C00E5AC */       jal __osSetWatchLo
  /* 001494 80000894 3C040490 */       lui $a0, 0x490
  /* 001498 80000898 0C00C894 */       jal osInitialize
  /* 00149C 8000089C 00000000 */       nop 
  /* 0014A0 800008A0 3C188004 */       lui $t8, %hi(D_8003FF80)
  /* 0014A4 800008A4 2718FF80 */     addiu $t8, $t8, %lo(D_8003FF80)
  /* 0014A8 800008A8 3C048004 */       lui $a0, %hi(D_8003FCD0)
  /* 0014AC 800008AC 3C068000 */       lui $a2, %hi(thread1_idle)
  /* 0014B0 800008B0 3C078004 */       lui $a3, %hi(D_80044E40)
  /* 0014B4 800008B4 2419007F */     addiu $t9, $zero, 0x7f
  /* 0014B8 800008B8 AFB90014 */        sw $t9, 0x14($sp)
  /* 0014BC 800008BC 24E74E40 */     addiu $a3, $a3, %lo(D_80044E40)
  /* 0014C0 800008C0 24C607C8 */     addiu $a2, $a2, %lo(thread1_idle)
  /* 0014C4 800008C4 2484FCD0 */     addiu $a0, $a0, %lo(D_8003FCD0)
  /* 0014C8 800008C8 AFB80010 */        sw $t8, 0x10($sp)
  /* 0014CC 800008CC 0C00C788 */       jal osCreateThread
  /* 0014D0 800008D0 24050001 */     addiu $a1, $zero, 1
  /* 0014D4 800008D4 3C09FEDC */       lui $t1, (0xFEDCBA98 >> 16) # 4275878552
  /* 0014D8 800008D8 3529BA98 */       ori $t1, $t1, (0xFEDCBA98 & 0xFFFF) # 4275878552
  /* 0014DC 800008DC 24080000 */     addiu $t0, $zero, 0
  /* 0014E0 800008E0 3C018004 */       lui $at, %hi(D_8003FEBC)
  /* 0014E4 800008E4 3C048004 */       lui $a0, %hi(D_8003FCD0)
  /* 0014E8 800008E8 2484FCD0 */     addiu $a0, $a0, %lo(D_8003FCD0)
  /* 0014EC 800008EC AC28FEB8 */        sw $t0, %lo(D_8003FEB8)($at)
  /* 0014F0 800008F0 0C00E464 */       jal osStartThread
  /* 0014F4 800008F4 AC29FEBC */        sw $t1, %lo(D_8003FEBC)($at)
  /* 0014F8 800008F8 8FBF001C */        lw $ra, 0x1c($sp)
  /* 0014FC 800008FC 27BD0020 */     addiu $sp, $sp, 0x20
  /* 001500 80000900 03E00008 */        jr $ra
  /* 001504 80000904 00000000 */       nop 

  /* 001508 80000908 00000000 */       nop 
  /* 00150C 8000090C 00000000 */       nop 
