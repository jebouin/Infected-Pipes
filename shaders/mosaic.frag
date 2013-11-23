uniform sampler2D texture;
uniform vec2 r;
uniform float amp;

void main()
{
   vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 p = gl_TexCoord[0].xy*r;
	
	int x = int(mod(p.x, 4.0));
	int y = int(mod(-p.y, 4.0));
	
	float c = 1.0;
	if(y == 3 || x == 3) {
		c = 1.1;
	}
	if(y == 3 && x == 3) {
		c = 1.3;
	}
	
   gl_FragColor = pixel * c * (1.+amp);
}