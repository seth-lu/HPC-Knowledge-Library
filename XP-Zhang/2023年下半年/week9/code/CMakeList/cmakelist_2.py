str_1 = '''cmake_minimum_required(VERSION 3.23)
project("week 9")

set(Torch_ROOT "/home/zxp/libtorch") #libtorch的路径
find_package(Torch REQUIRED NO_MODULE ) #添加torch
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED) #添加python开发工具给matplotlib使用

include_directories({PYTHON_INCLUDE_DIRS} include) #include包含项目的include文件夹

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} '''

str_2 =  '''") #编译的优化选项

add_executable(run_and_plot src/Run_and_Plot.cpp)

target_link_libraries(run_and_plot ${TORCH_LIBRARIES}) #给test链接torch
target_link_libraries(run_and_plot Python3::Python Python3::NumPy) #链接pythoon和NumPy给matplotlib使用
'''

str_array1 = ['-fmath-errno','-fsigned-zeros','-ftrapping-math'] #Of没开但O2O3开了的
str_array = ['-fallow-store-data-races','-fassociative-math','-fcx-limited-range','-ffinite-math-only','-freciprocal-math','-funsafe-math-optimizations'] #Of开了但O3没的

str_O3_Of = ''
for s in str_array:
    str_O3_Of += s + ' '

print(str_O3_Of)

index = 1
for s in str_array1:
    print('./CMakeLists/CMakeLists_Of_' + str(index) + '.txt')
    print(s)

    with open('./CMakeLists/CMakeLists_of_' + str(index) + '.txt', 'w') as file:
        file.write(str_1 + '-Ofast -march=native ' + s + str_2)

    index += 1

index = 1
for s in str_array:
    print('./CMakeLists/CMakeLists_O3_' + str(index) + '.txt')
    print('./CMakeLists/CMakeLists_O3_' + str(index) + 't.txt')
    print(s)
    print(str_O3_Of.replace(s + ' ',''))

    with open('./CMakeLists/CMakeLists_O3_' + str(index) + '.txt', 'w') as file:
        file.write(str_1 + '-O3 ' + s + str_2)

    with open('./CMakeLists/CMakeLists_O3' + str(index) + 't.txt', 'w') as file:
        file.write(str_1 + '-O3 ' + str_O3_Of.replace(s + ' ','') + str_2)

    index += 1

# with open('./CMakeLists/test.txt', 'w') as file:
#     file.write(str_1 + '-O2 -ftree-loop-distribution' +str_2)