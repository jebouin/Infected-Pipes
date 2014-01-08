uniform sampler2D texture;
uniform vec2 r;
uniform float amp;

void main() {
	vec4 col = texture2D(texture, gl_TexCoord[0].xy);
	vec2 p = gl_TexCoord[0].xy;
	p.y = 1-p.y;
	p *= r;
	float x = float(int(p.x));
	float y = float(int(p.y));
	
	if(mod(y, 4) == 0) {
		int i;
		if(mod(x, 4) == 0) {
			col *= 1.4;
		} else if(mod(x, 4) == 1) {
			col *= 1.27;
		} else if(mod(x, 4) == 2) {
			col *= 1.16;
		}
	}
	if(mod(x, 4) == 0 && mod(y, 4) == 1) {
		col *= 1.29;
	}
	
	gl_FragColor = col*(1+amp);
}