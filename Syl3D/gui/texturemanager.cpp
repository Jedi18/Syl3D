#include "texturemanager.h"
#include "../texture/texturefactory.h"

#include <iostream>

using namespace gui;

bool TextureManager::open = false;
int TextureManager::selectedTexture = 0;

void TextureManager::ShowTextureManager() {
    if (!TextureManager::open) {
        return;
    }

    ImGui::Begin("Texture Manager", &open);

    std::vector<std::string> textureMaterialsList = TextureFactory::getAvailableTextureMaterials();
    if (ImGui::Combo("Texture Material", &selectedTexture, getTextureMaterialsList(textureMaterialsList).c_str())) {
        std::cout << "Selected texture : " << selectedTexture << '\n';
    }

    // Testing textures
    std::shared_ptr<TextureMaterial> texMaterial = TextureFactory::getTextureMaterial(textureMaterialsList[selectedTexture]);
    ImTextureID my_tex_id = (void*)texMaterial->getTextureId(0);
    float my_tex_w = (float)100;
    float my_tex_h = (float)100;

    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
    ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
    ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), uv_min, uv_max, tint_col, border_col);

    ImGui::End();
}

std::string TextureManager::getTextureMaterialsList(const std::vector<std::string>& textureMaterialsList) {
    std::stringstream ss;

    for (const std::string& textureMaterial : textureMaterialsList) {
        ss << textureMaterial << '\0';
    }

    return ss.str();
}