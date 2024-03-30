# 软件安装

## gcc编译安装

1. 下载源码

​		https://ftp.gnu.org/gnu/gcc/gcc-9.5.0/
​		安装下面3.中所包含的环境

2. 安装

```shell
./configure -prefix=/public/home/hpc2316085405032/software/isl-0.18 --with-gmp-prefix=/public/home/hpc2316085405032/software/gmp-6.2.0
$tar -xvzf gcc-9.5.0.tar.gz
$cd gcc-9.5.0
$export LD_LIBRARY_PATH=/public/home/hpc2316085405032/software/isl-0.18/lib:$LD_LIBRARY_PATH
$ export LD_LIBRARY_PATH=/public/home/hpc2316085405032/software/mpfr-4.1.0/lib:$LD_LIBRARY_PATH 动态链接库
$ mkdir build
$ cd build 
$ ../configure --enable-bootstrap \
--enable-languages=c,c++,fortran,lto \
--prefix=/public/home/hpc2316085405032/software/gcc-9 \
--mandir=/public/home/hpc2316085405032/software/gcc-9/share/man \
--infodir=/public/home/hpc2316085405032/software/gcc-9/share/info \
--with-bugurl=http://bugzilla.redhat.com/bugzilla \
--enable-shared --enable-threads=posix --enable-checking=release --disable-multilib \
--with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object \
--enable-linker-build-id --with-gcc-major-version-only --enable-plugin --with-linker-hash-style=gnu \
--enable-initfini-array --with-default-libstdcxx-abi=gcc4-compatible \
--with-gmp=/public/home/hpc2316085405032/software/gmp-6.2.0 --with-gmp-include=/public/home/hpc2316085405032/software/gmp-6.2.0/include \
--with-gmp-lib=/public/home/hpc2316085405032/software/gmp-6.2.0/lib \
--with-mpfr=/public/home/hpc2316085405032/software/mpfr-4.1.0 --with-mpfr-include=/public/home/hpc2316085405032/software/mpfr-4.1.0/include \
--with-mpfr-lib=/public/home/hpc2316085405032/software/mpfr-4.1.0/lib \
--with-mpc=/public/home/hpc2316085405032/software/mpc-1.2.0 --with-mpc-include=/public/home/hpc2316085405032/software/mpc-1.2.0/include \
--with-mpc-lib=/public/home/hpc2316085405032/software/mpc-1.2.0/lib \
--with-isl=/public/home/hpc2316085405032/software/isl-0.18 --enable-libmpx --enable-gnu-indirect-function \
--with-tune=generic --build=x86_64-pc-linux-gnu

$ make -j 56

$ make install
export LD_LIBRARY_PATH=/public/software/compiler/gcc/7.3.1/external_libs/lib:$LD_LIBRARY_PATH
```

3. 安装gcc需要的环境

3.1 gmp 编译安装

https://ftp.gnu.org/gnu/gmp/

```shell
$tar -xvjf gmp-6.2.1.tar.bz2
$cd gmp-6.2.1/

$./configure --prefix=$(pwd)
$make
$make install
```

3.2 MPFR 编译安装

https://ftp.gnu.org/gnu/mpfr/

```shell
$tar -xvjf mpfr-4.1.0.tar.bz2
$cd mpfr-4.1.0/

$./configure --prefix=$(pwd) \
    --with-gmp-include=prefolder/gmp-6.2.1/include \
    --with-gmp-lib=prefolder/gmp-6.2.1/lib \

$make
$make install
```

3.3 安装MPC

https://ftp.gnu.org/gnu/mpc/
```shell
$ tar -xvzf mpc-1.2.1.tar.gz
$ cd mpc-1.2.1/

$ ./configure --prefix=$(pwd) \
    --with-gmp-include=prefolder/gmp-6.2.1/include \
    --with-gmp-lib=prefolder/gmp-6.2.1/lib \
    --with-mpfr-include=prefolder/mpfr-4.1.0/include \
    --with-mpfr-lib=prefolder/mpfr-4.1.0/lib \

$ make
$ make install
```

3.4 安装isl 

https://sourceforge.net/projects/libisl/files/isl-0.18.tar.bz2/download

```c++
tar xvf isl-0.18.tar.bz2
cd isl-0.18
 
./configure -prefix=/usr/local/isl-0.18 --with-gmp-prefix=/usr/local/gmp-6.1.0
make

```



## cuda-cudnn-安装

cuda 安装 https://developer.nvidia.com/cuda-11-3-1-download-archive?target_os=Linux&target_arch=x86_64&Distribution=CentOS&target_version=7&target_type=rpm_local

```shell
$ wget https://developer.download.nvidia.com/compute/cuda/11.3.1/local_installers/cuda_11.3.1_465.19.01_linux.run
$ sudo sh cuda_11.3.1_465.19.01_linux.run
```


参考博客：https://zhuanlan.zhihu.com/p/466056522



```python
export PATH=/public/home/hpc2316085405032/software/cuda-11.3/bin:$PATH
export LD_LIBRARY_PATH=/public/home/hpc2316085405032/software/cuda-11.3/lib64:/public/home/hpc2316085405032/software/cuda-11.3/mylib/lib64:$LD_LIBRARY_PATH
```
