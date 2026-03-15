// Pavel Penkov 2025 All Rights Reserved.

#include "Rules/ConventionKeeperRule_NamingConvention_PascalCase.h"

#include "Misc/Char.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ConventionKeeperRule_NamingConvention_PascalCase)

UConventionKeeperRule_NamingConvention_PascalCase::UConventionKeeperRule_NamingConvention_PascalCase()
{
	RuleId = FName(TEXT("naming-convention-pascalcase"));
	DescriptionKey = FName(TEXT("RuleDesc_naming-convention-pascalcase"));
	Description = FText::FromString(TEXT("Folder and asset names must be PascalCase (each segment after underscore: leading uppercase, rest alphanumeric)."));
	FolderPathPattern = FDirectoryPath(TEXT("Content/{ProjectName}"));
}

bool UConventionKeeperRule_NamingConvention_PascalCase::IsPascalCaseName(const FString& Name)
{
	if (Name.IsEmpty())
	{
		return false;
	}
	TArray<FString> Segments;
	Name.ParseIntoArray(Segments, TEXT("_"), true);
	for (const FString& Segment : Segments)
	{
		if (Segment.IsEmpty())
		{
			return false;
		}
		if (!FChar::IsUpper(Segment[0]))
		{
			return false;
		}
		for (int32 i = 1; i < Segment.Len(); ++i)
		{
			const TCHAR C = Segment[i];
			if (!FChar::IsDigit(C) && !FChar::IsLower(C) && !FChar::IsUpper(C))
			{
				return false;
			}
		}
	}
	return true;
}

bool UConventionKeeperRule_NamingConvention_PascalCase::IsNameValidForFolder_Implementation(const FString& Name) const
{
	return IsPascalCaseName(Name);
}

bool UConventionKeeperRule_NamingConvention_PascalCase::IsNameValidForAsset_Implementation(const FString& Name) const
{
	return IsPascalCaseName(Name);
}
