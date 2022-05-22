#version 330 core
out vec4 FragColor;


uniform sampler2D cubeTexture;
//uniform sampler2D dudvTexture;


in vec2 TexCoord;

void main(){
    
    vec4 ambient = texture(cubeTexture, TexCoord).rgba;

    //vec4 dudv = texture(dudvTexture, TexCoord).rgba;

    vec4 result = ambient;
    if(result.a < 0.1)
        discard;
    FragColor = result;
}
