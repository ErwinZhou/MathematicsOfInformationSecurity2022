//第二次作业第一题：编程实现平方-乘算法
#include<iostream>
#include<stack>
using namespace std;
stack<int> DecimalToBinary(unsigned  long long n) {//计算十进制转二进制，用一个栈s来保存
	stack<int> s;
	while (n!= 0) {
		int r = n % 2;
		s.push(r);
		n = n / 2;
	}
	return s;
}
unsigned long long  SquareAndMultiplyAlgorithm(unsigned long long a, unsigned long long n, unsigned long long m) {
	unsigned long long result = 1;//result定义为64位的整型,防止中间结果超过32位而发生溢出
	stack<int> s = DecimalToBinary(n);
	while (!s.empty()) {//由于算法的特性，先要处理的是二进制的头位，即在二进制转为十进制方法中最后得到的余数
		                //符合FILO的特性，故采用栈的形式存储并操作
		result = (result*result) % m;
		if(s.top()==1){
			result = (result *a) % m;
		}
		s.pop();
	}
	return result;
}
//unsigned recur_pow_mod(unsigned  a, unsigned  b, unsigned  mod)
//{
//	unsigned long long  result = 1; //这里result定义为64位的整型是因为有时result的中间值会超过32位，如果只用unsigned会溢出
//	unsigned array[64] = { 0 };  //用来存储b的二进制形式的每一位数
//	unsigned length = 0;
//	while (b)
//	{
//		array[length++] = b & 1;
//		b >>= 1;
//	}
//	for (int j = length - 1; j >= 0; j--)
//	{
//		if (array[j] == 1)
//			result = (result * result * a) % mod;
//		else
//			result = (result * result) % mod;
//	}
//	return result;
//}
int main() {
	cout << "Calculate a^n(mod m)..." << endl;
	cout << "Please inpust:" << endl;
	unsigned long long a;
	cout << "  a=";
	cin >> a;
	unsigned long long n;
	cout << "  n=";
	cin >> n;
	unsigned  long long m;
	cout << "  m=";
	cin >> m;
	cout << a << "^" << n << "(mod " << m << ")=" << SquareAndMultiplyAlgorithm(a,n,m)<< endl;
	return 0;
}