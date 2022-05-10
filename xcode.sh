DIR=$( cd "$( dirname "${ZSH_SOURCE[0]}" )" && pwd )
rm -rf build
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -G Xcode .. -T buildsystem=12
open ./FloatingGraph.xcodeproj
