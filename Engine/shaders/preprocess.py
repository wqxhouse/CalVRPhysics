import glob
import os
import re
import fileinput

os.chdir(".")
types = ('*.vert', '*.frag');
for files_ext in types: 
	for filename in glob.glob(files_ext) :
		for line in fileinput.input(filename, inplace=True) :
			if "#version" in line :
				print line + "#extension GL_ARB_texture_rectangle : enable\n",;
				continue;
			print line,;

	
