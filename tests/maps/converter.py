#!/usr/bin/env python3
"""
Convert an OBJ to a miniRT .rt mesh (triangle list).
Triangles are emitted as:
tr x1,y1,z1 x2,y2,z2 x3,y3,z3 R,G,B
Default color: 255,255,255
Usage: python3 obj2rt.py suzanne.obj suzanne.rt
"""
import sys

def parse_obj(inpath):
    verts = []
    faces = []
    with open(inpath, 'r') as f:
        for line in f:
            if line.startswith('v '):
                parts = line.split()
                x,y,z = parts[1:4]
                verts.append((float(x), float(y), float(z)))
            elif line.startswith('f '):
                parts = line.strip().split()[1:]
                idxs = []
                for p in parts:
                    # p can be v, v/vt, v//vn, v/vt/vn
                    v = p.split('/')[0]
                    idxs.append(int(v) - 1)  # OBJ is 1-based
                faces.append(idxs)
    return verts, faces

def write_rt(outpath, verts, faces, color=(255,255,255)):
    with open(outpath, 'w') as out:
        out.write("# Converted from OBJ — triangles only, materials ignored\n")
        out.write("# Default color: {0},{1},{2}\n".format(*color))
        for face in faces:
            if len(face) < 3:
                continue
            # fan triangulation: (0, i, i+1)
            v0 = verts[face[0]]
            for i in range(1, len(face)-1):
                v1 = verts[face[i]]
                v2 = verts[face[i+1]]
                s = "tr {0},{1},{2} {3},{4},{5} {6},{7},{8} {9},{10},{11}\n".format(
                    v0[0], v0[1], v0[2],
                    v1[0], v1[1], v1[2],
                    v2[0], v2[1], v2[2],
                    color[0], color[1], color[2]
                )
                out.write(s)

def main():
    if len(sys.argv) != 3:
        print("Usage: obj2rt.py input.obj output.rt")
        sys.exit(1)
    inp, outp = sys.argv[1], sys.argv[2]
    verts, faces = parse_obj(inp)
    write_rt(outp, verts, faces)
    print(f"Wrote {outp} ({len(faces)} faces, {len(verts)} vertices)")

if __name__ == '__main__':
    main()