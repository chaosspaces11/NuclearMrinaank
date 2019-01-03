#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float opacity;

uniform sampler2D texture1;


void main()
{
//    FragColor = mix(texture(texture1, TexCoord), vec4(ourColor,1.0), opacity);
    vec4 texColor = mix(texture(texture1, TexCoord), vec4(ourColor,1.0), opacity);
    if(texColor.a < 0.2)
            discard;
    FragColor = texColor;
}
