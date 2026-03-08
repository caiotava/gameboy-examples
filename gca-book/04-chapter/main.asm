include "utils.inc"

section "header", rom0[$0100]
entrypoint:
    di
    jp main

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section "main", rom0
main:
    call InitSample
    .loop
        call UpdateSample
        jr .loop
