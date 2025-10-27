#!/usr/bin/env python3

import os
import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt

COLOR_MAP = {
    'cold': 'blue',
    'neutral': 'green',
    'warm': 'orange',
    'hot': 'red',
}

def read_dat(path):
    xs = []
    ys = []
    ts = []
    with open(path, 'r') as fh:
        for line in fh:
            s = line.strip()
            if not s:
                continue
            parts = s.split()
            if len(parts) < 3:
                continue
            try:
                x = float(parts[0])
                y = float(parts[1])
                t = float(parts[2])
            except ValueError:
                continue
            xs.append(x); ys.append(y); ts.append(t)
    return np.array(xs), np.array(ys), np.array(ts)

def categorize_temperatures(tarr):
   
    if tarr.size == 0:
        return np.array([])
    vmin = float(np.min(tarr))
    vmax = float(np.max(tarr))
    rng = vmax - vmin if vmax != vmin else 1.0
    q1 = vmin + 0.25 * rng
    q2 = vmin + 0.50 * rng
    q3 = vmin + 0.75 * rng
    cats = []
    for v in tarr:
        if v <= q1:
            cats.append('cold')
        elif v <= q2:
            cats.append('neutral')
        elif v <= q3:
            cats.append('warm')
        else:
            cats.append('hot')
    return np.array(cats)

def plot_points(xs, ys, cats, title, outpath, show=True):
    import matplotlib as mpl
    plt.figure(figsize=(6,6))
    # create a smooth colormap that goes blue -> green -> yellow -> red
    cmap = mpl.colors.LinearSegmentedColormap.from_list('tempmap', ['blue', 'green', 'yellow', 'red'])
    sc = plt.scatter(xs, ys, c=cats, cmap=cmap, s=8, linewidths=0)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title(title)
    cbar = plt.colorbar(sc)
    cbar.set_label('Temperature')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.tight_layout()
    plt.savefig(outpath, dpi=300)
    print('Saved', outpath)
    try:
        if show:
            plt.show()
        else:
            plt.close()
    except KeyboardInterrupt:
        # Allow graceful interruption if a GUI blocks in some environments
        plt.close()

def process_file(path, outdir='.', show=True):
    xs, ys, ts = read_dat(path)
    if xs.size == 0:
        print('No valid data in', path)
        return
    # use continuous temperature mapping (pass temperature values directly)
    base = os.path.splitext(os.path.basename(path))[0]
    outname = base + '_scatter.png'
    outpath = os.path.join(outdir, outname)
    plot_points(xs, ys, ts, base, outpath, show=show)

def main(argv=None):
    parser = argparse.ArgumentParser(description='Plot .dat x y temperature files as colored scatter plots')
    parser.add_argument('files', nargs='*', help='input .dat files (optional). If omitted the script auto-detects .dat files in the current directory)')
    parser.add_argument('--no-show', dest='no_show', action='store_true', help='do not display the figures (headless)')
    parser.add_argument('--outdir', dest='outdir', default='.', help='directory to write PNG outputs')
    args = parser.parse_args(argv)

    files = args.files
    if not files:
        files = [f for f in os.listdir('.') if f.lower().endswith('.dat')]
        files.sort()
    if len(files) == 0:
        print('No .dat files found in current directory. Provide file names as arguments.')
        return

    # If user supplied more than 2 files, just process all of them.
    for f in files:
        process_file(f, outdir=args.outdir, show=(not args.no_show))

if __name__ == '__main__':
    main()
