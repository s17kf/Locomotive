#version 330 core
out vec4 FragColor;

//in vec4 vertexColor;
//uniform vec4 ourColor; // we set this variable in the OpenGL code.
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D Texture;
//uniform sampler2D Texture0;
//uniform sampler2D Texture1;

void main()
{
    //FragColor = vec4(0.7f, 0.5f, 0.2f, 1.0f);
	//FragColor = vertexColor;
	//FragColor = ourColor;
	//FragColor = vec4(ourColor, 1.0);
	FragColor = texture(Texture, TexCoord);
	//FragColor = texture(Texture0, TexCoord) * vec4(ourColor, 1.0);
	//FragColor = mix(texture(Texture0, TexCoord), texture(Texture1, TexCoord),0.65);
} 