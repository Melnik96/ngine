
./serialize:     формат файла elf64-x86-64


Дизасемблювання розділу .init:

0000000000400b40 <_init>:
  400b40:	48 83 ec 08          	sub    $0x8,%rsp
  400b44:	48 8b 05 3d 10 20 00 	mov    0x20103d(%rip),%rax        # 601b88 <_DYNAMIC+0x1d0>
  400b4b:	48 85 c0             	test   %rax,%rax
  400b4e:	74 05                	je     400b55 <_init+0x15>
  400b50:	e8 5b 00 00 00       	callq  400bb0 <__gmon_start__@plt>
  400b55:	48 83 c4 08          	add    $0x8,%rsp
  400b59:	c3                   	retq   

Дизасемблювання розділу .plt:

0000000000400b60 <free@plt-0x10>:
  400b60:	ff 35 32 10 20 00    	pushq  0x201032(%rip)        # 601b98 <_GLOBAL_OFFSET_TABLE_+0x8>
  400b66:	ff 25 34 10 20 00    	jmpq   *0x201034(%rip)        # 601ba0 <_GLOBAL_OFFSET_TABLE_+0x10>
  400b6c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400b70 <free@plt>:
  400b70:	ff 25 32 10 20 00    	jmpq   *0x201032(%rip)        # 601ba8 <_GLOBAL_OFFSET_TABLE_+0x18>
  400b76:	68 00 00 00 00       	pushq  $0x0
  400b7b:	e9 e0 ff ff ff       	jmpq   400b60 <_init+0x20>

0000000000400b80 <fclose@plt>:
  400b80:	ff 25 2a 10 20 00    	jmpq   *0x20102a(%rip)        # 601bb0 <_GLOBAL_OFFSET_TABLE_+0x20>
  400b86:	68 01 00 00 00       	pushq  $0x1
  400b8b:	e9 d0 ff ff ff       	jmpq   400b60 <_init+0x20>

0000000000400b90 <__libc_start_main@plt>:
  400b90:	ff 25 22 10 20 00    	jmpq   *0x201022(%rip)        # 601bb8 <_GLOBAL_OFFSET_TABLE_+0x28>
  400b96:	68 02 00 00 00       	pushq  $0x2
  400b9b:	e9 c0 ff ff ff       	jmpq   400b60 <_init+0x20>

0000000000400ba0 <calloc@plt>:
  400ba0:	ff 25 1a 10 20 00    	jmpq   *0x20101a(%rip)        # 601bc0 <_GLOBAL_OFFSET_TABLE_+0x30>
  400ba6:	68 03 00 00 00       	pushq  $0x3
  400bab:	e9 b0 ff ff ff       	jmpq   400b60 <_init+0x20>

0000000000400bb0 <__gmon_start__@plt>:
  400bb0:	ff 25 12 10 20 00    	jmpq   *0x201012(%rip)        # 601bc8 <_GLOBAL_OFFSET_TABLE_+0x38>
  400bb6:	68 04 00 00 00       	pushq  $0x4
  400bbb:	e9 a0 ff ff ff       	jmpq   400b60 <_init+0x20>

0000000000400bc0 <realloc@plt>:
  400bc0:	ff 25 0a 10 20 00    	jmpq   *0x20100a(%rip)        # 601bd0 <_GLOBAL_OFFSET_TABLE_+0x40>
  400bc6:	68 05 00 00 00       	pushq  $0x5
  400bcb:	e9 90 ff ff ff       	jmpq   400b60 <_init+0x20>

0000000000400bd0 <fopen@plt>:
  400bd0:	ff 25 02 10 20 00    	jmpq   *0x201002(%rip)        # 601bd8 <_GLOBAL_OFFSET_TABLE_+0x48>
  400bd6:	68 06 00 00 00       	pushq  $0x6
  400bdb:	e9 80 ff ff ff       	jmpq   400b60 <_init+0x20>

0000000000400be0 <fwrite@plt>:
  400be0:	ff 25 fa 0f 20 00    	jmpq   *0x200ffa(%rip)        # 601be0 <_GLOBAL_OFFSET_TABLE_+0x50>
  400be6:	68 07 00 00 00       	pushq  $0x7
  400beb:	e9 70 ff ff ff       	jmpq   400b60 <_init+0x20>

Дизасемблювання розділу .text:

0000000000400bf0 <main>:
  400bf0:	41 54                	push   %r12
  400bf2:	55                   	push   %rbp
  400bf3:	41 bc 00 7d 00 00    	mov    $0x7d00,%r12d
  400bf9:	53                   	push   %rbx
  400bfa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  400c00:	be 10 00 00 00       	mov    $0x10,%esi
  400c05:	bf 01 00 00 00       	mov    $0x1,%edi
  400c0a:	e8 91 ff ff ff       	callq  400ba0 <calloc@plt>
  400c0f:	be 10 00 00 00       	mov    $0x10,%esi
  400c14:	48 89 c3             	mov    %rax,%rbx
  400c17:	bf 01 00 00 00       	mov    $0x1,%edi
  400c1c:	c7 00 48 00 00 00    	movl   $0x48,(%rax)
  400c22:	48 c7 40 08 56 00 00 	movq   $0x56,0x8(%rax)
  400c29:	00 
  400c2a:	e8 71 ff ff ff       	callq  400ba0 <calloc@plt>
  400c2f:	31 f6                	xor    %esi,%esi
  400c31:	48 89 c7             	mov    %rax,%rdi
  400c34:	48 89 58 08          	mov    %rbx,0x8(%rax)
  400c38:	c7 00 2a 00 00 00    	movl   $0x2a,(%rax)
  400c3e:	c6 40 04 22          	movb   $0x22,0x4(%rax)
  400c42:	e8 69 01 00 00       	callq  400db0 <a__serializer>
  400c47:	be b4 14 40 00       	mov    $0x4014b4,%esi
  400c4c:	bf b6 14 40 00       	mov    $0x4014b6,%edi
  400c51:	48 89 c3             	mov    %rax,%rbx
  400c54:	e8 77 ff ff ff       	callq  400bd0 <fopen@plt>
  400c59:	48 85 c0             	test   %rax,%rax
  400c5c:	48 89 c5             	mov    %rax,%rbp
  400c5f:	74 14                	je     400c75 <main+0x85>
  400c61:	48 8b 73 08          	mov    0x8(%rbx),%rsi
  400c65:	48 8b 3b             	mov    (%rbx),%rdi
  400c68:	48 89 c1             	mov    %rax,%rcx
  400c6b:	ba 01 00 00 00       	mov    $0x1,%edx
  400c70:	e8 6b ff ff ff       	callq  400be0 <fwrite@plt>
  400c75:	48 89 ef             	mov    %rbp,%rdi
  400c78:	e8 03 ff ff ff       	callq  400b80 <fclose@plt>
  400c7d:	48 8b 3b             	mov    (%rbx),%rdi
  400c80:	31 f6                	xor    %esi,%esi
  400c82:	e8 29 03 00 00       	callq  400fb0 <a__deserializer>
  400c87:	48 8b 3b             	mov    (%rbx),%rdi
  400c8a:	e8 e1 fe ff ff       	callq  400b70 <free@plt>
  400c8f:	48 89 df             	mov    %rbx,%rdi
  400c92:	e8 d9 fe ff ff       	callq  400b70 <free@plt>
  400c97:	41 83 ec 01          	sub    $0x1,%r12d
  400c9b:	0f 85 5f ff ff ff    	jne    400c00 <main+0x10>
  400ca1:	5b                   	pop    %rbx
  400ca2:	31 c0                	xor    %eax,%eax
  400ca4:	5d                   	pop    %rbp
  400ca5:	41 5c                	pop    %r12
  400ca7:	c3                   	retq   

