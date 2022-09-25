// remnants of the past.All Rights Reserved.


#include "UI/Class_HUD.h"

#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void AClass_HUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrossHair();
}

void AClass_HUD::BeginPlay()
{
	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void AClass_HUD::DrawCrossHair()
{

	const TInterval<float>Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
	const float HalfLineSize = 5.0f;
	const float LineThinkers = 1.5f;
	const FLinearColor LineColor = FLinearColor::Blue;
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThinkers);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThinkers);
}