.include "macros.inc"

.section .rodata

# This probably isn't fully correct, but will have to do until more files are
# split from system.s

#libultra rodata start?

glabel jtbl_8003E870
  /* 3E470 03F470 8003E870 */  .4byte jtgt_80026C50
  /* 3E474 03F474 8003E874 */  .4byte jtgt_80026C78
  /* 3E478 03F478 8003E878 */  .4byte jtgt_80026CB0
  /* 3E47C 03F47C 8003E87C */  .4byte jtgt_80026CE0
  /* 3E480 03F480 8003E880 */  .4byte jtgt_80026CF4
  /* 3E484 03F484 8003E884 */  .4byte jtgt_80026E2C
  /* 3E488 03F488 8003E888 */  .4byte jtgt_80026E40
  /* 3E48C 03F48C 8003E88C */  .4byte jtgt_80026E80
  /* 3E490 03F490 8003E890 */  .4byte jtgt_80026E94
  /* 3E494 03F494 8003E894 */  .4byte jtgt_80026ED4
  /* 3E498 03F498 8003E898 */  .4byte jtgt_80026FF0
  /* 3E49C 03F49C 8003E89C */  .4byte jtgt_80026FFC
  /* 3E4A0 03F4A0 8003E8A0 */  .4byte jtgt_80027008
  /* 3E4A4 03F4A4 8003E8A4 */  .4byte jtgt_8002701C
  /* 3E4A8 03F4A8 8003E8A8 */  .4byte jtgt_8002705C
  /* 3E4AC 03F4AC 8003E8AC */  .4byte jtgt_80027108
  /* 3E4B0 03F4B0 8003E8B0 */  .4byte jtgt_80027114

glabel D_8003E8B4
  /* 3E4B4 03F4B4 8003E8B4 */  .4byte jtgt_80027150
  /* 3E4B8 03F4B8 8003E8B8 */  .4byte jtgt_80027158
  /* 3E4BC 03F4BC 8003E8BC */  .4byte jtgt_80027158
  /* 3E4C0 03F4C0 8003E8C0 */  .4byte jtgt_80027158
  /* 3E4C4 03F4C4 8003E8C4 */  .4byte jtgt_80027158
  /* 3E4C8 03F4C8 8003E8C8 */  .4byte jtgt_80027158
  /* 3E4CC 03F4CC 8003E8CC */  .4byte jtgt_80027158
  /* 3E4D0 03F4D0 8003E8D0 */  .4byte jtgt_80027168

