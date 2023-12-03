# Script to move all files from the subdirectories of a 
# directory to the directory itself and delete the subdirectories:
#
# All files in the subdirectories of the working directory will be moved to the working directory.

import os
import shutil
import glob

current_file_dir = os.path.dirname(os.path.realpath(__file__))
working_dir = current_file_dir + '/source/folders'

for root, dirs, files in os.walk(working_dir):
    for file in files:
        shutil.move(os.path.join(root, file), working_dir)

for dir in glob.glob(working_dir + '/*/'):
    shutil.rmtree(dir)

