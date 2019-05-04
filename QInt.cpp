#include "QInt.h"
#include "OutterFunctions.h"


//PT khởi tạo mặc định
QInt::QInt()
{
	this->len = 0;
	this->sign = 0;
}

//PT khởi tạo sao chép
QInt::QInt(QInt& number)
{
	this->len = number.len;
	this->sign = number.sign;
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = number.data[i];
	}
}

//PT khởi tạo kiểu QInt với các hệ cơ số
QInt::QInt(int kind, string str)
{
	string binaryString;
	if (kind == 2)  //Nếu chuỗi là chuỗi nhị phân
	{
		binaryString = str;
		int n = str.length();
		this->len = n;
		if (str[0] == '1')
		{
			this->sign = 1;
		}
		else this->sign = 0;
	}
	if (kind == 10)  //Nếu chuỗi là chuỗi thập phân
	{

		decimalToBinary(str, binaryString, this->sign);  //Chuyển về chuỗi nhị phân thứ tự đúng (dạng bù 2)
		if (str == "0")
		{
			binaryString.erase();
			for (int i = 0; i < 127; i++)
			{
				binaryString += "0";
			}
		}
		if (binaryString.at(0) == '1')
		{
			this->sign = 1;
		}
		else this->sign = 0;
		this->len = binaryString.length();
	}
	if (kind == 16) //Nếu chuỗi là chuỗi hệ 16
	{
		binaryString = hexToBinary(str);

		if (binaryString.at(0) == '1')
		{
			this->sign = 1;
		}
		else
		{
			this->sign = 0;
		}
		this->len = binaryString.length();
	}

	for (int i = 0; i < 4; i++)
	{
		this->data[i] = (this->data[i] & 0);
	}
	int k = binaryString.length() - 1;
	int shiftCount = 0;
	int temp = 3;

	for (int i = 0; i < this->len; i++)
	{
		int bitPosition;
		if (i + 1 <= 32)
		{
			bitPosition = 3;
		}
		else if (i + 1>32 && i + 1 <= 64)
		{
			bitPosition = 2;
		}
		else if (i + 1>64 && i + 1 <= 96)
		{
			bitPosition = 1;
		}
		else if (i + 1>96 && i + 1 <= 128)
		{
			bitPosition = 0;
		}

		this->data[bitPosition] = this->data[bitPosition] | ((int)(binaryString[k] - 48) << shiftCount);
		shiftCount++;
		k--;
	}

}

//PT hủy
QInt::~QInt()
{
	this->sign = this->len = 0;
}

//Toán tử gán
QInt QInt:: operator= (QInt number)
{
	this->len = number.len;
	this->sign = number.sign;
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = number.data[i];
	}
	return *this;
}

//Toán tử +
QInt operator+(QInt  firstNum, QInt  secondNum)
{
	string result = "";
	string n1 = firstNum.toDecimal(), n2 = secondNum.toDecimal();

	int x = n1.find_first_of('-'), y = n2.find_first_of('-');
	char sign1 = n1.at(0), sign2 = n2.at(0);
	if (sign1 != '-' && sign2 != '-'){  //Hai số dương thì cộng bình thường
		result = addDec(n1, n2);
	}
	if (n1.find_first_not_of('-') == 0 && y == 0){  // Số đầu dương, số thứ 2 âm
		string n2_ = n2.erase(0, 1);
		result = Subtraction(n1, n2_);
	}
	else if (x == 0 && y == -1) //Số 1 âm, số 2 dương
	{
		result = Subtraction(n2, n1.erase(0, 1));
	}
	else if (x == 0 && y == 0)
	{
		string n1New = n1.erase(0, 1);
		string n2New = n2.erase(0, 1);
		result = '-' + addDec(n1New, n2New);
	}
	return QInt(10, result);
}


//Phương thức lấy chuỗi 128 bit của đối tượng
string QInt::getBitString() const
{
	string res;
	bitset<32> bit;
	int k = 3;
	for (int i = 1; i <= 4; i++)
	{
		string temp;
		bit = bitset<32>(data[k]);
		temp = bit.to_string();
		k--;
		res = temp + res;
	}
	return res;
}


//Xuất ra dạng nhị phân của đối tượng, đã xóa bỏ những số 0 ở đầu không cần thiết
string QInt::toBinary()
{
	if (this->toDecimal() == "0")
	{
		return "0";
	}
	string temp = this->getBitString();
	int pos = 0;
	while (temp.at(pos) == '0')
	{
		pos++;
	}
	return temp.substr(pos);
}


//Xuất ra dạng thập phân của đối tượng
string QInt::toDecimal()
{
	string temp = this->getBitString();
	string res = binaryToDecimal(temp);
	return res;
}


//Xuất ra dạng thập lục phân của đối tượng, đã xóa những số 0 ở đầu không cần thiết
string QInt::toHex()
{
	if (this->toDecimal() == "0")
	{
		return "0";
	}
	string temp = this->getBitString();

	string res = binToHex(temp);
	int pos = 0;
	while (res.at(pos) == '0')
	{
		pos++;
	}
	return res.substr(pos);
}

//Toán tử dịch phải số học
QInt QInt:: operator >> (int number)
{
	string res = this->getBitString();
	for (int i = 1; i <= number; i++)
	{
		res = shiftRight(res);
	}
	QInt temp(2, res);
	return temp;
}

//Toán tử dịch trái
QInt QInt:: operator << (int number)
{
	string res = this->getBitString();
	for (int i = 1; i <= number; i++)
	{
		res = shiftLeft(res);
	}
	QInt temp(2, res);
	return temp;
}

//Toán tử NOT
QInt QInt::operator~()
{
	string res = this->getBitString();
	res = reverseBinaryString(res);
	return QInt(2, res);
}

