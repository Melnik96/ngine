
libngine_scenegraph.so:     формат файла elf64-x86-64


Дизасемблювання розділу .init:

0000000000000528 <_init>:
 528:	48 83 ec 08          	sub    $0x8,%rsp
 52c:	48 8b 05 dd 03 20 00 	mov    0x2003dd(%rip),%rax        # 200910 <_DYNAMIC+0x1d8>
 533:	48 85 c0             	test   %rax,%rax
 536:	74 05                	je     53d <_init+0x15>
 538:	e8 23 00 00 00       	callq  560 <__gmon_start__@plt>
 53d:	48 83 c4 08          	add    $0x8,%rsp
 541:	c3                   	retq   

Дизасемблювання розділу .plt:

0000000000000550 <__gmon_start__@plt-0x10>:
 550:	ff 35 e2 03 20 00    	pushq  0x2003e2(%rip)        # 200938 <_GLOBAL_OFFSET_TABLE_+0x8>
 556:	ff 25 e4 03 20 00    	jmpq   *0x2003e4(%rip)        # 200940 <_GLOBAL_OFFSET_TABLE_+0x10>
 55c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000000560 <__gmon_start__@plt>:
 560:	ff 25 e2 03 20 00    	jmpq   *0x2003e2(%rip)        # 200948 <_GLOBAL_OFFSET_TABLE_+0x18>
 566:	68 00 00 00 00       	pushq  $0x0
 56b:	e9 e0 ff ff ff       	jmpq   550 <_init+0x28>

0000000000000570 <__cxa_finalize@plt>:
 570:	ff 25 da 03 20 00    	jmpq   *0x2003da(%rip)        # 200950 <_GLOBAL_OFFSET_TABLE_+0x20>
 576:	68 01 00 00 00       	pushq  $0x1
 57b:	e9 d0 ff ff ff       	jmpq   550 <_init+0x28>

Дизасемблювання розділу .text:

0000000000000580 <deregister_tm_clones>:
 580:	48 8d 3d d9 03 20 00 	lea    0x2003d9(%rip),%rdi        # 200960 <_edata>
 587:	48 8d 05 d9 03 20 00 	lea    0x2003d9(%rip),%rax        # 200967 <_edata+0x7>
 58e:	55                   	push   %rbp
 58f:	48 29 f8             	sub    %rdi,%rax
 592:	48 89 e5             	mov    %rsp,%rbp
 595:	48 83 f8 0e          	cmp    $0xe,%rax
 599:	76 15                	jbe    5b0 <deregister_tm_clones+0x30>
 59b:	48 8b 05 66 03 20 00 	mov    0x200366(%rip),%rax        # 200908 <_DYNAMIC+0x1d0>
 5a2:	48 85 c0             	test   %rax,%rax
 5a5:	74 09                	je     5b0 <deregister_tm_clones+0x30>
 5a7:	5d                   	pop    %rbp
 5a8:	ff e0                	jmpq   *%rax
 5aa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
 5b0:	5d                   	pop    %rbp
 5b1:	c3                   	retq   
 5b2:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
 5b9:	1f 84 00 00 00 00 00 

00000000000005c0 <register_tm_clones>:
 5c0:	48 8d 3d 99 03 20 00 	lea    0x200399(%rip),%rdi        # 200960 <_edata>
 5c7:	48 8d 35 92 03 20 00 	lea    0x200392(%rip),%rsi        # 200960 <_edata>
 5ce:	55                   	push   %rbp
 5cf:	48 29 fe             	sub    %rdi,%rsi
 5d2:	48 89 e5             	mov    %rsp,%rbp
 5d5:	48 c1 fe 03          	sar    $0x3,%rsi
 5d9:	48 89 f0             	mov    %rsi,%rax
 5dc:	48 c1 e8 3f          	shr    $0x3f,%rax
 5e0:	48 01 c6             	add    %rax,%rsi
 5e3:	48 d1 fe             	sar    %rsi
 5e6:	74 18                	je     600 <register_tm_clones+0x40>
 5e8:	48 8b 05 31 03 20 00 	mov    0x200331(%rip),%rax        # 200920 <_DYNAMIC+0x1e8>
 5ef:	48 85 c0             	test   %rax,%rax
 5f2:	74 0c                	je     600 <register_tm_clones+0x40>
 5f4:	5d                   	pop    %rbp
 5f5:	ff e0                	jmpq   *%rax
 5f7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
 5fe:	00 00 
 600:	5d                   	pop    %rbp
 601:	c3                   	retq   
 602:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
 609:	1f 84 00 00 00 00 00 

0000000000000610 <__do_global_dtors_aux>:
 610:	80 3d 49 03 20 00 00 	cmpb   $0x0,0x200349(%rip)        # 200960 <_edata>
 617:	75 27                	jne    640 <__do_global_dtors_aux+0x30>
 619:	48 83 3d 07 03 20 00 	cmpq   $0x0,0x200307(%rip)        # 200928 <_DYNAMIC+0x1f0>
 620:	00 
 621:	55                   	push   %rbp
 622:	48 89 e5             	mov    %rsp,%rbp
 625:	74 0c                	je     633 <__do_global_dtors_aux+0x23>
 627:	48 8b 3d 2a 03 20 00 	mov    0x20032a(%rip),%rdi        # 200958 <__dso_handle>
 62e:	e8 3d ff ff ff       	callq  570 <__cxa_finalize@plt>
 633:	e8 48 ff ff ff       	callq  580 <deregister_tm_clones>
 638:	5d                   	pop    %rbp
 639:	c6 05 20 03 20 00 01 	movb   $0x1,0x200320(%rip)        # 200960 <_edata>
 640:	f3 c3                	repz retq 
 642:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
 649:	1f 84 00 00 00 00 00 

0000000000000650 <frame_dummy>:
 650:	48 8d 3d d9 00 20 00 	lea    0x2000d9(%rip),%rdi        # 200730 <__JCR_END__>
 657:	48 83 3f 00          	cmpq   $0x0,(%rdi)
 65b:	75 0b                	jne    668 <frame_dummy+0x18>
 65d:	e9 5e ff ff ff       	jmpq   5c0 <register_tm_clones>
 662:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
 668:	48 8b 05 a9 02 20 00 	mov    0x2002a9(%rip),%rax        # 200918 <_DYNAMIC+0x1e0>
 66f:	48 85 c0             	test   %rax,%rax
 672:	74 e9                	je     65d <frame_dummy+0xd>
 674:	55                   	push   %rbp
 675:	48 89 e5             	mov    %rsp,%rbp
 678:	ff d0                	callq  *%rax
 67a:	5d                   	pop    %rbp
 67b:	e9 40 ff ff ff       	jmpq   5c0 <register_tm_clones>

0000000000000680 <ngine_sc_node_name>:
 680:	48 85 f6             	test   %rsi,%rsi
 683:	74 0b                	je     690 <ngine_sc_node_name+0x10>
 685:	48 89 37             	mov    %rsi,(%rdi)
 688:	c3                   	retq   
 689:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
 690:	48 8b 07             	mov    (%rdi),%rax
 693:	c3                   	retq   

Дизасемблювання розділу .fini:

0000000000000694 <_fini>:
 694:	48 83 ec 08          	sub    $0x8,%rsp
 698:	48 83 c4 08          	add    $0x8,%rsp
 69c:	c3                   	retq   
