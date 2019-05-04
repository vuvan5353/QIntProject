﻿#include "OutterFunctions.h"

//Chuyển chuỗi nhị phân sang dạng bù 1
string reverseBinaryString(string binaryString)
{
	string result;
	int len = binaryString.length();
	for (int i = 0; i < len; i++)
	{
		if (binaryString[i] == '0')
		{
			result.push_back('1');
		}
		else
		{
			result.push_back('0');
		}
	}
	return result;
}


//Chia chuỗi số cho 2
int divideBy2(string& a, bool& sign)
{
	int len = a.length();
	int i = 0;
	string newString;
	if (a[0] == '-')
	{
		i = 1;
		sign = 1;
		newString += '-';
	}
	if ((a == "-1"))
	{
		newString = '0';
		a = newString;
		return 1;
	}
	if ((a == "1"))
	{
		newString = '0';
		a = newString;
		return 1;
	}
	if ((a == "0"))
	{
		newString = '0';
		a = newString;
		return 0;
	}

	int tempString = (a[i] - 48);
	if (tempString < 2)
	{
		tempString = tempString * 10 + (a[i + 1] - 48);
		i++;
	}
	int bitCount = 0;
	for (i;; i++)
	{
		bitCount++;
		int soDu = tempString % 2;
		newString = newString + (char)((tempString / 2) + 48);
		tempString = tempString - (tempString / 2) * 2;
		if (i < len - 1)
		{
			tempString = tempString * 10 + (a[i + 1] - 48);
		}
		if (i == len - 1)
		{
			a = newString;
			return soDu;
		}
	}
}

//Chuyển chuỗi thập phân sang chuỗi nhị phân
void decimalToBinary(string a, string& binaryString, bool& sign)
{

	binaryString += (char)(divideBy2(a, sign) + 48);
	if (a == "0")
	{
		if (binaryString.length() > 128)
		{
			binaryString = "0";
			return;
		}
		if (binaryString == "00")
		{
			binaryString = "0";
		}
		string tempString;
		for (int i = 1; i <= 128 - binaryString.length(); i++)
		{
			tempString += "0";
		}
		binaryString += tempString;
		reverse(binaryString.begin(), binaryString.end());
		if (sign == 1)
		{
			binaryString = binaryToSecondComplement(binaryString);

			return;
		}
		return;
	}
	decimalToBinary(a, binaryString, sign);
}

//Chuyển chuỗi nhị phân sang bù 2
string binaryToSecondComplement(string binaryString)
{
	if (binaryString == "0")
	{
		return "0";
	}
	int n = binaryString.length();
	binaryString = reverseBinaryString(binaryString);
	string res = addBin(binaryString, "1");
	return res;
}

//Chuyển chuỗi nhị phân sang thập phân
string binaryToDecimal(string binaryString)
{

	int n = binaryString.length();
	bool sign = 0;
	if (binaryString.at(0) == '1')
	{
		sign = 1;
	}
	string positivePart = "0"; //Chuỗi tổng các số phần dương
	string negativePart;//Chuỗi phần âm
	int k = 0; //vị trí số mũ
	for (int i = n - 1; i >= 0; i--)
	{
		if (i == 0 && sign == 1)
		{
			negativePart = pow("2", k);
			break;
		}
		if (binaryString.at(i) == '1')
		{
			positivePart = addDec(positivePart, pow("2", k));
		}

		k++;
	}

	if (sign == 0)
	{
		return positivePart;
	}
	else
	{
		string res = "-";
		res += diff(negativePart, positivePart);
		return res;
	}
}

//Chuyển từng 4 bit nhị phân sang thập lục phân
string hexToBin(char c)
{
	switch (c)
	{
	case '0':
		return "0000";
		break;
	case '1':
		return "0001";
		break;
	case '2':
		return "0010";
		break;
	case '3':
		return "0011";
		break;
	case '4':
		return "0100";
		break;
	case '5':
		return "0101";
		break;
	case '6':
		return "0110";
		break;
	case '7':
		return "0111";
		break;
	case '8':
		return "1000";
		break;
	case '9':
		return "1001";
		break;
	case 'A':
	case 'a':
		return "1010";
		break;
	case 'B':
	case 'b':
		return "1011";
		break;
	case 'C':
	case 'c':
		return "1100";
		break;
	case 'D':
	case 'd':
		return "1101";
		break;
	case 'E':
	case 'e':
		return "1110";
		break;
	case 'F':
	case 'f':
		return "1111";
		break;
	default:
		break;
	}

}

