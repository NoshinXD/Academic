package javagame;

import org.newdawn.slick.*;
import org.newdawn.slick.state.*;

import java.util.Scanner;

public class guiGame extends StateBasedGame {

    public static final String gamename = "LOA";
    public static final int menu = 0;
    public static final int play = 1;
    public static final int play_ai = 2;
    public static final int my_play = 3;

    public guiGame(String name, int n) {
        super(name);
        this.addState(new Play(play, n));
        this.addState(new Play_ai(play_ai, n));
        this.addState(new myPlay(my_play, n));
    }

    public void initStatesList(GameContainer gc) throws SlickException {
        //this.getState(menu).init(gc, this);
        this.getState(play).init(gc, this);
        this.getState(play_ai).init(gc, this);
        this.getState(my_play).init(gc, this);
        //this.enterState(play);
        this.enterState(play_ai);
        //this.enterState(my_play);
    }

    public static void main(String[] args) {
        System.out.println("enter ur board size: ");
        Scanner sc = new Scanner(System.in);
        int n =  sc.nextInt();
        AppGameContainer appgc;
        try {
            appgc = new AppGameContainer(new guiGame(gamename, n));
            appgc.setDisplayMode(520, 520, false);
            appgc.start();
        } catch (SlickException e) {
            e.printStackTrace();
        }
    }
}
