//第五次作业：实现基本的模P剩余类上椭圆曲线的计算
#include<iostream>
#include<stack>
#include<cmath>
#include<vector>
using namespace std;
int p, a, b;//全局变量曲线的参数p、a、b
bool flag;//定义功能一：是否为椭圆曲线的，若不是重新输入的标志位
class Point {//定义所需的点类
public:
	int x, y;
	Point(int x1, int y1) :x(x1), y(y1) {};
	Point() {};
};
vector<Point> AllPoints;//存储椭圆曲线上的所有点
bool if_vegetable(int n) {//判断是否为素数,辅助使用计算欧拉函数,以及用来各种地方
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
stack<int> DecimalToBinary(unsigned  long long n) {//计算十进制转二进制，用一个栈s来保存，用来辅助使用平方乘算法
	stack<int> s;
	while (n != 0) {
		int r = n % 2;
		s.push(r);
		n = n / 2;
	}
	return s;
}
unsigned long long  SquareAndMultiplyAlgorithm(unsigned long long a, unsigned long long n, unsigned long long m) {//平方乘算法
	unsigned long long result = 1;//result定义为64位的整型,防止中间结果超过32位而发生溢出
	stack<int> s = DecimalToBinary(n);
	while (!s.empty()) {//由于算法的特性，先要处理的是二进制的头位，即在二进制转为十进制方法中最后得到的余数
		//符合FILO的特性，故采用栈的形式存储并操作
		result = (result * result) % m;
		if (s.top() == 1) {
			result = (result * a) % m;
		}
		s.pop();
	}
	return result;
}
int ExtendedEuclideanAlgorithm(int a, int b, int& x, int& y) {//扩展的欧几里得算法求逆元，用于求逆元
	if (!b) {
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
int mod(int a, int p) {//重载取模运算mod
	if (a % p >= 0)
		return a % p;
	else
		return a % p + p;
}
int LegendreSymbol(int a, int p) {//计算勒让德符号
	return mod(pow(a, (p - 1) / 2), p);//由于p一般较小，所以直接采用欧拉判别式法求解
}
bool IfIsInfinitePoint_O(Point P) {//判断是否为无穷远点，设置无穷远点O的x和y均为特殊值INT_MAX
	return P.x == INT_MAX && P.y == INT_MAX ? true : false;
}
void If_EllipticCurve() {//功能一：给定参数p，a，b，判断E_p(a,b)是否为椭圆曲线
	if (p <= 3 || !if_vegetable(p)) {//若p不为大于3的素数
		cout << "E_" << p << "(" << a << "," << b << ") is not Elliptic Curve." << endl;
		flag = false;
		return;
	}
	int temp = 4 * pow(a, 3) + 27 * pow(b, 2);
	temp = mod(temp, p);
	if (!temp) {//判断该曲线是否为光滑曲线
		cout << "E_" << p << "(" << a << "," << b << ") is not Elliptic Curve." << endl;
		flag = false;//若不是椭圆曲线，需要重新在main函数中输入s
		return;
	}
	cout << "E_" << p << "(" << a << "," << b << ") is Elliptic Curve." << endl;
	return;
}
bool IfIsOnEllipticCurve(Point P) {//功能二：判断给定的点P，Q是否在椭圆曲线E_p(a,b)上
	if (IfIsInfinitePoint_O(P)) //若P为无穷远点，则一定在椭圆曲线上
		return true;
	int y_2 = mod(pow(P.x, 3) + a * P.x + b, p);//由椭圆方程求出y^2
	int y1 = 0, y2 = 0;//记录求出的两个二次同余方程的解
	if (LegendreSymbol(y_2, p) == -1)//若勒让德符号为-1，一定无解，一定不在椭圆曲线上
		return false;
	else {
		for (int i = 1; i <= p - 1; i++) {//由于当p一般较小时，可以直接遍历求解二次同余方程
			if (mod(pow(i, 2), p) == y_2) {
				y1 = i;
				y2 = p - y1;//另一解与y1相加为p
				break;
			}
		}
		if (mod(P.y, p) != y1 && mod(P.y, p) != y2)//若坐标的y均不为两个同余方程解，则一定不在椭圆曲线上
			return false;
		else
			return true;
	}
}
Point AddTwoPoints(Point P, Point Q) {//功能三：对在椭圆曲线E_p(a,b)上的两点P,Q，计算P+Q
	Point RP;
	if (IfIsInfinitePoint_O(P)) {//若其中P为无穷远点O
		if (IfIsInfinitePoint_O(Q)) {//若Q也为无穷远点O
			RP.x = RP.y = INT_MAX;
			return RP;
		}
		else {//若Q不为无穷远点O，则结果为Q
			RP.x = Q.x, RP.y = Q.y;
			return RP;
		}
	}
	if (IfIsInfinitePoint_O(Q)) {//若其中Q为无穷远点O
		if (IfIsInfinitePoint_O(Q)) {//若P也为无穷远点O,则结果为O
			RP.x = RP.y = INT_MAX;
			return RP;
		}
		else {//若P不为无穷远点P，则结果为P
			RP.x = P.x, RP.y = P.y;
			return RP;
		}
	}
	if (P.x == Q.x && P.y != Q.y) {//若两个点x坐标相同，但y坐标不同，即为不同点，二者相加结果为与椭圆曲线相交的第三个点——无穷远点O
		//此时对返回的结果点x和y设为最大值即特殊值INT_MAX
		RP.x = RP.y = INT_MAX;
		return RP;
	}
	if (P.x == Q.x && P.y == Q.y) {//若两点相同，为同一点，相加的结果为切线
		int y0 = mod(2 * P.y, p);
		int x0 = mod(3 * P.x * P.x + a, p);
		int a, b;
		ExtendedEuclideanAlgorithm(y0, p, a, b);//调用扩展欧几里得算法求逆元
		int y0ni = a;
		int k = mod(x0 * y0ni, p);
		int x3 = mod(k * k - 2 * P.x, p);
		int y3 = mod(k * (P.x - x3) - P.y, p);
		RP.x = x3, RP.y = y3;
		return RP;
	}
	else {//若两点不相同
		int y0 = mod(Q.y - P.y, p);
		int x0 = mod(Q.x - P.x, p);
		int a, b;
		ExtendedEuclideanAlgorithm(x0, p, a, b);//调用扩展欧几里得算法求逆元
		int x0ni = a;
		int k = mod(y0 * x0ni, p);
		int x3 = mod(k * k - P.x - Q.x, p);
		int y3 = mod(k * (P.x - x3) - P.y, p);
		RP.x = x3, RP.y = y3;
		return RP;
	}
}
Point DoubleAndAdd_ScalarProductOfPoint(Point P, int m) {//功能四：对在椭圆曲线E_p(a,b)上的点P，使用倍加-和算法计算mP
	stack<int> s = DecimalToBinary(m);
	Point T = P;//转换为二进制的结果最高位一定为1，所以T初始化一定为（dt=1）*P=P
	s.pop();
	for (int i = s.size(); i > 0; i--) {
		T = AddTwoPoints(T, T);//Double
		if (s.top())
			T = AddTwoPoints(T, P);//Double+Add
		s.pop();
	}
	return T;
}
Point ScalarProductOfPoint(Point P, int m) {//普通算法实现功能四
	Point temp_P = P;
	for (int i = 2; i <= m; i++)
		temp_P = AddTwoPoints(temp_P, P);
	return temp_P;
}
void OrdOfPointOnEllipticCurve(Point P) {//功能五：对在椭圆曲线E_p(a,b)上的点P，计算阶ord（P）
	if (IfIsInfinitePoint_O(P)) {//若P为O，则其阶为1
		cout << "P which is O:ord(P)=1" << endl;
		return;
	}
	int i = 2;
	while (1) {
		if (IfIsInfinitePoint_O(DoubleAndAdd_ScalarProductOfPoint(P, i))) {//如果iP=O,则i就是最小的正整数
			cout << "ordP(" << P.x << "," << P.y << ")=" << i << endl;
			return;
		}
		i++;
	}
}
void OrdOfEllipticCurve() {//功能六：对在椭圆曲线E_p(a,b)，计算阶#E
	Point p_O(INT_MAX, INT_MAX);
	AllPoints.push_back(p_O);//无穷远点O一定在椭圆曲线上
	for (int i = 0; i < p; i++) {
		int y_2 = mod(pow(i, 3) + a * i + b, p);//由椭圆方程求出y^2
		int y1 = 0, y2 = 0;//记录求出的两个二次同余方程的解
		if (LegendreSymbol(y_2, p) == -1)//若勒让德符号为-1，一定无解，一定不在椭圆曲线上
			continue;
		else {//若勒让德符号为1，则一定有解，求解二次同余方程
			for (int j = 0; j <= p - 1; j++) {//由于当p一般较小时，可以直接遍历求解二次同余方程
				if (mod(pow(j, 2), p) == y_2) {
					if (j == 0) {//若j==0，则实际上只解出来一个点
						Point p(i, 0);
						AllPoints.push_back(p);
						break;
					}
					y1 = j;
					y2 = p - y1;//另一解与y1相加为p
					Point p1(i, y1);
					AllPoints.push_back(p1);
					Point p2(i, y2);
					AllPoints.push_back(p2);
					break;
				}
			}

		}
	}
	cout << "#E of E_" << p << "(" << a << "," << b << ")= " << AllPoints.size() << endl;//此时vector的长度容量即所有有理点的个数，即椭圆曲线的阶
	return;
}
void AllPointsOfEllipticCurve() {//功能七：对在椭圆曲线E_p(a,b)，计算所有点
	//由于此时已经通过OrdOfEllipticCurve()将所有点都放入了AllPoints，此时只需要输出即可
	int size = AllPoints.size();
	cout << "All the points on E_" << p << "(" << a << "," << b << ") are:" << endl;
	cout << "{ O , ";
	for (int i = 1; i < size; i++) {
		if (i == size - 1) {
			Point P = AllPoints[i];
			cout << "(" << P.x << "," << P.y << ") }." << endl;
		}
		else {
			Point P = AllPoints[i];
			cout << "(" << P.x << "," << P.y << ") ,";
		}
	}
	return;
}
Point InversePoint(Point P) {//功能八（拓展功能）：对在椭圆曲线E_p(a,b)上的点P，计算其逆元-P
	Point IP;
	if (IfIsInfinitePoint_O(P)) {
		IP.x = IP.y = INT_MAX;
		return IP;
	}
	IP.x = mod(P.x, p);
	IP.y = mod(-P.y, p);
	return IP;
}
int main() {
	cout << "Z_P——E_p(a, b) " << endl;
	cout << "If you want to input the point of infinity:O，its x and y shouble be INT_MAX——2147483647" << endl;
	cout << "Fowllowing are some fuctions of E_p(a,b): " << endl;
	//功能一：给定参数p，a，b，判断E_p(a,b)是否为椭圆曲线：
	while (1)
	{
		cout << "Please input p,a,b of E_p(a,b):" << endl;
		cout << "p=";
		cin >> p;
		cout << "a=";
		cin >> a;
		cout << "b=";
		cin >> b;
		cout << "Q1:With the given factor p、a、b,is this curve a Elliptic Curve?" << endl;
		cout << "A1:";
		flag = true;
		If_EllipticCurve();
		if (flag)
			break;
		else
			cout << "Please input again!" << endl;
	}

	//功能二：判断给定的点P，Q是否在椭圆曲线E_p(a,b)上
	int xp, yp, xq, yq;
	Point P, Q;
	cout << "Please input x&y for P、Q:" << endl;
	while (1) {
		cout << "Point P:";
		cin >> xp >> yp;
		P.x = xp, P.y = yp;
		if (IfIsOnEllipticCurve(P)) {
			if (IfIsInfinitePoint_O(P)) {//若输入的点就是无穷远点O
				cout << "P which is O is on E_" << p << "(" << a << "," << b << ")" << endl;
				break;
			}
			else {
				cout << "P(" << P.x << "," << P.y << ") is on E_" << p << "(" << a << "," << b << ")" << endl;
				break;
			}
		}
		else {
			cout << "P(" << P.x << "," << P.y << ") is not on E_" << p << "(" << a << "," << b << ")" << endl;
			cout << "Please input again!" << endl;
		}
	}
	while (1) {
		cout << "Point Q:";
		cin >> xq >> yq;
		Q.x = xq, Q.y = yq;
		if (IfIsOnEllipticCurve(Q)) {
			if (IfIsInfinitePoint_O(Q)) {//若输入的点就是无穷远点O
				cout << "Q which is O is on E_" << p << "(" << a << "," << b << ")" << endl;
				break;
			}
			else {
				cout << "Q(" << Q.x << "," << Q.y << ") is on E_" << p << "(" << a << "," << b << ")" << endl;
				break;
			}
		}
		else {
			cout << "Q(" << Q.x << "," << Q.y << ") is not on E_" << p << "(" << a << "," << b << ")" << endl;
			cout << "Please input again!" << endl;
		}
	}

	//功能三：对在椭圆曲线E_p(a,b)上的两点P,Q，计算P+Q
	cout << "Q3:With the given Point P、Q,what is the result of P+Q?" << endl;
	cout << "A3:";
	Point RP = AddTwoPoints(P, Q);
	if (!IfIsInfinitePoint_O(RP))
		cout << "P(" << P.x << "," << P.y << ") + Q(" << Q.x << "," << Q.y << ")=(" << RP.x << "," << RP.y << ")" << endl;
	else
		cout << "P(" << P.x << "," << P.y << ") + Q(" << Q.x << "," << Q.y << ")=O" << endl;

	//功能四：对在椭圆曲线E_p(a,b)上的点P，使用倍加-和算法计算mP
	int m;
	cout << "Please input m in mP:" << endl;
	cin >> m;
	cout << "Q4:With the given factor m,what is the result of mP?" << endl;
	cout << "A4:";
	Point T = DoubleAndAdd_ScalarProductOfPoint(P, m);
	if (!IfIsInfinitePoint_O(T))//若不为无穷远点O，则正常输出结果
		cout << m << "P(" << P.x << "," << P.y << ")=(" << T.x << "," << T.y << ")" << endl;
	else
		cout << m << "P(" << P.x << "," << P.y << ")=O" << endl;

	//功能五：对在椭圆曲线E_p(a,b)上的点P，计算阶ord（P）
	cout << "Q5:With the given Point P,what is order(P)?" << endl;
	cout << "A5:";
	OrdOfPointOnEllipticCurve(P);

	//功能六：对在椭圆曲线E_p(a,b)，计算阶#E
	cout << "Q6:With the given E_p(a,b) , what is #E?" << endl;
	cout << "A6:";
	OrdOfEllipticCurve();

	//功能七：对在椭圆曲线E_p(a,b)，计算所有点
	cout << "Q7:With the given E_p(a,b),what are those points on E?" << endl;
	cout << "A7:";
	AllPointsOfEllipticCurve();

	//功能八（拓展功能）：对在椭圆曲线E_p(a,b)上的点P，计算其逆元-P
	cout << "Q8:With the given Point P,what is its inverse Point -P?" << endl;
	cout << "A8:";
	Point IP = InversePoint(P);
	if (IfIsInfinitePoint_O(IP))
		cout << "-P which is -O=O." << endl;
	else
		cout << "-P(" << P.x << "," << P.y << ")=(" << IP.x << "," << IP.y << ")" << endl;

	//所有功能展示结束，程序退出
	return 0;
}