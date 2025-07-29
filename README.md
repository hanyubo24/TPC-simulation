# TPC simulation package (WIP):

### Including The following steps:

    1. simulation of energy deposit in TPC region
        -> A root file will be saved 
    3. (offline/Step2.py): digitilization of the signal accoridng to the config of the readout silicon sensors
        -> convert the root file into a .h5 file 
    4. Training of CNN/GNN ?? `(TBD) 


### Usage:
   #### Step 0:  
      1. (clone the repository)
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
   #### step 1: 
      #this will generate the simulated sample 
      8. ./build/TPC -p kaon- -pmin 1 -pmax 800 -o output.root -n 10 -z 0
   #### step 2: 
      #this will do the offline digitalization, please take a look at the scripts in offine folder, and modify the yaml file if needed 
      9. cd offline
      9.1. python Step2.py --h 
      10. python Step2.py 
      #the files can be checked by the notebook in this folder 


      
