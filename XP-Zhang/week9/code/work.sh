  rm -rf build
  mkdir build
  cd build
  cmake .. -G Ninja
  ninja
  ./run_and_plot _of_4
  cd ..
