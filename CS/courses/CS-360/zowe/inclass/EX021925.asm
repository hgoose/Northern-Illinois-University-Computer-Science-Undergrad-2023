 //KC02322A JOB ,'G. DECKER',MSGCLASS=H 
 //JSTEP01  EXEC PGM=ASSIST 
 //STEPLIB  DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR 
 //SYSPRINT DD SYSOUT=* 
 //SYSIN    DD * 
 * 
 EX021925 CSECT 
          USING EX021925,15     ESTABLISH ADDRESSABILITY ON R15 
 * 
          L     3,NUM1 
          XDECO 3,ONUM1         CONVERT AND PLACE R3'S CONTENTS 
          L     4,NUM2 
          XDECO 4,ONUM2 
          AR    4,3 
          XDECO 4,OSUM 
 * 
          XPRNT HEADER1,133 
          XPRNT COLHDR1,133     PRINT COLUMN HEADER 1 
          XPRNT HYPHENS1,133    PRINT HYPHENS 
          XPRNT DETAIL,133      PRINT DETAIL LINE 
 * 
          BCR   B'1111',14 
 * 
          LTORG 
 * 
 NUM1     DC    F'35' 
 NUM2     DC    F'22' 
 SUM      DS    F 
 * 
 DETAIL   DC    C' '         CARRIAGE CONTROL CHARACTER 
 ONUM1    DS    CL12         OUTPUT AREA FOR NUM1 
          DC    5C' '        SPACES 
 ONUM2    DS    CL12         OUTPUT AREA FOR NUM2 
          DC    5C' '        SPACES 
 OSUM     DS    CL12         OUTPUT AREA FOR THE SUM OF NUM1 + NUM2 
          DC    86C' '       SPACES 
* 
HEADER1  DC    C'1' 
         DC    57C' ' 
         DC    C'HERE IS MY REPORT' 
         DC    58C' ' 
* 
COLHDR1  DC    C'0'              CARRIAGE CONTROL CHARACTER 
         DC    C'        NUM1'   OUTPUT AREA FOR NUM1 
         DC    5C' '             SPACES 
         DC    C'        NUM2'   OUTPUT AREA FOR NUM2 
         DC    5C' '             SPACES 
         DC    C'         SUM'   OUTPUT AREA FOR THE SUM 
         DC    86C' '            SPACES 
* 
HYPHENS1 DC    C' '              CARRIAGE CONTROL CHARACTER 
         DC    C'------------'   OUTPUT AREA FOR NUM1 
         DC    5C' '             SPACES 
         DC    C'------------'   OUTPUT AREA FOR NUM2 
         DC    5C' '             SPACES 
         DC    C'------------'   OUTPUT AREA FOR THE SUM 
         DC    86C' '            SPACES 
* 
         END   EX021925 
/* 
