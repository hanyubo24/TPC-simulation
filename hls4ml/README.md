# hls4ml-tutorial: Tutorial notebooks for `hls4ml`


[![Jupyter Book Badge](https://jupyterbook.org/badge.svg)](https://fastmachinelearning.org/hls4ml-tutorial)
![deploy-book](https://github.com/fastmachinelearning/hls4ml-tutorial/actions/workflows/deploy.yml/badge.svg)
[![Code style: black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/fastmachinelearning/hls4ml-tutorial)


There are several ways to run the tutorial notebooks:
## Online
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/fastmachinelearning/hls4ml-tutorial/HEAD)

## Conda
Running the tutorials requires AMD Vitis HLS to be installed, see [here](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vitis.html).
After the installation, the necessary environmental variables can be set using
```
source /path/to/your/installtion/Xilinx/Vitis_HLS/202X.X/settings64.(c)sh
```

The Python environment used for the tutorials is specified in the `environment.yml` file.
It can be setup like:
```bash
conda env create -f environment.yml
conda activate hls4ml-tutorial
source /path/to/your/installtion/Xilinx/Vitis_HLS/202X.X/settings64.(c)sh
```

Note that part 7 of the tutorial makes use of the `VivadoAccelator` backend of hls4ml for which no Vitis equivalent is available yet. For this part of the tutorial it is therefore necesary to install and source Vivado HLS version 2019.2 or 2020.1, which can be obtained [here](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vivado-design-tools/archive.html).

## Companion material
We have prepared a set of slides with some introduction and more details on each of the exercises.
Please find them [here](https://docs.google.com/presentation/d/1c4LvEc6yMByx2HJs8zUP5oxLtY6ACSizQdKvw5cg5Ck/edit?usp=sharing).


## Notebooks
```{tableofcontents}
```

also:
 pip install tf_keras
1. how to update a package:
	conda activate hls4ml-t
	conda install -c conda-forge tensorflow

2. update a environment with new yml file:
	conda env update --name hls4ml-t --file environment.yml

3. how to make a kernel accessable for jupyter-lab:
	pip install ipykernel
	python -m ipykernel install --user --name hls4ml --display-name "Python (hls4ml-2.12)"
        (uninstall) jupyter kernelspec list
        (uninstall) jupyter kernelspec uninstall your_env_name

4. switching to gcc (maybe not necessary, next step seems more important)
	conda activate hls4ml-t
        # set the environment before starting Jupyter-lab
	export CC=gcc-14
	export CXX=g++-14
        # if jp still using clang, try to create a new kernel 
        # in a cell
	import os
	import subprocess

	os.environ["CC"] = "gcc-14"
	os.environ["CXX"] = "g++-14"
	
5. make the build_lib.sh use gcc:
       #!/bin/bash
       set -e
       
       export CC=gcc-14
       export CXX=g++-14
       
       if [[ "$OSTYPE" == "linux-gnu" ]]; then
           CFLAGS="-O3 -fPIC -std=c++11 -fno-gnu-unique"
       elif [[ "$OSTYPE" == "darwin"* ]]; then
           CFLAGS="-O3 -fPIC -std=c++11"
       fi
       LDFLAGS=
       INCFLAGS="-Ifirmware/ap_types/"
       PROJECT=myproject
       LIB_STAMP=83066690
       BASEDIR="$(cd "$(dirname "$0")" && pwd)"
       WEIGHTS_DIR="\"${BASEDIR}/firmware/weights\""
       
       ${CC} ${CFLAGS} ${INCFLAGS} -D WEIGHTS_DIR="${WEIGHTS_DIR}" -c firmware/${PROJECT}.cpp -o ${PROJECT}.o
       ${CC} ${CFLAGS} ${INCFLAGS} -D WEIGHTS_DIR="${WEIGHTS_DIR}" -c ${PROJECT}_bridge.cpp -o ${PROJECT}_bridge.o
       ${CXX} ${CFLAGS} ${INCFLAGS} -shared ${PROJECT}.o ${PROJECT}_bridge.o -o firmware/${PROJECT}-${LIB_STAMP}.so
       rm -f *.o

			
6. sometimes the lib cannot be found
