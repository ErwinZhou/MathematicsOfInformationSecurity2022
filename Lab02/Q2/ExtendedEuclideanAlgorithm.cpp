////第二次作业第二题：编程实现扩展的欧几里得算法求逆元，
#include<iostream>
#include<vector>
using namespace std;
void ExtendedEuclideanAlgorithm(int result[],int a,int b) {//扩展的欧几里得算法
	                                                       //result数组，result[0]存gcd最大公因数，result[1]存最小公倍数
	                                                       //result[2]存a^(-1)(mod b),result[3]存b^(-1)(mod a)
	int r0, r1;
	a > b ? r0 = a, r1 = b : r0 = b, r1 = a;//先判断较大的作为r0，较小的作为r1
	vector<int> v_r, v_q, v_s, v_t;//分别用来存放ri,qi,si,ti的vector类型变量
	v_r.push_back(r0), v_r.push_back(r1);
	v_q.push_back(-1);//q0用不上，附上特殊值
	v_s.push_back(1), v_s.push_back(0);//s0=1,s1=0
	v_t.push_back(0), v_t.push_back(1);//t0=0,t1=1
	//在进行计算之前，先初始化操作
	while (v_r[v_r.size()-2]%v_r[v_r.size()-1]){//只要余数不为0
		v_q.push_back(v_r[v_r.size() - 2] / v_r[v_r.size() - 1]);
		v_r.push_back(v_r[v_r.size() - 2] % v_r[v_r.size() - 1]);
		v_s.push_back(v_s[v_s.size() - 2] - v_q[v_q.size()-1] * v_s[v_s.size() - 1]);
		v_t.push_back(v_t[v_t.size() - 2] - v_q[v_q.size()-1] * v_t[v_t.size() - 1]);
	}
	result[0] = v_r[v_r.size() - 1], result[1] = a * b / result[0];
	if (a > b) {//r0=a,r1=b
		if (v_s[v_s.size() - 1] < 0) {//判断一下系数是否为负，进行特殊处理
			result[2] = b + v_s[v_s.size() - 1];//result[2]存a^(-1)(mod b),用b+
		}
		else {
			result[2] = v_s[v_s.size() - 1];
		}
		if (v_t[v_t.size() - 1] < 0) {
			result[3] = a + v_t[v_t.size() - 1];//result[3]存b^(-1)(mod a)，用a+
		}
		else {
			result[3] = v_t[v_t.size() - 1];
		}
	}
	else {//r0=b,r1=a
		if (v_s[v_s.size() - 1] < 0) {//判断一下系数是否为负，进行特殊处理
			result[3] = a + v_s[v_s.size() - 1];//result[3]存b^(-1)(mod a)，用a+
		}
		else {
			result[3] = v_s[v_s.size() - 1];
		}
		if (v_t[v_t.size() - 1] < 0) {
			result[2] = b + v_t[v_t.size() - 1];//result[2]存a^(-1)(mod b),用b+
		}
		else {
			result[2] = v_t[v_t.size() - 1];
		}
	}
	return;
}
//改进版本，用引用传递，不用数组
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