
void HLSL_ge(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(greaterThanEqual(a, b));
}

void HLSL_ge(out float dest, float a, float b) {
    dest = (a >= b) ? 1.0 : 0.0;
}

void HLSL_ige(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(greaterThanEqual(a, b));
}

void HLSL_ige(out float dest, float a, float b) {
    dest = (a >= b) ? 1.0 : 0.0;
}

void HLSL_lt(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(lessThan(a, b));
}

void HLSL_lt(out vec3 dest, vec4 a, vec4 b) {
    dest = vec3(lessThan(a, b));
}

void HLSL_lt(out float dest, float a, float b) {
    dest = (a < b) ? 1.0 : 0.0;
}

void HLSL_ieq(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(equal(a, b));
}

void HLSL_ieq(out float dest, float a, float b) {
    dest = (a == b) ? 1.0 : 0.0;
}

void HLSL_eq(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(equal(a, b));
}

void HLSL_eq(out float dest, float a, float b) {
    dest = (a == b) ? 1.0 : 0.0;
}

#if __VERSION__ != 120 && __VERSION__ != 100
void HLSL_and(out vec4 dest, vec4 a, vec4 b) {
	ivec4 ia = ivec4(a);
	ivec4 ib = ivec4(b);
	dest = vec4(ia & ib);
}
void HLSL_and(out float dest, float a, float b) {
	int ia = int(a);
	int ib = int(b);
	dest = float(ia & ib);
}
#endif

void HLSL_ilt(out vec4 dest, vec4 a, vec4 b) {
	ivec4 ia = ivec4(a);
	ivec4 ib = ivec4(b);
   dest = vec4(lessThan(ia, ib));
}

void HLSL_ilt(out float dest, float a, float b) {
	int ia = int(a);
	int ib = int(b);
    dest = (ia < ib) ? 1.0 : 0.0;
}

