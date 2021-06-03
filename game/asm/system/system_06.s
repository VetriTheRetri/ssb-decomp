.include "macros.inc"

.section .data
# 06
glabel D_8003B940
  .incbin "system.raw.bin", 0x3B540, 0x4

glabel D_8003B944
  /* 3B544 03C544 8003B944 */  .4byte D_8003B940

glabel D_8003B948
  .incbin "system.raw.bin", 0x3B548, 0x4

glabel D_8003B94C
  .incbin "system.raw.bin", 0x3B54C, 0x4


.section .rodata
# 06
glabel D_8003E350
  /* 3DF50 03EF50 8003E350 */
  .4byte 0xbddd6712 # .float -0.10810675

glabel D_8003E354
  /* 3DF54 03EF54 8003E354 */
  .4byte 0xc23249a5 # .float -44.57192

glabel D_8003E358
  /* 3DF58 03EF58 8003E358 */
  .4byte 0xbe25cb3d # .float -0.1619081

glabel D_8003E35C
  /* 3DF5C 03EF5C 8003E35C */
  .4byte 0xc17c6261 # .float -15.774018

glabel D_8003E360
  /* 3DF60 03EF60 8003E360 */
  .4byte 0xbf0e39d2 # .float -0.55556977

glabel D_8003E364
  /* 3DF64 03EF64 8003E364 */
  .4byte 0xc040000d # .float -3.000003

glabel D_8003E368
  /* 3DF68 03EF68 8003E368 */
  .4byte 0x3fc90fdb # .float 1.5707964

glabel D_8003E36C
  /* 3DF6C 03EF6C 8003E36C */
  .4byte 0xbfc90fdb # .float -1.5707964

glabel D_8003E370
  /* 3DF70 03EF70 8003E370 */
  .4byte 0x40490fdb # .float 3.1415927

glabel D_8003E374
  /* 3DF74 03EF74 8003E374 */
  .4byte 0x3fc90fdb # .float 1.5707964

glabel D_8003E378
  /* 3DF78 03EF78 8003E378 */
  .4byte 0x3f7fff58 # .float 0.99999

glabel D_8003E37C
  /* 3DF7C 03EF7C 8003E37C */
  .4byte 0x3fc90fdb # .float 1.5707964

glabel D_8003E380
  /* 3DF80 03EF80 8003E380 */
  .4byte 0xbf7fff58 # .float -0.99999

glabel D_8003E384
  /* 3DF84 03EF84 8003E384 */
  .4byte 0xbfc90fdb # .float -1.5707964

glabel D_8003E388
  /* 3DF88 03EF88 8003E388 */
  .4byte 0x3f7fff58 # .float 0.99999

glabel D_8003E38C
  /* 3DF8C 03EF8C 8003E38C */
  .4byte 0xbf7fff58 # .float -0.99999

glabel D_8003E390
  /* 3DF90 03EF90 8003E390 */
  .4byte 0x40490fdb # .float 3.1415927

glabel D_8003E394
  /* 3DF94 03EF94 8003E394 */
  .4byte 0x3fc90fdb # .float 1.5707964
  .incbin "system.raw.bin", 0x3DF98, 0x8

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .text

.align 4

# Likely start of new file
glabel func_800184E0
  /* 0190E0 800184E0 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 0190E4 800184E4 AFBF0014 */        sw $ra, 0x14($sp)
  /* 0190E8 800184E8 E7AC0020 */      swc1 $f12, 0x20($sp)
  /* 0190EC 800184EC 0C00C0FC */       jal __sinf
  /* 0190F0 800184F0 C7AC0020 */      lwc1 $f12, 0x20($sp)
  /* 0190F4 800184F4 E7A0001C */      swc1 $f0, 0x1c($sp)
  /* 0190F8 800184F8 0C00D734 */       jal cosf
  /* 0190FC 800184FC C7AC0020 */      lwc1 $f12, 0x20($sp)
  /* 019100 80018500 8FBF0014 */        lw $ra, 0x14($sp)
  /* 019104 80018504 C7A4001C */      lwc1 $f4, 0x1c($sp)
  /* 019108 80018508 27BD0020 */     addiu $sp, $sp, 0x20
  /* 01910C 8001850C 03E00008 */        jr $ra
  /* 019110 80018510 46002003 */     div.s $f0, $f4, $f0

