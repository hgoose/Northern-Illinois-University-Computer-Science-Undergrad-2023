//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
***************************************************************
* *                                                            *
* CSCI 360-1 ASSIGNMENT 8
* spring 2025                                                 
* *                                                           *
* PROGRAMMER NAME: Nate Warner
* DATE DUE: 4/11/25
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
* Preliminary XREAD to get fed and state withholding
         XREAD IFEDWITH,80               Get withholding percents
         PACK  PFWHPCT(4),IFEDWITH(6)    Convert stwith to PD
         PACK  PSWHPCT(4),ISTWITH(6)     Convert Fedwith to PD
*
         XREAD RECORD,80                 Beginning of read loop 
LOOP1    BC    B'0111',ENDLOOP1          Branch if done
*
         MVI DETAIL+1,C' '               Reset detail line
         MVC DETAIL+2(131),DETAIL+1      Reset detail line
*
* Handle EmpID
*
         PACK  PEMPID(5),IEMPID(8)                 Convert EMPID to PD
         SRP   PEMPID(5),1,0
         MVC   OEMPID(10),=X'F0202060202020202020'
         ED    OEMPID(10),PEMPID                  Move ID into Output
*
* Handle hourly pay
*
         PACK  PHRPAY(3),IHRPAY(5) 
         LA    1,OHRPAY+3
         MVC   OHRPAY(7),=X'402021204B2020'
         EDMK  OHRPAY(7),PHRPAY
         BCTR  1,0
         MVI   0(1),C'$'
*
* Handle Hours worked
*
         PACK  PHOURS(3),IHOURS(5)
         MVC   OHOURS(6),=X'402021204B2020'
         ED    OHOURS(6),PHOURS
*
* Handle deduction amount 
*
         PACK  PDEDUCT(3),IDEDUCT(5)
*
* Handle bonus amount
*
         PACK  PBONUS(3),IBONUS(5)
*
* Handle Name
*
         MVC   OEMPNME(25),RECORD+28
*
* PRINT, READ, BRANCH  
*
         XPRNT DETAIL+1,133                   Print the line
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
* STORAGE FOR INITIAL XREAD
*
IFEDWITH DS    ZL6
ISTWITH  DS    ZL6
FILL1    DS    CL68
* 
* STORAGE FOR LOOPED XREAD
*
RECORD   DS    0H
IEMPID   DS    ZL8 
IHRPAY   DS    ZL5 
IHOURS   DS    ZL5 
IDEDUCT  DS    ZL5
IBONUS   DS    ZL5 
IEMPNME  DS    CL25
         DS    CL27
*
* PACKED DECIMAL VARIABLES
*
PFWHPCT  DC    PL4'0' PACKED FEDERAL WITHHOLDING PERCENTAGE
PSWHPCT  DC    PL4'0' PACKED STATE WITHHOLDING PERCENTAGE
*
PEMPCTR  DC    PL3'0' PACKED EMPLOYEE COUNTER (MAX 999)
PPAGECTR DC    PL2'0' PACKED PAGE COUNTER (MAX 999)
*
PEMPID   DC    PL5'0' PACKED EMPLOYEE ID
PHRPAY   DC    PL3'0' PACKED EMPLOYEE HOURLY PAY RATE
PHOURS   DC    PL3'0' PACKED EMPLOYEE HOURS WORKED
PDEDUCT  DC    PL3'0' PACKED EMPLOYEE DEDUCTION
PBONUS   DC    PL3'0' PACKED EMPLOYEE BONUS
PGRPAY   DC    PL6'0' PACKED CALCULATED EMPLOYEE GROSS PAY
PFEDWITH DC    PL6'0' PACKED CALCULATED FEDERAL WITHHOLDING
PSTWITH  DC    PL6'0' PACKED CALCULATED STATE WITHHOLDING
PNETPAY  DC    PL6'0' PACKED CALCULATED EMPLOYEE NET PAY
*
PCALC    DC    PL10'0' USED TO CALCULATE WITHHOLDING AND AVGS
*
PTGRPAY  DC    PL7'0' PACKED TOTAL GROSS EMPLOYEE PAY
PTFWITH  DC    PL7'0' PACKED TOTAL FEDERAL WITHHOLDING
PTSWITH  DC    PL7'0' PACKED TOTAL STATE WITHHOLDING
PTNETPAY DC    PL7'0' PACKED TOTAL NET EMPLOYEE PAY
*
*
* STORAGE FOR MAIN PRINT LINE
*
DETAIL   DC    C'0'
*
OEMPID   DS    CL10
         DC    2C' '
*
OEMPNME  DS    CL25
         DC    4C' '
*
OHRPAY   DS    CL7
         DC    4C' '
*
OHOURS   DS    CL6
         DC    11C' '
*
OGRRPAY  DS    CL8
         DC    4C' '
*
OFEDWITH DS    CL8
         DC    4C' '
*
OSTWITH  DS    CL8
         DC    4C' '
*
ONET     DS    CL8
         DC    4C' '
*
FILL2    DC    28C' '    
         END PAYROLL
/*
//*
//FT05F001 DD DSN=KC02322.CSCI360.DATAFA24(DATA8),DISP=SHR
//*
//FT06F001 DD SYSOUT=*
//
