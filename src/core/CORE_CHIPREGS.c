/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../core/CORE_CHIPREGS.h"

//-----------------------------------------------------------------------------
// (10XXh) Shared Memory Flash Interface Bridge (SMFI)
//-----------------------------------------------------------------------------
ECReg   FBCFG           ;    // FBIU Configuration
ECReg   FPCFG           ;    // Flash Programming Configuration
ECReg   FECBSR          ;    // Flash EC Code Banking Select
ECReg   FMSSR           ;    // Flash Memory Size Select
ECReg   SMECCS          ;    // Shared Memory EC Control and Status
ECReg   SMHSR           ;    // Shared Memory Host Semaphore
ECReg   FLHCTRL1R       ;    // Flash Control   1
ECReg   FLHCTRL2R       ;    // Flash Control   2
ECReg   DCache          ;    // 256 bytes cache
ECReg   UCCTRLR         ;    // uC Control
ECReg   HCTRL2R         ;    // Host Control 2
ECReg   HSPICTRL2R      ;    // HSPI Control 2
ECReg   HSPICTRL3R      ;    // HSPI
ECReg   ECINDAR0        ;    // EC-Indirect Memory Address   0
ECReg   ECINDAR1        ;    // EC-Indirect Memory Address   1
ECReg   ECINDAR2        ;    // EC-Indirect Memory Address   2
ECReg   ECINDAR3        ;    // EC-Indirect Memory Address   3
ECReg   ECINDDR         ;    // EC-Indirect Memory Data
ECReg   SCRA0L          ;    // Scratch SRAM 0 Address Low Byte
ECReg   SCRA0M          ;    // Scratch SRAM 0 Address Middle Byte
ECReg   SCRA0H          ;    // Scratch SRAM 0 Address High Byte

#if !ITE_CHIP_IT557X   //0: IT557x No DMA1~4
ECReg   SCRA1L          ;    // Scratch SRAM 1 Address Low Byte
ECReg   SCRA1M          ;    // Scratch SRAM 1 Address Middle Byte
ECReg   SCRA1H          ;    // Scratch SRAM 1 Address High Byte
ECReg   SCRA2L          ;    // Scratch SRAM 2 Address Low Byte
ECReg   SCRA2M          ;    // Scratch SRAM 2 Address Middle Byte
ECReg   SCRA2H          ;    // Scratch SRAM 2 Address High Byte
ECReg   SCRA3L          ;    // Scratch SRAM 3 Address Low Byte
ECReg   SCRA3M          ;    // Scratch SRAM 3 Address Middle Byte
ECReg   SCRA3H          ;    // Scratch SRAM 3 Address High Byte
ECReg   SCRA4L          ;    // Scratch SRAM 4 Address Low Byte
ECReg   SCRA4M          ;    // Scratch SRAM 4 Address Middle Byte
ECReg   SCRA4H          ;    // Scratch SRAM 4 Address High Byte
#endif  //ITE_CHIP_IT557X

ECReg   P0BA0R          ;    // Protect 0 Base Addr   0
ECReg   P0BA1R          ;    // Protect 0 Base Addr   1
ECReg   P0ZR            ;    // Protect 0 Size
ECReg   P1BA0R          ;    // Protect 1 Base Addr   0
ECReg   P1BA1R          ;    // Protect 1 Base Addr   1
ECReg   P1ZR            ;    // Protect 1 Size
ECReg   DSINST          ;    // Deferred SPI Instruction
ECReg   DSADR1          ;    // Deferred SPI Address
ECReg   DSADR2          ;    // Deferred SPI Address
ECReg   HINSTC1         ;    // Host Instruction Control 1
ECReg   HINSTC2         ;    // Host Instruction Control 2
ECReg   HRAMWC          ;    // Host RAM Window Control
ECReg   HRAMW0BA        ;    // Host RAM Window 0 Base Address
ECReg   HRAMW1BA        ;    // Host RAM Window 1 Base Address
ECReg   HRAMW0AAS       ;    // Host RAM Window 0 Access Allow Size
ECReg   HRAMW1AAS       ;    // Host RAM Window 1 Access Allow Size
ECReg   SCAR5H          ;
ECReg   REG_1060        ;
ECReg   FLHCTRL3R       ;    // Flash Control 3
ECReg   FLHCTRL4R       ;    // Flash Control 4
ECReg   HSPICTRL        ;    // HSPI Control Register 4
ECReg   P2BA0R          ;    // Protect 2 Base Addr Register 0
ECReg   P2BA1R          ;    // Protect 2 Base Addr Register 1
ECReg   P2ZR            ;    // Protect 2 Size
ECReg   P3BA0R          ;    // Protect 3 Base Addr Register 0
ECReg   P3BA1R          ;    // Protect 3 Base Addr Register 1
ECReg   P3ZR            ;    // Protect 3 Size
ECReg   HRAMW2BA        ;    // Host RAM Windows 2 Base Address
ECReg   HRAMW3BA        ;    // Host RAM Windows 3 Base Address
ECReg   HRAMW2AAS       ;    // Host RAM Windows 2 Access Allow Size
ECReg   HRAMW3AAS       ;    // Host RAM Windows 3 Access Allow Size
ECReg   H2RAMECSIE      ;    // H2RAM EC Semaphore Interrupt Enable
ECReg   H2RAMECSA       ;    // H2RAM EC Semaphore Address
ECReg   H2RAMHSS        ;    // H2RAM Host Semaphore Status
ECReg   HPADR           ;    // Host Protect Authentication Data
ECReg   FLHCTRL5R       ;    // Flash Control 5
ECReg   FLHCTRL6R       ;    // Flash Control 6

ECReg   SCARSL          ;    // Scratch SRAM SMBus Address Low
ECReg   SCARSM          ;    // Scratch SRAM SMBus Address Middle
ECReg   SCARSH          ;    // Scratch SRAM SMBus Address High
ECReg   REG_10A2        ;

//-----------------------------------------------------------------------------
// (11xxh) Interrupt controller (INTC)
//-----------------------------------------------------------------------------
ECReg   ISR0            ;    // Interrupt Status 0
ECReg   ISR1            ;    // Interrupt Status 1
ECReg   ISR2            ;    // Interrupt Status 2
ECReg   ISR3            ;    // Interrupt Status 3
ECReg   ISR4            ;    // Interrupt Status 4
ECReg   ISR5            ;    // Interrupt Status 5
ECReg   ISR6            ;    // Interrupt Status 6
ECReg   ISR7            ;    // Interrupt Status 7
ECReg   ISR8            ;    // Interrupt Status 8
ECReg   ISR9            ;    // Interrupt Status 9
ECReg   ISR10           ;    // Interrupt Status 10
ECReg   ISR11           ;    // Interrupt Status 11
ECReg   ISR12           ;    // Interrupt Status 12
ECReg   ISR13           ;    // Interrupt Status 13
ECReg   ISR14           ;    // Interrupt Status 14
ECReg   ISR15           ;    // Interrupt Status 15
ECReg   ISR16           ;    // Interrupt Status 16
ECReg   ISR17           ;    // Interrupt Status 17
ECReg   ISR18           ;    // Interrupt Status 18
ECReg   ISR19           ;    // Interrupt Status 19
ECReg   ISR20           ;    // Interrupt Status 20
ECReg   ISR21           ;    // Interrupt Status 21

ECReg   IER0            ;    // Interrupt Enable 0
ECReg   IER1            ;    // Interrupt Enable 1
ECReg   IER2            ;    // Interrupt Enable 2
ECReg   IER3            ;    // Interrupt Enable 3
ECReg   IER4            ;    // Interrupt Enable 4
ECReg   IER5            ;    // Interrupt Enable 5
ECReg   IER6            ;    // Interrupt Enable 6
ECReg   IER7            ;    // Interrupt Enable 7
ECReg   IER8            ;    // Interrupt Enable 8
ECReg   IER9            ;    // Interrupt Enable 9
ECReg   IER10           ;    // Interrupt Enable 10
ECReg   IER11           ;    // Interrupt Enable 11
ECReg   IER12           ;    // Interrupt Enable 12
ECReg   IER13           ;    // Interrupt Enable 13
ECReg   IER14           ;    // Interrupt Enable 14
ECReg   IER15           ;    // Interrupt Enable 15
ECReg   IER16           ;    // Interrupt Enable 16
ECReg   IER17           ;    // Interrupt Enable 17
ECReg   IER18           ;    // Interrupt Enable 18
ECReg   IER19           ;    // Interrupt Enable 19
ECReg   IER20           ;    // Interrupt Enable 20
ECReg   IER21           ;    // Interrupt Enable 21

