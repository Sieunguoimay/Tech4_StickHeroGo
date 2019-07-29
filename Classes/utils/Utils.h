#pragma once
class Utils {
public:
	static float linear(float a, float b, float t) {
		return a + t*(b - a);
	}
	static float bezier3(float a, float b, float c, float t) {
		return linear(linear(a, b, t), linear(b, c, t), t);
	}
	static float bezier4(float a, float b, float c,float d, float t) {
		return linear(bezier3(a, b,c, t), bezier3(b, c, d, t), t);
	}
	static float map(float a, float a1, float a2, float b1, float b2) {
		return (a - a1) / (a2 - a1) * (b2 - b1) + b1;
	}
	static bool isPrime(int n) {
		if (n == 2)return true;
		if (n == 3)return true;
		if (n % 2 == 0)return false;
		if (n % 3 == 0)return false;
		int i = 5;
		int w = 2;
		while (i * i <= n) {
			if (n % i == 0)return false;
			i += w;
			w = 6 - w;
		}
		return true;
	}
};
