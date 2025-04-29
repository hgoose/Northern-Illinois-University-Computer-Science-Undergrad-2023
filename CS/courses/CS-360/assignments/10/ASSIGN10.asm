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
* BC    B'0111',EMPTY            No data
         PACK  PFWHPCT(4),IFEDWITH(6)   Convert stwith to PD
         PACK  PSWHPCT(4),ISTWITH(6)    Convert Fedwith to PD
*
* CALL BUILDTBL
*
         LA    1,BTPARMS 
         L     15,=V(BUILDTBL)
         BALR  14,15
*
* CALL PROCTBL
*
         LA    1,PTPARMS
         L     15,=V(PROCTBL)
         BALR  14,15
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
*
BTPARMS  DC    A(EMPTBL)
         DC    A(PEMPCTR)
         DC    A(PFWHPCT)
         DC    A(PSWHPCT)
*
PTPARMS  DC    A(EMPTBL)
         DC    A(PEMPCTR)
         DC    A(PFWHPCT)
         DC    A(PSWHPCT)
*
CAPARMS  DC    A(PTOTAL)
         DC    A(PEMPCTR)
         DC    A(PAVG)
*
* BUILDTBL PROGRAM
*
$TEMPENT DSECT
$TEMPID  DS    PL5
$TEMPNME DS    CL25
$THRPAY  DS    PL3
$THOURS  DS    PL3
$TDEDUCT DS    PL3
$TBONUS  DS    PL3
*
BUILDTBL CSECT
*
* STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13) SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15 COPY CSECT ADDR INTO R12
         USING BUILDTBL,12 ESTABLISH R12 AS THE BASE REG
         LA    14,BTBLSAVE R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13) STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14) STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14 POINT R13 AT THIS CSECT'S SAVE AREA
*
* DEREFERENCE PARMS
*
         LM    2,4,0(1)
*
* BUILDTBL LOGIC
*
* Read loop to get data into table
*
         USING $TEMPENT,2               Adressability on DSECT
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
         LA    2,42(,4)                 Move ptr to next entry
*
         XREAD RECORD,80                Read and branch to condition
         BC    B'1111',TBLLOOP
*
ENDLOOP  DS    0H
*
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
         ORG BUILDTBL+((*-BUILDTBL+31)/32)*32
         DC C'* PROGRAM STORAGE FOR BUILDTBL **'
*
BTBLSAVE DS 18F REGISTER SAVE AREA
*
CNPPARMS DC     A(PEMPGPAY)
         DC     A(PFWHPCT)
         DC     A(PFEDWITH)
         DC     A(PSWHPCT)
*
* PROCTBL PROGRAM
*
PROCTBL  CSECT
*
* STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13) SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15 COPY CSECT ADDR INTO R12
         USING PROCTBL,12 ESTABLISH R12 AS THE BASE REG
         LA    14,PTBLSAVE R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13) STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14) STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14 POINT R13 AT THIS CSECT'S SAVE AREA
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
         ORG PROCTBL+((*-PROCTBL+31)/32)*32
         DC C'* PROGRAM STORAGE FOR PROCTBL **'
*
PTBLSAVE DS 18F REGISTER SAVE AREA
*
*
* CALCNPAY
*
CALCNPAY CSECT
*
* STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13) SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15 COPY CSECT ADDR INTO R12
         USING CALCNPAY,12 ESTABLISH R12 AS THE BASE REG
         LA    14,CNSAVE R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13) STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14) STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14 POINT R13 AT THIS CSECT'S SAVE AREA
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
         ORG CALCNPAY+((*-CALCNPAY+31)/32)*32
         DC C'* PROGRAM STORAGE FOR CALCNPAY **'
*
CNSAVE   DS 18F REGISTER SAVE AREA
*
*
* CALC AVG
*
CALCAVG CSECT
*
* STANDARD ENTRY LINKAGE WITH R12 AS BASE REGISTER
*
         STM   14,12,12(13) SAVE REGS IN CALLER'S SAVE AREA
         LR    12,15 COPY CSECT ADDR INTO R12
         USING CALCAVG,12 ESTABLISH R12 AS THE BASE REG
         LA    14,CASAVE R14 POINTS TO THIS CSECT'S SAVE AREA
         ST    14,8(,13) STORE ADDR OF THIS CSECT'S SAVE AREA
         ST    13,4(,14) STORE ADDR OF CALLER'S SAVE AREA
         LR    13,14 POINT R13 AT THIS CSECT'S SAVE AREA
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
         ORG CALCAVG+((*-CALCAVG+31)/32)*32
         DC C'* PROGRAM STORAGE FOR CALCAVG **'
*
CASAVE   DS 18F REGISTER SAVE AREA
*
         END PAYROLL
/*
//*
//FT05F001 DD DSN=KC02322.CSCI360.DATASP25(DATA10),DISP=SHR 
//*
//FT06F001 DD SYSOUT=*
//
