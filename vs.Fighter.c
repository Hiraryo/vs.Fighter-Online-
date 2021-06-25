/*
/////ゲーム画像提供サイト/////

//キャラクター
サイト名：	茫然の流もの喫茶
URL：	http://bozen.web.fc2.com/
作者名：	茫然

///////////////////////////

//ランキング確認サイト(自分のHP)
http://expresshr99.html.xdomain.jp/vsFighter.html
*/

/*ご使用のPCでこのゲームを初めて遊ぶ際は、commandファイルにアクセス権を付与してください。
cd でcommandファイルのあるディレクトリに移動し、
chmod u+x Download.command をターミナルで入力し、Download.commandファイルにアクセス権を付与
chmod u+x upload.command をターミナルで入力し、upload.commandファイルにアクセス権を付与
を行なってください。
*/

/*
学内Wi-Fi(KSU2010g、KSU2010gx、KSU2010n、KSU2010nx)では正常にランキングデータをアップロードができないことを確認しています。
(学内Wi-Fiでランキングデータをアップロードを実行してしまうと、
サーバーにあるランキングのデータが0バイトになってしまいます)
なので、学内Wi-Fi「以外」のWi-Fiをご利用ください。
宜しくお願いします。
*/

#include <stdio.h>
#include <handy.h>
#include <stdbool.h>            //boolを使う為
#include <stdlib.h>  // rand関数を使うために必要
#include <time.h>  // time関数を使うために必要
#include <unistd.h>     //chdir関数を使うために必要

#define WIDTH 1280
#define HIGHT 850
#define HIT_RANGE 120   //キャラのあたり幅
#define HIT_RANGE_Y 100 //キャラのあたり高さ(手の位置)
#define CHARA_HEIGHT 210    //キャラの高さ
char program[] = "./Download.command";
char program2[] = "./upload.command";

int Back_Line(void);
int Title(void);
int Game_main(void);
int Result_win(void);
int Result_lose(void);
int number[200];              //数値を格納する配列

int windowID;

int line1, line2, line1_X, line2_X_L, line2_X_R, line_floor_L, line_floor_R;

FILE *file, *out;
int i,j,tmp,total = 100;

