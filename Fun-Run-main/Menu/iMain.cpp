#include "iGraphics.h"
#include <stdio.h>

// Variables
int menu,name,level1,level2,level3,over,bird1,bird2,coin1,coin2,coin3,pig1,pig2,pig3,enemy,life,up_bg1,up_bg2,up_bg3,scorepic,choose,obstacle,enemy1,enemy2,enemy3,instruction,about,story; // picture variable
int gamestate = 0;
int option = 0;
int namestate = 0;
char name_str[100], backup_str[100];
int name_length;
int level = 1;
int levelstate = 0;
int img_position[64];
char img_name[64][18]= { "src\\01.bmp","src\\02.bmp","src\\03.bmp","src\\04.bmp","src\\05.bmp","src\\06.bmp","src\\07.bmp","src\\08.bmp","src\\09.bmp","src\\10.bmp","src\\11.bmp", "src\\12.bmp", "src\\13.bmp","src\\14.bmp","src\\15.bmp","src\\16.bmp","src\\17.bmp", "src\\18.bmp","src\\19.bmp","src\\20.bmp","src\\21.bmp","src\\22.bmp", "src\\23.bmp","src\\24.bmp","src\\25.bmp","src\\26.bmp","src\\27.bmp", "src\\28.bmp","src\\29.bmp","src\\30.bmp","src\\31.bmp","src\\32.bmp","src\\33.bmp","src\\34.bmp","src\\35.bmp","src\\36.bmp","src\\37.bmp","src\\38.bmp","src\\39.bmp","src\\40.bmp","src\\41.bmp","src\\42.bmp","src\\43.bmp","src\\44.bmp","src\\45.bmp","src\\46.bmp","src\\47.bmp","src\\48.bmp","src\\49.bmp","src\\50.bmp","src\\51.bmp","src\\52.bmp","src\\53.bmp","src\\54.bmp","src\\55.bmp","src\\56.bmp","src\\57.bmp","src\\58.bmp","src\\59.bmp","src\\60.bmp","src\\61.bmp","src\\62.bmp","src\\63.bmp","src\\64.bmp"};
int i;
int score  = 0;
int health = 3;
int jump_y = 0;
int jump_limit = 120;
FILE *nameinfo;
char score_string[20];
int sc;
char name2[20];
char score2[20];
int first = 320;
int second = 0;
int obstacle_x1 = 1200;
int obstacle_x2 = 100;
int enemy_x = 20;
int enemy_y = 135;
int c_option = 0;

// Booleans
bool jump = false;
bool jumpUp = false;
bool jumpDown = false;
bool musicOn = false;

// Structures
struct Object1 {
	int x,y,width,height,speed;
	
	// function for coin and bomb falling
	void setposition() {
		if ( y < 130 ) {
			x = rand() % 1100;
			y = 720;
			speed = rand()%10 + 6;
		}
		else {
			y -= speed;
		}
	}
	void setenemy() {
		if ( x < 0 ) {
			x = 1100;
			y = 300;
		}
		else {
			x -= speed;
		}
	}
}g_bird,g_coin[2],g_dragon,g_pig[4];

// Functions
void imgposf();
void saveinfo();
void levelIntro();
void levelCheck();
void healthCheck();
void loadPicture();
void loadElement();
void coll();
void showHealth();
void jump_change();
void showInfo();
void setPosition();
void obstaclePosition1();
void obstaclePosition2();
void groundEnemy();


