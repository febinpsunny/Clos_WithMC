#!/bin/bash

export SC_SIGNAL_WRITE_CHECK=DISABLE

file_name="OOK_PAPER3_64LAMBDA"
current_time=$(date "+%Y.%m.%d-%H.%M.%S")
new_filename="$file_name-$current_time.txt" 

../closPNOC64 blackscholes_modified.txt >> ../../Result/$new_filename
../closPNOC64 canneal_modified.txt >> ../../Result/$new_filename
../closPNOC64 fft_modified.txt >> ../../Result/$new_filename
../closPNOC64 fluidanimate_modified.txt >> ../../Result/$new_filename
../closPNOC64 jpeg_modified.txt >> ../../Result/$new_filename
../closPNOC64 sobel_modified.txt >> ../../Result/$new_filename
../closPNOC64 streamcluster_modified.txt >> ../../Result/$new_filename
../closPNOC64 x264_modified.txt >> ../../Result/$new_filename



:'
../closPNOC64 streamcluster_modified.txt >> ../../Result/$new_filename
../closPNOC64 bodytrack_modified.txt >> ../../Result/$new_filename
../closPNOC64 canneal_modified.txt >> ../../Result/$new_filename
../closPNOC64 facesim_modified.txt >> ../../Result/$new_filename
../closPNOC64 blackscholes_modified.txt >> ../../Result/$new_filename
../closPNOC64 ferret_modified.txt >> ../../Result/$new_filename
../closPNOC64 swaptions_modified.txt >> ../../Result/$new_filename
../closPNOC64 fluidanimate_modified.txt >> ../../Result/$new_filename
../closPNOC64 vips_modified.txt >> ../../Result/$new_filename
../closPNOC64 dedup_modified.txt  >> ../../Result/$new_filename
../closPNOC64 freqmine_modified.txt >> ../../Result/$new_filename
../closPNOC64 x264_modified.txt >> ../../Result/$new_filename
../closPNOC64 Trace2.txt >> ../../Result/$new_filename'
