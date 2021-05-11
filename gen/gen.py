import os 

def generate(dir_name, path):
	try:
		ch_fig = int(dir_name[0:4])
		ch, fig = ch_fig // 100, ch_fig % 100
		if ch > 10: return

		defines = []
		if os.path.exists(os.path.join(path, f"{dir_name}.pep")): defines.append("#define has_pep")
		if os.path.exists(os.path.join(path, f"{dir_name}.pepl")): defines.append("#define has_pepl")
		if os.path.exists(os.path.join(path, f"{dir_name}.c")): defines.append("#define has_c")
		if os.path.exists(os.path.join(path, f"{dir_name}.pepb")): defines.append("#define has_pepb")
		if os.path.exists(os.path.join(path, f"{dir_name}.peph")): defines.append("#define has_peph")
		if os.path.exists(os.path.join(path, f"{dir_name}.pepo")): defines.append("#define has_pepo")

		with open("header.cpp", "r") as header: header_text = header.read()
		with open("body.cpp", "r") as body: body_text = body.read()
		header_text = header_text.format(ch_num=ch, proc_name="pep10", fig_num=fig, dir_name = dir_name)
		body_text = body_text.format(dir_name = dir_name)
		with open(os.path.join(path, "reg.cpp"), "w") as out_file:
			out_file.write(header_text)
			for line in defines: out_file.write(line+"\n")
			out_file.write(body_text)
		
			
		
	except ValueError: return
	files = {}

def main():
	root = '../pep10'
	immediate_children = next(os.walk(root))[1]
	for directory in immediate_children:
		generate(directory, os.path.join(root, directory))

if __name__ == "__main__":
	main()