.section .late_rodata

glabel D_8003E3C0
  /* 3DFC0 03EFC0 8003E3C0 */
  .word 0x4422f983 # .float 651.8986

.section .text
glabel hal_rotate_rpy_translate_scale
  /* 01D188 8001C588 27BDFFB8 */     addiu $sp, $sp, -0x48
  /* 01D18C 8001C58C 3C018004 */       lui $at, %hi(D_8003E3C0)
  /* 01D190 8001C590 C420E3C0 */      lwc1 $f0, %lo(D_8003E3C0)($at)
  /* 01D194 8001C594 C7A40058 */      lwc1 $f4, 0x58($sp)
  /* 01D198 8001C598 C7AA005C */      lwc1 $f10, 0x5c($sp)
  /* 01D19C 8001C59C 44857000 */      mtc1 $a1, $f14
  /* 01D1A0 8001C5A0 46002182 */     mul.s $f6, $f4, $f0
  /* 01D1A4 8001C5A4 C7A40060 */      lwc1 $f4, 0x60($sp)
  /* 01D1A8 8001C5A8 3C0C8004 */       lui $t4, %hi(gSinTable)
  /* 01D1AC 8001C5AC 46005402 */     mul.s $f16, $f10, $f0
  /* 01D1B0 8001C5B0 258CB950 */     addiu $t4, $t4, %lo(gSinTable)
  /* 01D1B4 8001C5B4 3C014380 */       lui $at, (0x43800000 >> 16) # 256.0
  /* 01D1B8 8001C5B8 44866000 */      mtc1 $a2, $f12
  /* 01D1BC 8001C5BC AFA70054 */        sw $a3, 0x54($sp)
  /* 01D1C0 8001C5C0 C7AA0068 */      lwc1 $f10, 0x68($sp)
  /* 01D1C4 8001C5C4 4600320D */ trunc.w.s $f8, $f6
  /* 01D1C8 8001C5C8 46002182 */     mul.s $f6, $f4, $f0
  /* 01D1CC 8001C5CC 44810000 */      mtc1 $at, $f0 # 256.0 to cop1
  /* 01D1D0 8001C5D0 C7A4006C */      lwc1 $f4, 0x6c($sp)
  /* 01D1D4 8001C5D4 44034000 */      mfc1 $v1, $f8
  /* 01D1D8 8001C5D8 4600848D */ trunc.w.s $f18, $f16
  /* 01D1DC 8001C5DC 30630FFF */      andi $v1, $v1, 0xfff
  /* 01D1E0 8001C5E0 3065FFFF */      andi $a1, $v1, 0xffff
  /* 01D1E4 8001C5E4 30AF07FF */      andi $t7, $a1, 0x7ff
  /* 01D1E8 8001C5E8 000FC040 */       sll $t8, $t7, 1
  /* 01D1EC 8001C5EC 0198C821 */      addu $t9, $t4, $t8
  /* 01D1F0 8001C5F0 30AE0800 */      andi $t6, $a1, 0x800
  /* 01D1F4 8001C5F4 44039000 */      mfc1 $v1, $f18
  /* 01D1F8 8001C5F8 972A0000 */       lhu $t2, ($t9)
  /* 01D1FC 8001C5FC 11C00002 */      beqz $t6, .L8001C608
  /* 01D200 8001C600 4600320D */ trunc.w.s $f8, $f6
  /* 01D204 8001C604 000A5023 */      negu $t2, $t2
  .L8001C608:
  /* 01D208 8001C608 24A20400 */     addiu $v0, $a1, 0x400
  /* 01D20C 8001C60C 304F07FF */      andi $t7, $v0, 0x7ff
  /* 01D210 8001C610 000FC040 */       sll $t8, $t7, 1
  /* 01D214 8001C614 0198C821 */      addu $t9, $t4, $t8
  /* 01D218 8001C618 304E0800 */      andi $t6, $v0, 0x800
  /* 01D21C 8001C61C 11C00002 */      beqz $t6, .L8001C628
  /* 01D220 8001C620 97280000 */       lhu $t0, ($t9)
  /* 01D224 8001C624 00084023 */      negu $t0, $t0
  .L8001C628:
  /* 01D228 8001C628 30630FFF */      andi $v1, $v1, 0xfff
  /* 01D22C 8001C62C 3065FFFF */      andi $a1, $v1, 0xffff
  /* 01D230 8001C630 30B807FF */      andi $t8, $a1, 0x7ff
  /* 01D234 8001C634 0018C840 */       sll $t9, $t8, 1
  /* 01D238 8001C638 01997021 */      addu $t6, $t4, $t9
  /* 01D23C 8001C63C 30AF0800 */      andi $t7, $a1, 0x800
  /* 01D240 8001C640 11E00002 */      beqz $t7, .L8001C64C
  /* 01D244 8001C644 95C90000 */       lhu $t1, ($t6)
  /* 01D248 8001C648 00094823 */      negu $t1, $t1
  .L8001C64C:
  /* 01D24C 8001C64C 24A20400 */     addiu $v0, $a1, 0x400
  /* 01D250 8001C650 305807FF */      andi $t8, $v0, 0x7ff
  /* 01D254 8001C654 0018C840 */       sll $t9, $t8, 1
  /* 01D258 8001C658 01997021 */      addu $t6, $t4, $t9
  /* 01D25C 8001C65C 304F0800 */      andi $t7, $v0, 0x800
  /* 01D260 8001C660 11E00002 */      beqz $t7, .L8001C66C
  /* 01D264 8001C664 95C60000 */       lhu $a2, ($t6)
  /* 01D268 8001C668 00063023 */      negu $a2, $a2
  .L8001C66C:
  /* 01D26C 8001C66C 44024000 */      mfc1 $v0, $f8
  /* 01D270 8001C670 46005402 */     mul.s $f16, $f10, $f0
  /* 01D274 8001C674 30420FFF */      andi $v0, $v0, 0xfff
  /* 01D278 8001C678 3047FFFF */      andi $a3, $v0, 0xffff
  /* 01D27C 8001C67C 30F907FF */      andi $t9, $a3, 0x7ff
  /* 01D280 8001C680 00197040 */       sll $t6, $t9, 1
  /* 01D284 8001C684 018E7821 */      addu $t7, $t4, $t6
  /* 01D288 8001C688 30F80800 */      andi $t8, $a3, 0x800
  /* 01D28C 8001C68C 13000002 */      beqz $t8, .L8001C698
  /* 01D290 8001C690 95E50000 */       lhu $a1, ($t7)
  /* 01D294 8001C694 00052823 */      negu $a1, $a1
  .L8001C698:
  /* 01D298 8001C698 24E30400 */     addiu $v1, $a3, 0x400
  /* 01D29C 8001C69C 307907FF */      andi $t9, $v1, 0x7ff
  /* 01D2A0 8001C6A0 00197040 */       sll $t6, $t9, 1
  /* 01D2A4 8001C6A4 018E7821 */      addu $t7, $t4, $t6
  /* 01D2A8 8001C6A8 30780800 */      andi $t8, $v1, 0x800
  /* 01D2AC 8001C6AC 13000002 */      beqz $t8, .L8001C6B8
  /* 01D2B0 8001C6B0 95E20000 */       lhu $v0, ($t7)
  /* 01D2B4 8001C6B4 00021023 */      negu $v0, $v0
  .L8001C6B8:
  /* 01D2B8 8001C6B8 46002182 */     mul.s $f6, $f4, $f0
  /* 01D2BC 8001C6BC C7AA0064 */      lwc1 $f10, 0x64($sp)
  /* 01D2C0 8001C6C0 00C20019 */     multu $a2, $v0
  /* 01D2C4 8001C6C4 3C03FFFF */       lui $v1, 0xffff
  /* 01D2C8 8001C6C8 3C014780 */       lui $at, (0x47800000 >> 16) # 65536.0
  /* 01D2CC 8001C6CC 4600848D */ trunc.w.s $f18, $f16
  /* 01D2D0 8001C6D0 46005402 */     mul.s $f16, $f10, $f0
  /* 01D2D4 8001C6D4 44810000 */      mtc1 $at, $f0 # 65536.0 to cop1
  /* 01D2D8 8001C6D8 440D9000 */      mfc1 $t5, $f18
  /* 01D2DC 8001C6DC 46007102 */     mul.s $f4, $f14, $f0
  /* 01D2E0 8001C6E0 0000C012 */      mflo $t8
  /* 01D2E4 8001C6E4 0018CB83 */       sra $t9, $t8, 0xe
  /* 01D2E8 8001C6E8 4600848D */ trunc.w.s $f18, $f16
  /* 01D2EC 8001C6EC 4600320D */ trunc.w.s $f8, $f6
  /* 01D2F0 8001C6F0 440B9000 */      mfc1 $t3, $f18
  /* 01D2F4 8001C6F4 4600218D */ trunc.w.s $f6, $f4
  /* 01D2F8 8001C6F8 032B0019 */     multu $t9, $t3
  /* 01D2FC 8001C6FC 44074000 */      mfc1 $a3, $f8
  /* 01D300 8001C700 46006202 */     mul.s $f8, $f12, $f0
  /* 01D304 8001C704 4600428D */ trunc.w.s $f10, $f8
  /* 01D308 8001C708 00007012 */      mflo $t6
  /* 01D30C 8001C70C 000E7A03 */       sra $t7, $t6, 8
  /* 01D310 8001C710 AFAF0008 */        sw $t7, 8($sp)
  /* 01D314 8001C714 00C50019 */     multu $a2, $a1
  /* 01D318 8001C718 0000C012 */      mflo $t8
  /* 01D31C 8001C71C 0018CB83 */       sra $t9, $t8, 0xe
  /* 01D320 8001C720 00000000 */       nop 
  /* 01D324 8001C724 032B0019 */     multu $t9, $t3
  /* 01D328 8001C728 01E3C824 */       and $t9, $t7, $v1
  /* 01D32C 8001C72C 00007012 */      mflo $t6
  /* 01D330 8001C730 000EC203 */       sra $t8, $t6, 8
  /* 01D334 8001C734 00187402 */       srl $t6, $t8, 0x10
  /* 01D338 8001C738 032E7825 */        or $t7, $t9, $t6
  /* 01D33C 8001C73C AFB80004 */        sw $t8, 4($sp)
  /* 01D340 8001C740 AC8F0000 */        sw $t7, ($a0)
  /* 01D344 8001C744 8FAE0004 */        lw $t6, 4($sp)
  /* 01D348 8001C748 8FB80008 */        lw $t8, 8($sp)
  /* 01D34C 8001C74C 31CFFFFF */      andi $t7, $t6, 0xffff
  /* 01D350 8001C750 00097023 */      negu $t6, $t1
  /* 01D354 8001C754 01CB0019 */     multu $t6, $t3
  /* 01D358 8001C758 0018CC00 */       sll $t9, $t8, 0x10
  /* 01D35C 8001C75C 032FC025 */        or $t8, $t9, $t7
  /* 01D360 8001C760 AC980020 */        sw $t8, 0x20($a0)
  /* 01D364 8001C764 0000C812 */      mflo $t9
  /* 01D368 8001C768 001979C3 */       sra $t7, $t9, 7
  /* 01D36C 8001C76C AFAF000C */        sw $t7, 0xc($sp)
  /* 01D370 8001C770 01490019 */     multu $t2, $t1
  /* 01D374 8001C774 01E3C024 */       and $t8, $t7, $v1
  /* 01D378 8001C778 AC980004 */        sw $t8, 4($a0)
  /* 01D37C 8001C77C 8FAE000C */        lw $t6, 0xc($sp)
  /* 01D380 8001C780 000ECC00 */       sll $t9, $t6, 0x10
  /* 01D384 8001C784 AC990024 */        sw $t9, 0x24($a0)
  /* 01D388 8001C788 00005812 */      mflo $t3
  /* 01D38C 8001C78C 000B5BC3 */       sra $t3, $t3, 0xf
  /* 01D390 8001C790 00000000 */       nop 
  /* 01D394 8001C794 01620019 */     multu $t3, $v0
  /* 01D398 8001C798 00007812 */      mflo $t7
  /* 01D39C 8001C79C 000FC383 */       sra $t8, $t7, 0xe
  /* 01D3A0 8001C7A0 00000000 */       nop 
  /* 01D3A4 8001C7A4 01050019 */     multu $t0, $a1
  /* 01D3A8 8001C7A8 00007012 */      mflo $t6
  /* 01D3AC 8001C7AC 000ECB83 */       sra $t9, $t6, 0xe
  /* 01D3B0 8001C7B0 03197823 */      subu $t7, $t8, $t9
  /* 01D3B4 8001C7B4 01ED0019 */     multu $t7, $t5
  /* 01D3B8 8001C7B8 00007012 */      mflo $t6
  /* 01D3BC 8001C7BC 000EC203 */       sra $t8, $t6, 8
  /* 01D3C0 8001C7C0 AFB80008 */        sw $t8, 8($sp)
  /* 01D3C4 8001C7C4 01650019 */     multu $t3, $a1
  /* 01D3C8 8001C7C8 0000C812 */      mflo $t9
  /* 01D3CC 8001C7CC 00197B83 */       sra $t7, $t9, 0xe
  /* 01D3D0 8001C7D0 00000000 */       nop 
  /* 01D3D4 8001C7D4 01020019 */     multu $t0, $v0
  /* 01D3D8 8001C7D8 00007012 */      mflo $t6
  /* 01D3DC 8001C7DC 000ECB83 */       sra $t9, $t6, 0xe
  /* 01D3E0 8001C7E0 01F97021 */      addu $t6, $t7, $t9
  /* 01D3E4 8001C7E4 01CD0019 */     multu $t6, $t5
  /* 01D3E8 8001C7E8 03037024 */       and $t6, $t8, $v1
  /* 01D3EC 8001C7EC 00007812 */      mflo $t7
  /* 01D3F0 8001C7F0 000FCA03 */       sra $t9, $t7, 8
  /* 01D3F4 8001C7F4 00197C02 */       srl $t7, $t9, 0x10
  /* 01D3F8 8001C7F8 01460019 */     multu $t2, $a2
  /* 01D3FC 8001C7FC 01CFC025 */        or $t8, $t6, $t7
  /* 01D400 8001C800 AFB9000C */        sw $t9, 0xc($sp)
  /* 01D404 8001C804 AC980008 */        sw $t8, 8($a0)
  /* 01D408 8001C808 8FAF000C */        lw $t7, 0xc($sp)
  /* 01D40C 8001C80C 8FB90008 */        lw $t9, 8($sp)
  /* 01D410 8001C810 31F8FFFF */      andi $t8, $t7, 0xffff
  /* 01D414 8001C814 00197400 */       sll $t6, $t9, 0x10
  /* 01D418 8001C818 01D8C825 */        or $t9, $t6, $t8
  /* 01D41C 8001C81C 00007812 */      mflo $t7
  /* 01D420 8001C820 000F7383 */       sra $t6, $t7, 0xe
  /* 01D424 8001C824 AC990028 */        sw $t9, 0x28($a0)
  /* 01D428 8001C828 01CD0019 */     multu $t6, $t5
  /* 01D42C 8001C82C 0000C012 */      mflo $t8
  /* 01D430 8001C830 0018CA03 */       sra $t9, $t8, 8
  /* 01D434 8001C834 AFB9000C */        sw $t9, 0xc($sp)
  /* 01D438 8001C838 01090019 */     multu $t0, $t1
  /* 01D43C 8001C83C 03237824 */       and $t7, $t9, $v1
  /* 01D440 8001C840 AC8F000C */        sw $t7, 0xc($a0)
  /* 01D444 8001C844 8FAE000C */        lw $t6, 0xc($sp)
  /* 01D448 8001C848 000EC400 */       sll $t8, $t6, 0x10
  /* 01D44C 8001C84C AC98002C */        sw $t8, 0x2c($a0)
  /* 01D450 8001C850 00005812 */      mflo $t3
  /* 01D454 8001C854 000B5BC3 */       sra $t3, $t3, 0xf
  /* 01D458 8001C858 00000000 */       nop 
  /* 01D45C 8001C85C 01620019 */     multu $t3, $v0
  /* 01D460 8001C860 0000C812 */      mflo $t9
  /* 01D464 8001C864 00197B83 */       sra $t7, $t9, 0xe
  /* 01D468 8001C868 00000000 */       nop 
  /* 01D46C 8001C86C 01450019 */     multu $t2, $a1
  /* 01D470 8001C870 00007012 */      mflo $t6
  /* 01D474 8001C874 000EC383 */       sra $t8, $t6, 0xe
  /* 01D478 8001C878 01F8C821 */      addu $t9, $t7, $t8
  /* 01D47C 8001C87C 03270019 */     multu $t9, $a3
  /* 01D480 8001C880 00006012 */      mflo $t4
  /* 01D484 8001C884 000C6203 */       sra $t4, $t4, 8
  /* 01D488 8001C888 00000000 */       nop 
  /* 01D48C 8001C88C 01650019 */     multu $t3, $a1
  /* 01D490 8001C890 00007012 */      mflo $t6
  /* 01D494 8001C894 000E7B83 */       sra $t7, $t6, 0xe
  /* 01D498 8001C898 00000000 */       nop 
  /* 01D49C 8001C89C 01420019 */     multu $t2, $v0
  /* 01D4A0 8001C8A0 0000C012 */      mflo $t8
  /* 01D4A4 8001C8A4 0018CB83 */       sra $t9, $t8, 0xe
  /* 01D4A8 8001C8A8 01F97023 */      subu $t6, $t7, $t9
  /* 01D4AC 8001C8AC 01C70019 */     multu $t6, $a3
  /* 01D4B0 8001C8B0 0183C024 */       and $t8, $t4, $v1
  /* 01D4B4 8001C8B4 000C7400 */       sll $t6, $t4, 0x10
  /* 01D4B8 8001C8B8 00006812 */      mflo $t5
  /* 01D4BC 8001C8BC 000D6A03 */       sra $t5, $t5, 8
  /* 01D4C0 8001C8C0 000D7C02 */       srl $t7, $t5, 0x10
  /* 01D4C4 8001C8C4 01060019 */     multu $t0, $a2
  /* 01D4C8 8001C8C8 030FC825 */        or $t9, $t8, $t7
  /* 01D4CC 8001C8CC AC990010 */        sw $t9, 0x10($a0)
  /* 01D4D0 8001C8D0 31B8FFFF */      andi $t8, $t5, 0xffff
  /* 01D4D4 8001C8D4 01D87825 */        or $t7, $t6, $t8
  /* 01D4D8 8001C8D8 AC8F0030 */        sw $t7, 0x30($a0)
  /* 01D4DC 8001C8DC 0000C812 */      mflo $t9
  /* 01D4E0 8001C8E0 00197383 */       sra $t6, $t9, 0xe
  /* 01D4E4 8001C8E4 00000000 */       nop 
  /* 01D4E8 8001C8E8 01C70019 */     multu $t6, $a3
  /* 01D4EC 8001C8EC 0000C012 */      mflo $t8
  /* 01D4F0 8001C8F0 00187A03 */       sra $t7, $t8, 8
  /* 01D4F4 8001C8F4 AFAF0010 */        sw $t7, 0x10($sp)
  /* 01D4F8 8001C8F8 01E3C824 */       and $t9, $t7, $v1
  /* 01D4FC 8001C8FC AC990014 */        sw $t9, 0x14($a0)
  /* 01D500 8001C900 8FAE0010 */        lw $t6, 0x10($sp)
  /* 01D504 8001C904 44193000 */      mfc1 $t9, $f6
  /* 01D508 8001C908 000EC400 */       sll $t8, $t6, 0x10
  /* 01D50C 8001C90C AC980034 */        sw $t8, 0x34($a0)
  /* 01D510 8001C910 44185000 */      mfc1 $t8, $f10
  /* 01D514 8001C914 AFB90010 */        sw $t9, 0x10($sp)
  /* 01D518 8001C918 03237824 */       and $t7, $t9, $v1
  /* 01D51C 8001C91C 00187402 */       srl $t6, $t8, 0x10
  /* 01D520 8001C920 01EEC825 */        or $t9, $t7, $t6
  /* 01D524 8001C924 AFB8000C */        sw $t8, 0xc($sp)
  /* 01D528 8001C928 AC990018 */        sw $t9, 0x18($a0)
  /* 01D52C 8001C92C 8FB80010 */        lw $t8, 0x10($sp)
  /* 01D530 8001C930 8FAE000C */        lw $t6, 0xc($sp)
  /* 01D534 8001C934 00187C00 */       sll $t7, $t8, 0x10
  /* 01D538 8001C938 31D9FFFF */      andi $t9, $t6, 0xffff
  /* 01D53C 8001C93C 01F9C025 */        or $t8, $t7, $t9
  /* 01D540 8001C940 AC980038 */        sw $t8, 0x38($a0)
  /* 01D544 8001C944 C7B00054 */      lwc1 $f16, 0x54($sp)
  /* 01D548 8001C948 46008482 */     mul.s $f18, $f16, $f0
  /* 01D54C 8001C94C 4600910D */ trunc.w.s $f4, $f18
  /* 01D550 8001C950 440F2000 */      mfc1 $t7, $f4
  /* 01D554 8001C954 00000000 */       nop 
  /* 01D558 8001C958 01E3C824 */       and $t9, $t7, $v1
  /* 01D55C 8001C95C 37380001 */       ori $t8, $t9, 1
  /* 01D560 8001C960 AFAF0010 */        sw $t7, 0x10($sp)
  /* 01D564 8001C964 AC98001C */        sw $t8, 0x1c($a0)
  /* 01D568 8001C968 8FAE0010 */        lw $t6, 0x10($sp)
  /* 01D56C 8001C96C 27BD0048 */     addiu $sp, $sp, 0x48
  /* 01D570 8001C970 000E7C00 */       sll $t7, $t6, 0x10
  /* 01D574 8001C974 03E00008 */        jr $ra
  /* 01D578 8001C978 AC8F003C */        sw $t7, 0x3c($a0)

