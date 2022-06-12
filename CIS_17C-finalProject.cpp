/* 
 * File:   CIS_17C-finalProject.cpp
 * Author: Yan
 *
 * Created on June 12, 2022, 10:36 AM
 */
#include "createmaze.h"

const char PATH = ' ';
const char WALL = '*';
const char FLAG = 'F';
const char PEPOLE = '@';

int trim_left(string &somestr);
int trim_right(string &somestr);
int trim(string &somestr);
int str_split (string strObject, vector<string>& vecResult,string strMark);

int CMazeMap::init()
{
	for(int i = 0;i < mazeSize;i++ )
	{
		for(int j = 0;j < mazeSize; j++)
		{
			map[i][j].x = i;
			map[i][j].y = j; 
			map[i][j].value = WALL;
		}
	}
	return 0;
}

int CMazeMap::DFS_generator(int x,int y)
{		
    int dir[4][2] = { 
    	{ 1,0 },
    	{ -1,0 },
    	{ 0,-1 },
    	{ 0,1 } 
    };
    
    for (int k = 0; k < 4; k++) 
	{
		int r = rand() % 4;
		int temp = dir[0][0];
		dir[0][0] = dir[r][0];
		dir[r][0] = temp;
		temp = dir[0][1];
		dir[0][1] = dir[r][1];
		dir[r][1] = temp;
	} 
	
	map[x][y].value = PATH;
    for (int i = 0; i < 4; ++i)
    {
        if (x + 2 * dir[i][0] >= 1 
        	&& x + 2 * dir[i][0] <= mazeSize - 2 
        	&& y + 2 * dir[i][1] >= 1 
        	&& y + 2 * dir[i][1] <= mazeSize - 2
            && map[x + 2 * dir[i][0]][y + 2 * dir[i][1]].value == WALL)
        {
            map[x + dir[i][0]][y + dir[i][1]].value = PATH;
            DFS_generator(x + 2 * dir[i][0], y + 2 * dir[i][1]);
        }
    }
    
    return 0;
}

int CMazeMap::DFS()
{
	int x = (rand() % (mazeSize - 2) + 1) | 1;
	int y = (rand() % (mazeSize - 2) + 1) | 1;
	stack<SBox> rode;
	
	int dir[4][2] = { 
		{ 1,0 },
		{ -1,0 },
		{ 0,-1 },
		{ 0,1 } 
	};
	
	rode.push(map[x][y]);
	while (!rode.empty())
	{
		if(map[x][y].value != PATH)
		{
			map[x][y].value = PATH;
		}
		
		for (int k = 0; k < 4; k++) 
		{
			int r = rand() % 4;
			int temp = dir[0][0];
			dir[0][0] = dir[r][0];
			dir[r][0] = temp;
			temp = dir[0][1];
			dir[0][1] = dir[r][1];
			dir[r][1] = temp;
		} 
		
        int i = 0;
        for (; i < 4; i++)
        {
            if (x + 2 * dir[i][0] >= 1 
            	&& x + 2 * dir[i][0] <= mazeSize - 2 
            	&& y + 2 * dir[i][1] >= 1 
            	&& y + 2 * dir[i][1] <= mazeSize - 2
                && map[x + 2 * dir[i][0]][y + 2 * dir[i][1]].value == WALL)
            {
                map[x + dir[i][0]][y + dir[i][1]].value = PATH;
                x += 2 * dir[i][0];
                y += 2 * dir[i][1];
                rode.push(map[x][y]);
                break;
            }
        }
        if (i == 4) 
        {
        	rode.pop();
        }
        
        if (!rode.empty()) 
        {
        	x = rode.top().x;
        	y = rode.top().y;
        }
	}
	
	return 0;
}

