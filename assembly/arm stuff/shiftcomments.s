	.arch armv6
	.global	main
	.type	main, %function
main:
	PUSH	{r3, lr}
							
	MOV r1, #0			@result = 0 (well print from r1)
							
	MOV r2, #10			@num1 	multipland
								
	MOV r3, #4			@num2	multiplier

party: 

	LSRS r2, r2, #1		@num1 = num1 / 2 ("logical shift right set carry")
	
	BCC  dont_add  		@ if (carry from lsrs == 0) goto dont_add
	
	ADDCS r1, r1, r3 	@ num1 = num1 + num2 if the carry is set

dont_add:

	LSL r3, r3, #1		@num2 = num2 * 2 ("logical shift left no carry")

	CMP	r2, #0			@compare num1 to zero

	BEQ print			@if num1 is zero, goto print

	B party				@otherwise go back to party more
	
print: 	
	@the result is in register 1			

	LDR	r0, .stuff
	
	BL	printf					@print some stuff. 
		
	POP	 {r3, pc}				@clean house
	
.stuff:							@this is some formatting stuff...
	.word	.junk
	.section	.str1.1,"aMS", %progbits, 1
.junk:
	.ascii	"%i \012\000"		@the %i is for printing integers