uniform vec2 _middle_point;
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform float u_ratio_time;

void main() {
    vec2 st = vec2(5.0,5.0);

    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    // Calculate the distance from this vertex to the middle point.
    
    gl_TexCoord[0].x = u_ratio_time;//distance(gl_Vertex, vec4(_middle_point.x, _middle_point.y, 0,0)) * 0.01;
    //gl_TexCoord[0].x = distance(gl_Vertex, vec4(_middle_point.x, _middle_point.y, 0,0)) * 0.01;
    //gl_TexCoord[0].x = gl_TexCoord[0].x * gl_TexCoord[0].x * (3.0 -2.0 * gl_TexCoord[0].x);

    gl_FrontColor = gl_Color;
}