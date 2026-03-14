if !def(UTILS_RGBINC)
def UTILS_RGBINC equ 1

def _VRAM8000   equ ($8000)
def _OAMRAM     equ ($FE00)

include "../include/hardware.inc"

macro Copy
    ld a, \2
    ld \1, a
endm

macro InitOAM
    ld c, OAM_COUNT
    ld hl, _OAMRAM + OAMA_Y
    ld de, OBJ_SIZE
    .init_oam\@
        ld [hl], 0
        add hl, de

        dec c
        jr nz, .init_oam\@

endm

endc
