//the real number
const int myNumber = 6;

// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 
int guess(int n) {
	if (n < myNumber)
		return 1;
	else if (n > myNumber)
		return -1;
	else return 0;
}

int guessNumber(int n) {
	if (n <= 0) return 0;
	if (guess(n) == 0)
		return n;
	return makeGuess(0, n);
}

int makeGuess(long long start, long long end) {
	long long mid = (start + end) / 2;
	if (guess(mid) == -1) {
		return makeGuess(start, mid);

	}
	else if (guess(mid) == 1)
		return makeGuess(mid, end);
	else return mid;
}