mod1: begin
mod2: extern
INPUT OLD_DATA
LOAD OLD_DATA
L1: 
; asdad
DIV DOIS
STORE  NEW_DATA
MUL DOIS
STORE TMP_DATA
LOAD OLD_DATA
SUB TMP_DATA
STORE TMP_DATA
OUTPUT TMP_DATA
COPY NEW_DATA,OLD_DATA
LOAD OLD_DATA
JMPP L1
jmp mod2
DOIS: CONST 2
OLD_DATA: SPACE
NEW_DATA: SPACE
TMP_DATA: SPACE
end