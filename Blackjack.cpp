#include<simplecpp>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<vector>
using namespace std;
class Card{


    private :
                int value;
                char display[5];
    public  :
                Card(int n);
                int getValue();
                char* getDisplay();
};
Card::Card(int n){
                    switch(n-((n/13)*13)+1){
                    case 1:strcpy(display,"A ");
                            value=11;
                            break;
                    case 2:strcpy(display,"2 ");
                            value=2;
                            break;
                    case 3:strcpy(display,"3 ");
                            value=3;
                            break;
                    case 4:strcpy(display,"4 ");
                            value=4;
                            break;
                    case 5:strcpy(display,"5 ");
                            value=5;
                            break;
                    case 6:strcpy(display,"6 ");
                            value=6;
                            break;
                    case 7:strcpy(display,"7 ");
                            value=7;
                            break;
                    case 8:strcpy(display,"8 ");
                            value=8;
                            break;
                    case 9:strcpy(display,"9 ");
                            value=9;
                            break;
                    case 10:strcpy(display,"10 ");
                            value=10;
                            break;
                    case 11:strcpy(display,"J ");
                            value=10;
                            break;
                    case 12:strcpy(display,"Q ");
                            value=10;
                            break;
                    case 13:strcpy(display,"K ");
                            value=10;
                            break;
                }

                switch(n/13){
                    case 0:strcat(display,"S");
                            break;
                    case 1:strcat(display,"H");
                            break;
                    case 2:strcat(display,"C");
                            break;
                    case 3:strcat(display,"D");
                            break;
                }
}

int Card::getValue(){


                    return value;
}
char* Card::getDisplay(){

                    return display;
}
class Pack{

    private :   int memory[52];
                int nop,nocg; //nod means number of packs, nocg means number of cards given
                void refreshPack(){
                    nocg=0;
                    for(int i=0;i<52;i++){
                        memory[i]=nop;
                    }
                }
    public  :
                Pack(int n);
                Card randomCard();
};
Pack::Pack(int n){

                    nop=n;
                    ::srand(time(NULL));
                    refreshPack();
}
Card Pack::randomCard(){

                    int n;
                    bool flag = false;
                    while(!flag){
                        n=(rand()%52);
                        //checking if n was generated earlier also
                        if(memory[n]==0){
                            flag=false;
                        }
                        else{
                            memory[n]--;
                            flag=true;
                            nocg++;
                        }
                        if(nocg==52*nop)refreshPack();
                    }
                    Card temp(n);
                    return temp;
}
class Hand{
    private :   vector<Card>hand1;
                vector<Rectangle>c;
                vector<Text>t;
                vector<Card>hand1reserve;
                vector<Rectangle>creserve;
                vector<Text>treserve;
                vector<bool>flip;
                int startx,starty,i;
                int handtotal;
                int ace;
    public  :
                Hand(int x, int y);
                void drawCard(Pack &p1,bool show);
                void sethandtotal(int value);
                int gethandtotal();
                void flipCard();
                void moveCard(Hand &s1);
                void incrementi();
};

Hand::Hand(int x, int y){


                    startx=x;
                    starty=y;
                    i=0;
                    handtotal=0;
                    ace=0;
}
void Hand::drawCard(Pack &p1,bool show){


                    hand1.push_back(p1.randomCard());
                    c.push_back(Rectangle(startx+(i%11)*75,starty+(i/11)*100,50,80));
                    t.push_back(Text(startx+i*75,starty,""));
                    flip.push_back(show);
                    if(flip[i]){
                        t[i].reset(startx+i*75,starty,hand1[i].getDisplay());
                        sethandtotal(hand1[i].getValue());
                    }
                    i++;
}
void Hand::sethandtotal(int value){



                    if(value==11)ace++;

                    handtotal+=value;
                    if(handtotal>21&&ace>0){
                        handtotal-=10;
                        ace--;
                    }
 }
int Hand::gethandtotal(){
                    return handtotal;
}

