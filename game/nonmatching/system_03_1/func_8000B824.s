.section .text
glabel func_8000B824
  /* 00C424 8000B824 27BDFFD8 */     addiu $sp, $sp, -0x28
  /* 00C428 8000B828 AFBF0024 */        sw $ra, 0x24($sp)
  /* 00C42C 8000B82C AFB00020 */        sw $s0, 0x20($sp)
  /* 00C430 8000B830 0C00265A */       jal func_80009968
  /* 00C434 8000B834 30C600FF */      andi $a2, $a2, 0xff
  /* 00C438 8000B838 14400003 */      bnez $v0, .L8000B848
  /* 00C43C 8000B83C 00408025 */        or $s0, $v0, $zero
  /* 00C440 8000B840 10000019 */         b .L8000B8A8
  /* 00C444 8000B844 00001025 */        or $v0, $zero, $zero
  .L8000B848:
  /* 00C448 8000B848 8FAE0044 */        lw $t6, 0x44($sp)
  /* 00C44C 8000B84C 02002025 */        or $a0, $s0, $zero
  /* 00C450 8000B850 8FA50038 */        lw $a1, 0x38($sp)
  /* 00C454 8000B854 93A6003F */       lbu $a2, 0x3f($sp)
  /* 00C458 8000B858 8FA70040 */        lw $a3, 0x40($sp)
  /* 00C45C 8000B85C 0C00277D */       jal func_80009DF4
  /* 00C460 8000B860 AFAE0010 */        sw $t6, 0x10($sp)
  /* 00C464 8000B864 02002025 */        or $a0, $s0, $zero
  /* 00C468 8000B868 0C0024B4 */       jal func_800092D0
  /* 00C46C 8000B86C 8FA50048 */        lw $a1, 0x48($sp)
  /* 00C470 8000B870 8FAF004C */        lw $t7, 0x4c($sp)
  /* 00C474 8000B874 00402025 */        or $a0, $v0, $zero
  /* 00C478 8000B878 51E00004 */      beql $t7, $zero, .L8000B88C
  /* 00C47C 8000B87C 8FA50054 */        lw $a1, 0x54($sp)
  /* 00C480 8000B880 0C002CFB */       jal func_8000B3EC
  /* 00C484 8000B884 00000000 */       nop 
  /* 00C488 8000B888 8FA50054 */        lw $a1, 0x54($sp)
  .L8000B88C:
  /* 00C48C 8000B88C 02002025 */        or $a0, $s0, $zero
  /* 00C490 8000B890 93A60053 */       lbu $a2, 0x53($sp)
  /* 00C494 8000B894 50A00004 */      beql $a1, $zero, .L8000B8A8
  /* 00C498 8000B898 02001025 */        or $v0, $s0, $zero
  /* 00C49C 8000B89C 0C002062 */       jal func_80008188
  /* 00C4A0 8000B8A0 8FA70058 */        lw $a3, 0x58($sp)
  /* 00C4A4 8000B8A4 02001025 */        or $v0, $s0, $zero
  .L8000B8A8:
  /* 00C4A8 8000B8A8 8FBF0024 */        lw $ra, 0x24($sp)
  /* 00C4AC 8000B8AC 8FB00020 */        lw $s0, 0x20($sp)
  /* 00C4B0 8000B8B0 27BD0028 */     addiu $sp, $sp, 0x28
  /* 00C4B4 8000B8B4 03E00008 */        jr $ra
  /* 00C4B8 8000B8B8 00000000 */       nop 

