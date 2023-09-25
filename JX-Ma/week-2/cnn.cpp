#include<iostream>

using namespace std;

int main() {
	// 定义输入张量
	int I[1][3][3][3] = 
	{
		{
			{{1,2,3},{4,5,6},{7,8,9}},
			{{11,12,13},{14,15,16},{17,18,19}},
			{{21,22,23},{24,25,26},{27,28,29}}
		}
	};
	int F[1][3][2][2] =
	{
		{
			{{31,32},{33,34}},
			{{41,42},{43,44}},
			{{51,52},{53,54}}
		}
	};
	int O[1][1][2][2] = 
	{
		{
			{{0,0},{0,0}}
		}
	};
	int No = 1,Co = 1,Ho = 2,Wo = 2;
	int Cf = 3, Hf = 2, Wf = 2;

	for (int i = 0; i <= No - 1; i++)
		for (int j = 0; j <= Co - 1; j++)
			for (int m = 0; m <= Ho - 1; m++)
				for (int n = 0; n <= Wo - 1; n++)
				{
					cout << "输出张量第" << n + 1 + m * Wo << "个元素运算开始" << endl;
					for (int r = 0; r <= Cf - 1; r++)
						for (int u = 0; u <= Hf - 1; u++)
							for (int v = 0; v <= Wf - 1; v++) {
								cout << "第" << r * (Hf + Wf) + u * (Wf)+v + 1 << "步的乘数:" << I[i][r][m + u][n + v] << "和" << F[j][r][u][v] << endl;
									O[i][j][m][n] += I[i][r][m + u][n + v] * F[j][r][u][v];
							}
				}
					
								

}