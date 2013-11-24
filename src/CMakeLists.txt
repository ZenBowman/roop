cmake_minimum_required(VERSION 2.8)

set(LIBSEXP_SRC thirdparty/sexpr-1.2.1/)
set(SCHEME_SRC thirdparty/tinyscheme-1.41/)

project( Roop )
find_package( OpenCV REQUIRED )
find_package( Boost REQUIRED )

add_library( sexpr 
  thirdparty/sexpr-1.2.1/cstring.c
  thirdparty/sexpr-1.2.1/event_temp.c
  thirdparty/sexpr-1.2.1/faststack.c
  thirdparty/sexpr-1.2.1/parser.c
  thirdparty/sexpr-1.2.1/sexp.c
  thirdparty/sexpr-1.2.1/sexp_memory.c
  thirdparty/sexpr-1.2.1/sexp_ops.c
  thirdparty/sexpr-1.2.1/sexp_vis.c
)

add_library( tinyscheme
  thirdparty/tinyscheme-1.41/scheme.c
)

add_executable( Roop  
  ExecutableCommand.h
  RoopCommon.h
  Transform.h
  ForEachPixel.h

  ExecutableCommand.cpp
  RoopCommon.cpp
  Roop.cpp
  FileOperations.cpp
  MorphologicalOperations.cpp
  LogicalOperations.cpp
  DefGet.cpp
  EnhanceContrast.cpp
  Sharpen.cpp
  Blur.cpp
  Filter3.cpp
  ColorConversions.cpp
  Derivative.cpp
  Canny.cpp
  Multiply.cpp
  Segmentation.cpp
  ConnectedComponents.cpp
  ShapeAnalysis.cpp
  Transform.cpp
  ForEachPixel.cpp
)

include_directories(${LIBSEXP_SRC} ${SCHEME_SRC})

target_link_libraries(Roop
  ${OpenCV_LIBS} 
  ${Boost_LIBS}
  sexpr
  tinyscheme
)
