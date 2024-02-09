cmake . -DSSP=1
make HOG
./bin/HOG > outputssp

cmake . -DSSP=0
make HOG
./bin/HOG > outputsk

diff outputssp outputsk