void Hand::flipCard(){
                    t[1].reset(startx+75,starty,hand1[1].getDisplay());
                    sethandtotal(hand1[1].getValue());
}

void Hand::moveCard(Hand& s1){
                    handtotal/=2;
                    c[1].reset(startx,starty+100,50,80);
                    t[1].reset(startx,starty+100,hand1[1].getDisplay());
                    s1.hand1.push_back(hand1[1]);
                    s1.c.push_back(c[1]);
                    s1.t.push_back(t[1]);
                    s1.sethandtotal(gethandtotal());
                    s1.incrementi();
                    c.pop_back();
                    t.pop_back();
                    hand1.pop_back();
                    i--;
}

void Hand::incrementi(){
                    i++;
}

class Blackjack{
    private:char pageindicator;
            int currentmoney,currentbet,currenttotal,dealertotal,cputotal,ace_p,ace_d,ace_c,splittotal;
            Text ct_t,cm_t,cb_t,dt_t,cput_t,message;
            char playerName[10];
            bool spliti;
    public :
            Blackjack();
            void start();
            void mainGame();
            void startPage();
            void detailsPage();
            void rulesPage1();
            void rulesPage2();
            void rulesPage3();
            void endPage();

            void setcb(int value);
            void setcm(int value);
            void setcm_t();
            void setcb_t();
            void setct_t(int value);
            void setdt_t(int value);
            void setcput_t(int value);
            void setmsg(string value);

            void draw(Pack &p1, Hand& h1, char c, bool show);

            void hit(Pack& p1, Hand& h1);
            void stand(Pack& p1, Hand& d1);
            void doubledown(Pack& p1, Hand& h1);
            void split(Pack& p1, Hand& h1, Hand& s1);
            void compare();
            void reset();
};

void Blackjack::setcb(int value){
    if(value>currentmoney){
        setmsg("You don't have enough money to place this bet");
        wait(0.5);
    }
    else if(value==0){
        currentbet=value;
        setcb_t();
    }
    else{
    currentmoney-=value;
    currentbet+=value;
    setcm_t();
    setcb_t();
    }
}

void Blackjack::setcm(int value){

    currentmoney+=value;
    setcm_t();

}

void Blackjack::setcb_t(){
    cb_t.reset(405,600,currentbet);
}

void Blackjack::setcm_t(){
    cm_t.reset(200,600,currentmoney);
}

void Blackjack::setct_t(int value){
    currenttotal=value;
    ct_t.reset(200,550,currenttotal);
}

void Blackjack::setdt_t(int value){
    dealertotal=value;
    dt_t.reset(810,600,dealertotal);
}

void Blackjack::setcput_t(int value){
    cputotal=value;
    cput_t.reset(910,600,cputotal);
}

void Blackjack::setmsg(string value){
    message.reset(500,700,value);
}

void Blackjack::draw(Pack &p1, Hand& h1, char c, bool show=true){
    h1.drawCard(p1,show);
        switch(c){
            case 'd':   setdt_t(h1.gethandtotal());
                        break;
            case 'p':   setct_t(h1.gethandtotal());
                        break;
            case 'c':   setcput_t(h1.gethandtotal());
                        break;
        }
}

void Blackjack::hit(Pack& p1,Hand& h1){
    draw(p1,h1,'p');
}

void Blackjack::stand(Pack& p1,Hand& d1){
    d1.flipCard();
    setdt_t(d1.gethandtotal());
    wait(0.5);
    while(dealertotal<17){
        draw(p1,d1,'d');
        wait(2);
    }
}

void Blackjack::doubledown(Pack& p1, Hand& h1){
    setcb(currentbet);
    hit(p1,h1);
}

void Blackjack::split(Pack& p1, Hand& h1, Hand& s1){
    setcb(currentbet);
    h1.moveCard(s1);
    setct_t(h1.gethandtotal());
    splittotal=currenttotal;
}