0000000000400ca8 <_start>:
  400ca8:	31 ed                	xor    %ebp,%ebp
  400caa:	49 89 d1             	mov    %rdx,%r9
  400cad:	5e                   	pop    %rsi
  400cae:	48 89 e2             	mov    %rsp,%rdx
  400cb1:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400cb5:	50                   	push   %rax
  400cb6:	54                   	push   %rsp
  400cb7:	49 c7 c0 a0 14 40 00 	mov    $0x4014a0,%r8
  400cbe:	48 c7 c1 30 14 40 00 	mov    $0x401430,%rcx
  400cc5:	48 c7 c7 f0 0b 40 00 	mov    $0x400bf0,%rdi
  400ccc:	e8 bf fe ff ff       	callq  400b90 <__libc_start_main@plt>
  400cd1:	f4                   	hlt    
  400cd2:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400cd9:	00 00 00 
  400cdc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400ce0 <deregister_tm_clones>:
  400ce0:	b8 ff 1b 60 00       	mov    $0x601bff,%eax
  400ce5:	55                   	push   %rbp
  400ce6:	48 2d f8 1b 60 00    	sub    $0x601bf8,%rax
  400cec:	48 83 f8 0e          	cmp    $0xe,%rax
  400cf0:	48 89 e5             	mov    %rsp,%rbp
  400cf3:	76 1b                	jbe    400d10 <deregister_tm_clones+0x30>
  400cf5:	b8 00 00 00 00       	mov    $0x0,%eax
  400cfa:	48 85 c0             	test   %rax,%rax
  400cfd:	74 11                	je     400d10 <deregister_tm_clones+0x30>
  400cff:	5d                   	pop    %rbp
  400d00:	bf f8 1b 60 00       	mov    $0x601bf8,%edi
  400d05:	ff e0                	jmpq   *%rax
  400d07:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400d0e:	00 00 
  400d10:	5d                   	pop    %rbp
  400d11:	c3                   	retq   
  400d12:	66 66 66 66 66 2e 0f 	data32 data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  400d19:	1f 84 00 00 00 00 00 

0000000000400d20 <register_tm_clones>:
  400d20:	be f8 1b 60 00       	mov    $0x601bf8,%esi
  400d25:	55                   	push   %rbp
  400d26:	48 81 ee f8 1b 60 00 	sub    $0x601bf8,%rsi
  400d2d:	48 c1 fe 03          	sar    $0x3,%rsi
  400d31:	48 89 e5             	mov    %rsp,%rbp
  400d34:	48 89 f0             	mov    %rsi,%rax
  400d37:	48 c1 e8 3f          	shr    $0x3f,%rax
  400d3b:	48 01 c6             	add    %rax,%rsi
  400d3e:	48 d1 fe             	sar    %rsi
  400d41:	74 15                	je     400d58 <register_tm_clones+0x38>
  400d43:	b8 00 00 00 00       	mov    $0x0,%eax
  400d48:	48 85 c0             	test   %rax,%rax
  400d4b:	74 0b                	je     400d58 <register_tm_clones+0x38>
  400d4d:	5d                   	pop    %rbp
  400d4e:	bf f8 1b 60 00       	mov    $0x601bf8,%edi
  400d53:	ff e0                	jmpq   *%rax
  400d55:	0f 1f 00             	nopl   (%rax)
  400d58:	5d                   	pop    %rbp
  400d59:	c3                   	retq   
  400d5a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400d60 <__do_global_dtors_aux>:
  400d60:	80 3d 91 0e 20 00 00 	cmpb   $0x0,0x200e91(%rip)        # 601bf8 <_edata>
  400d67:	75 11                	jne    400d7a <__do_global_dtors_aux+0x1a>
  400d69:	55                   	push   %rbp
  400d6a:	48 89 e5             	mov    %rsp,%rbp
  400d6d:	e8 6e ff ff ff       	callq  400ce0 <deregister_tm_clones>
  400d72:	5d                   	pop    %rbp
  400d73:	c6 05 7e 0e 20 00 01 	movb   $0x1,0x200e7e(%rip)        # 601bf8 <_edata>
  400d7a:	f3 c3                	repz retq 
  400d7c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400d80 <frame_dummy>:
  400d80:	bf b0 19 60 00       	mov    $0x6019b0,%edi
  400d85:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  400d89:	75 05                	jne    400d90 <frame_dummy+0x10>
  400d8b:	eb 93                	jmp    400d20 <register_tm_clones>
  400d8d:	0f 1f 00             	nopl   (%rax)
  400d90:	b8 00 00 00 00       	mov    $0x0,%eax
  400d95:	48 85 c0             	test   %rax,%rax
  400d98:	74 f1                	je     400d8b <frame_dummy+0xb>
  400d9a:	55                   	push   %rbp
  400d9b:	48 89 e5             	mov    %rsp,%rbp
  400d9e:	ff d0                	callq  *%rax
  400da0:	5d                   	pop    %rbp
  400da1:	e9 7a ff ff ff       	jmpq   400d20 <register_tm_clones>
  400da6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400dad:	00 00 00 

