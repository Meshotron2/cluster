import sys


def print_file(f):
    x = int.from_bytes(f.read(2), "big")
    y = int.from_bytes(f.read(2), "big")
    z = int.from_bytes(f.read(2), "big")
    print(f"x, y, z: {x}, {y}, {z}")

    f = int.from_bytes(f.read(4), "big")
    print(f"f: {f}")


if __name__ == "__main__":
    files = sys.argv[1:]
    
    for fname in files:
        with open(fname, 'rb') as f:
            print(fname)
            print_file(f)
            print("\n")
