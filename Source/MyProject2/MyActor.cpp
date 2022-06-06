// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TextRendererBilboard = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextNickName"));

	TextRendererBilboard->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->MakeTextFacePlayer();
}

void AMyActor::MakeTextFacePlayer() const
{
	// find current possessed player
	ACharacter* Player = GetWorld()->GetFirstPlayerController()->GetCharacter();

	if (!Player)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Could not Find player"));
	else
	{
		FVector PlayerPosition = Player->GetActorLocation();

		// calculate rotation
		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), PlayerPosition);
		// apply rotation to 'look' at the current player
		TextRendererBilboard->SetWorldRotation(Rotator);
	}
}
