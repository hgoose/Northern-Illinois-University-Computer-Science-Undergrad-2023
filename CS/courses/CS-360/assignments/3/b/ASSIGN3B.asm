//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
***************************************************************
* *                                                           *
* CSCI 360-1 ASSIGNMENT 3B
* spring 2025                                                 
* *                                                           *
* PROGRAMMER NAME: Nate Warner
* DATE DUE: 02/14/25
* *                                                           *
* MAIN PROGRAM NAME: ASSIGN3B                                        
* *
* FUNCTION: Now store the result of subtracting R3 from R2 into
*           fullword in storage named ANSWER. XDUMP this area of
*           storage to view the fullword
* *                                                           *
***************************************************************
ASSIGN3B CSECT
         USING ASSIGN3B,15 
*
         L 2,NUM1          Load contents of NUM1 into R2
         L 3,NUM2          Load contents of NUM2 into R3
         SR 2,3            Subtract contents of R3 from R2
         ST 2,ANSWER       Store the contents of R2 into ANSWER
         XDUMP ANSWER,4    Dump the storage containing ANSWER
         BCR   B'1111',14  Unconditional return to caller
*
         LTORG
*
NUM1     DC    F'15'       Define NUM1 with value 15
NUM2     DC    F'7'        Define NUM1 with value 7
ANSWER   DS    F           Define STORAGE uninitialized
*
         END   ASSIGN3B 
