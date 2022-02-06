.section .rodata
glabel D_8003E650
  /* 3E250 03F250 8003E650 */
  .asciz "THREAD:%d  (%s)"
  .balign 4

glabel D_8003E660
  /* 3E260 03F260 8003E660 */
  .asciz "PC:%08XH   SR:%08XH   VA:%08XH"
  .balign 4

glabel D_8003E680
  /* 3E280 03F280 8003E680 */
  .asciz "THREAD:%d  (%s)"
  .balign 4

glabel D_8003E690
  /* 3E290 03F290 8003E690 */
  .asciz "PC:%08XH   SR:%08XH   VA:%08XH"
  .balign 4

glabel D_8003E6B0
  /* 3E2B0 03F2B0 8003E6B0 */
  .asciz "AT:%08XH   V0:%08XH   V1:%08XH"
  .balign 4

glabel D_8003E6D0
  /* 3E2D0 03F2D0 8003E6D0 */
  .asciz "A0:%08XH   A1:%08XH   A2:%08XH"
  .balign 4

glabel D_8003E6F0
  /* 3E2F0 03F2F0 8003E6F0 */
  .asciz "A3:%08XH   T0:%08XH   T1:%08XH"
  .balign 4

glabel D_8003E710
  /* 3E310 03F310 8003E710 */
  .asciz "T2:%08XH   T3:%08XH   T4:%08XH"
  .balign 4

glabel D_8003E730
  /* 3E330 03F330 8003E730 */
  .asciz "T5:%08XH   T6:%08XH   T7:%08XH"
  .balign 4

glabel D_8003E750
  /* 3E350 03F350 8003E750 */
  .asciz "S0:%08XH   S1:%08XH   S2:%08XH"
  .balign 4

glabel D_8003E770
  /* 3E370 03F370 8003E770 */
  .asciz "S3:%08XH   S4:%08XH   S5:%08XH"
  .balign 4

glabel D_8003E790
  /* 3E390 03F390 8003E790 */
  .asciz "S6:%08XH   S7:%08XH   T8:%08XH"
  .balign 4

glabel D_8003E7B0
  /* 3E3B0 03F3B0 8003E7B0 */
  .asciz "T9:%08XH   GP:%08XH   SP:%08XH"
  .balign 4

glabel D_8003E7D0
  /* 3E3D0 03F3D0 8003E7D0 */
  .asciz "S8:%08XH   RA:%08XH"
  .balign 4

glabel D_8003E7E4
  /* 3E3E4 03F3E4 8003E7E4 */
  .asciz "SP Base %08x"
  .balign 4

glabel D_8003E7F4
  /* 3E3F4 03F3F4 8003E7F4 */
  .asciz "%03d:%02x%02x%02x%02x %.3e"
  .balign 4

glabel D_8003E810
  /* 3E410 03F410 8003E810 */
  .asciz "%03d:%02x%02x%02x%02x %08x"
  .balign 4

glabel D_8003E82C
  /* 3E42C 03F42C 8003E82C */
  .asciz ":%02x%02x%02x%02x %.3e"
  .balign 4

glabel D_8003E844
  /* 3E444 03F444 8003E844 */
  .asciz ":%02x%02x%02x%02x %08x"
  .balign 4
  #.incbin "system.raw.bin", 0x3E45C, 0x4

