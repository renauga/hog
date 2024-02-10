echo "" > memprofssp
echo "" > memprofsk
echo "" > outputsk
echo "" > outputssp
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

cmake . -DALGO=1 -DAHO_CORASICK_MEMORY=1 -DDATASET_MEMORY=0 > cmakedump
make SSPAHO > makedump
cmake . -DALGO=2 -DAHO_CORASICK_MEMORY=1 -DDATASET_MEMORY=0 > cmakedump
make SKAHO > makedump
cmake . -DALGO=1 -DAHO_CORASICK_MEMORY=0 -DDATASET_MEMORY=0 > cmakedump
make SSP > makedump
cmake . -DALGO=2 -DAHO_CORASICK_MEMORY=0 -DDATASET_MEMORY=0 > cmakedump
make SK > makedump

for dataset in ${s[@]};do
    /usr/bin/time -f "$format" --output=memprofssp -a ./bin/SSPAHO $dataset >> outputssp
    /usr/bin/time -f "$format" --output=memprofssp -a ./bin/SSP $dataset >> outputssp
    /usr/bin/time -f "$format" --output=memprofsk -a ./bin/SKAHO $dataset >> outputsk
    /usr/bin/time -f "$format" --output=memprofsk -a ./bin/SK $dataset >> outputsk
done