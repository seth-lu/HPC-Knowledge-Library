#include<vector>

class Matrix{
private:
  size_t num_rows_,num_cols_;
  std::vector<double> storage_;
public:
  //构造函数
  Matrix(size_t M,size_t N)
    :num_rows_(M),num_cols_(N),storage_(num_rows_*num_cols_){}
  Matrix(size_t M,size_t N,double init)
    :num_rows_(M),num_cols_(N),storage_(num_rows_*num_cols_,init){}
  
  //获取指定位置的元素
  double &operator()(size_t i,size_t j){return storage_[i*num_cols_+j];}
  const double &operator()(size_t i,size_t j)const{return storage_[i*num_cols_+j];}
  //获取行列数量
  size_t num_rows() const {return num_rows_;}
  size_t num_cows() const {return num_cols_;}

};