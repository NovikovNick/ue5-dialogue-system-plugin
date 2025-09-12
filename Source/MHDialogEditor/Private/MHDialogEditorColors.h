// created by MetalHeart

#pragma once

#include "Math/Color.h"

namespace MH::Dialog::Private::Colors
{
namespace Asset
{
const FLinearColor Default(FColor::Magenta);
const FLinearColor WorldCentricTabColorScale(FColor::Red);
}  // namespace Asset
namespace Node
{
namespace Title
{
const FLinearColor Default(FColor::Magenta);
}
namespace Border
{
const FLinearColor Default(0.08f, 0.08f, 0.08f);
}
namespace Body
{
const FLinearColor Default(0.15f, 0.15f, 0.15f);
}
namespace Pin
{
const FLinearColor Default(0.02f, 0.02f, 0.02f);
const FLinearColor Hover(1.0f, 0.7f, 0.0f);
}  // namespace Pin
}  // namespace Node
}  // namespace MH::Dialog::Private::Colors