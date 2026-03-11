include "utils.inc"

section "entrypoint", rom0[$0100]
entrypoint:
    di
    jp main
    ds ($0150 - @), 0

macro DisableLCD
    .wait_vblank\@
        ld a, [rLY]
        cp a, SCREEN_HEIGHT_PX
        jr nz, .wait_vblank\@
   
    ;; disable LCD
    xor a
    ld [rLCDC], a
endm


section "main", rom0
main:
    DisableLCD
    call InitSample
    .loop
        call UpdateSample
        jr .loop
