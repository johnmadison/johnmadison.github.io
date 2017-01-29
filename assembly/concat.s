        .intel_syntax noprefix
        .section        .data.str1.1,"aMS",@progbits,1
string1:
         .ascii "Hello World \0"
string2:
         .ascii " This is the second string \0"
        .section        .text.startup,"ax",@progbits
        .globl  main
        .type   main, @function
main:
.LFB14:
        
        push    rax
        
        mov     edi, OFFSET FLAT:string1
        
        //this is my added code

        

        mov ebx, OFFSET FLAT:string2    

        //end added code

        call    puts
        mov edi, OFFSET FLAT:string2
        call puts
        pop     rdx
        
        ret