void iDraw()
{
	iClear();
	
	// Game Menu 
	if ( gamestate == 0 ) {

		if ( option == 0 ) {
			iShowImage(0, 0, 1280, 750, menu);
		}

		else if ( option == 1 ) {
			iShowImage(0, 0, 1280, 720, name); // Name Picture
			if ( namestate == 1 ) {
			iText(640, 370, name_str, GLUT_BITMAP_TIMES_ROMAN_24); // Name Box
			}
		}
		else if ( option == 2 ) {
			showInfo();
		}
		else if ( option == 3 ) {
			iShowImage(0, 0, 1280, 720, story);
		}
		else if ( option == 4 ) {
			iShowImage(0, 0, 1280, 720, about);
		}
		else if ( option == 5 ) {
			iShowImage(0, 0, 1280, 720, instruction);
		}
		else if ( option == 6 ) {
			exit(0);
		}
	
	}
	else if ( gamestate == 7 ) {
			iShowImage (0, 0, 1280, 720, choose );
		}

	// Level 01 
	else if ( gamestate == 1 && level == 1 ) {
		
		if (levelstate == 0) levelIntro(); // Intro
	    
		else {
			loadPicture();
			loadElement();
			coll();
		}
	}

	// Level 02
	else if ( gamestate == 1 && level == 2 ) {
		
		if ( levelstate == 0) levelIntro(); // Intro 

		else {
			loadPicture();
			loadElement();
			coll();
		}
	}
	// Level 03
	else if ( gamestate == 1 && level == 3 ) {
		if (levelstate == 0) levelIntro(); // Intro
		else {
			loadPicture();
			loadElement();
			coll();
		}
	}
	// Game Over
	if ( gamestate == 6 ) {
		iShowImage(0,0,1280,720,over);
	}
	levelCheck();
	healthCheck();
	showHealth();
}

void iPassiveMouse(int x, int y)
{
	
}
void iMouseMove(int mx, int my)
{
	
}
void iMouse(int button, int state, int mx, int my)
{
	printf("x = %d and y = %d\n",mx,my);

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// Menu Option
		if ( gamestate == 0 && option == 0 && mx >= 80 && mx <= 230 && my >= 610 && my <= 670 ) {
			option = 1;
		}
		else if ( gamestate == 0 && option == 0 && mx >= 80 && mx <= 230 && my >= 525 && my <= 575 ) {
			option = 2;
		}
		else if ( gamestate == 0 && option == 0 && mx >= 80 && mx <= 230 && my >= 400 && my <= 500 ) {
			option = 3;
		}
		else if ( gamestate == 0 && option == 0 && mx >= 80 && mx <= 230 && my >= 355 && my <= 415 ) {
			option = 4;
		}
		else if ( gamestate == 0 && option == 0 && mx >= 80 && mx <= 230 && my >= 265 && my <= 325 ) {
			option = 5;
		}
		else if ( gamestate == 0 && option == 0 && mx >= 80 && mx <= 230 && my >= 180 && my <= 230 ) {
			option = 6;
		}
		// Name
		else if ( gamestate == 0 && option == 1 && namestate == 0 && mx >= 350 && mx <= 1020 && my >= 360 && my <= 420 ) {
			namestate = 1;
		}
		else if ( gamestate == 0 && option == 2 && mx >= 55 && mx <= 135 && my >= 20 && my <= 50 ) {
			option = 0;
		}
		else if ( gamestate == 0 && option == 3 && mx >= 940 && mx <= 1070 && my >= 110 && my <= 150 ) {
			option = 0;
		}
		else if ( gamestate == 0 && option == 4 && mx >= 1030 && mx <= 1160 && my >= 80 && my <= 120 ) {
			option = 0;
		}
		else if ( gamestate == 0 && option == 5 && mx >= 950 && mx <= 1065 && my >= 95 && my <= 140 ) {
			option = 0;
		}
		else if ( gamestate == 1 && level == 1 && levelstate == 0 && mx >= 350 && mx <= 920 && my >= 350 && my <= 420 ) {
			levelstate = 1;
		}
		else if ( gamestate == 1 && level == 2 && levelstate == 0 && mx >= 350 && mx <= 920 && my >= 350 && my <= 420 ) {
			levelstate = 1;
		}
		else if ( gamestate == 1 && level == 3 && levelstate == 0 && mx >= 350 && mx <= 920 && my >= 350 && my <= 420 ) {
			levelstate = 1;
		}
		else if ( gamestate == 7 && mx >= 70 && mx <= 360 && my >= 80 && my <= 700 ) {
			c_option = 0;
			gamestate = 1;
		}
		else if ( gamestate == 7 && mx >= 800 && mx <= 1150 && my >= 70 && my <= 625 ) {
			c_option = 1;
			gamestate = 1;
		}
	}
	
}
void iKeyboard(unsigned char key)
{
	if ( namestate == 1 ) {
		if ( key == '\r' ) {
			namestate = 0;
			gamestate = 7;
		}
		else {
			name_str[name_length] = key;
			name_length ++;
		}
	}

	if ( key == ' ' ) {
		if ( !jump ) {
			jump = true;
			jumpUp = true;
		}
	}

	if ( key == 'x' ) { 
		saveinfo();
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_F1)
	{
		if (musicOn)
		{
			musicOn = false;
			PlaySound (0, 0, 0);
		}

		else
		{
		    musicOn = true;
            PlaySound ("angry_birds_theme.wav", NULL, SND_ASYNC | SND_LOOP);
		}
	}
	
	if ( key == GLUT_KEY_LEFT ) {
		g_bird.x -= g_bird.speed;
	}
	if ( key == GLUT_KEY_RIGHT ) {
		g_bird.x += g_bird.speed;
	}
}