int CMazeMap::Prim_generator()
{
    for (int i = 1; i <= mazeSize - 2; i += 2)
    {
        for (int j = 1; j <= mazeSize - 2; j += 2)
        {
            map[i][j].value = PATH;
        }
    }
   
    std::vector<SBox> vp;
  
   	int x = (rand() % (mazeSize - 2) + 1) | 1;
	int y = (rand() % (mazeSize - 2) + 1) | 1;
    // å°†å‘¨å›´å¢™å…¥æ ˆ
    if (x - 1 >= 2) 
    {	
    	vp.push_back(map[x - 1][y]);
    }
    if (x + 1 <= mazeSize - 3) 
    {
    	vp.push_back(map[x + 1][y]);
    }
    if (y - 1 >= 2) 
    {
    	vp.push_back(map[x][y - 1]);
    }
    if (y + 1 <= mazeSize - 3) 
    {
    	vp.push_back(map[x][y + 1]);
    }
    	

    map[x][y].value = FLAG;
    int pos = 0;

    while (!vp.empty())
    {
      
        pos = rand() % vp.size();
        x = vp[pos].x;
        y = vp[pos].y;
     
        bool flag = false;
       
        if (map[x + 1][y].value == WALL)
        {
            if (map[x][y - 1].value != map[x][y + 1].value)
            {
                map[x][y].value = PATH;
                if (map[x][y - 1].value == FLAG) 
                { 
                	map[x][y + 1].value = FLAG;
                	++y; 
                }
                else 
                { 
                	map[x][y - 1].value = FLAG;
                	--y; 
                }
                flag = true;
            }
        }
        else
        {
            if (map[x - 1][y].value != map[x + 1][y].value)
            {
                map[x][y].value = PATH;
                // å¯¹æ–°åŠ å…¥çš„é€šè·¯è¿›è¡Œæ ‡è®°
                if (map[x - 1][y].value == FLAG) 
                { 
                	map[x + 1][y].value = FLAG; 
                	++x; 
                }
                else 
                { 
                	map[x - 1][y].value = FLAG; 
                	--x; 
                }
                flag = true;
            }
        }
      
        if (flag)
        {
            if (x - 1 >= 2 && map[x - 1][y].value == WALL) 
            {
            	vp.push_back(map[x - 1][y]);
            }
            if (x + 1 <= mazeSize - 3 && map[x + 1][y].value == WALL) 
            {
            	vp.push_back(map[x+1][y]);
            }
            if (y - 1 >= 2 && map[x][y - 1].value == WALL) 
            {
            	vp.push_back(map[x][y - 1]);
            }	
            if (y + 1 <= mazeSize - 3 && map[x][y + 1].value == WALL) 
            {
            	vp.push_back(map[x][y + 1]);
            }  	
        }
       
        vp[pos] = *(vp.end() - 1);
        vp.pop_back();
    }
    // å°†è¢«æ ‡è®°çš„é€šè·¯è¿˜åŽŸ
    for (int i = 1; i < mazeSize -1; i++)
    {
    	for (int j = 1; j < mazeSize -1; j++)
    	{
    		if (map[i][j].value == FLAG)
    			 map[i][j].value = PATH;
    	}
    }
    
    return 0;        
}

int CMazeMap::createMaze()
{
	start.x = 0;
	start.y = 1;
	start.value = PATH;
	map[0][1].value = PATH;
	pepole.x = 0;
	pepole.y = 1;
	pepole.value = PEPOLE;
	end.x = mazeSize - 1;
	end.y = mazeSize - 2;
	end.value = PATH;
	map[mazeSize - 1][mazeSize - 2].value = PATH;
	mapSize = mazeSize;
	
	int num = rand() % 3;
	if(num == 0)
	{
		DFS();
	}
	else if(num == 1)
	{
		int x = (rand() % (mazeSize - 2) + 1) | 1;
		int y = (rand() % (mazeSize - 2) + 1) | 1;
		DFS_generator(x,y);
	}
	else
	{
		Prim_generator();
	}
	return 0;
}

int CMazeMap::printMaze()
{
	for(int i = 0 ;i < mazeSize ; i++)
	{
		for(int j = 0;j < mazeSize; j++)
		{
			if(i == pepole.x && j == pepole.y)
				printf("%c",pepole.value);
			else
				printf("%c",map[i][j].value);
		}
		printf("\n");
	}
	return 0;
}

