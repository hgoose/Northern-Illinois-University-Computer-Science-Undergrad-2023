//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
***************************************************************
* *                                                            *
* CSCI 360-1 ASSIGNMENT 9
* spring 2025                                                 
* *                                                           *
* PROGRAMMER NAME: Nate Warner
* DATE DUE: 4/25/25
* *                                                           *
* MAIN PROGRAM NAME: PAYROLL                                       
* *
* FUNCTION: An extension of programs 7,8 using tables
*           
*           
* *                                                           *
***************************************************************
*
$TEMPENT DSECT
$TEMPID  DS    PL5
$TEMPNME DS    CL25
$THRPAY  DS    PL3
$THOURS  DS    PL3
$TDEDUCT DS    PL3
$TBONUS  DS    PL3
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
* Estabilsh a second base register
*
         LA    11,4095(,12)
         LA    11,1(,11)
         USING PAYROLL+4096,11
*
* Preliminary XREAD to get fed and state withholding
*
         XREAD IFEDWITH,80              Get withholding percents
         BC    B'0111',EMPTY            No data
         PACK  PFWHPCT(4),IFEDWITH(6)   Convert stwith to PD
         PACK  PSWHPCT(4),ISTWITH(6)    Convert Fedwith to PD
*
* Read loop to get data into table
*
         LA    4,EMPTBL                 Pointer to table
         LA    5,0                      Count of entries
         LA    6,0                      Stays zero for CR
         USING $TEMPENT,4               Adressability on DSECT
         XREAD RECORD,80                Initial read
TBLLOOP  BC    B'0111',ENDLOOP          Condition check after read
*
         PACK  $TEMPID(5),IEMPID(8)     Convert EMPID to PD
         PACK  $THRPAY(3),IHRPAY(5)     Pack HRPAY into PD field
         PACK  $THOURS(3),IHOURS(5)     Pack hours into PD field
         PACK  $TDEDUCT(3),IDEDUCT(5)   Pack deduction amount
         PACK  $TBONUS(3),IBONUS(5)     Pack bonus amount
         MVC   $TEMPNME(25),IEMPNME     Move empnme to table
         AP    PEMPCTR(3),=PL1'1'       Increment emp count
         LA    5,1(,5)                  Increment entry count
         LA    4,42(,4)                 Move ptr to next entry
*
         XREAD RECORD,80                Read and branch to condition
         BC    B'1111',TBLLOOP
*
ENDLOOP  DS    0H
*
         LA    2,19                      Use R2 as line counter
         LA    3,19                      Use R3 to hold the key
*
* Loop through table and proc data
*
         LA    4,EMPTBL                  Pointer to table
LOOP2    CR    5,6                       Compare iter number
         BC    B'1000',ENDLOOP2          Branch if done
*
         MVI DETAIL+1,C' '               Reset detail line
         MVC DETAIL+2(131),DETAIL+1      Reset detail line
*
* Handle emp id
*
         MVC   OEMPID-1(10),=X'21202060202020202020' Created EP for ID
         ED    OEMPID-1(10),$TEMPID      Edit ID into print line 
         MVI   DETAIL,C'0'               Replace carriage control
*
* Handle hourly pay
*
         LA    1,OHRPAY+3                Safety mark for $
         MVC   OHRPAY(7),=X'402021204B2020' Construct EP for HRPAY
         EDMK  OHRPAY(7),$THRPAY         Edit and mark into printline
         BCTR  1,0                       Decrement R1 by one for $ pos
         MVI   0(1),C'$'                 Place $
*
* Handle Hours worked
*
         MVC   OHOURS(7),=X'402021204B2020' Construct EP for hours
         ED    OHOURS(7),$THOURS          Edit hours into print line
*
* Handle Name
*
         MVC   OEMPNME(25),$TEMPNME       Move empnme to output
*
* Handle Gross pay
*
         ZAP   PGRPAY(6),$THRPAY(3)      Zap hrpay into larger field
         MP    PGRPAY(6),$THOURS(3)      Multiply hrpay by hours
         SRP   PGRPAY(6),64-2,5          Shift right two and round
         SP    PGRPAY(6),$TDEDUCT(3)     Subtract deduction amount
         AP    PGRPAY(6),$TBONUS(3)      Add bonus amount
         LA    1,OGRPAY+11               Saftey mark for $
         MVC   OGRPAY(15),=X'402020206B2020206B2021204B2020' EP
         EDMK  OGRPAY(15),PGRPAY         Edit gross into printline
         BCTR  1,0                       Move R1 to $ position
         MVI   0(1),C'$'                 Place $
         AP    PTGRPAY(7),PGRPAY(6)      Add emp's gross to total
*
* Handle fed withholding amount
*
         ZAP   PCALC(10),PGRPAY(6)       Zap gross into larger field
         MP    PCALC(10),PFWHPCT(4)      Multiply gross by fed percent
         SRP   PCALC(10),64-5,5          Shift right 5 and round
         ZAP   PFEDWITH(6),PCALC(10)     Zap into result field
         LA    1,OFEDWITH+11             Saftey mark for $
         MVC   OFEDWITH(15),=X'402020206B2020206B2021204B2020' Make EP
         EDMK  OFEDWITH(15),PFEDWITH     Edit fedwith into print line
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
         AP    PTFWITH(7),PFEDWITH(6)    Add to total