glabel D_8003E8D4
  /* 3E4D4 03F4D4 8003E8D4 */  .4byte jtgt_80027534
  /* 3E4D8 03F4D8 8003E8D8 */  .4byte jtgt_800279F4
  /* 3E4DC 03F4DC 8003E8DC */  .4byte jtgt_800279F4
  /* 3E4E0 03F4E0 8003E8E0 */  .4byte jtgt_800279F4
  /* 3E4E4 03F4E4 8003E8E4 */  .4byte jtgt_800279F4
  /* 3E4E8 03F4E8 8003E8E8 */  .4byte jtgt_800279F4
  /* 3E4EC 03F4EC 8003E8EC */  .4byte jtgt_800279F4
  /* 3E4F0 03F4F0 8003E8F0 */  .4byte jtgt_800279F4
  /* 3E4F4 03F4F4 8003E8F4 */  .4byte jtgt_800279F4
  /* 3E4F8 03F4F8 8003E8F8 */  .4byte jtgt_800279F4
  /* 3E4FC 03F4FC 8003E8FC */  .4byte jtgt_800279F4
  /* 3E500 03F500 8003E900 */  .4byte jtgt_800279F4
  /* 3E504 03F504 8003E904 */  .4byte jtgt_800279F4
  /* 3E508 03F508 8003E908 */  .4byte jtgt_800279F4
  /* 3E50C 03F50C 8003E90C */  .4byte jtgt_800279F4
  /* 3E510 03F510 8003E910 */  .4byte jtgt_800279F4
  /* 3E514 03F514 8003E914 */  .4byte jtgt_80027588
  /* 3E518 03F518 8003E918 */  .4byte jtgt_800279F4
  /* 3E51C 03F51C 8003E91C */  .4byte jtgt_800279F4
  /* 3E520 03F520 8003E920 */  .4byte jtgt_800279F4
  /* 3E524 03F524 8003E924 */  .4byte jtgt_800279F4
  /* 3E528 03F528 8003E928 */  .4byte jtgt_800279F4
  /* 3E52C 03F52C 8003E92C */  .4byte jtgt_800279F4
  /* 3E530 03F530 8003E930 */  .4byte jtgt_800279F4
  /* 3E534 03F534 8003E934 */  .4byte jtgt_800279F4
  /* 3E538 03F538 8003E938 */  .4byte jtgt_800279F4
  /* 3E53C 03F53C 8003E93C */  .4byte jtgt_800279F4
  /* 3E540 03F540 8003E940 */  .4byte jtgt_800279F4
  /* 3E544 03F544 8003E944 */  .4byte jtgt_800279F4
  /* 3E548 03F548 8003E948 */  .4byte jtgt_800279F4
  /* 3E54C 03F54C 8003E94C */  .4byte jtgt_800279F4
  /* 3E550 03F550 8003E950 */  .4byte jtgt_800279F4
  /* 3E554 03F554 8003E954 */  .4byte jtgt_800275DC
  /* 3E558 03F558 8003E958 */  .4byte jtgt_800279F4
  /* 3E55C 03F55C 8003E95C */  .4byte jtgt_800279F4
  /* 3E560 03F560 8003E960 */  .4byte jtgt_800279F4
  /* 3E564 03F564 8003E964 */  .4byte jtgt_800279F4
  /* 3E568 03F568 8003E968 */  .4byte jtgt_800279F4
  /* 3E56C 03F56C 8003E96C */  .4byte jtgt_800279F4
  /* 3E570 03F570 8003E970 */  .4byte jtgt_800279F4
  /* 3E574 03F574 8003E974 */  .4byte jtgt_800279F4
  /* 3E578 03F578 8003E978 */  .4byte jtgt_800279F4
  /* 3E57C 03F57C 8003E97C */  .4byte jtgt_800279F4
  /* 3E580 03F580 8003E980 */  .4byte jtgt_800279F4
  /* 3E584 03F584 8003E984 */  .4byte jtgt_800279F4
  /* 3E588 03F588 8003E988 */  .4byte jtgt_800279F4
  /* 3E58C 03F58C 8003E98C */  .4byte jtgt_800279F4
  /* 3E590 03F590 8003E990 */  .4byte jtgt_800279F4
  /* 3E594 03F594 8003E994 */  .4byte jtgt_80027664
  /* 3E598 03F598 8003E998 */  .4byte jtgt_800279F4
  /* 3E59C 03F59C 8003E99C */  .4byte jtgt_800279F4
  /* 3E5A0 03F5A0 8003E9A0 */  .4byte jtgt_800279F4
  /* 3E5A4 03F5A4 8003E9A4 */  .4byte jtgt_800279F4
  /* 3E5A8 03F5A8 8003E9A8 */  .4byte jtgt_800279F4
  /* 3E5AC 03F5AC 8003E9AC */  .4byte jtgt_800279F4
  /* 3E5B0 03F5B0 8003E9B0 */  .4byte jtgt_800279F4
  /* 3E5B4 03F5B4 8003E9B4 */  .4byte jtgt_800279F4
  /* 3E5B8 03F5B8 8003E9B8 */  .4byte jtgt_800279F4
  /* 3E5BC 03F5BC 8003E9BC */  .4byte jtgt_800279F4
  /* 3E5C0 03F5C0 8003E9C0 */  .4byte jtgt_800279F4
  /* 3E5C4 03F5C4 8003E9C4 */  .4byte jtgt_800279F4
  /* 3E5C8 03F5C8 8003E9C8 */  .4byte jtgt_800279F4
  /* 3E5CC 03F5CC 8003E9CC */  .4byte jtgt_800279F4
  /* 3E5D0 03F5D0 8003E9D0 */  .4byte jtgt_800279F4
  /* 3E5D4 03F5D4 8003E9D4 */  .4byte jtgt_800276B8
  /* 3E5D8 03F5D8 8003E9D8 */  .4byte jtgt_800279F4
  /* 3E5DC 03F5DC 8003E9DC */  .4byte jtgt_800279F4
  /* 3E5E0 03F5E0 8003E9E0 */  .4byte jtgt_800279F4
  /* 3E5E4 03F5E4 8003E9E4 */  .4byte jtgt_800279F4
  /* 3E5E8 03F5E8 8003E9E8 */  .4byte jtgt_800279F4
  /* 3E5EC 03F5EC 8003E9EC */  .4byte jtgt_800279F4
  /* 3E5F0 03F5F0 8003E9F0 */  .4byte jtgt_800279F4
  /* 3E5F4 03F5F4 8003E9F4 */  .4byte jtgt_800279F4
  /* 3E5F8 03F5F8 8003E9F8 */  .4byte jtgt_800279F4
  /* 3E5FC 03F5FC 8003E9FC */  .4byte jtgt_800279F4
  /* 3E600 03F600 8003EA00 */  .4byte jtgt_800279F4
  /* 3E604 03F604 8003EA04 */  .4byte jtgt_800279F4
  /* 3E608 03F608 8003EA08 */  .4byte jtgt_800279F4
  /* 3E60C 03F60C 8003EA0C */  .4byte jtgt_800279F4
  /* 3E610 03F610 8003EA10 */  .4byte jtgt_800279F4
  /* 3E614 03F614 8003EA14 */  .4byte jtgt_8002790C
  /* 3E618 03F618 8003EA18 */  .4byte jtgt_800279F4
  /* 3E61C 03F61C 8003EA1C */  .4byte jtgt_800279F4
  /* 3E620 03F620 8003EA20 */  .4byte jtgt_800279F4
  /* 3E624 03F624 8003EA24 */  .4byte jtgt_800279F4
  /* 3E628 03F628 8003EA28 */  .4byte jtgt_800279F4
  /* 3E62C 03F62C 8003EA2C */  .4byte jtgt_800279F4
  /* 3E630 03F630 8003EA30 */  .4byte jtgt_800279F4
  /* 3E634 03F634 8003EA34 */  .4byte jtgt_800279F4
  /* 3E638 03F638 8003EA38 */  .4byte jtgt_800279F4
  /* 3E63C 03F63C 8003EA3C */  .4byte jtgt_800279F4
  /* 3E640 03F640 8003EA40 */  .4byte jtgt_800279F4
  /* 3E644 03F644 8003EA44 */  .4byte jtgt_800279F4
  /* 3E648 03F648 8003EA48 */  .4byte jtgt_800279F4
  /* 3E64C 03F64C 8003EA4C */  .4byte jtgt_800279F4
  /* 3E650 03F650 8003EA50 */  .4byte jtgt_800279F4
  /* 3E654 03F654 8003EA54 */  .4byte jtgt_80027974
  /* 3E658 03F658 8003EA58 */  .4byte jtgt_800279F4
  /* 3E65C 03F65C 8003EA5C */  .4byte jtgt_800279F4
  /* 3E660 03F660 8003EA60 */  .4byte jtgt_800279F4
  /* 3E664 03F664 8003EA64 */  .4byte jtgt_800279F4
  /* 3E668 03F668 8003EA68 */  .4byte jtgt_800279F4
  /* 3E66C 03F66C 8003EA6C */  .4byte jtgt_800279F4
  /* 3E670 03F670 8003EA70 */  .4byte jtgt_800279F4
  /* 3E674 03F674 8003EA74 */  .4byte jtgt_800279F4
  /* 3E678 03F678 8003EA78 */  .4byte jtgt_800279F4
  /* 3E67C 03F67C 8003EA7C */  .4byte jtgt_800279F4
  /* 3E680 03F680 8003EA80 */  .4byte jtgt_800279F4
  /* 3E684 03F684 8003EA84 */  .4byte jtgt_800279F4
  /* 3E688 03F688 8003EA88 */  .4byte jtgt_800279F4
  /* 3E68C 03F68C 8003EA8C */  .4byte jtgt_800279F4
  /* 3E690 03F690 8003EA90 */  .4byte jtgt_800279F4
  /* 3E694 03F694 8003EA94 */  .4byte jtgt_800279D8
  /* 3E698 03F698 8003EA98 */  .4byte jtgt_800279F4
  /* 3E69C 03F69C 8003EA9C */  .4byte jtgt_800279F4
  /* 3E6A0 03F6A0 8003EAA0 */  .4byte jtgt_800279F4
  /* 3E6A4 03F6A4 8003EAA4 */  .4byte jtgt_800279F4
  /* 3E6A8 03F6A8 8003EAA8 */  .4byte jtgt_800279F4
  /* 3E6AC 03F6AC 8003EAAC */  .4byte jtgt_800279F4
  /* 3E6B0 03F6B0 8003EAB0 */  .4byte jtgt_800279F4
  /* 3E6B4 03F6B4 8003EAB4 */  .4byte jtgt_800279F4
  /* 3E6B8 03F6B8 8003EAB8 */  .4byte jtgt_800279F4
  /* 3E6BC 03F6BC 8003EABC */  .4byte jtgt_800279F4
  /* 3E6C0 03F6C0 8003EAC0 */  .4byte jtgt_800279F4
  /* 3E6C4 03F6C4 8003EAC4 */  .4byte jtgt_800279F4
  /* 3E6C8 03F6C8 8003EAC8 */  .4byte jtgt_800279F4
  /* 3E6CC 03F6CC 8003EACC */  .4byte jtgt_800279F4
  /* 3E6D0 03F6D0 8003EAD0 */  .4byte jtgt_800279F4
  /* 3E6D4 03F6D4 8003EAD4 */  .4byte jtgt_800279E8
  /* 3E6D8 03F6D8 8003EAD8 */  .4byte jtgt_800279F4
  /* 3E6DC 03F6DC 8003EADC */  .4byte jtgt_800279F4
  /* 3E6E0 03F6E0 8003EAE0 */  .4byte jtgt_800279F4
  /* 3E6E4 03F6E4 8003EAE4 */  .4byte jtgt_800279F4
  /* 3E6E8 03F6E8 8003EAE8 */  .4byte jtgt_800279F4
  /* 3E6EC 03F6EC 8003EAEC */  .4byte jtgt_800279F4
  /* 3E6F0 03F6F0 8003EAF0 */  .4byte jtgt_800279F4
  /* 3E6F4 03F6F4 8003EAF4 */  .4byte jtgt_800279F4
  /* 3E6F8 03F6F8 8003EAF8 */  .4byte jtgt_800279F4
  /* 3E6FC 03F6FC 8003EAFC */  .4byte jtgt_800279F4
  /* 3E700 03F700 8003EB00 */  .4byte jtgt_800279F4
  /* 3E704 03F704 8003EB04 */  .4byte jtgt_800279F4
  /* 3E708 03F708 8003EB08 */  .4byte jtgt_800279F4
  /* 3E70C 03F70C 8003EB0C */  .4byte jtgt_800279F4
  /* 3E710 03F710 8003EB10 */  .4byte jtgt_800279F4
  /* 3E714 03F714 8003EB14 */  .4byte jtgt_800279F0

