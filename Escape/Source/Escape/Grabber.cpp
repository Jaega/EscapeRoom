// Copyright Xinzhao Li 2019

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::Grab(){
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));

	// LINE TRACE and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();
	// if we hit something then attach a physics handle
	// TODO attach physics handle
}

void UGrabber::Release(){
	UE_LOG(LogTemp, Warning, TEXT("Grab released!"));
	// TODO release physics handle
}

/// Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent(){
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle){
		
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s  missing physics handle component!"), *(GetOwner()->GetName()));
	}
}
/// Look for attached input component (only at run time)
void UGrabber::SetupInputComponent(){
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(PhysicsHandle){
		UE_LOG(LogTemp, Warning, TEXT("Input component found!"));
		// Bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s  missing input component!"), *(GetOwner()->GetName()));
	}
}

void UGrabber::GetFirstPhysicsBodyInReach(){
	/// Get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);
	/*UE_LOG(LogTemp,Warning,TEXT("Location: %s, Rotation: %s"), 
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointRotator.ToString()
	);*/

	FVector LineTraceDirection = PlayerViewPointRotation.Vector();
	FVector LineTraceEnd = PlayerViewPointLocation + LineTraceDirection * Reach;

	/*/// Draw a red trace in the world viewpoint
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);*/

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	/// See what we hit
	AActor* ActorHit = Hit.GetActor();
	if(ActorHit){
		UE_LOG(LogTemp, Warning, TEXT("Hitting: %s"), *(ActorHit->GetName()));
	}
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
		// move the object we are holding
	

	
	
}

