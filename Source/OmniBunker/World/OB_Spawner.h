// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_Spawner.generated.h"

class UBoxComponent;
class AOB_InteractableActor;

UCLASS()
class OMNIBUNKER_API AOB_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AOB_Spawner();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnItem();

protected:
	virtual void BeginPlay() override;

	// Items to spawn
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Spawn|Data")
	TArray<TSubclassOf<AOB_InteractableActor>> PossibleItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UBoxComponent> SpawnZone;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Spawn")
	bool bSpawnOnBeginPlay = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn", meta = (ClampMin = "1"))
    int32 MinSpawnCount = 1;

    // Максимальное количество предметов для спавна (если = MinSpawnCount, заспавнится ровно N)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn", meta = (ClampMin = "1"))
    int32 MaxSpawnCount = 1;

	TSubclassOf<AOB_InteractableActor> GetRandomItemClass() const;
	FVector GetRandomPointInZone() const;
};
