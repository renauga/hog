echo "" > memprofbcer
echo "" > memprofec
echo "" > outputec
echo "" > outputbcer
format="%M\nreal %e\nuser %U\nsys %S\n"
s=(clementina 
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
cmake . -DALGO=3 -DAHO_CORASICK_MEMORY=1 -DDATASET_MEMORY=0 > cmakedump
make BCEREHOG > makedump
cmake . -DALGO=3 -DAHO_CORASICK_MEMORY=0 -DDATASET_MEMORY=0 > cmakedump
make BCER > makedump
cmake . -DALGO=4 -DAHO_CORASICK_MEMORY=1 -DDATASET_MEMORY=0 > cmakedump
make ECEHOG > makedump
cmake . -DALGO=4 -DAHO_CORASICK_MEMORY=0 -DDATASET_MEMORY=0 > cmakedump
make EC > makedump

for dataset in ${s[@]};do
    /usr/bin/time -f "$format" --output=memprofbcer -a ./bin/BCEREHOG $dataset >> outputbcer
    /usr/bin/time -f "$format" --output=memprofbcer -a ./bin/BCER $dataset >> outputbcer
    /usr/bin/time -f "$format" --output=memprofec -a ./bin/ECEHOG $dataset >> outputec
    /usr/bin/time -f "$format" --output=memprofec -a ./bin/EC $dataset >> outputec
done