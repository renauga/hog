mkdir ehog_dump
mkdir dump
echo "" > ./dump/memprofssp
echo "" > ./dump/memprofsk
echo "" > ./dump/outputsk
echo "" > ./dump/outputssp
echo "" > ./dump/memprofehog
echo "" > ./dump/outputehog
format="%M\nreal %e\nuser %U\nsys %S\n"
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
cmake .
make SSP
make SK
make SSPEHOG

for dataset in ${s[@]};do
    /usr/bin/time -f "$format" --output=./dump/memprofehog -a ./bin/SSPEHOG $dataset >> ./dump/outputehog
    /usr/bin/time -f "$format" --output=./dump/memprofssp -a ./bin/SSP $dataset >> ./dump/outputssp
    /usr/bin/time -f "$format" --output=./dump/memprofsk -a ./bin/SK $dataset >> ./dump/outputsk
done