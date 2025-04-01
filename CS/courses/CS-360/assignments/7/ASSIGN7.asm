//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
***************************************************************
* *                                                            *
* CSCI 360-1 ASSIGNMENT 7
* spring 2025                                                 
* *                                                           *
* PROGRAMMER NAME: Nate Warner
* DATE DUE: 4/1/25
* *                                                           *
* MAIN PROGRAM NAME: PAYROLL                                       
* *
* FUNCTION: An introduction to packed decimal and PD arithmetic.
*           Output information on empyloyees and calculate gross
*           pay with packed decimal arithmetic
* *                                                           *
***************************************************************
*
PAYROLL CSECT
*
* STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13) SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15 COPY CSECT ADDR INTO R12
         USING PAYROLL,12 ESTABLISH R12 AS THE BASE REG
         LA    14,SAVEAREA R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13) STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14) STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14 POINT R13 AT THIS CSECT'S SAVE AREA
*
* Here is where you will write your program.
*
         XREAD RECORD,80                 Beginning of read loop 
LOOP1    BC    B'0111',ENDLOOP1          Branch if done
*
         MVI DETAIL+1,C' '               Reset detail line
         MVC DETAIL+2(131),DETAIL+1      Reset detail line
*
* Copy employee name and ID to printline
*
         MVC   OEMPNME(25),IEMPNME       Copy into printline
         MVC   OEMPID(6),IEMPID          Copy into printline
* 
* Convert pay to PD and edit into printline
*
         PACK  PHRPAY(3),IHRPAY(5)       Convert pay to PD
         LA    1,IHRPAY+3                Safety mark
         MVC   OHRPAY,=X'402021204B2020' Construct the edit pattern
         EDMK  OHRPAY(7),PHRPAY          Edit pay to printline
         BCTR  1,0                       Move R1 to $ position
         MVI   0(1),C'$'                 Place $
*
* Convert hours to PD and edit to printline
*
         PACK  PHOUR(3),IHOURS(5)           Convert hours to PD
         MVC   OHOURS(7),=X'402021204B2020' Construct edit pattern
         ED    OHOURS(7),PHOUR              Edit to printline
*
* Calculate gross pay
*
         ZAP   PGRPAY(6),PHRPAY(3)          Zap pay into larger field
         MP    PGRPAY(6),PHOUR(3)           Multiply pay by hours
         SRP   PGRPAY(6),64-2,5             Shift right 2 and round
         LA    1,PGRPAY+8                   Saftey mark for $
         MVC   OGROSS,=X'402020206B2020206B2021204B2020' Construct EP
         EDMK  OGROSS(15),PGRPAY            Edit gross into printline
         BCTR  1,0                          Move R1 to $ position
         MVI   0(1),C'$'                    Place $
*
         XPRNT DETAIL,133                   Print the line
         XREAD RECORD,80                    Read the next record
         BC    B'1111',LOOP1                Branch to check
ENDLOOP1 DS    0H                           End of loop
*
* STANDARD EXIT LINKAGE WITH RC OF 0
*
         SR    15,15 R15 = RETURN CODE OF 0
         L     13,4(,13) POINT R13 TO CALLER'S SAVE AREA
         L     14,12(,13) RESTORE REGISTER 14
         LM    0,12,20(13) RESTORE R0 THRU R12
*
         BR    14 RETURN TO CALLER
*
         LTORG
*
         ORG PAYROLL+((*-PAYROLL+31)/32)*32
         DC C'* PROGRAM STORAGE FOR PAYROLL **'
*
SAVEAREA DS 18F REGISTER SAVE AREA
*
* Here is where your storage will be defined.
*
RECORD   DS    0H
IEMPNME  DS    CL25
IEMPID   DS    CL6
IHRPAY   DS    ZL5
IHOURS   DS    ZL5
FILL     DS    39C' '
*
PHRPAY   DC    PL3'0'
PHOUR    DC    PL3'0'
PGRPAY   DC    PL6'0'
*
DETAIL   DC    C'0'
OEMPNME  DS    CL25
         DC    4C' '
OEMPID   DS    CL6
         DC    5C' '
OHRPAY   DS    CL7
         DC    5C' '
OHOURS   DS    CL7
         DC    5C' '
OGROSS   DS    CL15
         DC    4C' '
         DC    73C' '
         END PAYROLL
/*
//*
//FT05F001 DD DSN=KC02322.CSCI360.DATASP25(DATA7),DISP=SHR
//*
//FT06F001 DD SYSOUT=*
//
