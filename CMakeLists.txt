cmake_minimum_required(VERSION 2.8)

set(LIBSEXP_SRC thirdparty/sexpr-1.2.1/)
set(SCHEME_SRC thirdparty/tinyscheme-1.41/)

project( Roop )
find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED )

add_executable( Roop 
  thirdparty/sexpr-1.2.1/cstring.c
  thirdparty/sexpr-1.2.1/event_temp.c
  thirdparty/sexpr-1.2.1/faststack.c
  thirdparty/sexpr-1.2.1/parser.c
  thirdparty/sexpr-1.2.1/sexp.c
  thirdparty/sexpr-1.2.1/sexp_memory.c
  thirdparty/sexpr-1.2.1/sexp_ops.c
  thirdparty/sexpr-1.2.1/sexp_vis.c

  thirdparty/tinyscheme-1.41/scheme.c

  src/ExecutableCommand.h
  src/RoopCommon.h
  src/Transform.h
  src/ForEachPixel.h

  src/ExecutableCommand.cpp
  src/RoopCommon.cpp
  src/Roop.cpp
  src/FileOperations.cpp
  src/MorphologicalOperations.cpp
  src/LogicalOperations.cpp
  src/DefGet.cpp
  src/EnhanceContrast.cpp
  src/Sharpen.cpp
  src/Blur.cpp
  src/Filter3.cpp
  src/ColorConversions.cpp
  src/Derivative.cpp
  src/Canny.cpp
  src/Multiply.cpp
  src/Segmentation.cpp
  src/ConnectedComponents.cpp
  src/ShapeAnalysis.cpp
  src/Transform.cpp
  src/ForEachPixel.cpp
)

include_directories(${LIBSEXP_SRC} ${SCHEME_SRC})

target_link_libraries(Roop
  ${OpenCV_LIBS} 
  ${Boost_LIBS}
)
