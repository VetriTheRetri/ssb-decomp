.section .text
glabel func_800210C0
  /* 021CC0 800210C0 27BDFFF0 */     addiu $sp, $sp, -0x10
  /* 021CC4 800210C4 AFB1000C */        sw $s1, 0xc($sp)
  /* 021CC8 800210C8 AFB00008 */        sw $s0, 8($sp)
  /* 021CCC 800210CC 00808025 */        or $s0, $a0, $zero
  /* 021CD0 800210D0 00A08825 */        or $s1, $a1, $zero
  /* 021CD4 800210D4 04C00193 */      bltz $a2, .L80021724
  /* 021CD8 800210D8 AFA7001C */        sw $a3, 0x1c($sp)
  /* 021CDC 800210DC 28C10011 */      slti $at, $a2, 0x11
  /* 021CE0 800210E0 10200190 */      beqz $at, .L80021724
  /* 021CE4 800210E4 00067140 */       sll $t6, $a2, 5
  /* 021CE8 800210E8 3C0F8004 */       lui $t7, %hi(D_8003CC30)
  /* 021CEC 800210EC 25EFCC30 */     addiu $t7, $t7, %lo(D_8003CC30)
  /* 021CF0 800210F0 01CF2821 */      addu $a1, $t6, $t7
  /* 021CF4 800210F4 8CB80000 */        lw $t8, ($a1)
  /* 021CF8 800210F8 3C088004 */       lui $t0, %hi(D_800465B0)
  /* 021CFC 800210FC 250865B0 */     addiu $t0, $t0, %lo(D_800465B0)
  /* 021D00 80021100 17000009 */      bnez $t8, .L80021128
  /* 021D04 80021104 8D020000 */        lw $v0, ($t0) # D_800465B0 + 0
  /* 021D08 80021108 3C0C8004 */       lui $t4, %hi(gCurrScreenHeight)
  /* 021D0C 8002110C 3C098004 */       lui $t1, %hi(gCurrScreenWidth)
  /* 021D10 80021110 25296678 */     addiu $t1, $t1, %lo(gCurrScreenWidth)
  /* 021D14 80021114 258C667C */     addiu $t4, $t4, %lo(gCurrScreenHeight)
  /* 021D18 80021118 240D00F0 */     addiu $t5, $zero, 0xf0
  /* 021D1C 8002111C 3C0BF600 */       lui $t3, 0xf600
  /* 021D20 80021120 10000063 */         b .L800212B0
  /* 021D24 80021124 240A0140 */     addiu $t2, $zero, 0x140
  .L80021128:
  /* 021D28 80021128 3C098004 */       lui $t1, %hi(gCurrScreenWidth)
  /* 021D2C 8002112C 3C198004 */       lui $t9, %hi(D_8003CBB0 + 8)
  /* 021D30 80021130 8F39CBB8 */        lw $t9, %lo(D_8003CBB0 + 8)($t9)
  /* 021D34 80021134 25296678 */     addiu $t1, $t1, %lo(gCurrScreenWidth)
  /* 021D38 80021138 8D2F0000 */        lw $t7, ($t1) # gCurrScreenWidth + 0
  /* 021D3C 8002113C 03307021 */      addu $t6, $t9, $s0
  /* 021D40 80021140 240A0140 */     addiu $t2, $zero, 0x140
  /* 021D44 80021144 01CF0019 */     multu $t6, $t7
  /* 021D48 80021148 3C0BF600 */       lui $t3, 0xf600
  /* 021D4C 8002114C 3C0C8004 */       lui $t4, %hi(gCurrScreenHeight)
  /* 021D50 80021150 258C667C */     addiu $t4, $t4, %lo(gCurrScreenHeight)
  /* 021D54 80021154 240D00F0 */     addiu $t5, $zero, 0xf0
  /* 021D58 80021158 00403825 */        or $a3, $v0, $zero
  /* 021D5C 8002115C 24420008 */     addiu $v0, $v0, 8
  /* 021D60 80021160 0000C012 */      mflo $t8
  /* 021D64 80021164 00000000 */       nop 
  /* 021D68 80021168 00000000 */       nop 
  /* 021D6C 8002116C 030A001A */       div $zero, $t8, $t2
  /* 021D70 80021170 0000C812 */      mflo $t9
  /* 021D74 80021174 332E03FF */      andi $t6, $t9, 0x3ff
  /* 021D78 80021178 15400002 */      bnez $t2, .L80021184
  /* 021D7C 8002117C 00000000 */       nop 
  /* 021D80 80021180 0007000D */     break 7
  .L80021184:
  /* 021D84 80021184 2401FFFF */     addiu $at, $zero, -1
  /* 021D88 80021188 15410004 */       bne $t2, $at, .L8002119C
  /* 021D8C 8002118C 3C018000 */       lui $at, 0x8000
  /* 021D90 80021190 17010002 */       bne $t8, $at, .L8002119C
  /* 021D94 80021194 00000000 */       nop 
  /* 021D98 80021198 0006000D */     break 6
  .L8002119C:
  /* 021D9C 8002119C 000E7B80 */       sll $t7, $t6, 0xe
  /* 021DA0 800211A0 3C198004 */       lui $t9, %hi(D_8003CBB0 + 12)
  /* 021DA4 800211A4 8F39CBBC */        lw $t9, %lo(D_8003CBB0 + 12)($t9)
  /* 021DA8 800211A8 01EBC025 */        or $t8, $t7, $t3
  /* 021DAC 800211AC 8D8F0000 */        lw $t7, ($t4) # gCurrScreenHeight + 0
  /* 021DB0 800211B0 02397021 */      addu $t6, $s1, $t9
  /* 021DB4 800211B4 01CF0019 */     multu $t6, $t7
  /* 021DB8 800211B8 0000C812 */      mflo $t9
  /* 021DBC 800211BC 00000000 */       nop 
  /* 021DC0 800211C0 00000000 */       nop 
  /* 021DC4 800211C4 032D001A */       div $zero, $t9, $t5
  /* 021DC8 800211C8 00007012 */      mflo $t6
  /* 021DCC 800211CC 31CF03FF */      andi $t7, $t6, 0x3ff
  /* 021DD0 800211D0 15A00002 */      bnez $t5, .L800211DC
  /* 021DD4 800211D4 00000000 */       nop 
  /* 021DD8 800211D8 0007000D */     break 7
  .L800211DC:
  /* 021DDC 800211DC 2401FFFF */     addiu $at, $zero, -1
  /* 021DE0 800211E0 15A10004 */       bne $t5, $at, .L800211F4
  /* 021DE4 800211E4 3C018000 */       lui $at, 0x8000
  /* 021DE8 800211E8 17210002 */       bne $t9, $at, .L800211F4
  /* 021DEC 800211EC 00000000 */       nop 
  /* 021DF0 800211F0 0006000D */     break 6
  .L800211F4:
  /* 021DF4 800211F4 000FC880 */       sll $t9, $t7, 2
  /* 021DF8 800211F8 03197025 */        or $t6, $t8, $t9
  /* 021DFC 800211FC ACEE0000 */        sw $t6, ($a3)
  /* 021E00 80021200 3C0F8004 */       lui $t7, %hi(D_8003CBB0)
  /* 021E04 80021204 8DEFCBB0 */        lw $t7, %lo(D_8003CBB0)($t7)
  /* 021E08 80021208 8D390000 */        lw $t9, ($t1) # gCurrScreenWidth + 0
  /* 021E0C 8002120C 01F0C021 */      addu $t8, $t7, $s0
  /* 021E10 80021210 03190019 */     multu $t8, $t9
  /* 021E14 80021214 00007012 */      mflo $t6
  /* 021E18 80021218 00000000 */       nop 
  /* 021E1C 8002121C 00000000 */       nop 
