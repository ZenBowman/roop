cmake_minimum_required(VERSION 2.8)

set(LIBSEXP_SRC /Users/prasansamtani/dev/sexpr-1.3/src)

project( Roop )
find_package( OpenCV REQUIRED )

add_executable( Roop 
  src/Roop.cpp
  src/LoadImage.cpp
  src/ErodeImage.cpp
  src/DilateImage.cpp
  src/SubtractImage.cpp
  src/AddImage.cpp
  src/DefGet.cpp
  src/EnhanceContrast.cpp
  src/Sharpen.cpp
  src/Blur.cpp
  src/Filter3.cpp
  src/ToGrayScale.cpp
  src/Derivative.cpp
  src/Canny.cpp
  src/Multiply.cpp
)

include_directories(${LIBSEXP_SRC})

target_link_libraries(Roop
  ${LIBSEXP_SRC}/libsexp.a
  ${OpenCV_LIBS} 
)