0000000000400db0 <a__serializer>:
  400db0:	48 85 f6             	test   %rsi,%rsi
  400db3:	41 54                	push   %r12
  400db5:	55                   	push   %rbp
  400db6:	48 89 fd             	mov    %rdi,%rbp
  400db9:	53                   	push   %rbx
  400dba:	48 89 f3             	mov    %rsi,%rbx
  400dbd:	74 79                	je     400e38 <a__serializer+0x88>
  400dbf:	48 89 df             	mov    %rbx,%rdi
  400dc2:	be 10 00 00 00       	mov    $0x10,%esi
  400dc7:	e8 c4 03 00 00       	callq  401190 <serial_append>
  400dcc:	48 89 ee             	mov    %rbp,%rsi
  400dcf:	48 89 df             	mov    %rbx,%rdi
  400dd2:	e8 09 04 00 00       	callq  4011e0 <serial_add_ptr>
  400dd7:	8b 75 00             	mov    0x0(%rbp),%esi
  400dda:	48 89 df             	mov    %rbx,%rdi
  400ddd:	e8 8e 04 00 00       	callq  401270 <serial_write_int32>
  400de2:	0f be 75 04          	movsbl 0x4(%rbp),%esi
  400de6:	48 89 df             	mov    %rbx,%rdi
  400de9:	e8 72 04 00 00       	callq  401260 <serial_write_int8>
  400dee:	48 8b 75 08          	mov    0x8(%rbp),%rsi
  400df2:	48 89 df             	mov    %rbx,%rdi
  400df5:	e8 56 04 00 00       	callq  401250 <serial_write_ptr>
  400dfa:	48 8b 6d 08          	mov    0x8(%rbp),%rbp
  400dfe:	48 89 df             	mov    %rbx,%rdi
  400e01:	be 10 00 00 00       	mov    $0x10,%esi
  400e06:	e8 85 03 00 00       	callq  401190 <serial_append>
  400e0b:	48 89 df             	mov    %rbx,%rdi
  400e0e:	48 89 ee             	mov    %rbp,%rsi
  400e11:	e8 ca 03 00 00       	callq  4011e0 <serial_add_ptr>
  400e16:	8b 75 00             	mov    0x0(%rbp),%esi
  400e19:	48 89 df             	mov    %rbx,%rdi
  400e1c:	e8 4f 04 00 00       	callq  401270 <serial_write_int32>
  400e21:	48 8b 75 08          	mov    0x8(%rbp),%rsi
  400e25:	48 89 df             	mov    %rbx,%rdi
  400e28:	e8 53 04 00 00       	callq  401280 <serial_write_int64>
  400e2d:	5b                   	pop    %rbx
  400e2e:	31 c0                	xor    %eax,%eax
  400e30:	5d                   	pop    %rbp
  400e31:	41 5c                	pop    %r12
  400e33:	c3                   	retq   
  400e34:	0f 1f 40 00          	nopl   0x0(%rax)
  400e38:	31 c0                	xor    %eax,%eax
  400e3a:	e8 d1 02 00 00       	callq  401110 <serial_begin_write>
  400e3f:	be 10 00 00 00       	mov    $0x10,%esi
  400e44:	48 89 c3             	mov    %rax,%rbx
  400e47:	48 89 c7             	mov    %rax,%rdi
  400e4a:	e8 41 03 00 00       	callq  401190 <serial_append>
  400e4f:	48 89 ee             	mov    %rbp,%rsi
  400e52:	48 89 df             	mov    %rbx,%rdi
  400e55:	e8 86 03 00 00       	callq  4011e0 <serial_add_ptr>
  400e5a:	8b 75 00             	mov    0x0(%rbp),%esi
  400e5d:	48 89 df             	mov    %rbx,%rdi
  400e60:	e8 0b 04 00 00       	callq  401270 <serial_write_int32>
  400e65:	0f be 75 04          	movsbl 0x4(%rbp),%esi
  400e69:	48 89 df             	mov    %rbx,%rdi
  400e6c:	e8 ef 03 00 00       	callq  401260 <serial_write_int8>
  400e71:	48 8b 75 08          	mov    0x8(%rbp),%rsi
  400e75:	48 89 df             	mov    %rbx,%rdi
  400e78:	e8 d3 03 00 00       	callq  401250 <serial_write_ptr>
  400e7d:	48 85 db             	test   %rbx,%rbx
  400e80:	4c 8b 65 08          	mov    0x8(%rbp),%r12
  400e84:	75 4f                	jne    400ed5 <a__serializer+0x125>
  400e86:	31 c0                	xor    %eax,%eax
  400e88:	e8 83 02 00 00       	callq  401110 <serial_begin_write>
  400e8d:	be 10 00 00 00       	mov    $0x10,%esi
  400e92:	48 89 c5             	mov    %rax,%rbp
  400e95:	48 89 c7             	mov    %rax,%rdi
  400e98:	e8 f3 02 00 00       	callq  401190 <serial_append>
  400e9d:	4c 89 e6             	mov    %r12,%rsi
  400ea0:	48 89 ef             	mov    %rbp,%rdi
  400ea3:	e8 38 03 00 00       	callq  4011e0 <serial_add_ptr>
  400ea8:	41 8b 34 24          	mov    (%r12),%esi
  400eac:	48 89 ef             	mov    %rbp,%rdi
  400eaf:	e8 bc 03 00 00       	callq  401270 <serial_write_int32>
  400eb4:	49 8b 74 24 08       	mov    0x8(%r12),%rsi
  400eb9:	48 89 ef             	mov    %rbp,%rdi
  400ebc:	e8 bf 03 00 00       	callq  401280 <serial_write_int64>
  400ec1:	48 89 ef             	mov    %rbp,%rdi
  400ec4:	e8 c7 03 00 00       	callq  401290 <serial_end_write>
  400ec9:	48 89 df             	mov    %rbx,%rdi
  400ecc:	5b                   	pop    %rbx
  400ecd:	5d                   	pop    %rbp
  400ece:	41 5c                	pop    %r12
  400ed0:	e9 bb 03 00 00       	jmpq   401290 <serial_end_write>
  400ed5:	48 89 df             	mov    %rbx,%rdi
  400ed8:	be 10 00 00 00       	mov    $0x10,%esi
  400edd:	e8 ae 02 00 00       	callq  401190 <serial_append>
  400ee2:	4c 89 e6             	mov    %r12,%rsi
  400ee5:	48 89 df             	mov    %rbx,%rdi
  400ee8:	e8 f3 02 00 00       	callq  4011e0 <serial_add_ptr>
  400eed:	41 8b 34 24          	mov    (%r12),%esi
  400ef1:	48 89 df             	mov    %rbx,%rdi
  400ef4:	e8 77 03 00 00       	callq  401270 <serial_write_int32>
  400ef9:	49 8b 74 24 08       	mov    0x8(%r12),%rsi
  400efe:	48 89 df             	mov    %rbx,%rdi
  400f01:	e8 7a 03 00 00       	callq  401280 <serial_write_int64>
  400f06:	eb c1                	jmp    400ec9 <a__serializer+0x119>
  400f08:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  400f0f:	00 