int CMazeMap::Move()
{
	cout << "use w a s d  represent up left down right move the @"<< endl;
	char ch;
	while(1)
	{
		ch = getchar();
		if(ch == '\n' || ch == EOF)
			break;
	}
	
	int x = pepole.x;
	int y = pepole.y;
	while(1)
	{
		system("clear");
		printMaze();
		cout << "move the @ use w a s d and quit the game use q"<< endl;
		fflush(stdout);
		ch = getchar();
		if(ch == 'w') 
		{//up
			x--;
		}
		else if(ch == 's')
		{//down
			x++;
		}
		else if(ch == 'a')
		{//left
			y--;
		}
		else if(ch == 'd')
		{//right
			y++;
		}
		else if(ch == 'q')
		{
			break;
		}
		
		if(x < 0 || x >= mazeSize || y < 0 || y >= mazeSize)
		{
			printf("cross the border,illegal move,row = %d,column = %d\n",x,y);
			continue;
		}
		
		if(map[x][y].value == WALL)
		{
			printf("this is wall,can not move,row = %d,column = %d\n",x,y);
			continue;
		}
		
		pepole.x = x;
		pepole.y = y;
		if(x == end.x && y== end.y)
		{
			cout << "congratulations to you win the game"<< endl;
			break;
		}
	}
	return 0;
}

int CMazeMap::findPath()
{
	int dir[4][2] = { 
		{ 1,0 },
		{ -1,0 },
		{ 0,-1 },
		{ 0,1 } 
	};
	
    SBox temp = start;
    listPath.push_back(start);
    int x = temp.x;
    int y = temp.y;
    while (!listPath.empty())
    {
        int i = 0;
        for (; i < 4; ++i)
        {
            if (x + dir[i][0] >= 0 
            	&& x + dir[i][0] <= mazeSize - 1 
            	&& y + dir[i][1] >= 0 
            	&& y + dir[i][1] <= mazeSize - 1
                && map[x + dir[i][0]][y + dir[i][1]].value == PATH )
            {
                map[x][y].value = FLAG;
                x += dir[i][0];
                y += dir[i][1];
                listPath.push_back(map[x][y]);
                if (x == end.x && y == end.y)
                {
                	return 0;
                }	
                break;
            }
        }
        // æ— è·¯å�¯èµ°æ—¶å›žæº¯
        if (i == 4)
        {
            map[x][y].value = FLAG;
            listPath.pop_back();
            if (!listPath.empty()) 
            {
            	x = listPath.back().x;
            	y = listPath.back().y;
            }
        }
    }
   
    for (int i = 1; i < mazeSize -1; i++)
    {
    	for (int j = 1; j < mazeSize -1; j++)
    	{
    		if (map[i][j].value == FLAG)
    			map[i][j].value = PATH;
    	}
    }
    
    return 0;
}

int CMazeMap::printPath()
{
    cout << endl << "the path is:" << endl;
    int i = 0;
    SBox tmp = listPath.back();
    listPath.pop_back();
    list<SBox>::iterator itr;
    for ( itr =  listPath.begin(); itr != listPath.end(); itr++)
    {
	    cout	<< "(" 
	    		<< (*itr).x 
	    		<< ", " 
	    		<< (*itr).y 
	    		<< ")" 
	    		<< " -> ";
	    i ++;
	    if( i == 10)
	    {
	    	i = 0;
	    	cout << endl;
	    }
    }

    if( i == 10)
    {
    	cout << endl;
    }
    cout	<< "(" 
    		<< tmp.x 
    		<< ", " 
    		<< tmp.y 
    		<< ")";
    cout << endl;
    return 0;
}

int CMazeMap::convertChar(char c,char* szTemp)
{
	if(c == PATH)
		strcpy(szTemp,"PATH");
	else if(c == WALL)
		strcpy(szTemp,"WALL");
	else if(c == PEPOLE)
		strcpy(szTemp,"PEPOLE");
	else
		strcpy(szTemp,"ERROR");	
	return 0;	
}

