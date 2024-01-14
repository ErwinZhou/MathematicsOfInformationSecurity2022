//��һ����ҵ�����⣺ ��д����ʵ��������������
#include<iostream>
using namespace std;
bool if_vegetable(int n) {//�ж��Ƿ�Ϊ����
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
	int* factor = new int[n];//�������
	int NumOfFactor = 0;
	int* exponent = new int[n];//���ָ��
	int i = 2;//����С��������ʼ����
	for (int i = 0; i < n; i++) {
		factor[i] = exponent[i] = -1;
	}
	if (if_vegetable(n)) {//��n�����Ϊ������ֱ�����
		cout << n << "=" << n << "^1" << endl;
		return;
	}
	int temp = n;
	while (!if_vegetable(temp)) {//ֻҪ��ʱ��n��temp��û�б�����ֻʣ��һ���������ͼ�����
		if (temp % i== 0) {//���ܱ���������������������Ϊ��һ��������
			factor[NumOfFactor] = i;//�����������
			int current_exponent = 1;//ָ��Ϊ1
			temp = temp / i;
			while (temp % i == 0) {//ֻҪ���ܱ�i�������ͼ���ѭ��������ָ��
				current_exponent++;
				temp = temp / i;
			}
			exponent[NumOfFactor] = current_exponent;//����ָ��
			NumOfFactor++;
		}
		for (int j = i+1;;j++) {//��i��������n����֤��i�����������ݣ�ȥѰ�Ҵ���i����С�������ظ��˹���
			if (if_vegetable(j))
			{
				i = j;
				break;
			}
		}
	}
	bool flag = false;//�Ƿ����ʣ�µ�temp��֮ǰ���ֹ�������
	for (int t = 0; t < NumOfFactor; t++) {
		if (factor[t] == temp) {///��֮ǰ���ֹ�
			exponent[t]++;
			flag = true;
			break;
		}
	}
	if (flag == false) {//��֮ǰ��ʣ�µ�n��δ���ֹ���ָ��
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