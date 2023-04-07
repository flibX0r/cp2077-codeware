#pragma once

#include "EntityLifecycleEvent.hpp"
#include "App/Scripting/CallbackSystem.hpp"
#include "App/Scripting/EventController.hpp"
#include "Core/Hooking/HookingAgent.hpp"
#include "Red/Entity.hpp"

namespace App
{
class EntityReassembleHook
    : public EventController
    , public Core::HookingAgent
{
public:
    constexpr static auto EventName = Red::CName("Entity/Reassemble");

    Core::Vector<Red::CName> GetEvents() override
    {
        return {EventName};
    }

    bool Initialize() override
    {
        return IsHooked<Raw::Entity::Reassemble>()
            || HookBefore<Raw::Entity::Reassemble>(&Reassemble);
    }

    bool Uninitialize() override
    {
        return !IsHooked<Raw::Entity::Reassemble>()
            || Unhook<Raw::Entity::Reassemble>();
    }

protected:
    inline static void Reassemble(Red::Entity* aEntity, uintptr_t, uint64_t, uint64_t,
                                  Red::DynArray<Red::Handle<Red::IComponent>>& aNewComponents,
                                  Red::Handle<Red::ent::EntityParametersStorage>& aEntityParams)
    {
        auto storage = Raw::Entity::ComponentsStorage(aEntity);
        auto compCount = storage->components.size;

        CallbackSystem::PassEvent<EntityLifecycleEvent>(EventName, Red::AsWeakHandle(aEntity));

        if (compCount != storage->components.size)
        {
            while (compCount < storage->components.size)
            {
                aNewComponents.PushBack(storage->components[compCount]);
                ++compCount;
            }
        }
    }
};
}
