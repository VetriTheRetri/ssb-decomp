.section .text
glabel func_8000F720
  /* 010320 8000F720 27BDFF50 */     addiu $sp, $sp, -0xb0
  /* 010324 8000F724 AFB50034 */        sw $s5, 0x34($sp)
  /* 010328 8000F728 AFB40030 */        sw $s4, 0x30($sp)
  /* 01032C 8000F72C AFB3002C */        sw $s3, 0x2c($sp)
  /* 010330 8000F730 00A09825 */        or $s3, $a1, $zero
  /* 010334 8000F734 00C0A025 */        or $s4, $a2, $zero
  /* 010338 8000F738 00E0A825 */        or $s5, $a3, $zero
  /* 01033C 8000F73C AFBF0044 */        sw $ra, 0x44($sp)
  /* 010340 8000F740 AFBE0040 */        sw $fp, 0x40($sp)
  /* 010344 8000F744 AFB7003C */        sw $s7, 0x3c($sp)
  /* 010348 8000F748 AFB60038 */        sw $s6, 0x38($sp)
  /* 01034C 8000F74C AFB20028 */        sw $s2, 0x28($sp)
  /* 010350 8000F750 AFB10024 */        sw $s1, 0x24($sp)
  /* 010354 8000F754 AFB00020 */        sw $s0, 0x20($sp)
  /* 010358 8000F758 AFA400B0 */        sw $a0, 0xb0($sp)
  /* 01035C 8000F75C AFA0005C */        sw $zero, 0x5c($sp)
  /* 010360 8000F760 AFA00060 */        sw $zero, 0x60($sp)
  /* 010364 8000F764 27A20064 */     addiu $v0, $sp, 0x64
  /* 010368 8000F768 27A300A4 */     addiu $v1, $sp, 0xa4
  .L8000F76C:
  /* 01036C 8000F76C 24420010 */     addiu $v0, $v0, 0x10
  /* 010370 8000F770 AC40FFF4 */        sw $zero, -0xc($v0)
  /* 010374 8000F774 AC40FFF8 */        sw $zero, -8($v0)
  /* 010378 8000F778 AC40FFFC */        sw $zero, -4($v0)
  /* 01037C 8000F77C 1443FFFB */       bne $v0, $v1, .L8000F76C
  /* 010380 8000F780 AC40FFF0 */        sw $zero, -0x10($v0)
  /* 010384 8000F784 8E620000 */        lw $v0, ($s3)
  /* 010388 8000F788 24010012 */     addiu $at, $zero, 0x12
  /* 01038C 8000F78C 93BE00CB */       lbu $fp, 0xcb($sp)
  /* 010390 8000F790 1041004C */       beq $v0, $at, .L8000F8C4
  /* 010394 8000F794 93B700C7 */       lbu $s7, 0xc7($sp)
  /* 010398 8000F798 93B600C3 */       lbu $s6, 0xc3($sp)
  /* 01039C 8000F79C 30430FFF */      andi $v1, $v0, 0xfff
  .L8000F7A0:
  /* 0103A0 8000F7A0 10600009 */      beqz $v1, .L8000F7C8
  /* 0103A4 8000F7A4 00037080 */       sll $t6, $v1, 2
  /* 0103A8 8000F7A8 27AF005C */     addiu $t7, $sp, 0x5c
  /* 0103AC 8000F7AC 01CF8021 */      addu $s0, $t6, $t7
  /* 0103B0 8000F7B0 8E04FFFC */        lw $a0, -4($s0)
  /* 0103B4 8000F7B4 0C0024FD */       jal func_800093F4
  /* 0103B8 8000F7B8 8E650004 */        lw $a1, 4($s3)
  /* 0103BC 8000F7BC AE020000 */        sw $v0, ($s0)
  /* 0103C0 8000F7C0 10000006 */         b .L8000F7DC
  /* 0103C4 8000F7C4 00409025 */        or $s2, $v0, $zero
  .L8000F7C8:
  /* 0103C8 8000F7C8 8FA400B0 */        lw $a0, 0xb0($sp)
  /* 0103CC 8000F7CC 0C0024B4 */       jal func_800092D0
  /* 0103D0 8000F7D0 8E650004 */        lw $a1, 4($s3)
  /* 0103D4 8000F7D4 AFA2005C */        sw $v0, 0x5c($sp)
  /* 0103D8 8000F7D8 00409025 */        or $s2, $v0, $zero
  .L8000F7DC:
  /* 0103DC 8000F7DC 8E620000 */        lw $v0, ($s3)
  /* 0103E0 8000F7E0 02402025 */        or $a0, $s2, $zero
  /* 0103E4 8000F7E4 32C500FF */      andi $a1, $s6, 0xff
  /* 0103E8 8000F7E8 3042F000 */      andi $v0, $v0, 0xf000
  /* 0103EC 8000F7EC 10400009 */      beqz $v0, .L8000F814
  /* 0103F0 8000F7F0 32E600FF */      andi $a2, $s7, 0xff
  /* 0103F4 8000F7F4 02402025 */        or $a0, $s2, $zero
  /* 0103F8 8000F7F8 32C500FF */      andi $a1, $s6, 0xff
  /* 0103FC 8000F7FC 32E600FF */      andi $a2, $s7, 0xff
  /* 010400 8000F800 33C700FF */      andi $a3, $fp, 0xff
  /* 010404 8000F804 0C003CD9 */       jal func_8000F364
  /* 010408 8000F808 AFA20010 */        sw $v0, 0x10($sp)
  /* 01040C 8000F80C 10000004 */         b .L8000F820
  /* 010410 8000F810 8E790008 */        lw $t9, 8($s3)
  .L8000F814:
  /* 010414 8000F814 0C003CBF */       jal func_8000F2FC
  /* 010418 8000F818 33C700FF */      andi $a3, $fp, 0xff
  /* 01041C 8000F81C 8E790008 */        lw $t9, 8($s3)
  .L8000F820:
  /* 010420 8000F820 AE59001C */        sw $t9, 0x1c($s2)
  /* 010424 8000F824 8E78000C */        lw $t8, 0xc($s3)
  /* 010428 8000F828 AE580020 */        sw $t8, 0x20($s2)
  /* 01042C 8000F82C 8E790010 */        lw $t9, 0x10($s3)
  /* 010430 8000F830 AE590024 */        sw $t9, 0x24($s2)
  /* 010434 8000F834 8E690014 */        lw $t1, 0x14($s3)
  /* 010438 8000F838 AE490030 */        sw $t1, 0x30($s2)
  /* 01043C 8000F83C 8E680018 */        lw $t0, 0x18($s3)
  /* 010440 8000F840 AE480034 */        sw $t0, 0x34($s2)
  /* 010444 8000F844 8E69001C */        lw $t1, 0x1c($s3)
  /* 010448 8000F848 AE490038 */        sw $t1, 0x38($s2)
  /* 01044C 8000F84C 8E6B0020 */        lw $t3, 0x20($s3)
  /* 010450 8000F850 AE4B0040 */        sw $t3, 0x40($s2)
  /* 010454 8000F854 8E6A0024 */        lw $t2, 0x24($s3)
  /* 010458 8000F858 AE4A0044 */        sw $t2, 0x44($s2)
  /* 01045C 8000F85C 8E6B0028 */        lw $t3, 0x28($s3)
  /* 010460 8000F860 1280000F */      beqz $s4, .L8000F8A0
  /* 010464 8000F864 AE4B0048 */        sw $t3, 0x48($s2)
  /* 010468 8000F868 8E820000 */        lw $v0, ($s4)
  /* 01046C 8000F86C 5040000C */      beql $v0, $zero, .L8000F8A0
  /* 010470 8000F870 26940004 */     addiu $s4, $s4, 4
  /* 010474 8000F874 8C510000 */        lw $s1, ($v0)
  /* 010478 8000F878 00408025 */        or $s0, $v0, $zero
  /* 01047C 8000F87C 12200007 */      beqz $s1, .L8000F89C
  /* 010480 8000F880 02402025 */        or $a0, $s2, $zero
  .L8000F884:
  /* 010484 8000F884 0C002437 */       jal func_800090DC
  /* 010488 8000F888 02202825 */        or $a1, $s1, $zero
  /* 01048C 8000F88C 8E110004 */        lw $s1, 4($s0)
  /* 010490 8000F890 26100004 */     addiu $s0, $s0, 4
  /* 010494 8000F894 5620FFFB */      bnel $s1, $zero, .L8000F884
  /* 010498 8000F898 02402025 */        or $a0, $s2, $zero
  .L8000F89C:
  /* 01049C 8000F89C 26940004 */     addiu $s4, $s4, 4
  .L8000F8A0:
  /* 0104A0 8000F8A0 52A00004 */      beql $s5, $zero, .L8000F8B4
  /* 0104A4 8000F8A4 8E62002C */        lw $v0, 0x2c($s3)
  /* 0104A8 8000F8A8 AEB20000 */        sw $s2, ($s5)
  /* 0104AC 8000F8AC 26B50004 */     addiu $s5, $s5, 4
  /* 0104B0 8000F8B0 8E62002C */        lw $v0, 0x2c($s3)
  .L8000F8B4:
  /* 0104B4 8000F8B4 24010012 */     addiu $at, $zero, 0x12
  /* 0104B8 8000F8B8 2673002C */     addiu $s3, $s3, 0x2c
  /* 0104BC 8000F8BC 5441FFB8 */      bnel $v0, $at, .L8000F7A0
  /* 0104C0 8000F8C0 30430FFF */      andi $v1, $v0, 0xfff
  .L8000F8C4:
  /* 0104C4 8000F8C4 8FBF0044 */        lw $ra, 0x44($sp)
  /* 0104C8 8000F8C8 8FB00020 */        lw $s0, 0x20($sp)
  /* 0104CC 8000F8CC 8FB10024 */        lw $s1, 0x24($sp)
  /* 0104D0 8000F8D0 8FB20028 */        lw $s2, 0x28($sp)
  /* 0104D4 8000F8D4 8FB3002C */        lw $s3, 0x2c($sp)
  /* 0104D8 8000F8D8 8FB40030 */        lw $s4, 0x30($sp)
  /* 0104DC 8000F8DC 8FB50034 */        lw $s5, 0x34($sp)
  /* 0104E0 8000F8E0 8FB60038 */        lw $s6, 0x38($sp)
  /* 0104E4 8000F8E4 8FB7003C */        lw $s7, 0x3c($sp)
  /* 0104E8 8000F8E8 8FBE0040 */        lw $fp, 0x40($sp)
  /* 0104EC 8000F8EC 03E00008 */        jr $ra
  /* 0104F0 8000F8F0 27BD00B0 */     addiu $sp, $sp, 0xb0
