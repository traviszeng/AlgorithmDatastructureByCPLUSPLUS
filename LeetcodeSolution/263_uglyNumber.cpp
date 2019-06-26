bool isUgly(int num) {
	if (num == 0)
		return false;
	if (num == 1)
		return true;
	if (num == -1)
		return false;
	if (num % 2 != 0 && num % 3 != 0 && num % 5 != 0)
		return false;
	else {
		if ((num % 2 == 0 && num / 2 == 1) || (num % 3 == 0 && num / 3 == 1) || (num % 5 == 0 && num / 5 == 1))
			return true;
		if (num % 2 == 0 && num / 2 != 1)
			return isUgly(num / 2);
		if (num % 3 == 0 && num / 3 != 1)
			return isUgly(num / 3);
		if (num % 5 == 0 && num / 5 != 1)
			return isUgly(num / 5);

	}
	return false;
}