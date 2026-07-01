#include "../include/d3d12helper.hpp"

#include <vector>

std::optional<D3D_FEATURE_LEVEL> D3D12Helper::getMaxFeatureLevel(const Microsoft::WRL::ComPtr<IDXGIAdapter>& adapter) {
    if (!adapter) {
        return std::nullopt;
    }

    static const std::vector<D3D_FEATURE_LEVEL> feature_levels = {
        D3D_FEATURE_LEVEL_12_2,
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };

    HRESULT res = S_OK;

    Microsoft::WRL::ComPtr<ID3D12Device> device;
    res = D3D12CreateDevice(adapter.Get(), feature_levels.back(), IID_PPV_ARGS(&device));
    if (FAILED(res)) {
        return std::nullopt;
    }

    D3D12_FEATURE_DATA_FEATURE_LEVELS data_feature_levels = { };
    data_feature_levels.NumFeatureLevels = static_cast<UINT>(feature_levels.size());
    data_feature_levels.pFeatureLevelsRequested = feature_levels.data();

    res = device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &data_feature_levels, sizeof(data_feature_levels));
    if (FAILED(res)) {
        return std::nullopt;
    }

    return data_feature_levels.MaxSupportedFeatureLevel;
}