0000000000400f10 <b__serializer>:
  400f10:	55                   	push   %rbp
  400f11:	53                   	push   %rbx
  400f12:	48 89 fd             	mov    %rdi,%rbp
  400f15:	48 89 f3             	mov    %rsi,%rbx
  400f18:	48 83 ec 08          	sub    $0x8,%rsp
  400f1c:	48 85 f6             	test   %rsi,%rsi
  400f1f:	74 3f                	je     400f60 <b__serializer+0x50>
  400f21:	48 89 df             	mov    %rbx,%rdi
  400f24:	be 10 00 00 00       	mov    $0x10,%esi
  400f29:	e8 62 02 00 00       	callq  401190 <serial_append>
  400f2e:	48 89 ee             	mov    %rbp,%rsi
  400f31:	48 89 df             	mov    %rbx,%rdi
  400f34:	e8 a7 02 00 00       	callq  4011e0 <serial_add_ptr>
  400f39:	8b 75 00             	mov    0x0(%rbp),%esi
  400f3c:	48 89 df             	mov    %rbx,%rdi
  400f3f:	e8 2c 03 00 00       	callq  401270 <serial_write_int32>
  400f44:	48 8b 75 08          	mov    0x8(%rbp),%rsi
  400f48:	48 89 df             	mov    %rbx,%rdi
  400f4b:	e8 30 03 00 00       	callq  401280 <serial_write_int64>
  400f50:	48 83 c4 08          	add    $0x8,%rsp
  400f54:	5b                   	pop    %rbx
  400f55:	5d                   	pop    %rbp
  400f56:	c3                   	retq   
  400f57:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400f5e:	00 00 
  400f60:	31 c0                	xor    %eax,%eax
  400f62:	e8 a9 01 00 00       	callq  401110 <serial_begin_write>
  400f67:	be 10 00 00 00       	mov    $0x10,%esi
  400f6c:	48 89 c3             	mov    %rax,%rbx
  400f6f:	48 89 c7             	mov    %rax,%rdi
  400f72:	e8 19 02 00 00       	callq  401190 <serial_append>
  400f77:	48 89 ee             	mov    %rbp,%rsi
  400f7a:	48 89 df             	mov    %rbx,%rdi
  400f7d:	e8 5e 02 00 00       	callq  4011e0 <serial_add_ptr>
  400f82:	8b 75 00             	mov    0x0(%rbp),%esi
  400f85:	48 89 df             	mov    %rbx,%rdi
  400f88:	e8 e3 02 00 00       	callq  401270 <serial_write_int32>
  400f8d:	48 8b 75 08          	mov    0x8(%rbp),%rsi
  400f91:	48 89 df             	mov    %rbx,%rdi
  400f94:	e8 e7 02 00 00       	callq  401280 <serial_write_int64>
  400f99:	48 83 c4 08          	add    $0x8,%rsp
  400f9d:	48 89 df             	mov    %rbx,%rdi
  400fa0:	5b                   	pop    %rbx
  400fa1:	5d                   	pop    %rbp
  400fa2:	e9 e9 02 00 00       	jmpq   401290 <serial_end_write>
  400fa7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400fae:	00 00 

