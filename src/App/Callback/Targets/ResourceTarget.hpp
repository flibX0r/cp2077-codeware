#pragma once

#include "App/Callback/CallbackSystemTarget.hpp"
#include "App/Callback/Events/ResourceEvent.hpp"
#include "App/Depot/ResourcePathRegistry.hpp"
#include "Core/Facades/Container.hpp"

namespace App
{
struct ResourceTarget : CallbackSystemTarget
{
    ResourceTarget() = default;

    ResourceTarget(Red::ResourcePath aPath)
        : path(aPath)
    {
    }

    ResourceTarget(Red::CClass* aType)
        : type(aType)
    {
    }

    bool Matches(const Red::Handle<CallbackSystemEvent>& aEvent) override
    {
        const auto* event = aEvent.GetPtr<ResourceEvent>();

        if (path)
        {
            if (regex.has_value())
            {
                auto pathStr = Core::Resolve<ResourcePathRegistry>()->GetPath(event->resource->path);
                if (pathStr.empty())
                    return false;

                if (!std::regex_match(pathStr.begin(), pathStr.end(), regex.value()))
                    return false;
            }
            else
            {
                if (event->resource->path != path)
                    return false;
            }
        }

        if (type && !event->resource->GetNativeType()->IsA(type))
            return false;

        return true;
    }

    bool Equals(const Red::Handle<CallbackSystemTarget>& aTarget) override
    {
        const auto* target = aTarget.GetPtr<ResourceTarget>();

        return path == target->path && type == target->type;
    }

    bool Supports(Red::CName aEventType) override
    {
        return aEventType == Red::GetTypeName<ResourceEvent>();
    }

    static Red::Handle<ResourceTarget> Path(const Red::RaRef<>& aResourceRef)
    {
        auto target = Red::MakeHandle<ResourceTarget>();
        target->path = aResourceRef.path;

        auto pathStr = Core::Resolve<ResourcePathRegistry>()->GetPath(target->path);
        if (!pathStr.empty())
        {
            if (pathStr.starts_with("regex:"))
            {
                pathStr.remove_prefix(6);
                target->regex = {pathStr.data(), pathStr.size()};
            }
            else if (pathStr.find('*') != std::string_view::npos)
            {
                static const std::regex regexWildcardMeta(R"([\.\^\$\-\+\(\)\[\]\{\}\|\?\\])");
                static const std::regex regexWildcardStar("\\*");
                std::string pattern{pathStr};
                pattern = std::regex_replace(pattern, regexWildcardMeta, "\\$&");
                pattern = std::regex_replace(pattern, regexWildcardStar, ".*");
                target->regex = "^" + pattern + "$";
            }
        }

        return target;
    }

    static Red::Handle<ResourceTarget> Type(Red::CName aResourceType)
    {
        auto target = Red::MakeHandle<ResourceTarget>();
        target->type = Red::GetClass(aResourceType);

        return target;
    }

    Red::ResourcePath path{};
    std::optional<std::regex> regex{};
    Red::CClass* type{};

    RTTI_IMPL_TYPEINFO(App::ResourceTarget);
    RTTI_IMPL_ALLOCATOR();
};
}

RTTI_DEFINE_CLASS(App::ResourceTarget, {
    RTTI_PARENT(App::CallbackSystemTarget);
    RTTI_METHOD(Path);
    RTTI_METHOD(Type);
});
