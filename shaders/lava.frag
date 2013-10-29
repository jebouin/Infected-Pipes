uniform sampler2D texture;
uniform vec2 r;
uniform float time;

float Prec(float n, float p) {
	return float(int(n*p))/p;	
}

vec2 Prec(vec2 n, float p) {
	return vec2(Prec(n.x, p), Prec(n.y, p));
}

float Rand(vec2 co){
    return fract(sin(dot(co.xy, vec2(12.9898, 78.238)))*43758.5453);
}

float Noise(vec2 n) {
	const vec2 d = vec2(0.0, 1.0);
	vec2 b = floor(n);
	vec2 f = smoothstep(vec2(0.0), vec2(1.0), fract(n));
	return mix(mix(Rand(b), Rand(b + d.yx), f.x), mix(Rand(b + d.xy), Rand(b + d.yy), f.x), f.y);
}

float Lava(vec2 p) {
	float t=0.;
	float sa=0.;
	float amplitude = 1.;
	for(int i=0 ; i<4 ; i++) {
		t += Noise(p)*amplitude;
		sa += amplitude;
		amplitude *= .5;
		p *= 2.;
	}
	return t/sa;
}

void main()
{
   vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 p = gl_TexCoord[0].xy;
	p.y -= .5;
	p.x -= .5/*r.x/r.y*/;
	p = p*10.;
	float c = Lava(p*10. - vec2(-time*.2, time*.5)) + Lava(p*5. - vec2(time*.2, time*.7)) * (.9+Lava(p)*sin(time));
	c *= 1.;
	c += .2;
	vec4 color = vec4(Prec(c*2., 10.), Prec(c*2.-.5, 10.), 0, 1);
	
	if(pixel.w > 0.) {
	c = Prec(c, 4.);
		gl_FragColor = vec4(pixel.r*c, pixel.g*c, pixel.b*c, 1.);
	} else {
		gl_FragColor = gl_Color * pixel;
	}
}