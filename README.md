TPC simulation package:

including two parts:

      1. simulation of energy deposit in TPC region   
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
      7. ./TPC --h

      """
      ./TPC [-m macro ] [-u UIsession] [-t nThreads] [-vDefault]
                    -p e- -pmin 80 -pmax 80 -o myOutput.root -z -14.0
                    -csv xxx.csv -o myOutput.root -z -14.0
                    -ui: turnning on the ui
      """

      8. ./build/TPC -p kaon- -pmin 1 -pmax 800 -o output.root -n 10 -z 0
