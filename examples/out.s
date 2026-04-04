
========================================
IronCS K210 VM v4.0
Build: Apr  3 2026 15:25:06
========================================

[SYS] PLL0: 806000000 Hz
[SYS] PLL1: 159714285 Hz
[SYS] PLL2: 45066666 Hz
[00:00:00.000] [INFO] Initializing hardware...
[00:00:00.000] [INFO] Hardware initialized successfully
[00:00:00.000] [INFO] LED pins configured by script
[00:00:00.000] [INFO] Initializing VM...
[VM] registerNativeFunction: printf
[VM] registerNativeFunction: puts
[VM] registerNativeFunction: pinMode
[VM] registerNativeFunction: digitalWrite
[VM] registerNativeFunction: digitalRead
[VM] registerNativeFunction: analogWrite
[VM] registerNativeFunction: rgb_set
[VM] registerNativeFunction: fpioa_set_func
[VM] registerNativeFunction: gpio_set_mode
[VM] registerNativeFunction: gpio_write
[VM] registerNativeFunction: gpio_read
[VM] registerNativeFunction: uart_config
[VM] registerNativeFunction: uart_write
[VM] registerNativeFunction: uart_read
[VM] registerNativeFunction: timer_start
[VM] registerNativeFunction: timer_stop
[VM] registerNativeFunction: delay
[VM] registerNativeFunction: millis
[VM] registerNativeFunction: rgb_set
[VM] registerNativeFunction: led_init
[VM] registerNativeFunction: fpioa_set_func
[VM] registerNativeFunction: log_info
[VM] registerNativeFunction: dump_constants
[VM] registerConstant: INPUT = 0
[VM] registerConstant: INPUT_PULL_DOWN = 1
[VM] registerConstant: INPUT_PULL_UP = 2
[VM] registerConstant: OUTPUT = 3
[VM] registerConstant: HIGH = 1
[VM] registerConstant: LOW = 0
[VM] registerConstant: GPIOHS0 = 0
[VM] registerConstant: GPIOHS1 = 1
[VM] registerConstant: GPIOHS2 = 2
[VM] registerConstant: GPIOHS3 = 3
[VM] registerConstant: GPIOHS4 = 4
[VM] registerConstant: GPIOHS5 = 5
[VM] registerConstant: GPIOHS6 = 6
[VM] registerConstant: GPIOHS7 = 7
[VM] registerConstant: GPIOHS8 = 8
[VM] registerConstant: GPIOHS9 = 9
[VM] registerConstant: GPIOHS10 = 10
[VM] registerConstant: GPIOHS11 = 11
[VM] registerConstant: GPIOHS12 = 12
[VM] registerConstant: GPIOHS13 = 13
[VM] registerConstant: GPIOHS14 = 14
[VM] registerConstant: GPIOHS15 = 15
[VM] registerConstant: GPIOHS16 = 16
[VM] registerConstant: GPIOHS17 = 17
[VM] registerConstant: GPIOHS18 = 18
[VM] registerConstant: GPIOHS19 = 19
[VM] registerConstant: GPIOHS20 = 20
[VM] registerConstant: GPIOHS21 = 21
[VM] registerConstant: GPIOHS22 = 22
[VM] registerConstant: GPIOHS23 = 23
[VM] registerConstant: GPIOHS24 = 24
[VM] registerConstant: GPIOHS25 = 25
[VM] registerConstant: GPIOHS26 = 26
[VM] registerConstant: GPIOHS27 = 27
[VM] registerConstant: GPIOHS28 = 28
[VM] registerConstant: GPIOHS29 = 29
[VM] registerConstant: GPIOHS30 = 30
[VM] registerConstant: GPIOHS31 = 31
[VM] registerConstant: GPIO0 = 32
[VM] registerConstant: GPIO1 = 33
[VM] registerConstant: GPIO2 = 34
[VM] registerConstant: GPIO3 = 35
[VM] registerConstant: GPIO4 = 36
[VM] registerConstant: GPIO5 = 37
[VM] registerConstant: GPIO6 = 38
[VM] registerConstant: GPIO7 = 39
[VM] registerConstant: FUNC_GPIOHS0 = 24
[VM] registerConstant: FUNC_GPIOHS1 = 25
[VM] registerConstant: FUNC_GPIOHS2 = 26
[VM] registerConstant: FUNC_GPIOHS3 = 27
[VM] registerConstant: FUNC_GPIOHS4 = 28
[VM] registerConstant: FUNC_GPIOHS5 = 29
[VM] registerConstant: FUNC_GPIOHS6 = 30
[VM] registerConstant: FUNC_GPIOHS7 = 31
[VM] registerConstant: FUNC_GPIOHS8 = 32
[VM] registerConstant: FUNC_GPIOHS9 = 33
[VM] registerConstant: FUNC_GPIOHS10 = 34
[VM] registerConstant: FUNC_GPIOHS11 = 35
[VM] registerConstant: FUNC_GPIOHS12 = 36
[VM] registerConstant: FUNC_GPIOHS13 = 37
[VM] registerConstant: FUNC_GPIOHS14 = 38
[VM] registerConstant: FUNC_GPIOHS15 = 39
[VM] registerConstant: FUNC_GPIOHS16 = 40
[VM] registerConstant: FUNC_GPIOHS17 = 41
[VM] registerConstant: FUNC_GPIOHS18 = 42
[VM] registerConstant: FUNC_GPIOHS19 = 43
[VM] registerConstant: FUNC_GPIOHS20 = 44
[VM] registerConstant: FUNC_GPIOHS21 = 45
[VM] registerConstant: FUNC_GPIOHS22 = 46
[VM] registerConstant: FUNC_GPIOHS23 = 47
[VM] registerConstant: FUNC_GPIOHS24 = 48
[VM] registerConstant: FUNC_GPIOHS25 = 49
[VM] registerConstant: FUNC_GPIOHS26 = 50
[VM] registerConstant: FUNC_GPIOHS27 = 51
[VM] registerConstant: FUNC_GPIOHS28 = 52
[VM] registerConstant: FUNC_GPIOHS29 = 53
[VM] registerConstant: FUNC_GPIOHS30 = 54
[VM] registerConstant: FUNC_GPIOHS31 = 55
[VM] registerConstant: FUNC_GPIO0 = 56
[VM] registerConstant: FUNC_GPIO1 = 57
[VM] registerConstant: FUNC_GPIO2 = 58
[VM] registerConstant: FUNC_GPIO3 = 59
[VM] registerConstant: FUNC_GPIO4 = 60
[VM] registerConstant: FUNC_GPIO5 = 61
[VM] registerConstant: FUNC_GPIO6 = 62
[VM] registerConstant: FUNC_GPIO7 = 63
[00:00:00.000] [INFO] VM initialized with 20 native functions
[00:00:00.000] [INFO] Loading script from flash 0x80000...
[00:00:00.000] [INFO] Loading CSB from 0x00080000
[CSB] loadFromFlash addr=0x80000
[CSB] readFlash addr=0x80000 len=24 result=0
[CSB] header bytes: 43 53 42 01
[CSB] header valid
[CSB] funcCount=3, sizeof(BytecodeHeader)=24, firstFuncAddr=0x80018
[CSB] === Loading func 0 ===
[CSB] readFlash addr=0x80018 len=4 result=0
[CSB] func[0].nameOffset=0
[CSB] readFlash addr=0x8001C len=4 result=0
[CSB] func[0].paramCount=2
[CSB] readFlash addr=0x80020 len=4 result=0
[CSB] func[0].localCount=20
[CSB] readFlash addr=0x80024 len=4 result=0
[CSB] func[0].maxStackSize=16
[CSB] readFlash addr=0x80028 len=4 result=0
[CSB] func[0].instrCount=73
[CSB] func[0] sizeof(BytecodeInstruction)=5, totalInstrBytes=365
[CSB] func[0] resizing instructions to 73
[CSB] func[0] instructions resize done
[CSB] func[0] reading 365 bytes instructions from addr 0x8002C
[CSB] readFlash addr=0x8002C len=365 result=0
[CSB] func[0] instructions read done
[CSB] readFlash addr=0x80199 len=4 result=0
[CSB] func[0].constCount=0 (raw: 00 00 00 00)
[CSB] func[0] resizing constants to 0
[CSB] func[0] constants resize done
[CSB] func[0] pushing to module.functions
[CSB] func[0] pushed OK
[CSB] === Loading func 1 ===
[CSB] readFlash addr=0x8019D len=4 result=0
[CSB] func[1].nameOffset=4
[CSB] readFlash addr=0x801A1 len=4 result=0
[CSB] func[1].paramCount=3
[CSB] readFlash addr=0x801A5 len=4 result=0
[CSB] func[1].localCount=12
[CSB] readFlash addr=0x801A9 len=4 result=0
[CSB] func[1].maxStackSize=16
[CSB] readFlash addr=0x801AD len=4 result=0
[CSB] func[1].instrCount=37
[CSB] func[1] sizeof(BytecodeInstruction)=5, totalInstrBytes=185
[CSB] func[1] resizing instructions to 37
[CSB] func[1] instructions resize done
[CSB] func[1] reading 185 bytes instructions from addr 0x801B1
[CSB] readFlash addr=0x801B1 len=185 result=0
[CSB] func[1] instructions read done
[CSB] readFlash addr=0x8026A len=4 result=0
[CSB] func[1].constCount=0 (raw: 00 00 00 00)
[CSB] func[1] resizing constants to 0
[CSB] func[1] constants resize done
[CSB] func[1] pushing to module.functions
[CSB] func[1] pushed OK
[CSB] === Loading func 2 ===
[CSB] readFlash addr=0x8026E len=4 result=0
[CSB] func[2].nameOffset=6
[CSB] readFlash addr=0x80272 len=4 result=0
[CSB] func[2].paramCount=0
[CSB] readFlash addr=0x80276 len=4 result=0
[CSB] func[2].localCount=27
[CSB] readFlash addr=0x8027A len=4 result=0
[CSB] func[2].maxStackSize=16
[CSB] readFlash addr=0x8027E len=4 result=0
[CSB] func[2].instrCount=92
[CSB] func[2] sizeof(BytecodeInstruction)=5, totalInstrBytes=460
[CSB] func[2] resizing instructions to 92
[CSB] func[2] instructions resize done
[CSB] func[2] reading 460 bytes instructions from addr 0x80282
[CSB] readFlash addr=0x80282 len=460 result=0
[CSB] func[2] instructions read done
[CSB] readFlash addr=0x8044E len=4 result=0
[CSB] func[2].constCount=0 (raw: 00 00 00 00)
[CSB] func[2] resizing constants to 0
[CSB] func[2] constants resize done
[CSB] func[2] pushing to module.functions
[CSB] func[2] pushed OK
[CSB] readFlash addr=0x80452 len=4 result=0
[CSB] globalConstCount=45
[CSB] readFlash addr=0x80456 len=1 result=0
[CSB] readFlash addr=0x80457 len=8 result=0
[CSB] readFlash addr=0x8045F len=1 result=0
[CSB] readFlash addr=0x80460 len=8 result=0
[CSB] readFlash addr=0x80468 len=1 result=0
[CSB] readFlash addr=0x80469 len=8 result=0
[CSB] readFlash addr=0x80471 len=1 result=0
[CSB] readFlash addr=0x80472 len=8 result=0
[CSB] readFlash addr=0x8047A len=1 result=0
[CSB] readFlash addr=0x8047B len=8 result=0
[CSB] readFlash addr=0x80483 len=1 result=0
[CSB] readFlash addr=0x80484 len=8 result=0
[CSB] readFlash addr=0x8048C len=1 result=0
[CSB] readFlash addr=0x8048D len=8 result=0
[CSB] readFlash addr=0x80495 len=1 result=0
[CSB] readFlash addr=0x80496 len=8 result=0
[CSB] readFlash addr=0x8049E len=1 result=0
[CSB] readFlash addr=0x8049F len=8 result=0
[CSB] readFlash addr=0x804A7 len=1 result=0
[CSB] readFlash addr=0x804A8 len=8 result=0
[CSB] readFlash addr=0x804B0 len=1 result=0
[CSB] readFlash addr=0x804B1 len=8 result=0
[CSB] readFlash addr=0x804B9 len=1 result=0
[CSB] readFlash addr=0x804BA len=8 result=0
[CSB] readFlash addr=0x804C2 len=1 result=0
[CSB] readFlash addr=0x804C3 len=8 result=0
[CSB] readFlash addr=0x804CB len=1 result=0
[CSB] readFlash addr=0x804CC len=8 result=0
[CSB] readFlash addr=0x804D4 len=1 result=0
[CSB] readFlash addr=0x804D5 len=8 result=0
[CSB] readFlash addr=0x804DD len=1 result=0
[CSB] readFlash addr=0x804DE len=8 result=0
[CSB] readFlash addr=0x804E6 len=1 result=0
[CSB] readFlash addr=0x804E7 len=8 result=0
[CSB] readFlash addr=0x804EF len=1 result=0
[CSB] readFlash addr=0x804F0 len=8 result=0
[CSB] readFlash addr=0x804F8 len=1 result=0
[CSB] readFlash addr=0x804F9 len=8 result=0
[CSB] readFlash addr=0x80501 len=1 result=0
[CSB] readFlash addr=0x80502 len=8 result=0
[CSB] readFlash addr=0x8050A len=1 result=0
[CSB] readFlash addr=0x8050B len=8 result=0
[CSB] readFlash addr=0x80513 len=1 result=0
[CSB] readFlash addr=0x80514 len=8 result=0
[CSB] readFlash addr=0x8051C len=1 result=0
[CSB] readFlash addr=0x8051D len=8 result=0
[CSB] readFlash addr=0x80525 len=1 result=0
[CSB] readFlash addr=0x80526 len=8 result=0
[CSB] readFlash addr=0x8052E len=1 result=0
[CSB] readFlash addr=0x8052F len=4 result=0
[CSB] readFlash addr=0x80533 len=1 result=0
[CSB] readFlash addr=0x80534 len=8 result=0
[CSB] readFlash addr=0x8053C len=1 result=0
[CSB] readFlash addr=0x8053D len=4 result=0
[CSB] readFlash addr=0x80541 len=1 result=0
[CSB] readFlash addr=0x80542 len=8 result=0
[CSB] readFlash addr=0x8054A len=1 result=0
[CSB] readFlash addr=0x8054B len=8 result=0
[CSB] readFlash addr=0x80553 len=1 result=0
[CSB] readFlash addr=0x80554 len=8 result=0
[CSB] readFlash addr=0x8055C len=1 result=0
[CSB] readFlash addr=0x8055D len=8 result=0
[CSB] readFlash addr=0x80565 len=1 result=0
[CSB] readFlash addr=0x80566 len=8 result=0
[CSB] readFlash addr=0x8056E len=1 result=0
[CSB] readFlash addr=0x8056F len=8 result=0
[CSB] readFlash addr=0x80577 len=1 result=0
[CSB] readFlash addr=0x80578 len=8 result=0
[CSB] readFlash addr=0x80580 len=1 result=0
[CSB] readFlash addr=0x80581 len=8 result=0
[CSB] readFlash addr=0x80589 len=1 result=0
[CSB] readFlash addr=0x8058A len=8 result=0
[CSB] readFlash addr=0x80592 len=1 result=0
[CSB] readFlash addr=0x80593 len=8 result=0
[CSB] readFlash addr=0x8059B len=1 result=0
[CSB] readFlash addr=0x8059C len=8 result=0
[CSB] readFlash addr=0x805A4 len=1 result=0
[CSB] readFlash addr=0x805A5 len=8 result=0
[CSB] readFlash addr=0x805AD len=1 result=0
[CSB] readFlash addr=0x805AE len=8 result=0
[CSB] readFlash addr=0x805B6 len=1 result=0
[CSB] readFlash addr=0x805B7 len=8 result=0
[CSB] readFlash addr=0x805BF len=1 result=0
[CSB] readFlash addr=0x805C0 len=8 result=0
[CSB] readFlash addr=0x805C8 len=1 result=0
[CSB] readFlash addr=0x805C9 len=8 result=0
[CSB] readFlash addr=0x805D1 len=1 result=0
[CSB] readFlash addr=0x805D2 len=4 result=0
[CSB] readFlash addr=0x805D6 len=1 result=0
[CSB] readFlash addr=0x805D7 len=8 result=0
[CSB] readFlash addr=0x805DF len=4 result=0
[CSB] stringCount=10
[CSB] Loading 10 strings
[CSB] readFlash addr=0x805E3 len=4 result=0
[CSB] readFlash addr=0x805E7 len=7 result=0
[CSB] stringPool[0]: "rgbInit" (len=7)
[CSB] readFlash addr=0x805EF len=4 result=0
[CSB] readFlash addr=0x805F3 len=14 result=0
[CSB] stringPool[1]: "fpioa_set_func" (len=14)
[CSB] readFlash addr=0x80602 len=4 result=0
[CSB] readFlash addr=0x80606 len=7 result=0
[CSB] stringPool[2]: "pinMode" (len=7)
[CSB] readFlash addr=0x8060E len=4 result=0
[CSB] readFlash addr=0x80612 len=12 result=0
[CSB] stringPool[3]: "digitalWrite" (len=12)
[CSB] readFlash addr=0x8061F len=4 result=0
[CSB] readFlash addr=0x80623 len=8 result=0
[CSB] stringPool[4]: "rgbWrite" (len=8)
[CSB] readFlash addr=0x8062C len=4 result=0
[CSB] readFlash addr=0x80630 len=11 result=0
[CSB] stringPool[5]: "analogWrite" (len=11)
[CSB] readFlash addr=0x8063C len=4 result=0
[CSB] readFlash addr=0x80640 len=4 result=0
[CSB] stringPool[6]: "main" (len=4)
[CSB] readFlash addr=0x80645 len=4 result=0
[CSB] readFlash addr=0x80649 len=3 result=0
[CSB] stringPool[7]: "%d" (len=3)
[CSB] readFlash addr=0x8064D len=4 result=0
[CSB] readFlash addr=0x80651 len=6 result=0
[CSB] stringPool[8]: "printf" (len=6)
[CSB] readFlash addr=0x80658 len=4 result=0
[CSB] readFlash addr=0x8065C len=5 result=0
[CSB] stringPool[9]: "delay" (len=5)
[CSB] All loaded successfully!
[00:00:00.000] [INFO] CSB loaded: 3 functions, 10 strings, 45 constants
[00:00:00.000] [INFO] Executing entry point 2...
[VM] execute entryPoint=2, functions=3
[VM] entryFunc: instrCount=92, constCount=0
[VM] callFunction: funcIndex=2, paramCount=0, localCount=27, funcParamCount=0
[VM] push: slot=0, val.type=1, val.value=0
[VM] push:   m_Stack[0].type=1, m_Stack[0].value=0
[VM] push: slot=1, val.type=1, val.value=0
[VM] push:   m_Stack[1].type=1, m_Stack[1].value=0
[VM] push: slot=2, val.type=1, val.value=0
[VM] push:   m_Stack[2].type=1, m_Stack[2].value=0
[VM] push: slot=3, val.type=1, val.value=0
[VM] push:   m_Stack[3].type=1, m_Stack[3].value=0
[VM] push: slot=4, val.type=1, val.value=0
[VM] push:   m_Stack[4].type=1, m_Stack[4].value=0
[VM] push: slot=5, val.type=1, val.value=0
[VM] push:   m_Stack[5].type=1, m_Stack[5].value=0
[VM] push: slot=6, val.type=1, val.value=0
[VM] push:   m_Stack[6].type=1, m_Stack[6].value=0
[VM] push: slot=7, val.type=1, val.value=0
[VM] push:   m_Stack[7].type=1, m_Stack[7].value=0
[VM] push: slot=8, val.type=1, val.value=0
[VM] push:   m_Stack[8].type=1, m_Stack[8].value=0
[VM] push: slot=9, val.type=1, val.value=0
[VM] push:   m_Stack[9].type=1, m_Stack[9].value=0
[VM] push: slot=10, val.type=1, val.value=0
[VM] push:   m_Stack[10].type=1, m_Stack[10].value=0
[VM] push: slot=11, val.type=1, val.value=0
[VM] push:   m_Stack[11].type=1, m_Stack[11].value=0
[VM] push: slot=12, val.type=1, val.value=0
[VM] push:   m_Stack[12].type=1, m_Stack[12].value=0
[VM] push: slot=13, val.type=1, val.value=0
[VM] push:   m_Stack[13].type=1, m_Stack[13].value=0
[VM] push: slot=14, val.type=1, val.value=0
[VM] push:   m_Stack[14].type=1, m_Stack[14].value=0
[VM] push: slot=15, val.type=1, val.value=0
[VM] push:   m_Stack[15].type=1, m_Stack[15].value=0
[VM] push: slot=16, val.type=1, val.value=0
[VM] push:   m_Stack[16].type=1, m_Stack[16].value=0
[VM] push: slot=17, val.type=1, val.value=0
[VM] push:   m_Stack[17].type=1, m_Stack[17].value=0
[VM] push: slot=18, val.type=1, val.value=0
[VM] push:   m_Stack[18].type=1, m_Stack[18].value=0
[VM] push: slot=19, val.type=1, val.value=0
[VM] push:   m_Stack[19].type=1, m_Stack[19].value=0
[VM] push: slot=20, val.type=1, val.value=0
[VM] push:   m_Stack[20].type=1, m_Stack[20].value=0
[VM] push: slot=21, val.type=1, val.value=0
[VM] push:   m_Stack[21].type=1, m_Stack[21].value=0
[VM] push: slot=22, val.type=1, val.value=0
[VM] push:   m_Stack[22].type=1, m_Stack[22].value=0
[VM] push: slot=23, val.type=1, val.value=0
[VM] push:   m_Stack[23].type=1, m_Stack[23].value=0
[VM] push: slot=24, val.type=1, val.value=0
[VM] push:   m_Stack[24].type=1, m_Stack[24].value=0
[VM] push: slot=25, val.type=1, val.value=0
[VM] push:   m_Stack[25].type=1, m_Stack[25].value=0
[VM] push: slot=26, val.type=1, val.value=0
[VM] push:   m_Stack[26].type=1, m_Stack[26].value=0
[VM] callFunction: After push locals, stackTop=27
[VM] callFunction: localBase=0
[VM] opcode=1 operand=24
[VM] LOAD_CONST idx=24, globalConstants.size()=45, stackTop=27
[VM] LOAD_CONST entry.type=2, value.intVal=7, value.doubleVal=0.000000
[VM] push: slot=27, val.type=3, val.value=7
[VM] push:   m_Stack[27].type=3, m_Stack[27].value=7
[VM] LOAD_CONST done, new stackTop=28
[VM] opcode=3 operand=0
[VM] STORE_VAR: slot=0, localBase=0, localCount=0, actualSlot=0, value=7
[VM] opcode=2 operand=0
[VM] LOAD_VAR: slot=0, localBase=0, actualSlot=0
[VM] LOAD_VAR: loaded value=7
[VM] push: slot=27, val.type=3, val.value=7
[VM] push:   m_Stack[27].type=3, m_Stack[27].value=7
[VM] opcode=3 operand=1
[VM] STORE_VAR: slot=1, localBase=0, localCount=0, actualSlot=1, value=7
[VM] opcode=1 operand=25
[VM] LOAD_CONST idx=25, globalConstants.size()=45, stackTop=27
[VM] LOAD_CONST entry.type=0, value.intVal=111, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 111 to stack
[VM] push: slot=27, val.type=1, val.value=111
[VM] push:   m_Stack[27].type=1, m_Stack[27].value=111
[VM] LOAD_CONST done, new stackTop=28
[VM] opcode=3 operand=2
[VM] STORE_VAR: slot=2, localBase=0, localCount=0, actualSlot=2, value=111
[VM] opcode=2 operand=1
[VM] LOAD_VAR: slot=1, localBase=0, actualSlot=1
[VM] LOAD_VAR: loaded value=7
[VM] push: slot=27, val.type=3, val.value=7
[VM] push:   m_Stack[27].type=3, m_Stack[27].value=7
[VM] opcode=2 operand=2
[VM] LOAD_VAR: slot=2, localBase=0, actualSlot=2
[VM] LOAD_VAR: loaded value=111
[VM] push: slot=28, val.type=1, val.value=111
[VM] push:   m_Stack[28].type=1, m_Stack[28].value=111
[VM] opcode=48 operand=131080
[VM] CALL_NATIVE: stringPoolIndex=8, paramCount=2, stackTop=29
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'printf'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=29 - paramCount=2 = localBase=27
[VM]   arg[0] -> stack[27] = 7
[VM]   arg[1] -> stack[28] = 111
[VM] Saving caller pc=9 before native call
111[VM] Restored caller pc to 9 after native call
[VM] opcode=45 operand=0
[VM] push: slot=29, val.type=0, val.value=0
[VM] push:   m_Stack[29].type=0, m_Stack[29].value=0
[VM] opcode=32 operand=0
[VM] CALL: funcIndex=0, paramCount=0, stackTop=30
[VM] CALL: Stack before call: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 [16]=0 [17]=0 [18]=0 [19]=0 
[VM] callFunction: funcIndex=0, paramCount=0, localCount=20, funcParamCount=2
[VM] push: slot=30, val.type=1, val.value=0
[VM] push:   m_Stack[30].type=1, m_Stack[30].value=0
[VM] push: slot=31, val.type=1, val.value=0
[VM] push:   m_Stack[31].type=1, m_Stack[31].value=0
[VM] push: slot=32, val.type=1, val.value=0
[VM] push:   m_Stack[32].type=1, m_Stack[32].value=0
[VM] push: slot=33, val.type=1, val.value=0
[VM] push:   m_Stack[33].type=1, m_Stack[33].value=0
[VM] push: slot=34, val.type=1, val.value=0
[VM] push:   m_Stack[34].type=1, m_Stack[34].value=0
[VM] push: slot=35, val.type=1, val.value=0
[VM] push:   m_Stack[35].type=1, m_Stack[35].value=0
[VM] push: slot=36, val.type=1, val.value=0
[VM] push:   m_Stack[36].type=1, m_Stack[36].value=0
[VM] push: slot=37, val.type=1, val.value=0
[VM] push:   m_Stack[37].type=1, m_Stack[37].value=0
[VM] push: slot=38, val.type=1, val.value=0
[VM] push:   m_Stack[38].type=1, m_Stack[38].value=0
[VM] push: slot=39, val.type=1, val.value=0
[VM] push:   m_Stack[39].type=1, m_Stack[39].value=0
[VM] push: slot=40, val.type=1, val.value=0
[VM] push:   m_Stack[40].type=1, m_Stack[40].value=0
[VM] push: slot=41, val.type=1, val.value=0
[VM] push:   m_Stack[41].type=1, m_Stack[41].value=0
[VM] push: slot=42, val.type=1, val.value=0
[VM] push:   m_Stack[42].type=1, m_Stack[42].value=0
[VM] push: slot=43, val.type=1, val.value=0
[VM] push:   m_Stack[43].type=1, m_Stack[43].value=0
[VM] push: slot=44, val.type=1, val.value=0
[VM] push:   m_Stack[44].type=1, m_Stack[44].value=0
[VM] push: slot=45, val.type=1, val.value=0
[VM] push:   m_Stack[45].type=1, m_Stack[45].value=0
[VM] push: slot=46, val.type=1, val.value=0
[VM] push:   m_Stack[46].type=1, m_Stack[46].value=0
[VM] push: slot=47, val.type=1, val.value=0
[VM] push:   m_Stack[47].type=1, m_Stack[47].value=0
[VM] callFunction: After push locals, stackTop=48
[VM] callFunction: localBase=30
[VM] CALL: After setup frame, localBase=30
[VM] opcode=1 operand=0
[VM] LOAD_CONST idx=0, globalConstants.size()=45, stackTop=48
[VM] LOAD_CONST entry.type=0, value.intVal=13, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 13 to stack
[VM] push: slot=48, val.type=1, val.value=13
[VM] push:   m_Stack[48].type=1, m_Stack[48].value=13
[VM] LOAD_CONST done, new stackTop=49
[VM] opcode=3 operand=0
[VM] STORE_VAR: slot=0, localBase=30, localCount=2, actualSlot=30, value=13
[VM] opcode=1 operand=1
[VM] LOAD_CONST idx=1, globalConstants.size()=45, stackTop=48
[VM] LOAD_CONST entry.type=0, value.intVal=61, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 61 to stack
[VM] push: slot=48, val.type=1, val.value=61
[VM] push:   m_Stack[48].type=1, m_Stack[48].value=61
[VM] LOAD_CONST done, new stackTop=49
[VM] opcode=3 operand=1
[VM] STORE_VAR: slot=1, localBase=30, localCount=2, actualSlot=31, value=61
[VM] opcode=2 operand=0
[VM] LOAD_VAR: slot=0, localBase=30, actualSlot=30
[VM] LOAD_VAR: loaded value=13
[VM] push: slot=48, val.type=1, val.value=13
[VM] push:   m_Stack[48].type=1, m_Stack[48].value=13
[VM] opcode=2 operand=1
[VM] LOAD_VAR: slot=1, localBase=30, actualSlot=31
[VM] LOAD_VAR: loaded value=61
[VM] push: slot=49, val.type=1, val.value=61
[VM] push:   m_Stack[49].type=1, m_Stack[49].value=61
[VM] opcode=48 operand=131073
[VM] CALL_NATIVE: stringPoolIndex=1, paramCount=2, stackTop=50
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'fpioa_set_func'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=50 - paramCount=2 = localBase=48
[VM]   arg[0] -> stack[48] = 13
[VM]   arg[1] -> stack[49] = 61
[VM] Saving caller pc=7 before native call
[00:00:00.000] [DEBUG] fpioa_set_func(pin=13, func=61)
[VM] Restored caller pc to 7 after native call
[VM] opcode=45 operand=0
[VM] push: slot=50, val.type=1, val.value=0
[VM] push:   m_Stack[50].type=1, m_Stack[50].value=0
[VM] opcode=1 operand=2
[VM] LOAD_CONST idx=2, globalConstants.size()=45, stackTop=51
[VM] LOAD_CONST entry.type=0, value.intVal=14, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 14 to stack
[VM] push: slot=51, val.type=1, val.value=14
[VM] push:   m_Stack[51].type=1, m_Stack[51].value=14
[VM] LOAD_CONST done, new stackTop=52
[VM] opcode=3 operand=4
[VM] STORE_VAR: slot=4, localBase=30, localCount=2, actualSlot=34, value=14
[VM] opcode=1 operand=3
[VM] LOAD_CONST idx=3, globalConstants.size()=45, stackTop=51
[VM] LOAD_CONST entry.type=0, value.intVal=60, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 60 to stack
[VM] push: slot=51, val.type=1, val.value=60
[VM] push:   m_Stack[51].type=1, m_Stack[51].value=60
[VM] LOAD_CONST done, new stackTop=52
[VM] opcode=3 operand=5
[VM] STORE_VAR: slot=5, localBase=30, localCount=2, actualSlot=35, value=60
[VM] opcode=2 operand=4
[VM] LOAD_VAR: slot=4, localBase=30, actualSlot=34
[VM] LOAD_VAR: loaded value=14
[VM] push: slot=51, val.type=1, val.value=14
[VM] push:   m_Stack[51].type=1, m_Stack[51].value=14
[VM] opcode=2 operand=5
[VM] LOAD_VAR: slot=5, localBase=30, actualSlot=35
[VM] LOAD_VAR: loaded value=60
[VM] push: slot=52, val.type=1, val.value=60
[VM] push:   m_Stack[52].type=1, m_Stack[52].value=60
[VM] opcode=48 operand=131073
[VM] CALL_NATIVE: stringPoolIndex=1, paramCount=2, stackTop=53
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'fpioa_set_func'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=53 - paramCount=2 = localBase=51
[VM]   arg[0] -> stack[51] = 14
[VM]   arg[1] -> stack[52] = 60
[VM] Saving caller pc=15 before native call
[00:00:00.000] [DEBUG] fpioa_set_func(pin=14, func=60)
[VM] Restored caller pc to 15 after native call
[VM] opcode=45 operand=0
[VM] push: slot=53, val.type=1, val.value=0
[VM] push:   m_Stack[53].type=1, m_Stack[53].value=0
[VM] opcode=1 operand=4
[VM] LOAD_CONST idx=4, globalConstants.size()=45, stackTop=54
[VM] LOAD_CONST entry.type=0, value.intVal=12, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 12 to stack
[VM] push: slot=54, val.type=1, val.value=12
[VM] push:   m_Stack[54].type=1, m_Stack[54].value=12
[VM] LOAD_CONST done, new stackTop=55
[VM] opcode=3 operand=6
[VM] STORE_VAR: slot=6, localBase=30, localCount=2, actualSlot=36, value=12
[VM] opcode=1 operand=5
[VM] LOAD_CONST idx=5, globalConstants.size()=45, stackTop=54
[VM] LOAD_CONST entry.type=0, value.intVal=59, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 59 to stack
[VM] push: slot=54, val.type=1, val.value=59
[VM] push:   m_Stack[54].type=1, m_Stack[54].value=59
[VM] LOAD_CONST done, new stackTop=55
[VM] opcode=3 operand=7
[VM] STORE_VAR: slot=7, localBase=30, localCount=2, actualSlot=37, value=59
[VM] opcode=2 operand=6
[VM] LOAD_VAR: slot=6, localBase=30, actualSlot=36
[VM] LOAD_VAR: loaded value=12
[VM] push: slot=54, val.type=1, val.value=12
[VM] push:   m_Stack[54].type=1, m_Stack[54].value=12
[VM] opcode=2 operand=7
[VM] LOAD_VAR: slot=7, localBase=30, actualSlot=37
[VM] LOAD_VAR: loaded value=59
[VM] push: slot=55, val.type=1, val.value=59
[VM] push:   m_Stack[55].type=1, m_Stack[55].value=59
[VM] opcode=48 operand=131073
[VM] CALL_NATIVE: stringPoolIndex=1, paramCount=2, stackTop=56
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'fpioa_set_func'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=56 - paramCount=2 = localBase=54
[VM]   arg[0] -> stack[54] = 12
[VM]   arg[1] -> stack[55] = 59
[VM] Saving caller pc=23 before native call
[00:00:00.000] [DEBUG] fpioa_set_func(pin=12, func=59)
[VM] Restored caller pc to 23 after native call
[VM] opcode=45 operand=0
[VM] push: slot=56, val.type=1, val.value=0
[VM] push:   m_Stack[56].type=1, m_Stack[56].value=0
[VM] opcode=1 operand=6
[VM] LOAD_CONST idx=6, globalConstants.size()=45, stackTop=57
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=57, val.type=1, val.value=36
[VM] push:   m_Stack[57].type=1, m_Stack[57].value=36
[VM] LOAD_CONST done, new stackTop=58
[VM] opcode=3 operand=8
[VM] STORE_VAR: slot=8, localBase=30, localCount=2, actualSlot=38, value=36
[VM] opcode=1 operand=7
[VM] LOAD_CONST idx=7, globalConstants.size()=45, stackTop=57
[VM] LOAD_CONST entry.type=0, value.intVal=3, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 3 to stack
[VM] push: slot=57, val.type=1, val.value=3
[VM] push:   m_Stack[57].type=1, m_Stack[57].value=3
[VM] LOAD_CONST done, new stackTop=58
[VM] opcode=3 operand=9
[VM] STORE_VAR: slot=9, localBase=30, localCount=2, actualSlot=39, value=3
[VM] opcode=2 operand=8
[VM] LOAD_VAR: slot=8, localBase=30, actualSlot=38
[VM] LOAD_VAR: loaded value=36
[VM] push: slot=57, val.type=1, val.value=36
[VM] push:   m_Stack[57].type=1, m_Stack[57].value=36
[VM] opcode=2 operand=9
[VM] LOAD_VAR: slot=9, localBase=30, actualSlot=39
[VM] LOAD_VAR: loaded value=3
[VM] push: slot=58, val.type=1, val.value=3
[VM] push:   m_Stack[58].type=1, m_Stack[58].value=3
[VM] opcode=48 operand=131074
[VM] CALL_NATIVE: stringPoolIndex=2, paramCount=2, stackTop=59
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'pinMode'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=59 - paramCount=2 = localBase=57
[VM]   arg[0] -> stack[57] = 36
[VM]   arg[1] -> stack[58] = 3
[VM] Saving caller pc=31 before native call
[00:00:00.000] [DEBUG] pinMode(36, 3)
[VM] Restored caller pc to 31 after native call
[VM] opcode=45 operand=0
[VM] push: slot=59, val.type=1, val.value=0
[VM] push:   m_Stack[59].type=1, m_Stack[59].value=0
[VM] opcode=1 operand=8
[VM] LOAD_CONST idx=8, globalConstants.size()=45, stackTop=60
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=60, val.type=1, val.value=37
[VM] push:   m_Stack[60].type=1, m_Stack[60].value=37
[VM] LOAD_CONST done, new stackTop=61
[VM] opcode=3 operand=10
[VM] STORE_VAR: slot=10, localBase=30, localCount=2, actualSlot=40, value=37
[VM] opcode=1 operand=9
[VM] LOAD_CONST idx=9, globalConstants.size()=45, stackTop=60
[VM] LOAD_CONST entry.type=0, value.intVal=3, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 3 to stack
[VM] push: slot=60, val.type=1, val.value=3
[VM] push:   m_Stack[60].type=1, m_Stack[60].value=3
[VM] LOAD_CONST done, new stackTop=61
[VM] opcode=3 operand=11
[VM] STORE_VAR: slot=11, localBase=30, localCount=2, actualSlot=41, value=3
[VM] opcode=2 operand=10
[VM] LOAD_VAR: slot=10, localBase=30, actualSlot=40
[VM] LOAD_VAR: loaded value=37
[VM] push: slot=60, val.type=1, val.value=37
[VM] push:   m_Stack[60].type=1, m_Stack[60].value=37
[VM] opcode=2 operand=11
[VM] LOAD_VAR: slot=11, localBase=30, actualSlot=41
[VM] LOAD_VAR: loaded value=3
[VM] push: slot=61, val.type=1, val.value=3
[VM] push:   m_Stack[61].type=1, m_Stack[61].value=3
[VM] opcode=48 operand=131074
[VM] CALL_NATIVE: stringPoolIndex=2, paramCount=2, stackTop=62
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'pinMode'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=62 - paramCount=2 = localBase=60
[VM]   arg[0] -> stack[60] = 37
[VM]   arg[1] -> stack[61] = 3
[VM] Saving caller pc=39 before native call
[00:00:00.000] [DEBUG] pinMode(37, 3)
[VM] Restored caller pc to 39 after native call
[VM] opcode=45 operand=0
[VM] push: slot=62, val.type=1, val.value=0
[VM] push:   m_Stack[62].type=1, m_Stack[62].value=0
[VM] opcode=1 operand=10
[VM] LOAD_CONST idx=10, globalConstants.size()=45, stackTop=63
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=63, val.type=1, val.value=35
[VM] push:   m_Stack[63].type=1, m_Stack[63].value=35
[VM] LOAD_CONST done, new stackTop=64
[VM] opcode=3 operand=12
[VM] STORE_VAR: slot=12, localBase=30, localCount=2, actualSlot=42, value=35
[VM] opcode=1 operand=11
[VM] LOAD_CONST idx=11, globalConstants.size()=45, stackTop=63
[VM] LOAD_CONST entry.type=0, value.intVal=3, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 3 to stack
[VM] push: slot=63, val.type=1, val.value=3
[VM] push:   m_Stack[63].type=1, m_Stack[63].value=3
[VM] LOAD_CONST done, new stackTop=64
[VM] opcode=3 operand=13
[VM] STORE_VAR: slot=13, localBase=30, localCount=2, actualSlot=43, value=3
[VM] opcode=2 operand=12
[VM] LOAD_VAR: slot=12, localBase=30, actualSlot=42
[VM] LOAD_VAR: loaded value=35
[VM] push: slot=63, val.type=1, val.value=35
[VM] push:   m_Stack[63].type=1, m_Stack[63].value=35
[VM] opcode=2 operand=13
[VM] LOAD_VAR: slot=13, localBase=30, actualSlot=43
[VM] LOAD_VAR: loaded value=3
[VM] push: slot=64, val.type=1, val.value=3
[VM] push:   m_Stack[64].type=1, m_Stack[64].value=3
[VM] opcode=48 operand=131074
[VM] CALL_NATIVE: stringPoolIndex=2, paramCount=2, stackTop=65
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'pinMode'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=65 - paramCount=2 = localBase=63
[VM]   arg[0] -> stack[63] = 35
[VM]   arg[1] -> stack[64] = 3
[VM] Saving caller pc=47 before native call
[00:00:00.000] [DEBUG] pinMode(35, 3)
[VM] Restored caller pc to 47 after native call
[VM] opcode=45 operand=0
[VM] push: slot=65, val.type=1, val.value=0
[VM] push:   m_Stack[65].type=1, m_Stack[65].value=0
[VM] opcode=1 operand=12
[VM] LOAD_CONST idx=12, globalConstants.size()=45, stackTop=66
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=66, val.type=1, val.value=36
[VM] push:   m_Stack[66].type=1, m_Stack[66].value=36
[VM] LOAD_CONST done, new stackTop=67
[VM] opcode=3 operand=14
[VM] STORE_VAR: slot=14, localBase=30, localCount=2, actualSlot=44, value=36
[VM] opcode=1 operand=13
[VM] LOAD_CONST idx=13, globalConstants.size()=45, stackTop=66
[VM] LOAD_CONST entry.type=0, value.intVal=1, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 1 to stack
[VM] push: slot=66, val.type=1, val.value=1
[VM] push:   m_Stack[66].type=1, m_Stack[66].value=1
[VM] LOAD_CONST done, new stackTop=67
[VM] opcode=3 operand=15
[VM] STORE_VAR: slot=15, localBase=30, localCount=2, actualSlot=45, value=1
[VM] opcode=2 operand=14
[VM] LOAD_VAR: slot=14, localBase=30, actualSlot=44
[VM] LOAD_VAR: loaded value=36
[VM] push: slot=66, val.type=1, val.value=36
[VM] push:   m_Stack[66].type=1, m_Stack[66].value=36
[VM] opcode=2 operand=15
[VM] LOAD_VAR: slot=15, localBase=30, actualSlot=45
[VM] LOAD_VAR: loaded value=1
[VM] push: slot=67, val.type=1, val.value=1
[VM] push:   m_Stack[67].type=1, m_Stack[67].value=1
[VM] opcode=48 operand=131075
[VM] CALL_NATIVE: stringPoolIndex=3, paramCount=2, stackTop=68
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'digitalWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=68 - paramCount=2 = localBase=66
[VM]   arg[0] -> stack[66] = 36
[VM]   arg[1] -> stack[67] = 1
[VM] Saving caller pc=55 before native call
[00:00:00.000] [DEBUG] digitalWrite(36, 1)
[VM] Restored caller pc to 55 after native call
[VM] opcode=45 operand=0
[VM] push: slot=68, val.type=1, val.value=0
[VM] push:   m_Stack[68].type=1, m_Stack[68].value=0
[VM] opcode=1 operand=14
[VM] LOAD_CONST idx=14, globalConstants.size()=45, stackTop=69
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=69, val.type=1, val.value=37
[VM] push:   m_Stack[69].type=1, m_Stack[69].value=37
[VM] LOAD_CONST done, new stackTop=70
[VM] opcode=3 operand=16
[VM] STORE_VAR: slot=16, localBase=30, localCount=2, actualSlot=46, value=37
[VM] opcode=1 operand=15
[VM] LOAD_CONST idx=15, globalConstants.size()=45, stackTop=69
[VM] LOAD_CONST entry.type=0, value.intVal=1, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 1 to stack
[VM] push: slot=69, val.type=1, val.value=1
[VM] push:   m_Stack[69].type=1, m_Stack[69].value=1
[VM] LOAD_CONST done, new stackTop=70
[VM] opcode=3 operand=17
[VM] STORE_VAR: slot=17, localBase=30, localCount=2, actualSlot=47, value=1
[VM] opcode=2 operand=16
[VM] LOAD_VAR: slot=16, localBase=30, actualSlot=46
[VM] LOAD_VAR: loaded value=37
[VM] push: slot=69, val.type=1, val.value=37
[VM] push:   m_Stack[69].type=1, m_Stack[69].value=37
[VM] opcode=2 operand=17
[VM] LOAD_VAR: slot=17, localBase=30, actualSlot=47
[VM] LOAD_VAR: loaded value=1
[VM] push: slot=70, val.type=1, val.value=1
[VM] push:   m_Stack[70].type=1, m_Stack[70].value=1
[VM] opcode=48 operand=131075
[VM] CALL_NATIVE: stringPoolIndex=3, paramCount=2, stackTop=71
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'digitalWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=71 - paramCount=2 = localBase=69
[VM]   arg[0] -> stack[69] = 37
[VM]   arg[1] -> stack[70] = 1
[VM] Saving caller pc=63 before native call
[00:00:00.000] [DEBUG] digitalWrite(37, 1)
[VM] Restored caller pc to 63 after native call
[VM] opcode=45 operand=0
[VM] push: slot=71, val.type=1, val.value=0
[VM] push:   m_Stack[71].type=1, m_Stack[71].value=0
[VM] opcode=1 operand=16
[VM] LOAD_CONST idx=16, globalConstants.size()=45, stackTop=72
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=72, val.type=1, val.value=35
[VM] push:   m_Stack[72].type=1, m_Stack[72].value=35
[VM] LOAD_CONST done, new stackTop=73
[VM] opcode=3 operand=18
[VM] STORE_VAR: slot=18, localBase=30, localCount=2, actualSlot=48, value=35
[VM] opcode=1 operand=17
[VM] LOAD_CONST idx=17, globalConstants.size()=45, stackTop=72
[VM] LOAD_CONST entry.type=0, value.intVal=1, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 1 to stack
[VM] push: slot=72, val.type=1, val.value=1
[VM] push:   m_Stack[72].type=1, m_Stack[72].value=1
[VM] LOAD_CONST done, new stackTop=73
[VM] opcode=3 operand=19
[VM] STORE_VAR: slot=19, localBase=30, localCount=2, actualSlot=49, value=1
[VM] opcode=2 operand=18
[VM] LOAD_VAR: slot=18, localBase=30, actualSlot=48
[VM] LOAD_VAR: loaded value=35
[VM] push: slot=72, val.type=1, val.value=35
[VM] push:   m_Stack[72].type=1, m_Stack[72].value=35
[VM] opcode=2 operand=19
[VM] LOAD_VAR: slot=19, localBase=30, actualSlot=49
[VM] LOAD_VAR: loaded value=1
[VM] push: slot=73, val.type=1, val.value=1
[VM] push:   m_Stack[73].type=1, m_Stack[73].value=1
[VM] opcode=48 operand=131075
[VM] CALL_NATIVE: stringPoolIndex=3, paramCount=2, stackTop=74
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=0 [6]=0 [7]=0 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'digitalWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=74 - paramCount=2 = localBase=72
[VM]   arg[0] -> stack[72] = 35
[VM]   arg[1] -> stack[73] = 1
[VM] Saving caller pc=71 before native call
[00:00:00.000] [DEBUG] digitalWrite(35, 1)
[VM] Restored caller pc to 71 after native call
[VM] opcode=45 operand=0
[VM] push: slot=74, val.type=1, val.value=0
[VM] push:   m_Stack[74].type=1, m_Stack[74].value=0
[VM] RETURN
[VM] opcode=45 operand=0
[VM] push: slot=74, val.type=1, val.value=0
[VM] push:   m_Stack[74].type=1, m_Stack[74].value=0
[VM] opcode=1 operand=26
[VM] LOAD_CONST idx=26, globalConstants.size()=45, stackTop=75
[VM] LOAD_CONST entry.type=2, value.intVal=7, value.doubleVal=0.000000
[VM] push: slot=75, val.type=3, val.value=7
[VM] push:   m_Stack[75].type=3, m_Stack[75].value=7
[VM] LOAD_CONST done, new stackTop=76
[VM] opcode=3 operand=5
[VM] STORE_VAR: slot=5, localBase=0, localCount=0, actualSlot=5, value=7
[VM] opcode=2 operand=5
[VM] LOAD_VAR: slot=5, localBase=0, actualSlot=5
[VM] LOAD_VAR: loaded value=7
[VM] push: slot=75, val.type=3, val.value=7
[VM] push:   m_Stack[75].type=3, m_Stack[75].value=7
[VM] opcode=3 operand=6
[VM] STORE_VAR: slot=6, localBase=0, localCount=0, actualSlot=6, value=7
[VM] opcode=1 operand=27
[VM] LOAD_CONST idx=27, globalConstants.size()=45, stackTop=75
[VM] LOAD_CONST entry.type=0, value.intVal=888, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 888 to stack
[VM] push: slot=75, val.type=1, val.value=888
[VM] push:   m_Stack[75].type=1, m_Stack[75].value=888
[VM] LOAD_CONST done, new stackTop=76
[VM] opcode=3 operand=7
[VM] STORE_VAR: slot=7, localBase=0, localCount=0, actualSlot=7, value=888
[VM] opcode=2 operand=6
[VM] LOAD_VAR: slot=6, localBase=0, actualSlot=6
[VM] LOAD_VAR: loaded value=7
[VM] push: slot=75, val.type=3, val.value=7
[VM] push:   m_Stack[75].type=3, m_Stack[75].value=7
[VM] opcode=2 operand=7
[VM] LOAD_VAR: slot=7, localBase=0, actualSlot=7
[VM] LOAD_VAR: loaded value=888
[VM] push: slot=76, val.type=1, val.value=888
[VM] push:   m_Stack[76].type=1, m_Stack[76].value=888
[VM] opcode=48 operand=131080
[VM] CALL_NATIVE: stringPoolIndex=8, paramCount=2, stackTop=77
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=0 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'printf'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=77 - paramCount=2 = localBase=75
[VM]   arg[0] -> stack[75] = 7
[VM]   arg[1] -> stack[76] = 888
[VM] Saving caller pc=21 before native call
888[VM] Restored caller pc to 21 after native call
[VM] opcode=45 operand=0
[VM] push: slot=77, val.type=1, val.value=0
[VM] push:   m_Stack[77].type=1, m_Stack[77].value=0
[VM] opcode=1 operand=28
[VM] LOAD_CONST idx=28, globalConstants.size()=45, stackTop=78
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=78, val.type=1, val.value=255
[VM] push:   m_Stack[78].type=1, m_Stack[78].value=255
[VM] LOAD_CONST done, new stackTop=79
[VM] opcode=3 operand=8
[VM] STORE_VAR: slot=8, localBase=0, localCount=0, actualSlot=8, value=255
[VM] opcode=1 operand=29
[VM] LOAD_CONST idx=29, globalConstants.size()=45, stackTop=78
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=78, val.type=1, val.value=0
[VM] push:   m_Stack[78].type=1, m_Stack[78].value=0
[VM] LOAD_CONST done, new stackTop=79
[VM] opcode=3 operand=9
[VM] STORE_VAR: slot=9, localBase=0, localCount=0, actualSlot=9, value=0
[VM] opcode=1 operand=30
[VM] LOAD_CONST idx=30, globalConstants.size()=45, stackTop=78
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=78, val.type=1, val.value=0
[VM] push:   m_Stack[78].type=1, m_Stack[78].value=0
[VM] LOAD_CONST done, new stackTop=79
[VM] opcode=3 operand=10
[VM] STORE_VAR: slot=10, localBase=0, localCount=0, actualSlot=10, value=0
[VM] opcode=2 operand=8
[VM] LOAD_VAR: slot=8, localBase=0, actualSlot=8
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=78, val.type=1, val.value=255
[VM] push:   m_Stack[78].type=1, m_Stack[78].value=255
[VM] opcode=2 operand=9
[VM] LOAD_VAR: slot=9, localBase=0, actualSlot=9
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=79, val.type=1, val.value=0
[VM] push:   m_Stack[79].type=1, m_Stack[79].value=0
[VM] opcode=2 operand=10
[VM] LOAD_VAR: slot=10, localBase=0, actualSlot=10
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=80, val.type=1, val.value=0
[VM] push:   m_Stack[80].type=1, m_Stack[80].value=0
[VM] opcode=32 operand=196609
[VM] CALL: funcIndex=1, paramCount=3, stackTop=81
[VM] CALL: Stack before call: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 [16]=0 [17]=0 [18]=0 [19]=0 
[VM] callFunction: funcIndex=1, paramCount=3, localCount=12, funcParamCount=3
[VM] push: slot=81, val.type=1, val.value=0
[VM] push:   m_Stack[81].type=1, m_Stack[81].value=0
[VM] push: slot=82, val.type=1, val.value=0
[VM] push:   m_Stack[82].type=1, m_Stack[82].value=0
[VM] push: slot=83, val.type=1, val.value=0
[VM] push:   m_Stack[83].type=1, m_Stack[83].value=0
[VM] push: slot=84, val.type=1, val.value=0
[VM] push:   m_Stack[84].type=1, m_Stack[84].value=0
[VM] push: slot=85, val.type=1, val.value=0
[VM] push:   m_Stack[85].type=1, m_Stack[85].value=0
[VM] push: slot=86, val.type=1, val.value=0
[VM] push:   m_Stack[86].type=1, m_Stack[86].value=0
[VM] push: slot=87, val.type=1, val.value=0
[VM] push:   m_Stack[87].type=1, m_Stack[87].value=0
[VM] push: slot=88, val.type=1, val.value=0
[VM] push:   m_Stack[88].type=1, m_Stack[88].value=0
[VM] push: slot=89, val.type=1, val.value=0
[VM] push:   m_Stack[89].type=1, m_Stack[89].value=0
[VM] callFunction: After push locals, stackTop=90
[VM] callFunction: localBase=78
[VM] CALL: After setup frame, localBase=78
[VM] opcode=1 operand=18
[VM] LOAD_CONST idx=18, globalConstants.size()=45, stackTop=90
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=90, val.type=1, val.value=36
[VM] push:   m_Stack[90].type=1, m_Stack[90].value=36
[VM] LOAD_CONST done, new stackTop=91
[VM] opcode=3 operand=3
[VM] STORE_VAR: slot=3, localBase=78, localCount=3, actualSlot=81, value=36
[VM] opcode=1 operand=19
[VM] LOAD_CONST idx=19, globalConstants.size()=45, stackTop=90
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=90, val.type=1, val.value=255
[VM] push:   m_Stack[90].type=1, m_Stack[90].value=255
[VM] LOAD_CONST done, new stackTop=91
[VM] opcode=2 operand=0
[VM] LOAD_VAR: slot=0, localBase=78, actualSlot=78
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=91, val.type=1, val.value=255
[VM] push:   m_Stack[91].type=1, m_Stack[91].value=255
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=255, result=0
[VM] push: slot=90, val.type=1, val.value=0
[VM] push:   m_Stack[90].type=1, m_Stack[90].value=0
[VM] opcode=3 operand=4
[VM] STORE_VAR: slot=4, localBase=78, localCount=3, actualSlot=82, value=0
[VM] opcode=2 operand=4
[VM] LOAD_VAR: slot=4, localBase=78, actualSlot=82
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=90, val.type=1, val.value=0
[VM] push:   m_Stack[90].type=1, m_Stack[90].value=0
[VM] opcode=3 operand=5
[VM] STORE_VAR: slot=5, localBase=78, localCount=3, actualSlot=83, value=0
[VM] opcode=2 operand=3
[VM] LOAD_VAR: slot=3, localBase=78, actualSlot=81
[VM] LOAD_VAR: loaded value=36
[VM] push: slot=90, val.type=1, val.value=36
[VM] push:   m_Stack[90].type=1, m_Stack[90].value=36
[VM] opcode=2 operand=5
[VM] LOAD_VAR: slot=5, localBase=78, actualSlot=83
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=91, val.type=1, val.value=0
[VM] push:   m_Stack[91].type=1, m_Stack[91].value=0
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=92
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=92 - paramCount=2 = localBase=90
[VM]   arg[0] -> stack[90] = 36
[VM]   arg[1] -> stack[91] = 0
[VM] Saving caller pc=11 before native call
[00:00:00.000] [DEBUG] analogWrite(36, 0)
[VM] Restored caller pc to 11 after native call
[VM] opcode=45 operand=0
[VM] push: slot=92, val.type=1, val.value=0
[VM] push:   m_Stack[92].type=1, m_Stack[92].value=0
[VM] opcode=1 operand=20
[VM] LOAD_CONST idx=20, globalConstants.size()=45, stackTop=93
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=93, val.type=1, val.value=37
[VM] push:   m_Stack[93].type=1, m_Stack[93].value=37
[VM] LOAD_CONST done, new stackTop=94
[VM] opcode=3 operand=6
[VM] STORE_VAR: slot=6, localBase=78, localCount=3, actualSlot=84, value=37
[VM] opcode=1 operand=21
[VM] LOAD_CONST idx=21, globalConstants.size()=45, stackTop=93
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=93, val.type=1, val.value=255
[VM] push:   m_Stack[93].type=1, m_Stack[93].value=255
[VM] LOAD_CONST done, new stackTop=94
[VM] opcode=2 operand=1
[VM] LOAD_VAR: slot=1, localBase=78, actualSlot=79
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=94, val.type=1, val.value=0
[VM] push:   m_Stack[94].type=1, m_Stack[94].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=93, val.type=1, val.value=255
[VM] push:   m_Stack[93].type=1, m_Stack[93].value=255
[VM] opcode=3 operand=7
[VM] STORE_VAR: slot=7, localBase=78, localCount=3, actualSlot=85, value=255
[VM] opcode=2 operand=7
[VM] LOAD_VAR: slot=7, localBase=78, actualSlot=85
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=93, val.type=1, val.value=255
[VM] push:   m_Stack[93].type=1, m_Stack[93].value=255
[VM] opcode=3 operand=8
[VM] STORE_VAR: slot=8, localBase=78, localCount=3, actualSlot=86, value=255
[VM] opcode=2 operand=6
[VM] LOAD_VAR: slot=6, localBase=78, actualSlot=84
[VM] LOAD_VAR: loaded value=37
[VM] push: slot=93, val.type=1, val.value=37
[VM] push:   m_Stack[93].type=1, m_Stack[93].value=37
[VM] opcode=2 operand=8
[VM] LOAD_VAR: slot=8, localBase=78, actualSlot=86
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=94, val.type=1, val.value=255
[VM] push:   m_Stack[94].type=1, m_Stack[94].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=95
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=95 - paramCount=2 = localBase=93
[VM]   arg[0] -> stack[93] = 37
[VM]   arg[1] -> stack[94] = 255
[VM] Saving caller pc=23 before native call
[00:00:00.000] [DEBUG] analogWrite(37, 255)
[VM] Restored caller pc to 23 after native call
[VM] opcode=45 operand=0
[VM] push: slot=95, val.type=1, val.value=0
[VM] push:   m_Stack[95].type=1, m_Stack[95].value=0
[VM] opcode=1 operand=22
[VM] LOAD_CONST idx=22, globalConstants.size()=45, stackTop=96
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=96, val.type=1, val.value=35
[VM] push:   m_Stack[96].type=1, m_Stack[96].value=35
[VM] LOAD_CONST done, new stackTop=97
[VM] opcode=3 operand=9
[VM] STORE_VAR: slot=9, localBase=78, localCount=3, actualSlot=87, value=35
[VM] opcode=1 operand=23
[VM] LOAD_CONST idx=23, globalConstants.size()=45, stackTop=96
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=96, val.type=1, val.value=255
[VM] push:   m_Stack[96].type=1, m_Stack[96].value=255
[VM] LOAD_CONST done, new stackTop=97
[VM] opcode=2 operand=2
[VM] LOAD_VAR: slot=2, localBase=78, actualSlot=80
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=97, val.type=1, val.value=0
[VM] push:   m_Stack[97].type=1, m_Stack[97].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=96, val.type=1, val.value=255
[VM] push:   m_Stack[96].type=1, m_Stack[96].value=255
[VM] opcode=3 operand=10
[VM] STORE_VAR: slot=10, localBase=78, localCount=3, actualSlot=88, value=255
[VM] opcode=2 operand=10
[VM] LOAD_VAR: slot=10, localBase=78, actualSlot=88
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=96, val.type=1, val.value=255
[VM] push:   m_Stack[96].type=1, m_Stack[96].value=255
[VM] opcode=3 operand=11
[VM] STORE_VAR: slot=11, localBase=78, localCount=3, actualSlot=89, value=255
[VM] opcode=2 operand=9
[VM] LOAD_VAR: slot=9, localBase=78, actualSlot=87
[VM] LOAD_VAR: loaded value=35
[VM] push: slot=96, val.type=1, val.value=35
[VM] push:   m_Stack[96].type=1, m_Stack[96].value=35
[VM] opcode=2 operand=11
[VM] LOAD_VAR: slot=11, localBase=78, actualSlot=89
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=97, val.type=1, val.value=255
[VM] push:   m_Stack[97].type=1, m_Stack[97].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=98
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=0 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=98 - paramCount=2 = localBase=96
[VM]   arg[0] -> stack[96] = 35
[VM]   arg[1] -> stack[97] = 255
[VM] Saving caller pc=35 before native call
[00:00:00.000] [DEBUG] analogWrite(35, 255)
[VM] Restored caller pc to 35 after native call
[VM] opcode=45 operand=0
[VM] push: slot=98, val.type=1, val.value=0
[VM] push:   m_Stack[98].type=1, m_Stack[98].value=0
[VM] RETURN
[VM] opcode=45 operand=0
[VM] push: slot=98, val.type=1, val.value=0
[VM] push:   m_Stack[98].type=1, m_Stack[98].value=0
[VM] opcode=1 operand=31
[VM] LOAD_CONST idx=31, globalConstants.size()=45, stackTop=99
[VM] LOAD_CONST entry.type=0, value.intVal=2000, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 2000 to stack
[VM] push: slot=99, val.type=1, val.value=2000
[VM] push:   m_Stack[99].type=1, m_Stack[99].value=2000
[VM] LOAD_CONST done, new stackTop=100
[VM] opcode=3 operand=12
[VM] STORE_VAR: slot=12, localBase=0, localCount=0, actualSlot=12, value=2000
[VM] opcode=2 operand=12
[VM] LOAD_VAR: slot=12, localBase=0, actualSlot=12
[VM] LOAD_VAR: loaded value=2000
[VM] push: slot=99, val.type=1, val.value=2000
[VM] push:   m_Stack[99].type=1, m_Stack[99].value=2000
[VM] opcode=48 operand=65545
[VM] CALL_NATIVE: stringPoolIndex=9, paramCount=1, stackTop=100
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=0 [15]=0 
[VM] Calling native function: 'delay'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=100 - paramCount=1 = localBase=99
[VM]   arg[0] -> stack[99] = 2000
[VM] Saving caller pc=37 before native call
[VM] Restored caller pc to 37 after native call
[VM] opcode=45 operand=0
[VM] push: slot=100, val.type=1, val.value=0
[VM] push:   m_Stack[100].type=1, m_Stack[100].value=0
[VM] opcode=1 operand=32
[VM] LOAD_CONST idx=32, globalConstants.size()=45, stackTop=101
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=101, val.type=1, val.value=0
[VM] push:   m_Stack[101].type=1, m_Stack[101].value=0
[VM] LOAD_CONST done, new stackTop=102
[VM] opcode=3 operand=13
[VM] STORE_VAR: slot=13, localBase=0, localCount=0, actualSlot=13, value=0
[VM] opcode=1 operand=33
[VM] LOAD_CONST idx=33, globalConstants.size()=45, stackTop=101
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=101, val.type=1, val.value=255
[VM] push:   m_Stack[101].type=1, m_Stack[101].value=255
[VM] LOAD_CONST done, new stackTop=102
[VM] opcode=3 operand=14
[VM] STORE_VAR: slot=14, localBase=0, localCount=0, actualSlot=14, value=255
[VM] opcode=1 operand=34
[VM] LOAD_CONST idx=34, globalConstants.size()=45, stackTop=101
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=101, val.type=1, val.value=0
[VM] push:   m_Stack[101].type=1, m_Stack[101].value=0
[VM] LOAD_CONST done, new stackTop=102
[VM] opcode=3 operand=15
[VM] STORE_VAR: slot=15, localBase=0, localCount=0, actualSlot=15, value=0
[VM] opcode=2 operand=13
[VM] LOAD_VAR: slot=13, localBase=0, actualSlot=13
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=101, val.type=1, val.value=0
[VM] push:   m_Stack[101].type=1, m_Stack[101].value=0
[VM] opcode=2 operand=14
[VM] LOAD_VAR: slot=14, localBase=0, actualSlot=14
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=102, val.type=1, val.value=255
[VM] push:   m_Stack[102].type=1, m_Stack[102].value=255
[VM] opcode=2 operand=15
[VM] LOAD_VAR: slot=15, localBase=0, actualSlot=15
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=103, val.type=1, val.value=0
[VM] push:   m_Stack[103].type=1, m_Stack[103].value=0
[VM] opcode=32 operand=196609
[VM] CALL: funcIndex=1, paramCount=3, stackTop=104
[VM] CALL: Stack before call: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 [16]=0 [17]=0 [18]=0 [19]=0 
[VM] callFunction: funcIndex=1, paramCount=3, localCount=12, funcParamCount=3
[VM] push: slot=104, val.type=1, val.value=0
[VM] push:   m_Stack[104].type=1, m_Stack[104].value=0
[VM] push: slot=105, val.type=1, val.value=0
[VM] push:   m_Stack[105].type=1, m_Stack[105].value=0
[VM] push: slot=106, val.type=1, val.value=0
[VM] push:   m_Stack[106].type=1, m_Stack[106].value=0
[VM] push: slot=107, val.type=1, val.value=0
[VM] push:   m_Stack[107].type=1, m_Stack[107].value=0
[VM] push: slot=108, val.type=1, val.value=0
[VM] push:   m_Stack[108].type=1, m_Stack[108].value=0
[VM] push: slot=109, val.type=1, val.value=0
[VM] push:   m_Stack[109].type=1, m_Stack[109].value=0
[VM] push: slot=110, val.type=1, val.value=0
[VM] push:   m_Stack[110].type=1, m_Stack[110].value=0
[VM] push: slot=111, val.type=1, val.value=0
[VM] push:   m_Stack[111].type=1, m_Stack[111].value=0
[VM] push: slot=112, val.type=1, val.value=0
[VM] push:   m_Stack[112].type=1, m_Stack[112].value=0
[VM] callFunction: After push locals, stackTop=113
[VM] callFunction: localBase=101
[VM] CALL: After setup frame, localBase=101
[VM] opcode=1 operand=18
[VM] LOAD_CONST idx=18, globalConstants.size()=45, stackTop=113
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=113, val.type=1, val.value=36
[VM] push:   m_Stack[113].type=1, m_Stack[113].value=36
[VM] LOAD_CONST done, new stackTop=114
[VM] opcode=3 operand=3
[VM] STORE_VAR: slot=3, localBase=101, localCount=3, actualSlot=104, value=36
[VM] opcode=1 operand=19
[VM] LOAD_CONST idx=19, globalConstants.size()=45, stackTop=113
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=113, val.type=1, val.value=255
[VM] push:   m_Stack[113].type=1, m_Stack[113].value=255
[VM] LOAD_CONST done, new stackTop=114
[VM] opcode=2 operand=0
[VM] LOAD_VAR: slot=0, localBase=101, actualSlot=101
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=114, val.type=1, val.value=0
[VM] push:   m_Stack[114].type=1, m_Stack[114].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=113, val.type=1, val.value=255
[VM] push:   m_Stack[113].type=1, m_Stack[113].value=255
[VM] opcode=3 operand=4
[VM] STORE_VAR: slot=4, localBase=101, localCount=3, actualSlot=105, value=255
[VM] opcode=2 operand=4
[VM] LOAD_VAR: slot=4, localBase=101, actualSlot=105
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=113, val.type=1, val.value=255
[VM] push:   m_Stack[113].type=1, m_Stack[113].value=255
[VM] opcode=3 operand=5
[VM] STORE_VAR: slot=5, localBase=101, localCount=3, actualSlot=106, value=255
[VM] opcode=2 operand=3
[VM] LOAD_VAR: slot=3, localBase=101, actualSlot=104
[VM] LOAD_VAR: loaded value=36
[VM] push: slot=113, val.type=1, val.value=36
[VM] push:   m_Stack[113].type=1, m_Stack[113].value=36
[VM] opcode=2 operand=5
[VM] LOAD_VAR: slot=5, localBase=101, actualSlot=106
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=114, val.type=1, val.value=255
[VM] push:   m_Stack[114].type=1, m_Stack[114].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=115
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=115 - paramCount=2 = localBase=113
[VM]   arg[0] -> stack[113] = 36
[VM]   arg[1] -> stack[114] = 255
[VM] Saving caller pc=11 before native call
[00:00:02.000] [DEBUG] analogWrite(36, 255)
[VM] Restored caller pc to 11 after native call
[VM] opcode=45 operand=0
[VM] push: slot=115, val.type=1, val.value=0
[VM] push:   m_Stack[115].type=1, m_Stack[115].value=0
[VM] opcode=1 operand=20
[VM] LOAD_CONST idx=20, globalConstants.size()=45, stackTop=116
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=116, val.type=1, val.value=37
[VM] push:   m_Stack[116].type=1, m_Stack[116].value=37
[VM] LOAD_CONST done, new stackTop=117
[VM] opcode=3 operand=6
[VM] STORE_VAR: slot=6, localBase=101, localCount=3, actualSlot=107, value=37
[VM] opcode=1 operand=21
[VM] LOAD_CONST idx=21, globalConstants.size()=45, stackTop=116
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=116, val.type=1, val.value=255
[VM] push:   m_Stack[116].type=1, m_Stack[116].value=255
[VM] LOAD_CONST done, new stackTop=117
[VM] opcode=2 operand=1
[VM] LOAD_VAR: slot=1, localBase=101, actualSlot=102
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=117, val.type=1, val.value=255
[VM] push:   m_Stack[117].type=1, m_Stack[117].value=255
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=255, result=0
[VM] push: slot=116, val.type=1, val.value=0
[VM] push:   m_Stack[116].type=1, m_Stack[116].value=0
[VM] opcode=3 operand=7
[VM] STORE_VAR: slot=7, localBase=101, localCount=3, actualSlot=108, value=0
[VM] opcode=2 operand=7
[VM] LOAD_VAR: slot=7, localBase=101, actualSlot=108
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=116, val.type=1, val.value=0
[VM] push:   m_Stack[116].type=1, m_Stack[116].value=0
[VM] opcode=3 operand=8
[VM] STORE_VAR: slot=8, localBase=101, localCount=3, actualSlot=109, value=0
[VM] opcode=2 operand=6
[VM] LOAD_VAR: slot=6, localBase=101, actualSlot=107
[VM] LOAD_VAR: loaded value=37
[VM] push: slot=116, val.type=1, val.value=37
[VM] push:   m_Stack[116].type=1, m_Stack[116].value=37
[VM] opcode=2 operand=8
[VM] LOAD_VAR: slot=8, localBase=101, actualSlot=109
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=117, val.type=1, val.value=0
[VM] push:   m_Stack[117].type=1, m_Stack[117].value=0
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=118
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=118 - paramCount=2 = localBase=116
[VM]   arg[0] -> stack[116] = 37
[VM]   arg[1] -> stack[117] = 0
[VM] Saving caller pc=23 before native call
[00:00:02.000] [DEBUG] analogWrite(37, 0)
[VM] Restored caller pc to 23 after native call
[VM] opcode=45 operand=0
[VM] push: slot=118, val.type=1, val.value=0
[VM] push:   m_Stack[118].type=1, m_Stack[118].value=0
[VM] opcode=1 operand=22
[VM] LOAD_CONST idx=22, globalConstants.size()=45, stackTop=119
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=119, val.type=1, val.value=35
[VM] push:   m_Stack[119].type=1, m_Stack[119].value=35
[VM] LOAD_CONST done, new stackTop=120
[VM] opcode=3 operand=9
[VM] STORE_VAR: slot=9, localBase=101, localCount=3, actualSlot=110, value=35
[VM] opcode=1 operand=23
[VM] LOAD_CONST idx=23, globalConstants.size()=45, stackTop=119
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=119, val.type=1, val.value=255
[VM] push:   m_Stack[119].type=1, m_Stack[119].value=255
[VM] LOAD_CONST done, new stackTop=120
[VM] opcode=2 operand=2
[VM] LOAD_VAR: slot=2, localBase=101, actualSlot=103
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=120, val.type=1, val.value=0
[VM] push:   m_Stack[120].type=1, m_Stack[120].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=119, val.type=1, val.value=255
[VM] push:   m_Stack[119].type=1, m_Stack[119].value=255
[VM] opcode=3 operand=10
[VM] STORE_VAR: slot=10, localBase=101, localCount=3, actualSlot=111, value=255
[VM] opcode=2 operand=10
[VM] LOAD_VAR: slot=10, localBase=101, actualSlot=111
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=119, val.type=1, val.value=255
[VM] push:   m_Stack[119].type=1, m_Stack[119].value=255
[VM] opcode=3 operand=11
[VM] STORE_VAR: slot=11, localBase=101, localCount=3, actualSlot=112, value=255
[VM] opcode=2 operand=9
[VM] LOAD_VAR: slot=9, localBase=101, actualSlot=110
[VM] LOAD_VAR: loaded value=35
[VM] push: slot=119, val.type=1, val.value=35
[VM] push:   m_Stack[119].type=1, m_Stack[119].value=35
[VM] opcode=2 operand=11
[VM] LOAD_VAR: slot=11, localBase=101, actualSlot=112
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=120, val.type=1, val.value=255
[VM] push:   m_Stack[120].type=1, m_Stack[120].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=121
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=121 - paramCount=2 = localBase=119
[VM]   arg[0] -> stack[119] = 35
[VM]   arg[1] -> stack[120] = 255
[VM] Saving caller pc=35 before native call
[00:00:02.000] [DEBUG] analogWrite(35, 255)
[VM] Restored caller pc to 35 after native call
[VM] opcode=45 operand=0
[VM] push: slot=121, val.type=1, val.value=0
[VM] push:   m_Stack[121].type=1, m_Stack[121].value=0
[VM] RETURN
[VM] opcode=45 operand=0
[VM] push: slot=121, val.type=1, val.value=0
[VM] push:   m_Stack[121].type=1, m_Stack[121].value=0
[VM] opcode=1 operand=35
[VM] LOAD_CONST idx=35, globalConstants.size()=45, stackTop=122
[VM] LOAD_CONST entry.type=0, value.intVal=2000, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 2000 to stack
[VM] push: slot=122, val.type=1, val.value=2000
[VM] push:   m_Stack[122].type=1, m_Stack[122].value=2000
[VM] LOAD_CONST done, new stackTop=123
[VM] opcode=3 operand=16
[VM] STORE_VAR: slot=16, localBase=0, localCount=0, actualSlot=16, value=2000
[VM] opcode=2 operand=16
[VM] LOAD_VAR: slot=16, localBase=0, actualSlot=16
[VM] LOAD_VAR: loaded value=2000
[VM] push: slot=122, val.type=1, val.value=2000
[VM] push:   m_Stack[122].type=1, m_Stack[122].value=2000
[VM] opcode=48 operand=65545
[VM] CALL_NATIVE: stringPoolIndex=9, paramCount=1, stackTop=123
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'delay'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=123 - paramCount=1 = localBase=122
[VM]   arg[0] -> stack[122] = 2000
[VM] Saving caller pc=53 before native call
[VM] Restored caller pc to 53 after native call
[VM] opcode=45 operand=0
[VM] push: slot=123, val.type=1, val.value=0
[VM] push:   m_Stack[123].type=1, m_Stack[123].value=0
[VM] opcode=1 operand=36
[VM] LOAD_CONST idx=36, globalConstants.size()=45, stackTop=124
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=124, val.type=1, val.value=0
[VM] push:   m_Stack[124].type=1, m_Stack[124].value=0
[VM] LOAD_CONST done, new stackTop=125
[VM] opcode=3 operand=17
[VM] STORE_VAR: slot=17, localBase=0, localCount=0, actualSlot=17, value=0
[VM] opcode=1 operand=37
[VM] LOAD_CONST idx=37, globalConstants.size()=45, stackTop=124
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=124, val.type=1, val.value=0
[VM] push:   m_Stack[124].type=1, m_Stack[124].value=0
[VM] LOAD_CONST done, new stackTop=125
[VM] opcode=3 operand=18
[VM] STORE_VAR: slot=18, localBase=0, localCount=0, actualSlot=18, value=0
[VM] opcode=1 operand=38
[VM] LOAD_CONST idx=38, globalConstants.size()=45, stackTop=124
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=124, val.type=1, val.value=255
[VM] push:   m_Stack[124].type=1, m_Stack[124].value=255
[VM] LOAD_CONST done, new stackTop=125
[VM] opcode=3 operand=19
[VM] STORE_VAR: slot=19, localBase=0, localCount=0, actualSlot=19, value=255
[VM] opcode=2 operand=17
[VM] LOAD_VAR: slot=17, localBase=0, actualSlot=17
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=124, val.type=1, val.value=0
[VM] push:   m_Stack[124].type=1, m_Stack[124].value=0
[VM] opcode=2 operand=18
[VM] LOAD_VAR: slot=18, localBase=0, actualSlot=18
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=125, val.type=1, val.value=0
[VM] push:   m_Stack[125].type=1, m_Stack[125].value=0
[VM] opcode=2 operand=19
[VM] LOAD_VAR: slot=19, localBase=0, actualSlot=19
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=126, val.type=1, val.value=255
[VM] push:   m_Stack[126].type=1, m_Stack[126].value=255
[VM] opcode=32 operand=196609
[VM] CALL: funcIndex=1, paramCount=3, stackTop=127
[VM] CALL: Stack before call: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 [16]=2000 [17]=0 [18]=0 [19]=255 
[VM] callFunction: funcIndex=1, paramCount=3, localCount=12, funcParamCount=3
[VM] push: slot=127, val.type=1, val.value=0
[VM] push:   m_Stack[127].type=1, m_Stack[127].value=0
[VM] push: slot=128, val.type=1, val.value=0
[VM] push:   m_Stack[128].type=1, m_Stack[128].value=0
[VM] push: slot=129, val.type=1, val.value=0
[VM] push:   m_Stack[129].type=1, m_Stack[129].value=0
[VM] push: slot=130, val.type=1, val.value=0
[VM] push:   m_Stack[130].type=1, m_Stack[130].value=0
[VM] push: slot=131, val.type=1, val.value=0
[VM] push:   m_Stack[131].type=1, m_Stack[131].value=0
[VM] push: slot=132, val.type=1, val.value=0
[VM] push:   m_Stack[132].type=1, m_Stack[132].value=0
[VM] push: slot=133, val.type=1, val.value=0
[VM] push:   m_Stack[133].type=1, m_Stack[133].value=0
[VM] push: slot=134, val.type=1, val.value=0
[VM] push:   m_Stack[134].type=1, m_Stack[134].value=0
[VM] push: slot=135, val.type=1, val.value=0
[VM] push:   m_Stack[135].type=1, m_Stack[135].value=0
[VM] callFunction: After push locals, stackTop=136
[VM] callFunction: localBase=124
[VM] CALL: After setup frame, localBase=124
[VM] opcode=1 operand=18
[VM] LOAD_CONST idx=18, globalConstants.size()=45, stackTop=136
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=136, val.type=1, val.value=36
[VM] push:   m_Stack[136].type=1, m_Stack[136].value=36
[VM] LOAD_CONST done, new stackTop=137
[VM] opcode=3 operand=3
[VM] STORE_VAR: slot=3, localBase=124, localCount=3, actualSlot=127, value=36
[VM] opcode=1 operand=19
[VM] LOAD_CONST idx=19, globalConstants.size()=45, stackTop=136
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=136, val.type=1, val.value=255
[VM] push:   m_Stack[136].type=1, m_Stack[136].value=255
[VM] LOAD_CONST done, new stackTop=137
[VM] opcode=2 operand=0
[VM] LOAD_VAR: slot=0, localBase=124, actualSlot=124
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=137, val.type=1, val.value=0
[VM] push:   m_Stack[137].type=1, m_Stack[137].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=136, val.type=1, val.value=255
[VM] push:   m_Stack[136].type=1, m_Stack[136].value=255
[VM] opcode=3 operand=4
[VM] STORE_VAR: slot=4, localBase=124, localCount=3, actualSlot=128, value=255
[VM] opcode=2 operand=4
[VM] LOAD_VAR: slot=4, localBase=124, actualSlot=128
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=136, val.type=1, val.value=255
[VM] push:   m_Stack[136].type=1, m_Stack[136].value=255
[VM] opcode=3 operand=5
[VM] STORE_VAR: slot=5, localBase=124, localCount=3, actualSlot=129, value=255
[VM] opcode=2 operand=3
[VM] LOAD_VAR: slot=3, localBase=124, actualSlot=127
[VM] LOAD_VAR: loaded value=36
[VM] push: slot=136, val.type=1, val.value=36
[VM] push:   m_Stack[136].type=1, m_Stack[136].value=36
[VM] opcode=2 operand=5
[VM] LOAD_VAR: slot=5, localBase=124, actualSlot=129
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=137, val.type=1, val.value=255
[VM] push:   m_Stack[137].type=1, m_Stack[137].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=138
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=138 - paramCount=2 = localBase=136
[VM]   arg[0] -> stack[136] = 36
[VM]   arg[1] -> stack[137] = 255
[VM] Saving caller pc=11 before native call
[00:00:04.000] [DEBUG] analogWrite(36, 255)
[VM] Restored caller pc to 11 after native call
[VM] opcode=45 operand=0
[VM] push: slot=138, val.type=1, val.value=0
[VM] push:   m_Stack[138].type=1, m_Stack[138].value=0
[VM] opcode=1 operand=20
[VM] LOAD_CONST idx=20, globalConstants.size()=45, stackTop=139
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=139, val.type=1, val.value=37
[VM] push:   m_Stack[139].type=1, m_Stack[139].value=37
[VM] LOAD_CONST done, new stackTop=140
[VM] opcode=3 operand=6
[VM] STORE_VAR: slot=6, localBase=124, localCount=3, actualSlot=130, value=37
[VM] opcode=1 operand=21
[VM] LOAD_CONST idx=21, globalConstants.size()=45, stackTop=139
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=139, val.type=1, val.value=255
[VM] push:   m_Stack[139].type=1, m_Stack[139].value=255
[VM] LOAD_CONST done, new stackTop=140
[VM] opcode=2 operand=1
[VM] LOAD_VAR: slot=1, localBase=124, actualSlot=125
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=140, val.type=1, val.value=0
[VM] push:   m_Stack[140].type=1, m_Stack[140].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=139, val.type=1, val.value=255
[VM] push:   m_Stack[139].type=1, m_Stack[139].value=255
[VM] opcode=3 operand=7
[VM] STORE_VAR: slot=7, localBase=124, localCount=3, actualSlot=131, value=255
[VM] opcode=2 operand=7
[VM] LOAD_VAR: slot=7, localBase=124, actualSlot=131
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=139, val.type=1, val.value=255
[VM] push:   m_Stack[139].type=1, m_Stack[139].value=255
[VM] opcode=3 operand=8
[VM] STORE_VAR: slot=8, localBase=124, localCount=3, actualSlot=132, value=255
[VM] opcode=2 operand=6
[VM] LOAD_VAR: slot=6, localBase=124, actualSlot=130
[VM] LOAD_VAR: loaded value=37
[VM] push: slot=139, val.type=1, val.value=37
[VM] push:   m_Stack[139].type=1, m_Stack[139].value=37
[VM] opcode=2 operand=8
[VM] LOAD_VAR: slot=8, localBase=124, actualSlot=132
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=140, val.type=1, val.value=255
[VM] push:   m_Stack[140].type=1, m_Stack[140].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=141
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=141 - paramCount=2 = localBase=139
[VM]   arg[0] -> stack[139] = 37
[VM]   arg[1] -> stack[140] = 255
[VM] Saving caller pc=23 before native call
[00:00:04.000] [DEBUG] analogWrite(37, 255)
[VM] Restored caller pc to 23 after native call
[VM] opcode=45 operand=0
[VM] push: slot=141, val.type=1, val.value=0
[VM] push:   m_Stack[141].type=1, m_Stack[141].value=0
[VM] opcode=1 operand=22
[VM] LOAD_CONST idx=22, globalConstants.size()=45, stackTop=142
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=142, val.type=1, val.value=35
[VM] push:   m_Stack[142].type=1, m_Stack[142].value=35
[VM] LOAD_CONST done, new stackTop=143
[VM] opcode=3 operand=9
[VM] STORE_VAR: slot=9, localBase=124, localCount=3, actualSlot=133, value=35
[VM] opcode=1 operand=23
[VM] LOAD_CONST idx=23, globalConstants.size()=45, stackTop=142
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=142, val.type=1, val.value=255
[VM] push:   m_Stack[142].type=1, m_Stack[142].value=255
[VM] LOAD_CONST done, new stackTop=143
[VM] opcode=2 operand=2
[VM] LOAD_VAR: slot=2, localBase=124, actualSlot=126
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=143, val.type=1, val.value=255
[VM] push:   m_Stack[143].type=1, m_Stack[143].value=255
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=255, result=0
[VM] push: slot=142, val.type=1, val.value=0
[VM] push:   m_Stack[142].type=1, m_Stack[142].value=0
[VM] opcode=3 operand=10
[VM] STORE_VAR: slot=10, localBase=124, localCount=3, actualSlot=134, value=0
[VM] opcode=2 operand=10
[VM] LOAD_VAR: slot=10, localBase=124, actualSlot=134
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=142, val.type=1, val.value=0
[VM] push:   m_Stack[142].type=1, m_Stack[142].value=0
[VM] opcode=3 operand=11
[VM] STORE_VAR: slot=11, localBase=124, localCount=3, actualSlot=135, value=0
[VM] opcode=2 operand=9
[VM] LOAD_VAR: slot=9, localBase=124, actualSlot=133
[VM] LOAD_VAR: loaded value=35
[VM] push: slot=142, val.type=1, val.value=35
[VM] push:   m_Stack[142].type=1, m_Stack[142].value=35
[VM] opcode=2 operand=11
[VM] LOAD_VAR: slot=11, localBase=124, actualSlot=135
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=143, val.type=1, val.value=0
[VM] push:   m_Stack[143].type=1, m_Stack[143].value=0
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=144
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=144 - paramCount=2 = localBase=142
[VM]   arg[0] -> stack[142] = 35
[VM]   arg[1] -> stack[143] = 0
[VM] Saving caller pc=35 before native call
[00:00:04.000] [DEBUG] analogWrite(35, 0)
[VM] Restored caller pc to 35 after native call
[VM] opcode=45 operand=0
[VM] push: slot=144, val.type=1, val.value=0
[VM] push:   m_Stack[144].type=1, m_Stack[144].value=0
[VM] RETURN
[VM] opcode=45 operand=0
[VM] push: slot=144, val.type=1, val.value=0
[VM] push:   m_Stack[144].type=1, m_Stack[144].value=0
[VM] opcode=1 operand=39
[VM] LOAD_CONST idx=39, globalConstants.size()=45, stackTop=145
[VM] LOAD_CONST entry.type=0, value.intVal=2000, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 2000 to stack
[VM] push: slot=145, val.type=1, val.value=2000
[VM] push:   m_Stack[145].type=1, m_Stack[145].value=2000
[VM] LOAD_CONST done, new stackTop=146
[VM] opcode=3 operand=20
[VM] STORE_VAR: slot=20, localBase=0, localCount=0, actualSlot=20, value=2000
[VM] opcode=2 operand=20
[VM] LOAD_VAR: slot=20, localBase=0, actualSlot=20
[VM] LOAD_VAR: loaded value=2000
[VM] push: slot=145, val.type=1, val.value=2000
[VM] push:   m_Stack[145].type=1, m_Stack[145].value=2000
[VM] opcode=48 operand=65545
[VM] CALL_NATIVE: stringPoolIndex=9, paramCount=1, stackTop=146
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'delay'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=146 - paramCount=1 = localBase=145
[VM]   arg[0] -> stack[145] = 2000
[VM] Saving caller pc=69 before native call
[VM] Restored caller pc to 69 after native call
[VM] opcode=45 operand=0
[VM] push: slot=146, val.type=1, val.value=0
[VM] push:   m_Stack[146].type=1, m_Stack[146].value=0
[VM] opcode=1 operand=40
[VM] LOAD_CONST idx=40, globalConstants.size()=45, stackTop=147
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=147, val.type=1, val.value=0
[VM] push:   m_Stack[147].type=1, m_Stack[147].value=0
[VM] LOAD_CONST done, new stackTop=148
[VM] opcode=3 operand=21
[VM] STORE_VAR: slot=21, localBase=0, localCount=0, actualSlot=21, value=0
[VM] opcode=1 operand=41
[VM] LOAD_CONST idx=41, globalConstants.size()=45, stackTop=147
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=147, val.type=1, val.value=0
[VM] push:   m_Stack[147].type=1, m_Stack[147].value=0
[VM] LOAD_CONST done, new stackTop=148
[VM] opcode=3 operand=22
[VM] STORE_VAR: slot=22, localBase=0, localCount=0, actualSlot=22, value=0
[VM] opcode=1 operand=42
[VM] LOAD_CONST idx=42, globalConstants.size()=45, stackTop=147
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=147, val.type=1, val.value=0
[VM] push:   m_Stack[147].type=1, m_Stack[147].value=0
[VM] LOAD_CONST done, new stackTop=148
[VM] opcode=3 operand=23
[VM] STORE_VAR: slot=23, localBase=0, localCount=0, actualSlot=23, value=0
[VM] opcode=2 operand=21
[VM] LOAD_VAR: slot=21, localBase=0, actualSlot=21
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=147, val.type=1, val.value=0
[VM] push:   m_Stack[147].type=1, m_Stack[147].value=0
[VM] opcode=2 operand=22
[VM] LOAD_VAR: slot=22, localBase=0, actualSlot=22
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=148, val.type=1, val.value=0
[VM] push:   m_Stack[148].type=1, m_Stack[148].value=0
[VM] opcode=2 operand=23
[VM] LOAD_VAR: slot=23, localBase=0, actualSlot=23
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=149, val.type=1, val.value=0
[VM] push:   m_Stack[149].type=1, m_Stack[149].value=0
[VM] opcode=32 operand=196609
[VM] CALL: funcIndex=1, paramCount=3, stackTop=150
[VM] CALL: Stack before call: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 [16]=2000 [17]=0 [18]=0 [19]=255 
[VM] callFunction: funcIndex=1, paramCount=3, localCount=12, funcParamCount=3
[VM] push: slot=150, val.type=1, val.value=0
[VM] push:   m_Stack[150].type=1, m_Stack[150].value=0
[VM] push: slot=151, val.type=1, val.value=0
[VM] push:   m_Stack[151].type=1, m_Stack[151].value=0
[VM] push: slot=152, val.type=1, val.value=0
[VM] push:   m_Stack[152].type=1, m_Stack[152].value=0
[VM] push: slot=153, val.type=1, val.value=0
[VM] push:   m_Stack[153].type=1, m_Stack[153].value=0
[VM] push: slot=154, val.type=1, val.value=0
[VM] push:   m_Stack[154].type=1, m_Stack[154].value=0
[VM] push: slot=155, val.type=1, val.value=0
[VM] push:   m_Stack[155].type=1, m_Stack[155].value=0
[VM] push: slot=156, val.type=1, val.value=0
[VM] push:   m_Stack[156].type=1, m_Stack[156].value=0
[VM] push: slot=157, val.type=1, val.value=0
[VM] push:   m_Stack[157].type=1, m_Stack[157].value=0
[VM] push: slot=158, val.type=1, val.value=0
[VM] push:   m_Stack[158].type=1, m_Stack[158].value=0
[VM] callFunction: After push locals, stackTop=159
[VM] callFunction: localBase=147
[VM] CALL: After setup frame, localBase=147
[VM] opcode=1 operand=18
[VM] LOAD_CONST idx=18, globalConstants.size()=45, stackTop=159
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=159, val.type=1, val.value=36
[VM] push:   m_Stack[159].type=1, m_Stack[159].value=36
[VM] LOAD_CONST done, new stackTop=160
[VM] opcode=3 operand=3
[VM] STORE_VAR: slot=3, localBase=147, localCount=3, actualSlot=150, value=36
[VM] opcode=1 operand=19
[VM] LOAD_CONST idx=19, globalConstants.size()=45, stackTop=159
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=159, val.type=1, val.value=255
[VM] push:   m_Stack[159].type=1, m_Stack[159].value=255
[VM] LOAD_CONST done, new stackTop=160
[VM] opcode=2 operand=0
[VM] LOAD_VAR: slot=0, localBase=147, actualSlot=147
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=160, val.type=1, val.value=0
[VM] push:   m_Stack[160].type=1, m_Stack[160].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=159, val.type=1, val.value=255
[VM] push:   m_Stack[159].type=1, m_Stack[159].value=255
[VM] opcode=3 operand=4
[VM] STORE_VAR: slot=4, localBase=147, localCount=3, actualSlot=151, value=255
[VM] opcode=2 operand=4
[VM] LOAD_VAR: slot=4, localBase=147, actualSlot=151
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=159, val.type=1, val.value=255
[VM] push:   m_Stack[159].type=1, m_Stack[159].value=255
[VM] opcode=3 operand=5
[VM] STORE_VAR: slot=5, localBase=147, localCount=3, actualSlot=152, value=255
[VM] opcode=2 operand=3
[VM] LOAD_VAR: slot=3, localBase=147, actualSlot=150
[VM] LOAD_VAR: loaded value=36
[VM] push: slot=159, val.type=1, val.value=36
[VM] push:   m_Stack[159].type=1, m_Stack[159].value=36
[VM] opcode=2 operand=5
[VM] LOAD_VAR: slot=5, localBase=147, actualSlot=152
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=160, val.type=1, val.value=255
[VM] push:   m_Stack[160].type=1, m_Stack[160].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=161
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=161 - paramCount=2 = localBase=159
[VM]   arg[0] -> stack[159] = 36
[VM]   arg[1] -> stack[160] = 255
[VM] Saving caller pc=11 before native call
[00:00:06.000] [DEBUG] analogWrite(36, 255)
[VM] Restored caller pc to 11 after native call
[VM] opcode=45 operand=0
[VM] push: slot=161, val.type=1, val.value=0
[VM] push:   m_Stack[161].type=1, m_Stack[161].value=0
[VM] opcode=1 operand=20
[VM] LOAD_CONST idx=20, globalConstants.size()=45, stackTop=162
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=162, val.type=1, val.value=37
[VM] push:   m_Stack[162].type=1, m_Stack[162].value=37
[VM] LOAD_CONST done, new stackTop=163
[VM] opcode=3 operand=6
[VM] STORE_VAR: slot=6, localBase=147, localCount=3, actualSlot=153, value=37
[VM] opcode=1 operand=21
[VM] LOAD_CONST idx=21, globalConstants.size()=45, stackTop=162
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=162, val.type=1, val.value=255
[VM] push:   m_Stack[162].type=1, m_Stack[162].value=255
[VM] LOAD_CONST done, new stackTop=163
[VM] opcode=2 operand=1
[VM] LOAD_VAR: slot=1, localBase=147, actualSlot=148
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=163, val.type=1, val.value=0
[VM] push:   m_Stack[163].type=1, m_Stack[163].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=162, val.type=1, val.value=255
[VM] push:   m_Stack[162].type=1, m_Stack[162].value=255
[VM] opcode=3 operand=7
[VM] STORE_VAR: slot=7, localBase=147, localCount=3, actualSlot=154, value=255
[VM] opcode=2 operand=7
[VM] LOAD_VAR: slot=7, localBase=147, actualSlot=154
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=162, val.type=1, val.value=255
[VM] push:   m_Stack[162].type=1, m_Stack[162].value=255
[VM] opcode=3 operand=8
[VM] STORE_VAR: slot=8, localBase=147, localCount=3, actualSlot=155, value=255
[VM] opcode=2 operand=6
[VM] LOAD_VAR: slot=6, localBase=147, actualSlot=153
[VM] LOAD_VAR: loaded value=37
[VM] push: slot=162, val.type=1, val.value=37
[VM] push:   m_Stack[162].type=1, m_Stack[162].value=37
[VM] opcode=2 operand=8
[VM] LOAD_VAR: slot=8, localBase=147, actualSlot=155
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=163, val.type=1, val.value=255
[VM] push:   m_Stack[163].type=1, m_Stack[163].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=164
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=164 - paramCount=2 = localBase=162
[VM]   arg[0] -> stack[162] = 37
[VM]   arg[1] -> stack[163] = 255
[VM] Saving caller pc=23 before native call
[00:00:06.000] [DEBUG] analogWrite(37, 255)
[VM] Restored caller pc to 23 after native call
[VM] opcode=45 operand=0
[VM] push: slot=164, val.type=1, val.value=0
[VM] push:   m_Stack[164].type=1, m_Stack[164].value=0
[VM] opcode=1 operand=22
[VM] LOAD_CONST idx=22, globalConstants.size()=45, stackTop=165
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=165, val.type=1, val.value=35
[VM] push:   m_Stack[165].type=1, m_Stack[165].value=35
[VM] LOAD_CONST done, new stackTop=166
[VM] opcode=3 operand=9
[VM] STORE_VAR: slot=9, localBase=147, localCount=3, actualSlot=156, value=35
[VM] opcode=1 operand=23
[VM] LOAD_CONST idx=23, globalConstants.size()=45, stackTop=165
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=165, val.type=1, val.value=255
[VM] push:   m_Stack[165].type=1, m_Stack[165].value=255
[VM] LOAD_CONST done, new stackTop=166
[VM] opcode=2 operand=2
[VM] LOAD_VAR: slot=2, localBase=147, actualSlot=149
[VM] LOAD_VAR: loaded value=0
[VM] push: slot=166, val.type=1, val.value=0
[VM] push:   m_Stack[166].type=1, m_Stack[166].value=0
[VM] opcode=8 operand=0
[VM] SUB: a=255, b=0, result=255
[VM] push: slot=165, val.type=1, val.value=255
[VM] push:   m_Stack[165].type=1, m_Stack[165].value=255
[VM] opcode=3 operand=10
[VM] STORE_VAR: slot=10, localBase=147, localCount=3, actualSlot=157, value=255
[VM] opcode=2 operand=10
[VM] LOAD_VAR: slot=10, localBase=147, actualSlot=157
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=165, val.type=1, val.value=255
[VM] push:   m_Stack[165].type=1, m_Stack[165].value=255
[VM] opcode=3 operand=11
[VM] STORE_VAR: slot=11, localBase=147, localCount=3, actualSlot=158, value=255
[VM] opcode=2 operand=9
[VM] LOAD_VAR: slot=9, localBase=147, actualSlot=156
[VM] LOAD_VAR: loaded value=35
[VM] push: slot=165, val.type=1, val.value=35
[VM] push:   m_Stack[165].type=1, m_Stack[165].value=35
[VM] opcode=2 operand=11
[VM] LOAD_VAR: slot=11, localBase=147, actualSlot=158
[VM] LOAD_VAR: loaded value=255
[VM] push: slot=166, val.type=1, val.value=255
[VM] push:   m_Stack[166].type=1, m_Stack[166].value=255
[VM] opcode=48 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=167
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'analogWrite'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=167 - paramCount=2 = localBase=165
[VM]   arg[0] -> stack[165] = 35
[VM]   arg[1] -> stack[166] = 255
[VM] Saving caller pc=35 before native call
[00:00:06.000] [DEBUG] analogWrite(35, 255)
[VM] Restored caller pc to 35 after native call
[VM] opcode=45 operand=0
[VM] push: slot=167, val.type=1, val.value=0
[VM] push:   m_Stack[167].type=1, m_Stack[167].value=0
[VM] RETURN
[VM] opcode=45 operand=0
[VM] push: slot=167, val.type=1, val.value=0
[VM] push:   m_Stack[167].type=1, m_Stack[167].value=0
[VM] opcode=1 operand=43
[VM] LOAD_CONST idx=43, globalConstants.size()=45, stackTop=168
[VM] LOAD_CONST entry.type=2, value.intVal=7, value.doubleVal=0.000000
[VM] push: slot=168, val.type=3, val.value=7
[VM] push:   m_Stack[168].type=3, m_Stack[168].value=7
[VM] LOAD_CONST done, new stackTop=169
[VM] opcode=3 operand=24
[VM] STORE_VAR: slot=24, localBase=0, localCount=0, actualSlot=24, value=7
[VM] opcode=2 operand=24
[VM] LOAD_VAR: slot=24, localBase=0, actualSlot=24
[VM] LOAD_VAR: loaded value=7
[VM] push: slot=168, val.type=3, val.value=7
[VM] push:   m_Stack[168].type=3, m_Stack[168].value=7
[VM] opcode=3 operand=25
[VM] STORE_VAR: slot=25, localBase=0, localCount=0, actualSlot=25, value=7
[VM] opcode=1 operand=44
[VM] LOAD_CONST idx=44, globalConstants.size()=45, stackTop=168
[VM] LOAD_CONST entry.type=0, value.intVal=999, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 999 to stack
[VM] push: slot=168, val.type=1, val.value=999
[VM] push:   m_Stack[168].type=1, m_Stack[168].value=999
[VM] LOAD_CONST done, new stackTop=169
[VM] opcode=3 operand=26
[VM] STORE_VAR: slot=26, localBase=0, localCount=0, actualSlot=26, value=999
[VM] opcode=2 operand=25
[VM] LOAD_VAR: slot=25, localBase=0, actualSlot=25
[VM] LOAD_VAR: loaded value=7
[VM] push: slot=168, val.type=3, val.value=7
[VM] push:   m_Stack[168].type=3, m_Stack[168].value=7
[VM] opcode=2 operand=26
[VM] LOAD_VAR: slot=26, localBase=0, actualSlot=26
[VM] LOAD_VAR: loaded value=999
[VM] push: slot=169, val.type=1, val.value=999
[VM] push:   m_Stack[169].type=1, m_Stack[169].value=999
[VM] opcode=48 operand=131080
[VM] CALL_NATIVE: stringPoolIndex=8, paramCount=2, stackTop=170
[VM] Stack contents: [0]=7 [1]=7 [2]=111 [3]=0 [4]=0 [5]=7 [6]=7 [7]=888 [8]=255 [9]=0 [10]=0 [11]=0 [12]=2000 [13]=0 [14]=255 [15]=0 
[VM] Calling native function: 'printf'
[VM] Dumping m_NativeFunctionMap (21 entries):
[VM]   Entry: len=11, hex=[616E616C6F675772697465]
[VM]   Entry: len=5, hex=[64656C6179]
[VM]   Entry: len=11, hex=[6469676974616C52656164]
[VM]   Entry: len=12, hex=[6469676974616C5772697465]
[VM]   Entry: len=14, hex=[64756D705F636F6E7374616E7473]
[VM]   Entry: len=14, hex=[6670696F615F7365745F66756E63]
[VM]   Entry: len=9, hex=[6770696F5F72656164]
[VM]   Entry: len=13, hex=[6770696F5F7365745F6D6F6465]
[VM]   Entry: len=10, hex=[6770696F5F7772697465]
[VM]   Entry: len=8, hex=[6C65645F696E6974]
[VM]   Entry: len=8, hex=[6C6F675F696E666F]
[VM]   Entry: len=6, hex=[6D696C6C6973]
[VM]   Entry: len=7, hex=[70696E4D6F6465]
[VM]   Entry: len=6, hex=[7072696E7466]
[VM]   Entry: len=4, hex=[70757473]
[VM]   Entry: len=7, hex=[7267625F736574]
[VM]   Entry: len=11, hex=[74696D65725F7374617274]
[VM]   Entry: len=10, hex=[74696D65725F73746F70]
[VM]   Entry: len=11, hex=[756172745F636F6E666967]
[VM]   Entry: len=9, hex=[756172745F72656164]
[VM]   Entry: len=10, hex=[756172745F7772697465]
[VM] Native function found
[VM] Argument calculation: stackTop=170 - paramCount=2 = localBase=168
[VM]   arg[0] -> stack[168] = 7
[VM]   arg[1] -> stack[169] = 999
[VM] Saving caller pc=90 before native call
999[VM] Restored caller pc to 90 after native call
[VM] opcode=45 operand=0
[VM] push: slot=170, val.type=1, val.value=0
[VM] push:   m_Stack[170].type=1, m_Stack[170].value=0
[VM] HALT
[00:00:06.000] [INFO] Script completed with result: 0
[00:00:06.000] [INFO] Entering main loop...
