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
*
*
         LA    2,19                      Use R2 as line counter
         LA    3,19                      Use R3 to hold the key
*
* Start Loop
*
         XREAD RECORD,80                 Beginning of read loop 
LOOP1    BC    B'0111',ENDLOOP1          Branch if done
*
         MVI DETAIL+1,C' '               Reset detail line
         MVC DETAIL+2(131),DETAIL+1      Reset detail line
*
* Handle EmpID
*
         PACK  PEMPID(5),IEMPID(8)            Convert EMPID to PD
         MVC   OEMPID-1(10),=X'21202060202020202020'
         ED    OEMPID-1(10),PEMPID
         MVI   DETAIL,C'0'
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
         MVC   OHOURS(7),=X'402021204B2020'
         ED    OHOURS(7),PHOURS
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
* Handle Gross pay
*
         ZAP   PGRPAY(6),PHRPAY(3)
         MP    PGRPAY(6),PHOURS(3)
         SRP   PGRPAY(6),64-2,5
         SP    PGRPAY(6),PDEDUCT(3)
         AP    PGRPAY(6),PBONUS(3)
         LA    1,OGRPAY+11                   Saftey mark for $
         MVC   OGRPAY,=X'402020206B2020206B2021204B2020' Construct EP
         EDMK  OGRPAY(15),PGRPAY            Edit gross into printline
         BCTR  1,0                          Move R1 to $ position
         MVI   0(1),C'$'                    Place $
         AP    PTGRPAY(7),PGRPAY(6)
*
* Handle fed withholding amount
*
         ZAP   PCALC(10),PGRPAY(6)
         MP    PCALC(10),PFWHPCT(4)
         SRP   PCALC(10),64-5,5
         ZAP   PFEDWITH(6),PCALC(10)
         LA    1,OFEDWITH+11
         MVC   OFEDWITH(15),=X'402020206B2020206B2021204B2020'
         EDMK  OFEDWITH(15),PFEDWITH
         BCTR  1,0
         MVI   0(1),C'$'
         AP    PTFWITH(7),PFEDWITH(6)
*
* Handle State withholding amount
*
         ZAP   PCALC(10),PGRPAY(6)
         MP    PCALC(10),PSWHPCT(4)
         SRP   PCALC(10),64-5,5
         ZAP   PSTWITH(6),PCALC(10)
         LA    1,OSTWITH+11
         MVC   OSTWITH(15),=X'402020206B2020206B2021204B2020'
         EDMK  OSTWITH(15),PSTWITH
         BCTR  1,0
         MVI   0(1),C'$'
         AP    PTSWITH(7),PSTWITH(6)
*
* Handle Net Pay
*
         ZAP   PNETPAY(6),PGRPAY(6)     
         SP    PNETPAY(6),PFEDWITH(6)
         SP    PNETPAY(6),PSTWITH(6)
         LA    1,ONETPAY+11
         MVC   ONETPAY(15),=X'402020206B2020206B2021204B2020' 
         EDMK  ONETPAY(15),PNETPAY
         BCTR  1,0
         MVI   0(1),C'$'
         AP    PTNETPAY(7),PNETPAY(6)
*
* PRINT, READ, BRANCH  
*
         CR    2,3
         BC    B'0111',NOPRINT
         LA    2,0
         AP    PPAGECTR(2),=PL1'1'
         MVC   OPAGENM(4),=X'40202120'
         ED    OPAGENM(4),PPAGECTR
         XPRNT ONMEPAGE,133
         XPRNT OTITLE,133
         XPRNT OHEAD1,133
         XPRNT OHEAD2,133
         XPRNT OHEAD3,133
NOPRINT  DS    0H
*
         XPRNT DETAIL,133                   Print the line
         AP    PEMPCTR(3),=PL1'1'
         LA    2,1(,2)
         XREAD RECORD,80                    Read the next record
         BC    B'1111',LOOP1                Branch to check
ENDLOOP1 DS    0H                           End of loop
*
* Print Totals page headers
         AP    PPAGECTR(2),=PL1'1'
         MVC   OPAGENM(4),=X'40202120'
         ED    OPAGENM(4),PPAGECTR
         XPRNT ONMEPAGE,133
         XPRNT OTITLE,133
         XPRNT OTOTALS,133
*
* Handle total number of employees
*
         MVC   OTEMPCT(6),=X'402020202120' 
         ED    OTEMPCT(6),PEMPCTR
         XPRNT OEMPCTR,133
*
* Setup for averages
*
         SRP   PEMPCTR(3),2,0
*
* Handle total and average gross pay
*
         LA    1,OTGRPAY+14
         MVC   OTGRPAY(18),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OTGRPAY(18),PTGRPAY
         BCTR  1,0
         MVI   0(1),C'$'
