rm -rf build
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -G Xcode ..
open ./FloatGraph.xcodeproj