glabel func_80018514
  /* 019114 80018514 44801000 */      mtc1 $zero, $f2
  /* 019118 80018518 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 01911C 8001851C 46026032 */    c.eq.s $f12, $f2
  /* 019120 80018520 00000000 */       nop 
  /* 019124 80018524 45020004 */     bc1fl .L80018538
  /* 019128 80018528 44810000 */      mtc1 $at, $f0 # 1.0 to cop1
  /* 01912C 8001852C 03E00008 */        jr $ra
  /* 019130 80018530 46001006 */     mov.s $f0, $f2

  /* 019134 80018534 44810000 */      mtc1 $at, $f0
  .L80018538:
  /* 019138 80018538 24020001 */     addiu $v0, $zero, 1
  /* 01913C 8001853C 3C01BF80 */       lui $at, (0xBF800000 >> 16) # -1.0
  /* 019140 80018540 460C003C */    c.lt.s $f0, $f12
  /* 019144 80018544 00000000 */       nop 
  /* 019148 80018548 45020004 */     bc1fl .L8001855C
  /* 01914C 8001854C 44812000 */      mtc1 $at, $f4 # -1.0 to cop1
  /* 019150 80018550 1000000A */         b .L8001857C
  /* 019154 80018554 460C0303 */     div.s $f12, $f0, $f12
  /* 019158 80018558 44812000 */      mtc1 $at, $f4 # -1.0 to cop1
  .L8001855C:
  /* 01915C 8001855C 00001025 */        or $v0, $zero, $zero
  /* 019160 80018560 4604603C */    c.lt.s $f12, $f4
  /* 019164 80018564 00000000 */       nop 
  /* 019168 80018568 45000004 */      bc1f .L8001857C
  /* 01916C 8001856C 00000000 */       nop 
  /* 019170 80018570 460C0303 */     div.s $f12, $f0, $f12
  /* 019174 80018574 10000001 */         b .L8001857C
  /* 019178 80018578 24020002 */     addiu $v0, $zero, 2
  .L8001857C:
  /* 01917C 8001857C 460C6002 */     mul.s $f0, $f12, $f12
  /* 019180 80018580 3C018004 */       lui $at, %hi(D_8003E350)
  /* 019184 80018584 C426E350 */      lwc1 $f6, %lo(D_8003E350)($at)
  /* 019188 80018588 3C018004 */       lui $at, %hi(D_8003E354)
  /* 01918C 8001858C C42AE354 */      lwc1 $f10, %lo(D_8003E354)($at)
  /* 019190 80018590 3C018004 */       lui $at, %hi(D_8003E358)
  /* 019194 80018594 C424E358 */      lwc1 $f4, %lo(D_8003E358)($at)
  /* 019198 80018598 46060203 */     div.s $f8, $f0, $f6
  /* 01919C 8001859C 3C018004 */       lui $at, %hi(D_8003E35C)
  /* 0191A0 800185A0 460A4400 */     add.s $f16, $f8, $f10
  /* 0191A4 800185A4 C42AE35C */      lwc1 $f10, %lo(D_8003E35C)($at)
  /* 0191A8 800185A8 3C018004 */       lui $at, %hi(D_8003E360)
  /* 0191AC 800185AC 46100483 */     div.s $f18, $f0, $f16
  /* 0191B0 800185B0 46049180 */     add.s $f6, $f18, $f4
  /* 0191B4 800185B4 C424E360 */      lwc1 $f4, %lo(D_8003E360)($at)
  /* 0191B8 800185B8 3C018004 */       lui $at, %hi(D_8003E364)
  /* 0191BC 800185BC 46060203 */     div.s $f8, $f0, $f6
  /* 0191C0 800185C0 460A4400 */     add.s $f16, $f8, $f10
  /* 0191C4 800185C4 C42AE364 */      lwc1 $f10, %lo(D_8003E364)($at)
  /* 0191C8 800185C8 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 0191CC 800185CC 46100483 */     div.s $f18, $f0, $f16
  /* 0191D0 800185D0 46049180 */     add.s $f6, $f18, $f4
  /* 0191D4 800185D4 44812000 */      mtc1 $at, $f4 # 1.0 to cop1
  /* 0191D8 800185D8 24010001 */     addiu $at, $zero, 1
  /* 0191DC 800185DC 46060203 */     div.s $f8, $f0, $f6
  /* 0191E0 800185E0 460A4400 */     add.s $f16, $f8, $f10
  /* 0191E4 800185E4 46100483 */     div.s $f18, $f0, $f16
  /* 0191E8 800185E8 46049180 */     add.s $f6, $f18, $f4
  /* 0191EC 800185EC 460C3082 */     mul.s $f2, $f6, $f12
  /* 0191F0 800185F0 10400007 */      beqz $v0, .L80018610
  /* 0191F4 800185F4 00000000 */       nop 
  /* 0191F8 800185F8 10410007 */       beq $v0, $at, .L80018618
  /* 0191FC 800185FC 24010002 */     addiu $at, $zero, 2
  /* 019200 80018600 10410009 */       beq $v0, $at, .L80018628
  /* 019204 80018604 00000000 */       nop 
  /* 019208 80018608 03E00008 */        jr $ra
  /* 01920C 8001860C 00000000 */       nop 

  .L80018610:
  /* 019210 80018610 03E00008 */        jr $ra
  /* 019214 80018614 46001006 */     mov.s $f0, $f2

  .L80018618:
  /* 019218 80018618 3C018004 */       lui $at, %hi(D_8003E368)
  /* 01921C 8001861C C428E368 */      lwc1 $f8, %lo(D_8003E368)($at)
  /* 019220 80018620 03E00008 */        jr $ra
  /* 019224 80018624 46024001 */     sub.s $f0, $f8, $f2

  .L80018628:
  /* 019228 80018628 3C018004 */       lui $at, %hi(D_8003E36C)
  /* 01922C 8001862C C42AE36C */      lwc1 $f10, %lo(D_8003E36C)($at)
  /* 019230 80018630 46025001 */     sub.s $f0, $f10, $f2
  /* 019234 80018634 03E00008 */        jr $ra
  /* 019238 80018638 00000000 */       nop 

glabel func_8001863C
  /* 01923C 8001863C 44801000 */      mtc1 $zero, $f2
  /* 019240 80018640 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 019244 80018644 F7B40010 */      sdc1 $f20, 0x10($sp)
  /* 019248 80018648 460E103C */    c.lt.s $f2, $f14
  /* 01924C 8001864C 46006506 */     mov.s $f20, $f12
  /* 019250 80018650 AFBF001C */        sw $ra, 0x1c($sp)
  /* 019254 80018654 45020006 */     bc1fl .L80018670
  /* 019258 80018658 4602703C */    c.lt.s $f14, $f2
  /* 01925C 8001865C 0C006145 */       jal func_80018514
  /* 019260 80018660 460E6303 */     div.s $f12, $f12, $f14
  /* 019264 80018664 10000031 */         b .L8001872C
  /* 019268 80018668 8FBF001C */        lw $ra, 0x1c($sp)
  /* 01926C 8001866C 4602703C */    c.lt.s $f14, $f2
  .L80018670:
  /* 019270 80018670 00000000 */       nop 
  /* 019274 80018674 4502001B */     bc1fl .L800186E4
  /* 019278 80018678 4602A032 */    c.eq.s $f20, $f2
  /* 01927C 8001867C 4602A03C */    c.lt.s $f20, $f2
  /* 019280 80018680 24020001 */     addiu $v0, $zero, 1
  /* 019284 80018684 460EA003 */     div.s $f0, $f20, $f14
  /* 019288 80018688 45000003 */      bc1f .L80018698
  /* 01928C 8001868C 00000000 */       nop 
  /* 019290 80018690 10000001 */         b .L80018698
  /* 019294 80018694 2402FFFF */     addiu $v0, $zero, -1
  .L80018698:
  /* 019298 80018698 4602003C */    c.lt.s $f0, $f2
  /* 01929C 8001869C 00000000 */       nop 
  /* 0192A0 800186A0 45020004 */     bc1fl .L800186B4
  /* 0192A4 800186A4 46000306 */     mov.s $f12, $f0
  /* 0192A8 800186A8 10000002 */         b .L800186B4
  /* 0192AC 800186AC 46000307 */     neg.s $f12, $f0
  /* 0192B0 800186B0 46000306 */     mov.s $f12, $f0
  .L800186B4:
  /* 0192B4 800186B4 0C006145 */       jal func_80018514
  /* 0192B8 800186B8 AFA20020 */        sw $v0, 0x20($sp)
  /* 0192BC 800186BC 8FA20020 */        lw $v0, 0x20($sp)
  /* 0192C0 800186C0 3C018004 */       lui $at, %hi(D_8003E370)
  /* 0192C4 800186C4 C424E370 */      lwc1 $f4, %lo(D_8003E370)($at)
  /* 0192C8 800186C8 44824000 */      mtc1 $v0, $f8
  /* 0192CC 800186CC 46002181 */     sub.s $f6, $f4, $f0
  /* 0192D0 800186D0 468042A0 */   cvt.s.w $f10, $f8
  /* 0192D4 800186D4 460A3002 */     mul.s $f0, $f6, $f10
  /* 0192D8 800186D8 10000014 */         b .L8001872C
  /* 0192DC 800186DC 8FBF001C */        lw $ra, 0x1c($sp)
  /* 0192E0 800186E0 4602A032 */    c.eq.s $f20, $f2
  .L800186E4:
  /* 0192E4 800186E4 00000000 */       nop 
  /* 0192E8 800186E8 4503000F */     bc1tl .L80018728
  /* 0192EC 800186EC 46001006 */     mov.s $f0, $f2
  /* 0192F0 800186F0 4602A03C */    c.lt.s $f20, $f2
  /* 0192F4 800186F4 24020001 */     addiu $v0, $zero, 1
  /* 0192F8 800186F8 45000003 */      bc1f .L80018708
  /* 0192FC 800186FC 00000000 */       nop 
  /* 019300 80018700 10000001 */         b .L80018708
  /* 019304 80018704 2402FFFF */     addiu $v0, $zero, -1
  .L80018708:
  /* 019308 80018708 44828000 */      mtc1 $v0, $f16
  /* 01930C 8001870C 3C018004 */       lui $at, %hi(D_8003E374)
  /* 019310 80018710 C424E374 */      lwc1 $f4, %lo(D_8003E374)($at)
  /* 019314 80018714 468084A0 */   cvt.s.w $f18, $f16
  /* 019318 80018718 46049002 */     mul.s $f0, $f18, $f4
  /* 01931C 8001871C 10000003 */         b .L8001872C
  /* 019320 80018720 8FBF001C */        lw $ra, 0x1c($sp)
  /* 019324 80018724 46001006 */     mov.s $f0, $f2
  .L80018728:
  /* 019328 80018728 8FBF001C */        lw $ra, 0x1c($sp)
  .L8001872C:
  /* 01932C 8001872C D7B40010 */      ldc1 $f20, 0x10($sp)
  /* 019330 80018730 27BD0028 */     addiu $sp, $sp, 0x28
  /* 019334 80018734 03E00008 */        jr $ra
  /* 019338 80018738 00000000 */       nop 

