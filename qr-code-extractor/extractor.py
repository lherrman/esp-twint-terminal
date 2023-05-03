from PIL import Image
from pypdf import PdfReader
from pdf2image import convert_from_path
import glob
import cv2
import os

def delete_files(path, extension):
    files = glob.glob(path + f'/*.{extension}')
    for file in files:
        os.remove(file)

# Define paths
current_file_path = os.path.dirname(os.path.realpath(__file__))
parent_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
cpp_source_path = parent_dir + '/src'
source_path = current_file_path + '/source'
dest_path = current_file_path + '/lvgl_image_converter\images'
poppler_path = current_file_path + r"\lib\poppler-23.01.0\Library\bin"

# Delete old files
delete_files(cpp_source_path, 'bin')

filenames = []

files = glob.glob(source_path + '/*.pdf')
for file in files:
    # Read Text and Convert to Image
    reader = PdfReader(file)    
    page = reader.pages[0]
    value, store_name = page.extract_text().splitlines()[0:2]
    value = float(value.split(' ')[-1])
    image = convert_from_path(file, poppler_path=poppler_path)[0]

    # Crop Image to QR Code Area
    x1, y1, x2, y2 = 136, 850, 545, 1261
    image = image.crop((x1, y1, x2, y2))

    # resize image to 320x320
    image = image.resize((320, 320), Image.ANTIALIAS)

    # Save Image
    value = int(value * 100)
    file_name = f'qr{value:05}.png'
    image.save(f'{dest_path}/{file_name}', 'PNG')
    print(f'{file_name} saved')
    filenames.append(file_name)

# change to the directory of the script
os.chdir(os.path.dirname(os.path.abspath(__file__)))
# change to the directory of the converter
os.chdir('./lvgl_image_converter')
# run the converter
os.system('python3 lv_img_conv.py -f true_color_alpha -cf RGB888 -ff BIN -o ../../src -r ./images')
# delete old files
delete_files(dest_path, 'png')

# Create C++ Source File

with open(f'{cpp_source_path}/qr_codes.cpp', 'w') as f:
    f.write('void load_qr_code(float price) \n{\n')
    f.write('/* Create an image object */\n')
    f.write('lv_obj_t *img1 = lv_img_create( lv_scr_act() );\n\n')
    f.write('int price_switch = (int)(price*100);\n')
    f.write('switch (price_switch)\n{\n')
    for file in filenames:
        name = file.split('.')[0]
        value = int(name[2:])
        f.write(f'  case {value}:\n')
        f.write(f'    LV_IMG_DECLARE({name})\n')
        f.write(f'    lv_img_set_src(img1, &{name});\n')
        f.write('    break;\n')
    f.write('  }\n}\n')
    f.close()

# 



