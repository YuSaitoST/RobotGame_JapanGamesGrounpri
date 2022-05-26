#include "DomeRender.h"
#include "_Classes_Yu/_LoadCSV/LoadCSV.h"

void DomeRender::LoadAsset() {
	CSV::Schan(L"_Parameters\\DomesPosition.csv", numberOfDome_, posList_);
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"_Models_Field\\_Dome\\dome.x");
}

void DomeRender::Render() {
	for(int i = 0; i < numberOfDome_; ++i) {
		model_->SetPosition(posList_[i]);
		model_->Draw();
	};
}