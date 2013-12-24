;Structure du disque en System FAT
; Il est composé en 4 zones principales
;     -----------------------
;     | Zone réseévée       |
;     -----------------------
;     | Les tables FAT      |
;     -----------------------
;     |Repertoire racine    |
;     -----------------------
;     | Zone données        |
;     -----------------------
;
; Ici la "Zone resérvé" contient le secteur boot et elle est de taille d'un secteur
;
;Apres le chargement du secteur boot à l'adresse 0X7C00, le bootloader cherche le fichier 
; "KERNEL.TOS" qui va donné la main au vrai kernel.
;le passage en mode protegé se fait dans le bootloader d'une façon temporaire 
;puis dans le programme KERNEL.TOS on re-definis la GDT et on donne la main au vrai kernelf

[BITS 16]
[ORG 0x0]

 jmp     short start 	           ; Standard start of boot sector
 nop

bOEM       db      'Test OS '
bSectSize  dw      512             ; bytes/sector NEEDED ! FIXED
bClustSize db      1               ; sectors/allocation unit NEEDED ! (FIXED)
bResSect   dw      1               ; # reserved sectors NEEDED ! (FIXED)
bFatCnt    db      2               ; # of fats NEEDED
bRootSize  dw      224             ; # of root directories NEEDED
bTotalSec  dw      2880            ; # sectors total in image
bMedia     db      240             ; media descrip: fd=2side9sec, etc...
bFatSize   dw      9               ; # sectors in a fat NEEDED
bTrackSec  dw      18              ; # sectors/track NEEDED ! FIXED
bHeadCnt   dw      2               ; # heads
bHiddenSec dd      0               ; # hidden sectors
bHugeSec   dd      0               ; # sectors if > 65536
bBootDrv   db      00              ; drive number NEEDED ! FIXED
bReserved  db      00
bBootSign  db      41              ; extended boot signature
bVolID     dd      0
bVolLabel  db      'TEST OSV1.0'
bFSType    db      'FAT12   '

; *********************
;     Main program
; *********************

start:
 mov   [bBootDrv], dl ; Save boot drive

 cli                  ; Disable the interrupts
 mov   ax, 0x07c0     ; setup the segment registers
 mov   ds, ax
 mov   es, ax
 mov   ax, 0x0000     ; setup the stack
 mov   ss, ax
 mov   sp, 0xffff
 sti                  ; Enable the interrupts


 
 mov   si, loading    ; show 'Loading'
 call  print

; ********************
;    Misc functions
; ********************

