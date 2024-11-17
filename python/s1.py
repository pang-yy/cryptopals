import base64
import string


def xor_func(h1: str, h2: str) -> str:
    return bytes(x ^ y for x, y in zip(bytes.fromhex(h1), bytes.fromhex(h2))).hex()


def singleByteXor(data: str, key: str) -> bytes:
    correctKey = (key * len(data)).encode()
    byteString = bytes.fromhex(data)
    return bytes(x ^ y for x, y in zip(correctKey, byteString))


def repeatingKeyXor():
    pass


def hammingDist(x: bytes, y: bytes) -> int:
    count = 0

    # if different length
    if (len(x) != len(y)):
        count += abs(len(x) - len(y)) * 8
        if (len(x) > len(y)):
            x = x[:len(y)]
        else:
            y = y[:len(x)]

    # xyXor = bytearray(a ^ b for a,b in zip(x.encode(), y.encode()))
    xyXor = bytearray(a ^ b for a, b in zip(x, y))
    for byte in xyXor:
        while (byte != 0):
            count += 1
            byte = byte & (byte - 1)

    return count

def s1c1():
    hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
    answer = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

    result = base64.b64encode(bytes.fromhex(hexString)).decode()

    return (result == answer)


def s1c2():
    hexString1 = "1c0111001f010100061a024b53535009181c"
    hexString2 = "686974207468652062756c6c277320657965"
    answer = "746865206b696420646f6e277420706c6179"

    result = xor_func(hexString1, hexString2)

    return (result == answer)


def s1c3():
    hexString = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
    byteString = bytes.fromhex(hexString)
    inputLength = len(byteString)

    charList = string.printable
    for char in charList:
        key = (char * inputLength).encode()
        r = bytes(x ^ y for x, y in zip(key, byteString))
        # print(f"[{char}]:", end=" ")
        # print(r)

    # The answer should be: Cooking MC's like a pound of bacon


def s1c4():
    with open("4.txt", "r") as f, open("4.out", "w") as g:
        for hexString in f:
            byteString = bytes.fromhex(hexString.strip())
            inputLength = len(byteString)

            charList = string.printable
            for char in charList:
                key = (char * inputLength).encode()
                r = bytes(x ^ y for x, y in zip(key, byteString))
                try:
                    g.write(r.decode() +
                            f"\tKey: {char}, hex: {hexString}" + "\n")
                except UnicodeDecodeError:
                    # g.write("Not writable\n")
                    pass

    # The answer should be: Now that the party is jumping\n


def s1c5():
    key = b"ICE"
    text = """Burning 'em, if you ain't quick and nimble
I go crazy when I hear a cymbal"""
    answer = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"

    repeatedKey = (key * (len(text) // len(key))) + \
        key  # extra will be ignore in zip
    result = bytes(x ^ y for x, y in zip(repeatedKey, text.encode())).hex()

    return (result == answer)


def s1c6():
    encryptedBytes = base64.b64decode(open("6.txt", "r").read())

    # find keysize
    keysize = 0
    minDist = 100
    for i in range(2, 41):
        firstFewBits = encryptedBytes[:i]
        nextFewBits = encryptedBytes[i:i * 2]
        dist = hammingDist(firstFewBits, nextFewBits)
        if (dist/i < minDist):
            minDist = dist/i
            keysize = i

    # byteList = [encryptedBytes[i:i+keysize]
    #             for i in range(0, len(encryptedBytes), keysize)]
    # byteListA = bytearray(encryptedBytes)[0:keysize]
    # print(byteListA)
    keysize = 29
    for i in range(keysize):
        print("===============================")
        block = b''

        # Transpose the blocks: make a block that is the i-th byte of every block
        for j in range(i, len(encryptedBytes), keysize):
            block += bytes([encryptedBytes[j]])

        # Solve each block as if it was single-character XOR
        # key += bytes([singlechar_xor_brute_force(block)['key']])
        key = b'Terminator X: Bring the noise'
        r = bytes(x ^ y for x, y in zip(key, block))
        with open("6.out", "a") as outFile:
            outFile.writelines(r.decode())
        # charList = string.printable
        # for char in charList:
        #     key = (char * keysize).encode()
        #     r = bytes(x ^ y for x, y in zip(key, block))
        #     try:
        #         # g.write(r.decode() +
        #         #         f"\tKey: {char}, hex: {hexString}" + "\n")
        #         print(r.decode() + f"\tKey: {char}")
        #     except UnicodeDecodeError:
        #         # g.write("Not writable\n")
        #         pass


"""
    transposedByteList = list(zip(*byteList))
    assert(byteList[0][0] == transposedByteList[0][0]), "transpose failed"
    assert(byteList[0][1] == transposedByteList[1][0]), "transpose failed"
    print(transposedByteList)
"""


def main():
    # s1c1()
    # s1c2()
    # s1c3()
    # s1c4()
    # s1c5()
    s1c6()


if __name__ == "__main__":
    main()