glabel D_8003EB18
  /* 3E718 03F718 8003EB18 */  .4byte jtgt_80027A94
  /* 3E71C 03F71C 8003EB1C */  .4byte jtgt_80027B28
  /* 3E720 03F720 8003EB20 */  .4byte jtgt_80027B5C
  /* 3E724 03F724 8003EB24 */  .4byte jtgt_80027B7C
  /* 3E728 03F728 8003EB28 */  .4byte jtgt_80027BA0
  /* 3E72C 03F72C 8003EB2C */  .4byte jtgt_80027C04
  /* 3E730 03F730 8003EB30 */  .4byte jtgt_80027C94
  /* 3E734 03F734 8003EB34 */  .4byte jtgt_80027CD8
  /* 3E738 03F738 8003EB38 */  .4byte jtgt_80027D20

glabel D_8003EB3C
  /* 3E73C 03F73C 8003EB3C */  .4byte jtgt_80027E24
  /* 3E740 03F740 8003EB40 */  .4byte jtgt_80027E00
  /* 3E744 03F744 8003EB44 */  .4byte jtgt_80027EE8
  /* 3E748 03F748 8003EB48 */  .4byte jtgt_80027ED4
  /* 3E74C 03F74C 8003EB4C */  .4byte jtgt_80027F64
  /* 3E750 03F750 8003EB50 */  .4byte jtgt_80027F40

glabel D_8003EB54
  /* 3E754 03F754 8003EB54 */  .4byte jtgt_800280BC
  /* 3E758 03F758 8003EB58 */  .4byte jtgt_800280B4
  /* 3E75C 03F75C 8003EB5C */  .4byte jtgt_800280CC
  /* 3E760 03F760 8003EB60 */  .4byte jtgt_800280C4
  /* 3E764 03F764 8003EB64 */  .4byte jtgt_800280DC
  /* 3E768 03F768 8003EB68 */  .4byte jtgt_800280D4
  /* 3E76C 03F76C 8003EB6C */  .4byte jtgt_800280EC
  /* 3E770 03F770 8003EB70 */  .4byte jtgt_800280E4

glabel D_8003EB74
  /* 3E774 03F774 8003EB74 */
  .4byte 0x477fff00 # .float 65535.0
  .incbin "system.raw.bin", 0x3E778, 0x4

glabel jtbl_8003EB7C
  /* 3E77C 03F77C 8003EB7C */  .4byte jtgt_8002A7F0
  /* 3E780 03F780 8003EB80 */  .4byte jtgt_8002A8C8
  /* 3E784 03F784 8003EB84 */  .4byte jtgt_8002A8C8
  /* 3E788 03F788 8003EB88 */  .4byte jtgt_8002A8C8
  /* 3E78C 03F78C 8003EB8C */  .4byte jtgt_8002A8C8
  /* 3E790 03F790 8003EB90 */  .4byte jtgt_8002A88C
  /* 3E794 03F794 8003EB94 */  .4byte jtgt_8002A8C8
  /* 3E798 03F798 8003EB98 */  .4byte jtgt_8002A834
  /* 3E79C 03F79C 8003EB9C */  .4byte jtgt_8002A864
  /* 3E7A0 03F7A0 8003EBA0 */  .4byte jtgt_8002A8C8
  /* 3E7A4 03F7A4 8003EBA4 */  .4byte jtgt_8002A8C8
  /* 3E7A8 03F7A8 8003EBA8 */  .4byte jtgt_8002A5B8
  /* 3E7AC 03F7AC 8003EBAC */  .4byte jtgt_8002A5B8
  /* 3E7B0 03F7B0 8003EBB0 */  .4byte jtgt_8002A468
  /* 3E7B4 03F7B4 8003EBB4 */  .4byte jtgt_8002A790
  /* 3E7B8 03F7B8 8003EBB8 */  .4byte jtgt_8002A7B8
  /* 3E7BC 03F7BC 8003EBBC */  .4byte jtgt_8002A5B8
  /* 3E7C0 03F7C0 8003EBC0 */  .4byte jtgt_8002A5B8

