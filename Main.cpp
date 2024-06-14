#include <graphics.h>
#include <winbgim.h>
#include <windows.h>
#include <bits/stdc++.h>
 using namespace std;
 int width, height;
 int font = 30;
  int fonty = 10;
void draw();
 vector<vector<string>> location;

 vector<vector<string>> connection ;


vector<vector<string>> edges ;
vector<vector<int>> edges_int ;
vector<vector<string>> cost;
vector<vector<string>> path;
stack<string> path2;
vector<vector<int>> best;


int check(string s , int x,int y);
void home();

void initFullScreenWindow(int &width, int &height) {
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN)-23;
    initwindow(width, height, "Kishal", -3, -3);
}
double calculateAndNormalizeDistance(int x1, int y1, int x2, int y2) {
    // Calculate the differences
    int dx = x2 - x1;
    int dy = y2 - y1;

    // Calculate the distance using the Euclidean formula
    double distance = sqrt(pow(dx, 2) + pow(dy, 2));

    // Calculate the maximum possible distance (diagonal of a unit square)
    double maxDistance = sqrt(pow(width, 2) + pow(height, 2));


    // Normalize the distance
    double normalizedDistance = distance / maxDistance;

    return 1.15-normalizedDistance;
}
void clearScreen(int color,int i,int j) {
    int size1 = 7;
    int diff = 140;
    setfillstyle(SOLID_FILL, color);
    bar(i + 4 * size1 - diff, j + 19* size1 - diff, i + 21* size1 - diff, j + 29 * size1 - diff);
}

bool isInsideCircle(int x, int y, int centerX, int centerY, int radius) {
    // Calculate distance from the center of the circle
    int dx = x - centerX;
    int dy = y - centerY;
    return (dx * dx + dy * dy) <= (radius * radius);
}
void bus(int i,int j, float angle);
int intinput(int x, int y) {
    std::string input = "";
    up2:;
     setcolor(BLACK);
     outtextxy(x, y, "Invalid Input");
    char ch;
    int x1,y1;
    while (true) {
        if (kbhit()) {
            ch = getch();
            if (ch == 13) { // Enter key
                break;
            } else if (ch == 8) { // Backspace key
                if (!input.empty()) {
                        setcolor(BLACK);
                        outtextxy(x, y, (char*)input.c_str());
                    input.pop_back();
                }
            } else if (isdigit(ch)) {
                input += ch;
            }

            setcolor(WHITE);
            outtextxy(x, y, (char*)input.c_str());
        }

          if (ismouseclick(WM_LBUTTONDOWN)) {

            getmouseclick(WM_LBUTTONDOWN, x1, y1);

            if(x1>=1269 && x1<=1270+56 && y1>=29 && y1<=86)
            {
                return -1;
            }
            }
    }
     setcolor(BLACK);
                        outtextxy(x, y, (char*)input.c_str());
    if(input=="")
    {
        setcolor(RED);
     outtextxy(x, y, "Invalid Input");
     getch();
        goto up2;
    }
    else
    return std::stoi(input);
}

int intinput2(int x, int y,int stage) {
    std::string input = "";
    char ch;
    int x1,y1;
    while (true) {

        if (kbhit()) {

            ch = getch();

            if (ch == 13) { // Enter key
                break;
            } else if (ch == 8) { // Backspace key
                if (!input.empty()) {
                        setcolor(BLACK);
                        outtextxy(x, y, (char*)input.c_str());
                        if(input!="")
                            {
                                setcolor(BLACK);
                             setfillstyle(SOLID_FILL, BLACK);
                             if(stage==-1)
                            fillellipse(stoi(input),0,15,15);
                            else
                                 fillellipse(stage,stoi(input),15,15);
                            }
                    input.pop_back();
                }
            } else if (isdigit(ch)) {
                if(input!="")
                {
                setcolor(BLACK);
                 setfillstyle(SOLID_FILL, BLACK);

               if(stage==-1)
                    fillellipse(stoi(input),0,15,15);
                else
                    fillellipse(stage,stoi(input),15,15);
                }
                input += ch;
            }

            setcolor(WHITE);
            outtextxy(x, y, (char*)input.c_str());
            if(stage==-1)
            {
                if(input!="")
                {
                 setfillstyle(SOLID_FILL, WHITE);
                fillellipse(stoi(input),0,15,15);

                 setfillstyle(SOLID_FILL, BLACK);
                fillellipse(stoi(input),0,9,9);
                }
            }
            else{
                if(input!="")
                {
                 setfillstyle(SOLID_FILL, WHITE);
                fillellipse(stage,stoi(input),15,15);
                  setfillstyle(SOLID_FILL, BLACK);
                fillellipse(stage,stoi(input),9,9);
                }

            }
        draw();
        }

         if (ismouseclick(WM_LBUTTONDOWN)) {

            getmouseclick(WM_LBUTTONDOWN, x1, y1);

            if(x1>=1269 && x1<=1270+56 && y1>=29 && y1<=86)
            {
                return -1;
            }
            }

    }

     if(input!="" && stage==-1)
                {
                setcolor(BLACK);
                 setfillstyle(SOLID_FILL, BLACK);
                fillellipse(stoi(input),0,10,10);

                }
    else if(input!="" && stage!=-1)
                {
                 setfillstyle(SOLID_FILL, BLACK);
                fillellipse(stage,stoi(input),10,10);
                }

    return stoi(input);
}

