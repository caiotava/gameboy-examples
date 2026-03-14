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

macro GetPadInput
    ld a, JOYP_GET_CTRL_PAD
    ldh [rP1], a
    ldh a, [rP1]
    ldh a, [rP1]

    swap a
    and a, $F0
    ld b, a

    ld a, JOYP_GET_BUTTONS
    ldh [rP1], a
    ldh a, [rP1]
    ldh a, [rP1]
    ldh a, [rP1]
    ldh a, [rP1]
    ldh a, [rP1]
    ldh a, [rP1]

    and a, $OF
    or a, b
    ld b, a

    ld a, JOYP_GET_NONE
    ldh [rP1], a
endm

endc
