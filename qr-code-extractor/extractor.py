from PIL import Image
from pypdf import PdfReader
from pdf2image import convert_from_path
import glob
import os, re

current_file_dir = os.path.dirname(os.path.realpath(__file__))
parent_dir = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
cpp_source_dir = parent_dir + '/src'
cpp_file_path = cpp_source_dir + '/main.cpp'
pdf_source_dir = current_file_dir + '/source'
img_dest_dir = current_file_dir + '/lvgl_image_converter\images'
poppler_path = current_file_dir + r"\lib\poppler-23.01.0\Library\bin"

def delete_files(path, extension):
    files = glob.glob(path + f'/*.{extension}')
    for file in files:
        os.remove(file)

def convert_pdf_to_png(pdf_file_path):
    # Read Text and Convert to Image
    reader = PdfReader(pdf_file_path)    
    page = reader.pages[0]
    value, store_name = page.extract_text().splitlines()[0:2]
    value = float(value.split(' ')[-1])
    image = convert_from_path(pdf_file_path, poppler_path=poppler_path)[0]

    # Crop Image to QR Code Area
    x1, y1, x2, y2 = 136, 850, 545, 1261
    image = image.crop((x1, y1, x2, y2))

    # resize image to 320x320 and convert to black and white
    image = image.resize((320, 320), Image.NEAREST)
    image = image.convert('1')

    # Save Image
    value = int(value * 100)
    file_name = f'qr{value:05}.png'
    image.save(f'{img_dest_dir}/{file_name}', 'PNG')
    print(f'{file_name} saved')
    return file_name

def main():

    # Delete old binary and image files
    delete_files(cpp_source_dir, 'c')
    delete_files(img_dest_dir, 'png')

    # Convert PDFs to PNGs and save them in the image directory
    filenames = [] 
    for file in glob.glob(pdf_source_dir + '/*.pdf'):
        file_name = convert_pdf_to_png(file)
        filenames.append(file_name)

    # Run the image to binary converter
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    os.chdir('./lvgl_image_converter')
    #os.system('python3 lv_img_conv.py -f indexed_8 -ff C -o ../../src -r ./images')
    os.system('python3 lv_img_conv.py -f indexed_4 -cf RGB332 -ff C -o ../../src -r ./images')

    # Replace the switch statement in the CPP main file
    new_function = '''void load_qr_code(float price)
{
    /* Create an image object */
    lv_obj_t *img1 = lv_img_create( lv_scr_act() );
    int price_switch = (int)(price*100);
    switch (price_switch)
    {
'''
    for file in filenames:
        name = file.split('.')[0]
        value = int(name[2:])
        new_function += f'''    case {value}:
        LV_IMG_DECLARE({name});
        lv_img_set_src(img1, &{name});
        break;
'''
    new_function += '''
    }
'''

    # Open the CPP file and read its contents
    with open(cpp_file_path, "r") as f:
        file_contents = f.read()

    # Use a regular expression to find the old function
    function_name = "load_qr_code"
    pattern = r"void\s+" + function_name + r"\s*\([\s\S]*?\}\s*\n"
    old_function_match = re.search(pattern, file_contents)

    if old_function_match:
        # Replace the old function with the new function
        file_contents = re.sub(pattern, new_function, file_contents)

        # Save the modified CPP file
        with open(cpp_file_path, "w") as f:
            f.write(file_contents)
        
        print(f"Function {function_name} replaced in main.cpp")
    else:
        print("Function not found in file.")

    print("Done")


if __name__ == "__main__":
    main()

