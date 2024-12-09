import os
import argparse
import re


parse_args = argparse.ArgumentParser()
parse_args.add_argument('-d','--day')
parse_args.add_argument('-t', '--template', required=False, default=0)
args = parse_args.parse_args()
day = args.day
template = args.template

expr = f"([Dd]ay\s?){template}"
subs = re.compile(expr)

folder = f"Day{day}"
template_folder = f"Day{template}"

print(f"Using {template_folder} as template")
print(f"Making '{folder}'")
os.mkdir(folder)

files = os.listdir(template_folder)
for f in files:
    src_path = os.path.join(template_folder, f)
    dst_file = subs.sub("\g<1>"+day, f)
    dst_path = os.path.join(folder, dst_file)
    with open(src_path) as src:
        with open(dst_path, "w") as dst:
            for line in src:
                new_line = subs.sub("\g<1>"+day, line)
                dst.write(new_line)

with open("CMakeLists.txt", "a") as f:
    f.write(os.linesep)
    f.write(f"add_subdirectory(Day{day})")