void drawline(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    float angle = 0;
    double speed  = calculateAndNormalizeDistance( x0,  y0,  x1,  y1);
    int x00=x0 , y00=y0 ;
    setcolor(WHITE);
    while (true) {
       // cleardevice();
       clearScreen(BLACK,x0,y0);
       setcolor(WHITE);
       // line(x00,y00,x1,y1);
       draw();


            bus(x0,y0,angle);

             angle += 0.1;
            delay(1);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

}

void bus(int i, int j, float angle) {
    int size1 = 7;
    int diff = 140;

    // Draw bus body
    setcolor(WHITE);
    rectangle(i + 5 * size1 - diff, j + 20 * size1 - diff, i + 20 * size1 - diff, j + 25 * size1 - diff);

    // Draw windows
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(i + 6 * size1 - diff, j + 21 * size1 - diff, i + 9 * size1 - diff, j + 24 * size1 - diff);
    bar(i + 10 * size1 - diff, j + 21 * size1 - diff, i + 13 * size1 - diff, j + 24 * size1 - diff);

    // Draw wheels
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillellipse(i + 8 * size1 - diff, j + 27 * size1 - diff, 10, 10); // Left wheel
    fillellipse(i + 17 * size1 - diff, j + 27 * size1 - diff, 10, 10); // Right wheel

    // Draw rotating spokes on wheels
    int wheel_radius = 10;
    for (int k = 0; k < 2; k++) {
        int cx = i + (8 + 9 * k) * size1 - diff;
        int cy = j + 27 * size1 - diff;
        for (int n = 0; n < 4; n++) {
            int x1 = cx + wheel_radius * cos(angle + n * M_PI / 2);
            int y1 = cy + wheel_radius * sin(angle + n * M_PI / 2);
            int x2 = cx + wheel_radius * cos(angle + n * M_PI / 2 + M_PI);
            int y2 = cy + wheel_radius * sin(angle + n * M_PI / 2 + M_PI);
            line(cx, cy, x1, y1);
            line(cx, cy, x2, y2);
        }
    }
}

pair<int,int> digits(string s)
{int i;
    for( i=0;i<location.size();i++)
    {
        if(location[i][0]==s)
            break;
    }
    return {stoi(location[i][1]),stoi(location[i][2])};
}

void fix (string a,string b,int xmain,int ymain,int xmain2,int ymain2)
{
    for(int i=0;i<edges.size();i++)
    {
        if((a==edges[i][0] && b==edges[i][1]) || (a==edges[i][1] && b==edges[i][0]) )
        {
                return ;
        }
    }

    edges.push_back({a,b});
    edges_int.push_back({xmain,ymain,xmain2,ymain2});
}

void fix2()
{
     for(int i=0;i<connection.size();i++)
   {
       int xmain=digits(connection[i][0]).first,ymain=digits(connection[i][0]).second;

        for(int j=1;j<connection[i].size();j++)
       {
           int xmain2=digits(connection[i][j]).first,ymain2=digits(connection[i][j]).second;

            fix(connection[i][0],connection[i][j],xmain,ymain,xmain2,ymain2);

       }

   }
}

void draw()
{
     home();
    setfillstyle(SOLID_FILL, YELLOW);
    for(int i=0 ; i<edges_int.size() ;i++)
    {
    //  cout<<edges_int[i][0]<<edges_int[i][1]<<edges_int[i][2]<<edges_int[i][3]<<endl;
        line(edges_int[i][0],edges_int[i][1],edges_int[i][2],edges_int[i][3]);

    }


 for(int i =0;i<location.size();i++)
    {
        int temp = stoi(location[i][1]) , temp2 = stoi(location[i][2]);

        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(temp,temp2,10,10);
        setcolor(WHITE);

        outtextxy(temp+28, temp2+4,(char*)location[i][0].c_str());
    }
}

string stringinput(int x, int y) {
    std::string input = "";
    int x1, y1;
    char ch;
    while (true) {
        if (kbhit()) {
            ch = getch();
            if(ch == ' ')
                ch='_';
            if (ch == 13) { // Enter key
                break;
            } else if (ch == 8) { // Backspace key
                if (!input.empty()) {
                    setcolor(BLACK);
                    outtextxy(x, y, (char*)input.c_str());
                    input.pop_back();
                }
            } else if (isprint(ch)) { // Check if the character is printable
                input += ch;
            }

            setcolor(WHITE);
            outtextxy(x, y, (char*)input.c_str());

        }
        if (ismouseclick(WM_LBUTTONDOWN)) {

            getmouseclick(WM_LBUTTONDOWN, x1, y1);

            if(x1>=1269 && x1<=1270+56 && y1>=29 && y1<=86)
            {
                return "error";
            }

            for(int i=0;i<location.size();i++)
            {
                int x2=stoi(location[i][1]),y2=stoi(location[i][2]);

                if(isInsideCircle(x1,y1,x2,y2,10))
                {
                    setcolor(BLACK);
                    outtextxy(x, y, (char*)input.c_str());
                    input=location[i][0];
                    setcolor(WHITE);
                    outtextxy(x, y, (char*)input.c_str());
                    break;
                }

            }
        }
    }

    return input;
}


string directcost(string a , string b)
{

   int x1,x2,y1,y2;
   for(int i =0;i<location.size();i++)
    {
        if(location[i][0]==a) {
            x1=stoi(location[i][1]);
            y1=stoi(location[i][2]);
        }
        if(location[i][0]==b) {
            x2=stoi(location[i][1]);
            y2=stoi(location[i][2]);
        }
    }
    int dx = x2 - x1;
    int dy = y2 - y1;


    return to_string(sqrt(pow(dx, 2) + pow(dy, 2)));
}
void decision()
{
    int n = cost.size();
    for(int k = 0 ; k<n ;k++){

    int mini_int=INT_MAX, index;
    string mini;
        for(int i=0;i<cost.size();i++)
        {
            if(stoi(cost[i][1]) < mini_int)
            {
                mini_int = stoi(cost[i][1]);
                mini = cost[i][0] ;
                index = i;
            }
        }

    path.push_back({mini,to_string(mini_int)});

    int temp;
    for(temp=0;temp<connection.size();temp++)
        if(connection[temp][0]==mini) break;

     for(int i=1; i<connection[temp].size() ;i++)
        {


            int connection_cost;
            int j,flag=1;
            for(j=0;j<cost.size();j++){
                if(cost[j][0]==connection[temp][i])
                {
                    flag=0;
                    break;
                }
            }
            if(flag==1) continue;
            connection_cost = stoi(cost[j][1]);

            int new_cost = stoi(directcost(connection[temp][i],connection[temp][0])) + mini_int;

            if(new_cost < connection_cost )
            {
                cost[j][1] = to_string(new_cost);
            }

        }


       auto it = cost.begin() + index ;

        cost.erase(it);

    }


}


void back_path(string goal)
{string back2=path2.top() ;

    while(path2.top() != goal)
    {
        string current = path2.top() ;
    int temp;
    for(temp=0;temp<connection.size();temp++)
        if(connection[temp][0]==current) break;

    int mini_int = INT_MAX ;
    string mini;
    for(int i=1; i<connection[temp].size() ;i++)
        {int j;
            if(connection[temp][i]==back2) continue ;
            for(j=0;j<path.size();j++)
                    if(path[j][0]==connection[temp][i]) break ;
            if(stoi(path[j][1])<mini_int)
            {
                mini_int = stoi(path[j][1]) ;
                mini = path[j][0] ;

            }

        }
       path2.push(mini);
       back2 = mini ;
    }

}

void loaddata()
{

location.clear();
connection.clear();
    fstream myfile("location.txt");
    string data;
    while(getline(myfile,data))
    {int i=0;
    string a="";
    string b="";
    string c="";
        while(data[i]!=' '){a+=data[i];i++;};
        i++;
        while(data[i]!=' '){b+=data[i];i++;};
        i++;
        while(data[i]!=' '){c+=data[i];i++;};

        location.push_back({a,b,c});
    }

    myfile.close();
    fstream myfile2("connection.txt");
    while(getline(myfile2,data))
    {
        vector<string> temp;
        string temp2="";
        for(int i=0;i<data.size();i++)
        {
            if(data[i]==' ')
            {
                temp.push_back(temp2);
                temp2="";
            }
            else
            temp2+=data[i];

        }
        connection.push_back(temp);
    }
    myfile2.close();
}
void reloaddata()
{
ofstream myfile("location.txt", std::ofstream::out | std::ofstream::trunc);
    for(int i=0;i<location.size();i++)
    {
        myfile<<location[i][0]<<" "<<location[i][1]<<" "<<location[i][2]<<" ";
        if(i<location.size()-1) myfile<<"\n";
    }
    myfile.close();
    ofstream myfile2("connection.txt",std::ofstream::out | std::ofstream::trunc);
    for(int i=0;i<connection.size();i++)
    {
        for(int j=0;j<connection[i].size();j++)
        {
            myfile2<<connection[i][j]<<" ";
        }
        if(i<connection.size()-1) myfile2<<"\n";
    }
    myfile2.close();
}
void mouse(string &x,string &y,string current)
{
    int x1,y1;
    int mouseX = 0, mouseY = 0;
    while(1)
    {

        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(mouseX, mouseY, 10, 10);

        if (ismouseclick(WM_MOUSEMOVE)) {
            getmouseclick(WM_MOUSEMOVE, mouseX, mouseY);
             if (mouseY < 150) mouseY = 150;\
                draw();
            if(mouseX>=0 && mouseX<=110 && mouseY>=660 && mouseY<=760)
            {
                mouseX=110;
                mouseY=660;
            }// readimagefile("logo2.bmp",  5,660,  110,760);
        }
         if (ismouseclick(WM_LBUTTONDOWN)) {

            getmouseclick(WM_LBUTTONDOWN, x1, y1);

            if(x1>=1269 && x1<=1270+56 && y1>=29 && y1<=86)
            {
                x = "error" ;
                y= "error" ;
                return;
            }


            setcolor(YELLOW);
            setfillstyle(SOLID_FILL, YELLOW);
            fillellipse(mouseX, mouseY, 10, 10);
            setcolor(WHITE);

             outtextxy(x1+10, y1+10, "Press Enter to confirm location .");
             int ch2;

             while(1)
             {
                 if(kbhit())
                 {
                     ch2 = getch();
                     break;
                 }
                  if (ismouseclick(WM_LBUTTONDOWN))
                    {

                        getmouseclick(WM_LBUTTONDOWN, x1, y1);

                        if(x1>=1269 && x1<=1270+56 && y1>=29 && y1<=86)
                        {
                            x = "error" ;
                            y= "error" ;
                            return;
                        }
                    }
             }


             if(ch2==13) {
                setcolor(BLACK);
                 outtextxy(x1+10, y1+10, "Press Enter to confirm location .");

                 draw();
                 setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                fillellipse(mouseX, mouseY, 10, 10);
                 setcolor(WHITE);
                outtextxy(x1+10, y1+10, (char*)current.c_str());
                 break;
             }
             setcolor(BLACK);
             outtextxy(x1+10, y1+10, "Press Enter to confirm location .");


            }

        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(mouseX, mouseY, 10, 10);

        delay(10);
    }

    x=to_string(x1);
    y=to_string(y1);
}



void adddata()
{
    string current,x,y;
    cleardevice();
    setcolor(WHITE);
    readimagefile("logo2.bmp",  5,660,  110,760);
    setcolor(DARKGRAY);
    outtextxy(1100, 700 ,"Press Enter to Continue ...");
    draw();
    int flag=0;


     do{


            flag=0;
    setcolor(YELLOW);
    outtextxy(10, 10, "Name of location you want to add : ");
    current=stringinput(305,10);


    for(int i=0;i<location.size();i++)
    {
        if(location[i][0]==current)
        {
            flag=1;
            setcolor(BLACK);
            outtextxy(305,10, (char*)current.c_str());
            setcolor(RED);
            outtextxy(305,10, "This Location Already Exists on the Map");
           getch();
           setcolor(BLACK);
            outtextxy(305,10, "This Location Already Exists on the Map");
            break;
        }
    }
    }while(flag==1);


    if(current=="error")
       return ;


 setcolor(YELLOW);

    int menu=0;


    outtextxy(10, 40, "Choose appropriate input type to add coordinates :");
    setcolor(WHITE);
    outtextxy(10, 65, "Mouse");
    outtextxy(120,  65, "Keyboard");
    setcolor(WHITE);
    rectangle(5+(menu*100),65,110+(menu*100),90);
    char ch;
    int x1,y1;
    while(1){

      if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x1, y1);
            if(x1>=1269 && x1<=1270+56 && y1>=29 && y1<=86)
            {
                return ;
            }
             if(x1>=5 && x1<=110 && y1>=65 && y1<=90)
            {
                 setcolor(BLACK);
                rectangle(5+(1*100),65,110+(1*100),90);
                setcolor(WHITE);
                rectangle(5+(0*100),65,110+(0*100),90);
                menu=0;

                break;

            }
            else if (x1>=5+100 && x1<=110+100 && y1>=65 && y1<=90)
            {
                 setcolor(BLACK);
                rectangle(5+(0*100),65,110+(0*100),90);
                setcolor(WHITE);
                rectangle(5+(1*100),65,110+(1*100),90);
                menu=1;
                break;
            }

            }

      if(kbhit()){
            ch = getch();
      if(ch==75)//left menu=0
        {
            setcolor(BLACK);
            rectangle(5+(menu*100),65,110+(menu*100),90);
            if(menu==1) menu=0;
            else menu=1;
             setcolor(WHITE);
            rectangle(5+(menu*100),65,110+(menu*100),90);
        }
    else if(ch==77)//right menu=1;
        {
            setcolor(BLACK);
           rectangle(5+(menu*100),65,110+(menu*100),90);
            if(menu==0) menu = 1;
            else menu=0;
             setcolor(WHITE);
            rectangle(5+(menu*100),65,110+(menu*100),90);
        }
    else if(ch==13)//enter
        {
            break;
        }
      }

    }

    if(menu==1){
   setcolor(YELLOW);
    outtextxy(10, 100, "X Co-ordinates :  ");
    int temp=intinput2(160,100,-1);                             // invalid error detection
    if(temp==-1)
       return ;
   x=to_string(temp);
    setcolor(YELLOW);
    outtextxy(10, 130, "Y Co-ordinates :  ");

    temp = intinput2(160,130,temp);
     if(temp==-1)
       return ;
    y=to_string(temp);
    }
    else
    {
        mouse(x,y,current);
        if(x=="error" || y=="error")
            return ;
        setcolor(YELLOW);
    outtextxy(10, 100, "X Co-ordinates :  ");
    setcolor(WHITE);
    outtextxy(160,100, (char*)x.c_str());
     setcolor(YELLOW);
    outtextxy(10, 130, "Y Co-ordinates :  ");
     setcolor(WHITE);
    outtextxy(160,130, (char*)y.c_str());
    }


 setcolor(YELLOW);
        int n;
     outtextxy(10, 160, "Enter the Number of location you want to connect : ");
     n=intinput(10, 185);
    if(n==-1)
       return ;
    setcolor(BLACK);
     outtextxy(10, 160, "Enter the Number of location you want to connect : ");
      setcolor(YELLOW);
    outtextxy(10, 160, "Enter the Name of location you want to connect :");

    vector<string> v;
    v.push_back(current);



    for(int i=1;i<=n;i++){
            setcolor(WHITE);
    outtextxy(10, 185+((i-1)*20), (char*)to_string(i).c_str());
    outtextxy(20, 185+((i-1)*20), ":");

    string temp2;
    do{
     temp2= stringinput(30,185+((i-1)*20));
     if(temp2=="error")
       return ;
    }while(check(temp2,30,185+((i-1)*20)));


    int j;
    for(j=0;j<location.size();j++)
        if(location[j][0]==temp2)break;

    setcolor(YELLOW);
    line(stoi(x),stoi(y),stoi(location[j][1]),stoi(location[j][2]));
    v.push_back(temp2);
    }

     setcolor(GREEN);
    outtextxy(10, 250+(20*n-1), "Press Backspace key to delete information");
    outtextxy(10, 280+(20*n-1), "Press Space key to add new location");
    outtextxy(10, 310+(20*n-1), "Press Enter key to save location");
    char dec;

    while(1)
    {
        if(kbhit())
        {
            dec = getch();
            break;
        }
         if (ismouseclick(WM_LBUTTONDOWN)) {

            getmouseclick(WM_LBUTTONDOWN, x1, y1);

            if(x1>=1269 && x1<=1270+56 && y1>=29 && y1<=86)
            {
                return ;
            }
            }
    }
    if(dec==8)
        goto up;



     for(int i=1;i<v.size();i++){
            int j;
         for(j=0;j<connection.size();j++)
            {

            if(connection[j][0]==v[i])break;
            }
        connection[j].push_back(current);


    }
    connection.push_back(v);
    location.push_back({current,x,y});
    reloaddata();
    loaddata();
    fix2();
    if(dec==' ')
        adddata();
    return ;
    up:
        adddata();
}


