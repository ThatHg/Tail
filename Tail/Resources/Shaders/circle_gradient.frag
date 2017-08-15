uniform sampler2D texture;

void main() {
    // multiply it by the color
    vec4 pixel = texture2D(texture, vec2(gl_TexCoord[0].x,0));
    gl_FragColor = gl_Color * pixel;
}