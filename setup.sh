#build 3rd party libs
rm -rf ./libs/SFML/build
mkdir libs/SFML/build
cd libs/SFML/build
cmake .. 
make
