.section .text
glabel func_800053CC
  /* 005FCC 800053CC 27BDFF78 */     addiu $sp, $sp, -0x88
  /* 005FD0 800053D0 3C038004 */       lui $v1, %hi(D_800465B0)
  /* 005FD4 800053D4 3C028004 */       lui $v0, %hi(D_800465C0)
  /* 005FD8 800053D8 3C048004 */       lui $a0, %hi(D_800465D0)
  /* 005FDC 800053DC AFBF001C */        sw $ra, 0x1c($sp)
  /* 005FE0 800053E0 AFB00018 */        sw $s0, 0x18($sp)
  /* 005FE4 800053E4 00003025 */        or $a2, $zero, $zero
  /* 005FE8 800053E8 248465D0 */     addiu $a0, $a0, %lo(D_800465D0)
  /* 005FEC 800053EC 244265C0 */     addiu $v0, $v0, %lo(D_800465C0)
  /* 005FF0 800053F0 246365B0 */     addiu $v1, $v1, %lo(D_800465B0)
  .L800053F4:
  /* 005FF4 800053F4 8C6E0000 */        lw $t6, ($v1) # D_800465B0 + 0
  /* 005FF8 800053F8 8C4F0000 */        lw $t7, ($v0) # D_800465C0 + 0
  /* 005FFC 800053FC 24420004 */     addiu $v0, $v0, 4
  /* 006000 80005400 00063043 */       sra $a2, $a2, 1
  /* 006004 80005404 11CF0002 */       beq $t6, $t7, .L80005410
  /* 006008 80005408 00000000 */       nop 
  /* 00600C 8000540C 34C60008 */       ori $a2, $a2, 8
  .L80005410:
  /* 006010 80005410 1444FFF8 */       bne $v0, $a0, .L800053F4
  /* 006014 80005414 24630004 */     addiu $v1, $v1, 4
  /* 006018 80005418 10C000E4 */      beqz $a2, .L800057AC
  /* 00601C 8000541C 30D80001 */      andi $t8, $a2, 1
  /* 006020 80005420 13000051 */      beqz $t8, .L80005568
  /* 006024 80005424 AFB8002C */        sw $t8, 0x2c($sp)
  /* 006028 80005428 30CB0004 */      andi $t3, $a2, 4
  /* 00602C 8000542C 51600014 */      beql $t3, $zero, .L80005480
  /* 006030 80005430 30CF0002 */      andi $t7, $a2, 2
  /* 006034 80005434 0C001479 */       jal func_800051E4
  /* 006038 80005438 AFA60080 */        sw $a2, 0x80($sp)
  /* 00603C 8000543C 3C108004 */       lui $s0, %hi(D_800465B0)
  /* 006040 80005440 261065B0 */     addiu $s0, $s0, %lo(D_800465B0)
  /* 006044 80005444 02002025 */        or $a0, $s0, $zero
  /* 006048 80005448 0C0014D1 */       jal func_80005344
  /* 00604C 8000544C 00402825 */        or $a1, $v0, $zero
  /* 006050 80005450 8E020000 */        lw $v0, ($s0) # D_800465B0 + 0
  /* 006054 80005454 8FA60080 */        lw $a2, 0x80($sp)
  /* 006058 80005458 3C0A8004 */       lui $t2, %hi(D_800465C0)
  /* 00605C 8000545C 244C0008 */     addiu $t4, $v0, 8
  /* 006060 80005460 AE0C0000 */        sw $t4, ($s0) # D_800465B0 + 0
  /* 006064 80005464 3C0DDE01 */       lui $t5, 0xde01
  /* 006068 80005468 254A65C0 */     addiu $t2, $t2, %lo(D_800465C0)
  /* 00606C 8000546C AC4D0000 */        sw $t5, ($v0)
  /* 006070 80005470 8D4E0008 */        lw $t6, 8($t2) # D_800465C0 + 8
  /* 006074 80005474 1000003C */         b .L80005568
  /* 006078 80005478 AC4E0004 */        sw $t6, 4($v0)
  /* 00607C 8000547C 30CF0002 */      andi $t7, $a2, 2
  .L80005480:
  /* 006080 80005480 11E00016 */      beqz $t7, .L800054DC
  /* 006084 80005484 3C188004 */       lui $t8, %hi(D_80046628)
  /* 006088 80005488 97186628 */       lhu $t8, %lo(D_80046628)($t8)
  /* 00608C 8000548C 3C108004 */       lui $s0, 0x8004
  /* 006090 80005490 260465B0 */     addiu $a0, $s0, 0x65b0
  /* 006094 80005494 13000005 */      beqz $t8, .L800054AC
  /* 006098 80005498 3C058004 */       lui $a1, %hi(D_80046624)
  /* 00609C 8000549C 94A56624 */       lhu $a1, %lo(D_80046624)($a1)
  /* 0060A0 800054A0 0C0014D1 */       jal func_80005344
  /* 0060A4 800054A4 AFA60080 */        sw $a2, 0x80($sp)
  /* 0060A8 800054A8 8FA60080 */        lw $a2, 0x80($sp)
  .L800054AC:
  /* 0060AC 800054AC 3C108004 */       lui $s0, %hi(D_800465B0)
  /* 0060B0 800054B0 261065B0 */     addiu $s0, $s0, %lo(D_800465B0)
  /* 0060B4 800054B4 8E020000 */        lw $v0, ($s0) # D_800465B0 + 0
  /* 0060B8 800054B8 3C0A8004 */       lui $t2, %hi(D_800465C0)
  /* 0060BC 800054BC 3C0BDE01 */       lui $t3, 0xde01
  /* 0060C0 800054C0 24590008 */     addiu $t9, $v0, 8
  /* 0060C4 800054C4 AE190000 */        sw $t9, ($s0) # D_800465B0 + 0
  /* 0060C8 800054C8 254A65C0 */     addiu $t2, $t2, %lo(D_800465C0)
  /* 0060CC 800054CC AC4B0000 */        sw $t3, ($v0)
  /* 0060D0 800054D0 8D4C0004 */        lw $t4, 4($t2) # D_800465C0 + 4
  /* 0060D4 800054D4 10000024 */         b .L80005568
  /* 0060D8 800054D8 AC4C0004 */        sw $t4, 4($v0)
  .L800054DC:
  /* 0060DC 800054DC 30CD0008 */      andi $t5, $a2, 8
  /* 0060E0 800054E0 11A00013 */      beqz $t5, .L80005530
  /* 0060E4 800054E4 00000000 */       nop 
  /* 0060E8 800054E8 0C001479 */       jal func_800051E4
  /* 0060EC 800054EC AFA60080 */        sw $a2, 0x80($sp)
  /* 0060F0 800054F0 3C108004 */       lui $s0, %hi(D_800465B0)
  /* 0060F4 800054F4 261065B0 */     addiu $s0, $s0, %lo(D_800465B0)
  /* 0060F8 800054F8 02002025 */        or $a0, $s0, $zero
  /* 0060FC 800054FC 0C0014D1 */       jal func_80005344
  /* 006100 80005500 00402825 */        or $a1, $v0, $zero
  /* 006104 80005504 8E020000 */        lw $v0, ($s0) # D_800465B0 + 0
  /* 006108 80005508 8FA60080 */        lw $a2, 0x80($sp)
  /* 00610C 8000550C 3C0A8004 */       lui $t2, %hi(D_800465C0)
  /* 006110 80005510 244E0008 */     addiu $t6, $v0, 8
  /* 006114 80005514 AE0E0000 */        sw $t6, ($s0) # D_800465B0 + 0
  /* 006118 80005518 3C0FDE01 */       lui $t7, 0xde01
  /* 00611C 8000551C 254A65C0 */     addiu $t2, $t2, %lo(D_800465C0)
  /* 006120 80005520 AC4F0000 */        sw $t7, ($v0)
  /* 006124 80005524 8D58000C */        lw $t8, 0xc($t2) # D_800465C0 + 12
  /* 006128 80005528 1000000F */         b .L80005568
  /* 00612C 8000552C AC580004 */        sw $t8, 4($v0)
  .L80005530:
  /* 006130 80005530 3C108004 */       lui $s0, %hi(D_800465B0)
  /* 006134 80005534 261065B0 */     addiu $s0, $s0, %lo(D_800465B0)
  /* 006138 80005538 8E020000 */        lw $v0, ($s0) # D_800465B0 + 0
  /* 00613C 8000553C 3C0BE900 */       lui $t3, 0xe900
  /* 006140 80005540 3C0DDF00 */       lui $t5, 0xdf00
  /* 006144 80005544 24590008 */     addiu $t9, $v0, 8
  /* 006148 80005548 AE190000 */        sw $t9, ($s0) # D_800465B0 + 0
  /* 00614C 8000554C AC400004 */        sw $zero, 4($v0)
  /* 006150 80005550 AC4B0000 */        sw $t3, ($v0)
  /* 006154 80005554 8E020000 */        lw $v0, ($s0) # D_800465B0 + 0
  /* 006158 80005558 244C0008 */     addiu $t4, $v0, 8
  /* 00615C 8000555C AE0C0000 */        sw $t4, ($s0) # D_800465B0 + 0
  /* 006160 80005560 AC400004 */        sw $zero, 4($v0)
  /* 006164 80005564 AC4D0000 */        sw $t5, ($v0)
  .L80005568:
  /* 006168 80005568 3C0A8004 */       lui $t2, %hi(D_800465C0)
  /* 00616C 8000556C 3C108004 */       lui $s0, %hi(D_800465B0)
  /* 006170 80005570 30CE0004 */      andi $t6, $a2, 4
  /* 006174 80005574 261065B0 */     addiu $s0, $s0, %lo(D_800465B0)
  /* 006178 80005578 254A65C0 */     addiu $t2, $t2, %lo(D_800465C0)
  /* 00617C 8000557C AFAE0028 */        sw $t6, 0x28($sp)
  /* 006180 80005580 30C80002 */      andi $t0, $a2, 2
  /* 006184 80005584 11C0002B */      beqz $t6, .L80005634
  /* 006188 80005588 30C70008 */      andi $a3, $a2, 8
  /* 00618C 8000558C 11000013 */      beqz $t0, .L800055DC
  /* 006190 80005590 3C048004 */       lui $a0, %hi(D_800465B0 + 8)
  /* 006194 80005594 3C058004 */       lui $a1, %hi(D_80046624)
  /* 006198 80005598 94A56624 */       lhu $a1, %lo(D_80046624)($a1)
  /* 00619C 8000559C 248465B8 */     addiu $a0, $a0, %lo(D_800465B0 + 8)
  /* 0061A0 800055A0 AFA70020 */        sw $a3, 0x20($sp)
  /* 0061A4 800055A4 0C0014D1 */       jal func_80005344
  /* 0061A8 800055A8 AFA80024 */        sw $t0, 0x24($sp)
  /* 0061AC 800055AC 8E020008 */        lw $v0, 8($s0) # D_800465B0 + 8
  /* 0061B0 800055B0 8FA70020 */        lw $a3, 0x20($sp)
  /* 0061B4 800055B4 8FA80024 */        lw $t0, 0x24($sp)
  /* 0061B8 800055B8 24580008 */     addiu $t8, $v0, 8
  /* 0061BC 800055BC 3C0A8004 */       lui $t2, %hi(D_800465C0)
  /* 0061C0 800055C0 AE180008 */        sw $t8, 8($s0) # D_800465B0 + 8
  /* 0061C4 800055C4 3C19DE01 */       lui $t9, 0xde01
  /* 0061C8 800055C8 254A65C0 */     addiu $t2, $t2, %lo(D_800465C0)
  /* 0061CC 800055CC AC590000 */        sw $t9, ($v0)
  /* 0061D0 800055D0 8D4B0004 */        lw $t3, 4($t2) # D_800465C0 + 4
  /* 0061D4 800055D4 10000017 */         b .L80005634
  /* 0061D8 800055D8 AC4B0004 */        sw $t3, 4($v0)
  .L800055DC:
  /* 0061DC 800055DC 50E0000A */      beql $a3, $zero, .L80005608
  /* 0061E0 800055E0 8E020008 */        lw $v0, 8($s0) # D_800465B0 + 8
  /* 0061E4 800055E4 8E020008 */        lw $v0, 8($s0) # D_800465B0 + 8
  /* 0061E8 800055E8 3C0DDE01 */       lui $t5, 0xde01
  /* 0061EC 800055EC 244C0008 */     addiu $t4, $v0, 8
  /* 0061F0 800055F0 AE0C0008 */        sw $t4, 8($s0) # D_800465B0 + 8
  /* 0061F4 800055F4 AC4D0000 */        sw $t5, ($v0)
  /* 0061F8 800055F8 8D4E000C */        lw $t6, 0xc($t2) # D_800465C0 + 12
  /* 0061FC 800055FC 1000000D */         b .L80005634
  /* 006200 80005600 AC4E0004 */        sw $t6, 4($v0)
  /* 006204 80005604 8E020008 */        lw $v0, 8($s0) # D_800465B0 + 8
  .L80005608:
  /* 006208 80005608 3C18E900 */       lui $t8, 0xe900
  /* 00620C 8000560C 3C0BDF00 */       lui $t3, 0xdf00
  /* 006210 80005610 244F0008 */     addiu $t7, $v0, 8
  /* 006214 80005614 AE0F0008 */        sw $t7, 8($s0) # D_800465B0 + 8
  /* 006218 80005618 AC400004 */        sw $zero, 4($v0)
  /* 00621C 8000561C AC580000 */        sw $t8, ($v0)
  /* 006220 80005620 8E020008 */        lw $v0, 8($s0) # D_800465B0 + 8
  /* 006224 80005624 24590008 */     addiu $t9, $v0, 8
  /* 006228 80005628 AE190008 */        sw $t9, 8($s0) # D_800465B0 + 8
  /* 00622C 8000562C AC400004 */        sw $zero, 4($v0)
  /* 006230 80005630 AC4B0000 */        sw $t3, ($v0)
  .L80005634:
  /* 006234 80005634 11000021 */      beqz $t0, .L800056BC
  /* 006238 80005638 00000000 */       nop 
  /* 00623C 8000563C 50E00014 */      beql $a3, $zero, .L80005690
  /* 006240 80005640 8E020004 */        lw $v0, 4($s0) # D_800465B0 + 4
  /* 006244 80005644 AFA70020 */        sw $a3, 0x20($sp)
  /* 006248 80005648 0C001479 */       jal func_800051E4
  /* 00624C 8000564C AFA80024 */        sw $t0, 0x24($sp)
  /* 006250 80005650 02002025 */        or $a0, $s0, $zero
  /* 006254 80005654 0C0014D1 */       jal func_80005344
  /* 006258 80005658 00402825 */        or $a1, $v0, $zero
  /* 00625C 8000565C 8E020004 */        lw $v0, 4($s0) # D_800465B0 + 4
  /* 006260 80005660 8FA70020 */        lw $a3, 0x20($sp)
  /* 006264 80005664 8FA80024 */        lw $t0, 0x24($sp)
  /* 006268 80005668 244C0008 */     addiu $t4, $v0, 8
  /* 00626C 8000566C 3C0A8004 */       lui $t2, %hi(D_800465C0)
  /* 006270 80005670 AE0C0004 */        sw $t4, 4($s0) # D_800465B0 + 4
  /* 006274 80005674 3C0DDE01 */       lui $t5, 0xde01
  /* 006278 80005678 254A65C0 */     addiu $t2, $t2, %lo(D_800465C0)
  /* 00627C 8000567C AC4D0000 */        sw $t5, ($v0)
  /* 006280 80005680 8D4E000C */        lw $t6, 0xc($t2) # D_800465C0 + 12
  /* 006284 80005684 1000000D */         b .L800056BC
  /* 006288 80005688 AC4E0004 */        sw $t6, 4($v0)
  /* 00628C 8000568C 8E020004 */        lw $v0, 4($s0) # D_800465B0 + 4
  .L80005690:
  /* 006290 80005690 3C18E900 */       lui $t8, 0xe900
  /* 006294 80005694 3C0BDF00 */       lui $t3, 0xdf00
  /* 006298 80005698 244F0008 */     addiu $t7, $v0, 8
  /* 00629C 8000569C AE0F0004 */        sw $t7, 4($s0) # D_800465B0 + 4
  /* 0062A0 800056A0 AC400004 */        sw $zero, 4($v0)
  /* 0062A4 800056A4 AC580000 */        sw $t8, ($v0)
  /* 0062A8 800056A8 8E020004 */        lw $v0, 4($s0) # D_800465B0 + 4
  /* 0062AC 800056AC 24590008 */     addiu $t9, $v0, 8
  /* 0062B0 800056B0 AE190004 */        sw $t9, 4($s0) # D_800465B0 + 4
  /* 0062B4 800056B4 AC400004 */        sw $zero, 4($v0)
  /* 0062B8 800056B8 AC4B0000 */        sw $t3, ($v0)
  .L800056BC:
  /* 0062BC 800056BC 50E0000E */      beql $a3, $zero, .L800056F8
  /* 0062C0 800056C0 8FB8002C */        lw $t8, 0x2c($sp)
  /* 0062C4 800056C4 8E02000C */        lw $v0, 0xc($s0) # D_800465B0 + 12
  /* 0062C8 800056C8 3C0DE900 */       lui $t5, 0xe900
  /* 0062CC 800056CC 3C0FDF00 */       lui $t7, 0xdf00
  /* 0062D0 800056D0 244C0008 */     addiu $t4, $v0, 8
  /* 0062D4 800056D4 AE0C000C */        sw $t4, 0xc($s0) # D_800465B0 + 12
  /* 0062D8 800056D8 AC400004 */        sw $zero, 4($v0)
  /* 0062DC 800056DC AC4D0000 */        sw $t5, ($v0)
  /* 0062E0 800056E0 8E02000C */        lw $v0, 0xc($s0) # D_800465B0 + 12
  /* 0062E4 800056E4 244E0008 */     addiu $t6, $v0, 8
  /* 0062E8 800056E8 AE0E000C */        sw $t6, 0xc($s0) # D_800465B0 + 12
  /* 0062EC 800056EC AC400004 */        sw $zero, 4($v0)
  /* 0062F0 800056F0 AC4F0000 */        sw $t7, ($v0)
  /* 0062F4 800056F4 8FB8002C */        lw $t8, 0x2c($sp)
  .L800056F8:
  /* 0062F8 800056F8 13000003 */      beqz $t8, .L80005708
  /* 0062FC 800056FC 00004825 */        or $t1, $zero, $zero
  /* 006300 80005700 1000000D */         b .L80005738
  /* 006304 80005704 00002025 */        or $a0, $zero, $zero
  .L80005708:
  /* 006308 80005708 8FB90028 */        lw $t9, 0x28($sp)
  /* 00630C 8000570C 24090002 */     addiu $t1, $zero, 2
  /* 006310 80005710 13200003 */      beqz $t9, .L80005720
  /* 006314 80005714 00000000 */       nop 
  /* 006318 80005718 10000007 */         b .L80005738
  /* 00631C 8000571C 24040001 */     addiu $a0, $zero, 1
  .L80005720:
  /* 006320 80005720 11000004 */      beqz $t0, .L80005734
  /* 006324 80005724 24090003 */     addiu $t1, $zero, 3
  /* 006328 80005728 24090001 */     addiu $t1, $zero, 1
  /* 00632C 8000572C 10000002 */         b .L80005738
  /* 006330 80005730 00002025 */        or $a0, $zero, $zero
  .L80005734:
  /* 006334 80005734 24040001 */     addiu $a0, $zero, 1
  .L80005738:
  /* 006338 80005738 00093080 */       sll $a2, $t1, 2
  /* 00633C 8000573C 02061821 */      addu $v1, $s0, $a2
  /* 006340 80005740 8C650000 */        lw $a1, ($v1)
  /* 006344 80005744 3C0CDE00 */       lui $t4, 0xde00
  /* 006348 80005748 3C0D8004 */       lui $t5, %hi(D_8004662C)
  /* 00634C 8000574C 24AB0008 */     addiu $t3, $a1, 8
  /* 006350 80005750 AC6B0000 */        sw $t3, ($v1)
  /* 006354 80005754 ACAC0000 */        sw $t4, ($a1)
  /* 006358 80005758 8DAD662C */        lw $t5, %lo(D_8004662C)($t5)
  /* 00635C 8000575C 3C0FDE01 */       lui $t7, 0xde01
  /* 006360 80005760 0146C021 */      addu $t8, $t2, $a2
  /* 006364 80005764 ACAD0004 */        sw $t5, 4($a1)
  /* 006368 80005768 8C620000 */        lw $v0, ($v1)
  /* 00636C 8000576C 244E0008 */     addiu $t6, $v0, 8
  /* 006370 80005770 AC6E0000 */        sw $t6, ($v1)
  /* 006374 80005774 AC4F0000 */        sw $t7, ($v0)
  /* 006378 80005778 8F190000 */        lw $t9, ($t8)
  /* 00637C 8000577C 0C001490 */       jal func_80005240
  /* 006380 80005780 AC590004 */        sw $t9, 4($v0)
  /* 006384 80005784 3C0A8004 */       lui $t2, %hi(D_800465C0)
  /* 006388 80005788 254A65C0 */     addiu $t2, $t2, %lo(D_800465C0)
  /* 00638C 8000578C 8E0B0000 */        lw $t3, ($s0) # D_800465B0 + 0
  /* 006390 80005790 8E0C0008 */        lw $t4, 8($s0) # D_800465B0 + 8
  /* 006394 80005794 8E0D0004 */        lw $t5, 4($s0) # D_800465B0 + 4
  /* 006398 80005798 8E0E000C */        lw $t6, 0xc($s0) # D_800465B0 + 12
  /* 00639C 8000579C AD4B0000 */        sw $t3, ($t2) # D_800465C0 + 0
  /* 0063A0 800057A0 AD4C0008 */        sw $t4, 8($t2) # D_800465C0 + 8
  /* 0063A4 800057A4 AD4D0004 */        sw $t5, 4($t2) # D_800465C0 + 4
  /* 0063A8 800057A8 AD4E000C */        sw $t6, 0xc($t2) # D_800465C0 + 12
  .L800057AC:
  /* 0063AC 800057AC 0C0012E7 */       jal check_buffer_lengths
  /* 0063B0 800057B0 00000000 */       nop 
  /* 0063B4 800057B4 8FBF001C */        lw $ra, 0x1c($sp)
  /* 0063B8 800057B8 8FB00018 */        lw $s0, 0x18($sp)
  /* 0063BC 800057BC 27BD0088 */     addiu $sp, $sp, 0x88
  /* 0063C0 800057C0 03E00008 */        jr $ra
  /* 0063C4 800057C4 00000000 */       nop 

