// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetsManagerComponent.h"

#include "Animation/UMGSequencePlayer.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/WidgetsSystemInterface.h"
#include "Kismet/GameplayStatics.h"

UWidgetsManagerComponent::UWidgetsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UUserWidget* UWidgetsManagerComponent::OpenWidget(UUserWidget* Widget, EWidgetOpenMethod OpenMethod, int ZOrder, bool Instant)
{
	if(IsLocked()) return nullptr;
	
	if(!Widget) return nullptr;

	auto OpenLambda = [this, Instant, Widget, ZOrder]()
	{
		WidgetsHistory.Add(FWidgetHistory(Widget, ZOrder));

		if(Widget->GetClass()->ImplementsInterface(UWidgetsSystemInterface::StaticClass()))
		{
			IWidgetsSystemInterface::Execute_WidgetStartOpening(Widget);
			Widget->AddToViewport(ZOrder);

			const FWidgetsSystemAnimation OpenAnimation = IWidgetsSystemInterface::Execute_GetWidgetOpenAnimation(Widget);
			if(OpenAnimation.Animation && !Instant)
			{
				PlayingTransition = true;
				Widget->PlayAnimation(
					OpenAnimation.Animation,
					0.f,
					1,
					OpenAnimation.Reverse ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward
				)->OnSequenceFinishedPlaying().AddWeakLambda(this, [this, Widget](UUMGSequencePlayer& UMGSequencePlayer)
				{
					PlayingTransition = false;

					IWidgetsSystemInterface::Execute_WidgetOpened(Widget);
				});
			}
			else
			{
				IWidgetsSystemInterface::Execute_WidgetOpened(Widget);
			}
		}
		else
		{
			Widget->AddToViewport(ZOrder);
		}
	};
	
	switch(OpenMethod)
	{
	case EWidgetOpenMethod::ClearHistory:
		{
			for(const FWidgetHistory& OldWidget : WidgetsHistory)
			{
				if(OldWidget.Widget)
				{
					OldWidget.Widget->RemoveFromParent();
				}
			}

			WidgetsHistory.Empty();
			
			break;
		}
		
	case EWidgetOpenMethod::HideAll:
		{
			for(const FWidgetHistory& OldWidget : WidgetsHistory)
			{
				if(OldWidget.Widget)
				{
					OldWidget.Widget->RemoveFromParent();
				}
			}

			break;
		}

	case EWidgetOpenMethod::HidePrevious:
		{
			if(UUserWidget* PreviousWidget = GetCurrentWidget())
			{
				PreviousWidget->RemoveFromParent();
			}

			break;
		}
	}

	OpenLambda();
	
	return Widget;
}

UUserWidget* UWidgetsManagerComponent::OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, EWidgetOpenMethod OpenMethod, int ZOrder, bool Instant)
{
	if(IsLocked()) return nullptr;
	
	if(!IsValid(Class)) return nullptr;
	
	if(UUserWidget* Widget = CreateWidget<UUserWidget, UWorld*>(GetWorld(), Class, FName(FGuid::NewGuid().ToString())))
	{
		return OpenWidget(Widget, OpenMethod, ZOrder, Instant);
	}

	return nullptr;
}

UUserWidget* UWidgetsManagerComponent::Back(bool Instant)
{
	if(IsLocked()) return nullptr;
	
	if(WidgetsHistory.Num() <= 1) return nullptr;

	const FWidgetHistory OpenedPreviousElement = WidgetsHistory.Last(1);

	auto OpenPreviousLambda = [this, Instant, OpenedPreviousElement]()
	{
		UUserWidget* OpenedWidget = OpenedPreviousElement.Widget;
		if(!OpenedWidget) return;

		if(OpenedWidget->IsInViewport()) return;

		if(OpenedWidget->GetClass()->ImplementsInterface(UWidgetsSystemInterface::StaticClass()))
		{
			IWidgetsSystemInterface::Execute_WidgetStartOpening(OpenedWidget);
			OpenedWidget->AddToViewport(OpenedPreviousElement.ZOrder);

			const FWidgetsSystemAnimation OpenAnimation = IWidgetsSystemInterface::Execute_GetWidgetOpenAnimation(OpenedWidget);
			if(OpenAnimation.Animation && !Instant)
			{
				PlayingTransition = true;
				
				OpenedWidget->PlayAnimation(
					OpenAnimation.Animation,
					0.f,
					1,
					OpenAnimation.Reverse ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward
				)->OnSequenceFinishedPlaying().AddWeakLambda(this, [this, OpenedWidget](UUMGSequencePlayer& UMGSequencePlayer)
				{
					PlayingTransition = false;
					
					IWidgetsSystemInterface::Execute_WidgetOpened(OpenedWidget);
				});
			}
			else
			{
				IWidgetsSystemInterface::Execute_WidgetOpened(OpenedWidget);
			}
		}
		else
		{
			OpenedWidget->AddToViewport(OpenedPreviousElement.ZOrder);
		}
	};

	if(UUserWidget* CurrentWidget = GetCurrentWidget())
	{
		if(CurrentWidget->GetClass()->ImplementsInterface(UWidgetsSystemInterface::StaticClass()))
		{
			IWidgetsSystemInterface::Execute_WidgetStartClosing(CurrentWidget);

			const FWidgetsSystemAnimation CloseAnimation = IWidgetsSystemInterface::Execute_GetWidgetCloseAnimation(CurrentWidget);

			if(CloseAnimation.Animation && !Instant)
			{
				PlayingTransition = true;
				CurrentWidget->PlayAnimation(
					CloseAnimation.Animation,
					0.f,
					1,
					CloseAnimation.Reverse ? EUMGSequencePlayMode::Reverse : EUMGSequencePlayMode::Forward
				)->OnSequenceFinishedPlaying().AddWeakLambda(this, [this, CurrentWidget, OpenPreviousLambda](UUMGSequencePlayer& UUMGSequencePlayer)
				{
					PlayingTransition = false;

					WidgetsHistory.RemoveAt(WidgetsHistory.Num() - 1);
					CurrentWidget->RemoveFromParent();
					
					IWidgetsSystemInterface::Execute_WidgetClosed(CurrentWidget);
					
					OpenPreviousLambda();
				});

				return OpenedPreviousElement.Widget;
			}
			else
			{
				WidgetsHistory.RemoveAt(WidgetsHistory.Num() - 1);
				CurrentWidget->RemoveFromParent();
				
				IWidgetsSystemInterface::Execute_WidgetClosed(CurrentWidget);
			}
		}
		else
		{
			WidgetsHistory.RemoveAt(WidgetsHistory.Num() - 1);
			CurrentWidget->RemoveFromParent();
		}
	}

	OpenPreviousLambda();

	return OpenedPreviousElement.Widget;
}

UUserWidget* UWidgetsManagerComponent::GetCurrentWidget() const
{
	if(WidgetsHistory.Num() >= 1)
	{
		return WidgetsHistory.Last().Widget;
	}

	return nullptr;
}

bool UWidgetsManagerComponent::IsLocked() const
{
	if(PlayingTransition) return true;

	if(const UUserWidget* CurrentWidget = GetCurrentWidget())
	{
		if(CurrentWidget->GetClass()->ImplementsInterface(UWidgetsSystemInterface::StaticClass()))
		{
			return IWidgetsSystemInterface::Execute_IsWidgetLocked(CurrentWidget);
		}
	}

	return false;
}

void UWidgetsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	OpenWidgetFromClass(StartWidgetClass, EWidgetOpenMethod::ClearHistory, 0);
}
