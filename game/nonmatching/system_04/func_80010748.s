.section .text
glabel func_80010748
  /* 011348 80010748 27BDFF78 */     addiu $sp, $sp, -0x88
  /* 01134C 8001074C 3C0E8004 */       lui $t6, %hi(D_80046A58)
  /* 011350 80010750 8DCE6A58 */        lw $t6, %lo(D_80046A58)($t6)
  /* 011354 80010754 AFBF0014 */        sw $ra, 0x14($sp)
  /* 011358 80010758 AFA40088 */        sw $a0, 0x88($sp)
  /* 01135C 8001075C AFA60090 */        sw $a2, 0x90($sp)
  /* 011360 80010760 8DC20074 */        lw $v0, 0x74($t6)
  /* 011364 80010764 C4A4001C */      lwc1 $f4, 0x1c($a1)
  /* 011368 80010768 C4A80020 */      lwc1 $f8, 0x20($a1)
  /* 01136C 8001076C C446003C */      lwc1 $f6, 0x3c($v0)
  /* 011370 80010770 C44A0040 */      lwc1 $f10, 0x40($v0)
  /* 011374 80010774 46062401 */     sub.s $f16, $f4, $f6
  /* 011378 80010778 C4A40024 */      lwc1 $f4, 0x24($a1)
  /* 01137C 8001077C C4460044 */      lwc1 $f6, 0x44($v0)
  /* 011380 80010780 460A4081 */     sub.s $f2, $f8, $f10
  /* 011384 80010784 46108202 */     mul.s $f8, $f16, $f16
  /* 011388 80010788 E7B00044 */      swc1 $f16, 0x44($sp)
  /* 01138C 8001078C 46062481 */     sub.s $f18, $f4, $f6
  /* 011390 80010790 46021282 */     mul.s $f10, $f2, $f2
  /* 011394 80010794 E7A20040 */      swc1 $f2, 0x40($sp)
  /* 011398 80010798 AFA5008C */        sw $a1, 0x8c($sp)
  /* 01139C 8001079C 46129182 */     mul.s $f6, $f18, $f18
  /* 0113A0 800107A0 E7B2003C */      swc1 $f18, 0x3c($sp)
  /* 0113A4 800107A4 460A4100 */     add.s $f4, $f8, $f10
  /* 0113A8 800107A8 0C00CD44 */       jal sqrtf
  /* 0113AC 800107AC 46062300 */     add.s $f12, $f4, $f6
  /* 0113B0 800107B0 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 0113B4 800107B4 44814000 */      mtc1 $at, $f8 # 1.0 to cop1
  /* 0113B8 800107B8 C7B00044 */      lwc1 $f16, 0x44($sp)
  /* 0113BC 800107BC C7A20040 */      lwc1 $f2, 0x40($sp)
  /* 0113C0 800107C0 46004383 */     div.s $f14, $f8, $f0
  /* 0113C4 800107C4 C7B2003C */      lwc1 $f18, 0x3c($sp)
  /* 0113C8 800107C8 460E8402 */     mul.s $f16, $f16, $f14
  /* 0113CC 800107CC 00000000 */       nop 
  /* 0113D0 800107D0 460E1082 */     mul.s $f2, $f2, $f14
  /* 0113D4 800107D4 00000000 */       nop 
  /* 0113D8 800107D8 460E9482 */     mul.s $f18, $f18, $f14
  /* 0113DC 800107DC E7B00044 */      swc1 $f16, 0x44($sp)
  /* 0113E0 800107E0 46108282 */     mul.s $f10, $f16, $f16
  /* 0113E4 800107E4 E7A20040 */      swc1 $f2, 0x40($sp)
  /* 0113E8 800107E8 46021102 */     mul.s $f4, $f2, $f2
  /* 0113EC 800107EC E7B2003C */      swc1 $f18, 0x3c($sp)
  /* 0113F0 800107F0 0C00CD44 */       jal sqrtf
  /* 0113F4 800107F4 46045300 */     add.s $f12, $f10, $f4
  /* 0113F8 800107F8 44804000 */      mtc1 $zero, $f8
  /* 0113FC 800107FC 44806000 */      mtc1 $zero, $f12
  /* 011400 80010800 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 011404 80010804 46080032 */    c.eq.s $f0, $f8
  /* 011408 80010808 44813000 */      mtc1 $at, $f6 # 1.0 to cop1
  /* 01140C 8001080C 8FA5008C */        lw $a1, 0x8c($sp)
  /* 011410 80010810 C7A20040 */      lwc1 $f2, 0x40($sp)
  /* 011414 80010814 C7B00044 */      lwc1 $f16, 0x44($sp)
  /* 011418 80010818 C7B2003C */      lwc1 $f18, 0x3c($sp)
  /* 01141C 8001081C E7AC0074 */      swc1 $f12, 0x74($sp)
  /* 011420 80010820 E7AC0064 */      swc1 $f12, 0x64($sp)
  /* 011424 80010824 E7AC0054 */      swc1 $f12, 0x54($sp)
  /* 011428 80010828 E7AC0060 */      swc1 $f12, 0x60($sp)
  /* 01142C 8001082C 45010019 */      bc1t .L80010894
  /* 011430 80010830 E7A60084 */      swc1 $f6, 0x84($sp)
  /* 011434 80010834 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 011438 80010838 44815000 */      mtc1 $at, $f10 # 1.0 to cop1
  /* 01143C 8001083C 46008307 */     neg.s $f12, $f16
  /* 011440 80010840 E7A00070 */      swc1 $f0, 0x70($sp)
  /* 011444 80010844 46005383 */     div.s $f14, $f10, $f0
  /* 011448 80010848 E7AC0048 */      swc1 $f12, 0x48($sp)
  /* 01144C 8001084C 46001287 */     neg.s $f10, $f2
  /* 011450 80010850 E7AA0018 */      swc1 $f10, 0x18($sp)
  /* 011454 80010854 460E1102 */     mul.s $f4, $f2, $f14
  /* 011458 80010858 00000000 */       nop 
  /* 01145C 8001085C 46126182 */     mul.s $f6, $f12, $f18
  /* 011460 80010860 E7A40058 */      swc1 $f4, 0x58($sp)
  /* 011464 80010864 C7A40018 */      lwc1 $f4, 0x18($sp)
  /* 011468 80010868 460E3202 */     mul.s $f8, $f6, $f14
  /* 01146C 8001086C E7A4004C */      swc1 $f4, 0x4c($sp)
  /* 011470 80010870 460E6182 */     mul.s $f6, $f12, $f14
  /* 011474 80010874 E7A80068 */      swc1 $f8, 0x68($sp)
  /* 011478 80010878 46122202 */     mul.s $f8, $f4, $f18
  /* 01147C 8001087C E7A6005C */      swc1 $f6, 0x5c($sp)
  /* 011480 80010880 46009187 */     neg.s $f6, $f18
  /* 011484 80010884 E7A60050 */      swc1 $f6, 0x50($sp)
  /* 011488 80010888 460E4282 */     mul.s $f10, $f8, $f14
  /* 01148C 8001088C 1000000C */         b .L800108C0
  /* 011490 80010890 E7AA006C */      swc1 $f10, 0x6c($sp)
  .L80010894:
  /* 011494 80010894 44800000 */      mtc1 $zero, $f0
  /* 011498 80010898 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 01149C 8001089C 44811000 */      mtc1 $at, $f2 # 1.0 to cop1
  /* 0114A0 800108A0 E7A0006C */      swc1 $f0, 0x6c($sp)
  /* 0114A4 800108A4 E7A0004C */      swc1 $f0, 0x4c($sp)
  /* 0114A8 800108A8 E7A00068 */      swc1 $f0, 0x68($sp)
  /* 0114AC 800108AC E7A00058 */      swc1 $f0, 0x58($sp)
  /* 0114B0 800108B0 E7A00050 */      swc1 $f0, 0x50($sp)
  /* 0114B4 800108B4 E7A2005C */      swc1 $f2, 0x5c($sp)
  /* 0114B8 800108B8 E7A20048 */      swc1 $f2, 0x48($sp)
  /* 0114BC 800108BC E7A20070 */      swc1 $f2, 0x70($sp)
  .L800108C0:
  /* 0114C0 800108C0 8FAF0090 */        lw $t7, 0x90($sp)
  /* 0114C4 800108C4 27A40048 */     addiu $a0, $sp, 0x48
  /* 0114C8 800108C8 51E00009 */      beql $t7, $zero, .L800108F0
  /* 0114CC 800108CC 44801000 */      mtc1 $zero, $f2
  /* 0114D0 800108D0 C4A4001C */      lwc1 $f4, 0x1c($a1)
  /* 0114D4 800108D4 E7A40078 */      swc1 $f4, 0x78($sp)
  /* 0114D8 800108D8 C4A80020 */      lwc1 $f8, 0x20($a1)
  /* 0114DC 800108DC E7A8007C */      swc1 $f8, 0x7c($sp)
  /* 0114E0 800108E0 C4AA0024 */      lwc1 $f10, 0x24($a1)
  /* 0114E4 800108E4 10000006 */         b .L80010900
  /* 0114E8 800108E8 E7AA0080 */      swc1 $f10, 0x80($sp)
  /* 0114EC 800108EC 44801000 */      mtc1 $zero, $f2
  .L800108F0:
  /* 0114F0 800108F0 00000000 */       nop 
  /* 0114F4 800108F4 E7A2007C */      swc1 $f2, 0x7c($sp)
  /* 0114F8 800108F8 E7A20078 */      swc1 $f2, 0x78($sp)
  /* 0114FC 800108FC E7A20080 */      swc1 $f2, 0x80($sp)
  .L80010900:
  /* 011500 80010900 0C0067A8 */       jal func_80019EA0
  /* 011504 80010904 8FA50088 */        lw $a1, 0x88($sp)
  /* 011508 80010908 8FBF0014 */        lw $ra, 0x14($sp)
  /* 01150C 8001090C 27BD0088 */     addiu $sp, $sp, 0x88
  /* 011510 80010910 03E00008 */        jr $ra
  /* 011514 80010914 00000000 */       nop 
