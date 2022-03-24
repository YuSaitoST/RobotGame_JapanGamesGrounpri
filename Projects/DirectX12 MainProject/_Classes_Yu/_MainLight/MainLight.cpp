#include "MainLight.h"

void MainLight::Setting(const char* name, D3DLIGHT9 light) {
	lightList_.push_back(*name);
	DXTK->Direct3D9->SetLight((lightList_.size() - 1), light);
}

void MainLight::SetEnable(const char* name, bool enable) {
	const std::vector<char>::iterator iter = std::find(std::begin(lightList_), std::end(lightList_), *name);
	const int index = std::distance(std::begin(lightList_), iter);
	DXTK->Direct3D9->LightEnable(index, enable);
}