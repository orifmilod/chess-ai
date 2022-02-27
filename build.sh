mkdir -p build && cd build
echo $1 
if [ "$1" == "Debug" ];
then
  echo "\033[0;32m===================== Building debug version of the app ========================"
  cmake -DCMAKE_BUILD_TYPE=Debug -DFSANITIZE=address,undefined .. && make && ./bin/Chess
else 
  cmake -DCMAKE_BUILD_TYPE=Release  .. && make && ./bin/Chess
fi