glabel func_8001873C
  /* 01933C 8001873C 3C018004 */       lui $at, %hi(D_8003E378)
  /* 019340 80018740 C424E378 */      lwc1 $f4, %lo(D_8003E378)($at)
  /* 019344 80018744 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 019348 80018748 AFBF0014 */        sw $ra, 0x14($sp)
  /* 01934C 8001874C 460C203C */    c.lt.s $f4, $f12
  /* 019350 80018750 46006386 */     mov.s $f14, $f12
  /* 019354 80018754 3C018004 */       lui $at, 0x8004
  /* 019358 80018758 45000004 */      bc1f .L8001876C
  /* 01935C 8001875C 00000000 */       nop 
  /* 019360 80018760 3C018004 */       lui $at, %hi(D_8003E380)
  /* 019364 80018764 10000012 */         b .L800187B0
  /* 019368 80018768 C420E37C */      lwc1 $f0, %lo(D_8003E37C)($at)
  .L8001876C:
  /* 01936C 8001876C C426E380 */      lwc1 $f6, %lo(D_8003E380)($at)
  /* 019370 80018770 3C018004 */       lui $at, %hi(D_8003E384)
  /* 019374 80018774 4606703C */    c.lt.s $f14, $f6
  /* 019378 80018778 00000000 */       nop 
  /* 01937C 8001877C 45000003 */      bc1f .L8001878C
  /* 019380 80018780 00000000 */       nop 
  /* 019384 80018784 1000000A */         b .L800187B0
  /* 019388 80018788 C420E384 */      lwc1 $f0, %lo(D_8003E384)($at)
  .L8001878C:
  /* 01938C 8001878C 460E7282 */     mul.s $f10, $f14, $f14
  /* 019390 80018790 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 019394 80018794 44814000 */      mtc1 $at, $f8 # 1.0 to cop1
  /* 019398 80018798 E7AE0018 */      swc1 $f14, 0x18($sp)
  /* 01939C 8001879C 0C00CD44 */       jal sqrtf
  /* 0193A0 800187A0 460A4301 */     sub.s $f12, $f8, $f10
  /* 0193A4 800187A4 C7AE0018 */      lwc1 $f14, 0x18($sp)
  /* 0193A8 800187A8 0C006145 */       jal func_80018514
  /* 0193AC 800187AC 46007303 */     div.s $f12, $f14, $f0
  .L800187B0:
  /* 0193B0 800187B0 8FBF0014 */        lw $ra, 0x14($sp)
  /* 0193B4 800187B4 27BD0018 */     addiu $sp, $sp, 0x18
  /* 0193B8 800187B8 03E00008 */        jr $ra
  /* 0193BC 800187BC 00000000 */       nop 

glabel func_800187C0
  /* 0193C0 800187C0 3C018004 */       lui $at, %hi(D_8003E388)
  /* 0193C4 800187C4 C424E388 */      lwc1 $f4, %lo(D_8003E388)($at)
  /* 0193C8 800187C8 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 0193CC 800187CC AFBF0014 */        sw $ra, 0x14($sp)
  /* 0193D0 800187D0 460C203C */    c.lt.s $f4, $f12
  /* 0193D4 800187D4 46006386 */     mov.s $f14, $f12
  /* 0193D8 800187D8 3C018004 */       lui $at, %hi(D_8003E38C)
  /* 0193DC 800187DC 45000004 */      bc1f .L800187F0
  /* 0193E0 800187E0 00000000 */       nop 
  /* 0193E4 800187E4 44800000 */      mtc1 $zero, $f0
  /* 0193E8 800187E8 10000016 */         b .L80018844
  /* 0193EC 800187EC 8FBF0014 */        lw $ra, 0x14($sp)
  .L800187F0:
  /* 0193F0 800187F0 C426E38C */      lwc1 $f6, %lo(D_8003E38C)($at)
  /* 0193F4 800187F4 3C018004 */       lui $at, %hi(D_8003E390)
  /* 0193F8 800187F8 4606703C */    c.lt.s $f14, $f6
  /* 0193FC 800187FC 00000000 */       nop 
  /* 019400 80018800 45000003 */      bc1f .L80018810
  /* 019404 80018804 00000000 */       nop 
  /* 019408 80018808 1000000D */         b .L80018840
  /* 01940C 8001880C C420E390 */      lwc1 $f0, %lo(D_8003E390)($at)
  .L80018810:
  /* 019410 80018810 460E7282 */     mul.s $f10, $f14, $f14
  /* 019414 80018814 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 019418 80018818 44814000 */      mtc1 $at, $f8 # 1.0 to cop1
  /* 01941C 8001881C E7AE0018 */      swc1 $f14, 0x18($sp)
  /* 019420 80018820 0C00CD44 */       jal sqrtf
  /* 019424 80018824 460A4301 */     sub.s $f12, $f8, $f10
  /* 019428 80018828 C7AE0018 */      lwc1 $f14, 0x18($sp)
  /* 01942C 8001882C 0C006145 */       jal func_80018514
  /* 019430 80018830 46007303 */     div.s $f12, $f14, $f0
  /* 019434 80018834 3C018004 */       lui $at, %hi(D_8003E394)
  /* 019438 80018838 C430E394 */      lwc1 $f16, %lo(D_8003E394)($at)
  /* 01943C 8001883C 46008001 */     sub.s $f0, $f16, $f0
  .L80018840:
  /* 019440 80018840 8FBF0014 */        lw $ra, 0x14($sp)
  .L80018844:
  /* 019444 80018844 27BD0018 */     addiu $sp, $sp, 0x18
  /* 019448 80018848 03E00008 */        jr $ra
  /* 01944C 8001884C 00000000 */       nop 

  /* 019450 80018850 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 019454 80018854 AFBF0014 */        sw $ra, 0x14($sp)
  /* 019458 80018858 0C00C0FC */       jal __sinf
  /* 01945C 8001885C 00000000 */       nop 
  /* 019460 80018860 8FBF0014 */        lw $ra, 0x14($sp)
  /* 019464 80018864 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 019468 80018868 44812000 */      mtc1 $at, $f4 # 1.0 to cop1
  /* 01946C 8001886C 27BD0018 */     addiu $sp, $sp, 0x18
  /* 019470 80018870 03E00008 */        jr $ra
  /* 019474 80018874 46002003 */     div.s $f0, $f4, $f0

  /* 019478 80018878 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 01947C 8001887C AFBF0014 */        sw $ra, 0x14($sp)
  /* 019480 80018880 0C00D734 */       jal cosf
  /* 019484 80018884 00000000 */       nop 
  /* 019488 80018888 8FBF0014 */        lw $ra, 0x14($sp)
  /* 01948C 8001888C 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 019490 80018890 44812000 */      mtc1 $at, $f4 # 1.0 to cop1
  /* 019494 80018894 27BD0018 */     addiu $sp, $sp, 0x18
  /* 019498 80018898 03E00008 */        jr $ra
  /* 01949C 8001889C 46002003 */     div.s $f0, $f4, $f0

  /* 0194A0 800188A0 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 0194A4 800188A4 AFBF0014 */        sw $ra, 0x14($sp)
  /* 0194A8 800188A8 0C006138 */       jal func_800184E0
  /* 0194AC 800188AC 00000000 */       nop 
  /* 0194B0 800188B0 8FBF0014 */        lw $ra, 0x14($sp)
  /* 0194B4 800188B4 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 0194B8 800188B8 44812000 */      mtc1 $at, $f4 # 1.0 to cop1
  /* 0194BC 800188BC 27BD0018 */     addiu $sp, $sp, 0x18
  /* 0194C0 800188C0 03E00008 */        jr $ra
  /* 0194C4 800188C4 46002003 */     div.s $f0, $f4, $f0

  /* 0194C8 800188C8 3C0E8004 */       lui $t6, %hi(D_8003B944)
  /* 0194CC 800188CC 8DCEB944 */        lw $t6, %lo(D_8003B944)($t6)
  /* 0194D0 800188D0 03E00008 */        jr $ra
  /* 0194D4 800188D4 ADC40000 */        sw $a0, ($t6)

  /* 0194D8 800188D8 3C0E8004 */       lui $t6, %hi(D_8003B944)
  /* 0194DC 800188DC 8DCEB944 */        lw $t6, %lo(D_8003B944)($t6)
  /* 0194E0 800188E0 03E00008 */        jr $ra
  /* 0194E4 800188E4 8DC20000 */        lw $v0, ($t6)

