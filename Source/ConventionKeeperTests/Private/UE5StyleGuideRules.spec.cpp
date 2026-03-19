// Pavel Penkov 2025 All Rights Reserved.

#include "AssetRegistry/AssetData.h"
#include "Misc/AutomationTest.h"
#include "Rules/ConventionKeeperRule_AssetNaming.h"

#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AIController.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AimOffset.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimBlueprint.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimComposite.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimMontage.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimSequence.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_AnimatedVectorField.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BehaviorTree.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Blackboard.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlendSpace.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Blueprint.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintComponent.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintInterface.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTDecorator.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTService.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_BTTask.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CameraAnim.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CurveColor.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CurveFloat.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CurveTable.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_CurveVector.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DataTable.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DestructibleMesh.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DialogueVoice.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_DialogueWave.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Enumeration.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_EnvQuery.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_EnvQueryContext.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_FoliageType.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ForceFeedbackEffect.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Font.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LandscapeGrassType.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LandscapeLayer.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LevelSequence.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialFunction.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialInstance.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MaterialParameterCollection.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MatineeData.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MediaPlayer.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MediaSoundWave.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_MorphTarget.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ObjectLibrary.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PaperFlipbook.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ParticleSystem.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PhysicalMaterial.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_PhysicsAsset.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_ReverbEffect.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SkeletalMesh.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_StaticMesh.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_LevelMap.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SlateBrush.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SlateWidgetStyle.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundAttenuation.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundConcurrency.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundCue.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundMix.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SoundWave.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Sprite.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SpriteAtlasGroup.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_StaticVectorField.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_Structure.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_SubsurfaceProfile.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_TileMap.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_TileSet.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_TouchInterface.h"
#include "UE5StyleGuideConvention/Rules/UE5StyleGuideRule_AssetNaming_WidgetBlueprint.h"

#if WITH_DEV_AUTOMATION_TESTS

static FAssetData MakeSyntheticAssetData(const FString& PackagePath, const FString& AssetName, const FString& ClassPath)
{
	const FString LongPackageName = PackagePath.StartsWith(TEXT("/")) ? PackagePath : (TEXT("/Game/") + PackagePath);
	const FString ObjectPath = LongPackageName + TEXT(".") + AssetName;
	const FTopLevelAssetPath ClassPathTop = FTopLevelAssetPath(ClassPath);
	return FAssetData(LongPackageName, ObjectPath, ClassPathTop, FAssetDataTagMap(), TArrayView<const int32>(), 0u);
}

static void TestNamingRule(FAutomationTestBase* Test, UConventionKeeperRule_AssetNaming* Rule,
	const FString& ClassPath, const FString& BadName, const FString& GoodName, const FString& ExpectedPrefix)
{
	Test->TestNotNull(TEXT("Rule created"), Rule);
	if (!Rule) return;
	TMap<FString, FString> Placeholders;
	bool bValid = true;
	FString ExpectedPrefixOut;
	FAssetData Bad = MakeSyntheticAssetData(TEXT("/Game/Test/") + BadName, BadName, ClassPath);
	Rule->EvaluateSingleAssetNaming(Bad, Placeholders, bValid, &ExpectedPrefixOut, nullptr);
	Test->TestFalse(TEXT("Bad name must be invalid"), bValid);
	Test->TestEqual(TEXT("Expected prefix"), ExpectedPrefixOut, ExpectedPrefix);
	FAssetData Good = MakeSyntheticAssetData(TEXT("/Game/Test/") + GoodName, GoodName, ClassPath);
	Rule->EvaluateSingleAssetNaming(Good, Placeholders, bValid, nullptr, nullptr);
	Test->TestTrue(TEXT("Good name must be valid"), bValid);
}

