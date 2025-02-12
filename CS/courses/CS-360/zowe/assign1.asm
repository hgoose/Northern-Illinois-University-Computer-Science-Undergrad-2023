//KC03AEEA JOB ,'N. WARNER',MSGCLASS=H                                  00020001
//JSTEP01 EXEC PGM=ASSIST                                               00030001
//STEPLIB DD DSN=KC00NIU.ASSIST.LOADLIB,DISP=SHR                        00040001
//SYSPRINT DD SYSOUT=*                                                  00050001
//SYSIN DD *                                                            00060001
*****************************************************************       00070001
* *                                                                     00080001
* CSCI 360-1 ASSIGNMENT 1 SPRING 2025                                   00090001
* *                                                                     00100001
* PROGRAMMER NAME: Nate Warner                                          00110001
* DATE DUE: 1-24-2025                                                   00120001
* *                                                                     00130001
* MAIN PROGRAM NAME: MAIN                                               00140002
* *                                                                     00150001
* FUNCTION: The function of this program is to                          00160002
* provide an example of a simple ASSIST *                               00170001
* Assembler program and documentation. *                                00180001
* *                                                                     00190001
*****************************************************************       00200001
*                                                                       00210001
PROGRAM1 CSECT                                                          00220001
 USING PROGRAM1,15 ESTABLISH ADDRESSABILITY ON REG 15                   00230001
 LA 4,13 LOAD 13 INTO REG 4                                             00240001
 LA 8,6 LOAD 6 INTO REG 8                                               00250001
 AR 4,8 ADD REG 8'S CONTENTS TO REG 4'S                                 00260001
 XDUMP , DUMP CONTENTS OF ALL 16 REGS                                   00270001
 BCR B'1111',14 UNCONDITIONAL RETURN TO CALLER (OS)                     00280001
*                                                                       00290001
 LTORG LITERAL ORGANIZATION                                             00300001
*                                                                       00310001
 END PROGRAM1                                                           00320001
/*                                                                      00330001
//                                                                      00340001
