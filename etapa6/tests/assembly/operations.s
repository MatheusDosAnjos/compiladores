    .text
    .data
.printInt:
    .string    "%d"
.str_0:
    .string    "!= TRUE\n"
.str_1:
    .string    "& TRUE\n"
.str_2:
    .string    "< FALSE\n"
.str_3:
    .string    "< TRUE\n"
.str_4:
    .string    "<= TRUE\n"
.str_5:
    .string    "== TRUE\n"
.str_6:
    .string    "> TRUE\n"
.str_7:
    .string    ">= TRUE\n"
.str_8:
    .string    "\n"
.str_9:
    .string    "| TRUE\n"
.str_10:
    .string    "~ TRUE\n"
_1:
    .long    1
_2:
    .long    2
_3:
    .long    3
_4:
    .long    4
_5:
    .long    5
_55:
    .long    55
_6:
    .long    6
__temp0_:
    .long    0
__temp10_:
    .long    0
__temp11_:
    .long    0
__temp12_:
    .long    0
__temp13_:
    .long    0
__temp14_:
    .long    0
__temp15_:
    .long    0
__temp16_:
    .long    0
__temp17_:
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
__temp7_:
    .long    0
__temp8_:
    .long    0
__temp9_:
    .long    0
_number:
    .long    5
    .text

# --- Tac(BEGIN_FUNC, main, -, -) ---
    .globl    main
