#version 330 core
in vec2 TexCoords;
in vec3 JerryPos;

out vec4 color;

uniform sampler2D sprite;
uniform vec3 spriteColor;

uniform int LightOn;
uniform vec3 LightPos;

void main()
{
    color = vec4(spriteColor, 1.0) * texture(sprite, TexCoords);
    if(LightOn==0)
    {
        float distance = length(LightPos-JerryPos);
        if(distance > 100.0f){
            color = vec4(0.0, 0.0, 0.0, 1.0);
        }
    }
}