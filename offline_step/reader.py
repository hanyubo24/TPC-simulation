import uproot
import numpy as np
import pandas as pd
from tqdm import tqdm
import h5py
from collections import defaultdict
import matplotlib.pyplot as plt

# length unit = mm
def build_hitmap(df, pixel_size_xy=5, voxel_size_z=0.1, smear_sigma=0.0, radius=500, length_z=1000):
    """
    Build a cylindrical 3D voxel map from hit positions in a TPC.

    Parameters:
    - df: DataFrame with columns: prePos_x, prePos_y, prePos_z
    - pixel_size_xy: bin size in x and y (mm)
    - voxel_size_z: bin size in z (mm)
    - smear_sigma: Gaussian smearing applied to x, y, z (mm)
    - radius: radius of the TPC cylinder (mm)
    - length_z: full length of the TPC along Z (mm)

    Returns:
    - hist: 3D voxel map as NumPy array
    - x_edges, y_edges, z_edges: bin edges
    """
    required_columns = {"prePos_x", "prePos_y", "prePos_z"}
    if not required_columns.issubset(df.columns):
        raise ValueError(f"Input DataFrame must contain columns: {required_columns}")

    pos = df[["prePos_x", "prePos_y", "prePos_z"]].to_numpy()
    if smear_sigma > 0:
        pos += np.random.normal(0, smear_sigma, size=pos.shape)


    r2 = pos[:, 0]**2 + pos[:, 1]**2
    mask = (r2 <= radius**2) & (np.abs(pos[:, 2]) <= length_z / 2)
    pos = pos[mask]

    if len(pos) == 0:
        return None, None, None

    x_bins = int(2 * radius / pixel_size_xy)
    y_bins = int(2 * radius / pixel_size_xy)
    z_bins = int(length_z / voxel_size_z)
    print('bins ', x_bins, y_bins, z_bins)

    x_idx = ((pos[:, 0] + radius) / pixel_size_xy).astype(int)
    y_idx = ((pos[:, 1] + radius) / pixel_size_xy).astype(int)
    z_idx = ((pos[:, 2] + length_z / 2) / voxel_size_z).astype(int)

    coords = np.stack((x_idx, y_idx, z_idx), axis=1)
    uniq, counts = np.unique(coords, axis=0, return_counts=True)

    return uniq, counts, (x_bins, y_bins, z_bins)

def save_sparse_h5(h5file, event_id, coords, counts, shape):
    grp = h5file.create_group(str(event_id))
    grp.create_dataset("coords", data=coords, compression="gzip")
    grp.create_dataset("counts", data=counts, compression="gzip")
    grp.create_dataset("shape", data=shape)



def convert_root_to_sparse_h5(filename, treename, output_h5="test.h5",
                              pixel_size_xy=5, voxel_size_z=0.1,
                              smear_sigma=0.0, radius=500, length_z=1000):

    tree = uproot.open(filename)[treename]
    df = tree.arrays(library="pd")

    df = df[df["charge"] > 0]  # Apply a cut

    grouped = df.groupby("EventID")

    with h5py.File(output_h5, "w") as h5f:
        for event_id, group in tqdm(grouped, desc="Processing events"):
            coords, counts, shape = build_hitmap(
                group,
                pixel_size_xy=pixel_size_xy,
                voxel_size_z=voxel_size_z,
                smear_sigma=smear_sigma,
                radius=radius,
                length_z=length_z,
            )
            if coords is not None:
                save_sparse_h5(h5f, event_id, coords, counts, shape)



# load the h5 sample 
def load_sparse_event(h5file_path, event_id):
    with h5py.File(h5file_path, 'r') as f:
        group = f[str(event_id)]
        coords = group["coords"][:]
        counts = group["counts"][:]
        shape = tuple(group["shape"][:])
    return coords, counts, shape


def build_dense_hitmap(coords, counts, shape):
    hitmap = np.zeros(shape, dtype=np.float32)
    for (x, y, z), value in zip(coords, counts):
        hitmap[int(x), int(y), int(z)] = value
    return hitmap

def plot_projection(hitmap, axis='z'):
    if axis == 'z':
        proj = np.sum(hitmap, axis=2)  # X-Y projection
    elif axis == 'x':
        proj = np.sum(hitmap, axis=0)  # Y-Z projection
    elif axis == 'y':
        proj = np.sum(hitmap, axis=1)  # X-Z projection
    else:
        raise ValueError("Axis must be 'x', 'y', or 'z'.")

    plt.imshow(proj.T, origin='lower', cmap='viridis', aspect='auto')
    plt.title(f"Projection on {axis.upper()} axis")
    plt.colorbar(label="Hit Count")
    plt.xlabel("Pixel")
    plt.ylabel("Pixel")
    plt.show()

