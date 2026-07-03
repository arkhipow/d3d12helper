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

    HRESULT result = S_OK;

    Microsoft::WRL::ComPtr<ID3D12Device> device;
    result = D3D12CreateDevice(adapter.Get(), feature_levels.back(), IID_PPV_ARGS(&device));
    if (FAILED(result)) {
        return std::nullopt;
    }

    D3D12_FEATURE_DATA_FEATURE_LEVELS data_feature_levels = { };
    data_feature_levels.NumFeatureLevels = static_cast<UINT>(feature_levels.size());
    data_feature_levels.pFeatureLevelsRequested = feature_levels.data();

    result = device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &data_feature_levels, sizeof(data_feature_levels));
    if (FAILED(result)) {
        return std::nullopt;
    }

    return data_feature_levels.MaxSupportedFeatureLevel;
}

std::optional<UINT> D3D12Helper::getMaxMultisampleQualityLevel(const Microsoft::WRL::ComPtr<ID3D12Device>& device, DXGI_FORMAT format, UINT sample_count, D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS flags) {
    if (!device) {
        return std::nullopt;
    }

    HRESULT result = S_OK;

    D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS data_multisample_quality_levels = { };
    data_multisample_quality_levels.Format = format;
    data_multisample_quality_levels.SampleCount = sample_count;
    data_multisample_quality_levels.Flags = flags;

    result = device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &data_multisample_quality_levels, sizeof(data_multisample_quality_levels));
    if (FAILED(result)) {
        return std::nullopt;
    }

    UINT max_multisample_quality_level = data_multisample_quality_levels.NumQualityLevels;
    if (!max_multisample_quality_level) {
        return std::nullopt;
    }

    return max_multisample_quality_level - 1;
}