ECReg   IELMR0          ;    // Interrupt Edge/Level-Triggered Mode 0
ECReg   IELMR1          ;    // Interrupt Edge/Level-Triggered Mode 1
ECReg   IELMR2          ;    // Interrupt Edge/Level-Triggered Mode 2
ECReg   IELMR3          ;    // Interrupt Edge/Level-Triggered Mode 3
ECReg   IELMR4          ;    // Interrupt Edge/Level-Triggered Mode 4
ECReg   IELMR5          ;    // Interrupt Edge/Level-Triggered Mode 5
ECReg   IELMR6          ;    // Interrupt Edge/Level-Triggered Mode 6
ECReg   IELMR7          ;    // Interrupt Edge/Level-Triggered Mode 7
ECReg   IELMR8          ;    // Interrupt Edge/Level-Triggered Mode 8
ECReg   IELMR9          ;    // Interrupt Edge/Level-Triggered Mode 9
ECReg   IELMR10         ;    // Interrupt Edge/Level-Triggered Mode 10
ECReg   IELMR11         ;    // Interrupt Edge/Level-Triggered Mode 11
ECReg   IELMR12         ;    // Interrupt Edge/Level-Triggered Mode 12
ECReg   IELMR13         ;    // Interrupt Edge/Level-Triggered Mode 13
ECReg   IELMR14         ;    // Interrupt Edge/Level-Triggered Mode 14
ECReg   IELMR15         ;    // Interrupt Edge/Level-Triggered Mode 15
ECReg   IELMR16         ;    // Interrupt Edge/Level-Triggered Mode 16
ECReg   IELMR17         ;    // Interrupt Edge/Level-Triggered Mode 17
ECReg   IELMR18         ;    // Interrupt Edge/Level-Triggered Mode 18
ECReg   IELMR19         ;    // Interrupt Edge/Level-Triggered Mode 19
ECReg   IELMR20         ;    // Interrupt Edge/Level-Triggered Mode 20
ECReg   IELMR21         ;    // Interrupt Edge/Level-Triggered Mode 21

ECReg   IPOLR0          ;    // Interrupt Polarity 0
ECReg   IPOLR1          ;    // Interrupt Polarity 1
ECReg   IPOLR2          ;    // Interrupt Polarity 2
ECReg   IPOLR3          ;    // Interrupt Polarity 3
ECReg   IPOLR4          ;    // Interrupt Polarity 4
ECReg   IPOLR5          ;    // Interrupt Polarity 5
ECReg   IPOLR6          ;    // Interrupt Polarity 6
ECReg   IPOLR7          ;    // Interrupt Polarity 7
ECReg   IPOLR8          ;    // Interrupt Polarity 8
ECReg   IPOLR9          ;    // Interrupt Polarity 9
ECReg   IPOLR10         ;    // Interrupt Polarity 10
ECReg   IPOLR11         ;    // Interrupt Polarity 11
ECReg   IPOLR12         ;    // Interrupt Polarity 12
ECReg   IPOLR13         ;    // Interrupt Polarity 13
ECReg   IPOLR14         ;    // Interrupt Polarity 14
ECReg   IPOLR15         ;    // Interrupt Polarity 15
ECReg   IPOLR16         ;    // Interrupt Polarity 16
ECReg   IPOLR17         ;    // Interrupt Polarity 17
ECReg   IPOLR18         ;    // Interrupt Polarity 18
ECReg   IPOLR19         ;    // Interrupt Polarity 19
ECReg   IPOLR20         ;    // Interrupt Polarity 20
ECReg   IPOLR21         ;    // Interrupt Polarity 21

ECReg   IVECT           ;    // Interrupt Vector
ECReg   INT0ST          ;    // INT0# status
ECReg   PFAILR          ;    // Power Fail

//-----------------------------------------------------------------------------
// (12xxh) EC Access to ost Controlled Modules (EC2I Bridge)
//-----------------------------------------------------------------------------
ECReg   IHIOA           ;    // Indirect Host I/O Address
ECReg   IHD             ;    // Indirect Host Data
ECReg   LSIOHA          ;    // Lock Super I/O Host Access
ECReg   SIOLV           ;    // Super I/O Access Lock Violation
ECReg   IBMAE           ;    // EC to I-Bus Modules Access Enable
ECReg   IBCTL           ;    // I-Bus Control

//-----------------------------------------------------------------------------
// (13xxh) Keyboard Controller (KBC)
//-----------------------------------------------------------------------------
ECReg   KBHICR          ;    // KBC Host Interface Control
ECReg   KBIRQR          ;    // KBC Interrupt Control
ECReg   KBHISR          ;    // KBC Host Interface Keyboard/Mouse Status
ECReg   KBHIKDOR        ;    // KBC Host Interface Keyboard Data Output
ECReg   KBHIMDOR        ;    // KBC Host Interface Mouse Data Output
ECReg   KBHIDIR         ;    // KBC Host Interface Keyboard/Mouse Data Input

//-----------------------------------------------------------------------------
// (14xxh) System Wake-Up Control (SWUC)
//-----------------------------------------------------------------------------
ECReg   SWCTL1          ;    // SWUC Control Status 1
ECReg   SWCTL2          ;    // SWUC Control Status 2
ECReg   SWCTL3          ;    // SWUC Control Status 3
ECReg   SWCBALR         ;    // SWUC Host Configuration Base Address Low Byte
ECReg   SWCBAHR         ;    // SWUC Host Configuration Base Address High Byte
ECReg   SWCIER          ;    // SWUC Interrupt Enable
ECReg   SWCHSTR         ;    // SWUC Host Event Status
ECReg   SWCHIER         ;    // SWUC Host Event Interrupt Enable

//-----------------------------------------------------------------------------
// (15xxh) Power Management Channel (PMC)
//-----------------------------------------------------------------------------
ECReg   PM1STS          ;    // Host Interface PM Channel 1 Status
ECReg   PM1DO           ;    // Host Interface PM Channel 1 Data Out Port
ECReg   PM1DOSCI        ;    // Host Interface PM Channel 1 Data Out Port with SCI
ECReg   PM1DOSMI        ;    // Host Interface PM Channel 1 Data Out Port with SMI
ECReg   PM1DI           ;    // Host Interface PM Channel 1 Data In Port
ECReg   PM1DISCI        ;    // Host Interface PM Channel 1 Data In Port with SCI
ECReg   PM1CTL          ;    // Host Interface PM Channel 1 Control
ECReg   PM1IC           ;    // Host Interface PM Channel 1 Interrupt Control
ECReg   PM1IE           ;    // Host Interface PM Channel 1 Interrupt Enable

ECReg   PM2STS          ;    // Host Interface PM Channel 2 Status
ECReg   PM2DO           ;    // Host Interface PM Channel 2 Data Out Port
ECReg   PM2DOSCI        ;    // Host Interface PM Channel 2 Data Out Port with SCI
ECReg   PM2DOSMI        ;    // Host Interface PM Channel 2 Data Out Port with SMI
ECReg   PM2DI           ;    // Host Interface PM Channel 2 Data In Port
ECReg   PM2DISCI        ;    // Host Interface PM Channel 2 Data In Port with SCI
ECReg   PM2CTL          ;    // Host Interface PM Channel 2 Control
ECReg   PM2IC           ;    // Host Interface PM Channel 2 Interrupt Control
ECReg   PM2IE           ;    // Host Interface PM Channel 2 Interrupt Enable

ECReg   MBXCTRL         ;    // Mailbox Control

ECReg   PM3STS          ;    // Host Interface PM Channel 3 Status
ECReg   PM3DO           ;    // Host Interface PM Channel 3 Data Out Port
ECReg   PM3DI           ;    // Host Interface PM Channel 3 Data In Port
ECReg   PM3CTL          ;    // Host Interface PM Channel 3 Control
ECReg   PM3IC           ;    // Host Interface PM Channel 3 Interrupt Control
ECReg   PM3IE           ;    // Host Interface PM Channel 3 Interrupt Enable

ECReg   PM4STS          ;    // Host Interface PM Channel 4 Status
ECReg   PM4DO           ;    // Host Interface PM Channel 4 Data Out Port
ECReg   PM4DI           ;    // Host Interface PM Channel 4 Data In Port
ECReg   PM4CTL          ;    // Host Interface PM Channel 4 Control
ECReg   PM4IC           ;    // Host Interface PM Channel 4 Interrupt Control
ECReg   PM4IE           ;    // Host Interface PM Channel 4 Interrupt Enable

ECReg   PM5STS          ;    // Host Interface PM Channel 5 Status
ECReg   PM5DO           ;    // Host Interface PM Channel 5 Data Out Port
ECReg   PM5DI           ;    // Host Interface PM Channel 5 Data In Port
ECReg   PM5CTL          ;    // Host Interface PM Channel 5 Control
ECReg   PM5IC           ;    // Host Interface PM Channel 5 Interrupt Control
ECReg   PM5IE           ;    // Host Interface PM Channel 5 Interrupt Enable

ECReg   MBXEC[16]       ;    // 16-byte PMC2EX Mailbox 0 ~ Mailbox 15

//-----------------------------------------------------------------------------
// (16XXh) General Purpose I/O Control
//-----------------------------------------------------------------------------
ECReg   GCR             ;    // General Control

ECReg   GCR1            ;    // General Control 1
ECReg   GCR2            ;    // General Control 2
ECReg   GCR3            ;    // General Control 3
ECReg   GCR4            ;    // General Control 4
ECReg   GCR5            ;    // General Control 5
ECReg   GCR6            ;    // General Control 6
ECReg   GCR7            ;    // General Control 7
ECReg   GCR8            ;    // General Control 8
ECReg   GCR9            ;    // General Control 9
ECReg   GCR10           ;    // General Control 10
ECReg   GCR11           ;    // General Control 11
ECReg   GCR12           ;    // General Control 12
ECReg   GCR13           ;    // General Control 13
ECReg   GCR14           ;    // General Control 14
ECReg   GCR15           ;    // General Control 15
ECReg   PGWCR           ;    // Power Good Watch Control Register

