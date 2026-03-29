
========================================
CScript K210 VM v4.0
Build: Mar 29 2026 14:34:47
========================================

[SYS] PLL0: 806000000 Hz
[SYS] PLL1: 159714285 Hz
[SYS] PLL2: 45066666 Hz
[00:00:00.000] [INFO] Initializing hardware...
[00:00:00.000] [INFO] Hardware initialized successfully
[00:00:00.000] [INFO] LED pins configured by script
[00:00:00.000] [INFO] Initializing VM...
[VM] registerNativeFunction: print
[VM] registerNativeFunction: println
[VM] registerNativeFunction: pinMode
[VM] registerNativeFunction: digitalWrite
[VM] registerNativeFunction: digitalRead
[VM] registerNativeFunction: analogWrite
[VM] registerNativeFunction: Serial.print
[VM] registerNativeFunction: Serial.println
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
[CSB] func[0].paramCount=0
[CSB] readFlash addr=0x80020 len=4 result=0
[CSB] func[0].localCount=0
[CSB] readFlash addr=0x80024 len=4 result=0
[CSB] func[0].maxStackSize=16
[CSB] readFlash addr=0x80028 len=4 result=0
[CSB] func[0].instrCount=28
[CSB] func[0] sizeof(BytecodeInstruction)=5, totalInstrBytes=140
[CSB] func[0] resizing instructions to 28
[CSB] func[0] instructions resize done
[CSB] func[0] reading 140 bytes instructions from addr 0x8002C
[CSB] readFlash addr=0x8002C len=140 result=0
[CSB] func[0] instructions read done
[CSB] readFlash addr=0x800B8 len=4 result=0
[CSB] func[0].constCount=0 (raw: 00 00 00 00)
[CSB] func[0] resizing constants to 0
[CSB] func[0] constants resize done
[CSB] func[0] pushing to module.functions
[CSB] func[0] pushed OK
[CSB] === Loading func 1 ===
[CSB] readFlash addr=0x800BC len=4 result=0
[CSB] func[1].nameOffset=4
[CSB] readFlash addr=0x800C0 len=4 result=0
[CSB] func[1].paramCount=0
[CSB] readFlash addr=0x800C4 len=4 result=0
[CSB] func[1].localCount=0
[CSB] readFlash addr=0x800C8 len=4 result=0
[CSB] func[1].maxStackSize=16
[CSB] readFlash addr=0x800CC len=4 result=0
[CSB] func[1].instrCount=25
[CSB] func[1] sizeof(BytecodeInstruction)=5, totalInstrBytes=125
[CSB] func[1] resizing instructions to 25
[CSB] func[1] instructions resize done
[CSB] func[1] reading 125 bytes instructions from addr 0x800D0
[CSB] readFlash addr=0x800D0 len=125 result=0
[CSB] func[1] instructions read done
[CSB] readFlash addr=0x8014D len=4 result=0
[CSB] func[1].constCount=0 (raw: 00 00 00 00)
[CSB] func[1] resizing constants to 0
[CSB] func[1] constants resize done
[CSB] func[1] pushing to module.functions
[CSB] func[1] pushed OK
[CSB] === Loading func 2 ===
[CSB] readFlash addr=0x80151 len=4 result=0
[CSB] func[2].nameOffset=6
[CSB] readFlash addr=0x80155 len=4 result=0
[CSB] func[2].paramCount=0
[CSB] readFlash addr=0x80159 len=4 result=0
[CSB] func[2].localCount=0
[CSB] readFlash addr=0x8015D len=4 result=0
[CSB] func[2].maxStackSize=16
[CSB] readFlash addr=0x80161 len=4 result=0
[CSB] func[2].instrCount=30
[CSB] func[2] sizeof(BytecodeInstruction)=5, totalInstrBytes=150
[CSB] func[2] resizing instructions to 30
[CSB] func[2] instructions resize done
[CSB] func[2] reading 150 bytes instructions from addr 0x80165
[CSB] readFlash addr=0x80165 len=150 result=0
[CSB] func[2] instructions read done
[CSB] readFlash addr=0x801FB len=4 result=0
[CSB] func[2].constCount=0 (raw: 00 00 00 00)
[CSB] func[2] resizing constants to 0
[CSB] func[2] constants resize done
[CSB] func[2] pushing to module.functions
[CSB] func[2] pushed OK
[CSB] readFlash addr=0x801FF len=4 result=0
[CSB] globalConstCount=42
[CSB] readFlash addr=0x80203 len=1 result=0
[CSB] readFlash addr=0x80204 len=8 result=0
[CSB] readFlash addr=0x8020C len=1 result=0
[CSB] readFlash addr=0x8020D len=8 result=0
[CSB] readFlash addr=0x80215 len=1 result=0
[CSB] readFlash addr=0x80216 len=8 result=0
[CSB] readFlash addr=0x8021E len=1 result=0
[CSB] readFlash addr=0x8021F len=8 result=0
[CSB] readFlash addr=0x80227 len=1 result=0
[CSB] readFlash addr=0x80228 len=8 result=0
[CSB] readFlash addr=0x80230 len=1 result=0
[CSB] readFlash addr=0x80231 len=8 result=0
[CSB] readFlash addr=0x80239 len=1 result=0
[CSB] readFlash addr=0x8023A len=8 result=0
[CSB] readFlash addr=0x80242 len=1 result=0
[CSB] readFlash addr=0x80243 len=8 result=0
[CSB] readFlash addr=0x8024B len=1 result=0
[CSB] readFlash addr=0x8024C len=8 result=0
[CSB] readFlash addr=0x80254 len=1 result=0
[CSB] readFlash addr=0x80255 len=8 result=0
[CSB] readFlash addr=0x8025D len=1 result=0
[CSB] readFlash addr=0x8025E len=8 result=0
[CSB] readFlash addr=0x80266 len=1 result=0
[CSB] readFlash addr=0x80267 len=8 result=0
[CSB] readFlash addr=0x8026F len=1 result=0
[CSB] readFlash addr=0x80270 len=8 result=0
[CSB] readFlash addr=0x80278 len=1 result=0
[CSB] readFlash addr=0x80279 len=8 result=0
[CSB] readFlash addr=0x80281 len=1 result=0
[CSB] readFlash addr=0x80282 len=8 result=0
[CSB] readFlash addr=0x8028A len=1 result=0
[CSB] readFlash addr=0x8028B len=8 result=0
[CSB] readFlash addr=0x80293 len=1 result=0
[CSB] readFlash addr=0x80294 len=8 result=0
[CSB] readFlash addr=0x8029C len=1 result=0
[CSB] readFlash addr=0x8029D len=8 result=0
[CSB] readFlash addr=0x802A5 len=1 result=0
[CSB] readFlash addr=0x802A6 len=8 result=0
[CSB] readFlash addr=0x802AE len=1 result=0
[CSB] readFlash addr=0x802AF len=8 result=0
[CSB] readFlash addr=0x802B7 len=1 result=0
[CSB] readFlash addr=0x802B8 len=8 result=0
[CSB] readFlash addr=0x802C0 len=1 result=0
[CSB] readFlash addr=0x802C1 len=8 result=0
[CSB] readFlash addr=0x802C9 len=1 result=0
[CSB] readFlash addr=0x802CA len=8 result=0
[CSB] readFlash addr=0x802D2 len=1 result=0
[CSB] readFlash addr=0x802D3 len=8 result=0
[CSB] readFlash addr=0x802DB len=1 result=0
[CSB] readFlash addr=0x802DC len=8 result=0
[CSB] readFlash addr=0x802E4 len=1 result=0
[CSB] readFlash addr=0x802E5 len=8 result=0
[CSB] readFlash addr=0x802ED len=1 result=0
[CSB] readFlash addr=0x802EE len=8 result=0
[CSB] readFlash addr=0x802F6 len=1 result=0
[CSB] readFlash addr=0x802F7 len=8 result=0
[CSB] readFlash addr=0x802FF len=1 result=0
[CSB] readFlash addr=0x80300 len=8 result=0
[CSB] readFlash addr=0x80308 len=1 result=0
[CSB] readFlash addr=0x80309 len=8 result=0
[CSB] readFlash addr=0x80311 len=1 result=0
[CSB] readFlash addr=0x80312 len=8 result=0
[CSB] readFlash addr=0x8031A len=1 result=0
[CSB] readFlash addr=0x8031B len=8 result=0
[CSB] readFlash addr=0x80323 len=1 result=0
[CSB] readFlash addr=0x80324 len=8 result=0
[CSB] readFlash addr=0x8032C len=1 result=0
[CSB] readFlash addr=0x8032D len=8 result=0
[CSB] readFlash addr=0x80335 len=1 result=0
[CSB] readFlash addr=0x80336 len=8 result=0
[CSB] readFlash addr=0x8033E len=1 result=0
[CSB] readFlash addr=0x8033F len=8 result=0
[CSB] readFlash addr=0x80347 len=1 result=0
[CSB] readFlash addr=0x80348 len=8 result=0
[CSB] readFlash addr=0x80350 len=1 result=0
[CSB] readFlash addr=0x80351 len=8 result=0
[CSB] readFlash addr=0x80359 len=1 result=0
[CSB] readFlash addr=0x8035A len=8 result=0
[CSB] readFlash addr=0x80362 len=1 result=0
[CSB] readFlash addr=0x80363 len=8 result=0
[CSB] readFlash addr=0x8036B len=1 result=0
[CSB] readFlash addr=0x8036C len=8 result=0
[CSB] readFlash addr=0x80374 len=1 result=0
[CSB] readFlash addr=0x80375 len=8 result=0
[CSB] readFlash addr=0x8037D len=4 result=0
[CSB] stringCount=10
[CSB] Loading 10 strings
[CSB] readFlash addr=0x80381 len=4 result=0
[CSB] readFlash addr=0x80385 len=7 result=0
[CSB] stringPool[0]: "rgbInit" (len=7)
[CSB] readFlash addr=0x8038D len=4 result=0
[CSB] readFlash addr=0x80391 len=14 result=0
[CSB] stringPool[1]: "fpioa_set_func" (len=14)
[CSB] readFlash addr=0x803A0 len=4 result=0
[CSB] readFlash addr=0x803A4 len=7 result=0
[CSB] stringPool[2]: "pinMode" (len=7)
[CSB] readFlash addr=0x803AC len=4 result=0
[CSB] readFlash addr=0x803B0 len=12 result=0
[CSB] stringPool[3]: "digitalWrite" (len=12)
[CSB] readFlash addr=0x803BD len=4 result=0
[CSB] readFlash addr=0x803C1 len=8 result=0
[CSB] stringPool[4]: "rgbWrite" (len=8)
[CSB] readFlash addr=0x803CA len=4 result=0
[CSB] readFlash addr=0x803CE len=11 result=0
[CSB] stringPool[5]: "analogWrite" (len=11)
[CSB] readFlash addr=0x803DA len=4 result=0
[CSB] readFlash addr=0x803DE len=4 result=0
[CSB] stringPool[6]: "main" (len=4)
[CSB] readFlash addr=0x803E3 len=4 result=0
[CSB] readFlash addr=0x803E7 len=7 result=0
[CSB] stringPool[7]: "println" (len=7)
[CSB] readFlash addr=0x803EF len=4 result=0
[CSB] readFlash addr=0x803F3 len=5 result=0
[CSB] stringPool[8]: "print" (len=5)
[CSB] readFlash addr=0x803F9 len=4 result=0
[CSB] readFlash addr=0x803FD len=5 result=0
[CSB] stringPool[9]: "delay" (len=5)
[CSB] All loaded successfully!
[00:00:00.000] [INFO] CSB loaded: 3 functions, 10 strings, 42 constants
[00:00:00.000] [INFO] Executing entry point 2...
[VM] execute entryPoint=2, functions=3
[VM] entryFunc: instrCount=30, constCount=0
[VM] opcode=1 operand=24
[VM] LOAD_CONST idx=24, globalConstants.size()=42, stackTop=0
[VM] LOAD_CONST entry.type=0, value.intVal=111, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 111 to stack
[VM] push: slot=0, val.type=1, val.value=111
[VM] push:   m_Stack[0].type=1, m_Stack[0].value=111
[VM] LOAD_CONST done, new stackTop=1
[VM] opcode=46 operand=65543
[VM] CALL_NATIVE: stringPoolIndex=7, paramCount=1, stackTop=1
[VM] Stack contents: [0]=111 
[VM] Calling native function: 'println'
[VM] Native function found
[VM] Argument calculation: stackTop=1 - paramCount=1 = localBase=0
[VM]   arg[0] -> stack[0] = 111
[VM] Saving caller pc=2 before native call
111
[VM] Restored caller pc to 2 after native call
[VM] opcode=31 operand=0
[VM] opcode=1 operand=0
[VM] LOAD_CONST idx=0, globalConstants.size()=42, stackTop=1
[VM] LOAD_CONST entry.type=0, value.intVal=13, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 13 to stack
[VM] push: slot=1, val.type=1, val.value=13
[VM] push:   m_Stack[1].type=1, m_Stack[1].value=13
[VM] LOAD_CONST done, new stackTop=2
[VM] opcode=1 operand=1
[VM] LOAD_CONST idx=1, globalConstants.size()=42, stackTop=2
[VM] LOAD_CONST entry.type=0, value.intVal=61, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 61 to stack
[VM] push: slot=2, val.type=1, val.value=61
[VM] push:   m_Stack[2].type=1, m_Stack[2].value=61
[VM] LOAD_CONST done, new stackTop=3
[VM] opcode=46 operand=131073
[VM] CALL_NATIVE: stringPoolIndex=1, paramCount=2, stackTop=3
[VM] Stack contents: [0]=111 [1]=13 [2]=61 
[VM] Calling native function: 'fpioa_set_func'
[VM] Native function found
[VM] Argument calculation: stackTop=3 - paramCount=2 = localBase=1
[VM]   arg[0] -> stack[1] = 13
[VM]   arg[1] -> stack[2] = 61
[VM] Saving caller pc=3 before native call
[00:00:00.000] [DEBUG] fpioa_set_func(pin=13, func=61)
[VM] Restored caller pc to 3 after native call
[VM] opcode=1 operand=2
[VM] LOAD_CONST idx=2, globalConstants.size()=42, stackTop=3
[VM] LOAD_CONST entry.type=0, value.intVal=14, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 14 to stack
[VM] push: slot=3, val.type=1, val.value=14
[VM] push:   m_Stack[3].type=1, m_Stack[3].value=14
[VM] LOAD_CONST done, new stackTop=4
[VM] opcode=1 operand=3
[VM] LOAD_CONST idx=3, globalConstants.size()=42, stackTop=4
[VM] LOAD_CONST entry.type=0, value.intVal=60, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 60 to stack
[VM] push: slot=4, val.type=1, val.value=60
[VM] push:   m_Stack[4].type=1, m_Stack[4].value=60
[VM] LOAD_CONST done, new stackTop=5
[VM] opcode=46 operand=131073
[VM] CALL_NATIVE: stringPoolIndex=1, paramCount=2, stackTop=5
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 
[VM] Calling native function: 'fpioa_set_func'
[VM] Native function found
[VM] Argument calculation: stackTop=5 - paramCount=2 = localBase=3
[VM]   arg[0] -> stack[3] = 14
[VM]   arg[1] -> stack[4] = 60
[VM] Saving caller pc=6 before native call
[00:00:00.000] [DEBUG] fpioa_set_func(pin=14, func=60)
[VM] Restored caller pc to 6 after native call
[VM] opcode=1 operand=4
[VM] LOAD_CONST idx=4, globalConstants.size()=42, stackTop=5
[VM] LOAD_CONST entry.type=0, value.intVal=12, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 12 to stack
[VM] push: slot=5, val.type=1, val.value=12
[VM] push:   m_Stack[5].type=1, m_Stack[5].value=12
[VM] LOAD_CONST done, new stackTop=6
[VM] opcode=1 operand=5
[VM] LOAD_CONST idx=5, globalConstants.size()=42, stackTop=6
[VM] LOAD_CONST entry.type=0, value.intVal=59, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 59 to stack
[VM] push: slot=6, val.type=1, val.value=59
[VM] push:   m_Stack[6].type=1, m_Stack[6].value=59
[VM] LOAD_CONST done, new stackTop=7
[VM] opcode=46 operand=131073
[VM] CALL_NATIVE: stringPoolIndex=1, paramCount=2, stackTop=7
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 
[VM] Calling native function: 'fpioa_set_func'
[VM] Native function found
[VM] Argument calculation: stackTop=7 - paramCount=2 = localBase=5
[VM]   arg[0] -> stack[5] = 12
[VM]   arg[1] -> stack[6] = 59
[VM] Saving caller pc=9 before native call
[00:00:00.000] [DEBUG] fpioa_set_func(pin=12, func=59)
[VM] Restored caller pc to 9 after native call
[VM] opcode=1 operand=6
[VM] LOAD_CONST idx=6, globalConstants.size()=42, stackTop=7
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=7, val.type=1, val.value=36
[VM] push:   m_Stack[7].type=1, m_Stack[7].value=36
[VM] LOAD_CONST done, new stackTop=8
[VM] opcode=1 operand=7
[VM] LOAD_CONST idx=7, globalConstants.size()=42, stackTop=8
[VM] LOAD_CONST entry.type=0, value.intVal=3, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 3 to stack
[VM] push: slot=8, val.type=1, val.value=3
[VM] push:   m_Stack[8].type=1, m_Stack[8].value=3
[VM] LOAD_CONST done, new stackTop=9
[VM] opcode=46 operand=131074
[VM] CALL_NATIVE: stringPoolIndex=2, paramCount=2, stackTop=9
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 
[VM] Calling native function: 'pinMode'
[VM] Native function found
[VM] Argument calculation: stackTop=9 - paramCount=2 = localBase=7
[VM]   arg[0] -> stack[7] = 36
[VM]   arg[1] -> stack[8] = 3
[VM] Saving caller pc=12 before native call
[00:00:00.000] [DEBUG] pinMode(36, 3)
[VM] Restored caller pc to 12 after native call
[VM] opcode=1 operand=8
[VM] LOAD_CONST idx=8, globalConstants.size()=42, stackTop=9
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=9, val.type=1, val.value=37
[VM] push:   m_Stack[9].type=1, m_Stack[9].value=37
[VM] LOAD_CONST done, new stackTop=10
[VM] opcode=1 operand=9
[VM] LOAD_CONST idx=9, globalConstants.size()=42, stackTop=10
[VM] LOAD_CONST entry.type=0, value.intVal=3, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 3 to stack
[VM] push: slot=10, val.type=1, val.value=3
[VM] push:   m_Stack[10].type=1, m_Stack[10].value=3
[VM] LOAD_CONST done, new stackTop=11
[VM] opcode=46 operand=131074
[VM] CALL_NATIVE: stringPoolIndex=2, paramCount=2, stackTop=11
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 
[VM] Calling native function: 'pinMode'
[VM] Native function found
[VM] Argument calculation: stackTop=11 - paramCount=2 = localBase=9
[VM]   arg[0] -> stack[9] = 37
[VM]   arg[1] -> stack[10] = 3
[VM] Saving caller pc=15 before native call
[00:00:00.000] [DEBUG] pinMode(37, 3)
[VM] Restored caller pc to 15 after native call
[VM] opcode=1 operand=10
[VM] LOAD_CONST idx=10, globalConstants.size()=42, stackTop=11
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=11, val.type=1, val.value=35
[VM] push:   m_Stack[11].type=1, m_Stack[11].value=35
[VM] LOAD_CONST done, new stackTop=12
[VM] opcode=1 operand=11
[VM] LOAD_CONST idx=11, globalConstants.size()=42, stackTop=12
[VM] LOAD_CONST entry.type=0, value.intVal=3, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 3 to stack
[VM] push: slot=12, val.type=1, val.value=3
[VM] push:   m_Stack[12].type=1, m_Stack[12].value=3
[VM] LOAD_CONST done, new stackTop=13
[VM] opcode=46 operand=131074
[VM] CALL_NATIVE: stringPoolIndex=2, paramCount=2, stackTop=13
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 
[VM] Calling native function: 'pinMode'
[VM] Native function found
[VM] Argument calculation: stackTop=13 - paramCount=2 = localBase=11
[VM]   arg[0] -> stack[11] = 35
[VM]   arg[1] -> stack[12] = 3
[VM] Saving caller pc=18 before native call
[00:00:00.000] [DEBUG] pinMode(35, 3)
[VM] Restored caller pc to 18 after native call
[VM] opcode=1 operand=12
[VM] LOAD_CONST idx=12, globalConstants.size()=42, stackTop=13
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=13, val.type=1, val.value=36
[VM] push:   m_Stack[13].type=1, m_Stack[13].value=36
[VM] LOAD_CONST done, new stackTop=14
[VM] opcode=1 operand=13
[VM] LOAD_CONST idx=13, globalConstants.size()=42, stackTop=14
[VM] LOAD_CONST entry.type=0, value.intVal=1, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 1 to stack
[VM] push: slot=14, val.type=1, val.value=1
[VM] push:   m_Stack[14].type=1, m_Stack[14].value=1
[VM] LOAD_CONST done, new stackTop=15
[VM] opcode=46 operand=131075
[VM] CALL_NATIVE: stringPoolIndex=3, paramCount=2, stackTop=15
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 
[VM] Calling native function: 'digitalWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=15 - paramCount=2 = localBase=13
[VM]   arg[0] -> stack[13] = 36
[VM]   arg[1] -> stack[14] = 1
[VM] Saving caller pc=21 before native call
[00:00:00.000] [DEBUG] digitalWrite(36, 1)
[VM] Restored caller pc to 21 after native call
[VM] opcode=1 operand=14
[VM] LOAD_CONST idx=14, globalConstants.size()=42, stackTop=15
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=15, val.type=1, val.value=37
[VM] push:   m_Stack[15].type=1, m_Stack[15].value=37
[VM] LOAD_CONST done, new stackTop=16
[VM] opcode=1 operand=15
[VM] LOAD_CONST idx=15, globalConstants.size()=42, stackTop=16
[VM] LOAD_CONST entry.type=0, value.intVal=1, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 1 to stack
[VM] push: slot=16, val.type=1, val.value=1
[VM] push:   m_Stack[16].type=1, m_Stack[16].value=1
[VM] LOAD_CONST done, new stackTop=17
[VM] opcode=46 operand=131075
[VM] CALL_NATIVE: stringPoolIndex=3, paramCount=2, stackTop=17
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'digitalWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=17 - paramCount=2 = localBase=15
[VM]   arg[0] -> stack[15] = 37
[VM]   arg[1] -> stack[16] = 1
[VM] Saving caller pc=24 before native call
[00:00:00.000] [DEBUG] digitalWrite(37, 1)
[VM] Restored caller pc to 24 after native call
[VM] opcode=1 operand=16
[VM] LOAD_CONST idx=16, globalConstants.size()=42, stackTop=17
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=17, val.type=1, val.value=35
[VM] push:   m_Stack[17].type=1, m_Stack[17].value=35
[VM] LOAD_CONST done, new stackTop=18
[VM] opcode=1 operand=17
[VM] LOAD_CONST idx=17, globalConstants.size()=42, stackTop=18
[VM] LOAD_CONST entry.type=0, value.intVal=1, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 1 to stack
[VM] push: slot=18, val.type=1, val.value=1
[VM] push:   m_Stack[18].type=1, m_Stack[18].value=1
[VM] LOAD_CONST done, new stackTop=19
[VM] opcode=46 operand=131075
[VM] CALL_NATIVE: stringPoolIndex=3, paramCount=2, stackTop=19
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'digitalWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=19 - paramCount=2 = localBase=17
[VM]   arg[0] -> stack[17] = 35
[VM]   arg[1] -> stack[18] = 1
[VM] Saving caller pc=27 before native call
[00:00:00.000] [DEBUG] digitalWrite(35, 1)
[VM] Restored caller pc to 27 after native call
[VM] RETURN
[VM] opcode=1 operand=25
[VM] LOAD_CONST idx=25, globalConstants.size()=42, stackTop=18
[VM] LOAD_CONST entry.type=0, value.intVal=888, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 888 to stack
[VM] push: slot=18, val.type=1, val.value=888
[VM] push:   m_Stack[18].type=1, m_Stack[18].value=888
[VM] LOAD_CONST done, new stackTop=19
[VM] opcode=46 operand=65544
[VM] CALL_NATIVE: stringPoolIndex=8, paramCount=1, stackTop=19
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'print'
[VM] Native function found
[VM] Argument calculation: stackTop=19 - paramCount=1 = localBase=18
[VM]   arg[0] -> stack[18] = 888
[VM] Saving caller pc=5 before native call
888[VM] Restored caller pc to 5 after native call
[VM] opcode=1 operand=26
[VM] LOAD_CONST idx=26, globalConstants.size()=42, stackTop=19
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=19, val.type=1, val.value=255
[VM] push:   m_Stack[19].type=1, m_Stack[19].value=255
[VM] LOAD_CONST done, new stackTop=20
[VM] opcode=1 operand=27
[VM] LOAD_CONST idx=27, globalConstants.size()=42, stackTop=20
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=20, val.type=1, val.value=0
[VM] push:   m_Stack[20].type=1, m_Stack[20].value=0
[VM] LOAD_CONST done, new stackTop=21
[VM] opcode=1 operand=28
[VM] LOAD_CONST idx=28, globalConstants.size()=42, stackTop=21
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=21, val.type=1, val.value=0
[VM] push:   m_Stack[21].type=1, m_Stack[21].value=0
[VM] LOAD_CONST done, new stackTop=22
[VM] opcode=31 operand=196609
[VM] opcode=2 operand=0
[VM] push: slot=22, val.type=1, val.value=255
[VM] push:   m_Stack[22].type=1, m_Stack[22].value=255
[VM] opcode=3 operand=0
[VM] opcode=2 operand=1
[VM] push: slot=22, val.type=1, val.value=0
[VM] push:   m_Stack[22].type=1, m_Stack[22].value=0
[VM] opcode=3 operand=1
[VM] opcode=2 operand=2
[VM] push: slot=22, val.type=1, val.value=0
[VM] push:   m_Stack[22].type=1, m_Stack[22].value=0
[VM] opcode=3 operand=2
[VM] opcode=2 operand=0
[VM] push: slot=22, val.type=1, val.value=255
[VM] push:   m_Stack[22].type=1, m_Stack[22].value=255
[VM] opcode=1 operand=18
[VM] LOAD_CONST idx=18, globalConstants.size()=42, stackTop=23
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=23, val.type=1, val.value=255
[VM] push:   m_Stack[23].type=1, m_Stack[23].value=255
[VM] LOAD_CONST done, new stackTop=24
[VM] opcode=7 operand=0
[VM] push: slot=22, val.type=1, val.value=0
[VM] push:   m_Stack[22].type=1, m_Stack[22].value=0
[VM] opcode=3 operand=3
[VM] opcode=1 operand=19
[VM] LOAD_CONST idx=19, globalConstants.size()=42, stackTop=22
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=22, val.type=1, val.value=36
[VM] push:   m_Stack[22].type=1, m_Stack[22].value=36
[VM] LOAD_CONST done, new stackTop=23
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=23
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=23 - paramCount=2 = localBase=21
[VM]   arg[0] -> stack[21] = 0
[VM]   arg[1] -> stack[22] = 36
[VM] Saving caller pc=12 before native call
[00:00:00.000] [DEBUG] analogWrite(0, 36)
[VM] Restored caller pc to 12 after native call
[VM] opcode=2 operand=1
[VM] push: slot=23, val.type=1, val.value=0
[VM] push:   m_Stack[23].type=1, m_Stack[23].value=0
[VM] opcode=1 operand=20
[VM] LOAD_CONST idx=20, globalConstants.size()=42, stackTop=24
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=24, val.type=1, val.value=255
[VM] push:   m_Stack[24].type=1, m_Stack[24].value=255
[VM] LOAD_CONST done, new stackTop=25
[VM] opcode=7 operand=0
[VM] push: slot=23, val.type=1, val.value=-255
[VM] push:   m_Stack[23].type=1, m_Stack[23].value=-255
[VM] opcode=3 operand=4
[VM] opcode=1 operand=21
[VM] LOAD_CONST idx=21, globalConstants.size()=42, stackTop=23
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=23, val.type=1, val.value=37
[VM] push:   m_Stack[23].type=1, m_Stack[23].value=37
[VM] LOAD_CONST done, new stackTop=24
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=24
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=24 - paramCount=2 = localBase=22
[VM]   arg[0] -> stack[22] = 36
[VM]   arg[1] -> stack[23] = 37
[VM] Saving caller pc=18 before native call
[00:00:00.000] [DEBUG] analogWrite(36, 37)
[VM] Restored caller pc to 18 after native call
[VM] opcode=2 operand=2
[VM] push: slot=24, val.type=1, val.value=0
[VM] push:   m_Stack[24].type=1, m_Stack[24].value=0
[VM] opcode=1 operand=22
[VM] LOAD_CONST idx=22, globalConstants.size()=42, stackTop=25
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=25, val.type=1, val.value=255
[VM] push:   m_Stack[25].type=1, m_Stack[25].value=255
[VM] LOAD_CONST done, new stackTop=26
[VM] opcode=7 operand=0
[VM] push: slot=24, val.type=1, val.value=-255
[VM] push:   m_Stack[24].type=1, m_Stack[24].value=-255
[VM] opcode=3 operand=5
[VM] opcode=1 operand=23
[VM] LOAD_CONST idx=23, globalConstants.size()=42, stackTop=24
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=24, val.type=1, val.value=35
[VM] push:   m_Stack[24].type=1, m_Stack[24].value=35
[VM] LOAD_CONST done, new stackTop=25
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=25
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=25 - paramCount=2 = localBase=23
[VM]   arg[0] -> stack[23] = 37
[VM]   arg[1] -> stack[24] = 35
[VM] Saving caller pc=24 before native call
[00:00:00.000] [DEBUG] analogWrite(37, 35)
[VM] Restored caller pc to 24 after native call
[VM] RETURN
[VM] opcode=1 operand=29
[VM] LOAD_CONST idx=29, globalConstants.size()=42, stackTop=24
[VM] LOAD_CONST entry.type=0, value.intVal=2000, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 2000 to stack
[VM] push: slot=24, val.type=1, val.value=2000
[VM] push:   m_Stack[24].type=1, m_Stack[24].value=2000
[VM] LOAD_CONST done, new stackTop=25
[VM] opcode=46 operand=65545
[VM] CALL_NATIVE: stringPoolIndex=9, paramCount=1, stackTop=25
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'delay'
[VM] Native function found
[VM] Argument calculation: stackTop=25 - paramCount=1 = localBase=24
[VM]   arg[0] -> stack[24] = 2000
[VM] Saving caller pc=11 before native call
[VM] Restored caller pc to 11 after native call
[VM] opcode=1 operand=30
[VM] LOAD_CONST idx=30, globalConstants.size()=42, stackTop=25
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=25, val.type=1, val.value=0
[VM] push:   m_Stack[25].type=1, m_Stack[25].value=0
[VM] LOAD_CONST done, new stackTop=26
[VM] opcode=1 operand=31
[VM] LOAD_CONST idx=31, globalConstants.size()=42, stackTop=26
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=26, val.type=1, val.value=255
[VM] push:   m_Stack[26].type=1, m_Stack[26].value=255
[VM] LOAD_CONST done, new stackTop=27
[VM] opcode=1 operand=32
[VM] LOAD_CONST idx=32, globalConstants.size()=42, stackTop=27
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=27, val.type=1, val.value=0
[VM] push:   m_Stack[27].type=1, m_Stack[27].value=0
[VM] LOAD_CONST done, new stackTop=28
[VM] opcode=31 operand=196609
[VM] opcode=2 operand=0
[VM] push: slot=28, val.type=1, val.value=0
[VM] push:   m_Stack[28].type=1, m_Stack[28].value=0
[VM] opcode=3 operand=0
[VM] opcode=2 operand=1
[VM] push: slot=28, val.type=1, val.value=255
[VM] push:   m_Stack[28].type=1, m_Stack[28].value=255
[VM] opcode=3 operand=1
[VM] opcode=2 operand=2
[VM] push: slot=28, val.type=1, val.value=0
[VM] push:   m_Stack[28].type=1, m_Stack[28].value=0
[VM] opcode=3 operand=2
[VM] opcode=2 operand=0
[VM] push: slot=28, val.type=1, val.value=0
[VM] push:   m_Stack[28].type=1, m_Stack[28].value=0
[VM] opcode=1 operand=18
[VM] LOAD_CONST idx=18, globalConstants.size()=42, stackTop=29
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=29, val.type=1, val.value=255
[VM] push:   m_Stack[29].type=1, m_Stack[29].value=255
[VM] LOAD_CONST done, new stackTop=30
[VM] opcode=7 operand=0
[VM] push: slot=28, val.type=1, val.value=-255
[VM] push:   m_Stack[28].type=1, m_Stack[28].value=-255
[VM] opcode=3 operand=3
[VM] opcode=1 operand=19
[VM] LOAD_CONST idx=19, globalConstants.size()=42, stackTop=28
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=28, val.type=1, val.value=36
[VM] push:   m_Stack[28].type=1, m_Stack[28].value=36
[VM] LOAD_CONST done, new stackTop=29
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=29
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=29 - paramCount=2 = localBase=27
[VM]   arg[0] -> stack[27] = 0
[VM]   arg[1] -> stack[28] = 36
[VM] Saving caller pc=12 before native call
[00:00:02.000] [DEBUG] analogWrite(0, 36)
[VM] Restored caller pc to 12 after native call
[VM] opcode=2 operand=1
[VM] push: slot=29, val.type=1, val.value=255
[VM] push:   m_Stack[29].type=1, m_Stack[29].value=255
[VM] opcode=1 operand=20
[VM] LOAD_CONST idx=20, globalConstants.size()=42, stackTop=30
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=30, val.type=1, val.value=255
[VM] push:   m_Stack[30].type=1, m_Stack[30].value=255
[VM] LOAD_CONST done, new stackTop=31
[VM] opcode=7 operand=0
[VM] push: slot=29, val.type=1, val.value=0
[VM] push:   m_Stack[29].type=1, m_Stack[29].value=0
[VM] opcode=3 operand=4
[VM] opcode=1 operand=21
[VM] LOAD_CONST idx=21, globalConstants.size()=42, stackTop=29
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=29, val.type=1, val.value=37
[VM] push:   m_Stack[29].type=1, m_Stack[29].value=37
[VM] LOAD_CONST done, new stackTop=30
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=30
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=30 - paramCount=2 = localBase=28
[VM]   arg[0] -> stack[28] = 36
[VM]   arg[1] -> stack[29] = 37
[VM] Saving caller pc=18 before native call
[00:00:02.000] [DEBUG] analogWrite(36, 37)
[VM] Restored caller pc to 18 after native call
[VM] opcode=2 operand=2
[VM] push: slot=30, val.type=1, val.value=0
[VM] push:   m_Stack[30].type=1, m_Stack[30].value=0
[VM] opcode=1 operand=22
[VM] LOAD_CONST idx=22, globalConstants.size()=42, stackTop=31
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=31, val.type=1, val.value=255
[VM] push:   m_Stack[31].type=1, m_Stack[31].value=255
[VM] LOAD_CONST done, new stackTop=32
[VM] opcode=7 operand=0
[VM] push: slot=30, val.type=1, val.value=-255
[VM] push:   m_Stack[30].type=1, m_Stack[30].value=-255
[VM] opcode=3 operand=5
[VM] opcode=1 operand=23
[VM] LOAD_CONST idx=23, globalConstants.size()=42, stackTop=30
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=30, val.type=1, val.value=35
[VM] push:   m_Stack[30].type=1, m_Stack[30].value=35
[VM] LOAD_CONST done, new stackTop=31
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=31
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=31 - paramCount=2 = localBase=29
[VM]   arg[0] -> stack[29] = 37
[VM]   arg[1] -> stack[30] = 35
[VM] Saving caller pc=24 before native call
[00:00:02.000] [DEBUG] analogWrite(37, 35)
[VM] Restored caller pc to 24 after native call
[VM] RETURN
[VM] opcode=1 operand=33
[VM] LOAD_CONST idx=33, globalConstants.size()=42, stackTop=30
[VM] LOAD_CONST entry.type=0, value.intVal=2000, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 2000 to stack
[VM] push: slot=30, val.type=1, val.value=2000
[VM] push:   m_Stack[30].type=1, m_Stack[30].value=2000
[VM] LOAD_CONST done, new stackTop=31
[VM] opcode=46 operand=65545
[VM] CALL_NATIVE: stringPoolIndex=9, paramCount=1, stackTop=31
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'delay'
[VM] Native function found
[VM] Argument calculation: stackTop=31 - paramCount=1 = localBase=30
[VM]   arg[0] -> stack[30] = 2000
[VM] Saving caller pc=17 before native call
[VM] Restored caller pc to 17 after native call
[VM] opcode=1 operand=34
[VM] LOAD_CONST idx=34, globalConstants.size()=42, stackTop=31
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=31, val.type=1, val.value=0
[VM] push:   m_Stack[31].type=1, m_Stack[31].value=0
[VM] LOAD_CONST done, new stackTop=32
[VM] opcode=1 operand=35
[VM] LOAD_CONST idx=35, globalConstants.size()=42, stackTop=32
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=32, val.type=1, val.value=0
[VM] push:   m_Stack[32].type=1, m_Stack[32].value=0
[VM] LOAD_CONST done, new stackTop=33
[VM] opcode=1 operand=36
[VM] LOAD_CONST idx=36, globalConstants.size()=42, stackTop=33
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=33, val.type=1, val.value=255
[VM] push:   m_Stack[33].type=1, m_Stack[33].value=255
[VM] LOAD_CONST done, new stackTop=34
[VM] opcode=31 operand=196609
[VM] opcode=2 operand=0
[VM] push: slot=34, val.type=1, val.value=0
[VM] push:   m_Stack[34].type=1, m_Stack[34].value=0
[VM] opcode=3 operand=0
[VM] opcode=2 operand=1
[VM] push: slot=34, val.type=1, val.value=0
[VM] push:   m_Stack[34].type=1, m_Stack[34].value=0
[VM] opcode=3 operand=1
[VM] opcode=2 operand=2
[VM] push: slot=34, val.type=1, val.value=255
[VM] push:   m_Stack[34].type=1, m_Stack[34].value=255
[VM] opcode=3 operand=2
[VM] opcode=2 operand=0
[VM] push: slot=34, val.type=1, val.value=0
[VM] push:   m_Stack[34].type=1, m_Stack[34].value=0
[VM] opcode=1 operand=18
[VM] LOAD_CONST idx=18, globalConstants.size()=42, stackTop=35
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=35, val.type=1, val.value=255
[VM] push:   m_Stack[35].type=1, m_Stack[35].value=255
[VM] LOAD_CONST done, new stackTop=36
[VM] opcode=7 operand=0
[VM] push: slot=34, val.type=1, val.value=-255
[VM] push:   m_Stack[34].type=1, m_Stack[34].value=-255
[VM] opcode=3 operand=3
[VM] opcode=1 operand=19
[VM] LOAD_CONST idx=19, globalConstants.size()=42, stackTop=34
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=34, val.type=1, val.value=36
[VM] push:   m_Stack[34].type=1, m_Stack[34].value=36
[VM] LOAD_CONST done, new stackTop=35
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=35
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=35 - paramCount=2 = localBase=33
[VM]   arg[0] -> stack[33] = 255
[VM]   arg[1] -> stack[34] = 36
[VM] Saving caller pc=12 before native call
[00:00:04.000] [DEBUG] analogWrite(255, 36)
[VM] Restored caller pc to 12 after native call
[VM] opcode=2 operand=1
[VM] push: slot=35, val.type=1, val.value=0
[VM] push:   m_Stack[35].type=1, m_Stack[35].value=0
[VM] opcode=1 operand=20
[VM] LOAD_CONST idx=20, globalConstants.size()=42, stackTop=36
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=36, val.type=1, val.value=255
[VM] push:   m_Stack[36].type=1, m_Stack[36].value=255
[VM] LOAD_CONST done, new stackTop=37
[VM] opcode=7 operand=0
[VM] push: slot=35, val.type=1, val.value=-255
[VM] push:   m_Stack[35].type=1, m_Stack[35].value=-255
[VM] opcode=3 operand=4
[VM] opcode=1 operand=21
[VM] LOAD_CONST idx=21, globalConstants.size()=42, stackTop=35
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=35, val.type=1, val.value=37
[VM] push:   m_Stack[35].type=1, m_Stack[35].value=37
[VM] LOAD_CONST done, new stackTop=36
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=36
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=36 - paramCount=2 = localBase=34
[VM]   arg[0] -> stack[34] = 36
[VM]   arg[1] -> stack[35] = 37
[VM] Saving caller pc=18 before native call
[00:00:04.000] [DEBUG] analogWrite(36, 37)
[VM] Restored caller pc to 18 after native call
[VM] opcode=2 operand=2
[VM] push: slot=36, val.type=1, val.value=255
[VM] push:   m_Stack[36].type=1, m_Stack[36].value=255
[VM] opcode=1 operand=22
[VM] LOAD_CONST idx=22, globalConstants.size()=42, stackTop=37
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=37, val.type=1, val.value=255
[VM] push:   m_Stack[37].type=1, m_Stack[37].value=255
[VM] LOAD_CONST done, new stackTop=38
[VM] opcode=7 operand=0
[VM] push: slot=36, val.type=1, val.value=0
[VM] push:   m_Stack[36].type=1, m_Stack[36].value=0
[VM] opcode=3 operand=5
[VM] opcode=1 operand=23
[VM] LOAD_CONST idx=23, globalConstants.size()=42, stackTop=36
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=36, val.type=1, val.value=35
[VM] push:   m_Stack[36].type=1, m_Stack[36].value=35
[VM] LOAD_CONST done, new stackTop=37
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=37
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=37 - paramCount=2 = localBase=35
[VM]   arg[0] -> stack[35] = 37
[VM]   arg[1] -> stack[36] = 35
[VM] Saving caller pc=24 before native call
[00:00:04.000] [DEBUG] analogWrite(37, 35)
[VM] Restored caller pc to 24 after native call
[VM] RETURN
[VM] opcode=1 operand=37
[VM] LOAD_CONST idx=37, globalConstants.size()=42, stackTop=36
[VM] LOAD_CONST entry.type=0, value.intVal=2000, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 2000 to stack
[VM] push: slot=36, val.type=1, val.value=2000
[VM] push:   m_Stack[36].type=1, m_Stack[36].value=2000
[VM] LOAD_CONST done, new stackTop=37
[VM] opcode=46 operand=65545
[VM] CALL_NATIVE: stringPoolIndex=9, paramCount=1, stackTop=37
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'delay'
[VM] Native function found
[VM] Argument calculation: stackTop=37 - paramCount=1 = localBase=36
[VM]   arg[0] -> stack[36] = 2000
[VM] Saving caller pc=23 before native call
[VM] Restored caller pc to 23 after native call
[VM] opcode=1 operand=38
[VM] LOAD_CONST idx=38, globalConstants.size()=42, stackTop=37
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=37, val.type=1, val.value=0
[VM] push:   m_Stack[37].type=1, m_Stack[37].value=0
[VM] LOAD_CONST done, new stackTop=38
[VM] opcode=1 operand=39
[VM] LOAD_CONST idx=39, globalConstants.size()=42, stackTop=38
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=38, val.type=1, val.value=0
[VM] push:   m_Stack[38].type=1, m_Stack[38].value=0
[VM] LOAD_CONST done, new stackTop=39
[VM] opcode=1 operand=40
[VM] LOAD_CONST idx=40, globalConstants.size()=42, stackTop=39
[VM] LOAD_CONST entry.type=0, value.intVal=0, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 0 to stack
[VM] push: slot=39, val.type=1, val.value=0
[VM] push:   m_Stack[39].type=1, m_Stack[39].value=0
[VM] LOAD_CONST done, new stackTop=40
[VM] opcode=31 operand=196609
[VM] opcode=2 operand=0
[VM] push: slot=40, val.type=1, val.value=0
[VM] push:   m_Stack[40].type=1, m_Stack[40].value=0
[VM] opcode=3 operand=0
[VM] opcode=2 operand=1
[VM] push: slot=40, val.type=1, val.value=0
[VM] push:   m_Stack[40].type=1, m_Stack[40].value=0
[VM] opcode=3 operand=1
[VM] opcode=2 operand=2
[VM] push: slot=40, val.type=1, val.value=0
[VM] push:   m_Stack[40].type=1, m_Stack[40].value=0
[VM] opcode=3 operand=2
[VM] opcode=2 operand=0
[VM] push: slot=40, val.type=1, val.value=0
[VM] push:   m_Stack[40].type=1, m_Stack[40].value=0
[VM] opcode=1 operand=18
[VM] LOAD_CONST idx=18, globalConstants.size()=42, stackTop=41
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=41, val.type=1, val.value=255
[VM] push:   m_Stack[41].type=1, m_Stack[41].value=255
[VM] LOAD_CONST done, new stackTop=42
[VM] opcode=7 operand=0
[VM] push: slot=40, val.type=1, val.value=-255
[VM] push:   m_Stack[40].type=1, m_Stack[40].value=-255
[VM] opcode=3 operand=3
[VM] opcode=1 operand=19
[VM] LOAD_CONST idx=19, globalConstants.size()=42, stackTop=40
[VM] LOAD_CONST entry.type=0, value.intVal=36, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 36 to stack
[VM] push: slot=40, val.type=1, val.value=36
[VM] push:   m_Stack[40].type=1, m_Stack[40].value=36
[VM] LOAD_CONST done, new stackTop=41
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=41
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=41 - paramCount=2 = localBase=39
[VM]   arg[0] -> stack[39] = 0
[VM]   arg[1] -> stack[40] = 36
[VM] Saving caller pc=12 before native call
[00:00:06.000] [DEBUG] analogWrite(0, 36)
[VM] Restored caller pc to 12 after native call
[VM] opcode=2 operand=1
[VM] push: slot=41, val.type=1, val.value=0
[VM] push:   m_Stack[41].type=1, m_Stack[41].value=0
[VM] opcode=1 operand=20
[VM] LOAD_CONST idx=20, globalConstants.size()=42, stackTop=42
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=42, val.type=1, val.value=255
[VM] push:   m_Stack[42].type=1, m_Stack[42].value=255
[VM] LOAD_CONST done, new stackTop=43
[VM] opcode=7 operand=0
[VM] push: slot=41, val.type=1, val.value=-255
[VM] push:   m_Stack[41].type=1, m_Stack[41].value=-255
[VM] opcode=3 operand=4
[VM] opcode=1 operand=21
[VM] LOAD_CONST idx=21, globalConstants.size()=42, stackTop=41
[VM] LOAD_CONST entry.type=0, value.intVal=37, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 37 to stack
[VM] push: slot=41, val.type=1, val.value=37
[VM] push:   m_Stack[41].type=1, m_Stack[41].value=37
[VM] LOAD_CONST done, new stackTop=42
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=42
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=42 - paramCount=2 = localBase=40
[VM]   arg[0] -> stack[40] = 36
[VM]   arg[1] -> stack[41] = 37
[VM] Saving caller pc=18 before native call
[00:00:06.000] [DEBUG] analogWrite(36, 37)
[VM] Restored caller pc to 18 after native call
[VM] opcode=2 operand=2
[VM] push: slot=42, val.type=1, val.value=0
[VM] push:   m_Stack[42].type=1, m_Stack[42].value=0
[VM] opcode=1 operand=22
[VM] LOAD_CONST idx=22, globalConstants.size()=42, stackTop=43
[VM] LOAD_CONST entry.type=0, value.intVal=255, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 255 to stack
[VM] push: slot=43, val.type=1, val.value=255
[VM] push:   m_Stack[43].type=1, m_Stack[43].value=255
[VM] LOAD_CONST done, new stackTop=44
[VM] opcode=7 operand=0
[VM] push: slot=42, val.type=1, val.value=-255
[VM] push:   m_Stack[42].type=1, m_Stack[42].value=-255
[VM] opcode=3 operand=5
[VM] opcode=1 operand=23
[VM] LOAD_CONST idx=23, globalConstants.size()=42, stackTop=42
[VM] LOAD_CONST entry.type=0, value.intVal=35, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 35 to stack
[VM] push: slot=42, val.type=1, val.value=35
[VM] push:   m_Stack[42].type=1, m_Stack[42].value=35
[VM] LOAD_CONST done, new stackTop=43
[VM] opcode=46 operand=131077
[VM] CALL_NATIVE: stringPoolIndex=5, paramCount=2, stackTop=43
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'analogWrite'
[VM] Native function found
[VM] Argument calculation: stackTop=43 - paramCount=2 = localBase=41
[VM]   arg[0] -> stack[41] = 37
[VM]   arg[1] -> stack[42] = 35
[VM] Saving caller pc=24 before native call
[00:00:06.000] [DEBUG] analogWrite(37, 35)
[VM] Restored caller pc to 24 after native call
[VM] RETURN
[VM] opcode=1 operand=41
[VM] LOAD_CONST idx=41, globalConstants.size()=42, stackTop=42
[VM] LOAD_CONST entry.type=0, value.intVal=999, value.doubleVal=0.000000
[VM] LOAD_CONST pushing INTEGER 999 to stack
[VM] push: slot=42, val.type=1, val.value=999
[VM] push:   m_Stack[42].type=1, m_Stack[42].value=999
[VM] LOAD_CONST done, new stackTop=43
[VM] opcode=46 operand=65543
[VM] CALL_NATIVE: stringPoolIndex=7, paramCount=1, stackTop=43
[VM] Stack contents: [0]=111 [1]=13 [2]=61 [3]=14 [4]=60 [5]=12 [6]=59 [7]=36 [8]=3 [9]=37 [10]=3 [11]=35 [12]=3 [13]=36 [14]=1 [15]=37 
[VM] Calling native function: 'println'
[VM] Native function found
[VM] Argument calculation: stackTop=43 - paramCount=1 = localBase=42
[VM]   arg[0] -> stack[42] = 999
[VM] Saving caller pc=29 before native call
999
[VM] Restored caller pc to 29 after native call
[VM] HALT
[00:00:06.000] [INFO] Script completed with result: 35
[00:00:06.000] [INFO] Entering main loop...
