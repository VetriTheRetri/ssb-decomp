.section .text
glabel func_8001B924
  /* 01C524 8001B924 44856000 */      mtc1 $a1, $f12
  /* 01C528 8001B928 44867000 */      mtc1 $a2, $f14
  /* 01C52C 8001B92C AFA7000C */        sw $a3, 0xc($sp)
  /* 01C530 8001B930 E48C0030 */      swc1 $f12, 0x30($a0)
  /* 01C534 8001B934 E48E0034 */      swc1 $f14, 0x34($a0)
  /* 01C538 8001B938 C7A4000C */      lwc1 $f4, 0xc($sp)
  /* 01C53C 8001B93C 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 01C540 8001B940 44810000 */      mtc1 $at, $f0 # 1.0 to cop1
  /* 01C544 8001B944 44801000 */      mtc1 $zero, $f2
  /* 01C548 8001B948 24070003 */     addiu $a3, $zero, 3
  /* 01C54C 8001B94C 24060002 */     addiu $a2, $zero, 2
  /* 01C550 8001B950 24050001 */     addiu $a1, $zero, 1
  /* 01C554 8001B954 00001025 */        or $v0, $zero, $zero
  /* 01C558 8001B958 00801825 */        or $v1, $a0, $zero
  /* 01C55C 8001B95C E4840038 */      swc1 $f4, 0x38($a0)
  .L8001B960:
  /* 01C560 8001B960 54400004 */      bnel $v0, $zero, .L8001B974
  /* 01C564 8001B964 E4620000 */      swc1 $f2, ($v1)
  /* 01C568 8001B968 10000002 */         b .L8001B974
  /* 01C56C 8001B96C E4600000 */      swc1 $f0, ($v1)
  /* 01C570 8001B970 E4620000 */      swc1 $f2, ($v1)
  .L8001B974:
  /* 01C574 8001B974 54450004 */      bnel $v0, $a1, .L8001B988
  /* 01C578 8001B978 E4620004 */      swc1 $f2, 4($v1)
  /* 01C57C 8001B97C 10000002 */         b .L8001B988
  /* 01C580 8001B980 E4600004 */      swc1 $f0, 4($v1)
  /* 01C584 8001B984 E4620004 */      swc1 $f2, 4($v1)
  .L8001B988:
  /* 01C588 8001B988 54460004 */      bnel $v0, $a2, .L8001B99C
  /* 01C58C 8001B98C E4620008 */      swc1 $f2, 8($v1)
  /* 01C590 8001B990 10000002 */         b .L8001B99C
  /* 01C594 8001B994 E4600008 */      swc1 $f0, 8($v1)
  /* 01C598 8001B998 E4620008 */      swc1 $f2, 8($v1)
  .L8001B99C:
  /* 01C59C 8001B99C 54470004 */      bnel $v0, $a3, .L8001B9B0
  /* 01C5A0 8001B9A0 E462000C */      swc1 $f2, 0xc($v1)
  /* 01C5A4 8001B9A4 10000002 */         b .L8001B9B0
  /* 01C5A8 8001B9A8 E460000C */      swc1 $f0, 0xc($v1)
  /* 01C5AC 8001B9AC E462000C */      swc1 $f2, 0xc($v1)
  .L8001B9B0:
  /* 01C5B0 8001B9B0 24420001 */     addiu $v0, $v0, 1
  /* 01C5B4 8001B9B4 1447FFEA */       bne $v0, $a3, .L8001B960
  /* 01C5B8 8001B9B8 24630010 */     addiu $v1, $v1, 0x10
  /* 01C5BC 8001B9BC 03E00008 */        jr $ra
  /* 01C5C0 8001B9C0 E480003C */      swc1 $f0, 0x3c($a0)

