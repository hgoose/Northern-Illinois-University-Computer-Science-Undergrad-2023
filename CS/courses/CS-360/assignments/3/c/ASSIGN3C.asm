//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
***************************************************************
* *                                                           *
* CSCI 360-1 ASSIGNMENT 3C
* spring 2025                                                 
* *                                                           *
* PROGRAMMER NAME: Nate Warner
* DATE DUE: 02/14/25
* *                                                           *
* MAIN PROGRAM NAME: ASSIGN3C                                        
* *
* FUNCTION: Take ASSIGN3B and make implicit addressing explicit 
*           for load, store, and SR instructions. 
*          
* *                                                           *
***************************************************************
ASSIGN3C CSECT
         USING ASSIGN3C,15 
*
         L 2,24(,15)       Load R2 with FW 24 bytes off 15
         L 3,28(,15)       Load R3 with FW 28 bytes off 15
         SR 2,3            Subtract contents of R3 from R2
         ST 2,32(,15)      Store the contents of R2 into ANSWER
*                          which is 32 bytes off 15                          
*
         XDUMP ANSWER,4    Dump the storage containing ANSWER
         BCR   B'1111',14  Unconditional return to caller
*
         LTORG
*
         DC    F'15'       Define FW in storage with value 15 
         DC    F'7'        Define FW in storage with value 7
ANSWER   DS    F           Define ANSWER uninitialized
*
         END   ASSIGN3C 