void Blackjack::compare(){
    if(currenttotal>21){
        setmsg("You just went bust. You lose this round.");
    }
    else if(dealertotal>21){
        setmsg("Dealer went bust. You win this round.");
        setcm(2*currentbet);
    }
    else if(currenttotal>dealertotal){
        setmsg("Your total is greater than dealer. You win this round.");
        setcm(2*currentbet);
    }
    else if(currenttotal<dealertotal){
        setmsg("Your total is lesser than dealer. You lose this round.");
    }
    else{
        setmsg("Your total is equal to dealer. This round is a push.");
        setcm(currentbet);
    }
    setcb(0);
    setct_t(0);
    setdt_t(0);
    setcput_t(0);
}

void Blackjack::reset(){

    ct_t.reset(0,0,"");
    cm_t.reset(0,0,"");
    cb_t.reset(0,0,"");
    dt_t.reset(0,0,"");
    cput_t.reset(0,0,"");
    setmsg("");
}
//function for main game interface
void Blackjack::mainGame(){

    Line l1(0,1,1000,1);

    Rectangle dealerbox(75,50,100,50);
    Text dealer(75,50,"Dealer");

    Line l2(0,100,1000,100);

    Rectangle playerbox(75,150,100,50);
    Text player(75,150,playerName);

    Line l3(0,300,1000,300);

    Rectangle cpubox(75,350,100,50);
    Text cpu(75,350,"CPU");

    Line l4(0,500,1000,500);
    Line l5(150,0,150,500);

    Rectangle total(100,550,100,50);
    Text total_t(100,550,"Total : ");

    Rectangle ct(200,550,100,50);
    setct_t(0);

    Rectangle money(100,600,100,50);
    Text money_t(100,600,"Money : ");

    Rectangle cm(200,600,100,50);
    setcm_t();

    Rectangle bet10(275,550,50,50);
    Text bet10_t(275,550,"Bet 10 ");

    Rectangle bet20(325,550,50,50);
    Text bet20_t(325,550,"Bet 20 ");

    Rectangle bet50(375,550,50,50);
    Text bet50_t(375,550,"Bet 50 ");

    Rectangle bet100(430,550,60,50);
    Text bet100_t(430,550,"Bet 100 ");

    Rectangle bet(300,600,100,50);
    Text bet_t(300,600,"Bet : ");

    Rectangle cb(405,600,110,50);
    setcb_t();

    Rectangle start(490,575,60,100);
    Text start_t(490,575,"Start");

    Rectangle hitbutton(590,550,100,50);
    Text hit_t(590,550,"Hit");

    Rectangle standbutton(690,550,100,50);
    Text stand_t(690,550,"Stand");

    Rectangle splitbutton(590,600,100,50);
    Text split_t(590,600,"Split");

    Rectangle doublebutton(690,600,100,50);
    Text double_t(690,600,"Double");


    Rectangle dtotal(810,550,100,50);
    Text dtotal_t(810,550,"Dealer Total : ");

    Rectangle dt(810,600,100,50);
    setdt_t(0);

    Rectangle cputotal(910,550,100,50);
    Text cputotal_t(910,550,"CPU Total : ");

    Rectangle cput(910,600,100,50);
    setcput_t(0);

    Rectangle messagebox(500,700,950,100);

    Pack p1(2);


    while(currentmoney>0){

        while(true){
            setmsg("Place bet to start. Bets once placed can't be removed.");
            int m=getClick();
            if( ( ( m/65536<= (bet10.getX()+25) ) and ( m/65536>= (bet10.getX()-25) ) )
            and ( ( m%65536<= (bet10.getY()+25) ) and ( m%65536>= (bet10.getY()-25) ) ) ){
                setcb(10);
            }
            if( ( ( m/65536<= (bet20.getX()+25) ) and ( m/65536>= (bet20.getX()-25) ) )
            and ( ( m%65536<= (bet20.getY()+25) ) and ( m%65536>= (bet20.getY()-25) ) ) ){
                setcb(20);
            }
            if( ( ( m/65536<= (bet50.getX()+25) ) and ( m/65536>= (bet50.getX()-25) ) )
            and ( ( m%65536<= (bet50.getY()+25) ) and ( m%65536>= (bet50.getY()-25) ) ) ){
                setcb(50);
            }
            if( ( ( m/65536<= (bet100.getX()+25) ) and ( m/65536>= (bet100.getX()-25) ) )
            and ( ( m%65536<= (bet100.getY()+25) ) and ( m%65536>= (bet100.getY()-25) ) ) ){
                setcb(100);
            }
            if( ( ( m/65536<= (start.getX()+30) ) and ( m/65536>= (start.getX()-30) ) )
            and ( ( m%65536<= (start.getY()+50) ) and ( m%65536>= (start.getY()-50) ) ) ){
                if(!currentbet){
                    setmsg("You should place some bet to start round.");
                    wait(0.75);
                }
                else{
                    setmsg("Brace yourself. The game begins !");
                    break;
                }
            }
        }

        Hand dealer_h(200,50),player_h(200,150),cpu_h(200,350),split_h(200,250);
        draw(p1,dealer_h,'d');
        draw(p1,dealer_h,'d',false);
        draw(p1,player_h,'p');
        draw(p1,player_h,'p');
        draw(p1,cpu_h,'c');
        draw(p1,cpu_h,'c');

        while(currenttotal<=21){
            int m=getClick();
            if( ( ( m/65536<= (hitbutton.getX()+50) ) and ( m/65536>= (hitbutton.getX()-50) ) )
            and ( ( m%65536<= (hitbutton.getY()+25) ) and ( m%65536>= (hitbutton.getY()-25) ) ) ){
                hit(p1,player_h);
            }
            if( ( ( m/65536<= (standbutton.getX()+50) ) and ( m/65536>= (standbutton.getX()-50) ) )
            and ( ( m%65536<= (standbutton.getY()+25) ) and ( m%65536>= (standbutton.getY()-25) ) ) ){
                break;
            }
            if( ( ( m/65536<= (doublebutton.getX()+50) ) and ( m/65536>= (doublebutton.getX()-50) ) )
            and ( ( m%65536<= (doublebutton.getY()+25) ) and ( m%65536>= (doublebutton.getY()-25) ) ) ){
                if( currentmoney >= currentbet ){
                    doubledown(p1,player_h);
                    break;
                }
                else{
                    setmsg("Doubling down not allowed. You don't have enough money.");
                    wait(0.75);
                    setmsg("The round continues.");
                }
            }
            if( ( ( m/65536<= (splitbutton.getX()+50) ) and ( m/65536>= (splitbutton.getX()-50) ) )
            and ( ( m%65536<= (splitbutton.getY()+25) ) and ( m%65536>= (splitbutton.getY()-25) ) ) ){
                if( currentmoney >= currentbet ){
                    split(p1,player_h,split_h);
                    spliti=true;
                }
                else{
                    setmsg("Spliting not allowed. You don't have enough money.");
                    wait(0.75);
                    setmsg("The round continues.");
                }
            }
        }
        if(spliti){
            while(splittotal<=21){
            int m=getClick();
            if( ( ( m/65536<= (hitbutton.getX()+50) ) and ( m/65536>= (hitbutton.getX()-50) ) )
            and ( ( m%65536<= (hitbutton.getY()+25) ) and ( m%65536>= (hitbutton.getY()-25) ) ) ){
                hit(p1,split_h);
            }
            if( ( ( m/65536<= (standbutton.getX()+50) ) and ( m/65536>= (standbutton.getX()-50) ) )
            and ( ( m%65536<= (standbutton.getY()+25) ) and ( m%65536>= (standbutton.getY()-25) ) ) ){
                break;
            }
            }
        }
        stand(p1,dealer_h);
        wait(0.5);
        compare();
        wait(2);
    }
    setmsg("Your money has become zero. Thanks For Playing!");
    wait(1);
    reset();
    pageindicator = 'e';
}