glabel D_8003EBC4
  /* 3E7C4 03F7C4 8003EBC4 */  .4byte jtgt_8002B734
  /* 3E7C8 03F7C8 8003EBC8 */  .4byte jtgt_8002BD14
  /* 3E7CC 03F7CC 8003EBCC */  .4byte jtgt_8002BD14
  /* 3E7D0 03F7D0 8003EBD0 */  .4byte jtgt_8002BD14
  /* 3E7D4 03F7D4 8003EBD4 */  .4byte jtgt_8002BD14
  /* 3E7D8 03F7D8 8003EBD8 */  .4byte jtgt_8002BD14
  /* 3E7DC 03F7DC 8003EBDC */  .4byte jtgt_8002BD14
  /* 3E7E0 03F7E0 8003EBE0 */  .4byte jtgt_8002BD14
  /* 3E7E4 03F7E4 8003EBE4 */  .4byte jtgt_8002BD14
  /* 3E7E8 03F7E8 8003EBE8 */  .4byte jtgt_8002BD14
  /* 3E7EC 03F7EC 8003EBEC */  .4byte jtgt_8002BD14
  /* 3E7F0 03F7F0 8003EBF0 */  .4byte jtgt_8002BD14
  /* 3E7F4 03F7F4 8003EBF4 */  .4byte jtgt_8002BD14
  /* 3E7F8 03F7F8 8003EBF8 */  .4byte jtgt_8002BD14
  /* 3E7FC 03F7FC 8003EBFC */  .4byte jtgt_8002BD14
  /* 3E800 03F800 8003EC00 */  .4byte jtgt_8002BD14
  /* 3E804 03F804 8003EC04 */  .4byte jtgt_8002B348
  /* 3E808 03F808 8003EC08 */  .4byte jtgt_8002BD14
  /* 3E80C 03F80C 8003EC0C */  .4byte jtgt_8002BD14
  /* 3E810 03F810 8003EC10 */  .4byte jtgt_8002BD14
  /* 3E814 03F814 8003EC14 */  .4byte jtgt_8002BD14
  /* 3E818 03F818 8003EC18 */  .4byte jtgt_8002BD14
  /* 3E81C 03F81C 8003EC1C */  .4byte jtgt_8002BD14
  /* 3E820 03F820 8003EC20 */  .4byte jtgt_8002BD14
  /* 3E824 03F824 8003EC24 */  .4byte jtgt_8002BD14
  /* 3E828 03F828 8003EC28 */  .4byte jtgt_8002BD14
  /* 3E82C 03F82C 8003EC2C */  .4byte jtgt_8002BD14
  /* 3E830 03F830 8003EC30 */  .4byte jtgt_8002BD14
  /* 3E834 03F834 8003EC34 */  .4byte jtgt_8002BD14
  /* 3E838 03F838 8003EC38 */  .4byte jtgt_8002BD14
  /* 3E83C 03F83C 8003EC3C */  .4byte jtgt_8002BD14
  /* 3E840 03F840 8003EC40 */  .4byte jtgt_8002BD14
  /* 3E844 03F844 8003EC44 */  .4byte jtgt_8002B78C
  /* 3E848 03F848 8003EC48 */  .4byte jtgt_8002BD14
  /* 3E84C 03F84C 8003EC4C */  .4byte jtgt_8002BD14
  /* 3E850 03F850 8003EC50 */  .4byte jtgt_8002BD14
  /* 3E854 03F854 8003EC54 */  .4byte jtgt_8002BD14
  /* 3E858 03F858 8003EC58 */  .4byte jtgt_8002BD14
  /* 3E85C 03F85C 8003EC5C */  .4byte jtgt_8002BD14
  /* 3E860 03F860 8003EC60 */  .4byte jtgt_8002BD14
  /* 3E864 03F864 8003EC64 */  .4byte jtgt_8002BD14
  /* 3E868 03F868 8003EC68 */  .4byte jtgt_8002BD14
  /* 3E86C 03F86C 8003EC6C */  .4byte jtgt_8002BD14
  /* 3E870 03F870 8003EC70 */  .4byte jtgt_8002BD14
  /* 3E874 03F874 8003EC74 */  .4byte jtgt_8002BD14
  /* 3E878 03F878 8003EC78 */  .4byte jtgt_8002BD14
  /* 3E87C 03F87C 8003EC7C */  .4byte jtgt_8002BD14
  /* 3E880 03F880 8003EC80 */  .4byte jtgt_8002BD14
  /* 3E884 03F884 8003EC84 */  .4byte jtgt_8002B800
  /* 3E888 03F888 8003EC88 */  .4byte jtgt_8002BD14
  /* 3E88C 03F88C 8003EC8C */  .4byte jtgt_8002BD14
  /* 3E890 03F890 8003EC90 */  .4byte jtgt_8002BD14
  /* 3E894 03F894 8003EC94 */  .4byte jtgt_8002BD14
  /* 3E898 03F898 8003EC98 */  .4byte jtgt_8002BD14
  /* 3E89C 03F89C 8003EC9C */  .4byte jtgt_8002BD14
  /* 3E8A0 03F8A0 8003ECA0 */  .4byte jtgt_8002BD14
  /* 3E8A4 03F8A4 8003ECA4 */  .4byte jtgt_8002BD14
  /* 3E8A8 03F8A8 8003ECA8 */  .4byte jtgt_8002BD14
  /* 3E8AC 03F8AC 8003ECAC */  .4byte jtgt_8002BD14
  /* 3E8B0 03F8B0 8003ECB0 */  .4byte jtgt_8002BD14
  /* 3E8B4 03F8B4 8003ECB4 */  .4byte jtgt_8002BD14
  /* 3E8B8 03F8B8 8003ECB8 */  .4byte jtgt_8002BD14
  /* 3E8BC 03F8BC 8003ECBC */  .4byte jtgt_8002BD14
  /* 3E8C0 03F8C0 8003ECC0 */  .4byte jtgt_8002BD14
  /* 3E8C4 03F8C4 8003ECC4 */  .4byte jtgt_8002BBDC
  /* 3E8C8 03F8C8 8003ECC8 */  .4byte jtgt_8002BD14
  /* 3E8CC 03F8CC 8003ECCC */  .4byte jtgt_8002BD14
  /* 3E8D0 03F8D0 8003ECD0 */  .4byte jtgt_8002BD14
  /* 3E8D4 03F8D4 8003ECD4 */  .4byte jtgt_8002BD14
  /* 3E8D8 03F8D8 8003ECD8 */  .4byte jtgt_8002BD14
  /* 3E8DC 03F8DC 8003ECDC */  .4byte jtgt_8002BD14
  /* 3E8E0 03F8E0 8003ECE0 */  .4byte jtgt_8002BD14
  /* 3E8E4 03F8E4 8003ECE4 */  .4byte jtgt_8002BD14
  /* 3E8E8 03F8E8 8003ECE8 */  .4byte jtgt_8002BD14
  /* 3E8EC 03F8EC 8003ECEC */  .4byte jtgt_8002BD14
  /* 3E8F0 03F8F0 8003ECF0 */  .4byte jtgt_8002BD14
  /* 3E8F4 03F8F4 8003ECF4 */  .4byte jtgt_8002BD14
  /* 3E8F8 03F8F8 8003ECF8 */  .4byte jtgt_8002BD14
  /* 3E8FC 03F8FC 8003ECFC */  .4byte jtgt_8002BD14
  /* 3E900 03F900 8003ED00 */  .4byte jtgt_8002BD14
  /* 3E904 03F904 8003ED04 */  .4byte jtgt_8002B7E4
  /* 3E908 03F908 8003ED08 */  .4byte jtgt_8002BD14
  /* 3E90C 03F90C 8003ED0C */  .4byte jtgt_8002BD14
  /* 3E910 03F910 8003ED10 */  .4byte jtgt_8002BD14
  /* 3E914 03F914 8003ED14 */  .4byte jtgt_8002BD14
  /* 3E918 03F918 8003ED18 */  .4byte jtgt_8002BD14
  /* 3E91C 03F91C 8003ED1C */  .4byte jtgt_8002BD14
  /* 3E920 03F920 8003ED20 */  .4byte jtgt_8002BD14
  /* 3E924 03F924 8003ED24 */  .4byte jtgt_8002BD14
  /* 3E928 03F928 8003ED28 */  .4byte jtgt_8002BD14
  /* 3E92C 03F92C 8003ED2C */  .4byte jtgt_8002BD14
  /* 3E930 03F930 8003ED30 */  .4byte jtgt_8002BD14
  /* 3E934 03F934 8003ED34 */  .4byte jtgt_8002BD14
  /* 3E938 03F938 8003ED38 */  .4byte jtgt_8002BD14
  /* 3E93C 03F93C 8003ED3C */  .4byte jtgt_8002BD14
  /* 3E940 03F940 8003ED40 */  .4byte jtgt_8002BD14
  /* 3E944 03F944 8003ED44 */  .4byte jtgt_8002BC30

