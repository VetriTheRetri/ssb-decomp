.section .text
glabel unref_800036B4
  /* 0042B4 800036B4 27BDFBD0 */     addiu $sp, $sp, -0x430
  /* 0042B8 800036B8 AFB30014 */        sw $s3, 0x14($sp)
  /* 0042BC 800036BC AFB20010 */        sw $s2, 0x10($sp)
  /* 0042C0 800036C0 AFB1000C */        sw $s1, 0xc($sp)
  /* 0042C4 800036C4 AFB00008 */        sw $s0, 8($sp)
  /* 0042C8 800036C8 94830000 */       lhu $v1, ($a0)
  /* 0042CC 800036CC 948E0002 */       lhu $t6, 2($a0)
  /* 0042D0 800036D0 948F0004 */       lhu $t7, 4($a0)
  /* 0042D4 800036D4 00031C00 */       sll $v1, $v1, 0x10
  /* 0042D8 800036D8 006E1825 */        or $v1, $v1, $t6
  /* 0042DC 800036DC 94980006 */       lhu $t8, 6($a0)
  /* 0042E0 800036E0 00031C00 */       sll $v1, $v1, 0x10
  /* 0042E4 800036E4 006F1825 */        or $v1, $v1, $t7
  /* 0042E8 800036E8 00031C00 */       sll $v1, $v1, 0x10
  /* 0042EC 800036EC 00804825 */        or $t1, $a0, $zero
  /* 0042F0 800036F0 95390008 */       lhu $t9, 8($t1)
  /* 0042F4 800036F4 00781825 */        or $v1, $v1, $t8
  /* 0042F8 800036F8 00656821 */      addu $t5, $v1, $a1
  /* 0042FC 800036FC 00001025 */        or $v0, $zero, $zero
  /* 004300 80003700 24420008 */     addiu $v0, $v0, 8
  /* 004304 80003704 00031C00 */       sll $v1, $v1, 0x10
  /* 004308 80003708 240B0018 */     addiu $t3, $zero, 0x18
  /* 00430C 8000370C 01627023 */      subu $t6, $t3, $v0
  /* 004310 80003710 00791825 */        or $v1, $v1, $t9
  /* 004314 80003714 01C37804 */      sllv $t7, $v1, $t6
  /* 004318 80003718 000FC602 */       srl $t8, $t7, 0x18
  /* 00431C 8000371C 2524000A */     addiu $a0, $t1, 0xa
  /* 004320 80003720 27A60124 */     addiu $a2, $sp, 0x124
  /* 004324 80003724 00A04025 */        or $t0, $a1, $zero
  /* 004328 80003728 AFB8010C */        sw $t8, 0x10c($sp)
  /* 00432C 8000372C 00004825 */        or $t1, $zero, $zero
  /* 004330 80003730 AFA000BC */        sw $zero, 0xbc($sp)
  /* 004334 80003734 2407001F */     addiu $a3, $zero, 0x1f
  .L80003738:
  /* 004338 80003738 1C400006 */      bgtz $v0, .L80003754
  /* 00433C 8000373C 29210002 */      slti $at, $t1, 2
  /* 004340 80003740 94990000 */       lhu $t9, ($a0)
  /* 004344 80003744 00031C00 */       sll $v1, $v1, 0x10
  /* 004348 80003748 24840002 */     addiu $a0, $a0, 2
  /* 00434C 8000374C 24420010 */     addiu $v0, $v0, 0x10
  /* 004350 80003750 00791825 */        or $v1, $v1, $t9
  .L80003754:
  /* 004354 80003754 2442FFFF */     addiu $v0, $v0, -1
  /* 004358 80003758 00E27023 */      subu $t6, $a3, $v0
  /* 00435C 8000375C 01C35004 */      sllv $t2, $v1, $t6
  /* 004360 80003760 000A57C2 */       srl $t2, $t2, 0x1f
  /* 004364 80003764 11400002 */      beqz $t2, .L80003770
  /* 004368 80003768 00097880 */       sll $t7, $t1, 2
  /* 00436C 8000376C 14200023 */      bnez $at, .L800037FC
  .L80003770:
  /* 004370 80003770 27B800BC */     addiu $t8, $sp, 0xbc
  /* 004374 80003774 1140000D */      beqz $t2, .L800037AC
  /* 004378 80003778 01F86021 */      addu $t4, $t7, $t8
  /* 00437C 8000377C ACC00000 */        sw $zero, ($a2)
  /* 004380 80003780 ACC00004 */        sw $zero, 4($a2)
  /* 004384 80003784 ACC00008 */        sw $zero, 8($a2)
  /* 004388 80003788 8D99FFF8 */        lw $t9, -8($t4)
  /* 00438C 8000378C 00C05025 */        or $t2, $a2, $zero
  /* 004390 80003790 24C6000C */     addiu $a2, $a2, 0xc
  /* 004394 80003794 AD590000 */        sw $t9, ($t2)
  /* 004398 80003798 8D8EFFFC */        lw $t6, -4($t4)
  /* 00439C 8000379C 2529FFFF */     addiu $t1, $t1, -1
  /* 0043A0 800037A0 AD4E0004 */        sw $t6, 4($t2)
  /* 0043A4 800037A4 1000FFE4 */         b .L80003738
  /* 0043A8 800037A8 AD8AFFF8 */        sw $t2, -8($t4)
  .L800037AC:
  /* 0043AC 800037AC 00C05025 */        or $t2, $a2, $zero
  /* 0043B0 800037B0 28410008 */      slti $at, $v0, 8
  /* 0043B4 800037B4 24C6000C */     addiu $a2, $a2, 0xc
  /* 0043B8 800037B8 ACC0FFF4 */        sw $zero, -0xc($a2)
  /* 0043BC 800037BC ACC0FFF8 */        sw $zero, -8($a2)
  /* 0043C0 800037C0 10200006 */      beqz $at, .L800037DC
  /* 0043C4 800037C4 ACC0FFFC */        sw $zero, -4($a2)
  /* 0043C8 800037C8 948F0000 */       lhu $t7, ($a0)
  /* 0043CC 800037CC 00031C00 */       sll $v1, $v1, 0x10
  /* 0043D0 800037D0 24840002 */     addiu $a0, $a0, 2
  /* 0043D4 800037D4 24420010 */     addiu $v0, $v0, 0x10
  /* 0043D8 800037D8 006F1825 */        or $v1, $v1, $t7
  .L800037DC:
  /* 0043DC 800037DC 2442FFF8 */     addiu $v0, $v0, -8
  /* 0043E0 800037E0 0162C023 */      subu $t8, $t3, $v0
  /* 0043E4 800037E4 0303C804 */      sllv $t9, $v1, $t8
  /* 0043E8 800037E8 00197602 */       srl $t6, $t9, 0x18
  /* 0043EC 800037EC AD4E0008 */        sw $t6, 8($t2)
  /* 0043F0 800037F0 AD8A0000 */        sw $t2, ($t4)
  /* 0043F4 800037F4 1000FFD0 */         b .L80003738
  /* 0043F8 800037F8 25290001 */     addiu $t1, $t1, 1
  .L800037FC:
  /* 0043FC 800037FC 8FA900BC */        lw $t1, 0xbc($sp)
  /* 004400 80003800 00006025 */        or $t4, $zero, $zero
  /* 004404 80003804 AFA0005C */        sw $zero, 0x5c($sp)
  .L80003808:
  /* 004408 80003808 1C400006 */      bgtz $v0, .L80003824
  /* 00440C 8000380C 29810002 */      slti $at, $t4, 2
  /* 004410 80003810 948F0000 */       lhu $t7, ($a0)
  /* 004414 80003814 00031C00 */       sll $v1, $v1, 0x10
  /* 004418 80003818 24840002 */     addiu $a0, $a0, 2
  /* 00441C 8000381C 24420010 */     addiu $v0, $v0, 0x10
  /* 004420 80003820 006F1825 */        or $v1, $v1, $t7
  .L80003824:
  /* 004424 80003824 2442FFFF */     addiu $v0, $v0, -1
  /* 004428 80003828 00E2C023 */      subu $t8, $a3, $v0
  /* 00442C 8000382C 03035004 */      sllv $t2, $v1, $t8
  /* 004430 80003830 000A57C2 */       srl $t2, $t2, 0x1f
  /* 004434 80003834 11400002 */      beqz $t2, .L80003840
  /* 004438 80003838 000CC880 */       sll $t9, $t4, 2
  /* 00443C 8000383C 14200023 */      bnez $at, .L800038CC
  .L80003840:
  /* 004440 80003840 27AE005C */     addiu $t6, $sp, 0x5c
  /* 004444 80003844 1140000D */      beqz $t2, .L8000387C
  /* 004448 80003848 032E8021 */      addu $s0, $t9, $t6
  /* 00444C 8000384C ACC00000 */        sw $zero, ($a2)
  /* 004450 80003850 ACC00004 */        sw $zero, 4($a2)
  /* 004454 80003854 ACC00008 */        sw $zero, 8($a2)
  /* 004458 80003858 8E0FFFF8 */        lw $t7, -8($s0)
  /* 00445C 8000385C 00C05025 */        or $t2, $a2, $zero
  /* 004460 80003860 24C6000C */     addiu $a2, $a2, 0xc
  /* 004464 80003864 AD4F0000 */        sw $t7, ($t2)
  /* 004468 80003868 8E18FFFC */        lw $t8, -4($s0)
  /* 00446C 8000386C 258CFFFF */     addiu $t4, $t4, -1
  /* 004470 80003870 AD580004 */        sw $t8, 4($t2)
  /* 004474 80003874 1000FFE4 */         b .L80003808
  /* 004478 80003878 AE0AFFF8 */        sw $t2, -8($s0)
  .L8000387C:
  /* 00447C 8000387C 00C05025 */        or $t2, $a2, $zero
  /* 004480 80003880 28410008 */      slti $at, $v0, 8
  /* 004484 80003884 24C6000C */     addiu $a2, $a2, 0xc
  /* 004488 80003888 ACC0FFF4 */        sw $zero, -0xc($a2)
  /* 00448C 8000388C ACC0FFF8 */        sw $zero, -8($a2)
  /* 004490 80003890 10200006 */      beqz $at, .L800038AC
  /* 004494 80003894 ACC0FFFC */        sw $zero, -4($a2)
  /* 004498 80003898 94990000 */       lhu $t9, ($a0)
  /* 00449C 8000389C 00031C00 */       sll $v1, $v1, 0x10
  /* 0044A0 800038A0 24840002 */     addiu $a0, $a0, 2
  /* 0044A4 800038A4 24420010 */     addiu $v0, $v0, 0x10
  /* 0044A8 800038A8 00791825 */        or $v1, $v1, $t9
  .L800038AC:
  /* 0044AC 800038AC 2442FFF8 */     addiu $v0, $v0, -8
  /* 0044B0 800038B0 01627023 */      subu $t6, $t3, $v0
  /* 0044B4 800038B4 01C37804 */      sllv $t7, $v1, $t6
  /* 0044B8 800038B8 000FC602 */       srl $t8, $t7, 0x18
  /* 0044BC 800038BC AD580008 */        sw $t8, 8($t2)
  /* 0044C0 800038C0 AE0A0000 */        sw $t2, ($s0)
  /* 0044C4 800038C4 1000FFD0 */         b .L80003808
  /* 0044C8 800038C8 258C0001 */     addiu $t4, $t4, 1
  .L800038CC:
  /* 0044CC 800038CC 00AD082B */      sltu $at, $a1, $t5
  /* 0044D0 800038D0 102000C5 */      beqz $at, .L80003BE8
  /* 0044D4 800038D4 8FAC005C */        lw $t4, 0x5c($sp)
  /* 0044D8 800038D8 24060020 */     addiu $a2, $zero, 0x20
  .L800038DC:
  /* 0044DC 800038DC 5C400007 */     bgtzl $v0, .L800038FC
  /* 0044E0 800038E0 2442FFFF */     addiu $v0, $v0, -1
  /* 0044E4 800038E4 94990000 */       lhu $t9, ($a0)
  /* 0044E8 800038E8 00031C00 */       sll $v1, $v1, 0x10
  /* 0044EC 800038EC 24840002 */     addiu $a0, $a0, 2
  /* 0044F0 800038F0 24420010 */     addiu $v0, $v0, 0x10
  /* 0044F4 800038F4 00791825 */        or $v1, $v1, $t9
  /* 0044F8 800038F8 2442FFFF */     addiu $v0, $v0, -1
  .L800038FC:
  /* 0044FC 800038FC 00E27023 */      subu $t6, $a3, $v0
  /* 004500 80003900 01C37804 */      sllv $t7, $v1, $t6
  /* 004504 80003904 000FC7C2 */       srl $t8, $t7, 0x1f
  /* 004508 80003908 17000010 */      bnez $t8, .L8000394C
  /* 00450C 8000390C 8FB9010C */        lw $t9, 0x10c($sp)
  /* 004510 80003910 28410008 */      slti $at, $v0, 8
  /* 004514 80003914 50200007 */      beql $at, $zero, .L80003934
  /* 004518 80003918 2442FFF8 */     addiu $v0, $v0, -8
  /* 00451C 8000391C 94990000 */       lhu $t9, ($a0)
  /* 004520 80003920 00031C00 */       sll $v1, $v1, 0x10
  /* 004524 80003924 24840002 */     addiu $a0, $a0, 2
  /* 004528 80003928 24420010 */     addiu $v0, $v0, 0x10
  /* 00452C 8000392C 00791825 */        or $v1, $v1, $t9
  /* 004530 80003930 2442FFF8 */     addiu $v0, $v0, -8
  .L80003934:
  /* 004534 80003934 01627023 */      subu $t6, $t3, $v0
  /* 004538 80003938 01C37804 */      sllv $t7, $v1, $t6
  /* 00453C 8000393C 000FC602 */       srl $t8, $t7, 0x18
  /* 004540 80003940 A1180000 */        sb $t8, ($t0)
  /* 004544 80003944 100000A5 */         b .L80003BDC
  /* 004548 80003948 25080001 */     addiu $t0, $t0, 1
  .L8000394C:
  /* 00454C 8000394C 8D320000 */        lw $s2, ($t1)
  /* 004550 80003950 01802825 */        or $a1, $t4, $zero
  /* 004554 80003954 13200050 */      beqz $t9, .L80003A98
  /* 004558 80003958 8D8A0000 */        lw $t2, ($t4)
  /* 00455C 8000395C 00008025 */        or $s0, $zero, $zero
  /* 004560 80003960 12400014 */      beqz $s2, .L800039B4
  /* 004564 80003964 01208825 */        or $s1, $t1, $zero
  .L80003968:
  /* 004568 80003968 5C400007 */     bgtzl $v0, .L80003988
  /* 00456C 8000396C 2442FFFF */     addiu $v0, $v0, -1
  /* 004570 80003970 948E0000 */       lhu $t6, ($a0)
  /* 004574 80003974 00031C00 */       sll $v1, $v1, 0x10
  /* 004578 80003978 24840002 */     addiu $a0, $a0, 2
  /* 00457C 8000397C 24420010 */     addiu $v0, $v0, 0x10
  /* 004580 80003980 006E1825 */        or $v1, $v1, $t6
  /* 004584 80003984 2442FFFF */     addiu $v0, $v0, -1
  .L80003988:
  /* 004588 80003988 00E27823 */      subu $t7, $a3, $v0
  /* 00458C 8000398C 01E3C004 */      sllv $t8, $v1, $t7
  /* 004590 80003990 0018CFC2 */       srl $t9, $t8, 0x1f
  /* 004594 80003994 57200004 */      bnel $t9, $zero, .L800039A8
  /* 004598 80003998 8E310004 */        lw $s1, 4($s1)
  /* 00459C 8000399C 10000002 */         b .L800039A8
  /* 0045A0 800039A0 8E310000 */        lw $s1, ($s1)
  /* 0045A4 800039A4 8E310004 */        lw $s1, 4($s1)
  .L800039A8:
  /* 0045A8 800039A8 8E2E0000 */        lw $t6, ($s1)
  /* 0045AC 800039AC 15C0FFEE */      bnez $t6, .L80003968
  /* 0045B0 800039B0 00000000 */       nop 
  .L800039B4:
  /* 0045B4 800039B4 8E330008 */        lw $s3, 8($s1)
  /* 0045B8 800039B8 0053082A */       slt $at, $v0, $s3
  /* 0045BC 800039BC 10200006 */      beqz $at, .L800039D8
  /* 0045C0 800039C0 00D3C023 */      subu $t8, $a2, $s3
  /* 0045C4 800039C4 948F0000 */       lhu $t7, ($a0)
  /* 0045C8 800039C8 00031C00 */       sll $v1, $v1, 0x10
  /* 0045CC 800039CC 24840002 */     addiu $a0, $a0, 2
  /* 0045D0 800039D0 24420010 */     addiu $v0, $v0, 0x10
  /* 0045D4 800039D4 006F1825 */        or $v1, $v1, $t7
  .L800039D8:
  /* 0045D8 800039D8 00531023 */      subu $v0, $v0, $s3
  /* 0045DC 800039DC 0302C823 */      subu $t9, $t8, $v0
  /* 0045E0 800039E0 03237004 */      sllv $t6, $v1, $t9
  /* 0045E4 800039E4 00D37823 */      subu $t7, $a2, $s3
  /* 0045E8 800039E8 01EE8806 */      srlv $s1, $t6, $t7
  /* 0045EC 800039EC 2A210003 */      slti $at, $s1, 3
  /* 0045F0 800039F0 10200024 */      beqz $at, .L80003A84
  /* 0045F4 800039F4 01209825 */        or $s3, $t1, $zero
  /* 0045F8 800039F8 12400014 */      beqz $s2, .L80003A4C
  /* 0045FC 800039FC 26300001 */     addiu $s0, $s1, 1
  .L80003A00:
  /* 004600 80003A00 5C400007 */     bgtzl $v0, .L80003A20
  /* 004604 80003A04 2442FFFF */     addiu $v0, $v0, -1
  /* 004608 80003A08 94980000 */       lhu $t8, ($a0)
  /* 00460C 80003A0C 00031C00 */       sll $v1, $v1, 0x10
  /* 004610 80003A10 24840002 */     addiu $a0, $a0, 2
  /* 004614 80003A14 24420010 */     addiu $v0, $v0, 0x10
  /* 004618 80003A18 00781825 */        or $v1, $v1, $t8
  /* 00461C 80003A1C 2442FFFF */     addiu $v0, $v0, -1
  .L80003A20:
  /* 004620 80003A20 00E2C823 */      subu $t9, $a3, $v0
  /* 004624 80003A24 03237004 */      sllv $t6, $v1, $t9
  /* 004628 80003A28 000E7FC2 */       srl $t7, $t6, 0x1f
  /* 00462C 80003A2C 55E00004 */      bnel $t7, $zero, .L80003A40
  /* 004630 80003A30 8E730004 */        lw $s3, 4($s3)
  /* 004634 80003A34 10000002 */         b .L80003A40
  /* 004638 80003A38 8E730000 */        lw $s3, ($s3)
  /* 00463C 80003A3C 8E730004 */        lw $s3, 4($s3)
  .L80003A40:
  /* 004640 80003A40 8E780000 */        lw $t8, ($s3)
  /* 004644 80003A44 1700FFEE */      bnez $t8, .L80003A00
  /* 004648 80003A48 00000000 */       nop 
  .L80003A4C:
  /* 00464C 80003A4C 8E720008 */        lw $s2, 8($s3)
  /* 004650 80003A50 0052082A */       slt $at, $v0, $s2
  /* 004654 80003A54 10200006 */      beqz $at, .L80003A70
  /* 004658 80003A58 00D27023 */      subu $t6, $a2, $s2
  /* 00465C 80003A5C 94990000 */       lhu $t9, ($a0)
  /* 004660 80003A60 00031C00 */       sll $v1, $v1, 0x10
  /* 004664 80003A64 24840002 */     addiu $a0, $a0, 2
  /* 004668 80003A68 24420010 */     addiu $v0, $v0, 0x10
  /* 00466C 80003A6C 00791825 */        or $v1, $v1, $t9
  .L80003A70:
  /* 004670 80003A70 00521023 */      subu $v0, $v0, $s2
  /* 004674 80003A74 01C27823 */      subu $t7, $t6, $v0
  /* 004678 80003A78 01E3C004 */      sllv $t8, $v1, $t7
  /* 00467C 80003A7C 00D2C823 */      subu $t9, $a2, $s2
  /* 004680 80003A80 03388806 */      srlv $s1, $t8, $t9
  .L80003A84:
  /* 004684 80003A84 00117080 */       sll $t6, $s1, 2
  /* 004688 80003A88 010E7823 */      subu $t7, $t0, $t6
  /* 00468C 80003A8C 01F09023 */      subu $s2, $t7, $s0
  /* 004690 80003A90 10000025 */         b .L80003B28
  /* 004694 80003A94 26520008 */     addiu $s2, $s2, 8
  .L80003A98:
  /* 004698 80003A98 12400014 */      beqz $s2, .L80003AEC
  /* 00469C 80003A9C 01208025 */        or $s0, $t1, $zero
  .L80003AA0:
  /* 0046A0 80003AA0 5C400007 */     bgtzl $v0, .L80003AC0
  /* 0046A4 80003AA4 2442FFFF */     addiu $v0, $v0, -1
  /* 0046A8 80003AA8 94980000 */       lhu $t8, ($a0)
  /* 0046AC 80003AAC 00031C00 */       sll $v1, $v1, 0x10
  /* 0046B0 80003AB0 24840002 */     addiu $a0, $a0, 2
  /* 0046B4 80003AB4 24420010 */     addiu $v0, $v0, 0x10
  /* 0046B8 80003AB8 00781825 */        or $v1, $v1, $t8
  /* 0046BC 80003ABC 2442FFFF */     addiu $v0, $v0, -1
  .L80003AC0:
  /* 0046C0 80003AC0 00E2C823 */      subu $t9, $a3, $v0
  /* 0046C4 80003AC4 03237004 */      sllv $t6, $v1, $t9
  /* 0046C8 80003AC8 000E7FC2 */       srl $t7, $t6, 0x1f
  /* 0046CC 80003ACC 55E00004 */      bnel $t7, $zero, .L80003AE0
  /* 0046D0 80003AD0 8E100004 */        lw $s0, 4($s0)
  /* 0046D4 80003AD4 10000002 */         b .L80003AE0
  /* 0046D8 80003AD8 8E100000 */        lw $s0, ($s0)
  /* 0046DC 80003ADC 8E100004 */        lw $s0, 4($s0)
  .L80003AE0:
  /* 0046E0 80003AE0 8E180000 */        lw $t8, ($s0)
  /* 0046E4 80003AE4 1700FFEE */      bnez $t8, .L80003AA0
  /* 0046E8 80003AE8 00000000 */       nop 
  .L80003AEC:
  /* 0046EC 80003AEC 8E130008 */        lw $s3, 8($s0)
  /* 0046F0 80003AF0 0053082A */       slt $at, $v0, $s3
  /* 0046F4 80003AF4 10200006 */      beqz $at, .L80003B10
  /* 0046F8 80003AF8 00D37023 */      subu $t6, $a2, $s3
  /* 0046FC 80003AFC 94990000 */       lhu $t9, ($a0)
  /* 004700 80003B00 00031C00 */       sll $v1, $v1, 0x10
  /* 004704 80003B04 24840002 */     addiu $a0, $a0, 2
  /* 004708 80003B08 24420010 */     addiu $v0, $v0, 0x10
  /* 00470C 80003B0C 00791825 */        or $v1, $v1, $t9
  .L80003B10:
  /* 004710 80003B10 00531023 */      subu $v0, $v0, $s3
  /* 004714 80003B14 01C27823 */      subu $t7, $t6, $v0
  /* 004718 80003B18 01E3C004 */      sllv $t8, $v1, $t7
  /* 00471C 80003B1C 00D3C823 */      subu $t9, $a2, $s3
  /* 004720 80003B20 03388806 */      srlv $s1, $t8, $t9
  /* 004724 80003B24 01119023 */      subu $s2, $t0, $s1
  .L80003B28:
  /* 004728 80003B28 51400015 */      beql $t2, $zero, .L80003B80
  /* 00472C 80003B2C 8CAA0008 */        lw $t2, 8($a1)
  .L80003B30:
  /* 004730 80003B30 5C400007 */     bgtzl $v0, .L80003B50
  /* 004734 80003B34 2442FFFF */     addiu $v0, $v0, -1
  /* 004738 80003B38 948E0000 */       lhu $t6, ($a0)
  /* 00473C 80003B3C 00031C00 */       sll $v1, $v1, 0x10
  /* 004740 80003B40 24840002 */     addiu $a0, $a0, 2
  /* 004744 80003B44 24420010 */     addiu $v0, $v0, 0x10
  /* 004748 80003B48 006E1825 */        or $v1, $v1, $t6
  /* 00474C 80003B4C 2442FFFF */     addiu $v0, $v0, -1
  .L80003B50:
  /* 004750 80003B50 00E27823 */      subu $t7, $a3, $v0
  /* 004754 80003B54 01E3C004 */      sllv $t8, $v1, $t7
  /* 004758 80003B58 0018CFC2 */       srl $t9, $t8, 0x1f
  /* 00475C 80003B5C 57200004 */      bnel $t9, $zero, .L80003B70
  /* 004760 80003B60 8CA50004 */        lw $a1, 4($a1)
  /* 004764 80003B64 10000002 */         b .L80003B70
  /* 004768 80003B68 8CA50000 */        lw $a1, ($a1)
  /* 00476C 80003B6C 8CA50004 */        lw $a1, 4($a1)
  .L80003B70:
  /* 004770 80003B70 8CAE0000 */        lw $t6, ($a1)
  /* 004774 80003B74 15C0FFEE */      bnez $t6, .L80003B30
  /* 004778 80003B78 00000000 */       nop 
  /* 00477C 80003B7C 8CAA0008 */        lw $t2, 8($a1)
  .L80003B80:
  /* 004780 80003B80 004A082A */       slt $at, $v0, $t2
  /* 004784 80003B84 10200006 */      beqz $at, .L80003BA0
  /* 004788 80003B88 00CAC023 */      subu $t8, $a2, $t2
  /* 00478C 80003B8C 948F0000 */       lhu $t7, ($a0)
  /* 004790 80003B90 00031C00 */       sll $v1, $v1, 0x10
  /* 004794 80003B94 24840002 */     addiu $a0, $a0, 2
  /* 004798 80003B98 24420010 */     addiu $v0, $v0, 0x10
  /* 00479C 80003B9C 006F1825 */        or $v1, $v1, $t7
  .L80003BA0:
  /* 0047A0 80003BA0 004A1023 */      subu $v0, $v0, $t2
  /* 0047A4 80003BA4 0302C823 */      subu $t9, $t8, $v0
  /* 0047A8 80003BA8 03237004 */      sllv $t6, $v1, $t9
  /* 0047AC 80003BAC 00CA7823 */      subu $t7, $a2, $t2
  /* 0047B0 80003BB0 01EE2806 */      srlv $a1, $t6, $t7
  /* 0047B4 80003BB4 0005802A */       slt $s0, $zero, $a1
  /* 0047B8 80003BB8 12000008 */      beqz $s0, .L80003BDC
  /* 0047BC 80003BBC 24A5FFFF */     addiu $a1, $a1, -1
  .L80003BC0:
  /* 0047C0 80003BC0 92580000 */       lbu $t8, ($s2)
  /* 0047C4 80003BC4 0005802A */       slt $s0, $zero, $a1
  /* 0047C8 80003BC8 24A5FFFF */     addiu $a1, $a1, -1
  /* 0047CC 80003BCC 25080001 */     addiu $t0, $t0, 1
  /* 0047D0 80003BD0 26520001 */     addiu $s2, $s2, 1
  /* 0047D4 80003BD4 1600FFFA */      bnez $s0, .L80003BC0
  /* 0047D8 80003BD8 A118FFFF */        sb $t8, -1($t0)
  .L80003BDC:
  /* 0047DC 80003BDC 010D082B */      sltu $at, $t0, $t5
  /* 0047E0 80003BE0 1420FF3E */      bnez $at, .L800038DC
  /* 0047E4 80003BE4 00000000 */       nop 
  .L80003BE8:
  /* 0047E8 80003BE8 8FB00008 */        lw $s0, 8($sp)
  /* 0047EC 80003BEC 8FB1000C */        lw $s1, 0xc($sp)
  /* 0047F0 80003BF0 8FB20010 */        lw $s2, 0x10($sp)
  /* 0047F4 80003BF4 8FB30014 */        lw $s3, 0x14($sp)
  /* 0047F8 80003BF8 03E00008 */        jr $ra
  /* 0047FC 80003BFC 27BD0430 */     addiu $sp, $sp, 0x430

# split