ECReg   GCR16           ;    // General Control 16
ECReg   GCR17           ;    // General Control 17
ECReg   GCR18           ;    // General Control 18
ECReg   GCR19           ;    // General Control 19
ECReg   GCR20           ;    // General Control 20
ECReg   GCR21           ;    // General Control 21
ECReg   GCR22           ;    // General Control 22
ECReg   GCR23           ;    // General Control 23

ECReg   GCR24           ;    // General Control 24
ECReg   GCR25           ;    // General Control 25

ECReg   GPDRA           ;    // Port A Data
ECReg   GPDRB           ;    // Port B Data
ECReg   GPDRC           ;    // Port C Data
ECReg   GPDRD           ;    // Port D Data
ECReg   GPDRE           ;    // Port E Data
ECReg   GPDRF           ;    // Port F Data
ECReg   GPDRG           ;    // Port G Data
ECReg   GPDRH           ;    // Port H Data
ECReg   GPDRI           ;    // Port I Data
ECReg   GPDRJ           ;    // Port J Data
ECReg   GPDRM           ;    // Port M Data

ECReg   GPCRA0          ;    // Port Control A0
ECReg   GPCRA1          ;    // Port Control A1
ECReg   GPCRA2          ;    // Port Control A2
ECReg   GPCRA3          ;    // Port Control A3
ECReg   GPCRA4          ;    // Port Control A4
ECReg   GPCRA5          ;    // Port Control A5
ECReg   GPCRA6          ;    // Port Control A6
ECReg   GPCRA7          ;    // Port Control A7

ECReg   GPCRB0          ;    // Port Control B0
ECReg   GPCRB1          ;    // Port Control B1
ECReg   GPCRB2          ;    // Port Control B2
ECReg   GPCRB3          ;    // Port Control B3
ECReg   GPCRB4          ;    // Port Control B4
ECReg   GPCRB5          ;    // Port Control B5
ECReg   GPCRB6          ;    // Port Control B6
ECReg   GPCRB7          ;    // Port Control B7

ECReg   GPCRC0          ;    // Port Control C0
ECReg   GPCRC1          ;    // Port Control C1
ECReg   GPCRC2          ;    // Port Control C2
ECReg   GPCRC3          ;    // Port Control C3
ECReg   GPCRC4          ;    // Port Control C4
ECReg   GPCRC5          ;    // Port Control C5
ECReg   GPCRC6          ;    // Port Control C6
ECReg   GPCRC7          ;    // Port Control C7

ECReg   GPCRD0          ;    // Port Control D0
ECReg   GPCRD1          ;    // Port Control D1
ECReg   GPCRD2          ;    // Port Control D2
ECReg   GPCRD3          ;    // Port Control D3
ECReg   GPCRD4          ;    // Port Control D4
ECReg   GPCRD5          ;    // Port Control D5
ECReg   GPCRD6          ;    // Port Control D6
ECReg   GPCRD7          ;    // Port Control D7

ECReg   GPCRE0          ;    // Port Control E0
ECReg   GPCRE1          ;    // Port Control E1
ECReg   GPCRE2          ;    // Port Control E2
ECReg   GPCRE3          ;    // Port Control E3
ECReg   GPCRE4          ;    // Port Control E4
ECReg   GPCRE5          ;    // Port Control E5
ECReg   GPCRE6          ;    // Port Control E6
ECReg   GPCRE7          ;    // Port Control E7

ECReg   GPCRF0          ;    // Port Control F0
ECReg   GPCRF1          ;    // Port Control F1
ECReg   GPCRF2          ;    // Port Control F2
ECReg   GPCRF3          ;    // Port Control F3
ECReg   GPCRF4          ;    // Port Control F4
ECReg   GPCRF5          ;    // Port Control F5
ECReg   GPCRF6          ;    // Port Control F6
ECReg   GPCRF7          ;    // Port Control F7

ECReg   GPCRG0          ;    // Port Control G0
ECReg   GPCRG1          ;    // Port Control G1
ECReg   GPCRG2          ;    // Port Control G2
ECReg   GPCRG3          ;    // Port Control G3
ECReg   GPCRG4          ;    // Port Control G4
ECReg   GPCRG5          ;    // Port Control G5
ECReg   GPCRG6          ;    // Port Control G6
ECReg   GPCRG7          ;    // Port Control G7

ECReg   GPCRH0          ;    // Port Control H0
ECReg   GPCRH1          ;    // Port Control H1
ECReg   GPCRH2          ;    // Port Control H2
ECReg   GPCRH3          ;    // Port Control H3
ECReg   GPCRH4          ;    // Port Control H4
ECReg   GPCRH5          ;    // Port Control H5
ECReg   GPCRH6          ;    // Port Control H6
ECReg   GPCRH7          ;    // Port Control H7

ECReg   GPCRI0          ;    // Port Control I0
ECReg   GPCRI1          ;    // Port Control I1
ECReg   GPCRI2          ;    // Port Control I2
ECReg   GPCRI3          ;    // Port Control I3
ECReg   GPCRI4          ;    // Port Control I4
ECReg   GPCRI5          ;    // Port Control I5
ECReg   GPCRI6          ;    // Port Control I6
ECReg   GPCRI7          ;    // Port Control I7

ECReg   GPCRJ0          ;    // Port Control J0
ECReg   GPCRJ1          ;    // Port Control J1
ECReg   GPCRJ2          ;    // Port Control J2
ECReg   GPCRJ3          ;    // Port Control J3
ECReg   GPCRJ4          ;    // Port Control J4
ECReg   GPCRJ5          ;    // Port Control J5
ECReg   GPCRJ6          ;    // Port Control J6
ECReg   GPCRJ7          ;    // Port Control J7

ECReg   GPCRM0          ;    // Port Control M0
ECReg   GPCRM1          ;    // Port Control M1
ECReg   GPCRM2          ;    // Port Control M2
ECReg   GPCRM3          ;    // Port Control M3
ECReg   GPCRM4          ;    // Port Control M4
ECReg   GPCRM5          ;    // Port Control M5
ECReg   GPCRM6          ;    // Port Control M6

ECReg   GPDMRA          ;    // Port A Data Mirror
ECReg   GPDMRB          ;    // Port B Data Mirror
ECReg   GPDMRC          ;    // Port C Data Mirror
ECReg   GPDMRD          ;    // Port D Data Mirror
ECReg   GPDMRE          ;    // Port E Data Mirror
ECReg   GPDMRF          ;    // Port F Data Mirror
ECReg   GPDMRG          ;    // Port G Data Mirror
ECReg   GPDMRH          ;    // Port H Data Mirror
ECReg   GPDMRI          ;    // Port I Data Mirror
ECReg   GPDMRJ          ;    // Port J Data Mirror
ECReg   GPDMRM          ;    // Port M Data Mirror

ECReg   GPOTA           ;    // Output Type
ECReg   GPOTB           ;    // Output Type
ECReg   GPOTD           ;    // Output Type
ECReg   GPOTE           ;    // Output Type
ECReg   GPOTF           ;    // Output Type
ECReg   GPOTH           ;    // Output Type
ECReg   GPOTJ           ;    // Output Type

//-----------------------------------------------------------------------------
// (17XXh) PS/2 Interface
//-----------------------------------------------------------------------------
ECReg   PSCTL1          ;    // PS/2 Control 1
ECReg   PSCTL2          ;    // PS/2 Control 2
ECReg   PSCTL3          ;    // PS/2 Control 3
ECReg   PSINT1          ;    // PS/2 Interrupt Control 1
ECReg   PSINT2          ;    // PS/2 Interrupt Control 2
ECReg   PSINT3          ;    // PS/2 Interrupt Control 3
ECReg   PSSTS1          ;    // PS/2 Status 1
ECReg   PSSTS2          ;    // PS/2 Status 2
ECReg   PSSTS3          ;    // PS/2 Status 3
ECReg   PSDAT1          ;    // PS/2 Data 1
ECReg   PSDAT2          ;    // PS/2 Data 2
ECReg   PSDAT3          ;    // PS/2 Data 3

