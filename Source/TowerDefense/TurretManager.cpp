#include "TurretManager.h"
#include "F_TurretObjectPath.h"

ATurretManager::ATurretManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurretManager::BeginPlay()
{
	Super::BeginPlay();

	if (turretDataTable) 
	{
		dataTableRowNames = turretDataTable->GetRowNames();

		int amount = 0;
		for (auto element : dataTableRowNames)
		{
			amount++;
		}
		UE_LOG(LogTemp, Warning, TEXT("Elemets in DataTable = %d"), amount);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Data Table Within - %s"), *this->GetName());
	}
}

// Called every frame
void ATurretManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ATurretStatic* ATurretManager::SpawnTurretByRow(int rowIndex, FVector spawnLoc, FRotator spawnRot)
{
	UE_LOG(LogTemp, Warning, TEXT("Row Index from SpawnTurretByRow Function within %s = %d"), *this->GetName(), rowIndex);
	int index = rowIndex - 2;
	if (!dataTableRowNames.IsValidIndex(index))
	{
		UE_LOG(LogTemp, Warning, TEXT("Index %d out of range (0 to %d)"), rowIndex, dataTableRowNames.Num() - 1);
		return nullptr;
	}
	FName rowName = dataTableRowNames[index];

	F_TurretObjectPath* rowData = turretDataTable->FindRow<F_TurretObjectPath>(rowName, TEXT("Getting Data Table Row"));

	UClass* turretClass = rowData->turretClass.LoadSynchronous();

	FActorSpawnParameters spawnParams;

	ATurretStatic* spawnedTurret = GetWorld()->SpawnActor<ATurretStatic>(turretClass, spawnLoc, spawnRot, spawnParams);

	return spawnedTurret;
}

