.intel_syntax
 
data:
		dDecimalNumber DWORD ?
		binary         BYTE 30 DUP(?)
		dCounter       DWORD 0
		msgNumber          BYTE " Enter A Number : ",0 
		msgBinary          BYTE " Binary Number =  ",0
		msgDecimalToBinary BYTE " Decimal to Binary Converter in Assembly Language ",0
 
code:
	main PROC
		mov edx, OFFSET msgDecimalToBinary  
		call WriteString                    
		call Crlf                           
 
		mov edx, OFFSET msgNumber    
		call WriteString             
 
		call ReadDec                 
                                     
		mov dDecimalNumber, eax
 
		mov dCounter,0
		mov ebx,2                    
	L1:
		cmp dDecimalNumber,0               
		je Display                         
		mov ax, WORD PTR dDecimalNumber
		mov dx, WORD PTR dDecimalNumber + 2
		div bx
		movzx edx, dx
		push edx
		movzx eax, ax
		mov dDecimalNumber, eax
		inc dCounter
		jmp L1                     
 
	Display:
		mov edx, OFFSET msgBinary
		call WriteString
		mov ecx, dCounter	       
	L2:
		pop eax
		call WriteDec              
		dec dCounter
		Loop L2                   
 
	call Crlf       
	call WaitMsg    
	exit            
                    
	main ENDP  
END main      