# Maybe start of new file
  /* 021E20 80021220 01CA001A */       div $zero, $t6, $t2
  /* 021E24 80021224 15400002 */      bnez $t2, .L80021230
  /* 021E28 80021228 00000000 */       nop 
  /* 021E2C 8002122C 0007000D */     break 7
  .L80021230:
  /* 021E30 80021230 2401FFFF */     addiu $at, $zero, -1
  /* 021E34 80021234 15410004 */       bne $t2, $at, .L80021248
  /* 021E38 80021238 3C018000 */       lui $at, 0x8000
  /* 021E3C 8002123C 15C10002 */       bne $t6, $at, .L80021248
  /* 021E40 80021240 00000000 */       nop 
  /* 021E44 80021244 0006000D */     break 6
  .L80021248:
  /* 021E48 80021248 00007812 */      mflo $t7
  /* 021E4C 8002124C 31F803FF */      andi $t8, $t7, 0x3ff
  /* 021E50 80021250 3C0E8004 */       lui $t6, %hi(D_8003CBB0 + 4)
  /* 021E54 80021254 8DCECBB4 */        lw $t6, %lo(D_8003CBB0 + 4)($t6)
  /* 021E58 80021258 0018CB80 */       sll $t9, $t8, 0xe
  /* 021E5C 8002125C 8D980000 */        lw $t8, ($t4) # gCurrScreenHeight + 0
  /* 021E60 80021260 022E7821 */      addu $t7, $s1, $t6
  /* 021E64 80021264 01F80019 */     multu $t7, $t8
  /* 021E68 80021268 00007012 */      mflo $t6
  /* 021E6C 8002126C 00000000 */       nop 
  /* 021E70 80021270 00000000 */       nop 
  /* 021E74 80021274 01CD001A */       div $zero, $t6, $t5
  /* 021E78 80021278 00007812 */      mflo $t7
  /* 021E7C 8002127C 31F803FF */      andi $t8, $t7, 0x3ff
  /* 021E80 80021280 15A00002 */      bnez $t5, .L8002128C
  /* 021E84 80021284 00000000 */       nop 
  /* 021E88 80021288 0007000D */     break 7
  .L8002128C:
  /* 021E8C 8002128C 2401FFFF */     addiu $at, $zero, -1
  /* 021E90 80021290 15A10004 */       bne $t5, $at, .L800212A4
  /* 021E94 80021294 3C018000 */       lui $at, 0x8000
  /* 021E98 80021298 15C10002 */       bne $t6, $at, .L800212A4
  /* 021E9C 8002129C 00000000 */       nop 
  /* 021EA0 800212A0 0006000D */     break 6
  .L800212A4:
  /* 021EA4 800212A4 00187080 */       sll $t6, $t8, 2
  /* 021EA8 800212A8 032E7825 */        or $t7, $t9, $t6
  /* 021EAC 800212AC ACEF0004 */        sw $t7, 4($a3)
  .L800212B0:
  /* 021EB0 800212B0 24A40004 */     addiu $a0, $a1, 4
  /* 021EB4 800212B4 3C038004 */       lui $v1, %hi(D_8003CBB0 + 0x10)
  /* 021EB8 800212B8 2463CBC0 */     addiu $v1, $v1, %lo(D_8003CBB0 + 0x10)
  /* 021EBC 800212BC 24050007 */     addiu $a1, $zero, 7
  /* 021EC0 800212C0 24060001 */     addiu $a2, $zero, 1
  .L800212C4:
  /* 021EC4 800212C4 8C980000 */        lw $t8, ($a0)
  /* 021EC8 800212C8 24C60002 */     addiu $a2, $a2, 2
  /* 021ECC 800212CC 53000059 */      beql $t8, $zero, .L80021434
  /* 021ED0 800212D0 8C980004 */        lw $t8, 4($a0)
  /* 021ED4 800212D4 8C790008 */        lw $t9, 8($v1) # D_8003CBC0 + 8
  /* 021ED8 800212D8 8D2F0000 */        lw $t7, ($t1) # gCurrScreenWidth + 0
  /* 021EDC 800212DC 00403825 */        or $a3, $v0, $zero
  /* 021EE0 800212E0 03307021 */      addu $t6, $t9, $s0
  /* 021EE4 800212E4 01CF0019 */     multu $t6, $t7
  /* 021EE8 800212E8 24420008 */     addiu $v0, $v0, 8
  /* 021EEC 800212EC 0000C012 */      mflo $t8
  /* 021EF0 800212F0 00000000 */       nop 
  /* 021EF4 800212F4 00000000 */       nop 
  /* 021EF8 800212F8 030A001A */       div $zero, $t8, $t2
  /* 021EFC 800212FC 0000C812 */      mflo $t9
  /* 021F00 80021300 332E03FF */      andi $t6, $t9, 0x3ff
  /* 021F04 80021304 15400002 */      bnez $t2, .L80021310
  /* 021F08 80021308 00000000 */       nop 
  /* 021F0C 8002130C 0007000D */     break 7
  .L80021310:
  /* 021F10 80021310 2401FFFF */     addiu $at, $zero, -1
  /* 021F14 80021314 15410004 */       bne $t2, $at, .L80021328
  /* 021F18 80021318 3C018000 */       lui $at, 0x8000
  /* 021F1C 8002131C 17010002 */       bne $t8, $at, .L80021328
  /* 021F20 80021320 00000000 */       nop 
  /* 021F24 80021324 0006000D */     break 6
  .L80021328:
  /* 021F28 80021328 000E7B80 */       sll $t7, $t6, 0xe
  /* 021F2C 8002132C 8C79000C */        lw $t9, 0xc($v1) # D_8003CBC0 + 12
  /* 021F30 80021330 01EBC025 */        or $t8, $t7, $t3
  /* 021F34 80021334 8D8F0000 */        lw $t7, ($t4) # gCurrScreenHeight + 0
  /* 021F38 80021338 02397021 */      addu $t6, $s1, $t9
  /* 021F3C 8002133C 01CF0019 */     multu $t6, $t7
  /* 021F40 80021340 0000C812 */      mflo $t9
  /* 021F44 80021344 00000000 */       nop 
  /* 021F48 80021348 00000000 */       nop 
  /* 021F4C 8002134C 032D001A */       div $zero, $t9, $t5
  /* 021F50 80021350 00007012 */      mflo $t6
  /* 021F54 80021354 31CF03FF */      andi $t7, $t6, 0x3ff
  /* 021F58 80021358 15A00002 */      bnez $t5, .L80021364
  /* 021F5C 8002135C 00000000 */       nop 
  /* 021F60 80021360 0007000D */     break 7
  .L80021364:
  /* 021F64 80021364 2401FFFF */     addiu $at, $zero, -1
  /* 021F68 80021368 15A10004 */       bne $t5, $at, .L8002137C
  /* 021F6C 8002136C 3C018000 */       lui $at, 0x8000
  /* 021F70 80021370 17210002 */       bne $t9, $at, .L8002137C
  /* 021F74 80021374 00000000 */       nop 
  /* 021F78 80021378 0006000D */     break 6
  .L8002137C:
  /* 021F7C 8002137C 000FC880 */       sll $t9, $t7, 2
  /* 021F80 80021380 03197025 */        or $t6, $t8, $t9
  /* 021F84 80021384 ACEE0000 */        sw $t6, ($a3)
  /* 021F88 80021388 8C6F0000 */        lw $t7, ($v1) # D_8003CBC0 + 0
  /* 021F8C 8002138C 8D390000 */        lw $t9, ($t1) # gCurrScreenWidth + 0
  /* 021F90 80021390 01F0C021 */      addu $t8, $t7, $s0
  /* 021F94 80021394 03190019 */     multu $t8, $t9
  /* 021F98 80021398 00007012 */      mflo $t6
  /* 021F9C 8002139C 00000000 */       nop 
  /* 021FA0 800213A0 00000000 */       nop 
  /* 021FA4 800213A4 01CA001A */       div $zero, $t6, $t2
  /* 021FA8 800213A8 00007812 */      mflo $t7
  /* 021FAC 800213AC 31F803FF */      andi $t8, $t7, 0x3ff
  /* 021FB0 800213B0 15400002 */      bnez $t2, .L800213BC
  /* 021FB4 800213B4 00000000 */       nop 
  /* 021FB8 800213B8 0007000D */     break 7
  .L800213BC:
  /* 021FBC 800213BC 2401FFFF */     addiu $at, $zero, -1
  /* 021FC0 800213C0 15410004 */       bne $t2, $at, .L800213D4
  /* 021FC4 800213C4 3C018000 */       lui $at, 0x8000
  /* 021FC8 800213C8 15C10002 */       bne $t6, $at, .L800213D4
  /* 021FCC 800213CC 00000000 */       nop 
  /* 021FD0 800213D0 0006000D */     break 6
  .L800213D4:
  /* 021FD4 800213D4 8C6E0004 */        lw $t6, 4($v1) # D_8003CBC0 + 4
  /* 021FD8 800213D8 0018CB80 */       sll $t9, $t8, 0xe
  /* 021FDC 800213DC 8D980000 */        lw $t8, ($t4) # gCurrScreenHeight + 0
  /* 021FE0 800213E0 022E7821 */      addu $t7, $s1, $t6
  /* 021FE4 800213E4 01F80019 */     multu $t7, $t8
  /* 021FE8 800213E8 00007012 */      mflo $t6
  /* 021FEC 800213EC 00000000 */       nop 
  /* 021FF0 800213F0 00000000 */       nop 
  /* 021FF4 800213F4 01CD001A */       div $zero, $t6, $t5
  /* 021FF8 800213F8 00007812 */      mflo $t7
  /* 021FFC 800213FC 31F803FF */      andi $t8, $t7, 0x3ff
  /* 022000 80021400 15A00002 */      bnez $t5, .L8002140C
  /* 022004 80021404 00000000 */       nop 
  /* 022008 80021408 0007000D */     break 7
  .L8002140C:
  /* 02200C 8002140C 2401FFFF */     addiu $at, $zero, -1
  /* 022010 80021410 15A10004 */       bne $t5, $at, .L80021424
  /* 022014 80021414 3C018000 */       lui $at, 0x8000
  /* 022018 80021418 15C10002 */       bne $t6, $at, .L80021424
  /* 02201C 8002141C 00000000 */       nop 
  /* 022020 80021420 0006000D */     break 6
  .L80021424:
  /* 022024 80021424 00187080 */       sll $t6, $t8, 2
  /* 022028 80021428 032E7825 */        or $t7, $t9, $t6
  /* 02202C 8002142C ACEF0004 */        sw $t7, 4($a3)
  /* 022030 80021430 8C980004 */        lw $t8, 4($a0)
  .L80021434:
  /* 022034 80021434 24840004 */     addiu $a0, $a0, 4
  /* 022038 80021438 24840004 */     addiu $a0, $a0, 4
  /* 02203C 8002143C 13000058 */      beqz $t8, .L800215A0
  /* 022040 80021440 24630010 */     addiu $v1, $v1, 0x10
  /* 022044 80021444 8C790008 */        lw $t9, 8($v1) # D_8003CBC0 + 8
  /* 022048 80021448 8D2F0000 */        lw $t7, ($t1) # gCurrScreenWidth + 0
  /* 02204C 8002144C 00403825 */        or $a3, $v0, $zero
  /* 022050 80021450 03307021 */      addu $t6, $t9, $s0
  /* 022054 80021454 01CF0019 */     multu $t6, $t7
  /* 022058 80021458 24420008 */     addiu $v0, $v0, 8
  /* 02205C 8002145C 0000C012 */      mflo $t8
  /* 022060 80021460 00000000 */       nop 
  /* 022064 80021464 00000000 */       nop 
  /* 022068 80021468 030A001A */       div $zero, $t8, $t2
  /* 02206C 8002146C 0000C812 */      mflo $t9
  /* 022070 80021470 332E03FF */      andi $t6, $t9, 0x3ff
  /* 022074 80021474 15400002 */      bnez $t2, .L80021480
  /* 022078 80021478 00000000 */       nop 
  /* 02207C 8002147C 0007000D */     break 7
  .L80021480:
  /* 022080 80021480 2401FFFF */     addiu $at, $zero, -1
  /* 022084 80021484 15410004 */       bne $t2, $at, .L80021498
  /* 022088 80021488 3C018000 */       lui $at, 0x8000
  /* 02208C 8002148C 17010002 */       bne $t8, $at, .L80021498
  /* 022090 80021490 00000000 */       nop 
  /* 022094 80021494 0006000D */     break 6
  .L80021498:
  /* 022098 80021498 000E7B80 */       sll $t7, $t6, 0xe
  /* 02209C 8002149C 8C79000C */        lw $t9, 0xc($v1) # D_8003CBC0 + 12
  /* 0220A0 800214A0 01EBC025 */        or $t8, $t7, $t3
  /* 0220A4 800214A4 8D8F0000 */        lw $t7, ($t4) # gCurrScreenHeight + 0
  /* 0220A8 800214A8 02397021 */      addu $t6, $s1, $t9
  /* 0220AC 800214AC 01CF0019 */     multu $t6, $t7
  /* 0220B0 800214B0 0000C812 */      mflo $t9
  /* 0220B4 800214B4 00000000 */       nop 
  /* 0220B8 800214B8 00000000 */       nop 
  /* 0220BC 800214BC 032D001A */       div $zero, $t9, $t5
  /* 0220C0 800214C0 00007012 */      mflo $t6
  /* 0220C4 800214C4 31CF03FF */      andi $t7, $t6, 0x3ff
  /* 0220C8 800214C8 15A00002 */      bnez $t5, .L800214D4
  /* 0220CC 800214CC 00000000 */       nop 
  /* 0220D0 800214D0 0007000D */     break 7
  .L800214D4:
  /* 0220D4 800214D4 2401FFFF */     addiu $at, $zero, -1
  /* 0220D8 800214D8 15A10004 */       bne $t5, $at, .L800214EC
  /* 0220DC 800214DC 3C018000 */       lui $at, 0x8000
  /* 0220E0 800214E0 17210002 */       bne $t9, $at, .L800214EC
  /* 0220E4 800214E4 00000000 */       nop 
  /* 0220E8 800214E8 0006000D */     break 6
  .L800214EC:
  /* 0220EC 800214EC 000FC880 */       sll $t9, $t7, 2
  /* 0220F0 800214F0 03197025 */        or $t6, $t8, $t9
  /* 0220F4 800214F4 ACEE0000 */        sw $t6, ($a3)
  /* 0220F8 800214F8 8C6F0000 */        lw $t7, ($v1) # D_8003CBC0 + 0
  /* 0220FC 800214FC 8D390000 */        lw $t9, ($t1) # gCurrScreenWidth + 0
  /* 022100 80021500 01F0C021 */      addu $t8, $t7, $s0
  /* 022104 80021504 03190019 */     multu $t8, $t9
  /* 022108 80021508 00007012 */      mflo $t6
  /* 02210C 8002150C 00000000 */       nop 
  /* 022110 80021510 00000000 */       nop 
  /* 022114 80021514 01CA001A */       div $zero, $t6, $t2
  /* 022118 80021518 00007812 */      mflo $t7
  /* 02211C 8002151C 31F803FF */      andi $t8, $t7, 0x3ff
  /* 022120 80021520 15400002 */      bnez $t2, .L8002152C
  /* 022124 80021524 00000000 */       nop 
  /* 022128 80021528 0007000D */     break 7
  .L8002152C:
  /* 02212C 8002152C 2401FFFF */     addiu $at, $zero, -1
  /* 022130 80021530 15410004 */       bne $t2, $at, .L80021544
  /* 022134 80021534 3C018000 */       lui $at, 0x8000
  /* 022138 80021538 15C10002 */       bne $t6, $at, .L80021544
  /* 02213C 8002153C 00000000 */       nop 
  /* 022140 80021540 0006000D */     break 6
  .L80021544:
  /* 022144 80021544 8C6E0004 */        lw $t6, 4($v1) # D_8003CBC0 + 4
  /* 022148 80021548 0018CB80 */       sll $t9, $t8, 0xe
  /* 02214C 8002154C 8D980000 */        lw $t8, ($t4) # gCurrScreenHeight + 0
  /* 022150 80021550 022E7821 */      addu $t7, $s1, $t6
  /* 022154 80021554 01F80019 */     multu $t7, $t8
  /* 022158 80021558 00007012 */      mflo $t6
  /* 02215C 8002155C 00000000 */       nop 
  /* 022160 80021560 00000000 */       nop 
  /* 022164 80021564 01CD001A */       div $zero, $t6, $t5
  /* 022168 80021568 00007812 */      mflo $t7
  /* 02216C 8002156C 31F803FF */      andi $t8, $t7, 0x3ff
  /* 022170 80021570 15A00002 */      bnez $t5, .L8002157C
  /* 022174 80021574 00000000 */       nop 
  /* 022178 80021578 0007000D */     break 7
  .L8002157C:
  /* 02217C 8002157C 2401FFFF */     addiu $at, $zero, -1
  /* 022180 80021580 15A10004 */       bne $t5, $at, .L80021594
  /* 022184 80021584 3C018000 */       lui $at, 0x8000
  /* 022188 80021588 15C10002 */       bne $t6, $at, .L80021594
  /* 02218C 8002158C 00000000 */       nop 
  /* 022190 80021590 0006000D */     break 6
  .L80021594:
  /* 022194 80021594 00187080 */       sll $t6, $t8, 2
  /* 022198 80021598 032E7825 */        or $t7, $t9, $t6
  /* 02219C 8002159C ACEF0004 */        sw $t7, 4($a3)
  .L800215A0:
  /* 0221A0 800215A0 14C5FF48 */       bne $a2, $a1, .L800212C4
  /* 0221A4 800215A4 24630010 */     addiu $v1, $v1, 0x10
  
  /* 0221A8 800215A8 8FB8001C */        lw $t8, 0x1c($sp)
  /* 0221AC 800215AC 3C01800A */       lui $at, %hi(D_8009DA00)
  /* 0221B0 800215B0 AC23DA00 */        sw $v1, %lo(D_8009DA00)($at)
  /* 0221B4 800215B4 5300005B */      beql $t8, $zero, .L80021724
  /* 0221B8 800215B8 AD020000 */        sw $v0, ($t0) # D_800465B0 + 0
  /* 0221BC 800215BC 8C790008 */        lw $t9, 8($v1) # D_8003CBC0 + 8
  /* 0221C0 800215C0 8D2F0000 */        lw $t7, ($t1) # gCurrScreenWidth + 0
  /* 0221C4 800215C4 00402025 */        or $a0, $v0, $zero
  /* 0221C8 800215C8 03307021 */      addu $t6, $t9, $s0
  /* 0221CC 800215CC 01CF0019 */     multu $t6, $t7
  /* 0221D0 800215D0 24420008 */     addiu $v0, $v0, 8
  /* 0221D4 800215D4 0000C012 */      mflo $t8
  /* 0221D8 800215D8 00000000 */       nop 
  /* 0221DC 800215DC 00000000 */       nop 
