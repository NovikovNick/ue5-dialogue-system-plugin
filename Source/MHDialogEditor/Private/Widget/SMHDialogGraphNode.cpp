// created by MetalHeart

#include "Widget/SMHDialogGraphNode.h"

#include "Graph/MHDialogGraphNode.h"
#include "MHDialogEditorColors.h"
#include "Widgets/Text/SMultiLineEditableText.h"

namespace MH::Dialog::Private
{

void SMHDialogGraphNode::Construct(const FArguments& InArgs, UMHDialogGraphNode* InNode)
{
	SetCursor(EMouseCursor::CardinalCross);

	GraphNode = InNode;
	UpdateGraphNode();
}

void SMHDialogGraphNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const FMargin NodePadding = FMargin(15.0f, 5.0f);

	// clang-format off
	ContentScale.Bind(this, &SGraphNode::GetContentScale );
	GetOrAddSlot(ENodeZone::Center)
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Center)
	[
		SNew(SBorder)
		.BorderImage( FAppStyle::GetBrush( "Graph.StateNode.Body" ) )
		.Padding(0)
		.BorderBackgroundColor( this, &SMHDialogGraphNode::GetBorderBackgroundColor )
		[
			SNew(SOverlay)
			// Pins and node details
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				// INPUT PIN AREA
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBox)
					.MinDesiredHeight(NodePadding.Top)
					[
						SAssignNew(LeftNodeBox, SVerticalBox)
					]
				]
				// STATE NAME AREA
				+SVerticalBox::Slot()
				.Padding(FMargin(NodePadding.Left, 0.0f, NodePadding.Right, 0.0f))
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBorder)
							.BorderImage( FAppStyle::GetBrush("Graph.StateNode.Body") )
							.BorderBackgroundColor( this, &SMHDialogGraphNode::GetBackgroundColor )
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Visibility(EVisibility::SelfHitTestInvisible)
							[
								SNew(SVerticalBox)
								+SVerticalBox::Slot()
								.AutoHeight()
								[
									SNew(SHorizontalBox)
									+SHorizontalBox::Slot()
									.Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
									[
										SNew(SVerticalBox)
										+SVerticalBox::Slot()
										.AutoHeight()
										[
											SNew(SMultiLineEditableText)
											.WrapTextAt(400.0f)
											.TextStyle(FAppStyle::Get(), "Graph.StateNode.NodeTitle")
											.OnTextCommitted(this, &SMHDialogGraphNode::OnNameTextCommited)
											.Text(this, &SMHDialogGraphNode::GetTitle)
										]
										+SVerticalBox::Slot()
										.AutoHeight()
										[
											SNew(SNodeTitle, GraphNode)
										]
									]
								]
								+SVerticalBox::Slot()
								.AutoHeight()
								[
									// DESCRIPTION MESSAGE
									SNew(STextBlock )
									.Text(FText::FromString("..."))
								]
							]
						]
					]
				]
				// OUTPUT PIN AREA
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SBox)
					.MinDesiredHeight(NodePadding.Bottom)
					[
						SAssignNew(RightNodeBox, SVerticalBox)
					]
				]
			]
		]
	];
	// clang-format on

	CreatePinWidgets();
}

FSlateColor SMHDialogGraphNode::GetBorderBackgroundColor() const
{
	return FSlateColor(MH::Dialog::Private::Colors::Node::Border::Default);
}

FSlateColor SMHDialogGraphNode::GetBackgroundColor() const
{
	return FSlateColor(MH::Dialog::Private::Colors::Node::Body::Default);
}

}  // namespace MH::Dialog::Private
