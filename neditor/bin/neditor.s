
./neditor:     формат файла elf64-x86-64


Дизасемблювання розділу .init:

0000000000400ac0 <_init>:
  400ac0:	48 83 ec 08          	sub    $0x8,%rsp
  400ac4:	48 8b 05 9d 09 20 00 	mov    0x20099d(%rip),%rax        # 601468 <_DYNAMIC+0x2a0>
  400acb:	48 85 c0             	test   %rax,%rax
  400ace:	74 05                	je     400ad5 <_init+0x15>
  400ad0:	e8 0b 01 00 00       	callq  400be0 <__gmon_start__@plt>
  400ad5:	48 83 c4 08          	add    $0x8,%rsp
  400ad9:	c3                   	retq   

Дизасемблювання розділу .plt:

0000000000400ae0 <printf@plt-0x10>:
  400ae0:	ff 35 92 09 20 00    	pushq  0x200992(%rip)        # 601478 <_GLOBAL_OFFSET_TABLE_+0x8>
  400ae6:	ff 25 94 09 20 00    	jmpq   *0x200994(%rip)        # 601480 <_GLOBAL_OFFSET_TABLE_+0x10>
  400aec:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400af0 <printf@plt>:
  400af0:	ff 25 92 09 20 00    	jmpq   *0x200992(%rip)        # 601488 <_GLOBAL_OFFSET_TABLE_+0x18>
  400af6:	68 00 00 00 00       	pushq  $0x0
  400afb:	e9 e0 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b00 <ngine_sc_node_create@plt>:
  400b00:	ff 25 8a 09 20 00    	jmpq   *0x20098a(%rip)        # 601490 <_GLOBAL_OFFSET_TABLE_+0x20>
  400b06:	68 01 00 00 00       	pushq  $0x1
  400b0b:	e9 d0 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b10 <dynlib_getsym@plt>:
  400b10:	ff 25 82 09 20 00    	jmpq   *0x200982(%rip)        # 601498 <_GLOBAL_OFFSET_TABLE_+0x28>
  400b16:	68 02 00 00 00       	pushq  $0x2
  400b1b:	e9 c0 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b20 <dynlib_open@plt>:
  400b20:	ff 25 7a 09 20 00    	jmpq   *0x20097a(%rip)        # 6014a0 <_GLOBAL_OFFSET_TABLE_+0x30>
  400b26:	68 03 00 00 00       	pushq  $0x3
  400b2b:	e9 b0 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b30 <ngine_render_create@plt>:
  400b30:	ff 25 72 09 20 00    	jmpq   *0x200972(%rip)        # 6014a8 <_GLOBAL_OFFSET_TABLE_+0x38>
  400b36:	68 04 00 00 00       	pushq  $0x4
  400b3b:	e9 a0 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b40 <tree_add_child@plt>:
  400b40:	ff 25 6a 09 20 00    	jmpq   *0x20096a(%rip)        # 6014b0 <_GLOBAL_OFFSET_TABLE_+0x40>
  400b46:	68 05 00 00 00       	pushq  $0x5
  400b4b:	e9 90 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b50 <FMOD_System_CreateSound@plt>:
  400b50:	ff 25 62 09 20 00    	jmpq   *0x200962(%rip)        # 6014b8 <_GLOBAL_OFFSET_TABLE_+0x48>
  400b56:	68 06 00 00 00       	pushq  $0x6
  400b5b:	e9 80 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b60 <ngine_input_create@plt>:
  400b60:	ff 25 5a 09 20 00    	jmpq   *0x20095a(%rip)        # 6014c0 <_GLOBAL_OFFSET_TABLE_+0x50>
  400b66:	68 07 00 00 00       	pushq  $0x7
  400b6b:	e9 70 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b70 <malloc@plt>:
  400b70:	ff 25 52 09 20 00    	jmpq   *0x200952(%rip)        # 6014c8 <_GLOBAL_OFFSET_TABLE_+0x58>
  400b76:	68 08 00 00 00       	pushq  $0x8
  400b7b:	e9 60 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b80 <ngine_window_create@plt>:
  400b80:	ff 25 4a 09 20 00    	jmpq   *0x20094a(%rip)        # 6014d0 <_GLOBAL_OFFSET_TABLE_+0x60>
  400b86:	68 09 00 00 00       	pushq  $0x9
  400b8b:	e9 50 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400b90 <ngine_frame@plt>:
  400b90:	ff 25 42 09 20 00    	jmpq   *0x200942(%rip)        # 6014d8 <_GLOBAL_OFFSET_TABLE_+0x68>
  400b96:	68 0a 00 00 00       	pushq  $0xa
  400b9b:	e9 40 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400ba0 <speaker_play_fmod@plt>:
  400ba0:	ff 25 3a 09 20 00    	jmpq   *0x20093a(%rip)        # 6014e0 <_GLOBAL_OFFSET_TABLE_+0x70>
  400ba6:	68 0b 00 00 00       	pushq  $0xb
  400bab:	e9 30 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400bb0 <gettimeofday@plt>:
  400bb0:	ff 25 32 09 20 00    	jmpq   *0x200932(%rip)        # 6014e8 <_GLOBAL_OFFSET_TABLE_+0x78>
  400bb6:	68 0c 00 00 00       	pushq  $0xc
  400bbb:	e9 20 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400bc0 <ngine_create@plt>:
  400bc0:	ff 25 2a 09 20 00    	jmpq   *0x20092a(%rip)        # 6014f0 <_GLOBAL_OFFSET_TABLE_+0x80>
  400bc6:	68 0d 00 00 00       	pushq  $0xd
  400bcb:	e9 10 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400bd0 <__libc_start_main@plt>:
  400bd0:	ff 25 22 09 20 00    	jmpq   *0x200922(%rip)        # 6014f8 <_GLOBAL_OFFSET_TABLE_+0x88>
  400bd6:	68 0e 00 00 00       	pushq  $0xe
  400bdb:	e9 00 ff ff ff       	jmpq   400ae0 <_init+0x20>

