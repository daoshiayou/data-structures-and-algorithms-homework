;�����¹��ɱ��룺��ĸA��ΪE��a��Ϊe����������ĵ�4����ĸ��W��ΪA��Y��ΪC��Z��ΪD������ĸ���䡣�����롰China����Ϊ��Glmre����
;Ҫ����ʾ����һ�ַ������ַ���������Ϊ8����
;�������룬Enter���������룬��������ʾ���
DATAS SEGMENT
    inputMsg DB 'Please enter a string of length greater than 7$'
    outputMsg DB 'The converted string is:$'
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
	;����ַ�������
	MOV AL,[BUF+1]
	CMP AL,08H
	JB ERROR
	;�ַ��ӹ�
	CALL TRANSFORM
    ;��������ʾ��Ϣ
    LEA DX,outputMsg
    MOV AH,09H
    INT 21H
    ;����س�
    CALL NEWLINE
    ;����ӹ�����ַ���
    LEA DX,BUF+2
    MOV AH,09H
    INT 21H
    MOV AH,4CH
    INT 21H    
    
TRANSFORM PROC
	MOV AL,[BUF+1]
	INC AL
	MOV [BUF+1],AL
	CBW
	MOV SI,AX
	DEC SI
	MOV BUF+2[SI],'$'
	MOV CX,AX
	XOR SI,SI
LOP:
	MOV AL,BUF+2[SI]
	CMP AL,'A'
	JB CONT
	CMP AL,'z'
	JG CONT
	CMP AL,'Z'
	JBE ALPH
	CMP AL,'a'
	JGE ALPH
	JMP CONT
ALPH:
	ADD AL,04H
	CMP AL,'Z'
	JBE CONT
	CMP AL,'Z'+4
	JBE TOA
	CMP AL,'z'
	JBE CONT
TOA:
	SUB AL,1AH
CONT:
	MOV BUF+2[SI],AL
	ADD SI,TYPE BUF
	LOOP LOP
	RET
TRANSFORM ENDP

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










