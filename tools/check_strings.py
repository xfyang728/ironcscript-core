import struct

with open('d:/MyCode/CScriptEngine/examples/K210Test/rgb_test_arduino.csb', 'rb') as f:
    data = f.read()

# String pool is at offset 0x352
string_pool_offset = 0x352
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

print('\nConstants at indices 2, 4, 5:')
print(f'  [2] STRING offset = 2 -> "{strings[2]}"')
print(f'  [4] STRING offset = 4 -> "{strings[4]}"')
print(f'  [5] STRING offset = 5 -> "{strings[5]}"')