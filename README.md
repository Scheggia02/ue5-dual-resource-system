# ue5-dual-resource-system
Modular UE5 ability system with dual resource (mana - health) architecture and extensible execution pipeline.

## Source overview

- `ADRSCharacter` owns the DRS ability system component, character attribute set, and resource execution component. When possessed, it loads a `UDRSCharacterConfigData` primary data asset to grant default abilities and apply default attributes.
- `ADRSPlayerCharacter` adds the third-person camera setup and Enhanced Input bindings. Ability inputs are routed through gameplay tags so input actions can activate matching granted abilities.
- `UDRSAbilitySystemComponent` extends Unreal's Gameplay Ability System component with helpers for granting ability data assets, handling gameplay-tag input triggers, and applying attribute initialization effects.
- `UDRSCharacterAttributeSet` defines the current character resources: health, mana, and their regeneration-rate attributes.
- `UDRSGameplayAbilityData` describes a grantable ability class, ability level, and optional input tag. `UDRSCharacterConfigData` groups the default abilities and default attribute Gameplay Effect for a character.
- `UDRSInputConfig` maps Enhanced Input actions to gameplay tags used by the ability activation flow.
- `UDRSResourceExecutionComponent` is the extension point for future resource spending, regeneration, or execution rules.

## Ability input flow

1. Configure input gameplay tags in `DRSGameplayTags` and map them to Enhanced Input actions in a `UDRSInputConfig` asset.
2. Assign ability data assets in a `UDRSCharacterConfigData` asset.
3. When a character is possessed, the config asset is loaded and its default abilities are granted.
4. Each granted ability stores its configured input tag in the gameplay ability spec's dynamic source tags.
5. When an input action triggers, `ADRSPlayerCharacter` forwards the gameplay tag to `UDRSAbilitySystemComponent`, which activates granted abilities with an exact matching tag.

