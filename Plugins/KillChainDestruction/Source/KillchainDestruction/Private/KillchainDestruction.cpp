// Copyright Epic Games, Inc. All Rights Reserved.

#include "KillchainDestruction.h"

#include "GameplayTagsManager.h"

#define LOCTEXT_NAMESPACE "FKillchainDestructionModule"

void FKillchainDestructionModule::StartupModule()
{
	const FString PluginFolder = FPaths::Combine(FPaths::ProjectPluginsDir(), "KillchainDestruction");
	
	UGameplayTagsManager::Get().AddTagIniSearchPath(PluginFolder / TEXT("Config"));
}

void FKillchainDestructionModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FKillchainDestructionModule, KillchainDestruction)