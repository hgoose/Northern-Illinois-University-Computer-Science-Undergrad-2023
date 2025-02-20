//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
DUMPPGM  CSECT
         USING DUMPPGM,15     ESTABLISH A BASE REGISTER
         L     1,ONE          LOAD THE FIRST NUMBER INTO R1
         L     2,TWO          LOAD THE SECOND INTO R2
         AR    1,2            ADD THE TWO NUMBERS
         ST    1,THREE        STORE THE RESULT
         XDUMP THREE,4        DUMP THE RESULT
         BCR   B'1111',14     RETURN TO CALLER
*
*     NO LTORG NECESSARY
*
ONE      DC    F'64'          FIRST NUMBER
TWO      DC    F'32'          SECOND NUMBER
EOFFLAG  DC    C'0'           A FLAG SAVE AREA
THREE    DS    CL4' '         SUM OF THE TWO NUMBERS
*
         END   DUMPPGM