//Chuyển chuỗi thập lục phân sang hệ 2
string hexToBinary(string hex){
	string result = "";
	for (int i = 0; i < hex.length(); i++)
	{
		result += hexToBin(hex[i]);
	}
	string temp;
	for (int i = 1; i <= 128 - result.length(); i++)
	{
		temp += "0";
	}

	return temp + result;
}

//Làm chiều dài 2 chuỗi số bằng nhau bằng cách thêm số 0 vào chuỗi ngắn hơn
int makeEqualLength(string &str1, string &str2)
{
	int len1 = str1.size();
	int len2 = str2.size();
	if (len1 < len2)
	{
		for (int i = 0; i < len2 - len1; i++){
			str1 = '0' + str1;
		}
		return len2;
	}
	else if (len1 > len2)
	{
		for (int i = 0; i < len1 - len2; i++){
			str2 = '0' + str2;
		}
		return len1; // n?u len1 >= len2 
	}
}

//Phép trừ 2 số thập phân
string Subtraction(string a, string b)
{
	string result = "";
	while (a.length() < b.length())
		a = '0' + a;
	while (b.length() < a.length())
		b = '0' + b;
	bool neg = false;
	if (a<b)
	{
		swap(a, b);
		neg = true;
	}
	int borrow = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		int x = a[i] - b[i] - borrow;
		if (x<0)
		{
			x += 10;
			borrow = 1;
		}
		else borrow = 0;
		result = (char)(x % 10 + 48) + result;
	}
	while (result.length()>1 && result[0] == '0') result.erase(0, 1);
	if (neg) result = "-" + result;
	return result;
}

//Phép cộng 2 số nhị phân
string addBin(string firstNum, string secondNum)
{
	string result = ""; // Initialize result 
	int s = 0;          // Initialize digit sum 

	// Travers both strings starting from last 
	// characters 
	int i = firstNum.size() - 1, j = secondNum.size() - 1;
	while (i >= 0 || j >= 0 || s == 1)
	{
		// Comput sum of last digits and carry 
		s += ((i >= 0) ? firstNum[i] - '0' : 0);
		s += ((j >= 0) ? secondNum[j] - '0' : 0);

		// If current digit sum is 1 or 3, add 1 to result 
		result = char(s % 2 + '0') + result;

		// Compute carry 
		s /= 2;

		// Move to next digits 
		i--; j--;
	}

	return result;

}

