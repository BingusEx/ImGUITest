// #pragma once
// #include "imgui.h"
// #include "imgui_impl_win32.h"
// #include "imgui_impl_dx11.h"
// #include <d3d11.h>
// #include <tchar.h>
// #include <string>
// #include <format>
// #include <vector>
// #include <iostream>
// #include <memory>
// #include <d3dcompiler.h>

//TODO Funny stuff will happen here

// // Framebuffer and texture for background blur
// static ID3D11Texture2D* blurTexture = nullptr;
// static ID3D11RenderTargetView* blurRenderTargetView = nullptr;
// static ID3D11ShaderResourceView* blurShaderResourceView = nullptr;

// // Declare the shaders
// static ID3D11PixelShader* horizontalBlurShader;
// static ID3D11PixelShader* verticalBlurShader;

// extern ID3D11Device* pd3dDevice;
// extern ID3D11DeviceContext* pd3dDeviceContext;

// inline void DoBackgroundBlur() {
//     // Load the blur shaders
//     ID3DBlob* pBlob = nullptr;

//     D3DReadFileToBlob(L"..\\..\\shaders\\Blur.hlsl", &pBlob);
//     pd3dDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &horizontalBlurShader);
//     pd3dDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &verticalBlurShader);
//     pBlob->Release();

//     // Create the blur texture
//     D3D11_TEXTURE2D_DESC textureDesc = {};
//     // Clear the blur texture
//     float clearColor[4] = {0, 0, 0, 0};
//     textureDesc.Width = 800; // Set the width of the texture
//     textureDesc.Height = 600; // Set the height of the texture
//     textureDesc.MipLevels = 1;
//     textureDesc.ArraySize = 1;
//     textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//     textureDesc.SampleDesc.Count = 1;
//     textureDesc.Usage = D3D11_USAGE_DEFAULT;
//     textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

//     pd3dDevice->CreateTexture2D(&textureDesc, nullptr, &blurTexture);

//     // Create the render target view
//     pd3dDevice->CreateRenderTargetView(blurTexture, nullptr, &blurRenderTargetView);

//     // Create the shader resource view
//     pd3dDevice->CreateShaderResourceView(blurTexture, nullptr, &blurShaderResourceView);

//     // Set the render target to the blur texture
//     pd3dDeviceContext->OMSetRenderTargets(1, &blurRenderTargetView, nullptr);

//     // Clear the render target view
//     pd3dDeviceContext->ClearRenderTargetView(blurRenderTargetView, clearColor);

//     // Apply the blur effect
//     // Set the horizontal blur shader
//     pd3dDeviceContext->PSSetShader(horizontalBlurShader, nullptr, 0);
//     pd3dDeviceContext->PSSetShaderResources(0, 1, &blurShaderResourceView);
//     //g_pd3dDeviceContext->Draw(3, 0);

//     // Set the vertical blur shader
//     ImGui::GetBackgroundDrawList()->AddImage(reinterpret_cast<ImTextureID>(blurShaderResourceView), ImVec2(0, 0), ImVec2(800, 600));
//     //ImGui::Image(reinterpret_cast<ImTextureID>(blurShaderResourceView), ImGui::GetContentRegionAvail());
//     pd3dDeviceContext->PSSetShaderResources(0, 1, &blurShaderResourceView);
//     //g_pd3dDeviceContext->Draw(3, 0);
// }