//-----------------------------------------------------------------------------
// (18xxh) PWM & SmartAuto Fan Control (PWM)
//-----------------------------------------------------------------------------
ECReg   C0CPRS          ;    // Channel 0 Clock Pre-Scaler
ECReg   CTR0            ;    // Cycle Time 0
ECReg   DCR0            ;    // Channel 0 PWM Duty Cycle
ECReg   DCR1            ;    // Channel 0 PWM Duty Cycle
ECReg   DCR2            ;    // Channel 0 PWM Duty Cycle
ECReg   DCR3            ;    // Channel 0 PWM Duty Cycle
ECReg   DCR4            ;    // Channel 0 PWM Duty Cycle
ECReg   DCR5            ;    // Channel 0 PWM Duty Cycle
ECReg   DCR6            ;    // Channel 0 PWM Duty Cycle
ECReg   DCR7            ;    // Channel 0 PWM Duty Cycle
ECReg   PWMPOL          ;    // PWM Polarity
ECReg   PCFSR           ;    // Prescaler Clock Frequency Select
ECReg   PCSSGL          ;    // Prescaler Clock Source Select Group Low
ECReg   PCSSGH          ;    // Prescaler Clock Source Select Group High
ECReg   CR256PCSSG      ;    // CR256 Prescaler Clock Source Select Group
ECReg   PCSGR           ;    // Prescaler Clock Source Gating
ECReg   F1TLRR          ;    // Fan 1 Tachometer LSB Reading
ECReg   F1TMRR          ;    // Fan 1 Tachometer MSB Reading
ECReg   F2TLRR          ;    // Fan 2 Tachometer LSB Reading
ECReg   F2TMRR          ;    // Fan 2 Tachometer MSB Reading
ECReg   ZINTSCR         ;    // Zone Interrupt Status Control
ECReg   ZTIER           ;    // PWM Clock Control
ECReg   TSWCTLR         ;    // Tachometer Switch Control
ECReg   C4CPRS          ;    // Channel 4 Clock Prescaler
ECReg   C4MCPRS         ;    // Channel 4 Clock Prescaler MSB
ECReg   C6CPRS          ;    // Channel 6 Clock Prescaler
ECReg   C6MCPRS         ;    // Channel 6 Clock Prescaler MSB
ECReg   C7CPRS          ;    // Channel 7 Clock Prescaler
ECReg   C7MCPRS         ;    // Channel 7 Clock Prescaler MSB
ECReg   CLK6MSEL        ;    // PWM Clock 6MHz Select
ECReg   CTR1            ;    // Cycle Time 1
ECReg   CTR2            ;    // Cycle Time 2
ECReg   CTR3            ;    // Cycle Time 3
ECReg   PWM5TOCTRL      ;    // PWM5 Timeout Control
ECReg   F3TLRR          ;    // Fan 3 Tachometer LSB Reading
ECReg   F3TMRR          ;    // Fan 3 Tachometer MSB Reading

ECReg   ZINTSCR2        ;    // Zone Interrupt Status Control Register 2

ECReg   TSWCTRL         ;    // Tachometer Switch Control
ECReg   PWMODENR        ;    // PWM Output Open-Drain Enable

ECReg   BLDR            ;    // Backlight Duty Register
ECReg   TSWCTLR2        ;    // Tachometer Switch Control Register 2
ECReg   PWM0LHE         ;    // PWM0 LED DIMMING ENABLE
ECReg   PWM0LCR1        ;    // PWM0 LED DIMMING CONTROL 1
ECReg   PWM0LCR2        ;    // PWM0 LED DIMMING CONTROL 2
ECReg   PWM1LHE         ;    // PWM1 LED DIMMING ENABLE
ECReg   PWM1LCR1        ;    // PWM1 LED DIMMING CONTROL 1
ECReg   PWM1LCR2        ;    // PWM1 LED DIMMING CONTROL 2
ECReg   PWMLCCR         ;    // PWM Load Counter Control
ECReg   CTR1M           ;    // Cycle Time Register 1 MSB
ECReg   DCR2M           ;    // PWM Duty Cycle Register 2 MSB
ECReg   DCR3M           ;    // PWM Duty Cycle Register 3 MSB

//-----------------------------------------------------------------------------
// (19xxh) Analog to Digital converter (ADC)
//-----------------------------------------------------------------------------
ECReg   ADCSTS          ;    // ADC Status
ECReg   ADCCFG          ;    // ADC Configuration
ECReg   ADCCTL          ;    // ADC Clock Control
ECReg   ADCGCR          ;    // ADC General Control
ECReg   VCH0CTL         ;    // Voltage Channel 0 Channel Control
ECReg   KDCTL           ;    // Calibration Data Control
ECReg   VCH1CTL         ;    // Voltage Channel 1 Control
ECReg   VCH1DATL        ;    // Voltage Channel 1 Data Buffer LSB
ECReg   VCH1DATM        ;    // Voltage Channel 1 Data Buffer MSB
ECReg   VCH2CTL         ;    // Voltage Channel 2 Control
ECReg   VCH2DATL        ;    // Voltage Channel 2 Data Buffer LSB
ECReg   VCH2DATM        ;    // Voltage Channel 2 Data Buffer MSB
ECReg   VCH3CTL         ;    // Voltage Channel 3 Control
ECReg   VCH3DATL        ;    // Voltage Channel 3 Data Buffer LSB
ECReg   VCH3DATM        ;    // Voltage Channel 3 Data Buffer MSB
ECReg   VHSCDBL         ;    // Voltage High Scale Calibration Data Buffer LSB
ECReg   VHSCDBM         ;    // Voltage High Scale Calibration Data Buffer MSB
ECReg   VCH0DATL        ;    // Voltage Channel 0 Data Buffer LSB
ECReg   VCH0DATM        ;    // Voltage Channel 0 Data Buffer MSB
ECReg   VHSGCDBL        ;    // Voltage High Scale Gain-error Calibration Data Buffer LSB
ECReg   VHSGCDBM        ;    // Voltage High Scale Gain-error Calibration Data Buffer MSB

ECReg   VCMPSCP         ;    // Voltage Compare Scan Period
ECReg   VCH4CTL         ;    // Voltage Channel 4 Control
ECReg   VCH4DATM        ;    // Volt Channel 4 Data Buffer MSB
ECReg   VCH4DATL        ;    // Volt Channel 4 Data Buffer LSB
ECReg   VCH5CTL         ;    // Voltage Channel 5 Control
ECReg   VCH5DATM        ;    // Volt Channel 5 Data Buffer MSB
ECReg   VCH5DATL        ;    // Volt Channel 5 Data Buffer LSB
ECReg   VCH6CTL         ;    // Voltage Channel 6 Control
ECReg   VCH6DATM        ;    // Volt Channel 6 Data Buffer MSB
ECReg   VCH6DATL        ;    // Volt Channel 6 Data Buffer LSB
ECReg   VCH7CTL         ;    // Voltage Channel 7 Control
ECReg   VCH7DATM        ;    // Volt Channel 7 Data Buffer MSB
ECReg   VCH7DATL        ;    // Volt Channel 7 Data Buffer LSB
ECReg   ADCDVSTS        ;    // ADC Data Vaild Status
ECReg   VCMPSTS         ;    // Voltage Compare Status
ECReg   VCMP0CTL        ;    // Voltage Compare Channel 0 Control
ECReg   VCMP0THRDATM    ;    // Voltage Compare 0 Threshold Data Buffer MSB
ECReg   VCMP0THRDATL    ;    // Voltage Compare 0 Threshold Data Buffer LSB
ECReg   VCMP1CTL        ;    // Voltage Compare Channel 1 Control
ECReg   VCMP1THRDATM    ;    // Voltage Compare 1 Threshold Data Buffer MSB
ECReg   VCMP1THRDATL    ;    // Voltage Compare 1 Threshold Data Buffer LSB
ECReg   VCMP2CTL        ;    // Voltage Compare Channel 2 Control
ECReg   VCMP2THRDATM    ;    // Voltage Compare 2 Threshold Data Buffer MSB
ECReg   VCMP2THRDATL    ;    // Voltage Compare 2 Threshold Data Buffer LSB
ECReg   VCMPOTR         ;    // Voltage Comparator Output Type
ECReg   VCMP0HYDATM     ;    // Voltage Comparator 0 Hysteresis Data Buffer MSB
ECReg   VCMP0HYDATL     ;    // Voltage Comparator 0 Hysteresis Data Buffer LSB
ECReg   VCMPLR          ;    // Voltage Comparator Lock
ECReg   ADCIVMFSCS1     ;    // ADC Input Voltage Mapping Full-Scale Code Selection 1
ECReg   ADCIVMFSCS2     ;    // ADC Input Voltage Mapping Full-Scale Code Selection 2

//-----------------------------------------------------------------------------
// (1Axxh) Digital to Analog Converter (DAC)
//-----------------------------------------------------------------------------
ECReg   DACPDREG        ;    // DAC Power Down
ECReg   DACDAT0         ;    // DAC Data Channel 0 (IT8991E/IT557X None)
ECReg   DACDAT1         ;    // DAC Data Channel 1 (IT8991E/IT557X None)
ECReg   DACDAT2         ;    // DAC Data Channel 2
ECReg   DACDAT3         ;    // DAC Data Channel 3
ECReg   DACDAT4         ;    // DAC Data Channel 4
ECReg   DACDAT5         ;    // DAC Data Channel 5

//-----------------------------------------------------------------------------
// (1Bxxh) Wack-Up control (WUC)
//-----------------------------------------------------------------------------
ECReg   WUEMR1          ;    // Wake-Up Edge Mode 1
ECReg   WUEMR2          ;    // Wake-Up Edge Mode 2
ECReg   WUEMR3          ;    // Wake-Up Edge Mode 3
ECReg   WUEMR4          ;    // Wake-Up Edge Mode 4
ECReg   WUEMR6          ;    // Wake-Up Edge Mode 6
ECReg   WUEMR7          ;    // Wake-Up Edge Mode 7
ECReg   WUEMR8          ;    // Wake-Up Edge Mode 8
ECReg   WUEMR9          ;    // Wake-Up Edge Mode 9
ECReg   WUEMR10         ;    // Wake-Up Edge Mode 10
ECReg   WUEMR11         ;    // Wake-Up Edge Mode 11
ECReg   WUEMR12         ;    // Wake-Up Edge Mode 12
ECReg   WUEMR13         ;    // Wake-Up Edge Mode 13
ECReg   WUEMR14         ;    // Wake-Up Edge Mode 14

