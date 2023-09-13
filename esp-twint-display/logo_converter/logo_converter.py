from PIL import Image
from pypdf import PdfReader
from pdf2image import convert_from_path
import glob
import os, re
import shutil
import subprocess

current_file_dir = os.path.dirname(os.path.realpath(__file__))
parent_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
lvgl_converter_image_dir = current_file_dir + '/lvgl_image_converter/images'
logo_source_dir = current_file_dir + '/source'
logo_destination_dir = current_file_dir + '/dest'


def delete_files(path, extension):
    files = glob.glob(path + f'/*.{extension}')
    for file in files:
        os.remove(file)


def main():

    # Delete old binary and image files
    delete_files(lvgl_converter_image_dir, 'png')
    delete_files(logo_destination_dir, 'bin')

    source_image_files = glob.glob(logo_source_dir + '/*')

    if len(source_image_files) == 0:
        raise Exception('No image files found in source directory')
    if len(source_image_files) > 1:
        print('Warning: More than one image file found in source directory. Only the first file will be used.')

    for file in source_image_files[:1]:
        #shutil.copy(file, lvgl_converter_image_dir)
        # rename file to logo.png using shutil.move()
        shutil.copy(file, lvgl_converter_image_dir + '/twint_logo.png')
    
    # Run the image to binary converter
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    os.chdir('./lvgl_image_converter')
    subprocess.run(['python', 'lv_img_conv.py', '-f', 'indexed_8', '-cf', 'RGB332', '-ff', 'C', '-o', '../dest', '-r', './images'])


if __name__ == "__main__":
    main()

