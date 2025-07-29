import argparse
import uproot
from reader import convert_root_to_sparse_h5 
import yaml

# Open ROOT file and TTree
# nothing to do with the simulation, just the offline smearing and digitization
# could be done several times

def load_config(yaml_path):
    with open(yaml_path, 'r') as f:
        return yaml.safe_load(f)

def main():
    parser = argparse.ArgumentParser(description="Run ROOT-to-HDF5 conversion with config YAML.")
    parser.add_argument( "--config_path", default="demo_readout.yaml", 
                          help="Path to the YAML configuration file (default: demo_readout.yaml)")
    args = parser.parse_args()

    config = load_config(args.config_path)
    hitmaps = convert_root_to_sparse_h5(
        filename=config["filename"],
        treename=config["treename"],
        output_h5=config["output_h5"],
        pixel_size_xy=config["pixel_size_xy"],
        voxel_size_z=config["voxel_size_z"],
        smear_sigma=config["smear_sigma"],
        radius=config["radius"],
        length_z=config["length_z"],
        submap_size_xy=config["submap_size_xy"],
        events_per_group=config["events_per_group"]
    )

if __name__ == "__main__":
    main()

