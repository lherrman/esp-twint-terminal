# Script to extract qr codes from pdf files and construct the qrdata.cpp and qrdata.h files
#
# Instructions:
# 1. Put all the pdf files in the source directory (qr_code_extractor/source)
# 2. Make sure there is a pdf file named default.pdf in the source directory
# 3. Run the script
# 4. The qrdata.cpp and qrdata.h files will automatically be copied to the 
#    src directory of the embedded software project (esp-twint-display/src)
# 5. Upload the embedded software to the esp32 with PlatformIO 


import glob
import os
import re

from pdf2image import convert_from_path
from PIL import Image
from pypdf import PdfReader
from pyzbar.pyzbar import decode

current_file_dir = os.path.dirname(os.path.realpath(__file__))
parent_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
cpp_source_dir = parent_dir + '/src'
cpp_file_path = cpp_source_dir + '/qrdata'
pdf_source_dir = current_file_dir + '/source'
img_dest_dir = current_file_dir + '/qr_images'
poppler_path = current_file_dir + r"\lib\poppler-23.01.0\Library\bin"

def delete_files(path, extension):
    files = glob.glob(path + f'/*.{extension}')
    for file in files:
        os.remove(file)

def convert_pdf_to_png(pdf_file_path):
    # Read Text and Convert to Image
    name = os.path.basename(pdf_file_path).split('.')[0]
    default_code = name == 'default'

    reader = PdfReader(pdf_file_path)    
    page = reader.pages[0]
    if not default_code:
        value, store_name = page.extract_text().splitlines()[0:2]
        value = float(value.split(' ')[-1])
    image = convert_from_path(pdf_file_path, poppler_path=poppler_path)[0]

    # Crop Image to QR Code Area
    x1, y1, x2, y2 = 136, 850, 545, 1261
    image = image.crop((x1, y1, x2, y2))

    # Save Image
    if not default_code:
        value = int(value * 100)
        file_name = f'qr{value:05}.png'
    else:
        file_name = f'default.png'

    path = f'{img_dest_dir}/{file_name}'
    image.save(f'{path}', 'PNG')
    print(f'{file_name} saved')
    return path

def main():
    delete_files(img_dest_dir, 'png')

    pdf_files = glob.glob(pdf_source_dir + '/*.pdf')
    if len(pdf_files) == 0:
        raise Exception('No pdf files found in source directory')
    
    # extract qr codes from pdf files
    images_paths = []
    for file in pdf_files:
        images_paths.append(convert_pdf_to_png(file))
    print('All qr codes extracted')

    # read the qr codes data
    qr_data = {}
    qr_data_default = ''
    for img in images_paths:
        file_name = os.path.basename(img).split('.')[0]
        if file_name == 'default':
            qr_data_default = decode(Image.open(img))[0].data.decode('utf-8')
            continue

        file_name = re.sub('[^0-9]', '', file_name)
        key = int(file_name) 
        qrdata = decode(Image.open(img))[0].data.decode('utf-8')
        qr_data[key] = qrdata
    print('All qr codes decoded')
    
    if qr_data_default == '':
        raise Exception('No default qr code found. Make sure there is a pdf file named default.pdf in the source directory')

    # construct the cpp and h files
    function_declaration = 'const char * get_qr_data(float price)'
    cpp_file_content = ''
    cpp_file_content += f'{function_declaration}\n'
    cpp_file_content += '{\n'
    cpp_file_content += '    int price_switch = (int)(price * 100);\n'
    cpp_file_content += '    switch (price_switch)\n'
    cpp_file_content += '    {\n'
    for price, value in qr_data.items():
        cpp_file_content += f'        case {price}:\n'
        cpp_file_content += f'            return "{value}";\n'
        cpp_file_content += '             break;\n'
    cpp_file_content += '        default:\n'
    cpp_file_content += f'            return "{qr_data_default}";\n' # TODO: change this to a default qr code (currently UNVALID)
    cpp_file_content += '            break;\n'
    cpp_file_content += '    }\n'
    cpp_file_content += '}\n'

    h_file_content = ''
    h_file_content += f'{function_declaration};\n'

    # write the cpp file
    with open(cpp_file_path + '.cpp', 'w') as f:
        f.write(cpp_file_content)
    with open(cpp_file_path + '.h', 'w') as f:
        f.write(h_file_content)
    print('qrdata.cpp and qrdata.h files created')


if __name__ == "__main__":
    main()

