//�������ҵ��ʵ�ֻ�����ģPʣ��������Բ���ߵļ���
#include<iostream>
#include<stack>
#include<cmath>
#include<vector>
using namespace std;
int p, a, b;//ȫ�ֱ������ߵĲ���p��a��b
bool flag;//���幦��һ���Ƿ�Ϊ��Բ���ߵģ���������������ı�־λ
class Point {//��������ĵ���
public:
	int x, y;
	Point(int x1, int y1) :x(x1), y(y1) {};
	Point() {};
};
vector<Point> AllPoints;//�洢��Բ�����ϵ����е�
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
stack<int> DecimalToBinary(unsigned  long long n) {//����ʮ����ת�����ƣ���һ��ջs�����棬��������ʹ��ƽ�����㷨
	stack<int> s;
	while (n != 0) {
		int r = n % 2;
		s.push(r);
		n = n / 2;
	}
	return s;
}
unsigned long long  SquareAndMultiplyAlgorithm(unsigned long long a, unsigned long long n, unsigned long long m) {//ƽ�����㷨
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
int ExtendedEuclideanAlgorithm(int a, int b, int& x, int& y) {//��չ��ŷ������㷨����Ԫ����������Ԫ
	if (!b) {
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
int mod(int a, int p) {//����ȡģ����mod
	if (a % p >= 0)
		return a % p;
	else
		return a % p + p;
}
int LegendreSymbol(int a, int p) {//�������õ·���
	return mod(pow(a, (p - 1) / 2), p);//����pһ���С������ֱ�Ӳ���ŷ���б�ʽ�����
}
bool IfIsInfinitePoint_O(Point P) {//�ж��Ƿ�Ϊ����Զ�㣬��������Զ��O��x��y��Ϊ����ֵINT_MAX
	return P.x == INT_MAX && P.y == INT_MAX ? true : false;
}
void If_EllipticCurve() {//����һ����������p��a��b���ж�E_p(a,b)�Ƿ�Ϊ��Բ����
	if (p <= 3 || !if_vegetable(p)) {//��p��Ϊ����3������
		cout << "E_" << p << "(" << a << "," << b << ") is not Elliptic Curve." << endl;
		flag = false;
		return;
	}
	int temp = 4 * pow(a, 3) + 27 * pow(b, 2);
	temp = mod(temp, p);
	if (!temp) {//�жϸ������Ƿ�Ϊ�⻬����
		cout << "E_" << p << "(" << a << "," << b << ") is not Elliptic Curve." << endl;
		flag = false;//��������Բ���ߣ���Ҫ������main����������s
		return;
	}
	cout << "E_" << p << "(" << a << "," << b << ") is Elliptic Curve." << endl;
	return;
}
bool IfIsOnEllipticCurve(Point P) {//���ܶ����жϸ����ĵ�P��Q�Ƿ�����Բ����E_p(a,b)��
	if (IfIsInfinitePoint_O(P)) //��PΪ����Զ�㣬��һ������Բ������
		return true;
	int y_2 = mod(pow(P.x, 3) + a * P.x + b, p);//����Բ�������y^2
	int y1 = 0, y2 = 0;//��¼�������������ͬ�෽�̵Ľ�
	if (LegendreSymbol(y_2, p) == -1)//�����õ·���Ϊ-1��һ���޽⣬һ��������Բ������
		return false;
	else {
		for (int i = 1; i <= p - 1; i++) {//���ڵ�pһ���Сʱ������ֱ�ӱ���������ͬ�෽��
			if (mod(pow(i, 2), p) == y_2) {
				y1 = i;
				y2 = p - y1;//��һ����y1���Ϊp
				break;
			}
		}
		if (mod(P.y, p) != y1 && mod(P.y, p) != y2)//�������y����Ϊ����ͬ�෽�̽⣬��һ��������Բ������
			return false;
		else
			return true;
	}
}
Point AddTwoPoints(Point P, Point Q) {//��������������Բ����E_p(a,b)�ϵ�����P,Q������P+Q
	Point RP;
	if (IfIsInfinitePoint_O(P)) {//������PΪ����Զ��O
		if (IfIsInfinitePoint_O(Q)) {//��QҲΪ����Զ��O
			RP.x = RP.y = INT_MAX;
			return RP;
		}
		else {//��Q��Ϊ����Զ��O������ΪQ
			RP.x = Q.x, RP.y = Q.y;
			return RP;
		}
	}
	if (IfIsInfinitePoint_O(Q)) {//������QΪ����Զ��O
		if (IfIsInfinitePoint_O(Q)) {//��PҲΪ����Զ��O,����ΪO
			RP.x = RP.y = INT_MAX;
			return RP;
		}
		else {//��P��Ϊ����Զ��P������ΪP
			RP.x = P.x, RP.y = P.y;
			return RP;
		}
	}
	if (P.x == Q.x && P.y != Q.y) {//��������x������ͬ����y���겻ͬ����Ϊ��ͬ�㣬������ӽ��Ϊ����Բ�����ཻ�ĵ������㡪������Զ��O
		//��ʱ�Է��صĽ����x��y��Ϊ���ֵ������ֵINT_MAX
		RP.x = RP.y = INT_MAX;
		return RP;
	}
	if (P.x == Q.x && P.y == Q.y) {//��������ͬ��Ϊͬһ�㣬��ӵĽ��Ϊ����
		int y0 = mod(2 * P.y, p);
		int x0 = mod(3 * P.x * P.x + a, p);
		int a, b;
		ExtendedEuclideanAlgorithm(y0, p, a, b);//������չŷ������㷨����Ԫ
		int y0ni = a;
		int k = mod(x0 * y0ni, p);
		int x3 = mod(k * k - 2 * P.x, p);
		int y3 = mod(k * (P.x - x3) - P.y, p);
		RP.x = x3, RP.y = y3;
		return RP;
	}
	else {//�����㲻��ͬ
		int y0 = mod(Q.y - P.y, p);
		int x0 = mod(Q.x - P.x, p);
		int a, b;
		ExtendedEuclideanAlgorithm(x0, p, a, b);//������չŷ������㷨����Ԫ
		int x0ni = a;
		int k = mod(y0 * x0ni, p);
		int x3 = mod(k * k - P.x - Q.x, p);
		int y3 = mod(k * (P.x - x3) - P.y, p);
		RP.x = x3, RP.y = y3;
		return RP;
	}
}
Point DoubleAndAdd_ScalarProductOfPoint(Point P, int m) {//�����ģ�������Բ����E_p(a,b)�ϵĵ�P��ʹ�ñ���-���㷨����mP
	stack<int> s = DecimalToBinary(m);
	Point T = P;//ת��Ϊ�����ƵĽ�����λһ��Ϊ1������T��ʼ��һ��Ϊ��dt=1��*P=P
	s.pop();
	for (int i = s.size(); i > 0; i--) {
		T = AddTwoPoints(T, T);//Double
		if (s.top())
			T = AddTwoPoints(T, P);//Double+Add
		s.pop();
	}
	return T;
}
Point ScalarProductOfPoint(Point P, int m) {//��ͨ�㷨ʵ�ֹ�����
	Point temp_P = P;
	for (int i = 2; i <= m; i++)
		temp_P = AddTwoPoints(temp_P, P);
	return temp_P;
}
void OrdOfPointOnEllipticCurve(Point P) {//�����壺������Բ����E_p(a,b)�ϵĵ�P�������ord��P��
	if (IfIsInfinitePoint_O(P)) {//��PΪO�������Ϊ1
		cout << "P which is O:ord(P)=1" << endl;
		return;
	}
	int i = 2;
	while (1) {
		if (IfIsInfinitePoint_O(DoubleAndAdd_ScalarProductOfPoint(P, i))) {//���iP=O,��i������С��������
			cout << "ordP(" << P.x << "," << P.y << ")=" << i << endl;
			return;
		}
		i++;
	}
}
void OrdOfEllipticCurve() {//��������������Բ����E_p(a,b)�������#E
	Point p_O(INT_MAX, INT_MAX);
	AllPoints.push_back(p_O);//����Զ��Oһ������Բ������
	for (int i = 0; i < p; i++) {
		int y_2 = mod(pow(i, 3) + a * i + b, p);//����Բ�������y^2
		int y1 = 0, y2 = 0;//��¼�������������ͬ�෽�̵Ľ�
		if (LegendreSymbol(y_2, p) == -1)//�����õ·���Ϊ-1��һ���޽⣬һ��������Բ������
			continue;
		else {//�����õ·���Ϊ1����һ���н⣬������ͬ�෽��
			for (int j = 0; j <= p - 1; j++) {//���ڵ�pһ���Сʱ������ֱ�ӱ���������ͬ�෽��
				if (mod(pow(j, 2), p) == y_2) {
					if (j == 0) {//��j==0����ʵ����ֻ�����һ����
						Point p(i, 0);
						AllPoints.push_back(p);
						break;
					}
					y1 = j;
					y2 = p - y1;//��һ����y1���Ϊp
					Point p1(i, y1);
					AllPoints.push_back(p1);
					Point p2(i, y2);
					AllPoints.push_back(p2);
					break;
				}
			}

		}
	}
	cout << "#E of E_" << p << "(" << a << "," << b << ")= " << AllPoints.size() << endl;//��ʱvector�ĳ������������������ĸ���������Բ���ߵĽ�
	return;
}
void AllPointsOfEllipticCurve() {//�����ߣ�������Բ����E_p(a,b)���������е�
	//���ڴ�ʱ�Ѿ�ͨ��OrdOfEllipticCurve()�����е㶼������AllPoints����ʱֻ��Ҫ�������
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
Point InversePoint(Point P) {//���ܰˣ���չ���ܣ���������Բ����E_p(a,b)�ϵĵ�P����������Ԫ-P
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
	cout << "Z_P����E_p(a, b) " << endl;
	cout << "If you want to input the point of infinity:O��its x and y shouble be INT_MAX����2147483647" << endl;
	cout << "Fowllowing are some fuctions of E_p(a,b): " << endl;
	//����һ����������p��a��b���ж�E_p(a,b)�Ƿ�Ϊ��Բ���ߣ�
	while (1)
	{
		cout << "Please input p,a,b of E_p(a,b):" << endl;
		cout << "p=";
		cin >> p;
		cout << "a=";
		cin >> a;
		cout << "b=";
		cin >> b;
		cout << "Q1:With the given factor p��a��b,is this curve a Elliptic Curve?" << endl;
		cout << "A1:";
		flag = true;
		If_EllipticCurve();
		if (flag)
			break;
		else
			cout << "Please input again!" << endl;
	}

	//���ܶ����жϸ����ĵ�P��Q�Ƿ�����Բ����E_p(a,b)��
	int xp, yp, xq, yq;
	Point P, Q;
	cout << "Please input x&y for P��Q:" << endl;
	while (1) {
		cout << "Point P:";
		cin >> xp >> yp;
		P.x = xp, P.y = yp;
		if (IfIsOnEllipticCurve(P)) {
			if (IfIsInfinitePoint_O(P)) {//������ĵ��������Զ��O
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
			if (IfIsInfinitePoint_O(Q)) {//������ĵ��������Զ��O
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

	//��������������Բ����E_p(a,b)�ϵ�����P,Q������P+Q
	cout << "Q3:With the given Point P��Q,what is the result of P+Q?" << endl;
	cout << "A3:";
	Point RP = AddTwoPoints(P, Q);
	if (!IfIsInfinitePoint_O(RP))
		cout << "P(" << P.x << "," << P.y << ") + Q(" << Q.x << "," << Q.y << ")=(" << RP.x << "," << RP.y << ")" << endl;
	else
		cout << "P(" << P.x << "," << P.y << ") + Q(" << Q.x << "," << Q.y << ")=O" << endl;

	//�����ģ�������Բ����E_p(a,b)�ϵĵ�P��ʹ�ñ���-���㷨����mP
	int m;
	cout << "Please input m in mP:" << endl;
	cin >> m;
	cout << "Q4:With the given factor m,what is the result of mP?" << endl;
	cout << "A4:";
	Point T = DoubleAndAdd_ScalarProductOfPoint(P, m);
	if (!IfIsInfinitePoint_O(T))//����Ϊ����Զ��O��������������
		cout << m << "P(" << P.x << "," << P.y << ")=(" << T.x << "," << T.y << ")" << endl;
	else
		cout << m << "P(" << P.x << "," << P.y << ")=O" << endl;

	//�����壺������Բ����E_p(a,b)�ϵĵ�P�������ord��P��
	cout << "Q5:With the given Point P,what is order(P)?" << endl;
	cout << "A5:";
	OrdOfPointOnEllipticCurve(P);

	//��������������Բ����E_p(a,b)�������#E
	cout << "Q6:With the given E_p(a,b) , what is #E?" << endl;
	cout << "A6:";
	OrdOfEllipticCurve();

	//�����ߣ�������Բ����E_p(a,b)���������е�
	cout << "Q7:With the given E_p(a,b),what are those points on E?" << endl;
	cout << "A7:";
	AllPointsOfEllipticCurve();

	//���ܰˣ���չ���ܣ���������Բ����E_p(a,b)�ϵĵ�P����������Ԫ-P
	cout << "Q8:With the given Point P,what is its inverse Point -P?" << endl;
	cout << "A8:";
	Point IP = InversePoint(P);
	if (IfIsInfinitePoint_O(IP))
		cout << "-P which is -O=O." << endl;
	else
		cout << "-P(" << P.x << "," << P.y << ")=(" << IP.x << "," << IP.y << ")" << endl;

	//���й���չʾ�����������˳�
	return 0;
}