//Toán tử trừ
QInt operator- (QInt num1, QInt num2)
{
	string res = num2.getBitString();
	res = binaryToSecondComplement(res);
	QInt temp(2, res);
	return (num1 + temp);
}

//Phép so sánh với số QInt khác
int QInt::compare(QInt number)
{
	string temp1 = this->toDecimal();
	string temp2 = number.toDecimal();
	int signCheck = 0;

	if (this->sign == 0 && number.sign == 1)
	{
		return 1;
	}
	if (this->sign == 1 && number.sign == 0)
	{
		return -1;
	}
	if (this->sign == 1 && number.sign == 1)
	{
		temp1.erase(temp1.begin());
		temp2.erase(temp2.begin());
		signCheck = 1;
	}
	int n1 = temp1.length();
	int n2 = temp2.length();
	if (n1 < n2)
	{
		if (signCheck == 1)
		{
			return 1;
		}
		else
			return -1;
	}
	else if (n1>n2)
	{
		if (signCheck == 1)
		{
			return -1;
		}
		else return 1;
	}
	else if (n1 == n2)
	{

		if (signCheck == 1)
		{
			if (temp1 < temp2)
			{
				return 1;
			}
			else if (temp1>temp2)
			{
				return -1;
			}
			else if (temp1 == temp2)
			{
				return 0;
			}
		}
		else
		{
			return temp1.compare(temp2);
		}
	}
}

//Phép quay phải
QInt QInt::ror()
{
	string res = this->getBitString();
	int len = res.length();
	char c = res.at(len - 1);
	res.pop_back();
	res = c + res;
	return QInt(2, res);
}

//Phép quay trái
QInt QInt::rol()
{
	string res = this->getBitString();
	int len = res.length();
	char c = res.at(0);
	res.erase(res.begin());
	res = res + c;
	return QInt(2, res);
}

//Toán tử OR
QInt QInt::operator |(QInt number)
{
	string binaryString1 = this->getBitString();
	string binaryString2 = number.getBitString();

	QInt temp;
	int len = makeEqualLength(binaryString1, binaryString2);


	for (int i = 3; i >= 0; i--)
	{
		temp.data[i] = this->data[i] | number.data[i];
	}
	temp.len = len;
	if (temp.getBitString().at(0) == '1')
	{
		temp.sign = 1;
	}
	else temp.sign = 0;
	return temp;
}

//Toán tử AND
QInt QInt::operator & (QInt number)
{
	string binaryString1 = this->getBitString();
	string binaryString2 = number.getBitString();

	QInt temp;
	int len = makeEqualLength(binaryString1, binaryString2);


	for (int i = 3; i >= 0; i--)
	{
		temp.data[i] = this->data[i] & number.data[i];
	}
	temp.len = len;
	if (temp.getBitString().at(0) == '1')
	{
		temp.sign = 1;
	}
	else temp.sign = 0;
	return temp;
}

//Toán tử XOR
QInt QInt::operator ^ (QInt number)
{
	string binaryString1 = this->getBitString();
	string binaryString2 = number.getBitString();

	QInt temp;
	int len = makeEqualLength(binaryString1, binaryString2);


	for (int i = 3; i >= 0; i--)
	{
		temp.data[i] = this->data[i] ^ number.data[i];
	}
	temp.len = len;
	if (temp.getBitString().at(0) == '1')
	{
		temp.sign = 1;
	}
	else temp.sign = 0;
	return temp;
}


//Toán tử nhân
QInt operator*(QInt num1, QInt num2)
{
	string n1 = num1.toDecimal();
	string n2 = num2.toDecimal();
	string temp = Multiplication(n1, n2);
	return QInt(10, temp);
}


//Toán tử chia
QInt operator/(QInt Q, QInt M)
{
	string QDec = Q.toDecimal();
	string MDec = M.toDecimal();

	if (Q.toDecimal() == "0") //Số bị chia là 0
	{

		return QInt(10, "0");
	}
	if (M.toDecimal() == "1") //Chia cho số 1
	{
		return Q;
	}
	if (M.toDecimal() == "0") //Chia cho 0
	{
		throw exception("Divide by zero");
	}


	int check = sign(QDec, MDec);
	switch (check)
	{
	case 1: //2 so duong thi tiep tuc chia
	{
				break;
	}
	case 2: //so 1 am va so 2 duong
	{
				QDec.erase(QDec.begin());
				Q = QInt(10, QDec);
				break;
	}
	case 3: //So 1 duong va so 2 am thi tiep tuc
	{
				MDec.erase(MDec.begin());
				M = QInt(10, MDec);
				break;
	}
	case 4: //2 so am thi bo dau
	{
				QDec.erase(QDec.begin());
				Q = QInt(10, QDec);
				MDec.erase(MDec.begin());
				M = QInt(10, MDec);
				break;
	}
	}
	string tempNum; //Dung de khoi tao A
	if (Q.sign == 0)
	{
		for (int i = 1; i <= N; i++)
		{
			tempNum += "0";
		}
	}
	else
	{
		for (int i = 1; i <= N; i++)
		{
			tempNum += "1";
		}
	}
	QInt A(2, tempNum);
	int k = N;

	while (k>0)
	{
		groupShiftLeft(A, Q);
		QInt temp = A; //để khôi phục cho lẹ!
		A = A - M;
		if (A.sign == 1)
		{
			A = temp;
			setLastBit(Q, '0');
		}
		else
		{
			setLastBit(Q, '1');
		}

		k--;
	}
	if (check == 2 || check == 3)
	{
		string temp = Q.toDecimal();
		temp = '-' + temp;
		return QInt(10, temp);
	}
	else
	{
		return Q;
	}
}