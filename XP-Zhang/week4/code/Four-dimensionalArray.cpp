#include<iostream>
#include <chrono>
using namespace std;

//输出四维数组的地址
void addressOfFourdimensionalArray(){
    //输入张量I
    int I[1][1][6][6]={
        {
            {
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0}
            }
        }
    };

    cout <<"输出四维数组所有的地址:";
    for(int i=0;i<1;++i){
        for(int j=0;j<1;++j){
            for(int k=0;k<6;++k){
                for(int l=0;l<6;++l){
                    cout << &I[i][j][k][l] <<" ";
                }
            }
        }
    }

    //输入张量I2
    int I2[1][2][3][3]={
        {
            {
                {10,10,0},
                {10,10,0},
                {10,10,0}
            },
            {
                {10,10,0},
                {10,10,0},
                {10,10,0}
            }
        }
    };

    cout <<"\n输出四维数组所有的地址:";
    for(int i=0;i<1;++i){
        for(int j=0;j<2;++j){
            for(int k=0;k<3;++k){
                for(int l=0;l<3;++l){
                    cout << &I2[i][j][k][l] <<" ";
                }
            }
        }
    }

    //输入张量I3
    int I3[2][2][3][3]={
        {
            {
                {10,10,0},
                {10,10,0},
                {10,10,0}
            },
            {
                {10,10,0},
                {10,10,0},
                {10,10,0}
            }
        },
        {
            {
                {10,10,0},
                {10,10,0},
                {10,10,0}
            },
            {
                {10,10,0},
                {10,10,0},
                {10,10,0}
            }
        }
    };

    cout <<"\n输出四维数组所有的地址:";
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            for(int k=0;k<3;++k){
                for(int l=0;l<3;++l){
                    cout << &I3[i][j][k][l] <<" ";
                }
            }
        }
    }

}

//用一维数组实现七层循环
void linearArray(){
    //输入张量I
    int I[36] = {10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0};
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[9] = {1,0,-1,1,0,-1,1,0,-1};
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int on=1;int oc=1;int oh=4;int ow=4;
    
    //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                                O[i*oc*oh*ow+j*oh*ow+m*ow+n]+=I[i*ic*ih*iw+r*ih*iw+(m+u)*iw+n+v]*F[j*fc*fh*fw+r*fh*fw+u*fw+v];

                            }
                        }
                    }
                }
            }
        }
    }

    cout << "卷积运算后的输出张量：";
    for(int i=0;i<on;++i){
        for(int j=0;j<oc;++j){
            for(int k=0;k<oh;++k){
                cout <<"\n";
                for(int l=0;l<ow;++l){
                    cout << O[i*oc*oh*ow+j*oh*ow+k*ow+l] <<" ";
                }
            }
        }
    }
}

//全四维数组实现
void example1(){
    //输入张量I
    int I[1][1][6][6]={
        {
            {
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0}
            }
        }
    };
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[1][1][3][3]={
        {
            {
                {1,0,-1},
                {1,0,-1},
                {1,0,-1}
            }
        }
    };
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[1][1][4][4]={
        {
            {
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            }
        }
    };
    int on=1;int oc=1;int oh=4;int ow=4;

     //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                               O[i][j][m][n]+=I[i][r][m+u][n+v]*F[j][r][u][v];
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "卷积运算后的输出张量：";
    // for(int i=0;i<on;++i){
    //     for(int j=0;j<oc;++j){
    //         for(int k=0;k<oh;++k){
    //             cout <<"\n";
    //             for(int l=0;l<ow;++l){
    //                 cout << O[i][j][k][l] <<" ";
    //             }
    //         }
    //     }
    // }

}

//输入张量为一维，其他为四维
void example2(){
    //输入张量I
    int I[36] = {10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0};
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[1][1][3][3]={
        {
            {
                {1,0,-1},
                {1,0,-1},
                {1,0,-1}
            }
        }
    };
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[1][1][4][4]={
        {
            {
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            }
        }
    };
    int on=1;int oc=1;int oh=4;int ow=4;

     //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                               O[i][j][m][n]+=I[i*ic*ih*iw+r*ih*iw+(m+u)*iw+n+v]*F[j][r][u][v];
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "卷积运算后的输出张量：";
    // for(int i=0;i<on;++i){
    //     for(int j=0;j<oc;++j){
    //         for(int k=0;k<oh;++k){
    //             cout <<"\n";
    //             for(int l=0;l<ow;++l){
    //                 cout << O[i][j][k][l] <<" ";
    //             }
    //         }
    //     }
    // }

}

