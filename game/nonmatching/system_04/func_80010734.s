.section .text
glabel func_80010734
  /* 011334 80010734 3C018004 */       lui $at, %hi(D_800470AC)
  /* 011338 80010738 03E00008 */        jr $ra
  /* 01133C 8001073C AC2470AC */        sw $a0, %lo(D_800470AC)($at)

  /* 011340 80010740 03E00008 */        jr $ra
  /* 011344 80010744 00000000 */       nop 

