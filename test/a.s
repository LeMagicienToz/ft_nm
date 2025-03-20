bits 64 ;commentaire 

section .data

section .bss

section .text
	global ft_strcmp

ft_strcmp:
strcmp_loop:
	mov al, byte [rdi]    ; Charger le caractère de la chaîne pointée par rdi dans al
    mov bl, byte [rsi]    ; Charger le caractère de la chaîne pointée par rsi dans bl
    cmp al, bl            ; Comparer les deux caractères
    jne strcmp_diff       ; Si les caractères sont différents, sauter à strcmp_diff
	test al, al
	jz strcmp_end			; si == 0 (donc fin de la chaine de caracatere )
	inc rdi					;increment char next
	inc rsi					;increment char next
	jmp strcmp_loop			;recursive
strcmp_diff:
    movzx rax, al         ; Étendre la valeur d'al (8 bits) dans rax (64 bits) pour le retour
	sub rax, rbx            ; Calculer la différence entre les caractères
    ret                   ; Retourner la différence des caractères

strcmp_end :
	mov rax, 0 ; set 0 ret value
	ret
