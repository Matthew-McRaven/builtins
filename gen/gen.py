import os 
from pathlib import Path
import subprocess
def generate_figure(dir_name, path):
	helpers_path = Path(__file__).parent.absolute()
	path = Path(path)
	try:
		ch_fig = int(dir_name[0:4])
		ch, fig = ch_fig // 100, ch_fig % 100
		if ch > 10: return

		defines = []
		def generate(extension):
			ret = []
			ret.append(f"#define has_{extension}")
			ret.append(f'#include "./gen_{extension}.h"')
			subprocess.run(["xxd", "-i", f"{dir_name}.{extension}", f"gen_{extension}.h"], cwd=path)
			return ret

		if os.path.exists(path/"{dir_name}.pep"): defines.extend(generate("pep"))
		if os.path.exists(path/f"{dir_name}.pepl"): defines.extend(generate("pepl"))
		if os.path.exists(path/f"{dir_name}.c"): defines.extend(generate("c"))
		if os.path.exists(path/f"{dir_name}.pepb"): defines.extend(generate("pepb"))
		if os.path.exists(path/f"{dir_name}.peph"): defines.extend(generate("peph"))
		if os.path.exists(path/f"{dir_name}.pepo"): defines.extend(generate("pepo"))


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

def generate_file(file_path):
	if file_path.suffix != ".pepm": return
	helpers_path = Path(__file__).parent.absolute()
	def generate(macro_name):
		ret = []
		ret.append(f'#include "./gen_{macro_name}.h"')
		subprocess.run(["xxd", "-i", f"{macro_name}.pepm", f"gen_{macro_name}.h"], cwd=file_path.parent)
		return ret
	macro_name = file_path.with_suffix("").name
	defines = generate(macro_name)
	with open(helpers_path/"macro.cpp", "r") as body: body_text = body.read()
	body_text = body_text.format(macro_name = macro_name)
	with open(file_path.parent/f"reg_{macro_name}.cpp", "w") as out_file:
		for line in defines: out_file.write(line+"\n")
		out_file.write(body_text)

def generate_macro(directory, path):
	# Must recurse through subdirs to find macros ending in .pepm
	_1, directories, files = next(os.walk(path))
	# Generate CPP files for current files
	for f in files: generate_file(path/f)
	for directory in directories: generate_macro(path/directory, path/directory)

def main():
	path = Path(__file__)
	root = path.parent.absolute() / "../pep10"
	print(root)
	immediate_children = next(os.walk(root))[1]
	for directory in immediate_children:
		if "macro" in directory: generate_macro(directory, root/directory)
		else: generate_figure(directory, root/directory)

if __name__ == "__main__":
	main()