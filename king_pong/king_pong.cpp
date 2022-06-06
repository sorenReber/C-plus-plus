#include "iostream"
#include "raylib.h"
using namespace std;
// Background color
Color forest ={0, 65, 44, 255};

class Ball{
public:
    float x, y;
    float radius;
    float ballSpeedX, ballSpeedY;
    bool canReset = false;

    Ball(float aX, float aY, float aRadius, float aSpeed)
    //Ball constructor
    {
        x = aX;
        y = aY;
        radius = aRadius;
        ballSpeedX = aSpeed;
        ballSpeedY = aSpeed;
    };
    void draw()
    {
        DrawCircle((int) x, (int) y, radius, RAYWHITE);
    };
    void ballReset(float centerX, float centerY, float speed)
    // Reset the ball after it exits the screen, called when player presses the 'r' key.
    {
        if (canReset)
        {
           x = centerX;
           y = centerY;
           ballSpeedX = speed;
           ballSpeedY = speed;
           canReset = false;
        }
    }
    void screenCheck()
    // Check to see if the ball is hitting the screen edges and bounce if it's the top or bottom or declare a winner if left or right side.
    {
        if(y < 0 || y > GetScreenHeight() - radius)
        {
            ballSpeedY *= -1;
        }
        if(x < 0)
        {
            int textWidth = MeasureText("Right side Wins", 30);
            DrawText("Right side wins", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2, 30, GOLD);
            canReset = true;
        }
        if(x > GetScreenWidth())
        {
            int textWidth = MeasureText("Left side Wins", 30);
            DrawText("Left side wins", GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2, 30, GOLD);
            canReset = true;
        }
    }
};

class Paddle{
public:
    float x, y;
    float paddleSpeed;
    int keyUp, keyDown;

    Rectangle getRect()
    // Creates rectangle object
    {
        return Rectangle{x, y, 10, 100};
    }
    Paddle(float ax, float ay, float aSpeed, int aKeyUp, int aKeyDown)
    // Paddle Constructor
    {
        x = ax;
        y = ay;
        paddleSpeed = aSpeed;
        keyUp = aKeyUp;
        keyDown = aKeyDown;
    }
    void draw()
    {
        DrawRectangleRec(getRect(), RAYWHITE);
    }
    void paddleMove(float frames)
    //Moves the paddles up or down
    {
        if(IsKeyDown(keyUp))
        {
            y -= paddleSpeed * frames;
            if(y < 0)
            {
                y += paddleSpeed * frames;
            }
        }
        if(IsKeyDown(keyDown))
        {
            y += paddleSpeed * frames;
            if(y > GetScreenHeight() -100)
            {
                y -= paddleSpeed * frames;
            }
        }
    }
};

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "King Pong");
    Ball ball(screenWidth / 2, screenHeight / 2, 5, 200);
    Paddle leftPaddle(25, screenHeight / 2 - 50, 200, KEY_W, KEY_S);
    Paddle rightPaddle(screenWidth - 30, screenHeight / 2 - 50, 200, KEY_UP, KEY_DOWN);

    SetTargetFPS(60);               // Set game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Ball movements and functions
        ball.x += ball.ballSpeedX * GetFrameTime();
        ball.y += ball.ballSpeedY * GetFrameTime();
        ball.screenCheck();
        if(IsKeyReleased(KEY_R))
        {
            ball.ballReset(screenWidth / 2, screenHeight / 2, 200);
        }
        //Paddle Movements
        rightPaddle.paddleMove(GetFrameTime());
        leftPaddle.paddleMove(GetFrameTime());
        //Check for collisions
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, leftPaddle.getRect()))
        {
            if(ball.ballSpeedX < 0)
            {
              ball.ballSpeedX *= -1.1f;
            }
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, rightPaddle.getRect()))
        {
            if(ball.ballSpeedX > 0)
            {
              ball.ballSpeedX *= -1.1f;
            }
        }
        // Draw
        BeginDrawing();

            // Background
            ClearBackground(forest);
            // Ball
            ball.draw();
            // Paddles
            rightPaddle.draw();
            leftPaddle.draw();

        EndDrawing();

    }

    // De-Initialization
    CloseWindow();        // Close window


    return 0;
}