void imgposf() {
	
	int first = 0;
	for(i = 0; i < 64; i++)
	{
		img_position[i] = first;
		first += 20;
	}
	
}
void saveinfo() {
	strcpy ( backup_str, name_str);
	nameinfo = fopen ("info.txt", "a");
	fprintf (nameinfo, "%s %d\n", backup_str, score);
	fclose (nameinfo);
	exit(0);
}

void showInfo() {
	iShowImage(0, 0, 1280, 720, scorepic );
		int name_x = 572;
		int score_x = 890;
		int both_y = 535;
		nameinfo = fopen ( "info.txt", "r");
		while (fscanf( nameinfo, "%s  %d", name2, &sc ) != EOF) {
			sprintf(score2, "%d", sc);
			iText ( name_x, both_y, name2, GLUT_BITMAP_TIMES_ROMAN_24 );
			iText ( score_x, both_y, score2, GLUT_BITMAP_TIMES_ROMAN_24 );
			both_y -= 58;
		}
		fclose( nameinfo );
}

void levelIntro() {
	if ( level == 1 ) {
		iShowImage ( 0, 0, 1280, 720, level1);
	}
	if ( level == 2 ) {
		iShowImage ( 0, 0, 1280, 720, level2);
	}
	if ( level == 3 ) {
		iShowImage ( 0, 0, 1280, 720, level3);
	}
}

void loadPicture() {
	if ( level == 1 && levelstate == 1 ) {
		iShowImage(0, 135, 1280, 595, up_bg1 ); // Upper background Picture
	}
	if ( level == 2 && levelstate == 1 ) {
		iShowImage(0, 135, 1280, 595, up_bg2 ); // Upper background Picture
	}
	if ( level == 3 && levelstate == 1 ) {
		iShowImage(0, 135, 1280, 595, up_bg3 ); // Upper background Picture
	}
	for(i=0; i < 64; i++) {
		iShowBMP(img_position[i],0,img_name[i]); // Lower Background Pictures 
	}
		
	for(i=0; i<64; i++) {
		img_position[i] -= 20;   // Picture Rendering
		if(img_position[i] < 0) {
			img_position[i] = 1260;
		}
	}
	if ( c_option == 0 ) {
		if ( jump ) {
			iShowImage ( g_bird.x, g_bird.y + jump_y, g_bird.width, g_bird.height, bird1); // Bird Picture
		}
		else {
			iShowImage ( g_bird.x, g_bird.y + jump_y, g_bird.width, g_bird.height, bird1); // Bird Picture
		}
	}
	else if ( c_option == 1 ) {
		if ( jump ) {
			iShowImage ( g_bird.x, g_bird.y + jump_y, g_bird.width, g_bird.height, bird2); // Bird Picture
		}
		else {
			iShowImage ( g_bird.x, g_bird.y + jump_y, g_bird.width, g_bird.height, bird2); // Bird Picture
		}
	}
}

