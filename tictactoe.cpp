// 
/* 1 AI engine
    *state representation vector<vector<char>>
     * checking if game is end
     * detect winner
     * render
     * valid move
            * detect curent player
            * calculate valid moves
     * calculate state score
            * final state score
            * non-final state 
    * calculate best move
   2  User interface
    * chose X or O
    * input move cordinate start 
    * check illegal move
    *  response game result
    * print current game
    * print machine move
*/
#include<iostream>
#include<vector>
using namespace std;
typedef vector <vector<char>> GAMESTATE;
//state representation vector<vector<char>>
//* checking if game is end
bool check_game_state (GAMESTATE game)
{   //check row
    for (int i=0;i<3;i++)
       {
        if (game[i][0]==game[i][1]&&game[i][0]==game[i][2]&& game[i][0]!=' ') return true;
       }
    //check col
    for (int i=0;i<3;i++){
        if (game[0][i]==game[1][i]&&game[0][i]==game[2][i]&&game[0][i]!=' ')return true;
    }
     // check diagonals
    if (game[0][0] == game[1][1] && game[0][0] == game[2][2] && game[0][0] != ' ') return true;
    if (game[0][2] == game[1][1] && game[0][2] == game[2][0] && game[0][2] != ' ') return true;
     //check full
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game[i][j] == ' ') return false;
        }
    }
    return true;
}
// print to screen state game 
void  print_game (GAMESTATE game)

{
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++){
            
            cout<<"|"<< game[i][j]<<"|";
        }
        cout <<endl;
    }
}
// Detect curren player
char current_player(GAMESTATE game)
{
    int x=0;
    int o=0;
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            if(game[i][j]=='X') x++;
            else if (game[i][j]=='O') o++;
        }
    }
if (x==o) 
return 'X';
else 
return 'O';
}
// Enter coordinates to matrix
 GAMESTATE copy_move( int a, int b, GAMESTATE game,int player){
    GAMESTATE game_new(3,vector<char>(3));
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            game_new[i][j]=game[i][j];
        }
    }
    game_new[a][b]=player;
        return game_new;
 }
 // Find moves be probable
vector < GAMESTATE > valid_move(GAMESTATE game)
{
        char player =current_player(game);
        vector<GAMESTATE> result;
        for(int i=0;i<3;i++)
        {
            for (int j=0;j<3;j++)
            {
                if(game[i][j]==' '){
                    GAMESTATE game_new =copy_move(i,j, game,player);
                    game_new[i][j]=player;
                    result.push_back(game_new);
                }
            }
        }
        return result;


}
// get score final state
int final_state_score(GAMESTATE game)
{
     // check rows
    for (int i = 0; i < 3; i++)
        if (game[i][0] == game [i][1] && game[i][0] == game[i][2] && game[i][0] != ' ')
            return game[i][0] == 'X' ? 1 : -1;
    // check cols
    for (int i = 0; i < 3; i++)
        if (game[0][i] == game[1][i] && game[0][i] == game[2][i] && game[0][i] != ' ')
            return game[0][i] == 'X' ? 1 : -1;
    if (game[0][0] == game[1][1] && game[0][0] == game[2][2] && game[0][0] != ' ')
        return game[0][0] == 'X' ? 1 : -1;
    if (game[0][2] == game[1][1] && game[0][2] == game[2][0] && game[0][2] != ' ')
        return game[0][2] == 'X' ? 1 : -1;;
    return 0;
}
// get score state
int state_value(GAMESTATE game)
{
    if(check_game_state(game)) return final_state_score(game);
     vector<GAMESTATE> move =valid_move(game);
     const int NO_VALUE=-100;
     char player =current_player(game);
     int result= NO_VALUE;
     for (auto m: move){
        int score = state_value(m);
        if (player =='X')
        {
            if (result==NO_VALUE|| result<score) 
            result =score ;
        }

    if (player =='O')
        {
            if (result==NO_VALUE|| result>score) 
            result =score ;
        }
     }
     return result;
}
// detect best move
pair <int,int > best_move (GAMESTATE game)
{
    //pair<int,int> result;
    vector<GAMESTATE> move= valid_move(game);
    char player =current_player(game);
    const int NO_VALUE =-100;
    int bestscore =NO_VALUE;
    GAMESTATE bestmoves;
    for (GAMESTATE m: move){
        int score = state_value(m);
        if (player =='X')
        {
            if (bestscore==NO_VALUE|| bestscore<score) 
           {
            bestscore= score;
            bestmoves= m;
           }
        }
    if (player =='O')
        {
            if (bestscore==NO_VALUE|| bestscore>score) 
            {bestscore= score;
             bestmoves= m;
            }
        }
    }
        for (int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if (bestmoves[i][j]!=game[i][j])
                    return make_pair(i,j);
            }
            
        }
        return make_pair(-1,-1);
}
// check input cordinate is valid
bool check_cordinate(int a,int b,GAMESTATE game)
{
    if (a<0||a>2||b<0||b>2)
    {
        return false ;
    }
   
    if (game[a][b]==' ')
    {
        return true;
    }
    else{
    return false;}

     return true;

}
int main()
{
   GAMESTATE game(3,vector<char>(3,' '));
   char Human;
   char current_player='X';
   cout << "WHICH IS YOUR CHOOSE BETWEEN 'X' AND 'O'?  ";
   cin >>Human;
    // check your chose and 'X' or'O is uppercase letter.
   if (Human!='X'&&Human!='O'){
   do{
    cout << "YOUR CHOOSE IS INVALID !!. PLESE CHOOSE AGAIN !"<<endl;
   cin >> Human;
   }
   while(Human!='X'&&Human!='O');}
   
  

   while(true){
   int a,b;
   if (Human==current_player)
   {
     cout << "ENTER YOUR CORDINATE ";
     cin >> a >>b;
     // check illegal move
        if (check_cordinate(a,b,game)==true){
        cout << "HUMAN CHOSE "<< a<<" "<<b<<endl;}
        else{
         do{
        cout << "PLEASE !! ENTER COEDINATE AGAIN ";
        cin >> a>>b;}
        while (check_cordinate(a,b,game)==false);
     }}
   else{
    // print machine move
        pair <int, int>  robot =best_move(game);
        a=robot.first;
        b=robot.second;
        cout <<"COMPUTER CHOSE "<<a<<" "<<b<<endl;
   }
    // print current game
    game =copy_move(a,b,game,current_player);
    print_game(game);
    current_player=current_player=='X'? 'O' :'X';
    //  response game result
    if (check_game_state(game)==true)
    {
        int s=final_state_score(game);
        if (s==1&& Human =='X'){
        cout << "HUMAN WIN !!";}
        else if (s==1&&Human=='O'){
        cout << "HUMAN LOSE !!";}
        else if(s==-1&&Human=='O'){
        cout<<"HUMAN WIN !!";}
        else if (s==-1 &&Human =='X'){
        cout <<"HUMAN LOSE !!";}
        else {
        cout << "DRAW!!";}
        break;
        
    }
   }
   return 0;
}




















