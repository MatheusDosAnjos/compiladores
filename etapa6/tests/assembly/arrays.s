    .text
    .data
.printInt:
    .string    "%d"
.str_0:
    .string    "\n number[0] = "
.str_1:
    .string    "\n number[1] = "
.str_2:
    .string    "\n number[2] = "
.str_3:
    .string    "\n"
_0:
    .long    0
_1:
    .long    1
_2:
    .long    2
_3:
    .long    3
_5555:
    .long    5555
__temp0_:
    .long    0
__temp1_:
    .long    0
__temp2_:
    .long    0
__temp3_:
    .long    0
__temp4_:
    .long    0
__temp5_:
    .long    0
__temp6_:
    .long    0
_index:
    .long    1
_number:
    .long    1
    .long    2
    .long    3
_value:
    .long    5555
    .text

# --- Tac(BEGIN_FUNC, main, -, -) ---
    .globl    main
main:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(PRINT, "\n number[0] = ", -, -) ---
    leaq    .str_0(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(IDX_ACCESS, _temp0_, number, 0) ---
    movl    _0(%rip), %eax
    leaq    _number(%rip), %rcx
    movl    (%rcx, %rax, 4), %eax
    movl    %eax, __temp0_(%rip)

# --- Tac(PRINT, _temp0_, -, -) ---
    movl    __temp0_(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n number[1] = ", -, -) ---
    leaq    .str_1(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(IDX_ACCESS, _temp1_, number, 1) ---
    movl    _1(%rip), %eax
    leaq    _number(%rip), %rcx
    movl    (%rcx, %rax, 4), %eax
    movl    %eax, __temp1_(%rip)

# --- Tac(PRINT, _temp1_, -, -) ---
    movl    __temp1_(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n number[2] = ", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(IDX_ACCESS, _temp2_, number, 2) ---
    movl    _2(%rip), %eax
    leaq    _number(%rip), %rcx
    movl    (%rcx, %rax, 4), %eax
    movl    %eax, __temp2_(%rip)

# --- Tac(PRINT, _temp2_, -, -) ---
    movl    __temp2_(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_3(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(IDX_ACCESS, _temp3_, number, index) ---
    movl    _index(%rip), %eax
    leaq    _number(%rip), %rcx
    movl    (%rcx, %rax, 4), %eax
    movl    %eax, __temp3_(%rip)

# --- Tac(MOVE_IDX, number, index, value) ---
    movl    _index(%rip), %eax
    movl    _value(%rip), %edx
    leaq    _number(%rip), %rcx
    movl    %edx, (%rcx, %rax, 4)

# --- Tac(PRINT, "\n number[0] = ", -, -) ---
    leaq    .str_0(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(IDX_ACCESS, _temp4_, number, 0) ---
    movl    _0(%rip), %eax
    leaq    _number(%rip), %rcx
    movl    (%rcx, %rax, 4), %eax
    movl    %eax, __temp4_(%rip)

# --- Tac(PRINT, _temp4_, -, -) ---
    movl    __temp4_(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n number[1] = ", -, -) ---
    leaq    .str_1(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(IDX_ACCESS, _temp5_, number, 1) ---
    movl    _1(%rip), %eax
    leaq    _number(%rip), %rcx
    movl    (%rcx, %rax, 4), %eax
    movl    %eax, __temp5_(%rip)

# --- Tac(PRINT, _temp5_, -, -) ---
    movl    __temp5_(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n number[2] = ", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(IDX_ACCESS, _temp6_, number, 2) ---
    movl    _2(%rip), %eax
    leaq    _number(%rip), %rcx
    movl    (%rcx, %rax, 4), %eax
    movl    %eax, __temp6_(%rip)

# --- Tac(PRINT, _temp6_, -, -) ---
    movl    __temp6_(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_3(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(END_FUNC, main, -, -) ---
    popq    %rbp
    ret
