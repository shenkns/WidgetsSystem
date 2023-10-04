// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"

#include "WidgetsSystemInterface.generated.h"

class UWidgetAnimation;

USTRUCT(BlueprintType)
struct WIDGETSSYSTEM_API FWidgetsSystemAnimation
{
	GENERATED_BODY()

	FWidgetsSystemAnimation() {}

	FWidgetsSystemAnimation(UWidgetAnimation* WidgetAnimation, bool AnimationReverse = false) : Animation(WidgetAnimation), Reverse(AnimationReverse) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetAnimation")
	UWidgetAnimation* Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetAnimation")
	bool Reverse;
};

UINTERFACE()
class UWidgetsSystemInterface : public UInterface
{
	GENERATED_BODY()
};

class WIDGETSSYSTEM_API IWidgetsSystemInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = "WidgetsSystem|Animations")
	FWidgetsSystemAnimation GetWidgetOpenAnimation() const;

	UFUNCTION(BlueprintNativeEvent, Category = "WidgetsSystem|Animations")
	FWidgetsSystemAnimation GetWidgetCloseAnimation() const;

	UFUNCTION(BlueprintNativeEvent, Category = "WidgetsSystem|State")
	bool IsWidgetLocked() const;

	UFUNCTION(BlueprintNativeEvent, Category = "WidgetsSystem|State")
	void WidgetStartOpening();

	UFUNCTION(BlueprintNativeEvent, Category = "WidgetsSystem|State")
	void WidgetOpened();

	UFUNCTION(BlueprintNativeEvent, Category = "WidgetsSystem|State")
	void WidgetStartClosing();

	UFUNCTION(BlueprintNativeEvent, Category = "WidgetsSystem|State")
	void WidgetClosed();
};