int CMazeMap::saveGame(const char* szFile)
{
    char szTemp[1024] = {0};
    char szConvert[64] = {0};
    std::ofstream f(szFile, std::ios::trunc);
    memset(szTemp,0,sizeof(szTemp));
    sprintf(szTemp,"%d\n",mapSize);
    f << szTemp;
    memset(szTemp,0,sizeof(szTemp));
    memset(szConvert,0,sizeof(szConvert));
    convertChar(start.value,szConvert);
    sprintf(szTemp,"%d,%d,%s\n",start.x,start.y,szConvert);
    f << szTemp;
    memset(szTemp,0,sizeof(szTemp));
    memset(szConvert,0,sizeof(szConvert));
    convertChar(end.value,szConvert);
    sprintf(szTemp,"%d,%d,%s\n",end.x,end.y,szConvert);
    f << szTemp;
    memset(szTemp,0,sizeof(szTemp));
    memset(szConvert,0,sizeof(szConvert));
    convertChar(pepole.value,szConvert);
    sprintf(szTemp,"%d,%d,%s\n",pepole.x,pepole.y,szConvert);
    f << szTemp;
    for(int i = 0;i < mazeSize -1;i++ )
    {
        string strValue = "";
    	for(int j = 0;j < mazeSize -1; j++)
    	{
            memset(szConvert,0,sizeof(szConvert));
            convertChar(map[i][j].value,szConvert);
            sprintf(szTemp,"%d,%d,%s|",map[i][j].x,map[i][j].y,szConvert);
            strValue += szTemp;
    	}
    	int len = strValue.length();
    	strValue[len - 1] = '\n';
    	f << strValue;	
    }
    f.close();
    
    return 0;
}

int CMazeMap::loadGame(const char* szFile)
{
    ifstream f(szFile);
    char szBuf[1024] = {0};
    string strMark = "|";
    vector<string> vecResult,vecResult1;
    int count = 0;
    while( f.getline(szBuf, 1024, '\n') )
    {
    	//x,y,value|x,y,value|x,y,value
    	if(strcmp(szBuf,"") == 0)
    		continue;
    	
    	count++;
    	vecResult.clear();
    	if(count <=4)
    	{
    		if(count == 1)
    			mapSize = atoi(szBuf);
    		if(count == 2)
    		{
    			strMark = ",";
    			str_split(szBuf, vecResult, strMark);
    			start.x = atoi(vecResult[0].c_str());
    			start.y = atoi(vecResult[1].c_str());
    			if(vecResult[2] == "PATH")
    				start.value = PATH;
    			else if(vecResult[2] == "WALL")
    				start.value = WALL;
    			else if(vecResult[2] == "PEPOLE")
    				start.value = PEPOLE;
    			else
    				printf("error value %s\n",vecResult[2].c_str());
    		}
    		if(count == 3)
    		{
    			strMark = ",";
    			str_split(szBuf, vecResult, strMark);
    			end.x = atoi(vecResult[0].c_str());
    			end.y = atoi(vecResult[1].c_str());
    			if(vecResult[2] == "PATH")
    				end.value = PATH;
    			else if(vecResult[2] == "WALL")
    				end.value = WALL;
    			else if(vecResult[2] == "PEPOLE")
    				end.value = PEPOLE;
    			else
    				printf("error value %s\n",vecResult[2].c_str());
    		}
    		if(count == 4)
    		{
    			strMark = ",";
    			str_split(szBuf, vecResult, strMark);
    			pepole.x = atoi(vecResult[0].c_str());
    			pepole.y = atoi(vecResult[1].c_str());
    			if(vecResult[2] == "PATH")
    				pepole.value = PATH;
    			else if(vecResult[2] == "WALL")
    				pepole.value = WALL;
    			else if(vecResult[2] == "PEPOLE")
    				pepole.value = PEPOLE;
    			else
    				printf("error value %s\n",vecResult[2].c_str());
    		}	
    		continue;
    	}
    	
		strMark = "|"; 
        str_split(szBuf, vecResult, strMark);
        if(vecResult.size() != mapSize - 1) 
		{
			printf("error mazeMap %s\n",szFile);
			return -1;
        }
     
        for(int i = 0; i < vecResult.size();i++)
        {
        	strMark = ",";
        	vecResult1.clear();
			str_split(vecResult[i],vecResult1, strMark);
			int x = atoi(vecResult1[0].c_str());
			int y =  atoi(vecResult1[1].c_str());
			if(vecResult1[2] == "PATH")
    			map[x][y].value = PATH;
			else if(vecResult1[2] == "WALL")
				map[x][y].value = WALL;
			else if(vecResult1[2] == "PEPOLE")
			{
				map[x][y].value = PATH;
				pepole.x = x;
				pepole.y = y;
				pepole.value = PEPOLE;
			}	
			else
				printf("error value %s\n",vecResult1[2].c_str());
        }	
    }
    f.close();
    return 0;
}


