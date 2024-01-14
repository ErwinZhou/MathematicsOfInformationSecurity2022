////�ڶ�����ҵ�ڶ��⣺���ʵ����չ��ŷ������㷨����Ԫ��
#include<iostream>
#include<vector>
using namespace std;
void ExtendedEuclideanAlgorithm(int result[],int a,int b) {//��չ��ŷ������㷨
	                                                       //result���飬result[0]��gcd���������result[1]����С������
	                                                       //result[2]��a^(-1)(mod b),result[3]��b^(-1)(mod a)
	int r0, r1;
	a > b ? r0 = a, r1 = b : r0 = b, r1 = a;//���жϽϴ����Ϊr0����С����Ϊr1
	vector<int> v_r, v_q, v_s, v_t;//�ֱ��������ri,qi,si,ti��vector���ͱ���
	v_r.push_back(r0), v_r.push_back(r1);
	v_q.push_back(-1);//q0�ò��ϣ���������ֵ
	v_s.push_back(1), v_s.push_back(0);//s0=1,s1=0
	v_t.push_back(0), v_t.push_back(1);//t0=0,t1=1
	//�ڽ��м���֮ǰ���ȳ�ʼ������
	while (v_r[v_r.size()-2]%v_r[v_r.size()-1]){//ֻҪ������Ϊ0
		v_q.push_back(v_r[v_r.size() - 2] / v_r[v_r.size() - 1]);
		v_r.push_back(v_r[v_r.size() - 2] % v_r[v_r.size() - 1]);
		v_s.push_back(v_s[v_s.size() - 2] - v_q[v_q.size()-1] * v_s[v_s.size() - 1]);
		v_t.push_back(v_t[v_t.size() - 2] - v_q[v_q.size()-1] * v_t[v_t.size() - 1]);
	}
	result[0] = v_r[v_r.size() - 1], result[1] = a * b / result[0];
	if (a > b) {//r0=a,r1=b
		if (v_s[v_s.size() - 1] < 0) {//�ж�һ��ϵ���Ƿ�Ϊ�����������⴦��
			result[2] = b + v_s[v_s.size() - 1];//result[2]��a^(-1)(mod b),��b+
		}
		else {
			result[2] = v_s[v_s.size() - 1];
		}
		if (v_t[v_t.size() - 1] < 0) {
			result[3] = a + v_t[v_t.size() - 1];//result[3]��b^(-1)(mod a)����a+
		}
		else {
			result[3] = v_t[v_t.size() - 1];
		}
	}
	else {//r0=b,r1=a
		if (v_s[v_s.size() - 1] < 0) {//�ж�һ��ϵ���Ƿ�Ϊ�����������⴦��
			result[3] = a + v_s[v_s.size() - 1];//result[3]��b^(-1)(mod a)����a+
		}
		else {
			result[3] = v_s[v_s.size() - 1];
		}
		if (v_t[v_t.size() - 1] < 0) {
			result[2] = b + v_t[v_t.size() - 1];//result[2]��a^(-1)(mod b),��b+
		}
		else {
			result[2] = v_t[v_t.size() - 1];
		}
	}
	return;
}
//�Ľ��汾�������ô��ݣ���������
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
int main() {
	/*int a;
	cout << "a=";
	cin >> a;
	int b;
	cout << "b=";
	cin >> b;
	int result[4];
	for (int i = 0; i < 4; i++) {
		result[i] = 0;
	}
	ExtendedEuclideanAlgorithm(result, a, b);
	cout << "gcd(a,b)=" << result[0] << endl;
	cout << "lcm(a,b)=" << result[1] << endl;
	cout << "a^(-1)=" << result[2] << "(mod " << b << ")" << endl;
	cout << "b^(-1)=" << result[3] << "(mod " << a << ")" << endl;*/
	int a, p;
	cin >> a >> p;
	int result[4];
	for (int i = 0; i < 4; i++) {
		result[i] = 0;
	}
	ExtendedEuclideanAlgorithm(result, a, p);
	cout << result[2];
	return 0;
}