// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

using UnrealBuildTool;

public class WidgetsSystem : ModuleRules
{
	public WidgetsSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;
		
		PrivateIncludePaths.AddRange(
			new string[] 
			{
				"WidgetsSystem/"
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UMG",
				"LogSystem",
				"ManagersSystem",
				"DataSystem"
			}
		);
		
		PrivateIncludePathModuleNames.AddRange(
			new string[]
			{
				"LogSystem",
				"ManagersSystem",
				"DataSystem"
			}
		);
	}
}