int main(){
    //char *home_path = getenv("HOME");
    windowID = HgOpen(WIDTH,HIGHT);
    int game_status = 0;    //0:タイトル画面、1:モード選択画面、2:ゲームクリア画面、3:ゲームオーバー画面、4:ゲームメイン、5:キャラ選択
    hgevent *event;
    int bgm_1 = HgSoundLoad("sound/bgm/Title bgm.mp3"); //タイトルBGM
    int bgm_2 = HgSoundLoad("sound/bgm/Stage01.mp3");   //ステージBGM(ノーマル)
    int bgm_3 = HgSoundLoad("sound/bgm/_Stage01.mp3");   //ステージBGM(ファースト)
    int bgm_4 = HgSoundLoad("sound/bgm/Mode_Select.mp3");   //モードセレクトBGM
    int se_1 = HgSoundLoad("sound/se/finish.mp3");      //ゲームセット音
    int se_2 = HgSoundLoad("sound/se/Select.mp3");      //カーソル移動音
    //----------------------------------ボイス読み込み---------------------------------------------------------
    int voice_1 = HgSoundLoad("sound/voice/draw.wav");
    int voice_2 = HgSoundLoad("sound/voice/game_set.wav");
    int voice_3 = HgSoundLoad("sound/voice/go.wav");
    int voice_4 = HgSoundLoad("sound/voice/player_lose.wav");
    int voice_5 = HgSoundLoad("sound/voice/player_win.wav");
    int voice_6 = HgSoundLoad("sound/voice/ready.wav");
    int voice_7 = HgSoundLoad("sound/voice/time_up.wav");
    //----------------------------------タイトル画像読み込み---------------------------------------------------------
    int title_back = HgImageLoad("gra/titleBack.png");  //背景
    int title_1 = HgImageLoad("gra/vs.png");        //vs
    int title_2 = HgImageLoad("gra/Titledot.png");  //.
    int title_3 = HgImageLoad("gra/fightr.png");    //fightr
    int title_4 = HgImageLoad("gra/!.png");         //!
//----------------------------------ウェイト-------------------------------------------------------------------
    int player_w1 = HgImageLoad("gra/wait/wait_01.png");   //白(ウェイト・右向き)
    int player_w2 = HgImageLoad("gra/wait/wait_02.png");   //白(ウェイト・右向き)
    int player_w3 = HgImageLoad("gra/wait/wait_03.png");   //白(ウェイト・右向き)
    int player_w4 = HgImageLoad("gra/wait/wait_04.png");   //白(ウェイト・右向き)
    int player_w5 = HgImageLoad("gra/wait/wait_05.png");   //白(ウェイト・右向き)
    int player_w6 = HgImageLoad("gra/wait/wait_06.png");   //白(ウェイト・右向き)

    int enemy_w1 = HgImageLoad("gra/wait/wait_01_Black.png");   //黒(ウェイト・右向き)
    int enemy_w2 = HgImageLoad("gra/wait/wait_02_Black.png");   //黒(ウェイト・右向き)
    int enemy_w3 = HgImageLoad("gra/wait/wait_03_Black.png");   //黒(ウェイト・右向き)
    int enemy_w4 = HgImageLoad("gra/wait/wait_04_Black.png");   //黒(ウェイト・右向き)
    int enemy_w5 = HgImageLoad("gra/wait/wait_05_Black.png");   //黒(ウェイト・右向き)
    int enemy_w6 = HgImageLoad("gra/wait/wait_06_Black.png");   //黒(ウェイト・右向き)

    int green_w1 = HgImageLoad("gra/wait/wait_01_Green.png");   //緑(ウェイト・右向き)
    int green_w2 = HgImageLoad("gra/wait/wait_02_Green.png");   //緑(ウェイト・右向き)
    int green_w3 = HgImageLoad("gra/wait/wait_03_Green.png");   //緑(ウェイト・右向き)
    int green_w4 = HgImageLoad("gra/wait/wait_04_Green.png");   //緑(ウェイト・右向き)
    int green_w5 = HgImageLoad("gra/wait/wait_05_Green.png");   //緑(ウェイト・右向き)
    int green_w6 = HgImageLoad("gra/wait/wait_06_Green.png");   //緑(ウェイト・右向き)

    int pink_w1 = HgImageLoad("gra/wait/wait_01_Pink.png");   //ピンク(ウェイト・右向き)
    int pink_w2 = HgImageLoad("gra/wait/wait_02_Pink.png");   //ピンク(ウェイト・右向き)
    int pink_w3 = HgImageLoad("gra/wait/wait_03_Pink.png");   //ピンク(ウェイト・右向き)
    int pink_w4 = HgImageLoad("gra/wait/wait_04_Pink.png");   //ピンク(ウェイト・右向き)
    int pink_w5 = HgImageLoad("gra/wait/wait_05_Pink.png");   //ピンク(ウェイト・右向き)
    int pink_w6 = HgImageLoad("gra/wait/wait_06_Pink.png");   //ピンク(ウェイト・右向き)

    int red_w1 = HgImageLoad("gra/wait/wait_01_Red.png");   //赤(ウェイト・右向き)
    int red_w2 = HgImageLoad("gra/wait/wait_02_Red.png");   //赤(ウェイト・右向き)
    int red_w3 = HgImageLoad("gra/wait/wait_03_Red.png");   //赤(ウェイト・右向き)
    int red_w4 = HgImageLoad("gra/wait/wait_04_Red.png");   //赤(ウェイト・右向き)
    int red_w5 = HgImageLoad("gra/wait/wait_05_Red.png");   //赤(ウェイト・右向き)
    int red_w6 = HgImageLoad("gra/wait/wait_06_Red.png");   //赤(ウェイト・右向き)

    int player_w1L = HgImageLoad("gra/wait/wait_01L.png"); //白(ウェイト・左向き)
    int player_w2L = HgImageLoad("gra/wait/wait_02L.png"); //白(ウェイト・左向き)
    int player_w3L = HgImageLoad("gra/wait/wait_03L.png"); //白(ウェイト・左向き)
    int player_w4L = HgImageLoad("gra/wait/wait_04L.png"); //白(ウェイト・左向き)
    int player_w5L = HgImageLoad("gra/wait/wait_05L.png"); //白(ウェイト・左向き)
    int player_w6L = HgImageLoad("gra/wait/wait_06L.png"); //白(ウェイト・左向き)

    int enemy_w1L = HgImageLoad("gra/wait/wait_01L_Black.png");   //黒(ウェイト・左向き)
    int enemy_w2L = HgImageLoad("gra/wait/wait_02L_Black.png");   //黒(ウェイト・左向き)
    int enemy_w3L = HgImageLoad("gra/wait/wait_03L_Black.png");   //黒(ウェイト・左向き)
    int enemy_w4L = HgImageLoad("gra/wait/wait_04L_Black.png");   //黒(ウェイト・左向き)
    int enemy_w5L = HgImageLoad("gra/wait/wait_05L_Black.png");   //黒(ウェイト・左向き)
    int enemy_w6L = HgImageLoad("gra/wait/wait_06L_Black.png");   //黒(ウェイト・左向き)

    int green_w1L = HgImageLoad("gra/wait/wait_01L_Green.png");   //緑(ウェイト・左向き)
    int green_w2L = HgImageLoad("gra/wait/wait_02L_Green.png");   //緑(ウェイト・左向き)
    int green_w3L = HgImageLoad("gra/wait/wait_03L_Green.png");   //緑(ウェイト・左向き)
    int green_w4L = HgImageLoad("gra/wait/wait_04L_Green.png");   //緑(ウェイト・左向き)
    int green_w5L = HgImageLoad("gra/wait/wait_05L_Green.png");   //緑(ウェイト・左向き)
    int green_w6L = HgImageLoad("gra/wait/wait_06L_Green.png");   //緑(ウェイト・左向き)

    int pink_w1L = HgImageLoad("gra/wait/wait_01L_Pink.png");   //ピンク(ウェイト・左向き)
    int pink_w2L = HgImageLoad("gra/wait/wait_02L_Pink.png");   //ピンク(ウェイト・左向き)
    int pink_w3L = HgImageLoad("gra/wait/wait_03L_Pink.png");   //ピンク(ウェイト・左向き)
    int pink_w4L = HgImageLoad("gra/wait/wait_04L_Pink.png");   //ピンク(ウェイト・左向き)
    int pink_w5L = HgImageLoad("gra/wait/wait_05L_Pink.png");   //ピンク(ウェイト・左向き)
    int pink_w6L = HgImageLoad("gra/wait/wait_06L_Pink.png");   //ピンク(ウェイト・左向き)

    int red_w1L = HgImageLoad("gra/wait/wait_01L_Red.png");   //赤(ウェイト・左向き)
    int red_w2L = HgImageLoad("gra/wait/wait_02L_Red.png");   //赤(ウェイト・左向き)
    int red_w3L = HgImageLoad("gra/wait/wait_03L_Red.png");   //赤(ウェイト・左向き)
    int red_w4L = HgImageLoad("gra/wait/wait_04L_Red.png");   //赤(ウェイト・左向き)
    int red_w5L = HgImageLoad("gra/wait/wait_05L_Red.png");   //赤(ウェイト・左向き)
    int red_w6L = HgImageLoad("gra/wait/wait_06L_Red.png");   //赤(ウェイト・左向き)
//----------------------------------ウェイトここまで-------------------------------------------------------------------
//----------------------------------パンチ-------------------------------------------------------------------
    int player_p1 = HgImageLoad("gra/punch/punch_01.png");  //白(パンチ・右向き)
    int player_p2 = HgImageLoad("gra/punch/punch_02.png");  //白(パンチ・右向き)
    int player_p3 = HgImageLoad("gra/punch/punch_03.png");  //白(パンチ・右向き)
    int player_p4 = HgImageLoad("gra/punch/punch_04.png");  //白(パンチ・右向き)
    int player_p5 = HgImageLoad("gra/punch/punch_05.png");  //白(パンチ・右向き)
    int player_p6 = HgImageLoad("gra/punch/punch_06.png");  //白(パンチ・右向き)
    int player_p7 = HgImageLoad("gra/punch/punch_07.png");  //白(パンチ・右向き)
    int player_p8 = HgImageLoad("gra/punch/punch_08.png");  //白(パンチ・右向き)
    int player_p9 = HgImageLoad("gra/punch/punch_09.png");  //白(パンチ・右向き)
    int player_p10 = HgImageLoad("gra/punch/punch_10.png"); //白(パンチ・右向き)

    int enemy_p1 = HgImageLoad("gra/punch/punch_01_Black.png");  //黒(パンチ・右向き)
    int enemy_p2 = HgImageLoad("gra/punch/punch_02_Black.png");  //黒(パンチ・右向き)
    int enemy_p3 = HgImageLoad("gra/punch/punch_03_Black.png");  //黒(パンチ・右向き)
    int enemy_p4 = HgImageLoad("gra/punch/punch_04_Black.png");  //黒(パンチ・右向き)
    int enemy_p5 = HgImageLoad("gra/punch/punch_05_Black.png");  //黒(パンチ・右向き)
    int enemy_p6 = HgImageLoad("gra/punch/punch_06_Black.png");  //黒(パンチ・右向き)
    int enemy_p7 = HgImageLoad("gra/punch/punch_07_Black.png");  //黒(パンチ・右向き)
    int enemy_p8 = HgImageLoad("gra/punch/punch_08_Black.png");  //黒(パンチ・右向き)
    int enemy_p9 = HgImageLoad("gra/punch/punch_09_Black.png");  //黒(パンチ・右向き)
    int enemy_p10 = HgImageLoad("gra/punch/punch_10_Black.png"); //黒(パンチ・右向き)

    int green_p1 = HgImageLoad("gra/punch/punch_01_Green.png");  //緑(パンチ・右向き)
    int green_p2 = HgImageLoad("gra/punch/punch_02_Green.png");  //緑(パンチ・右向き)
    int green_p3 = HgImageLoad("gra/punch/punch_03_Green.png");  //緑(パンチ・右向き)
    int green_p4 = HgImageLoad("gra/punch/punch_04_Green.png");  //緑(パンチ・右向き)
    int green_p5 = HgImageLoad("gra/punch/punch_05_Green.png");  //緑(パンチ・右向き)
    int green_p6 = HgImageLoad("gra/punch/punch_06_Green.png");  //緑(パンチ・右向き)
    int green_p7 = HgImageLoad("gra/punch/punch_07_Green.png");  //緑(パンチ・右向き)
    int green_p8 = HgImageLoad("gra/punch/punch_08_Green.png");  //緑(パンチ・右向き)
    int green_p9 = HgImageLoad("gra/punch/punch_09_Green.png");  //緑(パンチ・右向き)
    int green_p10 = HgImageLoad("gra/punch/punch_10_Green.png"); //緑(パンチ・右向き)

    int pink_p1 = HgImageLoad("gra/punch/punch_01_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p2 = HgImageLoad("gra/punch/punch_02_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p3 = HgImageLoad("gra/punch/punch_03_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p4 = HgImageLoad("gra/punch/punch_04_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p5 = HgImageLoad("gra/punch/punch_05_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p6 = HgImageLoad("gra/punch/punch_06_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p7 = HgImageLoad("gra/punch/punch_07_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p8 = HgImageLoad("gra/punch/punch_08_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p9 = HgImageLoad("gra/punch/punch_09_Pink.png");  //ピンク(パンチ・右向き)
    int pink_p10 = HgImageLoad("gra/punch/punch_10_Pink.png"); //ピンク(パンチ・右向き)

    int red_p1 = HgImageLoad("gra/punch/punch_01_Red.png");  //赤(パンチ・右向き)
    int red_p2 = HgImageLoad("gra/punch/punch_02_Red.png");  //赤(パンチ・右向き)
    int red_p3 = HgImageLoad("gra/punch/punch_03_Red.png");  //赤(パンチ・右向き)
    int red_p4 = HgImageLoad("gra/punch/punch_04_Red.png");  //赤(パンチ・右向き)
    int red_p5 = HgImageLoad("gra/punch/punch_05_Red.png");  //赤(パンチ・右向き)
    int red_p6 = HgImageLoad("gra/punch/punch_06_Red.png");  //赤(パンチ・右向き)
    int red_p7 = HgImageLoad("gra/punch/punch_07_Red.png");  //赤(パンチ・右向き)
    int red_p8 = HgImageLoad("gra/punch/punch_08_Red.png");  //赤(パンチ・右向き)
    int red_p9 = HgImageLoad("gra/punch/punch_09_Red.png");  //赤(パンチ・右向き)
    int red_p10 = HgImageLoad("gra/punch/punch_10_Red.png"); //赤(パンチ・右向き)

    int player_p1L = HgImageLoad("gra/punch/punch_01L.png");  //白(パンチ・左向き)
    int player_p2L = HgImageLoad("gra/punch/punch_02L.png");  //白(パンチ・左向き)
    int player_p3L = HgImageLoad("gra/punch/punch_03L.png");  //白(パンチ・左向き)
    int player_p4L = HgImageLoad("gra/punch/punch_04L.png");  //白(パンチ・左向き)
    int player_p5L = HgImageLoad("gra/punch/punch_05L.png");  //白(パンチ・左向き)
    int player_p6L = HgImageLoad("gra/punch/punch_06L.png");  //白(パンチ・左向き)
    int player_p7L = HgImageLoad("gra/punch/punch_07L.png");  //白(パンチ・左向き)
    int player_p8L = HgImageLoad("gra/punch/punch_08L.png");  //白(パンチ・左向き)
    int player_p9L = HgImageLoad("gra/punch/punch_09L.png");  //白(パンチ・左向き)
    int player_p10L = HgImageLoad("gra/punch/punch_10L.png"); //白(パンチ・左向き)

    int enemy_p1L = HgImageLoad("gra/punch/punch_01L_Black.png");  //黒(パンチ・左向き)
    int enemy_p2L = HgImageLoad("gra/punch/punch_02L_Black.png");  //黒(パンチ・左向き)
    int enemy_p3L = HgImageLoad("gra/punch/punch_03L_Black.png");  //黒(パンチ・左向き)
    int enemy_p4L = HgImageLoad("gra/punch/punch_04L_Black.png");  //黒(パンチ・左向き)
    int enemy_p5L = HgImageLoad("gra/punch/punch_05L_Black.png");  //黒(パンチ・左向き)
    int enemy_p6L = HgImageLoad("gra/punch/punch_06L_Black.png");  //黒(パンチ・左向き)
    int enemy_p7L = HgImageLoad("gra/punch/punch_07L_Black.png");  //黒(パンチ・左向き)
    int enemy_p8L = HgImageLoad("gra/punch/punch_08L_Black.png");  //黒(パンチ・左向き)
    int enemy_p9L = HgImageLoad("gra/punch/punch_09L_Black.png");  //黒(パンチ・左向き)
    int enemy_p10L = HgImageLoad("gra/punch/punch_10L_Black.png"); //黒(パンチ・左向き)

    int green_p1L = HgImageLoad("gra/punch/punch_01L_Green.png");  //緑(パンチ・左向き)
    int green_p2L = HgImageLoad("gra/punch/punch_02L_Green.png");  //緑(パンチ・左向き)
    int green_p3L = HgImageLoad("gra/punch/punch_03L_Green.png");  //緑(パンチ・左向き)
    int green_p4L = HgImageLoad("gra/punch/punch_04L_Green.png");  //緑(パンチ・左向き)
    int green_p5L = HgImageLoad("gra/punch/punch_05L_Green.png");  //緑(パンチ・左向き)
    int green_p6L = HgImageLoad("gra/punch/punch_06L_Green.png");  //緑(パンチ・左向き)
    int green_p7L = HgImageLoad("gra/punch/punch_07L_Green.png");  //緑(パンチ・左向き)
    int green_p8L = HgImageLoad("gra/punch/punch_08L_Green.png");  //緑(パンチ・左向き)
    int green_p9L = HgImageLoad("gra/punch/punch_09L_Green.png");  //緑(パンチ・左向き)
    int green_p10L = HgImageLoad("gra/punch/punch_10L_Green.png"); //緑(パンチ・左向き)

    int pink_p1L = HgImageLoad("gra/punch/punch_01L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p2L = HgImageLoad("gra/punch/punch_02L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p3L = HgImageLoad("gra/punch/punch_03L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p4L = HgImageLoad("gra/punch/punch_04L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p5L = HgImageLoad("gra/punch/punch_05L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p6L = HgImageLoad("gra/punch/punch_06L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p7L = HgImageLoad("gra/punch/punch_07L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p8L = HgImageLoad("gra/punch/punch_08L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p9L = HgImageLoad("gra/punch/punch_09L_Pink.png");  //ピンク(パンチ・左向き)
    int pink_p10L = HgImageLoad("gra/punch/punch_10L_Pink.png"); //ピンク(パンチ・左向き)

    int red_p1L = HgImageLoad("gra/punch/punch_01L_Red.png");  //赤(パンチ・左向き)
    int red_p2L = HgImageLoad("gra/punch/punch_02L_Red.png");  //赤(パンチ・左向き)
    int red_p3L = HgImageLoad("gra/punch/punch_03L_Red.png");  //赤(パンチ・左向き)
    int red_p4L = HgImageLoad("gra/punch/punch_04L_Red.png");  //赤(パンチ・左向き)
    int red_p5L = HgImageLoad("gra/punch/punch_05L_Red.png");  //赤(パンチ・左向き)
    int red_p6L = HgImageLoad("gra/punch/punch_06L_Red.png");  //赤(パンチ・左向き)
    int red_p7L = HgImageLoad("gra/punch/punch_07L_Red.png");  //赤(パンチ・左向き)
    int red_p8L = HgImageLoad("gra/punch/punch_08L_Red.png");  //赤(パンチ・左向き)
    int red_p9L = HgImageLoad("gra/punch/punch_09L_Red.png");  //赤(パンチ・左向き)
    int red_p10L = HgImageLoad("gra/punch/punch_10L_Red.png"); //赤(パンチ・左向き)
//----------------------------------パンチここまで-------------------------------------------------------------------
//----------------------------------ジャンプ-------------------------------------------------------------------
    int player_j1 = HgImageLoad("gra/jump/jump_01.png");  //白(ジャンプ・右向き)
    int player_j2 = HgImageLoad("gra/jump/jump_02.png");  //白(ジャンプ・右向き)
    int player_j3 = HgImageLoad("gra/jump/jump_03.png");  //白(ジャンプ・右向き)
    int player_j4 = HgImageLoad("gra/jump/jump_04.png");  //白(ジャンプ・右向き)
    int player_j5 = HgImageLoad("gra/jump/jump_05.png");  //白(ジャンプ・右向き)
    int player_j6 = HgImageLoad("gra/jump/jump_06.png");  //白(ジャンプ・右向き)
    int player_j7 = HgImageLoad("gra/jump/jump_07.png");  //白(ジャンプ・右向き)
    int player_j8 = HgImageLoad("gra/jump/jump_08.png");  //白(ジャンプ・右向き)
    int player_j9 = HgImageLoad("gra/jump/jump_09.png");  //白(ジャンプ・右向き)
    int player_j10 = HgImageLoad("gra/jump/jump_10.png"); //白(ジャンプ・右向き)

    int enemy_j1 = HgImageLoad("gra/jump/jump_01_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j2 = HgImageLoad("gra/jump/jump_02_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j3 = HgImageLoad("gra/jump/jump_03_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j4 = HgImageLoad("gra/jump/jump_04_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j5 = HgImageLoad("gra/jump/jump_05_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j6 = HgImageLoad("gra/jump/jump_06_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j7 = HgImageLoad("gra/jump/jump_07_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j8 = HgImageLoad("gra/jump/jump_08_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j9 = HgImageLoad("gra/jump/jump_09_Black.png");  //黒(ジャンプ・右向き)
    int enemy_j10 = HgImageLoad("gra/jump/jump_10_Black.png"); //黒(ジャンプ・右向き)

    int green_j1 = HgImageLoad("gra/jump/jump_01_Green.png");  //緑(ジャンプ・右向き)
    int green_j2 = HgImageLoad("gra/jump/jump_02_Green.png");  //緑(ジャンプ・右向き)
    int green_j3 = HgImageLoad("gra/jump/jump_03_Green.png");  //緑(ジャンプ・右向き)
    int green_j4 = HgImageLoad("gra/jump/jump_04_Green.png");  //緑(ジャンプ・右向き)
    int green_j5 = HgImageLoad("gra/jump/jump_05_Green.png");  //緑(ジャンプ・右向き)
    int green_j6 = HgImageLoad("gra/jump/jump_06_Green.png");  //緑(ジャンプ・右向き)
    int green_j7 = HgImageLoad("gra/jump/jump_07_Green.png");  //緑(ジャンプ・右向き)
    int green_j8 = HgImageLoad("gra/jump/jump_08_Green.png");  //緑(ジャンプ・右向き)
    int green_j9 = HgImageLoad("gra/jump/jump_09_Green.png");  //緑(ジャンプ・右向き)
    int green_j10 = HgImageLoad("gra/jump/jump_10_Green.png"); //緑(ジャンプ・右向き)

    int pink_j1 = HgImageLoad("gra/jump/jump_01_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j2 = HgImageLoad("gra/jump/jump_02_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j3 = HgImageLoad("gra/jump/jump_03_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j4 = HgImageLoad("gra/jump/jump_04_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j5 = HgImageLoad("gra/jump/jump_05_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j6 = HgImageLoad("gra/jump/jump_06_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j7 = HgImageLoad("gra/jump/jump_07_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j8 = HgImageLoad("gra/jump/jump_08_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j9 = HgImageLoad("gra/jump/jump_09_Pink.png");  //ピンク(ジャンプ・右向き)
    int pink_j10 = HgImageLoad("gra/jump/jump_10_Pink.png"); //ピンク(ジャンプ・右向き)

    int red_j1 = HgImageLoad("gra/jump/jump_01_Red.png");  //赤(ジャンプ・右向き)
    int red_j2 = HgImageLoad("gra/jump/jump_02_Red.png");  //赤(ジャンプ・右向き)
    int red_j3 = HgImageLoad("gra/jump/jump_03_Red.png");  //赤(ジャンプ・右向き)
    int red_j4 = HgImageLoad("gra/jump/jump_04_Red.png");  //赤(ジャンプ・右向き)
    int red_j5 = HgImageLoad("gra/jump/jump_05_Red.png");  //赤(ジャンプ・右向き)
    int red_j6 = HgImageLoad("gra/jump/jump_06_Red.png");  //赤(ジャンプ・右向き)
    int red_j7 = HgImageLoad("gra/jump/jump_07_Red.png");  //赤(ジャンプ・右向き)
    int red_j8 = HgImageLoad("gra/jump/jump_08_Red.png");  //赤(ジャンプ・右向き)
    int red_j9 = HgImageLoad("gra/jump/jump_09_Red.png");  //赤(ジャンプ・右向き)
    int red_j10 = HgImageLoad("gra/jump/jump_10_Red.png"); //赤(ジャンプ・右向き)

    int player_j1L = HgImageLoad("gra/jump/jump_01L.png");  //白(ジャンプ・左向き)
    int player_j2L = HgImageLoad("gra/jump/jump_02L.png");  //白(ジャンプ・左向き)
    int player_j3L = HgImageLoad("gra/jump/jump_03L.png");  //白(ジャンプ・左向き)
    int player_j4L = HgImageLoad("gra/jump/jump_04L.png");  //白(ジャンプ・左向き)
    int player_j5L = HgImageLoad("gra/jump/jump_05L.png");  //白(ジャンプ・左向き)
    int player_j6L = HgImageLoad("gra/jump/jump_06L.png");  //白(ジャンプ・左向き)
    int player_j7L = HgImageLoad("gra/jump/jump_07L.png");  //白(ジャンプ・左向き)
    int player_j8L = HgImageLoad("gra/jump/jump_08L.png");  //白(ジャンプ・左向き)
    int player_j9L = HgImageLoad("gra/jump/jump_09L.png");  //白(ジャンプ・左向き)
    int player_j10L = HgImageLoad("gra/jump/jump_10L.png"); //白(ジャンプ・左向き)

    int enemy_j1L = HgImageLoad("gra/jump/jump_01L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j2L = HgImageLoad("gra/jump/jump_02L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j3L = HgImageLoad("gra/jump/jump_03L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j4L = HgImageLoad("gra/jump/jump_04L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j5L = HgImageLoad("gra/jump/jump_05L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j6L = HgImageLoad("gra/jump/jump_06L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j7L = HgImageLoad("gra/jump/jump_07L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j8L = HgImageLoad("gra/jump/jump_08L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j9L = HgImageLoad("gra/jump/jump_09L_Black.png");  //黒(ジャンプ・左向き)
    int enemy_j10L = HgImageLoad("gra/jump/jump_10L_Black.png"); //黒(ジャンプ・左向き)

    int green_j1L = HgImageLoad("gra/jump/jump_01L_Green.png");  //緑(ジャンプ・左向き)
    int green_j2L = HgImageLoad("gra/jump/jump_02L_Green.png");  //緑(ジャンプ・左向き)
    int green_j3L = HgImageLoad("gra/jump/jump_03L_Green.png");  //緑(ジャンプ・左向き)
    int green_j4L = HgImageLoad("gra/jump/jump_04L_Green.png");  //緑(ジャンプ・左向き)
    int green_j5L = HgImageLoad("gra/jump/jump_05L_Green.png");  //緑(ジャンプ・左向き)
    int green_j6L = HgImageLoad("gra/jump/jump_06L_Green.png");  //緑(ジャンプ・左向き)
    int green_j7L = HgImageLoad("gra/jump/jump_07L_Green.png");  //緑(ジャンプ・左向き)
    int green_j8L = HgImageLoad("gra/jump/jump_08L_Green.png");  //緑(ジャンプ・左向き)
    int green_j9L = HgImageLoad("gra/jump/jump_09L_Green.png");  //緑(ジャンプ・左向き)
    int green_j10L = HgImageLoad("gra/jump/jump_10L_Green.png"); //緑(ジャンプ・左向き)

    int pink_j1L = HgImageLoad("gra/jump/jump_01L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j2L = HgImageLoad("gra/jump/jump_02L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j3L = HgImageLoad("gra/jump/jump_03L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j4L = HgImageLoad("gra/jump/jump_04L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j5L = HgImageLoad("gra/jump/jump_05L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j6L = HgImageLoad("gra/jump/jump_06L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j7L = HgImageLoad("gra/jump/jump_07L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j8L = HgImageLoad("gra/jump/jump_08L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j9L = HgImageLoad("gra/jump/jump_09L_Pink.png");  //ピンク(ジャンプ・左向き)
    int pink_j10L = HgImageLoad("gra/jump/jump_10L_Pink.png"); //ピンク(ジャンプ・左向き)

    int red_j1L = HgImageLoad("gra/jump/jump_01L_Red.png");  //赤(ジャンプ・左向き)
    int red_j2L = HgImageLoad("gra/jump/jump_02L_Red.png");  //赤(ジャンプ・左向き)
    int red_j3L = HgImageLoad("gra/jump/jump_03L_Red.png");  //赤(ジャンプ・左向き)
    int red_j4L = HgImageLoad("gra/jump/jump_04L_Red.png");  //赤(ジャンプ・左向き)
    int red_j5L = HgImageLoad("gra/jump/jump_05L_Red.png");  //赤(ジャンプ・左向き)
    int red_j6L = HgImageLoad("gra/jump/jump_06L_Red.png");  //赤(ジャンプ・左向き)
    int red_j7L = HgImageLoad("gra/jump/jump_07L_Red.png");  //赤(ジャンプ・左向き)
    int red_j8L = HgImageLoad("gra/jump/jump_08L_Red.png");  //赤(ジャンプ・左向き)
    int red_j9L = HgImageLoad("gra/jump/jump_09L_Red.png");  //赤(ジャンプ・左向き)
    int red_j10L = HgImageLoad("gra/jump/jump_10L_Red.png"); //赤(ジャンプ・左向き)
//----------------------------------ジャンプここまで-------------------------------------------------------------------
//----------------------------------歩き-------------------------------------------------------------------
    int player_wk1 = HgImageLoad("gra/walk/walk_01.png");  //白(歩き・右向き)
    int player_wk2 = HgImageLoad("gra/walk/walk_02.png");  //白(歩き・右向き)
    int player_wk3 = HgImageLoad("gra/walk/walk_03.png");  //白(歩き・右向き)
    int player_wk4 = HgImageLoad("gra/walk/walk_04.png");  //白(歩き・右向き)
    int player_wk5 = HgImageLoad("gra/walk/walk_05.png");  //白(歩き・右向き)
    int player_wk6 = HgImageLoad("gra/walk/walk_06.png");  //白(歩き・右向き)
    int player_wk7 = HgImageLoad("gra/walk/walk_07.png");  //白(歩き・右向き)
    int player_wk8 = HgImageLoad("gra/walk/walk_08.png");  //白(歩き・右向き)

    int enemy_wk1 = HgImageLoad("gra/walk/walk_01_Black.png");  //黒(歩き・右向き)
    int enemy_wk2 = HgImageLoad("gra/walk/walk_02_Black.png");  //黒(歩き・右向き)
    int enemy_wk3 = HgImageLoad("gra/walk/walk_03_Black.png");  //黒(歩き・右向き)
    int enemy_wk4 = HgImageLoad("gra/walk/walk_04_Black.png");  //黒(歩き・右向き)
    int enemy_wk5 = HgImageLoad("gra/walk/walk_05_Black.png");  //黒(歩き・右向き)
    int enemy_wk6 = HgImageLoad("gra/walk/walk_06_Black.png");  //黒(歩き・右向き)
    int enemy_wk7 = HgImageLoad("gra/walk/walk_07_Black.png");  //黒(歩き・右向き)
    int enemy_wk8 = HgImageLoad("gra/walk/walk_08_Black.png");  //黒(歩き・右向き)

    int green_wk1 = HgImageLoad("gra/walk/walk_01_Green.png");  //緑(歩き・右向き)
    int green_wk2 = HgImageLoad("gra/walk/walk_02_Green.png");  //緑(歩き・右向き)
    int green_wk3 = HgImageLoad("gra/walk/walk_03_Green.png");  //緑(歩き・右向き)
    int green_wk4 = HgImageLoad("gra/walk/walk_04_Green.png");  //緑(歩き・右向き)
    int green_wk5 = HgImageLoad("gra/walk/walk_05_Green.png");  //緑(歩き・右向き)
    int green_wk6 = HgImageLoad("gra/walk/walk_06_Green.png");  //緑(歩き・右向き)
    int green_wk7 = HgImageLoad("gra/walk/walk_07_Green.png");  //緑(歩き・右向き)
    int green_wk8 = HgImageLoad("gra/walk/walk_08_Green.png");  //緑(歩き・右向き)

    int pink_wk1 = HgImageLoad("gra/walk/walk_01_Pink.png");  //ピンク(歩き・右向き)
    int pink_wk2 = HgImageLoad("gra/walk/walk_02_Pink.png");  //ピンク(歩き・右向き)
    int pink_wk3 = HgImageLoad("gra/walk/walk_03_Pink.png");  //ピンク(歩き・右向き)
    int pink_wk4 = HgImageLoad("gra/walk/walk_04_Pink.png");  //ピンク(歩き・右向き)
    int pink_wk5 = HgImageLoad("gra/walk/walk_05_Pink.png");  //ピンク(歩き・右向き)
    int pink_wk6 = HgImageLoad("gra/walk/walk_06_Pink.png");  //ピンク(歩き・右向き)
    int pink_wk7 = HgImageLoad("gra/walk/walk_07_Pink.png");  //ピンク(歩き・右向き)
    int pink_wk8 = HgImageLoad("gra/walk/walk_08_Pink.png");  //ピンク(歩き・右向き)

    int red_wk1 = HgImageLoad("gra/walk/walk_01_Red.png");  //赤(歩き・右向き)
    int red_wk2 = HgImageLoad("gra/walk/walk_02_Red.png");  //赤(歩き・右向き)
    int red_wk3 = HgImageLoad("gra/walk/walk_03_Red.png");  //赤(歩き・右向き)
    int red_wk4 = HgImageLoad("gra/walk/walk_04_Red.png");  //赤(歩き・右向き)
    int red_wk5 = HgImageLoad("gra/walk/walk_05_Red.png");  //赤(歩き・右向き)
    int red_wk6 = HgImageLoad("gra/walk/walk_06_Red.png");  //赤(歩き・右向き)
    int red_wk7 = HgImageLoad("gra/walk/walk_07_Red.png");  //赤(歩き・右向き)
    int red_wk8 = HgImageLoad("gra/walk/walk_08_Red.png");  //赤(歩き・右向き)

    int player_wk1L = HgImageLoad("gra/walk/walk_01L.png");  //白(歩き・左向き)
    int player_wk2L = HgImageLoad("gra/walk/walk_02L.png");  //白(歩き・左向き)
    int player_wk3L = HgImageLoad("gra/walk/walk_03L.png");  //白(歩き・左向き)
    int player_wk4L = HgImageLoad("gra/walk/walk_04L.png");  //白(歩き・左向き)
    int player_wk5L = HgImageLoad("gra/walk/walk_05L.png");  //白(歩き・左向き)
    int player_wk6L = HgImageLoad("gra/walk/walk_06L.png");  //白(歩き・左向き)
    int player_wk7L = HgImageLoad("gra/walk/walk_07L.png");  //白(歩き・左向き)
    int player_wk8L = HgImageLoad("gra/walk/walk_08L.png");  //白(歩き・左向き)

    int enemy_wk1L = HgImageLoad("gra/walk/walk_01L_Black.png");  //黒(歩き・左向き)
    int enemy_wk2L = HgImageLoad("gra/walk/walk_02L_Black.png");  //黒(歩き・左向き)
    int enemy_wk3L = HgImageLoad("gra/walk/walk_03L_Black.png");  //黒(歩き・左向き)
    int enemy_wk4L = HgImageLoad("gra/walk/walk_04L_Black.png");  //黒(歩き・左向き)
    int enemy_wk5L = HgImageLoad("gra/walk/walk_05L_Black.png");  //黒(歩き・左向き)
    int enemy_wk6L = HgImageLoad("gra/walk/walk_06L_Black.png");  //黒(歩き・左向き)
    int enemy_wk7L = HgImageLoad("gra/walk/walk_07L_Black.png");  //黒(歩き・左向き)
    int enemy_wk8L = HgImageLoad("gra/walk/walk_08L_Black.png");  //黒(歩き・左向き)

    int green_wk1L = HgImageLoad("gra/walk/walk_01L_Green.png");  //緑(歩き・左向き)
    int green_wk2L = HgImageLoad("gra/walk/walk_02L_Green.png");  //緑(歩き・左向き)
    int green_wk3L = HgImageLoad("gra/walk/walk_03L_Green.png");  //緑(歩き・左向き)
    int green_wk4L = HgImageLoad("gra/walk/walk_04L_Green.png");  //緑(歩き・左向き)
    int green_wk5L = HgImageLoad("gra/walk/walk_05L_Green.png");  //緑(歩き・左向き)
    int green_wk6L = HgImageLoad("gra/walk/walk_06L_Green.png");  //緑(歩き・左向き)
    int green_wk7L = HgImageLoad("gra/walk/walk_07L_Green.png");  //緑(歩き・左向き)
    int green_wk8L = HgImageLoad("gra/walk/walk_08L_Green.png");  //緑(歩き・左向き)

    int pink_wk1L = HgImageLoad("gra/walk/walk_01L_Pink.png");  //ピンク(歩き・左向き)
    int pink_wk2L = HgImageLoad("gra/walk/walk_02L_Pink.png");  //ピンク(歩き・左向き)
    int pink_wk3L = HgImageLoad("gra/walk/walk_03L_Pink.png");  //ピンク(歩き・左向き)
    int pink_wk4L = HgImageLoad("gra/walk/walk_04L_Pink.png");  //ピンク(歩き・左向き)
    int pink_wk5L = HgImageLoad("gra/walk/walk_05L_Pink.png");  //ピンク(歩き・左向き)
    int pink_wk6L = HgImageLoad("gra/walk/walk_06L_Pink.png");  //ピンク(歩き・左向き)
    int pink_wk7L = HgImageLoad("gra/walk/walk_07L_Pink.png");  //ピンク(歩き・左向き)
    int pink_wk8L = HgImageLoad("gra/walk/walk_08L_Pink.png");  //ピンク(歩き・左向き)

    int red_wk1L = HgImageLoad("gra/walk/walk_01L_Red.png");  //赤(歩き・左向き)
    int red_wk2L = HgImageLoad("gra/walk/walk_02L_Red.png");  //赤(歩き・左向き)
    int red_wk3L = HgImageLoad("gra/walk/walk_03L_Red.png");  //赤(歩き・左向き)
    int red_wk4L = HgImageLoad("gra/walk/walk_04L_Red.png");  //赤(歩き・左向き)
    int red_wk5L = HgImageLoad("gra/walk/walk_05L_Red.png");  //赤(歩き・左向き)
    int red_wk6L = HgImageLoad("gra/walk/walk_06L_Red.png");  //赤(歩き・左向き)
    int red_wk7L = HgImageLoad("gra/walk/walk_07L_Red.png");  //赤(歩き・左向き)
    int red_wk8L = HgImageLoad("gra/walk/walk_08L_Red.png");  //赤(歩き・左向き)
//----------------------------------歩きここまで-------------------------------------------------------------------
    int back_gra = HgImageLoad("gra/gra_sky_gridA.png");     //背景
    int ready_gra = HgImageLoad("gra/ready.png");            //readyの文字画像
    int dot_gra = HgImageLoad("gra/dot.png");                //ドット
    int go_gra = HgImageLoad("gra/go.png");                  //go!!
    int player_gra = HgImageLoad("gra/player.png");          //プレイヤーの位置を表す画像
    int online = HgImageLoad("gra/online.png");              //オンライン
    int warning = HgImageLoad("gra/warning.png");            //警告画像
    int game = HgImageLoad("gra/game.png");                  //game
    int set = HgImageLoad("gra/set.png");                    //set
    int critical = HgImageLoad("gra/critical.png");          //critical
    int player_win = HgImageLoad("gra/player_win.png");
    int enemy_win = HgImageLoad("gra/enemy_win.png");
    int draw = HgImageLoad("gra/draw.png");
    int char_status = HgImageLoad("gra/status.png");
    int player_gauge = HgImageLoad("gra/player_gauge.png"); //プレイヤーのHPゲージ
    int enemy_gauge = HgImageLoad("gra/enemy_gauge.png");   //敵のHPゲージ
    int icon1 = HgImageLoad("gra/icon1.png");
    int icon2 = HgImageLoad("gra/icon2.png");
    int icon3 = HgImageLoad("gra/icon3.png");
    int icon4 = HgImageLoad("gra/icon4.png");
    int icon5 = HgImageLoad("gra/icon5.png");
    int player_select = HgImageLoad("gra/player_select.png");
    int easy = HgImageLoad("gra/EasyMode.png");
    int normal = HgImageLoad("gra/NormalMode.png");
    int hard = HgImageLoad("gra/HardMode.png");
    int message = HgImageLoad("gra/MessageField.png");
    int frame = HgImageLoad("gra/frame.png");
    int frame2 = HgImageLoad("gra/frame2.png");
    int statusbar = HgImageLoad("gra/statusbar.png");
    int triangle = HgImageLoad("gra/triangle.png");
    int statustext = HgImageLoad("gra/statustext.png");
    int back = HgImageLoad("gra/back.png");
    doubleLayer layers_title_font;           //タイトルの文字

    doubleLayer layers_mode_select;     //モード選択画面

    doubleLayer layers_chara_select;    //キャラ選択
    doubleLayer layers_chara_frame;     //フレーム画像のレイヤー
    doubleLayer layers_triangle;        //ゲージ
    doubleLayer layers_statusbar;       //ステータスバー

    doubleLayer layers_back;            //背景
    doubleLayer layers_ready;           //ready
    doubleLayer layers_player_enemy_gauge;  //色のついたゲージ
    doubleLayer layers_char_status;     //ステータス画像
    doubleLayer layers_status;          //ゲーム内の文字
    doubleLayer layers_game_set;        //ゲームセットの文字

    doubleLayer layers_enemy_punch;    //右向き
    doubleLayer layers_enemy_jump;     //右向き
    doubleLayer layers_enemy_wait;     //右向き
    doubleLayer layers_enemy_walk;     //右向き
    doubleLayer layers_enemy_punch_L;  //左向き
    doubleLayer layers_enemy_jump_L;   //左向き
    doubleLayer layers_enemy_wait_L;   //左向き
    doubleLayer layers_enemy_walk_L;   //左向き

    doubleLayer layers_player_punch;    //右向き
    doubleLayer layers_player_jump;     //右向き
    doubleLayer layers_player_wait;     //右向き
    doubleLayer layers_player_walk;     //右向き
    doubleLayer layers_player_punch_L;  //左向き
    doubleLayer layers_player_jump_L;   //左向き
    doubleLayer layers_player_wait_L;   //左向き
    doubleLayer layers_player_walk_L;   //左向き

    doubleLayer layers_green_punch;    //右向き
    doubleLayer layers_green_jump;     //右向き
    doubleLayer layers_green_wait;     //右向き
    doubleLayer layers_green_walk;     //右向き
    doubleLayer layers_green_punch_L;  //左向き
    doubleLayer layers_green_jump_L;   //左向き
    doubleLayer layers_green_wait_L;   //左向き
    doubleLayer layers_green_walk_L;   //左向き

    doubleLayer layers_pink_punch;    //右向き
    doubleLayer layers_pink_jump;     //右向き
    doubleLayer layers_pink_wait;     //右向き
    doubleLayer layers_pink_walk;     //右向き
    doubleLayer layers_pink_punch_L;  //左向き
    doubleLayer layers_pink_jump_L;   //左向き
    doubleLayer layers_pink_wait_L;   //左向き
    doubleLayer layers_pink_walk_L;   //左向き

    doubleLayer layers_red_punch;    //右向き
    doubleLayer layers_red_jump;     //右向き
    doubleLayer layers_red_wait;     //右向き
    doubleLayer layers_red_walk;     //右向き
    doubleLayer layers_red_punch_L;  //左向き
    doubleLayer layers_red_jump_L;   //左向き
    doubleLayer layers_red_wait_L;   //左向き
    doubleLayer layers_red_walk_L;   //左向き

    layers_title_font = HgWAddDoubleLayer(windowID);

    layers_mode_select = HgWAddDoubleLayer(windowID);

    layers_chara_select = HgWAddDoubleLayer(windowID);
    layers_chara_frame = HgWAddDoubleLayer(windowID);
    layers_triangle = HgWAddDoubleLayer(windowID);
    layers_statusbar = HgWAddDoubleLayer(windowID);

    layers_back = HgWAddDoubleLayer(windowID);
    layers_ready = HgWAddDoubleLayer(windowID);
    layers_player_enemy_gauge = HgWAddDoubleLayer(windowID);
    layers_char_status = HgWAddDoubleLayer(windowID);
    layers_status = HgWAddDoubleLayer(windowID);
    layers_game_set = HgWAddDoubleLayer(windowID);

    layers_enemy_punch = HgWAddDoubleLayer(windowID);
    layers_enemy_jump = HgWAddDoubleLayer(windowID);
    layers_enemy_wait = HgWAddDoubleLayer(windowID);
    layers_enemy_walk = HgWAddDoubleLayer(windowID);
    layers_enemy_punch_L = HgWAddDoubleLayer(windowID);
    layers_enemy_jump_L = HgWAddDoubleLayer(windowID);
    layers_enemy_wait_L = HgWAddDoubleLayer(windowID);
    layers_enemy_walk_L = HgWAddDoubleLayer(windowID);

    layers_player_punch = HgWAddDoubleLayer(windowID);
    layers_player_jump = HgWAddDoubleLayer(windowID);
    layers_player_wait = HgWAddDoubleLayer(windowID);
    layers_player_walk = HgWAddDoubleLayer(windowID);
    layers_player_punch_L = HgWAddDoubleLayer(windowID);
    layers_player_jump_L = HgWAddDoubleLayer(windowID);
    layers_player_wait_L = HgWAddDoubleLayer(windowID);
    layers_player_walk_L = HgWAddDoubleLayer(windowID);

    layers_green_punch = HgWAddDoubleLayer(windowID);
    layers_green_jump = HgWAddDoubleLayer(windowID);
    layers_green_wait = HgWAddDoubleLayer(windowID);
    layers_green_walk = HgWAddDoubleLayer(windowID);
    layers_green_punch_L = HgWAddDoubleLayer(windowID);
    layers_green_jump_L = HgWAddDoubleLayer(windowID);
    layers_green_wait_L = HgWAddDoubleLayer(windowID);
    layers_green_walk_L = HgWAddDoubleLayer(windowID);

    layers_pink_punch = HgWAddDoubleLayer(windowID);
    layers_pink_jump = HgWAddDoubleLayer(windowID);
    layers_pink_wait = HgWAddDoubleLayer(windowID);
    layers_pink_walk = HgWAddDoubleLayer(windowID);
    layers_pink_punch_L = HgWAddDoubleLayer(windowID);
    layers_pink_jump_L = HgWAddDoubleLayer(windowID);
    layers_pink_wait_L = HgWAddDoubleLayer(windowID);
    layers_pink_walk_L = HgWAddDoubleLayer(windowID);

    layers_red_punch = HgWAddDoubleLayer(windowID);
    layers_red_jump = HgWAddDoubleLayer(windowID);
    layers_red_wait = HgWAddDoubleLayer(windowID);
    layers_red_walk = HgWAddDoubleLayer(windowID);
    layers_red_punch_L = HgWAddDoubleLayer(windowID);
    layers_red_jump_L = HgWAddDoubleLayer(windowID);
    layers_red_wait_L = HgWAddDoubleLayer(windowID);
    layers_red_walk_L = HgWAddDoubleLayer(windowID);

    int layerID_title_font;              //タイトルの文字

    int layerID_mode_select;        //モード選択画面

    int layerID_chara_select;       //キャラ選択
    int layerID_chara_frame;        //フレーム画像のレイヤー
    int layerID_triangle;           //ゲージ
    int layerID_statusbar;          //ステータスバー

    int layerID_back;               //背景
    int layerID_ready;              //ready
    int layerID_player_enemy_gauge; //色のついたゲージ
    int layerID_char_status;        //ステータス
    int layerID_status;             //ゲーム内の文字
    int layerID_game_set;           //ゲームセットの文字

    int layerID_punch_Enemy[10];   //右向き
    int layerID_jump_Enemy[10];    //右向き
    int layerID_wait_Enemy[6];     //右向き
    int layerID_walk_Enemy[8];     //右向き
    int layerID_punch_Enemy_L[10]; //左向き
    int layerID_jump_Enemy_L[10];  //左向き
    int layerID_wait_Enemy_L[6];   //左向き
    int layerID_walk_Enemy_L[8];   //左向き

    int layerID_punch_Player[10];   //右向き
    int layerID_jump_Player[10];    //右向き
    int layerID_wait_Player[6];     //右向き
    int layerID_walk_Player[8];     //右向き
    int layerID_punch_Player_L[10]; //左向き
    int layerID_jump_Player_L[10];  //左向き
    int layerID_wait_Player_L[6];   //左向き
    int layerID_walk_Player_L[8];   //左向き

    int layerID_punch_Green[10];   //右向き
    int layerID_jump_Green[10];    //右向き
    int layerID_wait_Green[6];     //右向き
    int layerID_walk_Green[8];     //右向き
    int layerID_punch_Green_L[10]; //左向き
    int layerID_jump_Green_L[10];  //左向き
    int layerID_wait_Green_L[6];   //左向き
    int layerID_walk_Green_L[8];   //左向き

    int layerID_punch_Pink[10];   //右向き
    int layerID_jump_Pink[10];    //右向き
    int layerID_wait_Pink[6];     //右向き
    int layerID_walk_Pink[8];     //右向き
    int layerID_punch_Pink_L[10]; //左向き
    int layerID_jump_Pink_L[10];  //左向き
    int layerID_wait_Pink_L[6];   //左向き
    int layerID_walk_Pink_L[8];   //左向き

    int layerID_punch_Red[10];   //右向き
    int layerID_jump_Red[10];    //右向き
    int layerID_wait_Red[6];     //右向き
    int layerID_walk_Red[8];     //右向き
    int layerID_punch_Red_L[10]; //左向き
    int layerID_jump_Red_L[10];  //左向き
    int layerID_wait_Red_L[6];   //左向き
    int layerID_walk_Red_L[8];   //左向き

    //ウェイト
    int player_w[6] = {player_w1,player_w2,player_w3,player_w4,player_w5,player_w6};
    int player_wL[6] = {player_w1L,player_w2L,player_w3L,player_w4L,player_w5L,player_w6L};
    
    int enemy_w[6] = {enemy_w1,enemy_w2,enemy_w3,enemy_w4,enemy_w5,enemy_w6};
    int enemy_wL[6] = {enemy_w1L,enemy_w2L,enemy_w3L,enemy_w4L,enemy_w5L,enemy_w6L};

    int green_w[6] = {green_w1,green_w2,green_w3,green_w4,green_w5,green_w6};
    int green_wL[6] = {green_w1L,green_w2L,green_w3L,green_w4L,green_w5L,green_w6L};

    int pink_w[6] = {pink_w1,pink_w2,pink_w3,pink_w4,pink_w5,pink_w6};
    int pink_wL[6] = {pink_w1L,pink_w2L,pink_w3L,pink_w4L,pink_w5L,pink_w6L};

    int red_w[6] = {red_w1,red_w2,red_w3,red_w4,red_w5,red_w6};
    int red_wL[6] = {red_w1L,red_w2L,red_w3L,red_w4L,red_w5L,red_w6L};
    //パンチ
    int player_p[10] = {player_p1,player_p2,player_p3,player_p4,player_p5,player_p6,player_p7,player_p8,player_p9,player_p10};
    int player_pL[10] = {player_p1L,player_p2L,player_p3L,player_p4L,player_p5L,player_p6L,player_p7L,player_p8L,player_p9L,player_p10L};

    int enemy_p[10] = {enemy_p1,enemy_p2,enemy_p3,enemy_p4,enemy_p5,enemy_p6,enemy_p7,enemy_p8,enemy_p9,enemy_p10};
    int enemy_pL[10] = {enemy_p1L,enemy_p2L,enemy_p3L,enemy_p4L,enemy_p5L,enemy_p6L,enemy_p7L,enemy_p8L,enemy_p9L,enemy_p10L};

    int green_p[10] = {green_p1,green_p2,green_p3,green_p4,green_p5,green_p6,green_p7,green_p8,green_p9,green_p10};
    int green_pL[10] = {green_p1L,green_p2L,green_p3L,green_p4L,green_p5L,green_p6L,green_p7L,green_p8L,green_p9L,green_p10L};

    int pink_p[10] = {pink_p1,pink_p2,pink_p3,pink_p4,pink_p5,pink_p6,pink_p7,pink_p8,pink_p9,pink_p10};
    int pink_pL[10] = {pink_p1L,pink_p2L,pink_p3L,pink_p4L,pink_p5L,pink_p6L,pink_p7L,pink_p8L,pink_p9L,pink_p10L};

    int red_p[10] = {red_p1,red_p2,red_p3,red_p4,red_p5,red_p6,red_p7,red_p8,red_p9,red_p10};
    int red_pL[10] = {red_p1L,red_p2L,red_p3L,red_p4L,red_p5L,red_p6L,red_p7L,red_p8L,red_p9L,red_p10L};

    //ジャンプ
    int player_j[10] = {player_j1,player_j2,player_j3,player_j4,player_j5,player_j6,player_j7,player_j8,player_j9,player_j10};
    int player_jL[10] = {player_j1L,player_j2L,player_j3L,player_j4L,player_j5L,player_j6L,player_j7L,player_j8L,player_j9L,player_j10L};

    int enemy_j[10] = {enemy_j1,enemy_j2,enemy_j3,enemy_j4,enemy_j5,enemy_j6,enemy_j7,enemy_j8,enemy_j9,enemy_j10};
    int enemy_jL[10] = {enemy_j1L,enemy_j2L,enemy_j3L,enemy_j4L,enemy_j5L,enemy_j6L,enemy_j7L,enemy_j8L,enemy_j9L,enemy_j10L};

    int green_j[10] = {green_j1,green_j2,green_j3,green_j4,green_j5,green_j6,green_j7,green_j8,green_j9,green_j10};
    int green_jL[10] = {green_j1L,green_j2L,green_j3L,green_j4L,green_j5L,green_j6L,green_j7L,green_j8L,green_j9L,green_j10L};

    int pink_j[10] = {pink_j1,pink_j2,pink_j3,pink_j4,pink_j5,pink_j6,pink_j7,pink_j8,pink_j9,pink_j10};
    int pink_jL[10] = {pink_j1L,pink_j2L,pink_j3L,pink_j4L,pink_j5L,pink_j6L,pink_j7L,pink_j8L,pink_j9L,pink_j10L};

    int red_j[10] = {red_j1,red_j2,red_j3,red_j4,red_j5,red_j6,red_j7,red_j8,red_j9,red_j10};
    int red_jL[10] = {red_j1L,red_j2L,red_j3L,red_j4L,red_j5L,red_j6L,red_j7L,red_j8L,red_j9L,red_j10L};

    //歩き
    int player_wk[8] = {player_wk1,player_wk2,player_wk3,player_wk4,player_wk5,player_wk6,player_wk7,player_wk8};
    int player_wkL[8] = {player_wk1L,player_wk2L,player_wk3L,player_wk4L,player_wk5L,player_wk6L,player_wk7L,player_wk8L};

    int enemy_wk[8] = {enemy_wk1,enemy_wk2,enemy_wk3,enemy_wk4,enemy_wk5,enemy_wk6,enemy_wk7,enemy_wk8};
    int enemy_wkL[8] = {enemy_wk1L,enemy_wk2L,enemy_wk3L,enemy_wk4L,enemy_wk5L,enemy_wk6L,enemy_wk7L,enemy_wk8L};

    int green_wk[8] = {green_wk1,green_wk2,green_wk3,green_wk4,green_wk5,green_wk6,green_wk7,green_wk8};
    int green_wkL[8] = {green_wk1L,green_wk2L,green_wk3L,green_wk4L,green_wk5L,green_wk6L,green_wk7L,green_wk8L};

    int pink_wk[8] = {pink_wk1,pink_wk2,pink_wk3,pink_wk4,pink_wk5,pink_wk6,pink_wk7,pink_wk8};
    int pink_wkL[8] = {pink_wk1L,pink_wk2L,pink_wk3L,pink_wk4L,pink_wk5L,pink_wk6L,pink_wk7L,pink_wk8L};

    int red_wk[8] = {red_wk1,red_wk2,red_wk3,red_wk4,red_wk5,red_wk6,red_wk7,red_wk8};
    int red_wkL[8] = {red_wk1L,red_wk2L,red_wk3L,red_wk4L,red_wk5L,red_wk6L,red_wk7L,red_wk8L};

    for(;;){
        switch (game_status){
            case 0:
                srand(time(NULL));  // 乱数を現在時刻で初期化する
                int frame_y = 600;                      //モード選択画面のフレーム画像を初期Y座標
                int frame_y_up = 0;            //フレームのY座標が一番上の位置に来たら、+1
                int frame_y_down = 0;          //フレームのY座標が一番下の位置に来たら、+1
                int mode_select_sound_cnt = 0;
                int mode_status = 0;        //1:初級、2:中級、3:上級
                int ranking_y = 180;
                int rank = 0;

                int power_player_and_enemy = 0;   //選択したプレイヤーの攻撃力
                int jump_player_and_enemy = 0;    //選択したプレイヤーのジャンプ力
                int speed_player_and_enemy = 0;   //選択したプレイヤーのスピード

                //---------------タイトル画面---------------------
                int title_font_x1 = -160;    //vs
                int title_font_x2 = WIDTH + 380;   //Fightr
                int title_font_x3 = 510;
                int title_font_x4 = 960;
                int title_font_x5 = 730;
                double title_font_z = 10.0;     //.と!
                int game_start = 0;
                bool font_ok = false;       //vsとfightrのアニメーションの状態を保存するフラグ false:アニメーションが終わってない
                bool title_move_ok = false;

                //---------------キャラクター選択画面---------------------
                int player_select_x = -500;
                int icon1_x = 0, icon2_x = 0, icon3_x = 0, icon4_x = 0, icon5_x = 0;
                int frame2_x = 80;
                int frame2_x_cnt = 1;   //1で一番左を選択している状態
                int aa = 0, bb = 0, cc = 0, dd = 0, ss1 = 0, ss2 = 0, ss3 = 0;
                int select_case = 0;    //0:パンチ、1:ジャンプ、2:歩き、3:ウェイト
                int player_y_select = 100;
                int triangle_x[15] = {542,542,542,542,542,542,542,542,542,542,542,542,542,542,542};
                int triangle_gx[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                int chara_select_back = 0;
                int enemy_number;
                /*
                int triangle_x1 = 542,triangle_x2 = 542,triangle_x3 = 542;          //三角画像の初期位置(白色)
                int triangle_x4 = 542,triangle_x5 = 542,triangle_x6 = 542;          //三角画像の初期位置(黒色)
                int triangle_x7 = 542,triangle_x8 = 542,triangle_x9 = 542;          //三角画像の初期位置(緑色)
                int triangle_x10 = 542,triangle_x11 = 542,triangle_x12 = 542;          //三角画像の初期位置(ピンク色)
                int triangle_x13 = 542,triangle_x14 = 542,triangle_x15 = 542;          //三角画像の初期位置(赤色)
                
                int triangle_gx1 = 0,triangle_gx2 = 0,triangle_gx3 = 0;       //ゲージの初期幅(白色)
                int triangle_gx4 = 0,triangle_gx5 = 0,triangle_gx6 = 0;       //ゲージの初期幅(黒色)
                int triangle_gx7 = 0,triangle_gx8 = 0,triangle_gx9 = 0;       //ゲージの初期幅(緑色)
                int triangle_gx10 = 0,triangle_gx11 = 0,triangle_gx12 = 0;       //ゲージの初期幅(ピンク色)
                int triangle_gx13 = 0,triangle_gx14 = 0,triangle_gx15 = 0;       //ゲージの初期幅(赤色)
                */
                int triangle_dif_x1 = 0,triangle_dif_x2 = 0,triangle_dif_x3 = 0;    //それぞれの三角画像の位置
                int triangle_dif_gx1 = 0,triangle_dif_gx2 = 0,triangle_dif_gx3 = 0; //それぞれのゲージの位置
                bool player_y_jump_f = false;   //キャラクターのジャンプが頂点に達した場合true

                HgClear();
                HgSoundVolume(bgm_1,1.0,1);
                HgSoundPlay(bgm_1);
                while(game_start == 0){
                    HgWSetEventMask(windowID,HG_KEY_DOWN);
                    hgevent *event = HgEventNonBlocking();
                    layerID_title_font = HgLSwitch(&layers_title_font);
                    HgLClear(layerID_title_font);
                    HgWImageDraw(layerID_title_font,0,0,title_back);
                    HgWImageDraw(layerID_title_font,title_font_x1, 700,title_1);    //vs
                    HgWImageDraw(layerID_title_font,title_font_x2,680,title_3);     //fightr
                    if(title_font_x1 <= 300 && font_ok == false){
                        title_font_x1 += 30;
                    }
                    if (title_font_x1 == 320 && title_font_x2 >= 550){
                        title_font_x2 -= 30;
                    }
                    if (title_font_x2 == 520){
                        font_ok = true;
                    }
                    if (title_font_x2 == 520 && title_font_z > 1){
                        title_font_z -= 0.5;
                    }
                    if (font_ok == true){
                        HgWImagePut(layerID_title_font,title_font_x3,720,title_2,title_font_z,0);   //.
                        HgWImagePut(layerID_title_font,title_font_x4,745,title_4,title_font_z,0);   //!
                    }
                    if (title_font_z == 1.0){
                        if (title_font_x1 > 0 && title_move_ok == false){
                            title_font_x1 -= 2;
                            title_font_x2 -= 2;
                            title_font_x3 -= 2;
                            title_font_x4 -= 2;
                            title_font_x5 -= 2;
                        }
                        if(title_font_x1 <= 0){
                            title_move_ok = true;
                        }
                        if (title_font_x4 < 1280 - 45 && title_move_ok == true){
                            title_font_x1 += 2;
                            title_font_x2 += 2;
                            title_font_x3 += 2;
                            title_font_x4 += 2;
                            title_font_x5 += 2;
                        }
                        if (title_font_x4 >= 1280 - 45){
                            title_move_ok = false;
                        }
                        HgWImageDraw(layerID_title_font,title_font_x5,630,online);
                        HgWSetFont(layerID_title_font,HG_TI,30);
                        HgWSetColor(layerID_title_font,HG_BLUE);
                        HgWText(layerID_title_font,580,550,"操作方法");
                        HgWText(layerID_title_font,500,390,"C\t\t\t\t\t\t\t:パンチ\nスペースキー  :ジャンプ\n<\t\t\t\t\t\t\t:左に移動\n>\t\t\t\t\t\t\t:右に移動");
                        HgWSetColor(layerID_title_font,HG_WHITE);
                        HgWText(layerID_title_font,450,200,"スペースキーを押してください");
                        HgWSetColor(layerID_title_font,HG_BLACK);
                        HgWText(layerID_title_font,510,170,"Qキーでゲーム終了");
                        HgWSetFont(layerID_title_font,HG_T,20);
                        HgWSetColor(layerID_title_font,HG_RED);
                        HgWText(layerID_title_font,280,290,"パンチやジャンプを駆使して、敵のHPを減らしてください。\nHPが0になった方が負けです。またタイムが0になった時点でも負けになります。\n敵を倒すまでの時間をスコアにし、試合終了後にオンラインのランキング順位が表示されます。");
                    }
                    if (event != NULL){
                        if (event -> type == HG_KEY_DOWN){
                            switch (event -> ch){
                                case ' ':   //ゲームスタート
                                    HgSoundStop(bgm_1);
                                    game_start = 1;
                                    game_status = 1;    //モード選択画面へ
                                    break;

                                case 'q':
                                    HgClose();
                                    return 0;
                            }
                        }
                    }
                }
            break;
            case 1: //モード選択画面
                if (mode_select_sound_cnt == 0){
                    HgSoundVolume(bgm_4,1.0,1);
                    HgSoundPlay(bgm_4);
                }
                mode_select_sound_cnt = 1;
                //HgClear();
                layerID_mode_select = HgLSwitch(&layers_mode_select);
                HgLClear(layerID_mode_select);
                HgWImageDraw(layerID_mode_select,0,600,easy);
                HgWImageDraw(layerID_mode_select,0,350,normal);
                HgWImageDraw(layerID_mode_select,0,100,hard);
                HgWImageDraw(layerID_mode_select,0,0,message);
                HgWImageDraw(layerID_mode_select,0,frame_y,frame);
                event = HgEventNonBlocking();
                HgWSetFont(layerID_mode_select,HG_T,20);
                HgWSetColor(layerID_mode_select,HG_WHITE);
                HgWText(layerID_mode_select,600,40,"Aキーで上へ、Zキーで下へ選択し、スペースキーで決定  Qキーで終了");
                if (frame_y == 600){
                    mode_status = 1;
                    HgWText(layerID_mode_select,50,40,"敵の強さが弱いモードです。(ランキングはありません)");
                }
                if (frame_y == 350){
                    mode_status = 2;
                    HgWText(layerID_mode_select,50,40,"敵の強さが程よいモードです。(ランキングはありません)");
                }
                if (frame_y == 100){
                    mode_status = 3;
                    HgWText(layerID_mode_select,50,40,"敵の強さが異常なモードです。(ランキングあり)");
                }
                if (event != NULL){
                    switch (event -> ch){
                        case 'a':   //上
                        HgSoundVolume(se_2,0.7,0);
                        HgSoundPlay(se_2);
                        if (frame_y < 600){
                            frame_y += 250;
                        }
                        if (frame_y >= 600){
                            frame_y_up += 1;
                        }
                        if (frame_y >= 600 && frame_y_up == 2){
                            frame_y = 100;
                            frame_y_up = 0;
                        }
                        break;
                        case 'z':   //下
                        HgSoundVolume(se_2,0.7,0);
                        HgSoundPlay(se_2);
                        if (frame_y > 100){
                            frame_y -= 250;
                        }
                        if (frame_y <= 100){
                            frame_y_down += 1;
                        }
                        if (frame_y <= 100 && frame_y_down == 2){
                            frame_y = 600;
                            frame_y_down = 0;
                        }
                        break;
                        case ' ':   //スペース
                            HgSoundStop(bgm_4);
                            HgClear();
                            player_select_x = -500;
                            icon1_x = 0, icon2_x = 0, icon3_x = 0, icon4_x = 0, icon5_x = 0;
                            frame2_x = 80;
                            frame2_x_cnt = 1;   //1で一番左を選択している状態
                            aa = 0, bb = 0, cc = 0, dd = 0, ss1 = 0, ss2 = 0, ss3 = 0;
                            select_case = 0;    //0:パンチ、1:ジャンプ、2:歩き、3:ウェイト
                            player_y_select = 100;
                            game_status = 5;
                        break;
                        case 'q':
                            HgClose();
                            return 0;
                    }
                }
                break;
            case 5: //キャラ選択
                srand(time(NULL));  // 乱数を現在時刻で初期化する
                layerID_chara_select = HgLSwitch(&layers_chara_select);
                layerID_chara_frame = HgLSwitch(&layers_chara_frame);
                layerID_triangle = HgLSwitch(&layers_triangle);
                layerID_statusbar = HgLSwitch(&layers_statusbar);

                layerID_punch_Player[aa] = HgLSwitch(&layers_player_punch);
                layerID_jump_Player[bb] = HgLSwitch(&layers_player_jump);
                layerID_walk_Player[cc] = HgLSwitch(&layers_player_walk);
                layerID_wait_Player[dd] = HgLSwitch(&layers_player_wait);

                layerID_punch_Enemy[aa] = HgLSwitch(&layers_enemy_punch);
                layerID_jump_Enemy[bb] = HgLSwitch(&layers_enemy_jump);
                layerID_walk_Enemy[cc] = HgLSwitch(&layers_enemy_walk);
                layerID_wait_Enemy[dd] = HgLSwitch(&layers_enemy_wait);
                
                
                layerID_punch_Green[aa] = HgLSwitch(&layers_green_punch);
                layerID_jump_Green[bb] = HgLSwitch(&layers_green_jump);
                layerID_walk_Green[cc] = HgLSwitch(&layers_green_walk);
                layerID_wait_Green[dd] = HgLSwitch(&layers_green_wait);

                layerID_punch_Pink[aa] = HgLSwitch(&layers_pink_punch);
                layerID_jump_Pink[bb] = HgLSwitch(&layers_pink_jump);
                layerID_walk_Pink[cc] = HgLSwitch(&layers_pink_walk);
                layerID_wait_Pink[dd] = HgLSwitch(&layers_pink_wait);

                layerID_punch_Red[aa] = HgLSwitch(&layers_red_punch);
                layerID_jump_Red[bb] = HgLSwitch(&layers_red_jump);
                layerID_walk_Red[cc] = HgLSwitch(&layers_red_walk);
                layerID_wait_Red[dd] = HgLSwitch(&layers_red_wait);
                
                HgLClear(layerID_chara_select);
                HgLClear(layerID_chara_frame);
                HgLClear(layerID_statusbar);
                HgLClear(layerID_triangle);

                HgLClear(layerID_punch_Player[aa]);
                HgLClear(layerID_jump_Player[bb]);
                HgLClear(layerID_walk_Player[cc]);
                HgLClear(layerID_wait_Player[dd]);

                HgLClear(layerID_punch_Enemy[aa]);
                HgLClear(layerID_jump_Enemy[bb]);
                HgLClear(layerID_walk_Enemy[cc]);
                HgLClear(layerID_wait_Enemy[dd]);

                HgLClear(layerID_punch_Green[aa]);
                HgLClear(layerID_jump_Green[bb]);
                HgLClear(layerID_walk_Green[cc]);
                HgLClear(layerID_wait_Green[dd]);

                HgLClear(layerID_punch_Pink[aa]);
                HgLClear(layerID_jump_Pink[bb]);
                HgLClear(layerID_walk_Pink[cc]);
                HgLClear(layerID_wait_Pink[dd]);

                HgLClear(layerID_punch_Red[aa]);
                HgLClear(layerID_jump_Red[bb]);
                HgLClear(layerID_walk_Red[cc]);
                HgLClear(layerID_wait_Red[dd]);

                event = HgEventNonBlocking();
                HgWSetFillColor(layerID_chara_select,HG_BLACK);
                HgWBoxFill(layerID_chara_select,0,0,WIDTH,HIGHT,0);
                if (player_select_x >= 0){
                    HgWSetFont(layerID_statusbar,HG_T,15);
                    HgWSetColor(layerID_statusbar,HG_WHITE);
                    HgWSetFillColor(layerID_triangle,HG_YELLOW);
                    HgWText(layerID_statusbar,497,810,"Wキー長押しで戻る");
                    HgWBoxFill(layerID_triangle,594 - chara_select_back,770,chara_select_back,30,0);
                    HgWImageDraw(layerID_statusbar,497,770,back);
                }
                if (player_select_x < 0){
                    player_select_x += 20;
                }
                if (icon1_x < 80){
                    icon1_x += 20;
                }
                if (icon2_x < 300){
                    icon2_x += 20;
                }
                if (icon3_x < 520){
                    icon3_x += 20;
                }
                if (icon4_x < 740){
                    icon4_x += 20;
                }
                if (icon5_x < 960){
                    icon5_x += 20;
                }
                if (icon5_x >= 960){
                    HgWImageDraw(layerID_chara_frame,frame2_x,550,frame2);
                    HgWSetFont(layerID_chara_frame,HG_T,30);
                    HgWSetColor(layerID_chara_frame,HG_WHITE);
                    HgWText(layerID_chara_frame,frame2_x + 50,500,"選択中");
                    HgWText(layerID_chara_frame,540,40,"＜ ＞キーで移動　スペースキーで決定");
                }
                if (frame2_x_cnt == 1){
                    frame2_x = 80;
                }
                if (frame2_x_cnt == 2){
                    frame2_x = 300;
                }
                if (frame2_x_cnt == 3){
                    frame2_x = 520;
                }
                if (frame2_x_cnt == 4){
                    frame2_x = 740;
                }
                if (frame2_x_cnt == 5){
                    frame2_x = 960;
                }
                HgWImageDraw(layerID_chara_select,player_select_x,770,player_select);
                HgWImageDraw(layerID_chara_select,icon1_x,550,icon1);
                HgWImageDraw(layerID_chara_select,icon2_x,550,icon2);
                HgWImageDraw(layerID_chara_select,icon3_x,550,icon3);
                HgWImageDraw(layerID_chara_select,icon4_x,550,icon4);
                HgWImageDraw(layerID_chara_select,icon5_x,550,icon5);
                if (icon5_x >= 960){
                    if (frame2_x_cnt == 1){ //白色プレイヤー
                        ss1 = 0;
                        ss2 = 1;
                        ss3 = 2;
                        triangle_dif_x1 = 842;  //B
                        triangle_dif_gx1 = 300;
                        triangle_dif_x2 = 1002; //A
                        triangle_dif_gx2 = 460;
                        triangle_dif_x3 = 842;  //B
                        triangle_dif_gx3 = 300;
                        HgWImageDraw(layerID_chara_select,520,420,statustext);
                        HgWImageDraw(layerID_statusbar,470,310,statusbar);
                        HgWImageDraw(layerID_statusbar,470,200,statusbar);
                        HgWImageDraw(layerID_statusbar,470,90,statusbar);
                        HgWSetFont(layerID_statusbar,HG_T,20);
                        HgWSetColor(layerID_statusbar,HG_WHITE);
                        HgWText(layerID_statusbar,350,340,"パワー");
                        HgWText(layerID_statusbar,350,230,"ジャンプ力");
                        HgWText(layerID_statusbar,350,130,"スピード");
                        HgWSetFillColor(layerID_triangle,HG_YELLOW);
                        //C:642,B:842,A:1002,S:1162
                        //C:100,B:300,A:460,S:620
                        HgWImageDraw(layerID_triangle,triangle_x[ss1],330,triangle);    //三角
                        HgWBoxFill(layerID_triangle,542,329,triangle_gx[ss1],46,0);  //X+72,Y+19

                        HgWImageDraw(layerID_triangle,triangle_x[ss2],220,triangle);    //三角
                        HgWBoxFill(layerID_triangle,542,219,triangle_gx[ss2],46,0);

                        HgWImageDraw(layerID_triangle,triangle_x[ss3],110,triangle);    //三角
                        HgWBoxFill(layerID_triangle,542,109,triangle_gx[ss3],46,0);

                        if (triangle_x[ss1] < triangle_dif_x1){
                            triangle_x[ss1] += 80;
                        }
                        if (triangle_gx[ss1] < triangle_dif_gx1){
                            triangle_gx[ss1] += 80;
                        }

                        if (triangle_x[ss2] < triangle_dif_x2){
                            triangle_x[ss2] += 80;
                        }
                        if (triangle_gx[ss2] < triangle_dif_gx2){
                            triangle_gx[ss2] += 80;
                        }

                        if (triangle_x[ss3] < triangle_dif_x3){
                            triangle_x[ss3] += 80;
                        }
                        if (triangle_gx[ss3] < triangle_dif_gx3){
                            triangle_gx[ss3] += 80;
                        }

                        switch (select_case){
                            case 0:
                                HgWImageDraw(layerID_punch_Player[aa],100,100,player_p[aa]);    //パンチ
                                if (aa <= 10){
                                    aa++;
                                }
                                if (aa == 10){
                                    aa = 0;
                                    select_case = 1;
                                }
                                break;
                            case 1:
                                HgWImageDraw(layerID_jump_Player[bb],100,player_y_select,player_j[bb]);    //ジャンプ
                                if (bb <= 10 && player_y_jump_f == false){
                                    bb++;
                                    player_y_select += 30;
                                }
                                if (bb == 10){
                                    player_y_jump_f = true;
                                }
                                if (bb >= 0 && player_y_jump_f == true){
                                    bb--;
                                    player_y_select -= 30;
                                }
                                if (bb == 0){
                                    bb = 0;
                                    player_y_jump_f = false;
                                    select_case = 2;
                                }
                                break;
                            case 2:
                                HgWImageDraw(layerID_walk_Player[cc],100,100,player_wk[cc]);    //歩き
                                if (cc <= 8){
                                    cc++;
                                }
                                if (cc == 8){
                                    cc = 0;
                                    select_case = 3;
                                }
                                break;
                            case 3:
                                HgWImageDraw(layerID_wait_Player[dd],100,100,player_w[dd]);    //ウェイト
                                if (dd <= 6){
                                    dd++;
                                }
                                if (dd == 6){
                                    dd = 0;
                                    select_case = 0;
                                }
                                break;
                            }
                        }
                        if (frame2_x_cnt == 2){ //黒色プレイヤー
                            ss1 = 3;
                            ss2 = 4;
                            ss3 = 5;
                            triangle_dif_x1 = 1002; //A
                            triangle_dif_gx1 = 460;
                            triangle_dif_x2 = 842;  //B
                            triangle_dif_gx2 = 300;
                            triangle_dif_x3 = 1002; //A
                            triangle_dif_gx3 = 460;
                            HgWImageDraw(layerID_chara_select,520,420,statustext);
                            HgWImageDraw(layerID_statusbar,470,310,statusbar);
                            HgWImageDraw(layerID_statusbar,470,200,statusbar);
                            HgWImageDraw(layerID_statusbar,470,90,statusbar);
                            HgWSetFont(layerID_statusbar,HG_T,20);
                            HgWSetColor(layerID_statusbar,HG_WHITE);
                            HgWText(layerID_statusbar,350,340,"パワー");
                            HgWText(layerID_statusbar,350,230,"ジャンプ力");
                            HgWText(layerID_statusbar,350,130,"スピード");
                            HgWSetFillColor(layerID_triangle,HG_YELLOW);
                            //C:642,B:842,A:1002,S:1162
                            //C:100,B:300,A:460,S:620
                            HgWImageDraw(layerID_triangle,triangle_x[ss1],330,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,329,triangle_gx[ss1],46,0);  //X+72,Y+19

                            HgWImageDraw(layerID_triangle,triangle_x[ss2],220,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,219,triangle_gx[ss2],46,0);

                            HgWImageDraw(layerID_triangle,triangle_x[ss3],110,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,109,triangle_gx[ss3],46,0);

                            if (triangle_x[ss1] < triangle_dif_x1){
                                triangle_x[ss1] += 80;
                            }
                            if (triangle_gx[ss1] < triangle_dif_gx1){
                                triangle_gx[ss1] += 80;
                            }

                            if (triangle_x[ss2] < triangle_dif_x2){
                                triangle_x[ss2] += 80;
                            }
                            if (triangle_gx[ss2] < triangle_dif_gx2){
                                triangle_gx[ss2] += 80;
                            }

                            if (triangle_x[ss3] < triangle_dif_x3){
                                triangle_x[ss3] += 80;
                            }
                            if (triangle_gx[ss3] < triangle_dif_gx3){
                                triangle_gx[ss3] += 80;
                            }
                        switch (select_case){
                            case 0:
                                HgWImageDraw(layerID_punch_Enemy[aa],100,100,enemy_p[aa]);    //パンチ
                                if (aa <= 10){
                                    aa++;
                                }
                                if (aa == 10){
                                    aa = 0;
                                    select_case = 1;
                                }
                                break;
                            case 1:
                                HgWImageDraw(layerID_jump_Enemy[bb],100,player_y_select,enemy_j[bb]);    //ジャンプ
                                if (bb <= 10 && player_y_jump_f == false){
                                    bb++;
                                    player_y_select += 30;
                                }
                                if (bb == 10){
                                    player_y_jump_f = true;
                                }
                                if (bb >= 0 && player_y_jump_f == true){
                                    bb--;
                                    player_y_select -= 30;
                                }
                                if (bb == 0){
                                    bb = 0;
                                    player_y_jump_f = false;
                                    select_case = 2;
                                }
                                break;
                            case 2:
                                HgWImageDraw(layerID_walk_Enemy[cc],100,100,enemy_wk[cc]);    //歩き
                                if (cc <= 8){
                                    cc++;
                                }
                                if (cc == 8){
                                    cc = 0;
                                    select_case = 3;
                                }
                                break;
                            case 3:
                                HgWImageDraw(layerID_wait_Enemy[dd],100,100,enemy_w[dd]);    //ウェイト
                                if (dd <= 6){
                                    dd++;
                                }
                                if (dd == 6){
                                    dd = 0;
                                    select_case = 0;
                                }
                                break;
                            }
                        }
                        if (frame2_x_cnt == 3){ //緑色プレイヤー
                            ss1 = 6;
                            ss2 = 7;
                            ss3 = 8;
                            triangle_dif_x1 = 1162; //S
                            triangle_dif_gx1 = 620;
                            triangle_dif_x2 = 842;  //B
                            triangle_dif_gx2 = 300;
                            triangle_dif_x3 = 642;  //C
                            triangle_dif_gx3 = 100;
                            HgWImageDraw(layerID_chara_select,520,420,statustext);
                            HgWImageDraw(layerID_statusbar,470,310,statusbar);
                            HgWImageDraw(layerID_statusbar,470,200,statusbar);
                            HgWImageDraw(layerID_statusbar,470,90,statusbar);
                            HgWSetFont(layerID_statusbar,HG_T,20);
                            HgWSetColor(layerID_statusbar,HG_WHITE);
                            HgWText(layerID_statusbar,350,340,"パワー");
                            HgWText(layerID_statusbar,350,230,"ジャンプ力");
                            HgWText(layerID_statusbar,350,130,"スピード");
                            HgWSetFillColor(layerID_triangle,HG_YELLOW);
                            //C:642,B:842,A:1002,S:1162
                            //C:100,B:300,A:460,S:620
                            HgWImageDraw(layerID_triangle,triangle_x[ss1],330,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,329,triangle_gx[ss1],46,0);  //X+72,Y+19

                            HgWImageDraw(layerID_triangle,triangle_x[ss2],220,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,219,triangle_gx[ss2],46,0);

                            HgWImageDraw(layerID_triangle,triangle_x[ss3],110,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,109,triangle_gx[ss3],46,0);

                            if (triangle_x[ss1] < triangle_dif_x1){
                                triangle_x[ss1] += 80;
                            }
                            if (triangle_gx[ss1] < triangle_dif_gx1){
                                triangle_gx[ss1] += 80;
                            }

                            if (triangle_x[ss2] < triangle_dif_x2){
                                triangle_x[ss2] += 80;
                            }
                            if (triangle_gx[ss2] < triangle_dif_gx2){
                                triangle_gx[ss2] += 80;
                            }

                            if (triangle_x[ss3] < triangle_dif_x3){
                                triangle_x[ss3] += 80;
                            }
                            if (triangle_gx[ss3] < triangle_dif_gx3){
                                triangle_gx[ss3] += 80;
                            }
                        switch (select_case){
                            case 0:
                                HgWImageDraw(layerID_punch_Green[aa],100,100,green_p[aa]);    //パンチ
                                if (aa <= 10){
                                    aa++;
                                }
                                if (aa == 10){
                                    aa = 0;
                                    select_case = 1;
                                }
                                break;
                            case 1:
                                HgWImageDraw(layerID_jump_Green[bb],100,player_y_select,green_j[bb]);    //ジャンプ
                                if (bb <= 10 && player_y_jump_f == false){
                                    bb++;
                                    player_y_select += 30;
                                }
                                if (bb == 10){
                                    player_y_jump_f = true;
                                }
                                if (bb >= 0 && player_y_jump_f == true){
                                    bb--;
                                    player_y_select -= 30;
                                }
                                if (bb == 0){
                                    bb = 0;
                                    player_y_jump_f = false;
                                    select_case = 2;
                                }
                                break;
                            case 2:
                                HgWImageDraw(layerID_walk_Green[cc],100,100,green_wk[cc]);    //歩き
                                if (cc <= 8){
                                    cc++;
                                }
                                if (cc == 8){
                                    cc = 0;
                                    select_case = 3;
                                }
                                break;
                            case 3:
                                HgWImageDraw(layerID_wait_Green[dd],100,100,green_w[dd]);    //ウェイト
                                if (dd <= 6){
                                    dd++;
                                }
                                if (dd == 6){
                                    dd = 0;
                                    select_case = 0;
                                }
                                break;
                            }
                        }
                        if (frame2_x_cnt == 4){ //ピンク色プレイヤー
                            ss1 = 9;
                            ss2 = 10;
                            ss3 = 11;
                            triangle_dif_x1 = 842;  //B
                            triangle_dif_gx1 = 300;
                            triangle_dif_x2 = 842;  //B
                            triangle_dif_gx2 = 300;
                            triangle_dif_x3 = 1162; //S
                            triangle_dif_gx3 = 620;
                            HgWImageDraw(layerID_chara_select,520,420,statustext);
                            HgWImageDraw(layerID_statusbar,470,310,statusbar);
                            HgWImageDraw(layerID_statusbar,470,200,statusbar);
                            HgWImageDraw(layerID_statusbar,470,90,statusbar);
                            HgWSetFont(layerID_statusbar,HG_T,20);
                            HgWSetColor(layerID_statusbar,HG_WHITE);
                            HgWText(layerID_statusbar,350,340,"パワー");
                            HgWText(layerID_statusbar,350,230,"ジャンプ力");
                            HgWText(layerID_statusbar,350,130,"スピード");
                            HgWSetFillColor(layerID_triangle,HG_YELLOW);
                            //C:642,B:842,A:1002,S:1162
                            //C:100,B:300,A:460,S:620
                            HgWImageDraw(layerID_triangle,triangle_x[ss1],330,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,329,triangle_gx[ss1],46,0);  //X+72,Y+19

                            HgWImageDraw(layerID_triangle,triangle_x[ss2],220,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,219,triangle_gx[ss2],46,0);

                            HgWImageDraw(layerID_triangle,triangle_x[ss3],110,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,109,triangle_gx[ss3],46,0);

                            if (triangle_x[ss1] < triangle_dif_x1){
                                triangle_x[ss1] += 80;
                            }
                            if (triangle_gx[ss1] < triangle_dif_gx1){
                                triangle_gx[ss1] += 80;
                            }

                            if (triangle_x[ss2] < triangle_dif_x2){
                                triangle_x[ss2] += 80;
                            }
                            if (triangle_gx[ss2] < triangle_dif_gx2){
                                triangle_gx[ss2] += 80;
                            }

                            if (triangle_x[ss3] < triangle_dif_x3){
                                triangle_x[ss3] += 80;
                            }
                            if (triangle_gx[ss3] < triangle_dif_gx3){
                                triangle_gx[ss3] += 80;
                            }
                        switch (select_case){
                            case 0:
                                HgWImageDraw(layerID_punch_Pink[aa],100,100,pink_p[aa]);    //パンチ
                                if (aa <= 10){
                                    aa++;
                                }
                                if (aa == 10){
                                    aa = 0;
                                    select_case = 1;
                                }
                                break;
                            case 1:
                                HgWImageDraw(layerID_jump_Pink[bb],100,player_y_select,pink_j[bb]);    //ジャンプ
                                if (bb <= 10 && player_y_jump_f == false){
                                    bb++;
                                    player_y_select += 30;
                                }
                                if (bb == 10){
                                    player_y_jump_f = true;
                                }
                                if (bb >= 0 && player_y_jump_f == true){
                                    bb--;
                                    player_y_select -= 30;
                                }
                                if (bb == 0){
                                    bb = 0;
                                    player_y_jump_f = false;
                                    select_case = 2;
                                }
                                break;
                            case 2:
                                HgWImageDraw(layerID_walk_Pink[cc],100,100,pink_wk[cc]);    //歩き
                                if (cc <= 8){
                                    cc++;
                                }
                                if (cc == 8){
                                    cc = 0;
                                    select_case = 3;
                                }
                                break;
                            case 3:
                                HgWImageDraw(layerID_wait_Pink[dd],100,100,pink_w[dd]);    //ウェイト
                                if (dd <= 6){
                                    dd++;
                                }
                                if (dd == 6){
                                    dd = 0;
                                    select_case = 0;
                                }
                                break;
                            }
                        }
                        if (frame2_x_cnt == 5){ //赤色プレイヤー
                            ss1 = 12;
                            ss2 = 13;
                            ss3 = 14;
                            triangle_dif_x1 = 1002; //A
                            triangle_dif_gx1 = 460;
                            triangle_dif_x2 = 1162; //S
                            triangle_dif_gx2 = 620;
                            triangle_dif_x3 = 642;  //C
                            triangle_dif_gx3 = 100;
                            HgWImageDraw(layerID_chara_select,520,420,statustext);
                            HgWImageDraw(layerID_statusbar,470,310,statusbar);
                            HgWImageDraw(layerID_statusbar,470,200,statusbar);
                            HgWImageDraw(layerID_statusbar,470,90,statusbar);
                            HgWSetFont(layerID_statusbar,HG_T,20);
                            HgWSetColor(layerID_statusbar,HG_WHITE);
                            HgWText(layerID_statusbar,350,340,"パワー");
                            HgWText(layerID_statusbar,350,230,"ジャンプ力");
                            HgWText(layerID_statusbar,350,130,"スピード");
                            HgWSetFillColor(layerID_triangle,HG_YELLOW);
                            //C:642,B:842,A:1002,S:1162
                            //C:100,B:300,A:460,S:620
                            HgWImageDraw(layerID_triangle,triangle_x[ss1],330,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,329,triangle_gx[ss1],46,0);  //X+72,Y+19

                            HgWImageDraw(layerID_triangle,triangle_x[ss2],220,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,219,triangle_gx[ss2],46,0);

                            HgWImageDraw(layerID_triangle,triangle_x[ss3],110,triangle);    //三角
                            HgWBoxFill(layerID_triangle,542,109,triangle_gx[ss3],46,0);

                            if (triangle_x[ss1] < triangle_dif_x1){
                                triangle_x[ss1] += 80;
                            }
                            if (triangle_gx[ss1] < triangle_dif_gx1){
                                triangle_gx[ss1] += 80;
                            }

                            if (triangle_x[ss2] < triangle_dif_x2){
                                triangle_x[ss2] += 80;
                            }
                            if (triangle_gx[ss2] < triangle_dif_gx2){
                                triangle_gx[ss2] += 80;
                            }

                            if (triangle_x[ss3] < triangle_dif_x3){
                                triangle_x[ss3] += 80;
                            }
                            if (triangle_gx[ss3] < triangle_dif_gx3){
                                triangle_gx[ss3] += 80;
                            }
                        switch (select_case){
                            case 0:
                                HgWImageDraw(layerID_punch_Red[aa],100,100,red_p[aa]);    //パンチ
                                if (aa <= 10){
                                    aa++;
                                }
                                if (aa == 10){
                                    aa = 0;
                                    select_case = 1;
                                }
                                break;
                            case 1:
                                HgWImageDraw(layerID_jump_Red[bb],100,player_y_select,red_j[bb]);    //ジャンプ
                                if (bb <= 10 && player_y_jump_f == false){
                                    bb++;
                                    player_y_select += 30;
                                }
                                if (bb == 10){
                                    player_y_jump_f = true;
                                }
                                if (bb >= 0 && player_y_jump_f == true){
                                    bb--;
                                    player_y_select -= 30;
                                }
                                if (bb == 0){
                                    bb = 0;
                                    player_y_jump_f = false;
                                    select_case = 2;
                                }
                                break;
                            case 2:
                                HgWImageDraw(layerID_walk_Red[cc],100,100,red_wk[cc]);    //歩き
                                if (cc <= 8){
                                    cc++;
                                }
                                if (cc == 8){
                                    cc = 0;
                                    select_case = 3;
                                }
                                break;
                            case 3:
                                HgWImageDraw(layerID_wait_Red[dd],100,100,red_w[dd]);    //ウェイト
                                if (dd <= 6){
                                    dd++;
                                }
                                if (dd == 6){
                                    dd = 0;
                                    select_case = 0;
                                }
                                break;
                            }
                        }
                    }
                HgSetEventMask(HG_KEY_DOWN);
                if (event != NULL){
                    switch (event -> ch){
                        case ' ':   //スペース
                        if (icon5_x >= 960){
                            enemy_number = rand() % 5 + 1;
                            if (enemy_number == frame2_x_cnt){  //選択したキャラと敵が同じ場合
                                enemy_number = rand() % 5 + 1;  //もう一度敵を選び直す
                            }
                            if (enemy_number != frame2_x_cnt){
                                game_status = 4;
                            }
                        }
                        break;
                        case ',':   //左
                        if (icon5_x >= 960){
                            frame2_x_cnt --;
                            if(frame2_x_cnt == 0){
                                frame2_x_cnt = 5;
                            }
                        }
                        break;
                        case '.':   //右
                        if (icon5_x >= 960){
                            frame2_x_cnt ++;
                            if (frame2_x_cnt == 6){
                                frame2_x_cnt = 1;
                            }
                        }
                        break;
                        case 'w':
                        if (player_select_x >= 0){
                            HgSetEventMask(HG_KEY_DOWN | HG_KEY_UP);
                            if (chara_select_back < 100){
                                chara_select_back += 5;
                            }
                            if (chara_select_back >= 100){
                                game_status = 1;    //難易度選択画面に戻る
                                HgClear();
                                chara_select_back = 0;
                                for (int back = 0; back < 15; back ++){
                                    triangle_x[back] = 540;
                                    triangle_gx[back] = 0;
                                }
                            }
                            if (event -> type == HG_KEY_UP){    //Wキーが離された時
                                chara_select_back = 0;
                            }
                        }
                        break;
                        case 'q':
                            HgClose();
                            return 0;
                    }
                }
                break;
            case 4: //ゲームスタート
                srand(time(NULL));  // 乱数を現在時刻で初期化する
                HgClear();
                int space_ok = 0;
                int w_ok = 0;
                int jump = 0;
                int jump_enemy = 0;
                int player_LR = 0;              //0:右向き,1:左向き(Playerの初期向き)
                int enemy_LR = 1;               //0:右向き,1:左向き(敵の初期向き)
                int enemy_status = 0;           //敵の初期状態0：ウェイト
                int enemy_walk = 0;             //0〜9の間の値をランダムで出し、偶数のときに敵が歩く。奇数は歩かない。
                int enemy_walk_cnt = 0;
                int player_x = 200;
                int player_y = 100;
                int enemy_x = 800;
                int enemy_y = 100;
                int player_HP = 300;
                int enemy_HP = 300;
                int score = 700;
                int game_set_time = 0;
                int game_x = -350;
                int set_x = WIDTH + 350;
                int critical_random_player = 0;        //0〜9の間の値をランダムで出し、0と1の時だけプレイヤーがクリティカルダメージを与える。
                int critical_random_enemy = 0;        //0〜9の間の値をランダムで出し、0と1の時だけ敵がクリティカルダメージを与える。
                int critical_cnt_player = 0;            //クリティカルの画像(プレイヤー)を表示する時間をカウント
                int critical_cnt_enemy = 0;             //クリティカルの画像(敵)を表示する時間をカウント
                int a = 0, b = 0, c = 0, d = 0, p = 0, q = 0, w = 0, wk = 0, r = 0, g1 = 0, g2 = 0, g3 = 0, g4 = 0, p1= 0, p2 = 0, p3 = 0, p4 = 0, r1 = 0, r2 = 0, r3 = 0, r4 = 0;
                double black_player_x = 621;            //HPバーの黒の左下X
                double black_player_width = 0.0;              //HPバーの黒の幅
                double black_enemy_width = 0.0;                //HPバーの黒
                bool jump_f = false;
                bool punch_f = false;
                bool enemy_on = false;  //歩く以外のアニメーションを行なっているかを判断するフラグ(false:行なっていない、true:行なっている)
                bool critical_player_ok = false;    //クリティカル(プレイヤー)が入るとtrue
                bool critical_enemy_ok = false;     //クリティカル(敵)が入るとtrue
                bool game_set_f = false;
                bool game_set_warning = false;
                HgSoundVolume(voice_6,1.0,0);
                HgSoundPlay(voice_6);
                //------------------攻撃力------------------
                if (triangle_dif_x1 == 642){    //C
                    power_player_and_enemy = 10;
                }
                if (triangle_dif_x1 == 842){    //B
                    power_player_and_enemy = 15;
                }
                if (triangle_dif_x1 == 1002){   //A
                    power_player_and_enemy = 20;
                }
                if (triangle_dif_x1 == 1162){   //S
                    power_player_and_enemy = 25;
                }
                //------------------ジャンプ力------------------
                if (triangle_dif_x2 == 642){    //C
                    jump_player_and_enemy = 25;
                }
                if (triangle_dif_x2 == 842){    //B
                    jump_player_and_enemy = 30;
                }
                if (triangle_dif_x2 == 1002){   //A
                    jump_player_and_enemy = 35;
                }
                if (triangle_dif_x2 == 1162){   //S
                    jump_player_and_enemy = 40;
                }
                //------------------スピード------------------
                if (triangle_dif_x3 == 642){    //C
                    speed_player_and_enemy = 20;
                }
                if (triangle_dif_x3 == 842){    //B
                    speed_player_and_enemy = 25;
                }
                if (triangle_dif_x3 == 1002){   //A
                    speed_player_and_enemy = 30;
                }
                if (triangle_dif_x3 == 1162){   //S
                    speed_player_and_enemy = 40;
                }
                //------------------終わり------------------

                //Back_Line();
                for (r = 0; r < 200; r++){
                    layerID_ready = HgLSwitch(&layers_ready);
                    HgLClear(layerID_ready);
                    HgWImageDraw(layerID_ready,0,0,title_back);
                    HgWImageDraw(layerID_ready,400,400,ready_gra);
                    if (r > 50){
                        HgWImageDraw(layerID_ready,800,400,dot_gra);
                    }
                    if (r > 100){
                        HgWImageDraw(layerID_ready,840,400,dot_gra);
                    }
                    if (r > 150){
                        HgWImageDraw(layerID_ready,880,400,dot_gra);
                    }
                }
                double go = 0;
                int se_cnt = 0;
                total += 1;
                if (go == 0){
                    HgSoundStop(voice_6);
                    HgSoundVolume(voice_3,1.0,0);
                    HgSoundPlay(voice_3);
                }
                while(1){
                    go += 0.5;
                    if (go < 8){
                        HgWImagePut(layerID_ready,WIDTH/2,HIGHT/2,go_gra,go,0);
                    }
                    if (go == 8){
                        HgSoundStop(voice_3);
                        HgSoundVolume(bgm_2,1.0,1);
                        HgSoundPlay(bgm_2);
                    }
                    layerID_ready = HgLSwitch(&layers_ready);
                    layerID_back = HgLSwitch(&layers_back);
                    layerID_player_enemy_gauge = HgLSwitch(&layers_player_enemy_gauge);
                    layerID_char_status = HgLSwitch(&layers_char_status);
                    layerID_status = HgLSwitch(&layers_status);
                    layerID_game_set = HgLSwitch(&layers_game_set);
                    if (frame2_x_cnt == 1){
                        layerID_punch_Player[q] = HgLSwitch(&layers_player_punch);
                        layerID_jump_Player[p] = HgLSwitch(&layers_player_jump);
                        layerID_wait_Player[w] = HgLSwitch(&layers_player_wait);
                        layerID_walk_Player[wk] = HgLSwitch(&layers_player_walk);
                        layerID_punch_Player_L[q] = HgLSwitch(&layers_player_punch_L);
                        layerID_jump_Player_L[p] = HgLSwitch(&layers_player_jump_L);
                        layerID_wait_Player_L[w] = HgLSwitch(&layers_player_wait_L);
                        layerID_walk_Player_L[wk] = HgLSwitch(&layers_player_walk_L);
                    }
                    if (frame2_x_cnt == 2){
                        layerID_punch_Enemy[q] = HgLSwitch(&layers_enemy_punch);
                        layerID_jump_Enemy[p] = HgLSwitch(&layers_enemy_jump);
                        layerID_wait_Enemy[w] = HgLSwitch(&layers_enemy_wait);
                        layerID_walk_Enemy[wk] = HgLSwitch(&layers_enemy_walk);
                        layerID_punch_Enemy_L[q] = HgLSwitch(&layers_enemy_punch_L);
                        layerID_jump_Enemy_L[p] = HgLSwitch(&layers_enemy_jump_L);
                        layerID_wait_Enemy_L[w] = HgLSwitch(&layers_enemy_wait_L);
                        layerID_walk_Enemy_L[wk] = HgLSwitch(&layers_enemy_walk_L);
                    }
                    if (frame2_x_cnt == 3){
                        layerID_punch_Green[q] = HgLSwitch(&layers_green_punch);
                        layerID_jump_Green[p] = HgLSwitch(&layers_green_jump);
                        layerID_wait_Green[w] = HgLSwitch(&layers_green_wait);
                        layerID_walk_Green[wk] = HgLSwitch(&layers_green_walk);
                        layerID_punch_Green_L[q] = HgLSwitch(&layers_green_punch_L);
                        layerID_jump_Green_L[p] = HgLSwitch(&layers_green_jump_L);
                        layerID_wait_Green_L[w] = HgLSwitch(&layers_green_wait_L);
                        layerID_walk_Green_L[wk] = HgLSwitch(&layers_green_walk_L);
                    }
                    if (frame2_x_cnt == 4){
                        layerID_punch_Pink[q] = HgLSwitch(&layers_pink_punch);
                        layerID_jump_Pink[p] = HgLSwitch(&layers_pink_jump);
                        layerID_wait_Pink[w] = HgLSwitch(&layers_pink_wait);
                        layerID_walk_Pink[wk] = HgLSwitch(&layers_pink_walk);
                        layerID_punch_Pink_L[q] = HgLSwitch(&layers_pink_punch_L);
                        layerID_jump_Pink_L[p] = HgLSwitch(&layers_pink_jump_L);
                        layerID_wait_Pink_L[w] = HgLSwitch(&layers_pink_wait_L);
                        layerID_walk_Pink_L[wk] = HgLSwitch(&layers_pink_walk_L);
                    }
                    if (frame2_x_cnt == 5){
                        layerID_punch_Red[q] = HgLSwitch(&layers_red_punch);
                        layerID_jump_Red[p] = HgLSwitch(&layers_red_jump);
                        layerID_wait_Red[w] = HgLSwitch(&layers_red_wait);
                        layerID_walk_Red[wk] = HgLSwitch(&layers_red_walk);
                        layerID_punch_Red_L[q] = HgLSwitch(&layers_red_punch_L);
                        layerID_jump_Red_L[p] = HgLSwitch(&layers_red_jump_L);
                        layerID_wait_Red_L[w] = HgLSwitch(&layers_red_wait_L);
                        layerID_walk_Red_L[wk] = HgLSwitch(&layers_red_walk_L);
                    }
                    if (enemy_number == 1){
                        layerID_punch_Player[a] = HgLSwitch(&layers_player_punch);
                        layerID_jump_Player[b] = HgLSwitch(&layers_player_jump);
                        layerID_wait_Player[c] = HgLSwitch(&layers_player_wait);
                        layerID_walk_Player[d] = HgLSwitch(&layers_player_walk);
                        layerID_punch_Player_L[a] = HgLSwitch(&layers_player_punch_L);
                        layerID_jump_Player_L[b] = HgLSwitch(&layers_player_jump_L);
                        layerID_wait_Player_L[c] = HgLSwitch(&layers_player_wait_L);
                        layerID_walk_Player_L[d] = HgLSwitch(&layers_player_walk_L);
                    }
                    if (enemy_number == 2){
                        layerID_punch_Enemy[a] = HgLSwitch(&layers_enemy_punch);
                        layerID_jump_Enemy[b] = HgLSwitch(&layers_enemy_jump);
                        layerID_wait_Enemy[c] = HgLSwitch(&layers_enemy_wait);
                        layerID_walk_Enemy[d] = HgLSwitch(&layers_enemy_walk);
                        layerID_punch_Enemy_L[a] = HgLSwitch(&layers_enemy_punch_L);
                        layerID_jump_Enemy_L[b] = HgLSwitch(&layers_enemy_jump_L);
                        layerID_wait_Enemy_L[c] = HgLSwitch(&layers_enemy_wait_L);
                        layerID_walk_Enemy_L[d] = HgLSwitch(&layers_enemy_walk_L);
                    }
                    if (enemy_number == 3){
                        layerID_punch_Green[a] = HgLSwitch(&layers_green_punch);
                        layerID_jump_Green[b] = HgLSwitch(&layers_green_jump);
                        layerID_wait_Green[c] = HgLSwitch(&layers_green_wait);
                        layerID_walk_Green[d] = HgLSwitch(&layers_green_walk);
                        layerID_punch_Green_L[a] = HgLSwitch(&layers_green_punch_L);
                        layerID_jump_Green_L[b] = HgLSwitch(&layers_green_jump_L);
                        layerID_wait_Green_L[c] = HgLSwitch(&layers_green_wait_L);
                        layerID_walk_Green_L[d] = HgLSwitch(&layers_green_walk_L);
                    }
                    if (enemy_number == 4){
                        layerID_punch_Pink[a] = HgLSwitch(&layers_pink_punch);
                        layerID_jump_Pink[b] = HgLSwitch(&layers_pink_jump);
                        layerID_wait_Pink[c] = HgLSwitch(&layers_pink_wait);
                        layerID_walk_Pink[d] = HgLSwitch(&layers_pink_walk);
                        layerID_punch_Pink_L[a] = HgLSwitch(&layers_pink_punch_L);
                        layerID_jump_Pink_L[b] = HgLSwitch(&layers_pink_jump_L);
                        layerID_wait_Pink_L[c] = HgLSwitch(&layers_pink_wait_L);
                        layerID_walk_Pink_L[d] = HgLSwitch(&layers_pink_walk_L);
                    }
                    if (enemy_number == 5){
                        layerID_punch_Red[a] = HgLSwitch(&layers_red_punch);
                        layerID_jump_Red[b] = HgLSwitch(&layers_red_jump);
                        layerID_wait_Red[c] = HgLSwitch(&layers_red_wait);
                        layerID_walk_Red[d] = HgLSwitch(&layers_red_walk);
                        layerID_punch_Red_L[a] = HgLSwitch(&layers_red_punch_L);
                        layerID_jump_Red_L[b] = HgLSwitch(&layers_red_jump_L);
                        layerID_wait_Red_L[c] = HgLSwitch(&layers_red_wait_L);
                        layerID_walk_Red_L[d] = HgLSwitch(&layers_red_walk_L);
                    }
                    HgLClear(layerID_ready);
                    HgLClear(layerID_back);
                    HgLClear(layerID_player_enemy_gauge);
                    HgLClear(layerID_status);
                    HgLClear(layerID_game_set);
                    event = HgEventNonBlocking();
                    HgWImageDraw(layerID_back,0,0,back_gra);
                    HgWImageDraw(layerID_player_enemy_gauge,9,743,player_gauge);
                    HgWImageDraw(layerID_player_enemy_gauge,659,743,enemy_gauge);
                    HgWSetFillColor(layerID_player_enemy_gauge,HG_BLACK);
                    HgWBoxFill(layerID_player_enemy_gauge,black_player_x,743,black_player_width,52,0);
                    HgWBoxFill(layerID_player_enemy_gauge,659,743,black_enemy_width,52,0);
                    HgWImageDraw(layerID_char_status,0,0,char_status);
                    if (go > 7){
                        if (player_HP <= 0){
                            player_HP = 0;
                        }
                        if (enemy_HP <= 0){
                            enemy_HP = 0;
                        }
                        
                        HgWSetFont(layerID_status,HG_T,40);
                        HgWSetColor(layerID_status,HG_WHITE);
                        HgWText(layerID_status,10,805,"PLAYER                    %d%%(HP)",player_HP);
                        HgWSetColor(layerID_status,HG_YELLOW);
                        HgWText(layerID_status,610,600,"%d",score);
                        HgWSetColor(layerID_status,HG_BLACK);
                        HgWText(layerID_status,750,805,"%d%%(HP)                    ENEMY",enemy_HP);
                        if (player_x <= -50){
                            enemy_LR = 0;
                        }
                        if (player_x >= 1075){
                            enemy_LR = 1;
                        }
                        if (player_HP > 0 || enemy_HP > 0){
                            if (score > 0 && player_HP > 0 && enemy_HP > 0){
                                score--;
                            }
                            if (score <= 100 && game_set_warning == false){
                                HgSoundStop(bgm_2);
                                if ((score <= 100 && score > 95) || (score <= 90 && score > 85) || (score <= 80 && score > 75)){
                                    HgWImageDraw(layerID_game_set,0,0,warning);
                                }
                                if (score == 100){
                                    HgSoundVolume(bgm_3,1.0,1);
                                    HgSoundPlay(bgm_3);
                                }
                            }
                        }
                        if (score > 0 && player_HP > 0 && enemy_HP > 0){
                            HgWImageDraw(layerID_back,player_x + 15,player_y + 200,player_gra); //プレイヤーの位置を表す画像を描画
                        }
                        //---------------------------------敵の処理------------------------------------------------
                        //敵のウェイト状態
                        if (enemy_number == 1){
                            HgLClear(layerID_punch_Player[a]);
                            HgLClear(layerID_jump_Player[b]);
                            HgLClear(layerID_wait_Player[c]);
                            HgLClear(layerID_walk_Player[d]);
                            HgLClear(layerID_punch_Player_L[a]);
                            HgLClear(layerID_jump_Player_L[b]);
                            HgLClear(layerID_wait_Player_L[c]);
                            HgLClear(layerID_walk_Player_L[d]);
                        }
                        if (enemy_number == 2){
                            HgLClear(layerID_punch_Enemy[a]);
                            HgLClear(layerID_jump_Enemy[b]);
                            HgLClear(layerID_wait_Enemy[c]);
                            HgLClear(layerID_walk_Enemy[d]);
                            HgLClear(layerID_punch_Enemy_L[a]);
                            HgLClear(layerID_jump_Enemy_L[b]);
                            HgLClear(layerID_wait_Enemy_L[c]);
                            HgLClear(layerID_walk_Enemy_L[d]);
                        }
                        if (enemy_number == 3){
                            HgLClear(layerID_punch_Green[a]);
                            HgLClear(layerID_jump_Green[b]);
                            HgLClear(layerID_wait_Green[c]);
                            HgLClear(layerID_walk_Green[d]);
                            HgLClear(layerID_punch_Green_L[a]);
                            HgLClear(layerID_jump_Green_L[b]);
                            HgLClear(layerID_wait_Green_L[c]);
                            HgLClear(layerID_walk_Green_L[d]);
                        }
                        if (enemy_number == 4){
                            HgLClear(layerID_punch_Pink[a]);
                            HgLClear(layerID_jump_Pink[b]);
                            HgLClear(layerID_wait_Pink[c]);
                            HgLClear(layerID_walk_Pink[d]);
                            HgLClear(layerID_punch_Pink_L[a]);
                            HgLClear(layerID_jump_Pink_L[b]);
                            HgLClear(layerID_wait_Pink_L[c]);
                            HgLClear(layerID_walk_Pink_L[d]);
                        }
                        if (enemy_number == 5){
                            HgLClear(layerID_punch_Red[a]);
                            HgLClear(layerID_jump_Red[b]);
                            HgLClear(layerID_wait_Red[c]);
                            HgLClear(layerID_walk_Red[d]);
                            HgLClear(layerID_punch_Red_L[a]);
                            HgLClear(layerID_jump_Red_L[b]);
                            HgLClear(layerID_wait_Red_L[c]);
                            HgLClear(layerID_walk_Red_L[d]);
                        }
                        if (score > 0 && player_HP > 0 && enemy_HP > 0){
                            if (critical_enemy_ok == true){
                                critical_cnt_enemy ++;
                                if (critical_cnt_enemy <= 25){  //クリティカル画像を表示
                                    HgWImageDraw(layerID_back,enemy_x,enemy_y + 200,critical);
                                }
                            }
                            if (critical_cnt_enemy > 26){
                                critical_cnt_enemy = 0;
                                critical_enemy_ok = false;
                            }
                            if (enemy_status == 0){
                                if (player_x < enemy_x){
                                    enemy_LR = 1;   //敵を左に向かせる
                                }
                                if (player_x > enemy_x){
                                    enemy_LR = 0;   //敵を右に向かせる
                                }
                                if (enemy_LR == 0){ //右向き
                                    if (enemy_number == 1){
                                        HgWImageDraw(layerID_wait_Player[c],enemy_x,enemy_y,player_w[c]);
                                    }
                                    if (enemy_number == 2){
                                        HgWImageDraw(layerID_wait_Enemy[c],enemy_x,enemy_y,enemy_w[c]);
                                    }
                                    if (enemy_number == 3){
                                        HgWImageDraw(layerID_wait_Green[c],enemy_x,enemy_y,green_w[c]);
                                    }
                                    if (enemy_number == 4){
                                        HgWImageDraw(layerID_wait_Pink[c],enemy_x,enemy_y,pink_w[c]);
                                    }
                                    if (enemy_number == 5){
                                        HgWImageDraw(layerID_wait_Red[c],enemy_x,enemy_y,red_w[c]);
                                    }
                                }
                                if (enemy_LR == 1){ //左向き
                                    if (enemy_number == 1){
                                        HgWImageDraw(layerID_wait_Player_L[c],enemy_x,enemy_y,player_wL[c]);
                                    }
                                    if (enemy_number == 2){
                                        HgWImageDraw(layerID_wait_Enemy_L[c],enemy_x,enemy_y,enemy_wL[c]);
                                    }
                                    if (enemy_number == 3){
                                        HgWImageDraw(layerID_wait_Green_L[c],enemy_x,enemy_y,green_wL[c]);
                                    }
                                    if (enemy_number == 4){
                                        HgWImageDraw(layerID_wait_Pink_L[c],enemy_x,enemy_y,pink_wL[c]);
                                    }
                                    if (enemy_number == 5){
                                        HgWImageDraw(layerID_wait_Red_L[c],enemy_x,enemy_y,red_wL[c]);
                                    }
                                    
                                }
                                enemy_on = true;
                                c++;
                                if (c == 6){
                                    c = 0;
                                    enemy_on = false;
                                    enemy_status = rand() % 5;
                                }
                            }
                            //敵のジャンプ状態
                            if (enemy_status == 1){
                                if (jump_enemy == 0){
                                    if (enemy_number == 1){
                                        HgLClear(layerID_punch_Player[a]);
                                        HgLClear(layerID_jump_Player[b]);
                                        HgLClear(layerID_wait_Player[c]);
                                        HgLClear(layerID_walk_Player[d]);
                                        HgLClear(layerID_punch_Player_L[a]);
                                        HgLClear(layerID_jump_Player_L[b]);
                                        HgLClear(layerID_wait_Player_L[c]);
                                        HgLClear(layerID_walk_Player_L[d]);
                                    }
                                    if (enemy_number == 2){
                                        HgLClear(layerID_punch_Enemy[a]);
                                        HgLClear(layerID_jump_Enemy[b]);
                                        HgLClear(layerID_wait_Enemy[c]);
                                        HgLClear(layerID_walk_Enemy[d]);
                                        HgLClear(layerID_punch_Enemy_L[a]);
                                        HgLClear(layerID_jump_Enemy_L[b]);
                                        HgLClear(layerID_wait_Enemy_L[c]);
                                        HgLClear(layerID_walk_Enemy_L[d]);
                                    }
                                    if (enemy_number == 3){
                                        HgLClear(layerID_punch_Green[a]);
                                        HgLClear(layerID_jump_Green[b]);
                                        HgLClear(layerID_wait_Green[c]);
                                        HgLClear(layerID_walk_Green[d]);
                                        HgLClear(layerID_punch_Green_L[a]);
                                        HgLClear(layerID_jump_Green_L[b]);
                                        HgLClear(layerID_wait_Green_L[c]);
                                        HgLClear(layerID_walk_Green_L[d]);
                                    }
                                    if (enemy_number == 4){
                                        HgLClear(layerID_punch_Pink[a]);
                                        HgLClear(layerID_jump_Pink[b]);
                                        HgLClear(layerID_wait_Pink[c]);
                                        HgLClear(layerID_walk_Pink[d]);
                                        HgLClear(layerID_punch_Pink_L[a]);
                                        HgLClear(layerID_jump_Pink_L[b]);
                                        HgLClear(layerID_wait_Pink_L[c]);
                                        HgLClear(layerID_walk_Pink_L[d]);
                                    }
                                    if (enemy_number == 5){
                                        HgLClear(layerID_punch_Red[a]);
                                        HgLClear(layerID_jump_Red[b]);
                                        HgLClear(layerID_wait_Red[c]);
                                        HgLClear(layerID_walk_Red[d]);
                                        HgLClear(layerID_punch_Red_L[a]);
                                        HgLClear(layerID_jump_Red_L[b]);
                                        HgLClear(layerID_wait_Red_L[c]);
                                        HgLClear(layerID_walk_Red_L[d]);
                                    }
                                    if (player_x < enemy_x){
                                        enemy_LR = 1;   //敵を左に向かせる
                                    }
                                    if (player_x > enemy_x){
                                        enemy_LR = 0;   //敵を右に向かせる
                                    }
                                    if (enemy_LR == 0){ //右向き
                                        if (enemy_number == 1){
                                            HgWImageDraw(layerID_jump_Player[b],enemy_x,enemy_y,player_j[b]);
                                        }
                                        if (enemy_number == 2){
                                            HgWImageDraw(layerID_jump_Enemy[b],enemy_x,enemy_y,enemy_j[b]);
                                        }
                                        if (enemy_number == 3){
                                            HgWImageDraw(layerID_jump_Green[b],enemy_x,enemy_y,green_j[b]);
                                        }
                                        if (enemy_number == 4){
                                            HgWImageDraw(layerID_jump_Pink[b],enemy_x,enemy_y,pink_j[b]);
                                        }
                                        if (enemy_number == 5){
                                            HgWImageDraw(layerID_jump_Red[b],enemy_x,enemy_y,red_j[b]);
                                        }
                                    }
                                    if (enemy_LR == 1){ //左向き
                                        if (enemy_number == 1){
                                            HgWImageDraw(layerID_jump_Player_L[b],enemy_x,enemy_y,player_jL[b]);
                                        }
                                        if (enemy_number == 2){
                                            HgWImageDraw(layerID_jump_Enemy_L[b],enemy_x,enemy_y,enemy_jL[b]);
                                        }
                                        if (enemy_number == 3){
                                            HgWImageDraw(layerID_jump_Green_L[b],enemy_x,enemy_y,green_jL[b]);
                                        }
                                        if (enemy_number == 4){
                                            HgWImageDraw(layerID_jump_Pink_L[b],enemy_x,enemy_y,pink_jL[b]);
                                        }
                                        if (enemy_number == 5){
                                            HgWImageDraw(layerID_jump_Red_L[b],enemy_x,enemy_y,red_jL[b]);
                                        }
                                    }
                                    enemy_y += 30;
                                    enemy_on = true;
                                    b++;
                                }
                                if (enemy_y == 400){
                                    jump_enemy = 1;
                                    b = 9;
                                }
                                if (jump_enemy == 1){
                                    if (enemy_number == 1){
                                        HgLClear(layerID_punch_Player[a]);
                                        HgLClear(layerID_jump_Player[b]);
                                        HgLClear(layerID_wait_Player[c]);
                                        HgLClear(layerID_walk_Player[d]);
                                        HgLClear(layerID_punch_Player_L[a]);
                                        HgLClear(layerID_jump_Player_L[b]);
                                        HgLClear(layerID_wait_Player_L[c]);
                                        HgLClear(layerID_walk_Player_L[d]);
                                    }
                                    if (enemy_number == 2){
                                        HgLClear(layerID_punch_Enemy[a]);
                                        HgLClear(layerID_jump_Enemy[b]);
                                        HgLClear(layerID_wait_Enemy[c]);
                                        HgLClear(layerID_walk_Enemy[d]);
                                        HgLClear(layerID_punch_Enemy_L[a]);
                                        HgLClear(layerID_jump_Enemy_L[b]);
                                        HgLClear(layerID_wait_Enemy_L[c]);
                                        HgLClear(layerID_walk_Enemy_L[d]);
                                    }
                                    if (enemy_number == 3){
                                        HgLClear(layerID_punch_Green[a]);
                                        HgLClear(layerID_jump_Green[b]);
                                        HgLClear(layerID_wait_Green[c]);
                                        HgLClear(layerID_walk_Green[d]);
                                        HgLClear(layerID_punch_Green_L[a]);
                                        HgLClear(layerID_jump_Green_L[b]);
                                        HgLClear(layerID_wait_Green_L[c]);
                                        HgLClear(layerID_walk_Green_L[d]);
                                    }
                                    if (enemy_number == 4){
                                        HgLClear(layerID_punch_Pink[a]);
                                        HgLClear(layerID_jump_Pink[b]);
                                        HgLClear(layerID_wait_Pink[c]);
                                        HgLClear(layerID_walk_Pink[d]);
                                        HgLClear(layerID_punch_Pink_L[a]);
                                        HgLClear(layerID_jump_Pink_L[b]);
                                        HgLClear(layerID_wait_Pink_L[c]);
                                        HgLClear(layerID_walk_Pink_L[d]);
                                    }
                                    if (enemy_number == 5){
                                        HgLClear(layerID_punch_Red[a]);
                                        HgLClear(layerID_jump_Red[b]);
                                        HgLClear(layerID_wait_Red[c]);
                                        HgLClear(layerID_walk_Red[d]);
                                        HgLClear(layerID_punch_Red_L[a]);
                                        HgLClear(layerID_jump_Red_L[b]);
                                        HgLClear(layerID_wait_Red_L[c]);
                                        HgLClear(layerID_walk_Red_L[d]);
                                    }
                                    if (player_x < enemy_x){
                                        enemy_LR = 1;   //敵を左に向かせる
                                    }
                                    if (player_x > enemy_x){
                                        enemy_LR = 0;   //敵を右に向かせる
                                    }
                                    if (enemy_LR == 0){ //右向き
                                        if (enemy_number == 1){
                                            HgWImageDraw(layerID_jump_Player[b],enemy_x,enemy_y,player_j[b]);
                                        }
                                        if (enemy_number == 2){
                                            HgWImageDraw(layerID_jump_Enemy[b],enemy_x,enemy_y,enemy_j[b]);
                                        }
                                        if (enemy_number == 3){
                                            HgWImageDraw(layerID_jump_Green[b],enemy_x,enemy_y,green_j[b]);
                                        }
                                        if (enemy_number == 4){
                                            HgWImageDraw(layerID_jump_Pink[b],enemy_x,enemy_y,pink_j[b]);
                                        }
                                        if (enemy_number == 5){
                                            HgWImageDraw(layerID_jump_Red[b],enemy_x,enemy_y,red_j[b]);
                                        }
                                    }
                                    if (enemy_LR == 1){ //左向き
                                        if (enemy_number == 1){
                                            HgWImageDraw(layerID_jump_Player_L[b],enemy_x,enemy_y,player_jL[b]);
                                        }
                                        if (enemy_number == 2){
                                            HgWImageDraw(layerID_jump_Enemy_L[b],enemy_x,enemy_y,enemy_jL[b]);
                                        }
                                        if (enemy_number == 3){
                                            HgWImageDraw(layerID_jump_Green_L[b],enemy_x,enemy_y,green_jL[b]);
                                        }
                                        if (enemy_number == 4){
                                            HgWImageDraw(layerID_jump_Pink_L[b],enemy_x,enemy_y,pink_jL[b]);
                                        }
                                        if (enemy_number == 5){
                                            HgWImageDraw(layerID_jump_Red_L[b],enemy_x,enemy_y,red_jL[b]);
                                        }
                                    }
                                    b--;
                                    enemy_y -= 30;
                                }
                                if (jump_enemy == 1 && enemy_y == 100){
                                    //enemy_status = 0;   //ウェイトに戻す
                                    enemy_status = rand() % 5;
                                    jump_enemy = 0;
                                    b = 0;
                                    enemy_on = false;
                                }
                            }
                            //敵のパンチ状態
                            if(enemy_status == 2 || enemy_status == 3){
                                if (enemy_number == 1){
                                    HgLClear(layerID_punch_Player[a]);
                                    HgLClear(layerID_jump_Player[b]);
                                    HgLClear(layerID_wait_Player[c]);
                                    HgLClear(layerID_walk_Player[d]);
                                    HgLClear(layerID_punch_Player_L[a]);
                                    HgLClear(layerID_jump_Player_L[b]);
                                    HgLClear(layerID_wait_Player_L[c]);
                                    HgLClear(layerID_walk_Player_L[d]);
                                }
                                if (enemy_number == 2){
                                    HgLClear(layerID_punch_Enemy[a]);
                                    HgLClear(layerID_jump_Enemy[b]);
                                    HgLClear(layerID_wait_Enemy[c]);
                                    HgLClear(layerID_walk_Enemy[d]);
                                    HgLClear(layerID_punch_Enemy_L[a]);
                                    HgLClear(layerID_jump_Enemy_L[b]);
                                    HgLClear(layerID_wait_Enemy_L[c]);
                                    HgLClear(layerID_walk_Enemy_L[d]);
                                }
                                if (enemy_number == 3){
                                    HgLClear(layerID_punch_Green[a]);
                                    HgLClear(layerID_jump_Green[b]);
                                    HgLClear(layerID_wait_Green[c]);
                                    HgLClear(layerID_walk_Green[d]);
                                    HgLClear(layerID_punch_Green_L[a]);
                                    HgLClear(layerID_jump_Green_L[b]);
                                    HgLClear(layerID_wait_Green_L[c]);
                                    HgLClear(layerID_walk_Green_L[d]);
                                }
                                if (enemy_number == 4){
                                    HgLClear(layerID_punch_Pink[a]);
                                    HgLClear(layerID_jump_Pink[b]);
                                    HgLClear(layerID_wait_Pink[c]);
                                    HgLClear(layerID_walk_Pink[d]);
                                    HgLClear(layerID_punch_Pink_L[a]);
                                    HgLClear(layerID_jump_Pink_L[b]);
                                    HgLClear(layerID_wait_Pink_L[c]);
                                    HgLClear(layerID_walk_Pink_L[d]);
                                }
                                if (enemy_number == 5){
                                    HgLClear(layerID_punch_Red[a]);
                                    HgLClear(layerID_jump_Red[b]);
                                    HgLClear(layerID_wait_Red[c]);
                                    HgLClear(layerID_walk_Red[d]);
                                    HgLClear(layerID_punch_Red_L[a]);
                                    HgLClear(layerID_jump_Red_L[b]);
                                    HgLClear(layerID_wait_Red_L[c]);
                                    HgLClear(layerID_walk_Red_L[d]);
                                }
                                if (player_x < enemy_x){
                                    enemy_LR = 1;   //敵を左に向かせる
                                }
                                if (player_x > enemy_x){
                                    enemy_LR = 0;   //敵を右に向かせる
                                }
                                if (enemy_LR == 0){ //右向き
                                    if (enemy_number == 1){
                                        HgWImageDraw(layerID_punch_Player[a],enemy_x,enemy_y,player_p[a]);
                                    }
                                    if (enemy_number == 2){
                                        HgWImageDraw(layerID_punch_Enemy[a],enemy_x,enemy_y,enemy_p[a]);
                                    }
                                    if (enemy_number == 3){
                                        HgWImageDraw(layerID_punch_Green[a],enemy_x,enemy_y,green_p[a]);
                                    }
                                    if (enemy_number == 4){
                                        HgWImageDraw(layerID_punch_Pink[a],enemy_x,enemy_y,pink_p[a]);
                                    }
                                    if (enemy_number == 5){
                                        HgWImageDraw(layerID_punch_Red[a],enemy_x,enemy_y,red_p[a]);
                                    }
                                }
                                if (enemy_LR == 1){ //左向き
                                    if (enemy_number == 1){
                                        HgWImageDraw(layerID_punch_Player_L[a],enemy_x,enemy_y,player_pL[a]);
                                    }
                                    if (enemy_number == 2){
                                        HgWImageDraw(layerID_punch_Enemy_L[a],enemy_x,enemy_y,enemy_pL[a]);
                                    }
                                    if (enemy_number == 3){
                                        HgWImageDraw(layerID_punch_Green_L[a],enemy_x,enemy_y,green_pL[a]);
                                    }
                                    if (enemy_number == 4){
                                        HgWImageDraw(layerID_punch_Pink_L[a],enemy_x,enemy_y,pink_pL[a]);
                                    }
                                    if (enemy_number == 5){
                                        HgWImageDraw(layerID_punch_Red_L[a],enemy_x,enemy_y,red_pL[a]);
                                    }
                                }
                                if (a < 10){
                                    enemy_on = true;
                                    a++;
                                }
                                if (a == 10){
                                    a = 0;
                                    enemy_on = false;
                                    if ((enemy_x >= player_x && enemy_x <= player_x + HIT_RANGE) || (enemy_x + HIT_RANGE >= player_x && enemy_x + HIT_RANGE <= player_x + HIT_RANGE)){  //横幅の当たり判定
                                        if (enemy_y + HIT_RANGE_Y >= player_y && enemy_y + HIT_RANGE_Y <= player_y + CHARA_HEIGHT){ //縦幅の当たり判定
                                            if (player_HP > 0){
                                                critical_random_enemy = rand() % 10;
                                                if (mode_status == 1){  //簡単モード
                                                    //プレイヤーにダメージが当たれば、続けて攻撃する
                                                    if (critical_random_enemy >= 2){
                                                        if (enemy_LR == 0 && player_x > 150){ //右向き
                                                            player_x -= 150;
                                                        }
                                                        if (enemy_LR == 0 && player_x <= 150){ //右向き
                                                            player_x -= player_x;
                                                        }
                                                        if (enemy_LR == 1 && player_x < WIDTH - 150){ //左向き
                                                            player_x += 150;
                                                        }
                                                        if (enemy_LR == 1 && player_x >= WIDTH - 150){ //左向き
                                                            player_x += WIDTH - player_x;
                                                        }
                                                        player_HP -= 10;
                                                        //300(MAXのHP) / 10(ダメージ量) = 30
                                                        //612(バーの画像の幅) / 30(上で求めた値) = 20.4
                                                        black_player_x -= 20.4;
                                                        black_player_width += 20.4;
                                                    }
                                                }
                                                if (mode_status == 2){  //普通モード
                                                    //プレイヤーにダメージが当たれば、続けて攻撃する
                                                    if (critical_random_enemy >= 3){
                                                        if (enemy_LR == 0 && player_x > 150){ //右向き
                                                            player_x -= 150;
                                                        }
                                                        if (enemy_LR == 0 && player_x <= 150){ //右向き
                                                            player_x -= player_x;
                                                        }
                                                        if (enemy_LR == 1 && player_x < WIDTH - 150){ //左向き
                                                            player_x += 150;
                                                        }
                                                        if (enemy_LR == 1 && player_x >= WIDTH - 150){ //左向き
                                                            player_x += WIDTH - player_x;
                                                        }
                                                        player_HP -= 10;
                                                        //300(MAXのHP) / 10(ダメージ量) = 30
                                                        //612(バーの画像の幅) / 30(上で求めた値) = 20.4
                                                        black_player_x -= 20.4;
                                                        black_player_width += 20.4;
                                                    }
                                                }
                                                if (mode_status == 3){  //難しいモード
                                                    //プレイヤーにダメージが当たれば、続けて攻撃する
                                                    if (critical_random_enemy >= 4){
                                                        if (enemy_LR == 0 && player_x > 150){ //右向き
                                                            player_x -= 150;
                                                        }
                                                        if (enemy_LR == 0 && player_x <= 150){ //右向き
                                                            player_x -= player_x;
                                                        }
                                                        if (enemy_LR == 1 && player_x < WIDTH - 150){ //左向き
                                                            player_x += 150;
                                                        }
                                                        if (enemy_LR == 1 && player_x >= WIDTH - 150){ //左向き
                                                            player_x += WIDTH - player_x;
                                                        }
                                                        player_HP -= 10;
                                                        //300(MAXのHP) / 10(ダメージ量) = 30
                                                        //612(バーの画像の幅) / 30(上で求めた値) = 20.4
                                                        black_player_x -= 20.4;
                                                        black_player_width += 20.4;
                                                    }
                                                }
                                                if (mode_status == 1){  //簡単モード
                                                    if (critical_random_enemy == 0 || critical_random_enemy == 1){  //クリティカル処理
                                                        if (enemy_LR == 0 && player_x > 300){ //右向き
                                                            player_x -= 300;
                                                        }
                                                        if (enemy_LR == 1 && player_x < WIDTH - 300){ //左向き
                                                            player_x += 300;
                                                        }
                                                        critical_enemy_ok = true;
                                                        player_HP -= 30;
                                                        black_player_x -= 20.4 * 3;
                                                        black_player_width += 20.4 * 3;
                                                    }
                                                }
                                                if (mode_status == 2){  //普通モード
                                                    if (critical_random_enemy == 0 || critical_random_enemy == 1 || critical_random_enemy == 2){  //クリティカル処理
                                                        if (enemy_LR == 0 && player_x > 300){ //右向き
                                                            player_x -= 300;
                                                        }
                                                        if (enemy_LR == 1 && player_x < WIDTH - 300){ //左向き
                                                            player_x += 300;
                                                        }
                                                        critical_enemy_ok = true;
                                                        player_HP -= 30;
                                                        black_player_x -= 20.4 * 3;
                                                        black_player_width += 20.4 * 3;
                                                    }
                                                }
                                                if (mode_status == 3){  //難しいモード
                                                    if (critical_random_enemy == 0 || critical_random_enemy == 1 || critical_random_enemy == 2 || critical_random_enemy == 3){  //クリティカル処理
                                                        if (enemy_LR == 0 && player_x > 300){ //右向き
                                                            player_x -= 300;
                                                        }
                                                        if (enemy_LR == 1 && player_x < WIDTH - 300){ //左向き
                                                            player_x += 300;
                                                        }
                                                        critical_enemy_ok = true;
                                                        player_HP -= 30;
                                                        black_player_x -= 20.4 * 3;
                                                        black_player_width += 20.4 * 3;
                                                    }
                                                }
                                                
                                                HgWSetFillColor(layerID_back,HgRGBA(1.0,0.0,0.0,0.6));
                                                HgWBoxFill(layerID_back,0,0,WIDTH,HIGHT,0);
                                            }
                                        }
                                    }
                                    else{
                                        enemy_status = rand() % 5;  //プレイヤーにダメージが当たらないなら、状態を変える。
                                    }
                                }
                            }
                            if (enemy_status == 4){
                                //敵の歩き状態(常)
                                if (enemy_number == 1){
                                    HgLClear(layerID_punch_Player[a]);
                                    HgLClear(layerID_jump_Player[b]);
                                    HgLClear(layerID_wait_Player[c]);
                                    HgLClear(layerID_walk_Player[d]);
                                    HgLClear(layerID_punch_Player_L[a]);
                                    HgLClear(layerID_jump_Player_L[b]);
                                    HgLClear(layerID_wait_Player_L[c]);
                                    HgLClear(layerID_walk_Player_L[d]);
                                }
                                if (enemy_number == 2){
                                    HgLClear(layerID_punch_Enemy[a]);
                                    HgLClear(layerID_jump_Enemy[b]);
                                    HgLClear(layerID_wait_Enemy[c]);
                                    HgLClear(layerID_walk_Enemy[d]);
                                    HgLClear(layerID_punch_Enemy_L[a]);
                                    HgLClear(layerID_jump_Enemy_L[b]);
                                    HgLClear(layerID_wait_Enemy_L[c]);
                                    HgLClear(layerID_walk_Enemy_L[d]);
                                }
                                if (enemy_number == 3){
                                    HgLClear(layerID_punch_Green[a]);
                                    HgLClear(layerID_jump_Green[b]);
                                    HgLClear(layerID_wait_Green[c]);
                                    HgLClear(layerID_walk_Green[d]);
                                    HgLClear(layerID_punch_Green_L[a]);
                                    HgLClear(layerID_jump_Green_L[b]);
                                    HgLClear(layerID_wait_Green_L[c]);
                                    HgLClear(layerID_walk_Green_L[d]);
                                }
                                if (enemy_number == 4){
                                    HgLClear(layerID_punch_Pink[a]);
                                    HgLClear(layerID_jump_Pink[b]);
                                    HgLClear(layerID_wait_Pink[c]);
                                    HgLClear(layerID_walk_Pink[d]);
                                    HgLClear(layerID_punch_Pink_L[a]);
                                    HgLClear(layerID_jump_Pink_L[b]);
                                    HgLClear(layerID_wait_Pink_L[c]);
                                    HgLClear(layerID_walk_Pink_L[d]);
                                }
                                if (enemy_number == 5){
                                    HgLClear(layerID_punch_Red[a]);
                                    HgLClear(layerID_jump_Red[b]);
                                    HgLClear(layerID_wait_Red[c]);
                                    HgLClear(layerID_walk_Red[d]);
                                    HgLClear(layerID_punch_Red_L[a]);
                                    HgLClear(layerID_jump_Red_L[b]);
                                    HgLClear(layerID_wait_Red_L[c]);
                                    HgLClear(layerID_walk_Red_L[d]);
                                }
                                if (player_x < enemy_x){
                                    enemy_LR = 1;   //敵を左に向かせる
                                }
                                if (player_x > enemy_x){
                                    enemy_LR = 0;   //敵を右に向かせる
                                }
                                if (enemy_x > 0 || enemy_x < WIDTH - 256){   //画面内
                                    enemy_walk = rand() % 10;
                                }
                                if (enemy_x <= 0 || enemy_x > WIDTH){  //画面外
                                    if (enemy_x <= 0){  //画面の左に出ると
                                        enemy_LR = 0;   //右向きにする
                                    }
                                    if (enemy_LR == 0){ //右向きになると
                                        enemy_x += 50;  //50ずつ右に移動
                                    }
                                    if (enemy_x > WIDTH){  //画面の右に出ると
                                        enemy_LR = 1;       //左向きにする
                                    }
                                    if (enemy_LR == 1){     //左向きになると
                                        enemy_x -= 50;      //50ずつ左に移動
                                    }
                                }
                                if (enemy_x > 0 || enemy_x < WIDTH - 256){   //画面内
                                    if (enemy_LR == 0){ //右向き
                                        if (enemy_number == 1){
                                            HgLClear(layerID_walk_Player[d]);
                                            HgWImageDraw(layerID_walk_Player[d],enemy_x,enemy_y,player_wk[d]);
                                        }
                                        if (enemy_number == 2){
                                            HgLClear(layerID_walk_Enemy[d]);
                                            HgWImageDraw(layerID_walk_Enemy[d],enemy_x,enemy_y,enemy_wk[d]);
                                        }
                                        if (enemy_number == 3){
                                            HgLClear(layerID_walk_Green[d]);
                                            HgWImageDraw(layerID_walk_Green[d],enemy_x,enemy_y,green_wk[d]);
                                        }
                                        if (enemy_number == 4){
                                            HgLClear(layerID_walk_Pink[d]);
                                            HgWImageDraw(layerID_walk_Pink[d],enemy_x,enemy_y,pink_wk[d]);
                                        }
                                        if (enemy_number == 5){
                                            HgLClear(layerID_walk_Red[d]);
                                            HgWImageDraw(layerID_walk_Red[d],enemy_x,enemy_y,red_wk[d]);
                                        }
                                        if (enemy_walk % 2 == 0){
                                            enemy_walk_cnt ++;
                                            enemy_x += 30;
                                        }
                                        if (enemy_walk_cnt == 10){   //10歩歩いたら
                                            enemy_status = 0;   //ウェイトに戻す
                                            enemy_walk_cnt = 0;
                                        }
                                    }
                                    if (enemy_LR == 1){ //左向き
                                        if (enemy_number == 1){
                                            HgLClear(layerID_walk_Player_L[d]);
                                            HgWImageDraw(layerID_walk_Player_L[d],enemy_x,enemy_y,player_wkL[d]);
                                        }
                                        if (enemy_number == 2){
                                            HgLClear(layerID_walk_Enemy_L[d]);
                                            HgWImageDraw(layerID_walk_Enemy_L[d],enemy_x,enemy_y,enemy_wkL[d]);
                                        }
                                        if (enemy_number == 3){
                                            HgLClear(layerID_walk_Green_L[d]);
                                            HgWImageDraw(layerID_walk_Green_L[d],enemy_x,enemy_y,green_wkL[d]);
                                        }
                                        if (enemy_number == 4){
                                            HgLClear(layerID_walk_Pink_L[d]);
                                            HgWImageDraw(layerID_walk_Pink_L[d],enemy_x,enemy_y,pink_wkL[d]);
                                        }
                                        if (enemy_number == 5){
                                            HgLClear(layerID_walk_Red_L[d]);
                                            HgWImageDraw(layerID_walk_Red_L[d],enemy_x,enemy_y,red_wkL[d]);
                                        }
                                        if (enemy_walk % 2 == 0){
                                            enemy_walk_cnt ++;
                                            enemy_x -= 30;
                                        }
                                        if (enemy_walk_cnt == 10){   //10歩歩いたら
                                            enemy_status = 0;   //ウェイトに戻す
                                            enemy_walk_cnt = 0;
                                        }
                                    }
                                }
                                if (d < 8 && enemy_on == false){
                                    d++;
                                }
                                if (d == 8){
                                    d = 0;
                                }
                            }
                        }
                        //-------------------------------------敵の処理ここまで-------------------------------------------
                        //-------------------------------------プレイヤーの処理-------------------------------------------
                        //printf("%s\n", btoa(line_f));
                        if (frame2_x_cnt == 1){
                            HgLClear(layerID_punch_Player[q]);
                            HgLClear(layerID_jump_Player[p]);
                            HgLClear(layerID_wait_Player[w]);
                            HgLClear(layerID_walk_Player[wk]);
                            HgLClear(layerID_punch_Player_L[q]);
                            HgLClear(layerID_jump_Player_L[p]);
                            HgLClear(layerID_wait_Player_L[w]);
                            HgLClear(layerID_walk_Player_L[wk]);
                        }
                        if (frame2_x_cnt == 2){
                            HgLClear(layerID_punch_Enemy[q]);
                            HgLClear(layerID_jump_Enemy[p]);
                            HgLClear(layerID_wait_Enemy[w]);
                            HgLClear(layerID_walk_Enemy[wk]);
                            HgLClear(layerID_punch_Enemy_L[q]);
                            HgLClear(layerID_jump_Enemy_L[p]);
                            HgLClear(layerID_wait_Enemy_L[w]);
                            HgLClear(layerID_walk_Enemy_L[wk]);
                        }
                        if (frame2_x_cnt == 3){
                            HgLClear(layerID_punch_Green[q]);
                            HgLClear(layerID_jump_Green[p]);
                            HgLClear(layerID_wait_Green[w]);
                            HgLClear(layerID_walk_Green[wk]);
                            HgLClear(layerID_punch_Green_L[q]);
                            HgLClear(layerID_jump_Green_L[p]);
                            HgLClear(layerID_wait_Green_L[w]);
                            HgLClear(layerID_walk_Green_L[wk]);
                        }
                        if (frame2_x_cnt == 4){
                            HgLClear(layerID_punch_Pink[q]);
                            HgLClear(layerID_jump_Pink[p]);
                            HgLClear(layerID_wait_Pink[w]);
                            HgLClear(layerID_walk_Pink[wk]);
                            HgLClear(layerID_punch_Pink_L[q]);
                            HgLClear(layerID_jump_Pink_L[p]);
                            HgLClear(layerID_wait_Pink_L[w]);
                            HgLClear(layerID_walk_Pink_L[wk]);
                        }
                        if (frame2_x_cnt == 5){
                            HgLClear(layerID_punch_Red[q]);
                            HgLClear(layerID_jump_Red[p]);
                            HgLClear(layerID_wait_Red[w]);
                            HgLClear(layerID_walk_Red[wk]);
                            HgLClear(layerID_punch_Red_L[q]);
                            HgLClear(layerID_jump_Red_L[p]);
                            HgLClear(layerID_wait_Red_L[w]);
                            HgLClear(layerID_walk_Red_L[wk]);
                        }
                        if (score > 0 && player_HP > 0 && enemy_HP > 0){
                            if (critical_player_ok == true){
                                critical_cnt_player ++;
                                if (critical_cnt_player <= 25){
                                    HgWImageDraw(layerID_back,player_x,player_y + 300,critical);
                                }
                            }
                            if (critical_cnt_player > 26){
                                critical_cnt_player = 0;
                                critical_player_ok = false;
                            }
                            if (w_ok == 1){
                                //パンチ
                                if (frame2_x_cnt == 1){
                                    HgLClear(layerID_punch_Player[q]);
                                    HgLClear(layerID_jump_Player[p]);
                                    HgLClear(layerID_wait_Player[w]);
                                    HgLClear(layerID_walk_Player[wk]);
                                    HgLClear(layerID_punch_Player_L[q]);
                                    HgLClear(layerID_jump_Player_L[p]);
                                    HgLClear(layerID_wait_Player_L[w]);
                                    HgLClear(layerID_walk_Player_L[wk]);
                                }
                                if (frame2_x_cnt == 2){
                                    HgLClear(layerID_punch_Enemy[q]);
                                    HgLClear(layerID_jump_Enemy[p]);
                                    HgLClear(layerID_wait_Enemy[w]);
                                    HgLClear(layerID_walk_Enemy[wk]);
                                    HgLClear(layerID_punch_Enemy_L[q]);
                                    HgLClear(layerID_jump_Enemy_L[p]);
                                    HgLClear(layerID_wait_Enemy_L[w]);
                                    HgLClear(layerID_walk_Enemy_L[wk]);
                                }
                                if (frame2_x_cnt == 3){
                                    HgLClear(layerID_punch_Green[q]);
                                    HgLClear(layerID_jump_Green[p]);
                                    HgLClear(layerID_wait_Green[w]);
                                    HgLClear(layerID_walk_Green[wk]);
                                    HgLClear(layerID_punch_Green_L[q]);
                                    HgLClear(layerID_jump_Green_L[p]);
                                    HgLClear(layerID_wait_Green_L[w]);
                                    HgLClear(layerID_walk_Green_L[wk]);
                                }
                                if (frame2_x_cnt == 4){
                                    HgLClear(layerID_punch_Pink[q]);
                                    HgLClear(layerID_jump_Pink[p]);
                                    HgLClear(layerID_wait_Pink[w]);
                                    HgLClear(layerID_walk_Pink[wk]);
                                    HgLClear(layerID_punch_Pink_L[q]);
                                    HgLClear(layerID_jump_Pink_L[p]);
                                    HgLClear(layerID_wait_Pink_L[w]);
                                    HgLClear(layerID_walk_Pink_L[wk]);
                                }
                                if (frame2_x_cnt == 5){
                                    HgLClear(layerID_punch_Red[q]);
                                    HgLClear(layerID_jump_Red[p]);
                                    HgLClear(layerID_wait_Red[w]);
                                    HgLClear(layerID_walk_Red[wk]);
                                    HgLClear(layerID_punch_Red_L[q]);
                                    HgLClear(layerID_jump_Red_L[p]);
                                    HgLClear(layerID_wait_Red_L[w]);
                                    HgLClear(layerID_walk_Red_L[wk]);
                                }
                                if (player_LR == 0){ //右向き
                                    if (frame2_x_cnt == 1){
                                        HgWImageDraw(layerID_punch_Player[q],player_x,player_y,player_p[q]);
                                    }
                                    if (frame2_x_cnt == 2){
                                        HgWImageDraw(layerID_punch_Enemy[q],player_x,player_y,enemy_p[q]);
                                    }
                                    if (frame2_x_cnt == 3){
                                        HgWImageDraw(layerID_punch_Green[q],player_x,player_y,green_p[q]);
                                    }
                                    if (frame2_x_cnt == 4){
                                        HgWImageDraw(layerID_punch_Pink[q],player_x,player_y,pink_p[q]);
                                    }
                                    if (frame2_x_cnt == 5){
                                        HgWImageDraw(layerID_punch_Red[q],player_x,player_y,red_p[q]);
                                    }
                                    
                                }
                                if (player_LR == 1){ //左向き
                                    if (frame2_x_cnt == 1){
                                        HgWImageDraw(layerID_punch_Player_L[q],player_x,player_y,player_pL[q]);
                                    }
                                    if (frame2_x_cnt == 2){
                                        HgWImageDraw(layerID_punch_Enemy_L[q],player_x,player_y,enemy_pL[q]);
                                    }
                                    if (frame2_x_cnt == 3){
                                        HgWImageDraw(layerID_punch_Green_L[q],player_x,player_y,green_pL[q]);
                                    }
                                    if (frame2_x_cnt == 4){
                                        HgWImageDraw(layerID_punch_Pink_L[q],player_x,player_y,pink_pL[q]);
                                    }
                                    if (frame2_x_cnt == 5){
                                        HgWImageDraw(layerID_punch_Red_L[q],player_x,player_y,red_pL[q]);
                                    }
                                    
                                }
                                q++;
                            }
                            if (q == 10){
                                q = 0;
                                w_ok = 0;
                                punch_f = false;
                                if ((player_x >= enemy_x && player_x <= enemy_x + HIT_RANGE) || (player_x + HIT_RANGE >= enemy_x && player_x + HIT_RANGE <= enemy_x + HIT_RANGE)){
                                    if (player_y + HIT_RANGE_Y >= enemy_y && player_y + HIT_RANGE_Y <= enemy_y + CHARA_HEIGHT){
                                        if (enemy_HP > 0){
                                            critical_random_player = rand() % 10;
                                            //プレイヤーにダメージが当たれば、続けて攻撃する
                                            if (critical_random_player >= 2){
                                                if (player_LR == 0 && enemy_x > 150){ //自分が右向き
                                                    enemy_x += 150;
                                                }
                                                if (player_LR == 0 && enemy_x <= 150){ //右向き
                                                    enemy_x -= enemy_x;
                                                }
                                                if (player_LR == 1 && enemy_x < WIDTH - 150){ //自分が左向き
                                                    enemy_x -= 150;
                                                }
                                                if (player_LR == 1 && enemy_x >= WIDTH - 150){ //左向き
                                                    enemy_x += WIDTH - enemy_x;
                                                }
                                                enemy_HP -= power_player_and_enemy;
                                                black_enemy_width += 20.4;
                                            }
                                            if (critical_random_player == 0 || critical_random_player == 1){
                                                if (player_LR == 0 && enemy_x > 300){ //自分が右向き
                                                    enemy_x += 300;
                                                }
                                                if (player_LR == 1 && enemy_x < WIDTH - 300){ //自分が左向き
                                                    enemy_x -= 300;
                                                }
                                                critical_player_ok = true;
                                                enemy_HP -= power_player_and_enemy * 3;
                                                black_enemy_width += 20.4 * 3;
                                            }
                                            HgWSetFillColor(layerID_back,HgRGBA(0.0,0.0,1.0,0.6));
                                            HgWBoxFill(layerID_back,0,0,WIDTH,HIGHT,0);
                                        }
                                    }
                                }

                            }
                            if (jump == 0 && space_ok == 1){
                                player_y += jump_player_and_enemy;
                                //ジャンプ
                                //HgLClear(layerID_punch_Player[q]);
                                if (frame2_x_cnt == 1){
                                    HgLClear(layerID_punch_Player[q]);
                                    HgLClear(layerID_jump_Player[p]);
                                    HgLClear(layerID_wait_Player[w]);
                                    HgLClear(layerID_walk_Player[wk]);
                                    HgLClear(layerID_punch_Player_L[q]);
                                    HgLClear(layerID_jump_Player_L[p]);
                                    HgLClear(layerID_wait_Player_L[w]);
                                    HgLClear(layerID_walk_Player_L[wk]);
                                }
                                if (frame2_x_cnt == 2){
                                    HgLClear(layerID_punch_Enemy[q]);
                                    HgLClear(layerID_jump_Enemy[p]);
                                    HgLClear(layerID_wait_Enemy[w]);
                                    HgLClear(layerID_walk_Enemy[wk]);
                                    HgLClear(layerID_punch_Enemy_L[q]);
                                    HgLClear(layerID_jump_Enemy_L[p]);
                                    HgLClear(layerID_wait_Enemy_L[w]);
                                    HgLClear(layerID_walk_Enemy_L[wk]);
                                }
                                if (frame2_x_cnt == 3){
                                    HgLClear(layerID_punch_Green[q]);
                                    HgLClear(layerID_jump_Green[p]);
                                    HgLClear(layerID_wait_Green[w]);
                                    HgLClear(layerID_walk_Green[wk]);
                                    HgLClear(layerID_punch_Green_L[q]);
                                    HgLClear(layerID_jump_Green_L[p]);
                                    HgLClear(layerID_wait_Green_L[w]);
                                    HgLClear(layerID_walk_Green_L[wk]);
                                }
                                if (frame2_x_cnt == 4){
                                    HgLClear(layerID_punch_Pink[q]);
                                    HgLClear(layerID_jump_Pink[p]);
                                    HgLClear(layerID_wait_Pink[w]);
                                    HgLClear(layerID_walk_Pink[wk]);
                                    HgLClear(layerID_punch_Pink_L[q]);
                                    HgLClear(layerID_jump_Pink_L[p]);
                                    HgLClear(layerID_wait_Pink_L[w]);
                                    HgLClear(layerID_walk_Pink_L[wk]);
                                }
                                if (frame2_x_cnt == 5){
                                    HgLClear(layerID_punch_Red[q]);
                                    HgLClear(layerID_jump_Red[p]);
                                    HgLClear(layerID_wait_Red[w]);
                                    HgLClear(layerID_walk_Red[wk]);
                                    HgLClear(layerID_punch_Red_L[q]);
                                    HgLClear(layerID_jump_Red_L[p]);
                                    HgLClear(layerID_wait_Red_L[w]);
                                    HgLClear(layerID_walk_Red_L[wk]);
                                }
                                if (punch_f == false){
                                    if (player_LR == 0){
                                        if (frame2_x_cnt == 1){
                                            HgWImageDraw(layerID_jump_Player[p],player_x,player_y,player_j[p]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgWImageDraw(layerID_jump_Enemy[p],player_x,player_y,enemy_j[p]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgWImageDraw(layerID_jump_Green[p],player_x,player_y,green_j[p]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgWImageDraw(layerID_jump_Pink[p],player_x,player_y,pink_j[p]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgWImageDraw(layerID_jump_Red[p],player_x,player_y,red_j[p]);
                                        }
                                    }
                                    if (player_LR == 1){
                                        if (frame2_x_cnt == 1){
                                            HgWImageDraw(layerID_jump_Player_L[p],player_x,player_y,player_jL[p]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgWImageDraw(layerID_jump_Enemy_L[p],player_x,player_y,enemy_jL[p]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgWImageDraw(layerID_jump_Green_L[p],player_x,player_y,green_jL[p]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgWImageDraw(layerID_jump_Pink_L[p],player_x,player_y,pink_jL[p]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgWImageDraw(layerID_jump_Red_L[p],player_x,player_y,red_jL[p]);
                                        }
                                    }
                                }
                                p++;
                            }
                            if (player_y == 400)
                            {
                                jump = 1;
                            }
                            if (jump == 1 && space_ok == 1)
                            {
                                p--;
                                player_y -= jump_player_and_enemy;
                                //ジャンプ
                                if (frame2_x_cnt == 1){
                                    HgLClear(layerID_punch_Player[q]);
                                    HgLClear(layerID_jump_Player[p]);
                                    HgLClear(layerID_wait_Player[w]);
                                    HgLClear(layerID_walk_Player[wk]);
                                    HgLClear(layerID_punch_Player_L[q]);
                                    HgLClear(layerID_jump_Player_L[p]);
                                    HgLClear(layerID_wait_Player_L[w]);
                                    HgLClear(layerID_walk_Player_L[wk]);
                                }
                                if (frame2_x_cnt == 2){
                                    HgLClear(layerID_punch_Enemy[q]);
                                    HgLClear(layerID_jump_Enemy[p]);
                                    HgLClear(layerID_wait_Enemy[w]);
                                    HgLClear(layerID_walk_Enemy[wk]);
                                    HgLClear(layerID_punch_Enemy_L[q]);
                                    HgLClear(layerID_jump_Enemy_L[p]);
                                    HgLClear(layerID_wait_Enemy_L[w]);
                                    HgLClear(layerID_walk_Enemy_L[wk]);
                                }
                                if (frame2_x_cnt == 3){
                                    HgLClear(layerID_punch_Green[q]);
                                    HgLClear(layerID_jump_Green[p]);
                                    HgLClear(layerID_wait_Green[w]);
                                    HgLClear(layerID_walk_Green[wk]);
                                    HgLClear(layerID_punch_Green_L[q]);
                                    HgLClear(layerID_jump_Green_L[p]);
                                    HgLClear(layerID_wait_Green_L[w]);
                                    HgLClear(layerID_walk_Green_L[wk]);
                                }
                                if (frame2_x_cnt == 4){
                                    HgLClear(layerID_punch_Pink[q]);
                                    HgLClear(layerID_jump_Pink[p]);
                                    HgLClear(layerID_wait_Pink[w]);
                                    HgLClear(layerID_walk_Pink[wk]);
                                    HgLClear(layerID_punch_Pink_L[q]);
                                    HgLClear(layerID_jump_Pink_L[p]);
                                    HgLClear(layerID_wait_Pink_L[w]);
                                    HgLClear(layerID_walk_Pink_L[wk]);
                                }
                                if (frame2_x_cnt == 5){
                                    HgLClear(layerID_punch_Red[q]);
                                    HgLClear(layerID_jump_Red[p]);
                                    HgLClear(layerID_wait_Red[w]);
                                    HgLClear(layerID_walk_Red[wk]);
                                    HgLClear(layerID_punch_Red_L[q]);
                                    HgLClear(layerID_jump_Red_L[p]);
                                    HgLClear(layerID_wait_Red_L[w]);
                                    HgLClear(layerID_walk_Red_L[wk]);
                                }
                                if (punch_f == false){
                                    if (player_LR == 0){
                                        if (frame2_x_cnt == 1){
                                            HgWImageDraw(layerID_jump_Player[p],player_x,player_y,player_j[p]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgWImageDraw(layerID_jump_Enemy[p],player_x,player_y,enemy_j[p]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgWImageDraw(layerID_jump_Green[p],player_x,player_y,green_j[p]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgWImageDraw(layerID_jump_Pink[p],player_x,player_y,pink_j[p]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgWImageDraw(layerID_jump_Red[p],player_x,player_y,red_j[p]);
                                        }
                                    }
                                    if (player_LR == 1){
                                        if (frame2_x_cnt == 1){
                                            HgWImageDraw(layerID_jump_Player_L[p],player_x,player_y,player_jL[p]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgWImageDraw(layerID_jump_Enemy_L[p],player_x,player_y,enemy_jL[p]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgWImageDraw(layerID_jump_Green_L[p],player_x,player_y,green_jL[p]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgWImageDraw(layerID_jump_Pink_L[p],player_x,player_y,pink_jL[p]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgWImageDraw(layerID_jump_Red_L[p],player_x,player_y,red_jL[p]);
                                        }
                                    }
                                }

                            }
                            if (player_y == 100){
                                jump = 0;
                                space_ok = 0;
                                p = 0;
                            }
                            if (jump == 0 && space_ok == 0){
                                //ウェイト
                                if (jump_f == true && w_ok == 0){
                                    if (frame2_x_cnt == 1){
                                        HgLClear(layerID_jump_Player[p]);
                                        HgLClear(layerID_walk_Player[wk]);
                                        HgLClear(layerID_jump_Player_L[p]);
                                        HgLClear(layerID_walk_Player_L[wk]);
                                    }
                                    if (frame2_x_cnt == 2){
                                        HgLClear(layerID_jump_Enemy[p]);
                                        HgLClear(layerID_walk_Enemy[wk]);
                                        HgLClear(layerID_jump_Enemy_L[p]);
                                        HgLClear(layerID_walk_Enemy_L[wk]);
                                    }
                                    if (frame2_x_cnt == 3){
                                        HgLClear(layerID_jump_Green[p]);
                                        HgLClear(layerID_walk_Green[wk]);
                                        HgLClear(layerID_jump_Green_L[p]);
                                        HgLClear(layerID_walk_Green_L[wk]);
                                    }
                                    if (frame2_x_cnt == 4){
                                        HgLClear(layerID_jump_Pink[p]);
                                        HgLClear(layerID_walk_Pink[wk]);
                                        HgLClear(layerID_jump_Pink_L[p]);
                                        HgLClear(layerID_walk_Pink_L[wk]);
                                    }
                                    if (frame2_x_cnt == 5){
                                        HgLClear(layerID_jump_Red[p]);
                                        HgLClear(layerID_walk_Red[wk]);
                                        HgLClear(layerID_jump_Red_L[p]);
                                        HgLClear(layerID_walk_Red_L[wk]);
                                    }
                                }
                                if (frame2_x_cnt == 1){
                                    HgLClear(layerID_wait_Player[w]);
                                    HgLClear(layerID_wait_Player_L[w]);
                                }
                                if (frame2_x_cnt == 2){
                                    HgLClear(layerID_wait_Enemy[w]);
                                    HgLClear(layerID_wait_Enemy_L[w]);
                                }
                                if (frame2_x_cnt == 3){
                                    HgLClear(layerID_wait_Green[w]);
                                    HgLClear(layerID_wait_Green_L[w]);
                                }
                                if (frame2_x_cnt == 4){
                                    HgLClear(layerID_wait_Pink[w]);
                                    HgLClear(layerID_wait_Pink_L[w]);
                                }
                                if (frame2_x_cnt == 5){
                                    HgLClear(layerID_wait_Red[w]);
                                    HgLClear(layerID_wait_Red_L[w]);
                                }
                                if (punch_f == false){
                                    if (player_LR == 0){
                                        if (frame2_x_cnt == 1){
                                            HgWImageDraw(layerID_wait_Player[w],player_x,player_y,player_w[w]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgWImageDraw(layerID_wait_Enemy[w],player_x,player_y,enemy_w[w]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgWImageDraw(layerID_wait_Green[w],player_x,player_y,green_w[w]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgWImageDraw(layerID_wait_Pink[w],player_x,player_y,pink_w[w]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgWImageDraw(layerID_wait_Red[w],player_x,player_y,red_w[w]);
                                        }
                                    }
                                    if (player_LR == 1){
                                        if (frame2_x_cnt == 1){
                                            HgWImageDraw(layerID_wait_Player_L[w],player_x,player_y,player_wL[w]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgWImageDraw(layerID_wait_Enemy_L[w],player_x,player_y,enemy_wL[w]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgWImageDraw(layerID_wait_Green_L[w],player_x,player_y,green_wL[w]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgWImageDraw(layerID_wait_Pink_L[w],player_x,player_y,pink_wL[w]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgWImageDraw(layerID_wait_Red_L[w],player_x,player_y,red_wL[w]);
                                        }
                                    }
                                }
                                w++;
                                if (w == 5){
                                    w = 0;
                                }
                            }
                            
                            if (event != NULL){
                                switch (event -> ch){
                                    case 'c':   //パンチ
                                        if (w_ok == 0){
                                            w_ok = 1;
                                            punch_f = true;
                                        }
                                        break;
                                    
                                    case ' ':   //ジャンプ
                                        if (space_ok == 0){
                                            space_ok = 1;
                                            jump = 0;
                                            jump_f = true;
                                        }
                                        break;
                                    case ',':   //左に移動
                                        if (player_x >= -50){
                                            player_x -= speed_player_and_enemy;
                                        }
                                        player_LR = 1;
                                        if (frame2_x_cnt == 1){
                                            HgLClear(layerID_punch_Player[q]);
                                            HgLClear(layerID_jump_Player[p]);
                                            HgLClear(layerID_wait_Player[w]);
                                            HgLClear(layerID_walk_Player[wk]);
                                            HgLClear(layerID_punch_Player_L[q]);
                                            HgLClear(layerID_jump_Player_L[p]);
                                            HgLClear(layerID_wait_Player_L[w]);
                                            HgLClear(layerID_walk_Player_L[wk]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgLClear(layerID_punch_Enemy[q]);
                                            HgLClear(layerID_jump_Enemy[p]);
                                            HgLClear(layerID_wait_Enemy[w]);
                                            HgLClear(layerID_walk_Enemy[wk]);
                                            HgLClear(layerID_punch_Enemy_L[q]);
                                            HgLClear(layerID_jump_Enemy_L[p]);
                                            HgLClear(layerID_wait_Enemy_L[w]);
                                            HgLClear(layerID_walk_Enemy_L[wk]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgLClear(layerID_punch_Green[q]);
                                            HgLClear(layerID_jump_Green[p]);
                                            HgLClear(layerID_wait_Green[w]);
                                            HgLClear(layerID_walk_Green[wk]);
                                            HgLClear(layerID_punch_Green_L[q]);
                                            HgLClear(layerID_jump_Green_L[p]);
                                            HgLClear(layerID_wait_Green_L[w]);
                                            HgLClear(layerID_walk_Green_L[wk]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgLClear(layerID_punch_Pink[q]);
                                            HgLClear(layerID_jump_Pink[p]);
                                            HgLClear(layerID_wait_Pink[w]);
                                            HgLClear(layerID_walk_Pink[wk]);
                                            HgLClear(layerID_punch_Pink_L[q]);
                                            HgLClear(layerID_jump_Pink_L[p]);
                                            HgLClear(layerID_wait_Pink_L[w]);
                                            HgLClear(layerID_walk_Pink_L[wk]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgLClear(layerID_punch_Red[q]);
                                            HgLClear(layerID_jump_Red[p]);
                                            HgLClear(layerID_wait_Red[w]);
                                            HgLClear(layerID_walk_Red[wk]);
                                            HgLClear(layerID_punch_Red_L[q]);
                                            HgLClear(layerID_jump_Red_L[p]);
                                            HgLClear(layerID_wait_Red_L[w]);
                                            HgLClear(layerID_walk_Red_L[wk]);
                                        }
                                        if (frame2_x_cnt == 1){
                                            HgWImageDraw(layerID_walk_Player_L[wk],player_x,player_y,player_wkL[wk]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgWImageDraw(layerID_walk_Enemy_L[wk],player_x,player_y,enemy_wkL[wk]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgWImageDraw(layerID_walk_Green_L[wk],player_x,player_y,green_wkL[wk]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgWImageDraw(layerID_walk_Pink_L[wk],player_x,player_y,pink_wkL[wk]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgWImageDraw(layerID_walk_Red_L[wk],player_x,player_y,red_wkL[wk]);
                                        }
                                        wk++;
                                        if (wk == 8){
                                            wk = 0;
                                        }
                                        break;

                                    case '.':   //右に移動
                                        if (player_x <= 1075){
                                            player_x += speed_player_and_enemy;
                                        }
                                        player_LR = 0;
                                        if (frame2_x_cnt == 1){
                                            HgLClear(layerID_punch_Player[q]);
                                            HgLClear(layerID_jump_Player[p]);
                                            HgLClear(layerID_wait_Player[w]);
                                            HgLClear(layerID_walk_Player[wk]);
                                            HgLClear(layerID_punch_Player_L[q]);
                                            HgLClear(layerID_jump_Player_L[p]);
                                            HgLClear(layerID_wait_Player_L[w]);
                                            HgLClear(layerID_walk_Player_L[wk]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgLClear(layerID_punch_Enemy[q]);
                                            HgLClear(layerID_jump_Enemy[p]);
                                            HgLClear(layerID_wait_Enemy[w]);
                                            HgLClear(layerID_walk_Enemy[wk]);
                                            HgLClear(layerID_punch_Enemy_L[q]);
                                            HgLClear(layerID_jump_Enemy_L[p]);
                                            HgLClear(layerID_wait_Enemy_L[w]);
                                            HgLClear(layerID_walk_Enemy_L[wk]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgLClear(layerID_punch_Green[q]);
                                            HgLClear(layerID_jump_Green[p]);
                                            HgLClear(layerID_wait_Green[w]);
                                            HgLClear(layerID_walk_Green[wk]);
                                            HgLClear(layerID_punch_Green_L[q]);
                                            HgLClear(layerID_jump_Green_L[p]);
                                            HgLClear(layerID_wait_Green_L[w]);
                                            HgLClear(layerID_walk_Green_L[wk]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgLClear(layerID_punch_Pink[q]);
                                            HgLClear(layerID_jump_Pink[p]);
                                            HgLClear(layerID_wait_Pink[w]);
                                            HgLClear(layerID_walk_Pink[wk]);
                                            HgLClear(layerID_punch_Pink_L[q]);
                                            HgLClear(layerID_jump_Pink_L[p]);
                                            HgLClear(layerID_wait_Pink_L[w]);
                                            HgLClear(layerID_walk_Pink_L[wk]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgLClear(layerID_punch_Red[q]);
                                            HgLClear(layerID_jump_Red[p]);
                                            HgLClear(layerID_wait_Red[w]);
                                            HgLClear(layerID_walk_Red[wk]);
                                            HgLClear(layerID_punch_Red_L[q]);
                                            HgLClear(layerID_jump_Red_L[p]);
                                            HgLClear(layerID_wait_Red_L[w]);
                                            HgLClear(layerID_walk_Red_L[wk]);
                                        }
                                        if (frame2_x_cnt == 1){
                                            HgWImageDraw(layerID_walk_Player[wk],player_x,player_y,player_wk[wk]);
                                        }
                                        if (frame2_x_cnt == 2){
                                            HgWImageDraw(layerID_walk_Enemy[wk],player_x,player_y,enemy_wk[wk]);
                                        }
                                        if (frame2_x_cnt == 3){
                                            HgWImageDraw(layerID_walk_Green[wk],player_x,player_y,green_wk[wk]);
                                        }
                                        if (frame2_x_cnt == 4){
                                            HgWImageDraw(layerID_walk_Pink[wk],player_x,player_y,pink_wk[wk]);
                                        }
                                        if (frame2_x_cnt == 5){
                                            HgWImageDraw(layerID_walk_Red[wk],player_x,player_y,red_wk[wk]);
                                        }
                                        wk++;
                                        if (wk == 8){
                                            wk = 0;
                                        }
                                        break;

                                    case 'q':
                                        HgClose();
                                        return 0;
                                }
                            }
                        }
                        //---------------------------プレイヤーの処理ここまで-------------------------------------------
                    }
                    if (enemy_HP <= 0 || player_HP <= 0 || score <= 0){
                        game_set_warning = true;
                        HgSoundStop(bgm_2);
                        HgSoundStop(bgm_3);

                        if (enemy_HP <= 0 || player_HP <= 0){
                            if (se_cnt == 0){
                                HgSoundVolume(voice_2,1.0,0);
                                HgSoundPlay(voice_2);
                                //HgSoundVolume(se_1,1.0,0);
                                //HgSoundPlay(se_1);
                            }
                        }                        
                        if (score <= 0){
                            if (se_cnt == 0){
                                HgSoundVolume(voice_7,1.0,0);
                                HgSoundPlay(voice_7);
                                //HgSoundVolume(se_1,1.0,1);
                                //HgSoundPlay(se_1);
                            }
                        }
                        se_cnt ++;
                        HgWImageDraw(layerID_game_set,game_x,500,game);
                        HgWImageDraw(layerID_game_set,set_x,420,set);
                        if (game_x < 450){
                            game_x += 200;
                        }
                        if (game_x >= 450 && set_x >= 550){
                            set_x -= 200;
                        }
                        if (set_x <= 550){
                            game_set_time ++;
                            if (enemy_HP <= 0){
                                if (se_cnt == 20){
                                    HgSoundStop(voice_2);
                                    HgSoundStop(voice_7);
                                    HgSoundVolume(voice_5,1.0,0);
                                    HgSoundPlay(voice_5);
                                }
                                HgWImageDraw(layerID_game_set,430,350,player_win);
                            }
                            if (player_HP <= 0){
                                if (se_cnt == 20){
                                    HgSoundStop(voice_2);
                                    HgSoundStop(voice_7);
                                    HgSoundVolume(voice_4,1.0,0);
                                    HgSoundPlay(voice_4);
                                }
                                HgWImageDraw(layerID_game_set,430,350,enemy_win);
                            }
                            if (score <= 0){
                                if (se_cnt == 20){
                                    HgSoundStop(voice_2);
                                    HgSoundStop(voice_7);
                                    HgSoundVolume(voice_1,1.0,0);
                                    HgSoundPlay(voice_1);
                                }
                                HgWImageDraw(layerID_game_set,430,350,draw);
                            }
                        }
                        if (game_set_time >= 30){
                            game_set_f = true;
                        }
                    }
                    if (enemy_HP <= 0 && game_set_f == true){   //ゲームクリア処理
                        if (mode_status == 3){
                            game_status = 2;    //ゲームクリア処理に移動
                        }else{
                            game_status = 0;
                        }
                        break;
                    }
                    if ((score <= 0 && game_set_f == true) || (player_HP <= 0 && game_set_f == true)){  //ゲームオーバー処理
                        game_status = 3;    //ゲームオーバー処理に移動
                        break;
                    }
                }
                break;

            case 2:
                system(program);
                HgClear();
                HgSoundStop(se_1);
                file = fopen("vsfighterRanking100.rnk","a");
                fprintf(file,"%d\n",score);
                fclose(file);

                file = fopen("vsfighterRanking100.rnk","r");
                out = fopen("b.txt","w");
                if (file == NULL){
                    printf("ファイルをオープンできませんでした。\n");
                    return 1;
                }
                for(i = 0; i < total; i++){
                    fscanf(file,"%d\n",&number[i]);
                }
                //数値を降順にソート
                for(i = 0; i < total; i++){
                    for(j = i + 1; j < total; j++){
                        if (number[i] < number[j]){
                            tmp = number[i];
                            number[i] = number[j];
                            number[j] = tmp;
                        }
                    }
                    
                    if (number[i] >= score){
                        if (rank <= 100){
                            rank++;
                        }
                    }
                }
                total -= 1;
                for(i = 0;i < total; i++){
                    fprintf(out, "%d\n",number[i]);
                }
                HgImageDraw(0,0,title_back);
                HgSetFont(HG_T,40);
                HgSetColor(HG_WHITE);
                HgText(WIDTH/2 - 190, HIGHT/2, "タイム(スコア)：%d\n",score);
                if (rank < 101){
                    HgText(WIDTH/2 - 190, HIGHT/2 - 70, "第%d位 / 100\n",rank);
                }
                if (rank >= 101){
                    HgText(WIDTH/2 - 190, HIGHT/2 - 70, "ランキング外でした...\n");
                }
                
                //上位５人を表示
                HgSetFont(HG_T,30);
                if (rank < 101){    //ランキング内
                    HgText(450,ranking_y + 60,"上位５人");
                }
                if (rank >= 101){   //ランキング外
                    HgText(580,ranking_y + 60,"上位５人");
                }
                for(i = 0; i < 5; i++){
                    HgSetFont(HG_T,20);
                    HgSetColor(HG_WHITE);
                    fscanf(file,"%d\n",&number[i]);
                    if (rank < 101){    //ランキング内
                        HgText(470,ranking_y - i*40,"%d位 : %d\n",i+1,number[i]);
                    }
                    if (rank >= 101){   //ランキング外
                        HgText(600,ranking_y - i*40,"%d位 : %d\n",i+1,number[i]);
                    }
                }
                if (rank < 101){
                    HgSetFont(HG_T,20);
                    HgText(630,ranking_y + 60,"周辺のスコア\n(赤色がプレイヤーさんです。)");
                    if (rank == 1){ //自分が1位
                        HgSetFont(HG_T,20);
                        HgSetColor(HG_RED);
                        HgText(650,ranking_y,"%d : %d\n",rank,number[rank-1]);    //自分
                        HgSetColor(HG_WHITE);
                        HgText(650,ranking_y - 30,"%d : %d\n",rank+1,number[rank]);
                        HgText(650,ranking_y - 60,"%d : %d\n",rank+2,number[rank+1]);
                        HgText(650,ranking_y - 90,"%d : %d\n",rank+3,number[rank+2]);
                        HgText(650,ranking_y - 120,"%d : %d\n",rank+4,number[rank+3]);                        
                    }
                    if (rank == 2){ //自分が2位
                        HgSetFont(HG_T,20);
                        HgSetColor(HG_RED);
                        HgText(650,ranking_y - 30,"%d : %d\n",rank,number[rank-1]);    //自分
                        HgSetColor(HG_WHITE);
                        HgText(650,ranking_y,"%d : %d\n",rank-1,number[rank-2]);
                        HgText(650,ranking_y - 60,"%d : %d\n",rank+1,number[rank]);
                        HgText(650,ranking_y - 90,"%d : %d\n",rank+2,number[rank+1]);
                        HgText(650,ranking_y - 120,"%d : %d\n",rank+3,number[rank+2]);
                    }
                    if (rank >= 3 && rank < 98){   //自分が3位以下〜97位以上
                        HgSetFont(HG_T,20);
                        HgSetColor(HG_RED);
                        HgText(650,ranking_y - 60,"%d : %d\n",rank,number[rank-1]);    //自分
                        HgSetColor(HG_WHITE);
                        HgText(650,ranking_y,"%d : %d\n",rank-2,number[rank-3]);
                        HgText(650,ranking_y - 30,"%d : %d\n",rank-1,number[rank-2]);
                        HgText(650,ranking_y - 90,"%d : %d\n",rank+1,number[rank]);
                        HgText(650,ranking_y - 120,"%d : %d\n",rank+2,number[rank+1]);
                    }
                    if (rank == 99){   //自分が99位
                        HgSetFont(HG_T,20);
                        HgSetColor(HG_RED);
                        HgText(650,ranking_y - 90,"%d : %d\n",rank,number[rank-1]);    //自分
                        HgSetColor(HG_WHITE);
                        HgText(650,ranking_y,"%d : %d\n",rank-3,number[rank-4]);
                        HgText(650,ranking_y - 30,"%d : %d\n",rank-2,number[rank-3]);
                        HgText(650,ranking_y - 60,"%d : %d\n",rank-1,number[rank-2]);
                        HgText(650,ranking_y - 120,"%d : %d\n",rank+1,number[rank]);
                    }
                    if (rank == 100){   //自分が100位
                        HgSetFont(HG_T,20);
                        HgSetColor(HG_RED);
                        HgText(650,ranking_y - 120,"%d : %d\n",rank,number[rank-1]);    //自分
                        HgSetColor(HG_WHITE);
                        HgText(650,ranking_y,"%d : %d\n",rank-4,number[rank-5]);
                        HgText(650,ranking_y - 30,"%d : %d\n",rank-3,number[rank-4]);
                        HgText(650,ranking_y - 60,"%d : %d\n",rank-2,number[rank-3]);
                        HgText(650,ranking_y - 90,"%d : %d\n",rank-1,number[rank-2]);
                    }
                }
                fclose(file);
                fclose(out);
                remove("vsfighterRanking100.rnk");
                rename("b.txt","vsfighterRanking100.rnk");
                HgSetFont(HG_T,20);
                HgSetColor(HG_WHITE);
                HgText(WIDTH/2 - 200, HIGHT/2 - 120, "ただいま、データをアップロードしています。\n自動で終了するので、しばらくお待ちください。\n");
                system(program2);
                game_status = 0;
                break;

            case 3:
                HgClear();
                HgSoundStop(se_1);
                HgImageDraw(0,0,title_back);
                HgSetColor(HG_WHITE);
                if (player_HP <= 0){
                    HgSetFont(HG_T,40);
                    HgText(WIDTH/2-150,HIGHT/2,"ゲームオーバー...");
                    HgSetFont(HG_T,20);
                }
                if (score <= 0){
                    HgSetFont(HG_T,40);
                    HgText(WIDTH/2-150,HIGHT/2,"タイムオーバー...");
                    HgSetFont(HG_T,20);
                    HgText(WIDTH/2-150,HIGHT/2 - 20,"(タイムが0になりました)");
                }
                HgSetFont(HG_T,20);
                HgSetColor(HG_WHITE);
                HgText(WIDTH/2 - 200, HIGHT/2 - 120, "自動でタイトルに戻るので、しばらくお待ちください。\n");
                HgSleep(4.0);
                game_status = 0;
                break;
            }
        }
    return 0;
}
