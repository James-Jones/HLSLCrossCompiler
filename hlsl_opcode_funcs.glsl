
void HLSL_mov(out float dest, float value) {
    dest = value;
}
void HLSL_mov(out float dest, vec4 value) {
    dest = value.x;
}
void HLSL_mov(out vec1 dest, vec4 value) {
    dest.x = value.x;
}
void HLSL_mov(out vec2 dest, vec4 value) {
    dest = value.xy;
}
void HLSL_mov(out vec3 dest, vec4 value) {
    dest = value.xyz;
}
void HLSL_mov(out vec4 dest, vec4 value) {
    dest = value;
}

void HLSL_movc(out float dest, float value) {
    if(value > 0.0) dest = value;
}
void HLSL_movc(out vec2 dest, vec4 value) {
    if(value.x > 0.0) dest.x = value.x;
    if(value.y > 0.0) dest.y = value.y;
}
void HLSL_mul(out float dest, float a, float b) {
    dest = a * b;
}
void HLSL_mul(out vec3 dest, vec4 a, vec4 b) {
    dest = a.xyz * b.xyz;
}
void HLSL_mul(out vec4 dest, vec4 a, vec4 b) {
    dest = a * b;
}

void HLSL_mad(out float dest, float a, float b, float c) {
    dest = a * b + c;
}
void HLSL_mad(out vec3 dest, vec4 a, vec4 b, vec4 c) {
    dest = a.xyz * b.xyz + c.xyz;
}
void HLSL_mad(out vec4 dest, vec4 a, vec4 b, vec4 c) {
    dest = a * b + c;
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

void HLSL_sample_l(out vec4 dest, sampler2D sampler, vec4 coord, float lod) {
    dest = texture2DLod(sampler, coord.xy, lod);
}
void HLSL_sample_l(out vec3 dest, sampler2D sampler, vec4 coord, float lod) {
    dest = texture2DLod(sampler, coord.xy, lod).xyz;
}

void HLSL_sample_l(out vec4 dest, sampler2D sampler, vec2 coord, float lod) {
    dest = texture2DLod(sampler, coord, lod);
}
void HLSL_sample_l(out vec3 dest, sampler2D sampler, vec2 coord, float lod) {
    dest = texture2DLod(sampler, coord, lod).xyz;
}