0000000000400fb0 <a__deserializer>:
  400fb0:	41 55                	push   %r13
  400fb2:	41 54                	push   %r12
  400fb4:	55                   	push   %rbp
  400fb5:	53                   	push   %rbx
  400fb6:	48 89 f3             	mov    %rsi,%rbx
  400fb9:	48 83 ec 08          	sub    $0x8,%rsp
  400fbd:	48 85 f6             	test   %rsi,%rsi
  400fc0:	0f 84 8a 00 00 00    	je     401050 <a__deserializer+0xa0>
  400fc6:	be 10 00 00 00       	mov    $0x10,%esi
  400fcb:	bf 01 00 00 00       	mov    $0x1,%edi
  400fd0:	49 89 dd             	mov    %rbx,%r13
  400fd3:	e8 c8 fb ff ff       	callq  400ba0 <calloc@plt>
  400fd8:	48 89 df             	mov    %rbx,%rdi
  400fdb:	48 89 c5             	mov    %rax,%rbp
  400fde:	e8 1d 04 00 00       	callq  401400 <serial_read_int32>
  400fe3:	48 89 df             	mov    %rbx,%rdi
  400fe6:	89 45 00             	mov    %eax,0x0(%rbp)
  400fe9:	e8 f2 03 00 00       	callq  4013e0 <serial_read_int8>
  400fee:	48 89 df             	mov    %rbx,%rdi
  400ff1:	88 45 04             	mov    %al,0x4(%rbp)
  400ff4:	e8 c7 03 00 00       	callq  4013c0 <serial_read_ptr>
  400ff9:	48 89 df             	mov    %rbx,%rdi
  400ffc:	e8 9f 03 00 00       	callq  4013a0 <serial_read_push>
  401001:	be 10 00 00 00       	mov    $0x10,%esi
  401006:	bf 01 00 00 00       	mov    $0x1,%edi
  40100b:	e8 90 fb ff ff       	callq  400ba0 <calloc@plt>
  401010:	48 89 df             	mov    %rbx,%rdi
  401013:	49 89 c4             	mov    %rax,%r12
  401016:	e8 e5 03 00 00       	callq  401400 <serial_read_int32>
  40101b:	48 89 df             	mov    %rbx,%rdi
  40101e:	41 89 04 24          	mov    %eax,(%r12)
  401022:	e8 e9 03 00 00       	callq  401410 <serial_read_int64>
  401027:	4c 89 65 08          	mov    %r12,0x8(%rbp)
  40102b:	4c 89 ef             	mov    %r13,%rdi
  40102e:	49 89 44 24 08       	mov    %rax,0x8(%r12)
  401033:	e8 78 03 00 00       	callq  4013b0 <serial_read_pop>
  401038:	48 83 c4 08          	add    $0x8,%rsp
  40103c:	48 89 e8             	mov    %rbp,%rax
  40103f:	5b                   	pop    %rbx
  401040:	5d                   	pop    %rbp
  401041:	41 5c                	pop    %r12
  401043:	41 5d                	pop    %r13
  401045:	c3                   	retq   
  401046:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40104d:	00 00 00 
  401050:	e8 1b 03 00 00       	callq  401370 <serial_begin_read>
  401055:	be 10 00 00 00       	mov    $0x10,%esi
  40105a:	49 89 c5             	mov    %rax,%r13
  40105d:	bf 01 00 00 00       	mov    $0x1,%edi
  401062:	e8 39 fb ff ff       	callq  400ba0 <calloc@plt>
  401067:	4c 89 ef             	mov    %r13,%rdi
  40106a:	48 89 c5             	mov    %rax,%rbp
  40106d:	e8 8e 03 00 00       	callq  401400 <serial_read_int32>
  401072:	4c 89 ef             	mov    %r13,%rdi
  401075:	89 45 00             	mov    %eax,0x0(%rbp)
  401078:	e8 63 03 00 00       	callq  4013e0 <serial_read_int8>
  40107d:	4c 89 ef             	mov    %r13,%rdi
  401080:	88 45 04             	mov    %al,0x4(%rbp)
  401083:	e8 38 03 00 00       	callq  4013c0 <serial_read_ptr>
  401088:	4c 89 ef             	mov    %r13,%rdi
  40108b:	48 89 c3             	mov    %rax,%rbx
  40108e:	e8 0d 03 00 00       	callq  4013a0 <serial_read_push>
  401093:	4d 85 ed             	test   %r13,%r13
  401096:	75 10                	jne    4010a8 <a__deserializer+0xf8>
  401098:	48 89 df             	mov    %rbx,%rdi
  40109b:	e8 d0 02 00 00       	callq  401370 <serial_begin_read>
  4010a0:	48 89 c3             	mov    %rax,%rbx
  4010a3:	e9 59 ff ff ff       	jmpq   401001 <a__deserializer+0x51>
  4010a8:	4c 89 eb             	mov    %r13,%rbx
  4010ab:	e9 51 ff ff ff       	jmpq   401001 <a__deserializer+0x51>

00000000004010b0 <b__deserializer>:
  4010b0:	55                   	push   %rbp
  4010b1:	53                   	push   %rbx
  4010b2:	48 89 f3             	mov    %rsi,%rbx
  4010b5:	48 83 ec 08          	sub    $0x8,%rsp
  4010b9:	48 85 f6             	test   %rsi,%rsi
  4010bc:	74 3a                	je     4010f8 <b__deserializer+0x48>
  4010be:	be 10 00 00 00       	mov    $0x10,%esi
  4010c3:	bf 01 00 00 00       	mov    $0x1,%edi
  4010c8:	e8 d3 fa ff ff       	callq  400ba0 <calloc@plt>
  4010cd:	48 89 df             	mov    %rbx,%rdi
  4010d0:	48 89 c5             	mov    %rax,%rbp
  4010d3:	e8 28 03 00 00       	callq  401400 <serial_read_int32>
  4010d8:	48 89 df             	mov    %rbx,%rdi
  4010db:	89 45 00             	mov    %eax,0x0(%rbp)
  4010de:	e8 2d 03 00 00       	callq  401410 <serial_read_int64>
  4010e3:	48 89 45 08          	mov    %rax,0x8(%rbp)
  4010e7:	48 83 c4 08          	add    $0x8,%rsp
  4010eb:	48 89 e8             	mov    %rbp,%rax
  4010ee:	5b                   	pop    %rbx
  4010ef:	5d                   	pop    %rbp
  4010f0:	c3                   	retq   
  4010f1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  4010f8:	e8 73 02 00 00       	callq  401370 <serial_begin_read>
  4010fd:	48 89 c3             	mov    %rax,%rbx
  401100:	eb bc                	jmp    4010be <b__deserializer+0xe>
  401102:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  401109:	00 00 00 
  40110c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401110 <serial_begin_write>:
  401110:	41 55                	push   %r13
  401112:	41 54                	push   %r12
  401114:	be 30 00 00 00       	mov    $0x30,%esi
  401119:	55                   	push   %rbp
  40111a:	53                   	push   %rbx
  40111b:	bf 01 00 00 00       	mov    $0x1,%edi
  401120:	48 83 ec 08          	sub    $0x8,%rsp
  401124:	e8 77 fa ff ff       	callq  400ba0 <calloc@plt>
  401129:	be 10 00 00 00       	mov    $0x10,%esi
  40112e:	48 89 c5             	mov    %rax,%rbp
  401131:	bf 01 00 00 00       	mov    $0x1,%edi
  401136:	e8 65 fa ff ff       	callq  400ba0 <calloc@plt>
  40113b:	48 8b 55 00          	mov    0x0(%rbp),%rdx
  40113f:	48 8b 38             	mov    (%rax),%rdi
  401142:	49 89 c4             	mov    %rax,%r12
  401145:	48 89 45 28          	mov    %rax,0x28(%rbp)
  401149:	89 d3                	mov    %edx,%ebx
  40114b:	29 fb                	sub    %edi,%ebx
  40114d:	4c 8d 6b 05          	lea    0x5(%rbx),%r13
  401151:	4c 89 ee             	mov    %r13,%rsi
  401154:	e8 67 fa ff ff       	callq  400bc0 <realloc@plt>
  401159:	49 89 04 24          	mov    %rax,(%r12)
  40115d:	48 8b 45 28          	mov    0x28(%rbp),%rax
  401161:	48 89 da             	mov    %rbx,%rdx
  401164:	48 03 10             	add    (%rax),%rdx
  401167:	4c 89 68 08          	mov    %r13,0x8(%rax)
  40116b:	48 8d 42 04          	lea    0x4(%rdx),%rax
  40116f:	c7 02 00 00 00 00    	movl   $0x0,(%rdx)
  401175:	48 89 45 00          	mov    %rax,0x0(%rbp)
  401179:	c6 42 04 00          	movb   $0x0,0x4(%rdx)
  40117d:	48 89 e8             	mov    %rbp,%rax
  401180:	48 83 45 00 01       	addq   $0x1,0x0(%rbp)
  401185:	48 83 c4 08          	add    $0x8,%rsp
  401189:	5b                   	pop    %rbx
  40118a:	5d                   	pop    %rbp
  40118b:	41 5c                	pop    %r12
  40118d:	41 5d                	pop    %r13
  40118f:	c3                   	retq   

