#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 color;

layout(std430, binding = 0) buffer RenderData
{
    float data[];
};
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
    int padding = gl_InstanceID * 17;

    mat4 model = mat4(
        data[padding + 3], 0, 0, 0,
        0, data[padding + 4], 0, 0,
        0, 0, data[padding + 5], 0,
        data[padding + 0], data[padding + 1], data[padding + 2], 1
    );

    mat4 view = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -data[padding + 9], -data[padding + 10], -data[padding + 11], 1
    );

    mat4 projection = mat4(
        1.0 / data[padding + 15] / data[padding + 16], 0, 0, 0,
        0, 1.0 / data[padding + 15], 0, 0,
        0, 0, 1.0 / data[padding + 15], 0,
        0, 0, 0, 1
    );

    gl_Position = projection * view * model * position;
    v_TexCoord = texCoord;
}