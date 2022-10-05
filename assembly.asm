global main 
extern printf	
extern scanf
segment .data
	scan_format db "%s %d",0	
	print_format db "Your String is: %s,Your Integer is: %d",0x0a,0 
	integer dq 0 ;defining integer byte
	string times 100 db 0 ;define string array
segment .text
main:
	push rbp
	lea rdi,[scan_format]  
	lea rsi,[string]	  
	lea rdx,[integer]	  
	xor eax,eax	  
	call scanf	
	lea rdi,[print_format]
	lea rsi,[string]
	mov rdx,[integer]		
	xor eax, eax	
	call printf	
	xor eax,eax
	pop rbp
	ret