//Phép cộng 2 số thập phân
string addDec(string number1, string number2)
{

	if (number1.length() > number2.length())
		number1.swap(number2);

	string result = ""; //khởi tạo chuỗi để lưu kết quả

	int n1 = number1.length(), n2 = number2.length();

	// đảo ngược 2 chuỗi
	reverse(number1.begin(), number1.end());
	reverse(number2.begin(), number2.end());

	int carry = 0;
	for (int i = 0; i<n1; i++)
	{

		int sum = ((number1[i] - '0') + (number2[i] - '0') + carry);
		result.push_back(sum % 10 + '0');

		carry = sum / 10;
	}

	// Thêm các chữ số còn lại của số lớn hơn
	for (int i = n1; i<n2; i++)
	{
		int sum = ((number2[i] - '0') + carry);
		result.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	if (carry)
		result.push_back(carry + '0');

	reverse(result.begin(), result.end()); //chuỗi kết quả ngược

	return result;
}

//Chuyển chuỗi nhị phân sang thập lục phân
string binToHex(string bin){
	string result;
	//string tmp, chr = "0000";
	string tmp;
	reverse(bin.begin(), bin.end());
	int len = bin.length() / 4;
	//chr = chr.substr(0, len);
	//bin = chr + bin;
	for (int i = 0; i<bin.length(); i += 4)
	{
		tmp = bin.substr(i, 4);
		if (!tmp.compare("0000"))
		{
			result = result + "0";
		}
		else if (!tmp.compare("0001"))
		{
			result = result + "8";
		}
		else if (!tmp.compare("0010"))
		{
			result = result + "4";
		}
		else if (!tmp.compare("0011"))
		{
			result = result + "C";
		}
		else if (!tmp.compare("0100"))
		{
			result = result + "2";
		}
		else if (!tmp.compare("0101"))
		{
			result = result + "A";
		}
		else if (!tmp.compare("0110"))
		{
			result = result + "6";
		}
		else if (!tmp.compare("0111"))
		{
			result = result + "E";
		}
		else if (!tmp.compare("1000"))
		{
			result = result + "1";
		}
		else if (!tmp.compare("1001"))
		{
			result = result + "9";
		}
		else if (!tmp.compare("1010"))
		{
			result = result + "5";
		}
		else if (!tmp.compare("1011"))
		{
			result = result + "D";
		}
		else if (!tmp.compare("1100"))
		{
			result = result + "3";
		}
		else if (!tmp.compare("1101"))
		{
			result = result + "B";
		}
		else if (!tmp.compare("1110"))
		{
			result = result + "7";
		}
		else if (!tmp.compare("1111"))
		{
			result = result + "F";
		}
		else
		{
			continue;
		}
	}
	reverse(result.begin(), result.end());
	return result;
}

//Chuẩn hóa chuỗi nhị phân/ thập lục phân bằng cách bỏ số 0 thừa ở đầu
string binaryStringStandardize(string number)
{
	if (binaryToDecimal(number) == "0")
	{
		return "0";
	}
	int pos = 0;
	while (number.at(pos) == '0')
	{
		pos++;
	}
	return number.substr(pos);
}

//Nhân 2 số thập phân
string multiply(string num1, string num2)
{
	int n1 = num1.size();
	int n2 = num2.size();
	if (n1 == 0 || n2 == 0)
	{
		return "0";
	}

	//Lưu kết quả vào vector theo thứ tự ngược
	vector<int> result(n1 + n2, 0);

	// Hai biến phụ tìm vị trí trong vector result
	int nPos1 = 0;
	int nPos2 = 0;

	// Duyệt số đầu tiên từ phải sang trái 
	for (int i = n1 - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';

		//Dịch chuyển vị trí sang trái sau mỗi lần nhân với một kí số của số thứ 2
		nPos2 = 0;

		// Duyệt từ phải sang trái ở số thứ 2           
		for (int j = n2 - 1; j >= 0; j--)
		{
			// Bốc ra kí số hiện tại của số thứ 2
			int n2 = num2[j] - '0';

			//Nhân n2 với số n1 và cộng vào kết quả đã lưu trước dó ở vị trí hiện tại
			int sum = n1*n2 + result[nPos1 + nPos2] + carry;

			// Phần nhớ
			carry = sum / 10;

			// Lưu vào kết quả
			result[nPos1 + nPos2] = sum % 10;

			nPos2++;
		}

		//Cộng phần nhớ
		if (carry > 0)
			result[nPos1 + nPos2] += carry;

		//Dịch chuyển sang kí số tiếp theo
		nPos1++;
	}

	// Bỏ qua số 0 bên phải
	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0)
		i--;

	// Kiểm tra xem trong 2 số có số nào là 0 không
	if (i == -1)
		return "0";


	string s = "";

	while (i >= 0)
		s += to_string(result[i--]);

	return s;
}

//Phép mũ
string pow(string num, int exp)
{
	string res;
	string temp = "1";
	res = temp;
	for (int i = 1; i <= exp; i++)
	{
		temp = multiply(num, temp);
		res = temp;
	}
	return res;
}

