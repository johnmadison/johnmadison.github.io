        .arch armv6
        .fpu vfp
        .section        .text.startup
        .global main
        .type   main, %function
main:
     	stmfd   sp!, {r0, r1, r2, r3, r4, lr}
        add     r1, sp, #8
        ldr     r3, stuff
        ldr     r0, [r3]
        ldrh    r3, [r3, #4]
        str     r0, [sp]
        strh    r3, [sp, #4]
        ldr     r3, stuff+4
        ldrh    r2, [r3, #4]
        ldr     r0, [r3]
        ldrb    r3, [r3, #6]
        str     r0, [sp, #8]
        mov     r0, sp
        strh    r2, [sp, #12]
        strb    r3, [sp, #14]
        bl	strcat
        mov     r0, sp
        bl	printf
        mov     r0, #0
        add     sp, sp, #20
        ldr     pc, [sp], #4
.L3:
    	.align  2
stuff:
    	.word   .LC0
        .word   .LC1
        .size   main, .-main
        .section        .rodata.str1.1
.LC0:
     	.ascii  "Hello\000"
.LC1:
     	.ascii  " Dave\012\000"