BEGIN_DEFINE_SPEC(UE5StyleGuideRulesSpec,
	"ConventionKeeper.UE5StyleGuideRules",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(UE5StyleGuideRulesSpec)

void UE5StyleGuideRulesSpec::Define()
{
	Describe("UE5 Style Guide asset naming rules (EvaluateSingleAssetNaming)", [this]()
	{
		It("DataTable: DT_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_DataTable>(GetTransientPackage()),
				TEXT("/Script/Engine.DataTable"), TEXT("MyTable"), TEXT("DT_MyTable"), TEXT("DT_"));
		});
		It("AnimatedVectorField: VFA_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_AnimatedVectorField>(GetTransientPackage()),
				TEXT("/Script/Engine.VectorFieldAnimated"), TEXT("Wind"), TEXT("VFA_Wind"), TEXT("VFA_"));
		});
		It("StaticVectorField: VF_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_StaticVectorField>(GetTransientPackage()),
				TEXT("/Script/Engine.VectorFieldStatic"), TEXT("Vortex"), TEXT("VF_Vortex"), TEXT("VF_"));
		});
		It("CameraAnim: CA_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_CameraAnim>(GetTransientPackage()),
				TEXT("/Script/Engine.CameraAnim"), TEXT("Shake"), TEXT("CA_Shake"), TEXT("CA_"));
		});
		It("ObjectLibrary: OL_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_ObjectLibrary>(GetTransientPackage()),
				TEXT("/Script/Engine.ObjectLibrary"), TEXT("Weapons"), TEXT("OL_Weapons"), TEXT("OL_"));
		});
		It("LandscapeGrassType: LG_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_LandscapeGrassType>(GetTransientPackage()),
				TEXT("/Script/Landscape.LandscapeGrassType"), TEXT("Grass"), TEXT("LG_Grass"), TEXT("LG_"));
		});
		It("LandscapeLayer: LL_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_LandscapeLayer>(GetTransientPackage()),
				TEXT("/Script/Landscape.LandscapeLayerInfoObject"), TEXT("Rock"), TEXT("LL_Rock"), TEXT("LL_"));
		});
		It("MatineeData: Matinee_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_MatineeData>(GetTransientPackage()),
				TEXT("/Script/Engine.InterpData"), TEXT("Intro"), TEXT("Matinee_Intro"), TEXT("Matinee_"));
		});
		It("TouchInterface: TI_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_TouchInterface>(GetTransientPackage()),
				TEXT("/Script/Engine.TouchInterface"), TEXT("Mobile"), TEXT("TI_Mobile"), TEXT("TI_"));
		});
		It("FoliageType: FT_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_FoliageType>(GetTransientPackage()),
				TEXT("/Script/Foliage.FoliageType_InstancedStaticMesh"), TEXT("Tree"), TEXT("FT_Tree"), TEXT("FT_"));
		});
		It("ForceFeedbackEffect: FFE_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_ForceFeedbackEffect>(GetTransientPackage()),
				TEXT("/Script/Engine.ForceFeedbackEffect"), TEXT("Rumble"), TEXT("FFE_Rumble"), TEXT("FFE_"));
		});
		It("MediaPlayer: MP_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_MediaPlayer>(GetTransientPackage()),
				TEXT("/Script/MediaAssets.MediaPlayer"), TEXT("Video"), TEXT("MP_Video"), TEXT("MP_"));
		});
		It("MediaSoundWave: MSW_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_MediaSoundWave>(GetTransientPackage()),
				TEXT("/Script/MediaAssets.MediaSoundWave"), TEXT("Stream"), TEXT("MSW_Stream"), TEXT("MSW_"));
		});
		It("CurveFloat: Curve_ prefix and _Float suffix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_CurveFloat>(GetTransientPackage()),
				TEXT("/Script/Engine.CurveFloat"), TEXT("Alpha"), TEXT("Curve_Alpha_Float"), TEXT("Curve_"));
		});
		It("CurveColor: Curve_ prefix and _Color suffix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_CurveColor>(GetTransientPackage()),
				TEXT("/Script/Engine.CurveLinearColor"), TEXT("Tint"), TEXT("Curve_Tint_Color"), TEXT("Curve_"));
		});
		It("CurveVector: Curve_ prefix and _Vector suffix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_CurveVector>(GetTransientPackage()),
				TEXT("/Script/Engine.CurveVector"), TEXT("Path"), TEXT("Curve_Path_Vector"), TEXT("Curve_"));
		});
		It("CurveTable: Curve_ prefix and _Table suffix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_CurveTable>(GetTransientPackage()),
				TEXT("/Script/Engine.CurveTable"), TEXT("Damage"), TEXT("Curve_Damage_Table"), TEXT("Curve_"));
		});
		It("ReverbEffect: Reverb_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_ReverbEffect>(GetTransientPackage()),
				TEXT("/Script/Engine.ReverbEffect"), TEXT("Cave"), TEXT("Reverb_Cave"), TEXT("Reverb_"));
		});
		It("SoundMix: Mix_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SoundMix>(GetTransientPackage()),
				TEXT("/Script/Engine.SoundMix"), TEXT("Master"), TEXT("Mix_Master"), TEXT("Mix_"));
		});
		It("SoundAttenuation: ATT_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SoundAttenuation>(GetTransientPackage()),
				TEXT("/Script/Engine.SoundAttenuation"), TEXT("Indoor"), TEXT("ATT_Indoor"), TEXT("ATT_"));
		});
		It("DialogueVoice: DV_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_DialogueVoice>(GetTransientPackage()),
				TEXT("/Script/Engine.DialogueVoice"), TEXT("Hero"), TEXT("DV_Hero"), TEXT("DV_"));
		});
		It("DialogueWave: DW_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_DialogueWave>(GetTransientPackage()),
				TEXT("/Script/Engine.DialogueWave"), TEXT("Line"), TEXT("DW_Line"), TEXT("DW_"));
		});
		It("SoundCue: A_ prefix and _Cue suffix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SoundCue>(GetTransientPackage()),
				TEXT("/Script/Engine.SoundCue"), TEXT("Explosion"), TEXT("A_Explosion_Cue"), TEXT("A_"));
		});
		It("SoundConcurrency: _SC suffix only", [this]()
		{
			UUE5StyleGuideRule_AssetNaming_SoundConcurrency* Rule = NewObject<UUE5StyleGuideRule_AssetNaming_SoundConcurrency>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule) return;
			TMap<FString, FString> Placeholders;
			bool bValid = true;
			FAssetData Bad = MakeSyntheticAssetData(TEXT("/Game/Test/Master"), TEXT("Master"), TEXT("/Script/Engine.SoundConcurrency"));
			Rule->EvaluateSingleAssetNaming(Bad, Placeholders, bValid, nullptr, nullptr);
			TestFalse(TEXT("Missing _SC invalid"), bValid);
			FAssetData Good = MakeSyntheticAssetData(TEXT("/Game/Test/Master_SC"), TEXT("Master_SC"), TEXT("/Script/Engine.SoundConcurrency"));
			Rule->EvaluateSingleAssetNaming(Good, Placeholders, bValid, nullptr, nullptr);
			TestTrue(TEXT("Master_SC valid"), bValid);
		});
		It("MaterialInstance: MI_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_MaterialInstance>(GetTransientPackage()),
				TEXT("/Script/Engine.MaterialInstanceConstant"), TEXT("Concrete"), TEXT("MI_Concrete"), TEXT("MI_"));
		});
		It("MaterialFunction: MF_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_MaterialFunction>(GetTransientPackage()),
				TEXT("/Script/Engine.MaterialFunction"), TEXT("Noise"), TEXT("MF_Noise"), TEXT("MF_"));
		});
		It("MaterialParameterCollection: MPC_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_MaterialParameterCollection>(GetTransientPackage()),
				TEXT("/Script/Engine.MaterialParameterCollection"), TEXT("Global"), TEXT("MPC_Global"), TEXT("MPC_"));
		});
		It("SubsurfaceProfile: SP_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SubsurfaceProfile>(GetTransientPackage()),
				TEXT("/Script/Engine.SubsurfaceProfile"), TEXT("Skin"), TEXT("SP_Skin"), TEXT("SP_"));
		});
		It("PhysicalMaterial: PM_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_PhysicalMaterial>(GetTransientPackage()),
				TEXT("/Script/Engine.PhysicalMaterial"), TEXT("Metal"), TEXT("PM_Metal"), TEXT("PM_"));
		});
		It("PhysicsAsset: PHYS_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_PhysicsAsset>(GetTransientPackage()),
				TEXT("/Script/Engine.PhysicsAsset"), TEXT("Character"), TEXT("PHYS_Character"), TEXT("PHYS_"));
		});
		It("SkeletalMesh: SK_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SkeletalMesh>(GetTransientPackage()),
				TEXT("/Script/Engine.SkeletalMesh"), TEXT("Hero"), TEXT("SK_Hero"), TEXT("SK_"));
		});
		It("StaticMesh: S_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_StaticMesh>(GetTransientPackage()),
				TEXT("/Script/Engine.StaticMesh"), TEXT("Rock"), TEXT("S_Rock"), TEXT("S_"));
		});
		It("LevelMap: no prefix, optional suffix _P/_Audio/_Lighting/_Geo/_Gameplay", [this]()
		{
			UConventionKeeperRule_AssetNaming* Rule = NewObject<UUE5StyleGuideRule_AssetNaming_LevelMap>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule) return;
			TMap<FString, FString> Placeholders;
			bool bValid = true;
			FString ExpectedPrefixOut;
			FAssetData Bad = MakeSyntheticAssetData(TEXT("/Game/Test/Maps/Level_Foo"), TEXT("Level_Foo"), TEXT("/Script/Engine.World"));
			Rule->EvaluateSingleAssetNaming(Bad, Placeholders, bValid, &ExpectedPrefixOut, nullptr);
			TestFalse(TEXT("Level_Foo must be invalid (bad suffix)"), bValid);
			FAssetData Good = MakeSyntheticAssetData(TEXT("/Game/Test/Maps/MainLevel"), TEXT("MainLevel"), TEXT("/Script/Engine.World"));
			Rule->EvaluateSingleAssetNaming(Good, Placeholders, bValid, nullptr, nullptr);
			TestTrue(TEXT("MainLevel must be valid"), bValid);
			FAssetData GoodSuffix = MakeSyntheticAssetData(TEXT("/Game/Test/Maps/Campaign_P"), TEXT("Campaign_P"), TEXT("/Script/Engine.World"));
			Rule->EvaluateSingleAssetNaming(GoodSuffix, Placeholders, bValid, nullptr, nullptr);
			TestTrue(TEXT("Campaign_P must be valid"), bValid);
		});
		It("LevelSequence: LS_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_LevelSequence>(GetTransientPackage()),
				TEXT("/Script/LevelSequence.LevelSequence"), TEXT("Intro"), TEXT("LS_Intro"), TEXT("LS_"));
		});
		It("AnimSequence: A_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_AnimSequence>(GetTransientPackage()),
				TEXT("/Script/Engine.AnimSequence"), TEXT("Idle"), TEXT("A_Idle"), TEXT("A_"));
		});
		It("AnimMontage: AM_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_AnimMontage>(GetTransientPackage()),
				TEXT("/Script/Engine.AnimMontage"), TEXT("Attack"), TEXT("AM_Attack"), TEXT("AM_"));
		});
		It("AnimBlueprint: ABP_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_AnimBlueprint>(GetTransientPackage()),
				TEXT("/Script/Engine.AnimBlueprint"), TEXT("Character"), TEXT("ABP_Character"), TEXT("ABP_"));
		});
		It("BlendSpace: BS_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BlendSpace>(GetTransientPackage()),
				TEXT("/Script/Engine.BlendSpace"), TEXT("Locomotion"), TEXT("BS_Locomotion"), TEXT("BS_"));
		});
		It("AimOffset: AO_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_AimOffset>(GetTransientPackage()),
				TEXT("/Script/Engine.AimOffset"), TEXT("Rifle"), TEXT("AO_Rifle"), TEXT("AO_"));
		});
		It("AnimComposite: AC_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_AnimComposite>(GetTransientPackage()),
				TEXT("/Script/Engine.AnimComposite"), TEXT("Combo"), TEXT("AC_Combo"), TEXT("AC_"));
		});
		It("MorphTarget: MT_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_MorphTarget>(GetTransientPackage()),
				TEXT("/Script/Engine.MorphTarget"), TEXT("Smile"), TEXT("MT_Smile"), TEXT("MT_"));
		});
		It("PaperFlipbook: PFB_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_PaperFlipbook>(GetTransientPackage()),
				TEXT("/Script/Paper2D.PaperFlipbook"), TEXT("Character"), TEXT("PFB_Character"), TEXT("PFB_"));
		});
		It("Sprite: SPR_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_Sprite>(GetTransientPackage()),
				TEXT("/Script/Paper2D.PaperSprite"), TEXT("Icon"), TEXT("SPR_Icon"), TEXT("SPR_"));
		});
		It("SpriteAtlasGroup: SPRG_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SpriteAtlasGroup>(GetTransientPackage()),
				TEXT("/Script/Paper2D.PaperSpriteAtlas"), TEXT("UI"), TEXT("SPRG_UI"), TEXT("SPRG_"));
		});
		It("TileMap: TM_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_TileMap>(GetTransientPackage()),
				TEXT("/Script/Paper2D.PaperTileMap"), TEXT("Level"), TEXT("TM_Level"), TEXT("TM_"));
		});
		It("TileSet: TS_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_TileSet>(GetTransientPackage()),
				TEXT("/Script/Paper2D.PaperTileSet"), TEXT("Tiles"), TEXT("TS_Tiles"), TEXT("TS_"));
		});
		It("Font: Font_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_Font>(GetTransientPackage()),
				TEXT("/Script/Engine.Font"), TEXT("Main"), TEXT("Font_Main"), TEXT("Font_"));
		});
		It("SlateBrush: Brush_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SlateBrush>(GetTransientPackage()),
				TEXT("/Script/SlateCore.SlateBrushAsset"), TEXT("Button"), TEXT("Brush_Button"), TEXT("Brush_"));
		});
		It("SlateWidgetStyle: Style_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SlateWidgetStyle>(GetTransientPackage()),
				TEXT("/Script/SlateCore.SlateWidgetStyleAsset"), TEXT("Button"), TEXT("Style_Button"), TEXT("Style_"));
		});
		It("WidgetBlueprint: WBP_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_WidgetBlueprint>(GetTransientPackage()),
				TEXT("/Script/UMG.UserWidgetBlueprint"), TEXT("HUD"), TEXT("WBP_HUD"), TEXT("WBP_"));
		});
		It("Blueprint: BP_ or TBP_ prefix", [this]()
		{
			UUE5StyleGuideRule_AssetNaming_Blueprint* Rule = NewObject<UUE5StyleGuideRule_AssetNaming_Blueprint>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule) return;
			TMap<FString, FString> Placeholders;
			bool bValid = true;
			FString ExpectedPrefixOut;
			FAssetData Bad = MakeSyntheticAssetData(TEXT("/Game/Test/MyActor"), TEXT("MyActor"), TEXT("/Script/Engine.Blueprint"));
			Rule->EvaluateSingleAssetNaming(Bad, Placeholders, bValid, &ExpectedPrefixOut, nullptr);
			TestFalse(TEXT("Bad name invalid"), bValid);
			FAssetData Good = MakeSyntheticAssetData(TEXT("/Game/Test/BP_MyActor"), TEXT("BP_MyActor"), TEXT("/Script/Engine.Blueprint"));
			Rule->EvaluateSingleAssetNaming(Good, Placeholders, bValid, nullptr, nullptr);
			TestTrue(TEXT("BP_ valid"), bValid);
		});
		It("BlueprintComponent: BP_ prefix and Component suffix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BlueprintComponent>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("Thing"), TEXT("BP_InventoryComponent"), TEXT("BP_"));
		});
		It("BlueprintFunctionLibrary: BPFL_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BlueprintFunctionLibrary>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("Helpers"), TEXT("BPFL_Helpers"), TEXT("BPFL_"));
		});
		It("BlueprintInterface: BPI_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BlueprintInterface>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("Interactable"), TEXT("BPI_Interactable"), TEXT("BPI_"));
		});
		It("BlueprintMacroLibrary: BPML_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BlueprintMacroLibrary>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("Macros"), TEXT("BPML_Macros"), TEXT("BPML_"));
		});
		It("AIController: AIC_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_AIController>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("Enemy"), TEXT("AIC_Enemy"), TEXT("AIC_"));
		});
		It("Blackboard: BB_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_Blackboard>(GetTransientPackage()),
				TEXT("/Script/AIModule.BlackboardData"), TEXT("AI"), TEXT("BB_AI"), TEXT("BB_"));
		});
		It("BehaviorTree: BT_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BehaviorTree>(GetTransientPackage()),
				TEXT("/Script/AIModule.BehaviorTree"), TEXT("Patrol"), TEXT("BT_Patrol"), TEXT("BT_"));
		});
		It("BTTask: BTTask_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BTTask>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("MoveTo"), TEXT("BTTask_MoveTo"), TEXT("BTTask_"));
		});
		It("BTDecorator: BTDecorator_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BTDecorator>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("Cooldown"), TEXT("BTDecorator_Cooldown"), TEXT("BTDecorator_"));
		});
		It("BTService: BTService_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_BTService>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("Sense"), TEXT("BTService_Sense"), TEXT("BTService_"));
		});
		It("EnvQuery: EQS_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_EnvQuery>(GetTransientPackage()),
				TEXT("/Script/AIModule.EnvQuery"), TEXT("FindCover"), TEXT("EQS_FindCover"), TEXT("EQS_"));
		});
		It("EnvQueryContext: EQS_ prefix and Context suffix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_EnvQueryContext>(GetTransientPackage()),
				TEXT("/Script/Engine.Blueprint"), TEXT("Item"), TEXT("EQS_ItemContext"), TEXT("EQS_"));
		});
		It("Enumeration: E prefix (no underscore)", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_Enumeration>(GetTransientPackage()),
				TEXT("/Script/Engine.UserDefinedEnum"), TEXT("MyEnum"), TEXT("EMyEnum"), TEXT("E"));
		});
		It("Structure: F or S prefix", [this]()
		{
			UUE5StyleGuideRule_AssetNaming_Structure* Rule = NewObject<UUE5StyleGuideRule_AssetNaming_Structure>(GetTransientPackage());
			TestNotNull(TEXT("Rule created"), Rule);
			if (!Rule) return;
			TMap<FString, FString> Placeholders;
			bool bValid = true;
			FAssetData Bad = MakeSyntheticAssetData(TEXT("/Game/Test/MyStruct"), TEXT("MyStruct"), TEXT("/Script/Engine.UserDefinedStruct"));
			Rule->EvaluateSingleAssetNaming(Bad, Placeholders, bValid, nullptr, nullptr);
			TestFalse(TEXT("No prefix invalid"), bValid);
			FAssetData GoodF = MakeSyntheticAssetData(TEXT("/Game/Test/FMyStruct"), TEXT("FMyStruct"), TEXT("/Script/Engine.UserDefinedStruct"));
			Rule->EvaluateSingleAssetNaming(GoodF, Placeholders, bValid, nullptr, nullptr);
			TestTrue(TEXT("F prefix valid"), bValid);
			FAssetData GoodS = MakeSyntheticAssetData(TEXT("/Game/Test/SMyStruct"), TEXT("SMyStruct"), TEXT("/Script/Engine.UserDefinedStruct"));
			Rule->EvaluateSingleAssetNaming(GoodS, Placeholders, bValid, nullptr, nullptr);
			TestTrue(TEXT("S prefix valid"), bValid);
		});
		It("SoundWave: A_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_SoundWave>(GetTransientPackage()),
				TEXT("/Script/Engine.SoundWave"), TEXT("Footstep"), TEXT("A_Footstep"), TEXT("A_"));
		});
		It("DestructibleMesh: DM_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_DestructibleMesh>(GetTransientPackage()),
				TEXT("/Script/ApexDestruction.DestructibleMesh"), TEXT("Barrel"), TEXT("DM_Barrel"), TEXT("DM_"));
		});
		It("ParticleSystem: PS_ prefix", [this]()
		{
			TestNamingRule(this, NewObject<UUE5StyleGuideRule_AssetNaming_ParticleSystem>(GetTransientPackage()),
				TEXT("/Script/Niagara.NiagaraSystem"), TEXT("Explosion"), TEXT("PS_Explosion"), TEXT("PS_"));
		});
	});
}

#endif // WITH_DEV_AUTOMATION_TESTS
