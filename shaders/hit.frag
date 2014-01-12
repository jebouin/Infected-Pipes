uniform sampler2D texture;
uniform float time;
uniform float lastTimeHit;

void main() {
	vec4 col = texture2D(texture, gl_TexCoord[0].xy);
	vec4 maxCol = vec4(1., .9, .6, col.w);
	float x = ((time-lastTimeHit)/42.);
	if(x < 0. | x > 1.) {
		gl_FragColor = col;
	} else {
		x = 1.-x;
		float y = x;
		gl_FragColor = vec4(y*(maxCol-col) + col);
	}
}