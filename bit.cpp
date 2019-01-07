		
		
		
		
		// Check two numbers for equality (=)
		// Проверка двух чисел на равенство (=)
		
bool isEqual(unsigned long x, unsigned long y) {
	if (x ^ y) {
		return false;
	}
	
	return true;
}


		// Check two numbers for inequality (!=)
		// Проверка двух чисел на неравенство (!=)
		
bool isNotEqual(unsigned long x, unsigned long y) {
	if (x ^ y) {
		return true;
	}
	
	return false;
}


		// Check whether the first number is greater than the second (>)
		// Проверка того, больше ли первое число второго (>)
		
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


		// Check whether the first number is less than the second (<)
		// Проверка того, меньше ли первое число второго (<)
		
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


		// Check for greater or equal (>=)
		// Проверка на больше либо равно (>=)
		
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


		// Check for less or equal (<=)
		// Проверка на меньше либо равно (<=)
		
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




		// Addition of two positive numbers (+)
		// Сложение двух положительных чисел (+)
		
unsigned long sum(unsigned long x, unsigned long y) {
	while (y) {
		unsigned long z = x ^ y;
		y &= x;
		y <<= 1;
		x = z;
	}
	
	return x;	
}


		// Subtraction of two positive numbers. The first is greater or equal then the second (-)
		// Вычитание двух положительных чисел. Первое больше либо равно второму (-)
		
unsigned long subtract(unsigned long x, unsigned long y) {
	while (y) {
		unsigned long z = x ^ y;
		y = y & ~x;
		y <<= 1;
		x = z;
	}
	
	return x;	
}


		// Subtraction of two positive numbers using a two’s complement for a negative number. The first is greater or equal then the second (-)
		// Вычитание двух положительных чисел с использованием дополнительного кода для отрицательного числа. Первое больше либо равно второму (-)
		
unsigned long subtract_1(unsigned long x, unsigned long y) {
	unsigned long onesComplement = ~y;
	unsigned long twosComplement = sum(onesComplement, 1ul);
	
	return sum(x, twosComplement);	
}


		// Multiplication of two positive numbers (*)
		// Перемножение двух положительных чисел (*)
		
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


		// Exponentiation
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


		// Factorial
		// Факториал

unsigned long factorial(unsigned long x) {
	if (!x) {
		return 1ul;
	}
	
	return multiply(x, factorial(decrement(x)));
}


		// Shift all the bits of the number to the beginning of the bit record to the left. The number may be zero.
		// Смещение всех битов числа в начало битовой записи влево. Число может быть равно нулю.
		
unsigned long shiftBitsToLeft(unsigned long number) {
	while (!(1ul << 63 & number) && number) {
		number <<= 1;
	}

	return number;
}


		// Get on the right a sequence of units of the same length as the length of the number. The number may be zero.
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


		// Get the new dividend from the old and its addition. Addition is shifted to the left to the beginning of the bit record.
		// Получение нового делимого из старого и его дополнения. Дополнение смещено влево в начало битовой записи.

unsigned long addBitToDividend(unsigned long dividend, unsigned long addition) {
	unsigned long newDividend = dividend;
	newDividend <<= 1;
	
	if (1ul << 63 & addition) {
		newDividend |= 1ul;
	}

	return newDividend;
}


		// Division (/)
		// Деление (/)
		
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


		// Modulo (%)
		// Остаток от деления (%)
		
unsigned long remainder(unsigned long dividend, unsigned long divider) {
	unsigned long x = divide(dividend, divider);
	x = multiply(divider, x);
	
	return subtract(dividend, x);
}


		// Increment (++)
		// Инкремент (++)
		
unsigned long increment(unsigned long x) {
	return sum(x, 1ul);
}


		// Decrement (--)
		// Декремент (--)

unsigned long decrement(unsigned long x) {
	return subtract(x, 1ul);	
}




		// Bitwise EXCLUSIVE OR. XOR (^)
		// Битовое ИСКЛЮЧАЮЩЕЕ ИЛИ. XOR (^)
		
unsigned long ExclusiveOR(unsigned long x, unsigned long y) {
	return (x | y) & ~(x & y);
}




		// Logical AND (&&)
		// Логическое И (&&)
		
bool logicalAND(bool x, bool y) {
	if (x & ~0ul) {
		if (y & ~0ul) {
			return true;
		}
	}
	
	return false;	
}


		// Logical OR (||)
		// Логическое ИЛИ (||)
		
bool logicalOR(bool x, bool y) {
	if (x | 0ul) {
		return true;
	}
	
	if (y | 0ul) {
		return true;
	}
	
	return false;
}


		// Logical NOT (!)
		// Логическое НЕ (!)

bool logicalNOT(bool x) {
	if (x) {
		return false;
	}
	
	return true;
}


		// Logical EXCLUSIVE OR. XOR
		// Логическое ИСКЛЮЧАЮЩЕЕ ИЛИ. XOR
		
bool logicalXOR(bool x, bool y) {
	bool a = logicalOR(x, y);	
	bool b = logicalAND(x, y);
	b = logicalNOT(b);
	
	return logicalAND(a, b);
}



