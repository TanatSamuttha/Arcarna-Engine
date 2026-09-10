#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 color;

layout(std430, binding = 0) buffer RenderData
{
    float data[];
};

// Index of camera data
const uint camDataSize = 8;
const uint camPosX = 0, camPosY = 1, camPosZ = 2;
const uint camRotX = 3, camRotY = 4, camRotZ = 5;
const uint camScale = 6, camAspect = 7;

// Index of model data
const uint modelDataSize = 9;
const uint modelPosX = 0, modelPosY = 1, modelPosZ = 2;
const uint modelScaleX = 3, modelScaleY = 4, modelScaleZ = 5;
const uint modelRotX = 6, modelRotY = 7, modelRotZ = 8;

out vec2 v_TexCoord;

void main ()
{
    uint padding = uint(gl_InstanceID) * modelDataSize + camDataSize;

    mat4 model = mat4(
        data[padding + modelScaleX], 0, 0, 0,
        0, data[padding + modelScaleY], 0, 0,
        0, 0, data[padding + modelScaleZ], 0,
        data[padding + modelPosX], data[padding + modelPosY], data[padding + modelPosZ], 1
    );

    mat4 view = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -data[camPosX], -data[camPosY], -data[camPosZ], 1
    );

    mat4 projection = mat4(
        1.0 / data[camScale] / data[camAspect], 0, 0, 0,
        0, 1.0 / data[camScale], 0, 0,
        0, 0, 1.0 / data[camScale], 0,
        0, 0, 0, 1
    );

    gl_Position = projection * view * model * position;
    v_TexCoord = texCoord;
}