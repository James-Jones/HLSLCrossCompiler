
void HLSL_mov(inout float dest, float value) {
    dest = value;
}
void HLSL_mov(inout float dest, vec4 value) {
    dest = value.x;
}
void HLSL_mov(inout vec1 dest, vec4 value) {
    dest.x = value.x;
}
void HLSL_mov(inout vec2 dest, vec4 value) {
    dest = value.xy;
}
void HLSL_mov(inout vec3 dest, vec4 value) {
    dest = value.xyz;
}
void HLSL_mov(inout vec4 dest, vec4 value) {
    dest = value;
}

void HLSL_movc(inout float dest, float value) {
    if(value > 0.0) dest = value;
}
void HLSL_movc(inout vec2 dest, vec4 value) {
    if(value.x > 0.0) dest.x = value.x;
    if(value.y > 0.0) dest.y = value.y;
}
void HLSL_mul(inout float dest, float a, float b) {
    dest = a * b;
}
void HLSL_mul(inout vec3 dest, vec4 a, vec4 b) {
    dest = a.xyz * b.xyz;
}
void HLSL_mul(inout vec4 dest, vec4 a, vec4 b) {
    dest = a * b;
}

void HLSL_mad(inout float dest, float a, float b, float c) {
    dest = a * b + c;
}
void HLSL_mad(inout vec3 dest, vec4 a, vec4 b, vec4 c) {
    dest = a.xyz * b.xyz + c.xyz;
}
void HLSL_mad(inout vec4 dest, vec4 a, vec4 b, vec4 c) {
    dest = a * b + c;
}

void HLSL_ge(inout vec4 dest, vec4 a, vec4 b) {
    dest = vec4(greaterThanEqual(a, b));
}

void HLSL_ge(inout float dest, float a, float b) {
    dest = (a >= b) ? 1 : 0;
}

void HLSL_ige(inout vec4 dest, vec4 a, vec4 b) {
    dest = vec4(greaterThanEqual(a, b));
}

void HLSL_ige(inout float dest, float a, float b) {
    dest = (a >= b) ? 1 : 0;
}

void HLSL_lt(inout vec4 dest, vec4 a, vec4 b) {
    dest = vec4(lessThan(a, b));
}

void HLSL_lt(inout float dest, float a, float b) {
    dest = (a < b) ? 1 : 0;
}

void HLSL_ieq(inout vec4 dest, vec4 a, vec4 b) {
    dest = vec4(equal(a, b));
}

void HLSL_ieq(inout float dest, float a, float b) {
    dest = (a == b) ? 1 : 0;
}

void HLSL_sample_l(inout vec4 dest, sampler2D sampler, vec4 coord, float lod) {
    dest = texture2DLod(sampler, coord.xy, lod);
}
void HLSL_sample_l(inout vec3 dest, sampler2D sampler, vec4 coord, float lod) {
    dest = texture2DLod(sampler, coord.xy, lod).xyz;
}

void HLSL_sample_l(inout vec4 dest, sampler2D sampler, vec2 coord, float lod) {
    dest = texture2DLod(sampler, coord, lod);
}
void HLSL_sample_l(inout vec3 dest, sampler2D sampler, vec2 coord, float lod) {
    dest = texture2DLod(sampler, coord, lod).xyz;
}