void removedata()
{
    cleardevice();
    draw();

    setcolor(YELLOW);
    outtextxy(10, 10, "Enter Name of location you want to delete from map : ");

    string in;
    do{
            readimagefile("logo2.bmp",  5,660,  110,760);
            setcolor(DARKGRAY);
            outtextxy(1100, 700 ,"Press Enter to Continue ...");
     in= stringinput(10,40);
     if(in=="error")
       return ;
    }while(check(in,10,40));

    for(int i=0;i<location.size();i++)
    {
        if(location[i][0]==in)
        {
            auto it = location.begin() + i ;
            location.erase(it);
            break;
        }
    }

     for(int i=0;i<connection.size();i++)
    {
        if(connection[i][0]==in)
        {
            auto it = connection.begin() + i ;
            connection.erase(it);
            i--;
        }
       else{
         for(int j=1;j<connection[i].size();j++)
        {
            if(connection[i][j]==in)
            {
                auto it = connection[i].begin() + j ;
                connection[i].erase(it);
                break;
            }
        }
       }
    }


    reloaddata();
    loaddata();
    edges.clear();
    edges_int.clear();
    fix2();

    setcolor(YELLOW);
    outtextxy(10, 10, "Enter Name of location you want to delete from map : ");
cleardevice();
setcolor(YELLOW);
    outtextxy(10, 10, "Enter Name of location you want to delete from map : ");
    setcolor(WHITE);
    outtextxy(10, 40, (char*)in.c_str());
    draw();
    readimagefile("logo2.bmp",  5,660,  110,760);
    setcolor(DARKGRAY);
    outtextxy(1100, 700 ,"Press Enter to Continue ...");
    setcolor(YELLOW);
     outtextxy(10, 70, "Press the Space key to delete another location.");
    char re;
    int x,y;
    while(1)
    {
        if(kbhit())
        {
           re=getch();
           break;
        }
         if (ismouseclick(WM_LBUTTONDOWN)) {


            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(x>=1269 && x<=1270+56 && y>=29 && y<=86)
            {
                return ;
            }
            }
    }

    if(re==' ')
        removedata();

}