0000000000400be0 <__gmon_start__@plt>:
  400be0:	ff 25 1a 09 20 00    	jmpq   *0x20091a(%rip)        # 601500 <_GLOBAL_OFFSET_TABLE_+0x90>
  400be6:	68 0f 00 00 00       	pushq  $0xf
  400beb:	e9 f0 fe ff ff       	jmpq   400ae0 <_init+0x20>

Дизасемблювання розділу .text:

0000000000400bf0 <_start>:
  400bf0:	31 ed                	xor    %ebp,%ebp
  400bf2:	49 89 d1             	mov    %rdx,%r9
  400bf5:	5e                   	pop    %rsi
  400bf6:	48 89 e2             	mov    %rsp,%rdx
  400bf9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400bfd:	50                   	push   %rax
  400bfe:	54                   	push   %rsp
  400bff:	49 c7 c0 e0 0f 40 00 	mov    $0x400fe0,%r8
  400c06:	48 c7 c1 70 0f 40 00 	mov    $0x400f70,%rcx
  400c0d:	48 c7 c7 e6 0c 40 00 	mov    $0x400ce6,%rdi
  400c14:	e8 b7 ff ff ff       	callq  400bd0 <__libc_start_main@plt>
  400c19:	f4                   	hlt    
  400c1a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400c20 <deregister_tm_clones>:
  400c20:	b8 1f 15 60 00       	mov    $0x60151f,%eax
  400c25:	55                   	push   %rbp
  400c26:	48 2d 18 15 60 00    	sub    $0x601518,%rax
  400c2c:	48 83 f8 0e          	cmp    $0xe,%rax
  400c30:	48 89 e5             	mov    %rsp,%rbp
  400c33:	76 1b                	jbe    400c50 <deregister_tm_clones+0x30>
  400c35:	b8 00 00 00 00       	mov    $0x0,%eax
  400c3a:	48 85 c0             	test   %rax,%rax
  400c3d:	74 11                	je     400c50 <deregister_tm_clones+0x30>
  400c3f:	5d                   	pop    %rbp
  400c40:	bf 18 15 60 00       	mov    $0x601518,%edi
  400c45:	ff e0                	jmpq   *%rax
  400c47:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400c4e:	00 00 
  400c50:	5d                   	pop    %rbp
  400c51:	c3                   	retq   
  400c52:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  400c59:	1f 84 00 00 00 00 00 