glabel D_8003ED48
  /* 3E948 03F948 8003ED48 */  .4byte jtgt_8002B8C0
  /* 3E94C 03F94C 8003ED4C */  .4byte jtgt_8002BD14
  /* 3E950 03F950 8003ED50 */  .4byte jtgt_8002BD14
  /* 3E954 03F954 8003ED54 */  .4byte jtgt_8002B860
  /* 3E958 03F958 8003ED58 */  .4byte jtgt_8002BD14
  /* 3E95C 03F95C 8003ED5C */  .4byte jtgt_8002BD14
  /* 3E960 03F960 8003ED60 */  .4byte jtgt_8002BD14
  /* 3E964 03F964 8003ED64 */  .4byte jtgt_8002BD14
  /* 3E968 03F968 8003ED68 */  .4byte jtgt_8002BD14
  /* 3E96C 03F96C 8003ED6C */  .4byte jtgt_8002B94C
  /* 3E970 03F970 8003ED70 */  .4byte jtgt_8002BD14
  /* 3E974 03F974 8003ED74 */  .4byte jtgt_8002BD14
  /* 3E978 03F978 8003ED78 */  .4byte jtgt_8002BD14
  /* 3E97C 03F97C 8003ED7C */  .4byte jtgt_8002BA6C
  /* 3E980 03F980 8003ED80 */  .4byte jtgt_8002BAC0
  /* 3E984 03F984 8003ED84 */  .4byte jtgt_8002BAC8
  /* 3E988 03F988 8003ED88 */  .4byte jtgt_8002BB28
  /* 3E98C 03F98C 8003ED8C */  .4byte jtgt_8002BB88
  /* 3E990 03F990 8003ED90 */  .4byte jtgt_8002BBC0

glabel D_8003ED94
  /* 3E994 03F994 8003ED94 */  .4byte jtgt_8002BD98
  /* 3E998 03F998 8003ED98 */  .4byte jtgt_8002C350
  /* 3E99C 03F99C 8003ED9C */  .4byte jtgt_8002C0F4
  /* 3E9A0 03F9A0 8003EDA0 */  .4byte jtgt_8002C350
  /* 3E9A4 03F9A4 8003EDA4 */  .4byte jtgt_8002C350
  /* 3E9A8 03F9A8 8003EDA8 */  .4byte jtgt_8002BE80
  /* 3E9AC 03F9AC 8003EDAC */  .4byte jtgt_8002BEC4
  /* 3E9B0 03F9B0 8003EDB0 */  .4byte jtgt_8002C114
  /* 3E9B4 03F9B4 8003EDB4 */  .4byte jtgt_8002C350
  /* 3E9B8 03F9B8 8003EDB8 */  .4byte jtgt_8002BE60
  /* 3E9BC 03F9BC 8003EDBC */  .4byte jtgt_8002C12C
  /* 3E9C0 03F9C0 8003EDC0 */  .4byte jtgt_8002C350
  /* 3E9C4 03F9C4 8003EDC4 */  .4byte jtgt_8002C2B8
  /* 3E9C8 03F9C8 8003EDC8 */  .4byte jtgt_8002C2DC
  /* 3E9CC 03F9CC 8003EDCC */  .4byte jtgt_8002C310
  /* 3E9D0 03F9D0 8003EDD0 */  .4byte jtgt_8002C184
  /* 3E9D4 03F9D4 8003EDD4 */  .4byte jtgt_8002C1B0
  /* 3E9D8 03F9D8 8003EDD8 */  .4byte jtgt_8002C21C
  /* 3E9DC 03F9DC 8003EDDC */  .4byte jtgt_8002C350
  /* 3E9E0 03F9E0 8003EDE0 */  .4byte jtgt_8002C350
  /* 3E9E4 03F9E4 8003EDE4 */  .4byte jtgt_8002C350
  /* 3E9E8 03F9E8 8003EDE8 */  .4byte jtgt_8002C0F4
  /* 3E9EC 03F9EC 8003EDEC */  .4byte jtgt_8002BF20
  /* 3E9F0 03F9F0 8003EDF0 */  .4byte jtgt_8002C020
  /* 3E9F4 03F9F4 8003EDF4 */  .4byte jtgt_8002C328
  /* 3E9F8 03F9F8 8003EDF8 */  .4byte jtgt_8002C340

