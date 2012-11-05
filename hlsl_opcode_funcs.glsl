
void HLSL_movc(out float dest, float value) {
    if(value > 0.0) dest = value;
}
void HLSL_movc(out vec2 dest, vec4 value) {
    if(value.x > 0.0) dest.x = value.x;
    if(value.y > 0.0) dest.y = value.y;
}

void HLSL_ge(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(greaterThanEqual(a, b));
}

void HLSL_ge(out float dest, float a, float b) {
    dest = (a >= b) ? 1 : 0;
}

void HLSL_ige(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(greaterThanEqual(a, b));
}

void HLSL_ige(out float dest, float a, float b) {
    dest = (a >= b) ? 1 : 0;
}

void HLSL_lt(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(lessThan(a, b));
}

void HLSL_lt(out float dest, float a, float b) {
    dest = (a < b) ? 1 : 0;
}

void HLSL_ieq(out vec4 dest, vec4 a, vec4 b) {
    dest = vec4(equal(a, b));
}

void HLSL_ieq(out float dest, float a, float b) {
    dest = (a == b) ? 1 : 0;
}
