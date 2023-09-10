from PIL import Image
from pypdf import PdfReader
from pdf2image import convert_from_path
import glob
import cv2

source_path = './source'
dest_path = './dest'
poppler_path = r".\lib\poppler-23.01.0\Library\bin"
files = glob.glob(source_path + '/*.pdf')
for file in files:
    # Read Text and Convert to Image
    reader = PdfReader(file)    
    page = reader.pages[0]
    value, store_name = page.extract_text().splitlines()[0:2]
    value = float(value.split(' ')[-1])
    image = convert_from_path(file, poppler_path=poppler_path)[0]

    # use opencv to find the QR code area


    # Crop Image to QR Code Area
    x1, y1, x2, y2 = 136, 850, 545, 1261
    image = image.crop((x1, y1, x2, y2))

    # resize image to 320x320
    image = image.resize((320, 320), Image.ANTIALIAS)

    # Save Image
    file_name = f'{store_name.replace(" ", "_")}_{value:05.2f}CHF.png'
    image.save(f'{dest_path}/{file_name}', 'PNG')
    print(f'{file_name} saved')