ECReg   WUESR1          ;    // Wake-Up Edge Sense 1
ECReg   WUESR2          ;    // Wake-Up Edge Sense 2
ECReg   WUESR3          ;    // Wake-Up Edge Sense 3
ECReg   WUESR4          ;    // Wake-Up Edge Sense 4
ECReg   WUESR6          ;    // Wake-Up Edge Sense 6
ECReg   WUESR7          ;    // Wake-Up Edge Sense 7
ECReg   WUESR8          ;    // Wake-Up Edge Sense 8
ECReg   WUESR9          ;    // Wake-Up Edge Sense 9
ECReg   WUESR10         ;    // Wake-Up Edge Sense 10
ECReg   WUESR11         ;    // Wake-Up Edge Sense 11
ECReg   WUESR12         ;    // Wake-Up Edge Sense 12
ECReg   WUESR13         ;    // Wake-Up Edge Sense 13
ECReg   WUESR14         ;    // Wake-Up Edge Sense 14

ECReg   WUENR1          ;    // Wake-Up Enable 1
ECReg   WUENR2          ;    // Wake-Up Enable 2
ECReg   WUENR3          ;    // Wake-Up Enable 3
ECReg   WUENR4          ;    // Wake-Up Enable 4
ECReg   WUENR6          ;    // Wake-Up Enable 6
ECReg   WUENR7          ;    // Wake-Up Enable 7
ECReg   WUENR8          ;    // Wake-Up Enable 8
ECReg   WUENR9          ;    // Wake-Up Enable 9

//-----------------------------------------------------------------------------
// (1Cxxh) SMBus Interface (SMB)
//-----------------------------------------------------------------------------
ECReg   HOSTA_A         ;    // Host Status A
ECReg   HOSTA_B         ;    // Host Status B
ECReg   HOSTA_C         ;    // Host Status C
ECReg   HOSTA_D         ;    // Host Status D
ECReg   HOSTA_E         ;    // Host Status E
ECReg   HOSTA_F         ;    // Host Status F

ECReg   HOCTL_A         ;    // Host Control A
ECReg   HOCTL_B         ;    // Host Control B
ECReg   HOCTL_C         ;    // Host Control C
ECReg   HOCTL_D         ;    // Host Control D
ECReg   HOCTL_E         ;    // Host Control E
ECReg   HOCTL_F         ;    // Host Control F

ECReg   HOCMD_A         ;    // Host Command A
ECReg   HOCMD_B         ;    // Host Command B
ECReg   HOCMD_C         ;    // Host Command C
ECReg   HOCMD_D         ;    // Host Command D
ECReg   HOCMD_E         ;    // Host Command E
ECReg   HOCMD_F         ;    // Host Command F

ECReg   TRASLA_A        ;    // Transmit Slave Address A
ECReg   TRASLA_B        ;    // Transmit Slave Address B
ECReg   TRASLA_C        ;    // Transmit Slave Address C
ECReg   TRASLA_D        ;    // Transmit Slave Address D
ECReg   TRASLA_E        ;    // Transmit Slave Address E
ECReg   TRASLA_F        ;    // Transmit Slave Address F

ECReg   D0REG_A         ;    // Host Data 0 A
ECReg   D0REG_B         ;    // Host Data 0 B
ECReg   D0REG_C         ;    // Host Data 0 C
ECReg   D0REG_D         ;    // Host Data 0 D
ECReg   D0REG_E         ;    // Host Data 0 E
ECReg   D0REG_F         ;    // Host Data 0 F

ECReg   D1REG_A         ;    // Host Data 1 A
ECReg   D1REG_B         ;    // Host Data 1 B
ECReg   D1REG_C         ;    // Host Data 1 C
ECReg   D1REG_D         ;    // Host Data 1 D
ECReg   D1REG_E         ;    // Host Data 1 E
ECReg   D1REG_F         ;    // Host Data 1 F

ECReg   HOBDB_A         ;    // Host Block Data Byte A
ECReg   HOBDB_B         ;    // Host Block Data Byte B
ECReg   HOBDB_C         ;    // Host Block Data Byte C
ECReg   HOBDB_D         ;    // Host Block Data Byte D
ECReg   HOBDB_E         ;    // Host Block Data Byte E
ECReg   HOBDB_F         ;    // Host Block Data Byte F

ECReg   PECERC_A        ;    // Packet Error Check A
ECReg   PECERC_B        ;    // Packet Error Check B
ECReg   PECERC_C        ;    // Packet Error Check C
ECReg   PECERC_D        ;    // Packet Error Check D
ECReg   PECERC_E        ;    // Packet Error Check E
ECReg   PECERC_F        ;    // Packet Error Check F

ECReg   RESLADR_A       ;    // Receive Slave Address A
ECReg   RESLADR_B       ;    // Receive Slave Address B
ECReg   RESLADR_C       ;    // Receive Slave Address C

ECReg   RESLADR2_A      ;    // Receive Slave Address_2 A
ECReg   RESLADR2_B      ;    // Receive Slave Address_2 B
ECReg   RESLADR2_C      ;    // Receive Slave Address_2 C

ECReg   SLDA_A          ;    // Slave Data A
ECReg   SLDA_B          ;    // Slave Data B
ECReg   SLDA_C          ;    // Slave Data C

ECReg   SMBPCTL_A       ;    // SMBUS Pin Control A
ECReg   SMBPCTL_B       ;    // SMBUS Pin Control B
ECReg   SMBPCTL_C       ;    // SMBUS Pin Control C
ECReg   SMBPCTL_D       ;    // SMBUS Pin Control D
ECReg   SMBPCTL_E       ;    // SMBUS Pin Control E
ECReg   SMBPCTL_F       ;    // SMBUS Pin Control F

ECReg   SLSTA_A         ;    // Slave Status A
ECReg   SLSTA_B         ;    // Slave Status B
ECReg   SLSTA_C         ;    // Slave Status C

ECReg   SICR_A          ;    // Slave Interrupt Control A
ECReg   SICR_B          ;    // Slave Interrupt Control B
ECReg   SICR_C          ;    // Slave Interrupt Control C

ECReg   NDADR_A         ;    // Notify Device Address A
ECReg   NDADR_B         ;    // Notify Device Address B
ECReg   NDADR_C         ;    // Notify Device Address C

ECReg   NDLB_A          ;    // Notify Data Low Byte A
ECReg   NDLB_B          ;    // Notify Data Low Byte B
ECReg   NDLB_C          ;    // Notify Data Low Byte C

ECReg   NDHB_A          ;    // Notify Data High Byte A
ECReg   NDHB_B          ;    // Notify Data High Byte B
ECReg   NDHB_C          ;    // Notify Data High Byte C

ECReg   HOCTL2_A        ;    // Host Control2 A
ECReg   HOCTL2_B        ;    // Host Control2 B
ECReg   HOCTL2_C        ;    // Host Control2 C
ECReg   HOCTL2_D        ;    // Host Control2 D
ECReg   HOCTL2_E        ;    // Host Control2 E
ECReg   HOCTL2_F        ;    // Host Control2 F

ECReg   SMB4P7USL       ;    // 4.7 �gs Low
ECReg   SMB4P0USH       ;    // 4.7 �gs High
ECReg   SMB300NS        ;    // 300 ns
ECReg   SMB250NS        ;    // 250 ns
ECReg   SMB25MS         ;    // 25 ms
ECReg   SMB45P3USL      ;    // 45.3 �gs Low
ECReg   SMBS4P3USH      ;    // 45.3 �gs High
ECReg   SMB4P7A4P0H     ;    // 4.7 �gs and 4.0 �gs High

ECReg   SLVISELR        ;    // Slave Interface Select
ECReg   SCLKTS_A        ;    // SMCLK Timing Setting   A
ECReg   SCLKTS_B        ;    // SMCLK Timing Setting   B
ECReg   SCLKTS_C        ;    // SMCLK Timing Setting   C
ECReg   SCLKTS_D        ;    // SMCLK Timing Setting   D

ECReg   SMBMSTFCTRL1    ;    // SMBus FIFO Control 1
ECReg   SMBMSTFSTS1     ;    // SMBus FIFO Status 1
ECReg   SMBMSTFCTRL2    ;    // SMBus FIFO Control 2
ECReg   SMBMSTFSTS2     ;    // SMBus FIFO Status 2

ECReg   HONACKSRC_A     ;    // HOST NACK Source A
ECReg   HONACKSRC_B     ;    // HOST NACK Source B
ECReg   HONACKSRC_C     ;    // HOST NACK Source C
ECReg   HONACKSRC_D     ;    // HOST NACK Source D
ECReg   HONACKSRC_E     ;    // HOST NACK Source E
ECReg   HONACKSRC_F     ;    // HOST NACK Source F

ECReg   SLVFTH          ;    // Slave FIFO Threshold
ECReg   DFTSDFSEL       ;    // DMA from Flash to SMB Dedicated FIFO Selection
ECReg   MSTHTH          ;    // Master FIFO Threshold
ECReg   MFTHEN          ;    // Master FIFO Threshold Enable
ECReg   MFTISTA         ;    // Master FIFO Threshold Interrupt Status
ECReg   SFTHEN          ;    // Slave FIFO Threshold Enable
ECReg   SFTISTA         ;    // Slave FIFO Threshold Interrupt Status
ECReg   SADFPCTL        ;    // Slave FIFO Control
ECReg   SFFSTA          ;    // Slave FIFO Status
ECReg   SDSIC           ;    // SMBus Design Switch Interface Control
ECReg   SDSIC2          ;    // SMBus Design Switch Interface Control 2
ECReg   SBDFPCTL        ;    // Slave B Dedicated FIFO Pre-defined Control Register
ECReg   SBDFFSTA        ;    // Slave B Dedicated FIFO Status
ECReg   SCDFFCTL        ;    // Slave C Dedicated FIFO Control Register
ECReg   SCDFFSTA        ;    // Slave C Dedicated FIFO Status

