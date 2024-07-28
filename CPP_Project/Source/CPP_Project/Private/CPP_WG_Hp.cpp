// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WG_Hp.h"

void UCPP_WG_Hp::SetHpBar(float hp, float maxHp)
{
	this->PB_HpBar->SetPercent(hp / maxHp);
}
