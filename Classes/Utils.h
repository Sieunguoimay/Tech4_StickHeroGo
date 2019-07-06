#pragma once
static float linear(float a, float b, float t) {
	return a + t*(b - a);
}
static float bezier3(float a, float b, float c, float t) {
	return linear(linear(a, b, t), linear(b, c, t), t);
}
static float bezier4(float a, float b, float c,float d, float t) {
	return linear(bezier3(a, b,c, t), bezier3(b, c, d, t), t);
}