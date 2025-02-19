#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STableRow.h"

struct FWeaponRowData
{
	int Number;
	FString Name;
	class UCWeaponAsset* Asset;

	FWeaponRowData()
	{

	}

	FWeaponRowData(int32 InNumber, FString InName, class UCWeaponAsset* InAsset)
		: Number(InNumber), Name(InName), Asset(InAsset)
	{

	}

	static TSharedPtr<FWeaponRowData> Make(int32 InNumber, FString InName, class UCWeaponAsset* InAsset)
	{
		return MakeShareable(new FWeaponRowData(InNumber, InName, InAsset));
	}
};
typedef TSharedPtr<FWeaponRowData> FWeaponRowDataPtr;

///////////////////////////////////////////////////////////////////////////////

class WEAPON_API SWeaponTableRow
	: public SMultiColumnTableRow<FWeaponRowDataPtr>
{
public:
	SLATE_BEGIN_ARGS(SWeaponTableRow) {	}
	SLATE_ARGUMENT(FWeaponRowDataPtr, RowData)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable);

protected:
	TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;
	
private:
	FWeaponRowDataPtr Data;
};

///////////////////////////////////////////////////////////////////////////////

DECLARE_DELEGATE_OneParam(FOnWeaponListViewSelectedItem, FWeaponRowDataPtr);

class WEAPON_API SWeaponLeftArea
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWeaponLeftArea) {}
	SLATE_EVENT(FOnWeaponListViewSelectedItem, OnSelectedItem)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

public:
	bool HasRowDataPtr() { return RowDatas.Num() > 0; }
	FWeaponRowDataPtr GetFirstDataPtr() { return RowDatas[0]; }

	void SelectDataPtr(class UCWeaponAsset* InAsset);

	FWeaponRowDataPtr GetRowDataPtrByName(FString InAssetName);
	FString SelectedRowDataPtrName();

private:
	TSharedRef<ITableRow> OnGenerateRow(FWeaponRowDataPtr InRow, const TSharedRef<STableViewBase>& InTable);
	void OnSelectionChanged(FWeaponRowDataPtr InDataPtr, ESelectInfo::Type InType);

	FText OnGetAssetCount() const;

	void OnTextChanged(const FText& InText);
	void OnTextCommitted(const FText& InText, ETextCommit::Type InType);

private:
	void ReadDataAssetList();

private:
	FOnWeaponListViewSelectedItem OnListViewSelectedItem;

private:
	TArray<FWeaponRowDataPtr> RowDatas;
	TSharedPtr<SListView<FWeaponRowDataPtr>> ListView;

private:
	TSharedPtr<class SSearchBox> SearchBox;
	FText SearchText;
};
