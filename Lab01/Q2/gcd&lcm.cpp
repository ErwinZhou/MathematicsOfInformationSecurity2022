//��һ����ҵ�ڶ��⣺��д������������������С������
//#include<iostream>
//using namespace std;
//int gcd(int a, int b) {//�������������շת�����
//	int max, min;
//	if (a > b)
//		 max = a, min = b;
//	else
//		 max = b, min = a;
//	while (max % min != 0) {//ֻҪ������Ϊ0���ͼ���
//		int r = max % min;
//		max = min;
//		min = r;
//	}
//	return min;//��ʱ��min������������һ��������r�������һ����Ϊ0�����������������
//}
//int lcm(int a, int b) {//��С������
//	return a * b / gcd(a, b);
//}
//int main() {
//	int a, b;
//	cout << "a=";
//	cin >> a;
//	cout << "b=";
//	cin >> b;
//	cout<<"gcd(a,b)="<<gcd(a, b)<<endl;
//	cout<<"lcm(a,b)="<<lcm(a, b)<<endl;
//	return 0;
//}