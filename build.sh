mkdir -p build && cd build

if [ "$1" == "Debug" ];
then
  echo "\033[0;32m===================== Building Debug version of the app ========================"
  conan install .. -r conancenter --profile ../profiles/armv8_macos_debug
  cmake -DCMAKE_BUILD_TYPE=Debug -DFSANITIZE=address,undefined .. && make
else 
  echo "\033[0;32m===================== Building Release version of the app ========================"
  conan install .. -r conancenter --profile ../profiles/armv8_macos_release
  cmake -DCMAKE_BUILD_TYPE=Release  .. && make
fi

echo "\033[0;32m===================== Running the app ========================"
./bin/Chess
