SET(VML_SOURCE_FILES
   src/vec2.cpp
)

SET(VML_HEADER_FILES
   basics.h
   vec2.h
   graph.h
)

add_library(vml ${VML_SOURCE_FILES} ${VML_HEADER_FILES})
target_include_directories(vml PUBLIC ..)

set_target_properties(vml PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)