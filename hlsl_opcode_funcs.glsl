
void movc(inout float dest, float value) {
    if(value > 0.0) dest = value;
};
void movc(inout vec2 dest, vec4 value) {
    if(value.x > 0.0) dest.x = value.x;
    if(value.y > 0.0) dest.y = value.y;
};
void mul(inout float dest, float a, float b) {
    dest = a * b;
}
void mul(inout vec3 dest, vec4 a, vec4 b) {
    dest = a.xyz * b.xyz;
}
void mul(inout vec4 dest, vec4 a, vec4 b) {
    dest = a * b;
}

void mad(inout float dest, float a, float b, float c) {
    dest = a * b + c;
}
void mad(inout vec3 dest, vec4 a, vec4 b, vec4 c) {
    dest = a.xyz * b.xyz + c.xyz;
}
void mad(inout vec4 dest, vec4 a, vec4 b, vec4 c) {
    dest = a * b + c;
}
