.text
.arm
.global convertidor

convertidor:

    mov r2, #0

    cmp r0, #26
    movle r2, #1
    ble final

    cmp r0, #51
    movle r2, #2
    ble final

    cmp r0, #77
    movle r2, #3
    ble final

    cmp r0, #102
    movle r2, #4
    ble final

    cmp r0, #128
    movle r2, #5
    ble final

    cmp r0, #154
    movle r2, #6
    ble final

    cmp r0, #179
    movle r2, #7
    ble final

    cmp r0, #205
    movle r2, #8
    ble final


    cmp r0, #230
    movle r2, #9
    ble final

    cmp r0, #256
    movle r2, #10
    ble final

Final

mov r0, r2
mov pc, lr