glabel func_800188E8
  /* 0194E8 800188E8 14800006 */      bnez $a0, .L80018904
  /* 0194EC 800188EC 3C018004 */       lui $at, 0x8004
  /* 0194F0 800188F0 3C0E8004 */       lui $t6, %hi(D_8003B940)
  /* 0194F4 800188F4 25CEB940 */     addiu $t6, $t6, %lo(D_8003B940)
  /* 0194F8 800188F8 3C018004 */       lui $at, %hi(D_8003B944)
  /* 0194FC 800188FC 03E00008 */        jr $ra
  /* 019500 80018900 AC2EB944 */        sw $t6, %lo(D_8003B944)($at)

  .L80018904:
  /* 019504 80018904 AC24B944 */        sw $a0, -0x46bc($at)
  /* 019508 80018908 03E00008 */        jr $ra
  /* 01950C 8001890C 00000000 */       nop 

glabel func_80018910
  /* 019510 80018910 3C048004 */       lui $a0, %hi(D_8003B944)
  /* 019514 80018914 8C84B944 */        lw $a0, %lo(D_8003B944)($a0)
  /* 019518 80018918 3C010003 */       lui $at, (0x343FD >> 16) # 214013
  /* 01951C 8001891C 342143FD */       ori $at, $at, (0x343FD & 0xFFFF) # 214013
  /* 019520 80018920 8C830000 */        lw $v1, ($a0)
  /* 019524 80018924 00610019 */     multu $v1, $at
  /* 019528 80018928 3C010026 */       lui $at, (0x269EC3 >> 16) # 2531011
  /* 01952C 8001892C 34219EC3 */       ori $at, $at, (0x269EC3 & 0xFFFF) # 2531011
  /* 019530 80018930 00001812 */      mflo $v1
  /* 019534 80018934 00611821 */      addu $v1, $v1, $at
  /* 019538 80018938 00031403 */       sra $v0, $v1, 0x10
  /* 01953C 8001893C 3042FFFF */      andi $v0, $v0, 0xffff
  /* 019540 80018940 03E00008 */        jr $ra
  /* 019544 80018944 AC830000 */        sw $v1, ($a0)

glabel func_80018948
  /* 019548 80018948 3C038004 */       lui $v1, %hi(D_8003B944)
  /* 01954C 8001894C 8C63B944 */        lw $v1, %lo(D_8003B944)($v1)
  /* 019550 80018950 3C010003 */       lui $at, (0x343FD >> 16) # 214013
  /* 019554 80018954 342143FD */       ori $at, $at, (0x343FD & 0xFFFF) # 214013
  /* 019558 80018958 8C620000 */        lw $v0, ($v1)
  /* 01955C 8001895C 00410019 */     multu $v0, $at
  /* 019560 80018960 3C010026 */       lui $at, (0x269EC3 >> 16) # 2531011
  /* 019564 80018964 34219EC3 */       ori $at, $at, (0x269EC3 & 0xFFFF) # 2531011
  /* 019568 80018968 00001012 */      mflo $v0
  /* 01956C 8001896C 00411021 */      addu $v0, $v0, $at
  /* 019570 80018970 00027403 */       sra $t6, $v0, 0x10
  /* 019574 80018974 31CFFFFF */      andi $t7, $t6, 0xffff
  /* 019578 80018978 448F2000 */      mtc1 $t7, $f4
  /* 01957C 8001897C 3C014780 */       lui $at, (0x47800000 >> 16) # 65536.0
  /* 019580 80018980 44814000 */      mtc1 $at, $f8 # 65536.0 to cop1
  /* 019584 80018984 468021A0 */   cvt.s.w $f6, $f4
  /* 019588 80018988 AC620000 */        sw $v0, ($v1)
  /* 01958C 8001898C 03E00008 */        jr $ra
  /* 019590 80018990 46083003 */     div.s $f0, $f6, $f8

