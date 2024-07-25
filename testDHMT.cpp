#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdbool.h>
#include <dos.h>

// Ham phat am thanh
void playSound(const char* soundFile) {
    PlaySound(TEXT(soundFile), NULL, SND_FILENAME | SND_ASYNC);
}

void playGameSound() {
    PlaySound(TEXT("play.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void playWinSound() {
    playSound("win.wav");
}

void playLoseSound() {
    playSound("lose.wav");
}

// Lua chon do kho
char showModeSelectionMenu() {
    char mode;
    clearviewport();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(50, 100, "Select Mode:");
    outtextxy(50, 150, "E - Easy");
    outtextxy(50, 200, "N - Normal");
    outtextxy(50, 250, "H - Hard");
    while (1) {
        if (kbhit()) {
            mode = getch();
            if (mode == 'E' || mode == 'e' || mode == 'N' || mode == 'n' || mode == 'H' || mode == 'h') {
                break;
            }
        }
    }
    return mode;
}

int main() {
    // Khoi tao cua so do hoa

    int windowWidth = 600;
    int windowHeight = 600;
    initwindow(windowWidth, windowHeight);

    int playAgain = 0;
    char key;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(windowWidth / 8 - 40, windowHeight / 3, "Press 'S' to play");
    while (1) {
        if (kbhit()) {
            key = getch();
            if (key == 's' || key == 'S') {

                playAgain = 1;
                break;
            }
        }
    }

    do {
        //Hien thi menu chon do kho
        char mode = showModeSelectionMenu();
        int ballSpeed, basketSpeed, initialBasketWidth;
        int minBasketWidth = 0;
        int isNormalMode = 0;
        int isHardMode = 0;
        switch (mode) {
            // Thiet lap cai dat tuy theo do kho
            case 'E':
            case 'e':
                ballSpeed = 7;
                basketSpeed = 30;
                initialBasketWidth = 90;
                break;
            case 'N':
            case 'n':
                ballSpeed = 9;
                basketSpeed = 20;
                initialBasketWidth = 75;
                minBasketWidth = 30;
                isNormalMode = 1;
                break;
            case 'H':
            case 'h':
                ballSpeed = 11;
                basketSpeed = 25;
                initialBasketWidth = 70;
                minBasketWidth = 40;
                isHardMode = 1;
                break;
            default:
                printf("Invalid mode selected. Defaulting to Normal mode.\n");
                ballSpeed = 6;
                basketSpeed = 20;
                initialBasketWidth = 50;
                break;
        }

    // Tinh toan kich thuoc cua 2 phan cua so
        int sideWidth = windowWidth * 0.2;
        int middleWidth = windowWidth * 0.6;
	// Ve khung mau
        setviewport(0, 0, sideWidth, windowHeight, 1);
        setcolor(LIGHTGREEN);
        rectangle(0, 0, sideWidth, windowHeight);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(sideWidth / 2, windowHeight / 2, LIGHTGREEN);
        setviewport(windowWidth - sideWidth, 0, windowWidth, windowHeight, 1);
        setcolor(LIGHTGREEN);
        rectangle(0, 0, sideWidth, windowHeight);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(sideWidth / 2, windowHeight / 2, LIGHTGREEN);

        // Ve phan choi
        setviewport(sideWidth, 0, sideWidth + middleWidth, windowHeight, 1);

        // Thiet lap vi tri ban dau cua ro
        int basketX = middleWidth / 2;
        int basketY = windowHeight - 50;
        int basketWidth = initialBasketWidth;
        int basketHeight = 10;
        int ballX = rand() % middleWidth;
        int ballY = 0;
        int score = 0;
        int lives = 2;
        char scoreStr[20];
        int isPaused = 0;

        // Bien de theo doi huong cua qua bong
        int isBallGoingRight = 1;

        // Bien va logic cho qua bong trang
        int whiteBallX = rand() % middleWidth;
        int whiteBallY = 0;
        int whiteBallSpeed = 4;
        int isWhiteBallGoingRight = 1;

        time_t startTime = time(NULL);
        time_t currentTime;

        // Bat dau phat am thanh nen
        playGameSound();

        // Vong lap chinh cua tro choi
        while (lives > 0 && basketWidth > 0) {
            clearviewport();

            // Ve khung choi va diem
            setcolor(WHITE);
            rectangle(0, 0, middleWidth, windowHeight);

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            sprintf(scoreStr, "Score: %d", score);
            strcat(scoreStr, "   Lives: ");
            char livesStr[2];
            itoa(lives, livesStr, 10);
            strcat(scoreStr, livesStr);
            outtextxy(10, 10, scoreStr);

            // Hien thi thoi gian
            currentTime = time(NULL);
            int elapsedTime = difftime(currentTime, startTime);
            char timeStr[20];
            sprintf(timeStr, "Time: %d sec", elapsedTime);
            outtextxy(windowWidth - sideWidth + 10, 10, timeStr);
            
            //Ve cai ro
	        setcolor(GREEN);
	        rectangle(basketX - basketWidth / 2, basketY, basketX + basketWidth / 2, basketY + basketHeight);
	        setfillstyle(SOLID_FILL, WHITE);
	        floodfill(basketX, basketY + basketHeight / 2, GREEN);
	
	        // Ve qua bong do
	        setcolor(RED);
	        circle(ballX, ballY, 10);
	        setfillstyle(SOLID_FILL, RED);
	        floodfill(ballX, ballY, RED);

        // Logic cho qua bong trang
        if (isHardMode) {
            setcolor(WHITE);
            circle(whiteBallX, whiteBallY, 10);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(whiteBallX, whiteBallY, WHITE);

            if (isWhiteBallGoingRight) {
				if (whiteBallX >= middleWidth) {
                    isWhiteBallGoingRight = 0;
                }
                whiteBallX += whiteBallSpeed;
            } else {
                if (whiteBallX <= 0) {
                    isWhiteBallGoingRight = 1;
                }
                whiteBallX -= whiteBallSpeed;
            }
            whiteBallY += whiteBallSpeed;

            if (whiteBallY >= windowHeight) {
                int hitBasket = (whiteBallX >= basketX - basketWidth / 2 && whiteBallX <= basketX + basketWidth / 2);
                if (!hitBasket) {
                    whiteBallX = rand() % middleWidth;
                    whiteBallY = 0;
                }
            }

            if (whiteBallY >= basketY && whiteBallX >= basketX - basketWidth / 2 && whiteBallX <= basketX + basketWidth / 2) {
                lives = 0;
                break;
            }
        }

        // Logic cho qua bong do 
        if (ballY >= windowHeight) {
            int hitBasket = (ballX >= basketX - basketWidth / 2 && ballX <= basketX + basketWidth / 2);
            if (!hitBasket) {
                ballX = rand() % middleWidth;
                ballY = 0;
                ballSpeed = 5;
                lives--;
            }
        }

        if (ballY >= basketY && ballX >= basketX - basketWidth / 2 && ballX <= basketX + basketWidth / 2) {
            score++;
            ballX = rand() % middleWidth;
            ballY = 0;
            ballSpeed += 1;
            basketWidth -= 6;
            if (isNormalMode && basketWidth < minBasketWidth) {
                basketWidth = minBasketWidth;
            }
            if (isHardMode && basketWidth < minBasketWidth) {
                basketWidth = minBasketWidth;
            }
            basketSpeed += 2;
        } else if (isHardMode && ballY >= basketY && ballX >= basketX - basketWidth / 2 && ballX <= basketX + basketWidth / 2) {
            lives = 0;
            break;
        }

    // Logic di chuyen cua bong do
        if (isNormalMode) {
            if (isBallGoingRight) {
                if (ballX >= middleWidth) {
                    isBallGoingRight = 0;
                }
                ballX += ballSpeed;
            } else {
                if (ballX <= 0) {
                    isBallGoingRight = 1;
                }
                ballX -= ballSpeed;
            }
        }

        if (isHardMode) {
            if (isBallGoingRight) {
                if (ballX >= middleWidth) {
                    isBallGoingRight = 0;
                }
                ballX += ballSpeed;
            } else {
                if (ballX <= 0) {
                    isBallGoingRight = 1;
                }
                ballX -= ballSpeed;
            }
        }

        ballY += ballSpeed;

        // Logic cho phím di chuyen va dung tro choi
        if (!isPaused) {
            if (kbhit()) {
                key = getch();
		if ((key == 75 || key == 'a' || key == 'A') && basketX - basketWidth / 2 > 0) {
                    basketX -= basketSpeed;
                } else if ((key == 77 || key == 'd' || key == 'D') && basketX + basketWidth / 2 < middleWidth) {
                    basketX += basketSpeed;
                } else if (key == 'p' || key == 'P') {
                    isPaused = 1;
                    outtextxy(windowWidth / 2 - 40, windowHeight / 2, "Game Paused");
                }
            }
        } else {
            if (kbhit()) {
                key = getch();
                if (key == 'p' || key == 'P') {
                    isPaused = 0;
                    clearviewport();
                }
            }
        }

        delay(50);
	    }
	
	    // Dung am thanh va hien thi ket qua
	    PlaySound(NULL, NULL, SND_FILENAME);
	
	    clearviewport();
	    if (basketWidth <= 0) {
	        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	        outtextxy(windowWidth / 8 - 40, windowHeight / 3, "You Win!");
	        playWinSound();
	    } else {
	        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	        outtextxy(windowWidth / 8 - 40, windowHeight / 3, "Game Over");
	        playLoseSound();
	    }
	    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	    outtextxy(windowWidth / 8 - 40, windowHeight / 2, "Press 'S' to play again or 'Q' to quit");
	
	    // Xu ly phim bam cua nguoi choi
	    while (1) {
	        if (kbhit()) {
	            key = getch();
	            if (key == 's' || key == 'S') {
	                playAgain = 1;
	                break;
	            } else if (key == 'q' || key == 'Q') {
	                playAgain = 0;
	                break;
	            }
	        }
	    }
	
	} while (playAgain);
	
	//dong cua so va ket thuc chuong trinh
	closegraph();
	return 0;
}
