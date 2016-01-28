#include <iostream>
#include <D3Dcompiler.h>
#include "MiniEngine/Helper/d3dx12.h"
#include "MiniEngine/D3D12/D3D12HLSLShader.h"

using namespace MiniEngine;

D3D12HLSLShader::D3D12HLSLShader(std::string const &filename, std::string const &entry) : HLSLShader(filename, entry), _blob(nullptr)
{}

D3D12HLSLShader::~D3D12HLSLShader()
{
    if (_blob)
        _blob->Release();

    _blob = nullptr;
}

void *D3D12HLSLShader::getBytecode()
{
    return (_blob->GetBufferPointer());
}

size_t D3D12HLSLShader::getSize()
{
    return (_blob->GetBufferSize());
}

bool D3D12HLSLShader::compile(Shader::Type type)
{
    HRESULT         result;
    std::wstring    filename(_filename.begin(), _filename.end());

    #if defined(_DEBUG)
        UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    #else
        UINT compileFlags = 0;
    #endif

    result = D3DCompileFromFile(filename.c_str(), nullptr, nullptr, _entry.c_str(), type == VERTEX ? "vs_5_0" : "ps_5_0", compileFlags, 0, &_blob, nullptr);

    if (FAILED(result))
        return (false);

    return (true);
}