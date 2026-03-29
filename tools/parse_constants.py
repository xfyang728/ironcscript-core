import struct

with open('d:/MyCode/CScriptEngine/examples/K210Test/rgb_test_arduino.csb', 'rb') as f:
    data = f.read()

print(f'File size: {len(data)} bytes')

header_size = 24
func_header_size = 20
instr_size = 5

# Calculate function starts
func_starts = []
offset = header_size
for i in range(3):
    func_starts.append(offset)
    instr_count = struct.unpack('<I', data[offset+16:offset+20])[0]
    offset += func_header_size + instr_count * instr_size
    if offset < len(data):
        const_count = struct.unpack('<I', data[offset:offset+4])[0]
        offset += 4 + const_count * 9

# Parse main function (func 2)
func2_start = func_starts[2]
print(f'\n=== Function 2 (main) at offset 0x{func2_start:02X} ===')
instr_count = struct.unpack('<I', data[func2_start+16:func2_start+20])[0]
instr_start = func2_start + func_header_size

# Global constants
const_data_offset = instr_start + instr_count * instr_size + 4
print(f'\n=== Global Constants at 0x{const_data_offset:02X} ===')
global_const_count = struct.unpack('<I', data[const_data_offset:const_data_offset+4])[0]
print(f'globalConstCount = {global_const_count}')

offset = const_data_offset + 4
constants = []
for i in range(global_const_count):
    type_byte = data[offset]
    if type_byte == 0:  # INTEGER
        val = struct.unpack('<q', data[offset+1:offset+9])[0]
        constants.append(('INTEGER', val))
        print(f'  [{i:2d}] INTEGER = {val}')
        offset += 9
    elif type_byte == 1:  # DOUBLE
        val = struct.unpack('<d', data[offset+1:offset+9])[0]
        constants.append(('DOUBLE', val))
        print(f'  [{i:2d}] DOUBLE = {val}')
        offset += 9
    elif type_byte == 2:  # STRING
        str_offset = struct.unpack('<I', data[offset+1:offset+5])[0]
        constants.append(('STRING', str_offset))
        print(f'  [{i:2d}] STRING offset = {str_offset}')
        offset += 5
    elif type_byte == 3:  # FUNCTION
        func_idx = struct.unpack('<I', data[offset+1:offset+5])[0]
        constants.append(('FUNCTION', func_idx))
        print(f'  [{i:2d}] FUNCTION idx = {func_idx}')
        offset += 5
    else:
        print(f'  [{i:2d}] UNKNOWN type = {type_byte}')
        break

# String pool
string_pool_offset = offset
print(f'\n=== String Pool at 0x{string_pool_offset:02X} ===')
string_count = struct.unpack('<I', data[string_pool_offset:string_pool_offset+4])[0]
print(f'stringCount = {string_count}')

strings = []
str_offset = string_pool_offset + 4
for i in range(string_count):
    str_len = struct.unpack('<I', data[str_offset:str_offset+4])[0]
    str_offset += 4
    str_data = data[str_offset:str_offset+str_len]
    str_value = str_data.decode('utf-8', errors='replace').rstrip('\x00')
    strings.append(str_value)
    print(f'  [{i}] "{str_value}" (len={str_len})')
    str_offset += str_len

# Decode instructions
print(f'\n=== Instruction Decode (main) ===')
print(f'Instructions at 0x{instr_start:02X}, count={instr_count}')
for i in range(min(instr_count, 30)):
    instr_offset = instr_start + i * instr_size
    opcode = data[instr_offset]
    operand = struct.unpack('<I', data[instr_offset+1:instr_offset+5])[0]
    op_name = ['NOP','LOAD_CONST','LOAD_VAR','STORE_VAR','LOAD_GLOBAL','STORE_GLOBAL',
               'ADD','SUB','MUL','DIV','MOD','NEG','NOT','BITAND','BITOR','BITXOR',
               'BITNOT','SHL','SHR','LT','GT','LE','GE','EQ','NE','LAND','LOR',
               'JUMP','JUMP_IF','CALL','RET','HALT','PUSH','POP','CALL_NATIVE'][opcode] if opcode < 32 else f'OP{opcode}'
    print(f'  [{i:2d}] {op_name:12s} operand={operand}', end='')
    if opcode == 1:  # LOAD_CONST
        if operand < len(constants):
            c = constants[operand]
            if c[0] == 'STRING':
                str_val = strings[c[1]] if c[1] < len(strings) else '?'
                print(f'  // STRING="{str_val}"', end='')
            elif c[0] == 'INTEGER':
                print(f'  // INTEGER={c[1]}', end='')
            elif c[0] == 'FUNCTION':
                print(f'  // FUNCTION idx={c[1]}', end='')
            else:
                print(f'  // {c[0]}={c[1]}', end='')
    elif opcode == 46:  # CALL_NATIVE
        paramCount = operand >> 16
        nameIdx = operand & 0xFFFF
        print(f'  // paramCount={paramCount}, nameIdx={nameIdx}', end='')
        if nameIdx < len(strings):
            print(f' ({strings[nameIdx]})', end='')
    print()
    if opcode == 30:  # HALT
        break