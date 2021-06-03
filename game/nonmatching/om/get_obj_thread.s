.section .rodata

glabel D_8003D930
  /* 3D530 03E530 8003D930 */
  .asciz "om : couldn\'t get GObjThread\n"
  .balign 4

.section .text
glabel get_obj_thread
  /* 007FE0 800073E0 3C068004 */       lui $a2, %hi(sObjThreadHead)
  /* 007FE4 800073E4 24C666B0 */     addiu $a2, $a2, %lo(sObjThreadHead)
  /* 007FE8 800073E8 8CC30000 */        lw $v1, ($a2) # sObjThreadHead + 0
  /* 007FEC 800073EC 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 007FF0 800073F0 AFBF0014 */        sw $ra, 0x14($sp)
  /* 007FF4 800073F4 14600008 */      bnez $v1, .L80007418
  /* 007FF8 800073F8 240401C0 */     addiu $a0, $zero, 0x1c0
  /* 007FFC 800073FC 0C001260 */       jal func_80004980
  /* 008000 80007400 24050008 */     addiu $a1, $zero, 8
  /* 008004 80007404 3C068004 */       lui $a2, %hi(sObjThreadHead)
  /* 008008 80007408 24C666B0 */     addiu $a2, $a2, %lo(sObjThreadHead)
  /* 00800C 8000740C ACC20000 */        sw $v0, ($a2) # sObjThreadHead + 0
  /* 008010 80007410 AC400000 */        sw $zero, ($v0)
  /* 008014 80007414 8CC30000 */        lw $v1, ($a2) # sObjThreadHead + 0
  .L80007418:
  /* 008018 80007418 14600006 */      bnez $v1, .L80007434
  /* 00801C 8000741C 3C058004 */       lui $a1, %hi(sObjThreadsActive)
  /* 008020 80007420 3C048004 */       lui $a0, %hi(D_8003D930)
  /* 008024 80007424 0C008D89 */       jal fatal_printf
  /* 008028 80007428 2484D930 */     addiu $a0, $a0, %lo(D_8003D930)
  .L8000742C:
  /* 00802C 8000742C 1000FFFF */         b .L8000742C
  /* 008030 80007430 00000000 */       nop 
  .L80007434:
  /* 008034 80007434 24A566B4 */     addiu $a1, $a1, %lo(sObjThreadsActive)
  /* 008038 80007438 8CB80000 */        lw $t8, ($a1)
  /* 00803C 8000743C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 008040 80007440 8C6F0000 */        lw $t7, ($v1)
  /* 008044 80007444 27190001 */     addiu $t9, $t8, 1
  /* 008048 80007448 ACB90000 */        sw $t9, ($a1)
  /* 00804C 8000744C 27BD0018 */     addiu $sp, $sp, 0x18
  /* 008050 80007450 00601025 */        or $v0, $v1, $zero
  /* 008054 80007454 03E00008 */        jr $ra
  /* 008058 80007458 ACCF0000 */        sw $t7, ($a2)
