;1）从键盘输入一个字符串（串长15~80）
;2）以十进制输出字符串中非字母字符的个数（不是a to z 或 A to Z）
;3）输出原字符串且令非字母字符闪烁显示
;4）找出字符串中ASCII 码值最大的字符，在字符串中用红色显示
;5）字符串的输入和结果的输出都要有必要的提示，且提示独占一行；
;6）要使用到子程序
DATAS SEGMENT
    inputMsg DB 'Please enter a string of length 15 to 80:$'
    rMsg DB 'The number of nonalphabetic characters in the string is:$'
    outputMsg DB 'The string you enter is:$'
    STRING DW 50H DUP(0)
    BUF DB 50H
    	DB ? 
    	DB 50H DUP(0)
    
DATAS ENDS

STACKS SEGMENT
    DW 20H DUP(0);此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;输出输入提示信息
ERROR:
    LEA DX,inputMsg
    MOV AH,09H
    INT 21H
    ;输出回车
    CALL NEWLINE
	;接收输入的字符串
	LEA DX,BUF
	MOV AH,0AH
	INT 21H
	;输出回车
	CALL NEWLINE
	;调用子程序
	CALL DETECTION
	PUSH BX
	PUSH DX
	;输出输出提示信息
	LEA DX,rMsg
    MOV AH,09H
    INT 21H
    ;输出回车
	CALL NEWLINE
	;16位转10进制，并显示
	POP DX
    MOV AX,DX
    MOV DL,0AH
    DIV DL
    ADD AL,30H
    ADD AH,30H
    MOV DL,AL
    MOV DH,AH
    MOV AH,02H
    INT 21H
    MOV DL,DH
    INT 21H
    ;输出回车
    CALL NEWLINE
    ;输出输出提示信息
    LEA DX,outputMsg
    MOV AH,09H
    INT 21H
    ;输出回车
    CALL NEWLINE
    ;输出加工后的字符串
    POP BX
    CALL SHOWSTRING
    MOV AH,4CH
    INT 21H    
    
DETECTION PROC
	MOV AL,BUF+1
	CMP AL,0FH
	JB ERROR
    CBW
    MOV CX,AX
    XOR DX,DX
    XOR SI,SI
    LEA DI,STRING
	;第一次循环，因为要初始化BX所以另写
	MOV AL,BUF+2[SI]
	MOV BL,AL	;BL存最大ascii码
	CMP AL,41H
	JB ANALPH
	CMP AL,7AH
	JG ANALPH
	CMP AL,5AH
	JBE ALPH
	CMP AL,61H
	JGE ALPH
ANALPH:
	MOV AH,87H
	MOV [DI],AX
	INC DX
	LOOP LOP1
	JMP OVER
ALPH:
	MOV AH,7H
	MOV [DI],AX
	LOOP LOP1
	JMP OVER
LOP1:
	ADD DI,TYPE STRING
	INC SI
	MOV AL,BUF+2[SI]
	CMP AL,BL
	JBE CONT1
	MOV BL,AL
CONT1:
	CMP AL,41H
	JB ANALPH
	CMP AL,7AH
	JG ANALPH
	CMP AL,5AH
	JBE ALPH
	CMP AL,61H
	JGE ALPH
	JMP ANALPH
OVER:
	RET
DETECTION ENDP

SHOWSTRING PROC
	MOV AL,BUF+1
	CBW
	MOV CX,AX
	XOR DX,DX
	MOV DH,BL
	XOR BX,BX
	LEA DI,STRING
LOP2:
	MOV AX,[DI]
	ADD DI,TYPE STRING
	CMP AL,DH
	JNE CONT2
	AND AH,0F4H
CONT2:
	MOV BL,AH
	PUSH CX
	INC DL
	PUSH DX
	MOV CX,01H
	MOV AH,09H
	INT 10H
	MOV AH,02H
	MOV DL,AL
	INT 21H
	POP DX
	POP CX
	LOOP LOP2
	RET
SHOWSTRING ENDP

NEWLINE PROC
	MOV DL,0DH
	MOV AH,02H
	INT 21H
	MOV DL,0AH
	INT 21H
	RET
NEWLINE ENDP

CODES ENDS
    END START






