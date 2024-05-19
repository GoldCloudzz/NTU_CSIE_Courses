.globl __start

.rodata
    division_by_zero: .string "division by zero"

.text
__start:
    # Read first operand
    li a0, 5
    ecall
    mv s0, a0
    # Read operation
    li a0, 5
    ecall
    mv s1, a0
    # Read second operand
    li a0, 5
    ecall
    mv s2, a0

###################################
#  TODO: Develop your calculator  #
#                                 #
###################################

# op = 0: +

add s3, s0, s2
beq s1, x0, output # If s1 == 0, output (s0 + s2)

# op = 1: -

sub s3, s0, s2
li t1, 1
beq s1, t1, output # If s1 == 1, output (s0 - s2)

# op = 2: ×

mul s3, s0, s2
li t1, 2
beq s1, t1, output # If s1 == 2, output (s0 * s2)

# op = 3: /

li t1, 3
beq s1, t1, division # If s1 == 3, jump to division

# op = 4: min

li t1, 4
beq s1, t1, minimum # If s1 == 4, jump to minimum

# op = 5: ^

li t1, 5
beq s1, t1, power # If s1 == 5, jump to power

# op = 6: !

li t1, 6
beq s1, t1, factorial # If s1 == 6, jump to factorial

output:
    # Output the result
    li a0, 1
    mv a1, s3
    ecall

exit:
    # Exit program(necessary)
    li a0, 10
    ecall
    
division:
    beq s2, x0, division_by_zero_except # If s2 == 0, jump to division_by_zero_except
    div s3, s0, s2
    beq x0, x0, output # s1 == 3, output (s0 / s2)

division_by_zero_except:
    li a0, 4
    la a1, division_by_zero
    ecall
    jal zero, exit

minimum:
    add s3, s0, x0
    blt s0, s2, output # If s0 < s2, output s0
    add s3, s2, x0
    beq x0, x0, output # s0 >= s2, output s2
    
power:
    li t2, 0 # the times that we have multiplied
    li s3, 1
    beq x0, x0, power_loop # jump to loop
    
power_loop:
    beq s2, t2, output # If s2 == t2, output (s0 ^ s2)
    addi t2, t2, 1
    mul s3, s3, s0
    beq x0, x0, power_loop # continue loop
  
factorial:
    li t2, 0 # the number to multiply
    li s3, 1
    beq x0, x0, factorial_loop # jump to loop
    
factorial_loop:
    beq t2, s0, output # If t2 == s0, output (s0!)
    addi t2, t2, 1
    mul s3, s3, t2
    beq x0, x0, factorial_loop # continue loop