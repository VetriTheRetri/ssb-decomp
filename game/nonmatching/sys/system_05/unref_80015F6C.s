.section .text
glabel unref_80015F6C
  /* 016B6C 80015F6C 27BDFFB0 */     addiu $sp, $sp, -0x50
  /* 016B70 80015F70 AFBF002C */        sw $ra, 0x2c($sp)
  /* 016B74 80015F74 AFB40028 */        sw $s4, 0x28($sp)
  /* 016B78 80015F78 AFB30024 */        sw $s3, 0x24($sp)
  /* 016B7C 80015F7C AFB20020 */        sw $s2, 0x20($sp)
  /* 016B80 80015F80 AFB1001C */        sw $s1, 0x1c($sp)
  /* 016B84 80015F84 AFB00018 */        sw $s0, 0x18($sp)
  /* 016B88 80015F88 8C930074 */        lw $s3, 0x74($a0)
  /* 016B8C 80015F8C 0000A025 */        or $s4, $zero, $zero
  /* 016B90 80015F90 926E0054 */       lbu $t6, 0x54($s3)
  /* 016B94 80015F94 31CF0002 */      andi $t7, $t6, 2
  /* 016B98 80015F98 55E000C4 */      bnel $t7, $zero, .L800162AC
  /* 016B9C 80015F9C 8FBF002C */        lw $ra, 0x2c($sp)
  /* 016BA0 80015FA0 8E700050 */        lw $s0, 0x50($s3)
  /* 016BA4 80015FA4 3C118004 */       lui $s1, %hi(D_800472A8)
  /* 016BA8 80015FA8 263172A8 */     addiu $s1, $s1, %lo(D_800472A8)
  /* 016BAC 80015FAC 120000BE */      beqz $s0, .L800162A8
  /* 016BB0 80015FB0 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 016BB4 80015FB4 44812000 */      mtc1 $at, $f4 # 1.0 to cop1
  /* 016BB8 80015FB8 3C018004 */       lui $at, %hi(D_80046FA4)
  /* 016BBC 80015FBC 02602025 */        or $a0, $s3, $zero
  /* 016BC0 80015FC0 E4246FA4 */      swc1 $f4, %lo(D_80046FA4)($at)
  /* 016BC4 80015FC4 0C0051E6 */       jal func_80014798
  /* 016BC8 80015FC8 AE200000 */        sw $zero, ($s1) # D_800472A8 + 0
  /* 016BCC 80015FCC C6060000 */      lwc1 $f6, ($s0)
  /* 016BD0 80015FD0 3C128004 */       lui $s2, %hi(D_800470B0)
  /* 016BD4 80015FD4 265270B0 */     addiu $s2, $s2, %lo(D_800470B0)
  /* 016BD8 80015FD8 4606003C */    c.lt.s $f0, $f6
  /* 016BDC 80015FDC 46000086 */     mov.s $f2, $f0
  /* 016BE0 80015FE0 02402025 */        or $a0, $s2, $zero
  /* 016BE4 80015FE4 4502000B */     bc1fl .L80016014
  /* 016BE8 80015FE8 8E060004 */        lw $a2, 4($s0)
  /* 016BEC 80015FEC 8E380000 */        lw $t8, ($s1) # D_800472A8 + 0
  .L80015FF0:
  /* 016BF0 80015FF0 26100008 */     addiu $s0, $s0, 8
  /* 016BF4 80015FF4 27190001 */     addiu $t9, $t8, 1
  /* 016BF8 80015FF8 AE390000 */        sw $t9, ($s1) # D_800472A8 + 0
  /* 016BFC 80015FFC C6080000 */      lwc1 $f8, ($s0)
  /* 016C00 80016000 4608103C */    c.lt.s $f2, $f8
  /* 016C04 80016004 00000000 */       nop 
  /* 016C08 80016008 4503FFF9 */     bc1tl .L80015FF0
  /* 016C0C 8001600C 8E380000 */        lw $t8, ($s1) # D_800472A8 + 0
  /* 016C10 80016010 8E060004 */        lw $a2, 4($s0)
  .L80016014:
  /* 016C14 80016014 8E4D0000 */        lw $t5, ($s2) # D_800470B0 + 0
  /* 016C18 80016018 02602825 */        or $a1, $s3, $zero
  /* 016C1C 8001601C AFA60034 */        sw $a2, 0x34($sp)
  /* 016C20 80016020 0C00435C */       jal func_80010D70
  /* 016C24 80016024 AFAD0030 */        sw $t5, 0x30($sp)
  /* 016C28 80016028 8FA60034 */        lw $a2, 0x34($sp)
  /* 016C2C 8001602C 00405825 */        or $t3, $v0, $zero
  /* 016C30 80016030 50C00057 */      beql $a2, $zero, .L80016190
  /* 016C34 80016034 8E640010 */        lw $a0, 0x10($s3)
  /* 016C38 80016038 926E0054 */       lbu $t6, 0x54($s3)
  /* 016C3C 8001603C 31CF0001 */      andi $t7, $t6, 1
  /* 016C40 80016040 55E00053 */      bnel $t7, $zero, .L80016190
  /* 016C44 80016044 8E640010 */        lw $a0, 0x10($s3)
  /* 016C48 80016048 8CC20000 */        lw $v0, ($a2)
  /* 016C4C 8001604C 24010004 */     addiu $at, $zero, 4
  /* 016C50 80016050 3C118004 */       lui $s1, %hi(D_800465B0)
  /* 016C54 80016054 1041004D */       beq $v0, $at, .L8001618C
  /* 016C58 80016058 263165B0 */     addiu $s1, $s1, %lo(D_800465B0)
  /* 016C5C 8001605C 3C078004 */       lui $a3, %hi(D_800470B8)
  /* 016C60 80016060 24E770B8 */     addiu $a3, $a3, %lo(D_800470B8)
  /* 016C64 80016064 8CD80004 */        lw $t8, 4($a2)
  .L80016068:
  /* 016C68 80016068 00028080 */       sll $s0, $v0, 2
  /* 016C6C 8001606C 00F0C821 */      addu $t9, $a3, $s0
  /* 016C70 80016070 53000042 */      beql $t8, $zero, .L8001617C
  /* 016C74 80016074 8CC20008 */        lw $v0, 8($a2)
  /* 016C78 80016078 8F240000 */        lw $a0, ($t9)
  /* 016C7C 8001607C 8E4D0000 */        lw $t5, ($s2) # D_800470B0 + 0
  /* 016C80 80016080 11A40019 */       beq $t5, $a0, .L800160E8
  /* 016C84 80016084 02307021 */      addu $t6, $s1, $s0
  .L80016088:
  /* 016C88 80016088 8DCF0000 */        lw $t7, ($t6)
  /* 016C8C 8001608C 8C990000 */        lw $t9, ($a0)
  /* 016C90 80016090 ADF90000 */        sw $t9, ($t7)
  /* 016C94 80016094 8C980004 */        lw $t8, 4($a0)
  /* 016C98 80016098 ADF80004 */        sw $t8, 4($t7)
  /* 016C9C 8001609C 8CCD0000 */        lw $t5, ($a2)
  /* 016CA0 800160A0 000D7080 */       sll $t6, $t5, 2
  /* 016CA4 800160A4 022E1821 */      addu $v1, $s1, $t6
  /* 016CA8 800160A8 8C6F0000 */        lw $t7, ($v1)
  /* 016CAC 800160AC 25F80008 */     addiu $t8, $t7, 8
  /* 016CB0 800160B0 AC780000 */        sw $t8, ($v1)
  /* 016CB4 800160B4 8CD90000 */        lw $t9, ($a2)
  /* 016CB8 800160B8 00196880 */       sll $t5, $t9, 2
  /* 016CBC 800160BC 00ED1021 */      addu $v0, $a3, $t5
  /* 016CC0 800160C0 8C4E0000 */        lw $t6, ($v0)
  /* 016CC4 800160C4 8E590000 */        lw $t9, ($s2) # D_800470B0 + 0
  /* 016CC8 800160C8 25CF0008 */     addiu $t7, $t6, 8
  /* 016CCC 800160CC AC4F0000 */        sw $t7, ($v0)
  /* 016CD0 800160D0 8CD00000 */        lw $s0, ($a2)
  /* 016CD4 800160D4 00108080 */       sll $s0, $s0, 2
  /* 016CD8 800160D8 00F0C021 */      addu $t8, $a3, $s0
  /* 016CDC 800160DC 8F040000 */        lw $a0, ($t8)
  /* 016CE0 800160E0 5724FFE9 */      bnel $t9, $a0, .L80016088
  /* 016CE4 800160E4 02307021 */      addu $t6, $s1, $s0
  .L800160E8:
  /* 016CE8 800160E8 8E6D0080 */        lw $t5, 0x80($s3)
  /* 016CEC 800160EC 51A0001B */      beql $t5, $zero, .L8001615C
  /* 016CF0 800160F0 02301821 */      addu $v1, $s1, $s0
  /* 016CF4 800160F4 1680000F */      bnez $s4, .L80016134
  /* 016CF8 800160F8 02301821 */      addu $v1, $s1, $s0
  /* 016CFC 800160FC 3C148004 */       lui $s4, %hi(gMatrixHeap + 12)
  /* 016D00 80016100 8E9465E4 */        lw $s4, %lo(gMatrixHeap + 12)($s4)
  /* 016D04 80016104 02602025 */        or $a0, $s3, $zero
  /* 016D08 80016108 02302821 */      addu $a1, $s1, $s0
  /* 016D0C 8001610C AFA60034 */        sw $a2, 0x34($sp)
  /* 016D10 80016110 0C004B64 */       jal func_80012D90
  /* 016D14 80016114 AFAB0044 */        sw $t3, 0x44($sp)
  /* 016D18 80016118 8FA60034 */        lw $a2, 0x34($sp)
  /* 016D1C 8001611C 3C078004 */       lui $a3, %hi(D_800470B8)
  /* 016D20 80016120 24E770B8 */     addiu $a3, $a3, %lo(D_800470B8)
  /* 016D24 80016124 8CD00000 */        lw $s0, ($a2)
  /* 016D28 80016128 8FAB0044 */        lw $t3, 0x44($sp)
  /* 016D2C 8001612C 1000000A */         b .L80016158
  /* 016D30 80016130 00108080 */       sll $s0, $s0, 2
  .L80016134:
  /* 016D34 80016134 8C620000 */        lw $v0, ($v1)
  /* 016D38 80016138 3C0FDB06 */       lui $t7, (0xDB060038 >> 16) # 3674603576
  /* 016D3C 8001613C 35EF0038 */       ori $t7, $t7, (0xDB060038 & 0xFFFF) # 3674603576
  /* 016D40 80016140 244E0008 */     addiu $t6, $v0, 8
  /* 016D44 80016144 AC6E0000 */        sw $t6, ($v1)
  /* 016D48 80016148 AC540004 */        sw $s4, 4($v0)
  /* 016D4C 8001614C AC4F0000 */        sw $t7, ($v0)
  /* 016D50 80016150 8CD00000 */        lw $s0, ($a2)
  /* 016D54 80016154 00108080 */       sll $s0, $s0, 2
  .L80016158:
  /* 016D58 80016158 02301821 */      addu $v1, $s1, $s0
  .L8001615C:
  /* 016D5C 8001615C 8C620000 */        lw $v0, ($v1)
  /* 016D60 80016160 3C19DE00 */       lui $t9, 0xde00
  /* 016D64 80016164 24580008 */     addiu $t8, $v0, 8
  /* 016D68 80016168 AC780000 */        sw $t8, ($v1)
  /* 016D6C 8001616C AC590000 */        sw $t9, ($v0)
  /* 016D70 80016170 8CCD0004 */        lw $t5, 4($a2)
  /* 016D74 80016174 AC4D0004 */        sw $t5, 4($v0)
  /* 016D78 80016178 8CC20008 */        lw $v0, 8($a2)
  .L8001617C:
  /* 016D7C 8001617C 24010004 */     addiu $at, $zero, 4
  /* 016D80 80016180 24C60008 */     addiu $a2, $a2, 8
  /* 016D84 80016184 5441FFB8 */      bnel $v0, $at, .L80016068
  /* 016D88 80016188 8CD80004 */        lw $t8, 4($a2)
  .L8001618C:
  /* 016D8C 8001618C 8E640010 */        lw $a0, 0x10($s3)
  .L80016190:
  /* 016D90 80016190 3C118004 */       lui $s1, %hi(D_800465B0)
  /* 016D94 80016194 263165B0 */     addiu $s1, $s1, %lo(D_800465B0)
  /* 016D98 80016198 50800005 */      beql $a0, $zero, .L800161B0
  /* 016D9C 8001619C 8FAE0030 */        lw $t6, 0x30($sp)
  /* 016DA0 800161A0 0C005703 */       jal func_80015C0C
  /* 016DA4 800161A4 AFAB0044 */        sw $t3, 0x44($sp)
  /* 016DA8 800161A8 8FAB0044 */        lw $t3, 0x44($sp)
  /* 016DAC 800161AC 8FAE0030 */        lw $t6, 0x30($sp)
  .L800161B0:
  /* 016DB0 800161B0 3C068004 */       lui $a2, %hi(D_800470B8)
  /* 016DB4 800161B4 3C0C8004 */       lui $t4, %hi(D_800470C8)
  /* 016DB8 800161B8 3C09D838 */       lui $t1, (0xD8380002 >> 16) # 3627548674
  /* 016DBC 800161BC 35290002 */       ori $t1, $t1, (0xD8380002 & 0xFFFF) # 3627548674
  /* 016DC0 800161C0 258C70C8 */     addiu $t4, $t4, %lo(D_800470C8)
  /* 016DC4 800161C4 24C670B8 */     addiu $a2, $a2, %lo(D_800470B8)
  /* 016DC8 800161C8 00003825 */        or $a3, $zero, $zero
  /* 016DCC 800161CC 240A0040 */     addiu $t2, $zero, 0x40
  /* 016DD0 800161D0 24080001 */     addiu $t0, $zero, 1
  /* 016DD4 800161D4 AE4E0000 */        sw $t6, ($s2) # D_800470B0 + 0
  .L800161D8:
  /* 016DD8 800161D8 8E450000 */        lw $a1, ($s2) # D_800470B0 + 0
  /* 016DDC 800161DC 8CCF0000 */        lw $t7, ($a2) # D_800470B8 + 0
  /* 016DE0 800161E0 00AF082B */      sltu $at, $a1, $t7
  /* 016DE4 800161E4 50200011 */      beql $at, $zero, .L8001622C
  /* 016DE8 800161E8 8CCE0004 */        lw $t6, 4($a2) # D_800470B8 + 4
  /* 016DEC 800161EC 1160000E */      beqz $t3, .L80016228
  /* 016DF0 800161F0 ACC50000 */        sw $a1, ($a2) # D_800470B8 + 0
  /* 016DF4 800161F4 8E780014 */        lw $t8, 0x14($s3)
  /* 016DF8 800161F8 02271821 */      addu $v1, $s1, $a3
  /* 016DFC 800161FC 51180005 */      beql $t0, $t8, .L80016214
  /* 016E00 80016200 8C640000 */        lw $a0, ($v1)
  /* 016E04 80016204 8E790008 */        lw $t9, 8($s3)
  /* 016E08 80016208 53200008 */      beql $t9, $zero, .L8001622C
  /* 016E0C 8001620C 8CCE0004 */        lw $t6, 4($a2) # D_800470B8 + 4
  /* 016E10 80016210 8C640000 */        lw $a0, ($v1)
  .L80016214:
  /* 016E14 80016214 248D0008 */     addiu $t5, $a0, 8
  /* 016E18 80016218 AC6D0000 */        sw $t5, ($v1)
  /* 016E1C 8001621C AC8A0004 */        sw $t2, 4($a0)
  /* 016E20 80016220 AC890000 */        sw $t1, ($a0)
  /* 016E24 80016224 8E450000 */        lw $a1, ($s2) # D_800470B0 + 0
  .L80016228:
  /* 016E28 80016228 8CCE0004 */        lw $t6, 4($a2) # D_800470B8 + 4
  .L8001622C:
  /* 016E2C 8001622C 00AE082B */      sltu $at, $a1, $t6
  /* 016E30 80016230 50200010 */      beql $at, $zero, .L80016274
  /* 016E34 80016234 24C60008 */     addiu $a2, $a2, 8
  /* 016E38 80016238 1160000D */      beqz $t3, .L80016270
  /* 016E3C 8001623C ACC50004 */        sw $a1, 4($a2) # D_800470B8 + 4
  /* 016E40 80016240 8E6F0014 */        lw $t7, 0x14($s3)
  /* 016E44 80016244 02271821 */      addu $v1, $s1, $a3
  /* 016E48 80016248 510F0005 */      beql $t0, $t7, .L80016260
  /* 016E4C 8001624C 8C640004 */        lw $a0, 4($v1)
  /* 016E50 80016250 8E780008 */        lw $t8, 8($s3)
  /* 016E54 80016254 53000007 */      beql $t8, $zero, .L80016274
  /* 016E58 80016258 24C60008 */     addiu $a2, $a2, 8
  /* 016E5C 8001625C 8C640004 */        lw $a0, 4($v1)
  .L80016260:
  /* 016E60 80016260 24990008 */     addiu $t9, $a0, 8
  /* 016E64 80016264 AC790004 */        sw $t9, 4($v1)
  /* 016E68 80016268 AC8A0004 */        sw $t2, 4($a0)
  /* 016E6C 8001626C AC890000 */        sw $t1, ($a0)
  .L80016270:
  /* 016E70 80016270 24C60008 */     addiu $a2, $a2, 8
  .L80016274:
  /* 016E74 80016274 14CCFFD8 */       bne $a2, $t4, .L800161D8
  /* 016E78 80016278 24E70008 */     addiu $a3, $a3, 8
  /* 016E7C 8001627C 8E6D000C */        lw $t5, 0xc($s3)
  /* 016E80 80016280 55A0000A */      bnel $t5, $zero, .L800162AC
  /* 016E84 80016284 8FBF002C */        lw $ra, 0x2c($sp)
  /* 016E88 80016288 8E700008 */        lw $s0, 8($s3)
  /* 016E8C 8001628C 52000007 */      beql $s0, $zero, .L800162AC
  /* 016E90 80016290 8FBF002C */        lw $ra, 0x2c($sp)
  .L80016294:
  /* 016E94 80016294 0C005703 */       jal func_80015C0C
  /* 016E98 80016298 02002025 */        or $a0, $s0, $zero
  /* 016E9C 8001629C 8E100008 */        lw $s0, 8($s0)
  /* 016EA0 800162A0 1600FFFC */      bnez $s0, .L80016294
  /* 016EA4 800162A4 00000000 */       nop 
  .L800162A8:
  /* 016EA8 800162A8 8FBF002C */        lw $ra, 0x2c($sp)
  .L800162AC:
  /* 016EAC 800162AC 8FB00018 */        lw $s0, 0x18($sp)
  /* 016EB0 800162B0 8FB1001C */        lw $s1, 0x1c($sp)
  /* 016EB4 800162B4 8FB20020 */        lw $s2, 0x20($sp)
  /* 016EB8 800162B8 8FB30024 */        lw $s3, 0x24($sp)
  /* 016EBC 800162BC 8FB40028 */        lw $s4, 0x28($sp)
  /* 016EC0 800162C0 03E00008 */        jr $ra
  /* 016EC4 800162C4 27BD0050 */     addiu $sp, $sp, 0x50
