#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 color;

uniform float u_RenderData[17];
// Index to data
// 0=modelPosX 1=modelPosY 2=modelPosZ
// 3=modelScaleX 4=modelScaleY 5=modelScaleZ
// 6=modelRotX 7=modelRotY 8=modelRotZ
// 9=camPosX 10=camPosY 11=camPosZ
// 12=camRotX 13=camRotY 14=camRotZ
// 15=camScale 16=camAspect

out vec2 v_TexCoord;

void main ()
{
    mat4 model = mat4(
        u_RenderData[3], 0, 0, 0,
        0, u_RenderData[4], 0, 0,
        0, 0, u_RenderData[5], 0,
        u_RenderData[0], u_RenderData[1], u_RenderData[2], 1
    );

    mat4 view = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -u_RenderData[9], -u_RenderData[10], -u_RenderData[11], 1
    );

    mat4 projection = mat4(
        1.0 / u_RenderData[15] / u_RenderData[16], 0, 0, 0,
        0, 1.0 / u_RenderData[15], 0, 0,
        0, 0, 1.0 / u_RenderData[15], 0,
        0, 0, 0, 1
    );

    gl_Position = projection * view * model * position;
    v_TexCoord = texCoord;
}