0000000000401190 <serial_append>:
  401190:	41 55                	push   %r13
  401192:	41 54                	push   %r12
  401194:	49 89 fc             	mov    %rdi,%r12
  401197:	55                   	push   %rbp
  401198:	53                   	push   %rbx
  401199:	48 83 ec 08          	sub    $0x8,%rsp
  40119d:	4c 8b 6f 28          	mov    0x28(%rdi),%r13
  4011a1:	49 8b 1c 24          	mov    (%r12),%rbx
  4011a5:	49 8b 7d 00          	mov    0x0(%r13),%rdi
  4011a9:	29 fb                	sub    %edi,%ebx
  4011ab:	48 8d 2c 33          	lea    (%rbx,%rsi,1),%rbp
  4011af:	48 89 ee             	mov    %rbp,%rsi
  4011b2:	e8 09 fa ff ff       	callq  400bc0 <realloc@plt>
  4011b7:	49 89 45 00          	mov    %rax,0x0(%r13)
  4011bb:	49 8b 44 24 28       	mov    0x28(%r12),%rax
  4011c0:	48 03 18             	add    (%rax),%rbx
  4011c3:	49 89 1c 24          	mov    %rbx,(%r12)
  4011c7:	48 89 68 08          	mov    %rbp,0x8(%rax)
  4011cb:	48 83 c4 08          	add    $0x8,%rsp
  4011cf:	5b                   	pop    %rbx
  4011d0:	5d                   	pop    %rbp
  4011d1:	41 5c                	pop    %r12
  4011d3:	41 5d                	pop    %r13
  4011d5:	c3                   	retq   
  4011d6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4011dd:	00 00 00 

00000000004011e0 <serial_add_ptr>:
  4011e0:	55                   	push   %rbp
  4011e1:	53                   	push   %rbx
  4011e2:	48 89 fb             	mov    %rdi,%rbx
  4011e5:	48 89 f5             	mov    %rsi,%rbp
  4011e8:	48 83 ec 08          	sub    $0x8,%rsp
  4011ec:	0f b6 47 20          	movzbl 0x20(%rdi),%eax
  4011f0:	48 8b 7f 10          	mov    0x10(%rdi),%rdi
  4011f4:	48 8d 34 c5 08 00 00 	lea    0x8(,%rax,8),%rsi
  4011fb:	00 
  4011fc:	e8 bf f9 ff ff       	callq  400bc0 <realloc@plt>
  401201:	0f b6 53 20          	movzbl 0x20(%rbx),%edx
  401205:	48 89 43 10          	mov    %rax,0x10(%rbx)
  401209:	48 89 c7             	mov    %rax,%rdi
  40120c:	48 8d 34 95 04 00 00 	lea    0x4(,%rdx,4),%rsi
  401213:	00 
  401214:	e8 a7 f9 ff ff       	callq  400bc0 <realloc@plt>
  401219:	0f b6 53 20          	movzbl 0x20(%rbx),%edx
  40121d:	48 89 43 18          	mov    %rax,0x18(%rbx)
  401221:	48 8b 43 10          	mov    0x10(%rbx),%rax
  401225:	48 89 2c d0          	mov    %rbp,(%rax,%rdx,8)
  401229:	48 8b 73 28          	mov    0x28(%rbx),%rsi
  40122d:	0f b6 4b 20          	movzbl 0x20(%rbx),%ecx
  401231:	48 8b 03             	mov    (%rbx),%rax
  401234:	48 8b 53 18          	mov    0x18(%rbx),%rdx
  401238:	48 2b 06             	sub    (%rsi),%rax
  40123b:	89 04 8a             	mov    %eax,(%rdx,%rcx,4)
  40123e:	80 43 20 01          	addb   $0x1,0x20(%rbx)
  401242:	48 83 c4 08          	add    $0x8,%rsp
  401246:	5b                   	pop    %rbx
  401247:	5d                   	pop    %rbp
  401248:	c3                   	retq   
  401249:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000401250 <serial_write_ptr>:
  401250:	0f b6 57 20          	movzbl 0x20(%rdi),%edx
  401254:	48 8b 07             	mov    (%rdi),%rax
  401257:	88 10                	mov    %dl,(%rax)
  401259:	48 83 07 01          	addq   $0x1,(%rdi)
  40125d:	c3                   	retq   
  40125e:	66 90                	xchg   %ax,%ax

0000000000401260 <serial_write_int8>:
  401260:	48 8b 07             	mov    (%rdi),%rax
  401263:	40 88 30             	mov    %sil,(%rax)
  401266:	48 83 07 01          	addq   $0x1,(%rdi)
  40126a:	c3                   	retq   
  40126b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000401270 <serial_write_int32>:
  401270:	48 8b 07             	mov    (%rdi),%rax
  401273:	89 30                	mov    %esi,(%rax)
  401275:	48 83 c0 04          	add    $0x4,%rax
  401279:	48 89 07             	mov    %rax,(%rdi)
  40127c:	c3                   	retq   
  40127d:	0f 1f 00             	nopl   (%rax)

