Pasos para la instalación del entorno de AMPE:
1. Instalar Anaconda
   1.1. Ir a https://www.anaconda.com/products/individual
   2.2. Descargar fichero para Linux Anaconda3-2020.11-Linux-x86_64.sh
   2.3. bash Anaconda3-2020.11-Linux-x86_64.sh
   2.4. Seguir los pasos del instalador. 

2. Instalar pytorch-frontend
    2.1. cd pytorch-frontend
    2.2. Instalar dependencias: conda install numpy ninja pyyaml mkl mkl-include setuptools cmake cffi typing_extensions future six requests dataclasses
    2.3. Instalar el framework: 
         export CMAKE_PREFIX_PATH=${CONDA_PREFIX:-"$(dirname $(which conda))/../"}
         python setup.py install (ver README en pytorch-frontend si se produce algun error)
3. Instalar vision (ver su README)
   3.1. cd vision
   3.2. python setup.py install 
3. Instalar elementos personalizados para las prácticas
   3.1. cd practica2
   3.2. ./compile_practica2.sh install
   
Si la operación ha funcionado correctamente, deberemos de ser capaces de importar las librerías torch y torch_stonne en un interprete de python. Tal que así:
alumno@lab27:~$ python
Python 2.7.18rc1 (default, Apr  7 2020, 12:05:55) 
[GCC 9.3.0] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import torch
>>>
>>> import torch_stonne
>>>
