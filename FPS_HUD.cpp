// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_HUD.h"

void AFPS_HUD::DrawHUD()
{
    Super::DrawHUD();
    
    if (CrossHairTexture)
    {
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        FVector2D CrossHairPosition(Center.X - (CrossHairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrossHairTexture->GetSurfaceHeight() * 0.5f));

        FCanvasTileItem TileItem(CrossHairPosition, CrossHairTexture->Resource, FLinearColor::White);

        TileItem.BlendMode = SE_BLEND_Translucent;

        Canvas->DrawItem(TileItem);
    }
}