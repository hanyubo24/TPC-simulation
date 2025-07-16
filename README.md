TPC simulation package:

including two parts:

      1. (online): simulation of energy deposition in TPC region   
      2. (offline): digitilization of the signal accoridng to the config of the readout silicon sensors:
         to-do: a python package to read in the simulation output and readout config file
         output: hitmap, with time info


usage:
      
      1. clone the repository 
      2. mkdir build 
      3. cd build 
      4. cmake ..
      5. make 
      6. (testing) ./TPC -ui
