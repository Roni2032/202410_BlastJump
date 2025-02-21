/*!
@file Sprite.h
@brief �X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	struct SpriteAnimation {
		int m_OrderCount;
		float m_AnimationTime;
		float m_UpdateInterval;
		bool m_IsLoop;
		bool m_IsReverse;

		vector<int> m_Order;
		void EndAnimation() {
			if (m_IsReverse) {
				m_OrderCount = m_Order.size() - 1;
			}
			else {
				m_OrderCount = 0;
			}
		}
		SpriteAnimation() {
			m_Order = {};
			m_OrderCount = 0;
			m_AnimationTime = 0;
			m_UpdateInterval = 0;
			m_IsLoop = false;
			m_IsReverse = false;
		}
		SpriteAnimation(vector<int> order, float time, float interval, const bool isLoop = false, const bool isReverse = false){
			m_Order = order;
			m_OrderCount = 0;
			m_AnimationTime = time;
			m_UpdateInterval = interval;
			m_IsLoop = isLoop;
			m_IsReverse = isReverse;
		}

		SpriteAnimation(int startOrder,int endOrder,float time,float interval,const bool isLoop = false,const bool isReverse = false){
			vector<int> order;
			for (int i = startOrder;i <= endOrder;i++) {
				order.push_back(i);
			}
			m_Order = order;
			m_OrderCount = 0;
			m_AnimationTime = time;
			m_UpdateInterval = interval;
			m_IsLoop = isLoop;
			m_IsReverse = isReverse;
		}
	};
	//----------------------------------------------------------
	//
	//	�摜�\���N���X						
	//																																
	//----------------------------------------------------------
	class Sprite : public GameObject {
		//�e�N�X�`���L�[
		wstring m_TexKey;
		//�T�C�Y
		Vec2 m_Size;
		//�ʒu
		Vec3 m_Pos;
		//�\����𒆐S�ɂ��邩
		bool m_IsUseCenterSprite;
		//�A�j���[�V���������邩
		bool m_IsAnimation;
		//�A�j���[�V�����؂�ւ�����
		float m_AnimationChangeTime;
		//�A�j���[�V�����؂�ւ����Ԍv��
		float m_AnimationTimer;
		//�g�p����A�j���[�V�����̃R�}��
		int m_UseIndex;
		//���݂̃R�}
		int m_Index;
		//�摜�̐؂��萔
		Vec2 m_cutUV;
		//�A�j���[�V������UV
		vector<vector<Vec2>> m_AnimationUV;
		//���_
		vector<VertexPositionColorTexture> m_Vertices;
		//�`��R���|�[�l���g
		shared_ptr<PCTSpriteDraw> m_Draw;
		//�ʒu�R���|�[�l���g
		shared_ptr<Transform> m_Transform;
		//�X�N���[���T�C�Y
		Vec2 m_ScreenSize;
		//�A�j���[�V�����}�b�v
		map<wstring, SpriteAnimation> m_Animations;
		//���݂̃A�j���[�V����
		SpriteAnimation m_CurrentAnimation;
		//�O�̃A�j���[�V����
		SpriteAnimation m_BeforeAnimation;

		//�A�j���[�V��������
		void Animation();
		void NewAnimation();
	public:
		Sprite(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,Vec2 size,const bool useCenter = false) : Sprite(ptr,texKey,pos,size,{1,1},useCenter,1,-1,false) {}
		Sprite(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec2 size, Vec2 cutUV, const bool useCenter = false, const float changeTime = 0.5f, const int useIndex = -1, const bool isAnimation = true) :
			GameObject(ptr),
			m_TexKey(texKey),
			m_Pos(pos), m_Size(size),
			m_cutUV(cutUV),
			m_IsUseCenterSprite(useCenter),
			m_Index(0), m_UseIndex(useIndex),
			m_IsAnimation(isAnimation),
			m_AnimationChangeTime(changeTime), m_AnimationTimer(0.0f),
			m_ScreenSize(0, 0)
			{}
		virtual ~Sprite(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		//�T�C�Y�̐؂�ւ�
		void UpdateSize(Vec3 size);
		void UpdateSize(Vec2 size);
		Vec2 GetSize() {
			return m_Size;
		}
		//�ʒu�̐؂�ւ�
		void SetPos(Vec3 pos);
		Vec3 GetPos() {
			return m_Pos;
		}
		
		void SetDiffuse(Col4 color);
		Col4 GetDiffuse();

		void CreateVertex(Vec2 size, vector<Vec2> uv);
		//----------------------------------------------------------
		//
		//	UV����		
		//																																
		//----------------------------------------------------------
		
		//UV�̐؂�ւ�
		void UpdateUV(vector<Vec2> uv);

		void CutAnimationUv(Vec2 cut);
		vector<vector<Vec2>> GetUvVec() {
			return m_AnimationUV;
		}
		vector<Vec2> GetUv(int index) {
			if (m_AnimationUV.size() <= index) {
				return {};
			}
			return m_AnimationUV[index];
		}

		//----------------------------------------------------------
		//
		//	�A�j���[�V��������		
		//																																
		//----------------------------------------------------------
		
		//�O�̃A�j���[�V�������擾
		SpriteAnimation GetBeforeAnimation() {
			return m_BeforeAnimation;
		}
		//���݂̃A�j���[�V�������擾
		SpriteAnimation GetCurrentAnimation() {
			return m_CurrentAnimation;
		}
		//�A�j���[�V�������擾
		SpriteAnimation GetAnimation(const wstring& key) {
			if (m_Animations.find(key) != m_Animations.end()) {
				return m_Animations[key];
			}
			return SpriteAnimation();
		}
		//�Đ�����A�j���[�V������ݒ�
		void SetCurrentAnimation(const wstring& key) {
			if (m_Animations.find(key) != m_Animations.end()) {
				m_CurrentAnimation.EndAnimation();
				m_BeforeAnimation = m_CurrentAnimation;
				m_CurrentAnimation = m_Animations[key];
			}
		}
		//�A�j���[�V������ǉ�
		void AddAnimation(const wstring& key, int startOrder, int endOrder, float time, float interval, const bool isLoop = false, const bool isReverse = false) {
			SpriteAnimation animation = SpriteAnimation(startOrder, endOrder, time, interval, isLoop, isReverse);
			m_Animations.insert(pair<wstring, SpriteAnimation>(key, animation));
		}
		void AddAnimation(const wstring& key, vector<int> order, float time, float interval, const bool isLoop = false, const bool isReverse = false) {
			SpriteAnimation animation = SpriteAnimation(order, time, interval, isLoop, isReverse);
			m_Animations.insert(pair<wstring, SpriteAnimation>(key, animation));
		}
		//�A�j���[�V���������X�V
		void UpdateAnimationData(const wstring& key, SpriteAnimation newAnimation) {
			if (m_Animations.find(key) != m_Animations.end()) {
				m_Animations[key] = newAnimation;
			}
		}
		//----------------------------------------------------------
		//
		//	�ʒu�ݒ�e���v���[�g		
		//																																
		//----------------------------------------------------------
		void ScreenCenter(const Vec2 diff = Vec2(0,0));
		void ScreenTop(const Vec2 diff = Vec2(0, 0));
		void ScreenTopLeft(const Vec2 diff = Vec2(0, 0));
		void ScreenTopRight(const Vec2 diff = Vec2(0, 0));
		void ScreenBottom(const Vec2 diff = Vec2(0, 0));
		void ScreenBottomLeft(const Vec2 diff = Vec2(0, 0));
		void ScreenBottomRight(const Vec2 diff = Vec2(0, 0));
		void ScreenLeft(const Vec2 diff = Vec2(0, 0));
		void ScreenRight(const Vec2 diff = Vec2(0, 0));
	};


	//----------------------------------------------------------
	//																																
	//	���l�\���N���X																												
	//																																
	//----------------------------------------------------------
	class BCNumber : public GameObject {
		vector<shared_ptr<Sprite>> m_Numbers;
		int m_CutNum;
		int m_DisplayNumber;
		int m_DisplayDigit;

		wstring m_TexKey;
		Vec3 m_Pos;
		Vec2 m_Size;

		vector<Vec2> GetUV(int displayDigit);
	public:
		BCNumber(const shared_ptr<Stage>& ptr,const wstring& texKey) : BCNumber(ptr,texKey,Vec3(0,0,0),Vec2(200,100),8){}
		BCNumber(const shared_ptr<Stage>& ptr,const wstring& texKey,Vec3 pos,Vec2 size,int displayDigit) : BCNumber(ptr, texKey, pos, size, displayDigit,10) {}
		BCNumber(const shared_ptr<Stage>& ptr, const wstring& texKey, Vec3 pos, Vec2 size, int displayDigit,int cutNum) : 
			GameObject(ptr) ,
			m_TexKey(texKey),
			m_Pos(pos),m_Size(size),
			m_DisplayDigit(displayDigit),m_DisplayNumber(1234), m_CutNum(cutNum)
		{}
		virtual ~BCNumber(){}

		virtual void OnCreate();
		virtual void OnUpdate();
		
		void UpdateNumber(int number);
		void SetActive(bool flag) {
			for (auto& number : m_Numbers) {
				number->SetDrawActive(flag);
			}
		}
	};

	//----------------------------------------------------------
	//																																
	//	Sprite����R���|�[�l���g�N���X
	// 
	//	< �g���� >
	//  AddComponent�Ŏg�������h���N���X��ݒ�
	//  Play() : �X�V
	//  Stop() : ��~																				
	//																																
	//----------------------------------------------------------
	class SpriteAction : public Component {
		bool m_IsPlay;
	protected:
		shared_ptr<SpriteBaseDraw> m_Draw;
		shared_ptr<Transform> m_Trans;
	public:
		SpriteAction(const shared_ptr<GameObject>& ptr) : Component(ptr),m_IsPlay(true){}
		virtual ~SpriteAction() {}

		virtual void OnCreate()override;
		virtual void OnDraw()override {}

		void Play() {
			m_IsPlay = true;
		}
		void Stop() {
			m_IsPlay = false;
		}

		bool IsPlay() {
			return m_IsPlay;
		}
	};
	//----------------------------------------------------------
	//																																
	//	Sprite���� : �_��																								
	//																																
	//----------------------------------------------------------
	class SpriteFlash : public SpriteAction {
		float m_FlashSpeed;
	public:
		SpriteFlash(const shared_ptr<GameObject>& ptr,float flashSpeed) : SpriteAction(ptr),
			m_FlashSpeed(flashSpeed){}
		virtual ~SpriteFlash(){}

		virtual void OnUpdate()override;

		void SetFlashSpeed(float flashSpeed) {
			m_FlashSpeed = flashSpeed;
		}

	};
	//----------------------------------------------------------
	//																																
	//	Sprite���� : �g��k��																								
	//																																
	//----------------------------------------------------------
	class SpriteScaling : public SpriteAction {
		float m_ScalingSpeed;
		Vec3 defaultSize;
		float m_Ratio;
		float m_MaxRatio;
		float m_MinRatio;

	public:
		SpriteScaling(const shared_ptr<GameObject>& ptr, float scalingSpeed, float max, float min) : SpriteAction(ptr), 
			m_ScalingSpeed(scalingSpeed), m_MaxRatio(max), m_MinRatio(min),defaultSize(0,0,0),m_Ratio(1.0f) {}
		virtual ~SpriteScaling() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetScalingSpeed(float scalingSpeed) {
			m_ScalingSpeed = scalingSpeed;
		}
		void SetMax(float max) {
			m_MaxRatio = max;
		}
		void SetMin(float min) {
			m_MinRatio = min;
		}

	};
	//----------------------------------------------------------
	//																																
	//	Sprite���� : �t�F�[�h�C���E�t�F�[�h�A�E�g																								
	//																																
	//----------------------------------------------------------
	class SpriteFade : public SpriteAction {
		float m_FadeSpeed;
		bool m_IsFadeOut;
		bool m_IsFinished;
	public:
		SpriteFade(const shared_ptr<GameObject>& ptr,float fadeSpeed) : SpriteAction(ptr),m_FadeSpeed(fadeSpeed),m_IsFadeOut(true),m_IsFinished(false){}
		virtual ~SpriteFade(){}

		virtual void OnUpdate()override;

		bool IsFadeOut() {
			return m_IsFadeOut;
		}
		void FadeOut() {
			m_IsFadeOut = true;
			m_IsFinished = false;
			m_Draw->SetDiffuse(Col4(1, 1, 1, 0));
		}
		void FadeIn() {
			m_IsFadeOut = false;
			m_IsFinished = false;
			m_Draw->SetDiffuse(Col4(1, 1, 1, 1));
		}
		bool IsFinish() {
			return m_IsFinished;
		}
	};
	//----------------------------------------------------------
	//																																
	//	�{�^��																		
	//																																
	//----------------------------------------------------------
	class SpriteButton : public SpriteAction {
		shared_ptr<SpriteBaseDraw> m_SpriteDraw;
		function<void(shared_ptr<Stage>&)> m_Function;
		function<void(shared_ptr<SpriteButton>&)> m_AddFunction;
		bool m_IsSelect;
		bool m_IsActive;
		wstring m_BelongGroup;

		vector<shared_ptr<Sprite>> m_FrontSprite;

		wstring m_UnSelectTexture;
		wstring m_SelectedTexture;
		Col4 m_UnSelectColor;
		Col4 m_SelectedColor;

		int m_GroupOrder;
		SpriteButton(shared_ptr<GameObject>& ptr, const wstring& defaultTexture, const wstring& group, const wstring& selectedTexture,Col4 selectedColor) :
			SpriteAction(ptr),
			m_BelongGroup(group),
			m_UnSelectTexture(defaultTexture),m_UnSelectColor(Col4()),
			m_SelectedTexture(selectedTexture), m_SelectedColor(selectedColor),
			m_IsSelect(false),m_IsActive(true),
			m_GroupOrder(0)
		{}
	public:

		SpriteButton(shared_ptr<GameObject>& ptr, const wstring& defaultTexture,const wstring& group,const wstring& selectedTexture) :
			SpriteButton(ptr,defaultTexture,group,selectedTexture,Col4(0,0,0,0))
		{}
		SpriteButton(shared_ptr<GameObject>& ptr, const wstring& defaultTexture, const wstring& group, Col4 selectedColor) :
			SpriteButton(ptr,defaultTexture,group,L"",selectedColor)
		{}
		virtual ~SpriteButton(){}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void AddFunction(function<void(shared_ptr<SpriteButton>&)> func) {
			m_AddFunction = func;
		}
		vector<shared_ptr<Sprite>> GetFrontSprite() {
			return m_FrontSprite;
		}
		shared_ptr<Sprite> GetFrontSprite(int index) {
			if (m_FrontSprite.size() <= index) {
				return nullptr;
			}
			return m_FrontSprite[index];
		}
		void AddFrontSprite(shared_ptr<Sprite>& sprite) {
			sprite->GetComponent<Transform>()->SetParent(GetGameObject());
			m_FrontSprite.push_back(sprite);
		}
		void SetFunction(function<void(shared_ptr<Stage>&)> func) {
			m_Function = func;
		}
		void Func() {
			m_Function(GetStage());
		}
		void Select() {
			m_IsSelect = true;
		}
		void UnSelect() {
			m_IsSelect = false;
		}
		void Open() {
			SetUpdateActive(true);
			m_SpriteDraw->SetDrawActive(true);
		}
		void Close() {
			SetUpdateActive(false);
			m_SpriteDraw->SetDrawActive(false);
			UnSelect();
		}
		void SetOrder(int order) {
			m_GroupOrder = order;
		}
		int GetOrder() {
			return m_GroupOrder;
		}
		void SetActive(bool flag) {
			m_IsActive = flag;
		}
		bool GetActive() {
			return m_IsActive;
		}
	};
	//----------------------------------------------------------
	//																																
	//	�{�^�����̓f�[�^																							
	//																																
	//----------------------------------------------------------
	struct InputData {
		int m_Input;
		int m_MoveAmount;

		InputData(int input,int amount) : m_Input(input),m_MoveAmount(amount){}
	};
	//----------------------------------------------------------
	//																																
	//	�{�^���p�}�l�[�W���[																							
	//																																
	//----------------------------------------------------------

	class ButtonManager : public GameObject{
		
		map<wstring, vector<shared_ptr<SpriteButton>>> m_ButtonGroup;
		map<wstring, int> m_SelectIndexes;
		map<wstring, Vec3> m_GroupMovementAmount;
		map<wstring, vector<InputData>> m_InputDates;

		wstring m_UsingGroup;

		wstring m_ClickSound;

		bool m_IsActive;

	public:
		static shared_ptr<ButtonManager> instance;

		ButtonManager(const shared_ptr<Stage>& ptr) : 
			GameObject(ptr),
			m_IsActive(true),m_UsingGroup(L""),m_ClickSound(L"")
		{}
		virtual ~ButtonManager(){}

		static shared_ptr<Sprite> Create(shared_ptr<Stage>& stage, const wstring& group, const wstring& defaultTex, const wstring& selectedTex, Vec3 pos, Vec2 size,function<void(shared_ptr<Stage>&)> func);
		static shared_ptr<Sprite> Create(shared_ptr<Stage>& stage, const wstring& group, const wstring& defaultTex, Col4 selectedColor, Vec3 pos, Vec2 size,function<void(shared_ptr<Stage>&)> func);
		shared_ptr<Sprite> Create(shared_ptr<Stage>& stage, const wstring& group, const wstring& defaultTex, const wstring& selectedTex,Col4 selectedColor, Vec3 pos, Vec2 size, function<void(shared_ptr<Stage>&)> func);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		int GetSize(const wstring& group) {
			if (m_InputDates.find(group) != end(m_InputDates)) {
				return m_ButtonGroup[group].size();
			}
			else {
				return 0;
			}
		}
		void SetMoveAmount(const wstring& group, Vec3 target);

		Vec3 GetMoveAmount(const wstring& group) {
			if (m_GroupMovementAmount.find(group) != end(m_GroupMovementAmount)) {
				return m_GroupMovementAmount[group];
			}
		}
		void SetSound(const wstring& sound);

		void SetInput(const wstring& group,int input,int amount) {
			SetInput(group, InputData(input, amount));
		}
		void SetInput(const wstring& group, InputData data) {
			if (m_InputDates.find(group) != end(m_InputDates)) {
				m_InputDates[group].push_back(data);
			}
			else {
				vector<InputData> dates = {};
				dates.push_back(data);
				m_InputDates.emplace(group, dates);
			}
		}
		void OpenAll() {
			for (auto& buttons : m_ButtonGroup) {
				Open(buttons.first);
			}
		}
		void CloseAll() {
			for (auto& buttons : m_ButtonGroup) {
				Close(buttons.first);
			}
			SetActive(false);
		}
		void OpenAndUse(const wstring& group) {
			Open(group);
			UseGroup(group);
		}
		void Open(const wstring& group) {
			if (m_ButtonGroup.find(group) != end(m_ButtonGroup)) {
				for (auto& button : m_ButtonGroup[group]) {
					button->Open();
				}
			}
			SetActive(true);
		}
		void Close(const wstring& group) {
			if (m_ButtonGroup.find(group) != end(m_ButtonGroup)) {
				for (auto& button : m_ButtonGroup[group]) {
					button->Close();
				}
				m_SelectIndexes[group] = 0;
			}
		}
		void SetActive(bool flag) {
			m_IsActive = flag;
		}
		bool GetActive() {
			return m_IsActive;
		}
		void LimitIndex() {
			int maxIndex = m_ButtonGroup[m_UsingGroup].size() - 1;
			int minIndex = 0;
			m_SelectIndexes[m_UsingGroup] = max(minIndex, m_SelectIndexes[m_UsingGroup]);
			m_SelectIndexes[m_UsingGroup] = min(maxIndex, m_SelectIndexes[m_UsingGroup]);
		}
		bool CheckOverIndex(int amount) {
			int index = m_SelectIndexes[m_UsingGroup];
			index += amount;
			if (index >= m_ButtonGroup[m_UsingGroup].size() || index < 0) {
				return false;
			}
			return true;
		}
		wstring GetUseGroup() {
			return m_UsingGroup;
		}
		void UseGroup(const wstring& group) {
			if (m_SelectIndexes.find(group) != end(m_SelectIndexes)) {
				m_SelectIndexes[m_UsingGroup] = 0;
				m_UsingGroup = group;
			}
		}
		bool CompareUseGroup(const wstring& group) {
			return m_UsingGroup == group;
		}
		void Register(const wstring& group, shared_ptr<SpriteButton>& button) {
			if (m_ButtonGroup.find(group) != end(m_ButtonGroup)) {
				m_ButtonGroup[group].push_back(button);
			}
			else {
				if (m_ButtonGroup.size() == 0) {
					m_UsingGroup = group;
				}
				vector<shared_ptr<SpriteButton>> buttons = {};
				buttons.push_back(button);
				m_ButtonGroup.emplace(group, buttons);
				m_SelectIndexes.emplace(group, 0);
				m_GroupMovementAmount.emplace(group, Vec3());
			}
			button->SetOrder(m_ButtonGroup[group].size() - 1);
		}
		void DeleteGroup(const wstring& group) {
			if (m_ButtonGroup.find(group) != end(m_ButtonGroup)) {
				m_ButtonGroup.erase(group);
				m_SelectIndexes.erase(group);
			}
		}

		void AddFrontSprite(const wstring& group,int index,shared_ptr<Sprite>& sprite) {
			if (m_ButtonGroup.find(group) != end(m_ButtonGroup)) {
				if (m_ButtonGroup[group].size() > index) {
					m_ButtonGroup[group][index]->AddFrontSprite(sprite);
				}
			}
		}
		void AddFunction(const wstring& group,function<void(shared_ptr<SpriteButton>&)> func) {
			if (m_ButtonGroup.find(group) != end(m_ButtonGroup)) {
				for (auto& buttons : m_ButtonGroup[group]) {
					buttons->AddFunction(func);
				}
			}
		}
		void AddFunction(const wstring& group,int index, function<void(shared_ptr<SpriteButton>&)> func) {
			if (m_ButtonGroup.find(group) != end(m_ButtonGroup)) {
				if (index < 0 || index >= m_ButtonGroup[group].size()) return;
				m_ButtonGroup[group][index]->AddFunction(func);
			}
		}
		
	};

	//----------------------------------------------------------
	//																																
	//	�|���p																					
	//																																
	//----------------------------------------------------------

	class Board : public GameObject {
		shared_ptr<PNTStaticDraw> m_Draw;
		shared_ptr<Transform> m_Trans;
		Vec3 m_StartPos;
		Vec3 m_Size;

		wstring m_TexKey;
	public:
		Board(shared_ptr<Stage>& ptr, const wstring& key,Vec3 pos, Vec3 size) : GameObject(ptr),m_TexKey(key), m_StartPos(pos), m_Size(size) {}
		virtual ~Board() {}

		virtual void OnCreate()override;
	};
}
//end basecross
