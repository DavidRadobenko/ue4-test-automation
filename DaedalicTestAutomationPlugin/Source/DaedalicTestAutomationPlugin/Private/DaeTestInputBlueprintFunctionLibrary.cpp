#include "DaeTestInputBlueprintFunctionLibrary.h"
#include "DaeTestLogCategory.h"
#include <InputCoreTypes.h>
#include <GameFramework/InputSettings.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerInput.h>
#include <Kismet/GameplayStatics.h>

void UDaeTestInputBlueprintFunctionLibrary::ApplyInputAction(
    UObject* Context, const FName& ActionName,
    EInputEvent InputEventType /*= EInputEvent::IE_Pressed*/)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);

    const UInputSettings* InputSettings = GetDefault<UInputSettings>();

    for (const FInputActionKeyMapping& Mapping : InputSettings->GetActionMappings())
    {
        if (Mapping.ActionName == ActionName)
        {
            PlayerController->InputKey(Mapping.Key, InputEventType, 0.0f, false);
            return;
        }
    }

    UE_LOG(LogDaeTest, Error, TEXT("%s - Input action not found: %s"),
           IsValid(Context) ? *Context->GetName() : TEXT(""), *ActionName.ToString());
}

void UDaeTestInputBlueprintFunctionLibrary::ApplyInputAxis(UObject* Context, const FName& AxisName,
                                                           float AxisValue /*= 1.0f*/)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);

    const UInputSettings* InputSettings = GetDefault<UInputSettings>();

    for (const FInputAxisKeyMapping& Mapping : InputSettings->GetAxisMappings())
    {
        if (Mapping.AxisName == AxisName)
        {
            PlayerController->InputAxis(Mapping.Key, AxisValue, 0.0f, 1, false);
            return;
        }
    }

    UE_LOG(LogDaeTest, Error, TEXT("%s - Input axis not found: %s"),
           IsValid(Context) ? *Context->GetName() : TEXT(""), *AxisName.ToString());
}

void UDaeTestInputBlueprintFunctionLibrary::ApplyInputTouch(UObject* Context, EDaeTouchType InTouchType, FVector2D Position)
{
    // FViewportClient* Client = GEngine->GameViewport->Viewport->GetClient();
    
    
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);
    
    ETouchType::Type TouchType = ETouchType::Stationary;
    
    switch (InTouchType)
    {
        case EDaeTouchType::Began:
        {
            TouchType = ETouchType::Began;
        }
        case EDaeTouchType::Ended:
        {
            TouchType = ETouchType::Ended;
        }
    }

    // Client->InputTouch(GEngine->GameViewport->Viewport, 0,0, TouchType, Position, 1.0f, FDateTime::Now(), 0);
    
    PlayerController->InputTouch(0, TouchType, Position, 1.0f, FDateTime::Now(), 0);
}

void UDaeTestInputBlueprintFunctionLibrary::ApplyInputClick(UObject* Context, FVector2D Position)
{
    FViewportClient* Client = GEngine->GameViewport->Viewport->GetClient();
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);

    PlayerController->SetMouseLocation(Position.X, Position.Y);
    Client->InputKey(GEngine->GameViewport->Viewport,0,EKeys::LeftMouseButton, EInputEvent::IE_Pressed);
    
    // PlayerController->InputKey(EKeys::LeftMouseButton, EInputEvent::IE_Pressed, 0.0f, false);
}
