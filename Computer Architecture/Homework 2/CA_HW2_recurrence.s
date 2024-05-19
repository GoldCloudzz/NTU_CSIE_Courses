.globl __start

.text
__start:
    # Read n
    li a0, 5
    ecall
    mv s0, a0
    
jal x1, fib
addi sp, sp, 24
addi s3, x10, 0
beq x0, x0, output

fib:
    addi sp, sp, -24
    sw x1, 16 (sp)
    sw x10, 8 (sp)
    sw s0, 0 (sp)
    addi t0, s0, -1
    bgt t0, x0, fib_loop # If s0 > 1, jump to loop
    addi x10, s0, 0 # If s0 <= 1, T(n) = n
    jalr x0, 0 (x1)
    
fib_loop:
    addi s0, s0, -1
    jal x1, fib # Calculate T(n - 1)
    addi sp, sp, 24
    lw s0, 0 (sp)
    addi s0, s0, -2
    jal x1, fib # Calculate T(n - 2)
    lw t0, 8 (sp) # Load the result of T(n - 1) to t0
    slli t0, t0, 1 # t0: 2 * T(n - 1)
    addi sp, sp, 24
    lw x1, 16 (sp)
    add x10, x10, t0 # T(n) = T(n - 2) + 2 * T(n - 1)
    jalr x0, 0 (x1)
    
output:
    # Output the result
    li a0, 1
    mv a1, s3
    ecall
    
exit:
    # Exit the program
    li a0, 10
    ecall