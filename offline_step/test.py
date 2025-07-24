import uproot
from reader import convert_root_to_sparse_h5 

# Open ROOT file and TTree

variables = [
    "charge", "prePos_x", "prePos_y", "prePos_z",
    "driftTime_notSmeared","StepLength","Gtime","HitPathLength_fromTrack",
    "postPos_x","postPos_y","postPos_z","EventID"
]

hitmaps = convert_root_to_sparse_h5( filename = "../build/TPC_pi.root",
                                      treename = "HitNtuple",
                                      #variables=variables,
                                      #mean_events_per_map=3,
                                      pixel_size_xy=5,
                                      voxel_size_z=0.1,
                                      smear_sigma=50e-6,
                                       radius = 500, length_z=1000)

