uniform sampler2D texture;
uniform vec2 r;
uniform float time;

#define PI 3.1415926535

void main()
{
	vec4 pixel = texture2D(texture, vec2(gl_TexCoord[0].x, 1.-gl_TexCoord[0].y));
	vec2 p = gl_TexCoord[0].xy;
	p.y -= 0.5;
	p.x -= 0.5;
	p.y *= r.y/r.x;
	
	float an = atan(p.y, p.x)+time;
	float r = step(mod(an, PI/4.), PI/8.);
	vec4 c;
	c = vec4(1., r, 0., 1.);
	
	if(length(p) < time * 2. * (3.-(r+1.))) {
		gl_FragColor = c;
	} else {
		gl_FragColor = pixel;
	}
}