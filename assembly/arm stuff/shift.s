	.arch armv6
	.global	main
	.type	main, %function
main:
	PUSH	{r3, lr}							
	MOV r1, #0									
	MOV r2, #10		
	MOV r3, #4		
party: 
	LSRS r2, r2, #1		
	BCC  dont_add  		
	ADDCS r1, r1, r3 	
dont_add:
	LSL r3, r3, #1		
	CMP	r2, #0		
	BEQ print		
	B party			
print: 	
	LDR	r0, .stuff
	BL	printf			
	POP	 {r3, pc}		
.stuff:					
	.word	.junk
	.section	.str1.1,"aMS", %progbits, 1
.junk:
	.ascii	"%i \012\000"		

