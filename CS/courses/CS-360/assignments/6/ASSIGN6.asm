//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
*****************************************************************
* *
* CSCI 360-1 ASSIGNMENT 6 FALL 2024 *
* *
* PROGRAMMER NAME: Nate Warner *
* DUE DATE: Wednesday, March 21 *
* *
* NO FURTHER DOCUMENTATION IS NECESSARY *
* *
*****************************************************************
*
DISASM   CSECT
         USING DISASM,15 ESTABLISH ADDRESSABILITY ON REG 15
*
         LA    4,23       Load 0x17 (23) into R4
         L     5,60(,15)  Load 0x3c (60) into R5
         LR    2,4        Load contents of R4 into R2
         AR    2,5        R2 += R5
         ST    2,64(,15)  Store R2 contents into addr 64(,25)
         LR    7,5        Load R5 into R7
         LR    6,4        Load R4 into R6
         MR    6,6        Multiply Even odd pair R6,R7 by R6
         ST    7,68(,15)  Store R7 into addr 68(,15)
         LR    9,4        Load R4 into R9
         M     4,80(,15)  Multiply R4,R5 by addr 80(,15)
         DR    4,9        Divide R5 by R9
         ST    4,72(,15)  Store R4 into 72(,15)
         ST    5,76(,15)  Store R5 into 76(,15)
         XDUMP DISASM,84  MEMDUMP 
         BCR   B'1111',14 Unconditional return to caller
*
         LTORG 
*
         DS    CL4
         DC    F'101'
         DS    F
         DS    F
         DS    F
         DS    F
         DC    F'1'
*
         END DISASM