.section .text
glabel func_80022984
  /* 023584 80022984 27BDFFC0 */     addiu $sp, $sp, -0x40
  /* 023588 80022988 AFBF003C */        sw $ra, 0x3c($sp)
  /* 02358C 8002298C AFB30038 */        sw $s3, 0x38($sp)
  /* 023590 80022990 AFB20034 */        sw $s2, 0x34($sp)
  /* 023594 80022994 AFB10030 */        sw $s1, 0x30($sp)
  /* 023598 80022998 AFB0002C */        sw $s0, 0x2c($sp)
  /* 02359C 8002299C 8C900120 */        lw $s0, 0x120($a0)
  /* 0235A0 800229A0 24010017 */     addiu $at, $zero, 0x17
  /* 0235A4 800229A4 00A08825 */        or $s1, $a1, $zero
  /* 0235A8 800229A8 00108082 */       srl $s0, $s0, 2
  /* 0235AC 800229AC 3210001F */      andi $s0, $s0, 0x1f
  /* 0235B0 800229B0 00108400 */       sll $s0, $s0, 0x10
  /* 0235B4 800229B4 00108403 */       sra $s0, $s0, 0x10
  /* 0235B8 800229B8 16010002 */       bne $s0, $at, .L800229C4
  /* 0235BC 800229BC 00809025 */        or $s2, $a0, $zero
  /* 0235C0 800229C0 24100010 */     addiu $s0, $zero, 0x10
  .L800229C4:
  /* 0235C4 800229C4 2401001F */     addiu $at, $zero, 0x1f
  /* 0235C8 800229C8 16010002 */       bne $s0, $at, .L800229D4
  /* 0235CC 800229CC 00000000 */       nop 
  /* 0235D0 800229D0 24100011 */     addiu $s0, $zero, 0x11
  .L800229D4:
  /* 0235D4 800229D4 0C00E458 */       jal osWritebackDCacheAll
  /* 0235D8 800229D8 00000000 */       nop 
  /* 0235DC 800229DC 12200023 */      beqz $s1, .L80022A6C
  /* 0235E0 800229E0 24040019 */     addiu $a0, $zero, 0x19
  /* 0235E4 800229E4 24050014 */     addiu $a1, $zero, 0x14
  /* 0235E8 800229E8 2406010E */     addiu $a2, $zero, 0x10e
  /* 0235EC 800229EC 0C0088FD */       jal func_800223F4
  /* 0235F0 800229F0 24070019 */     addiu $a3, $zero, 0x19
  /* 0235F4 800229F4 00107080 */       sll $t6, $s0, 2
  /* 0235F8 800229F8 3C0F8004 */       lui $t7, %hi(D_8003CFFC)
  /* 0235FC 800229FC 01EE7821 */      addu $t7, $t7, $t6
  /* 023600 80022A00 8DEFCFFC */        lw $t7, %lo(D_8003CFFC)($t7)
  /* 023604 80022A04 3C068004 */       lui $a2, %hi(D_8003E650)
  /* 023608 80022A08 8E470014 */        lw $a3, 0x14($s2)
  /* 02360C 80022A0C 24C6E650 */     addiu $a2, $a2, %lo(D_8003E650)
  /* 023610 80022A10 2404001E */     addiu $a0, $zero, 0x1e
  /* 023614 80022A14 24050019 */     addiu $a1, $zero, 0x19
  /* 023618 80022A18 0C008999 */       jal func_80022664
  /* 02361C 80022A1C AFAF0010 */        sw $t7, 0x10($sp)
  /* 023620 80022A20 26510020 */     addiu $s1, $s2, 0x20
  /* 023624 80022A24 8E3800F8 */        lw $t8, 0xf8($s1)
  /* 023628 80022A28 8E2700FC */        lw $a3, 0xfc($s1)
  /* 02362C 80022A2C 3C068004 */       lui $a2, %hi(D_8003E660)
  /* 023630 80022A30 AFB80010 */        sw $t8, 0x10($sp)
  /* 023634 80022A34 8E390104 */        lw $t9, 0x104($s1)
  /* 023638 80022A38 24C6E660 */     addiu $a2, $a2, %lo(D_8003E660)
  /* 02363C 80022A3C 2404001E */     addiu $a0, $zero, 0x1e
  /* 023640 80022A40 24050023 */     addiu $a1, $zero, 0x23
  /* 023644 80022A44 0C008999 */       jal func_80022664
  /* 023648 80022A48 AFB90014 */        sw $t9, 0x14($sp)
  /* 02364C 80022A4C 0C00E458 */       jal osWritebackDCacheAll
  /* 023650 80022A50 00000000 */       nop 
  /* 023654 80022A54 00002025 */        or $a0, $zero, $zero
  /* 023658 80022A58 0C008A42 */       jal func_80022908
  /* 02365C 80022A5C 00002825 */        or $a1, $zero, $zero
  /* 023660 80022A60 24042030 */     addiu $a0, $zero, 0x2030
  /* 023664 80022A64 0C008A42 */       jal func_80022908
  /* 023668 80022A68 00002825 */        or $a1, $zero, $zero
  .L80022A6C:
  /* 02366C 80022A6C 3C098004 */       lui $t1, %hi(D_8003CFFC)
  /* 023670 80022A70 2529CFFC */     addiu $t1, $t1, %lo(D_8003CFFC)
  /* 023674 80022A74 00104080 */       sll $t0, $s0, 2
  /* 023678 80022A78 01099821 */      addu $s3, $t0, $t1
  /* 02367C 80022A7C 24040019 */     addiu $a0, $zero, 0x19
  /* 023680 80022A80 24050014 */     addiu $a1, $zero, 0x14
  /* 023684 80022A84 2406010E */     addiu $a2, $zero, 0x10e
  /* 023688 80022A88 240700D2 */     addiu $a3, $zero, 0xd2
  /* 02368C 80022A8C 0C0088FD */       jal func_800223F4
  /* 023690 80022A90 26510020 */     addiu $s1, $s2, 0x20
  /* 023694 80022A94 8E6A0000 */        lw $t2, ($s3)
  /* 023698 80022A98 3C068004 */       lui $a2, %hi(D_8003E680)
  /* 02369C 80022A9C 8E470014 */        lw $a3, 0x14($s2)
  /* 0236A0 80022AA0 24C6E680 */     addiu $a2, $a2, %lo(D_8003E680)
  /* 0236A4 80022AA4 2404001E */     addiu $a0, $zero, 0x1e
  /* 0236A8 80022AA8 24050019 */     addiu $a1, $zero, 0x19
  /* 0236AC 80022AAC 0C008999 */       jal func_80022664
  /* 0236B0 80022AB0 AFAA0010 */        sw $t2, 0x10($sp)
  /* 0236B4 80022AB4 8E2B00F8 */        lw $t3, 0xf8($s1)
  /* 0236B8 80022AB8 8E2700FC */        lw $a3, 0xfc($s1)
  /* 0236BC 80022ABC 3C068004 */       lui $a2, %hi(D_8003E690)
  /* 0236C0 80022AC0 AFAB0010 */        sw $t3, 0x10($sp)
  /* 0236C4 80022AC4 8E2C0104 */        lw $t4, 0x104($s1)
  /* 0236C8 80022AC8 24C6E690 */     addiu $a2, $a2, %lo(D_8003E690)
  /* 0236CC 80022ACC 2404001E */     addiu $a0, $zero, 0x1e
  /* 0236D0 80022AD0 24050023 */     addiu $a1, $zero, 0x23
  /* 0236D4 80022AD4 0C008999 */       jal func_80022664
  /* 0236D8 80022AD8 AFAC0014 */        sw $t4, 0x14($sp)
  /* 0236DC 80022ADC 8E39000C */        lw $t9, 0xc($s1)
  /* 0236E0 80022AE0 8E270004 */        lw $a3, 4($s1)
  /* 0236E4 80022AE4 3C068004 */       lui $a2, %hi(D_8003E6B0)
  /* 0236E8 80022AE8 AFB90010 */        sw $t9, 0x10($sp)
  /* 0236EC 80022AEC 8E290014 */        lw $t1, 0x14($s1)
  /* 0236F0 80022AF0 24C6E6B0 */     addiu $a2, $a2, %lo(D_8003E6B0)
  /* 0236F4 80022AF4 2404001E */     addiu $a0, $zero, 0x1e
  /* 0236F8 80022AF8 24050032 */     addiu $a1, $zero, 0x32
  /* 0236FC 80022AFC 0C008999 */       jal func_80022664
  /* 023700 80022B00 AFA90014 */        sw $t1, 0x14($sp)
  /* 023704 80022B04 8E2F0024 */        lw $t7, 0x24($s1)
  /* 023708 80022B08 8E27001C */        lw $a3, 0x1c($s1)
  /* 02370C 80022B0C 3C068004 */       lui $a2, %hi(D_8003E6D0)
  /* 023710 80022B10 AFAF0010 */        sw $t7, 0x10($sp)
  /* 023714 80022B14 8E39002C */        lw $t9, 0x2c($s1)
  /* 023718 80022B18 24C6E6D0 */     addiu $a2, $a2, %lo(D_8003E6D0)
  /* 02371C 80022B1C 2404001E */     addiu $a0, $zero, 0x1e
  /* 023720 80022B20 2405003C */     addiu $a1, $zero, 0x3c
  /* 023724 80022B24 0C008999 */       jal func_80022664
  /* 023728 80022B28 AFB90014 */        sw $t9, 0x14($sp)
  /* 02372C 80022B2C 8E2D003C */        lw $t5, 0x3c($s1)
  /* 023730 80022B30 8E270034 */        lw $a3, 0x34($s1)
  /* 023734 80022B34 3C068004 */       lui $a2, %hi(D_8003E6F0)
  /* 023738 80022B38 AFAD0010 */        sw $t5, 0x10($sp)
  /* 02373C 80022B3C 8E2F0044 */        lw $t7, 0x44($s1)
  /* 023740 80022B40 24C6E6F0 */     addiu $a2, $a2, %lo(D_8003E6F0)
  /* 023744 80022B44 2404001E */     addiu $a0, $zero, 0x1e
  /* 023748 80022B48 24050046 */     addiu $a1, $zero, 0x46
  /* 02374C 80022B4C 0C008999 */       jal func_80022664
  /* 023750 80022B50 AFAF0014 */        sw $t7, 0x14($sp)
  /* 023754 80022B54 8E2B0054 */        lw $t3, 0x54($s1)
  /* 023758 80022B58 8E27004C */        lw $a3, 0x4c($s1)
  /* 02375C 80022B5C 3C068004 */       lui $a2, %hi(D_8003E710)
  /* 023760 80022B60 AFAB0010 */        sw $t3, 0x10($sp)
  /* 023764 80022B64 8E2D005C */        lw $t5, 0x5c($s1)
  /* 023768 80022B68 24C6E710 */     addiu $a2, $a2, %lo(D_8003E710)
  /* 02376C 80022B6C 2404001E */     addiu $a0, $zero, 0x1e
  /* 023770 80022B70 24050050 */     addiu $a1, $zero, 0x50
  /* 023774 80022B74 0C008999 */       jal func_80022664
  /* 023778 80022B78 AFAD0014 */        sw $t5, 0x14($sp)
  /* 02377C 80022B7C 8E29006C */        lw $t1, 0x6c($s1)
  /* 023780 80022B80 8E270064 */        lw $a3, 0x64($s1)
  /* 023784 80022B84 3C068004 */       lui $a2, %hi(D_8003E730)
  /* 023788 80022B88 AFA90010 */        sw $t1, 0x10($sp)
  /* 02378C 80022B8C 8E2B0074 */        lw $t3, 0x74($s1)
  /* 023790 80022B90 24C6E730 */     addiu $a2, $a2, %lo(D_8003E730)
  /* 023794 80022B94 2404001E */     addiu $a0, $zero, 0x1e
  /* 023798 80022B98 2405005A */     addiu $a1, $zero, 0x5a
  /* 02379C 80022B9C 0C008999 */       jal func_80022664
  /* 0237A0 80022BA0 AFAB0014 */        sw $t3, 0x14($sp)
  /* 0237A4 80022BA4 8E390084 */        lw $t9, 0x84($s1)
  /* 0237A8 80022BA8 8E27007C */        lw $a3, 0x7c($s1)
  /* 0237AC 80022BAC 3C068004 */       lui $a2, %hi(D_8003E750)
  /* 0237B0 80022BB0 AFB90010 */        sw $t9, 0x10($sp)
  /* 0237B4 80022BB4 8E29008C */        lw $t1, 0x8c($s1)
  /* 0237B8 80022BB8 24C6E750 */     addiu $a2, $a2, %lo(D_8003E750)
  /* 0237BC 80022BBC 2404001E */     addiu $a0, $zero, 0x1e
  /* 0237C0 80022BC0 24050064 */     addiu $a1, $zero, 0x64
  /* 0237C4 80022BC4 0C008999 */       jal func_80022664
  /* 0237C8 80022BC8 AFA90014 */        sw $t1, 0x14($sp)
  /* 0237CC 80022BCC 8E2F009C */        lw $t7, 0x9c($s1)
  /* 0237D0 80022BD0 8E270094 */        lw $a3, 0x94($s1)
  /* 0237D4 80022BD4 3C068004 */       lui $a2, %hi(D_8003E770)
  /* 0237D8 80022BD8 AFAF0010 */        sw $t7, 0x10($sp)
  /* 0237DC 80022BDC 8E3900A4 */        lw $t9, 0xa4($s1)
  /* 0237E0 80022BE0 24C6E770 */     addiu $a2, $a2, %lo(D_8003E770)
  /* 0237E4 80022BE4 2404001E */     addiu $a0, $zero, 0x1e
  /* 0237E8 80022BE8 2405006E */     addiu $a1, $zero, 0x6e
  /* 0237EC 80022BEC 0C008999 */       jal func_80022664
  /* 0237F0 80022BF0 AFB90014 */        sw $t9, 0x14($sp)
  /* 0237F4 80022BF4 8E2D00B4 */        lw $t5, 0xb4($s1)
  /* 0237F8 80022BF8 8E2700AC */        lw $a3, 0xac($s1)
  /* 0237FC 80022BFC 3C068004 */       lui $a2, %hi(D_8003E790)
  /* 023800 80022C00 AFAD0010 */        sw $t5, 0x10($sp)
  /* 023804 80022C04 8E2F00BC */        lw $t7, 0xbc($s1)
  /* 023808 80022C08 24C6E790 */     addiu $a2, $a2, %lo(D_8003E790)
  /* 02380C 80022C0C 2404001E */     addiu $a0, $zero, 0x1e
  /* 023810 80022C10 24050078 */     addiu $a1, $zero, 0x78
  /* 023814 80022C14 0C008999 */       jal func_80022664
  /* 023818 80022C18 AFAF0014 */        sw $t7, 0x14($sp)
  /* 02381C 80022C1C 8E2B00CC */        lw $t3, 0xcc($s1)
  /* 023820 80022C20 8E2700C4 */        lw $a3, 0xc4($s1)
  /* 023824 80022C24 3C068004 */       lui $a2, %hi(D_8003E7B0)
  /* 023828 80022C28 AFAB0010 */        sw $t3, 0x10($sp)
  /* 02382C 80022C2C 8E2D00D4 */        lw $t5, 0xd4($s1)
  /* 023830 80022C30 24C6E7B0 */     addiu $a2, $a2, %lo(D_8003E7B0)
  /* 023834 80022C34 2404001E */     addiu $a0, $zero, 0x1e
  /* 023838 80022C38 24050082 */     addiu $a1, $zero, 0x82
  /* 02383C 80022C3C 0C008999 */       jal func_80022664
  /* 023840 80022C40 AFAD0014 */        sw $t5, 0x14($sp)
  /* 023844 80022C44 8E2900E4 */        lw $t1, 0xe4($s1)
  /* 023848 80022C48 3C068004 */       lui $a2, %hi(D_8003E7D0)
  /* 02384C 80022C4C 8E2700DC */        lw $a3, 0xdc($s1)
  /* 023850 80022C50 24C6E7D0 */     addiu $a2, $a2, %lo(D_8003E7D0)
  /* 023854 80022C54 2404001E */     addiu $a0, $zero, 0x1e
  /* 023858 80022C58 2405008C */     addiu $a1, $zero, 0x8c
  /* 02385C 80022C5C 0C008999 */       jal func_80022664
  /* 023860 80022C60 AFA90010 */        sw $t1, 0x10($sp)
  /* 023864 80022C64 0C008A1F */       jal func_8002287C
  /* 023868 80022C68 8E24010C */        lw $a0, 0x10c($s1)
  /* 02386C 80022C6C 2404001E */     addiu $a0, $zero, 0x1e
  /* 023870 80022C70 240500AA */     addiu $a1, $zero, 0xaa
  /* 023874 80022C74 00003025 */        or $a2, $zero, $zero
  /* 023878 80022C78 0C0089FD */       jal func_800227F4
  /* 02387C 80022C7C 26270114 */     addiu $a3, $s1, 0x114
  /* 023880 80022C80 24040078 */     addiu $a0, $zero, 0x78
  /* 023884 80022C84 240500AA */     addiu $a1, $zero, 0xaa
  /* 023888 80022C88 24060002 */     addiu $a2, $zero, 2
  /* 02388C 80022C8C 0C0089FD */       jal func_800227F4
  /* 023890 80022C90 2627011C */     addiu $a3, $s1, 0x11c
  /* 023894 80022C94 240400D2 */     addiu $a0, $zero, 0xd2
  /* 023898 80022C98 240500AA */     addiu $a1, $zero, 0xaa
  /* 02389C 80022C9C 24060004 */     addiu $a2, $zero, 4
  /* 0238A0 80022CA0 0C0089FD */       jal func_800227F4
  /* 0238A4 80022CA4 26270124 */     addiu $a3, $s1, 0x124
  /* 0238A8 80022CA8 2404001E */     addiu $a0, $zero, 0x1e
  /* 0238AC 80022CAC 240500B4 */     addiu $a1, $zero, 0xb4
  /* 0238B0 80022CB0 24060006 */     addiu $a2, $zero, 6
  /* 0238B4 80022CB4 0C0089FD */       jal func_800227F4
  /* 0238B8 80022CB8 2627012C */     addiu $a3, $s1, 0x12c
  /* 0238BC 80022CBC 24040078 */     addiu $a0, $zero, 0x78
  /* 0238C0 80022CC0 240500B4 */     addiu $a1, $zero, 0xb4
  /* 0238C4 80022CC4 24060008 */     addiu $a2, $zero, 8
  /* 0238C8 80022CC8 0C0089FD */       jal func_800227F4
  /* 0238CC 80022CCC 26270134 */     addiu $a3, $s1, 0x134
  /* 0238D0 80022CD0 240400D2 */     addiu $a0, $zero, 0xd2
  /* 0238D4 80022CD4 240500B4 */     addiu $a1, $zero, 0xb4
  /* 0238D8 80022CD8 2406000A */     addiu $a2, $zero, 0xa
  /* 0238DC 80022CDC 0C0089FD */       jal func_800227F4
  /* 0238E0 80022CE0 2627013C */     addiu $a3, $s1, 0x13c
  /* 0238E4 80022CE4 2404001E */     addiu $a0, $zero, 0x1e
  /* 0238E8 80022CE8 240500BE */     addiu $a1, $zero, 0xbe
  /* 0238EC 80022CEC 2406000C */     addiu $a2, $zero, 0xc
  /* 0238F0 80022CF0 0C0089FD */       jal func_800227F4
  /* 0238F4 80022CF4 26270144 */     addiu $a3, $s1, 0x144
  /* 0238F8 80022CF8 24040078 */     addiu $a0, $zero, 0x78
  /* 0238FC 80022CFC 240500BE */     addiu $a1, $zero, 0xbe
  /* 023900 80022D00 2406000E */     addiu $a2, $zero, 0xe
  /* 023904 80022D04 0C0089FD */       jal func_800227F4
  /* 023908 80022D08 2627014C */     addiu $a3, $s1, 0x14c
  /* 02390C 80022D0C 240400D2 */     addiu $a0, $zero, 0xd2
  /* 023910 80022D10 240500BE */     addiu $a1, $zero, 0xbe
  /* 023914 80022D14 24060010 */     addiu $a2, $zero, 0x10
  /* 023918 80022D18 0C0089FD */       jal func_800227F4
  /* 02391C 80022D1C 26270154 */     addiu $a3, $s1, 0x154
  /* 023920 80022D20 2404001E */     addiu $a0, $zero, 0x1e
  /* 023924 80022D24 240500C8 */     addiu $a1, $zero, 0xc8
  /* 023928 80022D28 24060012 */     addiu $a2, $zero, 0x12
  /* 02392C 80022D2C 0C0089FD */       jal func_800227F4
  /* 023930 80022D30 2627015C */     addiu $a3, $s1, 0x15c
  /* 023934 80022D34 24040078 */     addiu $a0, $zero, 0x78
  /* 023938 80022D38 240500C8 */     addiu $a1, $zero, 0xc8
  /* 02393C 80022D3C 24060014 */     addiu $a2, $zero, 0x14
  /* 023940 80022D40 0C0089FD */       jal func_800227F4
  /* 023944 80022D44 26270164 */     addiu $a3, $s1, 0x164
  /* 023948 80022D48 240400D2 */     addiu $a0, $zero, 0xd2
  /* 02394C 80022D4C 240500C8 */     addiu $a1, $zero, 0xc8
  /* 023950 80022D50 24060016 */     addiu $a2, $zero, 0x16
  /* 023954 80022D54 0C0089FD */       jal func_800227F4
  /* 023958 80022D58 2627016C */     addiu $a3, $s1, 0x16c
  /* 02395C 80022D5C 2404001E */     addiu $a0, $zero, 0x1e
  /* 023960 80022D60 240500D2 */     addiu $a1, $zero, 0xd2
  /* 023964 80022D64 24060018 */     addiu $a2, $zero, 0x18
  /* 023968 80022D68 0C0089FD */       jal func_800227F4
  /* 02396C 80022D6C 26270174 */     addiu $a3, $s1, 0x174
  /* 023970 80022D70 24040078 */     addiu $a0, $zero, 0x78
  /* 023974 80022D74 240500D2 */     addiu $a1, $zero, 0xd2
  /* 023978 80022D78 2406001A */     addiu $a2, $zero, 0x1a
  /* 02397C 80022D7C 0C0089FD */       jal func_800227F4
  /* 023980 80022D80 2627017C */     addiu $a3, $s1, 0x17c
  /* 023984 80022D84 240400D2 */     addiu $a0, $zero, 0xd2
  /* 023988 80022D88 240500D2 */     addiu $a1, $zero, 0xd2
  /* 02398C 80022D8C 2406001C */     addiu $a2, $zero, 0x1c
  /* 023990 80022D90 0C0089FD */       jal func_800227F4
  /* 023994 80022D94 26270184 */     addiu $a3, $s1, 0x184
  /* 023998 80022D98 2404001E */     addiu $a0, $zero, 0x1e
  /* 02399C 80022D9C 240500DC */     addiu $a1, $zero, 0xdc
  /* 0239A0 80022DA0 2406001E */     addiu $a2, $zero, 0x1e
  /* 0239A4 80022DA4 0C0089FD */       jal func_800227F4
  /* 0239A8 80022DA8 2627018C */     addiu $a3, $s1, 0x18c
  /* 0239AC 80022DAC 0C00E458 */       jal osWritebackDCacheAll
  /* 0239B0 80022DB0 00000000 */       nop 
  /* 0239B4 80022DB4 00002025 */        or $a0, $zero, $zero
  /* 0239B8 80022DB8 0C008A42 */       jal func_80022908
  /* 0239BC 80022DBC 00002825 */        or $a1, $zero, $zero
  /* 0239C0 80022DC0 24042030 */     addiu $a0, $zero, 0x2030
  /* 0239C4 80022DC4 0C008A42 */       jal func_80022908
  /* 0239C8 80022DC8 00002825 */        or $a1, $zero, $zero
  /* 0239CC 80022DCC 24040019 */     addiu $a0, $zero, 0x19
  /* 0239D0 80022DD0 24050014 */     addiu $a1, $zero, 0x14
  /* 0239D4 80022DD4 2406010E */     addiu $a2, $zero, 0x10e
  /* 0239D8 80022DD8 0C0088FD */       jal func_800223F4
  /* 0239DC 80022DDC 240700D2 */     addiu $a3, $zero, 0xd2
  /* 0239E0 80022DE0 8E2700D4 */        lw $a3, 0xd4($s1)
  /* 0239E4 80022DE4 3C068004 */       lui $a2, %hi(D_8003E7E4)
  /* 0239E8 80022DE8 24C6E7E4 */     addiu $a2, $a2, %lo(D_8003E7E4)
  /* 0239EC 80022DEC 2404001A */     addiu $a0, $zero, 0x1a
  /* 0239F0 80022DF0 24050014 */     addiu $a1, $zero, 0x14
  /* 0239F4 80022DF4 0C008999 */       jal func_80022664
  /* 0239F8 80022DF8 00E08025 */        or $s0, $a3, $zero
  /* 0239FC 80022DFC 2411001E */     addiu $s1, $zero, 0x1e
  /* 023A00 80022E00 00009025 */        or $s2, $zero, $zero
  /* 023A04 80022E04 3C137F80 */       lui $s3, 0x7f80
  .L80022E08:
  /* 023A08 80022E08 8E030000 */        lw $v1, ($s0)
  /* 023A0C 80022E0C 00731024 */       and $v0, $v1, $s3
  /* 023A10 80022E10 000215C2 */       srl $v0, $v0, 0x17
  /* 023A14 80022E14 2442FF81 */     addiu $v0, $v0, -0x7f
  /* 023A18 80022E18 2841FF82 */      slti $at, $v0, -0x7e
  /* 023A1C 80022E1C 14200003 */      bnez $at, .L80022E2C
  /* 023A20 80022E20 28410080 */      slti $at, $v0, 0x80
  /* 023A24 80022E24 54200004 */      bnel $at, $zero, .L80022E38
  /* 023A28 80022E28 920C0000 */       lbu $t4, ($s0)
  .L80022E2C:
  /* 023A2C 80022E2C 54600015 */      bnel $v1, $zero, .L80022E84
  /* 023A30 80022E30 92190000 */       lbu $t9, ($s0)
  /* 023A34 80022E34 920C0000 */       lbu $t4, ($s0)
  .L80022E38:
  /* 023A38 80022E38 3C068004 */       lui $a2, %hi(D_8003E7F4)
  /* 023A3C 80022E3C 24C6E7F4 */     addiu $a2, $a2, %lo(D_8003E7F4)
  /* 023A40 80022E40 AFAC0010 */        sw $t4, 0x10($sp)
  /* 023A44 80022E44 920D0001 */       lbu $t5, 1($s0)
  /* 023A48 80022E48 2404001A */     addiu $a0, $zero, 0x1a
  /* 023A4C 80022E4C 02202825 */        or $a1, $s1, $zero
  /* 023A50 80022E50 AFAD0014 */        sw $t5, 0x14($sp)
  /* 023A54 80022E54 920E0002 */       lbu $t6, 2($s0)
  /* 023A58 80022E58 02403825 */        or $a3, $s2, $zero
  /* 023A5C 80022E5C AFAE0018 */        sw $t6, 0x18($sp)
  /* 023A60 80022E60 92180003 */       lbu $t8, 3($s0)
  /* 023A64 80022E64 AFB8001C */        sw $t8, 0x1c($sp)
  /* 023A68 80022E68 C6040000 */      lwc1 $f4, ($s0)
  /* 023A6C 80022E6C 460021A1 */   cvt.d.s $f6, $f4
  /* 023A70 80022E70 0C008999 */       jal func_80022664
  /* 023A74 80022E74 F7A60020 */      sdc1 $f6, 0x20($sp)
  /* 023A78 80022E78 10000011 */         b .L80022EC0
  /* 023A7C 80022E7C 8E030004 */        lw $v1, 4($s0)
  /* 023A80 80022E80 92190000 */       lbu $t9, ($s0)
  .L80022E84:
  /* 023A84 80022E84 3C068004 */       lui $a2, %hi(D_8003E810)
  /* 023A88 80022E88 24C6E810 */     addiu $a2, $a2, %lo(D_8003E810)
  /* 023A8C 80022E8C AFB90010 */        sw $t9, 0x10($sp)
  /* 023A90 80022E90 92080001 */       lbu $t0, 1($s0)
  /* 023A94 80022E94 2404001A */     addiu $a0, $zero, 0x1a
  /* 023A98 80022E98 02202825 */        or $a1, $s1, $zero
  /* 023A9C 80022E9C AFA80014 */        sw $t0, 0x14($sp)
  /* 023AA0 80022EA0 92090002 */       lbu $t1, 2($s0)
  /* 023AA4 80022EA4 02403825 */        or $a3, $s2, $zero
  /* 023AA8 80022EA8 AFA90018 */        sw $t1, 0x18($sp)
  /* 023AAC 80022EAC 920F0003 */       lbu $t7, 3($s0)
  /* 023AB0 80022EB0 AFA30020 */        sw $v1, 0x20($sp)
  /* 023AB4 80022EB4 0C008999 */       jal func_80022664
  /* 023AB8 80022EB8 AFAF001C */        sw $t7, 0x1c($sp)
  /* 023ABC 80022EBC 8E030004 */        lw $v1, 4($s0)
  .L80022EC0:
  /* 023AC0 80022EC0 26100004 */     addiu $s0, $s0, 4
  /* 023AC4 80022EC4 00731024 */       and $v0, $v1, $s3
  /* 023AC8 80022EC8 000215C2 */       srl $v0, $v0, 0x17
  /* 023ACC 80022ECC 2442FF81 */     addiu $v0, $v0, -0x7f
  /* 023AD0 80022ED0 2841FF82 */      slti $at, $v0, -0x7e
  /* 023AD4 80022ED4 14200003 */      bnez $at, .L80022EE4
  /* 023AD8 80022ED8 28410080 */      slti $at, $v0, 0x80
  /* 023ADC 80022EDC 54200004 */      bnel $at, $zero, .L80022EF0
  /* 023AE0 80022EE0 920A0001 */       lbu $t2, 1($s0)
  .L80022EE4:
  /* 023AE4 80022EE4 14600012 */      bnez $v1, .L80022F30
  /* 023AE8 80022EE8 240400AC */     addiu $a0, $zero, 0xac
  /* 023AEC 80022EEC 920A0001 */       lbu $t2, 1($s0)
  .L80022EF0:
  /* 023AF0 80022EF0 92070000 */       lbu $a3, ($s0)
  /* 023AF4 80022EF4 3C068004 */       lui $a2, %hi(D_8003E82C)
  /* 023AF8 80022EF8 AFAA0010 */        sw $t2, 0x10($sp)
  /* 023AFC 80022EFC 920B0002 */       lbu $t3, 2($s0)
  /* 023B00 80022F00 24C6E82C */     addiu $a2, $a2, %lo(D_8003E82C)
  /* 023B04 80022F04 240400AC */     addiu $a0, $zero, 0xac
  /* 023B08 80022F08 AFAB0014 */        sw $t3, 0x14($sp)
  /* 023B0C 80022F0C 920C0003 */       lbu $t4, 3($s0)
  /* 023B10 80022F10 02202825 */        or $a1, $s1, $zero
  /* 023B14 80022F14 AFAC0018 */        sw $t4, 0x18($sp)
  /* 023B18 80022F18 C6080000 */      lwc1 $f8, ($s0)
  /* 023B1C 80022F1C 460042A1 */   cvt.d.s $f10, $f8
  /* 023B20 80022F20 0C008999 */       jal func_80022664
  /* 023B24 80022F24 F7AA0020 */      sdc1 $f10, 0x20($sp)
  /* 023B28 80022F28 1000000E */         b .L80022F64
  /* 023B2C 80022F2C 26520008 */     addiu $s2, $s2, 8
  .L80022F30:
  /* 023B30 80022F30 920D0001 */       lbu $t5, 1($s0)
  /* 023B34 80022F34 92070000 */       lbu $a3, ($s0)
  /* 023B38 80022F38 3C068004 */       lui $a2, %hi(D_8003E844)
  /* 023B3C 80022F3C AFAD0010 */        sw $t5, 0x10($sp)
  /* 023B40 80022F40 920E0002 */       lbu $t6, 2($s0)
  /* 023B44 80022F44 24C6E844 */     addiu $a2, $a2, %lo(D_8003E844)
  /* 023B48 80022F48 02202825 */        or $a1, $s1, $zero
  /* 023B4C 80022F4C AFAE0014 */        sw $t6, 0x14($sp)
  /* 023B50 80022F50 92180003 */       lbu $t8, 3($s0)
  /* 023B54 80022F54 AFA3001C */        sw $v1, 0x1c($sp)
  /* 023B58 80022F58 0C008999 */       jal func_80022664
  /* 023B5C 80022F5C AFB80018 */        sw $t8, 0x18($sp)
  /* 023B60 80022F60 26520008 */     addiu $s2, $s2, 8
  .L80022F64:
  /* 023B64 80022F64 24010098 */     addiu $at, $zero, 0x98
  /* 023B68 80022F68 2631000A */     addiu $s1, $s1, 0xa
  /* 023B6C 80022F6C 1641FFA6 */       bne $s2, $at, .L80022E08
  /* 023B70 80022F70 26100004 */     addiu $s0, $s0, 4
  /* 023B74 80022F74 0C00E458 */       jal osWritebackDCacheAll
  /* 023B78 80022F78 00000000 */       nop 
  /* 023B7C 80022F7C 8FBF003C */        lw $ra, 0x3c($sp)
  /* 023B80 80022F80 8FB0002C */        lw $s0, 0x2c($sp)
  /* 023B84 80022F84 8FB10030 */        lw $s1, 0x30($sp)
  /* 023B88 80022F88 8FB20034 */        lw $s2, 0x34($sp)
  /* 023B8C 80022F8C 8FB30038 */        lw $s3, 0x38($sp)
  /* 023B90 80022F90 03E00008 */        jr $ra
  /* 023B94 80022F94 27BD0040 */     addiu $sp, $sp, 0x40