ECReg   I2CW2RF         ;    // I2C Wr to Rd FIFO
ECReg   IWRFISTA        ;    // I2C Wr to Rd FIFO Interrupt Status

ECReg   SFFE            ;    // Shared FIFO Function Enable
ECReg   SISPC           ;    // SMBus Interface Switch Pin control
ECReg   MSFSS           ;    // Master Shared FIFO Size Select
ECReg   SSFSS1          ;    // Slave Shared FIFO Size Select 1
ECReg   SFBAMA          ;    // Shared FIFO Base Address for Master A
ECReg   SFBAMBCD        ;    // Shared FIFO Base Address for Master BCD
ECReg   SFBASA          ;    // Shared FIFO Base Address for Slave A
ECReg   SFBASB          ;    // Shared FIFO Base Address for Slave B
ECReg   SFBASC          ;    // Shared FIFO Base Address for Slave C
ECReg   SSFSS2          ;    // Slave Shared FIFO Size Select 2
ECReg   HWPEC           ;    // Hardwired PEC Register
ECReg   HWPES           ;    // Hardwired PEC Error Status
ECReg   SLVTPECC        ;    // Slave Transaction PEC Control

ECReg   SHWPECV_A       ;    // Slave Hardwired PEC VALUE A
ECReg   SHWPECV_B       ;    // Slave Hardwired PEC VALUE B
ECReg   SHWPECV_C       ;    // Slave Hardwired PEC VALUE C

ECReg   BTOIER          ;    // Bridge Timeout Interrupt Enabled
ECReg   ISFBCH_A        ;    // I2C Shared FIFO Byte Count H A
ECReg   ISFBCH_B        ;    // I2C Shared FIFO Byte Count H B
ECReg   ISFBCH_C        ;    // I2C Shared FIFO Byte Count H C
ECReg   ISFBCH_D        ;    // I2C Shared FIFO Byte Count H D
ECReg   ISFBCH_E        ;    // I2C Shared FIFO Byte Count H E
ECReg   ISFBCH_F        ;    // I2C Shared FIFO Byte Count H F

ECReg   SDSIC3          ;    //SMBus Design Switch Interface Control 3
ECReg   MFTHEN2         ;    //Master Dedicated FIFO Threshold Enable 2
ECReg   MFTISTA2        ;    //Master Dedicated FIFO Threshold Interrupt Status 2
ECReg   HWPEC2          ;    //Hardwired PEC Register 2
ECReg   HWPES2          ;    //Hardwired PEC Error Status 2
ECReg   SCLKTS_E        ;    //SMCLK Timing Setting Register E
ECReg   SCLKTS_F        ;    //SMCLK Timing Setting Register F

//-----------------------------------------------------------------------------
// (1Dxxh) Keyboard Matrix Scan control (KBS)
//-----------------------------------------------------------------------------
ECReg   KSOL            ;    // Keyboard Scan Out
ECReg   KSOH1           ;    // Keyboard Scan Out
ECReg   KSOCTRL         ;    // Keyboard Scan Out Control
ECReg   KSOH2           ;    // Keyboard Scan Out
ECReg   KSI             ;    // Keyboard Scan In
ECReg   KSICTRL         ;    // Keyboard Scan In Control
ECReg   KSIGCTRLR       ;    // Keyboard Scan In [7:0] GPIO Control
ECReg   KSIGOENR        ;    // Keyboard Scan In [7:0] GPIO Output Enable
ECReg   KSIGDATR        ;    // Keyboard Scan In [7:0] GPIO DATA
ECReg   KSIGDMRRR       ;    // Keyboard Scan In [7:0] GPIO DATA Mirror
ECReg   KSOHGCTRLR      ;    // Keyboard Scan Out [15:8] GPIO Control
ECReg   KSOHGOENR       ;    // Keyboard Scan Out [15:8] GPIO Output Enable
ECReg   KSOHGDMRRR      ;    // Keyboard Scan Out [15:8] GPIO DATA Mirror
ECReg   KSOLGCTRLR      ;    // Keyboard Scan Out [7:0] GPIO Control
ECReg   KSOLGOENR       ;    // Keyboard Scan Out [7:0] GPIO Output Enable
ECReg   KSOLGDMRRR      ;    // Keyboard Scan Out [7:0] GPIO DATA Mirror
ECReg   KSO0LSDR        ;    // KSO 0 Low Scan Data
ECReg   KSO1LSDR        ;    // KSO 1 Low Scan Data
ECReg   KSO2LSDR        ;    // KSO 2 Low Scan Data
ECReg   KSO3LSDR        ;    // KSO 3 Low Scan Data
ECReg   KSO4LSDR        ;    // KSO 4 Low Scan Data
ECReg   KSO5LSDR        ;    // KSO 5 Low Scan Data
ECReg   KSO6LSDR        ;    // KSO 6 Low Scan Data
ECReg   KSO7LSDR        ;    // KSO 7 Low Scan Data
ECReg   KSO8LSDR        ;    // KSO 8 Low Scan Data
ECReg   KSO9LSDR        ;    // KSO 9 Low Scan Data
ECReg   KSO10LSDR       ;    // KSO 10 Low Scan Data
ECReg   KSO11LSDR       ;    // KSO 11 Low Scan Data
ECReg   KSO12LSDR       ;    // KSO 12 Low Scan Data
ECReg   KSO13LSDR       ;    // KSO 13 Low Scan Data
ECReg   KSO14LSDR       ;    // KSO 14 Low Scan Data
ECReg   KSO15LSDR       ;    // KSO 15 Low Scan Data
ECReg   KSO16LSDR       ;    // KSO 16 Low Scan Data
ECReg   KSO17LSDR       ;    // KSO 17 Low Scan Data
ECReg   SDC1R           ;    // Scan Data Control 1
ECReg   SDC2R           ;    // Scan Data Control 2
ECReg   SDC3R           ;    // Scan Data Control 3
ECReg   SDSR            ;    // Scan Data Control 4

ECReg   KSIGPODR        ;    // Keyboard Scan In [7:0] GPIO Open-Drain Register
ECReg   KSOHGPODR       ;    // Keyboard Scan Out [15:8] GPIO Open-Drain Register
ECReg   KSOLGPODR       ;    // Keyboard Scan Out [7:0] GPIO Open-Drain Register

//-----------------------------------------------------------------------------
// (1Exxh) EC Clock and Power Management controller (ECPM)
//-----------------------------------------------------------------------------
ECReg   CGCTRL1R        ;    // Clock Gating Control 1
ECReg   CGCTRL2R        ;    // Clock Gating Control 2
ECReg   CGCTRL3R        ;    // Clock Gating Control 3
ECReg   PLLCTRL         ;    // PLL Control
ECReg   AUTOCG          ;    // Auto Clock Gating
ECReg   PLLFREQR        ;    // PLL Frequency
ECReg   PLLSSCR         ;    // PLL Frequency
ECReg   PLLCSS          ;    // PLL Clock Source Status
ECReg   CGCTRL4R        ;    // Clock Gating Control 4

//-----------------------------------------------------------------------------
// (1Fxxh) External Timer & External Watchdog (ETWD)
//-----------------------------------------------------------------------------
ECReg   ETWCFG          ;    // External Timer/WDT Configuration
ECReg   ET1PSR          ;    // External Timer Prescaler
ECReg   ET1CNTLHR       ;    // External Timer Counter High Byte
ECReg   ET1CNTLLR       ;    // External Timer Counter Low Byte
ECReg   ETWCTRL         ;    // External Timer/WDT Control
ECReg   EWDCNTLLR       ;    // External WDT Counter Low Byte
ECReg   EWDKEYR         ;    // External WDT Key
ECReg   EWDCNTLHR       ;    // External WDT Counter High Byte

ECReg   ET2PSR          ;    // External Timer 2 Prescaler
ECReg   ET2CNTLHR       ;    // External Timer 2 Counter High Byte
ECReg   ET2CNTLLR       ;    // External Timer 2 Counter Low Byte
ECReg   ET2CNTLH2R      ;    // External Timer 2 Counter High Byte 2

ECReg   ET3PSR          ;    // External Timer 3 Prescaler
ECReg   ET3CNTLHR       ;    // External Timer 3 Counter High Byte
ECReg   ET3CNTLLR       ;    // External Timer 3 Counter Low Byte
ECReg   ET3CNTLH2R      ;    // External Timer 3 Counter High Byte 2

ECReg   ET4CNTLLR       ;    // External Timer 4 Counter Low Byte

