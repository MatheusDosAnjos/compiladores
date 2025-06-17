    .text
    .data
.printInt:
    .string    "%d"
.str_0:
    .string    "\n"
.str_1:
    .string    "enter a new value: "
.str_2:
    .string    "number now has a new value: "
.str_3:
    .string    "number value is: "
_1:
    .long    1
_number:
    .long    1
    .text

# --- Tac(BEGIN_FUNC, main, -, -) ---
    .globl    main
main:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(PRINT, "number value is: ", -, -) ---
    leaq    .str_3(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_0(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "enter a new value: ", -, -) ---
    leaq    .str_1(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(READ, number, -, -) ---
    leaq    _number(%rip), %rsi
    leaq    .printInt(%rip), %rdi
    call    scanf@PLT

# --- Tac(PRINT, "number now has a new value: ", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_0(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(END_FUNC, main, -, -) ---
    popq    %rbp
    ret
