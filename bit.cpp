		
		
		
		
		// Проверка равенства двух чисел
		
bool isEqual(unsigned long x, unsigned long y) {
	if (x ^ y) {
		return false;
	}
	
	return true;
}


		// Проверка двух чисел на неравенство
		
bool isNotEqual(unsigned long x, unsigned long y) {
	if (x ^ y) {
		return true;
	}
	
	return false;
}


		// Проверка того, больше ли первое число второго
		
bool isGreater(unsigned long x, unsigned long y) {
	unsigned long mask = 1ul << 63;
	
	while (mask) {
	
		if ((mask & x) && !(mask & y)) {
			return true;
		}
		
		if ((mask & y) && !(mask & x)) {
			return false;
		}
		
		mask >>= 1;
	}
	
	return false;
}


		// Проверка того, меньше ли первое число второго
		
bool isLess(unsigned long x, unsigned long y) {
	unsigned long mask = 1ul << 63;
	
	while (mask) {
	
		if ((mask & x) && !(mask & y)) {
			return false;
		}
		
		if ((mask & y) && !(mask & x)) {
			return true;
		}
		
		mask >>= 1;
	}
	
	return false;	
}


		// Проверка на больше либо равно
		
bool isGreaterOrEqual(unsigned long x, unsigned long y) {
	unsigned long mask = 1ul << 63;
	
	while (mask) {
	
		if ((mask & x) && !(mask & y)) {
			return true;
		}
		
		if ((mask & y) && !(mask & x)) {
			return false;
		}
		
		mask >>= 1;
	}
	
	return true;
}


		// Проверка на меньше либо равно
		
bool isLessOrEqual(unsigned long x, unsigned long y) {
	unsigned long mask = 1ul << 63;
	
	while (mask) {
	
		if ((mask & x) && !(mask & y)) {
			return false;
		}
		
		if ((mask & y) && !(mask & x)) {
			return true;
		}
		
		mask >>= 1;
	}
	
	return true;
}




		// Сложение двух положительных чисел
		
unsigned long sum(unsigned long x, unsigned long y) {
	while (y) {
		unsigned long z = x ^ y;
		y &= x;
		y <<= 1;
		x = z;
	}
	
	return x;	
}


		// Вычитание двух положительных чисел. Первое больше либо равно второму.
		
unsigned long subtract(unsigned long x, unsigned long y) {
	while (y) {
		unsigned long z = x ^ y;
		y = y & ~x;
		y <<= 1;
		x = z;
	}
	
	return x;	
}


		// Умножение двух положительных чисел
		
unsigned long multiply(unsigned long x, unsigned long y) {
	unsigned long result = 0ul;
	unsigned long mask = 1ul;
	
	while (mask) {
		if (mask & y) {
			result = sum(result, x);	
		}
		
		x <<= 1;
		mask <<= 1;
	}
	
	return result;
}		


		// Возведение в степень
		
unsigned long pow(unsigned long x, unsigned long y) {
	if (!y) {
		return 1ul;
	}
	
	unsigned long result = x;
	unsigned long mask = 1ul;
	
	while (y ^ mask) {
		result = multiply(result, x);
		mask = sum(mask, 1ul);
	}
	
	return result;
}


		// Факториал

unsigned long factorial(unsigned long x) {
	if (!x) {
		return 1ul;
	}
	
	return multiply(x, factorial(decrement(x)));
}


		// Смещение всех битов числа в начало битовой записи влево. Число может быть равно нулю.
		
unsigned long shiftBitsToLeft(unsigned long number) {
	while (!(1ul << 63 & number) && number) {
		number <<= 1;
	}

	return number;
}


		// Получение справа последовательности единиц той же длины, что и длина числа. Число может быть равно нулю.

unsigned long getLengthOfNumber(unsigned long number) {
	unsigned long length = 0ul;

	while (number) {
		length <<= 1;
		length |= 1ul;
		number >>= 1;
	}

	return length;
}


		// Получение нового делимого из старого и его дополнения. Дополнение смещено влево в начало битовой записи.

unsigned long addBitToDividend(unsigned long dividend, unsigned long addition) {
	unsigned long newDividend = dividend;
	newDividend <<= 1;
	
	if (1ul << 63 & addition) {
		newDividend |= 1ul;
	}

	return newDividend;
}


		// Деление
		
unsigned long divide(unsigned long dividend, unsigned long divider) {
	if (!divider) {
		
	}
	
	unsigned long result = 0ul;
	unsigned long tempDividend = 0ul;
	unsigned long addition = shiftBitsToLeft(dividend);
	unsigned long dividendLength = getLengthOfNumber(dividend);
	
	while (dividendLength) {
		result <<= 1;
		tempDividend = addBitToDividend(tempDividend, addition);
		addition <<= 1;
		dividendLength >>= 1;
		
		if (isGreaterOrEqual(tempDividend, divider)) {
			result |= 1ul;
			tempDividend = subtract(tempDividend, divider);
		}
	}
	
	return result;
}


		// Остаток от деления
		
unsigned long remainder(unsigned long dividend, unsigned long divider) {
	unsigned long x = divide(dividend, divider);
	x = multiply(divider, x);
	
	return subtract(dividend, x);
}


		// Инкремент
		
unsigned long increment(unsigned long x) {
	return sum(x, 1ul);
}


		// Декремент

unsigned long decrement(unsigned long x) {
	return subtract(x, 1ul);	
}




		// XOR
		
unsigned long ExclusiveOR(unsigned long x, unsigned long y) {
	return (x | y) & ~(x & y);
}




		// Логическое "И"
		
bool logicalAND(bool x, bool y) {
	if (x & ~0ul) {
		if (y & ~0ul) {
			return true;
		}
	}
	
	return false;	
}


		// Логическое "ИЛИ"
		
bool logicalOR(bool x, bool y) {
	if (x | 0ul) {
		return true;
	}
	
	if (y | 0ul) {
		return true;
	}
	
	return false;
}


		// Логическое "Не"

bool logicalNOT(bool x) {
	if (x) {
		return false;
	}
	
	return true;
}


		// Логическое "XOR"
		
bool logicalXOR(bool x, bool y) {
	bool a = logicalOR(x, y);	
	bool b = logicalAND(x, y);
	b = logicalNOT(b);
	
	return logicalAND(a, b);
}



