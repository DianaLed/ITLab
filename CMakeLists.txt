#Cmake --version
#cmake version 3.18.4

cmake_minimum_required(VERSION 3.18.4)

project(Perceptron)			#Название проекта
message("ferst version")   #Должен вывести 

set(SOURCE_EXE main.cpp)		# Установка переменной со списком исходников для исполняемого файла

set(SOURCE_LIB Inp.cpp)			# Установка переменной со списком исходников для билиотеки
add_library(Inp STATIC ${SOURCE_LIB})	# Создание статической библиотеки с именем inp

set(SOURCE_LIBL Layer.cpp)
add_library(Layer STATIC ${SOURCE_LIBL})

set(SOURCE_LIBS Sum.cpp)
add_library(Sum STATIC ${SOURCE_LIBS})

add_library(Layer_for_pic STATIC ${SOURCE_LIB})
add_library(Layer_for_all_picture STATIC ${SOURCE_LIB})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main
target_link_libraries(main Inp Layer Sum)		# Линковка программы с библиотекой
target_link_libraries( main ${OpenCV_LIBS} )