// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle
#define PWIDTH 60
#define PHEIGHT 5

// brick
#define BWIDTH 35
#define BHEIGHT 20
#define BMARGINX 7
#define BMARGINY 60
#define BINTERVAL 4

#define SCORELABEL "score: %i"
#define LIVESLABEL "lives: %i"
#define INFOFONT "SansSerif-10"
#define GRAY "GRAY"


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initLabel(GWindow window, char* text, int var, char* font, char* color, int x, int y);
void updateLabel(GWindow window, GLabel label, char* text, int var);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard label
    GLabel score_label = initLabel(window, SCORELABEL, 0, INFOFONT, GRAY, 5, 10);

    // instantiate lives label
    GLabel lives_label = initLabel(window, LIVESLABEL, 3, INFOFONT, GRAY, WIDTH - 35, 10);

    // number of bricks initially
    int bricks = COLS * ROWS;
    int score = 0;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    double yv = 0.1;
    double xv = drand48() / 10.0;

    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL) {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }
        double y = getY(ball);
        double x = getX(ball);
        if (y <= 0 ) {
            yv = -yv;
        }
        if (x <= 0 || x >= WIDTH - RADIUS * 2) {
            xv = -xv;
        }
        if (y >= HEIGHT - RADIUS * 2) {
            lives--;
            updateLabel(window, lives_label, LIVESLABEL, lives);
            removeGWindow(window, ball);
            pause(3);
            yv = 0.1;
            xv = drand48() / 10.0;
            ball = initBall(window);
        }

        GObject obj = detectCollision(window, ball);

        if (obj == paddle) {
            int x_paddle_center = (int) getX(paddle) + PWIDTH / 2;
            int x_ball_center = (int) getX(ball) + RADIUS;
            double diff = (x_paddle_center - x_ball_center) / 100.0;
            yv = -yv;
            xv = -diff;
        } else if (obj != NULL && strcmp(getType(obj), "GRect") == 0) {
            double xbr = getY(obj);
            double ybr = getX(obj);
            double xb = getX(ball);
            double yb = getY(ball);
            if (xb >= xbr && xb + RADIUS * 2 <= xbr + BWIDTH && (yb >= ybr + BHEIGHT || yb + RADIUS * 2 <= ybr)) {
                yv = -yv;
            } else {
                xv = -xv; 
            }
            removeGWindow(window, obj); 
            score += 100;
            updateLabel(window, score_label, SCORELABEL, score);
            bricks--;
        }
        
        move(ball, xv, yv);
        pause(1);
    }

    char* end_game_label;
    char* end_game_col;

    if (lives > 0) {
        end_game_label = "YOU WIN";
        end_game_col = "GREEN";
    } else {
        end_game_label = "GAME OVER";
        end_game_col = "RED";
    }

    GLabel label = newGLabel(end_game_label);
    setFont(label, "SansSerif-50");
    setColor(label, end_game_col);
    int label_width = getWidth(label);
    setLocation(label, (WIDTH - label_width) / 2, HEIGHT / 2);
    add(window, label);
    removeGWindow(window, ball);
    removeGWindow(window, paddle);

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    char * colors[] = {"RED", "BLUE", "CYAN", "GRAY", "ORANGE"};
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int x_pos = BMARGINX + (BINTERVAL * j) + (BWIDTH * j);
            int y_pos = BMARGINY + (BINTERVAL * i) + (BHEIGHT * i);
            GRect brick = newGRect(x_pos, y_pos, 35, 20);
            setFilled(brick, true);
            setColor(brick, colors[i]);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH / 2 - RADIUS / 2, HEIGHT / 2 - RADIUS / 2, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "GREEN");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH / 2 - PWIDTH / 2, HEIGHT - (HEIGHT / 7), PWIDTH, PHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

GLabel initLabel(GWindow window, char* text, int var, char* font, char* color, int x, int y)
{
    char s[20];
    sprintf(s, text, var); 
    GLabel label = newGLabel(s);
    setFont(label, font);
    setColor(label, color);
    add(window, label);
    setLocation(label, x, y);
    return label;
}

void updateLabel(GWindow window, GLabel label, char* text, int var)
{
    // update label
    char s[12];
    sprintf(s, text, var);
    setLabel(label, s);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
