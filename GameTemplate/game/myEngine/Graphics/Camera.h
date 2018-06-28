#pragma once

/*!
 *@brief	�J�����N���X�B
 */
class Camera {
private:
	D3DXMATRIX				viewMatrix;			//!<�r���[�s��B�J�����s��Ƃ������B
	D3DXMATRIX				projectionMatrix;	//!<�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
	D3DXVECTOR3				vEyePt;				//!<�J�����N���X����邽�߂̃q���g�B�J�����̎��_�B���̕ӂ�̓����o�ϐ��ɕύX����B
	D3DXVECTOR3				vLookatPt;			//!<�J�����N���X����邽�߂̃q���g�B�J�����̒����_�B�ǂ������Ă��邩�Ƃ������B���̕ӂ�̓����o�ϐ��ɕύX����B
	D3DXVECTOR3				vUpVec;				//!<�J�����N���X����邽�߂̃q���g�B�J�����̏�����B��{�I��Y�����ł��܂�Ȃ��B��{�I�ɂ́E�E�E�B���̕ӂ�̓����o�ϐ��ɕύX����B
	D3DXVECTOR3				vForward;			//!<�O�����B
	D3DXVECTOR3				vRight;				//!<�E�����B
	float					Far;				//!<�����ʁB
	float					Near;				//!<�ߕ��ʁB
	float					aspect;				//!<�A�X�y�N�g��
	float					angle;				//!<��p
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	Camera();
	/*!
	 *@brief	�f�X�g���N�^
	 */
	~Camera();
	/*!
	 *@brief	�A�X�y�N�g���ݒ�B
	 */
	void SetAspect(float _aspect);
	/*!
	 *@brief	�A�X�y�N�g����擾�B
	 */
	float GetAspect() const;
	/*!
	*@brief		��p��ݒ�B
	*/
	void SetAngle(float _angle);
	/*!
	*@brief		��p���擾�B
	*/
	float GetAngle() const;
	/*!
	 *@brief	�t�@�[��ݒ�B
	 */
	void SetFar(float _far);
	/*!
	 *@brief	�j�A���擾�B
	 */
	float GetNear() const;
	/*!
	 *@brief	�t�@�[���擾�B
	 */
	float GetFar() const;
	/*!
	 *@brief	�j�A��ݒ�B
	 */
	void SetNear(float _near);
	/*!
	 *@brief	���_��ݒ�B
	 */
	void SetEyePt(const D3DXVECTOR3& pt);
	/*!
	 *@brief	���_���擾�B
	 */
	const D3DXVECTOR3& GetEyePt() const;
	/*!
	 *@brief	�����_��ݒ�B
	 */
	void SetLookatPt(const D3DXVECTOR3& pt);
	/*!
	 *@brief	�����_�̎擾�B
	 */
	const D3DXVECTOR3& GetLookatPt() const;
	/*!
	*@brief		�O�����̐ݒ�B
	*/
	void SetForwardVec(const D3DXVECTOR3& forward);
	/*!
	*@brief		�O�����̎擾�B
	*/
	const D3DXVECTOR3& GetForwardVec() const;
	/*!
	*@brief		�E�����̐ݒ�B
	*/
	void SetRightVec(const D3DXVECTOR3& right);
	/*!
	*@brief		�E�����̎擾�B
	*/
	const D3DXVECTOR3& GetRightVec() const;
	/*!
	 *@brief	������̐ݒ�B
	 */
	void SetUpVec(const D3DXVECTOR3& up);
	/*!
	 *@brief	������̎擾�B
	 */
	const D3DXVECTOR3& GetUpVec() const;
	/*!
	 *@brief	�r���[�s��̐ݒ�B
	 */
	void SetViewMatrix(const D3DXMATRIX& mView);
	/*!
	 *@brief	�r���[�s��̎擾�B
	 */
	const D3DXMATRIX& GetViewMatrix() const;
	/*!
	 *@brief	�v���W�F�N�V�����s��̐ݒ�B
	 */
	void SetProjectionMatrix(const D3DXMATRIX& mProj);
	/*!
	 *@brief	�v���W�F�N�V�����s��̎擾�B
	 */
	const D3DXMATRIX& GetProjectionMatrix() const;
	/*!
	 *@brief	�J�����̍X�V�����B
	 */
	void Update();
	/*!
	 *@brief	�J�����̏������B
	 */
	void Init();
};