mkdir ehog_dump
mkdir dump
echo "" > ./dump/memprofbcer
echo "" > ./dump/memprofec
echo "" > ./dump/outputec
echo "" > ./dump/outputbcer
echo "" > ./dump/memprofehog
echo "" > ./dump/outputehog
format="%M\nreal %e\nuser %U\nsys %S\n"
s=(
    clementina 
    sinensis 
    trifoliata 
    elegans 
    # A_hydrophila_HiSeq
    # B_cereus_HiSeq
    # B_cereus_MiSeq
    # B_fragilis_HiSeq 
    # M_abscessus_HiSeq 
    # M_abscessus_MiSeq
    # R_sphaeroides_HiSeq 
    # R_sphaeroides_MiSeq 
    # S_aureus_HiSeq
    # V_cholerae_HiSeq 
    # V_cholerae_MiSeq
    # X_axonopodis_HiSeq
    ) 
cmake .
make BCER
make EC
make BCEREHOG

for dataset in ${s[@]};do
    /usr/bin/time -f "$format" --output=./dump/memprofehog -a ./bin/BCEREHOG $dataset >> ./dump/outputehog
    /usr/bin/time -f "$format" --output=./dump/memprofbcer -a ./bin/BCER $dataset >> ./dump/outputbcer
    /usr/bin/time -f "$format" --output=./dump/memprofec -a ./bin/EC $dataset >> ./dump/outputec
done