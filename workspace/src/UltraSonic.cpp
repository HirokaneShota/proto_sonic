/* ------------------------------------------------------------------------- */
/* UltraSonic.cpp															 */
/* 障害物からの距離を取得する												 */
/* シングルトンで定義														 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2022/07/14     筈尾　辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include																	 */
/* ------------------------------------------------------------------------- */
#include "UltraSonic.h"
#include"../include/Steering.h"
#include "UltraSonicSensor.h"
/* ------------------------------------------------------------------------- */
/* 関数名	: UltraSonic::UltraSonic										 */
/* 機能名	: コンストラクタ												 */
/* 機能概要	: インスタンス作成は getInstance() で行う、変数の初期化等を担当	 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2022/07/14		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
UltraSonic::UltraSonic( void )
{
	prevDisCM	= 0;							/* 0もなにか定数にする？？	 */
	critDisCM	= 0;							/* 0もなにか定数にする？？	 */
	distanceMM	= 0;							/* 0もなにか定数にする？？	 */
	distanceCM	= 0;							/* 0もなにか定数にする？？	 */
}
/* ------------------------------------------------------------------------- */
/* 関数名	: UltraSonic::~UltraSonic										 */
/* 機能名	: デストラクタ													 */
/* 機能概要	: DM開放やインスタンスのポインターNULL化を担当					 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2022/07/14		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
UltraSonic::~UltraSonic( void ){}

/* ------------------------------------------------------------------------- */
/* 関数名	: UltraSonic::getDistance										 */
/* 機能名	:																 */
/* 機能概要	: メンバー変数のdistanceを取得する								 */
/* 引数		: なし															 */
/* 戻り値	: int16_t			:distanceMM			:距離(mm単位)			 */
/* 作成日	: 2022/07/14		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
int16_t UltraSonic::getDistance( void ) 
{
	/* 距離(mm単位)を返す */
	return distanceMM_r;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: UltraSonic::update											 */
/* 機能名	: 障害物との距離をCM単位で取得する								 */
/* 機能概要	: 更新タスクで呼び出され、distance値の更新を行う				 */
/* 引数		: なし															 */
/* 戻り値	: int8_t				:SYS_OK			:正常終了				 */
/*			: int8_t				:SYS_NG			:異常終了				 */
/* 作成日	: 2022/07/14		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
int8_t UltraSonic::update( void ) {

	/* 超音波センサクラスの作成 */
	UltraSonicSensor USS = UltraSonicSensor::getInstance();

	/* 前回の距離(cm単位)の更新 */
	prevDisCM = distanceCM;

	/* 距離(cm単位)の取得 */
	distanceCM = USS.getDistance();

	/* エラーチェック */
	/* 正常ならOK、異常ならNGを返す */
	if ( distanceCM == 0 ) {
		return SYS_NG;
	}
	return SYS_OK;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: UltraSonic::calc												 */
/* 機能名	: 障害物との距離をMM単位で取得する								 */
/* 機能概要	: 更新タスクで呼び出され、distance値の更新を行う				 */
/* 引数		: なし															 */
/* 戻り値	: int8_t				:SYS_OK			:正常終了				 */
/*			: int8_t				:SYS_NG			:異常終了				 */
/* 作成日	: 2022/07/16		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
int8_t UltraSonic::calc(void) {

	/* モーター制御クラスの作成 */
	Steering &steering = Steering::getInstance();

	/* 初取得時は処理しない */
	if ( prevDisCM == 0 ) {
		return SYS_OK;
	}

	/* 基準点取得 */
	/* 前回の取得からCM単位に変更があれば基準点とする */
	if ( distanceCM != prevDisCM ){
		critDisCM = distanceCM;
	}

	/* 基準点が 0 なら処理しない */
	if ( critDisCM == 0 ) {
		return SYS_OK;
	}

	/* MM取得処理----------------------------------------------------------- */

	/* モータ値正常チェック */
	// モータ値異常時は0が入るので、チェック不可？

	/* 初処理時または基準点更新時 = 基準点と同距離 */
	if ( distanceMM == 0 || distanceCM != prevDisCM) {
		distanceMM = distanceCM;
		prevMorter = steering.getMotorAngle();			/* モータ角取得 */
		return SYS_OK;
	}
	/* 現在のモータ角度 */
	nowMorter = steering.getMotorAngle();

	/* 二回目以降 = 前回の値からモータ角の変化分を足し引きしたものがMM単位の距離 */
	//ここの計算式Define でまとめる　直径の10とかもDefine定義したほうが良い？？
	distanceMM_r = distanceMM_r - ( nowMorter.right - prevMorter.right ) * CAR_WHEEL_WIDTH * 3.14 / 360;
	distanceMM_l = distanceMM_l - ( nowMorter.left - prevMorter.left ) * CAR_WHEEL_WIDTH * 3.14 / 360;

	/* モータ値更新 */
	prevMorter = steering.getMotorAngle();
	/* --------------------------------------------------------------------- */


	/* 平均化--------------------------------------------------------------- */
	//10msでの進度が不明瞭なため未記載
	//ロジックとしては
	//
	// 平均値 = カウント値 * 平均値 + mm単位の取得値 / カウント値 + 1
	// 平均値　と　mm単位の取得値を比較して閾値以上のズレなら異常値とみなす
	/* --------------------------------------------------------------------- */
	return SYS_OK;
}