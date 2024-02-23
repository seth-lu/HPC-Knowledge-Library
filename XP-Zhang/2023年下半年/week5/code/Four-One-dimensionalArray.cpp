#include<iostream>
#include<chrono>
#include"Timer.cpp"

using namespace std;

class DimensionArray{//父类
  protected:
    int n,c,h,w; 
  public:
    //获取指定位置的元素
    virtual double &operator()(int,int,int,int) = 0;
    virtual const double &operator()(int,int,int,int)const = 0;
    //释放申请的空间
    virtual void releaseMemory() = 0;
   //获取批次，纬数，行数，列数
    int num_n() const{return n;}
    int num_c() const{return c;}
    int num_h() const{return h;}
    int num_w() const{return w;}
    
};
//一维数组
class One_dimensionArray : public DimensionArray{
  protected:
    double* I;
  public:
    //初始化，输入矩阵的纬度和初始的值
    One_dimensionArray(int,double);
    //获取指定位置的元素
    double &operator()(int i,int j,int k,int l) override{return I[i*c*h*w+j*h*w+k*w+l];}
    const double &operator()(int i,int j,int k,int l)const override{return I[i*c*h*w+j*h*w+k*w+l];}
    void releaseMemory()override{delete[] I;};
};
One_dimensionArray::One_dimensionArray(int index,double init){//输入矩阵的纬度和初始值
    I=new double[index*index];
    n=1;c=1;h=index;w=index;
    for(int i = 0;i<n;++i){
        for(int j = 0;j<c;++j){
            for(int k = 0;k<h;++k){
                for(int l= 0;l<w;++l){
                    I[i*c*h*w+j*h*w+k*w+l]=init;
                }
            }
        }
    }
}
//四维数组
class Four_dimensionArray : public DimensionArray{
  protected:
    double**** I;
  public:
    //初始化，输入矩阵的纬度和初始的值
    Four_dimensionArray(int,double);
    // 获取指定位置的元素
    double &operator()(int i,int j,int k,int l) override{return I[i][j][k][l];}
    const double &operator()(int i,int j,int k,int l)const override{return I[i][j][k][l];}
    void releaseMemory()override{
        for (int i = 0; i < n; ++i) {
        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < h; ++k) {
                delete[] I[i][j][k];
            }
            delete[] I[i][j];
        }
        delete[] I[i];
    }
    delete[] I;
    };
};
Four_dimensionArray::Four_dimensionArray(int index,double init){//输入矩阵的纬度和初始值
    n=1;c=1;h=index;w=index;
    // 动态分配内存
    I = new double***[n];
    for (int i = 0; i < n; ++i) {
        I[i] = new double**[c];
        for (int j = 0; j < c; ++j) {
            I[i][j] = new double*[h];
            for (int k = 0; k < h; ++k) {
                I[i][j][k] = new double[w];
            }
        }
    }

    for(int i = 0;i<n;++i){
        for(int j = 0;j<c;++j){
            for(int k = 0;k<h;++k){
                for(int l= 0;l<w;++l){
                    I[i][j][k][l]=init;
                }
            }
        }
    }
}

//七层循环
void linearArray(const DimensionArray& data_i, const DimensionArray& data_f, DimensionArray& data_o){
    //依次为O的批次，O的纬度，O的行，O的列，F的纬度，F的行，F的列
    for(int i=0; i<data_o.num_n();i++){
        for(int j=0;j<data_o.num_c();j++){
            for(int m=0;m<data_o.num_h();m++){
                for(int n=0;n<data_o.num_w();n++){
                    for(int r=0;r<data_f.num_c();r++){
                        for(int u=0;u<data_f.num_h();u++){
                            for(int v=0;v<data_f.num_w();v++){
                                data_o(i,j,m,n)+=data_i(i,r,m+u,n+v)*data_f(j,r,u,v);
                                // cout<< data_o(i,j,m,n)<< " " << data_i(i,r,m+u,n+v)<<" " << data_f(j,r,u,v)<<endl;
                            }
                        }
                    }
                }
            }
        }
    }

    // cout << "\n卷积运算后的输入张量：";
    // for(int i=0;i<data_i.num_n();++i){
    //     for(int j=0;j<data_i.num_c();++j){
    //         for(int k=0;k<data_i.num_h();++k){
    //             cout <<"\n";
    //             for(int l=0;l<data_i.num_w();++l){
    //                 cout << data_i(i,j,k,l) <<" ";
    //             }
    //         }
    //     }
    // }
    // cout << "\n卷积运算后的卷积核：";
    // for(int i=0;i<data_f.num_n();++i){
    //     for(int j=0;j<data_f.num_c();++j){
    //         for(int k=0;k<data_f.num_h();++k){
    //             cout <<"\n";
    //             for(int l=0;l<data_f.num_w();++l){
    //                 cout << data_f(i,j,k,l) <<" ";
    //             }
    //         }
    //     }
    // }
    // cout << "\n卷积运算后的输出张量：";
    // for(int i=0;i<data_o.num_n();++i){
    //     for(int j=0;j<data_o.num_c();++j){
    //         for(int k=0;k<data_o.num_h();++k){
    //             cout <<"\n";
    //             for(int l=0;l<data_o.num_w();++l){
    //                 cout << data_o(i,j,k,l) <<" ";
    //             }
    //         }
    //     }
    // }
}