0000000000400c60 <register_tm_clones>:
  400c60:	be 18 15 60 00       	mov    $0x601518,%esi
  400c65:	55                   	push   %rbp
  400c66:	48 81 ee 18 15 60 00 	sub    $0x601518,%rsi
  400c6d:	48 c1 fe 03          	sar    $0x3,%rsi
  400c71:	48 89 e5             	mov    %rsp,%rbp
  400c74:	48 89 f0             	mov    %rsi,%rax
  400c77:	48 c1 e8 3f          	shr    $0x3f,%rax
  400c7b:	48 01 c6             	add    %rax,%rsi
  400c7e:	48 d1 fe             	sar    %rsi
  400c81:	74 15                	je     400c98 <register_tm_clones+0x38>
  400c83:	b8 00 00 00 00       	mov    $0x0,%eax
  400c88:	48 85 c0             	test   %rax,%rax
  400c8b:	74 0b                	je     400c98 <register_tm_clones+0x38>
  400c8d:	5d                   	pop    %rbp
  400c8e:	bf 18 15 60 00       	mov    $0x601518,%edi
  400c93:	ff e0                	jmpq   *%rax
  400c95:	0f 1f 00             	nopl   (%rax)
  400c98:	5d                   	pop    %rbp
  400c99:	c3                   	retq   
  400c9a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400ca0 <__do_global_dtors_aux>:
  400ca0:	80 3d 99 08 20 00 00 	cmpb   $0x0,0x200899(%rip)        # 601540 <completed.6617>
  400ca7:	75 11                	jne    400cba <__do_global_dtors_aux+0x1a>
  400ca9:	55                   	push   %rbp
  400caa:	48 89 e5             	mov    %rsp,%rbp
  400cad:	e8 6e ff ff ff       	callq  400c20 <deregister_tm_clones>
  400cb2:	5d                   	pop    %rbp
  400cb3:	c6 05 86 08 20 00 01 	movb   $0x1,0x200886(%rip)        # 601540 <completed.6617>
  400cba:	f3 c3                	repz retq 
  400cbc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400cc0 <frame_dummy>:
  400cc0:	bf c0 11 60 00       	mov    $0x6011c0,%edi
  400cc5:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  400cc9:	75 05                	jne    400cd0 <frame_dummy+0x10>
  400ccb:	eb 93                	jmp    400c60 <register_tm_clones>
  400ccd:	0f 1f 00             	nopl   (%rax)
  400cd0:	b8 00 00 00 00       	mov    $0x0,%eax
  400cd5:	48 85 c0             	test   %rax,%rax
  400cd8:	74 f1                	je     400ccb <frame_dummy+0xb>
  400cda:	55                   	push   %rbp
  400cdb:	48 89 e5             	mov    %rsp,%rbp
  400cde:	ff d0                	callq  *%rax
  400ce0:	5d                   	pop    %rbp
  400ce1:	e9 7a ff ff ff       	jmpq   400c60 <register_tm_clones>

