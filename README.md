Набор утилит на эмуляторов Радио-86РК

rk86diff
========

Эта утилиты "умно" сравнивает файлы различных эмуляторов РК. Например,
есть два файлы `ASM_ED.RKR` и `ASM-ED.RK`. Их можно сравнить с помощью
утилиты `rk86diff`:

    ./rk86diff ASM_ED.RKR ASM-ED.RK
    
Результат:

    File 1: ASM_ED.RKR
    File 2: ASM-ED.RK
    ======================================
    Loading: [ASM_ED.RKR]
    File size: 4105
    Start: 0000
    End  : 0FFF
    Size : 1000
    Actual check sum: DCFF
    00
    00
    Found 2 trailing zero(s)
    Check sum: DCFF
    ======================================
    Loading: [ASM-ED.RK]
    File size: 4104
    Start: 0000
    End  : 0FFF
    Size : 1000
    Actual check sum: 1C41
    00
    Found 1 trailing zero(s)
    Check sum: 1C41
    ======================================
    > Summary
    E6 From To   Size 00..    E6 SUM  (real) Tail   Name
    -- ---- ---- ---- ------- -- ----------- ------ ----
    -- 0000 0FFF 1000 zeros=2 E6 DCFF (DCFF) tail=0 ASM_ED.RKR 
    -- 0000 0FFF 1000 zeros=1 E6 1C41 (1C41) tail=0 ASM-ED.RK 
    ======================================
    > prolog
    > start/end address
    > text
    0018/0018: 00 . . != 36 6 6 | F8C3*00* RM          | C3*00*F8 JMP F800    | *00*F8F5 NOP        

    0023/0023: FF . . != 00 . . | 0031*FF* NOP         | 31*FF*75 LXI SP,75FF | *FF*7521 RST 7      

    002D/002D: 19 . . != 30 0 0 | 2100*19* LXI H,1900  | 00*19*C3 NOP         | *19*C330 DAD D      

    04A5/04A5: 01 . . != 10 . . | CDF5*01* CALL 01F5   | F5*01*CA PUSH PSW    | *01*CA4A LXI B,4ACA 

    05EF/05EF: E7 . . != D0 . . | 2100*E7* LXI H,E700  | 00*E7*19 NOP         | *E7*193E RST 4      

    079E/079E: 45 E E != 72 r Р | 0D0A*45* DCR C       | 0A*45*44 LDAX B      | *45*442E MOV B,L    
    079F/079F: 44 D D != 65 e Е | 0A45*44* LDAX B      | 45*44*2E MOV B,L     | *44*2E2A MOV B,H    
    07A0/07A0: 2E . . != 64 d Д | 4544*2E* MOV B,L     | 44*2E*2A MOV B,H     | *2E*2A6D MVI L,2A   
    07A1/07A1: 2A * * != 61 a А | 442E*2A* MOV B,H     | 2E*2A*6D MVI L,2A    | *2A*6D69 LHLD 696D  
    07A2/07A2: 6D m М != 6B k К | 2E2A*6D* MVI L,2A    | 2A*6D*69 LHLD 696D   | *6D*696B MOV L,L    
    07A3/07A3: 69 i И != 74 t Т | 2A6D*69* LHLD 696D   | 6D*69*6B MOV L,L     | *69*6B72 MOV L,C    
    07A4/07A4: 6B k К != 6F o О | 6D69*6B* MOV L,L     | 69*6B*72 MOV L,C     | *6B*726F MOV L,E    

    07A6/07A6: 6F o О != 20     | 6B72*6F* MOV L,E     | 72*6F*6E MOV M,D     | *6F*6E2A MOV L,A    
    07A7/07A7: 6E n Н != 20     | 726F*6E* MOV M,D     | 6F*6E*2A MOV L,A     | *6E*2A0D MOV L,M    
    07A8/07A8: 2A * * != 20     | 6F6E*2A* MOV L,A     | 6E*2A*0D MOV L,M     | *2A*0D0A LHLD 0A0D  

    0805/0805: FF . . != 00 . . | 0031*FF* NOP         | 31*FF*75 LXI SP,75FF | *FF*7521 RST 7      

    0819/0819: 6C l Л != 36 6 6 | 31FA*6C* LXI SP,6CFA | FA*6C*F8 JM F86C     | *6C*F8FE MOV L,H    

    0851/0851: 19 . . != 30 0 0 | 2100*19* LXI H,1900  | 00*19*22 NOP         | *19*220F DAD D      

    086A/086A: FF . . != 00 . . | 1031*FF* 10          | 31*FF*75 LXI SP,75FF | *FF*75CD RST 7      

    0FE6/0FE6: 41 A A != 61 a А | 0D0A*41* DCR C       | 0A*41*53 LDAX B      | *41*5353 MOV B,C    
    0FE7/0FE7: 53 S S != 73 s С | 0A41*53* LDAX B      | 41*53*53 MOV B,C     | *53*534D MOV D,E    
    0FE8/0FE8: 53 S S != 73 s С | 4153*53* MOV B,C     | 53*53*4D MOV D,E     | *53*4D2E MOV D,E    
    0FE9/0FE9: 4D M M != 65 e Е | 5353*4D* MOV D,E     | 53*4D*2E MOV D,E     | *4D*2E2A MOV C,L    
    0FEA/0FEA: 2E . . != 6D m М | 534D*2E* MOV D,E     | 4D*2E*2A MOV C,L     | *2E*2A6D MVI L,2A   
    0FEB/0FEB: 2A * * != 62 b Б | 4D2E*2A* MOV C,L     | 2E*2A*6D MVI L,2A    | *2A*6D69 LHLD 696D  
    0FEC/0FEC: 6D m М != 6C l Л | 2E2A*6D* MVI L,2A    | 2A*6D*69 LHLD 696D   | *6D*696B MOV L,L    
    0FED/0FED: 69 i И != 65 e Е | 2A6D*69* LHLD 696D   | 6D*69*6B MOV L,L     | *69*6B72 MOV L,C    
    0FEE/0FEE: 6B k К != 72 r Р | 6D69*6B* MOV L,L     | 69*6B*72 MOV L,C     | *6B*726F MOV L,E    
    0FEF/0FEF: 72 r Р != 20     | 696B*72* MOV L,C     | 6B*72*6F MOV L,E     | *72*6F6E MOV M,D    
    0FF0/0FF0: 6F o О != 20     | 6B72*6F* MOV L,E     | 72*6F*6E MOV M,D     | *6F*6E2A MOV L,A    
    0FF1/0FF1: 6E n Н != 20     | 726F*6E* MOV M,D     | 6F*6E*2A MOV L,A     | *6E*2A0D MOV L,M    
    0FF2/0FF2: 2A * * != 20     | 6F6E*2A* MOV L,A     | 6E*2A*0D MOV L,M     | *2A*0D0A LHLD 0A0D  
    > trailing zeros
    1005     : 00 . .
    > checksum
    1007/1006: DC . . != 1C . .
    1008/1007: FF . . != 41 A A
