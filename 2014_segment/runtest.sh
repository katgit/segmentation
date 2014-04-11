#!/bin/bash

echo
echo "*********************************************"
echo "*********************************************"
echo "*********************************************"
echo

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
<<<<<<< HEAD
export PATH=/projectnb/scv/katia/projects/segmentation/segment:$PATH
=======
#export PATH=/projectnb/scv/katia/projects/segmentation/segment:$PATH
>>>>>>> b7b0cde9e1d370cb22061a8ea121622ce8155651
pushd ..
export PATH=`pwd`/segment:$PATH
popd
echo $PATH

# Set aside previous outpu
#mkdir "./"$datadir

# Run segment against test input
batch_segment.sh -i testsmall.bsq -p param.txt 
#exit
mv -v "./"$batch_segment_dir_name "./"$batch_segment_dir_name"."$timestamp
exit

# Confirm output is same after change to sergment code
echo Output of diff command:
diff -r "./"$refdatadir "./"$batch_segment_dir_name"."$timestamp
