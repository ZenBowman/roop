cmake_minimum_required(VERSION 2.8)

set(LIBSEXP_SRC /home/zenbowman/dev/externaltools/sexpr_1.2.1/src/)

project( Roop )
find_package( OpenCV REQUIRED )

add_executable( Roop 
  src/ExecutableCommand.h
  src/RoopCommon.h

  src/ExecutableCommand.cpp
  src/RoopCommon.cpp
  src/Roop.cpp
  src/LoadImage.cpp
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
)

include_directories(${LIBSEXP_SRC})

target_link_libraries(Roop
  ${LIBSEXP_SRC}/libsexp.a
  ${OpenCV_LIBS} 
)
