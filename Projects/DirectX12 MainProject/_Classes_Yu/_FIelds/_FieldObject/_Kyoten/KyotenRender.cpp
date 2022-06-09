#include "KyotenRender.h"
#include "_Classes_Yu/_LoadCSV/LoadCSV.h"
#include "_Classes_Yu/_FIelds/_FieldObject/FieldsObjectMaterial.h"

void KyotenRender::LoadAsset() {
	CSV::Schan(L"_Parameters\\_FieldObject\\KyotensPosition.csv", numberOfDome_, posList_);
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models_Field\\_Kyoten\\kyoten.x");
	model_->SetMaterial(FieldsObjectMaterial::Normal);
}

void KyotenRender::Render() {
	for(int i = 0; i < numberOfDome_; ++i) {
		model_->SetPosition(posList_[i]);
		model_->Draw();
	};
}