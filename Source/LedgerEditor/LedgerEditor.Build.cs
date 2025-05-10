using UnrealBuildTool;

public class LedgerEditor : ModuleRules
{
    public LedgerEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", 
                "GraphEditor",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "BlueprintGraph",
                "CoreUObject",
                "EditorStyle",
                "Engine",
                "InputCore",
                "Kismet",
                "KismetCompiler",
                "UnrealEd",
                "Slate",
                "SlateCore",
                "PropertyEditor",
                "Ledger",
                "DataValidation",
            }
        );
    }
}