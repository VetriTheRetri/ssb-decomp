.section .text
glabel func_80014068
  /* 014C68 80014068 27BDFFC8 */     addiu $sp, $sp, -0x38
  /* 014C6C 8001406C AFB00018 */        sw $s0, 0x18($sp)
  /* 014C70 80014070 240EFFFF */     addiu $t6, $zero, -1
  /* 014C74 80014074 00808025 */        or $s0, $a0, $zero
  /* 014C78 80014078 AFBF001C */        sw $ra, 0x1c($sp)
  /* 014C7C 8001407C 00A03825 */        or $a3, $a1, $zero
  /* 014C80 80014080 10A000D9 */      beqz $a1, .L800143E8
  /* 014C84 80014084 AFAE0030 */        sw $t6, 0x30($sp)
  /* 014C88 80014088 908F0054 */       lbu $t7, 0x54($a0)
  /* 014C8C 8001408C 3C038004 */       lui $v1, %hi(D_800465B0)
  /* 014C90 80014090 55E000D6 */      bnel $t7, $zero, .L800143EC
  /* 014C94 80014094 8FBF001C */        lw $ra, 0x1c($sp)
  /* 014C98 80014098 8CB80000 */        lw $t8, ($a1)
  /* 014C9C 8001409C 246365B0 */     addiu $v1, $v1, %lo(D_800465B0)
  /* 014CA0 800140A0 02002825 */        or $a1, $s0, $zero
  /* 014CA4 800140A4 0018C880 */       sll $t9, $t8, 2
  /* 014CA8 800140A8 00792021 */      addu $a0, $v1, $t9
  /* 014CAC 800140AC 8C890000 */        lw $t1, ($a0)
  /* 014CB0 800140B0 AFA7003C */        sw $a3, 0x3c($sp)
  /* 014CB4 800140B4 0C00435C */       jal func_80010D70
  /* 014CB8 800140B8 AFA9002C */        sw $t1, 0x2c($sp)
  /* 014CBC 800140BC 8FA7003C */        lw $a3, 0x3c($sp)
  /* 014CC0 800140C0 3C038004 */       lui $v1, %hi(D_800465B0)
  /* 014CC4 800140C4 246365B0 */     addiu $v1, $v1, %lo(D_800465B0)
  /* 014CC8 800140C8 8CE50000 */        lw $a1, ($a3)
  /* 014CCC 800140CC 8CEF0004 */        lw $t7, 4($a3)
  /* 014CD0 800140D0 8FA9002C */        lw $t1, 0x2c($sp)
  /* 014CD4 800140D4 00057080 */       sll $t6, $a1, 2
  /* 014CD8 800140D8 006E3021 */      addu $a2, $v1, $t6
  /* 014CDC 800140DC 00406025 */        or $t4, $v0, $zero
  /* 014CE0 800140E0 11E00032 */      beqz $t7, .L800141AC
  /* 014CE4 800140E4 8CC80000 */        lw $t0, ($a2)
  /* 014CE8 800140E8 3C188004 */       lui $t8, %hi(gMatrixHeap + 12)
  /* 014CEC 800140EC 8F1865E4 */        lw $t8, %lo(gMatrixHeap + 12)($t8)
  /* 014CF0 800140F0 02002025 */        or $a0, $s0, $zero
  /* 014CF4 800140F4 00C02825 */        or $a1, $a2, $zero
  /* 014CF8 800140F8 AFA7003C */        sw $a3, 0x3c($sp)
  /* 014CFC 800140FC AFA80028 */        sw $t0, 0x28($sp)
  /* 014D00 80014100 AFA9002C */        sw $t1, 0x2c($sp)
  /* 014D04 80014104 AFA20034 */        sw $v0, 0x34($sp)
  /* 014D08 80014108 0C004B64 */       jal func_80012D90
  /* 014D0C 8001410C AFB80020 */        sw $t8, 0x20($sp)
  /* 014D10 80014110 8FA7003C */        lw $a3, 0x3c($sp)
  /* 014D14 80014114 3C038004 */       lui $v1, %hi(D_800465B0)
  /* 014D18 80014118 246365B0 */     addiu $v1, $v1, %lo(D_800465B0)
  /* 014D1C 8001411C 8CF90000 */        lw $t9, ($a3)
  /* 014D20 80014120 8FAC0034 */        lw $t4, 0x34($sp)
  /* 014D24 80014124 8FA80028 */        lw $t0, 0x28($sp)
  /* 014D28 80014128 00197080 */       sll $t6, $t9, 2
  /* 014D2C 8001412C 006E3021 */      addu $a2, $v1, $t6
  /* 014D30 80014130 8CC20000 */        lw $v0, ($a2)
  /* 014D34 80014134 8FA9002C */        lw $t1, 0x2c($sp)
  /* 014D38 80014138 3C18DE00 */       lui $t8, 0xde00
  /* 014D3C 8001413C 244F0008 */     addiu $t7, $v0, 8
  /* 014D40 80014140 ACCF0000 */        sw $t7, ($a2)
  /* 014D44 80014144 AC580000 */        sw $t8, ($v0)
  /* 014D48 80014148 8CF90004 */        lw $t9, 4($a3)
  /* 014D4C 8001414C 11800013 */      beqz $t4, .L8001419C
  /* 014D50 80014150 AC590004 */        sw $t9, 4($v0)
  /* 014D54 80014154 8E0E0014 */        lw $t6, 0x14($s0)
  /* 014D58 80014158 24010001 */     addiu $at, $zero, 1
  /* 014D5C 8001415C 51C10005 */      beql $t6, $at, .L80014174
  /* 014D60 80014160 8CF80000 */        lw $t8, ($a3)
  /* 014D64 80014164 8E0F0008 */        lw $t7, 8($s0)
  /* 014D68 80014168 51E0000D */      beql $t7, $zero, .L800141A0
  /* 014D6C 8001416C 3C0DD838 */       lui $t5, 0xd838
  /* 014D70 80014170 8CF80000 */        lw $t8, ($a3)
  .L80014174:
  /* 014D74 80014174 3C0DD838 */       lui $t5, (0xD8380002 >> 16) # 3627548674
  /* 014D78 80014178 35AD0002 */       ori $t5, $t5, (0xD8380002 & 0xFFFF) # 3627548674
  /* 014D7C 8001417C 0018C880 */       sll $t9, $t8, 2
  /* 014D80 80014180 00793021 */      addu $a2, $v1, $t9
  /* 014D84 80014184 8CC20000 */        lw $v0, ($a2)
  /* 014D88 80014188 241F0040 */     addiu $ra, $zero, 0x40
  /* 014D8C 8001418C 244E0008 */     addiu $t6, $v0, 8
  /* 014D90 80014190 ACCE0000 */        sw $t6, ($a2)
  /* 014D94 80014194 AC5F0004 */        sw $ra, 4($v0)
  /* 014D98 80014198 AC4D0000 */        sw $t5, ($v0)
  .L8001419C:
  /* 014D9C 8001419C 3C0DD838 */       lui $t5, (0xD8380002 >> 16) # 3627548674
  .L800141A0:
  /* 014DA0 800141A0 35AD0002 */       ori $t5, $t5, (0xD8380002 & 0xFFFF) # 3627548674
  /* 014DA4 800141A4 10000005 */         b .L800141BC
  /* 014DA8 800141A8 241F0040 */     addiu $ra, $zero, 0x40
  .L800141AC:
  /* 014DAC 800141AC 3C0DD838 */       lui $t5, (0xD8380002 >> 16) # 3627548674
  /* 014DB0 800141B0 35AD0002 */       ori $t5, $t5, (0xD8380002 & 0xFFFF) # 3627548674
  /* 014DB4 800141B4 AFA50030 */        sw $a1, 0x30($sp)
  /* 014DB8 800141B8 241F0040 */     addiu $ra, $zero, 0x40
  .L800141BC:
  /* 014DBC 800141BC 8CE50008 */        lw $a1, 8($a3)
  /* 014DC0 800141C0 240B0004 */     addiu $t3, $zero, 4
  /* 014DC4 800141C4 24E70008 */     addiu $a3, $a3, 8
  /* 014DC8 800141C8 11650081 */       beq $t3, $a1, .L800143D0
  /* 014DCC 800141CC 3C0ADB06 */       lui $t2, (0xDB060038 >> 16) # 3674603576
  /* 014DD0 800141D0 354A0038 */       ori $t2, $t2, (0xDB060038 & 0xFFFF) # 3674603576
  /* 014DD4 800141D4 8CEF0004 */        lw $t7, 4($a3)
  .L800141D8:
  /* 014DD8 800141D8 51E0007A */      beql $t7, $zero, .L800143C4
  /* 014DDC 800141DC 8CE50008 */        lw $a1, 8($a3)
  /* 014DE0 800141E0 11280052 */       beq $t1, $t0, .L8001432C # sp2C == sp28
  /* 014DE4 800141E4 01201025 */        or $v0, $t1, $zero # v0 = sp2C (start)
  /* 014DE8 800141E8 01092823 */      subu $a1, $t0, $t1
  /* 014DEC 800141EC 30A5001F */      andi $a1, $a1, 0x1f
  /* 014DF0 800141F0 10A00013 */      beqz $a1, .L80014240
  /* 014DF4 800141F4 00A92021 */      addu $a0, $a1, $t1 # size + sp2C (start)
  .L800141F8:
  /* 014DF8 800141F8 8CF80000 */        lw $t8, ($a3)
  /* 014DFC 800141FC 24420008 */     addiu $v0, $v0, 8
  /* 014E00 80014200 0018C880 */       sll $t9, $t8, 2
  /* 014E04 80014204 00797021 */      addu $t6, $v1, $t9
  /* 014E08 80014208 8DCF0000 */        lw $t7, ($t6)
  /* 014E0C 8001420C 8C59FFF8 */        lw $t9, -8($v0)
  /* 014E10 80014210 ADF90000 */        sw $t9, ($t7)
  /* 014E14 80014214 8C58FFFC */        lw $t8, -4($v0)
  /* 014E18 80014218 ADF80004 */        sw $t8, 4($t7)
  /* 014E1C 8001421C 8CEE0000 */        lw $t6, ($a3)
  /* 014E20 80014220 000E7880 */       sll $t7, $t6, 2
  /* 014E24 80014224 006F3021 */      addu $a2, $v1, $t7
  /* 014E28 80014228 8CD80000 */        lw $t8, ($a2)
  /* 014E2C 8001422C 27190008 */     addiu $t9, $t8, 8
  /* 014E30 80014230 1482FFF1 */       bne $a0, $v0, .L800141F8
  /* 014E34 80014234 ACD90000 */        sw $t9, ($a2)
  
  /* 014E38 80014238 5048003C */      beql $v0, $t0, .L8001432C
  /* 014E3C 8001423C 8CE50000 */        lw $a1, ($a3)
  .L80014240:
  /* 014E40 80014240 8CEE0000 */        lw $t6, ($a3)
  /* 014E44 80014244 24420020 */     addiu $v0, $v0, 0x20
  /* 014E48 80014248 000E7880 */       sll $t7, $t6, 2
  /* 014E4C 8001424C 006FC021 */      addu $t8, $v1, $t7
  /* 014E50 80014250 8F190000 */        lw $t9, ($t8)
  /* 014E54 80014254 8C4FFFE0 */        lw $t7, -0x20($v0)
  /* 014E58 80014258 AF2F0000 */        sw $t7, ($t9)
  /* 014E5C 8001425C 8C4EFFE4 */        lw $t6, -0x1c($v0)
  /* 014E60 80014260 AF2E0004 */        sw $t6, 4($t9)
  /* 014E64 80014264 8CF80000 */        lw $t8, ($a3)
  /* 014E68 80014268 0018C880 */       sll $t9, $t8, 2
  /* 014E6C 8001426C 00793021 */      addu $a2, $v1, $t9
  /* 014E70 80014270 8CCE0000 */        lw $t6, ($a2)
  /* 014E74 80014274 25CF0008 */     addiu $t7, $t6, 8
  /* 014E78 80014278 ACCF0000 */        sw $t7, ($a2)
  /* 014E7C 8001427C 8CF80000 */        lw $t8, ($a3)
  /* 014E80 80014280 0018C880 */       sll $t9, $t8, 2
  /* 014E84 80014284 00797021 */      addu $t6, $v1, $t9
  /* 014E88 80014288 8DCF0000 */        lw $t7, ($t6)
  /* 014E8C 8001428C 8C59FFE8 */        lw $t9, -0x18($v0)
  /* 014E90 80014290 ADF90000 */        sw $t9, ($t7)
  /* 014E94 80014294 8C58FFEC */        lw $t8, -0x14($v0)
  /* 014E98 80014298 ADF80004 */        sw $t8, 4($t7)
  /* 014E9C 8001429C 8CEE0000 */        lw $t6, ($a3)
  /* 014EA0 800142A0 000E7880 */       sll $t7, $t6, 2
  /* 014EA4 800142A4 006F3021 */      addu $a2, $v1, $t7
  /* 014EA8 800142A8 8CD80000 */        lw $t8, ($a2)
  /* 014EAC 800142AC 27190008 */     addiu $t9, $t8, 8
  /* 014EB0 800142B0 ACD90000 */        sw $t9, ($a2)
  /* 014EB4 800142B4 8CEE0000 */        lw $t6, ($a3)
  /* 014EB8 800142B8 000E7880 */       sll $t7, $t6, 2
  /* 014EBC 800142BC 006FC021 */      addu $t8, $v1, $t7
  /* 014EC0 800142C0 8F190000 */        lw $t9, ($t8)
  /* 014EC4 800142C4 8C4FFFF0 */        lw $t7, -0x10($v0)
  /* 014EC8 800142C8 AF2F0000 */        sw $t7, ($t9)
  /* 014ECC 800142CC 8C4EFFF4 */        lw $t6, -0xc($v0)
  /* 014ED0 800142D0 AF2E0004 */        sw $t6, 4($t9)
  /* 014ED4 800142D4 8CF80000 */        lw $t8, ($a3)
  /* 014ED8 800142D8 0018C880 */       sll $t9, $t8, 2
  /* 014EDC 800142DC 00793021 */      addu $a2, $v1, $t9
  /* 014EE0 800142E0 8CCE0000 */        lw $t6, ($a2)
  /* 014EE4 800142E4 25CF0008 */     addiu $t7, $t6, 8
  /* 014EE8 800142E8 ACCF0000 */        sw $t7, ($a2)
  /* 014EEC 800142EC 8CF80000 */        lw $t8, ($a3)
  /* 014EF0 800142F0 0018C880 */       sll $t9, $t8, 2
  /* 014EF4 800142F4 00797021 */      addu $t6, $v1, $t9
  /* 014EF8 800142F8 8DCF0000 */        lw $t7, ($t6)
  /* 014EFC 800142FC 8C59FFF8 */        lw $t9, -8($v0)
  /* 014F00 80014300 ADF90000 */        sw $t9, ($t7)
  /* 014F04 80014304 8C58FFFC */        lw $t8, -4($v0)
  /* 014F08 80014308 ADF80004 */        sw $t8, 4($t7)
  /* 014F0C 8001430C 8CEE0000 */        lw $t6, ($a3)
  /* 014F10 80014310 000E7880 */       sll $t7, $t6, 2
  /* 014F14 80014314 006F3021 */      addu $a2, $v1, $t7
  /* 014F18 80014318 8CD80000 */        lw $t8, ($a2)
  /* 014F1C 8001431C 27190008 */     addiu $t9, $t8, 8
  /* 014F20 80014320 1448FFC7 */       bne $v0, $t0, .L80014240
  /* 014F24 80014324 ACD90000 */        sw $t9, ($a2)
  /* 014F28 80014328 8CE50000 */        lw $a1, ($a3)
  .L8001432C:
  /* 014F2C 8001432C 8E0E0080 */        lw $t6, 0x80($s0)
  /* 014F30 80014330 00057880 */       sll $t7, $a1, 2
  /* 014F34 80014334 006F3021 */      addu $a2, $v1, $t7
  /* 014F38 80014338 51C00009 */      beql $t6, $zero, .L80014360
  /* 014F3C 8001433C 00057080 */       sll $t6, $a1, 2
  /* 014F40 80014340 8CC20000 */        lw $v0, ($a2)
  /* 014F44 80014344 24580008 */     addiu $t8, $v0, 8
  /* 014F48 80014348 ACD80000 */        sw $t8, ($a2)
  /* 014F4C 8001434C AC4A0000 */        sw $t2, ($v0)
  /* 014F50 80014350 8FB90020 */        lw $t9, 0x20($sp)
  /* 014F54 80014354 AC590004 */        sw $t9, 4($v0)
  /* 014F58 80014358 8CE50000 */        lw $a1, ($a3)
  /* 014F5C 8001435C 00057080 */       sll $t6, $a1, 2
  .L80014360:
  /* 014F60 80014360 006E3021 */      addu $a2, $v1, $t6
  /* 014F64 80014364 8CC20000 */        lw $v0, ($a2)
  /* 014F68 80014368 3C18DE00 */       lui $t8, 0xde00
  /* 014F6C 8001436C 244F0008 */     addiu $t7, $v0, 8
  /* 014F70 80014370 ACCF0000 */        sw $t7, ($a2)
  /* 014F74 80014374 AC580000 */        sw $t8, ($v0)
  /* 014F78 80014378 8CF90004 */        lw $t9, 4($a3)
  /* 014F7C 8001437C 11800010 */      beqz $t4, .L800143C0
  /* 014F80 80014380 AC590004 */        sw $t9, 4($v0)
  /* 014F84 80014384 8E0E0014 */        lw $t6, 0x14($s0)
  /* 014F88 80014388 24010001 */     addiu $at, $zero, 1
  /* 014F8C 8001438C 51C10005 */      beql $t6, $at, .L800143A4
  /* 014F90 80014390 8CF80000 */        lw $t8, ($a3)
  /* 014F94 80014394 8E0F0008 */        lw $t7, 8($s0)
  /* 014F98 80014398 51E0000A */      beql $t7, $zero, .L800143C4
  /* 014F9C 8001439C 8CE50008 */        lw $a1, 8($a3)
  /* 014FA0 800143A0 8CF80000 */        lw $t8, ($a3)
  .L800143A4:
  /* 014FA4 800143A4 0018C880 */       sll $t9, $t8, 2
  /* 014FA8 800143A8 00793021 */      addu $a2, $v1, $t9
  /* 014FAC 800143AC 8CC20000 */        lw $v0, ($a2)
  /* 014FB0 800143B0 244E0008 */     addiu $t6, $v0, 8
  /* 014FB4 800143B4 ACCE0000 */        sw $t6, ($a2)
  /* 014FB8 800143B8 AC5F0004 */        sw $ra, 4($v0)
  /* 014FBC 800143BC AC4D0000 */        sw $t5, ($v0)
  .L800143C0:
  /* 014FC0 800143C0 8CE50008 */        lw $a1, 8($a3)
  .L800143C4:
  /* 014FC4 800143C4 24E70008 */     addiu $a3, $a3, 8
  /* 014FC8 800143C8 5565FF83 */      bnel $t3, $a1, .L800141D8
  /* 014FCC 800143CC 8CEF0004 */        lw $t7, 4($a3)
  .L800143D0:
  /* 014FD0 800143D0 8FAF0030 */        lw $t7, 0x30($sp)
  /* 014FD4 800143D4 2401FFFF */     addiu $at, $zero, -1
  /* 014FD8 800143D8 11E10003 */       beq $t7, $at, .L800143E8
  /* 014FDC 800143DC 000FC080 */       sll $t8, $t7, 2
  /* 014FE0 800143E0 0078C821 */      addu $t9, $v1, $t8
  /* 014FE4 800143E4 AF290000 */        sw $t1, ($t9)
  .L800143E8:
  /* 014FE8 800143E8 8FBF001C */        lw $ra, 0x1c($sp)
  .L800143EC:
  /* 014FEC 800143EC 8FB00018 */        lw $s0, 0x18($sp)
  /* 014FF0 800143F0 27BD0038 */     addiu $sp, $sp, 0x38
  /* 014FF4 800143F4 03E00008 */        jr $ra
  /* 014FF8 800143F8 00000000 */       nop 