# Maybe start of new file
  /* 0221E0 800215E0 030A001A */       div $zero, $t8, $t2
  /* 0221E4 800215E4 0000C812 */      mflo $t9
  /* 0221E8 800215E8 332E03FF */      andi $t6, $t9, 0x3ff
  /* 0221EC 800215EC 15400002 */      bnez $t2, .L800215F8
  /* 0221F0 800215F0 00000000 */       nop 
  /* 0221F4 800215F4 0007000D */     break 7
  .L800215F8:
  /* 0221F8 800215F8 2401FFFF */     addiu $at, $zero, -1
  /* 0221FC 800215FC 15410004 */       bne $t2, $at, .L80021610
  /* 022200 80021600 3C018000 */       lui $at, 0x8000
  /* 022204 80021604 17010002 */       bne $t8, $at, .L80021610
  /* 022208 80021608 00000000 */       nop 
  /* 02220C 8002160C 0006000D */     break 6
  .L80021610:
  /* 022210 80021610 000E7B80 */       sll $t7, $t6, 0xe
  /* 022214 80021614 8C79000C */        lw $t9, 0xc($v1) # D_8003CBC0 + 12
  /* 022218 80021618 01EBC025 */        or $t8, $t7, $t3
  /* 02221C 8002161C 8D8F0000 */        lw $t7, ($t4) # gCurrScreenHeight + 0
  /* 022220 80021620 02397021 */      addu $t6, $s1, $t9
  /* 022224 80021624 01CF0019 */     multu $t6, $t7
  /* 022228 80021628 0000C812 */      mflo $t9
  /* 02222C 8002162C 00000000 */       nop 
  /* 022230 80021630 00000000 */       nop 
  /* 022234 80021634 032D001A */       div $zero, $t9, $t5
  /* 022238 80021638 00007012 */      mflo $t6
  /* 02223C 8002163C 31CF03FF */      andi $t7, $t6, 0x3ff
  /* 022240 80021640 15A00002 */      bnez $t5, .L8002164C
  /* 022244 80021644 00000000 */       nop 
  /* 022248 80021648 0007000D */     break 7
  .L8002164C:
  /* 02224C 8002164C 2401FFFF */     addiu $at, $zero, -1
  /* 022250 80021650 15A10004 */       bne $t5, $at, .L80021664
  /* 022254 80021654 3C018000 */       lui $at, 0x8000
  /* 022258 80021658 17210002 */       bne $t9, $at, .L80021664
  /* 02225C 8002165C 00000000 */       nop 
  /* 022260 80021660 0006000D */     break 6
  .L80021664:
  /* 022264 80021664 000FC880 */       sll $t9, $t7, 2
  /* 022268 80021668 03197025 */        or $t6, $t8, $t9
  /* 02226C 8002166C AC8E0000 */        sw $t6, ($a0)
  /* 022270 80021670 8C6F0000 */        lw $t7, ($v1) # D_8003CBC0 + 0
  /* 022274 80021674 8D390000 */        lw $t9, ($t1) # gCurrScreenWidth + 0
  /* 022278 80021678 01F0C021 */      addu $t8, $t7, $s0
  /* 02227C 8002167C 03190019 */     multu $t8, $t9
  /* 022280 80021680 00007012 */      mflo $t6
  /* 022284 80021684 00000000 */       nop 
  /* 022288 80021688 00000000 */       nop 
  /* 02228C 8002168C 01CA001A */       div $zero, $t6, $t2
  /* 022290 80021690 00007812 */      mflo $t7
  /* 022294 80021694 31F803FF */      andi $t8, $t7, 0x3ff
  /* 022298 80021698 15400002 */      bnez $t2, .L800216A4
  /* 02229C 8002169C 00000000 */       nop 
  /* 0222A0 800216A0 0007000D */     break 7
  .L800216A4:
  /* 0222A4 800216A4 2401FFFF */     addiu $at, $zero, -1
  /* 0222A8 800216A8 15410004 */       bne $t2, $at, .L800216BC
  /* 0222AC 800216AC 3C018000 */       lui $at, 0x8000
  /* 0222B0 800216B0 15C10002 */       bne $t6, $at, .L800216BC
  /* 0222B4 800216B4 00000000 */       nop 
  /* 0222B8 800216B8 0006000D */     break 6
  .L800216BC:
  /* 0222BC 800216BC 8C6E0004 */        lw $t6, 4($v1) # D_8003CBC0 + 4
  /* 0222C0 800216C0 0018CB80 */       sll $t9, $t8, 0xe
  /* 0222C4 800216C4 8D980000 */        lw $t8, ($t4) # gCurrScreenHeight + 0
  /* 0222C8 800216C8 022E7821 */      addu $t7, $s1, $t6
  /* 0222CC 800216CC 01F80019 */     multu $t7, $t8
  /* 0222D0 800216D0 00007012 */      mflo $t6
  /* 0222D4 800216D4 00000000 */       nop 
  /* 0222D8 800216D8 00000000 */       nop 
  /* 0222DC 800216DC 01CD001A */       div $zero, $t6, $t5
  /* 0222E0 800216E0 15A00002 */      bnez $t5, .L800216EC
  /* 0222E4 800216E4 00000000 */       nop 
  /* 0222E8 800216E8 0007000D */     break 7
  .L800216EC:
  /* 0222EC 800216EC 2401FFFF */     addiu $at, $zero, -1
  /* 0222F0 800216F0 15A10004 */       bne $t5, $at, .L80021704
  /* 0222F4 800216F4 3C018000 */       lui $at, 0x8000
  /* 0222F8 800216F8 15C10002 */       bne $t6, $at, .L80021704
  /* 0222FC 800216FC 00000000 */       nop 
  /* 022300 80021700 0006000D */     break 6
  .L80021704:
  /* 022304 80021704 00007812 */      mflo $t7
  /* 022308 80021708 31F803FF */      andi $t8, $t7, 0x3ff
  /* 02230C 8002170C 00187080 */       sll $t6, $t8, 2
  /* 022310 80021710 032E7825 */        or $t7, $t9, $t6
  /* 022314 80021714 AC8F0004 */        sw $t7, 4($a0)
  /* 022318 80021718 3C01800A */       lui $at, %hi(D_8009DA00)
  /* 02231C 8002171C AC23DA00 */        sw $v1, %lo(D_8009DA00)($at)
  /* 022320 80021720 AD020000 */        sw $v0, ($t0) # D_800465B0 + 0
  .L80021724:
  /* 022324 80021724 8FB00008 */        lw $s0, 8($sp)
  /* 022328 80021728 8FB1000C */        lw $s1, 0xc($sp)
  /* 02232C 8002172C 03E00008 */        jr $ra
  /* 022330 80021730 27BD0010 */     addiu $sp, $sp, 0x10

