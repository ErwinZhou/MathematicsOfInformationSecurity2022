//�ڶ�����ҵ��һ�⣺���ʵ��ƽ��-���㷨
#include<iostream>
#include<stack>
using namespace std;
stack<int> DecimalToBinary(unsigned  long long n) {//����ʮ����ת�����ƣ���һ��ջs������
	stack<int> s;
	while (n!= 0) {
		int r = n % 2;
		s.push(r);
		n = n / 2;
	}
	return s;
}
unsigned long long  SquareAndMultiplyAlgorithm(unsigned long long a, unsigned long long n, unsigned long long m) {
	unsigned long long result = 1;//result����Ϊ64λ������,��ֹ�м�������32λ���������
	stack<int> s = DecimalToBinary(n);
	while (!s.empty()) {//�����㷨�����ԣ���Ҫ������Ƕ����Ƶ�ͷλ�����ڶ�����תΪʮ���Ʒ��������õ�������
		                //����FILO�����ԣ��ʲ���ջ����ʽ�洢������
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
//	unsigned long long  result = 1; //����result����Ϊ64λ����������Ϊ��ʱresult���м�ֵ�ᳬ��32λ�����ֻ��unsigned�����
//	unsigned array[64] = { 0 };  //�����洢b�Ķ�������ʽ��ÿһλ��
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