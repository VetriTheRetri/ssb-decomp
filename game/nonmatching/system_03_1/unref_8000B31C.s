.section .text
glabel unref_8000B31C
  /* 00BF1C 8000B31C 14800003 */      bnez $a0, .L8000B32C
  /* 00BF20 8000B320 24030001 */     addiu $v1, $zero, 1
  /* 00BF24 8000B324 3C048004 */       lui $a0, %hi(D_80046A54)
  /* 00BF28 8000B328 8C846A54 */        lw $a0, %lo(D_80046A54)($a0)
  .L8000B32C:
  /* 00BF2C 8000B32C 8C820018 */        lw $v0, 0x18($a0)
  /* 00BF30 8000B330 10400008 */      beqz $v0, .L8000B354
  /* 00BF34 8000B334 00000000 */       nop 
  /* 00BF38 8000B338 8C4E0020 */        lw $t6, 0x20($v0)
  .L8000B33C:
  /* 00BF3C 8000B33C 54AE0003 */      bnel $a1, $t6, .L8000B34C
  /* 00BF40 8000B340 8C420000 */        lw $v0, ($v0)
  /* 00BF44 8000B344 A0430015 */        sb $v1, 0x15($v0)
  /* 00BF48 8000B348 8C420000 */        lw $v0, ($v0)
  .L8000B34C:
  /* 00BF4C 8000B34C 5440FFFB */      bnel $v0, $zero, .L8000B33C
  /* 00BF50 8000B350 8C4E0020 */        lw $t6, 0x20($v0)
  .L8000B354:
  /* 00BF54 8000B354 03E00008 */        jr $ra
  /* 00BF58 8000B358 00000000 */       nop 

