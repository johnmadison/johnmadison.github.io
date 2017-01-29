.intel_syntax noprefix
// program to do octal input and output

section .data
prompt1: db "Please enter a decimal number: $"
prompt2: db 0Dh,0Ah, "The number in octal is:    $"
prompt3: db 0Dh,0Ah, "The number in decimal is:    $"

section .text
mov ah,9           // print prompt
mov dx,prompt1
int     21h
call    dec_in      // read value into bx
mov ah,9            // print output label
mov dx,prompt2
int     21h 
call    hexout
mov ah,9            // print output label
mov dx,prompt3
int     21h
call    dec_out     // display the value in bx as hex
exit:

mov ax,4C00h        // Normal Exit
int 21h             // bye!

// dec_in will read a base 10 value from the keyboard and place it into the bx    register
dec_in: 
// save registers
push    ax
push    dx

xor bx,bx       // bx holds accumulated input
mov ah,1        // read char fcn
int 21h         // read it into al
while1: 
cmp al,0Dh      // char = CR?
je  finis       // if so, we are done
push    ax      // save the character read
mov ax,10       // set up for multiply
mul bx          // dx:ax <- bx * 10
mov bx,ax       // put 16-bit result back in bx (assume no overflow)
pop ax          // restore the char read
and ax,000Fh    // convert character '0'-'9' to value 0-9
add bx,ax       // add value to accumulated input
mov ah,1        // read char fcn
int 21h         // read next char into al
jmp while1      // loop until done
finis:  
// restore registers
pop dx
pop ax
ret


// hexout will display the binary value in the bx register as a base 16 value
hexout:
// save registers we will be using
push    ax
push    cx
push    dx
mov ah,2        // display char fcn
mov cx,4        // loop counter init
for1:               // top of for loop
rol bx,4        // rotate so digit is in lowest 4 bits
mov dl,bl       // get low half in dl
and dl,0Fh      //  and mask out all but 4 bits
cmp dl,9        // dl <= 9?
jnbe    AtoF    // if not, then it's A-F
or  dl,30h      // convert 0-9 to '0'-'9'
jmp endif1      // get ready to display
AtoF:   add dl,55   // convert 10-15 to 'A'-'F'
endif1: int 21h     // display char
loop    for1    // loop until done
// restore registers
pop dx
pop cx
pop ax
ret

// dec_out will display the binary value in the bx register as a base 10 value
dec_out:
// save registers we will be using
push    ax
push    bx
push    cx
push    dx

xor cx,cx       //cx counts digits, initially zero
rept:
mov ax,bx       // set up to divide by by 10
xor dx,dx       // must have a 32 bit (unsigned) dividend
mov bx,10       // divisor will be in bx
div bx          // quotient will be in ax, remainder in dx
push    dx      // push remainder on stack
inc cx          // we generated another digit, so count it
mov bx,ax       // the quotient goes back in bx
cmp ax,0        // clever way to test if quotient is zero
jne rept        // if not, generate next digit

mov ah,2        // display character function
for2:               // loop cx times
pop dx          // pop digit to print
or  dl,30h      // convert the digit to print to ASCII code
int 21h         // display the character
loop    for2    // and keep going until all digits displayed

// restore registers
pop dx
pop cx
pop bx
pop ax
ret