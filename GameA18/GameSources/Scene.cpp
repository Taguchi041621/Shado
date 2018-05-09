
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses() {
		wstring DataDir;
		//サンプルのためアセットディレクトリを取得
		//App::GetApp()->GetAssetsDirectory(DataDir);
		//各ゲームは以下のようにデータディレクトリを取得すべき
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"Oreng.png";
		App::GetApp()->RegisterTexture(L"Oreng_TX", strTexture);
		strTexture = DataDir + L"Title.jpg";
		App::GetApp()->RegisterTexture(L"TITLE_TX", strTexture);
		strTexture = DataDir + L"Select.png";
		App::GetApp()->RegisterTexture(L"SELECT_TX", strTexture);
		strTexture = DataDir + L"Clear.png";
		App::GetApp()->RegisterTexture(L"CLEAR_TX", strTexture);
		strTexture = DataDir + L"GameOver.png";
		App::GetApp()->RegisterTexture(L"GAMEOVER_TX", strTexture);
		strTexture = DataDir + L"WallTexture.png";
		App::GetApp()->RegisterTexture(L"WallTexture_TX", strTexture);
		strTexture = DataDir + L"Red.tga";
		App::GetApp()->RegisterTexture(L"Red_TX", strTexture);
	}

	void Scene::OnCreate() {
		try {
			//リソース作成
			CreateResourses();
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToStageSelect") {
			ResetActiveStage<StageSelect>();
		}
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToGameOver") {
			ResetActiveStage<GameOverStage>();
		}
		else if (event->m_MsgStr == L"ToClearStage") {
			ResetActiveStage<ClearStage>();
		}
	}


}
//end basecross
