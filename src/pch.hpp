#pragma once

#include <algorithm>
#include <codecvt>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <future>
#include <map>
#include <memory>
#include <ranges>
#include <regex>
#include <set>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include <RED4ext/RED4ext.hpp>

#include <RED4ext/JobQueue.hpp>
#include <RED4ext/Package.hpp>
#include <RED4ext/ResourceDepot.hpp>
#include <RED4ext/ResourceLoader.hpp>
#include <RED4ext/SystemUpdate.hpp>

#include <RED4ext/Scripting/Natives/GameTime.hpp>
#include <RED4ext/Scripting/Natives/Generated/CMaterialInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/CMesh.hpp>
#include <RED4ext/Scripting/Natives/Generated/CResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/DynamicTexture.hpp>
#include <RED4ext/Scripting/Natives/Generated/EInputKey.hpp>
#include <RED4ext/Scripting/Natives/Generated/EngineTime.hpp>
#include <RED4ext/Scripting/Natives/Generated/IAreaSettings.hpp>
#include <RED4ext/Scripting/Natives/Generated/IRenderResourceBlob.hpp>
#include <RED4ext/Scripting/Natives/Generated/MorphTargetMesh.hpp>
#include <RED4ext/Scripting/Natives/Generated/Quaternion.hpp>
#include <RED4ext/Scripting/Natives/Generated/Transform.hpp>
#include <RED4ext/Scripting/Natives/Generated/Vector4.hpp>
#include <RED4ext/Scripting/Natives/Generated/appearance/AppearanceDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/appearance/AppearanceResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/community/CommunityTemplateData.hpp>
#include <RED4ext/Scripting/Natives/Generated/community/SpawnEntry.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/ComponentsStorage.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/Entity.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/EntityID.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/EntityInstanceData.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/EntityParameter.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/EntityParametersStorage.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/EntityTemplate.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/GarmentSkinnedMeshComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/IComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/ITransformBinding.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/MeshComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/MorphTargetManagerComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/MorphTargetSkinnedMeshComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/SkinnedMeshComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/SlotComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/VisualControllerComponent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/VisualTagsSchema.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/dismemberment/EffectResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/dismemberment/WoundConfigContainer.hpp>
#include <RED4ext/Scripting/Natives/Generated/ent/dismemberment/WoundResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ComponentPS.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/DeviceBase.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/EntityStubComponentPS.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/GameTagSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/HitRepresentationOverride.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/HitShapeUserData.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ICommunitySystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IContainerManager.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IDynamicEntityIDSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IEntitySpawnerEventsBroadcaster.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IEntityStubSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IGameSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IHitShape.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IJournalManager.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IPersistencySystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/IPopulationSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalEntry.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalEntryState.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalManager.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalNotifyOption.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalPath.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalPointOfInterestMappin.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/JournalRequestContext.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/Object.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/PersistentID.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/PersistentState.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/PuppetBase.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ResetContainerEvent.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ScriptableSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/VehicleSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/WardrobeSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/WorkspotGameSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/District.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/MappinPhase.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/MappinVariant.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/data/SpawnableObject_Record.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/mappins/IMappin.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/mappins/IMappinSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/mappins/MappinSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/mappins/PhaseVariant.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ui/CustomizationAppearance.hpp>
#include <RED4ext/Scripting/Natives/Generated/game/ui/GameSystemUI.hpp>
#include <RED4ext/Scripting/Natives/Generated/graph/GraphConnectionDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/graph/GraphDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/graph/GraphNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/graph/GraphSocketDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/CharacterEvent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/CompoundWidget.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/ControllerProcessor.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/HUDLayer.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/HudWidgetSpawnEntry.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/IEffect.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/ISystemRequestsHandler.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/IWidgetComponentWrapper.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/IWidgetController.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/ImageWidget.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/InputEvent.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/Layer.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/LayerProxy.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/MultiChildren.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/PropertyManager.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/SpawningProcessor.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/StyleResourceWrapper.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/UserData.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/VirtualWindow.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/Widget.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLibraryItemInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLibraryResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLibraryResourceWrapper.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetLogicController.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WidgetReference.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WorldLayer.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/WorldWidgetInfos.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/anim/Definition.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/anim/Event.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/anim/Interpolator.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/anim/Processor.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/anim/Sequence.hpp>
#include <RED4ext/Scripting/Natives/Generated/ink/anim/SequenceTargetInfo.hpp>
#include <RED4ext/Scripting/Natives/Generated/localization/PersistenceOnScreenEntries.hpp>
#include <RED4ext/Scripting/Natives/Generated/mesh/MeshAppearance.hpp>
#include <RED4ext/Scripting/Natives/Generated/mesh/MeshParameter.hpp>
#include <RED4ext/Scripting/Natives/Generated/net/PeerID.hpp>
#include <RED4ext/Scripting/Natives/Generated/physics/TraceResult.hpp>
#include <RED4ext/Scripting/Natives/Generated/population/PopulationSpawnParameter.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/CharacterCondition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/CharacterKilled_ConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/CharacterSpawned_ConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/CommunityTemplate_NodeType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/ComparisonParam.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/ConditionNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/EventManagerNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/FactsDBCondition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/FactsDBManagerNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/GraphDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/ICharacterConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/IObjectConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/IQuestsSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/InputNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/Interaction_ConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/Inventory_ConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/JournalChangeMappinPhase_NodeType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/JournalCondition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/JournalEntryState_ConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/JournalEntry_ConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/JournalEntry_NodeType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/JournalNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/NodeLoadingCondition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/ObjectCondition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/PauseConditionNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/PhaseInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/PhaseNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/QuestPhaseResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/SetVar_NodeType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/ShowWorldNode_NodeType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/SocketDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/SpawnManagerNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/SpawnSet_NodeType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/Spawner_NodeType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/TogglePrefabVariant_NodeType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/TriggerCondition.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/UniversalRef.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/VarComparison_ConditionType.hpp>
#include <RED4ext/Scripting/Natives/Generated/quest/WorldDataManagerNodeDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/red/ResourceReferenceScriptToken.hpp>
#include <RED4ext/Scripting/Natives/Generated/red/TagSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/vehicle/BaseObject.hpp>
#include <RED4ext/Scripting/Natives/Generated/vehicle/Controller.hpp>
#include <RED4ext/Scripting/Natives/Generated/vehicle/ELightMode.hpp>
#include <RED4ext/Scripting/Natives/Generated/vehicle/ELightType.hpp>
#include <RED4ext/Scripting/Natives/Generated/vehicle/GarageVehicleID.hpp>
#include <RED4ext/Scripting/Natives/Generated/work/WorkEntryId.hpp>
#include <RED4ext/Scripting/Natives/Generated/work/WorkspotInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/work/WorkspotResource.hpp>
#include <RED4ext/Scripting/Natives/Generated/work/WorkspotSystem.hpp>
#include <RED4ext/Scripting/Natives/Generated/work/WorkspotTree.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/CommunityRegistryItem.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/EnvironmentAreaParameters.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/EnvironmentDefinition.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/GlobalNodeID.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/INodeInstance.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/Node.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/RuntimeEntityRegistry.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/RuntimeSystemEntity.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/RuntimeSystemWeather.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/StreamingSector.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/WeatherScriptInterface.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/WeatherState.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/WeatherStateTransition.hpp>
#include <RED4ext/Scripting/Natives/Generated/world/ui/WorldLayerWidget.hpp>
#include <RED4ext/Scripting/Natives/ScriptGameInstance.hpp>

#include <clip.h>
#include <nameof.hpp>
#include <semver.hpp>

#include "Core/Raw.hpp"
#include "Core/Stl.hpp"

#include "Red/Alias.hpp"
#include "Red/Engine.hpp"
#include "Red/Specializations.hpp"
#include "Red/TypeInfo.hpp"
#include "Red/Utils.hpp"

#include "Red/Addresses/Library.hpp"
