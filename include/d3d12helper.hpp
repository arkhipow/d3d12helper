#pragma once

#include <dxgi.h>
#include <d3d12.h>
#include <wrl.h>

#include <optional>

namespace D3D12Helper {
    std::optional<D3D_FEATURE_LEVEL> getMaxFeatureLevel(const Microsoft::WRL::ComPtr<IDXGIAdapter>& adapter);
    std::optional<UINT> getMaxMultisampleQualityLevel(const Microsoft::WRL::ComPtr<ID3D12Device>& device, DXGI_FORMAT format, UINT sample_count = 1, D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE);
}