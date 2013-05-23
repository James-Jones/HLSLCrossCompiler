
void HLSL_ige(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(greaterThanEqual(a, b));
}

void HLSL_ige(out float dest, float a, float b) {
    dest = (a >= b) ? 1.0 : 0.0;
}

void HLSL_ieq(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(equal(a, b));
}

void HLSL_ieq(out float dest, float a, float b) {
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

void HLSL_ult(out vec4 dest, vec4 a, vec4 b) {
	uvec4 ia = uvec4(a);
	uvec4 ib = uvec4(b);
   dest = vec4(lessThan(ia, ib));
}

void HLSL_ult(out float dest, float a, float b) {
	uint ia = uint(a);
	uint ib = uint(b);
    dest = (ia < ib) ? 1.0 : 0.0;
}

void HLSL_uge(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(greaterThanEqual(a, b));
}

void HLSL_uge(out float dest, float a, float b) {
    dest = (a >= b) ? 1.0 : 0.0;
}
