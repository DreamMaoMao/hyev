sudo rm build/* -rf
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cmake --build build
sudo cp build/libhyev.so  /usr/lib

