//��������ҵ�����ʵ���й�ʣ�ඨ��
#include<iostream>
using namespace std;
int ExtendedEuclideanAlgorithm(int a,int b,int &x,int &y) {//��չ��ŷ������㷨����Ԫ���������M'
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int ret = ExtendedEuclideanAlgorithm(b, a % b, x, y);//�ݹ��������ʱ��õ���x��y����һ��״̬�ģ����Ƶ��Ĺ�ʽ������ʱ��x��y
	int temp = x;
	x = y;
	y = temp - a / b * (y);
	return ret;
}
void ChineseRemainderTheorem(int b[], int m[], int n) {
	int* M = new int[n];//�����������M
	int m0= 1;//m0������������mi�ĳ˻�m
	for (int i = 0; i < n; i++) {
		m0*= m[i];
	}
	for (int i = 0; i < n; i++) {
		M[i] = m0 / m[i];
	}
	int* M1 = new int[n];//M1�����������M����Ԫ
	for (int i = 0; i < n; i++) {
		int x, y;
		ExtendedEuclideanAlgorithm(M[i], m[i],x,y);//������չ��ŷ������㷨��M����ԪM'
		M1[i] = x;
	}
	int result = 0;
	for (int i = 0; i < n; i++) {
		result += M[i] * M1[i] * b[i];
	}
	cout << "x��" << result << " (mod " << m0 << ")" << endl;
	return;
}
int main() {
	int n;
	cout << "n=";
	cin >> n;
	int* b = new int[n];//������Ÿ�������b
	for (int i = 0; i < n; i++) {
		cout << " b_" << i << "=";
		cin >> b[i];
	}
	int* m = new int[n];//������Ÿ���ģ��m
	for (int i = 0; i < n; i++) {
		cout << " m_" << i << "=";
		cin >> m[i];
	}
	ChineseRemainderTheorem(b, m, n);
	return 0;
}