#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aShift;
layout (location = 4) in float aSpeed;

out vec3 ourColor;
out vec2 TexCoord;
out float opacity;

uniform mat4 transform;

void main()
{

    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    if (aShift == vec3(0.0,0.0,0.0))
    {
        gl_Position = vec4(aPos,1.0) + (vec4(0.0,0.0,0.0,0.0)  * transform);
    }
    else
    {
        vec4 base_vector = vec4(aShift,0.0) * transform;
        gl_Position = (base_vector) + vec4(aPos,1.0);
    }

    if (TexCoord == vec2(-1.0,-1.0))
    {
        opacity = 1.0;
    }
    else
    {
        opacity = 0.19;
    }

    ourColor = aColor;
}
