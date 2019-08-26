#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aShift;
layout (location = 4) in float aSpeed;

out vec3 ourColor;
out vec2 TexCoord;
out float opacity;
out vec4 position;

uniform mat4 transform;
uniform bool exploding;

void main()
{

    // Attaches coordinates of image texture to coordinates of the square sinha
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    // If there is no shift, it is not a sinha
    if (aShift == vec3(0.0,0.0,0.0))
    {
        // Position remains as given without modification as it will not move
        gl_Position = vec4(aPos,1.0);
    }
    else
    {
        // Vector for shifting sinha off the centre of the cell
        vec4 base_vector = vec4(aShift,0.0);

        // Transformation vector to translate/rotate the vector accordingly
        base_vector *= transform;

        // Position is transformed shifting vector + vector to the centre of the cell
        gl_Position = (base_vector) + vec4(aPos,1.0);

    }

    // If texcoord = sentinel value, then it does not require a picture overlay
    if (TexCoord == vec2(-1.0,-1.0))
    {
        // 100 opacity
        opacity = 1.0;
    }
    else
    {
        // Opacity is set just low enough that it will be later discarded
        opacity = 0.19;
    }

    //
    ourColor = aColor;
}
