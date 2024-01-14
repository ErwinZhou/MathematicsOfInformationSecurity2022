//第一次作业第三题： 编写程序实现算术基本定理
#include<iostream>
using namespace std;
bool if_vegetable(int n) {//判断是否为素数
	if (n <= 1)
		return false;
	else {
		bool flag = true;
		for (int i = 2; i < n; i++) {
			if (n % i == 0)
				flag = false;
		}
		return flag;
	}
}
void Fundamental_Theorem_of_Arithmetic(int n) {
	int* factor = new int[n];//存放因数
	int NumOfFactor = 0;
	int* exponent = new int[n];//存放指数
	int i = 2;//从最小的素数开始找起
	for (int i = 0; i < n; i++) {
		factor[i] = exponent[i] = -1;
	}
	if (if_vegetable(n)) {//若n本身就为素数，直接输出
		cout << n << "=" << n << "^1" << endl;
		return;
	}
	int temp = n;
	while (!if_vegetable(temp)) {//只要此时的n（temp）没有被除的只剩下一个素数，就继续除
		if (temp % i== 0) {//若能被这个素数整除，则该素数为其一个素数幂
			factor[NumOfFactor] = i;//保存该素数幂
			int current_exponent = 1;//指数为1
			temp = temp / i;
			while (temp % i == 0) {//只要还能被i整除，就继续循环，增加指数
				current_exponent++;
				temp = temp / i;
			}
			exponent[NumOfFactor] = current_exponent;//保存指数
			NumOfFactor++;
		}
		for (int j = i+1;;j++) {//若i不能整除n，则证明i不是其素数幂，去寻找大于i的最小素数，重复此过程
			if (if_vegetable(j))
			{
				i = j;
				break;
			}
		}
	}
	bool flag = false;//是否最后剩下的temp是之前出现过的因子
	for (int t = 0; t < NumOfFactor; t++) {
		if (factor[t] == temp) {///若之前出现过
			exponent[t]++;
			flag = true;
			break;
		}
	}
	if (flag == false) {//若之前所剩下的n是未出现过的指数
		factor[NumOfFactor] = temp;
		exponent[NumOfFactor] = 1;
		NumOfFactor++;
	}
	cout << n<<"=";
	for (int k = 0; k < NumOfFactor; k++) {
		if (k != NumOfFactor - 1)
			cout << factor[k] << "^" << exponent[k] << "*";
		else
			cout << factor[k] << "^" << exponent[k];
	}
	return;

}
int main() {
	int n;
	cout << "Please input n(n>0):";
	cin >> n;
	Fundamental_Theorem_of_Arithmetic(n);
	return 0;
}