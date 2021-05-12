import os 
from pathlib import Path
import subprocess
def generate(dir_name, path):
	helpers_path = Path(__file__).parent.absolute()
	path = Path(path)
	try:
		ch_fig = int(dir_name[0:4])
		ch, fig = ch_fig // 100, ch_fig % 100
		if ch > 10: return

		defines = []
		if os.path.exists(os.path.join(path, f"{dir_name}.pep")): 
			defines.append("#define has_pep")
			defines.append('#include "./gen_pep.h"')
			subprocess.run(["xxd", "-i", f"{dir_name}.pep", f"gen_pep.h"], cwd=path)
			
		if os.path.exists(os.path.join(path, f"{dir_name}.pepl")):
			defines.append("#define has_pepl")
			defines.append('#include "./gen_pepl.h"')
			subprocess.run(["xxd", "-i", f"{dir_name}.pepl", f"gen_pepl.h"], cwd=path)

		if os.path.exists(os.path.join(path, f"{dir_name}.c")):
			defines.append("#define has_c")
			defines.append('#include "./gen_c.h"')
			subprocess.run(["xxd", "-i", f"{dir_name}.c", f"gen_c.h"], cwd=path)

		if os.path.exists(os.path.join(path, f"{dir_name}.pepb")):
			defines.append("#define has_pepb")
			defines.append('#include "./gen_pepb.h"')
			subprocess.run(["xxd", "-i", f"{dir_name}.pepb", f"gen_pepb.h"], cwd=path)

		if os.path.exists(os.path.join(path, f"{dir_name}.peph")):
			defines.append("#define has_peph")
			defines.append('#include "./gen_peph.h"')
			subprocess.run(["xxd", "-i", f"{dir_name}.peph", f"gen_peph.h"], cwd=path)

		if os.path.exists(os.path.join(path, f"{dir_name}.pepo")):
			defines.append("#define has_pepo")
			defines.append('#include "./gen_pepo.h"')
			subprocess.run(["xxd", "-i", f"{dir_name}.pepo", f"gen_pepo.h"], cwd=path)


		for ctr in range(1000):
			if os.path.exists(path/f"io{ctr}/output.txt"):
				defines.append(f"#define has_out{ctr}")
				defines.append(f'#include "./gen_output{ctr}.h"')
				subprocess.run(["xxd", "-i", f"{dir_name}/io{ctr}/output.txt", f"{dir_name}/gen_output{ctr}.h"], cwd=path.parent)
			else: break;
			if os.path.exists(path/f"io{ctr}/input.txt"):
				defines.append(f"#define has_in{ctr}")
				defines.append(f'#include "./gen_input{ctr}.h"')
				subprocess.run(["xxd", "-i", f"{dir_name}/io{ctr}/input.txt", f"{dir_name}/gen_input{ctr}.h"], cwd=path.parent)

		with open(helpers_path/"header.cpp", "r") as header: header_text = header.read()
		with open(helpers_path/"body.cpp", "r") as body: body_text = body.read()
		header_text = header_text.format(ch_num=ch, proc_name="pep10", fig_num=fig, dir_name = dir_name)
		body_text = body_text.format(dir_name = dir_name)
		with open(os.path.join(path, "reg.cpp"), "w") as out_file:
			out_file.write(header_text)
			for line in defines: out_file.write(line+"\n")
			out_file.write(body_text)
		
			
		
	except ValueError: return
	files = {}

def main():
	path = Path(__file__)
	root = path.parent.absolute() / "../pep10"
	print(root)
	immediate_children = next(os.walk(root))[1]
	for directory in immediate_children:
		generate(directory, os.path.join(root, directory))

if __name__ == "__main__":
	main()