;��ʾ�������֣�������������int1��1000���ڣ������Enter�������룻
;���int1 ���������������int1 is a prime number����
;���int1 �����������������int1 is not a prime number���� 
;���Enter �����˳���
DATAS SEGMENT
    inputMsg DB 'Please enter a integer under1000:$'
    pMsg DB 'int1 is a prime number$'
    nPMsg DB 'int1 is not a prime number$'
    rMsg DB 'Press Enter to quit$'
DATAS ENDS

STACKS SEGMENT
    DW   20H   DUP(0);�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;�˴��������δ���
ERROR:
	XOR BX,BX
	LEA DX,inputMsg
	MOV AH,09H
	INT 21H
INPUT:
   	MOV AH,01H		;����dos����
    INT 21H
    CMP AL,0DH		;�ж��Ƿ��ǻ���
    JE JUDGE
    SUB AL,30H		;��30H��պ�������
    JL ERROR		;�ж�������Ƿ�������
    CMP AL,9
    JG START
    CBW				;�ֽ�ת��
    XCHG AX,BX		;֮ǰ����ֵ��AXת��
    MOV CX,10		;֮ǰ����ֵ��10
    MUL CX
    XCHG AX,BX		;��10��浽BX
    ADD BX,AX		;����֮ǰ���������
    JMP INPUT
JUDGE:
	CMP BX,1000
	JAE ERROR
	CMP BX,3H
	JB SUCCESS
	MOV CX,BX
	AND CX,1H
	JCXZ FAIL		;��2		
	MOV AX,BX
	MOV CX,6
	MUL CX
	MOV CX,AX
	SHR CX,1H
	AND CX,1H
	JCXZ FAIL		;��3
	MOV CX,BX
	SHR CX,1H
	SUB CX,1H
	PUSH BX
	MOV BX,3H
JUD:
	POP DX
	MOV AX,DX
	PUSH DX
	XOR DX,DX
	INC BX
	DIV BX
	CMP DX,0
	JE FAIL
	LOOP JUD
	JMP SUCCESS
SUCCESS:
	LEA DX,pMsg
	MOV AH,09H
	INT 21H
	JMP RETURN
FAIL:
    LEA DX,nPMsg
	MOV AH,09H
	INT 21H
RETURN:
	MOV DL,0DH
	MOV AH,02H
	INT 21H
	MOV DL,0AH
	INT 21H 
	LEA DX,rMsg
	MOV AH,09H
	INT 21H
	MOV AH,01H		;����dos����
    INT 21H
    CMP AL,0DH		;�ж��Ƿ��ǻ���
    JNE ERROR
	MOV AH,4CH
    INT 21H
CODES ENDS
    END START







