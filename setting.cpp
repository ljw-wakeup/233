#include"stdafx.h"
#include"setting.h"
#include<math.h>
#include<string>


using namespace std;

Setting::Setting() {

}

Setting::Setting(int ExpNumber, int operator_number, int Accuracy, bool fraction, bool decimal, int min, int max, bool Add, bool Sub, bool Mul, bool Div, bool Pow) {
	expnumber = ExpNumber;
	is_decimal = decimal;
	accuracy = Accuracy;
	operator_account = operator_number;
	is_proper_fraction = fraction;
	range[0] = min;
	range[1] = max;
	operate.add = Add;
	operate.sub = Sub;
	operate.mul = Mul;
	operate.div = Div;
	operate.pow = Pow;
	operation = Add + 2 * Sub + 4 * Mul + 8 * Div + 16 * Pow;
}

int Setting::funcOperate() {
	return operate.add * 1 + operate.sub * 2 + operate.mul * 4 + operate.div * 8 + operate.pow * 16;
}

int Setting::numbertype() {
	if (is_proper_fraction == 1) return 1;
	if (is_decimal == 1) return 2;
	return 0;
}
long ee = 0;
string Setting::load(double number)
{
	string c;
	number *= accuracy;
	bool x = !(accuracy == 1);
	number = (number - (long long)number > 0.5) ? ceil(number) : floor(number);
	number /= accuracy;
	c = to_string(number);
	int a = (int)log10(accuracy);
	if ((long long)number) {
		try {
			ee++;
			long  b = (long)log10((long long)number);
			b += 1 + x + a;
			c.erase(b, c.size());
		}
		catch (exception &e) {
			return"wrong";
		}
		return c;
	}
	else c.erase(1 + x + a, c.size());
	return c;
}

int Setting::getRange_min() {
	return range[0];
}

int Setting::getRange_max() {
	return range[1];
}

int Setting::getAccuracy() {
	return accuracy;
}

void Setting::init(int ExpNumber, int operator_number, int Accuracy, bool fraction, bool decimal, int min, int max, int operator_mode) {
	expnumber = ExpNumber;
	is_decimal = decimal;
	accuracy = Accuracy;
	operator_account = operator_number;
	is_proper_fraction = fraction;
	range[0] = min;
	range[1] = max;
	switch (operator_mode) {
	case 0:
		operate.add = true;
		operate.sub = false;
		operate.mul = false;
		operate.div = false;
		operate.pow = false;
		break;
	case 1:
		operate.add = true;
		operate.sub = true;
		operate.mul = false;
		operate.div = false;
		operate.pow = false;
		break;
	case 2:
		operate.add = true;
		operate.sub = true;
		operate.mul = true;
		operate.div = false;
		operate.pow = false;
		break;
	case 3:
		operate.add = true;
		operate.sub = true;
		operate.mul = true;
		operate.div = true;
		operate.pow = false;
		break;
	case 4:
		operate.add = true;
		operate.sub = true;
		operate.mul = true;
		operate.div = true;
		operate.pow = true;
		break;
	defult:
		break;
	}
	operation = operate.add + 2 * operate.sub + 4 * operate.mul + 8 * operate.div + 16 * operate.pow;
}
int Setting::getOperator_account()
{
	return operator_account;
}

bool Setting::getIs_proper_fraction()
{
	return is_proper_fraction;
}

bool Setting::getIs_decimal()
{
	return is_decimal;
}

int Setting::getExpnumber() {
	return expnumber;
}
void Setting::setOperate_pow(bool value) {
	operate.pow = value;
}

void Setting::setRange(int min, int max) {
	range[0] = min;
	range[1] = max;
}