0000000000401280 <serial_write_int64>:
  401280:	48 8b 07             	mov    (%rdi),%rax
  401283:	48 89 30             	mov    %rsi,(%rax)
  401286:	48 83 c0 08          	add    $0x8,%rax
  40128a:	48 89 07             	mov    %rax,(%rdi)
  40128d:	c3                   	retq   
  40128e:	66 90                	xchg   %ax,%ax

0000000000401290 <serial_end_write>:
  401290:	41 56                	push   %r14
  401292:	41 55                	push   %r13
  401294:	41 54                	push   %r12
  401296:	55                   	push   %rbp
  401297:	48 89 fd             	mov    %rdi,%rbp
  40129a:	53                   	push   %rbx
  40129b:	0f b6 4f 20          	movzbl 0x20(%rdi),%ecx
  40129f:	4c 8b 6f 28          	mov    0x28(%rdi),%r13
  4012a3:	4c 8d 24 8d 00 00 00 	lea    0x0(,%rcx,4),%r12
  4012aa:	00 
  4012ab:	48 8b 4d 00          	mov    0x0(%rbp),%rcx
  4012af:	49 8b 7d 00          	mov    0x0(%r13),%rdi
  4012b3:	89 cb                	mov    %ecx,%ebx
  4012b5:	29 fb                	sub    %edi,%ebx
  4012b7:	4e 8d 34 23          	lea    (%rbx,%r12,1),%r14
  4012bb:	4c 89 f6             	mov    %r14,%rsi
  4012be:	e8 fd f8 ff ff       	callq  400bc0 <realloc@plt>
  4012c3:	49 89 45 00          	mov    %rax,0x0(%r13)
  4012c7:	48 8b 45 28          	mov    0x28(%rbp),%rax
  4012cb:	48 8b 75 10          	mov    0x10(%rbp),%rsi
  4012cf:	48 03 18             	add    (%rax),%rbx
  4012d2:	41 83 fc 08          	cmp    $0x8,%r12d
  4012d6:	48 89 5d 00          	mov    %rbx,0x0(%rbp)
  4012da:	48 89 d9             	mov    %rbx,%rcx
  4012dd:	4c 89 70 08          	mov    %r14,0x8(%rax)
  4012e1:	73 15                	jae    4012f8 <serial_end_write+0x68>
  4012e3:	41 f6 c4 04          	test   $0x4,%r12b
  4012e7:	75 67                	jne    401350 <serial_end_write+0xc0>
  4012e9:	45 85 e4             	test   %r12d,%r12d
  4012ec:	74 34                	je     401322 <serial_end_write+0x92>
  4012ee:	0f b6 06             	movzbl (%rsi),%eax
  4012f1:	88 03                	mov    %al,(%rbx)
  4012f3:	eb 2d                	jmp    401322 <serial_end_write+0x92>
  4012f5:	0f 1f 00             	nopl   (%rax)
  4012f8:	48 8b 06             	mov    (%rsi),%rax
  4012fb:	48 8d 7b 08          	lea    0x8(%rbx),%rdi
  4012ff:	48 83 e7 f8          	and    $0xfffffffffffffff8,%rdi
  401303:	48 89 03             	mov    %rax,(%rbx)
  401306:	44 89 e0             	mov    %r12d,%eax
  401309:	48 29 f9             	sub    %rdi,%rcx
  40130c:	48 8b 54 06 f8       	mov    -0x8(%rsi,%rax,1),%rdx
  401311:	48 29 ce             	sub    %rcx,%rsi
  401314:	44 01 e1             	add    %r12d,%ecx
  401317:	c1 e9 03             	shr    $0x3,%ecx
  40131a:	48 89 54 03 f8       	mov    %rdx,-0x8(%rbx,%rax,1)
  40131f:	f3 48 a5             	rep movsq %ds:(%rsi),%es:(%rdi)
  401322:	49 8b 45 00          	mov    0x0(%r13),%rax
  401326:	48 8b 55 00          	mov    0x0(%rbp),%rdx
  40132a:	48 89 ef             	mov    %rbp,%rdi
  40132d:	48 29 c2             	sub    %rax,%rdx
  401330:	89 10                	mov    %edx,(%rax)
  401332:	0f b6 55 20          	movzbl 0x20(%rbp),%edx
  401336:	88 50 04             	mov    %dl,0x4(%rax)
  401339:	e8 32 f8 ff ff       	callq  400b70 <free@plt>
  40133e:	5b                   	pop    %rbx
  40133f:	4c 89 e8             	mov    %r13,%rax
  401342:	5d                   	pop    %rbp
  401343:	41 5c                	pop    %r12
  401345:	41 5d                	pop    %r13
  401347:	41 5e                	pop    %r14
  401349:	c3                   	retq   
  40134a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  401350:	8b 06                	mov    (%rsi),%eax
  401352:	45 89 e4             	mov    %r12d,%r12d
  401355:	89 03                	mov    %eax,(%rbx)
  401357:	42 8b 44 26 fc       	mov    -0x4(%rsi,%r12,1),%eax
  40135c:	42 89 44 23 fc       	mov    %eax,-0x4(%rbx,%r12,1)
  401361:	eb bf                	jmp    401322 <serial_end_write+0x92>
  401363:	66 66 66 66 2e 0f 1f 	data32 data32 data32 nopw %cs:0x0(%rax,%rax,1)
  40136a:	84 00 00 00 00 00 

