//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H
//JSTEP01 EXEC PGM=ASSIST
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR
//SYSPRINT DD SYSOUT=*
//SYSIN DD *
PROG2    CSECT
         USING PROG2,15
         L     3,NUM1
         L     4,NUM2
         AR    3,4
         S     3,RES
         XDUMP RES,4
         BCR   B'1111',14
*
         LTORG
*
NUM1     DC    F'12'
NUM2     DC    F'15'
RES      DS    F
*
         END   PROG2
