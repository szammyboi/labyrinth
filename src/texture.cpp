#include "texture.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include <iostream>

Texture::Texture(const std::string& path)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int channel_count;
    unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &channel_count, 0);

    glGenTextures(1, &m_Handle);
    glBindTexture(GL_TEXTURE_2D, m_Handle);

    if (channel_count == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    if (channel_count == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture::BindTo(unsigned slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Handle);
}