//-----------------------------------------------------------------------------
// General Control (GCTRL) (20xxh)
//-----------------------------------------------------------------------------
ECReg   ECHIPID1        ;    // Chip ID Byte 1
ECReg   ECHIPID2        ;    // Chip ID Byte 2
ECReg   ECHIPVER        ;    // Chip Version
ECReg   IDR             ;    // Identify Input
ECReg   RSTS            ;    // Reset Status
ECReg   RSTC1           ;    // Reset Control 1
ECReg   RSTC2           ;    // Reset Control 2
ECReg   RSTC3           ;    // Reset Control 3
ECReg   RSTC4           ;    // Reset Control 4
ECReg   RSTC6           ;    // Reset Control 6

ECReg   RSTDMMC         ;    // Reset Control DMMC
ECReg   BADRSEL         ;    // Base Address Select
ECReg   WNCKR           ;    // Wait Next Clock Rising
ECReg   SPCTRL5         ;    // Special Control 5
ECReg   SPCTRL1         ;    // Special Control 1
ECReg   RSTCH           ;    // Reset Control Host Side
ECReg   GENIRQ          ;    // Generate IRQ
ECReg   SPCTRL2         ;    // Special Control 2
ECReg   SPCTRL3         ;    // Special Control 3

ECReg   PI2ECH          ;    // Port I2EC High-Byte
ECReg   PI2ECL          ;    // Port I2EC Low-Byte
ECReg   BINTADDR0R      ;    // BRAM Interrupt Address 0
ECReg   BINTADDR1R      ;    // BRAM Interrupt Address 1
ECReg   BINTCTRLR       ;    // BRAM Interrupt Control
ECReg   SPCTRL4         ;    // Special Control 4
ECReg   REG_201D        ;

ECReg   SHA1HASHCTRLR   ;    // SHA1 Hash Control
ECReg   SHA1HBADDR      ;    // SHA1 Hash Base Address
ECReg   P80H81HSR       ;    // Port 80h/81h Status Register
ECReg   P80HDR          ;    // Port 80h Data Register
ECReg   P81HDR          ;    // Port 81h Data Register

//-----------------------------------------------------------------------------
// (21xxh) External GPIO Controller (EGPC)
//-----------------------------------------------------------------------------
ECReg   EADDR           ;    // External GPIO Address
ECReg   EDAT            ;    // External GPIO Data
ECReg   ECNT            ;    // External GPIO Control
ECReg   ESTS            ;    // External GPIO Status

ECReg   EARCR           ;    // External GPIO Auto Read Control
ECReg   ERE1R           ;    // External GPIO Read Enable 1
ECReg   ERE2R           ;    // External GPIO Read Enable 2
ECReg   ERE3R           ;    // External GPIO Read Enable 3
ECReg   ERE4R           ;    // External GPIO Read Enable 4
ECReg   ERE5R           ;    // External GPIO Read Enable 5
ECReg   ESVR            ;    // External GPIO Status Vector
ECReg   ESCF1R          ;    // External GPIO Status Change Flag 1
ECReg   ESCF2R          ;    // External GPIO Status Change Flag 2
ECReg   ESCF3R          ;    // External GPIO Status Change Flag 3
ECReg   ESCF4R          ;    // External GPIO Status Change Flag 4
ECReg   ESCF5R          ;    // External GPIO Status Change Flag 5

//-----------------------------------------------------------------------------
// (22xxh) Battery-Backed SRAM (BRAM)
//-----------------------------------------------------------------------------
ECReg   BRAM2[128]      ;    // 128 bytes ITE BRAM
ECReg   BRAM[64]        ;    // 64 bytes ITE BRAM

//-----------------------------------------------------------------------------
// (23xxh) Consumer IR (CIR)
//-----------------------------------------------------------------------------
ECReg   C0DR            ;    // CIR Data
ECReg   C0MSTCR         ;    // CIR Master Control
ECReg   C0IER           ;    // CIR Interrupt Enable
ECReg   C0IIR           ;    // CIR Interrupt Identification
ECReg   C0CFR           ;    // CIR Carrier Frequency
ECReg   C0RCR           ;    // CIR Receive Control
ECReg   C0TCR           ;    // CIR Transmitter
ECReg   C0SCK           ;    // CIR for sleep mode
ECReg   C0BDLR          ;    // CIR Baud Rate Divisor Low Byte
ECReg   C0BDHR          ;    // CIR Baud Rate Divisor High Byte
ECReg   C0TFSR          ;    // CIR Transmitter FIFO Status
ECReg   C0RFSR          ;    // CIR Receiver FIFO Status
ECReg   C0WCSSR         ;    // CIR Wakeup Code Set Select
ECReg   C0WCL           ;    // CIR Wakeup Code Length
ECReg   C0WCR           ;    // CIR Wakeup Code Read/Write
ECReg   C0WPS           ;    // CIR Wakeup Code Power Control/Status
ECReg   CSCRR           ;    // CIR Scratch

//-----------------------------------------------------------------------------
// (25xxh) Debugger (DBGR)
//-----------------------------------------------------------------------------
ECReg   BKA1L           ;    // Trigger 1 Address Low Byte
ECReg   BKA1M           ;    // Trigger 1 Address Middle Byte
ECReg   BKA1H           ;    // Trigger 1 Address High Byte
ECReg   BKA2L           ;    // Trigger 2 Address Low Byte
ECReg   BKA2M           ;    // Trigger 2 Address Middle Byte
ECReg   BKA2H           ;    // Trigger 2 Address High Byte
ECReg   BKA3L           ;    // Trigger 3 Address Low Byte
ECReg   BKA3M           ;    // Trigger 3 Address Middle Byte
ECReg   BKA3H           ;    // Trigger 3 Address High Byte

//-----------------------------------------------------------------------------
// (26xxh) Serial Peripheral Interface (SSPI)
//-----------------------------------------------------------------------------
ECReg   SPIDATA         ;    // SPI Data
ECReg   SPICTRL1        ;    // SPI Control 1
ECReg   SPICTRL2        ;    // SPI Control 2
ECReg   SPISTS          ;    // SPI Status
ECReg   SPICTRL3        ;    // SPI Control 3

//-----------------------------------------------------------------------------
// (27xxh) Extern Serial Port (UART1)
//-----------------------------------------------------------------------------
ECReg   UART1_RBR       ;    // Receiver Buffer
ECReg   UART1_IER       ;    // Interrupt Enable
ECReg   UART1_IIR       ;    // Interrupt Identification
ECReg   UART1_LCR       ;    // Line Control
ECReg   UART1_MCR       ;    // Modem Control
ECReg   UART1_LSR       ;    // Line Status
ECReg   UART1_MSR       ;    // Modem Status
ECReg   UART1_SCR       ;    // Scratch Pad
ECReg   UART1_ECSPMR    ;    // EC Serial Port Mode

//-----------------------------------------------------------------------------
// (28xxh) Extern Serial Port (UART2)
//-----------------------------------------------------------------------------
ECReg   UART2_RBR       ;    // Receiver Buffer
ECReg   UART2_IER       ;    // Interrupt Enable
ECReg   UART2_IIR       ;    // Interrupt Identification
ECReg   UART2_LCR       ;    // Line Control
ECReg   UART2_MCR       ;    // Modem Control
ECReg   UART2_LSR       ;    // Line Status
ECReg   UART2_MSR       ;    // Modem Status
ECReg   UART2_SCR       ;    // Scratch Pad
ECReg   UART2_ECSPMR    ;    // EC Serial Port Mode

//-----------------------------------------------------------------------------
// (29xxh) 8 Bit Timer (TMR)
//-----------------------------------------------------------------------------
ECReg   PRSC            ;    // TMR Prescaler
ECReg   GCSMS           ;    // Group Clock Source and Mode Select
ECReg   CTR_A0          ;    // A0 Cycle Time
ECReg   CTR_A1          ;    // A1 Cycle Time
ECReg   CTR_B0          ;    // B0 Cycle Time
ECReg   CTR_B1          ;    // B1 Cycle Time
ECReg   DCR_A0          ;    // A0 Duty Time
ECReg   DCR_A1          ;    // A1 Duty Time
ECReg   DCR_B0          ;    // B0 Duty Time
ECReg   DCR_B1          ;    // B1 Duty Time
ECReg   CCGSR           ;    // Channel Clock Group Select
ECReg   TMRCE           ;    // TMR Clock Enable
ECReg   TMEIE           ;    // TMR Interrupt Enable

//-----------------------------------------------------------------------------
// (2Exxh) Consumer Electronics Control (CEC)
//-----------------------------------------------------------------------------
ECReg   CECDR           ;    // CEC Data
ECReg   CECFSTS         ;    // CEC FIFO Status
ECReg   CECDLA          ;    // CEC Device Logical Address
ECReg   CECCTRL         ;    // CEC Control
ECReg   CECSTS          ;    // CEC Status
ECReg   CECIE           ;    // CEC Interrupt Enable
ECReg   CECOPSTS        ;    // CEC Operation Status
ECReg   CECCRH          ;    // CEC Received Header

//-----------------------------------------------------------------------------
// (30xxh) Platform Environment Control Interface (PECI)
//-----------------------------------------------------------------------------
ECReg   HOSTAR          ;    // Host Status
ECReg   HOCTLR          ;    // Host Control
ECReg   HOCMDR          ;    // Host Command
ECReg   HOTRADDR        ;    // Host Target Address
ECReg   HOWRLR          ;    // Host Write Length
ECReg   HORDLR          ;    // Host Read Length
ECReg   HOWRDR          ;    // Host Write Data
ECReg   HORDDR          ;    // Host Read Data

