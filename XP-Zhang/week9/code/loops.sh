files=$(ls ./CMakeLists)
for file in $files
do
  str=${file}
  echo ${str}
  str=${str//.txt/}
  str=${str//CMakeLists/}
  echo ${str}
  cp -f ./CMakeLists/${file} ./CMakeLists.txt
  rm -rf build
  mkdir build
  cd build
  cmake .. -G Ninja
  ninja
  ./run_and_plot ${str}
  cd ..
done