0000000000401370 <serial_begin_read>:
  401370:	53                   	push   %rbx
  401371:	be 30 00 00 00       	mov    $0x30,%esi
  401376:	48 89 fb             	mov    %rdi,%rbx
  401379:	bf 01 00 00 00       	mov    $0x1,%edi
  40137e:	e8 1d f8 ff ff       	callq  400ba0 <calloc@plt>
  401383:	8b 13                	mov    (%rbx),%edx
  401385:	48 89 18             	mov    %rbx,(%rax)
  401388:	48 01 da             	add    %rbx,%rdx
  40138b:	48 83 c3 05          	add    $0x5,%rbx
  40138f:	48 89 50 28          	mov    %rdx,0x28(%rax)
  401393:	0f b6 53 ff          	movzbl -0x1(%rbx),%edx
  401397:	48 89 58 10          	mov    %rbx,0x10(%rax)
  40139b:	88 50 20             	mov    %dl,0x20(%rax)
  40139e:	5b                   	pop    %rbx
  40139f:	c3                   	retq   

00000000004013a0 <serial_read_push>:
  4013a0:	48 8b 47 10          	mov    0x10(%rdi),%rax
  4013a4:	48 89 47 08          	mov    %rax,0x8(%rdi)
  4013a8:	c3                   	retq   
  4013a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004013b0 <serial_read_pop>:
  4013b0:	48 8b 47 08          	mov    0x8(%rdi),%rax
  4013b4:	48 89 47 10          	mov    %rax,0x10(%rdi)
  4013b8:	c3                   	retq   
  4013b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000004013c0 <serial_read_ptr>:
  4013c0:	48 8b 57 10          	mov    0x10(%rdi),%rdx
  4013c4:	48 8b 47 28          	mov    0x28(%rdi),%rax
  4013c8:	0f b6 0a             	movzbl (%rdx),%ecx
  4013cb:	48 83 c2 01          	add    $0x1,%rdx
  4013cf:	8b 04 88             	mov    (%rax,%rcx,4),%eax
  4013d2:	48 89 57 10          	mov    %rdx,0x10(%rdi)
  4013d6:	48 03 07             	add    (%rdi),%rax
  4013d9:	c3                   	retq   
  4013da:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004013e0 <serial_read_int8>:
  4013e0:	48 8b 57 10          	mov    0x10(%rdi),%rdx
  4013e4:	0f b6 02             	movzbl (%rdx),%eax
  4013e7:	48 83 c2 01          	add    $0x1,%rdx
  4013eb:	48 89 57 10          	mov    %rdx,0x10(%rdi)
  4013ef:	c3                   	retq   

00000000004013f0 <serial_read_int16>:
  4013f0:	48 8b 57 10          	mov    0x10(%rdi),%rdx
  4013f4:	0f b7 02             	movzwl (%rdx),%eax
  4013f7:	48 83 c2 02          	add    $0x2,%rdx
  4013fb:	48 89 57 10          	mov    %rdx,0x10(%rdi)
  4013ff:	c3                   	retq   

0000000000401400 <serial_read_int32>:
  401400:	48 8b 57 10          	mov    0x10(%rdi),%rdx
  401404:	8b 02                	mov    (%rdx),%eax
  401406:	48 83 c2 04          	add    $0x4,%rdx
  40140a:	48 89 57 10          	mov    %rdx,0x10(%rdi)
  40140e:	c3                   	retq   
  40140f:	90                   	nop

0000000000401410 <serial_read_int64>:
  401410:	48 8b 57 10          	mov    0x10(%rdi),%rdx
  401414:	48 8b 02             	mov    (%rdx),%rax
  401417:	48 83 c2 08          	add    $0x8,%rdx
  40141b:	48 89 57 10          	mov    %rdx,0x10(%rdi)
  40141f:	c3                   	retq   

0000000000401420 <serial_end_read>:
  401420:	48 8b 07             	mov    (%rdi),%rax
  401423:	c3                   	retq   
  401424:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  40142b:	00 00 00 
  40142e:	66 90                	xchg   %ax,%ax

0000000000401430 <__libc_csu_init>:
  401430:	41 57                	push   %r15
  401432:	41 56                	push   %r14
  401434:	41 89 ff             	mov    %edi,%r15d
  401437:	41 55                	push   %r13
  401439:	41 54                	push   %r12
  40143b:	4c 8d 25 5e 05 20 00 	lea    0x20055e(%rip),%r12        # 6019a0 <__frame_dummy_init_array_entry>
  401442:	55                   	push   %rbp
  401443:	48 8d 2d 5e 05 20 00 	lea    0x20055e(%rip),%rbp        # 6019a8 <__init_array_end>
  40144a:	53                   	push   %rbx
  40144b:	49 89 f6             	mov    %rsi,%r14
  40144e:	49 89 d5             	mov    %rdx,%r13
  401451:	31 db                	xor    %ebx,%ebx
  401453:	4c 29 e5             	sub    %r12,%rbp
  401456:	48 83 ec 08          	sub    $0x8,%rsp
  40145a:	48 c1 fd 03          	sar    $0x3,%rbp
  40145e:	e8 dd f6 ff ff       	callq  400b40 <_init>
  401463:	48 85 ed             	test   %rbp,%rbp
  401466:	74 1e                	je     401486 <__libc_csu_init+0x56>
  401468:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  40146f:	00 
  401470:	4c 89 ea             	mov    %r13,%rdx
  401473:	4c 89 f6             	mov    %r14,%rsi
  401476:	44 89 ff             	mov    %r15d,%edi
  401479:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  40147d:	48 83 c3 01          	add    $0x1,%rbx
  401481:	48 39 eb             	cmp    %rbp,%rbx
  401484:	75 ea                	jne    401470 <__libc_csu_init+0x40>
  401486:	48 83 c4 08          	add    $0x8,%rsp
  40148a:	5b                   	pop    %rbx
  40148b:	5d                   	pop    %rbp
  40148c:	41 5c                	pop    %r12
  40148e:	41 5d                	pop    %r13
  401490:	41 5e                	pop    %r14
  401492:	41 5f                	pop    %r15
  401494:	c3                   	retq   
  401495:	66 66 2e 0f 1f 84 00 	data32 nopw %cs:0x0(%rax,%rax,1)
  40149c:	00 00 00 00 

00000000004014a0 <__libc_csu_fini>:
  4014a0:	f3 c3                	repz retq 

Дизасемблювання розділу .fini:

00000000004014a4 <_fini>:
  4014a4:	48 83 ec 08          	sub    $0x8,%rsp
  4014a8:	48 83 c4 08          	add    $0x8,%rsp
  4014ac:	c3                   	retq   
