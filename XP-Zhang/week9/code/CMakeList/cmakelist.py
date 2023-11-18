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

str_array = ['-fgcse-after-reload','-fipa-cp-clone','-floop-interchange','-floop-unroll-and-jam','-fpeel-loops','-fpredictive-commoning',
             '-fsplit-loops','-fsplit-paths','-ftree-loop-distribution','-ftree-loop-vectorize','-ftree-partial-pre','-ftree-slp-vectorize',
             '-funroll-completely-grow-size','-funswitch-loops','-fvect-cost-model=dynamic','-fversion-loops-for-strides']

str_O2_O3 = ''
for s in str_array:
    str_O2_O3 += s + ' '

print(str_O2_O3)

index = 1
for s in str_array:
    print('./CMakeLists/CMakeLists_' + str(index) + '.txt')
    print('./CMakeLists/CMakeLists_' + str(index) + 't.txt')
    print(s)
    print(str_O2_O3.replace(s + ' ',''))

    with open('./CMakeLists/CMakeLists_' + str(index) + '.txt', 'w') as file:
        file.write(str_1 + '-O2 ' + s + str_2)

    with open('./CMakeLists/CMakeLists_' + str(index) + 't.txt', 'w') as file:
        file.write(str_1 + '-O2 ' + str_O2_O3.replace(s + ' ','') + str_2)

    index += 1

# with open('./CMakeLists/test.txt', 'w') as file:
#     file.write(str_1 + '-O2 -ftree-loop-distribution' +str_2)