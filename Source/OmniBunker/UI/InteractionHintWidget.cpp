// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "InteractionHintWidget.h"

void UInteractionHintWidget::PlayAppearAnim(const bool bPlayReverse) {
	PlayAnimation(
		AppearAnim, 
		0.f, 
		1, 
		bPlayReverse ? 
			EUMGSequencePlayMode::Reverse : 
			EUMGSequencePlayMode::Forward,
		1.f
	);
}

void UInteractionHintWidget::PlayClickAnim() {
	PlayAnimation(
		ClickAnim,
		0.f, 
		1, 
		EUMGSequencePlayMode::Forward,
		1.f
	);
}
