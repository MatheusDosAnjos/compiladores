    .text
    .data
.printInt:
    .string    "%d"
.str_0:
    .string    "DO number > 3 -> "
.str_1:
    .string    "ELSE1 -> number != 5\n"
.str_2:
    .string    "ELSE2 -> number == 5\n"
.str_3:
    .string    "IF1   -> number == 5\n"
.str_4:
    .string    "IF2   -> number != 5\n"
.str_5:
    .string    "WHILE number < 6 -> "
.str_6:
    .string    "\n"
.str_7:
    .string    "number = "
_1:
    .long    1
_3:
    .long    3
_5:
    .long    5
_6:
    .long    6
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
_number:
    .long    5
    .text

# --- Tac(BEGIN_FUNC, main, -, -) ---
    .globl    main
main:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(PRINT, "number = ", -, -) ---
    leaq    .str_7(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_6(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(EQ, _temp0_, number, 5) ---
    movl    _number(%rip), %eax
    cmpl    _5(%rip), %eax
    sete    %al
    movzbl  %al, %eax
    movl    %eax, __temp0_(%rip)

# --- Tac(IFZ, _label0_, _temp0_, -) ---
    movl    __temp0_(%rip), %eax
    testl   %eax, %eax
    jz      _label0_

# --- Tac(PRINT, "IF1   -> number == 5\n", -, -) ---
    leaq    .str_3(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label1_, -, -) ---
    jmp    _label1_

# --- Tac(LABEL, _label0_, -, -) ---
_label0_:

# --- Tac(PRINT, "ELSE1 -> number != 5\n", -, -) ---
    leaq    .str_1(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(LABEL, _label1_, -, -) ---
_label1_:

# --- Tac(DIF, _temp1_, number, 5) ---
    movl    _number(%rip), %eax
    cmpl    _5(%rip), %eax
    setne   %al
    movzbl  %al, %eax
    movl    %eax, __temp1_(%rip)

# --- Tac(IFZ, _label2_, _temp1_, -) ---
    movl    __temp1_(%rip), %eax
    testl   %eax, %eax
    jz      _label2_

# --- Tac(PRINT, "IF2   -> number != 5\n", -, -) ---
    leaq    .str_4(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label3_, -, -) ---
    jmp    _label3_

# --- Tac(LABEL, _label2_, -, -) ---
_label2_:

# --- Tac(PRINT, "ELSE2 -> number == 5\n", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(LABEL, _label3_, -, -) ---
_label3_:

# --- Tac(LABEL, _label4_, -, -) ---
_label4_:

# --- Tac(PRINT, "DO number > 3 -> ", -, -) ---
    leaq    .str_0(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "number = ", -, -) ---
    leaq    .str_7(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_6(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(SUB, _temp2_, number, 1) ---
    movl    _number(%rip), %eax
    subl    _1(%rip), %eax
    movl    %eax, __temp2_(%rip)

# --- Tac(MOVE, number, _temp2_, -) ---
    movl    __temp2_(%rip), %eax
    movl    %eax, _number(%rip)

# --- Tac(GREATER, _temp3_, number, 3) ---
    movl    _number(%rip), %eax
    cmpl    _3(%rip), %eax
    setg    %al
    movzbl  %al, %eax
    movl    %eax, __temp3_(%rip)

# --- Tac(IFZ, _label5_, _temp3_, -) ---
    movl    __temp3_(%rip), %eax
    testl   %eax, %eax
    jz      _label5_

# --- Tac(JUMP, _label4_, -, -) ---
    jmp    _label4_

# --- Tac(LABEL, _label5_, -, -) ---
_label5_:

# --- Tac(LABEL, _label6_, -, -) ---
_label6_:

# --- Tac(LESS, _temp4_, number, 6) ---
    movl    _number(%rip), %eax
    cmpl    _6(%rip), %eax
    setl    %al
    movzbl  %al, %eax
    movl    %eax, __temp4_(%rip)

# --- Tac(IFZ, _label7_, _temp4_, -) ---
    movl    __temp4_(%rip), %eax
    testl   %eax, %eax
    jz      _label7_

# --- Tac(PRINT, "WHILE number < 6 -> ", -, -) ---
    leaq    .str_5(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "number = ", -, -) ---
    leaq    .str_7(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_6(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(ADD, _temp5_, number, 1) ---
    movl    _number(%rip), %eax
    addl    _1(%rip), %eax
    movl    %eax, __temp5_(%rip)

# --- Tac(MOVE, number, _temp5_, -) ---
    movl    __temp5_(%rip), %eax
    movl    %eax, _number(%rip)

# --- Tac(JUMP, _label6_, -, -) ---
    jmp    _label6_

# --- Tac(LABEL, _label7_, -, -) ---
_label7_:

# --- Tac(END_FUNC, main, -, -) ---
    popq    %rbp
    ret
