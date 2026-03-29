import struct

with open('d:/MyCode/CScriptEngine/examples/K210Test/debug_test_arduino.csb', 'rb') as f:
    data = f.read()

print(f'File size: {len(data)} bytes')
print(f'Magic: {data[0:4]}')
print(f'funcCount: {struct.unpack("<I", data[8:12])[0]}')
print(f'totalConstants: {struct.unpack("<I", data[16:20])[0]}')
print(f'stringPoolSize: {struct.unpack("<I", data[12:16])[0]}')

# Find global constants after functions
func_count = struct.unpack("<I", data[8:12])[0]
const_count = struct.unpack("<I", data[16:20])[0]
print(f'\nfuncCount={func_count}, constCount={const_count}')

# Global constants start at offset 0x109 based on log
gc_start = 0x109
print(f'\nGlobal constants at 0x{gc_start:x}:')
idx = 0
offset = gc_start
for i in range(min(const_count, 15)):
    type_byte = data[offset]
    print(f'  [{i}] type={type_byte}', end='')
    if type_byte == 0:  # INTEGER
        val = struct.unpack('<q', data[offset+1:offset+9])[0]
        print(f' INTEGER={val}')
        offset += 9
    elif type_byte == 3:  # FUNCTION
        val = struct.unpack('<I', data[offset+1:offset+5])[0]
        print(f' FUNCTION idx={val}')
        offset += 5
    else:
        print(f' (other)')
        offset += 9

# String pool - find by scanning for string length prefixes
print('\nSearching for string pool...')
for addr in range(0x150, len(data) - 10):
    if data[addr] == 6 and data[addr+1] == 0 and data[addr+2] == 0 and data[addr+3] == 0:
        # Possible string count
        str_count = struct.unpack('<I', data[addr:addr+4])[0]
        if 4 < str_count < 20:
            print(f'  Found stringCount={str_count} at 0x{addr:x}')