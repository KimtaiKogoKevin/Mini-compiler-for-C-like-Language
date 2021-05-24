.data
prompt1: .asciiz "\nEnter X"
prompt2: .asciiz "\nEnter Y"
variableX: .asciiz "\nX:"
variableY: .asciiz "\nY:"
final: .asciiz "\n Final Result"
fileName: .asciiz "C:/Users/Kevin/Documents/compiler/src/out.txt"
filewords: .space 1024


.text 


main:
li $v0 ,4 #print string
la $a0, prompt1 #choose enter x
syscall
li $v0 , 4  #print string
la $a0, variableX 
syscall
li $v0,5
syscall
move $t0,$v0



li $v0,4  #print string
la ,$a0 , prompt2 #choose enter
syscall
li $v0 , 4 #print string
la $a0, variableY #choosey 
syscall
li $v0,5
syscall
move $t1 ,$v0
li $t3,1
beq	$t0, $t3, ELSE	# if $t0 != $t1 then target
add $t1,$t0,$t0 #y = x + x
li $t0,0 # x = 0
li $v0 , 4 #print string
la $a0 , final #print FINAL
syscall
li $v0 , 4 #print string

la , $a0 , variableY #choose  variabley
syscall
move $a0,$t1 #move y to console
li $v0,1 #print console
syscall
li $v0 , 4 #print string
la , $a0 , variableX #choose  variabley
syscall
move $a0 , $t0  #move  X to console
li $v0,1
syscall
j Exit
ELSE: add $t1 , $t1,$t3 #y++
li $v0 , 4 #print string
la $a0 , final #print string
syscall
li $v0 , 4 
la , $a0 , variableY #choose  variabley
syscall
move $a0,$t1 #move y to console
li $v0,1 #print console
syscall
li $v0 , 4 #print string
la , $a0 , variableX #choose  variabley
syscall
move $a0 , $t0  #move  X to console
li $v0,1
syscall

Exit:
li $v0,10
syscall