//constructor for class Blackjack
Blackjack::Blackjack(){

    pageindicator='s';
    currentmoney=500;
    currentbet=0;
    currenttotal=0;
    dealertotal=0;
    cputotal=0;
    ace_p=0;
    ace_d=0;
    ace_c=0;
    spliti=false;
    splittotal=0;
}

//function to switch between pages
void Blackjack::start(){
    bool playing = true;
    while(playing){
        switch(pageindicator){
            case 's'    :startPage();
                        break;
            case 'd'    :detailsPage();
                        break;
            case 'm'    :mainGame();
                        break;
            case '1'    :rulesPage1();
                        break;
            case '2'    :rulesPage2();
                        break;
            case '3'    :rulesPage3();
                        break;
            case 'e'    :endPage();
                        playing = false;
                        break;
        }
    }
}

//function to display start page
void Blackjack::startPage(){

    Text title(500,200,"BlackJack");
    Rectangle titlebox(500,200,300,300);
    Text start(500,450,"Start");
    Rectangle startbox(500,450,300,60);
    Text rules(500,550,"Rules");
    Rectangle rulesbox(500,550,300,60);
    while(true){
        int go = getClick();
        if( ( ( go/65536<= (startbox.getX()+150) ) and ( go/65536>= (startbox.getX()-150) ) )
        and ( ( go%65536<= (startbox.getY()+30 ) ) and ( go%65536>= (startbox.getY()-30 ) ) ) ){
            pageindicator = 'd';
            break;
        }
        if( ( ( go/65536<= (rulesbox.getX()+150) ) and ( go/65536>= (rulesbox.getX()-150) ) )
        and ( ( go%65536<= (rulesbox.getY()+30 ) ) and ( go%65536>= (rulesbox.getY()-30 ) ) ) ){
            pageindicator = '1';
            break;
        }
    }
}