int main(){
    
    cout <<"输入需要循环多少次："<< endl;
    int index ;
    cin >> index;
    cout <<"循环"<< index <<"次" << endl;//循环，因为矩阵太小测不到时间，不过自动填充1/0的话，可以把矩阵调大
    int index_i, index_f;
    cout <<"输入输入矩阵纬度："<< endl;
    cin >> index_i;
    cout <<"输入卷积核纬度："<< endl;
    cin >> index_f;
    cout <<"输入矩阵纬度为："<< index_i << " 卷积核纬度："<< index_f;
    // int index = 1,index_i = 10000,index_f = 2;
    
    //One_dimensionArray Four_dimensionArray
    //全四维数组实现
    Timer T;T.start();
    for(int i=0;i<index;++i){
        Four_dimensionArray I(index_i,1);//输入张量（四维）
        Four_dimensionArray F(index_f,1);//卷积核（四维）
        Four_dimensionArray O(index_i-index_f+1,0);//输出张量（四维）
        linearArray(I,F,O);
        I.releaseMemory();
    }
    T.stop();
    cout << "\n全为四维总耗时:" << T.elapsed() << "毫秒";
    //输入张量为一维，输出张量和卷积核为四维
    T.start();
    for(int i=0;i<index;++i){
        One_dimensionArray I(index_i,1);//输入张量（一维）
        Four_dimensionArray F(index_f,1);//卷积核（四维）
        Four_dimensionArray O(index_i-index_f+1,0);//输出张量（四维）
        linearArray(I,F,O);
        I.releaseMemory();
    }
    T.stop();
    cout << "\n输入张量为一维，输出张量和卷积核为四维总耗时:" << T.elapsed() << "毫秒";
    //输入张量和卷积核为一维，输出张量为四维
    T.start();
    for(int i=0;i<index;++i){
        One_dimensionArray I(index_i,1);//输入张量（一维）
        One_dimensionArray F(index_f,1);//卷积核（一维）
        Four_dimensionArray O(index_i-index_f+1,0);//输出张量（四维）
        linearArray(I,F,O);
        I.releaseMemory();
    }
    T.stop();
    cout << "\n输入张量和卷积核为一维，输出张量为四维总耗时:" << T.elapsed() << "毫秒";
    //全为一维
    T.start();
    for(int i=0;i<index;++i){
        One_dimensionArray I(index_i,1);//输入张量（一维）
        One_dimensionArray F(index_f,1);//卷积核（一维）
        One_dimensionArray O(index_i-index_f+1,0);//输出张量（一维）
        linearArray(I,F,O);
        I.releaseMemory();
    }
    T.stop();
    cout << "\n全为一维总耗时:" << T.elapsed() << "毫秒";
    //输入张量和卷积核为四维，输出张量为一维
    T.start();
    for(int i=0;i<index;++i){
        Four_dimensionArray I(index_i,1);//输入张量（四维）
        Four_dimensionArray F(index_f,1);//卷积核（四维）
        One_dimensionArray O(index_i-index_f+1,0);//输出张量（一维）
        linearArray(I,F,O);
        I.releaseMemory();
    }
    T.stop();
    cout << "\n输入张量和卷积核为四维，输出张量为一维总耗时:" << T.elapsed() << "毫秒";
    //输入张量为四维，输出张量和卷积核为一维
    T.start();
    for(int i=0;i<index;++i){
        Four_dimensionArray I(index_i,1);//输入张量（四维）
        One_dimensionArray F(index_f,1);//卷积核（一维）
        One_dimensionArray O(index_i-index_f+1,0);//输出张量（一维）
        linearArray(I,F,O);
        I.releaseMemory();
    }
    T.stop();
    cout << "\n输入张量为四维，输出张量和卷积核为一维总耗时:" << T.elapsed() << "毫秒";
    //输入张量和输出张量为一维，卷积核为四维
    T.start();
    for(int i=0;i<index;++i){
        One_dimensionArray I(index_i,1);//输入张量（一维）
        Four_dimensionArray F(index_f,1);//卷积核（四维）
        One_dimensionArray O(index_i-index_f+1,0);//输出张量（一维）
        linearArray(I,F,O);
        I.releaseMemory();
    }
    T.stop();
    cout << "\n输入张量和输出张量为一维，卷积核为四维总耗时:" << T.elapsed() << "毫秒";
    //输入张量和输出张量为四维，卷积核为一维
    T.start();
    for(int i=0;i<index;++i){
        Four_dimensionArray I(index_i,1);//输入张量（四维）
        One_dimensionArray F(index_f,1);//卷积核（一维）
        Four_dimensionArray O(index_i-index_f+1,0);//输出张量（四维）
        linearArray(I,F,O);
        I.releaseMemory();
    }
    T.stop();
    cout << "\n输入张量和输出张量为四维，卷积核为一维总耗时:" << T.elapsed() << "毫秒" <<endl;
    while (1==1)
    {
        int endend;
        cout << "好了，结束了" << endl;
        cin >> endend;
        cout <<"你输入了："<<  endend <<endl;
    }
    
}