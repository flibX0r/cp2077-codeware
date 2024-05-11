#pragma once

#include "App/Callback/CallbackSystem.hpp"
#include "App/Callback/CallbackSystemController.hpp"
#include "App/Callback/Events/GameSessionEvent.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/PlayerSystem.hpp"

namespace App
{
class PlayerSpawnedHook
    : public CallbackSystemController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Session/Ready");

    Core::Map<Red::CName, Red::CName> GetEvents() override
    {
        return {{EventName, Red::GetTypeName<EntityLifecycleEvent>()}};
    }

protected:
    bool OnActivateHook() override
    {
        return IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || HookAfter<Raw::PlayerSystem::OnPlayerSpawned>(&OnPlayerSpawned);
    }

    bool OnDeactivateHook() override
    {
        return !IsHooked<Raw::PlayerSystem::OnPlayerSpawned>() || Unhook<Raw::PlayerSystem::OnPlayerSpawned>();
    }

    inline static void OnPlayerSpawned()
    {
        auto system = CallbackSystem::Get();
        if (!system->IsRestored())
        {
            system->DispatchNativeEvent<GameSessionEvent>(EventName, system->IsPreGame(), system->IsRestored());
        }
    }
};
}