glabel func_80018994
  /* 019594 80018994 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 019598 80018998 AFBF0014 */        sw $ra, 0x14($sp)
  /* 01959C 8001899C 0C006244 */       jal func_80018910
  /* 0195A0 800189A0 AFA40018 */        sw $a0, 0x18($sp)
  /* 0195A4 800189A4 8FAE0018 */        lw $t6, 0x18($sp)
  /* 0195A8 800189A8 8FBF0014 */        lw $ra, 0x14($sp)
  /* 0195AC 800189AC 27BD0018 */     addiu $sp, $sp, 0x18
  /* 0195B0 800189B0 004E0019 */     multu $v0, $t6
  /* 0195B4 800189B4 00001012 */      mflo $v0
  /* 0195B8 800189B8 04410003 */      bgez $v0, .L800189C8
  /* 0195BC 800189BC 00400821 */      addu $at, $v0, $zero
  /* 0195C0 800189C0 3401FFFF */       ori $at, $zero, 0xffff
  /* 0195C4 800189C4 00220821 */      addu $at, $at, $v0
  .L800189C8:
  /* 0195C8 800189C8 00011403 */       sra $v0, $at, 0x10
  /* 0195CC 800189CC 03E00008 */        jr $ra
  /* 0195D0 800189D0 00000000 */       nop 

  /* 0195D4 800189D4 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 0195D8 800189D8 AFBF0014 */        sw $ra, 0x14($sp)
  /* 0195DC 800189DC 0C00D354 */       jal osGetTime
  /* 0195E0 800189E0 00000000 */       nop 
  /* 0195E4 800189E4 8FBF0014 */        lw $ra, 0x14($sp)
  /* 0195E8 800189E8 27BD0018 */     addiu $sp, $sp, 0x18
  /* 0195EC 800189EC 306200FF */      andi $v0, $v1, 0xff
  /* 0195F0 800189F0 03E00008 */        jr $ra
  /* 0195F4 800189F4 00000000 */       nop 

  /* 0195F8 800189F8 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 0195FC 800189FC AFBF0014 */        sw $ra, 0x14($sp)
  /* 019600 80018A00 0C00D354 */       jal osGetTime
  /* 019604 80018A04 00000000 */       nop 
  /* 019608 80018A08 00002025 */        or $a0, $zero, $zero
  /* 01960C 80018A0C 0C00E546 */       jal __ull_to_f
  /* 019610 80018A10 306500FF */      andi $a1, $v1, 0xff
  /* 019614 80018A14 3C013B80 */       lui $at, (0x3B800000 >> 16) # 0.00390625
  /* 019618 80018A18 44812000 */      mtc1 $at, $f4 # 0.00390625 to cop1
  /* 01961C 80018A1C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 019620 80018A20 27BD0018 */     addiu $sp, $sp, 0x18
  /* 019624 80018A24 46040002 */     mul.s $f0, $f0, $f4
  /* 019628 80018A28 03E00008 */        jr $ra
  /* 01962C 80018A2C 00000000 */       nop 

glabel func_80018A30
  /* 019630 80018A30 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 019634 80018A34 AFBF0014 */        sw $ra, 0x14($sp)
  /* 019638 80018A38 0C00D354 */       jal osGetTime
  /* 01963C 80018A3C AFA40018 */        sw $a0, 0x18($sp)
  /* 019640 80018A40 8FB90018 */        lw $t9, 0x18($sp)
  /* 019644 80018A44 306F00FF */      andi $t7, $v1, 0xff
  /* 019648 80018A48 3C013B80 */       lui $at, (0x3B800000 >> 16) # 0.00390625
  /* 01964C 80018A4C 01F90019 */     multu $t7, $t9
  /* 019650 80018A50 44814000 */      mtc1 $at, $f8 # 0.00390625 to cop1
  /* 019654 80018A54 8FBF0014 */        lw $ra, 0x14($sp)
  /* 019658 80018A58 27BD0018 */     addiu $sp, $sp, 0x18
  /* 01965C 80018A5C 00004012 */      mflo $t0
  /* 019660 80018A60 44882000 */      mtc1 $t0, $f4
  /* 019664 80018A64 00000000 */       nop 
  /* 019668 80018A68 468021A0 */   cvt.s.w $f6, $f4
  /* 01966C 80018A6C 46083282 */     mul.s $f10, $f6, $f8
  /* 019670 80018A70 4600540D */ trunc.w.s $f16, $f10
  /* 019674 80018A74 44028000 */      mfc1 $v0, $f16
  /* 019678 80018A78 03E00008 */        jr $ra
  /* 01967C 80018A7C 00000000 */       nop 

glabel func_80018A80
  /* 019680 80018A80 00C01025 */        or $v0, $a2, $zero
  /* 019684 80018A84 10C0000A */      beqz $a2, .L80018AB0
  /* 019688 80018A88 24C6FFFF */     addiu $a2, $a2, -1
  .L80018A8C:
  /* 01968C 80018A8C 90AE0000 */       lbu $t6, ($a1)
  /* 019690 80018A90 90830000 */       lbu $v1, ($a0)
  /* 019694 80018A94 00C01025 */        or $v0, $a2, $zero
  /* 019698 80018A98 A08E0000 */        sb $t6, ($a0)
  /* 01969C 80018A9C 24840001 */     addiu $a0, $a0, 1
  /* 0196A0 80018AA0 24A50001 */     addiu $a1, $a1, 1
  /* 0196A4 80018AA4 A0A3FFFF */        sb $v1, -1($a1)
  /* 0196A8 80018AA8 14C0FFF8 */      bnez $a2, .L80018A8C
  /* 0196AC 80018AAC 24C6FFFF */     addiu $a2, $a2, -1
  .L80018AB0:
  /* 0196B0 80018AB0 03E00008 */        jr $ra
  /* 0196B4 80018AB4 00000000 */       nop 