//输入张量和卷积核为一维，输出张量为四维
void example3(){
    //输入张量I
    int I[36] = {10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0};
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[9] = {1,0,-1,1,0,-1,1,0,-1};
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[1][1][4][4]={
        {
            {
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            }
        }
    };
    int on=1;int oc=1;int oh=4;int ow=4;

     //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                               O[i][j][m][n]+=I[i*ic*ih*iw+r*ih*iw+(m+u)*iw+n+v]*F[j*fc*fh*fw+r*fh*fw+u*fw+v];
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "卷积运算后的输出张量：";
    // for(int i=0;i<on;++i){
    //     for(int j=0;j<oc;++j){
    //         for(int k=0;k<oh;++k){
    //             cout <<"\n";
    //             for(int l=0;l<ow;++l){
    //                 cout << O[i][j][k][l] <<" ";
    //             }
    //         }
    //     }
    // }

}

//全为一维数组
void example4(){
    //输入张量I
    int I[36] = {10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0};
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[9] = {1,0,-1,1,0,-1,1,0,-1};
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int on=1;int oc=1;int oh=4;int ow=4;
    
    //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                                O[i*oc*oh*ow+j*oh*ow+m*ow+n]+=I[i*ic*ih*iw+r*ih*iw+(m+u)*iw+n+v]*F[j*fc*fh*fw+r*fh*fw+u*fw+v];

                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "卷积运算后的输出张量：";
    // for(int i=0;i<on;++i){
    //     for(int j=0;j<oc;++j){
    //         for(int k=0;k<oh;++k){
    //             cout <<"\n";
    //             for(int l=0;l<ow;++l){
    //                 cout << O[i*oc*oh*ow+j*oh*ow+k*ow+l] <<" ";
    //             }
    //         }
    //     }
    // }
}

//输入张量和卷积核为四维，输出张量为一维
void example5(){
    //输入张量I
    int I[1][1][6][6]={
        {
            {
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0}
            }
        }
    };
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[1][1][3][3]={
        {
            {
                {1,0,-1},
                {1,0,-1},
                {1,0,-1}
            }
        }
    };
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int on=1;int oc=1;int oh=4;int ow=4;
    
    //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                                O[i*oc*oh*ow+j*oh*ow+m*ow+n]+=I[i][r][m+u][n+v]*F[j][r][u][v];
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "卷积运算后的输出张量：";
    // for(int i=0;i<on;++i){
    //     for(int j=0;j<oc;++j){
    //         for(int k=0;k<oh;++k){
    //             cout <<"\n";
    //             for(int l=0;l<ow;++l){
    //                 cout << O[i*oc*oh*ow+j*oh*ow+k*ow+l] <<" ";
    //             }
    //         }
    //     }
    // }
}

//输入张量为四维，输出张量和卷积核为一维
void example6(){
    //输入张量I
    int I[1][1][6][6]={
        {
            {
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0}
            }
        }
    };
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[9] = {1,0,-1,1,0,-1,1,0,-1};
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int on=1;int oc=1;int oh=4;int ow=4;
    
    //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                                O[i*oc*oh*ow+j*oh*ow+m*ow+n]+=I[i][r][m+u][n+v]*F[j*fc*fh*fw+r*fh*fw+u*fw+v];
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "卷积运算后的输出张量：";
    // for(int i=0;i<on;++i){
    //     for(int j=0;j<oc;++j){
    //         for(int k=0;k<oh;++k){
    //             cout <<"\n";
    //             for(int l=0;l<ow;++l){
    //                 cout << O[i*oc*oh*ow+j*oh*ow+k*ow+l] <<" ";
    //             }
    //         }
    //     }
    // }
}