glabel D_8003EDFC
  /* 3E9FC 03F9FC 8003EDFC */  .4byte jtgt_8002BDD4
  /* 3EA00 03FA00 8003EE00 */  .4byte jtgt_8002C350
  /* 3EA04 03FA04 8003EE04 */  .4byte jtgt_8002BE00
  /* 3EA08 03FA08 8003EE08 */  .4byte jtgt_8002BE24
  /* 3EA0C 03FA0C 8003EE0C */  .4byte jtgt_8002C350
  /* 3EA10 03FA10 8003EE10 */  .4byte jtgt_8002C350
  /* 3EA14 03FA14 8003EE14 */  .4byte jtgt_8002C350
  /* 3EA18 03FA18 8003EE18 */  .4byte jtgt_8002C350
  /* 3EA1C 03FA1C 8003EE1C */  .4byte jtgt_8002C350
  /* 3EA20 03FA20 8003EE20 */  .4byte jtgt_8002C350
  /* 3EA24 03FA24 8003EE24 */  .4byte jtgt_8002C350
  /* 3EA28 03FA28 8003EE28 */  .4byte jtgt_8002C350
  /* 3EA2C 03FA2C 8003EE2C */  .4byte jtgt_8002C350
  /* 3EA30 03FA30 8003EE30 */  .4byte jtgt_8002C350
  /* 3EA34 03FA34 8003EE34 */  .4byte jtgt_8002C350
  /* 3EA38 03FA38 8003EE38 */  .4byte jtgt_8002C350
  /* 3EA3C 03FA3C 8003EE3C */  .4byte jtgt_8002C350
  /* 3EA40 03FA40 8003EE40 */  .4byte jtgt_8002BE50
  /* 3EA44 03FA44 8003EE44 */  .4byte jtgt_8002BE50
  /* 3EA48 03FA48 8003EE48 */  .4byte jtgt_8002BE50

glabel D_8003EE4C
  /* 3EA4C 03FA4C 8003EE4C */
  .4byte 0x48f42400 # .float 500000.0

glabel D_8003EE50
  /* 3EA50 03FA50 8003EE50 */
  .4byte 0x49742400 # .float 1000000.0

glabel D_8003EE54
  /* 3EA54 03FA54 8003EE54 */
  .4byte 0x49742400 # .float 1000000.0

glabel jtbl_8003EE58
  /* 3EA58 03FA58 8003EE58 */  .4byte jtgt_8002CFD8
  /* 3EA5C 03FA5C 8003EE5C */  .4byte jtgt_8002D00C
  /* 3EA60 03FA60 8003EE60 */  .4byte jtgt_8002D06C
  /* 3EA64 03FA64 8003EE64 */  .4byte jtgt_8002D040
  /* 3EA68 03FA68 8003EE68 */  .4byte jtgt_8002D098
  /* 3EA6C 03FA6C 8003EE6C */  .4byte jtgt_8002D0C4
  /* 3EA70 03FA70 8003EE70 */  .4byte jtgt_8002D12C
  /* 3EA74 03FA74 8003EE74 */  .4byte jtgt_8002D198

glabel D_8003EE78
  /* 3EA78 03FA78 8003EE78 */
  .4byte 0x482910da # .float 173123.4

glabel jtbl_8003EE7C
  /* 3EA7C 03FA7C 8003EE7C */  .4byte jtgt_8002D2B4
  /* 3EA80 03FA80 8003EE80 */  .4byte jtgt_8002D2C0
  /* 3EA84 03FA84 8003EE84 */  .4byte jtgt_8002D2D8
  /* 3EA88 03FA88 8003EE88 */  .4byte jtgt_8002D2E4
  /* 3EA8C 03FA8C 8003EE8C */  .4byte jtgt_8002D2CC
  /* 3EA90 03FA90 8003EE90 */  .4byte jtgt_8002D2F0

glabel D_8003EE94
  /* 3EA94 03FA94 8003EE94 */
  .4byte 0x482910da # .float 173123.4
  .incbin "system.raw.bin", 0x3EA98, 0x8

