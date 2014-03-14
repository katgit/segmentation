#!/bin/bash

timestamp="`date '+%Y%m%d%M%S'`"
batch_segment_dir_name="t10-m1-n15_15_100_2500_2500"
refdatadir=$batch_segment_dir_name"_reference"
export IPW="/project/earth/packages/ipw-1.1.0"

# Compile and link
pushd ../segment
make
popd

# Load modules
source /usr/local/Modules/3.2.10/init/bash
module purge
module load gdal/1.10.0
#module load ipw/1.1.0
module load envi/4.8
   
# Assure recompile segment program is selected
export PATH=/projectnb/scv/katia/projects/segmentation/segment:$PATH

# Set aside previous outpu
#mkdir "./"$datadir

# Run segment against test input
batch_segment.sh -i testsmall.bsq -p param.txt 
mv -v "./"$batch_segment_dir_name "./"$batch_segment_dir_name"."$timestamp

# Confirm output is same after change to sergment code
echo Output of diff command:
diff "./"$refdatadir "./"$batch_segment_dir_name"."$timestamp
