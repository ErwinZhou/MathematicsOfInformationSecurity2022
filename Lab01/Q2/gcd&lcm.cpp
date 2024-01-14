//第一次作业第二题：编写程序计算最大公因数和最小公倍数
//#include<iostream>
//using namespace std;
//int gcd(int a, int b) {//最大公因数，采用辗转相除法
//	int max, min;
//	if (a > b)
//		 max = a, min = b;
//	else
//		 max = b, min = a;
//	while (max % min != 0) {//只要余数不为0，就继续
//		int r = max % min;
//		max = min;
//		min = r;
//	}
//	return min;//此时的min（除数）是上一步的余数r，即最后一个不为0的余数，即最大公因数
//}
//int lcm(int a, int b) {//最小公倍数
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