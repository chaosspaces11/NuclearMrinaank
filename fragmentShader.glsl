#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in float opacity;

uniform sampler2D texture1;


void main()
{
    // Sets colour to be a blend of Mrinaank and colour of sinha cell.
    vec4 texColor = mix(texture(texture1, TexCoord), vec4(ourColor,1.0), opacity);
    // If slightly opaque, do not display
    if(texColor.a < 0.2)
            discard;

    // Sets output colour to the mixture of Mrinaanks face and overlay colour
    FragColor = texColor;
}
