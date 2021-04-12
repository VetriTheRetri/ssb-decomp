.include "macros.inc"

.section .data

glabel D_8003B750
  .incbin "system.raw.bin", 0x3B350, 0x8

glabel D_8003B758
  .incbin "system.raw.bin", 0x3B358, 0x40

glabel D_8003B798
  .incbin "system.raw.bin", 0x3B398, 0xC
  /* 3B3A4 03C3A4 8003B7A4 */  .4byte D_800466A0
  .incbin "system.raw.bin", 0x3B3A8, 0x3C
  /* 3B3E4 03C3E4 8003B7E4 */  .4byte D_8003B758
  .incbin "system.raw.bin", 0x3B3E8, 0x4
  /* 3B3EC 03C3EC 8003B7EC */  .4byte D_8003B758
  .incbin "system.raw.bin", 0x3B3F0, 0x80

.section .bss 

glabel D_800466A0
    .space 16

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .text

.align 4

# Likely start of new file
glabel func_80007080
  /* 007C80 80007080 44856000 */      mtc1 $a1, $f12
  /* 007C84 80007084 44877000 */      mtc1 $a3, $f14
  /* 007C88 80007088 3C013F00 */       lui $at, (0x3F000000 >> 16) # 0.5
  /* 007C8C 8000708C 44818000 */      mtc1 $at, $f16 # 0.5 to cop1
  /* 007C90 80007090 460E6100 */     add.s $f4, $f12, $f14
  /* 007C94 80007094 3C014080 */       lui $at, (0x40800000 >> 16) # 4.0
  /* 007C98 80007098 44819000 */      mtc1 $at, $f18 # 4.0 to cop1
  /* 007C9C 8000709C AFA60008 */        sw $a2, 8($sp)
  /* 007CA0 800070A0 46102002 */     mul.s $f0, $f4, $f16
  /* 007CA4 800070A4 46007181 */     sub.s $f6, $f14, $f0
  /* 007CA8 800070A8 46123202 */     mul.s $f8, $f6, $f18
  /* 007CAC 800070AC 4600428D */ trunc.w.s $f10, $f8
  /* 007CB0 800070B0 44185000 */      mfc1 $t8, $f10
  /* 007CB4 800070B4 00000000 */       nop 
  /* 007CB8 800070B8 A4980000 */        sh $t8, ($a0)
  /* 007CBC 800070BC C7A60010 */      lwc1 $f6, 0x10($sp)
  /* 007CC0 800070C0 C7A40008 */      lwc1 $f4, 8($sp)
  /* 007CC4 800070C4 241801FF */     addiu $t8, $zero, 0x1ff
  /* 007CC8 800070C8 A498000C */        sh $t8, 0xc($a0)
  /* 007CCC 800070CC 46062200 */     add.s $f8, $f4, $f6
  /* 007CD0 800070D0 8499000C */        lh $t9, 0xc($a0)
  /* 007CD4 800070D4 46104082 */     mul.s $f2, $f8, $f16
  /* 007CD8 800070D8 A4990004 */        sh $t9, 4($a0)
  /* 007CDC 800070DC 46023281 */     sub.s $f10, $f6, $f2
  /* 007CE0 800070E0 46125102 */     mul.s $f4, $f10, $f18
  /* 007CE4 800070E4 4600220D */ trunc.w.s $f8, $f4
  /* 007CE8 800070E8 46120182 */     mul.s $f6, $f0, $f18
  /* 007CEC 800070EC 00000000 */       nop 
  /* 007CF0 800070F0 46121102 */     mul.s $f4, $f2, $f18
  /* 007CF4 800070F4 44094000 */      mfc1 $t1, $f8
  /* 007CF8 800070F8 00000000 */       nop 
  /* 007CFC 800070FC A4890002 */        sh $t1, 2($a0)
  /* 007D00 80007100 4600328D */ trunc.w.s $f10, $f6
  /* 007D04 80007104 4600220D */ trunc.w.s $f8, $f4
  /* 007D08 80007108 440C5000 */      mfc1 $t4, $f10
  /* 007D0C 8000710C 440F4000 */      mfc1 $t7, $f8
  /* 007D10 80007110 A48C0008 */        sh $t4, 8($a0)
  /* 007D14 80007114 03E00008 */        jr $ra
  /* 007D18 80007118 A48F000A */        sh $t7, 0xa($a0)

