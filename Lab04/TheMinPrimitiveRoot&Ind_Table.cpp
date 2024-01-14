////���Ĵ���ҵ��һ�⣺���ʵ�������Сԭ����������Сԭ������ָ����
#include<iostream>
#include<cmath>
#include<stack>
#include<vector>
#include<iomanip>
using namespace std;
stack<int> DecimalToBinary(unsigned  long long n) {//����ʮ����ת�����ƣ���һ��ջs�����棬��������ʹ��ƽ�����㷨
	stack<int> s;
	while (n != 0) {
		int r = n % 2;
		s.push(r);
		n = n / 2;
	}
	return s;
}
unsigned long long  SquareAndMultiplyAlgorithm(unsigned long long a, unsigned long long n, unsigned long long m) {//ƽ�����㷨���������������Сԭ��������ָ����
	unsigned long long result = 1;//result����Ϊ64λ������,��ֹ�м�������32λ���������
	stack<int> s = DecimalToBinary(n);
	while (!s.empty()) {//�����㷨�����ԣ���Ҫ������Ƕ����Ƶ�ͷλ�����ڶ�����תΪʮ���Ʒ��������õ�������
		//����FILO�����ԣ��ʲ���ջ����ʽ�洢������
		result = (result * result) % m;
		if (s.top() == 1) {
			result = (result * a) % m;
		}
		s.pop();
	}
	return result;
}
bool if_vegetable(int n) {//�ж��Ƿ�Ϊ����,����ʹ�ü���ŷ������,�Լ��������ֵط�
	if (n <= 1)
		return false;
	else {
		for (int i = 2; i < n; i++) {
			if (n % i == 0) {
				return false;
			}
		}
		return true;
	}
}
int gcd(int a, int b) {//����շת�����,����������������������ж��������Ƿ���
	int max, min;
	if (a > b)
		max = a, min = b;
	else
		max = b, min = a;
	while (max % min != 0) {//ֻҪ������Ϊ0���ͼ���
		int r = max % min;
		max = min;
		min = r;
	}
	return min;//��ʱ��min������������һ��������r�������һ����Ϊ0�����������������
}
bool if_Coprime(int a, int b) {//�ж��������Ƿ��أ������������n��ŷ����������n����ϵ��С
	return gcd(a, b) == 1;
}
int EulerTotientFunction(int n) {//����ŷ���������������������Сԭ��
	int CoPrimeCount = 0;
	for (int i = 1; i < n; i++) {//�жϴ�1-n-1����n���ص������������Ϊn����ϵ��С
		if (if_Coprime(i, n)) {
			CoPrimeCount++;
		}
	}
	return CoPrimeCount;
}
void ReducedResidueSystem(int n, vector<int>& CoPrimes) {//�������n��������ϵ��Ԫ�أ��������������Сԭ��
	for (int i = 1; i < n; i++) {
		if (if_Coprime(i, n)) {//�жϴ�1-n-1����n���ص�����������֮���أ�����ѹ��vector
			CoPrimes.push_back(i);
		}
	}
}
void FundamentalTheoremOfArithmetic(int n,vector<int>& PrimeFactor) {//�������������������������Сԭ��
	int* factor = new int[n];//�������
	int NumOfFactor = 0;
	int* exponent = new int[n];//���ָ��
	int i = 2;//����С������2��ʼ����
	for (int i = 0; i < n; i++) {
		factor[i] = exponent[i] = -1;
	}
	if (if_vegetable(n)) {//��n�����Ϊ����������Ψһһ��������Ϊ���Լ�
		factor[NumOfFactor] = n;
		NumOfFactor++;
		for (int k = 0; k < NumOfFactor; k++) {//��֮ǰ����������ӷ���PrimeFactor��
			PrimeFactor.push_back(factor[k]);
		}
		return;
	}
	int temp = n;
	while (!if_vegetable(temp)&&temp!=1) {//ֻҪ��ʱ��n��temp��û�б�����ֻʣ��һ���������ͼ�����
		if (temp % i == 0) {//���ܱ���������������������Ϊ��һ��������
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
		for (int j = i + 1;; j++) {//��i��������n����֤��i�����������ݣ�ȥѰ�Ҵ���i����С�������ظ��˹���
			if (if_vegetable(j))
			{
				i = j;
				break;
			}
		}
	}
	//����������һ�����������������n=8������temp=2ʱ���Ѿ��˳�ѭ�������Ǵ�ʱ2ҲΪ�������ӣ���Ҫ��¼��
	bool flag = false;//�Ƿ����ʣ�µ�temp��֮ǰ���ֹ���������
	for (int t = 0; t < NumOfFactor; t++) {
		if (factor[t] == temp) {//��֮ǰ���ֹ�
			exponent[t]++;
			flag = true;
			break;
		}
	}
	if (flag == false&&temp!=1) {//��֮ǰ��ʣ�µ�temp��δ���ֹ��������ӣ����䱣��
		factor[NumOfFactor] = temp;
		exponent[NumOfFactor] = 1;
		NumOfFactor++;
	}
	for (int k = 0; k < NumOfFactor; k++) {//��֮ǰ����������ӷ���PrimeFactor��
		PrimeFactor.push_back(factor[k]);
	}
	return;
}
int TheMinPrimitiveRoot(int n) {//�����Сԭ��
	int ETF_n = EulerTotientFunction(n);//��ȡn��ŷ����ETF_n
	vector<int> PrimeFactor;//Ѱ�Ҳ���¼����ETF_n��������
	FundamentalTheoremOfArithmetic(ETF_n, PrimeFactor);
	vector<int> RequiredExponent;//������¼���������жϵ�ָ��
	for (int i = 0; i < PrimeFactor.size(); i++) {
		RequiredExponent.push_back(ETF_n/PrimeFactor[i]);
	}
	vector<int> ReducedResidueSystem_n;//������¼n����ϵ
	ReducedResidueSystem(n, ReducedResidueSystem_n);
	for (int i = 1; i < ETF_n; i++) {//�ӳ�ȥ1�ĵڶ���Ԫ�ؿ�ʼ�����ж�n����ϵ�е�Ԫ���Ƿ��������
		bool flag = true;//������¼�Ƿ��жϳɹ�
		for (int j = 0; j < RequiredExponent.size(); j++) {//������Ҫ���ָ�������һ��
			if (SquareAndMultiplyAlgorithm(ReducedResidueSystem_n[i], RequiredExponent[j], n) == 1) {
				flag = false;//ʧ��
				break;
			}
		}
		if (flag)//���ɹ������ʱ��i����Ϊ��Сԭ��
			return ReducedResidueSystem_n[i];
	}
	return -1;
}
int DiscreteLogarithm(int g, int a, int n) {//������ɢ����,������������ָ����
	int ETF_n = EulerTotientFunction(n);//��Ϊg��0-ETF_n-1�η�����ģn��һ����ϵ
	for (int i = 0; i < ETF_n; i++) {
		if (SquareAndMultiplyAlgorithm(g, i, n) == a) {
			return i;
		}
	}
}
void CreateInd_Table(int n, int g) {//����ָ����
	int ETF_n = EulerTotientFunction(n);
	vector<int> ReducedResidueSystem_n;//������¼n����ϵ
	ReducedResidueSystem(n, ReducedResidueSystem_n);
	cout << setw(5) << " ";
	cout.fill(' ');//���ݿ�Ȳ���ʱ���Զ����ո�fill��Ա�����������������ַ�
	for (int i = 0; i < 10; i++) {//�����ָ����ĵ�һ�У�����λ����
		cout << setw(5) << i;
		cout.fill(' ');//���ݿ�Ȳ���ʱ���Զ����ո�fill��Ա�����������������ַ�
	}
	cout << endl;
	int currentNum = 0;//��¼���ڱ�����n����ϵ�ĵڼ�λ��
	for (int i = 0; i <=n/10; i++) {//���ѭ����ÿ�У�Ϊָ�����ʮλ����n/10����ȡ�����õõ���������
		cout << setw(5) << i;//���ʮλ������
		for (int j = 0; j < 10; j++) {//�ڲ�ѭ����ÿ�У�Ϊָ����ĸ�λ
			if (i == 0 && j == 0) {//00��λ����Զ�����
				cout << setw(5) << "-";
				cout.fill(' ');//���ݿ�Ȳ���ʱ���Զ����ո�fill��Ա�����������������ַ�
				continue;
			}
			int a = 10 * i + j;//�����Ӧ��indga��a
			if (a<n) {//����ʱ��a��nС���������
				if (ReducedResidueSystem_n[currentNum] == a) {//��Ϊ����n�����������ӵ�n����ϵҲ�Ǵ�С������һ����a��ͬ
					                                          //�����ж�a�ǲ���n����ϵ�е�Ԫ�أ����ǣ�������ɢ��������ֱ�Ӽ���
					cout << setw(5) << DiscreteLogarithm(g, a, n);
					cout.fill(' ');//���ݿ�Ȳ���ʱ���Զ����ո�fill��Ա�����������������ַ�
					currentNum++;
					continue;
				}
				else {//��a��Ϊn����ϵ�е�Ԫ�أ�ֱ�����
					cout << setw(5) << "-";
					cout.fill(' ');//���ݿ�Ȳ���ʱ���Զ����ո�fill��Ա�����������������ַ�
					continue;
				}
			}
			else {//����ʱָ����n��ֱ�������-��
				cout << setw(5) << "-";
				cout.fill(' ');//���ݿ�Ȳ���ʱ���Զ����ո�fill��Ա�����������������ַ�
				continue;
			}
		}
		cout << endl;
	}
	return;
}
int main() {
	int n;
	cout << "Please input n(n>0): ";
	cin >> n;
	int g = TheMinPrimitiveRoot(n);
	if (g == -1) {
		cout <<n<<" has no primitive root!" << endl;
		return 0;
	}
	cout << "The min primitive root of " << n << ": g=" << g << endl;
	cout << "The ind_table of " << n << " based on g=" << g << " is:" << endl;
	CreateInd_Table(n, g);
	return 0;
}