int check(string s , int x,int y)
{
    for(int i=0;i<location.size();i++)
    {
        if(location[i][0]==s)
            return 0;
    }
    setcolor(BLACK);
     outtextxy(x, y, (char*)s.c_str());
     setcolor(RED);
      outtextxy(x,y, "Invalid Input Re-enter");

      getch();
     setcolor(BLACK);
      outtextxy(x,y, "Invalid Input Re-enter");
     return 1;
}


int addstop()
{
    int menu=0;
    while(1){
    setcolor(YELLOW);
    outtextxy(10, 70, "Do you want to add stop : ");
    outtextxy(10, 95, "Yes");
    outtextxy(100, 95, "No");
    setcolor(RED);
    rectangle(5+(menu*75),95,70+(menu*75),120);
    char ch;
    int x,y;
    while(1)
    {
        if(kbhit())
        {
           ch=getch();
           break;
        }
         if (ismouseclick(WM_LBUTTONDOWN)) {

             delay(150);
            getmouseclick(WM_LBUTTONDOWN, x, y);

             if(x>=1269 && x<=1270+56 && y>=29 && y<=86)
            {
                return -1;
            }


            if(x>=5 && x<=70 && y>=95 && y<=120)
            {
                 setcolor(BLACK);
                rectangle(5+(1*75),95,70+(1*75),120);
                setcolor(RED);
                rectangle(5+(0*75),95,70+(0*75),120);
                return 1;

            }
            else if (x>=5+75 && x<=70+75 && y>=95 && y<=120)
            {
                 setcolor(BLACK);
                rectangle(5+(0*75),95,70+(0*75),120);
                setcolor(RED);
                rectangle(5+(1*75),95,70+(1*75),120);
                return 0;
            }
            }
    }

    if(ch==75)//left
    {
        setcolor(BLACK);
        rectangle(5+(menu*75),95,70+(menu*75),120);
        if(menu==1) menu=0;
        else menu=1;
    }
    else if(ch==77)//right
    {
        setcolor(BLACK);
       rectangle(5+(menu*75),95,70+(menu*75),120);
        if(menu==0) menu = 1;
        else menu=0;
    }
    else if(ch==13)//enter
    {
        if(menu==0) return 1;
        else return 0;
    }
    }
    return 0;
}