main:
    pushq    %rbp
    movq    %rsp, %rbp

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_8(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(ADD, _temp0_, number, 1) ---
    movl    _number(%rip), %eax
    addl    _1(%rip), %eax
    movl    %eax, __temp0_(%rip)

# --- Tac(MOVE, number, _temp0_, -) ---
    movl    __temp0_(%rip), %eax
    movl    %eax, _number(%rip)

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_8(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(SUB, _temp1_, number, 4) ---
    movl    _number(%rip), %eax
    subl    _4(%rip), %eax
    movl    %eax, __temp1_(%rip)

# --- Tac(MOVE, number, _temp1_, -) ---
    movl    __temp1_(%rip), %eax
    movl    %eax, _number(%rip)

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_8(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(MULT, _temp2_, number, 6) ---
    movl    _number(%rip), %eax
    imull   _6(%rip), %eax
    movl    %eax, __temp2_(%rip)

# --- Tac(MOVE, number, _temp2_, -) ---
    movl    __temp2_(%rip), %eax
    movl    %eax, _number(%rip)

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_8(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(DIV, _temp3_, number, 4) ---
    movl    _number(%rip), %eax
    cltd
    idivl   _4(%rip)
    movl    %eax, __temp3_(%rip)

# --- Tac(MOVE, number, _temp3_, -) ---
    movl    __temp3_(%rip), %eax
    movl    %eax, _number(%rip)

# --- Tac(PRINT, number, -, -) ---
    movl    _number(%rip), %eax
    movl    %eax, %esi
    leaq    .printInt(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(PRINT, "\n", -, -) ---
    leaq    .str_8(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(LESS, _temp4_, number, 2) ---
    movl    _number(%rip), %eax
    cmpl    _2(%rip), %eax
    setl    %al
    movzbl  %al, %eax
    movl    %eax, __temp4_(%rip)

# --- Tac(IFZ, _label0_, _temp4_, -) ---
    movl    __temp4_(%rip), %eax
    testl   %eax, %eax
    jz      _label0_

# --- Tac(PRINT, "< TRUE\n", -, -) ---
    leaq    .str_3(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label1_, -, -) ---
    jmp    _label1_

# --- Tac(LABEL, _label0_, -, -) ---
_label0_:

# --- Tac(PRINT, "< FALSE\n", -, -) ---
    leaq    .str_2(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(LABEL, _label1_, -, -) ---
_label1_:

# --- Tac(GREATER, _temp5_, number, 2) ---
    movl    _number(%rip), %eax
    cmpl    _2(%rip), %eax
    setg    %al
    movzbl  %al, %eax
    movl    %eax, __temp5_(%rip)

# --- Tac(IFZ, _label2_, _temp5_, -) ---
    movl    __temp5_(%rip), %eax
    testl   %eax, %eax
    jz      _label2_

# --- Tac(PRINT, "> TRUE\n", -, -) ---
    leaq    .str_6(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label3_, -, -) ---
    jmp    _label3_

# --- Tac(LABEL, _label2_, -, -) ---
_label2_:

# --- Tac(LABEL, _label3_, -, -) ---
_label3_:

# --- Tac(LE, _temp6_, number, 4) ---
    movl    _number(%rip), %eax
    cmpl    _4(%rip), %eax
    setle   %al
    movzbl  %al, %eax
    movl    %eax, __temp6_(%rip)

# --- Tac(IFZ, _label4_, _temp6_, -) ---
    movl    __temp6_(%rip), %eax
    testl   %eax, %eax
    jz      _label4_

# --- Tac(PRINT, "<= TRUE\n", -, -) ---
    leaq    .str_4(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label5_, -, -) ---
    jmp    _label5_

# --- Tac(LABEL, _label4_, -, -) ---
_label4_:

# --- Tac(LABEL, _label5_, -, -) ---
_label5_:

# --- Tac(GE, _temp7_, number, 4) ---
    movl    _number(%rip), %eax
    cmpl    _4(%rip), %eax
    setge   %al
    movzbl  %al, %eax
    movl    %eax, __temp7_(%rip)

# --- Tac(IFZ, _label6_, _temp7_, -) ---
    movl    __temp7_(%rip), %eax
    testl   %eax, %eax
    jz      _label6_

# --- Tac(PRINT, ">= TRUE\n", -, -) ---
    leaq    .str_7(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label7_, -, -) ---
    jmp    _label7_

# --- Tac(LABEL, _label6_, -, -) ---
_label6_:

# --- Tac(LABEL, _label7_, -, -) ---
_label7_:

# --- Tac(EQ, _temp8_, number, 3) ---
    movl    _number(%rip), %eax
    cmpl    _3(%rip), %eax
    sete    %al
    movzbl  %al, %eax
    movl    %eax, __temp8_(%rip)

# --- Tac(IFZ, _label8_, _temp8_, -) ---
    movl    __temp8_(%rip), %eax
    testl   %eax, %eax
    jz      _label8_

# --- Tac(PRINT, "== TRUE\n", -, -) ---
    leaq    .str_5(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label9_, -, -) ---
    jmp    _label9_

# --- Tac(LABEL, _label8_, -, -) ---
_label8_:

# --- Tac(LABEL, _label9_, -, -) ---
_label9_:

# --- Tac(DIF, _temp9_, number, 55) ---
    movl    _number(%rip), %eax
    cmpl    _55(%rip), %eax
    setne   %al
    movzbl  %al, %eax
    movl    %eax, __temp9_(%rip)

# --- Tac(IFZ, _label10_, _temp9_, -) ---
    movl    __temp9_(%rip), %eax
    testl   %eax, %eax
    jz      _label10_

# --- Tac(PRINT, "!= TRUE\n", -, -) ---
    leaq    .str_0(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label11_, -, -) ---
    jmp    _label11_

# --- Tac(LABEL, _label10_, -, -) ---
_label10_:

# --- Tac(LABEL, _label11_, -, -) ---
_label11_:

# --- Tac(EQ, _temp10_, number, 3) ---
    movl    _number(%rip), %eax
    cmpl    _3(%rip), %eax
    sete    %al
    movzbl  %al, %eax
    movl    %eax, __temp10_(%rip)

# --- Tac(EQ, _temp11_, number, 3) ---
    movl    _number(%rip), %eax
    cmpl    _3(%rip), %eax
    sete    %al
    movzbl  %al, %eax
    movl    %eax, __temp11_(%rip)

# --- Tac(AND, _temp12_, _temp10_, _temp11_) ---
    movl    __temp10_(%rip), %eax
    andl    __temp11_(%rip), %eax
    movl    %eax, __temp12_(%rip)

# --- Tac(IFZ, _label12_, _temp12_, -) ---
    movl    __temp12_(%rip), %eax
    testl   %eax, %eax
    jz      _label12_

# --- Tac(PRINT, "& TRUE\n", -, -) ---
    leaq    .str_1(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label13_, -, -) ---
    jmp    _label13_

# --- Tac(LABEL, _label12_, -, -) ---
_label12_:

# --- Tac(LABEL, _label13_, -, -) ---
_label13_:

# --- Tac(EQ, _temp13_, number, 2) ---
    movl    _number(%rip), %eax
    cmpl    _2(%rip), %eax
    sete    %al
    movzbl  %al, %eax
    movl    %eax, __temp13_(%rip)

# --- Tac(EQ, _temp14_, number, 4) ---
    movl    _number(%rip), %eax
    cmpl    _4(%rip), %eax
    sete    %al
    movzbl  %al, %eax
    movl    %eax, __temp14_(%rip)

# --- Tac(OR, _temp15_, _temp13_, _temp14_) ---
    movl    __temp13_(%rip), %eax
    orl     __temp14_(%rip), %eax
    movl    %eax, __temp15_(%rip)

# --- Tac(IFZ, _label14_, _temp15_, -) ---
    movl    __temp15_(%rip), %eax
    testl   %eax, %eax
    jz      _label14_

# --- Tac(PRINT, "| TRUE\n", -, -) ---
    leaq    .str_9(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label15_, -, -) ---
    jmp    _label15_

# --- Tac(LABEL, _label14_, -, -) ---
_label14_:

# --- Tac(LABEL, _label15_, -, -) ---
_label15_:

# --- Tac(DIF, _temp16_, number, 3) ---
    movl    _number(%rip), %eax
    cmpl    _3(%rip), %eax
    setne   %al
    movzbl  %al, %eax
    movl    %eax, __temp16_(%rip)

# --- Tac(NOT, _temp17_, _temp16_, -) ---
    movl    __temp16_(%rip), %eax
    cmpl    $0, %eax
    sete    %al
    movzbl  %al, %eax
    movl    %eax, __temp17_(%rip)

# --- Tac(IFZ, _label16_, _temp17_, -) ---
    movl    __temp17_(%rip), %eax
    testl   %eax, %eax
    jz      _label16_

# --- Tac(PRINT, "~ TRUE\n", -, -) ---
    leaq    .str_10(%rip), %rax
    movq    %rax, %rdi
    call    printf@PLT

# --- Tac(JUMP, _label17_, -, -) ---
    jmp    _label17_

# --- Tac(LABEL, _label16_, -, -) ---
_label16_:

# --- Tac(LABEL, _label17_, -, -) ---
_label17_:

# --- Tac(END_FUNC, main, -, -) ---
    popq    %rbp
    ret
