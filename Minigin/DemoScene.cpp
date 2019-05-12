#include "MiniginPCH.h"
#include "DemoScene.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "RenderComponent.h"
#include "ContentManager.h"

dae::DemoScene::DemoScene(const std::string& name)
	:Scene(name)
{
}

void dae::DemoScene::SetupScene()
{
	auto go = std::make_shared<GameObject>();
	auto rendercomp = std::make_shared<RenderComponent>();
	rendercomp->SetTexture("background.jpg");
	go->AddComponent(rendercomp);
	Add(go);

	go = std::make_shared<GameObject>();
	rendercomp = std::make_shared<RenderComponent>();
	rendercomp->SetTexture("logo.png");
	go->AddComponent(rendercomp);
	go->SetPosition(216, 180);
	Add(go);

	auto font = ContentManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComp = std::make_shared<GameObject>();
	auto to = std::make_shared<TextRenderComponent>("Programming 4 Assignment", font);
	textComp->SetPosition(80, 20);
	textComp->AddComponent(to);
	Add(textComp);
}