void loadElement() {
	
		// Randomly Coin Falling 
	
	if ( level == 1 && levelstate == 1 ) {
		for( i=0; i<4; i++) {
			iShowImage ( g_pig[i].x, g_pig[i].y, g_pig[i].width, g_pig[i].height, pig1 ); // Bomb Picture
			g_pig[i].setposition();  
		}
		for ( i = 0; i < 2; i++ ) {
			iShowImage ( g_coin[i].x, g_coin[i].y, g_coin[i].width, g_coin[i].height, coin1); // Coin Picture
			g_coin[i].setposition();
		}
	}

	
	if ( level == 2 && levelstate == 1 ) {
		for( i=0; i<4; i++) {
			iShowImage ( g_pig[i].x, g_pig[i].y, g_pig[i].width, g_pig[i].height, pig2 ); // Bomb Picture
			g_pig[i].setposition();  
		}
		for ( i = 0; i < 2; i++ ) {
			iShowImage ( g_coin[i].x, g_coin[i].y, g_coin[i].width, g_coin[i].height, coin2); // Coin Picture
			g_coin[i].setposition();
		}
		iShowImage ( obstacle_x1, 135, 24, 60, obstacle );
		iShowImage ( obstacle_x2, 135, 24, 60, obstacle );
	}



	if ( level == 3 && levelstate == 1 ) {
		for( i=0; i<4; i++) {
			iShowImage ( g_pig[i].x, g_pig[i].y, g_pig[i].width, g_pig[i].height, pig3 ); // Bomb Picture
			g_pig[i].setposition();  
		}
		for ( i = 0; i < 2; i++ ) {
			iShowImage ( g_coin[i].x, g_coin[i].y, g_coin[i].width, g_coin[i].height, coin3); // Coin Picture
			g_coin[i].setposition();
		}
		iShowImage ( g_dragon.x, g_dragon.y, g_dragon.width, g_dragon.height, enemy);// Dragon Picture
		g_dragon.setenemy();// Moving Dragon
		groundEnemy();
	}

}

void coll() {
	// Score Check
	for ( i = 0; i < 2; i++ ) {
		if ( ( g_coin[i].x + g_coin[i].width > g_bird.x && g_coin[i].x < g_bird.x + g_bird.width ) && ( g_coin[i].y <= g_bird.y + g_bird.height + jump_y && g_bird.y + jump_y <= g_coin[i].y + g_coin[i].height)) {
			g_coin[i].y = -100;
			if ( level == 1 ) score += 10;
			else if ( level == 2 ) score += 20;
			else if ( level == 3 ) score += 30;
		}
	}
		
	// Show Score
	sprintf(score_string, "%d", score);
	iText ( 640, 690, score_string, GLUT_BITMAP_TIMES_ROMAN_24);

	// Bomb
	for ( i=0; i<4; i++) {
		if ( ( g_pig[i].x + g_pig[i].width > g_bird.x && g_pig[i].x < g_bird.x + g_bird.width ) && ( g_pig[i].y <= g_bird.y + g_bird.height + jump_y && g_bird.y + jump_y <= g_pig[i].y + g_pig[i].height)) {
				g_pig[i].y = -20;
				health -= 1;
		}
	}
	
	// Obstacle
	if ( level == 2 && levelstate == 1 ) {
		if ( obstacle_x1 + 12 >= g_bird.x && g_bird.x + g_bird.width >= obstacle_x1 ) {
			obstacle_x1 = 1250;
			health -= 1;
		}
		if ( obstacle_x2 + 12 >= g_bird.x && g_bird.x + g_bird.width >= obstacle_x2 ) {
			obstacle_x2 = 50;
			health -= 1;
		}
	}
	
	// Dragon
	if ( level == 3 && levelstate ==1 ) {
		if ( g_dragon.x + g_dragon.width > g_bird.x && g_bird.x + g_bird.width > g_dragon.x  &&  g_bird.y + g_bird.height + jump_y >= g_dragon.y ) {
			g_dragon.x = 1100;
			health -= 1;
		}
	}
	// Ground
	if ( level == 3 && levelstate ==1 ) {
		if ( enemy_x + 50 == g_bird.x && enemy_y + 30 > g_bird.y + jump_y ) {
			enemy_x = 10;
			health -= 1;
			printf("%d", health );
		}
	}
}
	


void showHealth () {
	int health_x = 1240;
	if ( gamestate == 1 && level == 1 && levelstate == 1 || gamestate == 1 && level == 2 && levelstate == 1 || gamestate == 1 && level == 3 && levelstate == 1) {
		for ( i=health; i>0; i--) {
			iShowImage ( health_x, 660, 40, 40, life);
			health_x -= 50;
		}
	}
}

