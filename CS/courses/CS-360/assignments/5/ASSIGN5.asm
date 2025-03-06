//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  
//JSTEP01 EXEC PGM=ASSIST                                               
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        
//SYSPRINT DD SYSOUT=*                                                  
//SYSIN DD *                                                            
***************************************************************
* *                                                           *
* CSCI 360-1 ASSIGNMENT 5
* spring 2025                                                 
* *                                                           *
* PROGRAMMER NAME: Nate Warner
* DATE DUE: March 7, 2025
* *                                                           *
* MAIN PROGRAM NAME:  PAYRPT                                      
* *
* FUNCTION: Calculates payroll for a business
* *                                                           *
***************************************************************
PAYRPT   CSECT
         USING PAYRPT,15      ESTABLISH ADDRESSABILITY ON REG 15
*                                  
         LA    10,16          GET FED WITHHOLDING PERCENT INTO R10
         LA    11,4           GET STATE WITHHOLDING PERCENT INTO R11
*
         XREAD RECORD,80      GET FIRST EMPLOYEE RECORD
*
LOOP     BC   B'0100',ENDLOOP BRANCH TO ENDLOOP1 IF END-OF-FILE (EOF)
*
* GRAB THE NAME AND ID
*
         MVC   OEMPNME(25),RECORD    Grab Empname
         MVC   OEMPID(5),RECORD+30   Grab EmpID
*
* GRAB PAY RATE, HOURS WORKED, DEDUCITION, BONUS
*
         XDECI 5,RECORD+36    Grab Hourly pay rate
         XDECO 5,OPAYRATE     XDECO pay rate into OPAYRATE
         XDECI 6,0(1)         Grab number of hours worked
         XDECO 6,OHOURS       XDECO number of hours into OHOURS
         XDECI 7,0(1)         Grab Deduction
         XDECI 8,0(1)         Grab bonus
*
* BEGIN GROSS CALCULATION
*
         MR    4,6            Multiply pay rate by hours worked
         SR    5,7            Subtract deduction from result above
         AR    5,8            Add bonus to result adove
         XDECO 5,OGROSS       Put gross in OGROSS
*
* FED AND STATE WITHHOLDING CALULATION SETUP
* 
         LR    9,5            Save state of R5 (gross) in R9
         LA    2,100(0)       Load 100 into R2
*
* FED WITHHOLDING CALCULATION 
*
         LR    7,10           Load FW percent into odd R7 
         MR    6,9            Multiply R7 by R9 (gross * FW percent)
         DR    6,2            Divide R7 by R2 (FW/100)
         XDECO 7,OFEDWH       XDECO fed withholding 
         SR    5,7            Subtract fed withoholding from gross
*
* STATE WITHHOLDING CALCULATION
*
         LR    7,11           Load SW into R7
         MR    6,9            Multiply R7 by R9 (gross * SW percent)
         DR    6,2            Divide R7 by R2 (above/100)
         XDECO 7,OSTWH        XDECO state withholding
         SR    5,7            Subtract Gross * SW/100 From gross
         XDECO 5,ONETPAY      Store net in ONETPAY
*
         XPRNT DETAIL,133     PRINT THE EMPLOYEE DETAIL RECORD
*
         XREAD RECORD,80      READ NEXT EMPLOYEE RECORD
*
         BC    B'1111',LOOP   BRANCH TO TOP OF LOOP1 TO CHECK EOF
*
ENDLOOP  DS    0H    
*
         BCR   B'1111',14     UNCONDITIONAL RETURN TO CALLER
*
         LTORG                LITERAL ORGANIZATION
*
* THE FOLLOWING 16 LINES ARE THE DEFINITION FOR THE OUTPUT DETAIL
*   LINE FOR EACH EMPLOYEE FOR THE REPORT YOU ARE CREATING.  IT 
*   IS EXACTLY 133 BYTES LONG.  EACH OUTPUT FIELD IS SEPARATED 
*   BY 4 OR 5 BYTES OF EBCDIC SPACES, i.e., X'40'.
*
DETAIL   DC    C'0'   CARRIAGE CONTROL CHARACTER
OEMPID   DS    CL5    OUTPUT FIELD FOR EMPLOYEE ID
         DC    4C' '  SPACES
OEMPNME  DS    CL25   OUTPUT FIELD FOR EMPLOYEE NAME
         DC    4C' '  SPACES
OPAYRATE DS    CL12   OUTPUT FIELD FOR XDECO OF PAY RATE
         DC    4C' '  SPACES
OHOURS   DS    CL12   OUTPUT FIELD FOR XDECO OF HOURS WORKED
         DC    4C' '  SPACES
OGROSS   DS    CL12   OUTPUT FIELD FOR XDECO OF GROSS PAY AMT
         DC    4C' '  SPACES
OFEDWH   DS    CL12   OUTPUT FIELD FOR XDECO OF FEDERAL WH AMT
         DC    5C' '  SPACES
OSTWH    DS    CL12   OUTPUT FIELD FOR XDECO OF STATE WH AMT
         DC    5C' '  SPACES
ONETPAY  DS    CL12   OUTPUT FIELD FOR XDECO OF NET PAY AMT
*
*  THE FOLLOWING IS THE BUFFER FOR THE INPUT RECORD
*
RECORD   DS    CL80   BUFFER FOR EMPLOYEE RECORD READ FROM INPUT FILE
*
         END   PAYRPT
/*
//*
//* THE FOLLOWING IS THE INPUT DATA SET
//*
//FT05F001 DD DSN=KC02322.CSCI360.DATAFA24(DATA5),DISP=SHR
//*
//* THE FOLLOWING IS THE OUTPUT DATA SET
//*
//FT06F001 DD SYSOUT=*
//*
//SYSPRINT DD SYSOUT=*
//*
//
