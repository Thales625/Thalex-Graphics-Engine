def convert_obj_quads_to_tris(input_path, output_path):
    with open(input_path, 'r') as infile, open(output_path, 'w') as outfile:
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

input_file = "skull.obj"
output_file = "skull2.obj"
convert_obj_quads_to_tris(input_file, output_file)