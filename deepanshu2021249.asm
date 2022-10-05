segment .data
	x dq 0 ;integer input
	s times 100 db 0 ;string array of max size 99
	ft db "%s %d",0	;input format specifier
	ftp db"String: %s ,Integer: %d",0x0a,0
segment .text
	global main ;calling our main function
	extern printf	
	extern scanf
main:
	push rbp
	lea rdi,[ft]  ;specifying format
	lea rsi,[s]	  ;string address into register 1 for storing in s
	lea rdx,[x]	  ;integer adrees(i.e address of x)
	xor eax,eax	  ;setting eax register to be 0 a xor a=0
	call scanf	;calling scanf for reading input
	lea rdi,[ftp]	;specifying print format and storing value into registers
	lea rsi,[s]
	mov rdx,[x]		
	xor eax, eax	
	call printf	
exit:
	xor eax,eax ;exit loop
	pop rbp
	ret
;reference Ray-Seyfarth