//Kiểm tra num1 có nhỏ hơn num2 không
bool isSmaller(string num1, string num2)
{
	{
		int len1 = num1.length(), len2 = num2.length();

		if (len1 < len2)
		{
			return true;
		}
		if (len1 > len2)
		{
			return false;
		}

		for (int i = 0; i<len1; i++)
		{
			if (num1[i] < num2[i])
			{
				return true;
			}
			else if (num1[i] > num2[i])
			{
				return false;
			}
		}
		return false;
	}
}

//Tính độ chênh lệch giữa 2 số dương
string diff(string num1, string num2)
{
	//Lưu ý: 2 số truyền vào đã được lược bỏ dấu - nếu có
	// Đảm bảo số đầu tiên là số lớn hơn (về mặt giá trị tuyệt đối)
	if (isSmaller(num1, num2))
	{
		string temp = num1;
		num1 = num2;
		num2 = temp;
	}

	string res;
	int len1 = num1.length(), len2 = num2.length();
	int diff = len1 - len2;

	// Initially take carry zero 
	int carry = 0;

	// Traverse from end of both strings 
	for (int i = len2 - 1; i >= 0; i--)
	{
		// Do school mathematics, compute difference of 
		// current digits and carry 
		int sub = ((num1[i + diff] - '0') - (num2[i] - '0') - carry);
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		res.push_back(sub + '0');
	}

	// subtract remaining digits of str1[] 
	for (int i = len1 - len2 - 1; i >= 0; i--)
	{
		if (num1[i] == '0' && carry)
		{
			res.push_back('9');
			continue;
		}
		int sub = ((num1[i] - '0') - carry);
		if (i > 0 || sub > 0) // remove preceding 0's 
			res.push_back(sub + '0');
		carry = 0;

	}

	// reverse resultant string 
	reverse(res.begin(), res.end());
	int pos = 0;
	while (res.at(pos) == '0')
	{
		pos++;
	}
	res = res.substr(pos);
	return res;
}

//Dịch phải số học chuỗi 1 lần
string shiftRight(string number)
{
	string res;
	int n = number.length();
	char bitSign = number.at(0);
	res += bitSign;
	res += number.substr(0, n - 1);
	return res;
}

//Dịch trái chuỗi 1 lần
string shiftLeft(string number)
{
	string res;
	int n = number.length();
	res = number.substr(1, n - 1);
	res += "0";
	return res;
}

//Kiểm tra dấu của  số trong phép nhân và trừ
int sign(string n1, string n2)
{
	int x = n1.find_first_of('-'), y = n2.find_first_of('-');
	if ((x == -1 && y == -1)) return 1; //2 số dương
	else if ((x == 0 && y == -1)) return 2; // số n1 âm, số n2 dương
	else if ((x == -1 && y == 0)) return 3; //Số n1 dương, n2 âm
	else if (x == 0 && y == 0) return 4; //2 số âm

}

//Phép nhân 2 số nhị phân
string Multiplication(string n1, string n2){
	string result = "";
	int KT = sign(n1, n2);
	if (KT == 4){  // S? d?u duong, s? th? 2 âm
		result = multiply(n1.erase(0, 1), n2.erase(0, 1));
	}
	else if (KT == 2) //S? 1 âm, s? 2 duong
	{
		result = '-' + multiply(n1.erase(0, 1), n2);
	}
	else if (KT == 3) //S? 1 âm, s? 2 duong
	{
		result = '-' + multiply(n1, n2.erase(0, 1));
	}
	else if (KT == 1){
		result = multiply(n1, n2);
	}
	return result;
}

//Phép dịch trái dạng [num1, num2], dùng trong thuật toán chia trong slide
void groupShiftLeft(QInt& num1, QInt& num2)
{
	string n1 = num1.getBitString();
	string n2 = num2.getBitString();
	char c = n2.at(0);
	n2 = shiftLeft(n2);

	n1.erase(n1.begin());
	n1 += c;
	num1 = QInt(2, n1);
	num2 = QInt(2, n2);

}

//Set bit cuối của chuỗi nhị phân bằng giá trị bit
void setLastBit(QInt& num, char bit)
{
	string temp = num.getBitString();
	temp.at(temp.length() - 1) = bit;
	num = QInt(2, temp);
}
