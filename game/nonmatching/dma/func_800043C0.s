.section .text
glabel func_800043C0
  /* 004FC0 800043C0 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 004FC4 800043C4 3C028004 */       lui $v0, %hi(D_80045268)
  /* 004FC8 800043C8 AFBF0014 */        sw $ra, 0x14($sp)
  /* 004FCC 800043CC AFA40020 */        sw $a0, 0x20($sp)
  /* 004FD0 800043D0 AFA50024 */        sw $a1, 0x24($sp)
  /* 004FD4 800043D4 24425268 */     addiu $v0, $v0, %lo(D_80045268)
  /* 004FD8 800043D8 00001825 */        or $v1, $zero, $zero
  .L800043DC:
  /* 004FDC 800043DC 8C4E0000 */        lw $t6, ($v0) # D_80045268 + 0
  /* 004FE0 800043E0 51C00006 */      beql $t6, $zero, .L800043FC
  /* 004FE4 800043E4 24010004 */     addiu $at, $zero, 4
  /* 004FE8 800043E8 24630001 */     addiu $v1, $v1, 1
  /* 004FEC 800043EC 28610004 */      slti $at, $v1, 4
  /* 004FF0 800043F0 1420FFFA */      bnez $at, .L800043DC
  /* 004FF4 800043F4 24420018 */     addiu $v0, $v0, 0x18
  /* 004FF8 800043F8 24010004 */     addiu $at, $zero, 4
  .L800043FC:
  /* 004FFC 800043FC 1461000E */       bne $v1, $at, .L80004438
  /* 005000 80004400 AFA3001C */        sw $v1, 0x1c($sp)
  /* 005004 80004404 3C048004 */       lui $a0, %hi(D_80045160)
  /* 005008 80004408 24845160 */     addiu $a0, $a0, %lo(D_80045160)
  /* 00500C 8000440C 27A5001C */     addiu $a1, $sp, 0x1c
  /* 005010 80004410 0C00C084 */       jal osRecvMesg
  /* 005014 80004414 24060001 */     addiu $a2, $zero, 1
  /* 005018 80004418 8FA3001C */        lw $v1, 0x1c($sp)
  /* 00501C 8000441C 3C188004 */       lui $t8, %hi(D_80045268)
  /* 005020 80004420 27185268 */     addiu $t8, $t8, %lo(D_80045268)
  /* 005024 80004424 00037880 */       sll $t7, $v1, 2
  /* 005028 80004428 01E37823 */      subu $t7, $t7, $v1
  /* 00502C 8000442C 000F78C0 */       sll $t7, $t7, 3
  /* 005030 80004430 10000003 */         b .L80004440
  /* 005034 80004434 01F81021 */      addu $v0, $t7, $t8
  .L80004438:
  /* 005038 80004438 24190001 */     addiu $t9, $zero, 1
  /* 00503C 8000443C AC590000 */        sw $t9, ($v0)
  .L80004440:
  /* 005040 80004440 8FA80020 */        lw $t0, 0x20($sp)
  /* 005044 80004444 8FA90024 */        lw $t1, 0x24($sp)
  /* 005048 80004448 3C048004 */       lui $a0, %hi(D_80045138)
  /* 00504C 8000444C 24845138 */     addiu $a0, $a0, %lo(D_80045138)
  /* 005050 80004450 24450004 */     addiu $a1, $v0, 4
  /* 005054 80004454 00003025 */        or $a2, $zero, $zero
  /* 005058 80004458 AC480010 */        sw $t0, 0x10($v0)
  /* 00505C 8000445C 0C00C000 */       jal osSendMesg
  /* 005060 80004460 AC490014 */        sw $t1, 0x14($v0)
  /* 005064 80004464 8FBF0014 */        lw $ra, 0x14($sp)
  /* 005068 80004468 27BD0020 */     addiu $sp, $sp, 0x20
  /* 00506C 8000446C 03E00008 */        jr $ra
  /* 005070 80004470 00000000 */       nop 

