uniform sampler2D texture;
uniform vec2 r;

void main()
{
   vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	vec2 p = gl_TexCoord[0].xy;
	p.y -= .5;
	p.x -= .5;
	float b = 1.-length(p);
   gl_FragColor = pixel * b;
}