#include "SmartGames/BDI/Belief/SG_Belief.h"

float FSG_Belief::Evaluate() const
{
	const float Min = Range.GetLowerBoundValue();
	const float Max = Range.GetUpperBoundValue();
	const float Val = FMath::Clamp(Value, Min, Max);
	return (FMath::IsNearlyEqual(Min,Max)) ? 0.0f : (Val - Min) / (Max - Min);
}