glabel func_8000711C
  /* 007D1C 8000711C 3C028004 */       lui $v0, %hi(D_80046678)
  /* 007D20 80007120 8C426678 */        lw $v0, %lo(D_80046678)($v0)
  /* 007D24 80007124 240E01FF */     addiu $t6, $zero, 0x1ff
  /* 007D28 80007128 00021040 */       sll $v0, $v0, 1
  /* 007D2C 8000712C 00021400 */       sll $v0, $v0, 0x10
  /* 007D30 80007130 00021403 */       sra $v0, $v0, 0x10
  /* 007D34 80007134 A4820008 */        sh $v0, 8($a0)
  /* 007D38 80007138 A4820000 */        sh $v0, ($a0)
  /* 007D3C 8000713C 3C028004 */       lui $v0, %hi(D_8004667C)
  /* 007D40 80007140 8C42667C */        lw $v0, %lo(D_8004667C)($v0)
  /* 007D44 80007144 A48E000C */        sh $t6, 0xc($a0)
  /* 007D48 80007148 848F000C */        lh $t7, 0xc($a0)
  /* 007D4C 8000714C 00021040 */       sll $v0, $v0, 1
  /* 007D50 80007150 00021400 */       sll $v0, $v0, 0x10
  /* 007D54 80007154 00021403 */       sra $v0, $v0, 0x10
  /* 007D58 80007158 A482000A */        sh $v0, 0xa($a0)
  /* 007D5C 8000715C A4820002 */        sh $v0, 2($a0)
  /* 007D60 80007160 03E00008 */        jr $ra
  /* 007D64 80007164 A48F0004 */        sh $t7, 4($a0)

glabel func_80007168
  /* 007D68 80007168 3C018004 */       lui $at, %hi(D_8003B750)
  /* 007D6C 8000716C 03E00008 */        jr $ra
  /* 007D70 80007170 AC24B750 */        sw $a0, %lo(D_8003B750)($at)

