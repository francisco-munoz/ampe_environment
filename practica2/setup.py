from setuptools import setup, Extension
from torch.utils import cpp_extension
import os

practica2_src_dir='src'


list_of_src_files_to_link=['practica2_connection/torch_practica2.cpp']

#Appending STONNE code to the list in order to link the sources
for filename in os.listdir(practica2_src_dir):
    if((filename != "main.cpp") and (filename.endswith("cpp"))):
        filename_path = os.path.join(practica2_src_dir, filename)
        #print(filename_path)
        list_of_src_files_to_link.append(filename_path)

print(list_of_src_files_to_link)

setup(name='torch_practica2',
      ext_modules=[cpp_extension.CppExtension('torch_practica2', list_of_src_files_to_link, include_dirs=['include'])],
      cmdclass={'build_ext': cpp_extension.BuildExtension})
