#!/bin/bash

# mkdir dump
# mkdir ./dump/aho_dump
# mkdir ./dump/ehog_dump
s=(
    clementina 
    sinensis 
    trifoliata 
    elegans 
    A_hydrophila_HiSeq
    B_cereus_HiSeq
    B_cereus_MiSeq
    B_fragilis_HiSeq 
    M_abscessus_HiSeq 
    M_abscessus_MiSeq
    R_sphaeroides_HiSeq 
    R_sphaeroides_MiSeq 
    S_aureus_HiSeq
    V_cholerae_HiSeq 
    V_cholerae_MiSeq
    X_axonopodis_HiSeq
    ) 

algos=(
    SSP
    # SK
    # EC
    # BCER
    # SP
)

format=",%M,%e,%U,%S"
format2=",%M"
rm output_time
rm output_memory_time
rm output_memory
rm output_memory_memory

# Hog from Aho Corasick and EHOG, No dumping, Time Reading
for dataset in ${s[@]};do
    for algo in ${algos[@]};do
        myvar=$algo"_TIME_DIRECT_AHO"
        # myvar+="AHO"
        timeout 2h /usr/bin/time -f "aho$dataset$algo,%M" --output=output_memory_time -a ./bin/$myvar $dataset >> output_time
        if [ $? -gt 0 ]; then
            echo -n "timeout,timeout,timeout,timeout," >> output_time
            echo "timeout,timeout" >> output_memory_time  
        fi
        myvar2=$algo"_TIME_DIRECT_EHOG"
        # myvar2+="EHOG"
        timeout 2h /usr/bin/time -f "ehog$dataset$algo,%M" --output=output_memory_time -a ./bin/$myvar2 $dataset >> output_time
        if [ $? -gt 0 ]; then
            echo -n "timeout,timeout,timeout,timeout," >> output_time 
            echo "timeout,timeout" >> output_memory_time 
        fi
    done
    echo "" >> output_time
done

# Hog from Aho Corasick and EHOG, No dumping, Memory Reading
# for dataset in ${s[@]};do
#     for algo in ${algos[@]};do
#         myvar=$algo"_MEMORY_DIRECT_AHO"
#         # myvar+="AHO"
#         timeout 2h /usr/bin/time -f "aho$dataset$algo,%M" --output=output_memory_memory -a ./bin/$myvar $dataset ./MemProfile/$dataset"_AHO_"$algo >> output_memory
#         if [ $? -gt 0 ]; then
#             echo -n "timeout,timeout,timeout,timeout," >> output_memory
#             echo "timeout,timeout" >> output_memory_memory  
#         fi
#         myvar2=$algo"_MEMORY_DIRECT_EHOG"
#         # myvar2+="EHOG"
#         timeout 2h /usr/bin/time -f "ehog$dataset$algo,%M" --output=output_memory_memory -a ./bin/$myvar2 $dataset ./MemProfile/$dataset"_EHOG_"$algo >> output_memory
#         if [ $? -gt 0 ]; then
#             echo -n "timeout,timeout,timeout,timeout," >> output_memory 
#             echo "timeout,timeout" >> output_memory_memory 
#         fi
#     done
#     echo "" >> output_memory
# done