//function to display page where user enters his name
void Blackjack::detailsPage(){
    XEvent event;
    Rectangle r1(500,300,300,50);
    Text t0(500,300,"Enter your name (10 characters only)");
    bool enter = false;
    Rectangle enterButton(500,500,300,50);
    Text go(500,500,"Go");
    Text name;
    int i = 0;
    playerName[i]='\0';
    while(!enter){
        nextEvent(event);
        if(mouseButtonPressEvent(event)){
            int x = event.xbutton.x;
            int y = event.xbutton.y;
            if( ( ( x <= (650) ) and ( x >= (350) ) )
            and ( ( y <= (525) ) and ( y >= (475) ) ) ){
                if(playerName[0]!='\0'){
                    enter = true;
                    pageindicator = 'm';
                }
            }
        }
        if(keyPressEvent(event)){
            char temp = charFromEvent(event);
            cout<<temp;
            if(temp=='\b'){
                if(i!=0){
                    i--;
                    playerName[i]='\0';
                    name.reset(500,400,playerName);
                }
            }
            else if(i<10){
                playerName[i]=temp;
                i++;
                playerName[i]='\0';
                name.reset(500,400,playerName);
            }
        }
    }
}

//function to display rules page no.1
void Blackjack::rulesPage1(){
    Rectangle backbutton(500,50,500,100);
    Text menu(500,50,"Back To Main Menu");
    Text t0(500,150,"::    Rules Page 1    ::");
    Text t1[4];
    t1[0].reset(500,250,"The object of the game is to beat the dealer in one of the following ways : ");
    t1[1].reset(500,350,"Get 21 points on the player's first two cards (called a blackjack), without a dealer blackjack ; ");
    t1[2].reset(500,450,"Reach a final score higher than the dealer without exceeding 21 ; ");
    t1[3].reset(500,550,"Let the dealer draw additional cards until his or her hand exceeds 21 .");
    Rectangle nextbutton(500,650,500,100);
    Text page2(500,650,"Go to Page 2");
    while(true){
        int go=getClick();
        if( ( ( go/65536<= (backbutton.getX()+250) ) and ( go/65536>= (backbutton.getX()-250) ) )
        and ( ( go%65536<= (backbutton.getY()+50 ) ) and ( go%65536>= (backbutton.getY()-50 ) ) ) ){
            pageindicator = 's';
            break;
        }
        if( ( ( go/65536<= (nextbutton.getX()+250) ) and ( go/65536>= (nextbutton.getX()-250) ) )
        and ( ( go%65536<= (nextbutton.getY()+50 ) ) and ( go%65536>= (nextbutton.getY()-50 ) ) ) ){
            pageindicator = '2';
            break;
        }
    }
}

