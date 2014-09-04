#include "Entities\Base_Ent.h"

Base_Ent::Base_Ent(int entnumber)
	:	mEntNumber(entnumber)
{
}
Base_Ent::~Base_Ent()
{
}
int Base_Ent::GetEntityNumber()
{
	return mEntNumber;
}