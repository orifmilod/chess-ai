#build 3rd party libs
git submodule init && git submodule update
mkdir libs/SFML/build
cd libs/SFML/build
cmake .. 
make
