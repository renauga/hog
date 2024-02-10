echo "" > memprofssp
echo "" > memprofsk
echo "" > outputsk
echo "" > outputssp
format="%M\nreal %e\nuser %U\nsys %S\n"
s=(clementina 
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
    X_axonopodis_HiSeq) 
for dataset in ${s[@]};do
    # cmake . -DSSP=1 -DDATASET_MEMORY=1 > cmakedump
    # make HOG > makedump
    # /usr/bin/time -f "$format" --output=memprof -a ./bin/HOG $dataset >> outputssp

    cmake . -DSSP=1 -DAHO_CORASICK_MEMORY=1 -DDATASET_MEMORY=0 > cmakedump
    make HOG > makedump
    /usr/bin/time -f "$format" --output=memprofssp -a ./bin/HOG $dataset >> outputssp

    cmake . -DSSP=1 -DAHO_CORASICK_MEMORY=0 -DDATASET_MEMORY=0 > cmakedump
    make HOG > makedump
    /usr/bin/time -f "$format" --output=memprofssp -a ./bin/HOG $dataset >> outputssp



    # cmake . -DSSP=0 -DDATASET_MEMORY=1 > cmakedump
    # make HOG > makedump
    # /usr/bin/time -f "$format" --output=memprof -a ./bin/HOG $dataset >> outputsk

    cmake . -DSSP=0 -DAHO_CORASICK_MEMORY=1 -DDATASET_MEMORY=0 > cmakedump
    make HOG > makedump
    /usr/bin/time -f "$format" --output=memprofsk -a ./bin/HOG $dataset >> outputsk

    cmake . -DSSP=0 -DAHO_CORASICK_MEMORY=0 -DDATASET_MEMORY=0 > cmakedump
    make HOG > makedump
    /usr/bin/time -f "$format" --output=memprofsk -a ./bin/HOG $dataset >> outputsk
done