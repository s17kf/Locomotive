#version 330 core

in vec3 FragPos; 
in vec2 TexCoords;  
in vec3 Normal; 

out vec4 FragColor;

uniform sampler2D Texture;

uniform vec3 lightPos; 
uniform vec3 lightColor;


void main()
{    
    // ambient
	float ambientStrenght = 0.4;
	vec3 ambient  = ambientStrenght * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse  = diff * lightColor;
    
	vec4 aColor = texture(Texture, TexCoords);
	vec3 bColor = (ambient + diffuse) * vec3(aColor.x, aColor.y, aColor.z);        
	FragColor = vec4(bColor, 1.0);
}