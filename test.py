import wasmer

def write_str(instance, str):
    # Get a memory view
    m = instance.memory.int32_view()

    # Allocate space for our string (noting size of int32)
    ptr = instance.exports.malloc(len(str) * m.bytes_per_element)

    #
    for i, c in enumerate(str):
        m[ptr + m.bytes_per_element * i] = ord(c)

    return ptr

def read_str(instance, ptr, length):
    m = instance.memory.int32_view()

    ptr = ptr // m.bytes_per_element

    str = m[ptr:ptr+length]

    return ''.join(chr(c) for c in str)


if __name__ == '__main__':
    wasm_bytes = open('target.wasm', 'rb').read()

    ins = wasmer.Instance(wasm_bytes)

    print(ins.exports)

    # memory = ins.memory.int32_view(ins.exports.getData())

    str = 'hi_there'

    ptr = write_str(ins, str)

    print(read_str(ins, ptr, len(str)))

    ptr2 = write_str(ins, 'you')

    ptr3 = ins.exports.concat(ptr, ptr2, len(str), 3)
    print(read_str(ins, ptr3, len(str) + 3))

    ptr4 = write_str(ins, 'e')

    print(ins.exports.contains(ptr, ptr4, len(str), 1))