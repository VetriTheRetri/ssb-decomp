.late_rodata
glabel jtbl_8003D698
  /* 3D298 03E298 8003D698 */  .word L80001A3C
  /* 3D29C 03E29C 8003D69C */  .word L80001AC8
  /* 3D2A0 03E2A0 8003D6A0 */  .word L80001AE4
  /* 3D2A4 03E2A4 8003D6A4 */  .word L80001B1C
  /* 3D2A8 03E2A8 8003D6A8 */  .word L80001B68
  /* 3D2AC 03E2AC 8003D6AC */  .word L80001BB0
  /* 3D2B0 03E2B0 8003D6B0 */  .word L80001D28
  /* 3D2B4 03E2B4 8003D6B4 */  .word L80001D48
  /* 3D2B8 03E2B8 8003D6B8 */  .word L80001D80
  /* 3D2BC 03E2BC 8003D6BC */  .word L80001DB8
  /* 3D2C0 03E2C0 8003D6C0 */  .word L80001DE0
  #.incbin "system.raw.bin", 0x3D2C4, 0xC all zeros

.text
glabel func_80001A00
  /* 002600 80001A00 27BDFFB0 */     addiu $sp, $sp, -0x50
  /* 002604 80001A04 AFBF002C */        sw $ra, 0x2c($sp)
  /* 002608 80001A08 AFB00028 */        sw $s0, 0x28($sp)
  /* 00260C 80001A0C AFA0004C */        sw $zero, 0x4c($sp)
  /* 002610 80001A10 8C8E0000 */        lw $t6, ($a0)
  /* 002614 80001A14 00808025 */        or $s0, $a0, $zero
  /* 002618 80001A18 25CFFFFF */     addiu $t7, $t6, -1
  /* 00261C 80001A1C 2DE1000B */     sltiu $at, $t7, 0xb
  /* 002620 80001A20 1020010B */      beqz $at, .L80001E50
  /* 002624 80001A24 000F7880 */       sll $t7, $t7, 2
  /* 002628 80001A28 3C018004 */       lui $at, %hi(jtbl_8003D698)
  /* 00262C 80001A2C 002F0821 */      addu $at, $at, $t7
  /* 002630 80001A30 8C2FD698 */        lw $t7, %lo(jtbl_8003D698)($at)
  /* 002634 80001A34 01E00008 */        jr $t7
  /* 002638 80001A38 00000000 */       nop 
  glabel L80001A3C # 0 + 1
  /* 00263C 80001A3C 8E020068 */        lw $v0, 0x68($s0)
  /* 002640 80001A40 3C198004 */       lui $t9, %hi(D_80044F9C)
  /* 002644 80001A44 50400009 */      beql $v0, $zero, .L80001A6C
  /* 002648 80001A48 8E090050 */        lw $t1, 0x50($s0)
  /* 00264C 80001A4C 8C580000 */        lw $t8, ($v0)
  /* 002650 80001A50 8F394F9C */        lw $t9, %lo(D_80044F9C)($t9)
  /* 002654 80001A54 24050004 */     addiu $a1, $zero, 4
  /* 002658 80001A58 03194025 */        or $t0, $t8, $t9
  /* 00265C 80001A5C AC480000 */        sw $t0, ($v0)
  /* 002660 80001A60 0C00C874 */       jal osWritebackDCache
  /* 002664 80001A64 8E040068 */        lw $a0, 0x68($s0)
  /* 002668 80001A68 8E090050 */        lw $t1, 0x50($s0)
  .L80001A6C:
  /* 00266C 80001A6C 2401FFFF */     addiu $at, $zero, -1
  /* 002670 80001A70 3C0A8004 */       lui $t2, %hi(D_80044FCC)
  /* 002674 80001A74 15210008 */       bne $t1, $at, .L80001A98
  /* 002678 80001A78 3C0B8004 */       lui $t3, %hi(D_80044FC8)
  /* 00267C 80001A7C 8D4A4FCC */        lw $t2, %lo(D_80044FCC)($t2)
  /* 002680 80001A80 8D6B4FC8 */        lw $t3, %lo(D_80044FC8)($t3)
  /* 002684 80001A84 26040050 */     addiu $a0, $s0, 0x50
  /* 002688 80001A88 24050004 */     addiu $a1, $zero, 4
  /* 00268C 80001A8C 014B6021 */      addu $t4, $t2, $t3
  /* 002690 80001A90 0C00C874 */       jal osWritebackDCache
  /* 002694 80001A94 AE0C0050 */        sw $t4, 0x50($s0)
  .L80001A98:
  /* 002698 80001A98 8E0D0074 */        lw $t5, 0x74($s0)
  /* 00269C 80001A9C 24050001 */     addiu $a1, $zero, 1
  /* 0026A0 80001AA0 3C048004 */       lui $a0, %hi(D_80044FC0)
  /* 0026A4 80001AA4 14AD0003 */       bne $a1, $t5, .L80001AB4
  /* 0026A8 80001AA8 24844FC0 */     addiu $a0, $a0, %lo(D_80044FC0)
  /* 0026AC 80001AAC 0C00D14C */       jal osInvalDCache
  /* 0026B0 80001AB0 24050008 */     addiu $a1, $zero, 8
  .L80001AB4:
  /* 0026B4 80001AB4 0C000638 */       jal func_800018E0
  /* 0026B8 80001AB8 02002025 */        or $a0, $s0, $zero
  /* 0026BC 80001ABC 240E0001 */     addiu $t6, $zero, 1
  /* 0026C0 80001AC0 100000E3 */         b .L80001E50
  /* 0026C4 80001AC4 AFAE004C */        sw $t6, 0x4c($sp)
  glabel L80001AC8 # 1 + 1 [2]
  /* 0026C8 80001AC8 0C00E458 */       jal osWritebackDCacheAll
  /* 0026CC 80001ACC 00000000 */       nop 
  /* 0026D0 80001AD0 0C00065A */       jal func_80001968
  /* 0026D4 80001AD4 02002025 */        or $a0, $s0, $zero
  /* 0026D8 80001AD8 240F0001 */     addiu $t7, $zero, 1
  /* 0026DC 80001ADC 100000DC */         b .L80001E50
  /* 0026E0 80001AE0 AFAF004C */        sw $t7, 0x4c($sp)
  glabel L80001AE4 # 2 + 1 [3]
  /* 0026E4 80001AE4 3C038004 */       lui $v1, %hi(D_80044EC0)
  /* 0026E8 80001AE8 24634EC0 */     addiu $v1, $v1, %lo(D_80044EC0)
  /* 0026EC 80001AEC 8E020024 */        lw $v0, 0x24($s0)
  /* 0026F0 80001AF0 8C780000 */        lw $t8, ($v1) # D_80044EC0 + 0
  /* 0026F4 80001AF4 00003025 */        or $a2, $zero, $zero
  /* 0026F8 80001AF8 AC580000 */        sw $t8, ($v0)
  /* 0026FC 80001AFC AC620000 */        sw $v0, ($v1) # D_80044EC0 + 0
  /* 002700 80001B00 8E040020 */        lw $a0, 0x20($s0)
  /* 002704 80001B04 508000D3 */      beql $a0, $zero, .L80001E54
  /* 002708 80001B08 8FBF002C */        lw $ra, 0x2c($sp)
  /* 00270C 80001B0C 0C00C000 */       jal osSendMesg
  /* 002710 80001B10 8E05001C */        lw $a1, 0x1c($s0)
  /* 002714 80001B14 100000CF */         b .L80001E54
  /* 002718 80001B18 8FBF002C */        lw $ra, 0x2c($sp)
  glabel L80001B1C # 3 + 1 [4]
  /* 00271C 80001B1C 86190032 */        lh $t9, 0x32($s0)
  /* 002720 80001B20 8E040024 */        lw $a0, 0x24($s0)
  /* 002724 80001B24 8E050028 */        lw $a1, 0x28($s0)
  /* 002728 80001B28 8E06002C */        lw $a2, 0x2c($s0)
  /* 00272C 80001B2C 86070030 */        lh $a3, 0x30($s0)
  /* 002730 80001B30 AFB90010 */        sw $t9, 0x10($sp)
  /* 002734 80001B34 86080034 */        lh $t0, 0x34($s0)
  /* 002738 80001B38 AFA80014 */        sw $t0, 0x14($sp)
  /* 00273C 80001B3C 86090036 */        lh $t1, 0x36($s0)
  /* 002740 80001B40 0C0003CC */       jal func_80000F30
  /* 002744 80001B44 AFA90018 */        sw $t1, 0x18($sp)
  /* 002748 80001B48 8E040020 */        lw $a0, 0x20($s0)
  /* 00274C 80001B4C 00003025 */        or $a2, $zero, $zero
  /* 002750 80001B50 508000C0 */      beql $a0, $zero, .L80001E54
  /* 002754 80001B54 8FBF002C */        lw $ra, 0x2c($sp)
  /* 002758 80001B58 0C00C000 */       jal osSendMesg
  /* 00275C 80001B5C 8E05001C */        lw $a1, 0x1c($s0)
  /* 002760 80001B60 100000BC */         b .L80001E54
  /* 002764 80001B64 8FBF002C */        lw $ra, 0x2c($sp)
  glabel L80001B68 # 4 + 1 [5]
  /* 002768 80001B68 3C028004 */       lui $v0, %hi(D_80044F90)
  /* 00276C 80001B6C 3C048004 */       lui $a0, %hi(D_80044F9C)
  /* 002770 80001B70 24844F9C */     addiu $a0, $a0, %lo(D_80044F9C)
  /* 002774 80001B74 24424F90 */     addiu $v0, $v0, %lo(D_80044F90)
  /* 002778 80001B78 02001825 */        or $v1, $s0, $zero
  .L80001B7C:
  /* 00277C 80001B7C 8C6A0024 */        lw $t2, 0x24($v1)
  /* 002780 80001B80 24420004 */     addiu $v0, $v0, 4
  /* 002784 80001B84 24630004 */     addiu $v1, $v1, 4
  /* 002788 80001B88 1444FFFC */       bne $v0, $a0, .L80001B7C
  /* 00278C 80001B8C AC4AFFFC */        sw $t2, -4($v0) # D_80044F90 + -4
  /* 002790 80001B90 8E040020 */        lw $a0, 0x20($s0)
  /* 002794 80001B94 00003025 */        or $a2, $zero, $zero
  /* 002798 80001B98 508000AE */      beql $a0, $zero, .L80001E54
  /* 00279C 80001B9C 8FBF002C */        lw $ra, 0x2c($sp)
  /* 0027A0 80001BA0 0C00C000 */       jal osSendMesg
  /* 0027A4 80001BA4 8E05001C */        lw $a1, 0x1c($s0)
  /* 0027A8 80001BA8 100000AA */         b .L80001E54
  /* 0027AC 80001BAC 8FBF002C */        lw $ra, 0x2c($sp)
  glabel L80001BB0 # 5 + 1 [6]
  /* 0027B0 80001BB0 3C048004 */       lui $a0, %hi(D_80044ECC)
  /* 0027B4 80001BB4 8C844ECC */        lw $a0, %lo(D_80044ECC)($a0)
  /* 0027B8 80001BB8 00001825 */        or $v1, $zero, $zero
  /* 0027BC 80001BBC 3C028004 */       lui $v0, %hi(D_80044ED4)
  /* 0027C0 80001BC0 1080000A */      beqz $a0, .L80001BEC
  /* 0027C4 80001BC4 00000000 */       nop 
  /* 0027C8 80001BC8 8C8B0000 */        lw $t3, ($a0)
  /* 0027CC 80001BCC 24050001 */     addiu $a1, $zero, 1
  /* 0027D0 80001BD0 14AB0006 */       bne $a1, $t3, .L80001BEC
  /* 0027D4 80001BD4 00000000 */       nop 
  /* 0027D8 80001BD8 8E0C0028 */        lw $t4, 0x28($s0)
  /* 0027DC 80001BDC 8C8D0080 */        lw $t5, 0x80($a0)
  /* 0027E0 80001BE0 158D0002 */       bne $t4, $t5, .L80001BEC
  /* 0027E4 80001BE4 00000000 */       nop 
  /* 0027E8 80001BE8 00801825 */        or $v1, $a0, $zero
  .L80001BEC:
  /* 0027EC 80001BEC 8C424ED4 */        lw $v0, %lo(D_80044ED4)($v0)
  /* 0027F0 80001BF0 24050001 */     addiu $a1, $zero, 1
  /* 0027F4 80001BF4 1040000C */      beqz $v0, .L80001C28
  /* 0027F8 80001BF8 00000000 */       nop 
  /* 0027FC 80001BFC 8C4E0000 */        lw $t6, ($v0)
  .L80001C00:
  /* 002800 80001C00 54AE0007 */      bnel $a1, $t6, .L80001C20
  /* 002804 80001C04 8C42000C */        lw $v0, 0xc($v0)
  /* 002808 80001C08 8E0F0028 */        lw $t7, 0x28($s0)
  /* 00280C 80001C0C 8C580080 */        lw $t8, 0x80($v0)
  /* 002810 80001C10 55F80003 */      bnel $t7, $t8, .L80001C20
  /* 002814 80001C14 8C42000C */        lw $v0, 0xc($v0)
  /* 002818 80001C18 00401825 */        or $v1, $v0, $zero
  /* 00281C 80001C1C 8C42000C */        lw $v0, 0xc($v0)
  .L80001C20:
  /* 002820 80001C20 5440FFF7 */      bnel $v0, $zero, .L80001C00
  /* 002824 80001C24 8C4E0000 */        lw $t6, ($v0)
  .L80001C28:
  /* 002828 80001C28 3C028004 */       lui $v0, %hi(D_80044EC4)
  /* 00282C 80001C2C 8C424EC4 */        lw $v0, %lo(D_80044EC4)($v0)
  /* 002830 80001C30 1040000C */      beqz $v0, .L80001C64
  /* 002834 80001C34 00000000 */       nop 
  /* 002838 80001C38 8C590000 */        lw $t9, ($v0)
  .L80001C3C:
  /* 00283C 80001C3C 54B90007 */      bnel $a1, $t9, .L80001C5C
  /* 002840 80001C40 8C42000C */        lw $v0, 0xc($v0)
  /* 002844 80001C44 8E080028 */        lw $t0, 0x28($s0)
  /* 002848 80001C48 8C490080 */        lw $t1, 0x80($v0)
  /* 00284C 80001C4C 55090003 */      bnel $t0, $t1, .L80001C5C
  /* 002850 80001C50 8C42000C */        lw $v0, 0xc($v0)
  /* 002854 80001C54 00401825 */        or $v1, $v0, $zero
  /* 002858 80001C58 8C42000C */        lw $v0, 0xc($v0)
  .L80001C5C:
  /* 00285C 80001C5C 5440FFF7 */      bnel $v0, $zero, .L80001C3C
  /* 002860 80001C60 8C590000 */        lw $t9, ($v0)
  .L80001C64:
  /* 002864 80001C64 3C028004 */       lui $v0, %hi(D_80044EE4)
  /* 002868 80001C68 8C424EE4 */        lw $v0, %lo(D_80044EE4)($v0)
  /* 00286C 80001C6C 10400009 */      beqz $v0, .L80001C94
  /* 002870 80001C70 00000000 */       nop 
  /* 002874 80001C74 8C4A0000 */        lw $t2, ($v0)
  /* 002878 80001C78 14AA0006 */       bne $a1, $t2, .L80001C94
  /* 00287C 80001C7C 00000000 */       nop 
  /* 002880 80001C80 8E0B0028 */        lw $t3, 0x28($s0)
  /* 002884 80001C84 8C8C0080 */        lw $t4, 0x80($a0)
  /* 002888 80001C88 156C0002 */       bne $t3, $t4, .L80001C94
  /* 00288C 80001C8C 00000000 */       nop 
  /* 002890 80001C90 00401825 */        or $v1, $v0, $zero
  .L80001C94:
  /* 002894 80001C94 3C028004 */       lui $v0, %hi(D_80044EDC)
  /* 002898 80001C98 8C424EDC */        lw $v0, %lo(D_80044EDC)($v0)
  /* 00289C 80001C9C 1040000C */      beqz $v0, .L80001CD0
  /* 0028A0 80001CA0 00000000 */       nop 
  /* 0028A4 80001CA4 8C4D0000 */        lw $t5, ($v0)
  .L80001CA8:
  /* 0028A8 80001CA8 54AD0007 */      bnel $a1, $t5, .L80001CC8
  /* 0028AC 80001CAC 8C42000C */        lw $v0, 0xc($v0)
  /* 0028B0 80001CB0 8E0E0028 */        lw $t6, 0x28($s0)
  /* 0028B4 80001CB4 8C4F0080 */        lw $t7, 0x80($v0)
  /* 0028B8 80001CB8 55CF0003 */      bnel $t6, $t7, .L80001CC8
  /* 0028BC 80001CBC 8C42000C */        lw $v0, 0xc($v0)
  /* 0028C0 80001CC0 00401825 */        or $v1, $v0, $zero
  /* 0028C4 80001CC4 8C42000C */        lw $v0, 0xc($v0)
  .L80001CC8:
  /* 0028C8 80001CC8 5440FFF7 */      bnel $v0, $zero, .L80001CA8
  /* 0028CC 80001CCC 8C4D0000 */        lw $t5, ($v0)
  .L80001CD0:
  /* 0028D0 80001CD0 50600009 */      beql $v1, $zero, .L80001CF8
  /* 0028D4 80001CD4 8E040024 */        lw $a0, 0x24($s0)
  /* 0028D8 80001CD8 8E18001C */        lw $t8, 0x1c($s0)
  /* 0028DC 80001CDC AC78001C */        sw $t8, 0x1c($v1)
  /* 0028E0 80001CE0 8E190020 */        lw $t9, 0x20($s0)
  /* 0028E4 80001CE4 AC790020 */        sw $t9, 0x20($v1)
  /* 0028E8 80001CE8 8E080024 */        lw $t0, 0x24($s0)
  /* 0028EC 80001CEC 10000058 */         b .L80001E50
  /* 0028F0 80001CF0 AC68006C */        sw $t0, 0x6c($v1)
  /* 0028F4 80001CF4 8E040024 */        lw $a0, 0x24($s0)
  .L80001CF8:
  /* 0028F8 80001CF8 50800004 */      beql $a0, $zero, .L80001D0C
  /* 0028FC 80001CFC 8E040020 */        lw $a0, 0x20($s0)
  /* 002900 80001D00 0C0005EE */       jal func_800017B8
  /* 002904 80001D04 00000000 */       nop 
  /* 002908 80001D08 8E040020 */        lw $a0, 0x20($s0)
  .L80001D0C:
  /* 00290C 80001D0C 00003025 */        or $a2, $zero, $zero
  /* 002910 80001D10 50800050 */      beql $a0, $zero, .L80001E54
  /* 002914 80001D14 8FBF002C */        lw $ra, 0x2c($sp)
  /* 002918 80001D18 0C00C000 */       jal osSendMesg
  /* 00291C 80001D1C 8E05001C */        lw $a1, 0x1c($s0)
  /* 002920 80001D20 1000004C */         b .L80001E54
  /* 002924 80001D24 8FBF002C */        lw $ra, 0x2c($sp)
  glabel L80001D28 # 6 + 1 [7]
  /* 002928 80001D28 8E040020 */        lw $a0, 0x20($s0)
  /* 00292C 80001D2C 00003025 */        or $a2, $zero, $zero
  /* 002930 80001D30 50800048 */      beql $a0, $zero, .L80001E54
  /* 002934 80001D34 8FBF002C */        lw $ra, 0x2c($sp)
  /* 002938 80001D38 0C00C000 */       jal osSendMesg
  /* 00293C 80001D3C 8E05001C */        lw $a1, 0x1c($s0)
  /* 002940 80001D40 10000044 */         b .L80001E54
  /* 002944 80001D44 8FBF002C */        lw $ra, 0x2c($sp)
  glabel L80001D48 # 7 + 1 [8]
  /* 002948 80001D48 8E090024 */        lw $t1, 0x24($s0)
  /* 00294C 80001D4C 3C018004 */       lui $at, %hi(D_80044FCC)
  /* 002950 80001D50 00003025 */        or $a2, $zero, $zero
  /* 002954 80001D54 AC294FCC */        sw $t1, %lo(D_80044FCC)($at)
  /* 002958 80001D58 8E0A0028 */        lw $t2, 0x28($s0)
  /* 00295C 80001D5C 3C018004 */       lui $at, %hi(D_80044FD0)
  /* 002960 80001D60 AC2A4FD0 */        sw $t2, %lo(D_80044FD0)($at)
  /* 002964 80001D64 8E040020 */        lw $a0, 0x20($s0)
  /* 002968 80001D68 5080003A */      beql $a0, $zero, .L80001E54
  /* 00296C 80001D6C 8FBF002C */        lw $ra, 0x2c($sp)
  /* 002970 80001D70 0C00C000 */       jal osSendMesg
  /* 002974 80001D74 8E05001C */        lw $a1, 0x1c($s0)
  /* 002978 80001D78 10000036 */         b .L80001E54
  /* 00297C 80001D7C 8FBF002C */        lw $ra, 0x2c($sp)
  glabel L80001D80 # 8 + 1 [9]
  /* 002980 80001D80 24050001 */     addiu $a1, $zero, 1
  /* 002984 80001D84 3C018004 */       lui $at, %hi(D_80045010)
  /* 002988 80001D88 AC255010 */        sw $a1, %lo(D_80045010)($at)
  /* 00298C 80001D8C 8E0B0024 */        lw $t3, 0x24($s0)
  /* 002990 80001D90 3C018004 */       lui $at, %hi(D_80045014)
  /* 002994 80001D94 00003025 */        or $a2, $zero, $zero
  /* 002998 80001D98 AC2B5014 */        sw $t3, %lo(D_80045014)($at)
  /* 00299C 80001D9C 8E040020 */        lw $a0, 0x20($s0)
  /* 0029A0 80001DA0 5080002C */      beql $a0, $zero, .L80001E54
  /* 0029A4 80001DA4 8FBF002C */        lw $ra, 0x2c($sp)
  /* 0029A8 80001DA8 0C00C000 */       jal osSendMesg
  /* 0029AC 80001DAC 8E05001C */        lw $a1, 0x1c($s0)
  /* 0029B0 80001DB0 10000028 */         b .L80001E54
  /* 0029B4 80001DB4 8FBF002C */        lw $ra, 0x2c($sp)
  glabel L80001DB8 # 9 + 1 [10]
  /* 0029B8 80001DB8 3C018004 */       lui $at, %hi(D_80045010)
  /* 0029BC 80001DBC AC205010 */        sw $zero, %lo(D_80045010)($at)
  /* 0029C0 80001DC0 8E040020 */        lw $a0, 0x20($s0)
  /* 0029C4 80001DC4 00003025 */        or $a2, $zero, $zero
  /* 0029C8 80001DC8 50800022 */      beql $a0, $zero, .L80001E54
  /* 0029CC 80001DCC 8FBF002C */        lw $ra, 0x2c($sp)
  /* 0029D0 80001DD0 0C00C000 */       jal osSendMesg
  /* 0029D4 80001DD4 8E05001C */        lw $a1, 0x1c($s0)
  /* 0029D8 80001DD8 1000001E */         b .L80001E54
  /* 0029DC 80001DDC 8FBF002C */        lw $ra, 0x2c($sp)
  glabel L80001DE0 # 10 + 1 [11]
  /* 0029E0 80001DE0 3C048004 */       lui $a0, %hi(D_80044EC4)
  /* 0029E4 80001DE4 8C844EC4 */        lw $a0, %lo(D_80044EC4)($a0)
  /* 0029E8 80001DE8 24050001 */     addiu $a1, $zero, 1
  /* 0029EC 80001DEC 10800010 */      beqz $a0, .L80001E30
  /* 0029F0 80001DF0 00000000 */       nop 
  /* 0029F4 80001DF4 8C820000 */        lw $v0, ($a0)
  .L80001DF8:
  /* 0029F8 80001DF8 24010004 */     addiu $at, $zero, 4
  /* 0029FC 80001DFC 50A20004 */      beql $a1, $v0, .L80001E10
  /* 002A00 80001E00 8C8C000C */        lw $t4, 0xc($a0)
  /* 002A04 80001E04 54410008 */      bnel $v0, $at, .L80001E28
  /* 002A08 80001E08 8C84000C */        lw $a0, 0xc($a0)
  /* 002A0C 80001E0C 8C8C000C */        lw $t4, 0xc($a0)
  .L80001E10:
  /* 002A10 80001E10 0C00033D */       jal func_80000CF4
  /* 002A14 80001E14 AFAC0034 */        sw $t4, 0x34($sp)
  /* 002A18 80001E18 24050001 */     addiu $a1, $zero, 1
  /* 002A1C 80001E1C 10000002 */         b .L80001E28
  /* 002A20 80001E20 8FA40034 */        lw $a0, 0x34($sp)
  /* 002A24 80001E24 8C84000C */        lw $a0, 0xc($a0)
  .L80001E28:
  /* 002A28 80001E28 5480FFF3 */      bnel $a0, $zero, .L80001DF8
  /* 002A2C 80001E2C 8C820000 */        lw $v0, ($a0)
  .L80001E30:
  /* 002A30 80001E30 3C018004 */       lui $at, %hi(D_80044F9C + 4)
  /* 002A34 80001E34 AC204FA0 */        sw $zero, %lo(D_80044F9C + 4)($at)
  /* 002A38 80001E38 8E040020 */        lw $a0, 0x20($s0)
  /* 002A3C 80001E3C 00003025 */        or $a2, $zero, $zero
  /* 002A40 80001E40 50800004 */      beql $a0, $zero, .L80001E54
  /* 002A44 80001E44 8FBF002C */        lw $ra, 0x2c($sp)
  /* 002A48 80001E48 0C00C000 */       jal osSendMesg
  /* 002A4C 80001E4C 8E05001C */        lw $a1, 0x1c($s0)
  .L80001E50:
  /* 002A50 80001E50 8FBF002C */        lw $ra, 0x2c($sp)
  .L80001E54:
  /* 002A54 80001E54 8FA2004C */        lw $v0, 0x4c($sp)
  /* 002A58 80001E58 8FB00028 */        lw $s0, 0x28($sp)
  /* 002A5C 80001E5C 03E00008 */        jr $ra
  /* 002A60 80001E60 27BD0050 */     addiu $sp, $sp, 0x50