glabel func_80018AB8
  /* 0196B8 80018AB8 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 0196BC 80018ABC AFB30020 */        sw $s3, 0x20($sp)
  /* 0196C0 80018AC0 3C138004 */       lui $s3, %hi(D_8003B948)
  /* 0196C4 80018AC4 2673B948 */     addiu $s3, $s3, %lo(D_8003B948)
  /* 0196C8 80018AC8 8E6E0000 */        lw $t6, ($s3) # D_8003B948 + 0
  /* 0196CC 80018ACC AFB50028 */        sw $s5, 0x28($sp)
  /* 0196D0 80018AD0 AFB2001C */        sw $s2, 0x1c($sp)
  /* 0196D4 80018AD4 AFB10018 */        sw $s1, 0x18($sp)
  /* 0196D8 80018AD8 AFB00014 */        sw $s0, 0x14($sp)
  /* 0196DC 80018ADC 0085082B */      sltu $at, $a0, $a1
  /* 0196E0 80018AE0 00809025 */        or $s2, $a0, $zero
  /* 0196E4 80018AE4 00A0A825 */        or $s5, $a1, $zero
  /* 0196E8 80018AE8 AFBF002C */        sw $ra, 0x2c($sp)
  /* 0196EC 80018AEC AFB40024 */        sw $s4, 0x24($sp)
  /* 0196F0 80018AF0 00808025 */        or $s0, $a0, $zero
  /* 0196F4 80018AF4 1020003E */      beqz $at, .L80018BF0
  /* 0196F8 80018AF8 00AE8821 */      addu $s1, $a1, $t6
  /* 0196FC 80018AFC 3C148004 */       lui $s4, %hi(D_8003B94C)
  /* 019700 80018B00 2694B94C */     addiu $s4, $s4, %lo(D_8003B94C)
  /* 019704 80018B04 8E6F0000 */        lw $t7, ($s3) # D_8003B948 + 0
  .L80018B08:
  /* 019708 80018B08 020F8021 */      addu $s0, $s0, $t7
  /* 01970C 80018B0C 0215082B */      sltu $at, $s0, $s5
  /* 019710 80018B10 50200009 */      beql $at, $zero, .L80018B38
  /* 019714 80018B14 8E660000 */        lw $a2, ($s3) # D_8003B948 + 0
  /* 019718 80018B18 8E990000 */        lw $t9, ($s4) # D_8003B94C + 0
  /* 01971C 80018B1C 02002025 */        or $a0, $s0, $zero
  /* 019720 80018B20 02402825 */        or $a1, $s2, $zero
  /* 019724 80018B24 0320F809 */      jalr $t9
  /* 019728 80018B28 00000000 */       nop 
  /* 01972C 80018B2C 5840FFF6 */     blezl $v0, .L80018B08
  /* 019730 80018B30 8E6F0000 */        lw $t7, ($s3) # D_8003B948 + 0
  /* 019734 80018B34 8E660000 */        lw $a2, ($s3) # D_8003B948 + 0
  .L80018B38:
  /* 019738 80018B38 02268823 */      subu $s1, $s1, $a2
  /* 01973C 80018B3C 0251082B */      sltu $at, $s2, $s1
  /* 019740 80018B40 5020000A */      beql $at, $zero, .L80018B6C
  /* 019744 80018B44 0211082B */      sltu $at, $s0, $s1
  /* 019748 80018B48 8E990000 */        lw $t9, ($s4) # D_8003B94C + 0
  /* 01974C 80018B4C 02202025 */        or $a0, $s1, $zero
  /* 019750 80018B50 02402825 */        or $a1, $s2, $zero
  /* 019754 80018B54 0320F809 */      jalr $t9
  /* 019758 80018B58 00000000 */       nop 
  /* 01975C 80018B5C 0443FFF6 */     bgezl $v0, .L80018B38
  /* 019760 80018B60 8E660000 */        lw $a2, ($s3) # D_8003B948 + 0
  /* 019764 80018B64 8E660000 */        lw $a2, ($s3) # D_8003B948 + 0
  /* 019768 80018B68 0211082B */      sltu $at, $s0, $s1
  .L80018B6C:
  /* 01976C 80018B6C 10200006 */      beqz $at, .L80018B88
  /* 019770 80018B70 02402025 */        or $a0, $s2, $zero
  /* 019774 80018B74 02002025 */        or $a0, $s0, $zero
  /* 019778 80018B78 0C0062A0 */       jal func_80018A80
  /* 01977C 80018B7C 02202825 */        or $a1, $s1, $zero
  /* 019780 80018B80 1000FFE1 */         b .L80018B08
  /* 019784 80018B84 8E6F0000 */        lw $t7, ($s3) # D_8003B948 + 0
  .L80018B88:
  /* 019788 80018B88 0C0062A0 */       jal func_80018A80
  /* 01978C 80018B8C 02202825 */        or $a1, $s1, $zero
  /* 019790 80018B90 0232C023 */      subu $t8, $s1, $s2
  /* 019794 80018B94 02B14023 */      subu $t0, $s5, $s1
  /* 019798 80018B98 0308082A */       slt $at, $t8, $t0
  /* 01979C 80018B9C 5420000A */      bnel $at, $zero, .L80018BC8
  /* 0197A0 80018BA0 8E6B0000 */        lw $t3, ($s3) # D_8003B948 + 0
  /* 0197A4 80018BA4 8E690000 */        lw $t1, ($s3) # D_8003B948 + 0
  /* 0197A8 80018BA8 02A02825 */        or $a1, $s5, $zero
  /* 0197AC 80018BAC 0C0062AE */       jal func_80018AB8
  /* 0197B0 80018BB0 02292021 */      addu $a0, $s1, $t1
  /* 0197B4 80018BB4 8E6A0000 */        lw $t2, ($s3) # D_8003B948 + 0
  /* 0197B8 80018BB8 02408025 */        or $s0, $s2, $zero
  /* 0197BC 80018BBC 10000009 */         b .L80018BE4
  /* 0197C0 80018BC0 022AA823 */      subu $s5, $s1, $t2
  /* 0197C4 80018BC4 8E6B0000 */        lw $t3, ($s3) # D_8003B948 + 0
  .L80018BC8:
  /* 0197C8 80018BC8 02402025 */        or $a0, $s2, $zero
  /* 0197CC 80018BCC 0C0062AE */       jal func_80018AB8
  /* 0197D0 80018BD0 022B2823 */      subu $a1, $s1, $t3
  /* 0197D4 80018BD4 8E660000 */        lw $a2, ($s3) # D_8003B948 + 0
  /* 0197D8 80018BD8 02269021 */      addu $s2, $s1, $a2
  /* 0197DC 80018BDC 02408025 */        or $s0, $s2, $zero
  /* 0197E0 80018BE0 02A68821 */      addu $s1, $s5, $a2
  .L80018BE4:
  /* 0197E4 80018BE4 0255082B */      sltu $at, $s2, $s5
  /* 0197E8 80018BE8 5420FFC7 */      bnel $at, $zero, .L80018B08
  /* 0197EC 80018BEC 8E6F0000 */        lw $t7, ($s3) # D_8003B948 + 0
  .L80018BF0:
  /* 0197F0 80018BF0 8FBF002C */        lw $ra, 0x2c($sp)
  /* 0197F4 80018BF4 8FB00014 */        lw $s0, 0x14($sp)
  /* 0197F8 80018BF8 8FB10018 */        lw $s1, 0x18($sp)
  /* 0197FC 80018BFC 8FB2001C */        lw $s2, 0x1c($sp)
  /* 019800 80018C00 8FB30020 */        lw $s3, 0x20($sp)
  /* 019804 80018C04 8FB40024 */        lw $s4, 0x24($sp)
  /* 019808 80018C08 8FB50028 */        lw $s5, 0x28($sp)
  /* 01980C 80018C0C 03E00008 */        jr $ra
  /* 019810 80018C10 27BD0030 */     addiu $sp, $sp, 0x30

  /* 019814 80018C14 27BDFFC0 */     addiu $sp, $sp, -0x40
  /* 019818 80018C18 AFB40028 */        sw $s4, 0x28($sp)
  /* 01981C 80018C1C AFB30024 */        sw $s3, 0x24($sp)
  /* 019820 80018C20 AFB20020 */        sw $s2, 0x20($sp)
  /* 019824 80018C24 AFB1001C */        sw $s1, 0x1c($sp)
  /* 019828 80018C28 00C09825 */        or $s3, $a2, $zero
  /* 01982C 80018C2C 00E0A025 */        or $s4, $a3, $zero
  /* 019830 80018C30 AFBF002C */        sw $ra, 0x2c($sp)
  /* 019834 80018C34 AFB00018 */        sw $s0, 0x18($sp)
  /* 019838 80018C38 AFA40040 */        sw $a0, 0x40($sp)
  /* 01983C 80018C3C AFA50044 */        sw $a1, 0x44($sp)
  /* 019840 80018C40 00809025 */        or $s2, $a0, $zero
  /* 019844 80018C44 00868821 */      addu $s1, $a0, $a2
  /* 019848 80018C48 10A00010 */      beqz $a1, .L80018C8C
  /* 01984C 80018C4C AFA00030 */        sw $zero, 0x30($sp)
  /* 019850 80018C50 24A3FFFF */     addiu $v1, $a1, -1
  /* 019854 80018C54 1060000D */      beqz $v1, .L80018C8C
  /* 019858 80018C58 2470FFFF */     addiu $s0, $v1, -1
  .L80018C5C:
  /* 01985C 80018C5C 02402025 */        or $a0, $s2, $zero
  /* 019860 80018C60 0280F809 */      jalr $s4
  /* 019864 80018C64 02202825 */        or $a1, $s1, $zero
  /* 019868 80018C68 18400004 */      blez $v0, .L80018C7C
  /* 01986C 80018C6C 02209025 */        or $s2, $s1, $zero
  /* 019870 80018C70 24180001 */     addiu $t8, $zero, 1
  /* 019874 80018C74 10000005 */         b .L80018C8C
  /* 019878 80018C78 AFB80030 */        sw $t8, 0x30($sp)
  .L80018C7C:
  /* 01987C 80018C7C 02001025 */        or $v0, $s0, $zero
  /* 019880 80018C80 02338821 */      addu $s1, $s1, $s3
  /* 019884 80018C84 1600FFF5 */      bnez $s0, .L80018C5C
  /* 019888 80018C88 2610FFFF */     addiu $s0, $s0, -1
  .L80018C8C:
  /* 01988C 80018C8C 8FB90030 */        lw $t9, 0x30($sp)
  /* 019890 80018C90 3C028004 */       lui $v0, %hi(D_8003B948)
  /* 019894 80018C94 2442B948 */     addiu $v0, $v0, %lo(D_8003B948)
  /* 019898 80018C98 1320000C */      beqz $t9, .L80018CCC
  /* 01989C 80018C9C 3C018004 */       lui $at, %hi(D_8003B94C)
  /* 0198A0 80018CA0 AC530000 */        sw $s3, ($v0) # D_8003B948 + 0
  /* 0198A4 80018CA4 8FA90044 */        lw $t1, 0x44($sp)
  /* 0198A8 80018CA8 AC34B94C */        sw $s4, %lo(D_8003B94C)($at)
  /* 0198AC 80018CAC 8C4B0000 */        lw $t3, ($v0) # D_8003B948 + 0
  /* 0198B0 80018CB0 252AFFFF */     addiu $t2, $t1, -1
  /* 0198B4 80018CB4 8FA40040 */        lw $a0, 0x40($sp)
  /* 0198B8 80018CB8 014B0019 */     multu $t2, $t3
  /* 0198BC 80018CBC 00006012 */      mflo $t4
  /* 0198C0 80018CC0 01842821 */      addu $a1, $t4, $a0
  /* 0198C4 80018CC4 0C0062AE */       jal func_80018AB8
  /* 0198C8 80018CC8 00000000 */       nop 
  .L80018CCC:
  /* 0198CC 80018CCC 8FBF002C */        lw $ra, 0x2c($sp)
  /* 0198D0 80018CD0 8FB00018 */        lw $s0, 0x18($sp)
  /* 0198D4 80018CD4 8FB1001C */        lw $s1, 0x1c($sp)
  /* 0198D8 80018CD8 8FB20020 */        lw $s2, 0x20($sp)
  /* 0198DC 80018CDC 8FB30024 */        lw $s3, 0x24($sp)
  /* 0198E0 80018CE0 8FB40028 */        lw $s4, 0x28($sp)
  /* 0198E4 80018CE4 03E00008 */        jr $ra
  /* 0198E8 80018CE8 27BD0040 */     addiu $sp, $sp, 0x40

  /* 0198EC 80018CEC 24CEFFFF */     addiu $t6, $a2, -1
  /* 0198F0 80018CF0 01C70019 */     multu $t6, $a3
  /* 0198F4 80018CF4 27BDFFC0 */     addiu $sp, $sp, -0x40
  /* 0198F8 80018CF8 AFB60030 */        sw $s6, 0x30($sp)
  /* 0198FC 80018CFC AFBE0038 */        sw $fp, 0x38($sp)
  /* 019900 80018D00 AFB5002C */        sw $s5, 0x2c($sp)
  /* 019904 80018D04 AFB40028 */        sw $s4, 0x28($sp)
  /* 019908 80018D08 00E0A025 */        or $s4, $a3, $zero
  /* 01990C 80018D0C 0080F025 */        or $fp, $a0, $zero
  /* 019910 80018D10 AFBF003C */        sw $ra, 0x3c($sp)
  /* 019914 80018D14 AFB70034 */        sw $s7, 0x34($sp)
  /* 019918 80018D18 00007812 */      mflo $t7
  /* 01991C 80018D1C 00AFB021 */      addu $s6, $a1, $t7
  /* 019920 80018D20 02C5082B */      sltu $at, $s6, $a1
  /* 019924 80018D24 AFB30024 */        sw $s3, 0x24($sp)
  /* 019928 80018D28 AFB20020 */        sw $s2, 0x20($sp)
  /* 01992C 80018D2C AFB1001C */        sw $s1, 0x1c($sp)
  /* 019930 80018D30 AFB00018 */        sw $s0, 0x18($sp)
  /* 019934 80018D34 1420002C */      bnez $at, .L80018DE8
  /* 019938 80018D38 00A0A825 */        or $s5, $a1, $zero
  /* 01993C 80018D3C 8FB70050 */        lw $s7, 0x50($sp)
  /* 019940 80018D40 00061042 */       srl $v0, $a2, 1
  .L80018D44:
  /* 019944 80018D44 1040001B */      beqz $v0, .L80018DB4
  /* 019948 80018D48 00408825 */        or $s1, $v0, $zero
  /* 01994C 80018D4C 30D20001 */      andi $s2, $a2, 1
  /* 019950 80018D50 12400003 */      beqz $s2, .L80018D60
  /* 019954 80018D54 2443FFFF */     addiu $v1, $v0, -1
  /* 019958 80018D58 10000001 */         b .L80018D60
  /* 01995C 80018D5C 00401825 */        or $v1, $v0, $zero
  .L80018D60:
  /* 019960 80018D60 00740019 */     multu $v1, $s4
  /* 019964 80018D64 03C02025 */        or $a0, $fp, $zero
  /* 019968 80018D68 0000C012 */      mflo $t8
  /* 01996C 80018D6C 03158021 */      addu $s0, $t8, $s5
  /* 019970 80018D70 02009825 */        or $s3, $s0, $zero
  /* 019974 80018D74 02E0F809 */      jalr $s7
  /* 019978 80018D78 02002825 */        or $a1, $s0, $zero
  /* 01997C 80018D7C 14400003 */      bnez $v0, .L80018D8C
  /* 019980 80018D80 02203025 */        or $a2, $s1, $zero
  /* 019984 80018D84 10000019 */         b .L80018DEC
  /* 019988 80018D88 02001025 */        or $v0, $s0, $zero
  .L80018D8C:
  /* 01998C 80018D8C 04410007 */      bgez $v0, .L80018DAC
  /* 019990 80018D90 00000000 */       nop 
  /* 019994 80018D94 12400003 */      beqz $s2, .L80018DA4
  /* 019998 80018D98 0214B023 */      subu $s6, $s0, $s4
  /* 01999C 80018D9C 1000000F */         b .L80018DDC
  /* 0199A0 80018DA0 02203025 */        or $a2, $s1, $zero
  .L80018DA4:
  /* 0199A4 80018DA4 1000000D */         b .L80018DDC
  /* 0199A8 80018DA8 2626FFFF */     addiu $a2, $s1, -1
  .L80018DAC:
  /* 0199AC 80018DAC 1000000B */         b .L80018DDC
  /* 0199B0 80018DB0 0274A821 */      addu $s5, $s3, $s4
  .L80018DB4:
  /* 0199B4 80018DB4 10C0000C */      beqz $a2, .L80018DE8
  /* 0199B8 80018DB8 03C02025 */        or $a0, $fp, $zero
  /* 0199BC 80018DBC 02E0F809 */      jalr $s7
  /* 0199C0 80018DC0 02A02825 */        or $a1, $s5, $zero
  /* 0199C4 80018DC4 10400003 */      beqz $v0, .L80018DD4
  /* 0199C8 80018DC8 02A01825 */        or $v1, $s5, $zero
  /* 0199CC 80018DCC 10000007 */         b .L80018DEC
  /* 0199D0 80018DD0 00001025 */        or $v0, $zero, $zero
  .L80018DD4:
  /* 0199D4 80018DD4 10000005 */         b .L80018DEC
  /* 0199D8 80018DD8 00601025 */        or $v0, $v1, $zero
  .L80018DDC:
  /* 0199DC 80018DDC 02D5082B */      sltu $at, $s6, $s5
  /* 0199E0 80018DE0 5020FFD8 */      beql $at, $zero, .L80018D44
  /* 0199E4 80018DE4 00061042 */       srl $v0, $a2, 1
  .L80018DE8:
  /* 0199E8 80018DE8 00001025 */        or $v0, $zero, $zero
  .L80018DEC:
  /* 0199EC 80018DEC 8FBF003C */        lw $ra, 0x3c($sp)
  /* 0199F0 80018DF0 8FB00018 */        lw $s0, 0x18($sp)
  /* 0199F4 80018DF4 8FB1001C */        lw $s1, 0x1c($sp)
  /* 0199F8 80018DF8 8FB20020 */        lw $s2, 0x20($sp)
  /* 0199FC 80018DFC 8FB30024 */        lw $s3, 0x24($sp)
  /* 019A00 80018E00 8FB40028 */        lw $s4, 0x28($sp)
  /* 019A04 80018E04 8FB5002C */        lw $s5, 0x2c($sp)
  /* 019A08 80018E08 8FB60030 */        lw $s6, 0x30($sp)
  /* 019A0C 80018E0C 8FB70034 */        lw $s7, 0x34($sp)
  /* 019A10 80018E10 8FBE0038 */        lw $fp, 0x38($sp)
  /* 019A14 80018E14 03E00008 */        jr $ra
  /* 019A18 80018E18 27BD0040 */     addiu $sp, $sp, 0x40

  /* 019A1C 80018E1C 27BDFFD0 */     addiu $sp, $sp, -0x30
  /* 019A20 80018E20 AFBF002C */        sw $ra, 0x2c($sp)
  /* 019A24 80018E24 AFB50028 */        sw $s5, 0x28($sp)
  /* 019A28 80018E28 AFB40024 */        sw $s4, 0x24($sp)
  /* 019A2C 80018E2C AFB30020 */        sw $s3, 0x20($sp)
  /* 019A30 80018E30 AFB2001C */        sw $s2, 0x1c($sp)
  /* 019A34 80018E34 AFB10018 */        sw $s1, 0x18($sp)
  /* 019A38 80018E38 AFB00014 */        sw $s0, 0x14($sp)
  /* 019A3C 80018E3C 8CCE0000 */        lw $t6, ($a2)
  /* 019A40 80018E40 00A08825 */        or $s1, $a1, $zero
  /* 019A44 80018E44 00C09825 */        or $s3, $a2, $zero
  /* 019A48 80018E48 0080A025 */        or $s4, $a0, $zero
  /* 019A4C 80018E4C 00E0A825 */        or $s5, $a3, $zero
  /* 019A50 80018E50 11C0000F */      beqz $t6, .L80018E90
  /* 019A54 80018E54 00008025 */        or $s0, $zero, $zero
  /* 019A58 80018E58 8FB20040 */        lw $s2, 0x40($sp)
  /* 019A5C 80018E5C 02802025 */        or $a0, $s4, $zero
  .L80018E60:
  /* 019A60 80018E60 0240F809 */      jalr $s2
  /* 019A64 80018E64 02202825 */        or $a1, $s1, $zero
  /* 019A68 80018E68 54400004 */      bnel $v0, $zero, .L80018E7C
  /* 019A6C 80018E6C 8E6F0000 */        lw $t7, ($s3)
  /* 019A70 80018E70 1000000F */         b .L80018EB0
  /* 019A74 80018E74 02201025 */        or $v0, $s1, $zero
  /* 019A78 80018E78 8E6F0000 */        lw $t7, ($s3)
  .L80018E7C:
  /* 019A7C 80018E7C 26100001 */     addiu $s0, $s0, 1
  /* 019A80 80018E80 02358821 */      addu $s1, $s1, $s5
  /* 019A84 80018E84 020F082B */      sltu $at, $s0, $t7
  /* 019A88 80018E88 5420FFF5 */      bnel $at, $zero, .L80018E60
  /* 019A8C 80018E8C 02802025 */        or $a0, $s4, $zero
  .L80018E90:
  /* 019A90 80018E90 02802025 */        or $a0, $s4, $zero
  /* 019A94 80018E94 02202825 */        or $a1, $s1, $zero
  /* 019A98 80018E98 0C00D0F8 */       jal memcpy
  /* 019A9C 80018E9C 02A03025 */        or $a2, $s5, $zero
  /* 019AA0 80018EA0 8E780000 */        lw $t8, ($s3)
  /* 019AA4 80018EA4 02201025 */        or $v0, $s1, $zero
  /* 019AA8 80018EA8 27190001 */     addiu $t9, $t8, 1
  /* 019AAC 80018EAC AE790000 */        sw $t9, ($s3)
  .L80018EB0:
  /* 019AB0 80018EB0 8FBF002C */        lw $ra, 0x2c($sp)
  /* 019AB4 80018EB4 8FB00014 */        lw $s0, 0x14($sp)
  /* 019AB8 80018EB8 8FB10018 */        lw $s1, 0x18($sp)
  /* 019ABC 80018EBC 8FB2001C */        lw $s2, 0x1c($sp)
  /* 019AC0 80018EC0 8FB30020 */        lw $s3, 0x20($sp)
  /* 019AC4 80018EC4 8FB40024 */        lw $s4, 0x24($sp)
  /* 019AC8 80018EC8 8FB50028 */        lw $s5, 0x28($sp)
  /* 019ACC 80018ECC 03E00008 */        jr $ra
  /* 019AD0 80018ED0 27BD0030 */     addiu $sp, $sp, 0x30

  /* 019AD4 80018ED4 00000000 */       nop 
  /* 019AD8 80018ED8 00000000 */       nop 
  /* 019ADC 80018EDC 00000000 */       nop 