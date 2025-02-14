//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
***************************************************************
* *
* CSCI 360-1 ASSIGNMENT 3a
* spring 2025*
* *
* PROGRAMMER NAME: Nate Warner *
* DATE DUE: 2/13/25*
* *
* MAIN PROGRAM NAME: ASSIGN3A*
* *
* FUNCTION: Create two constants NUM1 and NUM2, 
*    load into registers 2 and 3, then subtract the contents of 
*    R3 from R2*
* *
***************************************************************
ASSIGN3A CSECT
         USING ASSIGN3A,15 
*
         L 2,NUM1          Load contents of NUM1 into R2
         L 3,NUM2          Load contents of NUM2 into R3
         SR 2,3            Subtract contents of R3 from R2
         XDUMP ,           Dump the 15 GPRs
         BCR   B'1111',14  Unconditional return to caller
*
         LTORG
*
NUM1     DC    F'15'       Define NUM1 with value 15
NUM2     DC    F'7'        Define NUM1 with value 7
*
         END   ASSIGN3A 