glabel func_80007174
  /* 007D74 80007174 27BDFFC8 */     addiu $sp, $sp, -0x38
  /* 007D78 80007178 AFBF0014 */        sw $ra, 0x14($sp)
  /* 007D7C 8000717C AFA40038 */        sw $a0, 0x38($sp)
  /* 007D80 80007180 8C8F0000 */        lw $t7, ($a0)
  /* 007D84 80007184 3C19DB06 */       lui $t9, 0xdb06
  /* 007D88 80007188 27A40034 */     addiu $a0, $sp, 0x34
  /* 007D8C 8000718C AFAF0034 */        sw $t7, 0x34($sp)
  /* 007D90 80007190 25F80008 */     addiu $t8, $t7, 8
  /* 007D94 80007194 AFB80034 */        sw $t8, 0x34($sp)
  /* 007D98 80007198 ADE00004 */        sw $zero, 4($t7)
  /* 007D9C 8000719C 0C00123E */       jal func_800048F8
  /* 007DA0 800071A0 ADF90000 */        sw $t9, ($t7)
  /* 007DA4 800071A4 8FAC0034 */        lw $t4, 0x34($sp)
  /* 007DA8 800071A8 3C0EFE00 */       lui $t6, 0xfe00
  /* 007DAC 800071AC 3C0F8004 */       lui $t7, %hi(D_80046670)
  /* 007DB0 800071B0 258D0008 */     addiu $t5, $t4, 8
  /* 007DB4 800071B4 AFAD0034 */        sw $t5, 0x34($sp)
  /* 007DB8 800071B8 AD8E0000 */        sw $t6, ($t4)
  /* 007DBC 800071BC 8DEF6670 */        lw $t7, %lo(D_80046670)($t7)
  /* 007DC0 800071C0 3C048004 */       lui $a0, %hi(D_800466A0)
  /* 007DC4 800071C4 248466A0 */     addiu $a0, $a0, %lo(D_800466A0)
  /* 007DC8 800071C8 0C001C47 */       jal func_8000711C
  /* 007DCC 800071CC AD8F0004 */        sw $t7, 4($t4)
  /* 007DD0 800071D0 8FB80034 */        lw $t8, 0x34($sp)
  /* 007DD4 800071D4 3C0D8004 */       lui $t5, %hi(D_8003B798)
  /* 007DD8 800071D8 3C088004 */       lui $t0, %hi(D_80046678)
  /* 007DDC 800071DC 27190008 */     addiu $t9, $t8, 8
  /* 007DE0 800071E0 AFB90034 */        sw $t9, 0x34($sp)
  /* 007DE4 800071E4 25ADB798 */     addiu $t5, $t5, %lo(D_8003B798)
  /* 007DE8 800071E8 3C0CDE00 */       lui $t4, (0xDE000000 >> 16) # -2.305843e18
  /* 007DEC 800071EC 25086678 */     addiu $t0, $t0, %lo(D_80046678)
  /* 007DF0 800071F0 AF0C0000 */        sw $t4, ($t8)
  /* 007DF4 800071F4 AF0D0004 */        sw $t5, 4($t8)
  /* 007DF8 800071F8 03001025 */        or $v0, $t8, $zero
  /* 007DFC 800071FC 8D180000 */        lw $t8, ($t0) # D_80046678 + 0
  /* 007E00 80007200 24090140 */     addiu $t1, $zero, 0x140
  /* 007E04 80007204 2406000A */     addiu $a2, $zero, 0xa
  /* 007E08 80007208 0309001A */       div $zero, $t8, $t1
  /* 007E0C 8000720C 0000C812 */      mflo $t9
  /* 007E10 80007210 3C0A8004 */       lui $t2, %hi(D_8004667C)
  /* 007E14 80007214 254A667C */     addiu $t2, $t2, %lo(D_8004667C)
  /* 007E18 80007218 03260019 */     multu $t9, $a2
  /* 007E1C 8000721C 240B00F0 */     addiu $t3, $zero, 0xf0
  /* 007E20 80007220 3C014080 */       lui $at, (0x40800000 >> 16) # 4.0
  /* 007E24 80007224 44810000 */      mtc1 $at, $f0 # 4.0 to cop1
  /* 007E28 80007228 8FAE0034 */        lw $t6, 0x34($sp)
  /* 007E2C 8000722C 3C078004 */       lui $a3, %hi(D_8003B750)
  /* 007E30 80007230 01C01825 */        or $v1, $t6, $zero
  /* 007E34 80007234 25CF0008 */     addiu $t7, $t6, 8
  /* 007E38 80007238 AFAF0034 */        sw $t7, 0x34($sp)
  /* 007E3C 8000723C 00006012 */      mflo $t4
  /* 007E40 80007240 448C2000 */      mtc1 $t4, $f4 # -2.305843e18 to cop1
  /* 007E44 80007244 8D4C0000 */        lw $t4, ($t2) # D_8004667C + 0
  /* 007E48 80007248 15200002 */      bnez $t1, .L80007254
  /* 007E4C 8000724C 00000000 */       nop 
  /* 007E50 80007250 0007000D */     break 7
  .L80007254:
  /* 007E54 80007254 2401FFFF */     addiu $at, $zero, -1
  /* 007E58 80007258 15210004 */       bne $t1, $at, .L8000726C
  /* 007E5C 8000725C 3C018000 */       lui $at, 0x8000
  /* 007E60 80007260 17010002 */       bne $t8, $at, .L8000726C
  /* 007E64 80007264 00000000 */       nop 
  /* 007E68 80007268 0006000D */     break 6
  .L8000726C:
  /* 007E6C 8000726C 018B001A */       div $zero, $t4, $t3
  /* 007E70 80007270 468021A0 */   cvt.s.w $f6, $f4
  /* 007E74 80007274 00006812 */      mflo $t5
  /* 007E78 80007278 3C01ED00 */       lui $at, 0xed00
  /* 007E7C 8000727C 00000000 */       nop 
  /* 007E80 80007280 01A60019 */     multu $t5, $a2
  /* 007E84 80007284 46003202 */     mul.s $f8, $f6, $f0
  /* 007E88 80007288 4600428D */ trunc.w.s $f10, $f8
  /* 007E8C 8000728C 440E5000 */      mfc1 $t6, $f10
  /* 007E90 80007290 00000000 */       nop 
  /* 007E94 80007294 31CF0FFF */      andi $t7, $t6, 0xfff
  /* 007E98 80007298 00007012 */      mflo $t6
  /* 007E9C 8000729C 448E8000 */      mtc1 $t6, $f16
  /* 007EA0 800072A0 000FC300 */       sll $t8, $t7, 0xc
  /* 007EA4 800072A4 0301C825 */        or $t9, $t8, $at
  /* 007EA8 800072A8 468084A0 */   cvt.s.w $f18, $f16
  /* 007EAC 800072AC 15600002 */      bnez $t3, .L800072B8
  /* 007EB0 800072B0 00000000 */       nop 
  /* 007EB4 800072B4 0007000D */     break 7
  .L800072B8:
  /* 007EB8 800072B8 2401FFFF */     addiu $at, $zero, -1
  /* 007EBC 800072BC 15610004 */       bne $t3, $at, .L800072D0
  /* 007EC0 800072C0 3C018000 */       lui $at, 0x8000
  /* 007EC4 800072C4 15810002 */       bne $t4, $at, .L800072D0
  /* 007EC8 800072C8 00000000 */       nop 
  /* 007ECC 800072CC 0006000D */     break 6
  .L800072D0:
  /* 007ED0 800072D0 46009102 */     mul.s $f4, $f18, $f0
  /* 007ED4 800072D4 4600218D */ trunc.w.s $f6, $f4
  /* 007ED8 800072D8 44183000 */      mfc1 $t8, $f6
  /* 007EDC 800072DC 00000000 */       nop 
  /* 007EE0 800072E0 330C0FFF */      andi $t4, $t8, 0xfff
  /* 007EE4 800072E4 032C6825 */        or $t5, $t9, $t4
  /* 007EE8 800072E8 AC6D0000 */        sw $t5, ($v1)
  /* 007EEC 800072EC 8D040000 */        lw $a0, ($t0) # D_80046678 + 0
  /* 007EF0 800072F0 8D450000 */        lw $a1, ($t2) # D_8004667C + 0
  /* 007EF4 800072F4 0089001A */       div $zero, $a0, $t1
  /* 007EF8 800072F8 00007012 */      mflo $t6
  /* 007EFC 800072FC 15200002 */      bnez $t1, .L80007308
  /* 007F00 80007300 00000000 */       nop 
  /* 007F04 80007304 0007000D */     break 7
  .L80007308:
  /* 007F08 80007308 2401FFFF */     addiu $at, $zero, -1
  /* 007F0C 8000730C 15210004 */       bne $t1, $at, .L80007320
  /* 007F10 80007310 3C018000 */       lui $at, 0x8000
  /* 007F14 80007314 14810002 */       bne $a0, $at, .L80007320
  /* 007F18 80007318 00000000 */       nop 
  /* 007F1C 8000731C 0006000D */     break 6
  .L80007320:
  /* 007F20 80007320 01C60019 */     multu $t6, $a2
  /* 007F24 80007324 00007812 */      mflo $t7
  /* 007F28 80007328 008FC023 */      subu $t8, $a0, $t7
  /* 007F2C 8000732C 44984000 */      mtc1 $t8, $f8
  /* 007F30 80007330 00AB001A */       div $zero, $a1, $t3
  /* 007F34 80007334 00007812 */      mflo $t7
  /* 007F38 80007338 468042A0 */   cvt.s.w $f10, $f8
  /* 007F3C 8000733C 00000000 */       nop 
  /* 007F40 80007340 01E60019 */     multu $t7, $a2
  /* 007F44 80007344 46005402 */     mul.s $f16, $f10, $f0
  /* 007F48 80007348 0000C012 */      mflo $t8
  /* 007F4C 8000734C 00B8C823 */      subu $t9, $a1, $t8
  /* 007F50 80007350 44992000 */      mtc1 $t9, $f4
  /* 007F54 80007354 4600848D */ trunc.w.s $f18, $f16
  /* 007F58 80007358 468021A0 */   cvt.s.w $f6, $f4
  /* 007F5C 8000735C 440C9000 */      mfc1 $t4, $f18
  /* 007F60 80007360 00000000 */       nop 
  /* 007F64 80007364 318D0FFF */      andi $t5, $t4, 0xfff
  /* 007F68 80007368 000D7300 */       sll $t6, $t5, 0xc
  /* 007F6C 8000736C 46003202 */     mul.s $f8, $f6, $f0
  /* 007F70 80007370 15600002 */      bnez $t3, .L8000737C
  /* 007F74 80007374 00000000 */       nop 
  /* 007F78 80007378 0007000D */     break 7
  .L8000737C:
  /* 007F7C 8000737C 2401FFFF */     addiu $at, $zero, -1
  /* 007F80 80007380 15610004 */       bne $t3, $at, .L80007394
  /* 007F84 80007384 3C018000 */       lui $at, 0x8000
  /* 007F88 80007388 14A10002 */       bne $a1, $at, .L80007394
  /* 007F8C 8000738C 00000000 */       nop 
  /* 007F90 80007390 0006000D */     break 6
  .L80007394:
  /* 007F94 80007394 4600428D */ trunc.w.s $f10, $f8
  /* 007F98 80007398 440D5000 */      mfc1 $t5, $f10
  /* 007F9C 8000739C 00000000 */       nop 
  /* 007FA0 800073A0 31AF0FFF */      andi $t7, $t5, 0xfff
  /* 007FA4 800073A4 01CFC025 */        or $t8, $t6, $t7
  /* 007FA8 800073A8 AC780004 */        sw $t8, 4($v1)
  /* 007FAC 800073AC 8CE7B750 */        lw $a3, %lo(D_8003B750)($a3)
  /* 007FB0 800073B0 50E00004 */      beql $a3, $zero, .L800073C4
  /* 007FB4 800073B4 8FB90034 */        lw $t9, 0x34($sp)
  /* 007FB8 800073B8 00E0F809 */      jalr $a3
  /* 007FBC 800073BC 27A40034 */     addiu $a0, $sp, 0x34
  /* 007FC0 800073C0 8FB90034 */        lw $t9, 0x34($sp)
  .L800073C4:
  /* 007FC4 800073C4 8FAC0038 */        lw $t4, 0x38($sp)
  /* 007FC8 800073C8 AD990000 */        sw $t9, ($t4)
  /* 007FCC 800073CC 8FBF0014 */        lw $ra, 0x14($sp)
  /* 007FD0 800073D0 27BD0038 */     addiu $sp, $sp, 0x38
  /* 007FD4 800073D4 03E00008 */        jr $ra
  /* 007FD8 800073D8 00000000 */       nop 

  /* 007FDC 800073DC 00000000 */       nop 