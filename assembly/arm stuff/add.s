	.arch armv6
	.section	.text.startup,"ax"
	.align	2
	.global	main
	.type	main, %function
main:
	stmfd	sp!, {r3, lr}
	mov	r1, #10
	mov	r2, #6
	mov	r3, #66
	mov	r4, #65
	mov	r5, #67
	mov	r6, #68
	add 	r1, r1, r2
	ldr	r0, .L3
	bl	printf
	mov	r0, #0
	ldmfd	sp!, {r3, pc}
.L3:
	.word	.LC0 
	.size	main, .-main
	.text
	.section	.str1.1,"aMS"
.LC0:
	.ascii	"%i %i %i %i %i %i %i\012\000"
	
