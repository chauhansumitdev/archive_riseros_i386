BITS 16
org 0x7C00

start:
    ; Print memory size
    call get_memory_size
    call print_memory_size

    ; Infinite loop to halt execution
    jmp $

; Function to get memory size
get_memory_size:
    ; Use BIOS interrupt 0x12 to get memory size
    int 0x12
    ; AX now contains the size of conventional memory in kilobytes
    ret

; Function to print the memory size
print_memory_size:
    mov si, memory_msg
    call print_string

    ; Convert AX (memory size) to ASCII and print
    call print_number
    ret

; Function to print a string (uses BIOS int 0x10)
print_string:
    mov ah, 0x0E      ; Teletype output
.next_char:
    lodsb             ; Load next byte from [SI] into AL
    cmp al, 0         ; Check for null terminator
    je .done
    int 0x10          ; BIOS interrupt to print character
    jmp .next_char
.done:
    ret

; Function to print a number in AX as decimal
print_number:
    ; Convert the number in AX into ASCII and print it
    mov bx, 10        ; Base 10 divisor
    xor cx, cx        ; Clear CX (will hold digits)

convert_loop:
    xor dx, dx        ; Clear DX before division
    div bx            ; Divide AX by 10 (result in AX, remainder in DX)
    push dx           ; Push remainder (next digit) onto the stack
    inc cx            ; Increment the digit counter
    cmp ax, 0         ; If quotient is zero, we're done
    jne convert_loop

print_digits:
    pop dx            ; Get the next digit
    add dl, '0'       ; Convert it to ASCII ('0' to '9')
    mov ah, 0x0E      ; Teletype output
    mov al, dl        ; Move the digit into AL
    int 0x10          ; Print the digit
    loop print_digits ; Repeat for all digits
    ret

memory_msg db 'Memory Size: ', 0

times 510-($-$$) db 0
dw 0xAA55
