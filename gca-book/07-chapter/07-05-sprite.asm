include "utils.inc"

section "vblank_interrupt", rom0[$0040]
    reti


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

def TILES_COUNT                 equ (384)
def BYTES_PER_TILE              equ (16)
def TILES_BYTE_SIZE             equ (TILES_COUNT * BYTES_PER_TILE)

def TILEMAPS_COUNT              equ (2)
def BYTE_PER_TILEMAP            equ (1024)
def TILEMAPS_BYTE_SIZE         equ (TILES_COUNT * BYTES_PER_TILE)

def GRAPHICS_DATA_SIZE          equ (TILEMAPS_BYTE_SIZE + TILES_BYTE_SIZE)
def GRAPHICS_DATA_ADDRESS_END   equ ($8000)
def GRAPHICS_DATA_ADDRESS_START equ (GRAPHICS_DATA_ADDRESS_END - GRAPHICS_DATA_SIZE)

macro LoadGraphicsDataIntoVRAM
    ld de, GRAPHICS_DATA_ADDRESS_START
    ld hl, _VRAM8000
    .load_tile\@
        ld a, [de]
        inc de
        ld [hli], a
        ld a, d
        cp a, high(GRAPHICS_DATA_ADDRESS_END)
        jr nz, .load_tile\@
endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section "sample", rom0
InitSample:
    ld a, %11100100
    ld [rBGP], a
    ld [rOBP0], a
    ld a, %00011011
    ld [rOBP1], a

    LoadGraphicsDataIntoVRAM
    InitOAM

    ld a, IE_VBLANK
    ld [rIE], a
    ei

    ld a, 7
    ld [rWX], a
    ld a, 120
    ld [rWY], a

    ld a, LCDC_ON | LCDC_BG_9800 | LCDC_BG_ON | LCDC_WIN_ON | LCDC_WIN_9C00 | LCDC_OBJ_16 | LCDC_OBJ_ON
    ld [rLCDC], a

    ret

UpdateSample:
    halt

    xor a
    ld [rSCX], a
    ld [rSCY], a

def SPRITE_0_ADDRESS equ (_OAMRAM)
    Copy [SPRITE_0_ADDRESS + OAMA_X], 16
    Copy [SPRITE_0_ADDRESS + OAMA_Y], 32
    Copy [SPRITE_0_ADDRESS + OAMA_TILEID], 16
    Copy [SPRITE_0_ADDRESS + OAMA_FLAGS], OAM_PAL0

def SPRITE_1_ADDRESS equ (_OAMRAM + OBJ_SIZE)
    Copy [SPRITE_1_ADDRESS + OAMA_X], 80
    Copy [SPRITE_1_ADDRESS + OAMA_Y], 80
    Copy [SPRITE_1_ADDRESS + OAMA_TILEID], 0
    Copy [SPRITE_1_ADDRESS + OAMA_FLAGS], OAM_PAL0, OAM_XFLIP

    ret

export InitSample, UpdateSample

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section "graphics_data", rom0[GRAPHICS_DATA_ADDRESS_START]
incbin "tileset.chr"
incbin "background.tlm"
incbin "window.tlm"