*
* Handle State withholding amount
*
         ZAP   PCALC(10),PGRPAY(6)       Zap gross into larger field
         MP    PCALC(10),PSWHPCT(4)      Multiply gross by state pcnt
         SRP   PCALC(10),64-5,5          Shift right 5 and round
         ZAP   PSTWITH(6),PCALC(10)      Zap into result field
         LA    1,OSTWITH+11              Safety mark
         MVC   OSTWITH(15),=X'402020206B2020206B2021204B2020' Make EP
         EDMK  OSTWITH(15),PSTWITH       Edit into print line
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place 4
         AP    PTSWITH(7),PSTWITH(6)     Add to total
*
* Handle Net Pay
*
         ZAP   PNETPAY(6),PGRPAY(6)      Zap gross into result field
         SP    PNETPAY(6),PFEDWITH(6)    Subtract off fed withholding
         SP    PNETPAY(6),PSTWITH(6)     Subtract off state withholding
         LA    1,ONETPAY+11              Safety mark for $
         MVC   ONETPAY(15),=X'402020206B2020206B2021204B2020' Make EP
         EDMK  ONETPAY(15),PNETPAY       Edit into print line
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
*
         AP    PTNETPAY(7),PNETPAY(6)    Add to total
         CR    2,3                       Check if time for headers
         BC    B'0111',NOPRINT           Branch if not
         LA    2,0                       Reset line counter
         AP    PPAGECTR(2),=PL1'1'       Add one to page count
         MVC   OPAGENM(4),=X'40202120'   EP for current page no.
         ED    OPAGENM(4),PPAGECTR       Edit page number to PL 
*
         XPRNT ONMEPAGE,133              Print company name and page
         XPRNT OTITLE,133                Print title
         XPRNT OHEAD1,133                Print first header line
         XPRNT OHEAD2,133                Second header line
         XPRNT OHEAD3,133                Third header line
*
NOPRINT  DS    0H
*
         XPRNT DETAIL,133                Print the line
         LA    2,1(,2)                   Increase line count by one
*
* Decrement emp count and branch back to check
*
         BCTR  5,0                       Decrement iter tracker
         LA    4,42(,4)                  Move table ptr to next
         BC    B'1111',LOOP2             Branch
*
ENDLOOP2 DS    0H
*
* Print Totals page headers
         AP    PPAGECTR(2),=PL1'1'       Increase page count to final
         MVC   OPAGENM(4),=X'40202120'   Ep for final page count
         ED    OPAGENM(4),PPAGECTR       Edit page count to PL
         XPRNT ONMEPAGE,133              Print company name and page
         XPRNT OTITLE,133                Print title line
         XPRNT OTOTALS,133               Print totals line
*
* Handle total number of employees
*
         MVC   OTEMPCT(6),=X'402020202120' Ep for total emp count
         ED    OTEMPCT(6),PEMPCTR          Edit into printline
         XPRNT OEMPCTR,133                 Print total emp count
*
* Setup for averages
*
         SRP   PEMPCTR(3),2,0             Shift emp count for divide
*
* Handle total and average gross pay
*
         LA    1,OTGRPAY+14              Safety mark for $
         MVC   OTGRPAY(18),=X'4020206B2020206B2020206B2021204B2020' EP
         EDMK  OTGRPAY(18),PTGRPAY       Edit total gross to PL
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
*
         ZAP   PCALC(10),PTGRPAY(7)      Zap total gross to calc field
         SRP   PCALC(10),3,0             Add three fake decimal places
         DP    PCALC(10),PEMPCTR(3)     Divide total gross by emp count
         SRP   PCALC(7),64-1,5           Round to two decimal places
         LA    1,OAGRPAY+14              Safety mark for $
         MVC   OAGRPAY(19),=X'4020206B2020206B2020206B2021204B2020' EP
         EDMK  OAGRPAY(19),PCALC         Edit average gross into PL
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
         XPRNT OTAGRPAY,133              Print total and avg gross
*
* Handle total and average fed withholding
         LA    1,OTFWITH+14              Saftey mark for $
         MVC   OTFWITH(19),=X'4020206B2020206B2020206B2021204B2020' EP
         EDMK  OTFWITH(19),PTFWITH       Edit total fed withholding 
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
*
         ZAP   PCALC(10),PTFWITH(7)      Move total fedwith to calc fld
         SRP   PCALC(10),3,0             Add three fake decimal places
         DP    PCALC(10),PEMPCTR(3)      Divide total fedwith by emp ct
         SRP   PCALC(7),64-1,5           Round to two decimal places
         LA    1,OAFWITH+14              Safety mark
         MVC   OAFWITH(19),=X'4020206B2020206B2020206B2021204B2020' EP
         EDMK  OAFWITH(19),PCALC         Edit avg fed with to PL
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
         XPRNT OFEDTOT,133               Print total and avg fed with