void home() {

    int RECT_WIDTH = 55;   // Width of each rectangle
    int RECT_HEIGHT = 7;   // Height of each rectangle
    int RADIUS = 3;         // Radius of the rounded curve
    int x,y;
    setcolor(WHITE);
    for (int i = 0; i < 3; ++i) {
         x = 1270  ; // X position calculation
         y = 30+ i * 13; // Y position (fixed)

        // Draw the rounded rectangle with white fill color
        setfillstyle(SOLID_FILL, WHITE);
        bar(x + RADIUS, y, x + RECT_WIDTH, y + RECT_HEIGHT);  // Main rectangle
        bar(x, y + RADIUS, x + RADIUS, y + RECT_HEIGHT - RADIUS);  // Left rounded curve
        fillellipse(x + RADIUS, y + RADIUS, RADIUS, RADIUS);  // Top-left curve
        fillellipse(x + RADIUS, y + RECT_HEIGHT - RADIUS, RADIUS, RADIUS);  // Bottom-left curve



    }

        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(x , y + 12, "Menu");
          settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
}


void setWindowTitle(const char* title) {
    // Get the window handle created by initgraph
    HWND hwnd = GetForegroundWindow();
    // Set the window title
    SetWindowText(hwnd, title);
}


 void myinfo()
 {

   int maxX = getmaxx();
    int maxY = getmaxy();

    // Clear screen with black color
    setbkcolor(BLACK);
    cleardevice();

    // Set text properties
    settextstyle(BOLD_FONT, HORIZ_DIR, 4); // Larger font size and bold
    setcolor(WHITE); // Text color (white on black background)

    // Define thank you message
    char message1[] = "Thank you for using my app!";
    char message2[] = "Your support means a lot to me.";
    char message3[] = "Connect with me,";
    char message4[] = "Kishal Shah,";
    char message5[] = "on LinkedIn @kishalshah to stay updated and connected.";
    char message6[] = "I look forward to bringing you more value in the future.";

    // Calculate text dimensions
    int textWidth1 = textwidth(message1);
    int textWidth2 = textwidth(message2);
    int textWidth3 = textwidth(message3);
    int textWidth4 = textwidth(message4);
    int textWidth5 = textwidth(message5);
    int textWidth6 = textwidth(message6);

    // Calculate center coordinates for each line
    int centerX1 = (maxX - textWidth1) / 2;
    int centerX2 = (maxX - textWidth2) / 2;
    int centerX3 = (maxX - textWidth3) / 2;
    int centerX4 = (maxX - textWidth4) / 2;
    int centerX5 = (maxX - textWidth5) / 2;
    int centerX6 = (maxX - textWidth6) / 2;

    // Display text with appropriate formatting
    outtextxy(centerX1, 100, message1);
    outtextxy(centerX2, 150, message2);
    outtextxy(centerX3, 250, message3);
    setcolor(YELLOW);
    outtextxy(centerX4, 300, message4);
    setcolor(WHITE);
    outtextxy(centerX5, 350, message5);
    outtextxy(centerX6, 450, message6);


int x,y;
    while(1)
    {
        if(kbhit())
        {
           char ch= getch();
           return;
        }
         if (ismouseclick(WM_LBUTTONDOWN)) {
                getmouseclick(WM_LBUTTONDOWN, x, y);
         return;
         }
    }


 }

