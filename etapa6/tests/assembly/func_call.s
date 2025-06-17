    .text
    .data
.printInt:
    .string    "%d"
.str_0:
    .string    "Valor final: var =  "
.str_1:
    .string    "Valor inicial: var = "
.str_2:
    .string    "\n"
.str_3:
    .string    "var = "
_0:
    .long    0
_1:
    .long    1
_2:
    .long    2
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
_v:
    .long    0
_var:
    .long    0
_w:
    .long    0
_x:
    .long    0
_y:
    .long    0
    .text

# --- Tac(BEGIN_FUNC, main, -, -) ---
    .globl    main
main:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(PRINT, "Valor inicial: var = ", -, -) ---
    leaq    .str_1(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, var, -, -) ---
    movl    _var(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(ARG, 1, func2, w) ---
    movl    _1(%rip), %eax
    movl    %eax, _w(%rip)

# --- Tac(FUNC_CALL, _temp0_, func2, -) ---
    call    func2
    movl    %eax, __temp0_(%rip)

# --- Tac(ARG, 2, func3, v) ---
    movl    _2(%rip), %eax
    movl    %eax, _v(%rip)

# --- Tac(FUNC_CALL, _temp1_, func3, -) ---
    call    func3
    movl    %eax, __temp1_(%rip)

# --- Tac(ARG, _temp0_, func1, x) ---
    movl    __temp0_(%rip), %eax
    movl    %eax, _x(%rip)

# --- Tac(ARG, _temp1_, func1, y) ---
    movl    __temp1_(%rip), %eax
    movl    %eax, _y(%rip)

# --- Tac(FUNC_CALL, _temp2_, func1, -) ---
    call    func1
    movl    %eax, __temp2_(%rip)

# --- Tac(MOVE, var, _temp2_, -) ---
    movl    __temp2_(%rip), %eax
    movl    %eax, _var(%rip)

# --- Tac(PRINT, "var = ", -, -) ---
    leaq    .str_3(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, var, -, -) ---
    movl    _var(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(ARG, 2, func2, w) ---
    movl    _2(%rip), %eax
    movl    %eax, _w(%rip)

# --- Tac(FUNC_CALL, _temp3_, func2, -) ---
    call    func2
    movl    %eax, __temp3_(%rip)

# --- Tac(MOVE, var, _temp3_, -) ---
    movl    __temp3_(%rip), %eax
    movl    %eax, _var(%rip)

# --- Tac(PRINT, "var = ", -, -) ---
    leaq    .str_3(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, var, -, -) ---
    movl    _var(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(FUNC_CALL, _temp4_, func0, -) ---
    call    func0
    movl    %eax, __temp4_(%rip)

# --- Tac(MOVE, var, _temp4_, -) ---
    movl    __temp4_(%rip), %eax
    movl    %eax, _var(%rip)

# --- Tac(PRINT, "Valor final: var =  ", -, -) ---
    leaq    .str_0(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, var, -, -) ---
    movl    _var(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(END_FUNC, main, -, -) ---
    popq    %rbp
    ret

# --- Tac(BEGIN_FUNC, func0, -, -) ---
    .globl    func0
func0:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(RETURN, 0, -, -) ---
    movl    _0(%rip), %eax
    popq    %rbp
    ret

# --- Tac(END_FUNC, func0, -, -) ---
    popq    %rbp
    ret

# --- Tac(BEGIN_FUNC, func1, -, -) ---
    .globl    func1
func1:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(ADD, _temp5_, x, y) ---
    movl    _x(%rip), %eax
    addl    _y(%rip), %eax
    movl    %eax, __temp5_(%rip)

# --- Tac(RETURN, _temp5_, -, -) ---
    movl    __temp5_(%rip), %eax
    popq    %rbp
    ret

# --- Tac(END_FUNC, func1, -, -) ---
    popq    %rbp
    ret

# --- Tac(BEGIN_FUNC, func2, -, -) ---
    .globl    func2
func2:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(RETURN, w, -, -) ---
    movl    _w(%rip), %eax
    popq    %rbp
    ret

# --- Tac(END_FUNC, func2, -, -) ---
    popq    %rbp
    ret

# --- Tac(BEGIN_FUNC, func3, -, -) ---
    .globl    func3
func3:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(RETURN, v, -, -) ---
    movl    _v(%rip), %eax
    popq    %rbp
    ret

# --- Tac(END_FUNC, func3, -, -) ---
    popq    %rbp
    ret