//输入张量和输出张量为一维，卷积核为四维
void example7(){
    //输入张量I
    int I[36] = {10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0};
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[1][1][3][3]={
        {
            {
                {1,0,-1},
                {1,0,-1},
                {1,0,-1}
            }
        }
    };
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int on=1;int oc=1;int oh=4;int ow=4;
    
    //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                                O[i*oc*oh*ow+j*oh*ow+m*ow+n]+=I[i*ic*ih*iw+r*ih*iw+(m+u)*iw+n+v]*F[j][r][u][v];
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "卷积运算后的输出张量：";
    // for(int i=0;i<on;++i){
    //     for(int j=0;j<oc;++j){
    //         for(int k=0;k<oh;++k){
    //             cout <<"\n";
    //             for(int l=0;l<ow;++l){
    //                 cout << O[i*oc*oh*ow+j*oh*ow+k*ow+l] <<" ";
    //             }
    //         }
    //     }
    // }
}

//输入张量和输出张量为四维，卷积核为一维
void example8(){
    //输入张量I
    int I[1][1][6][6]={
        {
            {
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0},
                {10,10,10,0,0,0}
            }
        }
    };
    int in=1;int ic=1;int ih=6;int iw=6;//依次为批次，纬度，行数，列数
    //卷积核F
    int F[9] = {1,0,-1,1,0,-1,1,0,-1};
    int fn=1;int fc=1;int fh=3;int fw=3;
    //输出张量O
    int O[1][1][4][4]={
        {
            {
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            }
        }
    };
    int on=1;int oc=1;int oh=4;int ow=4;
    
    //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<on;i++){
        for(int j=0;j<oc;j++){
            for(int m=0;m<oh;m++){
                for(int n=0;n<ow;n++){
                    for(int r=0;r<fc;r++){
                        for(int u=0;u<fh;u++){
                            for(int v=0;v<fw;v++){
                                O[i][j][m][n]+=I[i][r][m+u][n+v]*F[j*fc*fh*fw+r*fh*fw+u*fw+v];
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "卷积运算后的输出张量：";
    // for(int i=0;i<on;++i){
    //     for(int j=0;j<oc;++j){
    //         for(int k=0;k<oh;++k){
    //             cout <<"\n";
    //             for(int l=0;l<ow;++l){
    //                 cout << O[i][j][k][l] <<" ";
    //             }
    //         }
    //     }
    // }
}

int main(){
    // addressOfFourdimensionalArray();
    // linearArray();
    // example1();
    // example2();
    // example3();
    // example4();
    // example5();
    // example6();
    // example7();
    // example8();

    int index = 100000;
    cout <<"循环"<< index <<"次";
    auto beforeTime = chrono::steady_clock::now();
    for(int i=0;i<index;++i){
        example1();
    }
    auto afterTime = chrono::steady_clock::now();
    double time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n全为四维总耗时:" << time << "纳秒";

    beforeTime = chrono::steady_clock::now();
    for(int i=0;i<index;++i){
        example2();
    }
    afterTime = chrono::steady_clock::now();
    time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n输入张量为一维，输出张量和卷积核为四维总耗时:" << time << "纳秒";

    beforeTime = chrono::steady_clock::now();
    for(int i=0;i<index;++i){
        example3();
    }
    afterTime = chrono::steady_clock::now();
    time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n输入张量和卷积核为一维，输出张量为四维总耗时:" << time << "纳秒";

    beforeTime = chrono::steady_clock::now();
    for(int i=0;i<index;++i){
        example4();
    }
    afterTime = chrono::steady_clock::now();
    time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n全为一维总耗时:" << time << "纳秒";

    beforeTime = chrono::steady_clock::now();
    for(int i=0;i<index;++i){
        example5();
    }
    afterTime = chrono::steady_clock::now();
    time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n输入张量和卷积核为四维，输出张量为一维总耗时:" << time << "纳秒";

    beforeTime = chrono::steady_clock::now();
    for(int i=0;i<index;++i){
        example6();
    }
    afterTime = chrono::steady_clock::now();
    time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n输入张量为四维，输出张量和卷积核为一维总耗时:" << time << "纳秒";

    beforeTime = chrono::steady_clock::now();
    for(int i=0;i<index;++i){
        example7();
    }
    afterTime = chrono::steady_clock::now();
    time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n输入张量和输出张量为一维，卷积核为四维++i总耗时:" << time << "纳秒";

    beforeTime = chrono::steady_clock::now();
    for(int i=0;i<index;++i){
        example8();
    }
    afterTime = chrono::steady_clock::now();
    time = chrono::duration<double, nano>(afterTime - beforeTime).count();
    cout << "\n输入张量和输出张量为四维，卷积核为一维总耗时:" << time << "纳秒";

}