getrootdir:                    ; catch the root directory
 xor   cx, cx
 xor   dx, dx
 mov   ax, 0x0020              ; à la fin ax=((32*RootSize)/512)+2
 mul   word [bRootSize]        
 div   word [bSectSize]        ;On a ici la taille du repertoire racine en secteurs
 xchg  ax, cx                  ;On sauvgarde le resultat dans CX
 mov   al, byte [bFatCnt]     
 mul   word [bFatSize]         ;On calcule aussi la Taille des Tables FAT (Nombre de FAT * Taille FAT)
 add   ax, word [bResSect]     ;On leur ajoute la Taille de la zone réservé
 mov   word [datasector], ax   
 add   word [datasector], cx   ;La variable [DataSector pointe sur le debut de la Zone de données
 mov   bx, 0x0200              ; load to 7c00:0200
 call  readsectors
 mov   cx, word [bRootSize]    ; counter
 mov   di, 0x0200              ; take first location
 .loop:
 push  cx
 mov   cx, 0x000B              ; check for 11 chars
 mov   si, kernel              ; which name?
 push  di
 rep   cmpsb                   ; is it equal?
 pop   di
 je    getfat
 pop   cx
 add   di, 0x0020              ; next one, please
 loop  .loop
 jmp   error

getfat:
 mov   si, dot                 ; show dot to ensure something is done
 call  print
 mov   dx, word [di + 0x001A]
 mov   word [cluster], dx      ; 1. file cluster
 xor   ax, ax
 mov   al, byte [bFatCnt]      ; Fat Count
 mul   word [bFatSize]         ; Fat Size
 mov   cx, ax
 mov   ax, word [bResSect]     ; reserved sectors
 mov   bx, 0x0200              ; copy to 7c00:0200
 call  readsectors

; Load the kernel file

 mov   ax, 0x100              ; load kernel to 1000:0000
 mov   es, ax
 xor   bx, bx
 push  bx
 mov   si, dot                 ; show dot to ensure something is done
 call  print

load:

 mov   ax, word [cluster]      ; cluster-counter
 pop   bx                      ; set buffer

 sub   ax, 0x0002              ; cluster-2
 xor   cx, cx
 mov   cl, byte [bClustSize]   ; byte -> word
 mul   cx
 add   ax, word [datasector]   ; base sector for data

 xor   cx, cx
 mov   cl, byte [bClustSize]   ; Cluster Size
 call  readsectors
 push  bx
 mov   ax, word [cluster]      ; check cluster
 mov   cx, ax                  ; copy cluster
 mov   dx, ax                  ; copy cluster
 shr   dx, 0x0001              ; dx / 2
 add   cx, dx                  ; sum for (3/2)
 mov   bx, 0x0200              ; FAT location
 add   bx, cx                  ; index into FAT
 mov   dx, word [bx]           ; read two bytes
 test  ax, 0x0001
 jnz   .odd
 .even:
 and   dx, 0000111111111111b   ; only the low twelve
 jmp   .done
 .odd:
 shr   dx, 0x0004              ; only the high twelve
 .done:
 mov   word [cluster], dx      ; store cluster
 cmp   dx, 0x0FF0              ; EOF?
 jb    load
 mov   si, dot        ; show 'a' to ensure something is done
 call  print


;------------------------------------------------------------------------------------------

 ;On passe au mode protegé
 ;On utilise une GDT temporaire pour passer en mode protegé 
 ;puis la vrai initialisation se fait dans le kernel
 cli 
 xor eax,eax
 mov ax,ds
 shl eax,4
 add eax,gdt
 mov dword [gdtr+2],eax
 
 lgdt [gdtr] ;On charge une GDT temporaire pour le passe en MP seulment
 mov  eax,cr0
 or   eax,1
 mov  cr0,eax ;On passe en mode protegé
 
 mov  ax,0x10
 mov  ds,ax
 mov  es,ax
 mov  gs,ax
 mov  fs,ax
 jmp dword 0x8:0x1000       ; Jump to kernel
retf

error:                         ; Damn, an error occured
 mov   si, error_
 call  print
 xor   ax, ax
 int   0x16                    ; get key
 int   0x19                    ; reboot

print: 
 lodsb                         ; load byte at ds:si into al
 or    al, al                  ; test if char is 0 (end)
 jz    end
 mov   ah, 0x0E                ; put char
 mov   bx, 0007                ; attribute
 int   0x10                    ; call BIOS
 jmp   print
 end:
retn

readsectors:
 .main
 mov   di, 0x0003              ; try to read 3 times
 .sloop
 push  ax
 push  bx
 push  cx

 xor   dx, dx                  ; set dx:ax for operation
 div   word [bTrackSec]        ; calc
 inc   dl                      ; set sector 0
 mov   byte [absSector], dl
 xor   dx, dx                  ; set dx:ax for operation
 div   word [bHeadCnt]         ; calc
 mov   byte [absHead], dl
 mov   byte [absTrack], al

 mov   ax, 0x201               ; read one sector
 mov   ch, byte [absTrack]     ; track
 mov   cl, byte [absSector]    ; sector
 mov   dh, byte [absHead]      ; head
 mov   dl, byte [bBootDrv]     ; drive
 int   0x13                    ; call BIOS
 jnc   .goal                   ; error?
 xor   ax, ax                  ; reset disk
 int   0x13                    ; call BIOS
 dec   di                      ; error counter-1
 pop   cx
 pop   bx
 pop   ax
 jnz   .sloop                  ; read again
 int   0x18
 .goal
 pop   cx
 pop   bx
 pop   ax
 add   bx, word [bSectSize]    ; next buffer
 inc   ax                      ; next sector
 loop  .main                   ; read next
retn

absSector   db 0x00
absHead     db 0x00
absTrack    db 0x00

datasector  dw 0x0000
cluster     dw 0x0000
kernel   db "KERNEL  TOS"
loading  db 'Loading',0
dot      db '.', 0
error_   db 'Error',0

gdt
gdt_null:  ;Le disrpteur NULL
	dw 0,0,0,0
gdt_cs:   ;discripteur du segment de code
	dw 0ffffh
    dw 0
    db 0
    db 10011011b
    db 0cfh
    db 0h
gdt_ds:  ;discripteur de segment de donées
     dw 0ffffh
     dw 0h
     db 0h
     db 10010011b
     db 0cfh
     db 0
gdtend

gdtr  dw 0x18   ;limit 
      dw 0x07C0 ; base
      dw gdt
      

TIMES 510-($-$$) DB 0
DW 0xAA55
