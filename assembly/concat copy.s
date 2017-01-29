CONCAT          proc    near
                push    si
                push    di
                push    cx
                push    ax
                pushf

; Copy the first string to the destination string:

                mov     al, [si]
                mov     cl, al
                mov     ch, 0
                mov     ah, ch
                add     al, [bx]        
                
                //Compute the sum of the string's lengths. 
                
                adc     ah, 0           
                cmp     ax, 256
                jb      SetNewLength
                mov     ah, [si]        
                
                //Save original string length.
                
                mov     al, 255         
                
                //Fix string length at 255.
                
SetNewLength:   mov     es:[di], al     

				//Save new string length.
                
                inc     di             
                
                //Skip over length bytes.
                
                inc     si
        rep     movsb                   
        		
        		//Copy source1 to dest string.

//If the sum of the two strings is too long, the second string
// must be truncated.

                mov     cl, [bx]        
                
                //Get length of second string.
                
                cmp     ax, 256
                jb      LengthsAreOK
                mov     cl, ah          
                
                //Compute truncated length.
                neg     cl              
                
                //CL := 256-Length(Str1).

LengthsAreOK:   lea     si, 1[bx]       

//Point at second string and
;                                       
// skip the string length.
                cld
                rep     movsb           
                
                //Perform the concatenation.

                popf
                pop     ax
                pop     cx
                pop     di
                pop     si
                ret
CONCAT          endp