glabel jtbl_8003EEA0
  /* 3EAA0 03FAA0 8003EEA0 */  .4byte jtgt_8002E8B8
  /* 3EAA4 03FAA4 8003EEA4 */  .4byte jtgt_8002ED3C
  /* 3EAA8 03FAA8 8003EEA8 */  .4byte jtgt_8002ED3C
  /* 3EAAC 03FAAC 8003EEAC */  .4byte jtgt_8002ED3C
  /* 3EAB0 03FAB0 8003EEB0 */  .4byte jtgt_8002ED3C
  /* 3EAB4 03FAB4 8003EEB4 */  .4byte jtgt_8002ED3C
  /* 3EAB8 03FAB8 8003EEB8 */  .4byte jtgt_8002ED3C
  /* 3EABC 03FABC 8003EEBC */  .4byte jtgt_8002ED3C
  /* 3EAC0 03FAC0 8003EEC0 */  .4byte jtgt_8002ED3C
  /* 3EAC4 03FAC4 8003EEC4 */  .4byte jtgt_8002ED3C
  /* 3EAC8 03FAC8 8003EEC8 */  .4byte jtgt_8002ED3C
  /* 3EACC 03FACC 8003EECC */  .4byte jtgt_8002ED3C
  /* 3EAD0 03FAD0 8003EED0 */  .4byte jtgt_8002ED3C
  /* 3EAD4 03FAD4 8003EED4 */  .4byte jtgt_8002ED3C
  /* 3EAD8 03FAD8 8003EED8 */  .4byte jtgt_8002ED3C
  /* 3EADC 03FADC 8003EEDC */  .4byte jtgt_8002ED3C
  /* 3EAE0 03FAE0 8003EEE0 */  .4byte jtgt_8002E560
  /* 3EAE4 03FAE4 8003EEE4 */  .4byte jtgt_8002ED3C
  /* 3EAE8 03FAE8 8003EEE8 */  .4byte jtgt_8002ED3C
  /* 3EAEC 03FAEC 8003EEEC */  .4byte jtgt_8002ED3C
  /* 3EAF0 03FAF0 8003EEF0 */  .4byte jtgt_8002ED3C
  /* 3EAF4 03FAF4 8003EEF4 */  .4byte jtgt_8002ED3C
  /* 3EAF8 03FAF8 8003EEF8 */  .4byte jtgt_8002ED3C
  /* 3EAFC 03FAFC 8003EEFC */  .4byte jtgt_8002ED3C
  /* 3EB00 03FB00 8003EF00 */  .4byte jtgt_8002ED3C
  /* 3EB04 03FB04 8003EF04 */  .4byte jtgt_8002ED3C
  /* 3EB08 03FB08 8003EF08 */  .4byte jtgt_8002ED3C
  /* 3EB0C 03FB0C 8003EF0C */  .4byte jtgt_8002ED3C
  /* 3EB10 03FB10 8003EF10 */  .4byte jtgt_8002ED3C
  /* 3EB14 03FB14 8003EF14 */  .4byte jtgt_8002ED3C
  /* 3EB18 03FB18 8003EF18 */  .4byte jtgt_8002ED3C
  /* 3EB1C 03FB1C 8003EF1C */  .4byte jtgt_8002ED3C
  /* 3EB20 03FB20 8003EF20 */  .4byte jtgt_8002E910
  /* 3EB24 03FB24 8003EF24 */  .4byte jtgt_8002ED3C
  /* 3EB28 03FB28 8003EF28 */  .4byte jtgt_8002ED3C
  /* 3EB2C 03FB2C 8003EF2C */  .4byte jtgt_8002ED3C
  /* 3EB30 03FB30 8003EF30 */  .4byte jtgt_8002ED3C
  /* 3EB34 03FB34 8003EF34 */  .4byte jtgt_8002ED3C
  /* 3EB38 03FB38 8003EF38 */  .4byte jtgt_8002ED3C
  /* 3EB3C 03FB3C 8003EF3C */  .4byte jtgt_8002ED3C
  /* 3EB40 03FB40 8003EF40 */  .4byte jtgt_8002ED3C
  /* 3EB44 03FB44 8003EF44 */  .4byte jtgt_8002ED3C
  /* 3EB48 03FB48 8003EF48 */  .4byte jtgt_8002ED3C
  /* 3EB4C 03FB4C 8003EF4C */  .4byte jtgt_8002ED3C
  /* 3EB50 03FB50 8003EF50 */  .4byte jtgt_8002ED3C
  /* 3EB54 03FB54 8003EF54 */  .4byte jtgt_8002ED3C
  /* 3EB58 03FB58 8003EF58 */  .4byte jtgt_8002ED3C
  /* 3EB5C 03FB5C 8003EF5C */  .4byte jtgt_8002ED3C
  /* 3EB60 03FB60 8003EF60 */  .4byte jtgt_8002E98C
  /* 3EB64 03FB64 8003EF64 */  .4byte jtgt_8002ED3C
  /* 3EB68 03FB68 8003EF68 */  .4byte jtgt_8002ED3C
  /* 3EB6C 03FB6C 8003EF6C */  .4byte jtgt_8002ED3C
  /* 3EB70 03FB70 8003EF70 */  .4byte jtgt_8002ED3C
  /* 3EB74 03FB74 8003EF74 */  .4byte jtgt_8002ED3C
  /* 3EB78 03FB78 8003EF78 */  .4byte jtgt_8002ED3C
  /* 3EB7C 03FB7C 8003EF7C */  .4byte jtgt_8002ED3C
  /* 3EB80 03FB80 8003EF80 */  .4byte jtgt_8002ED3C
  /* 3EB84 03FB84 8003EF84 */  .4byte jtgt_8002ED3C
  /* 3EB88 03FB88 8003EF88 */  .4byte jtgt_8002ED3C
  /* 3EB8C 03FB8C 8003EF8C */  .4byte jtgt_8002ED3C
  /* 3EB90 03FB90 8003EF90 */  .4byte jtgt_8002ED3C
  /* 3EB94 03FB94 8003EF94 */  .4byte jtgt_8002ED3C
  /* 3EB98 03FB98 8003EF98 */  .4byte jtgt_8002ED3C
  /* 3EB9C 03FB9C 8003EF9C */  .4byte jtgt_8002ED3C
  /* 3EBA0 03FBA0 8003EFA0 */  .4byte jtgt_8002EC68
  /* 3EBA4 03FBA4 8003EFA4 */  .4byte jtgt_8002ED3C
  /* 3EBA8 03FBA8 8003EFA8 */  .4byte jtgt_8002ED3C
  /* 3EBAC 03FBAC 8003EFAC */  .4byte jtgt_8002ED3C
  /* 3EBB0 03FBB0 8003EFB0 */  .4byte jtgt_8002ED3C
  /* 3EBB4 03FBB4 8003EFB4 */  .4byte jtgt_8002ED3C
  /* 3EBB8 03FBB8 8003EFB8 */  .4byte jtgt_8002ED3C
  /* 3EBBC 03FBBC 8003EFBC */  .4byte jtgt_8002ED3C
  /* 3EBC0 03FBC0 8003EFC0 */  .4byte jtgt_8002ED3C
  /* 3EBC4 03FBC4 8003EFC4 */  .4byte jtgt_8002ED3C
  /* 3EBC8 03FBC8 8003EFC8 */  .4byte jtgt_8002ED3C
  /* 3EBCC 03FBCC 8003EFCC */  .4byte jtgt_8002ED3C
  /* 3EBD0 03FBD0 8003EFD0 */  .4byte jtgt_8002ED3C
  /* 3EBD4 03FBD4 8003EFD4 */  .4byte jtgt_8002ED3C
  /* 3EBD8 03FBD8 8003EFD8 */  .4byte jtgt_8002ED3C
  /* 3EBDC 03FBDC 8003EFDC */  .4byte jtgt_8002ED3C
  /* 3EBE0 03FBE0 8003EFE0 */  .4byte jtgt_8002E970
  /* 3EBE4 03FBE4 8003EFE4 */  .4byte jtgt_8002ED3C
  /* 3EBE8 03FBE8 8003EFE8 */  .4byte jtgt_8002ED3C
  /* 3EBEC 03FBEC 8003EFEC */  .4byte jtgt_8002ED3C
  /* 3EBF0 03FBF0 8003EFF0 */  .4byte jtgt_8002ED3C
  /* 3EBF4 03FBF4 8003EFF4 */  .4byte jtgt_8002ED3C
  /* 3EBF8 03FBF8 8003EFF8 */  .4byte jtgt_8002ED3C
  /* 3EBFC 03FBFC 8003EFFC */  .4byte jtgt_8002ED3C
  /* 3EC00 03FC00 8003F000 */  .4byte jtgt_8002ED3C
  /* 3EC04 03FC04 8003F004 */  .4byte jtgt_8002ED3C
  /* 3EC08 03FC08 8003F008 */  .4byte jtgt_8002ED3C
  /* 3EC0C 03FC0C 8003F00C */  .4byte jtgt_8002ED3C
  /* 3EC10 03FC10 8003F010 */  .4byte jtgt_8002ED3C
  /* 3EC14 03FC14 8003F014 */  .4byte jtgt_8002ED3C
  /* 3EC18 03FC18 8003F018 */  .4byte jtgt_8002ED3C
  /* 3EC1C 03FC1C 8003F01C */  .4byte jtgt_8002ED3C
  /* 3EC20 03FC20 8003F020 */  .4byte jtgt_8002EC9C

