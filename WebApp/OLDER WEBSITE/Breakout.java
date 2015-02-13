/*
 * File: Breakout.java
 * -------------------
 * Name:
 * Section Leader:
 * 
 * This file will eventually implement the game of Breakout.
 */

import acm.graphics.*;
import acm.program.*;
import acm.util.*;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class Breakout extends GraphicsProgram {

	/** Width and height of application window in pixels */
	public static final int APPLICATION_WIDTH = 404;
	public static final int APPLICATION_HEIGHT = 600;

	/**
	 * Dimensions of game board Should not be used directly (use
	 * getWidth()/getHeight() instead). *
	 */
	private static final int WIDTH = APPLICATION_WIDTH;
	private static final int HEIGHT = APPLICATION_HEIGHT;

	/** Dimensions of the paddle */
	private static final int PADDLE_WIDTH = 60;
	private static final int PADDLE_HEIGHT = 10;

	/** Offset of the paddle up from the bottom */
	private static final int PADDLE_Y_OFFSET = 30;

	/** Number of bricks per row */
	private static final int NBRICKS_PER_ROW = 10;

	/** Number of rows of bricks */
	private static final int NBRICK_ROWS = 10;

	/** Separation between bricks */
	private static final int BRICK_SEP = 4;

	/** Width of a brick */
	private static final int BRICK_WIDTH = (WIDTH - (NBRICKS_PER_ROW - 1)
			* BRICK_SEP)
			/ NBRICKS_PER_ROW;

	/** Height of a brick */
	private static final int BRICK_HEIGHT = 8;

	/** Radius of the ball in pixels */
	private static final int BALL_RADIUS = 10;

	/** Offset of the top brick row from the top */
	private static final int BRICK_Y_OFFSET = 70;

	/** Number of turns */
	private static final int NTURNS = 3;

	/** Paddle rectangle */
	private GRect paddle;

	/** Ball oval */
	private GOval ball;

	/** Random paddle movement */
	private RandomGenerator rgen = RandomGenerator.getInstance();

	/** Bricks */
	private GObject brick;

	/** Check for collisons **/
	GObject collider;

	private GObject lastCollision;

	private GOval powerUp;

	private GOval poisonBall;

	private GLabel count;
	
	private int bricksAlive;
	
	
	double dx = 2.5;
	double dy = 2.5;

	private static final int POISON_BALL_RADIUS = 3;

	/** Runs the Breakout program. */
	public void run() {
		double poisonX = rgen.nextInt(15, getWidth() - 15);
		double poisonY = rgen.nextInt(BRICK_Y_OFFSET
				+ (NBRICK_ROWS * BRICK_HEIGHT), PADDLE_Y_OFFSET - 15);

		poisonBall = new GOval(poisonX, poisonY, POISON_BALL_RADIUS * 2,
				POISON_BALL_RADIUS * 2);
		
		addMouseListeners();
		setUpBricks();
		setUpPaddle();
		setUpBall();
		powerUp();
		waitForClick();

		ballMove();
		/*if (bricksAlive == 98)
		{
			poisonBall();
		}
		while (bricksAlive <= 98){
			poisonBallMove();
		}*/
		

		for (int i = 0; i <= NTURNS; i++) {
			resetGame();
		}

	}

	/* You fill this in, along with any subsidiary methods */

	/* Play the game */

	// ball movement
	private void ballMove() {
		bricksAlive = NBRICKS_PER_ROW * NBRICK_ROWS;
		double ballX = getWidth() / 2 - BALL_RADIUS;
		double ballY = getHeight() / 2 - BALL_RADIUS;
		AudioClip bounceClip = MediaTools.loadAudioClip("bounce.au");
		int i = 0;
		double vx = rgen.nextDouble(1.0, 3.0);
		if (rgen.nextBoolean(0.5))
			vx = -vx;

		double vy = rgen.nextDouble(1.0, 3.0);
		if (rgen.nextBoolean(0.5)) {
			vy = -vy;

		}

		count = new GLabel("Bricks Alive " + bricksAlive, getWidth() / 2,
				getHeight() - 7);

		while (ball.getY() < getHeight() - PADDLE_Y_OFFSET) {

			ballX = ballX + vx;
			ballY = ballY + vy;

			// bounce off walls

			if (ballX < 0 || ballX > getWidth() - (2 * BALL_RADIUS)) {
				vx = -vx;
				lastCollision = null;
			}
			if (ballY < 0 || ballY > getHeight()) {
				vy = -vy;
				lastCollision = null;
			}

			// test for collisions with sticky paddle bug fix
			GObject collider = getCollidingObject();
			if (collider == paddle && lastCollision != paddle) {
				if (collider.getX() < paddle.getX() + (PADDLE_WIDTH / 3)) {
					vx = -vx * 1.5;
					vy = rgen.nextDouble(1.0, 3.0);

				}

				if (collider.getX() > paddle.getX() - (PADDLE_WIDTH / 3)) {
					vx = -vx * 1.5;
					vy = rgen.nextDouble(1.0, 3.0);

				}
				vy = -vy * 1.5;

				bounceClip.play();
				lastCollision = paddle;

			}

			else if (collider != paddle && collider != null && collider != count && collider != poisonBall) {
				remove(count);
				remove(collider);
				bricksAlive--;
				// Bricks alive label counter
				count = new GLabel("Bricks Alive " + bricksAlive,
						getWidth() / 2, getHeight() - 7);
				lastCollision = brick;
				bounceClip.play();
				vy = -vy;
				vx = rgen.nextDouble(1.0, 3.0);
				add(count);

			}

		
				
			if (collider == paddle && lastCollision == paddle
					|| collider == count) {
			}
			// power up collision
			if (collider == powerUp) {

				paddle.setSize(PADDLE_WIDTH * 2, PADDLE_HEIGHT);
				remove(powerUp);

			}
			
			if (collider == poisonBall) {
				paddle.setSize(PADDLE_WIDTH/2, PADDLE_HEIGHT);
				remove(poisonBall);
				println("POISON BALL");
				lastCollision = poisonBall;
			}
				
			if(bricksAlive == 98 && i<1 )
				{
					poisonBall();
					i++;
				}
			if(bricksAlive<=98){
				poisonBallMove();
			}
			
			
			/*if (bricksAlive <=98){
				poisonBallMove();
			}*/

			// change speeds
			if (bricksAlive == 95) {
				vy = vy * 1.0009;
				vx = vx * 1.0009;
			}
			if (bricksAlive == 90) {
				vy = vy * 1.0009;
				vx = vx * 1.0009;
			}
			if (bricksAlive == 0) {
				vy = 0;
				vx = 0;
				GLabel win = new GLabel("you win", getWidth() / 2,
						getHeight() / 2);
				win.setColor(Color.red);

				add(win);
			}
			
			

			ball.setLocation(ballX + vx, ballY + vy);
			pause(10);
		}
	}

	private void poisonBallMove()
	{
		// poison ball
		
		//int i = 0;
		
		

			//if (i < 1) {

				//i++;
				//poisonBall();
			
				
				/*dx = rgen.nextDouble(2.0, 3.0);
				if (rgen.nextBoolean(.5)) {
					dx = -dx;
				}
				dy = rgen.nextDouble(2.0, 3.0);
				if (rgen.nextBoolean(.5)) {
					dy = -dy;
				}*/

			//}
			double pX = poisonBall.getX();
			double pY = poisonBall.getY();

			if (pX < 0.0 || pX > getWidth() - 2 * POISON_BALL_RADIUS) {
				dx = -dx;
				
			}
			if (pY < 0.0 || pY > getHeight() - 2 * POISON_BALL_RADIUS) {
				dy = -dy;
				
			}

			poisonBall.move(dx, dy);
			
			

		}
			
		
//	}
	
	private void poisonBall() {

		
		poisonBall.setFilled(true);
		poisonBall.setFillColor(Color.RED);
		poisonBall.setColor(Color.RED);
		add(poisonBall);

	}

	private void powerUp() {
		double locX = rgen.nextInt(5, getWidth() - 5);
		double locY = rgen.nextInt(BRICK_Y_OFFSET, BRICK_Y_OFFSET
				+ (NBRICK_ROWS * BRICK_HEIGHT));
		powerUp = new GOval(locX, locY, 10, 10);
		powerUp.setColor(Color.DARK_GRAY);
		powerUp.setFilled(true);

		add(powerUp);

	}

	private GObject getCollidingObject() {

		GObject objectTL = getElementAt(ball.getX(), ball.getY());
		GObject objectTR = getElementAt(ball.getX() + (2 * BALL_RADIUS),
				ball.getY());
		GObject objectBL = getElementAt(ball.getX(),
				(2 * BALL_RADIUS) + ball.getY());
		GObject objectBR = getElementAt(ball.getX() + (2 * BALL_RADIUS),
				ball.getY() + (2 * BALL_RADIUS));

		if (objectTL != null) {
			return objectTL;
		} else if (objectTR != null) {
			return objectTR;
		}

		else if (objectBL != null) {
			return objectBL;
		} else if (objectBR != null) {
			return objectBR;
		}

		else {
			return null;
		}
	}

	/* Sets up the Breakout Game */
	// creates rows
	private void setUpBricks() {

		for (int c = 0; c < NBRICK_ROWS; c++) {

			for (int i = 0; i < NBRICKS_PER_ROW; i++) {

				brick = new GRect(
						(BRICK_SEP * (i + 1) + (BRICK_WIDTH * (i))),
						(BRICK_Y_OFFSET + (BRICK_SEP * c) + (BRICK_HEIGHT * c)),
						BRICK_WIDTH, BRICK_HEIGHT);

				((GRect) brick).setFilled(true);

				// change brick colors
				int pickColor = c;
				if (c > 9) {
					pickColor = c % 10;
				}

				if (pickColor == 0 || pickColor == 1) {
					brick.setColor(Color.red);
				}
				if (pickColor == 2 || pickColor == 3) {
					brick.setColor(Color.orange);
				}
				if (pickColor == 4 || pickColor == 5) {
					brick.setColor(Color.yellow);
				}
				if (pickColor == 6 || pickColor == 7) {
					brick.setColor(Color.green);
				}
				if (pickColor == 8 || pickColor == 9) {
					brick.setColor(Color.cyan);
				}

				add(brick);

			}

		}

	}

	// set up paddle
	public void setUpPaddle() {

		int yPadCord = getHeight() - PADDLE_Y_OFFSET;

		paddle = new GRect(getWidth() / 2, yPadCord, PADDLE_WIDTH,
				PADDLE_HEIGHT);
		paddle.setFilled(true);
		paddle.setColor(Color.black);
		add(paddle);

	}

	// mouse movement
	public void mouseMoved(MouseEvent e) {
		int xCord = e.getX();
		if (xCord > (getWidth() - PADDLE_WIDTH - BRICK_SEP)) {
			xCord = xCord - PADDLE_WIDTH - BRICK_SEP;
		} else {

			paddle.setLocation(xCord, getHeight() - PADDLE_Y_OFFSET);
		}
	}

	public void resetGame() {
		if (ball.getY() >= getHeight() - PADDLE_Y_OFFSET) {
			GLabel lose = new GLabel("you lose", getWidth() / 2,
					getHeight() / 2);
			lose.setColor(Color.red);

			add(lose);

			waitForClick();
			removeAll();
			addMouseListeners();
			setUpBricks();
			setUpPaddle();
			setUpBall();
			powerUp();

			ballMove();

		}
	}

	// set up ball
	private void setUpBall() {

		ball = new GOval(getWidth() / 2 - BALL_RADIUS, getHeight() / 2
				- BALL_RADIUS, BALL_RADIUS * 2, BALL_RADIUS * 2);
		ball.setFilled(true);
		ball.setColor(Color.black);
		add(ball);

	}

}
