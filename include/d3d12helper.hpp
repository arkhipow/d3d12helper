#pragma once

#include <dxgi.h>
#include <d3d12.h>
#include <wrl.h>

#include <optional>

namespace D3D12Helper {
    std::optional<D3D_FEATURE_LEVEL> getMaxFeatureLevel(const Microsoft::WRL::ComPtr<IDXGIAdapter>& adapter);
}