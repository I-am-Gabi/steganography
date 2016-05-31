import os
from os import path

directories = [name for name in os.listdir(".") if os.path.isdir(name)]

for direc in directories:
	files = [x for x in os.listdir(direc) if path.isfile(direc + os.sep + x)]
	for f in files:
		os.system("file "+direc+"/" + f)