//function to display rules page no. 2
void Blackjack::rulesPage2(){
    Rectangle backbutton(500,50,500,100);
    Text page1(500,50,"Back To Page 1");
    Text t0(500,150,"::    Rules Page 2    ::");
    Text t1[4];
    t1[0].reset(500,250,"The player or players are dealt a two-card hand and add together the value of their cards . ");
    t1[1].reset(500,350,"Face cards (kings, queens, and jacks) are counted as ten points . ");
    t1[2].reset(500,450,"A player and the dealer can count an ace as 1 point or 11 points . ");
    t1[3].reset(500,550,"All other cards are counted as the numeric value shown on the card . ");
    Rectangle nextbutton(500,650,500,100);
    Text page3(500,650,"Go to Page 3");
    while(true){
        int go=getClick();
        if( ( ( go/65536<= (backbutton.getX()+250) ) and ( go/65536>= (backbutton.getX()-250) ) )
        and ( ( go%65536<= (backbutton.getY()+50 ) ) and ( go%65536>= (backbutton.getY()-50 ) ) ) ){
            pageindicator = '1';
            break;
        }
        if( ( ( go/65536<= (nextbutton.getX()+250) ) and ( go/65536>= (nextbutton.getX()-250) ) )
        and ( ( go%65536<= (nextbutton.getY()+50 ) ) and ( go%65536>= (nextbutton.getY()-50 ) ) ) ){
            pageindicator = '3';
            break;
        }
    }
}

//function to display rules page no.3
void Blackjack::rulesPage3(){
    Rectangle backbutton(500,50,500,100);
    Text page2(500,50,"Back To Page 2");
    Text t0(500,150,"::    Rules Page 3    ::");
    Text t1[6];
    t1[0].reset(500,250,"Hit : Take another card from the dealer . ");
    t1[1].reset(500,350,"Stand : Take no more cards . ");
    t1[2].reset(500,450,"Double down : The player is allowed to increase the initial bet by up to 100% in exchange for committing to stand after receiving exactly one more card . ");
    t1[3].reset(500,550,"Split : If the first two cards of a hand have the same value, the player can split them into two hands, by moving a second bet equal to the first . ");
    t1[4].reset(500,650,"The hands are treated as independent new hands, with the player winning or losing their wager separately for each hand . ");
    t1[5].reset(500,750,"Play the game and you will learn more !!!");
    while(true){
        int go=getClick();
        if( ( ( go/65536<= (backbutton.getX()+250) ) and ( go/65536>= (backbutton.getX()-250) ) )
        and ( ( go%65536<= (backbutton.getY()+50 ) ) and ( go%65536>= (backbutton.getY()-50 ) ) ) ){
            pageindicator = '2';
            break;
        }
    }
}

//function to display endpage
void Blackjack::endPage(){

    Rectangle endbox(500,400,200,200);
    Text gameover(500,400," GAME OVER ");
    getClick();
    endbox.reset(500,400,200,400);
    gameover.reset(500,250," Made by : ");
    Text name1(500,300," Darshan Tank ");
    Text roll1(500,350," 150020012 ");
    Text name2(500,400," Aarsh Dodhia ");
    Text roll2(500,450," 150020018 ");
    Text mentor(500,500," Mentor : ");
    Text mentorname(500,550," Prateesh Goyal ");
    getClick();
}

main_program{
    initCanvas("BlackJack",1000,800);
    Blackjack game;
    game.start();
}
