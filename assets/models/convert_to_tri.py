import sys

def convert_obj_to_tris(input_path, output_path):
    with open(input_path, 'r', encoding='utf-8') as infile, open(output_path, 'w', encoding='utf-8') as outfile:
        for line in infile:
            if line.startswith('f '):
                parts = line.strip().split()
                vertices = parts[1:]
                if len(vertices) > 3:
                    v1 = vertices[0]
                    for i in range(1, len(vertices) - 1):
                        v2 = vertices[i]
                        v3 = vertices[i + 1]
                        outfile.write(f"f {v1} {v2} {v3}\n")
                else:
                    outfile.write(line)
            else:
                outfile.write(line)

def convert_obj_quads_to_tris(input_path, output_path):
    with open(input_path, 'r', encoding='utf-8') as infile, open(output_path, 'w', encoding='utf-8') as outfile:
        for line in infile:
            if line.startswith('f '):
                parts = line.strip().split()
                if len(parts) == 5:
                    v1, v2, v3, v4 = parts[1:5]
                    outfile.write(f"f {v1} {v2} {v3}\n")
                    outfile.write(f"f {v1} {v3} {v4}\n")
                else:
                    outfile.write(line)
            else:
                outfile.write(line)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python quad_to_tri.py <input_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = input_file.replace('.obj', '_tri.obj')

    convert_obj_to_tris(input_file, output_file)
    # convert_obj_quads_to_tris(input_file, output_file)