void levelCheck() {
	if( gamestate == 1 && level == 1 && score == 10 ) {
		level = 2;
		levelstate = 0;
	}
	if( gamestate == 1 && level == 2 && score == 30 ) {
		level = 3;
		levelstate = 0;
	}
}

void jump_change() {
	if ( jump ) {
		jump_y += 5;
		if ( jump_y >= jump_limit ) {
			jump = false;
			jumpUp = false;
			jumpDown = true;
		}
	}

	if ( jumpDown ) {
		jump_y -= 5;
		if ( jump_y < 0 ) {
			jumpDown = false;
			jump_y = 0;
		}
	}
}
void healthCheck() {
	if ( health < 1 ) {
		gamestate = 6;
	}
}

void obstaclePosition1() {
	obstacle_x1 -= 50;
	if ( obstacle_x1 < 0 ) {
		obstacle_x1 = 1250;
	}
}

void obstaclePosition2() {
	obstacle_x2 += 50;
	if ( obstacle_x2 > 1280 ) {
		obstacle_x2 = 50;
	}
}

void groundEnemy() {
	iShowImage ( enemy_x, enemy_y, 50, 50, enemy1 );
	enemy_x += 10;
	if ( enemy_x >= 1280 ) {
		enemy_x = 10;
	}
}


int main()
{
	iInitialize(1280, 720, "Fun Run");
	
	// Calling function
	imgposf();
	iSetTimer ( 700, obstaclePosition1 );
	iSetTimer ( 700, obstaclePosition2 );
	if (musicOn)
		PlaySound ("angry_birds_theme.wav", NULL, SND_ASYNC | SND_LOOP); 
	//showinfo();
	
	// Initializing Picture
	menu = iLoadImage("menu.png");
	name = iLoadImage("name.jpg");
	scorepic = iLoadImage("score.png");
	level1 = iLoadImage("level1.png");
	level2 = iLoadImage("level2.png");
	level3 = iLoadImage("level3.png");
	over = iLoadImage("over.png");
	bird1 = iLoadImage("bird1.png");
	bird2 = iLoadImage("bird2.png");
	coin1 = iLoadImage("coin1.png");
	coin2 = iLoadImage("coin2.png");
	coin3 = iLoadImage("coin3.png");
	obstacle = iLoadImage( "obs.png" );
	choose = iLoadImage("choose.png");
	enemy = iLoadImage("dragon.png");
	pig1 = iLoadImage("pig1.png");
	pig2 = iLoadImage("pig2.png");
	pig3 = iLoadImage("pig3.png");
	enemy1 = iLoadImage("enemy1.png");
	enemy2 = iLoadImage("enemy2.png");
	enemy3 = iLoadImage("enemy3.png");
	life = iLoadImage("life.png");
	up_bg1 = iLoadImage("up_bg1.png");
	up_bg2 = iLoadImage("up_bg2.png");
	up_bg3 = iLoadImage("up_bg3.jpg");
	instruction = iLoadImage("instruction.png");
	about = iLoadImage("about.png");
	story = iLoadImage("story.png");
	// Structure value initialization
	g_bird.x = 60;
	g_bird.y = 135;
	g_bird.width  = 60;
	g_bird.height = 60;
	g_bird.speed  = 20;

	g_dragon.x = 1100;
	g_dragon.y = 300;
	g_dragon.width  = 150;
	g_dragon.height = 150;
	g_dragon.speed = 10;

	srand((unsigned)time(NULL));

	g_coin[0].x = 500;
	g_coin[1].x = 1000;
	g_coin[0].speed = 4;
	g_coin[1].speed = 5;
	for ( i = 0; i < 2; i++) {
		g_coin[i].y = 640;
		g_coin[i].width  = 40;
		g_coin[i].height = 50;
	}
	

	g_pig[0].x = 160;
	g_pig[1].x = 480;
	g_pig[2].x = 800;
	g_pig[3].x = 1120;

	g_pig[0].speed  = 6;
	g_pig[1].speed  = 7;
	g_pig[2].speed  = 8;
	g_pig[3].speed  = 9;

	for ( i=0; i<4; i++) {
		g_pig[i].y = 640;
		g_pig[i].width  = 50;
		g_pig[i].height = 50;
	}
	iSetTimer( 25, jump_change); 
	iStart();
	return 0;
}

