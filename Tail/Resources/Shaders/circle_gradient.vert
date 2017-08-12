uniform vec2 _middle_point;
uniform float _z_pos;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vec4 pos = gl_Vertex;
    pos.z = _z_pos;

    // Calculate the distance from this vertex to the middle point.
    gl_TexCoord[0].x = distance(pos, vec4(pos.x * 0.7 + _middle_point.x * 0.3, _middle_point.y, 0,0)) * 0.01;
}