0000000000400ce6 <main>:
  400ce6:	55                   	push   %rbp
  400ce7:	48 89 e5             	mov    %rsp,%rbp
  400cea:	53                   	push   %rbx
  400ceb:	48 81 ec 98 00 00 00 	sub    $0x98,%rsp
  400cf2:	89 bd 7c ff ff ff    	mov    %edi,-0x84(%rbp)
  400cf8:	48 89 b5 70 ff ff ff 	mov    %rsi,-0x90(%rbp)
  400cff:	bf 08 00 00 00       	mov    $0x8,%edi
  400d04:	e8 67 fe ff ff       	callq  400b70 <malloc@plt>
  400d09:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  400d0d:	b8 00 00 00 00       	mov    $0x0,%eax
  400d12:	e8 a9 fe ff ff       	callq  400bc0 <ngine_create@plt>
  400d17:	48 89 c2             	mov    %rax,%rdx
  400d1a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d1e:	48 89 10             	mov    %rdx,(%rax)
  400d21:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d25:	48 8b 00             	mov    (%rax),%rax
  400d28:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  400d2c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d30:	48 8b 18             	mov    (%rax),%rbx
  400d33:	b9 58 02 00 00       	mov    $0x258,%ecx
  400d38:	ba 00 04 00 00       	mov    $0x400,%edx
  400d3d:	be 00 00 00 00       	mov    $0x0,%esi
  400d42:	bf f8 0f 40 00       	mov    $0x400ff8,%edi
  400d47:	e8 34 fe ff ff       	callq  400b80 <ngine_window_create@plt>
  400d4c:	48 89 03             	mov    %rax,(%rbx)
  400d4f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d53:	48 8b 18             	mov    (%rax),%rbx
  400d56:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d5a:	48 8b 00             	mov    (%rax),%rax
  400d5d:	48 8b 00             	mov    (%rax),%rax
  400d60:	48 89 c7             	mov    %rax,%rdi
  400d63:	e8 f8 fd ff ff       	callq  400b60 <ngine_input_create@plt>
  400d68:	48 89 43 28          	mov    %rax,0x28(%rbx)
  400d6c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d70:	48 8b 18             	mov    (%rax),%rbx
  400d73:	b8 00 00 00 00       	mov    $0x0,%eax
  400d78:	e8 b3 fd ff ff       	callq  400b30 <ngine_render_create@plt>
  400d7d:	48 89 43 20          	mov    %rax,0x20(%rbx)
  400d81:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400d85:	48 8b 00             	mov    (%rax),%rax
  400d88:	be 0c 10 40 00       	mov    $0x40100c,%esi
  400d8d:	48 89 c7             	mov    %rax,%rdi
  400d90:	e8 8b fd ff ff       	callq  400b20 <dynlib_open@plt>
  400d95:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  400d99:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  400d9d:	be 0c 10 40 00       	mov    $0x40100c,%esi
  400da2:	48 89 c7             	mov    %rax,%rdi
  400da5:	e8 66 fd ff ff       	callq  400b10 <dynlib_getsym@plt>
  400daa:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  400dae:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  400db2:	be 19 10 40 00       	mov    $0x401019,%esi
  400db7:	48 89 c7             	mov    %rax,%rdi
  400dba:	e8 51 fd ff ff       	callq  400b10 <dynlib_getsym@plt>
  400dbf:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  400dc3:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400dc7:	48 8b 18             	mov    (%rax),%rbx
  400dca:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400dce:	48 8b 10             	mov    (%rax),%rdx
  400dd1:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  400dd5:	48 89 d7             	mov    %rdx,%rdi
  400dd8:	ff d0                	callq  *%rax
  400dda:	48 89 43 08          	mov    %rax,0x8(%rbx)
  400dde:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400de2:	48 8b 00             	mov    (%rax),%rax
  400de5:	48 8b 40 08          	mov    0x8(%rax),%rax
  400de9:	ba 04 00 00 00       	mov    $0x4,%edx
  400dee:	be 2a 10 40 00       	mov    $0x40102a,%esi
  400df3:	48 89 c7             	mov    %rax,%rdi
  400df6:	e8 05 fd ff ff       	callq  400b00 <ngine_sc_node_create@plt>
  400dfb:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  400dff:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  400e03:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  400e07:	48 8b 12             	mov    (%rdx),%rdx
  400e0a:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  400e0e:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  400e12:	48 89 c6             	mov    %rax,%rsi
  400e15:	48 89 d7             	mov    %rdx,%rdi
  400e18:	e8 23 fd ff ff       	callq  400b40 <tree_add_child@plt>
  400e1d:	48 8b 55 b8          	mov    -0x48(%rbp),%rdx
  400e21:	8b 05 41 02 00 00    	mov    0x241(%rip),%eax        # 401068 <_IO_stdin_used+0x78>
  400e27:	89 42 30             	mov    %eax,0x30(%rdx)
  400e2a:	48 c7 45 a0 00 00 00 	movq   $0x0,-0x60(%rbp)
  400e31:	00 
  400e32:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400e36:	48 8b 00             	mov    (%rax),%rax
  400e39:	48 8b 40 30          	mov    0x30(%rax),%rax
  400e3d:	48 8d 55 a0          	lea    -0x60(%rbp),%rdx
  400e41:	49 89 d0             	mov    %rdx,%r8
  400e44:	b9 00 00 00 00       	mov    $0x0,%ecx
  400e49:	ba 50 00 00 00       	mov    $0x50,%edx
  400e4e:	be 33 10 40 00       	mov    $0x401033,%esi
  400e53:	48 89 c7             	mov    %rax,%rdi
  400e56:	e8 f5 fc ff ff       	callq  400b50 <FMOD_System_CreateSound@plt>
  400e5b:	48 8b 55 a0          	mov    -0x60(%rbp),%rdx
  400e5f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400e63:	48 8b 00             	mov    (%rax),%rax
  400e66:	48 8b 70 30          	mov    0x30(%rax),%rsi
  400e6a:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  400e6e:	b9 00 00 00 00       	mov    $0x0,%ecx
  400e73:	48 89 c7             	mov    %rax,%rdi
  400e76:	e8 25 fd ff ff       	callq  400ba0 <speaker_play_fmod@plt>
  400e7b:	48 8d 45 90          	lea    -0x70(%rbp),%rax
  400e7f:	be 00 00 00 00       	mov    $0x0,%esi
  400e84:	48 89 c7             	mov    %rax,%rdi
  400e87:	e8 24 fd ff ff       	callq  400bb0 <gettimeofday@plt>
  400e8c:	48 8b 45 90          	mov    -0x70(%rbp),%rax
  400e90:	66 0f ef c9          	pxor   %xmm1,%xmm1
  400e94:	f2 48 0f 2a c8       	cvtsi2sd %rax,%xmm1
  400e99:	48 8b 45 98          	mov    -0x68(%rbp),%rax
  400e9d:	66 0f ef c0          	pxor   %xmm0,%xmm0
  400ea1:	f2 48 0f 2a c0       	cvtsi2sd %rax,%xmm0
  400ea6:	f2 0f 10 15 c2 01 00 	movsd  0x1c2(%rip),%xmm2        # 401070 <_IO_stdin_used+0x80>
  400ead:	00 
  400eae:	f2 0f 5e c2          	divsd  %xmm2,%xmm0
  400eb2:	f2 0f 58 c8          	addsd  %xmm0,%xmm1
  400eb6:	66 48 0f 7e c8       	movq   %xmm1,%rax
  400ebb:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  400ebf:	48 8d 45 80          	lea    -0x80(%rbp),%rax
  400ec3:	be 00 00 00 00       	mov    $0x0,%esi
  400ec8:	48 89 c7             	mov    %rax,%rdi
  400ecb:	e8 e0 fc ff ff       	callq  400bb0 <gettimeofday@plt>
  400ed0:	48 8b 45 80          	mov    -0x80(%rbp),%rax
  400ed4:	66 0f ef c9          	pxor   %xmm1,%xmm1
  400ed8:	f2 48 0f 2a c8       	cvtsi2sd %rax,%xmm1
  400edd:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  400ee1:	66 0f ef c0          	pxor   %xmm0,%xmm0
  400ee5:	f2 48 0f 2a c0       	cvtsi2sd %rax,%xmm0
  400eea:	f2 0f 10 15 7e 01 00 	movsd  0x17e(%rip),%xmm2        # 401070 <_IO_stdin_used+0x80>
  400ef1:	00 
  400ef2:	f2 0f 5e c2          	divsd  %xmm2,%xmm0
  400ef6:	f2 0f 58 c8          	addsd  %xmm0,%xmm1
  400efa:	66 48 0f 7e c8       	movq   %xmm1,%rax
  400eff:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  400f03:	f2 0f 10 45 b0       	movsd  -0x50(%rbp),%xmm0
  400f08:	f2 0f 5c 45 e8       	subsd  -0x18(%rbp),%xmm0
  400f0d:	66 48 0f 7e c0       	movq   %xmm0,%rax
  400f12:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  400f16:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  400f1a:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  400f1e:	f2 0f 5a 45 a8       	cvtsd2ss -0x58(%rbp),%xmm0
  400f23:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  400f27:	48 8b 00             	mov    (%rax),%rax
  400f2a:	48 89 c7             	mov    %rax,%rdi
  400f2d:	e8 5e fc ff ff       	callq  400b90 <ngine_frame@plt>
  400f32:	f2 0f 10 05 3e 01 00 	movsd  0x13e(%rip),%xmm0        # 401078 <_IO_stdin_used+0x88>
  400f39:	00 
  400f3a:	f2 0f 5e 45 a8       	divsd  -0x58(%rbp),%xmm0
  400f3f:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  400f43:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
  400f4a:	f2 0f 10 8d 68 ff ff 	movsd  -0x98(%rbp),%xmm1
  400f51:	ff 
  400f52:	bf 4d 10 40 00       	mov    $0x40104d,%edi
  400f57:	b8 02 00 00 00       	mov    $0x2,%eax
  400f5c:	e8 8f fb ff ff       	callq  400af0 <printf@plt>
  400f61:	e9 59 ff ff ff       	jmpq   400ebf <main+0x1d9>
  400f66:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400f6d:	00 00 00 

