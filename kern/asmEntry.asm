;
; boot.s -- Kernel start location. Also defines multiboot header.
; Based on Bran's kernel development tutorial file start.asm
;

MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
; NOTE: We do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass us a symbol table.
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)


[BITS 32]                       ; All instructions should be 32-bit.

[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
[EXTERN code]                   ; Start of the '.text' section.
[EXTERN bss]                    ; Start of the .bss section.
[EXTERN end]                    ; End of the last loadable section.



mboot:
  dd  MBOOT_HEADER_MAGIC        ; GRUB will search for this value on each
                                ; 4-byte boundary in your kernel file
  dd  MBOOT_HEADER_FLAGS        ; How GRUB should load your file / settings
  dd  MBOOT_CHECKSUM            ; To ensure that the above values are correct
   
  dd  mboot                     ; Location of this descriptor
  dd  code                      ; Start of kernel '.text' (code) section.
  dd  bss                       ; End of kernel '.data' section.
  dd  end                       ; End of kernel.
  dd  start                     ; Kernel entry point (initial EIP).

[GLOBAL start]                  ; Kernel entry point.
[EXTERN main]                   ; This is the entry point of our C code

start:

  push	  ebx
  push    eax                   ; Load multiboot header location

  ; Execute the kernel:
  cli                         ; Disable interrupts.
  call main                   ; call our main() function.




;The interupt Handlers for the fisrt 32 entries , here we have only 19
;because from 20 to 32 they are all reserved Interupts.
[GLOBAL DEVZERO]
[GLOBAL DEBUGISR]
[GLOBAL NONMASKABLEINT]
[GLOBAL BRPTSISR]
[GLOBAL INTODETOV]
[GLOBAL OUTBOUNDS]
[GLOBAL INVALIDOP]
[GLOBAL NOCOPP]
[GLOBAL DOUBLEF]
[GLOBAL COSEGOV]
[GLOBAL BADTSS]
[GLOBAL SEGNOTP]
[GLOBAL STKFAULT]
[GLOBAL GPROFAULT]
[GLOBAL PAGEFAULT]
[GLOBAL UNKOWNINT]
[GLOBAL COPFAULT]
[GLOBAL ALIGNCHECK]
[GLOBAL MCHECK]
[GLOBAL RESERVED1]
[GLOBAL RESERVED2]
[GLOBAL RESERVED3]
[GLOBAL RESERVED4]
[GLOBAL RESERVED5]
[GLOBAL RESERVED6]
[GLOBAL RESERVED7]
[GLOBAL RESERVED8]
[GLOBAL RESERVED9]
[GLOBAL RESERVED10]
[GLOBAL RESERVED11]
[GLOBAL RESERVED12]
[GLOBAL RESERVED13]

;Here the entry point for each Interupt
DEVZERO:
     cli
     push byte 0
     push byte 0
     ret
DEBUGISR:
     cli
     push byte 0
     push byte 1
     ret
NONMASKABLEINT:
     ret
BRPTSISR:
     ret
INTODETOV:
     ret
OUTBOUNDS:
     ret
INVALIDOP:
     ret
NOCOPP:
DOUBLEF:
COSEGOV:
BADTSS:
SEGNOTP:
STKFAULT:
GPROFAULT:
PAGEFAULT:
UNKOWNINT:
COPFAULT:
ALIGNCHECK:
MCHECK:
RESERVED1:
RESERVED2:
RESERVED3:
RESERVED4:
RESERVED5:
RESERVED6:
RESERVED7:
RESERVED8:
RESERVED9:
RESERVED10:
RESERVED11:
RESERVED12:
RESERVED13:


[GLOBAL ChargerIDT]
[EXTERN idtptr]
;Responsible for the loading of the IDT
ChargerIDT:
    cli
    lidt [idtptr]
    sti
    ret

;The IRQs handler	
[GLOBAL IrqTimer]
[GLOBAL IrqKeyboard]
[GLOBAL IrqCascade]
[GLOBAL IrqCOM2_4]
[GLOBAL IrqCOM1_3]
[GLOBAL IrqLpt]
[GLOBAL IrqFloppy]
[GLOBAL IrqFree7]
[GLOBAL IrqClock]
[GLOBAL IrqFree9]
[GLOBAL IrqFree10]
[GLOBAL IrqFree11]
[GLOBAL IrqPS2Mouse]
[GLOBAL IrqCoproc]
[GLOBAL IrqIDE_1]
[GLOBAL IrqIDE_2]
	
[EXTERN TimeHandler]
[EXTERN KbHandler]
[EXTERN NotyetDone]	

;The Time IRQ handler
IrqTimer:
	cli   ;Disable interupts
	pusha ;We save all the registres
	call TimeHandler; ; Handel the interupt
	popa ; Restore previous registres values
	sti  ;Enable interupts
	iret ; and return to the intrupted task

;The keyboard IRQ handler
IrqKeyboard:
	cli  ; Disable interupts
	pusha ;Save all the registres
	call KbHandler;Handel the interupt
	popa ;Restore the  previous registres values
	sti  ; Enable interupts
	iret ; and return to the intrupted task

;The others IRQs handlers but not yet implemented
IrqCascade:
IrqCOM2_4:
IrqCOM1_3:
IrqLpt:
IrqFloppy:
IrqFree7:
IrqClock:
IrqFree9:
IrqFree10:
IrqFree11:
IrqPS2Mouse:
IrqCoproc:
IrqIDE_1:
IrqIDE_2:

 cli			;Pour les autres IRQ qui ne sont pas encore definis on evois EOI (End of Interupt)
 pushad
 call NotyetDone
 popad
 sti
 iret


