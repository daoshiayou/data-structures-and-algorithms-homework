;1���Ӽ�������һ���ַ���������15~80��
;2����ʮ��������ַ����з���ĸ�ַ��ĸ���������a to z �� A to Z��
;3�����ԭ�ַ����������ĸ�ַ���˸��ʾ
;4���ҳ��ַ�����ASCII ��ֵ�����ַ������ַ������ú�ɫ��ʾ
;5���ַ���������ͽ���������Ҫ�б�Ҫ����ʾ������ʾ��ռһ�У�
;6��Ҫʹ�õ��ӳ���
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
    DW 20H DUP(0);�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;���������ʾ��Ϣ
ERROR:
    LEA DX,inputMsg
    MOV AH,09H
    INT 21H
    ;����س�
    CALL NEWLINE
	;����������ַ���
	LEA DX,BUF
	MOV AH,0AH
	INT 21H
	;����س�
	CALL NEWLINE
	;�����ӳ���
	CALL DETECTION
	PUSH BX
	PUSH DX
	;��������ʾ��Ϣ
	LEA DX,rMsg
    MOV AH,09H
    INT 21H
    ;����س�
	CALL NEWLINE
	;16λת10���ƣ�����ʾ
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
    ;����س�
    CALL NEWLINE
    ;��������ʾ��Ϣ
    LEA DX,outputMsg
    MOV AH,09H
    INT 21H
    ;����س�
    CALL NEWLINE
    ;����ӹ�����ַ���
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
	;��һ��ѭ������ΪҪ��ʼ��BX������д
	MOV AL,BUF+2[SI]
	MOV BL,AL	;BL�����ascii��
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