0000000000400f70 <__libc_csu_init>:
  400f70:	41 57                	push   %r15
  400f72:	41 56                	push   %r14
  400f74:	41 89 ff             	mov    %edi,%r15d
  400f77:	41 55                	push   %r13
  400f79:	41 54                	push   %r12
  400f7b:	4c 8d 25 2e 02 20 00 	lea    0x20022e(%rip),%r12        # 6011b0 <__frame_dummy_init_array_entry>
  400f82:	55                   	push   %rbp
  400f83:	48 8d 2d 2e 02 20 00 	lea    0x20022e(%rip),%rbp        # 6011b8 <__init_array_end>
  400f8a:	53                   	push   %rbx
  400f8b:	49 89 f6             	mov    %rsi,%r14
  400f8e:	49 89 d5             	mov    %rdx,%r13
  400f91:	31 db                	xor    %ebx,%ebx
  400f93:	4c 29 e5             	sub    %r12,%rbp
  400f96:	48 83 ec 08          	sub    $0x8,%rsp
  400f9a:	48 c1 fd 03          	sar    $0x3,%rbp
  400f9e:	e8 1d fb ff ff       	callq  400ac0 <_init>
  400fa3:	48 85 ed             	test   %rbp,%rbp
  400fa6:	74 1e                	je     400fc6 <__libc_csu_init+0x56>
  400fa8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  400faf:	00 
  400fb0:	4c 89 ea             	mov    %r13,%rdx
  400fb3:	4c 89 f6             	mov    %r14,%rsi
  400fb6:	44 89 ff             	mov    %r15d,%edi
  400fb9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  400fbd:	48 83 c3 01          	add    $0x1,%rbx
  400fc1:	48 39 eb             	cmp    %rbp,%rbx
  400fc4:	75 ea                	jne    400fb0 <__libc_csu_init+0x40>
  400fc6:	48 83 c4 08          	add    $0x8,%rsp
  400fca:	5b                   	pop    %rbx
  400fcb:	5d                   	pop    %rbp
  400fcc:	41 5c                	pop    %r12
  400fce:	41 5d                	pop    %r13
  400fd0:	41 5e                	pop    %r14
  400fd2:	41 5f                	pop    %r15
  400fd4:	c3                   	retq   
  400fd5:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  400fdc:	00 00 00 00 

0000000000400fe0 <__libc_csu_fini>:
  400fe0:	f3 c3                	repz retq 

Дизасемблювання розділу .fini:

0000000000400fe4 <_fini>:
  400fe4:	48 83 ec 08          	sub    $0x8,%rsp
  400fe8:	48 83 c4 08          	add    $0x8,%rsp
  400fec:	c3                   	retq   
