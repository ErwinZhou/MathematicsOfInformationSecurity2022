//第三次作业：编程实现中国剩余定理
#include<iostream>
using namespace std;
int ExtendedEuclideanAlgorithm(int a,int b,int &x,int &y) {//扩展的欧几里得算法求逆元，用于求解M'
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int ret = ExtendedEuclideanAlgorithm(b, a % b, x, y);//递归结束返回时候得到的x和y是下一个状态的，由推导的公式决定此时的x和y
	int temp = x;
	x = y;
	y = temp - a / b * (y);
	return ret;
}
void ChineseRemainderTheorem(int b[], int m[], int n) {
	int* M = new int[n];//用来保存各个M
	int m0= 1;//m0用来保存所有mi的乘积m
	for (int i = 0; i < n; i++) {
		m0*= m[i];
	}
	for (int i = 0; i < n; i++) {
		M[i] = m0 / m[i];
	}
	int* M1 = new int[n];//M1用来保存各个M的逆元
	for (int i = 0; i < n; i++) {
		int x, y;
		ExtendedEuclideanAlgorithm(M[i], m[i],x,y);//调用扩展的欧几里得算法求M的逆元M'
		M1[i] = x;
	}
	int result = 0;
	for (int i = 0; i < n; i++) {
		result += M[i] * M1[i] * b[i];
	}
	cout << "x≡" << result << " (mod " << m0 << ")" << endl;
	return;
}
int main() {
	int n;
	cout << "n=";
	cin >> n;
	int* b = new int[n];//用来存放各个余数b
	for (int i = 0; i < n; i++) {
		cout << " b_" << i << "=";
		cin >> b[i];
	}
	int* m = new int[n];//用来存放各个模数m
	for (int i = 0; i < n; i++) {
		cout << " m_" << i << "=";
		cin >> m[i];
	}
	ChineseRemainderTheorem(b, m, n);
	return 0;
}