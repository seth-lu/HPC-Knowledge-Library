#include <iostream>

using namespace std;

int main()
{
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

    int i=1,j=1,m=4,n=4,r=1,u=3,v=3,s=1;//i为O的批次，j为O的纬度，m为O的行，n为O的列，r是F的纬度，u是F的行，v是F的列
    for(int ii=0; ii<i;ii++){
        for(int jj=0;jj<j;jj++){
            for(int mm=0;mm<m;mm++){
                for(int nn=0;nn<n;nn++){
                    for(int rr=0;rr<r;rr++){
                        for(int uu=0;uu<u;uu++){
                            for(int vv=0;vv<v;vv++){
                                O[ii][jj][mm][nn]+=I[ii][rr][mm*s+uu][nn*s+vv]*F[jj][rr][uu][vv];
                                // cout << O[ii][jj][mm][nn]<<" " << I[ii][rr][mm*s+uu][nn*s+vv]<<" " << F[jj][rr][uu][vv] <<"\n";
                            }
                        }
                    }
                }
            }
        }
    }
    /*
    七个循环，因为要得到的结果是输出张量O，所以O一定会历遍一次，这就需要四个循环，分别历遍O的批次纬度行列。
    然后为了得到O该批次该纬度该行该列的值需要从I和F获得，因为I的批次和O一样，计算时I和F的纬度对应，需要I的行列和F的列行相乘，所以只需要三个循环历遍F的纬度，行和列
    因为OIF批次一样，循环-2，12-2=10。计算时F和I纬度一样，循环-1，10-1=9，F的行列和I的列行对应，循环-2，9-2=7。所以需要7个循环
    */

    //输出计算后的张量O
    for(int ii=0;ii<i;ii++){
        cout << "第"<< ii+1 << "批次\n";
        for(int jj=0;jj<j;jj++){
            cout << "第"<< jj+1 << "纬度\n";
            for(int mm=0;mm<m;mm++){
                cout << "{";
                for(int nn=0;nn<n;nn++){
                    cout << O[ii][jj][mm][nn] << ",";
                }
                cout << "}\n";
            }
        }
    }

}