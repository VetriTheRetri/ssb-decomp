.section .text
glabel func_80008F44
  /* 009B44 80008F44 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 009B48 80008F48 AFBF0014 */        sw $ra, 0x14($sp)
  /* 009B4C 80008F4C AFA40020 */        sw $a0, 0x20($sp)
  /* 009B50 80008F50 0C001F81 */       jal func_80007E04
  /* 009B54 80008F54 AFA50024 */        sw $a1, 0x24($sp)
  /* 009B58 80008F58 93AE0027 */       lbu $t6, 0x27($sp)
  /* 009B5C 80008F5C AFA2001C */        sw $v0, 0x1c($sp)
  /* 009B60 80008F60 44800000 */      mtc1 $zero, $f0
  /* 009B64 80008F64 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 009B68 80008F68 44812000 */      mtc1 $at, $f4 # 1.0 to cop1
  /* 009B6C 80008F6C A0400005 */        sb $zero, 5($v0)
  /* 009B70 80008F70 AC400020 */        sw $zero, 0x20($v0)
  /* 009B74 80008F74 A04E0004 */        sb $t6, 4($v0)
  /* 009B78 80008F78 E440001C */      swc1 $f0, 0x1c($v0)
  /* 009B7C 80008F7C E4400018 */      swc1 $f0, 0x18($v0)
  /* 009B80 80008F80 E4400014 */      swc1 $f0, 0x14($v0)
  /* 009B84 80008F84 E4400010 */      swc1 $f0, 0x10($v0)
  /* 009B88 80008F88 E440000C */      swc1 $f0, 0xc($v0)
  /* 009B8C 80008F8C E4440008 */      swc1 $f4, 8($v0)
  /* 009B90 80008F90 8FA40020 */        lw $a0, 0x20($sp)
  /* 009B94 80008F94 0C001FA4 */       jal func_80007E90
  /* 009B98 80008F98 00402825 */        or $a1, $v0, $zero
  /* 009B9C 80008F9C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 009BA0 80008FA0 8FA2001C */        lw $v0, 0x1c($sp)
  /* 009BA4 80008FA4 27BD0020 */     addiu $sp, $sp, 0x20
  /* 009BA8 80008FA8 03E00008 */        jr $ra
  /* 009BAC 80008FAC 00000000 */       nop 