int main(int argc, char** argv) {
	srand((unsigned)time(NULL));
	string strFileName;
	vector<CMazeMap> vecMazeMap;
	char szTemp[256] = {0};
	//create five fix map
	for(int i = 0; i < 5;i ++)
	{
		sprintf(szTemp,"./fix_map_%02d.dat",i);
		CMazeMap mazeMap;
		if(access(szTemp,0) == 0)
		{
			mazeMap.loadGame(szTemp);
		}
		else
		{
			mazeMap.createMaze();
			mazeMap.saveGame(szTemp);
		}
		vecMazeMap.push_back(mazeMap);
	}
	
	int Menu;
	CMazeMap mazeMap;
	while(1)
	{
		system("clear");
		cout << "1. Begin game" << endl;
		cout << "2. Exit game" << endl;
		cout << "3. View path" << endl;
		cin >> Menu;
		if(Menu == 1)
		{
			system("clear");
			cout << "1. Fixed pathway" << endl;
			cout << "2. Random pathway" << endl;
			cout << "3. Pathway which save last" << endl;
			int choice;
			cin >> choice;
			if(choice == 1)
			{
				system("clear");
				cout<<"There are 5 fixed pathways, select one pathway you want"<<endl;
				cout<<"1. The first pathway"<<endl;
				cout<<"2. The second pathway"<<endl;
				cout<<"3. The third pathway"<<endl;
				cout<<"4. The fourth pathway"<<endl;
				cout<<"5. The fifth pathway"<<endl;
				int num;
				cin >> num;
				mazeMap = vecMazeMap[num-1];	
			}
			else if(choice == 2)
			{
				system("clear");
				mazeMap.init();
				mazeMap.createMaze();
			}
			else if(choice == 3)
			{
				mazeMap.loadGame("./saved.dat");
			}
			else
			{
				printf("error choice\n");
				continue;
			}
			system("clear");
			mazeMap.Move();
		}
		else if(Menu == 2)
		{
			system("clear");
			cout << "Save the map" << endl;
			cout << "1. Yes" << endl;
			cout << "2. No" << endl;
			int num;
			cin >> num;
			if(num == 1)
				mazeMap.saveGame("./saved.dat");
			break;
		}
		else if(Menu == 3)
		{
			mazeMap.findPath();
			mazeMap.printPath();
		}		
	}
	vecMazeMap.clear();
        
        return 0;
}

int trim_left(string &somestr)
{
    int iPos = 0;
    for(; iPos < somestr.length(); iPos++)
    {
        int iCur = somestr[iPos];
        if(iCur != ' ' && iCur != '\t' && iCur != '\r'&& iCur != '\n') 
                break;
    }
    somestr = somestr.substr(iPos);
    return 0;
}

int trim_right(string &somestr)
{
    int iPos = somestr.length();
    for(; iPos > 0; iPos--)
    {
        int iCur = somestr[iPos-1];
        if(iCur != ' ' && iCur != '\t' && iCur != '\r'&& iCur != '\n') break;
    }
    somestr = somestr.substr(0, iPos);
    return 0;
}

int trim(string &somestr)
{
    trim_left(somestr);
    trim_right(somestr);
    return 0;
}

int str_split (string strObject, vector<string>& vecResult,string strMark)
{
    if(strObject.empty ()) return 1;
    if(strMark.empty ()) return 1;

    char *pTemp,*pOpt;
    int iObject,iMark;

    iMark = strMark.size ();
    iObject = strObject.size ();
    pOpt = (char *)strObject.c_str ();

    for(int i = 0; i < iObject; i++)
    {
        if(strObject[i] == ' ') continue;

        int iRes;
        string strRes;
        pTemp = strstr(pOpt + i, strMark.c_str ());
        if(pTemp)
        {
            strRes = strObject.substr (i, pTemp - pOpt - i);
            i = pTemp - pOpt + iMark - 1;
        }
        else
        {
            strRes = strObject.substr (i);
            i = iObject - 1;
        }
        for(iRes = strRes.size (); iRes > 0; iRes--)
            if(strRes[iRes-1] != ' ') break;
        strRes = strRes.substr (0, iRes);
		trim(strRes);
        vecResult.push_back(strRes);
    }
    return 0;
}