*
         ZAP   PCALC(10),PTGRPAY(7)
         SRP   PCALC(10),3,0
         DP    PCALC(10),PEMPCTR(3)
         SRP   PCALC(7),64-1,5
         LA    1,OAGRPAY+14
         MVC   OAGRPAY(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OAGRPAY(19),PCALC
         BCTR  1,0
         MVI   0(1),C'$'
         XPRNT OTAGRPAY,133
*
* Handle total and average fed withholding
         LA    1,OTFWITH+14 
         MVC   OTFWITH(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OTFWITH(19),PTFWITH
         BCTR  1,0
         MVI   0(1),C'$'
*
         ZAP   PCALC(10),PTFWITH(7)
         SRP   PCALC(10),3,0
         DP    PCALC(10),PEMPCTR(3)
         SRP   PCALC(7),64-1,5
         LA    1,OAFWITH+14
         MVC   OAFWITH(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OAFWITH(19),PCALC
         BCTR  1,0
         MVI   0(1),C'$'
         XPRNT OFEDTOT,133
*
* Handle total and average state withholding
*
         LA    1,OTSWITH+14 
         MVC   OTSWITH(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OTSWITH(19),PTSWITH
         BCTR  1,0
         MVI   0(1),C'$'
*
         ZAP   PCALC(10),PTSWITH(7)
         SRP   PCALC(10),3,0
         DP    PCALC(10),PEMPCTR(3)
         SRP   PCALC(7),64-1,5
         LA    1,OASWITH+14
         MVC   OASWITH(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OASWITH(19),PCALC
         BCTR  1,0
         MVI   0(1),C'$'
         XPRNT OSTTOT,133
*
* Handle total and average net pay
*
         LA    1,OTNETPAY+14 
         MVC   OTNETPAY(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OTNETPAY(19),PTNETPAY
         BCTR  1,0
         MVI   0(1),C'$'
*
         ZAP   PCALC(10),PTNETPAY(7)
         SRP   PCALC(10),3,0
         DP    PCALC(10),PEMPCTR(3)
         SRP   PCALC(7),64-1,5
         LA    1,OANETPAY+14
         MVC   OANETPAY(19),=X'4020206B2020206B2020206B2021204B2020'
         EDMK  OANETPAY(19),PCALC
         BCTR  1,0
         MVI   0(1),C'$'
         XPRNT ONETTOT,133
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
         DS    CL68
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
* STORAGE FOR COMPANY NAME AND PAGE NUMBER
*
ONMEPAGE DC    C'1'
         DC    52C' '
         DC    C'CHICAGO SOFTWARE COMPANY, INC.'
         DC    40C' '
         DC    C'PAGE: '
OPAGENM  DC    4C' '
*
* STORAGE FOR TITLE
*
OTITLE   DC    C' '
         DC    54C' '
         DC    C'EMPLOYEE PAYROLL REPORT' 
         DC    55C' '
*
* Storage for column headers
*
OHEAD1   DC    C'0'
         DC    C'EMPLOYEE'
         DC    C'   '
         DC    C'EMPLOYEE'
         DC    C'                     '
         DC    C'HOURLY'
         DC    C'     '
         DC    C'HOURS'
         DC    C'            '
         DC    C'EMPLOYEE'
         DC    C'    '
         DC    C'EMPLOYEE FEDERAL'
         DC    C'    '
         DC    C'EMPLOYEE STATE'
         DC    C'          '
         DC    C'EMPLOYEE'
OHEAD2   DC    C' '
         DC    C'ID         '
         DC    C'NAME                            '
         DC    C'PAY    '
         DC    C'WORKED           '
         DC    C'GROSS PAY         '
         DC    C'WITHHOLDING       '
         DC    C'WITHHOLDING           '
         DC    C'NET PAY'
OHEAD3   DC    C' '
         DC    C'---------  '
         DC    C'-------------------------   '
         DC    C'-------   '
         DC    C'-------     '
         DC    C'---------------    '
         DC    C'----------------    '
         DC    C'--------------   '
         DC    C'---------------'
*
* Storage For TOTALS line
*
OTOTALS  DC    C' '
         DC    62C' '
         DC    C'TOTALS'
         DC    64C' '
*
* Storage for number of employees 
*
OEMPCTR  DC    CL1'0'
         DC    6C' '
         DC    CL21'NUMBER OF EMPLOYEES: '
         DC    9C' '
OTEMPCT  DS    CL6
         DC    90C' '
*
* Storage for total gross and average gross
*
OTAGRPAY DC    CL1'0'
         DC    10C' '
         DC    CL16'TOTAL GROSS PAY: '
         DC    C' '
OTGRPAY  DS    CL18
         DC    20C' '
         DC    CL19'AVERAGE GROSS PAY: '
OAGRPAY  DS    CL19
         DC    29C' '
*
* Storage for total fed withholding and average fed withholding
*
OFEDTOT  DC    C'0'
         DC    CL26'TOTAL FEDERAL WITHHOLDING: '
OTFWITH  DS    CL19
         DC    10C' '
         DC    CL29'AVERAGE FEDERAL WITHHOLDING: '
OAFWITH  DS    CL19
         DC    29C' '
*
* Storage for total state withholding and average state withholding
*
OSTTOT  DC    C'0'
        DC    2C' '
        DC    CL25'TOTAL STATE WITHHOLDING: '
OTSWITH DS    CL19
        DC    12C' '
        DC    CL26'AVERAGE STATE WITHHOLDING: '
OASWITH DS    CL19
        DC    29C' '
*
* Storage for total net and average net
*
ONETTOT  DC   C'0'
         DC   12C' '
         DC   CL15'TOTAL NET PAY: '
OTNETPAY DS   CL19
         DC   22C' '
         DC   CL17'AVERAGE NET PAY: '
OANETPAY DS   CL19
         DC   28C' '
*
* STORAGE FOR MAIN PRINT LINE
*
DETAIL   DC    C'0'
OEMPID   DS    CL10
         DC    C' '
OEMPNME  DS    29C' '
OHRPAY   DS    CL7
         DC    2C' '
OHOURS   DS    CL7
         DC    5C' '
OGRPAY   DS    CL15
         DC    5C' '
OFEDWITH DS    CL15
         DC    3C' '
OSTWITH  DS    CL15
         DC    3C' '
ONETPAY  DS    CL15
         END PAYROLL
/*
//*
//FT05F001 DD DSN=KC02322.CSCI360.DATAFA24(DATA8),DISP=SHR
//*
//FT06F001 DD SYSOUT=*
//
