#pragma once

#include "Core/Facades/Runtime.hpp"

namespace App::Env
{
inline std::filesystem::path KnownHashesPath()
{
    return Core::Runtime::GetModuleDir() / L"KnownHashes.txt";
}
}
