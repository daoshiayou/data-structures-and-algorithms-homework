;ȥ���ַ����е�ĳ���ַ�
;���������ַ���string���ַ���������15������Enter �������룻��ʾ�����ַ�
;���������ַ�ch��Enter�������룬���ַ�����chȥ��
;����仯����ַ���String2����Enter�����˳�
DATAS SEGMENT
    inputMsg DB 'Please enter a string of a length greater than 14:$'
    chMsg DB 'Please enter the character to delete$'
    outputMsg DB 'The deleted string is:$'
    rMsg DB 'Press Enter to exit$'
    DCH db ?
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
    ;��������ַ���
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
	CMP AL,0FH
	JB ERROR
	;�����ʾ�����ַ�
    LEA DX,chMsg
    MOV AH,09H
    INT 21H
    ;����س�
	CALL NEWLINE
	;���������ַ�������Enter����	DO
	MOV AH,01H
INPUT:
	INT 21H
	CMP AL,0DH
	JE CONT
	MOV [DCH],AL
	JMP INPUT
CONT:
	;��������ʾ��Ϣ
	LEA DX,outputMsg
    MOV AH,09H
    INT 21H
    ;����س�
    CALL NEWLINE
    ;�����ӳ���ɾ���ַ���	DO
    CALL DELETECH
    ;�����ӳ�������ַ���	DO
    CALL ADJUST
    ;���������ַ���
    LEA DX,BUF+2
    MOV AH,09H
    INT 21H
    ;����س�
    CALL NEWLINE
    ;���������ʾ��Ϣ
    LEA DX,rMsg
    MOV AH,09H
    INT 21H
    ;����س�
    CALL NEWLINE
	;����Enter����	DO
	MOV AH,01H
QUIT:
	INT 21H
	CMP AL,0DH
	JNE QUIT
    MOV AH,4CH
    INT 21H    
    
DELETECH PROC
	MOV AL,[BUF+1]
	CBW
	MOV SI,AX
	MOV BX,AX	;BX����ԭ�ַ�������
	MOV BUF+2[SI],'$'
	MOV CX,AX
	XOR SI,SI
	MOV AH,AL
	MOV AL,[DCH]
LOP1:
	CMP AL,BUF+2[SI]
	JNE CONT1
	DEC AH
	MOV BUF+2[SI],0FFH
CONT1:
	ADD SI,TYPE BUF
	LOOP LOP1
	MOV [BUF+1],AH
	RET
DELETECH ENDP

ADJUST PROC
	MOV CX,BX
	XOR SI,SI
LOP2:
	CMP BUF+2[SI],0FFH
	JNE CONT2
	;����Ԫ��ȫ��ǰ��
	PUSH CX
	PUSH SI
	PUSH BX
	MOV CX,BX
	SUB CX,SI
	MOV BX,SI
	ADD BX,TYPE BUF
LOP3:
	MOV AL,BUF+2[BX]
	MOV BUF+2[SI],AL
	ADD SI,TYPE BUF
	ADD BX,TYPE BUF
	LOOP LOP3
	POP BX
	POP SI
	POP CX
	SUB SI,TYPE BUF
CONT2:
	ADD SI,TYPE BUF
	LOOP LOP2
	RET
ADJUST ENDP

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