*
* Handle total and average state withholding
*
         LA    1,OTSWITH+14              Safety mark
         MVC   OTSWITH(19),=X'4020206B2020206B2020206B2021204B2020' EP
         EDMK  OTSWITH(19),PTSWITH       Edit total st with to PL
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
*
         ZAP   PCALC(10),PTSWITH(7)      Zap total st with to calc fld
         SRP   PCALC(10),3,0             Add three fake decimal places
         DP    PCALC(10),PEMPCTR(3)      Divide total st with by emp ct
         SRP   PCALC(7),64-1,5           Round to two decimal places
         LA    1,OASWITH+14              Safety mark for $
         MVC   OASWITH(19),=X'4020206B2020206B2020206B2021204B2020' EP
         EDMK  OASWITH(19),PCALC         Edit avg st with to PL
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
         XPRNT OSTTOT,133                Print total and avg st with
*
* Handle total and average net pay
*
         LA    1,OTNETPAY+14             Saftey mark for $
         MVC   OTNETPAY(19),=X'4020206B2020206B2020206B2021204B2020' EP
         EDMK  OTNETPAY(19),PTNETPAY     Move total net pay to PL
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
*
         ZAP   PCALC(10),PTNETPAY(7)     Zap total net into calc field
         SRP   PCALC(10),3,0             Add three fake decimal places
         DP    PCALC(10),PEMPCTR(3)      Divide total net by emp count
         SRP   PCALC(7),64-1,5           Round to two decimal places
         LA    1,OANETPAY+14             Safety mark for $
         MVC   OANETPAY(19),=X'4020206B2020206B2020206B2021204B2020' EP
         EDMK  OANETPAY(19),PCALC        Edit avg net pay to PL
         BCTR  1,0                       Decrement R1
         MVI   0(1),C'$'                 Place $
         XPRNT ONETTOT,133               Print total and avg net pay
*
EMPTY    DS    0H            We branch here if input file is empty
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
* PROGRAM TABLE
*
EMPTBL   DS    120CL42
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
ONMEPAGE DC    CL1'1'
         DC    52C' '
         DC    CL30'CHICAGO SOFTWARE COMPANY, INC.'
         DC    40C' '
         DC    CL6'PAGE: '
OPAGENM  DC    4C' '
*
* STORAGE FOR TITLE
*
OTITLE   DC    CL1' '
         DC    54C' '
         DC    CL23'EMPLOYEE PAYROLL REPORT' 
         DC    55C' '
*
* Storage for column headers
*
OHEAD1   DC    CL1'0'
         DC    CL8'EMPLOYEE'
         DC    3C' '
         DC    CL8'EMPLOYEE'
         DC    21C' '
         DC    CL6'HOURLY'
         DC    5C' '
         DC    CL5'HOURS'
         DC    12C' '
         DC    CL8'EMPLOYEE'
         DC    4C' '
         DC    CL16'EMPLOYEE FEDERAL'
         DC    4C' '
         DC    C'EMPLOYEE STATE'
         DC    10C' '
         DC    CL8'EMPLOYEE'
*
OHEAD2   DC    C' '
         DC    CL2'ID'
         DC    9C' '
         DC    CL4'NAME'
         DC    28C' '
         DC    CL3'PAY'
         DC    4C' '
         DC    CL6'WORKED'
         DC    11C' '
         DC    CL9'GROSS PAY'
         DC    9C' '
         DC    CL11'WITHHOLDING'
         DC    7C' '
         DC    CL11'WITHHOLDING'
         DC    11C' '
         DC    CL7'NET PAY'
*
OHEAD3   DC    CL1' '
         DC    9C'-'
         DC    2C' '
         DC    25C'-'
         DC    3C' '
         DC    7C'-'
         DC    3C' '
         DC    7C'-'
         DC    5C' '
         DC    15C'-'
         DC    4C' '
         DC    16C'-'
         DC    4C' '
         DC    14C'-'
         DC    3C' '
         DC    15C'-'
*
* Storage For TOTALS line
*
OTOTALS  DC    CL1' '
         DC    62C' '
         DC    CL6'TOTALS'
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
         DC    CL1' '
OTGRPAY  DS    CL18
         DC    20C' '
         DC    CL19'AVERAGE GROSS PAY: '
OAGRPAY  DS    CL19
         DC    29C' '
*
* Storage for total fed withholding and average fed withholding
*
OFEDTOT  DC    CL1'0'
         DC    CL26'TOTAL FEDERAL WITHHOLDING: '
OTFWITH  DS    CL19
         DC    10C' '
         DC    CL29'AVERAGE FEDERAL WITHHOLDING: '
OAFWITH  DS    CL19
         DC    29C' '
*
* Storage for total state withholding and average state withholding
*
OSTTOT  DC    CL1'0'
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
ONETTOT  DC   CL1'0'
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
DETAIL   DC    CL1'0'
OEMPID   DS    CL10 
         DC    CL1' '
OEMPNME  DS    28C' '
OHRPAY   DS    CL7
         DC    3C' '
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
//FT05F001 DD DSN=KC02322.CSCI360.DATASP25(DATA9),DISP=SHR 
//*
//FT06F001 DD SYSOUT=*
//