glabel D_8003F024
  /* 3EC24 03FC24 8003F024 */  .4byte jtgt_8002EA58
  /* 3EC28 03FC28 8003F028 */  .4byte jtgt_8002ED3C
  /* 3EC2C 03FC2C 8003F02C */  .4byte jtgt_8002ED3C
  /* 3EC30 03FC30 8003F030 */  .4byte jtgt_8002E9F8
  /* 3EC34 03FC34 8003F034 */  .4byte jtgt_8002ED3C
  /* 3EC38 03FC38 8003F038 */  .4byte jtgt_8002ED3C
  /* 3EC3C 03FC3C 8003F03C */  .4byte jtgt_8002ED3C
  /* 3EC40 03FC40 8003F040 */  .4byte jtgt_8002ED3C
  /* 3EC44 03FC44 8003F044 */  .4byte jtgt_8002ED3C
  /* 3EC48 03FC48 8003F048 */  .4byte jtgt_8002EAEC
  /* 3EC4C 03FC4C 8003F04C */  .4byte jtgt_8002ED3C
  /* 3EC50 03FC50 8003F050 */  .4byte jtgt_8002ED3C
  /* 3EC54 03FC54 8003F054 */  .4byte jtgt_8002ED3C
  /* 3EC58 03FC58 8003F058 */  .4byte jtgt_8002EC0C
  /* 3EC5C 03FC5C 8003F05C */  .4byte jtgt_8002EC60
  /* 3EC60 03FC60 8003F060 */  .4byte jtgt_8002ED3C
  /* 3EC64 03FC64 8003F064 */  .4byte jtgt_8002ED3C
  /* 3EC68 03FC68 8003F068 */  .4byte jtgt_8002ED3C
  /* 3EC6C 03FC6C 8003F06C */  .4byte jtgt_8002ED3C
  /* 3EC70 03FC70 8003F070 */  .4byte jtgt_8002ED3C
  /* 3EC74 03FC74 8003F074 */  .4byte jtgt_8002ED3C

glabel D_8003F078
  /* 3EC78 03FC78 8003F078 */  .4byte jtgt_8002EDB8
  /* 3EC7C 03FC7C 8003F07C */  .4byte jtgt_8002F348
  /* 3EC80 03FC80 8003F080 */  .4byte jtgt_8002F0FC
  /* 3EC84 03FC84 8003F084 */  .4byte jtgt_8002F348
  /* 3EC88 03FC88 8003F088 */  .4byte jtgt_8002F348
  /* 3EC8C 03FC8C 8003F08C */  .4byte jtgt_8002EE80
  /* 3EC90 03FC90 8003F090 */  .4byte jtgt_8002EEC4
  /* 3EC94 03FC94 8003F094 */  .4byte jtgt_8002F118
  /* 3EC98 03FC98 8003F098 */  .4byte jtgt_8002F348
  /* 3EC9C 03FC9C 8003F09C */  .4byte jtgt_8002EE60
  /* 3ECA0 03FCA0 8003F0A0 */  .4byte jtgt_8002F248
  /* 3ECA4 03FCA4 8003F0A4 */  .4byte jtgt_8002F2A8
  /* 3ECA8 03FCA8 8003F0A8 */  .4byte jtgt_8002F2C4
  /* 3ECAC 03FCAC 8003F0AC */  .4byte jtgt_8002F2E8
  /* 3ECB0 03FCB0 8003F0B0 */  .4byte jtgt_8002F338
  /* 3ECB4 03FCB4 8003F0B4 */  .4byte jtgt_8002F12C
  /* 3ECB8 03FCB8 8003F0B8 */  .4byte jtgt_8002F150
  /* 3ECBC 03FCBC 8003F0BC */  .4byte jtgt_8002F1B8
  /* 3ECC0 03FCC0 8003F0C0 */  .4byte jtgt_8002F348
  /* 3ECC4 03FCC4 8003F0C4 */  .4byte jtgt_8002F348
  /* 3ECC8 03FCC8 8003F0C8 */  .4byte jtgt_8002F348
  /* 3ECCC 03FCCC 8003F0CC */  .4byte jtgt_8002F348
  /* 3ECD0 03FCD0 8003F0D0 */  .4byte jtgt_8002EF20
  /* 3ECD4 03FCD4 8003F0D4 */  .4byte jtgt_8002F028

glabel D_8003F0D8
  /* 3ECD8 03FCD8 8003F0D8 */
  .4byte 0x48f42400 # .float 500000.0
  .incbin "system.raw.bin", 0x3ECDC, 0x4