int main() {


    initFullScreenWindow(width, height);
    loaddata();
    setbkcolor(BLACK); // Dark background
    string current , goal;


    char ch;
    char ch_menu;

    int menu=0;
    char arrow;
    int flag=0;

    int x, y;
    int mainx=400,mainy=300;

    do{

    flag=0;

    fix2();
    cleardevice();
     setcolor(WHITE);
 readimagefile("logo2.bmp",  484,10,  884,310);
      setWindowTitle("Main Menu");
     setcolor(COLOR(255, 140, 0));
     settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(100+mainx, 50+mainy, "Main Menu");


    rectangle(90+mainx,145+(50*menu)+mainy,500+mainx,(50*menu)+195+mainy);
    // Option settings

    setcolor(DARKGRAY);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
    if(menu==0){ setcolor(WHITE);};
    outtextxy(100+mainx, 150+mainy, "Map");
    setcolor(DARKGRAY);

    if(menu==1){ setcolor(WHITE);};
    outtextxy(100+mainx, 200+mainy, "Add Location");
    setcolor(DARKGRAY);

    if(menu==2){ setcolor(WHITE);};
    outtextxy(100+mainx, 250+mainy, "Delete Location");
    setcolor(DARKGRAY);

    if(menu==3){ setcolor(WHITE);};
    outtextxy(100+mainx, 300+mainy, "Exit");
    setcolor(DARKGRAY);
     settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
      outtextxy(1100, 700, " - Created by Kishal Shah");



    while(1)
    {
        if(kbhit()){

        arrow = getch();
        if(arrow==80)
        {
            if(menu<3)
            menu++;
            else menu=0;
            break;
        }
        else if(arrow==72)
        {
            if(menu>0)
            menu--;
            else menu=3;
            break;
        }
        else if(arrow==13)
        {
            flag=1;
            delay(150);
            break;
        }


        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            // Get the coordinates of the mouse click
             delay(150);
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(x>=90+mainx &&x<=500+mainx && y>=145+mainy && y<=195+mainy)
            {
                menu=0;
                flag=1;
            }
            else if(x>=1100 && x<=1330 && y>=700 && y<=730)
            {
                myinfo();
                goto error;

            }

            else if(x>=90+mainx &&x<=500+mainx && y>=145+50+mainy && y<=195+50+mainy)
            {
                menu=1;
                flag=1;
            }
            else if(x>=90+mainx &&x<=500+mainx && y>=145+(2*50)+mainy && y<=195+(2*50)+mainy)
            {
                menu=2;
                flag=1;
            }
            else if(x>=90+mainx &&x<=500+mainx && y>=145+(3*50)+mainy && y<=195+(3*50)+mainy)
            {
                menu=3;
                flag=1;

            }
            break;
        }
    }


    if(flag==1)
    {
         settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

        if(menu==3) return 0;
    else if(menu==1)
        {
            setWindowTitle("Add Location");
            adddata();

    }
     else if(menu==2)
        {

            setWindowTitle("Delete Location");
            removedata();
        }

    else if(menu==0){
        setWindowTitle("Maps");
            cleardevice();
    do{

    draw();


    do{

     setcolor(DARKGRAY);
    outtextxy(1100, 700 ,"Press Enter to Continue ...");
    readimagefile("logo2.bmp",  5,660,  110,760);
    home();

    setcolor(YELLOW);
    outtextxy(10, 10, "Current Location : ");
    current=stringinput(140+font,10);
    if(current=="error")
        goto error;
    }while(check(current,140+font,10));

    do{
    setcolor(YELLOW);
    outtextxy(10, 40, "Goal Location : ");
    goal=stringinput(140+font,40);
    if(goal=="error")
        goto error;
    }while(check(goal,140+font,40));



    int stop1 = addstop();
    if(stop1==-1)
        goto error;
    string stop;
    string currect_back = current;
    string goal_back = goal;
    if(stop1==1)
    {
        setcolor(YELLOW);
        outtextxy(0, 140, "Stop Location : ");
        do{
        stop=stringinput(130+font,140);
        if(stop=="error")
        goto error;
        }while(check(stop,130+font,140));
    }

    //drawline(600,600,600,200);


    //  --- initial step ---

    if(stop1==1)
    {
        goal = stop;
        goto skip;
    }
    skip2:;
    if(stop1==1)
    {
        current = stop;
        goal = goal_back;
        stop1=0;
    }



    skip:;
    int temp;
    for(temp=0;temp<connection.size();temp++)
        if(connection[temp][0]==current) break;

    for(int i=1;i<connection[temp].size();i++)
    {
        cost.push_back({connection[temp][i],directcost(current,connection[temp][i])});
    }

    for(int i=0;i<location.size();i++)
    {
        for(int j=0;j<cost.size();j++)
            if(cost[j][0]==location[i][0]) goto down;
        if(location[i][0] == current) goto down;

        cost.push_back({location[i][0],to_string(INT_MAX)});
        down:;

    }

    path.push_back({current,"0"});

    decision();
/*
  for(int i=0;i<path.size();i++)
        cout<<path[i][0]<<path[i][1]<<endl;*/


    path2.push(goal);

    back_path(current);


    while(path2.size()>1)
        {
            string a,b;
            a=path2.top();
            path2.pop();
            b=path2.top();
            int i;
            for(i=0;i<location.size();i++)
                if(location[i][0]==a) break;
            int x1 =stoi( location[i][1]);
            int y1 =stoi( location[i][2]);

             for(i=0;i<location.size();i++)
                if(location[i][0]==b) break;
            int x2 =stoi( location[i][1]);
            int y2 =stoi( location[i][2]);

            best.push_back({x1,y1,x2,y2});


        }

       // animation

       for(int i=0;i<best.size();i++)
       {
           drawline(best[i][0],best[i][1],best[i][2],best[i][3]);
       }





        cost.clear();
        path.clear();
        path2.pop();
        best.clear();

        if(stop1==1)
            goto skip2;

        outtextxy(10, 170, "Enter Escape Key to Exit  ");

        int x1,y1;
        while (true) {
        if (kbhit()) {
            ch = getch();
            break;
            }

             if (ismouseclick(WM_LBUTTONDOWN)) {

            getmouseclick(WM_LBUTTONDOWN, x1, y1);

            if(x1>=1269 && x1<=1270+56 && y1>=29 && y1<=86)
            {
                goto error ;
            }
            }
            }
            cleardevice();
       }while(ch!=27);
    }
    else outtextxy(0, 450, " !! Invalid Input !!");

    flag=0;
    }
    error:;
    }while(1);
    closegraph();
    return 0;
}


// when you add new location undate the connect in other location connection as well
