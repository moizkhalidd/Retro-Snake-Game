//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include <fstream>
#include<vector>
#include <time.h>
#include <cstdlib>
#include<algorithm>
#include <iomanip>
#include <cstdio>
//#include<cstdlib>
#include<ctime>
#include<string>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}
  

/*
 * Main Canvas drawing function.
 * */
double startx=320,starty=400;
int row , col;
float score;
int t ,t1,t2,t3,t4, t5, obstX , obstY, foodR  , foodC, foodR1, foodC1, foodR2, foodC2, foodR3, foodC3, foodR4, foodC4, foodR5 , foodC5;
bool eaten ,eaten1 , eaten2, eaten3 , eaten4 ,eaten5, firstTime = 1, gameOver;
string snake[65][65];  
int sqtime[65][65];
string direction;
float highscore =0 ;
int length;
bool diagP= 0, diagS = 0, diagP1= 0, diagS1 = 0, diagP2= 0, diagS2 = 0, diagP3= 0, diagS3 = 0, diagP4= 0, diagS4 = 0, diagP5 = 0, diagS5 = 0;
bool VFF = 0; //valid food found
int RefreshR;
float xaxis ;
bool Time1 = 1, onSnake ,resume = 0, Difficulty =0, high = 0, history =0;
int obstacleX , obstacleY, obstacleX1 =-1, obstacleY1 =-1,obstacleX2=-1 , obstacleY2=-1;
int tObstacle ,score2, highscore2;
std::ofstream scorefile;
std::ofstream highscorefile;
void Display(){
glClearColor(0.5,0.5,0.5,1);
   if(!resume)
   {
     glClear(GL_COLOR_BUFFER_BIT);
     DrawString(280, 380, "Press N to Start New Game", colors[DARK_SLATE_GRAY]);                              //main menu
     DrawString(280, 350, "Press S to Resume", colors[DARK_SLATE_GRAY]); 
     DrawString(280, 320, "Press D for difficulty information", colors[DARK_SLATE_GRAY]);
      DrawString(280, 290, "Press H for Highscores", colors[DARK_SLATE_GRAY]);
      DrawString(280, 260, "Press G for Game History", colors[DARK_SLATE_GRAY]);
      DrawString(280, 230, "Press ESC to Quit", colors[BLACK]);
     if(Difficulty)
     {
      glClear(GL_COLOR_BUFFER_BIT);
      DrawString(230, 350, "score 0-100: easy", colors[DARK_SLATE_GRAY]);                           //difficulty criteria
      DrawString(230, 320, "score 100-200: medium", colors[DARK_SLATE_GRAY]);
      DrawString(230, 290, "score 200+: hard", colors[DARK_SLATE_GRAY]);
      DrawString(230, 260, "Press B to go back", colors[BLACK]); 
     }
     if(high)
     {
        
        glClear(GL_COLOR_BUFFER_BIT);
        DrawString(230,500, "Press B to go back", colors[BLACK]);
        ifstream myfile("highscores.txt");
		if(myfile.is_open())
	      {
		int i = 0;
		string line;
               while (getline(myfile, line))                                                            //display highscores
	       {
	        DrawString(280, 320 + i, line, colors[DARK_SLATE_GRAY]);
	        i = i+20;
	       } 
	       myfile.close();
	      i=0;
	      }
	      
     
     }
     if(history)
     {
        
        
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        DrawString(230,500, "Press B to go back", colors[BLACK]);
        ifstream myfile("scores.txt");
		if(myfile.is_open())
	      {
		int i = 0;                                                                    //display scores
		string line;
               while (getline(myfile, line))
	       {
	        DrawString(280, 320 + i, line, colors[DARK_SLATE_GRAY]);
	        i = i+20;
	       } 
	       myfile.close();
	      i=0;
	      }
	     
     }
     
     
     
     
     
     
     
     glutSwapBuffers(); 
   }
 if(resume )  
 {  
	   srand(time(NULL));
           
	  if(firstTime){                                                         //main code
	      for(int i = 0; i<65 ; i++)
	      {
	      for(int j= 0; j<65 ; j++)
	      {
	       sqtime[i][j] = 0;
	      }
	     } 
	     RefreshR = 100;
	     startx=320;
	     starty=400;
	     row =32; 
	     col = 32;
	     score = 0;
	     t = RefreshR ;  
	     t1 = RefreshR ;  
	     t2 = RefreshR ;  
	     t3 = RefreshR ;  
	     t4 = RefreshR ; 
	     t5 = 400; 
	     obstX = 12;  
	     obstY = 14; 
	     foodR =0;  
	     foodC = 0;
	     foodR1 =0;  
	     foodC1 = 0;
	     foodR2 =0;  
	     foodC2 = 0;
	     foodR3 =0;  
	     foodC3 = 0;
	     foodR4 =0;  
	     foodC4 = 0;
	     foodR5 =0;  
	     foodC5 = 0;
	     eaten = 0; 
	     eaten1 = 0; 
	     eaten2 = 0; 
	     eaten3 = 0; 
	     eaten4 = 0;
	     eaten5 = 0; 
	     firstTime = 1;  
	     gameOver = 0;
	     direction = "up";
	     length = 2;
	     diagP= 0;
	     diagS = 0; 
	     diagP1= 0; 
	     diagS1 = 0; 
	     diagP2= 0; 
	     diagS2 = 0; 
	     diagP3= 0; 
	     diagS3 = 0;
	     diagP4= 0; 
	     diagS4 = 0;
	     diagP5= 0; 
	     diagS5 = 0;
	     tObstacle = 200;
	     onSnake = 0;
	     obstacleX1 =9999;
	     obstacleY1 =9999;
	     obstacleX2=9999;  
	     obstacleY2=9999;
	     
	     
	     sqtime[row -1][col] = 2;
	     sqtime[row -2][col] = 1;
	     
	     firstTime = 0;
	    }
	    
	     if(highscore > 0)
	     xaxis = (score/highscore) * 140;

            score2 =score;
	    // set the background color using function glClearColotgr.
	    // to change the background play with the red, green and blue values below.
	    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	      glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
		    0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
	    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
	    DrawString(30, 630, "Snake", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
	    DrawString(500, 630, "Score = " + to_string(score2) , colors[MISTY_ROSE]); // this will print given string at x=50 , y=570
	    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	    DrawLine( 60 , 633 ,  200 , 633 , 600 , colors[MISTY_ROSE] ); 
	    
	    if(Time1)
	    {
	      if(score == 0)
	      {
	      }
	      else   
	      if(score >= highscore)
	      {
	 	 DrawLine( 60 , 633 , 200 , 633 , 600 , colors[LIME_GREEN] );                             //score bar colour increase
		 Time1 = 0;     
	      }   
	    }
	    else
	    if(score >= highscore)
	    {
	      DrawLine( 60 , 633 , 200 , 633 , 600 , colors[LIME_GREEN] );
	    }
	    else
	    if(highscore != 0)
	    {
	      DrawLine( 60 , 633 , 60 + xaxis  , 633 , 600 , colors[LIME_GREEN] );  
	    } 

	    srand(time(NULL));
	    
	    
	 if(!gameOver)
	 {   
	    VFF  = 0;
	    if(t5 == 400)
	    {                                                               //power food
	      if(eaten5 == 0)
	     {     
	      t5 = 0;
	      eaten5 = 1;
	      foodR5 = -1;
	      foodC5 = -1;
	     }
	     else
	     {
	       t5 = 0;
	       VFF  = 0;
	      while(!VFF)
	      {
	      diagP5 =0;
	      diagS5 = 0;
	      
	      foodR5 = rand() % 65;
	      foodC5 = rand() % 65;
	      if(foodR5 == foodC5)
	      { 
		diagP5 = 1;
	      }
	      if(foodR5 + foodC5 == 64)
	      {
		diagS5 = 1;
	      }
	      if(foodR5 == foodR || foodR5 == foodR1 || foodR5 == foodR2|| foodR5 == foodR3 || foodR5 == foodR4 || foodC5 == foodC || foodC5 == foodC1 || foodC5 == foodC2 || foodC5 == foodC3|| foodC5 == foodC4 || diagP + diagP1 + diagP2 + diagP3 +diagP4 + diagP5 > 1 || diagS + diagS1 + diagS2 + diagS3 + diagS4 + diagS5 > 1)
	       {
		VFF = 0;
	       }
	       else
	       {
		VFF = 1;
		
	       }
	      
	      }
	       eaten5 = 0;
	      } 
	    }
	      
	      VFF  = 0;
	    if(t == RefreshR  || eaten)
	    {
	      t = 0;                                                                          //food one
	      
	       VFF  = 0;
	      while(!VFF)
	      {
	      diagP =0;
	      diagS = 0;
	      
	      foodR = rand() % 65;
	      foodC = rand() % 65;
	      if(foodR == foodC)
	      { 
		diagP = 1;
	      }
	      if(foodR + foodC == 64)
	      {
		diagS = 1;
	      }
	      if(foodR == foodR1 || foodR == foodR2 || foodR == foodR3|| foodR == foodR4 || foodR == foodR5|| foodC == foodC1 || foodC == foodC2 || foodC == foodC3|| foodC == foodC4 || foodC == foodC5|| diagP + diagP1 + diagP2 + diagP3 +diagP4 + diagP5 > 1 || diagS + diagS1 + diagS2 + diagS3 + diagS4  + diagS5> 1)
	       {
		VFF = 0;
	       }
	       else
	       {
		VFF = 1;
	       }
	      
	      }
	       eaten = 0;   
	    }
	      VFF  = 0;
	      
	      if(t1 == RefreshR  || eaten1)
	    {
	      t1 = 0;                                                                            //food two
	     
	      while(!VFF)
	      {
	       diagP1 =0;
	      diagS1 = 0;
	 
	       foodR1 = rand() % 65;
	       foodC1 = rand() % 65;
	       if(foodR1 == foodC1)
	      { 
		diagP1 = 1;
	      }
	      if(foodR1 + foodC1 == 64)
	      {
		diagS1 = 1;
	      }
	       if(foodR1 == foodR || foodR1 == foodR2 || foodR1 == foodR3|| foodR1 == foodR4 ||foodR1 == foodR5 || foodC1 == foodC || foodC1 == foodC2 || foodC1 == foodC3|| foodC1 == foodC4 ||foodC1 == foodC5 || diagP + diagP1 + diagP2 + diagP3 +diagP4 + diagP5> 1 || diagS + diagS1 + diagS2 + diagS3 + diagS4 + diagS5> 1)
	       {
		VFF = 0;
	       }
	       else
	       {
		VFF = 1;
	       }
	      }
	      
	       eaten1 = 0;
	    }
	       VFF  = 0;
		  
	      if(t2 == RefreshR  || eaten2)
	    { 
	     t2 = 0;                                                                                  //food three
	    
	      while(!VFF)
	      {
		diagP2 =0;
	     diagS2 = 0;
	      
	       foodR2 = rand() % 65;
	       foodC2 = rand() % 65;
	       if(foodR2 == foodC2)
	      { 
		diagP2 = 1;
	      }
	      if(foodR2 + foodC2 == 64)
	      {
		diagS2 = 1;
	      }
	       if(foodR2 == foodR || foodR2 == foodR1 || foodR2 == foodR3|| foodR2 == foodR4 || foodR2 == foodR5 ||foodC2 == foodC || foodC2 == foodC1 || foodC2 == foodC3|| foodC2 == foodC4 ||foodC2 == foodC5 || diagP + diagP1 + diagP2 + diagP3 +diagP4 + diagP5 > 1 || diagS + diagS1 + diagS2 + diagS3 + diagS4 +diagS5 > 1)
	       {
		VFF = 0;
	       }
	       else
	       {
		VFF = 1;
	       }
	      }
	      
	      eaten2 = 0;
	      
	     }
	      if(t3 == RefreshR  || eaten3)
	    {  
	       t3 = 0;                                                                                //food four
	    
	       VFF  = 0;
		while(!VFF)
	      {
		  diagP3 =0;
	       diagS3 = 0;
	    
	       foodR3 = rand() % 65;
	       foodC3 = rand() % 65;
	       if(foodR3 == foodC3)
	      { 
		diagP3 = 1;
	      }
	      if(foodR3 + foodC3 == 64)
	      {
		diagS3 = 1;
	      }
	       if(foodR3 == foodR || foodR3 == foodR1 || foodR3 == foodR2|| foodR3 == foodR4 ||foodR3 == foodR5 || foodC3 == foodC || foodC3 == foodC1 || foodC3 == foodC2|| foodC3 == foodC4 || foodC3 == foodC5 ||diagP + diagP1 + diagP2 + diagP3 +diagP4 + diagP5 > 1 || diagS + diagS1 + diagS2 + diagS3 + diagS4 + diagS5> 1)
	       {
		VFF = 0;
	       }
	       else
	       {
		VFF = 1;
	       }
	      }
	      
	      eaten3 = 0;
	      }
	      
	       if(t4 == RefreshR  || eaten4)
	    { 
		t4 = 0;                                                                     //food  five
	       
	       VFF  = 0;
		while(!VFF)
	      {
	       diagP4 =0;
	       diagS4 = 0;
	       
	       foodR4 = rand() % 65;
	       foodC4 = rand() % 65;
	       if(foodR4 == foodC4)
	      { 
		diagP4 = 1;
	      }
	      if(foodR4 + foodC4 == 64)
	      {
		diagS4 = 1;
	      }
	       if(foodR4 == foodR || foodR4 == foodR1 || foodR4 == foodR2 || foodR4 == foodR3 || foodR4 == foodR5 || foodC4 == foodC || foodC4 == foodC1 || foodC4 == foodC2 || foodC4 == foodC3 ||foodC4 == foodC5 || diagP + diagP1 + diagP2 + diagP3 +diagP4 + diagP5 > 1 || diagS + diagS1 + diagS2 + diagS3 + diagS4 + diagS5> 1)
	       {
		VFF = 0;
	       }
	       else
	       {
		VFF = 1;
	       }
	      }
		    
	     eaten4 = 0;
	     }
	 
	    t += 1;                                                                  //time increase for each food
	    t1 += 1;
	    t2 += 1;
	    t3 += 1;
	    t4 += 1;
	    t5 += 1;
	    
	     for(int i = 0; i<65 ; i++)
	    {
	      for(int j= 0; j<65 ; j++)
	      {
		snake[i][j]=" ";
	      }
	    } 
	    snake[row][col] = "snake";
	    snake[foodR][foodC] = "food";

	    for(int i = 0; i<65 ;i++)
	    {
	     for(int j=0; j<65; j++)
	     {
	      if(snake[i][j] == "snake")
	      {
	      
	       DrawCircle(j*10 + 4.5 , i*10 + 5 , 5 , colors[LIGHT_SLATE_GRAY]); // snake head
	      
	     }
	     if(sqtime[i][j] != 0)
	     {
		DrawSquare((j)*10 , (i)*10 , 10,colors[GRAY]);              //snake body
	     }
	    }
	   }
	   
	     //if snake hits itself or obstacle
	    if(sqtime[row][col] != 0 || (row == obstacleY && col >= obstacleX && col <= obstacleX +5) || (col == obstacleX && row >= obstacleY && row <= obstacleY + 10) || 
	    (row == obstacleY2 && col >= obstacleX2 && col <= obstacleX2 +5) || (col == obstacleX2+5  && row >= obstacleY2-5 && row <= obstacleY2) ||
	      (col == obstacleX2  && row >= obstacleY2-10 && row <= obstacleY2-5) || (row == obstacleY2-10 && col >= obstacleX2 && col <= obstacleX2 +5) || (row == obstacleY2-5 && col >= obstacleX2 && col <= obstacleX2 +5) || (row == obstacleY1 && col >= obstacleX1 && col <= obstacleX1 +5) || (col == obstacleX1 && row >= obstacleY1 && row <= obstacleY1 + 10) || (col == obstacleX1+ 5 && row >= obstacleY1 && row <= obstacleY1 + 10))
	    {
	    
	      DrawString(290, 380, "Game Over!", colors[RED]); 
	      gameOver =1;
	      DrawString(280, 300, "Press P for Menu", colors[DARK_SLATE_GRAY]);
	      DrawString(280, 350, "Press R to restart", colors[DARK_SLATE_GRAY]); // game over screen
	      DrawString(280, 230, "Press ESC to Quit", colors[WHITE]);
	      DrawString(285, 325, "Your score is " + to_string(score2), colors[DARK_SLATE_GRAY]);
	      if(score > highscore)
	      {
		 highscore = score;
		 highscore2 = highscore;
	       DrawString(200, 270, "You have broken all previous records and now the highest score is " + to_string(highscore2), colors[DARK_SLATE_GRAY]); 
	       
	       highscorefile.open("highscores.txt" , std::ios::app);
		if(highscorefile.is_open())
	      {
		
		highscorefile <<highscore<<endl;                                       //file making for highscores
		highscorefile.close();
	      }
	      else
	      {
	       // Handle file opening error
		std::cerr << "Error opening file!" << std::endl;
	      } 
	      
	      }  
	      
		scorefile.open("scores.txt" , std::ios::app);
	      if(scorefile.is_open())
	      {
		
		scorefile <<score<<endl;                                                //file making for game history
		scorefile.close();
	      }
	      else
	      {
	       // Handle file opening error
		std::cerr << "Error opening file!" << std::endl;
	      }
	       
	    } 
	  
	    if(((row == foodR) && (col == foodC)) || ((row == foodR1) && (col == foodC1)) || ((row == foodR2) && (col == foodC2)) || ((row == foodR3) && (col == foodC3)) || ((row == foodR4) && (col == foodC4))|| ((row == foodR5) && (col == foodC5)))
	    {
	      for(int i = 0; i<65 ; i++)
	      {
		for(int j= 0; j<65 ; j++)                                                           //using array to increase snake's length
		{
		  if(sqtime[i][j] !=0)
		  sqtime[i][j] = sqtime[i][j] + 1;
		}
	      }

	     if(row == foodR && col == foodC)
	     {
	      eaten = 1;
	      score = score + 5;
	      length = length + 1;
	     }
	     else
	     if(row == foodR1 && col == foodC1)
	     {
	      eaten1 = 1;
	      score = score + 5;
	      length = length + 1;
	     }
	     else
	     if(row == foodR2 && col == foodC2)
	     {
	       eaten2 = 1;
	       score = score + 5;
	       length = length + 1;
	     }
	     else
	     if(row == foodR3 && col == foodC3)
	     {
	      eaten3 = 1;
	      score = score + 5;
	      length = length + 1;
	     } 
	     else
	     if(row == foodR4 && col == foodC4)
	     {
	      eaten4 = 1;
	      score = score + 5;
	      length = length + 1;
	     }    
	     else
	     if(row == foodR5 && col == foodC5 && eaten5 == 0)
	     {
	      eaten5 = 1;
	      score = score + 20;
	      length = length + 1;
	     }    
	    }
																			
	   DrawTriangle( (foodC)*10, (foodR)*10 , (foodC+0.5)*10, (foodR+1)*10 , (foodC+1) * 10 , (foodR)*10, colors[DARK_OLIVE_GREEN] ); 
	   DrawTriangle( (foodC1)*10, (foodR1)*10 , (foodC1+0.5)*10, (foodR1+1)*10 , (foodC1+1) * 10 , (foodR1)*10, colors[DARK_OLIVE_GREEN] );
	   DrawTriangle( (foodC2)*10, (foodR2)*10 , (foodC2+0.5)*10, (foodR2+1)*10 , (foodC2+1) * 10 , (foodR2)*10, colors[DARK_OLIVE_GREEN] );        //making food
	   DrawTriangle( (foodC3)*10, (foodR3)*10 , (foodC3+0.5)*10, (foodR3+1)*10 , (foodC3+1) * 10 , (foodR3)*10, colors[DARK_OLIVE_GREEN] );
	   DrawTriangle( (foodC4)*10, (foodR4)*10 , (foodC4+0.5)*10, (foodR4+1)*10 , (foodC4+1) * 10 , (foodR4)*10, colors[DARK_OLIVE_GREEN] ); 
	   if(eaten5 == 0)
	   DrawTriangle( (foodC5)*10, (foodR5)*10 , (foodC5+0.5)*10, (foodR5+1)*10 , (foodC5+1) * 10 , (foodR5)*10, colors[STEEL_BLUE] ); 

	     if(tObstacle == 200)
	     {
		    tObstacle = 0;
		  
		    obstacleX = rand() % 65;
		    obstacleY =rand() % 65;
		    onSnake = 0;
		    //checking if obstacle is placed on any food or snake
		    while((foodR >= obstacleY && foodR <= obstacleY+10 && foodC >= obstacleX && foodC <= obstacleX+5) || 
		      (foodR1 >= obstacleY && foodR1 <= obstacleY+10 && foodC1 >= obstacleX && foodC1 <= obstacleX+5)||                                           //obstacle1
			  (foodR2 >= obstacleY && foodR2 <= obstacleY+10 && foodC2 >= obstacleX && foodC2 <= obstacleX+5) || 
			  (foodR3 >= obstacleY && foodR3 <= obstacleY+10 && foodC3 >= obstacleX && foodC3 <= obstacleX+5) ||
			  (foodR4 >= obstacleY && foodR4 <= obstacleY+10 && foodC4 >= obstacleX && foodC4 <= obstacleX+5)||
			  (foodR5 >= obstacleY && foodR5 <= obstacleY+10 && foodC5 >= obstacleX && foodC5 <= obstacleX+5)||
			  (row >= obstacleY && row <= obstacleY+10 && col >= obstacleX && col <= obstacleX+5)||
			  (onSnake))
		     {
			      obstacleX =rand() % 65;
			      obstacleY =rand() % 65;
			      
			      //checking if obstacle placed on any snake square
			    for(int i =0 ; i<65 ; i++)
			    {
			     for(int j=0 ; j<65; j++)
			     {
			      if(sqtime[i][j] != 0 && j >= obstacleX && j <= obstacleX+5 && i >= obstacleY && i <= obstacleY+10)
			      {
			       onSnake = 1;
			      }	     
			     }
			    }
			    
		      }
		      
		      if(score>=100)
		      {
		              obstacleX2 =rand() % 65;
			      obstacleY2 =rand() % 65;
			      onSnake = 0;
		      while((foodR <= obstacleY2-50 && foodR >= obstacleY2 && foodC >= obstacleX2 && foodC <= obstacleX2+5) || 
		      (foodR1 <= obstacleY2-50 && foodR1 >= obstacleY2 && foodC1 >= obstacleX2 && foodC1 <= obstacleX2+5)||                                           //obstacle2
			  (foodR2 <= obstacleY2 -50 && foodR2 >= obstacleY2 && foodC2 >= obstacleX2 && foodC2 <= obstacleX2+5) || 
			  (foodR3 <= obstacleY2 -50 && foodR3 >= obstacleY2 && foodC3 >= obstacleX2 && foodC3 <= obstacleX2+5) ||
			  (foodR4 <= obstacleY2-50 && foodR4 >= obstacleY2 && foodC4 >= obstacleX2 && foodC4 <= obstacleX2+5)||
			  (foodR5 <= obstacleY2-50 && foodR5 >= obstacleY2 && foodC5 >= obstacleX2 && foodC5 <= obstacleX2+5)||
			  (row <= obstacleY2-50 && row >= obstacleY2 && col >= obstacleX2 && col <= obstacleX2+5)||
			  (onSnake))
		     {
			      obstacleX2 =rand() % 65;
			      obstacleY2 =rand() % 65;
			      cout<<"okoko";
			      //checking if obstacle placed on any snake square
			    for(int i =0 ; i<65 ; i++)
			    {
			     for(int j=0 ; j<65; j++)
			     {
			      if(sqtime[i][j] != 0 && j >= obstacleX2 && j <= obstacleX2+5 && i <= obstacleY2-50 && i >= obstacleY2)
			      {
			       onSnake = 1;
			      }	     
			     }
			    }	   
		      }
		      
		      }
		      
		      
		      
		      
		      
		      
		      if(score >= 50)
		      {
		              obstacleX1 =rand() % 65;
			      obstacleY1 =rand() % 65;
			      onSnake = 0;
		      while((foodR <= obstacleY1 && foodR >= obstacleY1 + 10 && foodC >= obstacleX1 && foodC <= obstacleX1+5) || 
		      (foodR1 <= obstacleY1 && foodR1 >= obstacleY1+10 && foodC1 >= obstacleX1 && foodC1 <= obstacleX1+5)||                                           //obstacle3
			  (foodR2 <= obstacleY1 && foodR2 >= obstacleY1 +10 && foodC2 >= obstacleX1 && foodC2 <= obstacleX1+5) || 
			  (foodR3 <= obstacleY1 && foodR3 >= obstacleY1 +10 && foodC3 >= obstacleX1 && foodC3 <= obstacleX1+5) ||
			  (foodR4 <= obstacleY1 && foodR4 >= obstacleY1 +10 && foodC4 >= obstacleX1 && foodC4 <= obstacleX1+5)||
			  (foodR5 <= obstacleY1 && foodR5 >= obstacleY1 +10 && foodC5 >= obstacleX1 && foodC5 <= obstacleX1+5)||
			  (row <= obstacleY1 && row >= obstacleY1 +10 && col >= obstacleX1 && col <= obstacleX1+5)||
			  (onSnake))
		     {
			      obstacleX1 =rand() % 65;
			      obstacleY1 =rand() % 65;
			      cout<<"okoko";
			      //checking if obstacle placed on any snake square
			    for(int i =0 ; i<65 ; i++)
			    {
			     for(int j=0 ; j<65; j++)
			     {
			      if(sqtime[i][j] != 0 && j >= obstacleX1 && j <= obstacleX1+5 && i <= obstacleY1-50 && i >= obstacleY1+5)
			      {
			       onSnake = 1;
			      }	     
			     }
			    }  		    
		      }
		     }  
	   
	    }
	    
	    tObstacle += 1;
		    DrawLine( obstacleX *10 , obstacleY *10 ,  (obstacleX + 5) *10 , obstacleY *10  , 600 , colors[SADDLE_BROWN] );
		    DrawLine( obstacleX*10 , obstacleY*10 ,  obstacleX *10, (obstacleY +  10) *10 , 600 , colors[SADDLE_BROWN] );                            //making obstacles
		    
		    if(score >=50)
		    {
		    DrawLine( obstacleX1 *10 , obstacleY1 *10 ,  (obstacleX1 + 5) *10 , obstacleY1 *10  ,600 , colors[SADDLE_BROWN] );
		    DrawLine( obstacleX1*10 , obstacleY1*10 ,  obstacleX1 *10, (obstacleY1 +  10) *10 , 600 , colors[SADDLE_BROWN] );
		    DrawLine( (obstacleX1 +5)*10 , obstacleY1*10 ,  (obstacleX1+5) *10, (obstacleY1 +  10) *10 , 600 , colors[SADDLE_BROWN] );
		    }
		    if(score >=100)
		    {
		    DrawLine( obstacleX2 *10 , obstacleY2 *10 ,  (obstacleX2 + 5) *10 , obstacleY2 *10  , 600 , colors[SADDLE_BROWN] );
		    DrawLine( (obstacleX2+5)*10 , obstacleY2*10 ,  (obstacleX2+5) *10, (obstacleY2 -  5) *10 , 600 , colors[SADDLE_BROWN] );
		    DrawLine( obstacleX2 *10 , (obstacleY2 *10 -50),  (obstacleX2 + 5) *10 , (obstacleY2 *10 - 50 ) , 600 , colors[SADDLE_BROWN] );
		    DrawLine( (obstacleX2)*10 , (obstacleY2*10 -50) ,  (obstacleX2) *10, (obstacleY2 - 10) *10 , 600 , colors[SADDLE_BROWN] );
		    DrawLine( obstacleX2 *10 , (obstacleY2 -10) *10 ,  (obstacleX2 + 5) *10 , (obstacleY2-10) *10  , 600 , colors[SADDLE_BROWN] );
		    }

	      glutSwapBuffers(); // do not modify this line..
	   }  
   }	   
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
   
   int Prow= row , Pcol = col; 
   bool moved = 0;  
       
    if (key == GLUT_KEY_LEFT && direction != "right"  /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
     
     moved = 1;
     direction = "left";
     col--;
     if(col < 0)
     col = 64;
											// what to do when left key is pressed..  
    } else if (key == GLUT_KEY_RIGHT  && direction != "left" /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
    
     moved = 1;
     direction = "right";
     col++;
     if(col > 64)
     col = 0;
		
    } else if (key == GLUT_KEY_UP && direction != "down" ) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
        
        moved = 1;    
        direction = "up";
        row++;
        if(row > 64)
        row = 0;
    }
    else if (key == GLUT_KEY_DOWN && direction != "up" )   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
     
     moved = 1;
     direction = "down";
     row--;
     if(row < 0)
     row = 64;
    }
    
    if(moved)
      {
      for(int i = 0; i<65 ; i++)
      {
        for(int j= 0; j<65 ; j++)
        {
          if(sqtime[i][j] !=0)
          sqtime[i][j] = sqtime[i][j] - 1;
        }
      }
      sqtime[Prow][Pcol] = length;
     }
     
    
   

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC && (gameOver == 1 || resume == 0)&& (history ==0) && (high == 0) && (Difficulty ==0)/* Escape key ASCII*/) {
        
        remove("highscores.txt");
        remove("scores.txt");
        exit(1); // exit the program when escape key is pressed.
    }
    if ((key == 'R' || key=='r') && gameOver == 1/* Escape key ASCII*/) {
    
       firstTime = 1;
       gameOver = 0;
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    if ((key == 'S' || key=='s') && (history ==0) && (high == 0) && (Difficulty ==0)/* Escape key ASCII*/) {
    
       resume = 1;
       if(gameOver==1)
       {
        gameOver = 0;
        firstTime =1;
       } 
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    if ((key == 'P' || key=='p')/* Escape key ASCII*/) {
    
       resume = 0;
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    if ((key == 'D' || key=='d') && resume == 0/* Escape key ASCII*/) {
    
       Difficulty = 1;
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    if ((key == 'B' || key=='b')  /* Escape key ASCII*/) {
       if(Difficulty)
       Difficulty = 0;
       if(high)
       high=0;
       if(history)
       history=0;
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    if ((key == 'H' || key=='h') && resume == 0/* Escape key ASCII*/) {
    
       high = 1;
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    if ((key == 'G' || key=='g') && resume == 0/* Escape key ASCII*/) {
    
       history = 1;
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    if ((key == 'N' || key=='n') && (history ==0) && (high == 0) && (Difficulty ==0)/* Escape key ASCII*/) {
    
       remove("highscores.txt");
       remove("scores.txt");
       firstTime=1;
       highscore = 0;
       highscore2 =0;
       resume = 1;
       Time1 = 1;
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
   
    else if (int(key) == 13)
    {  
	}
    
    glutPostRedisplay();
}

/*
 * This function is called after every RefreshR 0.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next RefreshR 0/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

    srand(time(NULL));
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowSize(width, height);
    glutCreateWindow("PF's Snake Game");
    glutFullScreen();
    InitRandomizer(); // seed the random number generator...
     // initialize the graphics library...
   // we will be using color display mode
    glutInitWindowPosition(100,200); // set the initial position of our window
     // set the size of our window
     // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...
    
    
    






// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after RefreshR 0.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

