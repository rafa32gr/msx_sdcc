; ========================================================================== 
;                                                                            
;   WBRLE to VRAM                                                            
;                    
; ========================================================================== 
	.area _DATA


  .area _CODE

;system vars
MSXVER     = 0x002D  
  
VDPVRAM    = 0x98 ;VRAM Data (Read/Write)
VDPSTATUS  = 0x99 ;VDP Status Registers

RLECONTROL = 0x80


;void unRLEWBtoVRAM (uint RAM, uint VRAM)
_unRLEWBtoVRAM::
  push ix
  ld ix,#0
  add ix,sp
      
  ld  L,4(ix) ; Data RAM address
  ld  H,5(ix)
    
  ld E,6(ix) ; VRAM address
  ld D,7(ix)
   
  call unRLEWBVRAM
    
  pop IX
  ret


;===========================================================================
; unRLEWBtoVR
; Function : RLE type 3 to VRAM unpacker
;     
; Input    : HL - source RAM RLE data address
;            DE - target VRAM address            
;=========================================================================== 
unRLEWBVRAM::
  ; set VRAM addr 
  in   A,(VDPSTATUS)
  
  di
  ld   A,(#MSXVER)
  or   A
  jr   Z,setVADDR  ;if MSX1 -> TMS9918
  ;V9938 or higher
  xor  A
  out  (0x99),A
  ld   A,#0x8E
  out  (0x99),A

setVADDR:
  ld   A,E    
  out  (VDPSTATUS),A
  ld   A,D        
  and  #0x3F
  or   #0x40
  out  (VDPSTATUS),A
  ei
  
ANALYZE:
  ld   A,(HL)         ; get byte
  cp   #RLECONTROL                      
  jr   NZ,WriteByte   ; if raw
  
  inc  HL             ; get next byte 
  ld   A,(HL)
  or   A
  jr   Z,WriteCONTROL ;if A=0 then write one $80  ($80 $0)
  cp   #0xFF          ;if A=$FF ($80 $FF) 
  ret  Z              ;THEN exit
  
  ;$80 nn dd
  inc  A              ;2 to 255
  ld   B,A            
  inc  HL
  ld   A,(HL)         ;get value
  
doRLE:
  out  (VDPVRAM),A     ;write in VRAM
  nop
  nop
  djnz doRLE
  
  inc  HL
  jr   ANALYZE

WriteCONTROL:
  ld   A,#RLECONTROL  ;write CONTROL value
  
WriteByte:
  out  (VDPVRAM),A     ;write in VRAM
  inc  HL
  jr   ANALYZE