ECReg   HOCTL2R         ;    // Host Control 2
ECReg   RWFCSV          ;    // Received Write FCS Value
ECReg   RRFCSV          ;    // Received Read FCS Value
ECReg   WFCSV           ;    // Write FCS Value
ECReg   RFCSV           ;    // Read FCS Value
ECReg   AWFCSV          ;    // Assured Write FCS Value
ECReg   PADCTLR         ;    // Pad Control

//-----------------------------------------------------------------------------
// (31xxh) eSPI slave Interface ()
//-----------------------------------------------------------------------------
/* Device Identification 00h-03h */
ECReg   REG_3100        ;
ECReg   REG_3101        ;
ECReg   REG_3102        ;
ECReg   REG_3103        ;

/* General Capabilities and Configurations     04h-07h */
ECReg   REG_3104        ;
ECReg   REG_3105        ;
ECReg   REG_3106        ;
ECReg   REG_3107        ;

/* Channel 0 Capabilities and Configurations   08h-0Bh */
ECReg   REG_3108        ;
ECReg   REG_3109        ;
ECReg   REG_310A        ;
ECReg   REG_310B        ;

/* Channel 1 Capabilities and Configurations   0Ch-0Fh */
ECReg   REG_310C        ;
ECReg   REG_310D        ;
ECReg   REG_310E        ;
ECReg   REG_310F        ;

/* Channel 2 Capabilities and Configurations   10h-13h */
ECReg   REG_3110        ;
ECReg   REG_3111        ;
ECReg   REG_3112        ;
ECReg   REG_3113        ;

/* Channel 3 Capabilities and Configurations   14h-17h */
ECReg   REG_3114        ;
ECReg   REG_3115        ;
ECReg   REG_3116        ;
ECReg   REG_3117        ;

/* Channel 3 Capabilities and Configurations 2 18h-1Bh */
ECReg   REG_3118        ;
ECReg   REG_3119        ;
ECReg   REG_311A        ;
ECReg   REG_311B        ;

ECReg   ESPCTRL0        ;    //eSPI PC Control 0 (ESPCTRL0) 90h
ECReg   ESPCTRL1        ;    //eSPI PC Control 1 (ESPCTRL1) 91h
ECReg   ESPCTRL2        ;    //eSPI PC Control 2 (ESPCTRL2) 92h
ECReg   ESPCTRL3        ;    //eSPI PC Control 3 (ESPCTRL3) 93h
ECReg   ESPCTRL4        ;    //eSPI PC Control 4 (ESPCTRL4) 94h
ECReg   ESPCTRL5        ;    //eSPI PC Control 5 (ESPCTRL5) 95h
ECReg   ESPCTRL6        ;    //eSPI PC Control 6 (ESPCTRL6) 96h
ECReg   ESPCTRL7        ;    //eSPI PC Control 7 (ESPCTRL7) 97h
ECReg   ESPCTRL8        ;    //eSPI PC Control 8 (ESPCTRL8) 98h
ECReg   ESPCTRL9        ;    //eSPI PC Control 9 (ESPCTRL9) 99h

ECReg   ESGCTRL0        ;    //eSPI General Control 0 (ESGCTRL0) A0h
ECReg   ESGCTRL1        ;    //eSPI General Control 1 (ESGCTRL1) A1h
ECReg   ESGCTRL2        ;    //eSPI General Control 2 (ESGCTRL2) A2h
ECReg   ESGCTRL3        ;    //eSPI General Control 3 (ESGCTRL3) A3h

ECReg   ESUCTRL0        ;    //eSPI Upstream Control 0 (ESUCTRL0) B0h
ECReg   ESUCTRL1        ;    //eSPI Upstream Control 1 (ESUCTRL1) B1h
ECReg   ESUCTRL2        ;    //eSPI Upstream Control 2 (ESUCTRL2) B2h
ECReg   ESUCTRL3        ;    //eSPI Upstream Control 3 (ESUCTRL3) B3h
ECReg   ESUCTRL4        ;    //eSPI Upstream Control 4 (ESUCTRL4) B4h
ECReg   ESUCTRL5        ;    //eSPI Upstream Control 5 (ESUCTRL5) B5h
ECReg   ESUCTRL6        ;    //eSPI Upstream Control 6 (ESUCTRL6) B6h
ECReg   ESUCTRL7        ;    //eSPI Upstream Control 7 (ESUCTRL7) B7h
ECReg   ESUCTRL8        ;    //eSPI Upstream Control 8 (ESUCTRL8) B8h

ECReg   ESOCTRL0        ;    //eSPI OOB Control 0 (ESOCTRL0) C0h
ECReg   ESOCTRL1        ;    //eSPI OOB Control 1 (ESOCTRL1) C1h
ECReg   ESOCTRL2        ;    //eSPI OOB Control 2 (ESOCTRL2) C2h
ECReg   ESOCTRL3        ;    //eSPI OOB Control 3 (ESOCTRL3) C3h
ECReg   ESOCTRL4        ;    //eSPI OOB Control 4 (ESOCTRL4) C4h
ECReg   ESOCTRL5        ;    //eSPI OOB Control 5 (ESOCTRL5) C5h
ECReg   ESOCTRL6        ;    //eSPI OOB Control 6 (ESOCTRL6) C6h
ECReg   ESOCTRL7        ;    //eSPI OOB Control 7 (ESOCTRL7) C7h

ECReg   ESPISAFSC0      ;    //eSPI SAFS Control 0 (ESPISAFSC0)
ECReg   ESPISAFSC1      ;    //eSPI SAFS Control 1 (ESPISAFSC1)
ECReg   ESPISAFSC2      ;    //eSPI SAFS Control 2 (ESPISAFSC2)
ECReg   ESPISAFSC3      ;    //eSPI SAFS Control 3 (ESPISAFSC3)
ECReg   ESPISAFSC4      ;    //eSPI SAFS Control 4 (ESPISAFSC4)
ECReg   ESPISAFSC5      ;    //eSPI SAFS Control 5 (ESPISAFSC5)
ECReg   ESPISAFSC6      ;    //eSPI SAFS Control 6 (ESPISAFSC6)
ECReg   ESPISAFSC7      ;    //eSPI SAFS Control 7 (ESPISAFSC7)

//-----------------------------------------------------------------------------
// (32xxh) eSPI slave Interface ()
//-----------------------------------------------------------------------------
ECReg   VWIDX0          ;    //eSPI VW Index 0

ECReg   VWIDX2          ;    //eSPI VW Index 2
ECReg   VWIDX3          ;    //eSPI VW Index 3
ECReg   VWIDX4          ;    //eSPI VW Index 4
ECReg   VWIDX5          ;    //eSPI VW Index 5
ECReg   VWIDX6          ;    //eSPI VW Index 6
ECReg   VWIDX7          ;    //eSPI VW Index 7

ECReg   VWIDX40         ;    //eSPI VW Index 40
ECReg   VWIDX41         ;    //eSPI VW Index 41
ECReg   VWIDX42         ;    //eSPI VW Index 42
ECReg   VWIDX43         ;    //eSPI VW Index 43
ECReg   VWIDX44         ;    //eSPI VW Index 44
ECReg   VWIDX45         ;    //eSPI VW Index 45
ECReg   VWIDX46         ;    //eSPI VW Index 46
ECReg   VWIDX47         ;    //eSPI VW Index 47

ECReg   VWCTRL0         ;    //eSPI VW Contrl 0
ECReg   VWCTRL1         ;    //eSPI VW Contrl 1
ECReg   VWCTRL2         ;    //eSPI VW Contrl 2
ECReg   VWCTRL3         ;    //eSPI VW Contrl 3

ECReg   VWCTRL5         ;    //eSPI VW Contrl 5
ECReg   VWCTRL6         ;    //eSPI VW Contrl 6
ECReg   VWCTRL7         ;    //eSPI VW Contrl 7

ECReg   REG_32A6        ;

//-----------------------------------------------------------------------------
// (33xxh) EC Interface Registers, eSI Queue 0 - PUT_PC DATA , PUT_OOB DATA
//-----------------------------------------------------------------------------
/* PUT_PC Data Byte 0-63 (PUTPCDB0-63) */
ECReg   PUT_PC_DATA[64]     ;    // 64 bytes PUT_PC_DATA buffer
/* PUT_OOB Data Byte 0-79 (PUTOOBDB0-79) */
ECReg   PUT_OOB_DATA[80]    ;    // 80 bytes PUT_OOB_DATA buffer

//-----------------------------------------------------------------------------
// (34xxh) EC Interface Registers, eSI Queue 1 - UPSTEAM DATA
//-----------------------------------------------------------------------------
/* Upstream Data Byte 0-79 (UDB0-79) 3400h-344Fh */
ECReg   UPSTREAM_DATA[80]   ;    // 80 bytes UPSTREAM_DATA buffer
/* PUT_FLASH_NP Data Byte 0-63 (PUTFLASHNPDB0-63) Address Offset: 80h-BFh */
ECReg   PUTFLASHNPDB[64]    ;

//-----------------------------------------------------------------------------
// SCRATCH_ROM - 0xB400 to 0xB7FF
//-----------------------------------------------------------------------------
ECReg   SCRATCH_ROM[1024]   ;    //(0xB400 to 0xB7FF)

/*-----------------------------------------------------------------------------
 * End of CORE_CHIPREGS.C */